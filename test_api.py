# Date: 2025-05-22
# FileName: test_api.py
# Description: A file to test the python interface to SeeCubeSDK library.

import pytest
import py_seecube


def f():
    raise SystemExit(1)


def test_mytest():
    with pytest.raises(SystemExit):
        f()


def test_SeeCubeSDKClassInstance():
    sc_sdk = py_seecube.SeeCubeSDK(
            py_seecube.SeeCubeSDK.verbosityLevel.info, 1)
