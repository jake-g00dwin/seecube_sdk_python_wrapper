# Jetson py_seecube

## USB rules

If you haven't already you will want to make sure that you have accesss to the
actual usb device.

This will already be setup if you have used the original SeeCube SDK script
to install them `install_udev_rule.sh`


## Downloading the software from a release

Download the latest release from: [releases](https://github.com/jake-g00dwin/seecube_sdk_python_wrapper/releases).

If you want you can also download the repository inside your terminal using
the following commands.
```sh
# Downloads the vX.X.X zip to local directory
# Replace with newest release URL.
wget https://github.com/jake-g00dwin/seecube_sdk_python_wrapper/archive/refs/tags/vX.X.X.zip
```

Next you will need to extract the repository, you can do this using either your
preferred archiving tool such as Arc, 7zip or your operating systems default.

If you are already in your terminal the following command will work if you have
the `unzip` utility installed.

```sh
unzip ./X.X.X.zip

# Example output
Archive: ./X.X.X.zip
....
    creating: ...
    inflating: ...
    ...
```


## Installing needed build tools

The setup for the build tools needed is automated through the use of a shell
script inside the project's directory.

To run the `setup.sh` file you will need to first ensure it has permissions
to run by setting the execute bit.

After the execute bit/permissions are set you can proceed with running the 
script as shown below.

```sh
# Changing directory into the project directory.
cd ./seecube_sdk_python_wrapper-X.X.X

# Setting the execute permissions on the shell script.
sudo chmod +x ./setup.sh

# Execute the script using:
./setup.sh
```

**Example output:**
```sh
Setting up env
debian detected
checking the OS...
debian detected
Installing dependencies...
[sudo] password for user: 
```

**libusb:**

If your system seems to have trouble in the building step you can check to
make sure that `pkg-config` can find the correct usb library with the following
terminal commands.

The name of the package itself needed can change depending on the operating 
system, and it's package managers.

```sh
pkg-config --cflags --libs libusb-1.0
```


## Configuring for your hardware

In order to build for the correct hardware you need to know what camera you are
building for.

The current default linked library(SeeCube SDK) supports three different camera
serial numbers.

You may change the version targeted by editing the cmake configuration file
at `src/CMakeLists.txt` and comment/uncomment by placing or removing the `#`
symbol at the beginning of a line.

## Building the python module

To build the module the process is automated. You can use the shell script in 
the projects directory to build the project.

Use the commands below to follow a standard build.

```sh
# This pipes the menu selection into it automatically if you don't need the menu.
echo "2" | ./otto.sh


# Use this version if you would like to see the menu.
./otto.sh
```

This will have built the python bindings module into the `build/src/` directory
and should be available as a `.so` file.

## Using the python module

In order to run the example program you will want to place or execute your script
from the same directory as both the py_seecube file and the SeeCubed file(s).

You can copy all three files to their own directory using the `cp` or copy
command.

```sh
# Creates new directory in the downloads folder.
mkdir ~/Downloads/py_seecube_project

# Copy your version of the lib into the project dir.
# The `<>` indicates that section varies based on your system.
cp ./build/src/py_seecube.cpython-<PY_VER>-<CPU_ARCH>-linux-gnu.so ~/Downloads/py_seecube_project/

# Copy the original SeeCube Library files.
cp ./src/linux_arm/<SERIAL_NUMS>/libSeeCube.so ~/Downloads/py_seecube_project/

# Copy the example script.
cp ./src/example.py ~/Downloads/py_seecube_project/

```

**Running the Example:**

```sh
python3.10 ./example.py
```

