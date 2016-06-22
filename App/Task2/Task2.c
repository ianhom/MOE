/******************************************************************************
* File       : Task2.c
* Function   : It is No. 2 task which is just a demo task
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "OSAL.h"
#include "OSAL_Timer.h"
#include "OSAL_Msg.h"
#include "Task2.h"
#include "debug.h"

static uint16 Task2_Process(uint16 u16Evt);

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : void Task2_Init(uint8 u8TaskID)
* Function   : Init task2
* Input      : To be done.
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Task2_Init(uint8 u8TaskID)
{
    sg_u8TaskID = u8TaskID;        /* Get the task ID */
    Osal_Reg_Tasks(Task2_Process);
    DBG_PRINT("Task 2 is inited successfully, Task ID is %d\n", sg_u8TaskID);

    /*--------------------   Add your init code here   ----------------------*/

    /*-------------------   The end of your init code   ---------------------*/
    return;
}

/******************************************************************************
* Name       : uint16 Task2_Process(uint16 u16Evt)
* Function   : Task 2 process
* Input      : To be done
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
static uint16 Task2_Process(uint16 u16Evt)
{
    uint8  u8MsgType;
    void  *ptMsg;

/******************************************************************************/
/* Process for message event                                                  */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_MSG); 
    /*-----------------   Add your event process code here   -----------------*/
        ptMsg = (void*)Osal_Msg_Receive(sg_u8TaskID, &u8MsgType);
        while(ptMsg)
        {
            switch(u8MsgType)
            {
                case MSG_TYPE_TEST:
                {
                    T_TEST_MSG *ptTestMsg = (T_TEST_MSG*)ptMsg;
                    DBG_PRINT("This is task %d\n",sg_u8TaskID);
                    DBG_PRINT("I get a uint32 data 0x%x!\n",(ptTestMsg->DATA.u32Data));
                    DBG_PRINT("I get a uint16 data 0x%x,0x%x!\n",(ptTestMsg->DATA.au16Data[0]),(ptTestMsg->DATA.au16Data[1]));
                    DBG_PRINT("I get a uint8 data 0x%x,0x%x,0x%x,0x%x!\n",(ptTestMsg->DATA.au8Data[0]),(ptTestMsg->DATA.au8Data[1]),(ptTestMsg->DATA.au8Data[2]),(ptTestMsg->DATA.au8Data[3]));
                    ptTestMsg->DATA.u32Data = 0xaabbccdd;
                    DBG_PRINT("Task %d change the message and forward it\n",sg_u8TaskID);
                    Osal_Msg_Forward(ptMsg,2);
                }
            }
            ptMsg = (void*)Osal_Msg_Receive(sg_u8TaskID, &u8MsgType);
        }
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


