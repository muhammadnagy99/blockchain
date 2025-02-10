#ifndef BLOCKBODY_H
#define BLOCKBODY_H

#include <vector>
#include "transaction.h"

class BlockBody {
private:
    std::vector<Transaction> transactions;

public:
    BlockBody();

    std::vector<Transaction> get_transactions() const;
    
    void add_transaction(const Transaction& transaction);
};

#endif // BLOCKBODY_H
