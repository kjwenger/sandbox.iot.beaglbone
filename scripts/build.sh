#!/usr/bin/env bash

CURRENT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

${CURRENT_DIR}/thirdparty/pcre.sh
${CURRENT_DIR}/thirdparty/zlib.sh
${CURRENT_DIR}/thirdparty/cppcms.sh
${CURRENT_DIR}/thirdparty/googletest.sh
${CURRENT_DIR}/thirdparty/curl.sh
${CURRENT_DIR}/thirdparty/curlpp.sh
${CURRENT_DIR}/thirdparty/hiberlite.sh

${CURRENT_DIR}/app.sh
