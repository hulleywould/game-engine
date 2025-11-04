#!/bin/bash
# Build script for the game engine
# Usage: ./build.sh

set -e  # Exit on error

echo "Building game engine..."
mkdir -p build
cd build

echo "Running CMake..."
cmake ..

echo "Compiling..."
make -j$(nproc)

echo "Build complete! Run with: ./build/game-engine"
echo "Or from build directory: ./game-engine"

