#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "PythonArpComponentProgramProvider.hpp"
#include "PythonArpLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Commons/Threading/Thread.hpp"
#include "Arp/System/Acf/IControllerComponent.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"

#define PY_SSIZE_T_CLEAN
#include "python3.7m/Python.h"
#include <memory>

#include "PyDataAccessService.hpp"
#include "PyForceService.hpp"
#include "PySubscriptionService.hpp"
#include "PyDeviceInfoService.hpp"
#include "PyDeviceStatusService.hpp"

//Macro for Doc generate
#define Arp_WITH_DOC_STRINGS

//switch of Service add-in
#define ENABLE_DATAACCESSSERVICE
#define ENABLE_SUBSCRIPTIONSERVICE
#define ENABLE_DEVICESTATUSSERVICE
#define ENABLE_DEVICEINFOSERVICE

//get GIL and release
#define __ARP_START_PYTHON__ {PyGILState_STATE _gstate = PyGILState_Ensure();
#define __ARP_STOP_PYTHON__ PyGILState_Release(_gstate);}

//Exception Log Title
#define PyArpErrTitle "\n\033[4;31;43m *** Exception From Python *** \033[0m\n"



namespace PythonArp
{
using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Gds::Services;
using namespace Arp::System::Rsc;
using namespace Arp::Device::Interface::Services;



//#component
class PythonArpComponent : public IControllerComponent ,public ComponentBase, public ProgramComponentBase, public Loggable<PythonArpComponent>
{
public: // typedefs

public: // construction/destruction
    PythonArpComponent(IApplication& application, const String& name);
    virtual ~PythonArpComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

    void Start() override;
    void Stop() override;

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    PythonArpComponent(const PythonArpComponent& arg) = delete;
    PythonArpComponent& operator= (const PythonArpComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    PythonArpComponentProgramProvider programProvider;

public: /* Ports
           =====
           Component ports are defined in the following way:

           //#attributes(Hidden)
           struct Ports 
           {
               //#name(NameOfPort)
               //#attributes(Input|Retain|Opc)
               Arp::boolean portField = false;
               // The GDS name is "<componentName>/NameOfPort" if the struct is declared as Hidden
               // otherwise the GDS name is "<componentName>/PORTS.NameOfPort"
           };
           
           //#port
           Ports ports;

           Create one (and only one) instance of this struct.
           Apart from this single struct instance, there must be no other Component variables declared with the #port comment.
           The only attribute that is allowed on the struct instance is "Hidden", and this is optional.
           The struct can contain as many members as necessary.
           The #name comment can be applied to each member of the struct, and is optional.
           The #name comment defines the GDS name of an individual port element. If omitted, the member variable name is used as the GDS name.
           The members of the struct can be declared with any of the attributes allowed for a Program port.
        */
public:
    bool isPyStarter = false;
    //PyThreadState *tstate;
    static PythonArpComponent* instancePointer;
    static PyMethodDef ArpFunctions[];

    //stdout - > Log::Info
    static PyObject *ArpStdOut(PyObject *self,PyObject *arg);
    static PyObject *ArpStdOut_flush(PyObject *self,PyObject *arg);
    static PyMethodDef console_method[];
    static struct PyModuleDef consoldModule;

    //errout - >Log::Error (with auto flush)
    static PyObject *ArpStdOut_err(PyObject *self,PyObject *arg);
    static PyObject *ArpStdOut_flush_err(PyObject *self,PyObject *arg);
    static PyMethodDef console_method_err[];
    static struct PyModuleDef consoldModule_err;
    Thread errOutFlushThread_ins; //used for auto-flush
    bool errFlag_2 = false;
    size_t errFlag_1 = 0;
    void errOutFlushThread(void *);
    std::unique_ptr<Arp::String> errOutBuff = std::make_unique<String>(PyArpErrTitle) ;

    
    //services
    IDataAccessService::Ptr p_IDataAccessService = nullptr;
    IForceService::Ptr p_IForceService = nullptr;
    ISubscriptionService::Ptr p_ISubscriptionService = nullptr;
    IDeviceStatusService::Ptr p_IDeviceStatusService = nullptr;
    IDeviceInfoService::Ptr p_IDeviceInfoService = nullptr;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class PythonArpComponent
inline PythonArpComponent::PythonArpComponent(IApplication& application, const String& name)
: ComponentBase(application, ::PythonArp::PythonArpLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::PythonArp::PythonArpLibrary::GetInstance().GetNamespace(), programProvider)
, errOutFlushThread_ins(this,&PythonArpComponent::errOutFlushThread)
{
    PythonArpComponent::instancePointer = this;
}

inline IComponent::Ptr PythonArpComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new PythonArpComponent(application, name));
}

} // end of namespace PythonArp
