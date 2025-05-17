FROM almalinux:9

# install build essentials, cmake, git, python (for Conan), etc.
RUN dnf install -y \
      gcc gcc-c++ make \
      cmake \
      git \
      python3 python3-pip \
    && dnf clean all

# Create the vscode user (UID/GID 1000), give it passwordless sudo
RUN dnf install -y sudo \
    && groupadd --gid 1000 vscode \
    && useradd --uid 1000 --gid vscode -m vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/vscode \
    && chmod 0440 /etc/sudoers.d/vscode \
    && dnf clean all

# install Conan
RUN pip3 install --no-cache-dir conan

# bootstrap your Conan profile as needed
USER vscode
RUN conan profile detect
USER root

ENV PATH="/usr/local/bin:${PATH}"
