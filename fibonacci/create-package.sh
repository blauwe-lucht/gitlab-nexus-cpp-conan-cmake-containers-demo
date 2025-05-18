#!/bin/bash

set -xeuo pipefail

conan create .
conan list "fibonacci/*"
