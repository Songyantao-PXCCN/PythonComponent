#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "Prog_1arrINT10_1arrINT10.hpp"
#include "Prog_1LWToByteArray.hpp"
#include "Prog_1s_1s.hpp"
#include "Prog_2i_1i.hpp"
#include "Prog_2x1i_2x1i.hpp"
#include "Prog_2x_1x.hpp"
#include "Prog_NoPort.hpp"
#include "PythonArpLibrary.hpp"

namespace PythonArp
{

using namespace Arp::Plc::Commons::Meta;

    static const FieldDefinition PythonArp_Prog_1arrINT10_1arrINT10_PyReady("xReady", offsetof(::PythonArp::Prog_1arrINT10_1arrINT10, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_1arrINT10_1arrINT10_arrINT10_toPy("arrINT10_toPy", offsetof(::PythonArp::Prog_1arrINT10_1arrINT10, arrINT10_toPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 10 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_1arrINT10_1arrINT10_arrINT10_fromPy("arrINT10_fromPy", offsetof(::PythonArp::Prog_1arrINT10_1arrINT10, arrINT10_fromPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 10 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_1LWToByteArray_PyReady("xReady", offsetof(::PythonArp::Prog_1LWToByteArray, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_1LWToByteArray_lw_1_toPy("lw_1_toPy", offsetof(::PythonArp::Prog_1LWToByteArray, lw_1_toPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_1LWToByteArray_lw_1_fromPy("lw_1_fromPy", offsetof(::PythonArp::Prog_1LWToByteArray, lw_1_fromPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_1s_1s_PyReady("xReady", offsetof(::PythonArp::Prog_1s_1s, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_1s_1s_iStr_1_toPy("iStr_1_toPy", offsetof(::PythonArp::Prog_1s_1s, iStr_1_toPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_1s_1s_iStr_1_fromPy("iStr_1_fromPy", offsetof(::PythonArp::Prog_1s_1s, iStr_1_fromPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2i_1i_PyReady("xReady", offsetof(::PythonArp::Prog_2i_1i, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2i_1i_iINT16_1_toPy("iINT16_1_toPy", offsetof(::PythonArp::Prog_2i_1i, iINT16_1_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_2i_1i_iINT16_2_toPy("iINT16_2_toPy", offsetof(::PythonArp::Prog_2i_1i, iINT16_2_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_2i_1i_iINT16_1_fromPy("iINT16_1_fromPy", offsetof(::PythonArp::Prog_2i_1i, iINT16_1_fromPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2x1i_2x1i_PyReady("xReady", offsetof(::PythonArp::Prog_2x1i_2x1i, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2x1i_2x1i_xBool_1_toPy("xBool_1_toPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_1_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_2x1i_2x1i_xBool_2_toPy("xBool_2_toPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_2_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_2x1i_2x1i_iInt16_1_toPy("iInt16_1_toPy", offsetof(::PythonArp::Prog_2x1i_2x1i, iInt16_1_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_2x1i_2x1i_xBool_1_fromPy("xBool_1_fromPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_1_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2x1i_2x1i_xBool_2_fromPy("xBool_2_fromPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_2_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2x1i_2x1i_iInt16_1_fromPy("iInt16_1_fromPy", offsetof(::PythonArp::Prog_2x1i_2x1i, iInt16_1_fromPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2x_1x_PyReady("xReady", offsetof(::PythonArp::Prog_2x_1x, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_2x_1x_xBool_1_toPy("xBool_1_toPy", offsetof(::PythonArp::Prog_2x_1x, xBool_1_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_2x_1x_xBool_2_toPy("xBool_2_toPy", offsetof(::PythonArp::Prog_2x_1x, xBool_2_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_2x_1x_xBool_1_fromPy("xBool_1_fromPy", offsetof(::PythonArp::Prog_2x_1x, xBool_1_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_NoPort_PyReady("xReady", offsetof(::PythonArp::Prog_NoPort, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    
    void PythonArpLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {   // ProgramDefinition: PythonArp::Prog_1arrINT10_1arrINT10
                    DataType::Program, CTN<PythonArp::Prog_1arrINT10_1arrINT10>(), sizeof(::PythonArp::Prog_1arrINT10_1arrINT10), alignof(::PythonArp::Prog_1arrINT10_1arrINT10), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_1arrINT10_1arrINT10_PyReady,
                        PythonArp_Prog_1arrINT10_1arrINT10_arrINT10_toPy,
                        PythonArp_Prog_1arrINT10_1arrINT10_arrINT10_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_1LWToByteArray
                    DataType::Program, CTN<PythonArp::Prog_1LWToByteArray>(), sizeof(::PythonArp::Prog_1LWToByteArray), alignof(::PythonArp::Prog_1LWToByteArray), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_1LWToByteArray_PyReady,
                        PythonArp_Prog_1LWToByteArray_lw_1_toPy,
                        PythonArp_Prog_1LWToByteArray_lw_1_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_1s_1s
                    DataType::Program, CTN<PythonArp::Prog_1s_1s>(), sizeof(::PythonArp::Prog_1s_1s), alignof(::PythonArp::Prog_1s_1s), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_1s_1s_PyReady,
                        PythonArp_Prog_1s_1s_iStr_1_toPy,
                        PythonArp_Prog_1s_1s_iStr_1_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_2i_1i
                    DataType::Program, CTN<PythonArp::Prog_2i_1i>(), sizeof(::PythonArp::Prog_2i_1i), alignof(::PythonArp::Prog_2i_1i), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_2i_1i_PyReady,
                        PythonArp_Prog_2i_1i_iINT16_1_toPy,
                        PythonArp_Prog_2i_1i_iINT16_2_toPy,
                        PythonArp_Prog_2i_1i_iINT16_1_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_2x1i_2x1i
                    DataType::Program, CTN<PythonArp::Prog_2x1i_2x1i>(), sizeof(::PythonArp::Prog_2x1i_2x1i), alignof(::PythonArp::Prog_2x1i_2x1i), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_2x1i_2x1i_PyReady,
                        PythonArp_Prog_2x1i_2x1i_xBool_1_toPy,
                        PythonArp_Prog_2x1i_2x1i_xBool_2_toPy,
                        PythonArp_Prog_2x1i_2x1i_iInt16_1_toPy,
                        PythonArp_Prog_2x1i_2x1i_xBool_1_fromPy,
                        PythonArp_Prog_2x1i_2x1i_xBool_2_fromPy,
                        PythonArp_Prog_2x1i_2x1i_iInt16_1_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_2x_1x
                    DataType::Program, CTN<PythonArp::Prog_2x_1x>(), sizeof(::PythonArp::Prog_2x_1x), alignof(::PythonArp::Prog_2x_1x), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_2x_1x_PyReady,
                        PythonArp_Prog_2x_1x_xBool_1_toPy,
                        PythonArp_Prog_2x_1x_xBool_2_toPy,
                        PythonArp_Prog_2x_1x_xBool_1_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_NoPort
                    DataType::Program, CTN<PythonArp::Prog_NoPort>(), sizeof(::PythonArp::Prog_NoPort), alignof(::PythonArp::Prog_NoPort), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_NoPort_PyReady,
                    }
                },
            }
            // End TypeDefinitions
        );
    }

} // end of namespace PythonArp

