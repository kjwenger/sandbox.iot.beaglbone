#!/usr/bin/env bash

set -x

CPUS=$(lscpu | grep "^CPU(s):" | sed s/"CPU(s):                "//)

CURRENT_DIR="$(pwd)"
SCRIPTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "${SCRIPTS_DIR}")"
USR_DIR="${PROJECT_DIR}/usr"

cd "${PROJECT_DIR}"
cppcheck include src
mkdir -p build-arm-linux-gnueabihf
pushd build-arm-linux-gnueabihf
cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON \
      -DCMAKE_TOOLCHAIN_FILE="${PROJECT_DIR}/toolchains/arm-linux-gnueabihf.cmake" \
      -DDISABLE_ICU_LOCALIZATION=ON \
      -DCMAKE_INSTALL_PREFIX="${USR_DIR}/arm-linux-gnueabihf" \
      ..
make -j ${CPUS}
popd
cd "${CURRENT_DIR}"
