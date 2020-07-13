#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include <vector>
#include "Arp/System/Core/Arp.h"
#include "PythonArpComponent.hpp"

namespace PythonArp::util::arg
{

    //int xPyArg_ParseTupleAndKeywords(PyObject *, PyObject *,const char *, char **, ...);

    int _Py_hasNoKeywords(PyObject *kwargs);
    int _Py_hadNoPositional(PyObject *args);

    int variablesParse(PyObject* PyO_variables, const char* prefix,std::vector<Arp::String>& varNames,int& offset);


    const char* _ToIecChar(const char* source);
    const char* PyObject_ToIECString(PyObject* PythonObject);

    template <class T>
    inline constexpr int getArrayLen(T&array)
    {
        return sizeof(array) / sizeof(array[0]);
    }





    template<typename T>
    inline PyObject* PortVal_ToPyBytes(const T &Variable)
    {
        PyObject* v = PyBytes_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyBytes_AS_STRING(v);
        *p =Variable;
        return v;
    }
    template<class T, int n>
    inline PyObject* PortVal_ToPyBytes(const T(&Variable)[n])
    {
        PyObject* v = PyBytes_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyBytes_AS_STRING(v);
        memcpy(p,Variable,sizeof(T));
        return v;
    }
    inline PyObject* PortVal_ToPyBytes(const StaticString<80> &Variable)
    {
        return PyBytes_FromStringAndSize(Variable.GetData(),Variable.GetLength());
    }

    template<typename T>
    inline int PyBytes_ToPortVal(PyObject* Bytes,T &Variable)
    {
        if (sizeof(T) == PyBytes_GET_SIZE(Bytes))
        {
            T t = *(T*)PyBytes_AS_STRING(Bytes);
            memcpy(&Variable,&t,sizeof(T));
            return 0;
        }
        else
        {
            Arp::System::Commons::Diagnostics::Logging::Log::Error("size not match !");
            return -1;
        }
    }
    template<class T, int n>
    inline int PyBytes_ToPortVal(PyObject* ByteArray,T(&Variable)[n]) 
    { 
        if (sizeof(T) == PyBytes_GET_SIZE(ByteArray))
        {
            memcpy(Variable,*(T*)PyBytes_AS_STRING(ByteArray),sizeof(T));
            return 0;
        }
        else
        {
            Arp::System::Commons::Diagnostics::Logging::Log::Error("size not match !");
            return -1;
        }
    }
    inline int PyBytes_ToPortVal(PyObject* Bytes,StaticString<80> &Variable)
    {
        Variable = _ToIecChar(PyBytes_AS_STRING(Bytes));
        return 0;
    }

    template<typename T>
    inline PyObject* PortVal_ToPyByteArray(const T &Variable)
    {
        PyObject* v = PyByteArray_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyByteArray_AS_STRING(v);
        *p =Variable;
        return v;
    }
    template<class T, int n>
    inline PyObject* PortVal_ToPyByteArray(const T(&Variable)[n])
    {
        PyObject* v = PyBytes_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyBytes_AS_STRING(v);
        memcpy(p,Variable,sizeof(T));
        return v;
    }
    inline PyObject* PortVal_ToPyByteArray(const StaticString<80> &Variable)
    {
        return PyByteArray_FromStringAndSize(Variable.GetData(),Variable.GetLength());
    }


    template<typename T>
    inline int PyByteArray_ToPortVal(PyObject* ByteArray,T &Variable)
    {
        if (sizeof(T) == PyByteArray_GET_SIZE(ByteArray))
        {
            T t =(*(T*)PyByteArray_AS_STRING(ByteArray));
            memcpy(&Variable,&t,sizeof(T));
            return 0;
        }
        else
        {
            Arp::System::Commons::Diagnostics::Logging::Log::Error("size not match !");
            return -1;
        }
    }
    template<class T, int n>
    inline int PyByteArray_ToPortVal(PyObject* ByteArray,T(&Variable)[n]) 
    { 
        if (sizeof(T) == PyByteArray_GET_SIZE(ByteArray))
        {
            memcpy(Variable,*(T*)PyByteArray_AS_STRING(ByteArray),sizeof(T));
            return 0;
        }
        else
        {
            Arp::System::Commons::Diagnostics::Logging::Log::Error("size not match !");
            return -1;
        }
    }
    inline int PyByteArray_ToPortVal(PyObject* ByteArray,StaticString<80> &Variable)
    {
        Variable = _ToIecChar(PyByteArray_AS_STRING(ByteArray));
        return 0;
    }

    template<typename T>
    inline int PyByteArrayOrBytes_ToPortVal(PyObject* op,T &Variable)
    {
        if (PyBytes_Check(op))
        {
            return PyBytes_ToPortVal(op,Variable);
        }
        else if (PyByteArray_Check(op))
        {
            return PyByteArray_ToPortVal(op,Variable);
        }
        else
        {
            return -1;
        }
    }



/* -------------------------- PrimitivePortVar_ToPyObject ------------------------- */
    template<class T>
    inline PyObject* PrimitivePortVar_ToPyObject(const T& sourceVar,bool ByteArray = false)
    {
        RscType argType = GetRscType<T>();

        if (ByteArray)
        {
            // if(std::is_array<T>::value && typeid(sourceVar)==typeid(StaticString<80>)
            // {
            //     Py_RETURN_NONE;
            // }
            // else
                return PortVal_ToPyByteArray(sourceVar);
        }

        switch (argType)
        {
        case RscType::Bool:
            return PyBool_FromLong(sourceVar);
        case RscType::Int8:
        case RscType::Int16:
        case RscType::Int32:
            return PyLong_FromLong(sourceVar);
        case RscType::Int64:
            return PyLong_FromLongLong(sourceVar);
        case RscType::Uint8:
        case RscType::Uint16:
        case RscType::Uint32:
            return PyLong_FromUnsignedLong(sourceVar);
        case RscType::Uint64:
            return PyLong_FromUnsignedLongLong(sourceVar);
        case RscType::Real32:
        case RscType::Real64:
            return PyFloat_FromDouble(sourceVar);
        default:
            Py_RETURN_NONE;
        }
    }

    // template<class T, int n>
    // inline PyObject* PrimitivePortVar_ToPyObject(const T(&sourceVar)[n],bool ByteArray = false,bool ArrayElementAsByteArray = false) 
    // { 
    //     if (ByteArray){return PortVal_ToPyByteArray(sourceVar);}
    //     else{return ArrayPortVar_ToPyTuple(sourceVar,ArrayElementAsByteArray);}
    // }
    inline PyObject* PrimitivePortVar_ToPyObject(const StaticString<80>& sourceVar,bool ByteArray = false)
    {
        if (ByteArray){return PortVal_ToPyByteArray(sourceVar);}
        else {return PyUnicode_FromString(sourceVar.GetData());}
    }


/* -------------------------- PyObject_ToPrimitivePortVar ------------------------- */
    template<class T>
    inline int PyObject_ToPrimitivePortVar(PyObject* PythonObject,T& targetVar)
    {
        RscType argType = GetRscType<T>();
        if (!PythonObject) {goto Error_PyTypeNotCorrect;}//NULL reveiced
        
        if (PyByteArray_Check(PythonObject) || PyBytes_Check(PythonObject))
        {
            return PyByteArrayOrBytes_ToPortVal(PythonObject,targetVar);
        }
        switch (argType)
        {
        case RscType::Bool:
            {
                if (PyBool_Check(PythonObject)){targetVar = PyObject_IsTrue(PythonObject);goto Done;}
                else {goto Error_PyTypeNotCorrect;}
            }
        case RscType::Int8:
        case RscType::Int16:
        case RscType::Int32:
            {
                if (PyLong_Check(PythonObject)){ targetVar = PyLong_AsLong(PythonObject);goto Done;}
                else {goto Error_PyTypeNotCorrect;}
            }
        case RscType::Int64:
            {
                if (PyLong_Check(PythonObject)){ targetVar = PyLong_AsLongLong(PythonObject);goto Done;}
                else {goto Error_PyTypeNotCorrect;}
            }
        case RscType::Uint8:
        case RscType::Uint16:
        case RscType::Uint32:
            {
                if (PyLong_Check(PythonObject)){ targetVar = PyLong_AsUnsignedLong(PythonObject);goto Done;}
                else {goto Error_PyTypeNotCorrect;}
            }
        case RscType::Uint64:
            {
                if (PyLong_Check(PythonObject)){ targetVar = PyLong_AsUnsignedLongLong(PythonObject);goto Done;}
                else {goto Error_PyTypeNotCorrect;}
            }
        case RscType::Real32:
        case RscType::Real64:
            {
                if (PyFloat_Check(PythonObject)){ targetVar = PyFloat_AsDouble(PythonObject);goto Done;}
                else {goto Error_PyTypeNotCorrect;}
            }
        default:
            goto Error_NotImplemented;
        }

    Error_PyTypeNotCorrect:
        return -1;

    Error_NotImplemented:
        return -1;

    Done:
        return 0;
    }

    // template<class T, int n>
    // inline int PyObject_ToPrimitivePortVar(PyObject* PythonObject, T(&targetVar)[n]) 
    // {
    //     if (!PythonObject) {goto Error_PyTypeNotCorrect;}//NULL reveiced
        
    //     if (PyByteArray_Check(PythonObject) || PyBytes_Check(PythonObject))
    //     {
    //         return PyByteArrayOrBytes_ToPortVal(PythonObject,targetVar);
    //     }
    //     else
    //     {
    //         int r = PyTupleOrList_ToArrayPortVar(PythonObject,targetVar);
    //         if (!r) {goto Done;}
    //         else {return r;}
    //     }
    // Error_PyTypeNotCorrect:
    //     return -1;
    // Done:
    //     return 0;
    // }

    inline int PyObject_ToPrimitivePortVar(PyObject* PythonObject,StaticString<80>& targetVar)
    {
        if (!PythonObject) {goto Error_PyTypeNotCorrect;}//NULL reveiced
        if(PyBytes_Check(PythonObject)||PyByteArray_Check(PythonObject))
        {
            return PyByteArrayOrBytes_ToPortVal(PythonObject,targetVar);
        }
        else
        {
            targetVar = PyObject_ToIECString(PythonObject);
            goto Done;
        }
        
    Error_PyTypeNotCorrect:
        return -1;

    Done:
        return 0;
    }


/* ----------------------- ArrayPortVar_ToPyTuple ---------------------- */
    template<class T>
    PyObject* ArrayPortVar_ToPyTuple(const T&sourceArray,bool ArrayElementAsByteArray = false)
    {
        int size = getArrayLen(sourceArray);
        PyObject *ret = PyTuple_New(size);
        while(size--){PyTuple_SET_ITEM(ret,size,PrimitivePortVar_ToPyObject(sourceArray[size],ArrayElementAsByteArray));}
        return ret;
    }


/* --------------------- PyTupleOrList_ToArrayPortVar --------------------- */
    template <class T>
    int PyTupleOrList_ToArrayPortVar(PyObject* PythonObject,T& targetArray)
    {
        if (PythonObject && (PyTuple_Check(PythonObject)|| PyList_Check(PythonObject)))
        {
            int size = getArrayLen(targetArray);
            PyObject *t_seq, *t_item;
            if(PyObject_Size(PythonObject)!=size) {goto Error_WrongSize;}
            t_seq = PyObject_GetIter(PythonObject);
            int tmpIndex = 0;
            while ((t_item = PyIter_Next(t_seq)))
            {
                PyObject_ToPrimitivePortVar(t_item,targetArray[tmpIndex++]);  
                Py_XDECREF(t_item);
            }
            Py_XDECREF(t_seq);
            goto Done;
        }
        else{goto Error_WrongType;}

    Error_WrongType:
        return -1;

    Error_WrongSize:
        return -1;

    Done:
        return 0;
    }


    // template<class T>
    // static T EndianConvert(const T& Variable)
    // {
    //     T ret;
    //     char* ret_char =  (char*)&ret;
    //     char* origin_char =  (char*)&Variable;
    //     uint8_t size = sizeof(T);
    //     for(int i=0;i<size;i++)
    //         ret_char[i] = origin_char[size-i-1];
    //     return ret;
    // }
    // template<class T, int n>
    // static T EndianConvert(const T(&Variable)[n])
    // {
    //     T ret;
    //     char* ret_char =  (char*)&ret;
    //     char* origin_char =  (char*)Variable;
    //     uint8_t size = sizeof(T);
    //     for(int i=0;i<size;i++)
    //         ret_char[i] = origin_char[size-i-1];
    //     return ret;
    // }
}