cmake_minimum_required(VERSION 3.10)
project(simple_ckks)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/encoder.cpp src/plaintext.cpp src/parameters.cpp src/public_key.cpp src/secret_key.cpp
                 src/encryptor.cpp src/math/ntt_transformer.cpp src/util.cpp src/keygen.cpp src/rand_util.cpp src/ciphertext.cpp
                 src/math/rns_transformer.cpp src/evaluation_key.cpp src/evaluator.cpp src/math/rns_converter.cpp
                 build/lib/BigInt.cpp)
set(TEST_FILES test/encoder.cpp test/math/ntt_transformer.cpp test/encryptor.cpp test/evaluator.cpp)

FILE(DOWNLOAD https://github.com/faheel/BigInt/releases/download/v0.5.0-dev/BigInt.hpp build/lib/BigInt.cpp)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

FetchContent_MakeAvailable(googletest)

# Add the main library
add_library(simple_ckks ${SOURCE_FILES})
target_include_directories(simple_ckks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_executable(tests ${TEST_FILES})
target_link_libraries(tests gtest_main simple_ckks)

include(GoogleTest)
gtest_discover_tests(tests PROPERTIES DISCOVERY_TIMEOUT 600)

# Add the demo executable
add_executable(ckks_demo demo/ckks_demo.cpp)
target_link_libraries(ckks_demo simple_ckks)
