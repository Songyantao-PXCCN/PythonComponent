#include "PyArpLog.hpp"
#include "util/docMacros.hpp"
#include "util/arg.hpp"
#include "PythonArpComponent.hpp"

#define Arp_INFO 0
#define Arp_ERROR 1
#define Arp_FATAL 2

namespace PythonArp::PyArpLog
{

#define _ArpLog_Info_METHODDEF \
{"ArpLog_Info", (PyCFunction)Wrap_ArpLog_Info, METH_VARARGS, ArpLog_Info__doc__},
ArpPyDoc_STRVAR(ArpLog_Info__doc__,
"wrap of Log::Info()");
static PyObject *Wrap_ArpLog_Info(PyObject *, PyObject *args)
{
    const char *message = NULL;
    if (!PyArg_ParseTuple(args, "s", &message))
    {
        return NULL;
    }
    Log::Info("{}",message);
    Py_RETURN_NONE;
}


#define _ArpLog_Error_METHODDEF \
{"ArpLog_Error", (PyCFunction)Wrap_ArpLog_Error, METH_VARARGS, ArpLog_Error__doc__},
ArpPyDoc_STRVAR(ArpLog_Error__doc__,
"wrap of Log::Error()");
static PyObject *Wrap_ArpLog_Error(PyObject *, PyObject *args)
{
    const char *message = NULL;
    if (!PyArg_ParseTuple(args, "s", &message))
    {
        return NULL;
    }
    Log::Error("{}",message);
    Py_RETURN_NONE;
}


#define _ArpLog_Fatal_METHODDEF \
{"ArpLog_Fatal", (PyCFunction)Wrap_ArpLog_Fatal, METH_VARARGS, ArpLog_Fatal__doc__},
ArpPyDoc_STRVAR(ArpLog_Fatal__doc__,
"wrap of Log::Fatal()");
static PyObject *Wrap_ArpLog_Fatal(PyObject *, PyObject *args)
{
    const char *message = NULL;
    if (!PyArg_ParseTuple(args, "s", &message))
    {
        return NULL;
    }
    Log::Fatal("{}",message);
    Py_RETURN_NONE;
}

#define _ArpLog_METHODDEF \
{"ArpLog", (PyCFunction)Wrap_ArpLog, METH_VARARGS|METH_KEYWORDS, ArpLog__doc__},
ArpPyDoc_STRVAR(ArpLog__doc__,
"wrap of Log");
static PyObject *Wrap_ArpLog(PyObject *, PyObject *args ,PyObject *kwargs)
{
    static const char *kwList[] = {"message", "level", NULL};
    int level = 0;
    PyObject *PYO_Message = NULL;
    PyObject *_PYO_Message = NULL;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O|i", (char**)kwList, &PYO_Message,&level))
    {
        return NULL;
    }

    _PYO_Message = PyObject_Str(PYO_Message);

    PyObject* callTuple = PyTuple_Pack(1,_PYO_Message);

    if (_PYO_Message == NULL or PyErr_Occurred())
    {
        PyErr_Print();
        Py_RETURN_NONE;
    }else
    {
        switch (level)
        {
        case Arp_INFO:
                Py_XDECREF(Wrap_ArpLog_Info(NULL,callTuple));
            break;

        case Arp_ERROR:
                Py_XDECREF(Wrap_ArpLog_Error(NULL,callTuple));
            break;

        case Arp_FATAL:
                Py_XDECREF(Wrap_ArpLog_Fatal(NULL,callTuple));
            break;

        default:
            break;
        }
        Py_XDECREF(callTuple);
        Py_XDECREF(_PYO_Message);


    }
    
    Py_RETURN_NONE;
}


static PyMethodDef ArpLog_methods[] = {
    _ArpLog_Info_METHODDEF
    _ArpLog_Error_METHODDEF
    _ArpLog_Fatal_METHODDEF
    _ArpLog_METHODDEF
    {NULL, NULL, 0, NULL}};

int AddObject(PyObject* builtinsObject)
{
    int ret = -1;
    ret = PyModule_AddFunctions(builtinsObject, ArpLog_methods);
    PyModule_AddIntMacro(builtinsObject,Arp_INFO);
    PyModule_AddIntMacro(builtinsObject,Arp_ERROR);
    PyModule_AddIntMacro(builtinsObject,Arp_FATAL);

    if (ret !=0) 
    {
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Internal Error of ArpLog");
    }
    return ret;
}

}