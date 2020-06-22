﻿#pragma once
#include "Prog_base.hpp"


namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_2i_1i : public Prog_base
{
public: // construction/destruction
    Prog_2i_1i(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_2i_1i(const Prog_2i_1i& arg) = delete;
    virtual ~Prog_2i_1i() = default;

public: // operators
    Prog_2i_1i&  operator=(const Prog_2i_1i& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:
        //#port
        //#attributes(Input|Retain)
        //#name(iINT16_1_toPy)
        int16 iINT16_1_toPy = 0;

        //#port
        //#attributes(Input|Retain)
        //#name(iINT16_2_toPy)
        int16 iINT16_2_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(iINT16_1_fromPy)
        int16 iINT16_1_fromPy = 0;
        

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_2i_1i::Prog_2i_1i(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_2i_1i::CallPyExecute()
{
    PyReady = this->_PyReady;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"ii",iINT16_1_toPy,iINT16_2_toPy);
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        if(PyLong_Check(ret))
        {
            iINT16_1_fromPy=PyLong_AsLong(ret);
        }
        Py_XDECREF(ret);
    }
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
