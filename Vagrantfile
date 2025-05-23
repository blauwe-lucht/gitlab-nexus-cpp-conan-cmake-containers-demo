Vagrant.configure("2") do |config|
    config.vm.box = "almalinux/9"
    config.vm.hostname = "harbor"
    config.vm.network "private_network", ip: "192.168.15.28"

    config.vm.provision "shell", inline: <<-SHELL
        dnf -y update
        dnf -y install dnf-plugins-core
        dnf config-manager --add-repo=https://download.docker.com/linux/centos/docker-ce.repo
        dnf -y install docker-ce docker-ce-cli containerd.io
        systemctl enable --now docker
        usermod -aG docker vagrant
    SHELL
end