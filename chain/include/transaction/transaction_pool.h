#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include "core/transaction.h"
#include "interfaces/itransaction_pool.h"
#include <rocksdb/db.h>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>

class TransactionPool : public ITransactionPool
{
private:
    std::unique_ptr<rocksdb::DB> db;
    std::vector<Transaction> pending_transactions;
    std::vector<Transaction> mining_queue;
    std::chrono::time_point<std::chrono::steady_clock> last_mine_time;
    std::function<void()> mine_callback;
    bool is_mining = false;
    std::atomic_flag mining_in_progress = ATOMIC_FLAG_INIT; 

    void load_transactions_from_db();
    void save_transaction_to_db(const Transaction &tx);
    void remove_transaction_from_db(const std::string &tx_id);
    void check_mining_condition();

public:
    TransactionPool(const std::string &db_path, std::function<void()> mine_callback);

    void add_transaction(const Transaction &tx) override;
    std::vector<Transaction> get_pending_transactions() const override;
    std::vector<Transaction> get_mining_transactions() const;
    void clear_mined_transactions(const std::vector<std::string> &mined_tx_ids);
    size_t get_pending_transaction_count() const;
    size_t get_pending_transactions_size() const;
    void mining_completed();

    ~TransactionPool();
};

#endif // TRANSACTIONPOOL_H
