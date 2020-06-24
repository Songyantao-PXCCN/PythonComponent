try:
    from ArpEmulation import *
    print(f"\033[1;33;44m *** Running '{__name__}' in emulation mode *** \033[0m")
except ImportError:
    pass

import threading

class GlobalValues():
    pass
class WorkerThread(threading.Thread):
    
    def __init__(self,interval:float,callableFunction,startImmediately = True):
        if callable(callableFunction) and interval>0:
            threading.Thread.__init__(self)
            self.interval = interval
            self.callableFunction = callableFunction
            self.StopEvent = threading.Event()
            if startImmediately:
                self.start()
        else:
            raise ValueError("Bad Argument")

    def stop(self):
        self.StopEvent.set()
        self.join()

    def run(self):
        while True:
            if not self.StopEvent.wait(self.interval):
                try:
                    self.callableFunction()
                except Exception as e:
                    import traceback
                    traceback.print_exc()
            else:
                return


# please check examples in "ArpEmulation.py" for more detail
def TestDataAccessService():
    print("*"*80)
    variables = ("Arp.Plc.Eclr/BOOL001","Arp.Plc.Eclr/INT001") 
    # Typical use of GDS_Read()
    _ret , _error, _type = GDS_Read(variables)

    for index,currentError in enumerate(_error):
        if currentError == 'None':
            print ("Variable '{}' : {}\t, type :{}".format(variables[index],_ret[index],_type[index]))
        else:
            print("Error occured while reading '{}' : {}".format(variables[index],currentError))

    # get return of DICT 
    _ret , _error, _type = GDS_Read(variables,returnType = GDS_RETURN_VALUES | GDS_RETURN_FAULTREASON | GDS_RETURN_DATATYPE | GDS_RETURN_DICT )
    
    for curName,currentError in _error.items():
        if currentError == 'None':
            print ("Variable '{}' : {}\t, type :{}".format(curName,_ret[curName],_type[curName]))
        else:
            print("Error occured while reading '{}' : {}".format(curName,currentError))

    # custom return
    _ret = GDS_Read(variables,returnType = GDS_RETURN_VALUES | GDS_RETURN_DICT )
    print(_ret)

    # use 'prefix'

    _ret = GDS_Read(("BOOL001","INT001"),prefix = "Arp.Plc.Eclr/",returnType = GDS_RETURN_VALUES | GDS_RETURN_DICT )
    print(_ret)

    ####################################################################
    ####################################################################
    ####################################################################
    ####################################################################
    # static
    if (not hasattr(TestDataAccessService,"tmpBool")):
        TestDataAccessService.tmpBool = True
    if (not hasattr(TestDataAccessService,"tmpInt")):
        TestDataAccessService.tmpInt = 1
    TestDataAccessService.tmpBool ^= True
    TestDataAccessService.tmpInt += 1

    # assume variables are type of BOOL,INT,REAL,STRING
    _error = GDS_Write({"BOOL001":TestDataAccessService.tmpBool,"INT001":TestDataAccessService.tmpInt},prefix = "Arp.Plc.Eclr/")
    for varName,varError in _error.items():
        if varError != 'None':
            print("Error occured while writing '{}' : {}".format(varName,varError))

    # if variables are not basic type , should use 'forceType'
    _error = GDS_Write({"LREAL001":12345.67,"DINT001":1234567},  prefix = "Arp.Plc.Eclr/",
                                                                forceType=  {   "LREAL001": GDS_TYPE_FLOAT64,
                                                                                "DINT001":GDS_TYPE_INT32    
                                                                            })
    for varName,varError in _error.items():
        if varError != 'None':
            print("Error occured while writing '{}' : {}".format(varName,varError))

    


# Here we only add these two PLC event Function ,it's enough for this test
# The thread will start while PLC have a Cold/Warm/Hot Start, And stop thread while PLC turn to STOP
def Start():
    print("Start called !")
    GlobalValues.threadInstance = WorkerThread(2,TestDataAccessService)


def Stop():
    print("Stop called !")
    GlobalValues.threadInstance.stop()



# for test on computer
import time
if __name__ == "__main__":
    # Initialize()
    Start()
    for i in range(100):
        time.sleep(0.1)
        # Execute()
    Stop()
    # Dispose()

'''
24.06.20 15:49:53.840 root                                                         INFO  - ********************************************************************************
24.06.20 15:49:53.843 root                                                         INFO  - Variable 'Arp.Plc.Eclr/BOOL001' : False      , type :Bool
24.06.20 15:49:53.843 root                                                         INFO  - Variable 'Arp.Plc.Eclr/INT001' : 108 , type :Int16
24.06.20 15:49:53.845 root                                                         INFO  - Variable 'Arp.Plc.Eclr/BOOL001' : False      , type :Bool
24.06.20 15:49:53.847 root                                                         INFO  - Variable 'Arp.Plc.Eclr/INT001' : 108 , type :Int16
24.06.20 15:49:53.848 root                                                         INFO  - {'Arp.Plc.Eclr/BOOL001': False, 'Arp.Plc.Eclr/INT001': 108}
24.06.20 15:49:53.851 root                                                         INFO  - {'BOOL001': False, 'INT001': 108}
24.06.20 15:49:55.856 root                                                         INFO  - ********************************************************************************
24.06.20 15:49:55.859 root                                                         INFO  - Variable 'Arp.Plc.Eclr/BOOL001' : True       , type :Bool
24.06.20 15:49:55.859 root                                                         INFO  - Variable 'Arp.Plc.Eclr/INT001' : 109 , type :Int16
24.06.20 15:49:55.863 root                                                         INFO  - Variable 'Arp.Plc.Eclr/BOOL001' : True       , type :Bool
24.06.20 15:49:55.863 root                                                         INFO  - Variable 'Arp.Plc.Eclr/INT001' : 109 , type :Int16
24.06.20 15:49:55.866 root                                                         INFO  - {'Arp.Plc.Eclr/BOOL001': True, 'Arp.Plc.Eclr/INT001': 109}
24.06.20 15:49:55.869 root                                                         INFO  - {'BOOL001': True, 'INT001': 109}
24.06.20 15:49:57.876 root                                                         INFO  - ********************************************************************************
24.06.20 15:49:57.879 root                                                         INFO  - Variable 'Arp.Plc.Eclr/BOOL001' : False      , type :Bool
24.06.20 15:49:57.879 root                                                         INFO  - Variable 'Arp.Plc.Eclr/INT001' : 110 , type :Int16
24.06.20 15:49:57.883 root                                                         INFO  - Variable 'Arp.Plc.Eclr/BOOL001' : False      , type :Bool
24.06.20 15:49:57.883 root                                                         INFO  - Variable 'Arp.Plc.Eclr/INT001' : 110 , type :Int16
24.06.20 15:49:57.888 root                                                         INFO  - {'Arp.Plc.Eclr/BOOL001': False, 'Arp.Plc.Eclr/INT001': 110}
24.06.20 15:49:57.893 root                                                         INFO  - {'BOOL001': False, 'INT001': 110}
'''