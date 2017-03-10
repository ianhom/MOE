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
MOE Core             | 任务调度及事件处理模块
MOE message          | 消息机制模块，通过该模块可以实现各个任务之间的通信
MOE Timer            | 软件定时器模块，所有时间相关的服务都由该模块提供：系统计时、任务延时调度、定时器CallBack等。
MOE Queue            | 通用队列操作模块
...                  | 

*********************************************************************************************
*********************************************************************************************

### MOE Core
该模块是MOE系统的核心部分，包含调度及事件驱动机制的处理。
#### uint8 Moe_Init(PF_TIMER_SRC pfSysTm, PF_POLL pfPoll)  

<table aline="center" border="1" width="1000">
    <tr>
        <th width="120">函数原型</th>
        <th width="880">uint8 Moe_Init(PF_TIMER_SRC pfSysTm, PF_POLL pfPoll)</th>
    </tr>
    <tr>
    	<td align="center">文件</td>
	<td><a href="https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c#L77">MOE/Core/MOE_Core.c </a></td>
    </tr>
    <tr>
        <td align="center">功能</td>
        <td>MOE系统的初始化函数，该函数初始化硬件、系统模块及所有任务的初始化操作。</td>
    </tr>
    <tr>
	<td align="center">函数入参</td>
        <td><i>PF_TIMER_SRC pfSysTm</i>：获取系统毫秒时钟的函数。因为时间服务是系统必备，所以此参数<b>必填</b>。<br>
	    <i>PF_POLL pfPoll</i>：需要系统代为轮询的函数。如无轮询函数，此参数<b>填NULL</b>。</td>
    </tr>
    <tr>
    	<td align="center">函数出参</td>
        <td>无</td>
    </tr>
    <tr>
    	<td align="center">返回值</td>
        <td><i>SW_OK</i>: 操作成功<br>
	    <i>SW_ERR</i>：操作失败</td>
    </tr>
    <tr>
    	<td align="center">说明</td>
        <td><b>该函数需要在Moe_Run_System()调用之前调用一次，且全程只能调用一次</b></td>
    </tr>
</table>


--------------------------------------------------------------------------------------------- 
   
#### void Moe_Run_System(void)

<table aline="center" border="1" width="1000">
    <tr>
        <th width="120">函数原型</th>
        <th width="880">void Moe_Run_System(void)</th>
    </tr>
	
    <tr>
    	<td align="center">文件</td>
	<td><a href="https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c#L125">MOE/Core/MOE_Core.c </a></td>
    </tr>
    
    <tr>
        <td align="center">功能</td>
        <td> MOE系统启动函数，进入该函数后将无法退出，所有系统模块及任务的处理都将在该函数中进行。</td>
    </tr>
    
    <tr>
	<td align="center">函数入参</td>
        <td>无</td>
    </tr>
    
    <tr>
    	<td align="center">函数出参</td>
        <td>无</td>
    </tr>
    
    <tr>
    	<td align="center">返回值</td>
        <td>无</td>
    </tr>
    
    <tr>
    	<td align="center">说明</td>
        <td><b>调用该函数之前，必须调用Moe_Init()初始化函数</b></td>
    </tr>
</table>

---------------------------------------------------------------------------------------------

#### uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)
 
<table aline="center" border="1" width="1000">
    <tr>
        <th width="120">函数原型</th>
        <th width="880">uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)</th>
    </tr>
    <tr>
    	<td align="center">文件</td>
	<td><a href="https://github.com/ianhom/MOE/blob/master/Core/MOE_Event.c#L80">MOE/Core/MOE_Event.c </a></td>
    </tr>
    <tr>
        <td align="center">功能</td>
        <td>事件设置函数，通过该函数可以向目标任务设置对应事件。</td>
    </tr>
    <tr>
	<td align="center">函数入参</td>
        <td><i>uint8  u8TaskID</i>：被设置事件的任务ID<br>
	    <i>uint16 u16Evt</i>：被设置事件的类型</td>
    </tr>
    <tr>
    	<td align="center">函数出参</td>
        <td>无</td>
    </tr>
    <tr>
    	<td align="center">返回值</td>
        <td><i>SW_OK</i>: 操作成功<br>
	    <i>SW_ERR</i>：操作失败</td>
    </tr>
    <tr>
    	<td align="center">说明</td>
        <td>无</td>
    </tr>
</table>
---------------------------------------------------------------------------------------------

#### uint8 Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)

<table aline="center" border="1" width="1000">
    <tr>
        <th width="120">函数原型</th>
        <th width="880">uint8 Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)</th>
    </tr>
    <tr>
    	<td align="center">文件</td>
	<td><a href="https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c#L42">MOE/Core/MOE_Core.c </a></td>
    </tr>
    <tr>
        <td align="center">功能</td>
        <td>在内存指定位置写入指定长度的指定数值。</td>
    </tr>
    <tr>
	<td align="center">函数入参</td>
        <td><i>uint8* pDes</i>：被写入内存的起始位置<br>
	    <i>uint8  u8Val</i>：被写入的值<br>
	    <i>uint8  u8Lenl</i>：被写入的指定长度</td>
    </tr>
    <tr>
    	<td align="center">函数出参</td>
        <td>无</td>
    </tr>
    <tr>
    	<td align="center">返回值</td>
        <td><i>SW_OK</i>: 操作成功<br>
	    <i>SW_ERR</i>：操作失败</td>
    </tr>
    <tr>
    	<td align="center">说明</td>
        <td>该函数可用于清空数组、队列等数据，如事件队列初始化。</td>
    </tr>
</table>
---------------------------------------------------------------------------------------------

#### uint8 Moe_Get_Active_Task(void)
   
<table aline="center" border="1" width="1000">
    <tr>
        <th width="120">函数原型</th>
        <th width="880">uint8 Moe_Get_Active_Task(void)</th>
    </tr>
    <tr>
    	<td align="center">文件</td>
	<td><a href="https://github.com/ianhom/MOE/blob/master/Core/MOE_Core.c#L164">MOE/Core/MOE_Core.c </a></td>
    </tr>
    <tr>
        <td align="center">功能</td>
        <td>获取当前正在执行的任务编号。</td>
    </tr>
    <tr>
	<td align="center">函数入参</td>
        <td>无</td>
    </tr>
    <tr>
    	<td align="center">函数出参</td>
        <td>无</td>
    </tr>
    <tr>
    	<td align="center">返回值</td>
        <td><i>TASK_NO_TASK(0)</i>: 无任务在执行<br>
	    <i>1~254</i>：正在执行的任务的编号</td>
    </tr>
    <tr>
    	<td align="center">说明</td>
        <td>无</td>
    </tr>
</table>
---------------------------------------------------------------------------------------------

#### void Moe_Reg_Malloc_Free()
To be done...

---------------------------------------------------------------------------------------------

#### void* Moe_Malloc(uint32 u32Size)
To be done...

---------------------------------------------------------------------------------------------

#### void Moe_Free(void *p)
To be done...   

*********************************************************************************************
*********************************************************************************************

### MOE Message
To be done...   

*********************************************************************************************
*********************************************************************************************

### MOE Timer
To be done...   

*********************************************************************************************
*********************************************************************************************

### MOE Queue
To be done...   

-------------   

### MOE Link List
To be done...


