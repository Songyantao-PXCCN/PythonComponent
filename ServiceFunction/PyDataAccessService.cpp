#include "PyDataAccessService.hpp"
#include "PythonArpComponent.hpp"

#include "util/arg.hpp"
#include "util/docMacros.hpp"

#include <list>
#include <vector>

#define GDS_RETURN_VALUES 1
#define GDS_RETURN_FAULTREASON 2
#define GDS_RETURN_DATATYPE 4
#define GDS_RETURN_DICT 8
#define GDS_TYPE_INT8 1
#define GDS_TYPE_INT16 2
#define GDS_TYPE_INT32 3
#define GDS_TYPE_INT64 4
#define GDS_TYPE_UINT8 5
#define GDS_TYPE_UINT16 6
#define GDS_TYPE_UINT32 7
#define GDS_TYPE_UINT64 8
#define GDS_TYPE_FLOAT32 9
#define GDS_TYPE_FLOAT64 10

namespace PythonArp::PyDataAccessService
{
    // //DEPARTED in future (these two function can not operate array and struct )
    // std::list<ReadItem> readVariables(const std::vector<String> &varNames)
    // {
    //     std::list<ReadItem> ret;

    //     PythonArpComponent::instancePointer->p_IDataAccessService->Read(
    //         IDataAccessService::ReadPortNamesDelegate::create(
    //             [&](IRscWriteEnumerator<RscString<512>> &WriteEnumerator) {
    //                 WriteEnumerator.BeginWrite(varNames.size());
    //                 for (auto &varname : varNames)
    //                     WriteEnumerator.WriteNext(varname);
    //                 WriteEnumerator.EndWrite();
    //             }),
    //         IDataAccessService::ReadResultDelegate::create(
    //             [&](IRscReadEnumerator<ReadItem> &ReadEnumerator) {
    //                 ret.clear();
    //                 size_t valueCount = ReadEnumerator.BeginRead();
    //                 ReadItem current;
    //                 for (size_t i = 0; i < valueCount; i++)
    //                 {
    //                     ReadEnumerator.ReadNext(current);
    //                     ret.push_back(current);
    //                 }
    //                 ReadEnumerator.EndRead();
    //             }));

    //     return ret;
    // }

    std::list<DataAccessError> writeVariables(const std::vector<WriteItem> &WriteVariables)
    {
        std::list<DataAccessError> ret;
        PythonArpComponent::instancePointer->p_IDataAccessService->Write(
            IDataAccessService::WriteDataDelegate::create([&](IRscWriteEnumerator<WriteItem> &writedataEnumerator) {
                writedataEnumerator.BeginWrite(WriteVariables.size());
                for (auto &currentItem : WriteVariables)
                    writedataEnumerator.WriteNext(currentItem);
                writedataEnumerator.EndWrite();
            }),
            IDataAccessService::WriteResultDelegate::create([&](IRscReadEnumerator<DataAccessError> &DataAccessErrorEnumerator) {
                ret.clear();
                size_t valueCount = DataAccessErrorEnumerator.BeginRead();
                DataAccessError current;
                for (size_t i = 0; i < valueCount; i++)
                {
                    DataAccessErrorEnumerator.ReadNext(current);
                    ret.push_back(current);
                }
                DataAccessErrorEnumerator.EndRead();
            }));
        return ret;
    }


    //functions for parsing RscVariant(including array and struct) to PyObject
    PyObject* StructTypeReadHandler(RscStructReader<512> reader);
    PyObject* PrimitiveTypeReadHandler(RscVariant<512> var);
    PyObject* ArrayTypeReadHandler(RscArrayReader reader);
    PyObject* AutoTypeReadHandler(RscVariant<512> var);


    PyObject* PrimitiveTypeReadHandler(RscVariant<512> var)
    {
        switch (var.GetValueType())
        {
        case RscType::Void:
            Py_INCREF(Py_None);
            return  Py_None;
        case RscType::Bool:
            return PyBool_FromLong(var.GetValue<bool>());
        case RscType::Int8:
            return PyLong_FromLong(var.GetValue<Arp::int8>());
        case RscType::Int16:
            return PyLong_FromLong(var.GetValue<Arp::int16>());
        case RscType::Int32:
            return PyLong_FromLong(var.GetValue<Arp::int32>());
        case RscType::Int64:
            return PyLong_FromLongLong(var.GetValue<Arp::int64>());
        case RscType::Uint8:
            return PyLong_FromUnsignedLong(var.GetValue<Arp::uint8>());
        case RscType::Uint16:
            return PyLong_FromUnsignedLong(var.GetValue<Arp::uint16>());
        case RscType::Uint32:
            return PyLong_FromUnsignedLong(var.GetValue<Arp::uint32>());
        case RscType::Uint64:
            return PyLong_FromUnsignedLongLong(var.GetValue<Arp::uint64>());
        case RscType::Real32:
            return PyFloat_FromDouble(var.GetValue<Arp::float32>());
        case RscType::Real64:
            return PyFloat_FromDouble(var.GetValue<Arp::float64>());
        case RscType::String:
            return PyUnicode_FromString(var.GetChars());
        default:
            Py_INCREF(Py_None);
            return Py_None;
        }
    }
    PyObject* ArrayTypeReadHandler(RscArrayReader reader)
    {
        int count = reader.GetSize();
        if (IsPrimitiveRscType(reader.GetElementType()))
        {
            PyObject* TupObj = PyTuple_New(count);
            for (int i=0;i<count;i++)
            {
                RscVariant<512> tmp;
                reader.ReadNext(tmp);
                PyTuple_SET_ITEM(TupObj,i,PrimitiveTypeReadHandler(tmp));
            }
            return TupObj;
        }
        else if (reader.GetElementType() == RscType::Array)
        {
            PyObject* TupObj = PyTuple_New(count);
            for (int i=0;i<count;i++)
            {
                PyTuple_SET_ITEM(TupObj,i,ArrayTypeReadHandler(reader.ReadNextArray()));
            }
            return TupObj;
        }
        else if (reader.GetElementType() ==RscType::Struct)
        {
            PyObject* TupObj = PyTuple_New(count);
            for (int i=0;i<count;i++)
            {
                PyTuple_SET_ITEM(TupObj,i,StructTypeReadHandler(reader.ReadNextStruct<512>()));
            }
            return TupObj;
        }
        else
        {
            Py_RETURN_NONE;
        }
        
    }
    PyObject* StructTypeReadHandler(RscStructReader<512> reader)
    {
        int count = reader.GetFieldCount();
        PyObject* TupObj = PyTuple_New(count);
        for(int i=0;i<count;i++)
        {
            RscVariant<512> tmp;
            reader.ReadNextField(tmp);
            if(IsPrimitiveRscType(tmp.GetType()))
            {
                PyTuple_SET_ITEM(TupObj,i,PrimitiveTypeReadHandler(tmp));
            }
            else if (tmp.GetType() == RscType::Array)
            {
                RscArrayReader reader_arr(tmp);
                PyTuple_SET_ITEM(TupObj,i,ArrayTypeReadHandler(reader_arr));
            }
            else if (tmp.GetType() == RscType::Struct)
            {
                RscStructReader<512> reader_struct(tmp);
                PyTuple_SET_ITEM(TupObj,i,StructTypeReadHandler(reader_struct));
            }
            else
            {
                Py_INCREF(Py_None);
                PyTuple_SET_ITEM(TupObj,i,Py_None);
            }
            
        }
        return TupObj;
    }
    PyObject* AutoTypeReadHandler(RscVariant<512> var)
    {
        if(IsPrimitiveRscType(var.GetType()))
        {
            return PrimitiveTypeReadHandler(var);
        }
        else if (var.GetType() == RscType::Array)
        {
            RscArrayReader reader_arr(var);
            return ArrayTypeReadHandler(reader_arr);
        }
        else if (var.GetType() == RscType::Struct)
        {
            RscStructReader<512> reader_struct(var);
            return StructTypeReadHandler(reader_struct);
        }
        else
        {
            Py_RETURN_NONE;
        }
    }

// /* ------------------------- DataAccessService->Read ------------------------ */
//     #define _DATAACCESSSERVICE_READ_METHODDEF \
//     {"GDS_Read", (PyCFunction)Wrap_DataAccessService_Read, METH_VARARGS | METH_KEYWORDS, DataAccessService_Read__doc__},
//     ArpPyDoc_STRVAR(DataAccessService_Read__doc__,
//     "Wrap of DataAccessService->Read,this function can read primitive type only");
//     static PyObject *Wrap_DataAccessService_Read(PyObject *, PyObject *args, PyObject *kwargs)
//     {
//         static const char *kwList[] = {"variables", "prefix", "returnType", NULL};
//         int returnType = 7;
//         PyObject  *PyO_variables;
//         const char *prefix = NULL;

//         if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|si",(char **) kwList, &PyO_variables, &prefix, &returnType))
//         {
//             return NULL;
//         }


//         bool _RETURN_VALUES = returnType & GDS_RETURN_VALUES;
//         bool _RETURN_FAULTREASON = returnType & GDS_RETURN_FAULTREASON;
//         bool _RETURN_DATATYPE = returnType & GDS_RETURN_DATATYPE;
//         bool _RETURN_DICT = returnType & GDS_RETURN_DICT;

//         if (!_RETURN_VALUES and !_RETURN_FAULTREASON and !_RETURN_DATATYPE)
//         {
//             PyErr_SetString(PyExc_TypeError, "Wrong returnType , Nothing can be return");
//             return NULL;
//         }


//         std::vector<String> varNames;
//         if(PythonArp::util::argParse::variablesParse(PyO_variables,prefix,varNames))
//         {
//             return NULL;
//         }



//         auto result = readVariables(varNames);
//         int size = result.size();

//         PyObject *retValues;
//         PyObject *retFaultReason;
//         PyObject *retDataType;


//         if (_RETURN_DICT)
//         {
//             if (_RETURN_VALUES)
//                 retValues = PyDict_New();
//             if (_RETURN_FAULTREASON)
//                 retFaultReason = PyDict_New();
//             if (_RETURN_DATATYPE)
//                 retDataType = PyDict_New();
//         }
//         else
//         {
//             if (_RETURN_VALUES)
//                 retValues = PyTuple_New(size);
//             if (_RETURN_FAULTREASON)
//                 retFaultReason = PyTuple_New(size);
//             if (_RETURN_DATATYPE)
//                 retDataType = PyTuple_New(size);
//         }

//         int index = 0;

//         for (auto &currentReadItem : result)
//         {
//             if (_RETURN_DATATYPE)
//             {   
//                 PyObject *tmp = PyUnicode_FromString(Enum<RscType>(currentReadItem.Value.GetType()).ToString().CStr());
//                 if (_RETURN_DICT)
//                 {
//                     PyDict_SetItemString(retDataType, varNames[index].CStr(), tmp);
//                     Py_XDECREF(tmp);
//                 }
//                 else
//                     PyTuple_SET_ITEM(retDataType, index, tmp);
//                 //Py_XDECREF(tmp);
//             }
//             if (_RETURN_FAULTREASON)
//             {
//                 PyObject *tmp = PyUnicode_FromString(Enum<DataAccessError>(currentReadItem.Error).ToString().CStr());
//                 if (_RETURN_DICT)
//                 {
//                     PyDict_SetItemString(retFaultReason, varNames[index].CStr(), tmp);
//                     Py_XDECREF(tmp);
//                 }
//                 else
//                     PyTuple_SET_ITEM(retFaultReason, index, tmp);
//                 //Py_XDECREF(tmp);
//             }

//             if (_RETURN_VALUES)
//             {
//                 PyObject *O_value = NULL;
//                 if (currentReadItem.Error == DataAccessError::None)
//                 {
//                     //(type >= RscType::Bool && type <= RscType::Real64) || (type >= RscType::IecTime && type <= RscType::IecTimeOfDay64);

//                     switch (currentReadItem.Value.GetValueType())
//                     {
//                     case RscType::Void: //maybe never reached in case of 'DataAccessError::None' .
//                         O_value = NULL;
//                         break;
//                     case RscType::Bool:
//                         O_value = PyBool_FromLong(currentReadItem.Value.GetValue<bool>());
//                         break;
//                     case RscType::Int8:
//                         O_value = PyLong_FromLong(currentReadItem.Value.GetValue<Arp::int8>());
//                         break;
//                     case RscType::Int16:
//                         O_value = PyLong_FromLong(currentReadItem.Value.GetValue<Arp::int16>());
//                         break;
//                     case RscType::Int32:
//                         O_value = PyLong_FromLong(currentReadItem.Value.GetValue<Arp::int32>());
//                         break;
//                     case RscType::Int64:
//                         O_value = PyLong_FromLongLong(currentReadItem.Value.GetValue<Arp::int64>());
//                         break;
//                     case RscType::Uint8:
//                         O_value = PyLong_FromUnsignedLong(currentReadItem.Value.GetValue<Arp::uint8>());
//                         break;
//                     case RscType::Uint16:
//                         O_value = PyLong_FromUnsignedLong(currentReadItem.Value.GetValue<Arp::uint16>());
//                         break;
//                     case RscType::Uint32:
//                         O_value = PyLong_FromUnsignedLong(currentReadItem.Value.GetValue<Arp::uint32>());
//                         break;
//                     case RscType::Uint64:
//                         O_value = PyLong_FromUnsignedLongLong(currentReadItem.Value.GetValue<Arp::uint64>());
//                         break;
//                     case RscType::Real32:
//                         O_value = PyFloat_FromDouble(currentReadItem.Value.GetValue<Arp::float32>());
//                         break;
//                     case RscType::Real64:
//                         O_value = PyFloat_FromDouble(currentReadItem.Value.GetValue<Arp::float64>());
//                         break;
//                     case RscType::String:
//                         O_value = PyUnicode_FromString(currentReadItem.Value.GetChars());
//                         break;

//                     //todo  Array & Struct
//                     default:
//                         O_value = NULL;
//                         break;
//                     }
//                 }
//                 else
//                 {
//                     O_value = NULL;
//                 }

//                 if (_RETURN_DICT)
//                 {
//                     if (O_value)
//                     {
//                         PyDict_SetItemString(retValues, varNames[index].CStr(),O_value);
//                         Py_XDECREF(O_value);
//                     }
//                     else
//                     {
//                         PyDict_SetItemString(retValues, varNames[index].CStr(),Py_None);
//                     }
//                 }
//                 else
//                 {
//                     if (O_value)
//                     {
//                         PyTuple_SET_ITEM(retValues, index,O_value);
//                     }else
//                     {
//                         Py_INCREF(Py_None);
//                         PyTuple_SET_ITEM(retValues, index, Py_None);
//                     }
//                 }
//             }
//             index++;
//         }

//         if (_RETURN_VALUES and _RETURN_FAULTREASON and _RETURN_DATATYPE)
//             return Py_BuildValue("NNN",retValues,retFaultReason,retDataType);
//         else if (_RETURN_VALUES and !_RETURN_FAULTREASON and ! _RETURN_DATATYPE)
//             return retValues;
//         else if (!_RETURN_VALUES and _RETURN_FAULTREASON and !_RETURN_DATATYPE)
//             return retFaultReason;
//         else if (!_RETURN_VALUES and !_RETURN_FAULTREASON and _RETURN_DATATYPE)
//             return retDataType;
//         else if (_RETURN_VALUES and _RETURN_FAULTREASON and !_RETURN_DATATYPE)
//             return Py_BuildValue("NN",retValues,retFaultReason);
//         else if (_RETURN_VALUES and !_RETURN_FAULTREASON and _RETURN_DATATYPE)
//             return Py_BuildValue("NN",retValues,retDataType);
//         else if (!_RETURN_VALUES and _RETURN_FAULTREASON and _RETURN_DATATYPE)
//             return Py_BuildValue("NN",retFaultReason,retDataType);
//         else
//             return NULL;
        
//     }
    



/* ----------------- DataAccessService->Read(array & struct) ---------------- */
    //this function can read any kind of RscVariant , but more test is needed
    //key-word arguments crash in this function need to be fixed
    #define _DATAACCESSSERVICE_READ_METHODDEF \
    {"GDS_Read", (PyCFunction)Wrap_DataAccessService_Readc, METH_VARARGS | METH_KEYWORDS, DataAccessService_Readc__doc__},
    ArpPyDoc_STRVAR(DataAccessService_Readc__doc__,
    "Warp of DataAccessService->Read,this function can read any kind of RscVariant");
    static PyObject *Wrap_DataAccessService_Readc(PyObject *, PyObject *args, PyObject *kwargs)
    {
        static const char *kwList[] = {"variables", "prefix", "returnType", NULL};
        int returnType = 7;
        PyObject *PyO_variables;
        const char *prefix = NULL;

        if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|si",(char **) kwList, &PyO_variables, &prefix, &returnType))
        {
            return NULL;
        }

        bool _RETURN_VALUES = returnType & GDS_RETURN_VALUES;
        bool _RETURN_FAULTREASON = returnType & GDS_RETURN_FAULTREASON;
        bool _RETURN_DATATYPE = returnType & GDS_RETURN_DATATYPE;
        bool _RETURN_DICT = returnType & GDS_RETURN_DICT;

        if (!_RETURN_VALUES and !_RETURN_FAULTREASON and !_RETURN_DATATYPE)
        {
            PyErr_SetString(PyExc_TypeError, "Wrong returnType , Nothing can be return");
            return NULL;
        }

        std::vector<String> varNames;
        int offset =0;
        if(PythonArp::util::arg::variablesParse(PyO_variables,prefix,varNames,offset))
        {
            return NULL;

            
        }

        // int nameOffset =0;
        // if(prefix)
        // {
        //     nameOffset = strlen(prefix);
        // }

        PyObject *retValues;
        PyObject *retFaultReason;
        PyObject *retDataType;

        if (_RETURN_DICT)
        {
            if (_RETURN_VALUES)
                retValues = PyDict_New();
            if (_RETURN_FAULTREASON)
                retFaultReason = PyDict_New();
            if (_RETURN_DATATYPE)
                retDataType = PyDict_New();
        }
        else
        {
            if (_RETURN_VALUES)
                retValues = PyTuple_New(varNames.size());
            if (_RETURN_FAULTREASON)
                retFaultReason = PyTuple_New(varNames.size());
            if (_RETURN_DATATYPE)
                retDataType = PyTuple_New(varNames.size());
        }

        PythonArpComponent::instancePointer->p_IDataAccessService->Read(
            IDataAccessService::ReadPortNamesDelegate::create(
                [&](IRscWriteEnumerator<RscString<512>> &WriteEnumerator) {
                    WriteEnumerator.BeginWrite(varNames.size());
                    for (auto &varname : varNames)
                        WriteEnumerator.WriteNext(varname);
                    WriteEnumerator.EndWrite();
                }),
            IDataAccessService::ReadResultDelegate::create(
                [&](IRscReadEnumerator<ReadItem> &ReadEnumerator) {

                    size_t valueCount = ReadEnumerator.BeginRead();
                    ReadItem current;
                    for (size_t i = 0; i < valueCount; i++)
                    {
                        ReadEnumerator.ReadNext(current);
                        if (_RETURN_DATATYPE)
                        {   
                            PyObject *tmp = PyUnicode_FromString(Enum<RscType>(current.Value.GetType()).ToString().CStr());
                            if (_RETURN_DICT)
                            {
                                PyDict_SetItemString(retDataType, varNames[i].CStr()+offset, tmp);
                                Py_XDECREF(tmp);
                            }
                            else
                                PyTuple_SET_ITEM(retDataType, i, tmp);
                        }
                        if (_RETURN_FAULTREASON)
                        {
                            PyObject *tmp = PyUnicode_FromString(Enum<DataAccessError>(current.Error).ToString().CStr());
                            if (_RETURN_DICT)
                            {
                                PyDict_SetItemString(retFaultReason, varNames[i].CStr()+offset, tmp);
                                Py_XDECREF(tmp);
                            }
                            else
                                PyTuple_SET_ITEM(retFaultReason, i, tmp);
                        }
                        if (_RETURN_VALUES)
                        {
                            PyObject *O_value = NULL;
                            if (current.Error == DataAccessError::None)
                            {
                                O_value = AutoTypeReadHandler(current.Value);
                            }
                            else
                            {
                                Py_INCREF(Py_None);
                                O_value = Py_None;
                            }

                            if(_RETURN_DICT)
                            {
                                PyDict_SetItemString(retValues, varNames[i].CStr()+offset,O_value);
                                Py_XDECREF(O_value);
                            }
                            else 
                            {
                                PyTuple_SET_ITEM(retValues, i,O_value);
                            }
                        }
                    }
                    ReadEnumerator.EndRead();
                }));



        if (_RETURN_VALUES and _RETURN_FAULTREASON and _RETURN_DATATYPE)
            return Py_BuildValue("NNN",retValues,retFaultReason,retDataType);
        else if (_RETURN_VALUES and !_RETURN_FAULTREASON and ! _RETURN_DATATYPE)
            return retValues;
        else if (!_RETURN_VALUES and _RETURN_FAULTREASON and !_RETURN_DATATYPE)
            return retFaultReason;
        else if (!_RETURN_VALUES and !_RETURN_FAULTREASON and _RETURN_DATATYPE)
            return retDataType;
        else if (_RETURN_VALUES and _RETURN_FAULTREASON and !_RETURN_DATATYPE)
            return Py_BuildValue("NN",retValues,retFaultReason);
        else if (_RETURN_VALUES and !_RETURN_FAULTREASON and _RETURN_DATATYPE)
            return Py_BuildValue("NN",retValues,retDataType);
        else if (!_RETURN_VALUES and _RETURN_FAULTREASON and _RETURN_DATATYPE)
            return Py_BuildValue("NN",retFaultReason,retDataType);
        else
            return NULL;
    }

/*
#define GDS_TYPE_INT8 1
#define GDS_TYPE_INT16 2
#define GDS_TYPE_INT32 3
#define GDS_TYPE_INT64 4
#define GDS_TYPE_UINT8 5
#define GDS_TYPE_UINT16 6
#define GDS_TYPE_UINT32 7
#define GDS_TYPE_UINT64 8
#define GDS_TYPE_FLOAT32 9
#define GDS_TYPE_FLOAT64 10
*/

static int parseForceTypeToMacro(PyObject * op)
{
    if (PyLong_CheckExact(op))
    {
        return PyLong_AsLong(op);
    }
    else if(PyUnicode_CheckExact(op))
    {
        const char* s = PyUnicode_AsUTF8(op);
             if (strcmp(s,"None")==0)  {return -1;}
        else if (strcmp(s,"Int8")==0){return GDS_TYPE_INT8;}
        else if (strcmp(s,"Int16")==0){return GDS_TYPE_INT16;}
        else if (strcmp(s,"Int32")==0){return GDS_TYPE_INT32;}
        else if (strcmp(s,"Int64")==0){return GDS_TYPE_INT64;}
        else if (strcmp(s,"Uint8")==0){return GDS_TYPE_UINT8;}
        else if (strcmp(s,"Uint16")==0){return GDS_TYPE_UINT16;}
        else if (strcmp(s,"Uint32")==0){return GDS_TYPE_UINT32;}
        else if (strcmp(s,"Uint64")==0){return GDS_TYPE_UINT64;}
        else if (strcmp(s,"Real32")==0){return GDS_TYPE_FLOAT32;}
        else if (strcmp(s,"Real64")==0){return GDS_TYPE_FLOAT64;}
        else {return -1;}
    }
    else
    {
        return -1;
    }
    
}



/* ------------------------ DataAccessService->Write ------------------------ */
    #define _DATAACCESSSERVICE_WRITE_METHODDEF \
    {"GDS_Write", (PyCFunction)Wrap_DataAccessService_Write, METH_VARARGS | METH_KEYWORDS, DataAccessService_Write__doc__},
    ArpPyDoc_STRVAR(DataAccessService_Write__doc__,
    "Warp of DataAccessService->Write,this function can write primitive type only");
    static PyObject *Wrap_DataAccessService_Write(PyObject *, PyObject *args, PyObject *kwargs)
    {
        static const char *kwList[] = {"variables", "prefix", "forceType", NULL};
        PyObject *PyO_variables, *PyO_forceType = NULL, *t_seq, *t_item;
        const char *prefix = NULL;

        if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!|sO!", (char **)kwList,&PyDict_Type,&PyO_variables, &prefix,&PyDict_Type, &PyO_forceType))
        {
            return NULL;
        }



        int count = PyDict_GET_SIZE(PyO_variables);
        PyObject *varNames = PyDict_Keys(PyO_variables);
        const char *varName;
        std::vector<WriteItem> paramWriteItems;
        paramWriteItems.reserve(count);
        for (int i = 0; i < count; i++)
        {
            PyObject *O_varName = PyList_GetItem(varNames, i);
            if (!PyUnicode_Check(O_varName)) continue;
            varName = PyUnicode_AsUTF8(O_varName);
            PyObject *PyO_value = PyDict_GetItem(PyO_variables, O_varName);
            if (PyBool_Check(PyO_value))
            {
                WriteItem current;
                current.PortName = varName;
                current.Value = (PyO_value == Py_True)?true:false;
                paramWriteItems.push_back(current);
            }

            else if (PyLong_Check(PyO_value))
            {
                WriteItem current;
                current.PortName = varName;

                if (PyO_forceType != NULL)
                {
                    PyObject *type = PyDict_GetItem(PyO_forceType, O_varName);
                    if (type != NULL )
                    {
                        switch (parseForceTypeToMacro(type))
                        {
                        case GDS_TYPE_INT8:
                            current.Value = (Arp::int8)PyLong_AsLong(PyO_value);
                            break;
                        case GDS_TYPE_INT16:
                            current.Value = (Arp::int16)PyLong_AsLong(PyO_value);
                            break;
                        case GDS_TYPE_INT32:
                            current.Value = (Arp::int32)PyLong_AsLong(PyO_value);
                            break;
                        case GDS_TYPE_INT64:
                            current.Value = (Arp::int64)PyLong_AsLongLong(PyO_value);
                            break;
                        case GDS_TYPE_UINT8:
                            current.Value = (Arp::uint8)PyLong_AsUnsignedLong(PyO_value);
                            break;
                        case GDS_TYPE_UINT16:
                            current.Value = (Arp::uint16)PyLong_AsUnsignedLong(PyO_value);
                            break;
                        case GDS_TYPE_UINT32:
                            current.Value = (Arp::uint32)PyLong_AsUnsignedLong(PyO_value);
                            break;
                        case GDS_TYPE_UINT64:
                            current.Value = (Arp::uint64)PyLong_AsUnsignedLongLong(PyO_value);
                            break;
                        default:
                            Log::Error("Wrong type is given, set to int16 by default");
                            current.Value = (Arp::int16)PyLong_AsLong(PyO_value); 
                            break;
                        }
                        //Py_XDECREF(type);
                    }
                    else
                    {
                        current.Value = (Arp::int16)PyLong_AsLong(PyO_value);
                    }
                }
                else
                {
                    current.Value = (Arp::int16)PyLong_AsLong(PyO_value);
                }
                paramWriteItems.push_back(current);
            }
            else if (PyFloat_Check(PyO_value))
            {
                WriteItem current;
                current.PortName = varName;
                if (PyO_forceType != NULL)
                {
                    PyObject *type = PyDict_GetItem(PyO_forceType, O_varName);
                    if (type != NULL)
                    {
                        switch (parseForceTypeToMacro(type))
                        {
                        case GDS_TYPE_FLOAT32:
                            current.Value = (Arp::float32)PyFloat_AsDouble(PyO_value);
                            break;
                        case GDS_TYPE_FLOAT64:
                            current.Value = (Arp::float64)PyFloat_AsDouble(PyO_value);
                            break;
                        default:
                            Log::Error("Wrong type is given, set to float32 by default");
                            current.Value = (Arp::float32)PyFloat_AsDouble(PyO_value);
                            break;
                        }
                    }
                    else
                    {
                        current.Value = (Arp::float32)PyFloat_AsDouble(PyO_value);
                    }
                }
                else
                {
                    current.Value = (Arp::float32)PyFloat_AsDouble(PyO_value);
                }
                paramWriteItems.push_back(current);
            }
            else if (PyUnicode_Check(PyO_value))
            {
                WriteItem current;
                current.PortName = varName;
                current.Value = PyUnicode_AsUTF8(PyO_value);
                paramWriteItems.push_back(current);
            }
            else
            {
                /* code */
                String err("Not support type for value : ");
                err += varName;
                PyErr_SetString(PyExc_ValueError, err.CStr());
                Py_XDECREF(varNames);
                return NULL;
            }
            //Py_XDECREF(O_varName);
        }
        Py_XDECREF(varNames);
        int offset =0;
        if (prefix != NULL)
        {   offset = strlen(prefix);
            do
            {
                String s_prefix = prefix;
                if (s_prefix.IsEmpty())
                    break;
                for (auto &item : paramWriteItems)
                    item.PortName = s_prefix + item.PortName.ToString();
            } while (0);
        }

        auto result = writeVariables(paramWriteItems);

        int size = result.size();
        PyObject *retResult = PyDict_New();
        int index = 0;

        for (auto &error : result)
        {   
            PyObject *va = PyUnicode_FromString(Enum<DataAccessError>(error).ToString().CStr());
            PyDict_SetItemString(retResult, paramWriteItems[index].PortName.CStr()+offset, va);
            Py_XDECREF(va);
            index++;
        }
        //paramWriteItems.clear();

        return retResult;
    }


/* -------------------------------------------------------------------------- */
/*                          DataAccessService_methods                         */
/* -------------------------------------------------------------------------- */
    static PyMethodDef DataAccess_methods[] = {
        _DATAACCESSSERVICE_READ_METHODDEF
        _DATAACCESSSERVICE_WRITE_METHODDEF
        {NULL, NULL, 0, NULL}};



    int AddObject(PyObject* builtinsObject)
    {
        int ret = -1;
        ret = PyModule_AddFunctions(builtinsObject, DataAccess_methods);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_RETURN_VALUES);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_RETURN_DATATYPE);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_RETURN_FAULTREASON);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_RETURN_DICT);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_INT8);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_INT16);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_INT32);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_INT64);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_UINT8);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_UINT16);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_UINT32);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_UINT64);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_FLOAT32);
        if (ret !=0) goto _ERROR;
        ret = PyModule_AddIntMacro(builtinsObject,GDS_TYPE_FLOAT64);
        if (ret !=0) goto _ERROR;
        return ret;
    _ERROR:
        Arp::System::Commons::Diagnostics::Logging::Log::Error("Internal Error of DataAccessService");
        return ret;
    }

}