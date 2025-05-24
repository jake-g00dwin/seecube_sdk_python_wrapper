/*
 * Author: JakeGoodwin@gorge.works
 * Date: 2025-05-22 
 * filename: main.cpp
 * description: wrapper around the SeeCube SDK for python. 
 */

//Include needed pybind stuff.
#include <pybind11/pybind11.h>

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
        .def("getDeviceName", &SeeCubeSDK::getDeviceName)
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

    py::class_<SeeCube>(sc_cls, "metadata")
        .def(py::init<>())
        .def_readwrite("sensorTemperature", &SeeCube::metadata::sensorTemperature)
        .def_readwrite("frameCounter", &SeeCube::metadata::frameCounter)
        .def_readwrite("relativeTimestamp", &SeeCube::metadata::relativeTimestamp)
        .def_readwrite("epochTimestamp", &SeeCube::metadata::epochTimestamp)
        .def_readwrite("histogram", &SeeCube::metadata::histogram);

}
