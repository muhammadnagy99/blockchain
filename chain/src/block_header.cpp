#include "core/block_header.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

BlockHeader::BlockHeader(std::time_t timestamp, const std::string& previous_hash, uint32_t nonce, const std::string& merkle_root)
    : timestamp(timestamp == 0 ? std::time(nullptr) : timestamp), previous_hash(previous_hash), nonce(nonce), merkle_root(merkle_root) {
    
    if (!previous_hash.empty() && previous_hash.length() != 64) {
        throw std::invalid_argument("Invalid previous hash: must be 64 characters (SHA-256) or empty for genesis block.\n");
    }
    if (merkle_root.length() != 64) {
        throw std::invalid_argument("Invalid merkle root: must be 64 characters (SHA-256).\n");
    }
}

std::time_t BlockHeader::get_timestamp() const {
    return timestamp;
}

std::string BlockHeader::get_previous_hash() const {
    return previous_hash;
}

uint32_t BlockHeader::get_nonce() const {
    return nonce;
}

std::string BlockHeader::get_merkle_root() const{
    return merkle_root;
}
