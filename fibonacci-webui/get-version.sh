#!/bin/bash

set -euo pipefail

# Retrieve the latest Git tag:
TAG=$(git describe --tags --abbrev=0)

# Filter out the version number (assumes there is no suffix):
TAG_NO_V=$(echo "$TAG" | sed 's/^[^0-9]*//')

# Count the number of commits since the last tag:
COMMITS_SINCE_TAG=$(git rev-list "${TAG}"..HEAD --count)

echo "${TAG_NO_V}.${COMMITS_SINCE_TAG}"
