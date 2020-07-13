#include "PyDeviceStatusService.hpp"
#include "util/docMacros.hpp"
#include "util/arg.hpp"
#include "PythonArpComponent.hpp"

namespace PythonArp::PyDeviceStatusService
{


#define _DEVICESTATUS_METHODDEF \
{"DeviceStatus", (PyCFunction)Wrap_DeviceStatusService_GetItems, METH_VARARGS | METH_KEYWORDS, DeviceStatusService_GetItems__doc__},
ArpPyDoc_STRVAR(DeviceStatusService_GetItems__doc__,
"Use this service to read device states");
static PyObject *Wrap_DeviceStatusService_GetItems(PyObject *, PyObject *args, PyObject *kwargs)
{
    static const char *kwList[] = {"variables", "prefix", NULL};
    PyObject *PyO_variables;
    const char *prefix = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|s",(char **) kwList, &PyO_variables, &prefix))
    {
        return NULL;
    }
    std::vector<String> varNames;
    int offset =0;
    if(PythonArp::util::arg::variablesParse(PyO_variables,prefix,varNames,offset))
    {
        return NULL;
    }
    PyObject *retValues = PyDict_New();
    PythonArpComponent::instancePointer->p_IDeviceStatusService->GetItems(
            IDeviceStatusService::GetItemsIdentifiersDelegate::create(
            [&](IRscWriteEnumerator<RscString<512>> &WriteEnumerator) {
                WriteEnumerator.BeginWrite(varNames.size());
                for (auto &varname : varNames)
                    WriteEnumerator.WriteNext(varname);
                WriteEnumerator.EndWrite();
            }),
        IDeviceStatusService::GetItemsResultDelegate::create(
            [&](IRscReadEnumerator<RscVariant<512>> &ReadEnumerator) {

                size_t valueCount = ReadEnumerator.BeginRead();
                RscVariant<512> current;
                for (size_t i = 0; i < valueCount; i++)
                {
                    ReadEnumerator.ReadNext(current);
                    PyObject *O_value = NULL;
                    O_value = PyDataAccessService::PrimitiveTypeReadHandler(current);
                    PyDict_SetItemString(retValues, varNames[i].CStr()+offset,O_value);
                    Py_XDECREF(O_value);
                }
                ReadEnumerator.EndRead();
            }));
    return retValues;
}

static PyMethodDef DeviceStatus_methods[] = {
    _DEVICESTATUS_METHODDEF
    {NULL, NULL, 0, NULL}};

int AddObject(PyObject* builtinsObject)
{
    int ret = -1;
    ret = PyModule_AddFunctions(builtinsObject, DeviceStatus_methods);
    if (ret !=0) 
    {
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Internal Error of DeviceStatusService");
    }
    return ret;
}

}