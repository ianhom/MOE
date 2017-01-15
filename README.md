# MOE    
![LOGO](https://github.com/ianhom/MOE/blob/master/Documents/Pic/MOE_logo_V0_1e.png?raw=true)    
[中文说明](https://github.com/ianhom/MOE/blob/master/README_CHINESE.md) 
## Introduce
MOE is an event-driven scheduler system for 8/16/32-bit MCUs. MOE means "Minds Of Embedded system", it’s also the name of my lovely baby daughter :smile:    
Features with:   


 | Description   
----------------- | ---------------------------------------------   
[**Event-driven**](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md/#关于事件驱动) | Flexible event queue length, priority event supported.   
[**Timer**](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md/#关于定时器) | Useful ms-timer with callback.   
[**Message**](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md/#再谈消息机制) | Easy-use message API for communication between tasks, To-All-Task message with low RAM comsuption supported.   
[**Debug**](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md/#关于调试选项) | Flexible debug print options for each task or module; Useful easy-assert.  
[**Protothread**](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md/#关于PT协程应用) | Protothread is supported for application module.   


For more discussion, please join our QQ Group: **[475258651](https://jq.qq.com/?_wv=1027&k=41PrZvS)**   

## How to use
- **Step 1**: Port the MOE to your hardware, provide "**system clock in ms**" and "**poll function(if available)**", init and run MOE.  
```c
/* EXAMPLE CODE */
uint16 GetMsClock(void)    /* Function to get ms clock */
{
    return sg_u16SysClk;  /* System ms clock, increased every 1 ms in hardware timer interrupt */
}

void Poll(void)    /* Function to be Polled */
{
    /* Something you want to do by polling */
    return;
}

void main(void)
{
    ....                         /* Board init operation */
    MOE_Init(GetMsClock, Poll);  /* Init MOE with system clock funtion, and poll function(fill "NULL" if NOT available) */
    MOE_Run();                   /* Start MOE            */
    return;
}
```
- **Step 2**: **Create** your own tasks or **re-use** exist app tasks to build your application.   
```c
/* EXAMPLE CODE */
/* Task 1: Blinking LED */
uint8 Task_PT_Demo_Process(uint8 u8Evt, void *pPara)
{   
    PT_INIT();
    PT_BEGIN();
    MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */

    while(1)
    {
        TASK_PT_DEMO_LED_Toggle(LED_RED);
        PT_DELAY(1000);

        TASK_PT_DEMO_LED_Toggle(LED_GREEN);
        PT_DELAY(1000);

        TASK_PT_DEMO_LED_Toggle(LED_BLUE);
        PT_DELAY(1000);
    }
    PT_END();
    return SW_OK;
}
```   

```c
/* EXAMPLE CODE */
/* Task 2: Periodic printing */
uint8 Task_PT_Demo2_Process(uint8 u8Evt, void *pPara)
{    
    PT_INIT(); 
    PT_BEGIN();
    MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */

    while(1)
    {
        DBG_PRINT("I am another Task!!\n");
        PT_DELAY(1000);
    }
    PT_END();
    return SW_OK;
}
```

- **Step 3**: [**Register tasks**](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md/#关于任务注册) in **Project_Config.h** and continue other **configuration** in the same file.   
```c
#define LIST_OF_REG_TASK \
        REG_TASK(Task_PT_Demo_Proces)\
        REG_TASK(Task_PT_Demo2_Proces)
```
- **Step 4**: Run & Enjoy. :smile:   


## Source Tree Structure  
   Folder         |   Description  
    :-----        | :------------   
   [**App/**](https://github.com/ianhom/MOE/tree/master/App)             | App modules which can be re-used in different projects. Please add new app module here for new application requirement
   [**Core/**](https://github.com/ianhom/MOE/tree/master/Core)           | Core files including scheduler, Event-drivern, timer and message.
   [**Cpu/**](https://github.com/ianhom/MOE/tree/master/Cpu)             | Startup and other necessary code for starting MCUs
   [**Driver/**](https://github.com/ianhom/MOE/tree/master/Driver)       | Driver of MCU peripheral and other extended module(sensors or RF parts)
   [**Pub/**](https://github.com/ianhom/MOE/tree/master/Pub)             | Public files including public head file, MACRO and debug file
   [**Utility/**](https://github.com/ianhom/MOE/tree/master/Utility)     | Useful function modules including queue, link list, printf
   [**project/**](https://github.com/ianhom/MOE/tree/master/project)     | Files for specific projects including configuration of SW/HW and the main file
   [**Documents/**](https://github.com/ianhom/MOE/tree/master/Documents) | Description documents including design record, API reference and pictures
   

## Useful Documents
 - [API Description(Chinese)](https://github.com/ianhom/MOE/blob/master/Documents/API_Description_Chinese.md)    
 - [Design Record(Chinese)](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md) 


## Special Thanks 
- :tada:MOE Logo drawing by **Miss Cai Jianan**.:tada:
