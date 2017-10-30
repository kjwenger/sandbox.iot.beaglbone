#!/usr/bin/env bash

set -x

CURRENT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

SCRIPTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "${SCRIPTS_DIR}")"
BUILD_DIR="${PROJECT_DIR}/build-arm-linux-gnueabihf"

sshpass -p 'temppwd' \
scp "${BUILD_DIR}/sample/modbus-master" \
    "${BUILD_DIR}/sample/modbus-slave" \
    "${BUILD_DIR}/sample/test_485" \
    "debian@beaglebone:/home/debian"

sshpass -p 'temppwd' \
ssh "debian@beaglebone" \
    "echo 'temppwd' | sudo -S mkdir -p /com.u14n/development/projects/sandbox/sandbox.iot/sandbox.iot.beaglebone/sample/src/"

sshpass -p 'temppwd' \
ssh "debian@beaglebone" \
    "echo 'temppwd' | sudo -S chown -R debian:debian /com.u14n"

sshpass -p 'temppwd' \
scp "${PROJECT_DIR}/sample/src/test_485.c" \
    "debian@beaglebone:/com.u14n/development/projects/sandbox/sandbox.iot/sandbox.iot.beaglebone/sample/src/test_485.c"
