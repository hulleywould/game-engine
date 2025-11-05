# Game Engine - 3D Phong Shading Demo

A simple 3D game engine built with C++, OpenGL, GLFW, GLEW, and GLM, featuring Phong shading with multiple light sources.

## Current Demo

The current demo renders **2 monkey head meshes** on screen with the following features:

- **Mesh**: Both meshes use the same model (`monkey3.obj`), positioned at different locations
- **Textures**: 
  - First monkey: `difuso_flip_oscuro.jpg` texture with brown tint (RGB: 0.6, 0.3, 0.0)
  - Second monkey: `wood.jpg` texture with white tint (RGB: 1.0, 1.0, 1.0)
- **Animation**: The first monkey head bobs up and down smoothly using a sine wave
- **Lighting Setup**:
  - 1 directional light (white, intensity 0.5)
  - 2 point lights (blue/purple tinted, intensity 0.8)
  - 1 moving spotlight (green, intensity 0.8) that sweeps across the scene
  - Ambient light (RGB: 0.1, 0.1, 0.1)
- **Rendering**: Both meshes are rendered with Phong shading including ambient, diffuse, and specular components

## Features

- **Phong Shading**: Realistic lighting with ambient, diffuse, and specular components
- **Multiple Light Types**: Directional lights, point lights, and spotlights
- **3D Model Loading**: OBJ file support
- **Texture Mapping**: Load and apply textures to 3D models
- **Camera Controls**: Navigate the 3D scene with keyboard and mouse
- **Parsec Remote Access**: Stream and view the game engine remotely with low latency

## Prerequisites

### System Requirements
- **C++ Compiler**: GCC/G++ with C++14 support
- **CMake**: Version 3.5 or higher
- **OpenGL**: Version 3.3+ (WSLg compatible)
- **Libraries**:
  - GLFW3 (windowing and input)
  - GLEW (OpenGL extension loading)
  - GLM (OpenGL Mathematics, header-only)
  - OpenGL development libraries

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

**Note**: The project includes a custom OBJ loader implementation for loading 3D models. No additional model loading libraries are required.

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

**What to expect**: When you run the game engine, you'll see a window displaying two monkey head meshes side by side. The left monkey head will bob up and down smoothly, and both will be lit by multiple dynamic light sources. You can use the camera controls (see Controls section) to navigate around the scene.

### 4. Remote Access with Parsec (Windows)

To view and control the game engine remotely:

**Note**: The game engine runs in WSL, while Parsec runs on Windows. Parsec will capture the WSLg window displaying your game engine.

1. **Check Parsec setup**:
   ```powershell
   .\check-parsec.ps1
   ```

2. **Launch with Parsec helper**:
   ```powershell
   .\launch-with-parsec.ps1
   ```
   This script will verify WSL/WSLg and launch the game engine automatically.

3. **Connect from another device**:
   - Install Parsec on your client device
   - Connect using your Windows machine's Parsec ID
   - View and control the game engine remotely (Parsec captures the WSLg window)

For detailed Parsec setup instructions, see [PARSEC_SETUP.md](PARSEC_SETUP.md).

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
│   ├── monkey3.obj     # Monkey head mesh (used in demo)
│   ├── wood.jpg        # Wood texture (used in demo)
│   └── difuso_flip_oscuro.jpg  # Dark texture (used in demo)
├── build/              # Build output directory
├── include/            # Header files
│   ├── MainGame.hpp    # Main game class
│   ├── Sprite.hpp      # Mesh rendering class
│   ├── PhongShader.hpp # Phong shading shader manager
│   ├── Camera.hpp      # Camera controls
│   └── ...             # Other component headers
├── src/                # Source files
│   ├── MainGame.cpp    # Main game loop and rendering
│   ├── Sprite.cpp      # Mesh loading and rendering
│   ├── obj_loader.cpp  # Custom OBJ file loader
│   └── shaders/        # GLSL shader files
│       ├── phongShading.vert  # Vertex shader
│       └── phongShading.frag  # Fragment shader
├── CMakeLists.txt     # Build configuration
├── install.sh         # Dependency installation script
├── build.sh           # Build script
├── WSL2_SETUP.md     # Detailed WSL2 setup guide
├── PARSEC_SETUP.md   # Parsec remote access setup guide
├── launch-with-parsec.ps1  # PowerShell script to launch with Parsec
└── check-parsec.ps1   # PowerShell script to check Parsec configuration
```

## Technical Details

### Rendering Pipeline
- **OpenGL Version**: 3.3 Core Profile (WSLg compatible)
- **Shading Language**: GLSL 3.30
- **C++ Standard**: C++14
- **Build System**: CMake 3.5+

### Assets Used

The current demo uses the following assets:

- **3D Models**:
  - `assets/monkey3.obj` - Monkey head mesh (loaded twice for the two instances)

- **Textures**:
  - `assets/difuso_flip_oscuro.jpg` - Texture applied to the first monkey head
  - `assets/wood.jpg` - Texture applied to the second monkey head

- **Shaders**:
  - `src/shaders/phongShading.vert` - Vertex shader (GLSL 330)
    - Handles vertex positions, texture coordinates, and normals
    - Transforms vertices to world space and clip space
  - `src/shaders/phongShading.frag` - Fragment shader with Phong lighting
    - Implements Phong shading with ambient, diffuse, and specular components
    - Supports up to 4 point lights and 4 spotlights
    - Calculates lighting contributions from all light sources

### Lighting Configuration

The demo scene uses the following lighting setup:

- **Ambient Light**: `vec3(0.1, 0.1, 0.1)` - Low-intensity base lighting
- **Directional Light**: 
  - Color: `vec3(1.0, 1.0, 1.0)` (white)
  - Intensity: `0.5`
  - Direction: `vec3(1.0, 1.0, 1.0)`
- **Point Light 1**:
  - Position: `vec3(1.0, 1.0, 1.0)`
  - Color: `vec3(0.4, 0.2, 1.0)` (purple-blue)
  - Intensity: `0.8`
  - Range: `10.0`
- **Point Light 2**:
  - Position: `vec3(1.0, 1.0, 1.0)`
  - Color: `vec3(0.0, 0.5, 1.0)` (blue)
  - Intensity: `0.8`
  - Range: `10.0`
- **Spotlight**:
  - Position: `vec3(7.0, 2.0, 1.0)`
  - Color: `vec3(0.0, 1.0, 0.0)` (green)
  - Intensity: `0.8`
  - Cutoff: `0.7`
  - **Note**: The spotlight direction moves dynamically based on a sine wave, creating a sweeping effect

### Code Structure

The main rendering loop is implemented in `MainGame::gameLoop()` (`src/MainGame.cpp`):

1. **Initialization**:
   - Creates two `Transform` objects for positioning the monkey heads
   - Loads textures and materials
   - Creates two `Sprite` objects (both using `monkey3.obj`)
   - Sets up lighting configuration

2. **Render Loop**:
   - Updates camera position based on input
   - Animates the first monkey head's Y position using `sin(counter) / 10`
   - Updates spotlight direction dynamically
   - Renders both meshes with their respective textures and materials
   - Uses Phong shader for lighting calculations

3. **Key Classes**:
   - `Sprite` - Handles mesh loading (OBJ files) and rendering
   - `Transform` - Manages model transformations (position, rotation, scale)
   - `PhongShader` - Manages shader uniforms and lighting setup
   - `Camera` - Handles view and projection matrices
   - `Material` - Stores material properties (texture, specular intensity/power)

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

### Parsec remote access issues
- Run `.\check-parsec.ps1` to diagnose configuration issues
- Ensure Parsec is running and hosting is enabled
- Check Windows Firewall settings
- See [PARSEC_SETUP.md](PARSEC_SETUP.md) for detailed troubleshooting

## License

This is a learning/demo project.

## Acknowledgments

- Uses stb_image for image loading
- Uses tiny_gltf for glTF model support
- Includes picojson for JSON parsing

