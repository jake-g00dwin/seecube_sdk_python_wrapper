cmake_minimum_required(VERSION 3.20)

# Use the fancy version substitution
project(SeeCubeSDK_PyWrapper
    VERSION 0.1.0
    DESCRIPTION "A python wrapper for the SeeCube SDK"
    LANGUAGES   C CXX
)
enable_testing()

set(TARGET_GROUP production CACHE STRING "Group to build")

if(MSVC OR MSYS OR MINGW)
    message("### SETUP FOR WINDOWS ###")
    add_definitions(-DWINDOWS)
else()
    message("### SETUP FOR UNIX ###")
    add_definitions(-DUNIX)
endif()

# For being able to used LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


