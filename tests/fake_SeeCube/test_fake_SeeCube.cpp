/*
 * Author: username
 * Date: todays_date 
 * filename: test_fake_SeeCube.c
 * description: module_purpose
 */


//The include for <map> causes issues, likely due to the memory leak detection
//that is part of the cpputest framework.
#include "fake_SeeCube.h"


#include "CppUTest/CommandLineTestRunner.h"

#include <iostream>

extern "C" 
{
    //#include "fake_SeeCube.h"
}

TEST_GROUP(test_fakeSeeCube)
{
    SeeCubeSDK sc_sdk;
    SeeCube device;
    void setup()
    {
        //Declareing an instance of the SeeCubeSDK class as sc_sdk
        SeeCubeSDK sc_sdk(SeeCubeSDK::verbosityLevel::info, 1);
        SeeCube device(0, "./data");
    }
    void teardown()
    {

    }
};


TEST(test_fakeSeeCube, SCSDK_GetsDeviceCount)
{
    set_FakeSeeCubeDeviceCount(0);
    CHECK_EQUAL(0, sc_sdk.getDeviceCount());

    set_FakeSeeCubeDeviceCount(1);
    CHECK_EQUAL(1, sc_sdk.getDeviceCount());
}



TEST(test_fakeSeeCube, SCSDK_GetDeviceNameWhenOneDevice)
{
    set_FakeSeeCubeDeviceCount(1);
    std::string expected_name = "device_name";
    std::string device_name = sc_sdk.getDeviceName();


    CHECK_TRUE(device_name.compare(expected_name) == 0);
}


TEST(test_fakeSeeCube, SCSDK_GetDeviceNameWhenNoDevice)
{
    set_FakeSeeCubeDeviceCount(0);
    std::string expected_name{"undefined"};
    std::string device_name = sc_sdk.getDeviceName();
   
    int result = expected_name.compare(device_name);

    CHECK_EQUAL(0, result);
}

TEST(test_fakeSeeCube, SCSDK_isConnectedReturnsFalseWhenFlagUnset)
{
    fakeSeeCube_setCameraConnectionState(false);
    CHECK_FALSE(sc_sdk.isConnected()); 
}


TEST(test_fakeSeeCube, SCSDK_isConnectedReturnsTrueWhenFlagSet)
{
    fakeSeeCube_setCameraConnectionState(true);
    CHECK_TRUE(sc_sdk.isConnected()); 
}

TEST(test_fakeSeeCube, SC_getPartNumberReturnsString)
{
    std::string part_number = device.getSerialNumber();
    CHECK_TRUE(part_number.length() != 0);
}

TEST(test_fakeSeeCube, SC_Stubbedgetsensorsettings)
{
    uint16_t a, b, c, d;
    device.getSensorSettings(a, b, c, d);
    CHECK_TRUE(true);
}

TEST(test_fakeSeeCube, SC_setFPSWorks)
{
    bool result = device.setDeviceFrameRate(30.0);
    CHECK_TRUE(result);
    CHECK_EQUAL(30.0, device.getDeviceFrameRate());
}

TEST(test_fakeSeeCube, SC_setInvalidFPSReturnsFalse)
{
    bool result = device.setDeviceFrameRate(fake_max_fps + 1);
    CHECK_FALSE(result);

    result = device.setDeviceFrameRate(fake_min_fps - 1);
    CHECK_FALSE(result);
}

TEST(test_fakeSeeCube, SC_getImageSizeReturnsTrue)
{
    fakeSeeCube_setImageSizeReturnValue(true);
    size_t width; 
    size_t height;
    bool result = device.getImageSize(width, height);
    CHECK_TRUE(result);
    CHECK_EQUAL(fake_width_default, width);
    CHECK_EQUAL(fake_height_default, height);
}

TEST(test_fakeSeeCube, SC_getImageSizeReturnsFalseWhenUnset)
{
    fakeSeeCube_setImageSizeReturnValue(false);
    size_t width; 
    size_t height;
    bool result = device.getImageSize(width, height);
    CHECK_FALSE(result);
    CHECK_EQUAL(fake_width_default, width);
    CHECK_EQUAL(fake_height_default, height);
}




