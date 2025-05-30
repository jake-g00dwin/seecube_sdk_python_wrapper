# Author: Jake G
# Date: 2025
# Filename: setup.ps1
# Description: Setup script to automate installation of dependencies.



# #############################
# Function Defs
# #############################

function Check-Requirements {
    # First check if the script is being ran under admin.
    if (-not ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole('Administrator')) {
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
    winget install --id $Package -e --source winget
}


# #############################
# Start of main script.  
# #############################

Check-Requirements
Show-Menu

Install-Package -PackageId "Git.Git" -DisplayName "Git"
Install-Package -PackageId "Python.Python3.10" -DisplayName "Python 3.10"
Install-Package -PackageId "Kitware.CMake" -DisplayName "CMake"
Install-Package -PackageId "LLVM.LLVM" -DislpayName "LLVM/Clang"

