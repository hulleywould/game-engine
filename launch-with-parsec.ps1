# PowerShell script to launch game engine with Parsec compatibility checks
# Usage: .\launch-with-parsec.ps1
# Note: Game engine runs in WSL, Parsec runs on Windows to capture WSLg window

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Game Engine - Parsec Launch Helper (WSL)" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Check if Parsec is running
Write-Host "Checking Parsec status..." -ForegroundColor Yellow
$parsecProcess = Get-Process -Name "parsecd" -ErrorAction SilentlyContinue

if ($parsecProcess) {
    Write-Host "[OK] Parsec is running" -ForegroundColor Green
    Write-Host "  Process ID: $($parsecProcess.Id)" -ForegroundColor Gray
} else {
    Write-Host "[WARNING] Parsec is not running" -ForegroundColor Yellow
    Write-Host "  Starting Parsec is recommended for remote access" -ForegroundColor Gray
    $startParsec = Read-Host "Would you like to start Parsec? (Y/N)"
    if ($startParsec -eq "Y" -or $startParsec -eq "y") {
        try {
            Start-Process "parsecd" -ErrorAction Stop
            Write-Host "[OK] Parsec started" -ForegroundColor Green
            Start-Sleep -Seconds 2
        } catch {
            Write-Host "[ERROR] Could not start Parsec. Please start it manually." -ForegroundColor Red
        }
    }
}

Write-Host ""

# Check WSL status
Write-Host "Checking WSL status..." -ForegroundColor Yellow
try {
    $wslStatus = wsl --status 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host "[OK] WSL is available" -ForegroundColor Green
        
        # Check if WSLg is available (Windows 11)
        $wslVersion = wsl --version 2>&1
        if ($wslVersion -match "WSLg") {
            Write-Host "[OK] WSLg detected (GUI support available)" -ForegroundColor Green
        } else {
            Write-Host "[WARNING] WSLg not detected (Windows 10 or older WSL version)" -ForegroundColor Yellow
            Write-Host "  You may need VcXsrv for GUI support" -ForegroundColor Gray
        }
    } else {
        Write-Host "[ERROR] WSL is not available" -ForegroundColor Red
        Write-Host "  Please install WSL2 first" -ForegroundColor Yellow
        exit 1
    }
} catch {
    Write-Host "[ERROR] Could not check WSL status" -ForegroundColor Red
    exit 1
}

Write-Host ""

# Check if build directory exists (Windows path)
$buildPath = Join-Path $PSScriptRoot "build"
$gameEngineExe = Join-Path $buildPath "game-engine"

# Convert Windows path to WSL path
$wslPath = $PSScriptRoot -replace "C:", "/mnt/c" -replace "\\", "/"
$wslBuildPath = "$wslPath/build"
$wslGameEngine = "$wslBuildPath/game-engine"

if (-not (Test-Path $buildPath)) {
    Write-Host "[ERROR] Build directory not found!" -ForegroundColor Red
    Write-Host "  Path: $buildPath" -ForegroundColor Gray
    Write-Host "  Please run build.sh in WSL first." -ForegroundColor Yellow
    exit 1
}

if (-not (Test-Path $gameEngineExe)) {
    Write-Host "[ERROR] Game engine executable not found!" -ForegroundColor Red
    Write-Host "  Path: $gameEngineExe" -ForegroundColor Gray
    Write-Host "  Please build the project in WSL first:" -ForegroundColor Yellow
    Write-Host "    wsl bash -c 'cd $wslPath && ./build.sh'" -ForegroundColor Gray
    exit 1
}

Write-Host "[OK] Game engine found" -ForegroundColor Green
Write-Host "  Windows path: $gameEngineExe" -ForegroundColor Gray
Write-Host "  WSL path: $wslGameEngine" -ForegroundColor Gray
Write-Host ""

# Display Parsec connection info and try to get Parsec ID
Write-Host "Parsec Connection Info:" -ForegroundColor Cyan
$parsecId = $null

# Try multiple possible config file locations
$configPaths = @(
    "$env:LOCALAPPDATA\Parsec\config.txt",
    "$env:APPDATA\Parsec\config.txt",
    "$env:LOCALAPPDATA\Parsec\parsecd.conf",
    "$env:APPDATA\Parsec\parsecd.conf"
)

foreach ($path in $configPaths) {
    if (Test-Path $path) {
        try {
            $config = Get-Content $path -ErrorAction SilentlyContinue -Raw
            if ($config) {
                # Try various possible ID formats
                if ($config -match 'host_id\s*=\s*"([^"]+)"') {
                    $parsecId = $matches[1].Trim()
                    break
                } elseif ($config -match 'host_id\s*=\s*(\S+)') {
                    $parsecId = $matches[1].Trim()
                    break
                } elseif ($config -match 'parsec_id\s*=\s*"([^"]+)"') {
                    $parsecId = $matches[1].Trim()
                    break
                } elseif ($config -match 'parsec_id\s*=\s*(\S+)') {
                    $parsecId = $matches[1].Trim()
                    break
                } elseif ($config -match 'user_id\s*=\s*"([^"]+)"') {
                    $parsecId = $matches[1].Trim()
                    break
                } elseif ($config -match 'user_id\s*=\s*(\S+)') {
                    $parsecId = $matches[1].Trim()
                    break
                } elseif ($config -match '"id"\s*:\s*"([^"]+)"') {
                    $parsecId = $matches[1].Trim()
                    break
                }
            }
        } catch {
            # Ignore errors
        }
    }
}

# Try command line method if config file didn't work
if (-not $parsecId) {
    try {
        $parsecExe = "C:\Program Files\Parsec\parsecd.exe"
        if (Test-Path $parsecExe) {
            $cmdOutput = & $parsecExe --config 2>&1 | Out-String
            if ($cmdOutput -match 'host_id[:\s]+([A-Za-z0-9]+)') {
                $parsecId = $matches[1].Trim()
            } elseif ($cmdOutput -match 'id[:\s]+([A-Za-z0-9]+)') {
                $parsecId = $matches[1].Trim()
            }
        }
    } catch {
        # Ignore errors
    }
}

# Display Parsec ID prominently if found
if ($parsecId) {
    Write-Host "" -ForegroundColor Cyan
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "YOUR PARSEC ID: $parsecId" -ForegroundColor Green -BackgroundColor Black
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Connect from another device using this ID" -ForegroundColor Gray
    Write-Host "" -ForegroundColor Cyan
} else {
    Write-Host "  Your Parsec ID can be found in Parsec settings" -ForegroundColor Gray
    Write-Host "  Open Parsec app -> Settings -> Host tab" -ForegroundColor Gray
    Write-Host "  Or run: .\check-parsec.ps1" -ForegroundColor Gray
}
Write-Host "  Parsec will capture the WSLg window showing your game engine" -ForegroundColor Gray
Write-Host ""

# Check network connectivity
Write-Host "Checking network connectivity..." -ForegroundColor Yellow
$networkOk = Test-NetConnection -ComputerName "www.google.com" -Port 80 -InformationLevel Quiet -WarningAction SilentlyContinue
if ($networkOk) {
    Write-Host "[OK] Internet connection available" -ForegroundColor Green
} else {
    Write-Host "[WARNING] Internet connection check failed (may still work on local network)" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Launching game engine in WSL..." -ForegroundColor Cyan
Write-Host ""

# Launch game engine via WSL
# Using bash -c to ensure proper path handling
$wslCommand = "cd '$wslBuildPath' && ./game-engine"
wsl bash -c $wslCommand

Write-Host ""
Write-Host "[OK] Game engine launched in WSL!" -ForegroundColor Green
Write-Host ""
Write-Host "Tips for Parsec with WSL:" -ForegroundColor Cyan
Write-Host "  - The game engine window should appear via WSLg" -ForegroundColor Gray
Write-Host "  - Parsec will capture this window automatically" -ForegroundColor Gray
Write-Host "  - Keep the game engine window visible (not minimized)" -ForegroundColor Gray
Write-Host "  - Windowed mode works better than fullscreen" -ForegroundColor Gray
Write-Host "  - Use Alt+Tab if window is not visible" -ForegroundColor Gray
Write-Host ""
