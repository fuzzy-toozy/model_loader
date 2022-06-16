#!/usr/bin/env bash

set -e

ROOT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}"; )" &> /dev/null && pwd 2> /dev/null; )";
BUILD_DIR=${ROOT_DIR}/build
mkdir -p ${BUILD_DIR}

rm -r ${BUILD_DIR}/soil || true
mkdir -p ${BUILD_DIR}/soil
cd ${ROOT_DIR}/externals/soil/
./configure
make -j4
mv build/* ${BUILD_DIR}/soil
rm -r build

cd ${ROOT_DIR}/externals/glfw-3.3.4/
cmake -B${BUILD_DIR}/glfw
cd ${BUILD_DIR}/glfw
make -j4

cd ${ROOT_DIR}/externals/glew-2.1.0/build/cmake
cmake -B${BUILD_DIR}/glew
cd ${BUILD_DIR}/glew
make -j4

cd ${ROOT_DIR}/externals/assimp-3.1.1/
cmake -B${BUILD_DIR}/assimp
cd ${BUILD_DIR}/assimp
make -j4
