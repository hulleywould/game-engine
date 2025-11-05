@echo off
REM Batch script to launch game engine with Parsec compatibility checks
REM Usage: launch-with-parsec.bat

echo ========================================
echo Game Engine - Parsec Launch Helper
echo ========================================
echo.

REM Check if Parsec is running
echo Checking Parsec status...
tasklist /FI "IMAGENAME eq parsecd.exe" 2>NUL | find /I /N "parsecd.exe">NUL
if "%ERRORLEVEL%"=="0" (
    echo [OK] Parsec is running
) else (
    echo [WARNING] Parsec is not running
    echo Starting Parsec is recommended for remote access
)

echo.

REM Check if build directory exists
if not exist "build\game-engine" (
    echo [ERROR] Game engine executable not found!
    echo Path: %CD%\build\game-engine
    echo Please build the project in WSL first.
    pause
    exit /b 1
)

echo [OK] Game engine found
echo Path: %CD%\build\game-engine
echo.

REM Check WSL
echo Checking WSL...
wsl --status >nul 2>&1
if errorlevel 1 (
    echo [ERROR] WSL is not available
    echo Please install WSL2 first
    pause
    exit /b 1
)
echo [OK] WSL is available
echo.

REM Display Parsec connection info and try to get Parsec ID
echo Parsec Connection Info:
echo.

REM Try to extract Parsec ID using PowerShell helper script
powershell -ExecutionPolicy Bypass -File "%~dp0get-parsec-id.ps1"

echo   Parsec will capture the WSLg window showing your game engine
echo.

REM Launch game engine via WSL
echo Launching game engine in WSL...
echo.

REM Convert Windows path to WSL path
set WSL_PATH=%CD:C:=/mnt/c%
set WSL_PATH=%WSL_PATH:\=/%

wsl bash -c "cd '%WSL_PATH%/build' && ./game-engine"

echo [OK] Game engine launched!
echo.
echo Tips for Parsec:
echo   - Keep the game engine window visible (not minimized)
echo   - Windowed mode works better than fullscreen
echo   - Use Alt+Tab if window is not visible
echo.

pause

