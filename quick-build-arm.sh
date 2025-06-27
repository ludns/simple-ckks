#!/bin/bash

# Quick rebuild script for ARM - doesn't clean, just rebuilds
# Use this when you've only changed source files, not CMakeLists.txt

set -e  # Exit on error

echo "=== Quick rebuild for ARM64 ==="

# Check if build-arm exists and is configured
if [ ! -f "build-arm/Makefile" ]; then
    echo "No Makefile found. Running full build instead..."
    ./build-arm.sh
    exit 0
fi

# Just run make
cd build-arm
echo "Building ckks_demo..."
make ckks_demo -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo "=== Build complete ==="
echo "ARM64 binary: $(pwd)/ckks_demo ($(du -h ckks_demo | cut -f1))"