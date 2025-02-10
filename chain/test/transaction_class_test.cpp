#include "core/transaction.h"
#include <gtest/gtest.h>
#include <ctime>

TEST(TransactionTest, ConstructorInitialization) {
    Transaction tx("user1", "user2", 100.50);
    EXPECT_EQ(tx.get_sender(), "user1");
    EXPECT_EQ(tx.get_receiver(), "user2");
    EXPECT_EQ(tx.get_amount(), 100.50);
    EXPECT_NE(tx.get_transaction_id(), "");
    EXPECT_GT(tx.get_timestamp(), 0);
}

TEST(TransactionTest, Getters) {
    Transaction tx("user1", "user2", 250.75);
    EXPECT_EQ(tx.get_sender(), "user1");
    EXPECT_EQ(tx.get_receiver(), "user2");
    EXPECT_EQ(tx.get_amount(), 250.75);
    EXPECT_NE(tx.get_transaction_id(), "");
}

TEST(TransactionTest, UniqueTransactionID) {
    Transaction tx1("user1", "user2", 99.99);
    Transaction tx2("user1", "user2", 99.99);
    EXPECT_NE(tx1.get_transaction_id(), tx2.get_transaction_id());
}

TEST(TransactionTest, ToStringFormat) {
    Transaction tx("user1", "user2", 500.00);
    std::string tx_string = tx.to_string();
    EXPECT_NE(tx_string.find("user1"), std::string::npos);
    EXPECT_NE(tx_string.find("user2"), std::string::npos);
    EXPECT_NE(tx_string.find("500"), std::string::npos);
}


