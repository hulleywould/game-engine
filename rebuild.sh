#!/bin/bash
# Clean rebuild script to fix CMake cache path mismatch

echo "Cleaning build directory..."
rm -rf build

echo "Creating fresh build directory..."
mkdir -p build
cd build

echo "Running CMake..."
cmake ..

echo "Building project..."
make -j$(nproc)

echo ""
echo "Build complete! Run with: ./build/game-engine"

