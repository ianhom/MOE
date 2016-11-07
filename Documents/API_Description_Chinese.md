# MOE的API说明

## 简介
**MOE**是一个用于8/16/32位MCU的事件驱动型调度系统，已实现如下功能：   
- 基本调度功能；
- 多任务；
- 事件驱动；
- 软件定时器；
- 消息机制；
- 通用队列操作；
- 其它...   

本文档包含MOE的所有API详细描述，以帮助用户编写应用程序。

## API描述
MOE的API按如下模块进行分类

Module               | Description
-------------------- | -----------------------------
MOE Core             | 调度&事件处理模块
MOE message          | 消息机制模块
MOE Timer            | 软件定时器模块
MOE Queue            | 通用队列操作模块
...                  | ...

------------

### MOE Core
该模块是MOE系统的核心部分，包含调度及事件驱动机制的处理。
#### void Moe_Init(void)   

函数名           | void Moe_Init(void) 
--------------- | ------------------------------------------------   
文件             | [MOE/Core/MOE_Core.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c) 
功能             | MOE系统的初始化函数，该函数初始化硬件、系统模块及所有任务的初始化操作。
函数入参         | 无
函数出参         | 无
返回值           | 无
说明             | **该函数需要在Moe_Run_System()调用之前调用一次，且全程只能调用一次。**   


#### void Moe_Run_System(void)

函数名           | void Moe_Run_System(void)
--------------- | ------------------------------------------------   
文件             | [MOE/Core/MOE_Core.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c) 
功能             | MOE系统启动函数，进入该函数后将无法退出，所有系统模块及任务的处理都将在该函数中进行。
函数入参         | 无
函数出参         | 无
返回值           | 无
说明             | **调用该函数之前，必须调用Moe_Init()初始化函数。**   


#### uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)

函数名           | uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)
--------------- | ------------------------------------------------   
文件             | [MOE/Core/MOE_Event.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Event.c) 
功能             | 事件设置函数，通过该函数可以向目标任务设置对应事件。                           
函数入参         | uint8 u8TaskID： 被设置事件的任务ID                                             
                | uint16 u16Evt： 被设置事件的类型
函数出参         | 无
返回值           | SW_OK：操作成功 / SW_ERR：操作失败
说明             | 无   


#### uint8 Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
To be done...
#### uint8 Moe_Get_Acktive_Task()
To be done...
#### void Moe_Reg_Malloc_Free()
To be done...
#### void* Moe_Malloc(uint32 u32Size)
To be done...
#### void Moe_Free(void *p)
To be done...   

------------   

### MOE Message
To be done...   

------------

### MOE Timer
To be done...   

------------

### MOE Queue
To be done...   

-------------   

### MOE Link List
To be done...
