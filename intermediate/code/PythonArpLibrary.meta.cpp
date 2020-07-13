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

    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_1_xBOOL("xBOOL", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, xBOOL), DataType::Boolean, "", sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_1_iINT("iINT", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, iINT), DataType::Int16, "", sizeof(Arp::int16), alignof(Arp::int16), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_1_dwDWORD("dwDWORD", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, dwDWORD), DataType::UInt32, "", sizeof(Arp::uint32), alignof(Arp::uint32), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_1_sSTRING("sSTRING", offsetof(::PythonArp::Prog_TestStruct1::udtIN_1, sSTRING), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_2_iArray5("iArray5", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, iArray5), DataType::Int16 | DataType::Array, "", sizeof(Arp::int16), alignof(Arp::int16), { 5 }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_2_rArray10("rArray10", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, rArray10), DataType::Float32 | DataType::Array, "", sizeof(Arp::float32), alignof(Arp::float32), { 10 }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_2_dwArray3("dwArray3", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, dwArray3), DataType::UInt32 | DataType::Array, "", sizeof(Arp::uint32), alignof(Arp::uint32), { 3 }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtIN_2_stSub("stSub", offsetof(::PythonArp::Prog_TestStruct1::udtIN_2, stSub), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtSub>(), sizeof(PythonArp::Prog_TestStruct1::udtSub), alignof(PythonArp::Prog_TestStruct1::udtSub), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtOUT_1_sSTRING("sSTRING", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_1, sSTRING), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtOUT_1_xBOOL("xBOOL", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_1, xBOOL), DataType::Boolean, "", sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtOUT_1_iINT("iINT", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_1, iINT), DataType::Int16, "", sizeof(Arp::int16), alignof(Arp::int16), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtOUT_2_arrLWORD3("arrLWORD3", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_2, arrLWORD3), DataType::UInt64 | DataType::Array, "", sizeof(Arp::uint64), alignof(Arp::uint64), { 3 }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtOUT_2_arrWORD3("arrWORD3", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_2, arrWORD3), DataType::UInt16 | DataType::Array, "", sizeof(Arp::uint16), alignof(Arp::uint16), { 3 }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtOUT_2_stSub3("stSub3", offsetof(::PythonArp::Prog_TestStruct1::udtOUT_2, stSub3), DataType::Struct | DataType::Array, CTN<PythonArp::Prog_TestStruct1::udtSub>(), sizeof(PythonArp::Prog_TestStruct1::udtSub), alignof(PythonArp::Prog_TestStruct1::udtSub), { 3 }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtSub_xBOOL("xBOOL", offsetof(::PythonArp::Prog_TestStruct1::udtSub, xBOOL), DataType::Boolean, "", sizeof(Arp::boolean), alignof(Arp::boolean), {  }, StandardAttribute::None);
    static const FieldDefinition PythonArp_Prog_TestStruct1_udtSub_iArray10("iArray10", offsetof(::PythonArp::Prog_TestStruct1::udtSub, iArray10), DataType::Int16 | DataType::Array, "", sizeof(Arp::int16), alignof(Arp::int16), { 10 }, StandardAttribute::None);
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
    static const FieldDefinition PythonArp_Prog_TestArray_PyReady("xReady", offsetof(::PythonArp::Prog_TestArray, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_Bool_toPy("xBool_toPy", offsetof(::PythonArp::Prog_TestArray, Bool_toPy), DataType::Boolean | DataType::Array, "", sizeof(boolean), alignof(boolean), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_Bool_fromPy("xBool_fromPy", offsetof(::PythonArp::Prog_TestArray, Bool_fromPy), DataType::Boolean | DataType::Array, "", sizeof(boolean), alignof(boolean), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_int8_toPy("int8_toPy", offsetof(::PythonArp::Prog_TestArray, int8_toPy), DataType::Int8 | DataType::Array, "", sizeof(int8), alignof(int8), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_int8_fromPy("int8_fromPy", offsetof(::PythonArp::Prog_TestArray, int8_fromPy), DataType::Int8 | DataType::Array, "", sizeof(int8), alignof(int8), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_int16_toPy("int16_toPy", offsetof(::PythonArp::Prog_TestArray, int16_toPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_int16_fromPy("int16_fromPy", offsetof(::PythonArp::Prog_TestArray, int16_fromPy), DataType::Int16 | DataType::Array, "", sizeof(int16), alignof(int16), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_int32_toPy("int32_toPy", offsetof(::PythonArp::Prog_TestArray, int32_toPy), DataType::Int32 | DataType::Array, "", sizeof(int32), alignof(int32), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_int32_fromPy("int32_fromPy", offsetof(::PythonArp::Prog_TestArray, int32_fromPy), DataType::Int32 | DataType::Array, "", sizeof(int32), alignof(int32), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_int64_toPy("int64_toPy", offsetof(::PythonArp::Prog_TestArray, int64_toPy), DataType::Int64 | DataType::Array, "", sizeof(int64), alignof(int64), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_int64_fromPy("int64_fromPy", offsetof(::PythonArp::Prog_TestArray, int64_fromPy), DataType::Int64 | DataType::Array, "", sizeof(int64), alignof(int64), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_uint8_toPy("uint8_toPy", offsetof(::PythonArp::Prog_TestArray, uint8_toPy), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_uint8_fromPy("uint8_fromPy", offsetof(::PythonArp::Prog_TestArray, uint8_fromPy), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_uint16_toPy("uint16_toPy", offsetof(::PythonArp::Prog_TestArray, uint16_toPy), DataType::UInt16 | DataType::Array, "", sizeof(uint16), alignof(uint16), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_uint16_fromPy("uint16_fromPy", offsetof(::PythonArp::Prog_TestArray, uint16_fromPy), DataType::UInt16 | DataType::Array, "", sizeof(uint16), alignof(uint16), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_uint32_toPy("uint32_toPy", offsetof(::PythonArp::Prog_TestArray, uint32_toPy), DataType::UInt32 | DataType::Array, "", sizeof(uint32), alignof(uint32), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_uint32_fromPy("uint32_fromPy", offsetof(::PythonArp::Prog_TestArray, uint32_fromPy), DataType::UInt32 | DataType::Array, "", sizeof(uint32), alignof(uint32), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_uint64_toPy("uint64_toPy", offsetof(::PythonArp::Prog_TestArray, uint64_toPy), DataType::UInt64 | DataType::Array, "", sizeof(uint64), alignof(uint64), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_uint64_fromPy("uint64_fromPy", offsetof(::PythonArp::Prog_TestArray, uint64_fromPy), DataType::UInt64 | DataType::Array, "", sizeof(uint64), alignof(uint64), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_float32_toPy("float32_toPy", offsetof(::PythonArp::Prog_TestArray, float32_toPy), DataType::Float32 | DataType::Array, "", sizeof(float32), alignof(float32), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_float32_fromPy("float32_fromPy", offsetof(::PythonArp::Prog_TestArray, float32_fromPy), DataType::Float32 | DataType::Array, "", sizeof(float32), alignof(float32), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_float64_toPy("float64_toPy", offsetof(::PythonArp::Prog_TestArray, float64_toPy), DataType::Float64 | DataType::Array, "", sizeof(float64), alignof(float64), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_float64_fromPy("float64_fromPy", offsetof(::PythonArp::Prog_TestArray, float64_fromPy), DataType::Float64 | DataType::Array, "", sizeof(float64), alignof(float64), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestArray_STRING_toPy("STRING_toPy", offsetof(::PythonArp::Prog_TestArray, STRING_toPy), DataType::StaticString | DataType::Array, "", sizeof(StaticString<80>), alignof(StaticString<80>), { 3 }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestArray_STRING_fromPy("STRING_fromPy", offsetof(::PythonArp::Prog_TestArray, STRING_fromPy), DataType::StaticString | DataType::Array, "", sizeof(StaticString<80>), alignof(StaticString<80>), { 3 }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_PyReady("xReady", offsetof(::PythonArp::Prog_TestPrimitive, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_Bool_toPy("xBool_toPy", offsetof(::PythonArp::Prog_TestPrimitive, Bool_toPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_Bool_fromPy("xBool_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, Bool_fromPy), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int8_toPy("int8_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int8_toPy), DataType::Int8, "", sizeof(int8), alignof(int8), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int8_fromPy("int8_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int8_fromPy), DataType::Int8, "", sizeof(int8), alignof(int8), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int16_toPy("int16_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int16_toPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int16_fromPy("int16_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int16_fromPy), DataType::Int16, "", sizeof(int16), alignof(int16), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int32_toPy("int32_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int32_toPy), DataType::Int32, "", sizeof(int32), alignof(int32), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int32_fromPy("int32_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int32_fromPy), DataType::Int32, "", sizeof(int32), alignof(int32), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int64_toPy("int64_toPy", offsetof(::PythonArp::Prog_TestPrimitive, int64_toPy), DataType::Int64, "", sizeof(int64), alignof(int64), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_int64_fromPy("int64_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, int64_fromPy), DataType::Int64, "", sizeof(int64), alignof(int64), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint8_toPy("uint8_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint8_toPy), DataType::UInt8, "", sizeof(uint8), alignof(uint8), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint8_fromPy("uint8_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint8_fromPy), DataType::UInt8, "", sizeof(uint8), alignof(uint8), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint16_toPy("uint16_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint16_toPy), DataType::UInt16, "", sizeof(uint16), alignof(uint16), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint16_fromPy("uint16_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint16_fromPy), DataType::UInt16, "", sizeof(uint16), alignof(uint16), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint32_toPy("uint32_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint32_toPy), DataType::UInt32, "", sizeof(uint32), alignof(uint32), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint32_fromPy("uint32_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint32_fromPy), DataType::UInt32, "", sizeof(uint32), alignof(uint32), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint64_toPy("uint64_toPy", offsetof(::PythonArp::Prog_TestPrimitive, uint64_toPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_uint64_fromPy("uint64_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, uint64_fromPy), DataType::UInt64, "", sizeof(uint64), alignof(uint64), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_float32_toPy("float32_toPy", offsetof(::PythonArp::Prog_TestPrimitive, float32_toPy), DataType::Float32, "", sizeof(float32), alignof(float32), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_float32_fromPy("float32_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, float32_fromPy), DataType::Float32, "", sizeof(float32), alignof(float32), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_float64_toPy("float64_toPy", offsetof(::PythonArp::Prog_TestPrimitive, float64_toPy), DataType::Float64, "", sizeof(float64), alignof(float64), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_float64_fromPy("float64_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, float64_fromPy), DataType::Float64, "", sizeof(float64), alignof(float64), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_STRING_toPy("STRING_toPy", offsetof(::PythonArp::Prog_TestPrimitive, STRING_toPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestPrimitive_STRING_fromPy("STRING_fromPy", offsetof(::PythonArp::Prog_TestPrimitive, STRING_fromPy), DataType::StaticString, "", sizeof(StaticString<80>), alignof(StaticString<80>), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestStruct1_PyReady("xReady", offsetof(::PythonArp::Prog_TestStruct1, PyReady), DataType::Boolean, "", sizeof(boolean), alignof(boolean), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestStruct1_STRUCT_1_toPy("STRUCT_1_toPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_1_toPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtIN_1>(), sizeof(PythonArp::Prog_TestStruct1::udtIN_1), alignof(PythonArp::Prog_TestStruct1::udtIN_1), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestStruct1_STRUCT_2_toPy("STRUCT_2_toPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_2_toPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtIN_2>(), sizeof(PythonArp::Prog_TestStruct1::udtIN_2), alignof(PythonArp::Prog_TestStruct1::udtIN_2), {  }, StandardAttribute::Input | StandardAttribute::Retain);
    static const FieldDefinition PythonArp_Prog_TestStruct1_STRUCT_1_fromPy("STRUCT_1_fromPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_1_fromPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_1>(), sizeof(PythonArp::Prog_TestStruct1::udtOUT_1), alignof(PythonArp::Prog_TestStruct1::udtOUT_1), {  }, StandardAttribute::Output);
    static const FieldDefinition PythonArp_Prog_TestStruct1_STRUCT_2_fromPy("STRUCT_2_fromPy", offsetof(::PythonArp::Prog_TestStruct1, STRUCT_2_fromPy), DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_2>(), sizeof(PythonArp::Prog_TestStruct1::udtOUT_2), alignof(PythonArp::Prog_TestStruct1::udtOUT_2), {  }, StandardAttribute::Output);
    
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
                        PythonArp_Prog_TestStruct1_udtIN_1_xBOOL,
                        PythonArp_Prog_TestStruct1_udtIN_1_iINT,
                        PythonArp_Prog_TestStruct1_udtIN_1_dwDWORD,
                        PythonArp_Prog_TestStruct1_udtIN_1_sSTRING,
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtIN_2
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtIN_2>(), sizeof(::PythonArp::Prog_TestStruct1::udtIN_2), alignof(::PythonArp::Prog_TestStruct1::udtIN_2), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_TestStruct1_udtIN_2_iArray5,
                        PythonArp_Prog_TestStruct1_udtIN_2_rArray10,
                        PythonArp_Prog_TestStruct1_udtIN_2_dwArray3,
                        PythonArp_Prog_TestStruct1_udtIN_2_stSub,
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtOUT_1
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_1>(), sizeof(::PythonArp::Prog_TestStruct1::udtOUT_1), alignof(::PythonArp::Prog_TestStruct1::udtOUT_1), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_TestStruct1_udtOUT_1_sSTRING,
                        PythonArp_Prog_TestStruct1_udtOUT_1_xBOOL,
                        PythonArp_Prog_TestStruct1_udtOUT_1_iINT,
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtOUT_2
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtOUT_2>(), sizeof(::PythonArp::Prog_TestStruct1::udtOUT_2), alignof(::PythonArp::Prog_TestStruct1::udtOUT_2), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_TestStruct1_udtOUT_2_arrLWORD3,
                        PythonArp_Prog_TestStruct1_udtOUT_2_arrWORD3,
                        PythonArp_Prog_TestStruct1_udtOUT_2_stSub3,
                    }
                },
                {   // TypeDefinition: PythonArp::Prog_TestStruct1::udtSub
                    DataType::Struct, CTN<PythonArp::Prog_TestStruct1::udtSub>(), sizeof(::PythonArp::Prog_TestStruct1::udtSub), alignof(::PythonArp::Prog_TestStruct1::udtSub), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_TestStruct1_udtSub_xBOOL,
                        PythonArp_Prog_TestStruct1_udtSub_iArray10,
                    }
                },
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
                {   // ProgramDefinition: PythonArp::Prog_TestArray
                    DataType::Program, CTN<PythonArp::Prog_TestArray>(), sizeof(::PythonArp::Prog_TestArray), alignof(::PythonArp::Prog_TestArray), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_TestArray_PyReady,
                        PythonArp_Prog_TestArray_Bool_toPy,
                        PythonArp_Prog_TestArray_Bool_fromPy,
                        PythonArp_Prog_TestArray_int8_toPy,
                        PythonArp_Prog_TestArray_int8_fromPy,
                        PythonArp_Prog_TestArray_int16_toPy,
                        PythonArp_Prog_TestArray_int16_fromPy,
                        PythonArp_Prog_TestArray_int32_toPy,
                        PythonArp_Prog_TestArray_int32_fromPy,
                        PythonArp_Prog_TestArray_int64_toPy,
                        PythonArp_Prog_TestArray_int64_fromPy,
                        PythonArp_Prog_TestArray_uint8_toPy,
                        PythonArp_Prog_TestArray_uint8_fromPy,
                        PythonArp_Prog_TestArray_uint16_toPy,
                        PythonArp_Prog_TestArray_uint16_fromPy,
                        PythonArp_Prog_TestArray_uint32_toPy,
                        PythonArp_Prog_TestArray_uint32_fromPy,
                        PythonArp_Prog_TestArray_uint64_toPy,
                        PythonArp_Prog_TestArray_uint64_fromPy,
                        PythonArp_Prog_TestArray_float32_toPy,
                        PythonArp_Prog_TestArray_float32_fromPy,
                        PythonArp_Prog_TestArray_float64_toPy,
                        PythonArp_Prog_TestArray_float64_fromPy,
                        PythonArp_Prog_TestArray_STRING_toPy,
                        PythonArp_Prog_TestArray_STRING_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_TestPrimitive
                    DataType::Program, CTN<PythonArp::Prog_TestPrimitive>(), sizeof(::PythonArp::Prog_TestPrimitive), alignof(::PythonArp::Prog_TestPrimitive), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_TestPrimitive_PyReady,
                        PythonArp_Prog_TestPrimitive_Bool_toPy,
                        PythonArp_Prog_TestPrimitive_Bool_fromPy,
                        PythonArp_Prog_TestPrimitive_int8_toPy,
                        PythonArp_Prog_TestPrimitive_int8_fromPy,
                        PythonArp_Prog_TestPrimitive_int16_toPy,
                        PythonArp_Prog_TestPrimitive_int16_fromPy,
                        PythonArp_Prog_TestPrimitive_int32_toPy,
                        PythonArp_Prog_TestPrimitive_int32_fromPy,
                        PythonArp_Prog_TestPrimitive_int64_toPy,
                        PythonArp_Prog_TestPrimitive_int64_fromPy,
                        PythonArp_Prog_TestPrimitive_uint8_toPy,
                        PythonArp_Prog_TestPrimitive_uint8_fromPy,
                        PythonArp_Prog_TestPrimitive_uint16_toPy,
                        PythonArp_Prog_TestPrimitive_uint16_fromPy,
                        PythonArp_Prog_TestPrimitive_uint32_toPy,
                        PythonArp_Prog_TestPrimitive_uint32_fromPy,
                        PythonArp_Prog_TestPrimitive_uint64_toPy,
                        PythonArp_Prog_TestPrimitive_uint64_fromPy,
                        PythonArp_Prog_TestPrimitive_float32_toPy,
                        PythonArp_Prog_TestPrimitive_float32_fromPy,
                        PythonArp_Prog_TestPrimitive_float64_toPy,
                        PythonArp_Prog_TestPrimitive_float64_fromPy,
                        PythonArp_Prog_TestPrimitive_STRING_toPy,
                        PythonArp_Prog_TestPrimitive_STRING_fromPy,
                    }
                },
                {   // ProgramDefinition: PythonArp::Prog_TestStruct1
                    DataType::Program, CTN<PythonArp::Prog_TestStruct1>(), sizeof(::PythonArp::Prog_TestStruct1), alignof(::PythonArp::Prog_TestStruct1), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                        PythonArp_Prog_TestStruct1_PyReady,
                        PythonArp_Prog_TestStruct1_STRUCT_1_toPy,
                        PythonArp_Prog_TestStruct1_STRUCT_2_toPy,
                        PythonArp_Prog_TestStruct1_STRUCT_1_fromPy,
                        PythonArp_Prog_TestStruct1_STRUCT_2_fromPy,
                    }
                },
            }
            // End TypeDefinitions
        );
    }

} // end of namespace PythonArp

