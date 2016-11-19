# API Description of MOE

## Introduction
**MOE** is an event-driven scheduler system for 8/16/32-bit MCUs. . Following features are realised:
- Basic scheduler;
- Multi-task;
- Event driven.
- Software Timer.
- Messages.
- Queue operation for general use.
- And so on....   

This document contains all description of MOE API, and help user for task coding.

## API Description
APIs are classified by different modules:

Module               | Description
-------------------- | -----------------------------
MOE Core             | Scheduler & Event process
MOE message          | Messge mechanism
MOE Timer            | Software timer
MOE Queue            | General queue operation
...                  | ...

------------

### MOE Core
This is the core module of MOE, this module includes event-driven and scheduler。
#### void Moe_Init(void)   

Name            | void Moe_Init(void) 
--------------- | ------------------------------------------------   
File            | [MOE/Core/MOE_Core.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c) 
Function        | Systeom init funciton which init hardware, system module and task init operation.
Input           | None
Output          | None
Return          | None
Note            | **Call this function once only before calling Moe_Run_System()**   


#### void Moe_Run_System(void)

Name            | void Moe_Run_System(void)
--------------- | ------------------------------------------------   
File            | [MOE/Core/MOE_Core.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c) 
Function        | System start function which will never return.
Input           | None
Output          | None
Return          | None
Note            | **Call Moe_Init() once before calling this function**   


#### uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)

Name            | uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)
--------------- | ------------------------------------------------   
File            | [MOE/Core/MOE_Event.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Event.c) 
Function        | Event-Set function                           
Input           | uint8  u8TaskID： ID of the task which accept this event                                            
                | uint16 u16Evt  ： Type of the event
Output          | None
Return          | SW_OK：Successful / SW_ERR：Failed
Note            | None  


#### uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)

Name            | uint8 Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
--------------- | ------------------------------------------------   
File            | [MOE/Core/MOE_Core.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c) 
Function        | Set desired value into desired position of memory with desired length                          
Input           | uint8* pDes  : The start position of the memory to be writen                                      
                | uint8  u8Val : The desired value  
                | uint8  u8Len : The desired length
Output          | None
Return          | SW_OK：Successful / SW_ERR：Failed
Note            | This function is used to  clear memory like event queue.


#### uint8 Moe_Get_Active_Task(void)

Name            | uint8 Moe_Get_Active_Task(void)
--------------- | ------------------------------------------------   
File            | [MOE/Core/MOE_Core.c ](https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c) 
Function        | Get the current active task number。
Input           | None
Output          | None
Return          | TASK_NO_TASK(0)： No task is active
                | 1~254:            The active task number
Note            | None

#### void* Moe_Malloc(uint32 u32Size)
To be done...
#### void Moe_Free(void *p)
To be done...   

------------   

### MOE Timer
To be done...   

------------   

### MOE Message
To be done...   

------------   

### MOE Queue
To be done...   

-------------   

### MOE Link List
To be done...
