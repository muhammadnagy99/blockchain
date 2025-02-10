#include "core/block.h"
#include "core/block_header.h"
#include "core/block_body.h"
#include "core/block_serializer.h"
#include "core/transaction.h"
#include <gtest/gtest.h>
#include <memory>
#include <iostream>

std::string generate_dummy_hash() {
    return "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";
}

class BlockTest : public ::testing::Test {
protected:
    std::unique_ptr<BlockHeader> header;
    std::unique_ptr<BlockBody> body;
    std::unique_ptr<Block> block;

    void SetUp() override {
        body = std::make_unique<BlockBody>();
        body->add_data(std::make_unique<Transaction>("User1", "User2", 100.0));
        body->add_data(std::make_unique<Transaction>("User3", "User4", 50.5));

        std::string merkle_root = body->get_merkle_root();
        header = std::make_unique<BlockHeader>(std::time(nullptr), generate_dummy_hash(), 42, merkle_root);

        block = std::make_unique<Block>(std::move(header), std::move(body));
    }
};

TEST_F(BlockTest, BlockInitialization) {
    EXPECT_NE(block, nullptr) << "Block should be initialized.";
}

TEST_F(BlockTest, BlockHashIs64Characters) {
    EXPECT_EQ(block->get_hash().length(), 64) << "Block hash should always be 64 characters long.";
}

TEST_F(BlockTest, BlockHeaderRetrieval) {
    const IBlockHeader& retrieved_header = block->get_header();
    const BlockHeader* actual_header = dynamic_cast<const BlockHeader*>(&retrieved_header);

    ASSERT_NE(actual_header, nullptr) << "Header should be castable to BlockHeader.";
    EXPECT_EQ(actual_header->get_previous_hash(), generate_dummy_hash()) << "Previous hash should match.";
    EXPECT_EQ(actual_header->get_nonce(), 42) << "Nonce should match.";
}

TEST_F(BlockTest, BlockBodyRetrieval) {
    const IBlockBody& retrieved_body = block->get_body();
    const BlockBody* actual_body = dynamic_cast<const BlockBody*>(&retrieved_body);

    ASSERT_NE(actual_body, nullptr) << "Body should be castable to BlockBody.";
    std::vector<std::string> data_strings = actual_body->get_data_strings();

    ASSERT_EQ(data_strings.size(), 2) << "BlockBody should contain 2 transactions.";
    EXPECT_NE(data_strings[0].find("User1"), std::string::npos) << "First transaction should contain 'User1'.";
    EXPECT_NE(data_strings[1].find("User4"), std::string::npos) << "Second transaction should contain 'User4'.";
}

TEST_F(BlockTest, BlockHashConsistency) {
    std::unique_ptr<BlockBody> body2 = std::make_unique<BlockBody>();
    body2->add_data(std::make_unique<Transaction>("User1", "User2", 100.0));
    body2->add_data(std::make_unique<Transaction>("User3", "User4", 50.5));

    std::string merkle_root = body2->get_merkle_root();
    std::unique_ptr<BlockHeader> header2 = std::make_unique<BlockHeader>(std::time(nullptr), generate_dummy_hash(), 42, merkle_root);

    std::unique_ptr<Block> block2 = std::make_unique<Block>(std::move(header2), std::move(body2));

    EXPECT_EQ(block->get_hash(), block2->get_hash()) << "Identical blocks should have the same hash.";
}

TEST_F(BlockTest, SerializeBlockToJson) {
    std::string json_data = block->to_json();
    std::cout << "Serialized Block JSON:\n" << json_data << std::endl;

    EXPECT_FALSE(json_data.empty()) << "Serialized block JSON should not be empty.";
}

TEST_F(BlockTest, DeserializeBlockFromJson) {
    std::string json_data = block->to_json();
    Block deserialized_block = Block::from_json(json_data);

    std::cout << "=== Original Block ===" << std::endl;
    std::cout << "Hash: " << block->get_hash() << std::endl;
    std::cout << "Previous Hash: " << block->get_header().get_previous_hash() << std::endl;
    std::cout << "Timestamp: " << block->get_header().get_timestamp() << std::endl;
    std::cout << "Nonce: " << block->get_header().get_nonce() << std::endl;
    std::cout << "Merkle Root: " << block->get_header().get_merkle_root() << std::endl;
    std::cout << "Transactions: " << block->get_body().get_data_entries().size() << " transactions" << std::endl;
    std::cout << "=====================================" << std::endl;

    std::cout << "=== Deserialized Block ===" << std::endl;
    std::cout << "Hash: " << deserialized_block.get_hash() << std::endl;
    std::cout << "Previous Hash: " << deserialized_block.get_header().get_previous_hash() << std::endl;
    std::cout << "Timestamp: " << deserialized_block.get_header().get_timestamp() << std::endl;
    std::cout << "Nonce: " << deserialized_block.get_header().get_nonce() << std::endl;
    std::cout << "Merkle Root: " << deserialized_block.get_header().get_merkle_root() << std::endl;
    std::cout << "Transactions: " << deserialized_block.get_body().get_data_entries().size() << " transactions" << std::endl;
    std::cout << "=====================================" << std::endl;

    EXPECT_EQ(block->get_hash(), deserialized_block.get_hash()) << "Deserialized block should have the same hash.";

    EXPECT_EQ(block->get_header().get_previous_hash(), deserialized_block.get_header().get_previous_hash())
        << "Deserialized block should have the same previous hash.";
    EXPECT_EQ(block->get_header().get_timestamp(), deserialized_block.get_header().get_timestamp())
        << "Deserialized block should have the same timestamp.";
    EXPECT_EQ(block->get_header().get_nonce(), deserialized_block.get_header().get_nonce())
        << "Deserialized block should have the same nonce.";
    EXPECT_EQ(block->get_header().get_merkle_root(), deserialized_block.get_header().get_merkle_root())
        << "Deserialized block should have the same Merkle root.";

    EXPECT_EQ(block->get_body().get_data_entries().size(), deserialized_block.get_body().get_data_entries().size())
        << "Deserialized block should have the same number of transactions.";
}
