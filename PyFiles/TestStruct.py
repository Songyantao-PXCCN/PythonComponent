

class udtSub_t():
    def __init__(self):
        self.xBOOL = False
        self.iArray10 = [0 for i in range(10)]
        
class udtOUT_1_t():
    def __init__(self):
        self.sSTRING = ''
        self.xBOOL = False
        self.iINT = 0
class udtOUT_2_t():
    
    def __init__(self):
        self.arrLWORD3 = [0 for i in range(3)]
        self.arrWORD3 = [0 for i in range(3)]
        self.stSub3 = [udtSub_t() for i in range(3)]
        
def Execute(udtIN_1_val,udtIN_2_val):
    '''
    the Execute() function is called by the ESM task
    :param args: Input of Program (usually is In-Port)
    :return:  Output to Program (usually is Out-Port)
    '''
    print("*"*80)
    print(udtIN_1_val)
    print(udtIN_2_val)
    
    print("--- udtIN_1_val:")
    print("------ xBOOL :"+str(udtIN_1_val.xBOOL))
    print("------ iINT  :"+str(udtIN_1_val.iINT))
    print("------ dwDWORD:"+str(udtIN_1_val.dwDWORD))
    print("------ sSTRING:"+str(udtIN_1_val.sSTRING))
    print("")
    print("--- udtIN_2_val:")
    print("------ iArray5 :"+str(udtIN_2_val.iArray5))
    print("------ rArray10:"+str(udtIN_2_val.rArray10))
    print("------ dwArray3:"+str(udtIN_2_val.dwArray3))
    print("------ stSub   :")
    print("------------- xBOOL   :"+str(udtIN_2_val.stSub.xBOOL))
    print("------------- iArray10:"+str(udtIN_2_val.stSub.iArray10))
    
    o1 = udtOUT_1_t()
    o1.sSTRING = "Hello..."
    o1.xBOOL = True
    o1.iINT = 100
    
    o2 = udtOUT_2_t()
    o2.arrLWORD3 = [11,22,33]
    o2.arrWORD3 = [bytearray.fromhex("BBAA"),bytearray.fromhex("DDCC"),bytearray.fromhex("FFEE")]
    o2.stSub3[0].xBOOL = True
    o2.stSub3[1].iArray10 = [123 for i in range(10)]
    
    return o1,o2


    '''
13.07.20 16:32:53.025 root   INFO  - --- udtIN_1_val:
13.07.20 16:32:53.025 root   INFO  - ------ xBOOL :True
13.07.20 16:32:53.025 root   INFO  - ------ iINT  :5555
13.07.20 16:32:53.025 root   INFO  - ------ dwDWORD:bytearray(b'\x00\x00\x00\x00')
13.07.20 16:32:53.025 root   INFO  - ------ sSTRING:55555
13.07.20 16:32:53.025 root   INFO  -
13.07.20 16:32:53.025 root   INFO  - --- udtIN_2_val:
13.07.20 16:32:53.025 root   INFO  - ------ iArray5 :(0, 0, 0, 0, 0)
13.07.20 16:32:53.025 root   INFO  - ------ rArray10:(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
13.07.20 16:32:53.025 root   INFO  - ------ dwArray3:(bytearray(b'\x00\x00\x00\x00'), bytearray(b'\x00\x00\x00\x00'), bytearray(b'\x00\x00\x00\x00'))
13.07.20 16:32:53.025 root   INFO  - ------ stSub   :
13.07.20 16:32:53.025 root   INFO  - ------------- xBOOL   :False
13.07.20 16:32:53.026 root   INFO  - ------------- iArray10:(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)


    udtIN_1_t : Prog_TestStruct1
        xBOOL   : BOOL;
        iINT    :  INT;
        dwDWORD : DWORD;
        sSTRING : STRING;
    END_Prog_TestStruct1
    
    udtSub_t : Prog_TestStruct1
        xBOOL   : BOOL;
        iArray10: ARRAY[0..9] OF INT;
    END_Prog_TestStruct1
    
    udtIN_2_t : Prog_TestStruct1
        iArray5 : ARRAY[0..4] OF INT;
        rArray10: ARRAY[0..9] OF REAL;
        dwArray3: ARRAY[0..2] OF DWORD;
        stSub   : udtSub_t;
    END_Prog_TestStruct1
    
    udtOUT_1_t : Prog_TestStruct1
        sSTRING : STRING;
        xBOOL   : BOOL;
        iINT    : INT;
    END_Prog_TestStruct1
    
    udtOUT_2_t : Prog_TestStruct1
        arrLWORD3: ARRAY[0..2] OF LWORD;
        arrWORD3 : ARRAY[0..2] OF WORD;
        stSub3   : ARRAY[0..2] OF udtSub_t;
    END_Prog_TestStruct1

    

'''