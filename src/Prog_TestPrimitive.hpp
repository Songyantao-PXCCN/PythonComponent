﻿#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"

namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_TestPrimitive : public Prog_base
{
public: // construction/destruction
    Prog_TestPrimitive(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_TestPrimitive(const Prog_TestPrimitive& arg) = delete;
    virtual ~Prog_TestPrimitive() = default;

public: // operators
    Prog_TestPrimitive&  operator=(const Prog_TestPrimitive& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:

        //#port
        //#attributes(Input|Retain)
        //#name(xBool_toPy)
        boolean Bool_toPy = false;
        //#port
        //#attributes(Output)
        //#name(xBool_fromPy)
        boolean Bool_fromPy = false;

        //#port
        //#attributes(Input|Retain)
        //#name(int8_toPy)
        int8 int8_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(int8_fromPy)
        int8 int8_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(int16_toPy)
        int16 int16_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(int16_fromPy)
        int16 int16_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(int32_toPy)
        int32 int32_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(int32_fromPy)
        int32 int32_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(int64_toPy)
        int64 int64_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(int64_fromPy)
        int64 int64_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(uint8_toPy)
        uint8 uint8_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(uint8_fromPy)
        uint8 uint8_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(uint16_toPy)
        uint16 uint16_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(uint16_fromPy)
        uint16 uint16_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(uint32_toPy)
        uint32 uint32_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(uint32_fromPy)
        uint32 uint32_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(uint64_toPy)
        uint64 uint64_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(uint64_fromPy)
        uint64 uint64_fromPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(float32_toPy)
        float32 float32_toPy = 0.0;

        //#port
        //#attributes(Output)
        //#name(float32_fromPy)
        float32 float32_fromPy = 0.0;

        //#port
        //#attributes(Input|Retain)
        //#name(float64_toPy)
        float64 float64_toPy = 0.0;

        //#port
        //#attributes(Output)
        //#name(float64_fromPy)
        float64 float64_fromPy = 0.0;

        //#port
        //#attributes(Input|Retain)
        //#name(STRING_toPy)
        StaticString<80> STRING_toPy;

        //#port
        //#attributes(Output)
        //#name(STRING_fromPy)
        StaticString<80> STRING_fromPy;

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_TestPrimitive::Prog_TestPrimitive(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_TestPrimitive::CallPyExecute()
{
    PyReady = this->LoadScriptSuccess;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_GET_GIL___
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"((NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN))",
                                                                    util::arg::PortVar_AsPyObject(Bool_toPy)    ,util::arg::PortVar_AsPyObject(Bool_toPy,true),//here the 'true' means convert the RAW buffer to bytearray object 
                                                                    util::arg::PortVar_AsPyObject(int8_toPy)    ,util::arg::PortVar_AsPyObject(int8_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(int16_toPy)   ,util::arg::PortVar_AsPyObject(int16_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(int32_toPy)   ,util::arg::PortVar_AsPyObject(int32_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(int64_toPy)   ,util::arg::PortVar_AsPyObject(int64_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(uint8_toPy)   ,util::arg::PortVar_AsPyObject(uint8_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(uint16_toPy)  ,util::arg::PortVar_AsPyObject(uint16_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(uint32_toPy)  ,util::arg::PortVar_AsPyObject(uint32_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(uint64_toPy)  ,util::arg::PortVar_AsPyObject(uint64_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(float32_toPy) ,util::arg::PortVar_AsPyObject(float32_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(float64_toPy) ,util::arg::PortVar_AsPyObject(float64_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(STRING_toPy)  ,util::arg::PortVar_AsPyObject(STRING_toPy,true)
                                                                    );
    if (PyErr_Occurred()){PyErr_Print();}
    if (ret != NULL)
    {
        int idx = 0;
        PyObject *retArray[12]{};
        if(PyArg_ParseTuple(ret,"OOOOOOOOOOOO", &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++],
                                                &retArray[idx++])
                                                )
            {
                idx = 0;
                util::arg::PortVar_FromPyObject(retArray[idx++],Bool_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],int8_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],int16_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],int32_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],int64_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],uint8_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],uint16_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],uint32_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],uint64_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],float32_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],float64_fromPy);
                util::arg::PortVar_FromPyObject(retArray[idx++],STRING_fromPy);
            }
    }
    if (PyErr_Occurred()){PyErr_Print();}
    Py_XDECREF(ret);
    __ARP_RELEASE_GIL___
}

} // end of namespace PythonArp
