# Date: 2025-05-22
# FileName: test_api.py

import pytest
import py_seecube


def f():
    raise SystemExit(1)


def test_mytest():
    with pytest.raises(SystemExit):
        f()
