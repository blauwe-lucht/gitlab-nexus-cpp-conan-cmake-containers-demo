#!/bin/bash

set -xeuo pipefail

docker build -t fibonacci-webservice:latest .
