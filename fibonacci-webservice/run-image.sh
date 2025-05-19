#!/bin/bash

set -xeuo pipefail

docker run -d -p 27372:27372 --name fibonacci-service fibonacci-webservice:latest
