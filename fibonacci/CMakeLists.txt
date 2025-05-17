cmake_minimum_required(VERSION 3.15)
project(fibonacci CXX)

add_library(fibonacci src/fibonacci.cpp)
target_include_directories(fibonacci PUBLIC include)

set_target_properties(fibonacci PROPERTIES PUBLIC_HEADER "include/fibonacci.hpp")
install(TARGETS fibonacci)
