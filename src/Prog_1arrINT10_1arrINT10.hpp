#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"

namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_1arrINT10_1arrINT10 : public Prog_base
{
public: // construction/destruction
    Prog_1arrINT10_1arrINT10(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_1arrINT10_1arrINT10(const Prog_1arrINT10_1arrINT10& arg) = delete;
    virtual ~Prog_1arrINT10_1arrINT10() = default;

public: // operators
    Prog_1arrINT10_1arrINT10&  operator=(const Prog_1arrINT10_1arrINT10& arg) = delete;


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
         boolean PyReady = false;
public:
        //#port
        //#attributes(Input|Retain)
        //#name(arrINT10_toPy)
        int16 arrINT10_toPy[10];    

        //#port
        //#attributes(Output)
        //#name(arrINT10_fromPy)
        int16 arrINT10_fromPy[10]; 

public:
    void CallPyExecute() override;
};

///////////////////////////////////////////////////////////////////////////////
inline Prog_1arrINT10_1arrINT10::Prog_1arrINT10_1arrINT10(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
}

static inline PyObject* createTupleFromArray(const int16* sourceArray,const size_t size)
    {
        PyObject* ret = PyTuple_New(size);
        for(size_t i=0;i<size;i++)
        {
            PyTuple_SetItem(ret,i,PyLong_FromLong(sourceArray[i]));
        }
        return ret;
    }

static int parseTupleOrListToArray(PyObject* tupObj,int16* targetArray,const size_t size)
    {
        PyObject *t_seq, *t_item;
        size_t tmpIndex = 0;
        if (PyTuple_Check(tupObj) or PyList_Check(tupObj))
        {
            if(PyObject_Size(tupObj)!=size) 
                return -1;

            t_seq = PyObject_GetIter(tupObj);
            while ((t_item = PyIter_Next(t_seq)))
            {
                targetArray[tmpIndex++]= PyLong_AsLong(t_item);
                Py_XDECREF(t_item);
            }
            Py_XDECREF(t_seq);
            return 0;
        }
        return -1;
    }


// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_1arrINT10_1arrINT10::CallPyExecute()
{
    PyReady = this->_PyReady;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_START_PYTHON__
    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"(N)",createTupleFromArray(arrINT10_toPy,10));
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        parseTupleOrListToArray(ret,arrINT10_fromPy,10);
    }
    Py_XDECREF(ret);
    __ARP_STOP_PYTHON__
}

} // end of namespace PythonArp
