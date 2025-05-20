#!/bin/bash

set -xeuo pipefail

# Extract the version from conanfile.py
VERSION=$(grep -Po '(?<=version = ")[^"]*' conanfile.py)

# Build the Docker image and tag it with both "latest" and the version
docker build -t fibonacci-webservice:latest -t fibonacci-webservice:"$VERSION" .