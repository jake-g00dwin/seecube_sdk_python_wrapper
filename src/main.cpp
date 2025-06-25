/*
 * Author: JakeGoodwin@gorge.works
 * Date: 2025-05-22 
 * filename: main.cpp
 * description: wrapper around the SeeCube SDK for python. 
 */

//Include needed pybind stuff.
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

// The SeeCube SDK header(s)
#ifdef UNIT_TESTING
    #include "fake_SeeCube.h"
#else
    #include <SeeCube_SDK_user.h>
#endif

#include <string>
#include <iostream>

//#include <sys/types.h>

namespace py = pybind11;


// Structs and typedefs

// Define rgb color structure
typedef struct {
    uint8_t r, g, b;
} rgb;

// Putting globals here that get used later and have memory allocated.


//Global image size vars.
size_t GBL_width = 0;
size_t GBL_height = 0;

// memory for metadata
bool is_metadata_allocated;
SeeCube::metadata thermalMetadata;
SeeCube::metadata colorMetadata;
SeeCube::metadata frameMetadata;


// memory for images
bool is_imagedata_allocated;
uint16_t* thermalImg;
rgb* colorImg;


// Used for the defective pixel overlaoded methods.
std::vector<std::pair<int, int>> defectivePixelsList;


void allocate_metadata(void) {
    if(is_metadata_allocated){
        std::cout << "Attempt to allocate already allocated memory!" << std::endl;
        return;
    }
    is_metadata_allocated = true;
    /*
     * I'm keeping the old lines here for refernce as they seem to be a result
     * of the original developers likely coming from a only C background.
     *
     * The new keyword should need the sizeof() function call as the keyword 
     * itself and syntax for new already has a type.
     */

    /*
    thermalMetadata.histogram = new uint32_t[(UINT16_MAX + 1) * sizeof(uint32_t)];
    colorMetadata.histogram = new uint32_t[(UINT16_MAX + 1) * sizeof(uint32_t)];
    */

    thermalMetadata.histogram = new uint32_t[(UINT16_MAX + 1)];
    colorMetadata.histogram = new uint32_t[(UINT16_MAX + 1)];
}

//This should always be called at the end.
void delete_metadata(void) {
    if(!is_metadata_allocated){
        std::cout << "Attempt to free unallocated memory!" << std::endl;
        return; 
    }
    delete [] thermalMetadata.histogram;
    delete [] colorMetadata.histogram; 
    is_metadata_allocated = false;
}

void allocate_imagedata(size_t width, size_t height) {
    if(is_imagedata_allocated){
        std::cout << "Attempt to allocate already allocated memory!" << std::endl;
        return;
    }
    //Save the value in the global scope.
    GBL_height = height;
    GBL_width = width;

    uint16_t* thermalImg = new uint16_t[width * height ];
    rgb* colorImg = new rgb[width * height];
    is_imagedata_allocated = true;
}

void delete_imagedata(void){
    if(!is_imagedata_allocated){
        std::cout << "Attempt to free unallocated memory!" << std::endl;
        return; 
    }
    delete [] thermalImg;
    delete [] colorImg; 
    is_imagedata_allocated = false;
}

void test_SDKFunction(void) {
    std::cout << "test_SDKFunction():" << std::endl;
    std::cout << 
        "If the program crashes it indicates it's not a python/binding issue." 
        << std::endl;

    SeeCubeSDK seeCubeSDK(SeeCubeSDK::verbosityLevel::info, 4);
    seeCubeSDK.parseCoreParameter("displayHistogram");

    int count = seeCubeSDK.getDeviceCount();
    printf("Device count: %d\n", count);

   //Now we try out getting the device name. This should work. 
    int i = 0; //Device index

    //std::print("Device {:d}: {:s}\n", i, seeCubeSDK.getDeviceName(i));
    std::cout << 
        "Device: " << i << 
        ", " << seeCubeSDK.getDeviceName(i) << std::endl;

}

SeeCube::metadata get_ThermalMetaData(void){
    SeeCube::metadata md;
    return md;
}

SeeCube::metadata get_ColorMetaData(void){
    SeeCube::metadata md;
    return md;
}

SeeCube::metadata get_LastMetaData(void){
    SeeCube::metadata md; 
    
    md.epochTimestamp = 0;
    md.relativeTimestamp = 1;
    md.frameCounter = 1;
    md.histogram = nullptr;
    md.sensorTemperature = 0.5;

    return md;
}

py::array_t<uint16_t, py::array::c_style> get_TestFrame(size_t width, size_t height){

    std::ptrdiff_t size = width * height;
    uint16_t *rawFrame = new uint16_t[size];

    //Populate with striped data.
    for(uint16_t i = 0; i < size; i++){
        if(i % 2 == 0){
            rawFrame[i] = 0;
        }
        else{
            rawFrame[i] = UINT16_MAX;
        }
    }
 
    std::vector<std::ptrdiff_t> shape = {(std::ptrdiff_t)height, (std::ptrdiff_t)width};
    std::vector<std::ptrdiff_t> strides = {
        static_cast<std::ptrdiff_t>(width * sizeof(uint16_t)),
        sizeof(uint16_t)
    };

    // 250 is the timout value in ms.
    //self.getRawFrame((uint8_t *)rawFrame, &thermalMetadata, 250); 
    py::capsule free_when_done(rawFrame, [](void *f){
        uint16_t *rawFrame = reinterpret_cast<uint16_t*>(f);
        delete[] rawFrame;        
    });

    return py::array_t<uint16_t, py::array::c_style>(
        shape,
        strides, 
        rawFrame,
        free_when_done
    );
}


PYBIND11_MODULE(py_seecube, handle) {
    handle.doc() = "This is the module docs.";
    handle.doc() = R"pbdoc(
        py_seecube 
        --------
        This module provides bindings for the SeeCube SDK and related functionality.
    )pbdoc";
    handle.def("test_SDKFunction", &test_SDKFunction);
    handle.def("allocate_metadata", &allocate_metadata);
    handle.def("delete_metadata", &delete_metadata);
    handle.def("allocate_imagedata", &allocate_imagedata);
    handle.def("delete_imagedata", &delete_imagedata);
    handle.def("get_TestFrame", &get_TestFrame); 
    handle.def("get_LastMetaData", &get_LastMetaData);

    // Testing Functionality, used with Fake of classes.
#ifdef UNIT_TESTING
    handle.def("set_FakeSeeCubeDeviceCount", &set_FakeSeeCubeDeviceCount);
    handle.def("fakeSeeCube_setCameraConnectionState", &fakeSeeCube_setCameraConnectionState);
    handle.def("fakeSeeCube_setImageSizeReturnValue", &fakeSeeCube_setImageSizeReturnValue);
    handle.def("fakeSeeCube_setRawImageReturnBool", &fakeSeeCube_setRawImageReturnBool);
    handle.def("spy_is_pixelcorrection", &spy_is_pixelcorrection);
#endif



    // SeeCubeSDK SECTION:
    py::class_<SeeCubeSDK> cls(handle, "SeeCubeSDK");

    //Bind the nested enum class.
    py::enum_<SeeCubeSDK::verbosityLevel>(cls, "verbosityLevel")
        .value("error", SeeCubeSDK::verbosityLevel::error)
        .value("warning", SeeCubeSDK::verbosityLevel::warning)
        .value("info", SeeCubeSDK::verbosityLevel::info);

    //Binding the class and it's constructor methods.
    cls
        .def(py::init<SeeCubeSDK::verbosityLevel, const int&>(),
            py::arg("verbosityLevel"), py::arg("value")) // Constructor
        .def("getDeviceCount", &SeeCubeSDK::getDeviceCount)
        .def("getDeviceName", &SeeCubeSDK::getDeviceName, py::return_value_policy::copy)
        .def("isConnected", &SeeCubeSDK::isConnected)
        .def("parseCoreParameter", &SeeCubeSDK::parseCoreParameter);

    // SeeCube SECTION:
    py::class_<SeeCube> sc_cls(handle, "SeeCube");

    py::enum_<SeeCube::mapping>(sc_cls, "mapping")
        .value("fullScale", SeeCube::mapping::fullScale)
        .value("auomatic", SeeCube::mapping::automatic)
        .value("manual", SeeCube::mapping::manual)
        .value("histEq", SeeCube::mapping::histEq)
        .value("adaptive", SeeCube::mapping::adaptive)
        .export_values();

    py::class_<SeeCube::metadata>(sc_cls, "metadata")
        .def(py::init<>())
        .def_readwrite("sensorTemperature", &SeeCube::metadata::sensorTemperature)
        .def_readwrite("frameCounter", &SeeCube::metadata::frameCounter)
        .def_readwrite("relativeTimestamp", &SeeCube::metadata::relativeTimestamp)
        .def_readwrite("epochTimestamp", &SeeCube::metadata::epochTimestamp)
        .def_readwrite("histogram", &SeeCube::metadata::histogram);

    sc_cls
        .def(py::init<const int&, const std::string&>(),
                py::arg("pHandle"), py::arg("mSensorDataPath"))

        .def("getPartNumber", &SeeCube::getPartNumber)

        .def("getSerialNumber", &SeeCube::getSerialNumber)

        .def("getSensorSettings", [](SeeCube &self) {
                uint16_t TINT, GFID, GSK, GAIN;       
                self.getSensorSettings(TINT, GFID, GSK, GAIN);
                return std::make_tuple(TINT, GFID, GSK, GAIN);
                }, R"pbdoc(
 param[out] TINT variable where the integration time value will be stored.
 param[out] GFID variable where the transistors gate voltage for the active microbolometers value will be stored.
 param[out] GSK  variable where the transistors gate voltage for the compensation microbolometers value will be stored.
 param[out] GAIN variable where the external trigger mode / gain / window invert-revert-rotation values will be stored.
                )pbdoc") 

        .def("getDeviceFrameRate", &SeeCube::getDeviceFrameRate)

        .def("setDeviceFrameRate", &SeeCube::setDeviceFrameRate)

        .def("getImageSize", [](SeeCube &self) {
                self.getImageSize(GBL_width, GBL_height); 
                return std::make_tuple(GBL_width, GBL_height);
                })

        .def("getRawFrame", [](SeeCube &self, uint32_t Timeout) {

            std::ptrdiff_t size = GBL_width * GBL_height;
            uint16_t *rawFrame = new uint16_t[size];

            //Get the data from the camera.
            if(!self.getRawFrame((uint8_t*)rawFrame, &thermalMetadata, Timeout)) {
                std::cout << "No new thermal frame received!" << std::endl;
            }
         
            std::vector<std::ptrdiff_t> shape = {(std::ptrdiff_t)GBL_height, (std::ptrdiff_t)GBL_width};
            std::vector<std::ptrdiff_t> strides = {
                static_cast<std::ptrdiff_t>(GBL_width * sizeof(uint16_t)),
                sizeof(uint16_t)
            };

            // 250 is the timout value in ms.
            //self.getRawFrame((uint8_t *)rawFrame, &thermalMetadata, 250); 
            py::capsule free_when_done(rawFrame, [](void *f){
                uint16_t *rawFrame = reinterpret_cast<uint16_t*>(f);
                delete[] rawFrame;        
            });

            return py::array_t<uint16_t, py::array::c_style>(
                shape,
                strides, 
                rawFrame,
                free_when_done
            );
        }, py::arg("Timeout") = 0, R"pbdoc(
Args:
    Timeout: Timeout value in milliseconds for frame acquisition.(Default 0)

For receiving a single frame using direct assingment is fine, however for 
multiple frames you'll need to preform a deep copy so that the memory assigned
to hold that previous frame is freed.

Example(single frame):

# SeeCube Object
frame = device.getRawFame()


Example(Multiple frames):
shape = (height, width)
frame = numpy.zeros(shape, numpy.uint16_t)
np.copyto(frame, device.getRawFrame())
        )pbdoc")

        .def("getColorFrame", [](SeeCube &self, uint32_t Timeout) {
            std::ptrdiff_t size = GBL_width * GBL_height;
            rgb *colorFrame = new rgb[size];

            //Get the data from the camera.
            if(!self.getColorFrame((uint8_t*)colorFrame, &colorMetadata, Timeout)) {
                std::cout << "No new color frame received!" << std::endl;
            }
         
            std::vector<std::ptrdiff_t> shape = {
            (std::ptrdiff_t)GBL_height,
            (std::ptrdiff_t)GBL_width,
            3};


            std::vector<std::ptrdiff_t> strides = {
                static_cast<std::ptrdiff_t>(GBL_width * sizeof(rgb)),
                sizeof(rgb),
                1
            };

            // Cast to a byte pointer.
            uint8_t *raw = reinterpret_cast<uint8_t*>(colorFrame);

            // 250 is the timout value in ms.
            //self.getRawFrame((uint8_t *)colorFrame, &thermalMetadata, 250); 
            py::capsule free_when_done(colorFrame, [](void *f){
                rgb *colorFrame = reinterpret_cast<rgb*>(f);
                delete[] colorFrame;        
            });

            return py::array(
                py::buffer_info(
                    raw,
                    sizeof(uint8_t),
                    py::format_descriptor<uint8_t>::format(),
                    3,  // NDim
                    shape,
                    strides
                ),
                free_when_done
            );

        }, py::arg("Timeout") = 0, R"pbdoc(
        )pbdoc")
        .def("getProcessingFrameRate", &SeeCube::getProcessingFrameRate)

        .def("setProcessingFrameRate", &SeeCube::setProcessingFrameRate)

        .def("setFreeRun", &SeeCube::setFreeRun)

        .def("getFreeRun", &SeeCube::getFreeRun)

        .def("runFFC", &SeeCube::runFFC)

        .def("setFFC", &SeeCube::setFFC)

        .def("getFFC", &SeeCube::getFFC)

        .def("closeShutter", &SeeCube::closeShutter)

        .def("openShutter", &SeeCube::openShutter)

        .def("setColorPreset", &SeeCube::setColorPreset)

        .def("getColorPreset", &SeeCube::getColorPreset)

        .def("setDefectivePixelsCorrection", &SeeCube::setDefectivePixelsCorrection)

        //Overloaded function
        .def("getDefectivePixelsCorrectionStatus",
                static_cast<bool (SeeCube::*)()>(&SeeCube::getDefectivePixelsCorrection))

        .def("getDefectivePixelsCorrection", [](SeeCube &self) {
                    std::vector<std::pair<int, int>> defective_pixels;
                    bool result = self.getDefectivePixelsCorrection(defective_pixels);
                    return py::make_tuple(result, defective_pixels);
                })

        .def("setShutterlessCorrection", &SeeCube::setShutterlessCorrection)

        .def("getShutterlessCorrection", &SeeCube::getShutterlessCorrection)

        .def("setRadiometricCorrection", &SeeCube::setRadiometricCorrection)

        .def("getRadiometricCorrection", &SeeCube::getRadiometricCorrection)
        
        .def("getSensorTemperature", &SeeCube::getSensorTemperature)

        .def("getPixelTemperature", &SeeCube::getPixelTemperature,
                py::arg("X"),
                py::arg("Y"),
                py::arg("Emissivity") = 100.0f)

        .def("setMappingMode", &SeeCube::setMappingMode,
                py::arg("mapping"),
                py::arg("pFirstParam") = -1.0f,
                py::arg("pSecondParam") = -1.0f)
        .def("getMappingMode", &SeeCube::getMappingMode)

        .def("setColumnDestriping", &SeeCube::setColumnDestriping)

        .def("getColumnDestriping", &SeeCube::getColumnDestriping)

        .def("setTemporalFiltering", &SeeCube::setTemporalFiltering)

        .def("getTemporalFiltering", &SeeCube::getTemporalFiltering)

        .def("softwareTriggerRequest", &SeeCube::softwareTriggerRequest);
        
}
