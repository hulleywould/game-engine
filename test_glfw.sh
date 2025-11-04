#!/bin/bash
# Test GLFW window creation
# This will help diagnose the GLFW window creation issue

echo "Testing GLFW setup..."
echo "DISPLAY=$DISPLAY"
echo "WAYLAND_DISPLAY=$WAYLAND_DISPLAY"

# Try to run a simple GLFW test
cd /mnt/c/Users/hulle/OneDrive/Desktop/mywork/game-engine/build

echo ""
echo "Running game-engine with error reporting..."
./game-engine 2>&1

echo ""
echo "If the above failed, trying with explicit X11 backend..."
XDG_SESSION_TYPE=x11 ./game-engine 2>&1 || echo "X11 backend failed"

echo ""
echo "If still failing, trying with Wayland backend..."
XDG_SESSION_TYPE=wayland ./game-engine 2>&1 || echo "Wayland backend failed"

