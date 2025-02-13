#ifndef MINER_H
#define MINER_H

#include "interfaces/iminer.h"

class Miner : public IMiner {
public:
    Block mine_block(const IBlockHeader& previous_header, const std::vector<Transaction>& transactions);
};

#endif // MINER_H
