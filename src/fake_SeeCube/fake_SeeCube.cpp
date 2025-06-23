/*
 * Author: Jake G 
 * Date: 2025 
 * filename: fake_SeeCube.c
 * description: For testing. 
 */

#include "fake_SeeCube.h"
#include <iostream>

// dumb test function
int add_two(int a)
{
    int b = a;
    b += 2;
    return b;
}


int FakeSeeCube_DeviceCount = 0;


void set_FakeSeeCubeDeviceCount(int count)
{
    FakeSeeCube_DeviceCount = count;
}

/**
* @brief Constructor for the SeeCubeSDK class.
*
* Creates a SeeCubeSDK instance and enumerates connected devices, setting up the SDK environment
* with specified verbosity level and thread pool size.
*
* @param[in] pVerbosity The verbosity level for logging. Determines the amount of information logged.
*                       Default value is verbosityLevel::error.
* @param[in] pThreadPoolSize The size of the thread pool to be used by the SDK.
*                            A value of 0 lets the SDK determine the optimal size.
*                            Default is 0.
*/
SeeCubeSDK::SeeCubeSDK(const verbosityLevel& pVerbosity,
           const int& pThreadPoolSize)
{
    std::cout << "Constructor Called!" << std::endl;
}


SeeCubeSDK::~SeeCubeSDK(void)
{
    std::cout << "Destructor Called!" << std::endl;
}

int SeeCubeSDK::getDeviceCount()
{
    return FakeSeeCube_DeviceCount;
}


