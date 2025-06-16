# seecube_sdk_python_wrapper
A Python SDK wrapper/interface for the seecube sdk

## Description

This repo is setup to automate the process of building the needed python module
to interface with the SeeCubeSDK library.


## Requirements

- Python3.10
- pybind11, for C++ to python bindings.
- pytest, for unit testing.
- Cmake, for building the library.
- OpenCV

For new installs it's reccommended to run the setup script file for your 
system.

The setup scripts will automate the process of installing the dependencies
needed for both building and testing the system.

**Unix(BASH):**
```sh
#Set script as executable.
chmod +x ./setup.sh

#Run script to install dependencies.
./setup.sh
```

**Windows(PowerShell):**

To run the script you can execute it from an admin powershell instance or you
may right click the power shell script install and run it as admin.

If you system isn't setup already to run unsigned powershell scripts you can
follow the instructions in the `windows_install.md` file located in the repos
root directory.

```
./setup.ps1
```

## Python Usage

To load the module/library from python first navigate to the directory where
the module is located then import it.

If you're running on windows you'll want to first copy the library files from
the `src/windows/` sub-directory into the same location that the new library
files are located.

```sh
python3.10
>>>import py_seecube
>>>sc_sdk = py_seecube.SeeCubeSDK(py_seecube.SeeCubeSDK.verbosityLevel.info, 1)
```

As you can see from the example above it functions as a normal python module, 
but you may want to cut down it's length a bit using something like
`import py_seecube as psc` for instance.

## Building (Windows)

1. Open VisualStudio Development terminal(powershell).
2. Navigate to the project root directory.
3. Follow the commands below.

```sh
mkdir ./build
cd ./build
# One of the below commands depending on versions.
cmake ..; msbuild py_seecube
cmake ..; msbuild ALL_BUILD.vcxproj
```
Once the build process is finished the library/python module will be in the
`build/src/Debug/` sub-directory.


## Building (Linux/Unix) 

**Setting execution for scripts:**
```sh
sudo chmod +x ./otto.sh
sudo chmod +x ./setup.sh

```

During setup after copying or cloning the repo:

```sh
git submodule update --init --recursive

# To build and test/check pybind11
cd ./pybind11
mkdir ./build && cd ./build
cmake ..
make check -j 4

```

**Running cpputests(unix):**
```sh
echo 1 | ./otto.sh
```
After running the above line in terminal the output should be inside the
`./build/src/` sub-directory as an shared library file.


**Building shared library(unix):**
```sh
echo 2 | ./otto.sh
```


## Testing

In order to ensure the integrity of the bindings and their correctness the
bindings need to be tested.

Testing of the build system and it's automation for the detection of it's host 
system is also needed ideally.




## RoadMap

- [X] Establish version number/tag system.
- [ ] Create release & tag for current SDK version.
- [X] Add automatic OS detection.
- [X] Setup to load shared library(multiple platforms).
- [ ] Add pytest files.
- [ ] Add API documentation.
- [X] Setup project structure for C/C++ development.
- [X] Automate the building of C interface.
- [X] Update doxygen configuration.
- [X] Add pybind11 as git sub-module.
- [ ] setup pytesting via script.

