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

    size_t num_elements = fake_width_default * fake_height_default;
    uint16_t *raw_img;
    
    void setup()
    {
        //Declareing an instance of the SeeCubeSDK class as sc_sdk
        SeeCubeSDK sc_sdk(SeeCubeSDK::verbosityLevel::info, 1);
        SeeCube device(0, "./data");
        raw_img = new uint16_t[num_elements];
    }
    void teardown()
    {
        delete [] raw_img;
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

TEST(test_fakeSeeCube, SC_getRawImageSucessOnSetTrue)
{
    fakeSeeCube_setRawImageReturnBool(true); 
    
    //Initialize the memory to be all the same value. 
    for(unsigned int i = 0; i < num_elements; i++){
        raw_img[i] = 128;
    }

    //Expect that the fake camera sets all of them to zero.
    bool result = device.getRawFrame((uint8_t*)raw_img);

    CHECK_TRUE(result);

    for(unsigned int i = 0; i < num_elements; i++){
        CHECK_EQUAL(0, raw_img[i]);
    }
}

TEST(test_fakeSeeCube, SC_SetPixelCorrectionTogglesCorrectly)
{
    bool is_pixelcorrection = true;
    device.setDefectivePixelsCorrection(is_pixelcorrection);

    //Confirm it's set using our spy
    CHECK_TRUE(spy_is_pixelcorrection());
}

TEST(test_fakeSeeCube, SC_CheckPixelCorrectionEnabledFailsOnUnset)
{
    bool is_pixelcorrection = false;
    device.setDefectivePixelsCorrection(is_pixelcorrection);
    bool is_enabled = device.getDefectivePixelsCorrection();
    CHECK_FALSE(is_enabled);
}

TEST(test_fakeSeeCube, SC_CheckPixelCorrectionEnabledStatus)
{
    bool is_pixelcorrection = true;
    device.setDefectivePixelsCorrection(is_pixelcorrection);

    bool is_enabled = device.getDefectivePixelsCorrection();
    CHECK_TRUE(is_enabled);
}

TEST(test_fakeSeeCube, SC_CheckPixelCorrectionAcceptsOverload)
{
    std::vector<std::pair<int, int>> pixel_list;
    bool is_enabled = device.getDefectivePixelsCorrection(pixel_list);
    CHECK_TRUE(is_enabled);
}

TEST(test_fakeSeeCube, SC_CheckPixelCorrectionChangesRefernce)
{
    bool is_pixelcorrection = true;
    device.setDefectivePixelsCorrection(is_pixelcorrection);

    std::vector<std::pair<int, int>> pixel_list;
    bool is_enabled = device.getDefectivePixelsCorrection(pixel_list);
    CHECK_TRUE(is_enabled);

    //Check the zeroth elements, less processing intensive.
    CHECK_EQUAL(255, pixel_list[0].first);
    CHECK_EQUAL(255, pixel_list[0].second);
}


TEST(test_fakeSeeCube, SC_CheckPixelCorrectionOverloadReturnsFalseOnUnset)
{
    bool is_pixelcorrection = false;
    device.setDefectivePixelsCorrection(is_pixelcorrection);

    std::vector<std::pair<int, int>> pixel_list;
    bool is_enabled = device.getDefectivePixelsCorrection(pixel_list);
    CHECK_FALSE(is_enabled);

}


