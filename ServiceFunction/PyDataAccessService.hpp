#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Rsc/Services/RscArrayReader.hpp"
#include "Arp/System/Rsc/Services/RscArrayWriter.hpp"
#include "Arp/System/Rsc/Services/RscStructWriter.hxx"
#include "Arp/System/Rsc/Services/RscStructReader.hxx"
#include "Arp/Plc/Gds/Services/IDataAccessService.hpp"


namespace PythonArp::PyDataAccessService
{
    using namespace Arp;
    using namespace Arp::Plc::Gds::Services;
    using namespace Arp::System::Rsc;


    PyObject* StructTypeReadHandler(RscStructReader<512> reader);
    PyObject* PrimitiveTypeReadHandler(RscVariant<512> var);
    PyObject* ArrayTypeReadHandler(RscArrayReader reader);
    PyObject* AutoTypeReadHandler(RscVariant<512> var);


    int AddObject(PyObject* builtinsObject);

}