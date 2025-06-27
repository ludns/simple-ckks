#!/bin/bash

# Build script for ARM cross-compilation
# This script cleans, configures and builds the project for ARM64 target

set -e  # Exit on error

echo "=== Building simple-ckks for ARM64 (aarch64) ==="

# Check if cross-compiler is available
if ! command -v aarch64-unknown-linux-gnu-gcc &> /dev/null; then
    echo "Error: aarch64-unknown-linux-gnu-gcc not found in PATH"
    echo "Please install the cross-compiler first"
    exit 1
fi

# Check if sysroot exists
if [ ! -d "$HOME/dev/gp/imx-sysroot" ]; then
    echo "Warning: Sysroot not found at $HOME/dev/gp/imx-sysroot"
    echo "The build might fail. Make sure the sysroot path is correct."
fi

# Clean build directory
echo "Cleaning build-arm directory..."
rm -rf build-arm/*

# Configure with CMake using toolchain file
echo "Configuring with CMake for ARM64..."
cmake -B build-arm -S . \
    -DCMAKE_TOOLCHAIN_FILE=toolchain-aarch64.cmake \
    -DCMAKE_BUILD_TYPE=Release

# Build only the demo (skip tests for cross-compilation)
echo "Building ckks_demo for ARM64..."
cd build-arm
make ckks_demo -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Strip the binary to reduce size
echo "Creating stripped version..."
aarch64-unknown-linux-gnu-strip -s ckks_demo -o ckks_demo_stripped || echo "Strip failed, continuing with unstripped binary"

echo "=== Build complete ==="
echo "ARM64 binary: $(pwd)/ckks_demo ($(du -h ckks_demo | cut -f1))"
if [ -f ckks_demo_stripped ]; then
    echo "Stripped binary: $(pwd)/ckks_demo_stripped ($(du -h ckks_demo_stripped | cut -f1))"
fi
echo ""
echo "To copy to the board:"
echo "  scp $(pwd)/ckks_demo root@nxp1:/path/to/destination/"
