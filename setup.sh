#!/bin/bash

set -euo pipefail

docker compose up -d
./build-pipeline-images.sh
./configure-gitlab.sh
./configure-nexus.sh
./register-runner.sh
