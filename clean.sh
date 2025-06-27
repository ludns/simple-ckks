#!/bin/bash

# Clean script to remove all build artifacts

echo "=== Cleaning all build directories ==="

echo "Removing build directory..."
rm -rf build/*

echo "Removing build-arm directory..."
rm -rf build-arm/*

echo "Removing any CMake cache files..."
find . -name "CMakeCache.txt" -delete
find . -name "cmake_install.cmake" -delete
find . -name "Makefile" -depth -delete 2>/dev/null || true
find . -name "CMakeFiles" -type d -exec rm -rf {} + 2>/dev/null || true

echo "=== Clean complete ==="