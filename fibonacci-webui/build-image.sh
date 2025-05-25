#!/bin/bash

set -xeuo pipefail

if [[ -f VERSION ]]; then
    VERSION=$(cat VERSION)
else
    VERSION="unknown"
fi

docker build \
    --build-arg FIBONACCI_WEBUI_VERSION="$VERSION" \
    -t registry.local:5000/fibonacci-webui:latest \
    -t registry.local:5000/fibonacci-webui:"$VERSION" \
    .

docker push --tls-verify=false registry.local:5000/fibonacci-webui:latest
docker push --tls-verify=false registry.local:5000/fibonacci-webui:"$VERSION"
