cmake_minimum_required(VERSION 3.20)

# Use the fancy version substitution
project(py_seecube
    VERSION 0.0.4
    DESCRIPTION "A python wrapper for the SeeCube SDK"
    LANGUAGES   C CXX
)
enable_testing()

set(TARGET_GROUP production CACHE STRING "Group to build")

message(${CMAKE_SYSTEM_NAME})

# Set defines and variable based on the OS and CPU.
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message("Configuring for Linux")
    add_definitions(-DLINUX)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message("Configuring for Windows")
    add_definitions(-DWINDOWS)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    message("Configuring for FreeBSD")
    add_definitions(-DBSD)
endif()

# For being able to used LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C 17 standard features
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")

# SETUP THE CXX flags for .cpp
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")

# #######################################
# TESTING STUFF 
# #######################################

if (UNIT_TESTING)

    if(DEFINED ENV{CPPUTEST_HOME})
        message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
        set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
        set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
        set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
    else()
        find_package(PkgConfig REQUIRED)
        pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
        message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
    endif()
    
    include_directories(
        ${CPPUTEST_INCLUDE_DIRS}
        ./inc
        ./mocks
        )
    link_directories(${CPPUTEST_LIBRARIES})
    
    add_subdirectory(mocks)
    add_subdirectory(tests)

endif()


# #######################################
# PROJECT SPECIFIC 
# #######################################

# Pybind11 submodule needs to be included.
set(PYBIND11_PYTHON_VERSION 3.10)


# Include all external
add_subdirectory(extern)

include_directories(
    ./inc
)
add_subdirectory(src)
