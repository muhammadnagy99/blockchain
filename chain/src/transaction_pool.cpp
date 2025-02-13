#include "transaction/transaction_pool.h"
#include "core/transaction.h"
#include <nlohmann/json.hpp>
#include <rocksdb/db.h>
#include <rocksdb/options.h>
#include <iostream>
#include <thread>
#include <future>

using json = nlohmann::json;

TransactionPool::TransactionPool(const std::string &db_path, std::function<void()> mine_callback)
    : mine_callback(mine_callback), last_mine_time(std::chrono::steady_clock::now())
{
    rocksdb::Options options;
    options.create_if_missing = true;

    rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);
    if (!status.ok())
    {
        throw std::runtime_error("Failed to open RocksDB: " + status.ToString());
    }

    load_transactions_from_db();
}

void TransactionPool::load_transactions_from_db()
{
    std::string tx_list_json;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), "pending_transactions", &tx_list_json);

    if (status.ok() && !tx_list_json.empty())
    {
        json tx_ids = json::parse(tx_list_json);
        for (const auto &tx_id : tx_ids)
        {
            std::string tx_json;
            if (db->Get(rocksdb::ReadOptions(), "tx_" + tx_id.get<std::string>(), &tx_json).ok())
            {
                pending_transactions.emplace_back(json::parse(tx_json));
            }
        }
    }
}

void TransactionPool::add_transaction(const Transaction &tx)
{
    pending_transactions.push_back(tx);

    save_transaction_to_db(tx);

    if (!mining_in_progress.test_and_set(std::memory_order_acquire))
    {
        std::thread([this]()
                    {
                        this->check_mining_condition();
                        mining_in_progress.clear(std::memory_order_release);
                    })
            .detach();
    }
}

void TransactionPool::save_transaction_to_db(const Transaction &tx)
{
    std::string tx_id = tx.get_transaction_id();
    db->Put(rocksdb::WriteOptions(), "tx_" + tx_id, tx.to_json().dump());

    json tx_list = json::array();
    for (const auto &t : pending_transactions)
    {
        tx_list.push_back(t.get_transaction_id());
    }
    db->Put(rocksdb::WriteOptions(), "pending_transactions", tx_list.dump());
}

std::vector<Transaction> TransactionPool::get_pending_transactions() const
{
    return pending_transactions;
}

std::vector<Transaction> TransactionPool::get_mining_transactions() const
{
    return mining_queue;
}

size_t TransactionPool::get_pending_transaction_count() const
{
    return pending_transactions.size();
}

size_t TransactionPool::get_pending_transactions_size() const
{
    size_t total_size = 0;
    for (const auto &tx : pending_transactions)
    {
        total_size += tx.to_json().size();
    }
    return total_size;
}

void TransactionPool::check_mining_condition()
{
    size_t tx_count = get_pending_transaction_count();
    size_t tx_size = get_pending_transactions_size();
    auto now = std::chrono::steady_clock::now();

    if (is_mining)
    {
        // std::cout << "[Auto-Mining] Mining already in progress. Queuing new transactions." << std::endl;
        return;
    }

    if (tx_count >= 10)
    {
        // std::cout << "[Auto-Mining] Triggered: 10 transactions reached." << std::endl;
        mining_queue = std::move(pending_transactions);
        pending_transactions.clear();
        mine_callback();
        return;
    }

    if (std::chrono::duration_cast<std::chrono::minutes>(now - last_mine_time).count() >= 5)
    {
        // std::cout << "[Auto-Mining] Triggered: 5-minute interval reached." << std::endl;
        mining_queue = std::move(pending_transactions);
        pending_transactions.clear();
        mine_callback();
        return;
    }
}

void TransactionPool::clear_mined_transactions(const std::vector<std::string> &mined_tx_ids)
{
    mining_queue.erase(
        std::remove_if(mining_queue.begin(), mining_queue.end(),
                       [&](const Transaction &tx)
                       {
                           return std::find(mined_tx_ids.begin(), mined_tx_ids.end(), tx.get_transaction_id()) != mined_tx_ids.end();
                       }),
        mining_queue.end());

    for (const auto &tx_id : mined_tx_ids)
    {
        remove_transaction_from_db(tx_id);
    }

    json tx_list = json::array();
    for (const auto &t : pending_transactions)
    {
        tx_list.push_back(t.get_transaction_id());
    }
    db->Put(rocksdb::WriteOptions(), "pending_transactions", tx_list.dump());
}

void TransactionPool::remove_transaction_from_db(const std::string &tx_id)
{
    db->Delete(rocksdb::WriteOptions(), "tx_" + tx_id);
}

void TransactionPool::mining_completed()
{
    is_mining = false;
    // std::cout << "[Auto-Mining] Mining completed. Checking for new transactions..." << std::endl;

    if (!pending_transactions.empty())
    {
        check_mining_condition();
    }
}

TransactionPool::~TransactionPool()
{
    delete db.release();
}