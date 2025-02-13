#include "core/blockchain.h"
#include "serializers/block_header_serializer.h"
#include "serializers/block_body_serializer.h"
#include <iostream>
#include <stdexcept>
#include <rocksdb/db.h>
#include <rocksdb/write_batch.h>

Blockchain::Blockchain(std::unique_ptr<ITransactionPool> tp,
                       std::unique_ptr<IBlockValidator> bv,
                       std::unique_ptr<IMiner> m,
                       const std::string &db_path)
    : transaction_pool(std::move(tp)), block_validator(std::move(bv)), miner(std::move(m))
{
    rocksdb::Options options;
    options.create_if_missing = true;

    rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db);

    if (!status.ok())
    {
        throw std::runtime_error("Failed to open RocksDB: " + status.ToString());
    }

    if (get_latest_block_height() == -1)
    {
        std::cout << "[Blockchain] No blocks found. Creating Genesis Block." << std::endl;
        BlockHeader genesis_header(time(nullptr), "", 0, GENESIS_MERKLE_ROOT, GENESIS_HASH);
        Block genesis_block(std::make_unique<BlockHeader>(genesis_header), std::make_unique<BlockBody>());
        store_block(genesis_block);
        set_latest_block_height(0);
    }
}

void Blockchain::set_transaction_pool(std::unique_ptr<ITransactionPool> tp)
{
    if (transaction_pool_set)
    {
        throw std::runtime_error("[Security] Transaction pool has already been set and cannot be modified.");
    }
    if (!tp)
    {
        throw std::invalid_argument("[Blockchain] Cannot set a null TransactionPool.");
    }

    transaction_pool = std::move(tp);
    transaction_pool_set = true;
}

ITransactionPool &Blockchain::get_transaction_pool() const
{
    if (!transaction_pool)
    {
        throw std::runtime_error("[Blockchain] Transaction pool is not set.");
    }
    return *transaction_pool;
}

int Blockchain::get_latest_block_height() const
{
    std::string height_str;
    rocksdb::Status status = db->Get(rocksdb::ReadOptions(), "latest_block", &height_str);
    return status.ok() ? std::stoi(height_str) : -1;
}

void Blockchain::set_latest_block_height(int height)
{
    db->Put(rocksdb::WriteOptions(), "latest_block", std::to_string(height));
}

void Blockchain::store_block(const Block &block)
{
    rocksdb::WriteBatch batch;

    const BlockHeader *header = dynamic_cast<const BlockHeader *>(&block.get_header());
    if (!header)
    {
        throw std::runtime_error("Failed to cast IBlockHeader to BlockHeader.");
    }
    // std::cout << "Storing Start" << std::endl;

    std::string header_json = BlockHeaderSerializer::serialize(*header);
    batch.Put("header_" + std::to_string(get_latest_block_height() + 1), header_json);
    batch.Put("header_" + header->get_hash(), header_json);

    // std::cout << "Header stored" << std::endl;

    const BlockBody *body = dynamic_cast<const BlockBody *>(&block.get_body());
    if (!body)
    {
        throw std::runtime_error("Failed to cast IBlockBody to BlockBody.");
    }


    std::string body_json = BlockBodySerializer::serialize(*body);

    batch.Put("body_" + header->get_merkle_root(), body_json);


    rocksdb::Status status = db->Write(rocksdb::WriteOptions(), &batch);
    if (!status.ok())
    {
        throw std::runtime_error("Failed to store block: " + status.ToString());
    }
}

Block Blockchain::fetch_block(int height) const
{
    std::string header_json;
    if (!db->Get(rocksdb::ReadOptions(), "header_" + std::to_string(height), &header_json).ok())
    {
        throw std::runtime_error("Block at height " + std::to_string(height) + " not found.");
    }


    BlockHeader header = BlockHeaderSerializer::deserialize(header_json);

    BlockBody body = get_block_body_by_merkle_root(header.get_merkle_root());

    return Block(std::make_unique<BlockHeader>(header), std::make_unique<BlockBody>(std::move(body)));
}

BlockHeader Blockchain::get_block_header(int height) const
{
    std::string header_json;
    if (!db->Get(rocksdb::ReadOptions(), "header_" + std::to_string(height), &header_json).ok())
    {
        throw std::runtime_error("Block header at height " + std::to_string(height) + " not found.");
    }
    return BlockHeaderSerializer::deserialize(header_json);
}

Block Blockchain::get_block_by_hash(const std::string &hash) const
{
    std::string header_json;
    if (!db->Get(rocksdb::ReadOptions(), "header_" + hash, &header_json).ok())
    {
        throw std::runtime_error("Block with hash " + hash + " not found.");
    }

    BlockHeader header = BlockHeaderSerializer::deserialize(header_json);
    BlockBody body = get_block_body_by_merkle_root(header.get_merkle_root());

    return Block(std::make_unique<BlockHeader>(std::move(header)), std::make_unique<BlockBody>(std::move(body)));
}

BlockBody Blockchain::get_block_body_by_merkle_root(const std::string &merkle_root) const
{
    std::string body_json;
    if (!db->Get(rocksdb::ReadOptions(), "body_" + merkle_root, &body_json).ok())
    {
        throw std::runtime_error("Block body with Merkle root " + merkle_root + " not found.");
    }

    return BlockBodySerializer::deserialize(body_json);
}

std::vector<std::string> Blockchain::extract_transaction_ids(const std::vector<Transaction> &transactions) const
{
    std::vector<std::string> tx_ids;
    for (const auto &tx : transactions)
    {
        tx_ids.push_back(tx.get_transaction_id());
    }
    return tx_ids;
}

bool Blockchain::is_valid() const
{
    return block_validator->is_valid_chain(db.get());
}

void Blockchain::mine_block()
{
    std::vector<Transaction> transactions = transaction_pool->get_mining_transactions();
    if (transactions.empty())
    {
        std::cout << "[Mining] No transactions available for mining." << std::endl;
        return;
    }

    BlockHeader prev_header = get_block_header(get_latest_block_height());
    Block new_block = miner->mine_block(prev_header, transactions);
    store_block(new_block);
    transaction_pool->clear_mined_transactions(extract_transaction_ids(transactions));
    set_latest_block_height(get_latest_block_height() + 1);
    notify_mining_completed();
}

void Blockchain::notify_mining_completed()
{
    // std::cout << "[Mining] Mining process completed. Checking for new transactions..." << std::endl;
    transaction_pool->mining_completed();
}

Block Blockchain::get_latest_block() const
{
    return fetch_block(get_latest_block_height());
}

Block Blockchain::get_block(int height) const
{
    return fetch_block(height);
}

std::vector<std::string> Blockchain::get_chain() const
{
    std::vector<std::string> blocks;
    int latest_height = get_latest_block_height();

    for (int height = 0; height <= latest_height; ++height)
    {
        blocks.push_back(get_block(height).to_json());
    }

    return blocks;
}


Blockchain::~Blockchain() {
    delete db.release();
}
