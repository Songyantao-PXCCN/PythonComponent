#pragma once
#include "Prog_base.hpp"
#include "util/arg.hpp"

namespace PythonArp
{
//#program
//#component(PythonArp::PythonArpComponent)
class Prog_TestStruct1 : public Prog_base
{
public: // construction/destruction
    Prog_TestStruct1(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_TestStruct1(const Prog_TestStruct1& arg) = delete;
    virtual ~Prog_TestStruct1();

public: // operators
    Prog_TestStruct1&  operator=(const Prog_TestStruct1& arg) = delete;

public: //TypeDefine (Cpp side)

/**
    udtIN_1_t : STRUCT
        xBOOL   : BOOL;
        iINT    :  INT;
        dwDWORD : DWORD;
        sSTRING : STRING;
    END_STRUCT
    
    udtSub_t : STRUCT
        xBOOL   : BOOL;
        iINT    : ARRAY[0..9] OF INT;
    END_STRUCT
    
    udtIN_2_t : STRUCT
        iArray5 : ARRAY[0..4] OF INT;
        rArray10: ARRAY[0..9] OF REAL;
        dwArray3: ARRAY[0..2] OF DWORD;
        stSub   : udtSub_t;
    END_STRUCT
    
    udtOUT_1_t : STRUCT
        sSTRING : STRING;
        xBOOL   : BOOL;
        iINT    : INT;
    END_STRUCT
    
    udtOUT_2_t : STRUCT
        arrLWORD3: ARRAY[0..2] OF LWORD;
        arrWORD3 : ARRAY[0..2] OF WORD;
        stSub3   : ARRAY[0..2] OF udtSub_t;
    END_STRUCT
 */

/* --------------------------------- udtIN_1 -------------------------------- */
    struct udtIN_1{
        Arp::boolean        xBOOL = false;
        Arp::int16          iINT = 0;
        Arp::uint32         dwDWORD = 0;
        StaticString<80>    sSTRING;
    };

/* --------------------------------- udtSub --------------------------------- */
    struct udtSub{
        Arp::boolean          xBOOL = false;
        Arp::int16            iArray10[10] = {0};
    };

/* --------------------------------- udtIN_2 -------------------------------- */
    struct udtIN_2{
        Arp::int16          iArray5[5] = {0};
        Arp::float32        rArray10[10] ={0};
        Arp::uint32         dwArray3[3] = {0};
        udtSub              stSub;
    };

/* -------------------------------- udtOUT_1 -------------------------------- */
    struct udtOUT_1{
        StaticString<80>    sSTRING;
        Arp::boolean        xBOOL = false;
        Arp::int16          iINT = 0;
    };

/* -------------------------------- udtOUT_2 -------------------------------- */
    struct udtOUT_2{
        Arp::uint64          arrLWORD3[3] ={0};
        Arp::uint16          arrWORD3[3] = {0};
        udtSub               stSub3[3];
    };


public: 
        //#port
        //#attributes(Output)
        //#name(xReady)
        boolean PyReady = false;
public:
        //#port
        //#attributes(Input|Retain)
        //#name(STRUCT_1_toPy)
        udtIN_1 STRUCT_1_toPy ;

        //#port
        //#attributes(Input|Retain)
        //#name(STRUCT_2_toPy)
        udtIN_2 STRUCT_2_toPy ;

        //#port
        //#attributes(Output)
        //#name(STRUCT_1_fromPy)
        udtOUT_1 STRUCT_1_fromPy ;
        
        //#port
        //#attributes(Output)
        //#name(STRUCT_2_fromPy)
        udtOUT_2 STRUCT_2_fromPy ;

public:
    void CallPyExecute() override;

    void buildArgs(PyObject** udtIN_1_Obj,PyObject** udtIN_2_Obj);
    void parseObject_udtOUT_1(PyObject* udtOUT_1_obj);
    void parseObject_udtOUT_2(PyObject* udtOUT_2_obj);
    void parse_stSub3(PyObject *udtOUT_2_stSub3_obj);
};


static bool isInited = false;
//TypeDefine (Python side)
/* --------------------------------- udtIN_1 -------------------------------- */
static PyStructSequence_Field struct_udtIN_1_type_fields[] = {
//{FieldName , doc }
   {"xBOOL", ""},
   {"iINT", ""},
   {"dwDWORD", ""},
   {"sSTRING", ""},
   {0}//END_Flag
};
static PyStructSequence_Desc struct_udtIN_1_type_desc = {
   /*name*/         "udtIN_1",
   /* doc*/         "",
   /*fields*/       struct_udtIN_1_type_fields,
   /*n_in_sequence*/4
};
static PyTypeObject Struct_udtIN_1_Type;
/* --------------------------------- udtIN_2 -------------------------------- */
static PyStructSequence_Field struct_udtIN_2_type_fields[] = {
    //{FieldName , doc }
   {"iArray5", ""},
   {"rArray10", ""},
   {"dwArray3",""},
   {"stSub", ""},
   {0}//END_Flag
};
static PyStructSequence_Desc struct_udtIN_2_type_desc = {
   /*name*/         "udtIN_2",
   /* doc*/         "",
   /*fields*/       struct_udtIN_2_type_fields,
   /*n_in_sequence*/3
};
static PyTypeObject Struct_udtIN_2_Type;
/* --------------------------------- udtSub --------------------------------- */
static PyStructSequence_Field struct_udtSub_type_fields[] = {
    //{FieldName , doc }
   {"xBOOL", ""},
   {"iArray10", ""},
   {0}//END_Flag
};
static PyStructSequence_Desc struct_udtSub_type_desc = {
   /*name*/         "udtSub",
   /* doc*/         "",
   /*fields*/       struct_udtSub_type_fields,
   /*n_in_sequence*/2
};
static PyTypeObject Struct_udtSub_Type;


///////////////////////////////////////////////////////////////////////////////
//Here we create the Types in Constructor
inline Prog_TestStruct1::Prog_TestStruct1(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name): Prog_base(pythonArpComponentArg,name)
{
    __ARP_GET_GIL___
    //create Types
    if (not isInited)//prevent other instance execute 'PyStructSequence_InitType' again.
    {
        PyStructSequence_InitType(&Struct_udtIN_1_Type,&struct_udtIN_1_type_desc);
        PyStructSequence_InitType(&Struct_udtIN_2_Type,&struct_udtIN_2_type_desc);
        PyStructSequence_InitType(&Struct_udtSub_Type,&struct_udtSub_type_desc);
        Py_INCREF((PyObject *) &Struct_udtIN_1_Type);
        Py_INCREF((PyObject *) &Struct_udtIN_2_Type);
        Py_INCREF((PyObject *) &Struct_udtSub_Type);
        isInited = true;
    }
    __ARP_RELEASE_GIL___
}

inline Prog_TestStruct1::~Prog_TestStruct1()
{
    isInited = false;
}

// for more information : https://docs.python.org/3/c-api/arg.html and  https://docs.python.org/3/c-api/object.html
inline void Prog_TestStruct1::CallPyExecute()
{
    PyReady = this->LoadScriptSuccess;
    if (this->PYO_Execute == NULL)
        return;
    __ARP_GET_GIL___

    //Create Objects which represent the Struct Port from Cpp to Python
    PyObject* udtIN_1_Obj = NULL;
    PyObject* udtIN_2_Obj = NULL;
    buildArgs(&udtIN_1_Obj,&udtIN_2_Obj);

    PyObject * ret = PyObject_CallFunction(this->PYO_Execute,"(NN)",udtIN_1_Obj,udtIN_2_Obj);
    if (PyErr_Occurred())
    {
        PyErr_Print();
    }
    if (ret != NULL)
    {
        if(PyTuple_Check(ret))
        {
            PyObject *udtOUT_1_obj = NULL;
            PyObject *udtOUT_2_obj = NULL;

            if(PyArg_ParseTuple(ret,"OO",&udtOUT_1_obj,&udtOUT_2_obj))
            {
                parseObject_udtOUT_1(udtOUT_1_obj);
                parseObject_udtOUT_2(udtOUT_2_obj);
            }
            
        }
    }
    if (PyErr_Occurred()){PyErr_Print();}
    Py_XDECREF(ret);
    __ARP_RELEASE_GIL___
}



inline void Prog_TestStruct1::buildArgs(PyObject** udtIN_1_Obj,PyObject** udtIN_2_Obj)
{
    *udtIN_1_Obj = PyStructSequence_New(&Struct_udtIN_1_Type);
    PyStructSequence_SetItem(*udtIN_1_Obj,0,util::arg::PortVar_AsPyObject(STRUCT_1_toPy.xBOOL));
    PyStructSequence_SetItem(*udtIN_1_Obj,1,util::arg::PortVar_AsPyObject(STRUCT_1_toPy.iINT));
    PyStructSequence_SetItem(*udtIN_1_Obj,2,util::arg::PortVar_AsPyObject(STRUCT_1_toPy.dwDWORD,true));//as ByteArray
    PyStructSequence_SetItem(*udtIN_1_Obj,3,util::arg::PortVar_AsPyObject(STRUCT_1_toPy.sSTRING));

    PyObject* udtSub_Obj = PyStructSequence_New(&Struct_udtSub_Type);
    PyStructSequence_SetItem(udtSub_Obj,0,util::arg::PortVar_AsPyObject(STRUCT_2_toPy.stSub.xBOOL));
    PyStructSequence_SetItem(udtSub_Obj,1,util::arg::PortVar_AsPyObject(STRUCT_2_toPy.stSub.iArray10));

    *udtIN_2_Obj = PyStructSequence_New(&Struct_udtIN_2_Type);
    PyStructSequence_SetItem(*udtIN_2_Obj,0,util::arg::PortVar_AsPyObject(STRUCT_2_toPy.iArray5));
    PyStructSequence_SetItem(*udtIN_2_Obj,1,util::arg::PortVar_AsPyObject(STRUCT_2_toPy.rArray10));
    PyStructSequence_SetItem(*udtIN_2_Obj,2,util::arg::PortVar_AsPyObject(STRUCT_2_toPy.dwArray3,true));//Element as ByteArray
    PyStructSequence_SetItem(*udtIN_2_Obj,3,udtSub_Obj);
}

inline void Prog_TestStruct1::parseObject_udtOUT_1(PyObject* udtOUT_1_obj)
{
    PyObject* udtOUT_1_sSTRING_obj = PyObject_GetAttrString(udtOUT_1_obj,"sSTRING");
    PyObject* udtOUT_1_xBOOL_obj = PyObject_GetAttrString(udtOUT_1_obj,"xBOOL");
    PyObject* udtOUT_1_iINT_obj = PyObject_GetAttrString(udtOUT_1_obj,"iINT");
    
    util::arg::PortVar_FromPyObject(udtOUT_1_sSTRING_obj,STRUCT_1_fromPy.sSTRING);
    util::arg::PortVar_FromPyObject(udtOUT_1_xBOOL_obj,STRUCT_1_fromPy.xBOOL);
    util::arg::PortVar_FromPyObject(udtOUT_1_iINT_obj,STRUCT_1_fromPy.iINT);
 

    if (PyErr_Occurred()){PyErr_Clear();}
    Py_XDECREF(udtOUT_1_sSTRING_obj);
    Py_XDECREF(udtOUT_1_xBOOL_obj);
    Py_XDECREF(udtOUT_1_iINT_obj);
}

inline void Prog_TestStruct1::parseObject_udtOUT_2(PyObject* udtOUT_2_obj)
{
    PyObject* udtOUT_2_arrLWORD3_obj = PyObject_GetAttrString(udtOUT_2_obj,"arrLWORD3");
    PyObject* udtOUT_2_arrWORD3_obj = PyObject_GetAttrString(udtOUT_2_obj,"arrWORD3");
    PyObject* udtOUT_2_stSub3_obj = PyObject_GetAttrString(udtOUT_2_obj,"stSub3");


    util::arg::PortVar_FromPyObject(udtOUT_2_arrLWORD3_obj,STRUCT_2_fromPy.arrLWORD3);
    util::arg::PortVar_FromPyObject(udtOUT_2_arrWORD3_obj,STRUCT_2_fromPy.arrWORD3);
    parse_stSub3(udtOUT_2_stSub3_obj);
    

    if (PyErr_Occurred()){PyErr_Clear();}
    Py_XDECREF(udtOUT_2_arrLWORD3_obj);
    Py_XDECREF(udtOUT_2_arrWORD3_obj);
    Py_XDECREF(udtOUT_2_stSub3_obj);
}

inline void Prog_TestStruct1::parse_stSub3(PyObject *udtOUT_2_stSub3_obj)
{
    PyObject *t_seq, *t_item;
    size_t tmpIndex = 0;
    if (PyTuple_Check(udtOUT_2_stSub3_obj) or PyList_Check(udtOUT_2_stSub3_obj))
    {
        if(PyObject_Size(udtOUT_2_stSub3_obj)!=3) {return;}//size not match
        t_seq = PyObject_GetIter(udtOUT_2_stSub3_obj);
        while ((t_item = PyIter_Next(t_seq)))
        {
            PyObject* current_udtOUT_2_stSub3_xBOOL_obj = PyObject_GetAttrString(t_item,"xBOOL");
            PyObject* current_udtOUT_2_stSub3_iArray10_obj = PyObject_GetAttrString(t_item,"iArray10");

            util::arg::PortVar_FromPyObject(current_udtOUT_2_stSub3_xBOOL_obj,STRUCT_2_fromPy.stSub3[tmpIndex].xBOOL);
            util::arg::PortVar_FromPyObject(current_udtOUT_2_stSub3_iArray10_obj , STRUCT_2_fromPy.stSub3[tmpIndex].iArray10);
            
            if (PyErr_Occurred()){PyErr_Clear();}
            Py_XDECREF(current_udtOUT_2_stSub3_xBOOL_obj);
            Py_XDECREF(current_udtOUT_2_stSub3_iArray10_obj);
            Py_XDECREF(t_item);
            tmpIndex++;
        }
        Py_XDECREF(t_seq);
        return;
    }
    return;
}

} // end of namespace PythonArp
