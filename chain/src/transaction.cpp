#include "transaction.h"
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <random>

Transaction::Transaction(const std::string& sender, const std::string& receiver, double amount)
    : sender(sender), receiver(receiver), amount(amount) {
    
    timestamp = std::time(nullptr);

    if (timestamp == -1) {
        throw std::runtime_error("Failed to initialize timestamp");
    }

    // Generate a random nonce
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);
    flag = dist(gen);

    transaction_id = generate_transaction_id();
}



std::string Transaction::get_sender() const { return sender; }
std::string Transaction::get_receiver() const { return receiver; }
double Transaction::get_amount() const { return amount; }
std::time_t Transaction::get_timestamp() const { return timestamp; }
std::string Transaction::get_signature() const { return signature; }
std::string Transaction::get_transaction_id() const { return transaction_id; }

std::string Transaction::to_string() const {
    std::ostringstream oss;
    oss << sender << receiver << amount << timestamp;
    return oss.str();
}

std::string Transaction::generate_transaction_id() const {
    std::ostringstream oss;
    oss << sender << receiver << amount << timestamp << flag;

    std::string data = oss.str();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    std::ostringstream hash_string;
    for (unsigned char c : hash) {
        hash_string << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }

    return hash_string.str();
}


