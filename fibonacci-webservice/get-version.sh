#!/bin/bash

set -euo pipefail

# Retrieve the latest Git tag:
TAG=$(git tag --sort=-creatordate --list 'webservice-*' 2> /dev/null | head -n1)
if [ -z "$TAG" ]; then
    echo "No tags found matching 'webservice-*'. Exiting."
    exit 1
fi

# Filter out the version number (assumes there is no suffix):
TAG_NO_V=$(echo "$TAG" | sed 's/^[^0-9]*//')

# Count the number of commits since the last tag:
COMMITS_SINCE_TAG=$(git rev-list "${TAG}"..HEAD --count)

echo "${TAG_NO_V}.${COMMITS_SINCE_TAG}"
