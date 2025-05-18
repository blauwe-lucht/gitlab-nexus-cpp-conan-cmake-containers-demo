#!/bin/bash

set -xeuo pipefail

REMOTE_NAME="conan-hosted"
REMOTE_URL="http://172.17.0.1:8081/repository/conan-hosted/"

# Check if the remote already exists
if conan remote list | awk '{print $1}' | grep -Fq "$REMOTE_NAME"; then
    echo "[INFO] Remote '$REMOTE_NAME' already exists with correct URL. Skipping."
else
    echo "[INFO] Adding remote '$REMOTE_NAME' → '$REMOTE_URL'."
    conan remote add "$REMOTE_NAME" "$REMOTE_URL" --insecure
fi

conan remote login conan-hosted conan-upload -p "Abcd1234!"
conan upload fibonacci -r conan-hosted
