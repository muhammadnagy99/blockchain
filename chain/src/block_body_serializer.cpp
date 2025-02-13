#include "serializers/block_body_serializer.h"
#include <nlohmann/json.hpp>
#include "core/transaction.h"
#include <iostream>

using json = nlohmann::json;

std::string BlockBodySerializer::serialize(const BlockBody &body)
{
    json j;
    std::vector<std::string> transactions;

    // std::cout << "Serialize start" << std::endl;
    for (const auto &data_entry : body.get_data_entries())
    {
        transactions.push_back(dynamic_cast<const Transaction &>(*data_entry).to_json().dump());
    }
    // std::cout << "Serialize end" << std::endl;

    j["transactions"] = transactions;

    return j.dump();
}

BlockBody BlockBodySerializer::deserialize(const std::string &json_data)
{
    json j = json::parse(json_data);

    BlockBody body;

    for (const auto &raw_tx_json : j["transactions"])
    {
        json tx_json;

        if (raw_tx_json.is_string())
        {
            tx_json = json::parse(raw_tx_json.get<std::string>());
        }
        else
        {
            tx_json = raw_tx_json; 
        }

        if (!tx_json.contains("sender") || !tx_json.contains("receiver") ||
            !tx_json.contains("amount") || !tx_json.contains("transaction_id"))
        {
            std::cerr << "Error: Missing required transaction fields!" << std::endl;
            continue;
        }

        body.add_data(std::make_unique<Transaction>(tx_json));
    }

    return body;
}
