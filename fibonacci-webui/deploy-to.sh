#!/bin/bash

set -euo pipefail

# Cmdline argument is the target environment.
if [ $# -ne 2 ]; then
    echo "Usage: $0 <environment> <version>"
    exit 1
fi
TARGET_ENV="$1"
VERSION="$2"

# Ansible doesn't like to run in a world-writable directory, so remove those write bits.
chmod -R o-w ansible
cd ansible
ansible-playbook playbook.yml -v --limit ${TARGET_ENV} -e fibonacci_webui_version=${VERSION}
