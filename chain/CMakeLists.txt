cmake_minimum_required(VERSION 3.10)
project(BlockchainLayer0)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

include_directories(include)

find_package(nlohmann_json 3.11.2 REQUIRED)

file(GLOB SOURCES "src/*.cpp")

file(GLOB TEST_SOURCES "test/*.cpp")

add_executable(app_test ${TEST_SOURCES} ${SOURCES})

target_link_libraries(app_test 
    PRIVATE GTest::GTest 
    GTest::Main 
    OpenSSL::Crypto 
    pthread 
    nlohmann_json::nlohmann_json
)
