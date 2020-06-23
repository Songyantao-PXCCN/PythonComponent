'''
This file emulate function of PythonArpComponent
Do not trans this file to PLCnext !, otherwise this file will over write functions from PythonArpComponent

the following function is support for now :

    GDS_Read()
    GDS_Write()

'''

GDS_RETURN_VALUES = 1
GDS_RETURN_FAULTREASON = 2
GDS_RETURN_DATATYPE = 4
GDS_RETURN_DICT = 8

GDS_TYPE_INT8 = 1
GDS_TYPE_INT16 = 2
GDS_TYPE_INT32 = 3
GDS_TYPE_INT64 = 4
GDS_TYPE_UINT8 = 5
GDS_TYPE_UINT16 = 6
GDS_TYPE_UINT32 = 7
GDS_TYPE_UINT64 = 8
GDS_TYPE_FLOAT32 = 9
GDS_TYPE_FLOAT64 = 10


class DB:
    def __init__(self, pringNewValue: bool = False):
        self.DB = dict()
        self.printVal = pringNewValue

    def add(self, varName: str, varValue, figureType: int = None):
        item = GDS_DB.variableItem(varName, varValue, figureType, self.printVal)
        self.DB[varName] = item

    class variableItem:
        def __init__(self, varName, varValue, figureType, printVal):
            self.varName = varName
            self.varValue = varValue
            self._print = printVal
            if type(varValue) == str:
                self.varType = ('String', 0)
            elif type(varValue) == bool:
                self.varType = ('Bool', 0)
            elif type(varValue) == int:
                if figureType == GDS_TYPE_INT8:
                    self.varType = ('Int8', GDS_TYPE_INT8)
                elif figureType in [GDS_TYPE_INT16, None]:
                    self.varType = ('Int16', GDS_TYPE_INT16)
                elif figureType == GDS_TYPE_INT32:
                    self.varType = ('Int32', GDS_TYPE_INT32)
                elif figureType == GDS_TYPE_INT64:
                    self.varType = ('Int64', GDS_TYPE_INT64)
                elif figureType == GDS_TYPE_UINT8:
                    self.varType = ("Uint8", GDS_TYPE_UINT8)
                elif figureType == GDS_TYPE_UINT16:
                    self.varType = ("Uint16", GDS_TYPE_UINT16)
                elif figureType == GDS_TYPE_UINT32:
                    self.varType = ("Uint32", GDS_TYPE_UINT32)
                elif figureType == GDS_TYPE_UINT64:
                    self.varType = ("Uint64", GDS_TYPE_UINT64)
                else:
                    raise TypeError(f"Wrong type of {varName}")
            elif type(varValue) == float:
                if figureType in [GDS_TYPE_FLOAT32, None]:
                    self.varType = ("Real32", GDS_TYPE_FLOAT32)
                elif figureType == GDS_TYPE_FLOAT64:
                    self.varType = ("Real64", GDS_TYPE_FLOAT64)
                else:
                    raise TypeError(f"Wrong type of {varName}")

        def refreshValue(self, newValue):
            self.varValue = newValue
            if self._print:
                print(f"\033[1;33;44m GDS Data Change  '{self.varName}' : {self.varValue}\033[0m")


GDS_DB = DB()
# GDS_DB = DB(True) # with DataChangeLog
'''
Variables that PLC should have with it's init value
when the variable is figureType,better to provide explicit type of it.
By default,float is set to 'GDS_TYPE_FLOAT32' , int is set to 'GDS_TYPE_INT16'
'''
GDS_DB.add("Arp.Plc.Eclr/BOOL001", True)
GDS_DB.add("Arp.Plc.Eclr/REAL001", 12.3)  # by default is GDS_TYPE_FLOAT32
GDS_DB.add("Arp.Plc.Eclr/LREAL001", 12345.67, figureType=GDS_TYPE_FLOAT64)
GDS_DB.add("Arp.Plc.Eclr/INT001", 12)  # by default is GDS_TYPE_INT16
GDS_DB.add("Arp.Plc.Eclr/DINT001", 123456, figureType=GDS_TYPE_INT32)
GDS_DB.add("Arp.Plc.Eclr/STRING001", "hello")


def GDS_Read(variables, prefix: str = None,
             returnType: int = GDS_RETURN_VALUES | GDS_RETURN_FAULTREASON | GDS_RETURN_DATATYPE):
    '''this is the wrap function of DataAccessService->read()

    :param variables: str type if read a single variable,or using list|tuple of str for read multi-variables
    :param prefix:(optional)
    :param returnType:(optional) default is 'GDS_RETURN_VALUES | GDS_RETURN_FAULTREASON | GDS_RETURN_DATATYPE'
    :return: tuple (values , fault-reason , type)

    Example:
        values , faultReason , valueType = GDS_Read("Arp.Plc.Eclr/xTest")
        values , faultReason , valueType = GDS_Read("xTest", prefix = 'Arp.Plc.Eclr/')
        values , faultReason , valueType = GDS_Read(["xTest1","xTest2"], prefix = 'Arp.Plc.Eclr/')
        values_dict  = GDS_Read(["xTest1","xTest2"], prefix = 'Arp.Plc.Eclr/' ,
                                                    returnType = GDS_RETURN_VALUES | GDS_RETURN_DICT)

    '''

    if (not type(variables) in [str, list, tuple]):
        raise TypeError("Variables should be tuple, List or Str !")
    if (type(variables) in [list, tuple]):
        for item in variables:
            if (type(item) != str):
                raise TypeError("all items must be str")
    if prefix and type(prefix) != str:
        raise TypeError("prefix shoule be str or None")
    if (type(returnType) != int):
        raise TypeError("returnType shoule be int")

    _RETURN_VALUES = bool(returnType & GDS_RETURN_VALUES)
    _RETURN_FAULTREASON = bool(returnType & GDS_RETURN_FAULTREASON)
    _RETURN_DATATYPE = bool(returnType & GDS_RETURN_DATATYPE)
    _RETURN_DICT = bool(returnType & GDS_RETURN_DICT)

    if (not _RETURN_VALUES) and (not _RETURN_FAULTREASON) and (not _RETURN_DATATYPE):
        raise TypeError("Wrong returnType , Nothing can be return")

    if prefix:
        if type(variables) == str:
            varNames = [prefix + variables]
        else:
            varNames = [prefix + var for var in variables]
    else:
        if type(variables) == str:
            varNames = [variables]
        else:
            varNames = variables

    if _RETURN_DICT:
        buf_Result = dict()
        buf_FaultReason = dict()
        buf_Type = dict()
        for var in varNames:
            curRet = GDS_DB.DB.get(var, None)
            if curRet is None:
                buf_Result[var] = None
                buf_FaultReason[var] = "NotExists"
                buf_Type[var] = "Void"
            else:
                buf_Result[var] = curRet.varValue
                buf_FaultReason[var] = "None"
                buf_Type[var] = curRet.varType[0]
    else:
        buf_Result = list()
        buf_FaultReason = list()
        buf_Type = list()
        for var in varNames:
            curRet = GDS_DB.DB.get(var, None)
            if curRet is None:
                buf_Result.append(None)
                buf_FaultReason.append("NotExists")
                buf_Type.append("Void")
            else:
                buf_Result.append(curRet.varValue)
                buf_FaultReason.append("None")
                buf_Type.append(curRet.varType[0])
        buf_Result = tuple(buf_Result)
        buf_FaultReason = tuple(buf_FaultReason)
        buf_Type = tuple(buf_Type)

    # return buf_Result if _RETURN_VALUES else None, \
    #        buf_FaultReason if _RETURN_FAULTREASON else None, \
    #        buf_Type if _RETURN_DATATYPE else None
    if _RETURN_VALUES and _RETURN_FAULTREASON and _RETURN_DATATYPE:
        return buf_Result, buf_FaultReason, buf_Type
    if _RETURN_VALUES and (not _RETURN_FAULTREASON) and (not _RETURN_DATATYPE):
        return buf_Result
    if (not _RETURN_VALUES) and _RETURN_FAULTREASON and (not _RETURN_DATATYPE):
        return buf_FaultReason
    if (not _RETURN_VALUES) and (not _RETURN_FAULTREASON) and _RETURN_DATATYPE:
        return buf_Type
    if _RETURN_VALUES and _RETURN_FAULTREASON and (not _RETURN_DATATYPE):
        return buf_Result, buf_FaultReason
    if _RETURN_VALUES and (not _RETURN_FAULTREASON) and _RETURN_DATATYPE:
        return buf_Result, buf_Type
    if (not _RETURN_VALUES) and _RETURN_FAULTREASON and _RETURN_DATATYPE:
        return buf_FaultReason, buf_Type


def GDS_Write(variables: dict, prefix: str = None, forceType: dict = None) -> dict:
    '''this is the wrap function of DataAccessService->write()


    :param variables: dict type,key is variable name.
    :param prefix: (optional)
    :param forceType: (optional) , when variable is figure(int or float) type ,better to provide explicit type of it.
                                   By default,float is set to 'GDS_TYPE_FLOAT32' , int is set to 'GDS_TYPE_INT16'
    :return:dict{variableName : Fault reason}
    '''
    if type(variables) != dict:
        raise TypeError("variables should be dict")
    if prefix and type(prefix) != str:
        raise TypeError("prefix shoule be str or None")
    if forceType and (type(forceType) != dict):
        raise TypeError("forceType should be dict")

    _vars = dict()
    _forceType = dict()

    if prefix:
        for _key in variables:
            _vars[prefix + _key] = variables[_key]
        if forceType is None:
            _forceType = None
        else:
            for __key in forceType:
                _forceType[prefix + __key] = forceType[__key]
    else:
        _vars = variables
        _forceType = forceType

    result = dict()
    for key in _vars:
        DB_val = GDS_DB.DB.get(key, None)
        if DB_val is None:
            result[key] = "NotExists"
        else:
            valueSet = _vars[key]
            if type(valueSet) != type(DB_val.varValue):
                result[key] = "TypeMismatch"
            else:
                if type(valueSet) == bool:
                    result[key] = "None"
                    DB_val.refreshValue(valueSet)
                elif type(valueSet) == str:
                    result[key] = "None"
                    DB_val.refreshValue(valueSet)
                else:
                    if type(valueSet) == float:
                        if _forceType is None:
                            _realTYpe = GDS_TYPE_FLOAT32
                        else:
                            _realTYpe = _forceType.get(key, GDS_TYPE_FLOAT32)
                        if DB_val.varType[1] == _realTYpe:
                            DB_val.refreshValue(valueSet)
                            result[key] = "None"
                        else:
                            result[key] = "TypeMismatch"
                    if type(valueSet) == int:
                        if _forceType is None:
                            _intTYpe = GDS_TYPE_INT16
                        else:
                            _intTYpe = _forceType.get(key, GDS_TYPE_INT16)
                        if DB_val.varType[1] == _intTYpe:
                            DB_val.refreshValue(valueSet)
                            result[key] = "None"
                        else:
                            result[key] = "TypeMismatch"
    return result


if __name__ == "__main__":
    # read a single value can directly use str type parameter
    print(GDS_Read("Arp.Plc.Eclr/STRING001"))
    # read multi-variables should use tuple or list
    print(GDS_Read(["Arp.Plc.Eclr/STRING001", "Arp.Plc.Eclr/DINT001", "Arp.Plc.Eclr/INT001"]))
    # use 'prefix'
    print(GDS_Read(["STRING001", "DINT001", "INT001"], prefix="Arp.Plc.Eclr/"))
    # set 'returnType'
    dictVal = GDS_Read(["STRING001", "DINT001", "INT001"], prefix="Arp.Plc.Eclr/",
                       returnType=GDS_RETURN_VALUES | GDS_RETURN_DICT)
    print(dictVal)

    dictVal, dataType = GDS_Read(["STRING001", "DINT001", "INT001"], prefix="Arp.Plc.Eclr/",
                                 returnType=GDS_RETURN_VALUES | GDS_RETURN_DATATYPE | GDS_RETURN_DICT)

    print(dictVal)
    print(dataType)
    # --------------------------
    # write variables:
    print(GDS_Write({"BOOL001": False, "REAL001": 23.4, "LREAL001": 23456.78}, prefix="Arp.Plc.Eclr/",
                    forceType={"LREAL001": GDS_TYPE_FLOAT64}))
    # if write to variable that doesn't exist:
    print(GDS_Write({"BOOL002": False, "REAL002": 23.4}, prefix="Arp.Plc.Eclr/"))
    # if type doesn't match:
    print(GDS_Write({"Arp.Plc.Eclr/STRING001": True}))
    print(GDS_Write({"Arp.Plc.Eclr/DINT001": 1000}))
    # right way to write "Arp.Plc.Eclr/DINT001"
    print(GDS_Write({"Arp.Plc.Eclr/DINT001": 1000}, forceType={"Arp.Plc.Eclr/DINT001": GDS_TYPE_INT32}))
    # --------------------------
    for i in range(5):
        ret = GDS_Read("Arp.Plc.Eclr/STRING001", returnType=GDS_RETURN_VALUES)
        print(ret[0])
        GDS_Write({"Arp.Plc.Eclr/STRING001": ret[0] + '.'})
