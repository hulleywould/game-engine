# WSL2 Setup Guide for Game Engine

This guide will help you set up and run the Linux C++ game engine in WSL2 on Windows.

## Prerequisites

- WSL2 installed (âœ“ Already installed with Ubuntu)
- Windows 10 version 19044+ or Windows 11 (for WSLg GUI support)

## Step 1: Verify WSL2 Installation

Run in PowerShell:
```powershell
wsl --status
wsl --list --verbose
```

You should see Ubuntu running as version 2.

## Step 2: GUI Support Setup

### Option A: Windows 11 with WSLg (Recommended - Automatic)

If you're on Windows 11, WSLg is built-in and should work automatically. No additional setup needed!

### Option B: Windows 10 or Manual X11 Setup

If WSLg doesn't work or you're on Windows 10, you'll need an X server:

1. **Install VcXsrv Windows X Server**:
   - Download from: https://sourceforge.net/projects/vcxsrv/
   - Install it
   - Start "XLaunch" with these settings:
     - Display settings: Multiple windows
     - Client startup: Start no client
     - Extra settings: âœ“ Disable access control
   
2. **Set DISPLAY variable in WSL**:
   ```bash
   # Add to ~/.bashrc or ~/.zshrc
   export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
   ```

## Step 3: Install Dependencies in WSL

1. Open WSL terminal:
   ```powershell
   wsl
   ```

2. Navigate to the project directory:
   ```bash
   cd /mnt/c/Users/hulle/OneDrive/Desktop/mywork/game-engine
   ```

3. Run the installation script:
   ```bash
   sudo bash install.sh
   ```

This will install:
- build-essential (gcc, g++, make)
- cmake
- OpenGL development libraries
- GLFW3, GLEW, GLM libraries

## Step 4: Build the Project

```bash
mkdir -p build
cd build
cmake ..
make
```

## Step 5: Run the Game Engine

```bash
./game-engine
```

The window should appear either:
- Automatically (Windows 11 with WSLg)
- Through VcXsrv window (Windows 10 with X11 forwarding)

## Troubleshooting

### Issue: "Could not open window with GLFW3"
- **Solution**: Make sure DISPLAY is set correctly (for X11) or WSLg is enabled (Windows 11)

### Issue: "GLFW3 not found" during cmake
- **Solution**: Run `sudo apt-get install libglfw3-dev` manually

### Issue: OpenGL version error
- **Solution**: Make sure you have a graphics driver installed in Windows that supports OpenGL 4.1+

### Issue: Window appears but is black/blank
- **Solution**: This might be a shader issue. Check that shader files are in the correct location relative to the executable

## Build Script

For convenience, you can create a `build.sh` script:

```bash
#!/bin/bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

Make it executable: `chmod +x build.sh`

## Notes

- The project has been updated to work with modern OpenGL (removed deprecated `glEnable(GL_TEXTURE_2D)`)
- CMakeLists.txt now properly handles GLFW3 and GLM on Linux
- All dependencies can be installed via apt-get (no manual compilation needed)

