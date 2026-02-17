#!/bin/bash

opt_type=""
opt_clean=""

while [[ $# -gt 0 ]]; do
    case $1 in
        --type)
            opt_type="$2"
            shift
            shift
            ;;
        --clean)
            opt_clean=1
            shift
            ;;
        *)
            echo "Unknown option $1" >&2
            exit 1
            ;;
    esac
done


if [[ "$opt_clean" == "1" ]]; then
    rm -rf ./build
fi

