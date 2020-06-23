# Python Component

> <address>songyantao@phoenixcontact.com.cn</address>

本项目是PLCnext PLM工程，用于实现在PLCnext控制器上集成Python代码。

This is a PLCnext PLM project , which can realize Python program

Python程序可以作为Task被ESM调用，也可作为后台程序与Task并行执行，这取决于对Python程序的组织方式。

Python program be embed in Task (Trigged by ESM) ,and also can be a background thread , it depends on how to program Python Code

目前支持如下功能：

These Funtion are supported for now :

+ stdout ( print() )

+ stderr  (Exception)

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
+ tips about corss-compile Python Module from C ( such as Scipy ,Numpy ,Opencv)



## How to use 

...



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





