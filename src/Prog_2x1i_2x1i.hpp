#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"

namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_2x1i_2x1i : public Prog_base
{
public: // construction/destruction
    Prog_2x1i_2x1i(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_2x1i_2x1i(const Prog_2x1i_2x1i& arg) = delete;
    virtual ~Prog_2x1i_2x1i() = default;

public: // operators
    Prog_2x1i_2x1i&  operator=(const Prog_2x1i_2x1i& arg) = delete;


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
        //#attributes(Input|Retain)
        //#name(iInt16_1_toPy)
        int16 iInt16_1_toPy = 0;

        //#port
        //#attributes(Output)
        //#name(xBool_1_fromPy)
        boolean xBool_1_fromPy = false;

        //#port
        //#attributes(Output)
        //#name(xBool_2_fromPy)
        boolean xBool_2_fromPy = false;

        //#port
        //#attributes(Output)
        //#name(iInt16_1_fromPy)
        int16 iInt16_1_fromPy = 0;
        

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_2x1i_2x1i::Prog_2x1i_2x1i(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_2x1i_2x1i::CallPyExecute()
{
    PyReady = this->LoadScriptSuccess;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"(NNN)",   util::arg::PortVar_AsPyObject(xBool_2_toPy),
                                                                        util::arg::PortVar_AsPyObject(xBool_2_toPy),
                                                                        util::arg::PortVar_AsPyObject(iInt16_1_toPy)
                                                                        );
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        if(PyTuple_Check(ret))
        {
            PyObject *ret_0 = NULL,*ret_1 = NULL,*ret_2 = NULL;
            if(PyArg_ParseTuple(ret,"OOO",&ret_0,&ret_1,&ret_2))
            {
                util::arg::PortVar_FromPyObject(ret_0,xBool_1_fromPy);
                util::arg::PortVar_FromPyObject(ret_1,xBool_2_fromPy);
                util::arg::PortVar_FromPyObject(ret_2,iInt16_1_fromPy);
            }
        }
    }
    if (PyErr_Occurred()){PyErr_Print();}
    Py_XDECREF(ret);
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
