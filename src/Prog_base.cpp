#include "Prog_base.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace PythonArp
{
 
void Prog_base::Execute()
{
    this->CallPyExecute();
}


void Prog_base::PythonArpProgramConstruction()
{
    this->LoadScriptSuccess = false;
    this->PYO_Module = NULL;
    this->PYO_Execute = NULL;
    this->PYO_Start = NULL;
    this->PYO_Stop = NULL;
    this->PYO_Initialize = NULL;
    this->PYO_Dispose = NULL;
    if (!Py_IsInitialized()) return;

    Arp::String progName = this->GetFullName();
    progName = progName.Substr(progName.Find("/") + 1);

    __ARP_GET_GIL___
        if (PyErr_Occurred()){PyErr_Print();PyErr_Clear();}
        this->PYO_Module = PyImport_ImportModule(progName.CStr());
        if (PYO_Module == NULL)
        {
            log.Error("Can not load Python Module : \'{}\'", progName.CStr());
            if (PyErr_Occurred()){PyErr_Print();}
        }
        else
        {

#ifdef RELOAD_MODE
            this->PYO_Module = PyImport_ReloadModule(PYO_Module); // force to reload it for refresh!
            if(PYO_Module == NULL || PyErr_Occurred() )
            {
                log.Error("Can not load Python Module : \'{}\'", progName.CStr());
                PyErr_Print();
            }
            else
            {
                Py_XDECREF(PYO_Module);
#endif
                log.Info("Success load Python Module : \'{}\'", progName.CStr());
                this->PYO_Dispose = PyObject_GetAttrString(PYO_Module,"Dispose");
                this->PYO_Initialize = PyObject_GetAttrString(PYO_Module,"Initialize");
                this->PYO_Start = PyObject_GetAttrString(PYO_Module, "Start");
                this->PYO_Stop = PyObject_GetAttrString(PYO_Module, "Stop");
                this->PYO_Execute = PyObject_GetAttrString(PYO_Module, "Execute");
                if (PyErr_Occurred()){PyErr_Clear();
                }
#ifdef RELOAD_MODE
            }
#endif
        }
    __ARP_RELEASE_GIL___
    if (PYO_Module !=NULL)
    { 
        this->CallPyInitialize();
        this->LoadScriptSuccess = true;
    }
}

Prog_base::~Prog_base()
{
    if (!Py_IsInitialized()) return;
    this->CallPyDispose();
    __ARP_GET_GIL___
        Py_CLEAR(PYO_Execute);
        Py_CLEAR(PYO_Stop);
        Py_CLEAR(PYO_Start);
        Py_CLEAR(PYO_Initialize);
        Py_CLEAR(PYO_Dispose);
        Py_CLEAR(PYO_Module);
    __ARP_RELEASE_GIL___
}


void Prog_base::CallPyStart()
{
    
    if (this->PYO_Start == NULL)
        return;
    __ARP_GET_GIL___
    Py_XDECREF(PyObject_CallObject(this->PYO_Start, NULL));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    __ARP_RELEASE_GIL___
}

void Prog_base::CallPyStop()
{
    if (this->PYO_Stop == NULL)
        return;
    __ARP_GET_GIL___
    Py_XDECREF(PyObject_CallObject(this->PYO_Stop, NULL));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    __ARP_RELEASE_GIL___
}
void Prog_base::CallPyDispose()
{
    if (this->PYO_Dispose == NULL)
        return;
    __ARP_GET_GIL___
    Py_XDECREF(PyObject_CallObject(this->PYO_Dispose, NULL));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    __ARP_RELEASE_GIL___
}

void Prog_base::CallPyInitialize()
{
    if (this->PYO_Initialize == NULL)
        return;
    __ARP_GET_GIL___
    Py_XDECREF(PyObject_CallObject(this->PYO_Initialize, NULL));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    __ARP_RELEASE_GIL___
}

} // end of namespace PythonArp
