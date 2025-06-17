/*
 * Author: JakeGoodwin@gorge.works
 * Date: 2025-05-22 
 * filename: main.cpp
 * description: wrapper around the SeeCube SDK for python. 
 */

//Include needed pybind stuff.
#include <pybind11/pybind11.h>
//#include <pybind11/stl.h>

// The SeeCube SDK header(s)
#include <SeeCube_SDK_user.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(py_seecube, handle) {
    handle.doc() = "This is the module docs.";
    handle.def("add", &add);

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
        /*
        .def("getDeviceName", [](SeeCubeSDK &self, int pHandle) {
                    try {
                        return self.getDeviceName(pHandle);
                    } catch (const std::exception& e) {
                        throw std::runtime_error(std::string("C++ exeception: ") + e.what());
                    } catch (...) {
                        throw std::runtime_error("Unknown C++ exeception");
                    }
                })
        */
        .def("isConnected", &SeeCubeSDK::isConnected)
        .def("parseCoreParameter", &SeeCubeSDK::parseCoreParameter);

    // SeeCube SECTION:
    py::class_<SeeCube> sc_cls(handle, "SeeCube");

    py::enum_<SeeCube::mapping>(sc_cls, "mapping")
        .value("fullScale", SeeCube::mapping::fullScale)
        .value("auomatic", SeeCube::mapping::automatic)
        .value("manual", SeeCube::mapping::manual)
        .value("histEq", SeeCube::mapping::histEq)
        .value("adaptive", SeeCube::mapping::adaptive);


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
        .def("getSensorSettings", &SeeCube::getSensorSettings)
        .def("getDeviceFrameRate", &SeeCube::getDeviceFrameRate)
        .def("setDeviceFrameRate", &SeeCube::setDeviceFrameRate)
        .def("getImageSize", &SeeCube::getImageSize)
        .def("getRawFrame", &SeeCube::getRawFrame)
        .def("getColorFrame", &SeeCube::getColorFrame)
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
        .def("getDefectivePixelsCorrection",
                static_cast<bool (SeeCube::*)()>(&SeeCube::getDefectivePixelsCorrection))
        .def("getDefectivePixelsCorrection",
                static_cast<bool (SeeCube::*)(std::vector<std::pair<int, int>>&)>(&SeeCube::getDefectivePixelsCorrection),
                py::arg("pDefectivePixelsList"))
        .def("setShutterlessCorrection", &SeeCube::setShutterlessCorrection)
        .def("getShutterlessCorrection", &SeeCube::getShutterlessCorrection)
        .def("setRadiometricCorrection", &SeeCube::setRadiometricCorrection)
        .def("getRadiometricCorrection", &SeeCube::getRadiometricCorrection)
        .def("getSensorTemperature", &SeeCube::getSensorTemperature)
        .def("getPixelTemperature", &SeeCube::getPixelTemperature)
        .def("setMappingMode", &SeeCube::setMappingMode)
        .def("getMappingMode", &SeeCube::getMappingMode)
        .def("setColumnDestriping", &SeeCube::setColumnDestriping)
        .def("getColumnDestriping", &SeeCube::getColumnDestriping)
        .def("setTemporalFiltering", &SeeCube::setTemporalFiltering)
        .def("getTemporalFiltering", &SeeCube::getTemporalFiltering)
        .def("softwareTriggerRequest", &SeeCube::softwareTriggerRequest);
        
}
