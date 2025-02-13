#ifndef BLOCK_SERIALIZER_H
#define BLOCK_SERIALIZER_H

#include "core/block.h"
#include <string>

class BlockSerializer {
public:
    static std::string serialize(const Block& block);
    static Block deserialize(const std::string& json_data);
};

#endif // BLOCK_SERIALIZER_H
