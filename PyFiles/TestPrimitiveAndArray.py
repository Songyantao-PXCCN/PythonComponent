# Loopback Test
# Prog_TestPrimitive
# Prog_TestArray

# mode = 0 #=>normal object mode
mode = 1 #=>bytearray object mode
# mode = 2 #=>bytearray object of array element mode (for Prog_TestArray)

def Execute(*args):
    '''
    the Execute() function is called by the ESM task
    :param args: Input of Program (usually is In-Port)
    :return:  Output to Program (usually is Out-Port)
    '''
    global mode
    ret = tuple([arg[mode] for arg in args])
    for t in ret:
        print(t)
    return ret

