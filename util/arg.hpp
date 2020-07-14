#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include "PythonArpComponent.hpp"

namespace PythonArp::util::arg
{
    int _Py_hasNoKeywords(PyObject *kwargs);
    int _Py_hadNoPositional(PyObject *args);
    int variablesParse(PyObject* PyO_variables, const char* prefix,std::vector<Arp::String>& varNames,int& offset);

    const char* _ToIecChar(const char* source);
    const char* PyObject_ToIECString(PyObject* PythonObject);

    template <typename T,int n>
    constexpr int getArrayLen(T(&Array)[n]);
    template<typename T>
    PyObject* PortVar_ToPyBytes(const T &Variable);
    template<typename T, int n>
    PyObject* PortVar_ToPyBytes(const T(&Variable)[n]);
    template<typename T>
    int PyBytes_ToPortVar(PyObject* Bytes,T &Variable);
    template<typename T, int n>
    int PyBytes_ToPortVar(PyObject* ByteArray,T(&Variable)[n]) ;
    template<typename T, int n>
    PyObject* PortVar_ToPyByteArray(const T(&Variable)[n]);
    template<typename T>
    PyObject* PortVar_ToPyByteArray(const T &Variable);
    template<typename T>
    int PyByteArray_ToPortVar(PyObject* ByteArray,T &Variable);
    template<typename T, int n>
    int PyByteArray_ToPortVar(PyObject* ByteArray,T(&Variable)[n]);
    template<typename T>
    int PyByteArrayOrBytes_ToPortVar(PyObject* op,T &Variable);
    template<typename T>
    PyObject* ArrayPortVar_ToPyTuple(const T&sourceArray,bool ArrayElementAsByteArray = false);
    template<typename T>
    PyObject* PortVar_ToPyObject_impl(const T& sourceVar,bool ByteArray = false,bool ArrayElementAsByteArray = false);
    template<typename T, int n>
    PyObject* PortVar_ToPyObject_impl(const T(&sourceVar)[n],bool ByteArray = false,bool ArrayElementAsByteArray = false) ;
    template <typename T>
    int PyTupleOrList_ToArrayPortVar(PyObject* PythonObject,T& targetArray);
    template<typename T>
    int PyObject_ToPortVar_impl(PyObject* PythonObject,T& targetVar);
    template<typename T, int n>
    int PyObject_ToPortVar_impl(PyObject* PythonObject, T(&targetVar)[n]);

/* -------------------------------------------------------------------------- */

    //For Primitive type and Array Type
    template<class PortType>
    int PortVar_FromPyObject(PyObject* PythonObject,PortType& targetVar);

    //For Primitive type and Array Type
    template<class PortType>
    PyObject* PortVar_AsPyObject(const PortType& sourceVar,bool AsByteArray = false,bool ArrayElementAsByteArray = false);

/* -------------------------------------------------------------------------- */
#include "arg.tpp"
}