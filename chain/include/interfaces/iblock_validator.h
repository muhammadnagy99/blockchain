#ifndef IBLOCK_VALIDATOR_H
#define IBLOCK_VALIDATOR_H

#include "core/block_header.h"
#include "core/block_body.h"
#include <rocksdb/db.h>
#include <vector>

class IBlockValidator
{
public:
    virtual ~IBlockValidator() = default;
    virtual bool is_valid_block(const BlockHeader &new_header, const BlockHeader &prev_header) = 0;

    virtual bool is_valid_chain(rocksdb::DB *db) = 0;

    virtual bool is_valid_body(const BlockHeader &header, const BlockBody &body) = 0;

    virtual bool is_valid_proof_of_work(const BlockHeader &header) = 0;
};

#endif // IBLOCK_VALIDATOR_H
