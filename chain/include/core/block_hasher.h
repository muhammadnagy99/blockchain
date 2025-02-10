#ifndef BLOCK_HASHER_H
#define BLOCK_HASHER_H

#include "interfaces/iblock_header.h"
#include "interfaces/iblock_body.h"
#include <string>

class BlockHasher {
public:
    static std::string calculate_hash(const IBlockHeader& header, const IBlockBody& body);
};

#endif // BLOCK_HASHER_H
