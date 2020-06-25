# from 'SubscriptionService.ReadRecords'
try:
    from ArpEmulation import *

    print(f"\033[1;33;44m *** Running '{__name__}' in emulation mode *** \033[0m")
except ImportError:
    pass

import threading


class GlobalValues():
    pass


class WorkerThread(threading.Thread):

    def __init__(self, interval: float, callableFunction, startImmediately=True):
        if callable(callableFunction) and interval > 0:
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


from datetime import datetime as dt

def TestSubscriptionService():
    print("*"*80)

    print("ReadValues : ")
    ReadValuesRet = GlobalValues.subInstance.ReadValues()
    print(ReadValuesRet)
    if ReadValuesRet[0] == "None" :
        for _varName,_value in ReadValuesRet[1].items():
            print(" -{}\t: {}".format(_varName,_value))


    print("ReadTimeStampedValues : ")
    ReadTimeStampedValuesRet = GlobalValues.subInstance.ReadTimeStampedValues()
    print(ReadTimeStampedValuesRet)
    if ReadTimeStampedValuesRet[0] == "None":
        for _varName,_tuple in ReadTimeStampedValuesRet[1].items():
            if _tuple[1]>0:
                print(" -{}\t: {}\t{}".format(_varName,_tuple[0],dt.fromtimestamp(_tuple[1]/ 1000000).strftime("%Y-%m-%dT%H:%M:%S.%f")))



# Here we only add these two PLC event's functions ,it's enough for this test
# The thread will start while PLC have a Cold/Warm/Hot Start, And stop thread while PLC turn to STOP
def Start():
    print("Start called !")

    # create Service
    sub = SubscriptionService(SUBSCRIPTION_HIGHPERFORMANCE)
    print("Current subscription id is : " + str(sub.GetSubscriptionID()))

    # add variables to this subscription
    ret = sub.AddVariable(("Arp.Plc.Eclr/BOOL001", "Arp.Plc.Eclr/INT001"))
    for _varName, _error in ret.items():
        if _error != 'None':
            print("Error occured while adding '{}' : {}".format(_varName, _error))

    # or use prefix
    ret = sub.AddVariable(("BOOL002", "INT002"), prefix='Arp.Plc.Eclr/')
    for _varName, _error in ret.items():
        if _error != 'None':
            print("Error occured while adding '{}' : {}".format(_varName, _error))

    # start subscribe and set sampleRate in micro-seconds
    sub.Subscribe(100000)

    GlobalValues.subInstance = sub
    GlobalValues.threadInstance = WorkerThread(2, TestSubscriptionService)


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
25.06.20 04:50:36.783 root                                                         INFO  - ********************************************************************************
25.06.20 04:50:36.783 root                                                         INFO  - ReadValues :
25.06.20 04:50:36.784 root                                                         INFO  - ('None', {'Arp.Plc.Eclr/INT002': False, 'Arp.Plc.Eclr/INT001': False, 'Arp.Plc.Eclr/BOOL002': False, 'Arp.Plc.Eclr/BOOL001': False})
25.06.20 04:50:36.784 root                                                         INFO  -  -Arp.Plc.Eclr/INT002        : False
25.06.20 04:50:36.785 root                                                         INFO  -  -Arp.Plc.Eclr/INT001        : False
25.06.20 04:50:36.786 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL002       : False
25.06.20 04:50:36.786 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL001       : False
25.06.20 04:50:36.787 root                                                         INFO  - ReadTimeStampedValues :
25.06.20 04:50:36.788 root                                                         INFO  - ('None', {'Arp.Plc.Eclr/INT002': (False, 1593060636774238), 'Arp.Plc.Eclr/INT001': (False, 1593060636774238), 'Arp.Plc.Eclr/BOOL002': (False, 1593060636774238), 'Arp.Plc.Eclr/BOOL001': (False, 1593060636774238)})
25.06.20 04:50:36.790 root                                                         INFO  -  -Arp.Plc.Eclr/INT002        : False 2020-06-25T04:50:36.774238
25.06.20 04:50:36.792 root                                                         INFO  -  -Arp.Plc.Eclr/INT001        : False 2020-06-25T04:50:36.774238
25.06.20 04:50:36.793 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL002       : False 2020-06-25T04:50:36.774238
25.06.20 04:50:36.794 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL001       : False 2020-06-25T04:50:36.774238
25.06.20 04:50:38.795 root                                                         INFO  - ********************************************************************************
25.06.20 04:50:38.796 root                                                         INFO  - ReadValues :
25.06.20 04:50:38.797 root                                                         INFO  - ('None', {'Arp.Plc.Eclr/INT002': False, 'Arp.Plc.Eclr/INT001': False, 'Arp.Plc.Eclr/BOOL002': False, 'Arp.Plc.Eclr/BOOL001': False})
25.06.20 04:50:38.798 root                                                         INFO  -  -Arp.Plc.Eclr/INT002        : False
25.06.20 04:50:38.799 root                                                         INFO  -  -Arp.Plc.Eclr/INT001        : False
25.06.20 04:50:38.799 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL002       : False
25.06.20 04:50:38.799 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL001       : False
25.06.20 04:50:38.800 root                                                         INFO  - ReadTimeStampedValues :
25.06.20 04:50:38.802 root                                                         INFO  - ('None', {'Arp.Plc.Eclr/INT002': (False, 1593060638774685), 'Arp.Plc.Eclr/INT001': (False, 1593060638774685), 'Arp.Plc.Eclr/BOOL002': (False, 1593060638774685), 'Arp.Plc.Eclr/BOOL001': (False, 1593060638774685)})
25.06.20 04:50:38.803 root                                                         INFO  -  -Arp.Plc.Eclr/INT002        : False 2020-06-25T04:50:38.774685
25.06.20 04:50:38.804 root                                                         INFO  -  -Arp.Plc.Eclr/INT001        : False 2020-06-25T04:50:38.774685
25.06.20 04:50:38.805 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL002       : False 2020-06-25T04:50:38.774685
25.06.20 04:50:38.807 root                                                         INFO  -  -Arp.Plc.Eclr/BOOL001       : False 2020-06-25T04:50:38.774685
'''