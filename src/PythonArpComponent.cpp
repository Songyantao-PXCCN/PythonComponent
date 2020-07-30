#include "PythonArpComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"

#include "Prog_base.hpp"

static void wait_for_thread_shutdown(void)
{
    __ARP_GET_GIL___
    _Py_IDENTIFIER(threading);
    _Py_IDENTIFIER(_shutdown);
    PyObject *result;
    PyObject *threading = _PyImport_GetModuleId(&PyId_threading);
    if (threading == NULL) {
        if (PyErr_Occurred()) {
            PyErr_WriteUnraisable(NULL);
        }
        /* else: threading not imported */
        return;
    }
    result = _PyObject_CallMethodId(threading, &PyId__shutdown, NULL);
    if (result == NULL) {
        PyErr_WriteUnraisable(threading);
    }
    else {
        Py_DECREF(result);
    }
    //Reload 'threading' module
    threading = PyImport_ReloadModule(threading);
    Py_DECREF(threading);
    Py_DECREF(threading);
    __ARP_RELEASE_GIL___
}

namespace PythonArp
{
    
    PythonArpComponent *PythonArpComponent::instancePointer = nullptr;

    PyMODINIT_FUNC PyInit_ArpConsoleSupport(void)
    {
        return PyModule_Create(&PythonArpComponent::consoldModule);
    }
    PyMODINIT_FUNC PyInit_ArpConsoleSupport_err(void)
    {
        return PyModule_Create(&PythonArpComponent::consoldModule_err);
    }

    void PythonArpComponent::Initialize()
    {
        // never remove next line
        ProgramComponentBase::Initialize();
        newLifeCycle = true;
        // subscribe events from the event system (Nm) here
    }

    void PythonArpComponent::LoadConfig()
    {
        // load project config here
        if (!p_IDataAccessService)
            this->p_IDataAccessService = ServiceManager::GetService<IDataAccessService>();
        //if(!p_IForceService)
        //   this->p_IForceService=ServiceManager::GetService<IForceService>();
        if(!p_ISubscriptionService)
            this->p_ISubscriptionService=ServiceManager::GetService<ISubscriptionService>();
        if(!p_IDeviceStatusService)
            this->p_IDeviceStatusService=ServiceManager::GetService<IDeviceStatusService>();
        if(!p_IDeviceInfoService)
            this->p_IDeviceInfoService=ServiceManager::GetService<IDeviceInfoService>();




        this->isPyStarter = false;
        if (Py_IsInitialized())
        {
            log.Warning("Python already initialized !");
            if (newLifeCycle)
            {
                goto ADD_MODULES;
            }
            return;
        }
        //this->tstate = NULL;

        //add built-in module of 'stdout' & 'stderr'
        PyImport_AppendInittab("ArpConsoleSupport", &PyInit_ArpConsoleSupport);
        PyImport_AppendInittab("ArpConsoleSupport_err", &PyInit_ArpConsoleSupport_err);

        //!it is danger to call sometime if a new other C++ component is added!!
        Py_Initialize();

        if (!Py_IsInitialized())
        {
            log.Fatal("can not initialize python !");
            return;
        }

        this->isPyStarter = true;//means that this component started the Py interpreter ,so this component must finalize it.

        PyEval_ReleaseThread(PyThreadState_GET()); 

ADD_MODULES:

        log.Info("Adding Modules into current interpreter");


        __ARP_GET_GIL___

        PyObject *builtins = PyImport_AddModule("builtins");

        //Register Python Functions here
        #ifdef ENABLE_DATAACCESSSERVICE
        PythonArp::PyDataAccessService::AddObject(builtins);
        #endif

        #ifdef ENABLE_SUBSCRIPTIONSERVICE
        PythonArp::PySubscriptionService::AddObject(builtins);
        #endif

        #ifdef ENABLE_DEVICESTATUSSERVICE
        PythonArp::PyDeviceStatusService::AddObject(builtins);
        #endif

        #ifdef ENABLE_DEVICEINFOSERVICE
        PythonArp::PyDeviceInfoService::AddObject(builtins);
        #endif

        #ifdef ENABLE_ARPLOG
        PythonArp::PyArpLog::AddObject(builtins);
        #endif

        
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("import ArpConsoleSupport");
        PyRun_SimpleString("import ArpConsoleSupport_err");
        PyRun_SimpleString("sys.stdout = ArpConsoleSupport");
        PyRun_SimpleString("sys.stderr = ArpConsoleSupport_err");
        PyRun_SimpleString("sys.path.append('/opt/plcnext/')");//define where to find extern module

        __ARP_RELEASE_GIL___

        newLifeCycle = false;
    }


    void PythonArpComponent::SetupConfig()
    {
        // never remove next line
        ProgramComponentBase::SetupConfig();
    }

    void PythonArpComponent::ResetConfig()
    {
        // never remove next line
        ProgramComponentBase::ResetConfig();


//if use 'RELOAD_MODE' ,then the interpreter's life will always same with Arp
#ifdef RELOAD_MODE

        //wait_for_thread_shutdown();

#else
        // implement this inverse to SetupConfig() and LoadConfig()
        if(!this->isPyStarter)
            return;
        sleep(1);
        PyGILState_Ensure();//before calling Py_Finalize(),must gain GIL first.
        if (Py_IsInitialized())
        {
            Py_Finalize();
        }
#endif
    }

    void PythonArpComponent::Start()
    {
        auto Progs = this->programProvider.GetPrograms();
        for (auto &Prog : Progs)
        {
            if (Prog_base* p = dynamic_cast<Prog_base*>(Prog.second.get()))
            {
                p->CallPyStart();
            }
        }
    }

    void PythonArpComponent::Stop()
    {
        auto Progs = this->programProvider.GetPrograms();
        for (auto &Prog : Progs)
        {
            if (Prog_base* p = dynamic_cast<Prog_base*>(Prog.second.get()))
            {
                p->CallPyStop();
            }
        }
    }


#pragma region CALLBACK OF STDOUT and ERROUT
    PyObject *PythonArpComponent::ArpStdOut(PyObject *self, PyObject *arg)
    {
        char *MsgString;
        if (!PyArg_ParseTuple(arg, "s", &MsgString))
            return NULL;
        if (strcmp(MsgString, "\n") == 0)
            Py_RETURN_NONE;
        Log::Info("{}", MsgString);
        Py_RETURN_NONE;
    }

    PyObject *PythonArpComponent::ArpStdOut_flush(PyObject *self, PyObject *arg)
    {
        Py_RETURN_NONE;
    }

    PyMethodDef PythonArpComponent::console_method[] =
        {
            {"write", ArpStdOut, METH_VARARGS, NULL},
            {"flush", ArpStdOut_flush, METH_VARARGS, NULL},
            {NULL, NULL}};

    struct PyModuleDef PythonArpComponent::consoldModule = {PyModuleDef_HEAD_INIT, "ArpConsoleSupport", NULL, -1, console_method};

    
    PyObject *PythonArpComponent::ArpStdOut_err(PyObject *self, PyObject *arg)
    {
        char *MsgString;
        if (!PyArg_ParseTuple(arg, "s", &MsgString))
            return NULL;
   
        if (instancePointer->errOutFlushThread_ins.IsRunning() or instancePointer->errFlag_2)
        {
            instancePointer->errFlag_1 ++;
        }
        else
        {
            instancePointer->errOutFlushThread_ins.Start();
            instancePointer->errFlag_2 = true;
        }
        
        instancePointer->errOutBuff->operator+=(MsgString);
        Py_RETURN_NONE;
    }

//todo 'MutexLock to protect errOutBuff'
    void PythonArpComponent::errOutFlushThread(void *)
    {
        do{
            auto tmp = errFlag_1;
            Thread::Sleep(20);
            if (errFlag_1 == tmp) break;
            else continue;
        }while(0);
        Log::Error("{}",*errOutBuff.get());
        errOutBuff->operator=(PyArpErrTitle);
        errFlag_1 = 0;
        errFlag_2 = false;
    }

    PyObject *PythonArpComponent::ArpStdOut_flush_err(PyObject *self, PyObject *arg)
    {
        Py_RETURN_NONE;
    }

    PyMethodDef PythonArpComponent::console_method_err[] =
        {
            {"write", ArpStdOut_err, METH_VARARGS, NULL},
            {"flush", ArpStdOut_flush_err, METH_VARARGS, NULL},
            {NULL, NULL}};

    struct PyModuleDef PythonArpComponent::consoldModule_err = {PyModuleDef_HEAD_INIT, "ArpConsoleSupport_err", NULL, -1, console_method_err};


#pragma endregion

} // end of namespace PythonArp
