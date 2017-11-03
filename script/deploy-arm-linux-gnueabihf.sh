#!/usr/bin/env bash

#set -x

USER=${1:-debian}
PASSWORD=${2:-temppwd}
HOST=${3:-beaglebone}

CURRENT_DIR="$(pwd)"

SCRIPTS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "${SCRIPTS_DIR}")"

MULTIARCH_TUPLE="arm-linux-gnueabihf"
BUILD_DIR="${PROJECT_DIR}/build-${MULTIARCH_TUPLE}"

sshpass -p "${PASSWORD}" \
scp "${BUILD_DIR}/sample/modbus-master" \
    "${BUILD_DIR}/sample/modbus-slave" \
    "${BUILD_DIR}/sample/test_485" \
    "${USER}@${HOST}:/home/${USER}"

sshpass -p "${PASSWORD}" \
ssh "${USER}@${HOST}" \
    "echo '${PASSWORD}' | sudo -S mkdir -p /com.u14n/development/projects/sandbox/sandbox.iot/sandbox.iot.beaglebone/sample/src/"

sshpass -p "${PASSWORD}" \
ssh "${USER}@${HOST}" \
    "echo '${PASSWORD}' | sudo -S chown -R ${USER}:${USER} /com.u14n"

sshpass -p "${PASSWORD}" \
scp -r \
    "${PROJECT_DIR}/sample/src/"* \
    "${USER}@${HOST}:/com.u14n/development/projects/sandbox/sandbox.iot/sandbox.iot.beaglebone/sample/src/"
