#include "PythonArpComponentProgramProvider.hpp"
#include "Prog_2i_1i.hpp"
#include "Prog_2xi_2xi.hpp"
#include "Prog_2x_1x.hpp"
#include "Prog_NoPort.hpp"

namespace PythonArp
{

IProgram::Ptr PythonArpComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "Prog_2i_1i")
    { 
        return std::make_shared<::PythonArp::Prog_2i_1i>(this->pythonArpComponent, programName);
    }
    if (programType == "Prog_2xi_2xi")
    { 
        return std::make_shared<::PythonArp::Prog_2xi_2xi>(this->pythonArpComponent, programName);
    }
    if (programType == "Prog_2x_1x")
    { 
        return std::make_shared<::PythonArp::Prog_2x_1x>(this->pythonArpComponent, programName);
    }
    if (programType == "Prog_NoPort")
    { 
        return std::make_shared<::PythonArp::Prog_NoPort>(this->pythonArpComponent, programName);
    }

    // else unknown program
    return nullptr;
}

} // end of namespace PythonArp
