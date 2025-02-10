#include "core/block_hasher.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::string BlockHasher::calculate_hash(const IBlockHeader& header, const IBlockBody& body) {
    std::ostringstream oss;
    oss << header.get_previous_hash()
        << header.get_timestamp()
        << header.get_nonce()
        << header.get_merkle_root();

    std::string data = oss.str(); 

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    std::ostringstream hash_string;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hash_string << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return hash_string.str(); 
}
