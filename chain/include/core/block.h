#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include <string>
#include "interfaces/iblock_header.h"
#include "interfaces/iblock_body.h"
#include "block_hasher.h"

class Block {
private:
    std::unique_ptr<IBlockHeader> header;
    std::unique_ptr<IBlockBody> body;

public:
    Block(std::unique_ptr<IBlockHeader> header, std::unique_ptr<IBlockBody> body);

    std::string get_hash() const;
    const IBlockHeader& get_header() const;
    const IBlockBody& get_body() const;

    std::string to_json() const;
    static Block from_json(const std::string& json_data);
};

#endif // BLOCK_H
