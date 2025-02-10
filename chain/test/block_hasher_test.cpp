#include "core/block_hasher.h"
#include "core/block_header.h"
#include "core/block_body.h"
#include <gtest/gtest.h>
#include <memory>

class MockBlockHeader : public IBlockHeader
{
public:
    std::string previous_hash;
    std::time_t timestamp;
    uint32_t nonce;

    MockBlockHeader(std::string prev, std::time_t ts, uint32_t n)
        : previous_hash(std::move(prev)), timestamp(ts), nonce(n) {}

    std::string get_previous_hash() const override { return previous_hash; }
    std::time_t get_timestamp() const override { return timestamp; }
    uint32_t get_nonce() const override { return nonce; }
    std::string get_merkle_root() const
    {
        return previous_hash;
    }
};

class MockBlockBody : public IBlockBody {
public:
    std::string merkle_root;
    std::vector<std::unique_ptr<BodyData>> data_entries;

    explicit MockBlockBody(std::string merkle) : merkle_root(std::move(merkle)) {}

    std::string get_merkle_root() const override { return merkle_root; }

    const std::vector<std::unique_ptr<BodyData>>& get_data_entries() const override {
        return data_entries;
    }

    void add_mock_transaction(std::unique_ptr<BodyData> transaction) {
        data_entries.push_back(std::move(transaction));
    }
};


TEST(BlockHasherTest, HashLengthIsCorrect)
{
    MockBlockHeader header("prevhash123", 1700000000, 42);
    MockBlockBody body("mockMerkleRoot");

    std::string hash = BlockHasher::calculate_hash(header, body);

    ASSERT_EQ(hash.length(), 64) << "SHA-256 hash should always be 64 characters.";
}

TEST(BlockHasherTest, HashConsistency)
{
    MockBlockHeader header1("prevhash123", 1700000000, 42);
    MockBlockBody body1("mockMerkleRoot");

    MockBlockHeader header2("prevhash123", 1700000000, 42);
    MockBlockBody body2("mockMerkleRoot");

    std::string hash1 = BlockHasher::calculate_hash(header1, body1);
    std::string hash2 = BlockHasher::calculate_hash(header2, body2);

    ASSERT_EQ(hash1, hash2) << "Hashes should be the same for identical input.";
}

TEST(BlockHasherTest, DifferentInputsProduceDifferentHashes)
{
    MockBlockHeader header1("prevhash123", 1700000000, 42);
    MockBlockBody body1("mockMerkleRoot");

    MockBlockHeader header2("differentPrevHash", 1700000001, 43);
    MockBlockBody body2("differentMerkleRoot");

    std::string hash1 = BlockHasher::calculate_hash(header1, body1);
    std::string hash2 = BlockHasher::calculate_hash(header2, body2);

    ASSERT_NE(hash1, hash2) << "Different inputs should produce different hashes.";
}

TEST(BlockHasherTest, HashingEmptyBlock)
{
    MockBlockHeader header("", 0, 0);
    MockBlockBody body("");

    std::string hash = BlockHasher::calculate_hash(header, body);

    ASSERT_EQ(hash.length(), 64) << "SHA-256 hash of an empty block should still be 64 characters.";
}
