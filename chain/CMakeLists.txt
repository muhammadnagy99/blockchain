cmake_minimum_required(VERSION 3.10)
project(BlockchainLayer0)

enable_testing()
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_library(ROCKSDB_LIBRARY NAMES rocksdb REQUIRED)
include_directories(/usr/include/rocksdb)  

find_package(nlohmann_json 3.11.2 REQUIRED)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp")

add_executable(blockchain_app example/main.cpp ${SOURCES})
target_link_libraries(blockchain_app 
    PRIVATE OpenSSL::Crypto 
    pthread 
    nlohmann_json::nlohmann_json 
    ${ROCKSDB_LIBRARY}  
)

