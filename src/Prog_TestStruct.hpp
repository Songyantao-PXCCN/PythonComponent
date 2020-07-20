// #pragma once
// #include "Prog_base.hpp"
// #include "util/arg.hpp"

// namespace PythonArp
// {
// //#program
// //#component(PythonArp::PythonArpComponent)
// class Prog_TestStruct : public Prog_base
// {
// public: // construction/destruction
//     Prog_TestStruct(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
//     Prog_TestStruct(const Prog_TestStruct& arg) = delete;
//     virtual ~Prog_TestStruct() = default;

// public: // operators
//     Prog_TestStruct&  operator=(const Prog_TestStruct& arg) = delete;


// public: 
//         //#port
//         //#attributes(Output)
//         //#name(xReady)
//          boolean PyReady = false;
// public:

//         //#port
//         //#attributes(Input|Retain)
//         //#name(xBool_toPy)
//         boolean Bool_toPy[3] ={};
//         //#port
//         //#attributes(Output)
//         //#name(xBool_fromPy)
//         boolean Bool_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(int8_toPy)
//         int8 int8_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(int8_fromPy)
//         int8 int8_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(int16_toPy)
//         int16 int16_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(int16_fromPy)
//         int16 int16_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(int32_toPy)
//         int32 int32_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(int32_fromPy)
//         int32 int32_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(int64_toPy)
//         int64 int64_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(int64_fromPy)
//         int64 int64_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(uint8_toPy)
//         uint8 uint8_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(uint8_fromPy)
//         uint8 uint8_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(uint16_toPy)
//         uint16 uint16_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(uint16_fromPy)
//         uint16 uint16_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(uint32_toPy)
//         uint32 uint32_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(uint32_fromPy)
//         uint32 uint32_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(uint64_toPy)
//         uint64 uint64_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(uint64_fromPy)
//         uint64 uint64_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(float32_toPy)
//         float32 float32_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(float32_fromPy)
//         float32 float32_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(float64_toPy)
//         float64 float64_toPy[3] ={};

//         //#port
//         //#attributes(Output)
//         //#name(float64_fromPy)
//         float64 float64_fromPy[3] ={};

//         //#port
//         //#attributes(Input|Retain)
//         //#name(STRING_toPy)
//         StaticString<80> STRING_toPy[3];

//         //#port
//         //#attributes(Output)
//         //#name(STRING_fromPy)
//         StaticString<80> STRING_fromPy[3];

// public:
//     void CallPyExecute() override;
// };

// ///////////////////////////////////////////////////////////////////////////////
// inline Prog_TestStruct::Prog_TestStruct(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
// {
// }
// // for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
// inline void Prog_TestStruct::CallPyExecute()
// {
//     PyReady = this->LoadScriptSuccess;
//     if (this->PYO_Execute == NULL)
//         return;
//     __ARP_GET_GIL___
//     PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"((NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN)(NN))",
//                                                                     util::arg::ArrayPortVar_ToPyTuple(Bool_toPy),util::arg::ArrayPortVar_ToPyTuple(Bool_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(int8_toPy),util::arg::ArrayPortVar_ToPyTuple(int8_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(int16_toPy),util::arg::ArrayPortVar_ToPyTuple(int16_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(int32_toPy),util::arg::ArrayPortVar_ToPyTuple(int32_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(int64_toPy),util::arg::ArrayPortVar_ToPyTuple(int64_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(uint8_toPy),util::arg::ArrayPortVar_ToPyTuple(uint8_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(uint16_toPy),util::arg::ArrayPortVar_ToPyTuple(uint16_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(uint32_toPy),util::arg::ArrayPortVar_ToPyTuple(uint32_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(uint64_toPy),util::arg::ArrayPortVar_ToPyTuple(uint64_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(float32_toPy),util::arg::ArrayPortVar_ToPyTuple(float32_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(float64_toPy),util::arg::ArrayPortVar_ToPyTuple(float64_toPy,true),
//                                                                     util::arg::ArrayPortVar_ToPyTuple(STRING_toPy),util::arg::ArrayPortVar_ToPyTuple(STRING_toPy,true)
//                                                                     );
//     if (PyErr_Occurred())
//     {
//         PyErr_Print();
//     }
//     if (ret != NULL)
//     {
//         PyObject *r1 = NULL,*r2 = NULL,*r3 = NULL,*r4 = NULL,*r5 = NULL,*r6 = NULL,*r7 = NULL,*r8 = NULL,*r9 = NULL,*r10 = NULL,*r11 = NULL,*r12 = NULL;
//         if(PyArg_ParseTuple(ret,"OOOOOOOOOOOO",&r1,&r2,&r3,&r4,&r5,&r6,&r7,&r8,&r9,&r10,&r11,&r12))
//             {
//                 util::arg::PyTupleOrList_ToArrayPortVar(r1,Bool_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r2,int8_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r3,int16_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r4,int32_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r5,int64_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r6,uint8_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r7,uint16_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r8,uint32_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r9,uint64_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r10,float32_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r11,float64_fromPy);
//                 util::arg::PyTupleOrList_ToArrayPortVar(r12,STRING_fromPy);
//             }
//     }
//     if (PyErr_Occurred()){PyErr_Print();}
//     Py_XDECREF(ret);
//     __ARP_RELEASE_GIL___
// }

// } // end of namespace PythonArp
