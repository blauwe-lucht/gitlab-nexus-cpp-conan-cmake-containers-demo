#!/bin/bash

set -xeuo pipefail

conan build . --build=missing
build/Release/unit_tests
