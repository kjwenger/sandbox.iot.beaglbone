#!/usr/bin/env bash

CURRENT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

${CURRENT_DIR}/app-arm-linux-gnueabihf.sh
SCRIPTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "${SCRIPTS_DIR}")"
BUILD_DIR="${PROJECT_DIR}/build-arm-linux-gnueabihf"

scp "${BUILD_DIR}/sample/modbus-master" \
    "${BUILD_DIR}/sample/modbus-slave" \
    "debian@beaglebone:/home/debian"
