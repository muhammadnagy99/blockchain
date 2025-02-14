cmake_minimum_required(VERSION 3.15)
project(TransactionServer)

set(CMAKE_CXX_STANDARD 17)

# Find gRPC and Protobuf
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_library(ROCKSDB_LIBRARY NAMES rocksdb REQUIRED)
include_directories(/usr/include/rocksdb)  

find_package(nlohmann_json 3.11.2 REQUIRED)

# Define the absolute path to the blockchain directory
set(CHAIN_DIR "${CMAKE_SOURCE_DIR}/../chain")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CHAIN_DIR}/include)

# Include directories (add blockchain headers)
include_directories(${Protobuf_INCLUDE_DIRS})

file(GLOB CHAIN_SRC_FILES
    "${CHAIN_DIR}/src/*.cpp"
)

# Debugging: Print the detected chain directory path
message(STATUS "CHAIN_DIR: ${CHAIN_DIR}")

set(PROTO_SRCS transaction.pb.cc transaction.grpc.pb.cc)
set(PROTO_HDRS transaction.pb.h transaction.grpc.pb.h)


# Add all sources for the server
set(SERVER_SRCS server.cpp ${PROTO_SRCS} ${GRPC_SRCS} ${CHAIN_SRC_FILES} ${CHAIN_HEADER_FILES})

# Create the server executable
add_executable(transaction_server ${SERVER_SRCS})

# Link against gRPC, Protobuf, and other dependencies
target_link_libraries(transaction_server
    gRPC::grpc++
    protobuf::libprotobuf
    OpenSSL::Crypto 
    pthread 
    nlohmann_json::nlohmann_json 
    ${ROCKSDB_LIBRARY}  
)

add_executable(transaction_client client.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_link_libraries(transaction_client
    gRPC::grpc++
    protobuf::libprotobuf
)