#ifndef ITRANSACTIONPOOL_H
#define ITRANSACTIONPOOL_H

#include "transaction.h"
#include <vector>

class ITransactionPool {
public:
    virtual void add_transaction(const Transaction& tx) = 0;
    virtual std::vector<Transaction> get_pending_transactions() const = 0;
    virtual ~ITransactionPool() = default;
};

#endif // ITRANSACTIONPOOL_H
