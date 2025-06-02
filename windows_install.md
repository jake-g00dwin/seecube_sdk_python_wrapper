# Windows setup instructions

## Windows 11

### Inital Setup 

**PowerShell:**
1. Under `System->For developers` turn on powershell execution polisy for unsigned scripts.

**Package Manager:**
If your windows system doesn't already have the `winget` utility installed you
will need to install it following the instructions below.

1. go to [link](https://learn.microsoft.com/en-us/windows/msix/app-installer/install-update-app-installer)
2. Download and run the installer msi file. This will also install `winget`.
3. Test the command in shell with: `winget list` and accept with `Y` if needed.
4. Check that the command gave a list of packages as output.
5. You should now have a functional package manager ready to be used.

### Using setup Script

1. Download a zip of the most recent release: [repo](https://github.com/jake-g00dwin/seecube_sdk_python_wrapper)
2. Extract the archive/zip to your desired location.
3. Run PowerShell as admin.
4. Change directory to the extracted location: `cd C:\Users\<YourName>\Downloads\seecube_sdk_python_wrapper\seecube_sdk_python_wrapper-main`
5. Change execution policy: `Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass`
6. Enter `Y` to accept.
7. Run the setup script using: `.\setup.ps1`.
8. Wait for the entire script to finish running and installing software.
9. Exit powershell once script is finished.


