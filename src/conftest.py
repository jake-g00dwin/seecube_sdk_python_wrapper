# Date: 2025-06-16
# FileName: src/tests/conftest.py
# Description: Test configuration of mocking the seecube SDK.
import sys
# import types
# import pytest


def sc_add(a, b):
    return a + b


module = type(sys)('py_seecube')
module.add = sc_add
sys.modules['py_seecube'] = module


# A second method that worked I pulled out of pytest fixture.
"""
fake_mod = types.ModuleType("py_seecube")
fake_mod.add = lambda a, b, X: a + b
sys.modules["py_seecube"] = fake_mod
"""
