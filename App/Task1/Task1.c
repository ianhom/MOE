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
#include "MOE_Core.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "Task1.h"
#include "debug.h"

static uint16 Task1_Process(uint8 u8Evt);

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
    Moe_Reg_Tasks(Task1_Process);
    DBG_PRINT(" APP_TASK_NAME is inited successfully, Task ID is %d\n", sg_u8TaskID);

    /*--------------------   Add your init code here   ----------------------*/
    Moe_Event_Set(sg_u8TaskID, 10, 0);
    /*-------------------   The end of your init code   ---------------------*/
    
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
static uint16 Task1_Process(uint8 u8Evt)
{   

    TASK_EVENT_PROCESS_LIST_START;
    EVENT_PROCESS(EVENT_DELAY,ms);
    TASK_EVENT_PROCESS_LIST_END;

    DBG_PRINT("Hello\n");
    MOE_DELAY(3000,ms);  
    DBG_PRINT("Goodbye\n");
 

#if (0)


/******************************************************************************/
/* Process for message event                                                  */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_MSG); 
    /*-----------------   Add your event process code here   -----------------*/
        ptMsg = (void*)Moe_Msg_Receive(sg_u8TaskID, &u8MsgType);
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
    /*----------------  The end of your event process code  ------------------*/
    EVENT_PROCESS_END(EVENT_MSG);
/******************************************************************************/



/******************************************************************************/
/* Process for test event                                                     */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_TEST);
    /*-----------------   Add your event process code here   -----------------*/
        T_TEST_MSG tMsg;
        tMsg.DATA.u32Data = 0x11223344;
        for(uint8 u8Idx = 0; u8Idx < 100; u8Idx++)
        {
            Moe_Msg_Send(3,MSG_TYPE_TEST,sizeof(tMsg),&tMsg);
        }
        DBG_PRINT("\n\n\nTask %d Send a message\n", sg_u8TaskID);
    /*----------------  The end of your event process code  ------------------*/
    EVENT_PROCESS_END(EVENT_TEST);
/******************************************************************************/
#endif
    return 0;
}

/* End of file */



