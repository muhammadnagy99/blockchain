#include "core/block_body.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>

void BlockBody::add_data(std::unique_ptr<BodyData> data)
{
    data_entries.push_back(std::move(data));
}

std::vector<std::string> BlockBody::get_data_strings() const
{
    std::vector<std::string> data_strings;
    for (const auto &data : data_entries)
    {
        data_strings.push_back(data->to_string());
    }
    return data_strings;
}

std::string sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    std::ostringstream hash_string;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hash_string << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return hash_string.str();
}

std::string compute_merkle_root(std::vector<std::string> leaves) {
    if (leaves.empty()) return "EMPTY_MERKLE_ROOT";

    while (leaves.size() > 1) {
        std::vector<std::string> new_level;

        for (size_t i = 0; i < leaves.size(); i += 2) {
            if (i + 1 < leaves.size()) {
                new_level.push_back(sha256(leaves[i] + leaves[i + 1]));
            } else {
                new_level.push_back(sha256(leaves[i] + leaves[i])); 
            }
        }
        leaves = new_level;
    }
    return leaves.front();
}

std::string BlockBody::get_merkle_root() const {
    std::vector<std::string> leaves = get_data_strings();
    for (auto &leaf : leaves) {
        leaf = sha256(leaf); 
    }
    return compute_merkle_root(leaves);
}

const std::vector<std::unique_ptr<BodyData>>& BlockBody::get_data_entries() const {
    return data_entries;
}

