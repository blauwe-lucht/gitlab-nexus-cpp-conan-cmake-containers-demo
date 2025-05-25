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
                dnf -y install podman podman-docker
                
                if ! grep -q "10.0.2.2 registry.local" /etc/hosts; then
                    echo "10.0.2.2 registry.local" >> /etc/hosts
                fi
            SHELL
        end
    end
end