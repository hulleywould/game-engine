# Changes Made for WSL2 Compatibility

This document details all changes made to run the Linux C++ game engine on Windows via WSL2.

## Summary

The game engine originally built for Linux/macOS has been successfully ported to run on Windows using WSL2 with GUI support through WSLg.

## Files Modified

### 1. `install.sh`
**Changes:**
- Replaced Homebrew (macOS) commands with apt-get (Linux/Ubuntu)
- Added all required OpenGL and development dependencies
- Fixed line endings (CRLF → LF)

**New dependencies installed:**
- build-essential, cmake
- libgl1-mesa-dev, libglu1-mesa-dev
- libglfw3-dev
- libglew-dev
- libglm-dev

### 2. `CMakeLists.txt`
**Changes:**
- Enhanced GLFW3 package finding (tries both `glfw3` and `glfw`)
- Added GLM support via pkg-config
- **Critical: Added automatic copying of shaders and assets to build directory**
- Improved cross-platform compatibility

**Key addition:**
```cmake
# Copy shader files and assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/src/shaders DESTINATION ${CMAKE_BINARY_DIR}/src)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
```

### 3. `src/MainGame.cpp`
**Changes:**
- **OpenGL version**: Changed from 4.1 to 3.3 (WSLg supports up to 3.3)
- Added Linux-specific OpenGL profile configuration
- Set `GLFW_OPENGL_FORWARD_COMPAT` to `GL_FALSE` for Linux
- Added fallback mechanism: tries core profile first, falls back to compatibility profile
- Enhanced error reporting with GLFW error codes and descriptions
- Removed deprecated `glEnable(GL_TEXTURE_2D)` call

**Before:**
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glEnable(GL_TEXTURE_2D);
```

**After:**
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
// glEnable(GL_TEXTURE_2D) removed - deprecated in OpenGL 3.1+
```

### 4. Shader Files
**All shader files updated:**
- `src/shaders/phongShading.vert`
- `src/shaders/phongShading.frag`
- `src/shaders/colorShading.vert`
- `src/shaders/colorShading.frag`

**Changes:**
- GLSL version: 4.00 → 3.30
- Fixed line endings (CRLF → LF)

**Before:**
```glsl
#version 400
```

**After:**
```glsl
#version 330
```

## New Files Created

### 1. `WSL2_SETUP.md`
Comprehensive setup guide including:
- WSL2 installation verification
- GUI support configuration (WSLg vs X11)
- Step-by-step build instructions
- Troubleshooting guide

### 2. `build.sh`
Convenience build script for quick compilation:
```bash
#!/bin/bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

### 3. `test_glfw.sh`
Diagnostic script to test different GLFW backends (X11 vs Wayland)

### 4. `README.md`
Complete project documentation with:
- Feature list
- Installation instructions
- Controls
- Technical details
- Troubleshooting

## Key Technical Changes

### OpenGL Version Compatibility
- **Original**: OpenGL 4.1 Core Profile
- **Updated**: OpenGL 3.3 Core Profile
- **Reason**: WSLg's Mesa implementation supports up to OpenGL 3.3

### GLSL Version Compatibility
- **Original**: GLSL 4.00
- **Updated**: GLSL 3.30
- **Reason**: Matches OpenGL 3.3; WSLg Mesa supports GLSL versions: 1.10, 1.20, 1.30, 1.40, 1.50, 3.30, 1.00 ES, 3.00 ES

### Window Creation Strategy
Added intelligent fallback:
1. First tries OpenGL 3.3 Core Profile
2. If that fails, automatically tries Compatibility Profile
3. Provides detailed error messages for debugging

### Build System Enhancement
CMake now automatically:
- Copies shader files from `src/shaders/` to `build/src/shaders/`
- Copies assets from `assets/` to `build/assets/`
- Ensures executable can find resources at runtime

## Testing Environment

**Successfully tested on:**
- Windows 11 (Build 26200)
- WSL version: 2.3.24.0
- WSLg version: 1.0.65
- Ubuntu 20.04 on WSL2
- OpenGL: 3.3 Core Profile Mesa 21.2.6
- Renderer: D3D12 (AMD Radeon(TM) Vega 8 Graphics)

## Known Limitations

1. **OpenGL Version**: Limited to 3.3 by WSLg (not an issue for this project)
2. **Performance**: Slightly slower than native Linux due to WSL2 translation layer
3. **GPU Access**: Uses software rendering through D3D12 translation layer

## Benefits of This Approach

1. **No Code Duplication**: Maintains single codebase
2. **Linux-First**: Preserves Linux compatibility
3. **No Windows-Specific APIs**: Uses standard OpenGL/GLFW
4. **Easy Setup**: Simple dependency installation via apt-get
5. **GUI Support**: WSLg provides seamless window display

## Alternative Approaches Considered

1. **Native Windows Build**: Would require significant code changes
2. **Docker with X11**: More complex setup, similar performance
3. **Virtual Machine**: Much slower, more resource intensive

WSL2 with WSLg was chosen as the optimal solution for this use case.

