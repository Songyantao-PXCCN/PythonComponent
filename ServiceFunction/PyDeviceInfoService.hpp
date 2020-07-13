#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include "Arp/System/Core/Arp.h"
#include "Arp/Device/Interface/Services/IDeviceInfoService.hpp"
namespace PythonArp::PyDeviceInfoService
{
    int AddObject(PyObject* builtinsObject);
}