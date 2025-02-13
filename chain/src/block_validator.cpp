#include "validators/block_validator.h"
#include "serializers/block_header_serializer.h"
#include "serializers/block_body_serializer.h"
#include "core/block_hasher.h"
#include <rocksdb/db.h>
#include <iostream>
#include <sstream>

const int DIFFICULTY = 4;  

bool BlockValidator::is_valid_block(const BlockHeader& new_header, const BlockHeader& prev_header) {

    if (new_header.get_previous_hash() != prev_header.get_hash()) {
        std::cout << "[Validation] Failed Block's previous hash mismatch!\n";
        return false;
    }

    std::string computed_hash = BlockHasher::calculate_hash(new_header);
    if (computed_hash != new_header.get_hash()) {
        std::cout << "[Validation] Failed Block hash does not match computed hash!\n";
        return false;
    }

    if (!is_valid_proof_of_work(new_header)) {
        std::cout << "[Validation] Failed Block fails Proof of Work check!\n";
        return false;
    }

    if (new_header.get_timestamp() < prev_header.get_timestamp()) {
        std::cout << "[Validation] Failed Block timestamp is earlier than previous block!\n";
        return false;
    }

    std::cout << "[Validation] Success Block is valid!\n";
    return true;
}

bool BlockValidator::is_valid_chain(rocksdb::DB* db) {
    rocksdb::Status status;
    std::string latest_height_str;

    status = db->Get(rocksdb::ReadOptions(), "latest_block", &latest_height_str);
    if (!status.ok()) {
        std::cerr << "[Validation] Failed Failed to retrieve latest block height!\n";
        return false;
    }

    int latest_height = std::stoi(latest_height_str);
    std::string current_hash, previous_hash, header_json;

    status = db->Get(rocksdb::ReadOptions(), "header_" + std::to_string(latest_height), &header_json);
    if (!status.ok()) {
        std::cerr << "[Validation] Failed Failed to retrieve latest block header!\n";
        return false;
    }

    BlockHeader current_header = BlockHeaderSerializer::deserialize(header_json);

    for (int height = latest_height; height > 0; --height) {
        previous_hash = current_header.get_previous_hash();

        status = db->Get(rocksdb::ReadOptions(), "header_" + previous_hash, &header_json);
        if (!status.ok()) {
            std::cerr << "[Validation] Failed Missing previous block at height " << height - 1 << "\n";
            return false;
        }

        BlockHeader previous_header = BlockHeaderSerializer::deserialize(header_json);

        if (!is_valid_block(current_header, previous_header)) {
            return false;
        }

        current_header = previous_header;
    }

    std::cout << "[Validation] Success Blockchain is fully valid!\n";
    return true;
}

bool BlockValidator::is_valid_body(const BlockHeader& header, const BlockBody& body) {
    if (header.get_merkle_root() != body.get_merkle_root()) {
        std::cerr << "[Validation] Failed Block body Merkle root mismatch!\n";
        return false;
    }

    std::cout << "[Validation] Success Block body is valid!\n";
    return true;
}

bool BlockValidator::is_valid_proof_of_work(const BlockHeader& header) {
    return header.get_hash().substr(0, DIFFICULTY) == std::string(DIFFICULTY, '0');
}
