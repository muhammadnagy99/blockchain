cmake_minimum_required(VERSION 3.10)
project(BlockchainLayer0)

enable_testing()
include_directories(${CMAKE_SOURCE_DIR}/include)

# ✅ Find GTest (for unit testing)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# ✅ Find OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# ✅ Find RocksDB (Replaces LevelDB)
find_library(ROCKSDB_LIBRARY NAMES rocksdb REQUIRED)
include_directories(/usr/include/rocksdb)  # Ensure RocksDB include directory is set

# ✅ Find JSON Library
find_package(nlohmann_json 3.11.2 REQUIRED)

# ✅ Source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp")

# ✅ Add main executable (console application)
add_executable(blockchain_app example/main.cpp ${SOURCES})
target_link_libraries(blockchain_app 
    PRIVATE OpenSSL::Crypto 
    pthread 
    nlohmann_json::nlohmann_json 
    ${ROCKSDB_LIBRARY}  # ✅ Link RocksDB instead of LevelDB
)

