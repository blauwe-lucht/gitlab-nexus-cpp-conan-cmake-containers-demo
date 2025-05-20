#!/bin/bash

set -euo pipefail

docker build -t conan-cpp:latest -f Dockerfile-CI .
