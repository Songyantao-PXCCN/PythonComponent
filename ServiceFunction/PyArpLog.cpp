#include "PyArpLog.hpp"
#include "util/docMacros.hpp"
#include "util/arg.hpp"
#include "PythonArpComponent.hpp"
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



static PyMethodDef ArpLog_methods[] = {
    _ArpLog_Info_METHODDEF
    _ArpLog_Error_METHODDEF
    _ArpLog_Fatal_METHODDEF
    {NULL, NULL, 0, NULL}};

int AddObject(PyObject* builtinsObject)
{
    int ret = -1;
    ret = PyModule_AddFunctions(builtinsObject, ArpLog_methods);
    if (ret !=0) 
    {
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Internal Error of ArpLog");
    }
    return ret;
}

}