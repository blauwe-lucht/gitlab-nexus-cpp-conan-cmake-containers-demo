#!/bin/bash

set -xeuo pipefail

cd "$(dirname "$0")"
VERSION=$(./get-version.sh)

docker build \
    --build-arg FIBONACCI_WEBUI_VERSION="$VERSION" \
    -t registry.local:5000/fibonacci-webui:latest \
    -t registry.local:5000/fibonacci-webui:"$VERSION" \
    .


docker push --tls-verify=false registry.local:5000/fibonacci-webui:latest
docker push --tls-verify=false registry.local:5000/fibonacci-webui:"$VERSION"
