#ifndef BLOCK_HEADER_SERIALIZER_H
#define BLOCK_HEADER_SERIALIZER_H

#include "core/block_header.h"
#include <nlohmann/json.hpp>
#include <string>

class BlockHeaderSerializer {
public:
    static std::string serialize(const BlockHeader& header);

    static BlockHeader deserialize(const std::string& json_data);
};

#endif // BLOCK_HEADER_SERIALIZER_H
