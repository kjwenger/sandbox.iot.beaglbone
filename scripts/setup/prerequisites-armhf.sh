#!/usr/bin/env bash

# Add ARM HF for BeagleBone
sudo dpkg --add-architecture armhf
sudo dpkg --print-foreign-architectures

# Get latest packages
sudo apt update

# Get development tools
sudo apt install crossbuild-essential-armhf -y
