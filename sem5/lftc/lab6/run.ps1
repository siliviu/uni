# Check if the filename is provided as an argument
if ($args.Count -ne 1) {
    Write-Host "Usage: ./script.ps1 <filename.asm>"
    exit 1
}

# Get the input filename
$inputFile = $args[0]

# Extract the base name without extension
$baseName = [System.IO.Path]::GetFileNameWithoutExtension($inputFile)

# Check if the file has the correct .asm extension
if (-not $inputFile.EndsWith(".asm")) {
    Write-Host "Error: Input file must have a .asm extension."
    exit 1
}

try {
    # Run nasm to assemble the file
    $nasmResult = & nasm -f obj $inputFile
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Error: nasm failed."
        exit 1
    }

    # Run alink to link the object file
    $alinkResult = & alink "$baseName.obj" -oPE -subsys console -entry start
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Error: alink failed."
        exit 1
    }

    # Rename the file to $baseName.exe
    Rename-Item -Path "$baseName" -NewName "$baseName.exe"
    if (-not $?) {
        Write-Host "Error: Failed to rename $baseName.obj to $baseName.exe."
        exit 1
    }

    # Execute the resulting .exe file in PowerShell
    & ".\$baseName.exe"
} catch {
    Write-Host $_
    Write-Host "Process failed. Cleaning up generated files..."
} finally {
    # Cleanup: Delete all generated files
    if (Test-Path "$baseName.obj") {
        Remove-Item "$baseName.obj" -Force
    }
    if (Test-Path "$baseName.exe") {
        Remove-Item "$baseName.exe" -Force
    }
    if (Test-Path "$baseName") {
        Remove-Item "$baseName" -Force
    }
}