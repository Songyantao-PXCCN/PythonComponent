#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"


namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_1s_1s : public Prog_base
{
public: // construction/destruction
    Prog_1s_1s(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_1s_1s(const Prog_1s_1s& arg) = delete;
    virtual ~Prog_1s_1s() = default;

public: // operators
    Prog_1s_1s&  operator=(const Prog_1s_1s& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:
        //#port
        //#attributes(Input|Retain)
        //#name(iStr_1_toPy)
        StaticString<80> iStr_1_toPy ;

        //#port
        //#attributes(Output)
        //#name(iStr_1_fromPy)
        StaticString<80> iStr_1_fromPy ;
        

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_1s_1s::Prog_1s_1s(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}
// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_1s_1s::CallPyExecute()
{
    PyReady = this->LoadScriptSuccess;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_GET_GIL___
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"(N)",util::arg::PortVar_AsPyObject(iStr_1_toPy));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        util::arg::PortVar_FromPyObject(ret,iStr_1_fromPy);
    }
    if (PyErr_Occurred()){PyErr_Print();}
    Py_XDECREF(ret);
    __ARP_RELEASE_GIL___
}

} // end of namespace PythonArp
