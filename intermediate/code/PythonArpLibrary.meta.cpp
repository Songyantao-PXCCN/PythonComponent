#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "Prog_1arrINT10_1arrINT10.hpp"
#include "Prog_1LWToByteArray.hpp"
#include "Prog_1s_1s.hpp"
#include "Prog_2i_1i.hpp"
#include "Prog_2x1i_2x1i.hpp"
#include "Prog_2x_1x.hpp"
#include "Prog_NoPort.hpp"
#include "Prog_TestArray.hpp"
#include "Prog_TestPrimitive.hpp"
#include "Prog_TestStruct1.hpp"
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
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtIN_1
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtIN_1>(), sizeof(::PythonArp::Prog_TestStruct1::udtIN_1), alignof(::PythonArp::Prog_TestStruct1::udtIN_1), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xBOOL", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, xBOOL), DataType::Boolean, "", sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "iINT", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, iINT), DataType::Int16, "", sizeof(Arp::int16), alignof(Arp::int16), {  }, StandardAttribute::None },
                        { "dwDWORD", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, dwDWORD), DataType::UInt32, "", sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::None },
                        { "sSTRING", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, sSTRING), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtIN_2
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtIN_2>(), sizeof(::PythonArp::Prog_TestStruct1::udtIN_2), alignof(::PythonArp::Prog_TestStruct1::udtIN_2), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "iArray5", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, iArray5), DataType::Int16 | DataType::Array, "", sizeof(Arp::int16), alignof(Arp::int16), { 5 }, StandardAttribute::None },
                        { "rArray10", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, rArray10), DataType::Float32 | DataType::Array, "", sizeof(Arp::float32), alignof(Arp::float32), { 10 }, StandardAttribute::None },
                        { "dwArray3", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, dwArray3), DataType::UInt32 | DataType::Array, "", sizeof(Arp::uint32), alignof(Arp::uint32), { 3 }, StandardAttribute::None },
                        { "stSub", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, stSub), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtSub>(), sizeof(PythonArp::Prog_TestStruct1::udtSub), alignof(PythonArp::Prog_TestStruct1::udtSub), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtOUT_1
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_1>(), sizeof(::PythonArp::Prog_TestStruct1::udtOUT_1), alignof(::PythonArp::Prog_TestStruct1::udtOUT_1), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "sSTRING", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_1, sSTRING), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::None },
                        { "xBOOL", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_1, xBOOL), DataType::Boolean, "", sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "iINT", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_1, iINT), DataType::Int16, "", sizeof(Arp::int16), alignof(Arp::int16), {  }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtOUT_2
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_2>(), sizeof(::PythonArp::Prog_TestStruct1::udtOUT_2), alignof(::PythonArp::Prog_TestStruct1::udtOUT_2), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "arrLWORD3", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_2, arrLWORD3), DataType::UInt64 | DataType::Array, "", sizeof(Arp::uint64), alignof(Arp::uint64), { 3 }, StandardAttribute::None },
                        { "arrWORD3", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_2, arrWORD3), DataType::UInt16 | DataType::Array, "", sizeof(Arp::uint16), alignof(Arp::uint16), { 3 }, StandardAttribute::None },
                        { "stSub3", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_2, stSub3), DataType::Struct | DataType::Array, CTN<PythonArp::Prog_TestStruct1::udtSub>(), sizeof(PythonArp::Prog_TestStruct1::udtSub), alignof(PythonArp::Prog_TestStruct1::udtSub), { 3 }, StandardAttribute::None },
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtSub
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtSub>(), sizeof(::PythonArp::Prog_TestStruct1::udtSub), alignof(::PythonArp::Prog_TestStruct1::udtSub), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xBOOL", offsetof(::PythonArp::Prog_TestStruct1::udtSub, xBOOL), DataType::Boolean, "", sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None },
                        { "iArray10", offsetof(::PythonArp::Prog_TestStruct1::udtSub, iArray10), DataType::Int16 | DataType::Array, "", sizeof(Arp::int16), alignof(Arp::int16), { 10 }, StandardAttribute::None },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_1arrINT10_1arrINT10
                    DataType::Program, CTN<PythonArp::Prog_1arrINT10_1arrINT10>(), sizeof(::PythonArp::Prog_1arrINT10_1arrINT10), alignof(::PythonArp::Prog_1arrINT10_1arrINT10), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_1arrINT10_1arrINT10, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "arrINT10_toPy", offsetof(::PythonArp::Prog_1arrINT10_1arrINT10, arrINT10_toPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 10 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "arrINT10_fromPy", offsetof(::PythonArp::Prog_1arrINT10_1arrINT10, arrINT10_fromPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 10 }, StandardAttribute::Output },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_1LWToByteArray
                    DataType::Program, CTN<PythonArp::Prog_1LWToByteArray>(), sizeof(::PythonArp::Prog_1LWToByteArray), alignof(::PythonArp::Prog_1LWToByteArray), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_1LWToByteArray, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "lw_1_toPy", offsetof(::PythonArp::Prog_1LWToByteArray, lw_1_toPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "lw_1_fromPy", offsetof(::PythonArp::Prog_1LWToByteArray, lw_1_fromPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Output },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_1s_1s
                    DataType::Program, CTN<PythonArp::Prog_1s_1s>(), sizeof(::PythonArp::Prog_1s_1s), alignof(::PythonArp::Prog_1s_1s), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_1s_1s, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "iStr_1_toPy", offsetof(::PythonArp::Prog_1s_1s, iStr_1_toPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "iStr_1_fromPy", offsetof(::PythonArp::Prog_1s_1s, iStr_1_fromPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Output },
                    }
                },
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
                {   // ProgramDefinition: PythonArp::Prog_2x1i_2x1i
                    DataType::Program, CTN<PythonArp::Prog_2x1i_2x1i>(), sizeof(::PythonArp::Prog_2x1i_2x1i), alignof(::PythonArp::Prog_2x1i_2x1i), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_2x1i_2x1i, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "xBool_1_toPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_1_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_2_toPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_2_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "iInt16_1_toPy", offsetof(::PythonArp::Prog_2x1i_2x1i, iInt16_1_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_1_fromPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_1_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "xBool_2_fromPy", offsetof(::PythonArp::Prog_2x1i_2x1i, xBool_2_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "iInt16_1_fromPy", offsetof(::PythonArp::Prog_2x1i_2x1i, iInt16_1_fromPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Output },
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
                {   // ProgramDefinition: PythonArp::Prog_TestArray
                    DataType::Program, CTN<PythonArp::Prog_TestArray>(), sizeof(::PythonArp::Prog_TestArray), alignof(::PythonArp::Prog_TestArray), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_TestArray, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "xBool_toPy", offsetof(::PythonArp::Prog_TestArray, Bool_toPy), DataType::Boolean | DataType::Array, "", sizeof(boolean), alignof(boolean), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_fromPy", offsetof(::PythonArp::Prog_TestArray, Bool_fromPy), DataType::Boolean | DataType::Array, "", sizeof(boolean), alignof(boolean), { 3 }, StandardAttribute::Output },
                        { "int8_toPy", offsetof(::PythonArp::Prog_TestArray, int8_toPy), DataType::Int8 | DataType::Array, "", sizeof(int8), alignof(int8), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int8_fromPy", offsetof(::PythonArp::Prog_TestArray, int8_fromPy), DataType::Int8 | DataType::Array, "", sizeof(int8), alignof(int8), { 3 }, StandardAttribute::Output },
                        { "int16_toPy", offsetof(::PythonArp::Prog_TestArray, int16_toPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int16_fromPy", offsetof(::PythonArp::Prog_TestArray, int16_fromPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 3 }, StandardAttribute::Output },
                        { "int32_toPy", offsetof(::PythonArp::Prog_TestArray, int32_toPy), DataType::Int32 | DataType::Array, "", sizeof(int32), alignof(int32), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int32_fromPy", offsetof(::PythonArp::Prog_TestArray, int32_fromPy), DataType::Int32 | DataType::Array, "", sizeof(int32), alignof(int32), { 3 }, StandardAttribute::Output },
                        { "int64_toPy", offsetof(::PythonArp::Prog_TestArray, int64_toPy), DataType::Int64 | DataType::Array, "", sizeof(int64), alignof(int64), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int64_fromPy", offsetof(::PythonArp::Prog_TestArray, int64_fromPy), DataType::Int64 | DataType::Array, "", sizeof(int64), alignof(int64), { 3 }, StandardAttribute::Output },
                        { "uint8_toPy", offsetof(::PythonArp::Prog_TestArray, uint8_toPy), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint8_fromPy", offsetof(::PythonArp::Prog_TestArray, uint8_fromPy), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 3 }, StandardAttribute::Output },
                        { "uint16_toPy", offsetof(::PythonArp::Prog_TestArray, uint16_toPy), DataType::UInt16 | DataType::Array, "", sizeof(uint16), alignof(uint16), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint16_fromPy", offsetof(::PythonArp::Prog_TestArray, uint16_fromPy), DataType::UInt16 | DataType::Array, "", sizeof(uint16), alignof(uint16), { 3 }, StandardAttribute::Output },
                        { "uint32_toPy", offsetof(::PythonArp::Prog_TestArray, uint32_toPy), DataType::UInt32 | DataType::Array, "", sizeof(uint32), alignof(uint32), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint32_fromPy", offsetof(::PythonArp::Prog_TestArray, uint32_fromPy), DataType::UInt32 | DataType::Array, "", sizeof(uint32), alignof(uint32), { 3 }, StandardAttribute::Output },
                        { "uint64_toPy", offsetof(::PythonArp::Prog_TestArray, uint64_toPy), DataType::UInt64 | DataType::Array, "", sizeof(uint64), alignof(uint64), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint64_fromPy", offsetof(::PythonArp::Prog_TestArray, uint64_fromPy), DataType::UInt64 | DataType::Array, "", sizeof(uint64), alignof(uint64), { 3 }, StandardAttribute::Output },
                        { "float32_toPy", offsetof(::PythonArp::Prog_TestArray, float32_toPy), DataType::Float32 | DataType::Array, "", sizeof(float32), alignof(float32), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "float32_fromPy", offsetof(::PythonArp::Prog_TestArray, float32_fromPy), DataType::Float32 | DataType::Array, "", sizeof(float32), alignof(float32), { 3 }, StandardAttribute::Output },
                        { "float64_toPy", offsetof(::PythonArp::Prog_TestArray, float64_toPy), DataType::Float64 | DataType::Array, "", sizeof(float64), alignof(float64), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "float64_fromPy", offsetof(::PythonArp::Prog_TestArray, float64_fromPy), DataType::Float64 | DataType::Array, "", sizeof(float64), alignof(float64), { 3 }, StandardAttribute::Output },
                        { "STRING_toPy", offsetof(::PythonArp::Prog_TestArray, STRING_toPy), DataType::StaticString | DataType::Array, "", sizeof(StaticString<80>), alignof(StaticString<80>), { 3 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "STRING_fromPy", offsetof(::PythonArp::Prog_TestArray, STRING_fromPy), DataType::StaticString | DataType::Array, "", sizeof(StaticString<80>), alignof(StaticString<80>), { 3 }, StandardAttribute::Output },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_TestPrimitive
                    DataType::Program, CTN<PythonArp::Prog_TestPrimitive>(), sizeof(::PythonArp::Prog_TestPrimitive), alignof(::PythonArp::Prog_TestPrimitive), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_TestPrimitive, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "xBool_toPy", offsetof(::PythonArp::Prog_TestPrimitive, Bool_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "xBool_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, Bool_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "int8_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int8_toPy), DataType::Int8, "", sizeof(int8), alignof(int8), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int8_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int8_fromPy), DataType::Int8, "", sizeof(int8), alignof(int8), {  }, StandardAttribute::Output },
                        { "int16_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int16_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int16_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int16_fromPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Output },
                        { "int32_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int32_toPy), DataType::Int32, "", sizeof(int32), alignof(int32), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int32_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int32_fromPy), DataType::Int32, "", sizeof(int32), alignof(int32), {  }, StandardAttribute::Output },
                        { "int64_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int64_toPy), DataType::Int64, "", sizeof(int64), alignof(int64), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "int64_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int64_fromPy), DataType::Int64, "", sizeof(int64), alignof(int64), {  }, StandardAttribute::Output },
                        { "uint8_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint8_toPy), DataType::UInt8, "", sizeof(uint8), alignof(uint8), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint8_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint8_fromPy), DataType::UInt8, "", sizeof(uint8), alignof(uint8), {  }, StandardAttribute::Output },
                        { "uint16_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint16_toPy), DataType::UInt16, "", sizeof(uint16), alignof(uint16), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint16_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint16_fromPy), DataType::UInt16, "", sizeof(uint16), alignof(uint16), {  }, StandardAttribute::Output },
                        { "uint32_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint32_toPy), DataType::UInt32, "", sizeof(uint32), alignof(uint32), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint32_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint32_fromPy), DataType::UInt32, "", sizeof(uint32), alignof(uint32), {  }, StandardAttribute::Output },
                        { "uint64_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint64_toPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "uint64_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint64_fromPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Output },
                        { "float32_toPy", offsetof(::PythonArp::Prog_TestPrimitive, float32_toPy), DataType::Float32, "", sizeof(float32), alignof(float32), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "float32_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, float32_fromPy), DataType::Float32, "", sizeof(float32), alignof(float32), {  }, StandardAttribute::Output },
                        { "float64_toPy", offsetof(::PythonArp::Prog_TestPrimitive, float64_toPy), DataType::Float64, "", sizeof(float64), alignof(float64), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "float64_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, float64_fromPy), DataType::Float64, "", sizeof(float64), alignof(float64), {  }, StandardAttribute::Output },
                        { "STRING_toPy", offsetof(::PythonArp::Prog_TestPrimitive, STRING_toPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "STRING_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, STRING_fromPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Output },
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_TestStruct1
                    DataType::Program, CTN<PythonArp::Prog_TestStruct1>(), sizeof(::PythonArp::Prog_TestStruct1), alignof(::PythonArp::Prog_TestStruct1), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        { "xReady", offsetof(::PythonArp::Prog_TestStruct1, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output },
                        { "STRUCT_1_toPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_1_toPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtIN_1>(), sizeof(PythonArp::Prog_TestStruct1::udtIN_1), alignof(PythonArp::Prog_TestStruct1::udtIN_1), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "STRUCT_2_toPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_2_toPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtIN_2>(), sizeof(PythonArp::Prog_TestStruct1::udtIN_2), alignof(PythonArp::Prog_TestStruct1::udtIN_2), {  }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "STRUCT_1_fromPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_1_fromPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_1>(), sizeof(PythonArp::Prog_TestStruct1::udtOUT_1), alignof(PythonArp::Prog_TestStruct1::udtOUT_1), {  }, StandardAttribute::Output },
                        { "STRUCT_2_fromPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_2_fromPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_2>(), sizeof(PythonArp::Prog_TestStruct1::udtOUT_2), alignof(PythonArp::Prog_TestStruct1::udtOUT_2), {  }, StandardAttribute::Output },
                    }
                },
            }
            // End TypeDefinitions
        );
    }

} // end of namespace PythonArp

