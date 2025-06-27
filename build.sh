#!/bin/bash

# Build script for native build
# This script cleans, configures and builds the project for the host system

set -e  # Exit on error

echo "=== Building simple-ckks for native platform ==="

# Clean build directory
echo "Cleaning build directory..."
rm -rf build/*

# Configure with CMake
echo "Configuring with CMake..."
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build
echo "Building..."
cd build
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo "=== Build complete ==="
echo "Binaries are in: $(pwd)"
echo ""
echo "To run tests: ./build/tests"
echo "To run demo: ./build/ckks_demo"