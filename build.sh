#!/usr/bin/env bash
set -e
./build_exts.sh
cmake -Bbuild
cd build && make -j4

