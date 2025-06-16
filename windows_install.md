# Windows setup instructions

## Windows 11

### Initial Setup 

**PowerShell:**
1. Under `System->For developers` turn on power shell execution policy for unsigned scripts.

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
3. Run power shell as admin.
4. Change directory to the extracted location: `cd C:\Users\<YourName>\Downloads\seecube_sdk_python_wrapper\seecube_sdk_python_wrapper-main`
5. Change execution policy: `Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass`
6. Enter `Y` to accept.
7. Run the setup script using: `.\setup.ps1`.
8. Wait for the entire script to finish running and installing software.
9. Exit power shell once script is finished.
10. From the start menu open the Visual Studio Installer.
11. Click the modify button for visual studio community.
12. Select `Desktop Development with C++` under workloads.
13. Click modify to install all required components. 


## Troubleshooting

If you have followed all the instructions above and are still running into
issues it is often related to environmental variables and their changes 
not being propagated across your system.

If you get an error when trying to run the `winget.exe` command in power shell 
this indicates it's either not installed or that your `Path` variable doesn't
include the correct directories.

**Checking For WinGet:**

1. Open a power shell window.
2. navigate to `C:\Program Files\WindowsApps\`
3. check for a directory in this format: `Microsoft.DesktopAppInstaller_*`
4. If that directory contains the `winget.exe` file copy the path.

**Enviroment Variable Append(GUI):**

1. Open the Start menu.
2. Open Windows Settings
3. Click the System Options in the left pane.
4. Navigate to About --> Advanced system settings.
5. Click the "Advanced" tab.
6. Click the "Environment Variables" button.
7. In the lower pane scroll until you see the "Path" variable.
8. Select the path variable and click "Edit".
9. Add a new line to the Path with the location you found previously.


**Enviroment Variable Append:**

Sometimes the path won't be updated/correct when you run admin power shell and
you will need to manually update the environmental variable manually using
the command below.

```sh
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" +
            [System.Environment]::GetEnvironmentVariable("Path", "User")
```

To check that the path was added you can use the following command to print
out the path separated by a newline for each delimiting token.

```sh
$env:PATH -split ';'
```


