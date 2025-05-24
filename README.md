# seecube_sdk_python_wrapper
A Python SDK wrapper/interface for the seecube sdk

## Description

The SDK in question uses a header file `*.h` with object oriented code and
making use of C++ keywords in the header file.

In order to make the library compatable for use with python's ctype module the
C++ needs to be wrapped with an C interface.

I admit to finding in somewhat strange that the SDK didn't opt to use C for at
least the external interface as it's pretty much the standard for offering 
interoperability between programming langauges.

A secondary option is the pybind11 library, which is meant for writting 
bindings for CPP but does introduce a external dependency.

## Requirements

- Python3.10
- pybind11, for C++ to python bindings.
- pytest, for unit testing.
- Cmake, for building the 


## Usage

During setup after copying or cloning the repo:

```sh
git submodule update --init --recursive

# To build and test/check pybind11
cd ./pybind11
mkdir ./build && cd ./build
cmake ..
make check -j 4



```



## RoadMap

- [ ] Establish version number/tag system.
- [ ] Create release & tag for current SDK version.
- [ ] Add automatic OS detection.
- [ ] Setup to load shared library(multiple platforms).
- [ ] Add pytest files.
- [ ] Add API documentation.
- [X] Setup project structure for C/C++ development.
- [X] Automate the building of C interface.
- [ ] Update doxygen configuration.
- [X] Add pybind11 as git sub-module.




