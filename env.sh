#!/bin/bash

THIS_DIR=$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
export PATH="${THIS_DIR}/external/glslc/bin:${PATH}"
