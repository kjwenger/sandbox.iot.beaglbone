#!/usr/bin/env bash

# Get latest packages
sudo apt update

# Get network tools
sudo apt install curl -y
sudo apt install wget -y

# Get version control tools
sudo apt install git -y
sudo apt install subversion -y

# Get development tools
sudo apt install build-essential -y
sudo apt install gcc -y
sudo apt install g++ -y
sudo apt install cmake -y
sudo apt install cppcheck -y
sudo apt install autotools-dev -y
sudo apt install autoconf -y
sudo apt install libtool -y
sudo apt install libpam0g-dev -y

sudo apt install clang-3.9
sudo apt install clang-3.9-doc
sudo apt install clang-3.9-examples
sudo apt install clang-format-3.9
sudo apt install clang-tidy-3.9

# Get test prerequisites
sudo apt install libcurl4-openssl-dev -y
sudo apt install libjsoncpp-dev -y
sudo apt install libjsoncpp1 -y
