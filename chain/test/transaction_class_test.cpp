#include "transaction.h"
#include <gtest/gtest.h>
#include <ctime>

TEST(TransactionTest, ConstructorInitialization) {
    Transaction tx("Alice", "Bob", 100.50);
    EXPECT_EQ(tx.get_sender(), "Alice");
    EXPECT_EQ(tx.get_receiver(), "Bob");
    EXPECT_EQ(tx.get_amount(), 100.50);
    EXPECT_NE(tx.get_transaction_id(), "");
    EXPECT_GT(tx.get_timestamp(), 0);
}

TEST(TransactionTest, Getters) {
    Transaction tx("Charlie", "Dave", 250.75);
    EXPECT_EQ(tx.get_sender(), "Charlie");
    EXPECT_EQ(tx.get_receiver(), "Dave");
    EXPECT_EQ(tx.get_amount(), 250.75);
    EXPECT_NE(tx.get_transaction_id(), "");
}

TEST(TransactionTest, UniqueTransactionID) {
    Transaction tx1("Eve", "Frank", 99.99);
    Transaction tx2("Eve", "Frank", 99.99);
    EXPECT_NE(tx1.get_transaction_id(), tx2.get_transaction_id());
}

TEST(TransactionTest, ToStringFormat) {
    Transaction tx("Grace", "Hank", 500.00);
    std::string tx_string = tx.to_string();
    EXPECT_NE(tx_string.find("Grace"), std::string::npos);
    EXPECT_NE(tx_string.find("Hank"), std::string::npos);
    EXPECT_NE(tx_string.find("500"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
