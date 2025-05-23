#!/bin/bash

set -xeuo pipefail

VERSION=$(grep -Po '(?<=version = ")[^"]*' conanfile.py)

docker build -t registry:5000/fibonacci-webservice:latest -t registry:5000/fibonacci-webservice:"$VERSION" .

podman push --tls-verify=false registry:5000/fibonacci-webservice:latest
podman push --tls-verify=false registry:5000/fibonacci-webservice:"$VERSION"
