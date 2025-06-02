# Author: Jake G
# Date: 2025
# Filename: setup.ps1
# Description: Setup script to automate installation of dependencies.



# #############################
# Function Defs
# #############################

function Check-Requirements {
    # First check if the script is being ran under admin.
    if (-not ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
        Write-Warning "You need to run this script as Administrator."
        exit 1
    }

    # Check if the tools/utilites needed are availble.
    if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
        Write-Error "winget is not installed. Install Windows Package Manager first."
        exit 1
    }
}

function Show-Menu {
    Write-Host "`nSeeCube SDK - python bindings enviroment setup:"
    Write-Host "Installs: Git, CMake, Python3.x, OpenCV"
    Write-Host "1. Continue Installation"
    Write-Host "2. Exit"

    $choice = Read-Host "Enter choice(1,2):"
    if($choice -ne '1') {
        Write-Host "Exiting..."
        exit 0
    }
}


#Program Install Helper function.
function Install-Package {
    param (
        [string]$PackageId,
        [string]$DisplayName
    )

    Write-Host "`nInstalling $DisplayName"
    winget install --id $PackageId -e --source winget
}


# Install python packages using pip.
function Install-PipPackage {
    param (
        [Parameter(Mandatory=$true)]
        [string]$Package
    )

    $pip = Get-Command pip -ErrorAction SilentlyContinue

    if (-not $pip) {
        Write-Warning "pip not found in PATH. Trying python -m pip..."
        $python = Get-Command python -ErrorAction SilentlyContinue
        if ($python) {
            $pipCmd = "$($python.Source) -m pip"
        } else {
            Write-Error "Python is not installed or not found in PATH."
            return
        }
    } else {
        $pipCmd = $pip.Source
    }

    Write-Host "Installing pip package: $pkg"
    & $pipCmd install $pkg
}


# #############################
# Start of main script.  
# #############################

Check-Requirements
Show-Menu

Install-Package -PackageId "Git.Git" -DisplayName "Git"
Install-Package -PackageId "Python.Python.3.10" -DisplayName "Python 3.10"
Install-Package -PackageId "Kitware.CMake" -DisplayName "CMake"
Install-Package -PackageId "LLVM.LLVM" -DislpayName "LLVM/Clang"

# We need to do this so that we can find the new installed programs.
# Refresh PATH from the registry (User and System)
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" +
            [System.Environment]::GetEnvironmentVariable("Path", "User")

# Now install python packages needed using pip.
Install-PipPackage -Package "pytest"
Install-PipPackage -Package "opencv-python"

