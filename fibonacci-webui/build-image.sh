#!/bin/bash

set -xeuo pipefail

if [[ -f VERSION ]]; then
    VERSION=$(cat VERSION)
else
    VERSION="unknown"
fi

docker build \
    --build-arg FIBONACCI_WEBUI_VERSION="$VERSION" \
    -t fibonacci-webui:latest \
    -t fibonacci-webui:"$VERSION" \
    .