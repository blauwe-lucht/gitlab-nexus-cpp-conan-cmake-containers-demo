#!/bin/bash

set -euo pipefail

# Config
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/.env"

docker exec -it $RUNNER_CONTAINER gitlab-runner unregister --all-runners
