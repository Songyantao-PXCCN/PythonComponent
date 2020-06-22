﻿#pragma once
#include "Prog_base.hpp"


namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_2x_1x : public Prog_base
{
public: // construction/destruction
    Prog_2x_1x(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_2x_1x(const Prog_2x_1x& arg) = delete;
    virtual ~Prog_2x_1x() = default;

public: // operators
    Prog_2x_1x&  operator=(const Prog_2x_1x& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:

        //#port
        //#attributes(Input|Retain)
        //#name(xBool_1_toPy)
        boolean xBool_1_toPy = false;

        //#port
        //#attributes(Input|Retain)
        //#name(xBool_2_toPy)
        boolean xBool_2_toPy = false;

        //#port
        //#attributes(Output)
        //#name(xBool_1_fromPy)
        boolean xBool_1_fromPy = false;
        

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_2x_1x::Prog_2x_1x(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_2x_1x::CallPyExecute()
{
    PyReady = this->_PyReady;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"NN",PyBool_FromLong(this->xBool_1_toPy),PyBool_FromLong(this->xBool_2_toPy));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        if(PyBool_Check(ret))
        {
            PyArg_Parse(ret,"p",&this->xBool_1_fromPy);
        }
        Py_XDECREF(ret);
    }
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
