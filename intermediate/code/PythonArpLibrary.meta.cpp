#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "Prog_2i_1i.hpp"
#include "Prog_2xi_2xi.hpp"
#include "Prog_2x_1x.hpp"
#include "Prog_NoPort.hpp"
#include "PythonArpLibrary.hpp"

namespace PythonArp
{

using namespace Arp::Plc::Commons::Meta;

    void PythonArpLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {   // ProgramDefinition: PythonArp::Prog_2i_1i
                    DataType::Program, CTN<PythonArp::Prog_2i_1i>(), sizeof(::PythonArp::Prog_2i_1i), alignof(::PythonArp::Prog_2i_1i), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_2i_1i, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "iINT16_1_toPy", offsetof(::PythonArp::Prog_2i_1i, iINT16_1_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "iINT16_2_toPy", offsetof(::PythonArp::Prog_2i_1i, iINT16_2_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "iINT16_1_fromPy", offsetof(::PythonArp::Prog_2i_1i, iINT16_1_fromPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Output },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_2xi_2xi
                    DataType::Program, CTN<PythonArp::Prog_2xi_2xi>(), sizeof(::PythonArp::Prog_2xi_2xi), alignof(::PythonArp::Prog_2xi_2xi), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_2xi_2xi, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "xBool_1_toPy", offsetof(::PythonArp::Prog_2xi_2xi, xBool_1_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_2_toPy", offsetof(::PythonArp::Prog_2xi_2xi, xBool_2_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "iInt16_1_toPy", offsetof(::PythonArp::Prog_2xi_2xi, iInt16_1_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_1_fromPy", offsetof(::PythonArp::Prog_2xi_2xi, xBool_1_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "xBool_2_fromPy", offsetof(::PythonArp::Prog_2xi_2xi, xBool_2_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "iInt16_1_fromPy", offsetof(::PythonArp::Prog_2xi_2xi, iInt16_1_fromPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Output },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_2x_1x
                    DataType::Program, CTN<PythonArp::Prog_2x_1x>(), sizeof(::PythonArp::Prog_2x_1x), alignof(::PythonArp::Prog_2x_1x), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_2x_1x, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "xBool_1_toPy", offsetof(::PythonArp::Prog_2x_1x, xBool_1_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_2_toPy", offsetof(::PythonArp::Prog_2x_1x, xBool_2_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_1_fromPy", offsetof(::PythonArp::Prog_2x_1x, xBool_1_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_NoPort
                    DataType::Program, CTN<PythonArp::Prog_NoPort>(), sizeof(::PythonArp::Prog_NoPort), alignof(::PythonArp::Prog_NoPort), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_NoPort, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                    }
                },
            }
            // End TypeDefinitions
        );
    }

} // end of namespace PythonArp

