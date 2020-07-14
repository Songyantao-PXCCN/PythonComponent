#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"

namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_1arrINT10_1arrINT10 : public Prog_base
{
public: // construction/destruction
    Prog_1arrINT10_1arrINT10(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_1arrINT10_1arrINT10(const Prog_1arrINT10_1arrINT10& arg) = delete;
    virtual ~Prog_1arrINT10_1arrINT10() = default;

public: // operators
    Prog_1arrINT10_1arrINT10&  operator=(const Prog_1arrINT10_1arrINT10& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:
        //#port
        //#attributes(Input|Retain)
        //#name(arrINT10_toPy)
        int16 arrINT10_toPy[10]{};    

        //#port
        //#attributes(Output)
        //#name(arrINT10_fromPy)
        int16 arrINT10_fromPy[10]{}; 

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_1arrINT10_1arrINT10::Prog_1arrINT10_1arrINT10(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}

// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_1arrINT10_1arrINT10::CallPyExecute()
{
    PyReady = this->LoadScriptSuccess;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__

    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"(NNN)",util::arg::PortVar_AsPyObject(arrINT10_toPy),
                                                                    util::arg::PortVar_AsPyObject(arrINT10_toPy,true),
                                                                    util::arg::PortVar_AsPyObject(arrINT10_toPy,false,true));

    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        util::arg::PortVar_FromPyObject(ret,arrINT10_fromPy);
    }
    if (PyErr_Occurred()){PyErr_Print();}
    Py_XDECREF(ret);
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
