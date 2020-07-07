#include "PythonArpComponentProgramProvider.hpp"
#include "Prog_1arrINT10_1arrINT10.hpp"
#include "Prog_1LWToByteArray.hpp"
#include "Prog_1s_1s.hpp"
#include "Prog_2i_1i.hpp"
#include "Prog_2x1i_2x1i.hpp"
#include "Prog_2x_1x.hpp"
#include "Prog_NoPort.hpp"

namespace PythonArp
{

IProgram::Ptr PythonArpComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "Prog_1arrINT10_1arrINT10")
    { 
        return std::make_shared<::PythonArp::Prog_1arrINT10_1arrINT10>(this->pythonArpComponent, programName);
    }
    if (programType == "Prog_1LWToByteArray")
    { 
        return std::make_shared<::PythonArp::Prog_1LWToByteArray>(this->pythonArpComponent, programName);
    }
    if (programType == "Prog_1s_1s")
    { 
        return std::make_shared<::PythonArp::Prog_1s_1s>(this->pythonArpComponent, programName);
    }
    if (programType == "Prog_2i_1i")
    { 
        return std::make_shared<::PythonArp::Prog_2i_1i>(this->pythonArpComponent, programName);
    }
    if (programType == "Prog_2x1i_2x1i")
    { 
        return std::make_shared<::PythonArp::Prog_2x1i_2x1i>(this->pythonArpComponent, programName);
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
