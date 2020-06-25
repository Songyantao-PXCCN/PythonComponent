#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "PythonArpComponent.hpp"
#include "util/arg.hpp"

namespace PythonArp
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

class Prog_base : public ProgramBase, public Loggable<Prog_base>
{
public: // construction/destruction
    Prog_base(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name);
    Prog_base(const Prog_base& arg) = delete;
    virtual ~Prog_base();
    void PythonArpProgramConstruction();
    
public: // operators
    Prog_base&  operator=(const Prog_base& arg) = delete;

public: // operations
    void   Execute() override;

private: // fields
    PythonArp::PythonArpComponent& pythonArpComponent;
    

public:
    bool _PyReady;
    PyObject *PYO_Module;
    PyObject *PYO_Start;
    PyObject *PYO_Stop;
    PyObject *PYO_Execute;
    PyObject *PYO_Initialize;
    PyObject *PYO_Dispose;

    virtual void CallPyExecute() = 0;
    void CallPyStart();
    void CallPyStop();
    void CallPyInitialize();
    void CallPyDispose();
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline Prog_base::Prog_base(PythonArp::PythonArpComponent& pythonArpComponentArg, const String& name)
: ProgramBase(name)
, pythonArpComponent(pythonArpComponentArg)
{
    this->PythonArpProgramConstruction();
}

} // end of namespace PythonArp
