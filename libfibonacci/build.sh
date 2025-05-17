#!/bin/bash

set -xeuo pipefail

conan install . --output-folder=build --build=missing
cmake -S . -B build/cmake -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build/cmake --config Release
build/cmake/test_libfibonacci
