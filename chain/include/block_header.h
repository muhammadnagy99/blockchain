#ifndef BLOCKHEADER_H
#define BLOCKHEADER_H

#include <string>
#include <ctime>
#include <cstdint>

class BlockHeader {
private:
    std::time_t timestamp;
    std::string previous_hash;
    uint32_t nonce;
    std::string merkle_root;

public:
    // Constructor
    BlockHeader(std::time_t timestamp, const std::string& previous_hash, uint32_t nonce, const std::string& merkle_root);

    // Getters
    std::time_t get_timestamp() const;
    std::string get_previous_hash() const;
    uint32_t get_nonce() const;
};

#endif // BLOCKHEADER_H
