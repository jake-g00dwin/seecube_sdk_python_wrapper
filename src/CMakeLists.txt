
pybind11_add_module(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME}
PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

# Variable to hold the name of the targed shared library to be linked with.
set(SHARED_SDK "")


# Determine the correct shared library to link
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    # If the system is a linux based system then it coulb be x86 or arm
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
        set(MY_SHARED_LIB "linux_x86/libSeeCube.so")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
        set(MY_SHARED_LIB "linux_arm/libSeeCube.so")
    endif()
# For windows based systems, there is only one sdk.
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(MY_SHARED_LIB "windows/SeeCube.lib")
endif()

# Link with the correct shared library from the SDK.
target_link_libraries(${PROJECT_NAME} PRIVATE ${SHARED_SDK})
