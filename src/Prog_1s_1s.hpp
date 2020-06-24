#pragma once
#include "Prog_base.hpp"


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
    PyReady = this->_PyReady;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"s",iStr_1_toPy.ToString().CStr());
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        if(PyUnicode_Check(ret))
        {
            // iINT16_1_fromPy=
            Py_ssize_t len;
            const char* s = PyUnicode_AsUTF8AndSize(ret,&len);
            if (len<=80)
            {
                iStr_1_fromPy = s;
            }
            else
            {
                iStr_1_fromPy = "<ERROR: Too large for IEC String>";
            }
            
        }
        Py_XDECREF(ret);
    }
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
