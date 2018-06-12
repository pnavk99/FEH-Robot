# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  install_desktop = true
  if install_desktop == true
    config.vm.box = "fso/xenial64-desktop"
    config.vm.box_version = "2017-11-15"
  else
    config.vm.box = "minimal/xenial64"    
  end
  config.vm.box_check_update = true

  install_pycharm = true
  install_intellij = false

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # config.vm.network "forwarded_port", guest: 80, host: 19720, host_ip: "127.0.0.1"
  # config.vm.network "forwarded_port", guest: 22, host: 2240, id: "ssh", host_ip: "127.0.0.1" # , auto_correct: true, disabled: true

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"
  # config.vm.synced_folder "local_host_folder/", "/vagrant_box_folder", create: true
  
  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  config.vm.provider "virtualbox" do |vb|
    # Display the VirtualBox GUI when booting the machine
    vb.gui = false
    # Set VirtualBox Name
    my_vm_name = Time.now.getutc
    my_vm_name = "taf_" + my_vm_name.strftime("%Y_%m_%d_%H_%M_%S")
    vb.name = my_vm_name
    # Customize the amount of memory on the VM:
    vb.memory = "2048"
  end
  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
  # Create user: autouser
  config.vm.provision "shell", inline: <<-SHELL
    # Uncomment the line below and add a password to enable log in.
    # export VAGRANT_AUTOUSER_PASSWORD=
    # Example: export VAGRANT_AUTOUSER_PASSWORD=Password01!
    export VAGRANT_AUTOUSER_PASSWORD=Password01!

    sudo adduser autouser
    sudo echo "autouser:$VAGRANT_AUTOUSER_PASSWORD" | chpasswd
    sudo usermod -aG sudo autouser
    sudo sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
    sudo sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd
    sudo apt-get install -y sshpass
  SHELL
  # Install prerequisites  
  config.vm.provision "shell", inline: <<-SHELL
    sudo apt-get update
    sudo apt-get install -y git
    sudo apt-get install -y python3
    sudo apt-get install -y python3-setuptools
    sudo easy_install3 pip
    sudo apt-get install -y default-jdk
    sudo apt-get install -y zip
    sudo apt-get install -y build-essential
    sudo apt-get install -y python3-dev
    sudo apt-get install -y libffi-dev
    sudo apt-get install -y libssl-dev
    sudo apt-get install -y chrpath
    sudo apt-get install -y libxft-dev
    sudo apt-get install -y libfreetype6
    sudo apt-get install -y libfreetype6-dev
    sudo apt-get install -y libfontconfig1
    sudo apt-get install -y libfontconfig1-dev
    sudo apt-get install -y dos2unix
    sudo apt-get install -y python-paramiko
    sudo pip install paramiko --upgrade
    sudo pip install pika
    sudo apt-get install -y python-requests
    sudo pip install virtualenv
    sudo apt-get install firefox
    sudo apt-get install -y chromium-browser
    # Phantom JS
    cd ~
    sudo rm -f phantomjs-1.9.8-linux-x86_64.tar.bz2
    sudo wget --no-check-certificate https://bitbucket.org/ariya/phantomjs/downloads/phantomjs-1.9.8-linux-x86_64.tar.bz2
    sudo tar xvjf phantomjs-1.9.8-linux-x86_64.tar.bz2
    sudo mv phantomjs-1.9.8-linux-x86_64 /usr/local/share
    sudo ln -sf /usr/local/share/phantomjs-1.9.8-linux-x86_64/bin/phantomjs /usr/local/bin
    sudo rm -f phantomjs-1.9.8-linux-x86_64.tar.bz2
    sudo rm -rf phantomjs-1.9.8-linux-x86_64
    # Gecko Driver
    cd ~
    sudo rm -f geckodriver-v0.18.0-linux64.tar.gz
    sudo wget --no-check-certificate https://github.com/mozilla/geckodriver/releases/download/v0.18.0/geckodriver-v0.18.0-linux64.tar.gz
    sudo tar -xvzf geckodriver*
    sudo mv geckodriver /usr/local/share
    sudo ln -sf /usr/local/share/geckodriver /usr/local/bin
    sudo rm -f geckodriver-v0.18.0-linux64.tar.gz
    # Chrome Driver
    cd ~
    sudo rm -f chromedriver_linux64.zip
    sudo wget --no-check-certificate -N http://chromedriver.storage.googleapis.com/2.32/chromedriver_linux64.zip -P ~/
    sudo unzip ~/chromedriver_linux64.zip -d ~/
    sudo mv ~/chromedriver /usr/local/share
    sudo ln -sf /usr/local/share/chromedriver /usr/local/bin
    sudo rm ~/chromedriver_linux64.zip
  SHELL
  # Install PyCharm IDE
  if install_pycharm == true
    config.vm.provision "shell", inline: <<-SHELL  
      sudo snap install pycharm-community --classic    
    SHELL
  end
  # Install IntelliJ IDE
  if install_pycharm == true
    config.vm.provision "shell", inline: <<-SHELL  
      sudo snap install intellij-idea-community --classic --edge
    SHELL
  end
  # Install Test Automation Framework
  config.vm.provision "shell", inline: <<-SHELL
    # TAF ENV Vars
    sudo echo "AF_BASE_PATH=/home/autouser/PycharmProjects/auto-framework" >> /etc/environment
    sudo echo "AF_CERT_PATH=/home/autouser/PycharmProjects/auto-framework/certs" >> /etc/environment
    sudo echo "AF_COMMON_LIB_PATH=/home/autouser/PycharmProjects/auto-framework/common_libs" >> /etc/environment
    sudo echo "AF_LIB_PATH=/home/autouser/PycharmProjects/auto-framework/libs" >> /etc/environment
    sudo echo "AF_REPORTS_PATH=/home/autouser/PycharmProjects/auto-framework/test_suites/reports" >> /etc/environment
    sudo echo "AF_RESOURCES_PATH=/home/autouser/PycharmProjects/auto-framework/resources" >> /etc/environment
    sudo echo "AF_RUN_JOBS_PATH=/home/autouser/PycharmProjects/auto-framework/run_jobs" >> /etc/environment
    sudo echo "AF_TEST_SUITE_NAME=Test_Suite_Name_Not_Set" >> /etc/environment
    sudo echo "AF_TEST_SUITE_PATH=/home/autouser/PycharmProjects/auto-framework/test_suites" >> /etc/environment
    sudo echo "DISPLAY=:0" >> /etc/environment
    sudo echo "PYTEST_ADDOPTS=\"-v -W ignore\"" >> /etc/environment
    sudo echo "PYTEST_TIMEOUT=1800" >> /etc/environment
    sudo echo "PYTHONPATH=/home/autouser/PycharmProjects/auto-framework/common_libs" >> /etc/environment
    sudo echo "VISIBLE=now" >> /etc/environment
    # TAF Platform and Version
    echo "Version=$(date)" > /home/autouser/vagrant-version.txt
    # Create af_install.sh
    sudo echo "cd" > /af_install.sh
    sudo echo "rm auto-framework.zip" >> /af_install.sh
    sudo echo "wget --no-check-certificate http://waldevkbmgizl01.dev.rocketsoftware.com:8081/artifactory/generic-local/internal-tooling/taf/auto-framework.zip" >> /af_install.sh
    sudo echo "chmod +x auto-framework.zip" >> /af_install.sh
    sudo echo "mkdir -p /home/autouser/PycharmProjects/auto-framework" >> /af_install.sh
    sudo echo "unzip -o auto-framework.zip -d /home/autouser/PycharmProjects/auto-framework" >> /af_install.sh
    sudo echo ". /home/autouser/PycharmProjects/auto-framework/env_setup/af_setup.sh" >> /af_install.sh
    # Update /etc/bash.bashrc
    sudo echo "" >> /etc/bash.bashrc
    sudo echo "" >> /etc/bash.bashrc
    sudo echo "if [ \$""USER = autouser ]; then" >> /etc/bash.bashrc
    sudo echo "    if [ ! -f /home/autouser/auto-framework.zip ]; then" >> /etc/bash.bashrc
    sudo echo "        . /af_install.sh" >> /etc/bash.bashrc
    sudo echo "    fi" >> /etc/bash.bashrc
    sudo echo "    alias af_debug_on='export AF_DEBUG=TRUE'" >> /etc/bash.bashrc
    sudo echo "    alias af_debug_off='export AF_DEBUG=FALSE'" >> /etc/bash.bashrc
    sudo echo "    alias af_env='. \$""HOME/af_env.sh; echo; echo Test Automation Environment Loaded; echo'" >> /etc/bash.bashrc
    sudo echo "    alias af_link_test_packs='python \$""AF_BASE_PATH/test_packs_mapping.py --function link; echo'" >> /etc/bash.bashrc
    sudo echo "    alias af_unlink_test_packs='python \$""AF_BASE_PATH/test_packs_mapping.py --function unlink; echo'" >> /etc/bash.bashrc
    sudo echo "    alias af_remove_reports='rm -rf \$""AF_REPORTS_PATH; echo; echo All Reports Removed; echo'" >> /etc/bash.bashrc
    sudo echo "    alias af_update_framework='. /af_install.sh; echo; echo Test Automation Framework Updated; echo'" >> /etc/bash.bashrc
    sudo echo "    . \$""HOME/af_env.sh" >> /etc/bash.bashrc
    sudo echo "fi" >> /etc/bash.bashrc
    sudo echo "" >> /etc/bash.bashrc
  SHELL
  if install_desktop == true  
      config.vm.provision "shell", inline: <<-SHELL
        # Update /etc/lightdm/lightdm.conf
        sudo echo "[SeatDefaults]" > /etc/lightdm/lightdm.conf
        sudo echo "autologin-user=autouser" >> /etc/lightdm/lightdm.conf
        sudo echo "allow-guest=false" >> /etc/lightdm/lightdm.conf
        sudo echo "greeter-hide-users=true" >> /etc/lightdm/lightdm.conf
        sudo echo "greeter-show-manual-login=true" >> /etc/lightdm/lightdm.conf
        # Update /etc/profile
        sudo echo "" >> /etc/profile    
        sudo echo "dconf write /org/gnome/desktop/screensaver/idle-activation-enabled false" >> /etc/profile
        sudo echo "dconf write /org/gnome/desktop/screensaver/lock-enabled false" >> /etc/profile
        sudo echo ""
        sudo echo "Please run the command: 'vagrant reload'  to complete the setup."
        sudo echo "Please run the command: 'vagrant reload'  to complete the setup."
        sudo echo "Please run the command: 'vagrant reload'  to complete the setup."
        sudo echo ""
      SHELL
  end
end
