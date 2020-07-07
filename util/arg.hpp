#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include <vector>
#include "Arp/System/Core/Arp.h"
#include "PythonArpComponent.hpp"

namespace PythonArp::util::argParse
{

    //int xPyArg_ParseTupleAndKeywords(PyObject *, PyObject *,const char *, char **, ...);

    int _Py_hasNoKeywords(PyObject *kwargs);
    int _Py_hadNoPositional(PyObject *args);

    int variablesParse(PyObject* PyO_variables, const char* prefix,std::vector<Arp::String>& varNames,int& offset);



    PyObject* createTupleFromArray(const uint64* sourceArray,size_t size);
    PyObject* createTupleFromArray(const uint32* sourceArray,size_t size);
    PyObject* createTupleFromArray(const uint16* sourceArray,size_t size);
    PyObject* createTupleFromArray(const uint8* sourceArray,size_t size);
    PyObject* createTupleFromArray(const int64* sourceArray,size_t size);
    PyObject* createTupleFromArray(const int32* sourceArray,size_t size);
    PyObject* createTupleFromArray(const int16* sourceArray,size_t size);
    PyObject* createTupleFromArray(const int8* sourceArray,size_t size);

    int parseTupleOrListToArray(PyObject* tupObj,int8* targetArray,const size_t size);
    int parseTupleOrListToArray(PyObject* tupObj,int16* targetArray,const size_t size);
    int parseTupleOrListToArray(PyObject* tupObj,int32* targetArray,const size_t size);
    int parseTupleOrListToArray(PyObject* tupObj,int64* targetArray,const size_t size);
    int parseTupleOrListToArray(PyObject* tupObj,uint8* targetArray,const size_t size);
    int parseTupleOrListToArray(PyObject* tupObj,uint16* targetArray,const size_t size);
    int parseTupleOrListToArray(PyObject* tupObj,uint32* targetArray,const size_t size);
    int parseTupleOrListToArray(PyObject* tupObj,uint64* targetArray,const size_t size);


    template<typename T>
    static T EndianConvert(const T& Variable)
    {
        T ret;
        char* ret_char =  (char*)&ret;
        char* origin_char =  (char*)&Variable;
        uint8_t size = sizeof(T);
        for(int i=0;i<size;i++)
            ret_char[i] = origin_char[size-i-1];
        return ret;
    }
    template<typename T>
    PyObject* ArpBytesBuild(const T &Variable,bool endianConvert = false)
    {
        PyObject* v = PyBytes_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyBytes_AS_STRING(v);
        *p =endianConvert?EndianConvert(Variable):Variable;
        return v;
    }
    template<typename T>
    int ArpBytesParse(PyObject* Bytes,T &Variable,bool endianConvert = false)
    {
        if (sizeof(T) == PyBytes_GET_SIZE(Bytes))
        {
            Variable =endianConvert?EndianConvert(*(T*)PyBytes_AS_STRING(Bytes)):*(T*)PyBytes_AS_STRING(Bytes);
            return 0;
        }
        else
        {
            Log::Error("size not match !");
            return -1;
        }
    }
    template<typename T>
    PyObject* ArpByteArrayBuild(const T &Variable,bool endianConvert = false)
    {
        PyObject* v = PyByteArray_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyByteArray_AS_STRING(v);
        *p =endianConvert?EndianConvert(Variable):Variable;
        return v;
    }
    template<typename T>
    int ArpByteArrayParse(PyObject* ByteArray,T &Variable,bool endianConvert = false)
    {
        if (sizeof(T) == PyByteArray_GET_SIZE(ByteArray))
        {
            Variable =endianConvert?EndianConvert(*(T*)PyByteArray_AS_STRING(ByteArray)):*(T*)PyByteArray_AS_STRING(ByteArray);
            return 0;
        }
        else
        {
            Arp::System::Commons::Diagnostics::Logging::Log::Error("size not match !");
            return -1;
        }
    }
    template<typename T>
    int ArpByteArrayOrBytesParse(PyObject* op,T &Variable,bool endianConvert = false)
    {
        if (PyBytes_Check(op))
        {
            return ArpBytesParse(op,Variable,endianConvert);
        }
        else if (PyByteArray_Check(op))
        {
            return ArpByteArrayParse(op,Variable,endianConvert);
        }
        else
        {
            return -1;
        }
    }






}