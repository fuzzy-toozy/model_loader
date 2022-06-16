#!/usr/bin/env bash

set -e
sudi apt install build-essential
sudo apt install cmake
sudo apt install libglu1-mesa-dev
sudo apt install libxrandr-de
sudo apt install libxrandr-dev
sudo apt install libxinerama-dev
sudo apt install libxcursor-dev
sudo apt install libxi-dev
sudo apt-get install libcurl4-gnutls-dev
git clone https://github.com/clibs/clib.git /tmp/clib || true
cd /tmp/clib && make -j4 && sudo make install
