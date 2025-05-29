#!/bin/bash

set -euo pipefail

vagrant up
docker compose up -d
./build-pipeline-images.sh
./configure-gitlab.sh
./configure-nexus.sh
./register-runner.sh
