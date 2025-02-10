#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "itransaction_pool.h"
#include "iblock_validator.h"
#include "iminer.h"
#include <vector>
#include <memory>

class Blockchain
{
private:
    std::vector<Block> chain;
    std::unique_ptr<ITransactionPool> transaction_pool;
    std::unique_ptr<IBlockValidator> block_validator;
    std::unique_ptr<IMiner> miner;

public:
    Blockchain(std::unique_ptr<ITransactionPool> tp,
               std::unique_ptr<IBlockValidator> bv,
               std::unique_ptr<IMiner> m);

    void add_transaction(const Transaction &tx);
    bool is_valid() const;

    void mine_block();

    Block get_latest_block() const;
};

#endif // BLOCKCHAIN_H
