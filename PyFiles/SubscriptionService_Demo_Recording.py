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


def ReadRecordsParse(records, Epoch=True):
    def EpochConvert(data):
        if data and type(data) == dict:
            for name, val in data.items():
                if val[1] > 0:
                    v = dt.fromtimestamp(val[1] / 1000000).strftime("%Y-%m-%dT%H:%M:%S.%f")
                    data[name] = (val[0], v)
                else:
                    data[name] = "inValid"

    print('*' * 80)
    for i, tup in enumerate(records):
        if i is 0:
            print("- DataAccessError : " + '"' + tup + '"')
        else:
            print("- Records")
            for taskIndex, task in enumerate(tup):
                print('\t- Task ' + str(taskIndex))
                for cycleIndex, cycle in enumerate(task):
                    if not Epoch:
                        EpochConvert(cycle)
                    print("\t\t- Cycle " + str(cycleIndex) + ' : ' + str(cycle))


def TestSubscriptionService():
    print("*" * 80)

    print("ReadRecords : ")
    ReadRecordsRet = GlobalValues.subInstance.ReadRecords(0)  # '0' means get all
    ReadRecordsParse(ReadRecordsRet,False)


# Here we only add these two PLC event's functions ,it's enough for this test
# The thread will start while PLC have a Cold/Warm/Hot Start, And stop thread while PLC turn to STOP
def Start():
    print("Start called !")

    sub = SubscriptionService(SUBSCRIPTION_RECORDING, 10)  # '10' is buffer size
    print("Current subscription id is : " + str(sub.GetSubscriptionID()))


    # add variables to this subscription
    ret = sub.AddVariable(("Arp.Plc.Eclr/BOOL001","Arp.Plc.Eclr/MainInstance_500.AA","Arp.Plc.Eclr/MainInstance_500.BB"))
    for _varName, _error in ret.items():
        if _error != 'None':
            print("Error occured while adding '{}' : {}".format(_varName, _error))

    # or use prefix
    ret = sub.AddVariable(("AA", "BB"), prefix='Arp.Plc.Eclr/MainInstance_1000.')
    for _varName, _error in ret.items():
        if _error != 'None':
            print("Error occured while adding '{}' : {}".format(_varName, _error))



    # start subscribe and set sampleRate in micro-seconds
    sub.Subscribe(100000)

    print(sub.GetRecordInfos())

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
print(sub.GetRecordInfos()):

25.06.20 05:15:56.412 root  INFO  - ('None', (('Arp.Plc.Eclr/MainInstance_1000.BB', 'Arp.Plc.Eclr/MainInstance_1000.AA'), ('Arp.Plc.Eclr/MainInstance_500.BB', 'Arp.Plc.Eclr/MainInstance_500.AA'), ('Arp.Plc.Eclr/BOOL001',)))




25.06.20 05:16:02.527 root  INFO  - ********************************************************************************
25.06.20 05:16:02.529 root  INFO  - - DataAccessError : "None"
25.06.20 05:16:02.530 root  INFO  - - Records
25.06.20 05:16:02.531 root  INFO  -      - Task 0
25.06.20 05:16:02.533 root  INFO  -              - Cycle 0 : {'Arp.Plc.Eclr/MainInstance_1000.BB': (False, '2020-06-25T05:16:01.439888'), 'Arp.Plc.Eclr/MainInstance_1000.AA': (False, '2020-06-25T05:16:01.439888')}
25.06.20 05:16:02.535 root  INFO  -              - Cycle 1 : {'Arp.Plc.Eclr/MainInstance_1000.BB': (False, '2020-06-25T05:16:02.439902'), 'Arp.Plc.Eclr/MainInstance_1000.AA': (False, '2020-06-25T05:16:02.439902')}
25.06.20 05:16:02.537 root  INFO  -      - Task 1
25.06.20 05:16:02.540 root  INFO  -              - Cycle 0 : {'Arp.Plc.Eclr/MainInstance_500.BB': (False, '2020-06-25T05:16:00.939926'), 'Arp.Plc.Eclr/MainInstance_500.AA': (False, '2020-06-25T05:16:00.939926')}
25.06.20 05:16:02.543 root  INFO  -              - Cycle 1 : {'Arp.Plc.Eclr/MainInstance_500.BB': (False, '2020-06-25T05:16:01.440025'), 'Arp.Plc.Eclr/MainInstance_500.AA': (False, '2020-06-25T05:16:01.440025')}
25.06.20 05:16:02.545 root  INFO  -              - Cycle 2 : {'Arp.Plc.Eclr/MainInstance_500.BB': (False, '2020-06-25T05:16:01.939913'), 'Arp.Plc.Eclr/MainInstance_500.AA': (False, '2020-06-25T05:16:01.939913')}
25.06.20 05:16:02.549 root  INFO  -              - Cycle 3 : {'Arp.Plc.Eclr/MainInstance_500.BB': (False, '2020-06-25T05:16:02.440049'), 'Arp.Plc.Eclr/MainInstance_500.AA': (False, '2020-06-25T05:16:02.440049')}
25.06.20 05:16:02.551 root  INFO  -      - Task 2
25.06.20 05:16:02.553 root  INFO  -              - Cycle 0 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:00.540216')}
25.06.20 05:16:02.555 root  INFO  -              - Cycle 1 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:00.640092')}
25.06.20 05:16:02.557 root  INFO  -              - Cycle 2 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:00.740088')}
25.06.20 05:16:02.559 root  INFO  -              - Cycle 3 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:00.840165')}
25.06.20 05:16:02.562 root  INFO  -              - Cycle 4 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:00.940274')}
25.06.20 05:16:02.563 root  INFO  -              - Cycle 5 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.040134')}
25.06.20 05:16:02.566 root  INFO  -              - Cycle 6 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.140187')}
25.06.20 05:16:02.569 root  INFO  -              - Cycle 7 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.240175')}
25.06.20 05:16:02.571 root  INFO  -              - Cycle 8 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.340217')}
25.06.20 05:16:02.573 root  INFO  -              - Cycle 9 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.440343')}
25.06.20 05:16:02.575 root  INFO  -              - Cycle 10 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.540194')}
25.06.20 05:16:02.578 root  INFO  -              - Cycle 11 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.640197')}
25.06.20 05:16:02.580 root  INFO  -              - Cycle 12 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.740497')}
25.06.20 05:16:02.582 root  INFO  -              - Cycle 13 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.840174')}
25.06.20 05:16:02.584 root  INFO  -              - Cycle 14 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:01.940279')}
25.06.20 05:16:02.586 root  INFO  -              - Cycle 15 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:02.040174')}
25.06.20 05:16:02.589 root  INFO  -              - Cycle 16 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:02.140171')}
25.06.20 05:16:02.592 root  INFO  -              - Cycle 17 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:02.240171')}
25.06.20 05:16:02.593 root  INFO  -              - Cycle 18 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:02.340214')}
25.06.20 05:16:02.596 root  INFO  -              - Cycle 19 : {'Arp.Plc.Eclr/BOOL001': (False, '2020-06-25T05:16:02.440503')}


'''

# RAW:
'''
('None',(   (
                {'Arp.Plc.Eclr/M1.B': (False, 1592820481699459), 'Arp.Plc.Eclr/M1.A': (False, 1592820481699459)},
            ),
            (
                {'Arp.Plc.Eclr/B': (False, 1592820481700432), 'Arp.Plc.Eclr/A': (False, 1592820481700432)},
                {'Arp.Plc.Eclr/B': (False, 1592820481796731), 'Arp.Plc.Eclr/A': (False, 1592820481796731)},
                {'Arp.Plc.Eclr/B': (False, 1592820481896706), 'Arp.Plc.Eclr/A': (False, 1592820481896706)},
                {'Arp.Plc.Eclr/B': (False, 1592820481996693), 'Arp.Plc.Eclr/A': (False, 1592820481996693)},
                {'Arp.Plc.Eclr/B': (False, 1592820482096679), 'Arp.Plc.Eclr/A': (False, 1592820482096679)},
                {'Arp.Plc.Eclr/B': (False, 1592820482196706), 'Arp.Plc.Eclr/A': (False, 1592820482196706)},
                {'Arp.Plc.Eclr/B': (False, 1592820482296678), 'Arp.Plc.Eclr/A': (False, 1592820482296678)},
                {'Arp.Plc.Eclr/B': (False, 1592820482396673), 'Arp.Plc.Eclr/A': (False, 1592820482396673)},
                {'Arp.Plc.Eclr/B': (False, 1592820482496695), 'Arp.Plc.Eclr/A': (False, 1592820482496695)},
                {'Arp.Plc.Eclr/B': (False, 1592820482596704), 'Arp.Plc.Eclr/A': (False, 1592820482596704)}
            ),
            (
                {'Arp.Plc.Eclr/M2.B': (False, 1592820481796389), 'Arp.Plc.Eclr/M2.A': (False, 1592820481796389)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820481896383), 'Arp.Plc.Eclr/M2.A': (False, 1592820481896383)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820481996381), 'Arp.Plc.Eclr/M2.A': (False, 1592820481996381)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482096367), 'Arp.Plc.Eclr/M2.A': (False, 1592820482096367)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482196461), 'Arp.Plc.Eclr/M2.A': (False, 1592820482196461)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482296377), 'Arp.Plc.Eclr/M2.A': (False, 1592820482296377)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482396371), 'Arp.Plc.Eclr/M2.A': (False, 1592820482396371)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482496372), 'Arp.Plc.Eclr/M2.A': (False, 1592820482496372)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482596375), 'Arp.Plc.Eclr/M2.A': (False, 1592820482596375)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482696385), 'Arp.Plc.Eclr/M2.A': (False, 1592820482696385)}
            )
        )
)
'''


'''
- DataAccessError : "None"
- Records
	- Task 0
		- Cycle 0 : {'Arp.Plc.Eclr/M1.B': (False, 1592820481699459), 'Arp.Plc.Eclr/M1.A': (False, 1592820481699459)}
	- Task 1
		- Cycle 0 : {'Arp.Plc.Eclr/B': (False, 1592820481700432), 'Arp.Plc.Eclr/A': (False, 1592820481700432)}
		- Cycle 1 : {'Arp.Plc.Eclr/B': (False, 1592820481796731), 'Arp.Plc.Eclr/A': (False, 1592820481796731)}
		- Cycle 2 : {'Arp.Plc.Eclr/B': (False, 1592820481896706), 'Arp.Plc.Eclr/A': (False, 1592820481896706)}
		- Cycle 3 : {'Arp.Plc.Eclr/B': (False, 1592820481996693), 'Arp.Plc.Eclr/A': (False, 1592820481996693)}
		- Cycle 4 : {'Arp.Plc.Eclr/B': (False, 1592820482096679), 'Arp.Plc.Eclr/A': (False, 1592820482096679)}
		- Cycle 5 : {'Arp.Plc.Eclr/B': (False, 1592820482196706), 'Arp.Plc.Eclr/A': (False, 1592820482196706)}
		- Cycle 6 : {'Arp.Plc.Eclr/B': (False, 1592820482296678), 'Arp.Plc.Eclr/A': (False, 1592820482296678)}
		- Cycle 7 : {'Arp.Plc.Eclr/B': (False, 1592820482396673), 'Arp.Plc.Eclr/A': (False, 1592820482396673)}
		- Cycle 8 : {'Arp.Plc.Eclr/B': (False, 1592820482496695), 'Arp.Plc.Eclr/A': (False, 1592820482496695)}
		- Cycle 9 : {'Arp.Plc.Eclr/B': (False, 1592820482596704), 'Arp.Plc.Eclr/A': (False, 1592820482596704)}
	- Task 2
		- Cycle 0 : {'Arp.Plc.Eclr/M2.B': (False, 1592820481796389), 'Arp.Plc.Eclr/M2.A': (False, 1592820481796389)}
		- Cycle 1 : {'Arp.Plc.Eclr/M2.B': (False, 1592820481896383), 'Arp.Plc.Eclr/M2.A': (False, 1592820481896383)}
		- Cycle 2 : {'Arp.Plc.Eclr/M2.B': (False, 1592820481996381), 'Arp.Plc.Eclr/M2.A': (False, 1592820481996381)}
		- Cycle 3 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482096367), 'Arp.Plc.Eclr/M2.A': (False, 1592820482096367)}
		- Cycle 4 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482196461), 'Arp.Plc.Eclr/M2.A': (False, 1592820482196461)}
		- Cycle 5 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482296377), 'Arp.Plc.Eclr/M2.A': (False, 1592820482296377)}
		- Cycle 6 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482396371), 'Arp.Plc.Eclr/M2.A': (False, 1592820482396371)}
		- Cycle 7 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482496372), 'Arp.Plc.Eclr/M2.A': (False, 1592820482496372)}
		- Cycle 8 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482596375), 'Arp.Plc.Eclr/M2.A': (False, 1592820482596375)}
		- Cycle 9 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482696385), 'Arp.Plc.Eclr/M2.A': (False, 1592820482696385)}
'''
