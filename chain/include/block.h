#ifndef BLOCK_H
#define BLOCK_H

#include "block_header.h"
#include "block_body.h"
#include <string>

class Block {
private:
    BlockHeader header;
    BlockBody body;
    std::string hash;

public:
    Block(const BlockHeader& header, const BlockBody& body);

    std::string calculate_hash() const;
    std::string get_hash() const;
    BlockHeader get_header() const;
    BlockBody get_body() const;
};

#endif // BLOCK_H
