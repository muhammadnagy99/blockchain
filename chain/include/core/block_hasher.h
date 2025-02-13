#ifndef BLOCK_HASHER_H
#define BLOCK_HASHER_H

#include "interfaces/iblock_header.h"
#include "interfaces/iblock_body.h"
#include <string>

class BlockHasher {
public:
    static std::string calculate_hash(const IBlockHeader& header);
    static std::string calculate_hash(const std::string& previous_hash, std::time_t timestamp, uint32_t nonce, const std::string& merkle_root);
};

#endif // BLOCK_HASHER_H
