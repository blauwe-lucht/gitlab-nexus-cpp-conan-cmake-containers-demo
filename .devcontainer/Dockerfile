FROM almalinux:9

RUN dnf install -y \
      gcc gcc-c++ make \
      cmake \
      git \
      python3 python3-pip \
      sudo \
      docker \
    && dnf clean all

# Create the vscode user (UID/GID 1000), give it passwordless sudo, and add it to the docker group
RUN groupadd --gid 1000 vscode \
    && useradd --uid 1000 --gid vscode -m vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/vscode \
    && chmod 0440 /etc/sudoers.d/vscode \
    && groupadd docker \
    && usermod -aG docker vscode

# install Conan
RUN pip3 install --no-cache-dir conan

# Add ll alias for the vscode user
RUN echo "alias ll='ls -alF'" >> /home/vscode/.bashrc

# Create Conan profile, prevent gtest requirements error.
USER vscode
RUN conan profile detect \
    && sed -i 's/compiler.cppstd=gnu17/compiler.cppstd=17/' ~/.conan2/profiles/default \
    && conan remote add conan-hosted http://172.17.0.1:8081/repository/conan-hosted/ --insecure \
    && conan remote login conan-hosted conan-upload -p "Abcd1234!"
USER root

ENV PATH="/usr/local/bin:${PATH}"
