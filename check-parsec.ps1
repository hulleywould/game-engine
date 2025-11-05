# PowerShell script to check Parsec configuration and status
# Usage: .\check-parsec.ps1
# Note: Game engine runs in WSL, Parsec runs on Windows

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Parsec Configuration Checker" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Check if Parsec is installed
Write-Host "1. Checking Parsec Installation..." -ForegroundColor Yellow
$parsecProcess = Get-Process -Name "parsecd" -ErrorAction SilentlyContinue
$parsecInstalled = Test-Path "$env:LOCALAPPDATA\Parsec"

if ($parsecInstalled) {
    Write-Host "   [OK] Parsec is installed" -ForegroundColor Green
} else {
    Write-Host "   [ERROR] Parsec installation not found" -ForegroundColor Red
    Write-Host "     Install from: https://parsec.app/" -ForegroundColor Gray
}

if ($parsecProcess) {
    Write-Host "   [OK] Parsec daemon is running (PID: $($parsecProcess.Id))" -ForegroundColor Green
} else {
    Write-Host "   [WARNING] Parsec daemon is not running" -ForegroundColor Yellow
    Write-Host "     Start Parsec application to enable hosting" -ForegroundColor Gray
}

Write-Host ""

# Check WSL status
Write-Host "2. Checking WSL Status..." -ForegroundColor Yellow
try {
    $wslStatus = wsl --status 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host "   [OK] WSL is available" -ForegroundColor Green
        
        # Try to get WSL version info
        $wslVersion = wsl --version 2>&1
        if ($wslVersion -match "WSLg") {
            Write-Host "   [OK] WSLg detected (GUI support available)" -ForegroundColor Green
            Write-Host "     Parsec can capture WSLg windows" -ForegroundColor Gray
        } else {
            Write-Host "   [WARNING] WSLg not detected" -ForegroundColor Yellow
            Write-Host "     You may need VcXsrv for GUI support on Windows 10" -ForegroundColor Gray
        }
        
        # Check if WSL is running
        $wslList = wsl --list --verbose 2>&1
        if ($wslList -match "Running") {
            Write-Host "   [OK] WSL distribution is running" -ForegroundColor Green
        } else {
            Write-Host "   [WARNING] WSL distribution may not be running" -ForegroundColor Yellow
        }
    } else {
        Write-Host "   [ERROR] WSL is not available" -ForegroundColor Red
        Write-Host "     Install WSL2 to run the game engine" -ForegroundColor Gray
    }
} catch {
    Write-Host "   [WARNING] Could not check WSL status" -ForegroundColor Yellow
    Write-Host "     Error: $_" -ForegroundColor Gray
}

Write-Host ""

# Check Windows Firewall
Write-Host "3. Checking Windows Firewall..." -ForegroundColor Yellow
try {
    $firewallProfile = Get-NetFirewallProfile -Profile Domain,Public,Private
    $firewallEnabled = ($firewallProfile | Where-Object { $_.Enabled -eq $true }).Count -gt 0

    if ($firewallEnabled) {
        Write-Host "   [OK] Windows Firewall is enabled" -ForegroundColor Green
        
        # Check Parsec firewall rules
        $parsecRules = Get-NetFirewallRule -DisplayName "*Parsec*" -ErrorAction SilentlyContinue
        if ($parsecRules) {
            Write-Host "   [OK] Parsec firewall rules found" -ForegroundColor Green
            foreach ($rule in $parsecRules) {
                Write-Host "     - $($rule.DisplayName): $($rule.Enabled)" -ForegroundColor Gray
            }
        } else {
            Write-Host "   [WARNING] No Parsec firewall rules found (may need manual configuration)" -ForegroundColor Yellow
        }
    } else {
        Write-Host "   [WARNING] Windows Firewall is disabled" -ForegroundColor Yellow
    }
} catch {
    Write-Host "   [WARNING] Could not check firewall status" -ForegroundColor Yellow
}

Write-Host ""

# Check network connectivity
Write-Host "4. Checking Network Connectivity..." -ForegroundColor Yellow
try {
    $ping = Test-Connection -ComputerName "8.8.8.8" -Count 2 -Quiet
    if ($ping) {
        Write-Host "   [OK] Internet connectivity OK" -ForegroundColor Green
    } else {
        Write-Host "   [WARNING] Internet connectivity issues detected" -ForegroundColor Yellow
    }
} catch {
    Write-Host "   [WARNING] Could not test internet connectivity" -ForegroundColor Yellow
}

# Check local network
Write-Host "   Checking local network..." -ForegroundColor Gray
try {
    $localIP = (Get-NetIPAddress -AddressFamily IPv4 | Where-Object { $_.IPAddress -like "192.168.*" -or $_.IPAddress -like "10.*" -or $_.IPAddress -like "172.*" }).IPAddress | Select-Object -First 1
    if ($localIP) {
        Write-Host "   [OK] Local IP: $localIP" -ForegroundColor Green
    } else {
        Write-Host "   [WARNING] Could not detect local IP" -ForegroundColor Yellow
    }
} catch {
    Write-Host "   [WARNING] Could not check local network" -ForegroundColor Yellow
}

Write-Host ""

# Check Parsec configuration file location and extract Parsec ID
Write-Host "5. Checking Parsec Configuration..." -ForegroundColor Yellow
$parsecId = $null

# Try multiple possible config file locations
$configPaths = @(
    "$env:LOCALAPPDATA\Parsec\config.txt",
    "$env:APPDATA\Parsec\config.txt",
    "$env:LOCALAPPDATA\Parsec\parsecd.conf",
    "$env:APPDATA\Parsec\parsecd.conf"
)

$parsecConfigPath = $null
foreach ($path in $configPaths) {
    if (Test-Path $path) {
        $parsecConfigPath = $path
        break
    }
}

if ($parsecConfigPath) {
    Write-Host "   [OK] Parsec config file found" -ForegroundColor Green
    Write-Host "     Path: $parsecConfigPath" -ForegroundColor Gray
    
    # Try to read config and extract Parsec ID
    try {
        $config = Get-Content $parsecConfigPath -ErrorAction SilentlyContinue -Raw
        if ($config) {
            # Try various possible ID formats
            if ($config -match 'host_id\s*=\s*"([^"]+)"') {
                $parsecId = $matches[1].Trim()
            } elseif ($config -match 'host_id\s*=\s*(\S+)') {
                $parsecId = $matches[1].Trim()
            } elseif ($config -match 'parsec_id\s*=\s*"([^"]+)"') {
                $parsecId = $matches[1].Trim()
            } elseif ($config -match 'parsec_id\s*=\s*(\S+)') {
                $parsecId = $matches[1].Trim()
            } elseif ($config -match 'user_id\s*=\s*"([^"]+)"') {
                $parsecId = $matches[1].Trim()
            } elseif ($config -match 'user_id\s*=\s*(\S+)') {
                $parsecId = $matches[1].Trim()
            } elseif ($config -match '"id"\s*:\s*"([^"]+)"') {
                $parsecId = $matches[1].Trim()
            }
            
            if ($config -match "host_enabled") {
                Write-Host "     Host configuration found" -ForegroundColor Gray
            }
        }
    } catch {
        # Ignore read errors
    }
} else {
    Write-Host "   [WARNING] Parsec config file not found" -ForegroundColor Yellow
    Write-Host "     Run Parsec once to generate configuration" -ForegroundColor Gray
}

# Try to get Parsec ID from command line if config file didn't work
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

# Display Parsec ID if found
if ($parsecId) {
    Write-Host "" -ForegroundColor Green
    Write-Host "   ========================================" -ForegroundColor Cyan
    Write-Host "   YOUR PARSEC ID: $parsecId" -ForegroundColor Green -BackgroundColor Black
    Write-Host "   ========================================" -ForegroundColor Cyan
    Write-Host "   Use this ID to connect from another device" -ForegroundColor Gray
} else {
    Write-Host "   [INFO] Parsec ID not found in config" -ForegroundColor Yellow
    Write-Host "     Open Parsec app -> Settings -> Host tab to see your ID" -ForegroundColor Gray
}

Write-Host ""

# Check ports (Parsec typically uses 8000-8010)
Write-Host "6. Checking Parsec Ports..." -ForegroundColor Yellow
$ports = @(8000, 8001, 8002, 8003, 8004, 8005, 8006, 8007, 8008, 8009, 8010)
$openPorts = @()

foreach ($port in $ports) {
    try {
        $connection = Get-NetTCPConnection -LocalPort $port -ErrorAction SilentlyContinue
        if ($connection) {
            $openPorts += $port
        }
    } catch {
        # Ignore errors
    }
}

if ($openPorts.Count -gt 0) {
    Write-Host "   [OK] Parsec ports in use: $($openPorts -join ', ')" -ForegroundColor Green
} else {
    Write-Host "   [WARNING] No Parsec ports detected (Parsec may not be hosting)" -ForegroundColor Yellow
}

Write-Host ""

# Summary and recommendations
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Summary and Recommendations" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

if ($parsecProcess -and $parsecInstalled) {
    Write-Host "[OK] Parsec appears to be properly configured" -ForegroundColor Green
    Write-Host ""
    Write-Host "Next steps:" -ForegroundColor Cyan
    Write-Host "  1. Open Parsec application" -ForegroundColor Gray
    Write-Host "  2. Go to Settings -> Host tab" -ForegroundColor Gray
    Write-Host "  3. Enable Host toggle" -ForegroundColor Gray
    Write-Host "  4. Note your Parsec ID" -ForegroundColor Gray
    Write-Host "  5. Connect from another device using your Parsec ID" -ForegroundColor Gray
    Write-Host "  6. Launch game engine in WSL (use launch-with-parsec.ps1)" -ForegroundColor Gray
    Write-Host "  7. Parsec will capture the WSLg window automatically" -ForegroundColor Gray
} else {
    Write-Host "[WARNING] Parsec needs to be set up" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Actions needed:" -ForegroundColor Cyan
    if (-not $parsecInstalled) {
        Write-Host "  - Install Parsec from https://parsec.app/" -ForegroundColor Gray
    }
    if (-not $parsecProcess) {
        Write-Host "  - Launch Parsec application" -ForegroundColor Gray
        Write-Host "  - Sign in or create account" -ForegroundColor Gray
        Write-Host "  - Enable Host mode in Settings" -ForegroundColor Gray
    }
}

Write-Host ""
Write-Host "Note: Game engine runs in WSL, Parsec runs on Windows" -ForegroundColor Cyan
Write-Host "      Parsec captures the WSLg window showing your game engine" -ForegroundColor Gray
Write-Host ""
Write-Host "For detailed setup instructions, see PARSEC_SETUP.md" -ForegroundColor Cyan
