# Python Component

> <address>songyantao@phoenixcontact.com.cn</address>

本项目是PLM工程，用于实现在PLCnext控制器上集成Python代码

This is a PLM project through which we can execute Python program on PLCnext

Python程序可以作为Task被ESM调用，也可作为后台程序与Task并行执行，这取决于对Python程序的组织方式

Python script can be embedded in Task (triggered by ESM) ,and can also be a background thread , it depends on how to program Python Code

目前支持如下功能：

These funtions are supported for now :

+ stdout ( print() ) write to '~/logs/Output.log' (INFO)

+ stderr  ( exception ) write to '~/logs/Output.log' (ERROR)

+ PLC event 

  + Initialize
  + Dispose
  + Start
  + Stop
  + Execute (Task trig)

+ DataAccessService

  + GDS_Read()
  + GDS_Write()

+ SubscriptionService

  + Class SubscriptionService()

Roadmap:

+ ForceService
+ tips about cross-compile Python Module from C ( such as Scipy ,Numpy ,Opencv)



## How to use 

...

Set the program instance name the same with Python script's name (under `/opt/plcnext` )

For example :

The Python script's path is `/opt/plcnext/PLCnextPyTest.py`

then the instance's name of '`Prog_NoPort`' should be '`PLCnextPyTest` in 'Tasks and Events' of Engineer.


## DataAccessService

...

```python
def GDS_Read(variables,preifx,returnType)
def GDS_Write(variablesSet,prefix,forceType)
```



## SubscriptionService

...

```python
Class SubscriptionService()
	def __init__(kind,recordCount = 10)
	def CreateSubscription(kind,recordCount = 10)
	def RecreateSubscription()
	def GetSubscriptionID()
	def SetSubscriptionID(NewID)
	def AddVariable(variables,prefix)
	def RemoveVariable(variables,prefix)
	def Subscribe(sampleRate)
	def Resubscribe(sampleRate)
	def Resubscribe()
	def Unsubscribe()
	def _DeleteSubscription()
	def ReadValues()
	def ReadTimeStampedValues()
	def GetRecordInfos()
	def ReadRecords(count)
```

## DeviceInfoService & DeviceStatusService

```python
def Execute(*args):
    print(DeviceInfo(["VendorName","SerialNumber"],prefix = 'General.'))
    print(DeviceStatus(["Status.Board.Temperature.Centigrade","Status.Cpu.0.Load.Percent"]))

'''
13.07.20 16:36:10.082 root   INFO  - {'VendorName': 'Phoenix Contact', 'SerialNumber': '1357546765'}
13.07.20 16:36:10.175 root   INFO  - {'Status.Board.Temperature.Centigrade': 53, 'Status.Cpu.0.Load.Percent': 21}

'''
```
## CAUTION
1. Never use `exit()` in Python script! otherwise PLCnext will crash and then reboot .

## Known issue
1. Maybe memory Leak when using `SubscriptionService`


