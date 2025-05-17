cmake_minimum_required(VERSION 3.15)
project(libfibonacci)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(libfibonacci src/Fibonacci.cpp)
target_include_directories(libfibonacci PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Unit tests
find_package(GTest REQUIRED)

enable_testing()

add_executable(test_libfibonacci tests/FibonacciTests.cpp)
target_link_libraries(test_libfibonacci PRIVATE libfibonacci GTest::gtest_main)
add_test(NAME FibonacciTests COMMAND test_libfibonacci)
