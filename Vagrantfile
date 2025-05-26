Vagrant.configure("2") do |config|
    config.vm.box = "almalinux/9"
    {
        "test-server" => "192.168.8.18",
        "acceptance-server" => "192.168.8.19"
    }.each do |name, ip|
        config.vm.define name do |vm_config|
            vm_config.vm.hostname = name
            vm_config.vm.network "private_network", ip: ip
            vm_config.vm.provision "shell", inline: <<-SHELL
                dnf -y update
                dnf -y install python3-requests

                # Install Docker
                dnf -y install dnf-plugins-core
                dnf config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
                dnf -y install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

                # Configure Docker to trust registry.local:5000 as insecure
                mkdir -p /etc/docker
                echo '{' > /etc/docker/daemon.json
                echo '    "insecure-registries" : ["registry.local:5000"]' >> /etc/docker/daemon.json
                echo '}' >> /etc/docker/daemon.json

                # Start and enable Docker service
                systemctl daemon-reexec
                systemctl restart docker
                systemctl enable docker

                # Add vagrant user to docker group
                usermod -aG docker vagrant

                # Add registry.local to hosts
                if ! grep -q "10.0.2.2 registry.local" /etc/hosts; then
                    echo "10.0.2.2 registry.local" >> /etc/hosts
                fi
            SHELL
        end
    end
end
