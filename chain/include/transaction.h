#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Transaction {
private:
    std::string sender;
    std::string receiver;
    std::time_t timestamp;
    double amount;
    std::string signature;
    std::string transaction_id;
    int flag;

public:
    Transaction(const std::string& sender, const std::string& receiver, double amount);

    std::string get_sender() const;
    std::string get_receiver() const;
    double get_amount() const;
    std::time_t get_timestamp() const;
    std::string get_signature() const;
    std::string get_transaction_id() const;
    
    std::string generate_transaction_id() const;
    std::string to_string() const;
};

#endif // TRANSACTION_H
