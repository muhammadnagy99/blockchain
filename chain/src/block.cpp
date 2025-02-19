#include "core/block.h"
#include "serializers/block_serializer.h"

Block::Block(std::unique_ptr<IBlockHeader> header, std::unique_ptr<IBlockBody> body)
    : header(std::move(header)), body(std::move(body)) {}

std::string Block::get_hash() const
{
    return header->get_hash();
}

const IBlockHeader &Block::get_header() const
{
    return *header;
}

const IBlockBody &Block::get_body() const
{
    return *body;
}

std::string Block::to_json() const
{
    return BlockSerializer::serialize(*this);
}

Block Block::from_json(const std::string &json_data)
{
    return BlockSerializer::deserialize(json_data);
}