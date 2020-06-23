# Python Component

> <address>songyantao@phoenixcontact.com.cn</address>

本项目是PLCnext PLM工程，用于实现在PLCnext控制器上集成Python代码。

Python程序可以作为Task被ESM调用，也可作为后台程序与Task并行执行，这取决于对Python程序的组织方式。

目前支持如下功能：

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

    

