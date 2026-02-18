#!/bin/bash

export VANE_SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
export VANE_PROJECT_ROOT=$(cd ${VANE_SCRIPT_DIR}/../ && pwd)
export VANE_THIRDPARTY_DIR="${VANE_PROJECT_ROOT}/external"
export VANE_BUILD_DIR="${VANE_PROJECT_ROOT}/build"
export VANE_OUTPUT_DIR="${VANE_PROJECT_ROOT}/output"
export VANE_SOURCE_DIR="${VANE_PROJECT_ROOT}/vane/src"
export VANE_INCLUDE_DIR="${VANE_PROJECT_ROOT}/vane/include"

export THIRDPARTY_INSTALL_PREFIX="${VANE_THIRDPARTY_DIR}/install"

export THIRDPARTY_VK_VERSION="1.4.304.0"
# export THIRDPARTY_VK_VERSION="1.4.341.1"

# source "${VANE_THIRDPARTY_DIR}/repo/vulkan/${THIRDPARTY_VK_VERSION}/setup-env.sh"
