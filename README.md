# Game Engine - 3D Phong Shading Demo

A simple 3D game engine built with C++, OpenGL, GLFW, GLEW, and GLM, featuring Phong shading with multiple light sources.

## Features

- **Phong Shading**: Realistic lighting with ambient, diffuse, and specular components
- **Multiple Light Types**: Directional lights, point lights, and spotlights
- **3D Model Loading**: OBJ file support
- **Texture Mapping**: Load and apply textures to 3D models
- **Camera Controls**: Navigate the 3D scene with keyboard and mouse

## Prerequisites

### Windows (WSL2)
- Windows 10 version 19044+ or Windows 11
- WSL2 installed with Ubuntu
- WSLg for GUI support (automatically included in Windows 11)

## Installation

### 1. Install Dependencies

```bash
sudo bash install.sh
```

This installs:
- build-essential (gcc, g++, make)
- cmake
- OpenGL development libraries (Mesa)
- GLFW3, GLEW, GLM libraries

### 2. Build the Project

```bash
./build.sh
```

Or manually:
```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

### 3. Run the Game Engine

From the build directory:
```bash
cd build
./game-engine
```

Or from the project root:
```bash
./build/game-engine
```

## Controls

- **W/S**: Move camera up/down
- **A/D**: Move camera left/right
- **Q/E**: Zoom in/out
- **Left Mouse Button**: Rotate view
- **ESC**: Exit

## Project Structure

```
game-engine/
├── assets/              # 3D models and textures
├── build/              # Build output directory
├── include/            # Header files
├── src/                # Source files
│   └── shaders/       # GLSL shader files
├── CMakeLists.txt     # Build configuration
├── install.sh         # Dependency installation script
├── build.sh           # Build script
└── WSL2_SETUP.md     # Detailed WSL2 setup guide
```

## Technical Details

- **OpenGL Version**: 3.3 Core Profile (WSLg compatible)
- **Shading Language**: GLSL 3.30
- **C++ Standard**: C++14
- **Build System**: CMake 3.5+

## Modifications for WSL2

This project has been updated to run on WSL2:

1. **OpenGL Version**: Changed from 4.1 to 3.3 for WSLg compatibility
2. **Shaders**: Updated from GLSL 4.00 to GLSL 3.30
3. **Build System**: Enhanced CMakeLists.txt with automatic shader/asset copying
4. **Compatibility**: Added fallback from core profile to compatibility profile

## Troubleshooting

### Window doesn't appear
- Ensure WSLg is installed: `wsl --version`
- Check DISPLAY variable: `echo $DISPLAY`
- For Windows 10, you may need to install VcXsrv

### Shader compilation errors
- Shaders are automatically copied to build directory during CMake configuration
- Ensure shader files are present in `build/src/shaders/`

### Build errors
- Make sure all dependencies are installed: `sudo bash install.sh`
- Clean build: `rm -rf build && mkdir build && cd build && cmake .. && make`

## License

This is a learning/demo project.

## Acknowledgments

- Uses stb_image for image loading
- Uses tiny_gltf for glTF model support
- Includes picojson for JSON parsing

