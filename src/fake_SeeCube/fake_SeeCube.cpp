/*
 * Author: Jake G 
 * Date: 2025 
 * filename: fake_SeeCube.c
 * description: For testing. 
 */

#include "fake_SeeCube.h"
#include <iostream>

/*
 *################################
 * SECTION
 *################################
 */



// dumb test function
int add_two(int a)
{
    int b = a;
    b += 2;
    return b;
}


int FakeSeeCube_DeviceCount;
std::string device_name = "";
bool is_connected = false;


void set_FakeSeeCubeDeviceCount(int count)
{
    FakeSeeCube_DeviceCount = count;
}


void fakeSeeCube_setCameraConnectionState( bool set_connected)
{
    is_connected = set_connected;
}


/*
 *################################
 * SeeCubeSDK 
 *################################
 */

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
    //std::cout << "Constructor Called!" << std::endl;
}


SeeCubeSDK::~SeeCubeSDK(void)
{
    //std::cout << "Destructor Called!" << std::endl;
}

int SeeCubeSDK::getDeviceCount()
{
    return FakeSeeCube_DeviceCount;
}


std::string SeeCubeSDK::getDeviceName(const int& pHandle)
{
    if(FakeSeeCube_DeviceCount == 0){
        device_name = "undefined"; 
    }
    else{
        device_name = "device_name";
    }
    return device_name;
}


bool SeeCubeSDK::isConnected(const int& pHandle)
{
    return is_connected;
}


void SeeCubeSDK::parseCoreParameter(const std::string& pParameter)
{
    //Do nothing for now.
}



/*
 *################################
 * SeeCube Class Definitions 
 *################################
 */

SeeCube::SeeCube(const int& pHandle,const std::string& mSensorDataPath)
{
   //Nothing.
}

std::string SeeCube::getPartNumber(void)
{
    std::string part_number{"XXXXXXXXXX"};
    return part_number;
}


