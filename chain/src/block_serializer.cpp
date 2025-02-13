#include "serializers/block_serializer.h"
#include <nlohmann/json.hpp> 
#include "core/block_header.h"
#include "core/block_body.h"
#include "core/transaction.h"
using json = nlohmann::json;

std::string BlockSerializer::serialize(const Block& block) {
    json j;
    j["header"]["previous_hash"] = block.get_header().get_previous_hash();
    j["header"]["block_hash"] = block.get_header().get_hash();
    j["header"]["timestamp"] = block.get_header().get_timestamp();
    j["header"]["nonce"] = block.get_header().get_nonce();
    j["header"]["merkle_root"] = block.get_header().get_merkle_root();

    std::vector<json> transactions;
    for (const auto& data_entry : block.get_body().get_data_entries()) {  
        transactions.push_back(dynamic_cast<const Transaction&>(*data_entry).to_json()); 
    }
    j["body"]["transactions"] = transactions;

    return j.dump();
}


Block BlockSerializer::deserialize(const std::string& json_data) {
    json j = json::parse(json_data);

    std::unique_ptr<IBlockHeader> header = std::make_unique<BlockHeader>(
        j["header"]["timestamp"], 
        j["header"]["previous_hash"], 
        j["header"]["nonce"], 
        j["header"]["merkle_root"],
        j["header"]["block_hash"] 
    );

    std::unique_ptr<BlockBody> body = std::make_unique<BlockBody>();
    for (const auto& tx_json : j["body"]["transactions"]) {
        body->add_data(std::make_unique<Transaction>(tx_json)); 
    }

    return Block(std::move(header), std::move(body));
}
