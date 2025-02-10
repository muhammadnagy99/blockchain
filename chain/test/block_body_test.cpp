#include "core/block_body.h"
#include "core/transaction.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

class MockData : public BodyData {
public:
    std::string content;

    explicit MockData(std::string content) : content(std::move(content)) {}

    std::string to_string() const override {
        return "MockData: " + content;
    }
};

class BlockBodyTest : public ::testing::Test {
protected:
    BlockBody body;

    void SetUp() override {
    }
};

TEST_F(BlockBodyTest, ConstructorInitializesEmpty) {
    EXPECT_TRUE(body.get_data_strings().empty()) << "BlockBody should be initialized empty.";
}

TEST_F(BlockBodyTest, AddTransaction) {
    body.add_data(std::make_unique<Transaction>("User1", "User2", 100.0));
    body.add_data(std::make_unique<Transaction>("User3", "User4", 50.5));

    std::vector<std::string> data_strings = body.get_data_strings();
    
    ASSERT_EQ(data_strings.size(), 2) << "BlockBody should contain 2 transactions.";

    EXPECT_NE(data_strings[0].find("User1"), std::string::npos) << "First transaction should contain 'User1'.";
    EXPECT_NE(data_strings[1].find("User4"), std::string::npos) << "Second transaction should contain 'User4'.";
}

TEST_F(BlockBodyTest, AddCustomData) {
    body.add_data(std::make_unique<MockData>("Blockchain Custom Message"));

    std::vector<std::string> data_strings = body.get_data_strings();
    
    ASSERT_EQ(data_strings.size(), 1) << "BlockBody should contain 1 custom data entry.";
    EXPECT_EQ(data_strings[0], "MockData: Blockchain Custom Message") 
        << "Custom data should match expected format.";
}

TEST_F(BlockBodyTest, AddTransactionsAndCustomData) {
    body.add_data(std::make_unique<Transaction>("User5", "User6", 75.0));
    body.add_data(std::make_unique<MockData>("Smart Contract Execution"));

    std::vector<std::string> data_strings = body.get_data_strings();

    ASSERT_EQ(data_strings.size(), 2) << "BlockBody should contain 2 entries.";

    EXPECT_NE(data_strings[0].find("User5"), std::string::npos) 
        << "First entry should be a transaction containing 'User5'.";
    EXPECT_EQ(data_strings[1], "MockData: Smart Contract Execution") 
        << "Second entry should be mock data.";
}


