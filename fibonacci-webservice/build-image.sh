#!/bin/bash

set -xeuo pipefail

VERSION=$(grep -Po '(?<=version = ")[^"]*' conanfile.py)

docker build -t registry.local:5000/fibonacci-webservice:latest -t registry.local:5000/fibonacci-webservice:"$VERSION" .

docker push --tls-verify=false registry.local:5000/fibonacci-webservice:latest
docker push --tls-verify=false registry.local:5000/fibonacci-webservice:"$VERSION"
