#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace PythonArp
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class PythonArpComponent;

class PythonArpComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    PythonArpComponentProgramProvider(PythonArpComponent& pythonArpComponentArg);
    virtual ~PythonArpComponentProgramProvider() = default;

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

private:   // deleted methods
    PythonArpComponentProgramProvider(const PythonArpComponentProgramProvider& arg) = delete;
    PythonArpComponentProgramProvider& operator=(const PythonArpComponentProgramProvider& arg) = delete;

private: // fields
    PythonArpComponent& pythonArpComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class PythonArpComponentProgramProvider

inline PythonArpComponentProgramProvider::PythonArpComponentProgramProvider(PythonArpComponent& pythonArpComponentArg)
    : pythonArpComponent(pythonArpComponentArg)
{
}

} // end of namespace PythonArp
