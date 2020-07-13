
def Execute(*args):
    '''
    the Execute() function is called by the ESM task
    :param args: Input of Program (usually is In-Port)
    :return:  Output to Program (usually is Out-Port)
    '''
    print(DeviceInfo(["VendorName","SerialNumber"],prefix = 'General.'))
    print(DeviceStatus(["Status.Board.Temperature.Centigrade","Status.Cpu.0.Load.Percent"]))

'''
13.07.20 16:36:10.082 root   INFO  - {'VendorName': 'Phoenix Contact', 'SerialNumber': '1357546765'}
13.07.20 16:36:10.175 root   INFO  - {'Status.Board.Temperature.Centigrade': 53, 'Status.Cpu.0.Load.Percent': 21}

'''