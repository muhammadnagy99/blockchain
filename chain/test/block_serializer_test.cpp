#include "core/block.h"
#include "core/block_serializer.h"
#include "core/block_header.h"
#include "core/block_body.h"
#include "core/transaction.h"
#include <gtest/gtest.h>
#include <memory>

std::string generate_dummy_hash();

class BlockSerializerTest : public ::testing::Test
{
protected:
    std::unique_ptr<BlockHeader> header;
    std::unique_ptr<BlockBody> body;
    std::unique_ptr<Block> block;

    void SetUp() override
    {
        body = std::make_unique<BlockBody>();
        body->add_data(std::make_unique<Transaction>("User1", "User2", 100.0));
        body->add_data(std::make_unique<Transaction>("User3", "User4", 50.5));

        std::string merkle_root = body->get_merkle_root();

        header = std::make_unique<BlockHeader>(std::time(nullptr), generate_dummy_hash(), 42, merkle_root);

        block = std::make_unique<Block>(std::move(header), std::move(body));
    }
};

TEST_F(BlockSerializerTest, SerializeBlock)
{
    std::string json_data = BlockSerializer::serialize(*block);
    EXPECT_FALSE(json_data.empty()) << "Serialized block JSON should not be empty.";
}

TEST_F(BlockSerializerTest, DeserializeBlock)
{
    std::string json_data = BlockSerializer::serialize(*block);
    Block deserialized_block = BlockSerializer::deserialize(json_data);

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
