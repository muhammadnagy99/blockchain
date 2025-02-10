#ifndef TRANSACTIONPOOL_H
#define TRANSACTIONPOOL_H

#include "itransaction_pool.h"
#include <vector>

class TransactionPool : public ITransactionPool {
private:
    std::vector<Transaction> pending_transactions;

public:
    void add_transaction(const Transaction& tx) override;
    std::vector<Transaction> get_pending_transactions() const override;
};

#endif // TRANSACTIONPOOL_H
