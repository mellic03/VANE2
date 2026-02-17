#!/bin/bash

THIS_DIR=$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cd "${THIS_DIR}"

if [[ ! -d "${THIS_DIR}/glslc" ]]; then
    if [[ ! -f "./glslc.tgz" ]]; then
        wget "https://storage.googleapis.com/shaderc/artifacts/prod/graphics_shader_compiler/shaderc/linux/continuous_gcc_release/515/20260126-070259/install.tgz"
        mv install.tgz glslc.tgz
    fi
    tar -xvzf ./glslc.tgz
    mv ${THIS_DIR}/install ${THIS_DIR}/glslc
fi


mkdir -p $THIS_DIR/vulkan && cd $THIS_DIR/vulkan
VK_VERSION="1.4.341.1"
VK_DIRNAME=$VK_VERSION
VK_FILENAME="vulkansdk-linux-x86_64-${VK_VERSION}.tar.xz"

if [[ ! -d $VK_DIRNAME ]]; then
    if [[ ! -f $VK_FILENAME ]]; then
        wget "https://sdk.lunarg.com/sdk/download/1.4.341.1/linux/${VK_FILENAME}"
    fi
    tar -xvf $VK_FILENAME
fi
