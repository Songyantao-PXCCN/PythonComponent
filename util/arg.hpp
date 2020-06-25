#pragma once
#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include <vector>
#include "Arp/System/Core/Arp.h"

namespace PythonArp::util::argParse
{

    //int xPyArg_ParseTupleAndKeywords(PyObject *, PyObject *,const char *, char **, ...);

    int _Py_hasNoKeywords(PyObject *kwargs);
    int _Py_hadNoPositional(PyObject *args);

    int variablesParse(PyObject* PyO_variables, const char* prefix,std::vector<Arp::String>& varNames,int& offset);


    template<typename T>
    PyObject* ArpBytesBuild(const T &Variable,bool endianConvert = false);

    template<typename T>
    PyObject* ArpByteArrayBuild(const T &Variable,bool endianConvert = false);

    template<typename T>
    int ArpByteArrayOrBytesParse(PyObject* op,T &Variable,bool endianConvert = false);

}