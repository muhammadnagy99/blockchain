#ifndef IMINER_H
#define IMINER_H

#include "block.h"
#include "transaction.h"


class IMiner {
public:
    virtual Block mine_block(const Block& previous_block, const std::vector<Transaction>& transactions) = 0;
    virtual ~IMiner() = default;
};

#endif // IMINER_H
