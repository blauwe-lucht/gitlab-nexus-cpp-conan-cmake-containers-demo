#!/bin/bash

set -xeuo pipefail

VERSION=$(grep -Po '(?<=version = ")[^"]*' conanfile.py)

docker build -t registry:5000/fibonacci-webservice:latest -t registry:5000/fibonacci-webservice:"$VERSION" .

docker push registry:5000/fibonacci-webservice:latest
docker push registry:5000/fibonacci-webservice:"$VERSION"
