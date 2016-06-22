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

## Description
To be done...
### MOE Basic
To be done...
#### void Moe_Init()
To be done...
#### void Moe_Reg_Tasks(PF_TASK_PROCESS pfTaskFn)
To be done...
#### void Moe_Run_System()
To be done...
#### uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)
To be done...
#### uint8 Moe_Event_Clr(uint8 u8TaskID, uint16 u16Evt)
To be done...
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
