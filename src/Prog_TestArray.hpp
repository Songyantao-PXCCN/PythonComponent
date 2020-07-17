#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"

namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_TestArray : public Prog_base
{
public: // construction/destruction
    Prog_TestArray(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_TestArray(const Prog_TestArray& arg) = delete;
    virtual ~Prog_TestArray() = default;

public: // operators
    Prog_TestArray&  operator=(const Prog_TestArray& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:
    /*
    _1_BOOL_3_t : ARRAY[0..2] OF BOOL;

    _2_SINT_3_t : ARRAY[0..2] OF SINT;

    _3_INT_3_t  : ARRAY[0..2] OF INT;

    _4_DINT_3_t : ARRAY[0..2] OF DINT;

    _5_LINT_3_t : ARRAY[0..2] OF LINT;

    _6_USINT_3_t :ARRAY[0..2] OF USINT;
    _6_BYTE_3_t :ARRAY[0..2] OF BYTE;

    _7_UINT_3_t : ARRAY[0..2] OF UINT;
    _7_WORD_3_t : ARRAY[0..2] OF WORD;

    _8_UDINT_3_t : ARRAY[0..2] OF UDINT;
    _8_DWORD_3_t : ARRAY[0..2] OF DWORD;

    _9_ULINT_3_t : ARRAY[0..2] OF ULINT;
    _9_LWORD_3_t : ARRAY[0..2] OF LWORD;

    _10_REAL_3_t : ARRAY[0..2] OF REAL;

    _11_LREAL_3_t : ARRAY[0..2] OF LREAL;

    _12_STRING_3_t : ARRAY[0..2] OF STRING;
        */

        //#port
        //#attributes(Input|Retain)
        //#name(xBool_toPy)
        boolean Bool_toPy[3] ={};
        //#port
        //#attributes(Output)
        //#name(xBool_fromPy)
        boolean Bool_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(int8_toPy)
        int8 int8_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(int8_fromPy)
        int8 int8_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(int16_toPy)
        int16 int16_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(int16_fromPy)
        int16 int16_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(int32_toPy)
        int32 int32_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(int32_fromPy)
        int32 int32_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(int64_toPy)
        int64 int64_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(int64_fromPy)
        int64 int64_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(uint8_toPy)
        uint8 uint8_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(uint8_fromPy)
        uint8 uint8_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(uint16_toPy)
        uint16 uint16_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(uint16_fromPy)
        uint16 uint16_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(uint32_toPy)
        uint32 uint32_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(uint32_fromPy)
        uint32 uint32_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(uint64_toPy)
        uint64 uint64_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(uint64_fromPy)
        uint64 uint64_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(float32_toPy)
        float32 float32_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(float32_fromPy)
        float32 float32_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(float64_toPy)
        float64 float64_toPy[3] ={};

        //#port
        //#attributes(Output)
        //#name(float64_fromPy)
        float64 float64_fromPy[3] ={};

        //#port
        //#attributes(Input|Retain)
        //#name(STRING_toPy)
        StaticString<80> STRING_toPy[3];

        //#port
        //#attributes(Output)
        //#name(STRING_fromPy)
        StaticString<80> STRING_fromPy[3];

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_TestArray::Prog_TestArray(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_TestArray::CallPyExecute()
{
    PyReady = this->LoadScriptSuccess;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"((NNN)(NNN)(NNN)(NNN)(NNN)(NNN)(NNN)(NNN)(NNN)(NNN)(NNN)(NNN))",
                                                                    /*        relative  Object                      convert array RAW buffer to bytearray                convert each element to bytearray        */
                                                                    util::arg::PortVar_AsPyObject(Bool_toPy)    ,util::arg::PortVar_AsPyObject(Bool_toPy,true)     ,util::arg::PortVar_AsPyObject(Bool_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(int8_toPy)    ,util::arg::PortVar_AsPyObject(int8_toPy,true)     ,util::arg::PortVar_AsPyObject(int8_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(int16_toPy)   ,util::arg::PortVar_AsPyObject(int16_toPy,true)    ,util::arg::PortVar_AsPyObject(int16_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(int32_toPy)   ,util::arg::PortVar_AsPyObject(int32_toPy,true)    ,util::arg::PortVar_AsPyObject(int32_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(int64_toPy)   ,util::arg::PortVar_AsPyObject(int64_toPy,true)    ,util::arg::PortVar_AsPyObject(int64_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(uint8_toPy)   ,util::arg::PortVar_AsPyObject(uint8_toPy,true)    ,util::arg::PortVar_AsPyObject(uint8_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(uint16_toPy)  ,util::arg::PortVar_AsPyObject(uint16_toPy,true)   ,util::arg::PortVar_AsPyObject(uint16_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(uint32_toPy)  ,util::arg::PortVar_AsPyObject(uint32_toPy,true)   ,util::arg::PortVar_AsPyObject(uint32_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(uint64_toPy)  ,util::arg::PortVar_AsPyObject(uint64_toPy,true)   ,util::arg::PortVar_AsPyObject(uint64_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(float32_toPy) ,util::arg::PortVar_AsPyObject(float32_toPy,true)  ,util::arg::PortVar_AsPyObject(float32_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(float64_toPy) ,util::arg::PortVar_AsPyObject(float64_toPy,true)  ,util::arg::PortVar_AsPyObject(float64_toPy,false,true),
                                                                    util::arg::PortVar_AsPyObject(STRING_toPy)  ,util::arg::PortVar_AsPyObject(STRING_toPy,true)   ,util::arg::PortVar_AsPyObject(STRING_toPy,false,true)
                                                                    );
    if (PyErr_Occurred()){PyErr_Print();}
    if (ret != NULL)
    {
        int idx = 0;
        PyObject *retObj[12]{};
        if(PyArg_ParseTuple(ret,"OOOOOOOOOOOO", &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++],
                                                &retObj[idx++])
                                                )
            {
                idx = 0;
                util::arg::PortVar_FromPyObject(retObj[idx++],Bool_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],int8_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],int16_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],int32_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],int64_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],uint8_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],uint16_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],uint32_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],uint64_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],float32_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],float64_fromPy);
                util::arg::PortVar_FromPyObject(retObj[idx++],STRING_fromPy);
            }
    }
    if (PyErr_Occurred()){PyErr_Print();}
    Py_XDECREF(ret);
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
