#!/bin/bash

# This script cleans up the .conan2 cache from all Docker volumes

set -euo pipefail

for volume in $(docker volume ls -q | grep 'runner-glrtr'); do
  echo "Checking volume: $volume"
  # First check if .conan2 exists
  if docker run --rm -v $volume:/inspect alpine sh -c "[ -d /inspect/profiles ] && echo 'Found .conan2/profiles'" | grep -q "Found"; then
    echo "Cleaning .conan2 from $volume"
    docker run --rm -v $volume:/cleanup alpine sh -c "rm -rf /cleanup/*"
    echo "Cleaned $volume"
  fi
done