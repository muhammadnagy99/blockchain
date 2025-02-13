#include "core/block_header.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

BlockHeader::BlockHeader(std::time_t timestamp, const std::string &previous_hash, uint32_t nonce, const std::string &merkle_root, const std::string &block_hash)
    : timestamp(timestamp == 0 ? std::time(nullptr) : timestamp), previous_hash(previous_hash), nonce(nonce), merkle_root(merkle_root), block_hash(block_hash)
{
    const std::string GENESIS_MERKLE_ROOT = "6fe8b9a48e39b91c6c0c0ea843e92b63fbe789e27594f7b3e3b7522b5d3f8b63";
    if (previous_hash.empty())
    {
        if (merkle_root != GENESIS_MERKLE_ROOT)
        {
            throw std::invalid_argument("Invalid Genesis block: Merkle root must be the predefined Genesis root.\n");
        }
    }
    else
    {
        if (previous_hash.length() != 64)
        {
            throw std::invalid_argument("Invalid previous hash: must be 64 characters (SHA-256).\n");
        }
        if (merkle_root.length() != 64)
        {
            throw std::invalid_argument("Invalid merkle root: must be 64 characters (SHA-256).\n");
        }
    }
}

std::time_t BlockHeader::get_timestamp() const
{
    return timestamp;
}

std::string BlockHeader::get_previous_hash() const
{
    return previous_hash;
}

std::string BlockHeader::get_hash() const
{
    return block_hash;
}

uint32_t BlockHeader::get_nonce() const
{
    return nonce;
}

std::string BlockHeader::get_merkle_root() const
{
    return merkle_root;
}
