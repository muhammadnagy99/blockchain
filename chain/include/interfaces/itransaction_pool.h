#ifndef ITRANSACTIONPOOL_H
#define ITRANSACTIONPOOL_H

#include "core/transaction.h"
#include <vector>

class ITransactionPool {
public:
    virtual void add_transaction(const Transaction& tx) = 0;
    virtual std::vector<Transaction> get_pending_transactions() const = 0;
    virtual std::vector<Transaction> get_mining_transactions() const = 0;
    virtual void clear_mined_transactions(const std::vector<std::string> &mined_tx_ids) = 0;
    virtual void mining_completed() = 0;
    virtual size_t get_pending_transaction_count() const = 0;
    virtual size_t get_pending_transactions_size() const = 0;
    virtual ~ITransactionPool() = default;
};

#endif // ITRANSACTIONPOOL_H
