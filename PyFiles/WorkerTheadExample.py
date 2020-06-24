# remember: do not copy 'ArpEmulation' to PLC,
# otherwise that file will overwrite the builtin function of GDS_service from PythonArpComponent
try:
    from ArpEmulation import *
    print(f"\033[1;33;44m *** Running '{__name__}' in emulation mode *** \033[0m")
except ImportError:
    pass

import time, threading


class GlobalValues():
    pass

# this is a basic thread example
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


def threadFunction():
    print("Print from WorkerThread")
    # raise RuntimeError("Exception Test")


def Initialize():
    '''
    PLC冷启或暖启时，本函数将触发
    可在本函数内做变量初始化、对象实例化
    '''
    print("Initialize called !")


def Dispose():
    '''
    PLC冷启或暖启前，本函数将触发,
    应当在本函数中停止所有线程实例。
    当本函数返回时，Python解释器将关闭
    '''
    print("Dispose called !")


def Start():
    '''
    PLC处于运行状态时将触发本函数
    '''
    GlobalValues.wktd = WorkerThread(2,threadFunction)


def Stop():
    '''
    PLC处于停止状态时将触发本函数
    '''
    GlobalValues.wktd.stop()


def Execute(*args):
    '''
    PLC每个扫描周期本函数将被触发
    由Program类CallPyExecute（）传入参数
    :param args: Input of Program (usually is In-Port)
    :return:  Output to Program (usually is Out-Port)
    '''
    # print(*args)
    pass


# for test purpose
if __name__ == "__main__":
    Initialize()
    Start()
    for i in range(100):
        time.sleep(0.1)
        Execute()
    Stop()
    Dispose()
