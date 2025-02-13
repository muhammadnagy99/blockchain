#ifndef BLOCK_BODY_SERIALIZER_H
#define BLOCK_BODY_SERIALIZER_H

#include "core/block_body.h"
#include <nlohmann/json.hpp>
#include <string>

class BlockBodySerializer {
public:
    static std::string serialize(const BlockBody& body);

    static BlockBody deserialize(const std::string& json_data);
};

#endif // BLOCK_BODY_SERIALIZER_H
