#!/bin/bash

set -xeuo pipefail

conan build .
build/Release/unit_tests
