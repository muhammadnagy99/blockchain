#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "core/block.h"
#include "interfaces/itransaction_pool.h"
#include "interfaces/iblock_validator.h"
#include "interfaces/iminer.h"
#include <rocksdb/db.h>
#include <memory>
#include <string>

const std::string GENESIS_MERKLE_ROOT = "6fe8b9a48e39b91c6c0c0ea843e92b63fbe789e27594f7b3e3b7522b5d3f8b63";
const std::string GENESIS_HASH = "6fe8b9a48e39b91c6c0c000043e92b63fbe789e27594f7b3e3b7522b5d3f8b63";

class Blockchain
{
private:
    std::unique_ptr<rocksdb::DB> db;
    std::unique_ptr<ITransactionPool> transaction_pool;
    std::unique_ptr<IBlockValidator> block_validator;
    std::unique_ptr<IMiner> miner;
    bool transaction_pool_set = false;

    int get_latest_block_height() const;
    void set_latest_block_height(int height);
    void store_block(const Block &block);
    Block fetch_block(int height) const;

    BlockHeader get_block_header(int height) const;
    BlockBody get_block_body_by_merkle_root(const std::string &merkle_root) const;

    std::vector<std::string> extract_transaction_ids(const std::vector<Transaction> &transactions) const;
    void notify_mining_completed();

public:
    Blockchain(std::unique_ptr<ITransactionPool> tp,
               std::unique_ptr<IBlockValidator> bv,
               std::unique_ptr<IMiner> m,
               const std::string &db_path);

    bool is_valid() const;
    void mine_block();

    void set_transaction_pool(std::unique_ptr<ITransactionPool> tp);
    ITransactionPool &get_transaction_pool() const;

    Block get_latest_block() const;
    Block get_block(int height) const;
    Block get_block_by_hash(const std::string &hash) const;
    std::vector<std::string> get_chain() const;


    ~Blockchain();
};

#endif // BLOCKCHAIN_H