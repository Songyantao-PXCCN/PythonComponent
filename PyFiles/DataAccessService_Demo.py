try:
    from ArpEmulation import *

    print(f"\033[1;33;44m *** Running '{__name__}' in emulation mode *** \033[0m")
except ImportError:
    pass


def Initialize():
    print("Initialize called !")


def Dispose():
    print("Dispose called !")


def Start():
    print("Start called !")


def Stop():
    print("Stop called !")


def Execute(*arg):
    Value, FaultReason, ValueType = GDS_Read(["Arp.Plc.Eclr/A","Arp.Plc.Eclr/B"])
    # same as Value, FaultReason, ValueType = GDS_Read(["A","B"],prefix="Arp.Plc.Eclr/A")
    pass
