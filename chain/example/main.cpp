#include "core/blockchain.h"
#include "core/transaction.h"
#include "transaction/transaction_pool.h"
#include "validators/block_validator.h"
#include "mining/miner.h"
#include <rocksdb/db.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

void print_menu()
{
    std::cout << "\n===== Blockchain CLI =====\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. Mine Block\n";
    std::cout << "3. View Latest Block\n";
    std::cout << "4. View chain\n";
    std::cout << "5. Check Transaction Pool\n";
    std::cout << "6. Validate Chain\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

int main()
{
    std::string blockchain_db_path = "blockchain_db";
    std::string transaction_pool_db_path = "transaction_pool_db_path";

    auto validator = std::make_unique<BlockValidator>();
    auto miner = std::make_unique<Miner>();
    auto blockchain = std::make_unique<Blockchain>(nullptr, std::move(validator), std::move(miner), blockchain_db_path);
    auto transaction_pool = std::make_unique<TransactionPool>(
        transaction_pool_db_path, std::bind(&Blockchain::mine_block, blockchain.get()));

    blockchain->set_transaction_pool(std::move(transaction_pool));

    int choice;
    while (true)
    {
        print_menu();
        std::cin >> choice;

        if (choice == 1)
        {
            std::string sender, receiver;
            double amount;
            std::cout << "Enter sender: ";
            std::cin >> sender;
            std::cout << "Enter receiver: ";
            std::cin >> receiver;
            std::cout << "Enter amount: ";
            std::cin >> amount;

            Transaction tx(sender, receiver, amount);
            blockchain->get_transaction_pool().add_transaction(tx);
        }
        else if (choice == 2)
        {
            blockchain->mine_block();
        }
        else if (choice == 3)
        {
            Block latest = blockchain->get_latest_block();
            std::cout << "🔗 Latest Block: " << latest.to_json() << "\n";
        }
        else if (choice == 4)
        {
            std::vector<std::string> chain = blockchain->get_chain();
            int i = 0;
            for (auto &block : chain)
                std::cout << block << std::endl;
        }
        else if (choice == 5)
        {
            std::cout << blockchain->get_transaction_pool().get_pending_transaction_count() << std::endl;
        }
        else if (choice == 6)
        {
            std::cout << blockchain->is_valid() << std::endl;
        }
        else if (choice == 7)
        {
            std::cout << "Exiting...\n";
            break;
        }
        else
        {
            std::cout << "❌ Invalid choice. Try again.\n";
        }
    }

    return 0;
}
