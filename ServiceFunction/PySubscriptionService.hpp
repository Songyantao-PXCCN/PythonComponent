#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Gds/Services/ISubscriptionService.hpp"
namespace PythonArp::PySubscriptionService
{
    using namespace Arp;
    using namespace Arp::Plc::Gds::Services;
    using namespace Arp::System::Rsc;

    
    
    int AddObject(PyObject* builtinsObject);



}