#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"

namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_1LWToByteArray : public Prog_base
{
public: // construction/destruction
    Prog_1LWToByteArray(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_1LWToByteArray(const Prog_1LWToByteArray& arg) = delete;
    virtual ~Prog_1LWToByteArray() = default;

public: // operators
    Prog_1LWToByteArray&  operator=(const Prog_1LWToByteArray& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:
        //#port
        //#attributes(Input|Retain)
        //#name(lw_1_toPy)
        uint64 lw_1_toPy ;    

        //#port
        //#attributes(Output)
        //#name(lw_1_fromPy)
        uint64 lw_1_fromPy ; 

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_1LWToByteArray::Prog_1LWToByteArray(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_1LWToByteArray::CallPyExecute()
{
    PyReady = this->_PyReady;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"(N)",util::arg::PrimitivePortVar_ToPyObject(lw_1_toPy,true));//As ByteArray
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        util::arg::PyObject_ToPrimitivePortVar(ret,lw_1_fromPy);
    }
    if (PyErr_Occurred()){PyErr_Print();}
    Py_XDECREF(ret);
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
