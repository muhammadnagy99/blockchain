#ifndef IBLOCK_HEADER_H
#define IBLOCK_HEADER_H

#include <string>
#include <ctime>
#include <cstdint>

class IBlockHeader {
public:
    virtual std::string get_previous_hash() const = 0;
    virtual std::string get_hash() const = 0;
    virtual std::time_t get_timestamp() const = 0;
    virtual uint32_t get_nonce() const = 0;
    virtual std::string get_merkle_root() const = 0;
    virtual ~IBlockHeader() = default;
};

#endif // IBLOCK_HEADER_H
