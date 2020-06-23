# remember: do not copy 'ArpEmulation.py' to PLC,
# otherwise that file will overwrite the builtin function of GDS_service from PythonArpComponent
# and then this script will still run in 'emulation mode'
try:
    from ArpEmulation import *
    print(f"\033[1;33;44m *** Running '{__name__}' in emulation mode *** \033[0m")
except ImportError:
    pass


def Initialize():
    '''
    For each python instance, the PLCnext Technology firmware calls this function first.
    '''
    print("Initialize called !")


def Dispose():
    '''
    During a cold or warm restart,Python Interpreter will be finalized and initialize a new instance.
    after this function return , the current instance will be destructed .
    '''
    print("Dispose called !")


def Start():
    '''
    During a cold, warm or hot restart of the PLC application, the Start() function is
    called after all program objects of the component have been generated.
    '''
    print("Start called !")


def Stop():
    '''
    The Stop() function is called when the PLC application is stopped, before the programs
    are destroyed.
    '''
    print("Stop called !")



def Execute(*arg):
    # print(arg)
    pass


# for test purpose
if __name__ == "__main__":
    import time
    Initialize()
    Start()
    for i in range(100):
        time.sleep(0.1)
        Execute()
    Stop()
    Dispose()
