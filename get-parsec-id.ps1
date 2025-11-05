# PowerShell helper script to get Parsec ID
# Called by launch-with-parsec.bat

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
            $config = Get-Content $path -Raw -ErrorAction SilentlyContinue
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

# Output the result
if ($parsecId) {
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "YOUR PARSEC ID: $parsecId" -ForegroundColor Green -BackgroundColor Black
    Write-Host "========================================" -ForegroundColor Cyan
    Write-Host "Connect from another device using this ID" -ForegroundColor Gray
    Write-Host ""
} else {
    Write-Host "  Your Parsec ID can be found in Parsec settings" -ForegroundColor Gray
    Write-Host "  Open Parsec app -> Settings -> Host tab" -ForegroundColor Gray
    Write-Host "  Or run: .\check-parsec.ps1" -ForegroundColor Gray
}

