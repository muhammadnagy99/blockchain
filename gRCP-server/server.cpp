#include <grpcpp/grpcpp.h>
#include <nlohmann/json.hpp>
#include "transaction.grpc.pb.h"
#include "core/blockchain.h"
#include "core/transaction.h"
#include "transaction/transaction_pool.h"
#include "validators/block_validator.h"
#include "mining/miner.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using transaction::TransactionJsonRequest;
using transaction::TransactionResponse;
using transaction::TransactionService;
using json = nlohmann::json; 

constexpr const char* BLOCKCHAIN_DB_PATH = "blockchain_db";
constexpr const char* TRANSACTION_POOL_DB_PATH = "transaction_pool_db_path";

class TransactionServiceImpl final : public TransactionService::Service
{
private:
    std::shared_ptr<Blockchain> blockchain;

public:
    explicit TransactionServiceImpl(std::shared_ptr<Blockchain> chain) : blockchain(std::move(chain)) {}

    Status AddTransaction(ServerContext *context, const TransactionJsonRequest *request, TransactionResponse *response) override
    {
        try
        {
            json json_data = json::parse(request->json_data());
            Transaction tx(json_data);
            std::cout << tx.to_json().dump() << std::endl;

            blockchain->get_transaction_pool().add_transaction(tx);

            response->set_success(true);
            response->set_message("Transaction added successfully");

            return Status::OK;
        }
        catch (const std::exception &e)
        {
            response->set_success(false);
            response->set_message(std::string("Failed to parse JSON: ") + e.what());
            std::cout<< e.what() << std::endl;
            return Status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid JSON format");
        }
    }
};

void RunServer(std::shared_ptr<Blockchain> blockchain)
{
    std::string server_address("0.0.0.0:50051");
    TransactionServiceImpl service(blockchain);

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "🚀 gRPC Server listening on " << server_address << std::endl;
    server->Wait();
}

int main()
{
    std::string blockchain_db_path = std::string(BLOCKCHAIN_DB_PATH);
    std::string transaction_pool_db_path = std::string(TRANSACTION_POOL_DB_PATH);

    auto validator = std::make_unique<BlockValidator>();
    auto miner = std::make_unique<Miner>();
    auto blockchain = std::make_shared<Blockchain>(nullptr, std::move(validator), std::move(miner), blockchain_db_path);
    auto transaction_pool = std::make_unique<TransactionPool>(
        transaction_pool_db_path, std::bind(&Blockchain::mine_block, blockchain.get()));

    blockchain->set_transaction_pool(std::move(transaction_pool));

    RunServer(blockchain);
    return 0;
}
