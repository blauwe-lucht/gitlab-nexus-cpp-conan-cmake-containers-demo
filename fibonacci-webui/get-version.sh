#!/bin/bash

set -euo pipefail

cd "$(dirname "$0")"
VERSION=$(cat VERSION)
echo ${VERSION}
