/*
 * Author: JakeGoodwin@gorge.works
 * Date: 2025-05-22 
 * filename: main.cpp
 * description: wrapper around the SeeCube SDK for python. 
 */

//Include needed pybind stuff.
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(py_seecube, handle) {
    handle.doc() = "This is the module docs.";
    handle.def("add", &add);
}
