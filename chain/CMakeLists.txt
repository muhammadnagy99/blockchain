cmake_minimum_required(VERSION 3.10)
project(BlockchainLayer0)

# Enable testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Find OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Include project headers
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add test files
file(GLOB TEST_SOURCES "test/*.cpp")

# Define executable for tests
add_executable(transaction_test ${TEST_SOURCES} ${SOURCES})

# Link Google Test, OpenSSL, and pthread
target_link_libraries(transaction_test PRIVATE GTest::GTest GTest::Main OpenSSL::Crypto pthread)
