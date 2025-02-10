#ifndef IBLOCKVALIDATOR_H
#define IBLOCKVALIDATOR_H

#include "block.h"

class IBlockValidator {
public:
    virtual bool is_valid_block(const Block& new_block, const Block& prev_block) = 0;
    virtual bool is_valid_chain(const std::vector<Block>& chain) = 0;
    virtual ~IBlockValidator() = default;
};

#endif // IBLOCKVALIDATOR_H
