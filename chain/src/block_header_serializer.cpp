#include "serializers/block_header_serializer.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string BlockHeaderSerializer::serialize(const BlockHeader& header) {
    json j;
    j["timestamp"] = header.get_timestamp();
    j["previous_hash"] = header.get_previous_hash();
    j["block_hash"] = header.get_hash();
    j["nonce"] = header.get_nonce();
    j["merkle_root"] = header.get_merkle_root();


    return j.dump(); 
}

BlockHeader BlockHeaderSerializer::deserialize(const std::string& json_data) {
    json j = json::parse(json_data);

    return BlockHeader(
        j["timestamp"],
        j["previous_hash"],
        j["nonce"],
        j["merkle_root"],
        j["block_hash"]
    );
}
