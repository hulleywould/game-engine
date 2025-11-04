#!/bin/bash
# Linux (Ubuntu/Debian) dependency installation script for WSL2
# Run with: sudo bash install.sh

set -e  # Exit on error

echo "Updating package lists..."
sudo apt-get update

echo "Installing build essentials and CMake..."
sudo apt-get install -y build-essential cmake

echo "Installing OpenGL development libraries..."
sudo apt-get install -y libgl1-mesa-dev libglu1-mesa-dev

echo "Installing GLFW3 development libraries..."
sudo apt-get install -y libglfw3-dev

echo "Installing GLEW development libraries..."
sudo apt-get install -y libglew-dev

echo "Installing GLM (header-only library)..."
sudo apt-get install -y libglm-dev

echo "Installation complete!"
echo "To build the project, run:"
echo "  mkdir -p build && cd build"
echo "  cmake .."
echo "  make"
