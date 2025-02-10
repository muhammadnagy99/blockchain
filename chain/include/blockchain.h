#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "transaction.h"
#include <vector>

class Blockchain {
private:
    std::vector<Block> chain;
    std::vector<Transaction> pending_transactions;

public:
    Blockchain();

    void add_block(const Block& block);
    Block get_latest_block() const;
    bool is_valid() const;
    bool is_valid_new_block(const Block& new_block) const;
    void add_transaction(const Transaction& transaction);
    void mine_block();
};

#endif // BLOCKCHAIN_H