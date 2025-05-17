# Use Microsoft’s “bionic” devcontainer as a base (or ubuntu:22.04)
ARG VARIANT="22.04"
FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-${VARIANT}

# avoid prompts
ENV DEBIAN_FRONTEND=noninteractive

# install build-tools, CMake, Git, Python (for Conan)
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    python3 \
    python3-pip \
 && rm -rf /var/lib/apt/lists/*

# install Conan (latest)
RUN pip3 install --no-cache-dir conan

# set up a default Conan profile
RUN conan profile detect

# ensure “conan” & “cmake” are in PATH
ENV PATH="/usr/local/bin:${PATH}"
