# Date: 2025-05-29
# FileName: src/tests/test_example.py
# Description: Tests for the example.py file.

import sys
import types
import pytest
import example

# Creating fake module.
# fake_seecubesdk = types.ModuleType("py_seecube")
# fake_seecubesdk.compute = lambada X: x = 45


fake_cmake_text = """
cmake_minimum_required(VERSION 3.20)

# Use the fancy version substitution
project(py_seecube
    VERSION 0.0.1
    DESCRIPTION "A python wrapper for the SeeCube SDK"
    LANGUAGES   C CXX
)
enable_testing()

set(TARGET_GROUP production CACHE STRING "Group to build")

message(${CMAKE_SYSTEM_NAME})


"""


def test_self():
    assert 1 == 1


"""
class TestExampleHelpers:
    def test_projectversionextractor(self):
        # Create temorary file.
        d = tmp_path / "sub"
        d.mkdir()
        p = d / "CMakeLists.txt"
        p.write_text(fake_cmake_text)
        assert p.read_text() == fake_cmake_text
        # ver = example.exract_project_version("../CMakeLists.txt")
        # assert ver == "0.0.3"

"""
