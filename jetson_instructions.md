# Jetson py_seecube


## Downloading the software from a release

Download the latest release from: [releases](https://github.com/jake-g00dwin/seecube_sdk_python_wrapper/releases).

If you want you can also download the repository inside your terminal using
the following commands.
```sh
# Downloads the v0.0.5 zip to local directory
# Replace with newest release URL.
wget https://github.com/jake-g00dwin/seecube_sdk_python_wrapper/archive/refs/tags/v0.0.5.zip
```

Next you will need to extract the repository, you can do this using either your
prefered archiving tool such as Arc, 7zip or your operating systems default.

If you are already in your terminal the following command will work if you have
the `unzip` utility installed.

```sh
unzip ./v0.0.5.zip

# Example output
Archive: ./v0.0.5.zip
....
    creating: ...
    inflating: ...
    ...
```


## Installing needed build tools

The setup for the build tools needed is automated through the use of a shell
script inside the project's directory.

To run the `setup.sh` file you will need to first ensure it has premissions
to run by setting the execute bit.

After the execute bit/permissions are set you can proceed with running the 
script as shown below.

```sh
# Chainging directory into the project directory.
cd ./seecube_sdk_python_wrapper-0.0.5

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

## Configuring for your hardware

In order to build for the correct hardware you need to know what camera you are
building for.

The current default linked library(SeeCube SDK) supports three differnt camera
serial numbers.

You may change the version targeted by editing the cmake configuration file
at `src/CMakeLists.txt` and comment/uncomment by placing or removing the `#`
symbol at the begining of a line.

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


## Using the python module
