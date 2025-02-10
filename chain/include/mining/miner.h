#ifndef SIMPLEMINER_H
#define SIMPLEMINER_H

#include "iminer.h"

class Miner : public IMiner {
public:
    Block mine_block(const Block& previous_block, const std::vector<Transaction>& transactions) override;
};

#endif // SIMPLEMINER_H
