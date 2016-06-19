/******************************************************************************
* File       : Task_Demo_Queue.c
* Function   : It is demo task for queue
* description: This task creates two queues,one is located in task space, and 
*              the other is created by Queue API. Task sends two messages with 
*              the two queues and recieves the two messages from the queues.           
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
* History    :  No.  When           Who      What
*               1    19/Jun/2016    Ian      V1.00: Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "OSAL.h"
#include "OSAL_Timer.h"
#include "OSAL_Msg.h"
#include "Task_Demo_Queue.h"
#include "debug.h"

static uint16 Task_Demo_Queue_Process(uint16 u16Evt);

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : void Task_Demo_Queue_Init(uint8 u8TaskID)
* Function   : Init task_Demo_Queue
* Input      : To be done.
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
******************************************************************************/
void Task_Demo_Queue_Init(uint8 u8TaskID)
{
    sg_u8TaskID = u8TaskID;        /* Get the task ID */
    Osal_Reg_Tasks(Task_Demo_Queue_Process);
    DBG_PRINT("Task Demo Queue is inited successfully, Task ID is %d\n", sg_u8TaskID);

    /*--------------------   Add your init code here   ----------------------*/

    /*-------------------   The end of your init code   ---------------------*/
    
    return;
}

/******************************************************************************
* Name       : uint16 Task_Demo_Queue_Process(uint16 u16Evt)
* Function   : Task Demo Queue process
* Input      : To be done
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
******************************************************************************/
static uint16 Task_Demo_Queue_Process(uint16 u16Evt)
{
    uint8  u8MsgType;
    void  *ptMsg;

/******************************************************************************/
/* Process for message event                                                  */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_MSG); 
    /*-----------------   Add your event process code here   -----------------*/
       
    /*----------------  The end of your event process code  ------------------*/
    EVENT_PROCESS_END(EVENT_MSG);
/******************************************************************************/


/******************************************************************************/
/* Process for test event                                                     */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_TEST);
    /*-----------------   Add your event process code here   -----------------*/

        DBG_PRINT("This is task %d process function\n", sg_u8TaskID);

    /*----------------  The end of your event process code  ------------------*/
    EVENT_PROCESS_END(EVENT_TEST);
/******************************************************************************/

    return 0;
}

/* End of file */



