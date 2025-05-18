cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(fibonacci CONFIG REQUIRED)

add_executable(fibonacci_test src/fibonacci_test.cpp)
target_link_libraries(fibonacci_test PRIVATE fibonacci::fibonacci)
