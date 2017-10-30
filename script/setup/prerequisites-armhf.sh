#!/usr/bin/env bash

# Add ARM HF for BeagleBone
sudo dpkg --add-architecture armhf
sudo dpkg --print-foreign-architectures

# Get latest packages
sudo apt update

# Get development tools
sudo apt install crossbuild-essential-armhf -y
sudo apt install gdb-arm-none-eabi -y

# Get prerequisites
sudo apt install libmodbus5:armhf -y
sudo apt install libmodbus-dev:armhf -y
