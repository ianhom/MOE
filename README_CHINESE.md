# MOE   
![LOGO](https://github.com/ianhom/MOE/blob/master/Documents/Pic/MOE_logo_V0_1e.png?raw=true)   
[English](https://github.com/ianhom/MOE/blob/master/README.md) 
## 简介
MOE是一个用于8/16/32位MCU多任务事件驱动型的调度系统。特点如下：   

 | 描述     
----------------- | ---------------------------------------------   
**事件驱动** | 可变的事件队列长度，支持高优先级事件插队.   
**软件定时器** | 实用的软件定时器功能，支持回调.   
**消息机制** | 易用的消息API轻松实现任务间通讯，支持“To All”消息（低RAM消耗）.   
**调试选项** | 灵活的调试选项，每个模块可设置不同的调试信息打印等级;易用的ASSERT.  
**Protothread** | 应用模块支持Protothread的编写方式.

更多讨论欢迎加入我们的QQ群：**475258651**

## 如何使用
- **步骤 1**: 将MOE移植到您的硬件上，并为其提供“系统毫秒时钟”及“需要时刻轮询的函数”，然后初始化并运行MOE.      
```c
/* Function to get ms clock */
uint16 GetMsClock(void)
{
    return sg_u16SysClk;  /* System ms clock, increased every 1 ms in hardware timer interrupt */
}

/* Function to be Polled */
void Poll(void)
{
    /* Something you want to do by polling */
}

void main(void)
{
    .... /* Board init operation */
    MOE_Init(GetMsClock, Poll);
    MOE_Run(); 
    return;
}
```
- **步骤 2**: 创建您的TASK或使用已有的经过测试的TASK来实现你的应用功能.  
```c
uint8 Task1_Process(uint8 u8Evt, void *pPara)
{   
    /* Check which event should be processed */
    switch (u8Evt)
    {
        /* If it is a timer event */
        case EVENT_PERIODIC:       
        {
            DBG_PRINT("I am task 1 and I am working!!\n");
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a message event */
        case EVENT_MSG:       
        {
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a timer event */
        case EVENT_TIMER:       
        {         
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a message event */
        case EVENT_INIT:       
        {
            /******************************************************************/
            MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
            /******************************************************************/

            /*--------------------   Add your init code here   ----------------------*/
            Moe_Timer_Periodic(1500);
            /*-------------------   The end of your init code   ---------------------*/
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is other event */
        default:       
        {
            return u8Evt;     /* Return event to indicate event is NOT processed */
        }
    }
}
```
- **步骤 3**: 在Project_Config.h文件中注册需要运行的TASK，并在该文件中进行其他相关配置.   
```c
#define LIST_OF_REG_TASK \
        REG_TASK(Task1_Process)\
        REG_TASK(Task2_Process)\
        REG_TASK(Task3_Process)
```
- **步骤 4**: 运行，Enjoy.   

## 文档参考
 - [API说明](https://github.com/ianhom/MOE/blob/master/Documents/API_Description_Chinese.md)    
 - [设计笔记](https://github.com/ianhom/MOE/blob/master/Documents/Design_Record.md)    
 
## 特别感谢
- :tada:**蔡嘉楠小姐**对MOE Logo的精心绘制。:tada:
