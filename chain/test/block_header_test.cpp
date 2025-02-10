#include "core/block_header.h"
#include <gtest/gtest.h>
#include <ctime>

TEST(BlockHeaderTest, ConstructorValid) {
    std::time_t now = std::time(nullptr);
    std::string valid_hash = std::string(64, 'a'); 
    std::string valid_merkle = std::string(64, 'b'); 

    BlockHeader block(now, valid_hash, 12345, valid_merkle);
    EXPECT_EQ(block.get_timestamp(), now);
    EXPECT_EQ(block.get_previous_hash(), valid_hash);
    EXPECT_EQ(block.get_nonce(), 12345);
}

TEST(BlockHeaderTest, GenesisBlock) {
    std::time_t now = std::time(nullptr);
    std::string valid_merkle = std::string(64, 'b');

    BlockHeader block(now, "", 0, valid_merkle);
    EXPECT_EQ(block.get_previous_hash(), "");
}

TEST(BlockHeaderTest, InvalidPreviousHash) {
    std::time_t now = std::time(nullptr);
    std::string invalid_hash = "abc";
    std::string valid_merkle = std::string(64, 'b');
    
    EXPECT_THROW(BlockHeader block(now, invalid_hash, 12345, valid_merkle), std::invalid_argument);
}

TEST(BlockHeaderTest, InvalidMerkleRoot) {
    std::time_t now = std::time(nullptr);
    std::string valid_hash = std::string(64, 'a');
    std::string invalid_merkle = "abc";
    
    EXPECT_THROW(BlockHeader block(now, valid_hash, 12345, invalid_merkle), std::invalid_argument);
}

