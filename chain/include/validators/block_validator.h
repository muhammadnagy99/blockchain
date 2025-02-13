#ifndef BLOCK_VALIDATOR_H
#define BLOCK_VALIDATOR_H

#include "interfaces/iblock_validator.h"
#include "core/block_header.h"
#include "core/block_body.h"
#include "core/block_hasher.h"
#include <rocksdb/db.h>
#include <memory>
#include <string>

class BlockValidator : public IBlockValidator {
public:
    bool is_valid_block(const BlockHeader& new_header, const BlockHeader& prev_header);

    bool is_valid_chain(rocksdb::DB* db) ;

    bool is_valid_body(const BlockHeader& header, const BlockBody& body);

    bool is_valid_proof_of_work(const BlockHeader& header);
};

#endif // BLOCK_VALIDATOR_H
