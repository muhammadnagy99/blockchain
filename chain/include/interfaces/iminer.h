#ifndef IMINER_H
#define IMINER_H

#include "core/block.h"
#include "core/transaction.h"


class IMiner {
public:
    virtual  Block mine_block(const IBlockHeader& previous_header, const std::vector<Transaction>& transactions) = 0;
    virtual ~IMiner() = default;
};

#endif // IMINER_H
