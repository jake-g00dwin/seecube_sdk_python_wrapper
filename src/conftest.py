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

"""
@pytest.fixture(autouse=True, scope="session")
def mock_py_seecube():
    # Create a fake module with the same interface
    fake_mod = types.ModuleType("py_seecube")
    fake_mod.compute = lambda x: 999  # Stubbed result
    sys.modules["py_seecube"] = fake_mod
"""
