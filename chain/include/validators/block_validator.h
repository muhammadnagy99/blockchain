#ifndef BLOCK_VALIDATOR_H
#define BLOCK_VALIDATOR_H

#include "interfaces/iblock_validator.h"

class BlockValidator : public IBlockValidator {
public:
    bool is_valid_block(const Block& new_block, const Block& prev_block) override;
    bool is_valid_chain(const std::vector<Block>& chain) override;
};

#endif // BLOCK_VALIDATOR_H
