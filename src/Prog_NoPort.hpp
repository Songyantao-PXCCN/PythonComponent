#pragma once
#include "Prog_base.hpp"


namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_NoPort : public Prog_base
{
public: // construction/destruction
    Prog_NoPort(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_NoPort(const Prog_NoPort& arg) = delete;
    virtual ~Prog_NoPort() = default;

public: // operators
    Prog_NoPort&  operator=(const Prog_NoPort& arg) = delete;

public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
        

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_NoPort::Prog_NoPort(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_NoPort::CallPyExecute()
{
    PyReady = this->_PyReady;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    Py_XDECREF(PyObject_CallObject(this->PYO_Execute, NULL));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
