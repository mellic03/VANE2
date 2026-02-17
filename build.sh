#!/bin/bash

set -e

THIS_DIR=$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

opt_clean=""
opt_run=""

while [[ $# -gt 0 ]]; do
    case $1 in
        --clean)
            opt_clean=1
            shift
            ;;
        --run)
            opt_run=1
            shift
            ;;
        *)
            echo "Unknown option $1" >&2
            exit 1
            ;;
    esac
done


if [[ "$opt_clean" == "1" ]]; then
    rm -rf "${THIS_DIR}/build"
fi

mkdir -p build && cd build
cmake -G Ninja .. -DVANE_GPULIB_GL=1
ninja -j6

if [[ "$opt_run" == "1" ]]; then
    ./vane
fi
