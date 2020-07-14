/* -------------------------------------------------------------------------- */
/*                                   SOURCE                                   */
/* -------------------------------------------------------------------------- */
    template <typename T,int n>
    inline constexpr int getArrayLen(T(&Array)[n])
    {
        return n;
    }

    template<typename T>
    inline PyObject* PortVar_ToPyBytes(const T &Variable)
    {
        PyObject* v = PyBytes_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyBytes_AS_STRING(v);
        *p =Variable;
        return v;
    }

    template<>
    inline PyObject* PortVar_ToPyBytes<StaticString<80>>(const StaticString<80> &Variable)
    {
        return PyBytes_FromStringAndSize(Variable.GetData(),Variable.GetLength());
    }

    template<typename T, int n>
    inline PyObject* PortVar_ToPyBytes(const T(&Variable)[n])
    {
        PyObject* v = PyBytes_FromStringAndSize(NULL, n*sizeof(T));
        T *p = (T*)PyBytes_AS_STRING(v);
        memcpy(p,&Variable,n*sizeof(T));
        return v;
    }

    template<typename T>
    inline int PyBytes_ToPortVar(PyObject* Bytes,T &Variable)
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

    template<>
    inline int PyBytes_ToPortVar<StaticString<80>>(PyObject* Bytes,StaticString<80> &Variable)
    {
        Variable = _ToIecChar(PyBytes_AS_STRING(Bytes));
        return 0;
    }

    template<typename T, int n>
    inline int PyBytes_ToPortVar(PyObject* ByteArray,T(&Variable)[n]) 
    { 
        if (n*sizeof(T) == PyBytes_GET_SIZE(ByteArray))
        {
            memcpy(&Variable,(T*)PyBytes_AS_STRING(ByteArray),n*sizeof(T));
            return 0;
        }
        else
        {
            Arp::System::Commons::Diagnostics::Logging::Log::Error("size not match !");
            return -1;
        }
    }

    template<typename T>
    inline PyObject* PortVar_ToPyByteArray(const T &Variable)
    {
        PyObject* v = PyByteArray_FromStringAndSize(NULL, sizeof(T));
        T *p = (T*)PyByteArray_AS_STRING(v);
        *p =Variable;
        return v;
    }

    template<>
    inline PyObject* PortVar_ToPyByteArray<StaticString<80>>(const StaticString<80> &Variable)
    {
        return PyByteArray_FromStringAndSize(Variable.GetData(),Variable.GetLength());
    }

    template<typename T, int n>
    inline PyObject* PortVar_ToPyByteArray(const T(&Variable)[n])
    {
        PyObject* v = PyBytes_FromStringAndSize(NULL, n*sizeof(T));
        T *p = (T*)PyBytes_AS_STRING(v);
        memcpy(p,&Variable,n*sizeof(T));
        return v;
    }

    template<typename T>
    inline int PyByteArray_ToPortVar(PyObject* ByteArray,T &Variable)
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

    template<>
    inline int PyByteArray_ToPortVar<StaticString<80>>(PyObject* ByteArray,StaticString<80> &Variable)
    {
        Variable = _ToIecChar(PyByteArray_AS_STRING(ByteArray));
        return 0;
    }

    template<typename T, int n>
    inline int PyByteArray_ToPortVar(PyObject* ByteArray,T(&Variable)[n]) 
    { 
        if (n*sizeof(T) == PyByteArray_GET_SIZE(ByteArray))
        {
            memcpy(&Variable,(T*)PyByteArray_AS_STRING(ByteArray),n*sizeof(T));
            return 0;
        }
        else
        {
            Arp::System::Commons::Diagnostics::Logging::Log::Error("size not match !");
            return -1;
        }
    }
    
    template<typename T>
    inline int PyByteArrayOrBytes_ToPortVar(PyObject* op,T &Variable)
    {
        if (PyBytes_Check(op))
        {
            return PyBytes_ToPortVar(op,Variable);
        }
        else if (PyByteArray_Check(op))
        {
            return PyByteArray_ToPortVar(op,Variable);
        }
        else
        {
            return -1;
        }
    }

/* -------------------------- PortVar_ToPyObject_impl ------------------------- */
    template<typename T>
    inline PyObject* PortVar_ToPyObject_impl(const T& sourceVar,bool ByteArray,bool ArrayElementAsByteArray)
    {
        RscType argType = GetRscType<T>();

        if (ByteArray)
        {
            return PortVar_ToPyByteArray(sourceVar);
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

    template<typename T, int n>
    inline PyObject* PortVar_ToPyObject_impl(const T(&sourceVar)[n],bool ByteArray,bool ArrayElementAsByteArray)
    {
        if (ByteArray){return PortVar_ToPyByteArray(sourceVar);}
        else{return ArrayPortVar_ToPyTuple(sourceVar,ArrayElementAsByteArray);}
    }
    template<>
    inline PyObject* PortVar_ToPyObject_impl<StaticString<80>>(const StaticString<80>& sourceVar,bool ByteArray,bool ArrayElementAsByteArray)
    {
        if (ByteArray){return PortVar_ToPyByteArray(sourceVar);}
        else {return PyUnicode_FromString(sourceVar.GetData());}
    }

/* -------------------------- PyObject_ToPortVar_impl ------------------------- */
    template<typename T>
    inline int PyObject_ToPortVar_impl(PyObject* PythonObject,T& targetVar)
    {
        RscType argType = GetRscType<T>();
        if (!PythonObject) {goto Error_PyTypeNotCorrect;}//NULL reveiced
        
        if (PyByteArray_Check(PythonObject) || PyBytes_Check(PythonObject))
        {
            return PyByteArrayOrBytes_ToPortVar(PythonObject,targetVar);
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
    
    template<>
    inline int PyObject_ToPortVar_impl<StaticString<80>>(PyObject* PythonObject,StaticString<80>& targetVar)
    {
        if (!PythonObject) {goto Error_PyTypeNotCorrect;}//NULL reveiced
        if(PyBytes_Check(PythonObject)||PyByteArray_Check(PythonObject))
        {
            return PyByteArrayOrBytes_ToPortVar(PythonObject,targetVar);
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
    
    template<typename T, int n>
    inline int PyObject_ToPortVar_impl(PyObject* PythonObject, T(&targetVar)[n])
    {
        if (!PythonObject) {goto Error_PyTypeNotCorrect;}//NULL reveiced
        
        if (PyByteArray_Check(PythonObject) || PyBytes_Check(PythonObject))
        {
            return PyByteArrayOrBytes_ToPortVar(PythonObject,targetVar);
        }
        else
        {
            int r = PyTupleOrList_ToArrayPortVar(PythonObject,targetVar);
            if (!r) {goto Done;}
            else {return r;}
        }
    Error_PyTypeNotCorrect:
        return -1;
    Done:
        return 0;
    }

/* ----------------------- ArrayPortVar_ToPyTuple ---------------------- */
    template<typename T>
    PyObject* ArrayPortVar_ToPyTuple(const T&sourceArray,bool ArrayElementAsByteArray)
    {
        int size = getArrayLen(sourceArray);
        PyObject *ret = PyTuple_New(size);
        while(size--){PyTuple_SET_ITEM(ret,size,PortVar_ToPyObject_impl(sourceArray[size],ArrayElementAsByteArray));}
        return ret;
    }

/* --------------------- PyTupleOrList_ToArrayPortVar --------------------- */
    template <typename T>
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
                PyObject_ToPortVar_impl(t_item,targetArray[tmpIndex++]);  
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

/* -------------------------------------------------------------------------- */

    template<class PortType>
    inline int PortVar_FromPyObject(PyObject* PythonObject,PortType& targetVar)
    {
        return PyObject_ToPortVar_impl(PythonObject,targetVar);
    }

    template<class PortType>
    inline PyObject* PortVar_AsPyObject(const PortType& sourceVar,bool AsByteArray,bool ArrayElementAsByteArray)
    {
        return PortVar_ToPyObject_impl(sourceVar,AsByteArray,ArrayElementAsByteArray);
    }

        // template<typename T>
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
    // template<typename T, int n>
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
