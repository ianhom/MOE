/******************************************************************************
* File       : Task1.c
* Function   : It is No. 1 task which is just a demo task
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
#include "Task1.h"
#include "debug.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : void Task1_Init(uint8 u8TaskID)
* Function   : Init task1
* Input      : To be done.
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Task1_Init(uint8 u8TaskID)
{

    sg_u8TaskID = u8TaskID;        /* Get the task ID */

    Osal_Reg_Tasks(Task1_Process);

    DBG_PRINT("Task 1 is inited successfully, Task ID is %d\n", sg_u8TaskID);
    
    return;
}

/******************************************************************************
* Name       : uint16 Task1_Process(uint16 u16Evt)
* Function   : Task 1 process
* Input      : To be done
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint16 Task1_Process(uint16 u16Evt)
{
    uint8  u8MsgType;
    void  *ptMsg;

    if (u16Evt & EVENT_TEST)
    {
        T_TEST_MSG tMsg;
        tMsg.DATA.u32Data = 0x11223344;
        Osal_Msg_Send(TASK_ALL_TASK,MSG_TYPE_TEST,sizeof(tMsg),&tMsg);
        DBG_PRINT("\n\n\nTask %d Send a message\n", sg_u8TaskID);
        return (u16Evt ^ EVENT_TEST);
    }

    if (u16Evt & EVENT_MSG)
    {
        ptMsg = (void*)Osal_Msg_Receive(sg_u8TaskID, NULL, &u8MsgType);
        switch(u8MsgType)
        {
            case MSG_TYPE_TEST:
            {
                T_TEST_MSG *ptTestMsg = (T_TEST_MSG*)ptMsg;
                DBG_PRINT("This is task %d\n",sg_u8TaskID);
                DBG_PRINT("I get a uint32 data 0x%x!\n",(ptTestMsg->DATA.u32Data));
                DBG_PRINT("I get a uint16 data 0x%x,0x%x!\n",(ptTestMsg->DATA.au16Data[0]),(ptTestMsg->DATA.au16Data[1]));
                DBG_PRINT("I get a uint8 data 0x%x,0x%x,0x%x,0x%x!\n",(ptTestMsg->DATA.au8Data[0]),(ptTestMsg->DATA.au8Data[1]),(ptTestMsg->DATA.au8Data[2]),(ptTestMsg->DATA.au8Data[3]));
            }
        }
        return (u16Evt ^ EVENT_MSG);
    }
    return u16Evt;
}

/* End of file */



