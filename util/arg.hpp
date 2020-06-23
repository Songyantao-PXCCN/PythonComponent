#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"

namespace PythonArp::util::argParse
{

    int xPyArg_ParseTupleAndKeywords(PyObject *, PyObject *,const char *, char **, ...);

    int _Py_hasNoKeywords(PyObject *kwargs);
    int _Py_hadNoPositional(PyObject *args);
}