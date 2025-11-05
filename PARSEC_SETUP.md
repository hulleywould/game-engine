# Parsec Remote Access Setup Guide

This guide will help you set up Parsec to remotely view and control your game engine running on Windows.

## Overview

Parsec allows you to stream your game engine remotely with low latency, making it perfect for:
- Viewing the game engine from another device
- Remote development and testing
- Sharing your work with others

**Important**: This game engine runs in WSL (Windows Subsystem for Linux), and Parsec runs on Windows. Parsec will capture the WSLg window that displays your game engine, allowing remote viewing and control.

## Prerequisites

- Parsec installed on your Windows machine (host)
- Parsec account (free tier available)
- Stable internet connection
- Client device with Parsec installed (for remote access)

## Setup Instructions

### 1. Host Machine Setup (Your Windows PC)

#### Step 1: Launch Parsec
1. Open Parsec application on your Windows machine
2. Sign in or create a free account
3. Go to **Settings** → **Host** tab

#### Step 2: Enable Hosting
1. Toggle **Host** to **ON**
2. Set a **Computer Name** (e.g., "Game-Engine-Dev")
3. Note your **Parsec ID** (displayed at the top)

#### Step 3: Configure Host Settings
Recommended settings for game engine development:

**Video:**
- **Encoder**: Hardware (NVENC if available, otherwise Software)
- **Resolution**: Match your display or lower for better performance
- **FPS**: 60 FPS (or 30 for lower bandwidth)

**Hosting:**
- **Controller**: Enable if you want to use a gamepad remotely
- **Host on Startup**: Optional (enables hosting when Windows starts)

**Network:**
- **Bandwidth Limit**: Set based on your connection (or leave Auto)
- **Latency**: Enable "Low Latency Mode" for best experience

#### Step 4: Firewall Configuration
Parsec should automatically configure Windows Firewall, but if you have issues:

1. Open Windows Defender Firewall
2. Ensure Parsec is allowed through firewall
3. Or manually add rules for:
   - **UDP Port 8000-8010** (Parsec's default ports)
   - **TCP Port 8000-8010**

### 2. Running the Game Engine with Parsec

#### Option A: Run Game Engine First, Then Connect
1. Launch your game engine in WSL:
   ```powershell
   # Open WSL
   wsl
   
   # Navigate to project and run
   cd /mnt/c/Users/hulle/OneDrive/Desktop/mywork/game-engine/build
   ./game-engine
   ```

2. Ensure Parsec is running and hosting is enabled on Windows
3. Connect from your client device using your Parsec ID
4. Parsec will capture the WSLg window showing your game engine

#### Option B: Launch via Parsec Script (Recommended)
Use the provided `launch-with-parsec.ps1` script from PowerShell:
```powershell
.\launch-with-parsec.ps1
```

This script will:
- Check Parsec status
- Verify WSL and WSLg are available
- Launch the game engine in WSL automatically
- Provide tips for remote viewing

### 3. Client Device Setup

1. **Install Parsec** on your client device (Windows, Mac, Linux, Android, iOS)
2. **Sign in** with the same account or use guest mode
3. **Connect** using the host's Parsec ID
4. **Control**: Use keyboard/mouse or gamepad (if enabled)

## Optimizing for Game Engine Development

### Performance Tips

1. **Resolution**: Lower resolution can improve streaming quality and reduce latency
2. **Fullscreen**: Run game engine in windowed mode for better Parsec compatibility
3. **Frame Rate**: Cap game engine FPS to match Parsec streaming rate
4. **Bandwidth**: Use wired Ethernet connection for best results

### Game Engine Settings

The game engine runs in WSL via WSLg, which displays windows on Windows. Consider modifying the game engine window settings in `MainGame.cpp`:

```cpp
// Windowed mode recommended for Parsec
glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
```

### WSLg Considerations

- **WSLg**: Windows 11 includes WSLg which automatically displays Linux GUI applications
- **Window Capture**: Parsec running on Windows will automatically capture WSLg windows
- **Performance**: WSLg uses D3D12 translation, which works well with Parsec
- **No Additional Setup**: If you're on Windows 11, WSLg works automatically

### Network Optimization

- **Local Network**: For LAN access, ensure both devices are on the same network
- **Internet**: For remote access, ensure stable upload speed (5+ Mbps recommended)
- **Latency**: Use 5GHz WiFi or Ethernet for lower latency

## Troubleshooting

### Connection Issues

**Problem**: Cannot connect to host
- **Solution**: 
  - Verify Parsec is running and hosting is enabled
  - Check Windows Firewall settings
  - Ensure both devices have internet access
  - Try restarting Parsec

**Problem**: High latency
- **Solution**:
  - Use wired connection
  - Lower resolution in Parsec settings
  - Enable "Low Latency Mode"
  - Close bandwidth-intensive applications

**Problem**: Poor video quality
- **Solution**:
  - Increase bandwidth limit in Parsec settings
  - Use hardware encoding (NVENC)
  - Lower game engine resolution
  - Check network speed

### Game Engine Issues

**Problem**: Window not visible in Parsec
- **Solution**: 
  - Ensure game engine is running in WSL (check WSL terminal)
  - Verify WSLg is working (window should appear on Windows desktop)
  - Ensure game engine window is not minimized
  - Run in windowed mode (not fullscreen exclusive)
  - Alt+Tab to bring window to foreground
  - Check WSLg status: `wsl --status`

**Problem**: Input lag
- **Solution**:
  - Enable "Low Latency Mode" in Parsec
  - Use wired connection
  - Reduce game engine frame rate if needed

## Security Considerations

1. **Access Control**: Set a host access code in Parsec settings
2. **Guest Access**: Control who can connect (Friends, Anyone, or Password)
3. **Session Timeout**: Configure auto-disconnect for security
4. **Firewall**: Keep Windows Firewall enabled

## Advanced: Parsec SDK Integration (Optional)

For embedded streaming directly in the game engine, you can integrate Parsec SDK:

1. Download Parsec SDK from Parsec's developer portal
2. Add SDK headers and libraries to CMakeLists.txt
3. Implement frame capture and streaming in MainGame.cpp

See `PARSEC_SDK_INTEGRATION.md` for detailed SDK integration guide.

## Useful Parsec Commands

### Check Parsec Status (PowerShell)
```powershell
# Check if Parsec process is running
Get-Process -Name "parsecd" -ErrorAction SilentlyContinue
```

### Test Connection
```powershell
# Ping test (replace with your Parsec ID)
parsec host --status
```

## References

- [Parsec Official Documentation](https://support.parsec.app/)
- [Parsec Hosting Guide](https://support.parsec.app/host/getting-started-with-hosting)
- [Parsec SDK Documentation](https://docs.parsec.app/)

## Quick Start Checklist

- [ ] Parsec installed and running on Windows host
- [ ] Parsec account created and signed in
- [ ] Host mode enabled in Parsec settings
- [ ] Parsec ID noted for connection
- [ ] Firewall configured (usually automatic)
- [ ] Game engine built and ready to run
- [ ] Client device with Parsec installed
- [ ] Test connection successful

