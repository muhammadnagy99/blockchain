#include "mining/miner.h"
#include "core/block_header.h"
#include "core/block.h"
#include "core/block_body.h"
#include "core/block_hasher.h"
#include "core/transaction.h"
#include <iostream>
#include <ctime>

const int DIFFICULTY = 4;

Block Miner::mine_block(const IBlockHeader& previous_header, const std::vector<Transaction>& transactions) {
    std::string previous_hash = previous_header.get_hash();
    uint32_t nonce = 0;
    std::time_t timestamp = std::time(nullptr);
    std::string block_hash;

    auto body = std::make_unique<BlockBody>();
    for (const auto& tx : transactions) {
        body->add_data(std::make_unique<Transaction>(tx));
    }

    std::string merkle_root = body->get_merkle_root();

    // std::cout << "[Mining] Started mining new block..." << std::endl;

    do {
        nonce++;
        block_hash = BlockHasher::calculate_hash(previous_hash, timestamp, nonce, merkle_root); 
    } while (block_hash.substr(0, DIFFICULTY) != std::string(DIFFICULTY, '0'));

    // std::cout << "[Mining] Block Mined! Nonce: " << nonce << " Hash: " << block_hash << std::endl;

    auto header = std::make_unique<BlockHeader>(timestamp, previous_hash, nonce, merkle_root, block_hash);

    return Block(std::move(header), std::move(body));
}
