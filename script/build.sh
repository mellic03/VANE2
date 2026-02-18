#!/bin/bash
set -e

THIS_DIR=$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cd $THIS_DIR && source env.sh

opt_gpulib="GL"
opt_clean=""
opt_run=""
opt_bdtype=""

while [[ $# -gt 0 ]]; do
    case $1 in
        --gpulib=*)
            opt_gpulib="${1#*=}"
            shift
            ;;
        --clean)
            opt_clean=1
            shift
            ;;
        --run)
            opt_run=1
            shift
            ;;
        --debug)
            opt_bdtype="Debug"
            shift
            ;;
        --release)
            opt_bdtype="Release"
            shift
            ;;
        *)
            echo "Unknown option $1" >&2
            exit 1
            ;;
    esac
done


if [[ "$opt_clean" == "1" ]]; then
    rm -rf ${VANE_BUILD_DIR}
fi

mkdir -p "${VANE_BUILD_DIR}" && cd "${VANE_BUILD_DIR}"
cmake ../vane -DCMAKE_BUILD_TYPE="${opt_bdtype}" -DVANE_GFXLIB_GL=1
make -j$(nproc)

if [[ "$opt_run" == "1" ]]; then
    ./vane
fi
