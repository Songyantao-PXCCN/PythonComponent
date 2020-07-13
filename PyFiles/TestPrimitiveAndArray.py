# Loopback Test

# mode = False =>   ByteArray Object Mode
# mode = True =>    Normal Object Mode

mode = False

def Execute(*args):
    '''
    the Execute() function is called by the ESM task
    :param args: Input of Program (usually is In-Port)
    :return:  Output to Program (usually is Out-Port)
    '''
    global mode
    ret = tuple([arg[0 if mode else 1] for arg in args])
    print(ret)
    return ret

