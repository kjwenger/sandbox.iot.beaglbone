#!/usr/bin/env bash

CURRENT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

${CURRENT_DIR}/thirdparty/pcre-arm-linux-gnueabihf.sh
${CURRENT_DIR}/thirdparty/zlib-arm-linux-gnueabihf.sh
${CURRENT_DIR}/thirdparty/cppcms-arm-linux-gnueabihf.sh
${CURRENT_DIR}/thirdparty/googletest-arm-linux-gnueabihf.sh
${CURRENT_DIR}/thirdparty/curl-arm-linux-gnueabihf.sh
${CURRENT_DIR}/thirdparty/curlpp-arm-linux-gnueabihf.sh
${CURRENT_DIR}/thirdparty/hiberlite-arm-linux-gnueabihf.sh

${CURRENT_DIR}/app-arm-linux-gnueabihf.sh
