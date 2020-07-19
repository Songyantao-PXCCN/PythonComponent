#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include "Arp/System/Core/Arp.h"
namespace PythonArp::PyArpLog
{
    int AddObject(PyObject* builtinsObject);
}