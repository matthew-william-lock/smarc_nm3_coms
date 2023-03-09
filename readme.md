# smarc_nm3_coms

Underwater communications for SAM and LoLo using the University of Newcastle's NanoModem3.

## Installation

1. Install the [Dynamic Compact Control Language (DCCL)](https://github.com/GobySoft/dccl) marshealling library.

On Ubuntu:

```bash
echo "deb http://packages.gobysoft.org/ubuntu/release/ `lsb_release -c -s`/" | sudo tee /etc/apt/sources.list.d/gobysoft_release.list
sudo apt-key adv --recv-key --keyserver keyserver.ubuntu.com 19478082E2F8D3FE
sudo apt update
# minimal
sudo apt install libdccl4-dev
# full
sudo apt install libdccl4-dev dccl4-compiler dccl4-apps
```

## Usage

Running example talker and listener:

1. On sender:

```bash
roslaunch smarc_nm3_coms dccl_talker.launch
```