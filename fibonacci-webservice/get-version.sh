#!/bin/bash

set -euo pipefail

cd "$(dirname "$0")"
VERSION=$(grep -Po '(?<=version = ")[^"]*' conanfile.py)
echo ${VERSION}
