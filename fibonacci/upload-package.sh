#!/bin/bash

set -xeuo pipefail

conan upload fibonacci -r conan-hosted
