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
#include "MOE_Event.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "Task1.h"
#include "debug.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : uint8 Task1_Process(uint8 u8Evt, void *pPara)
* Function   : Task 1 process
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Task1_Process(uint8 u8Evt, void *pPara)
{   
    static uint32 u32Temp = 0x0;
    u32Temp += 0x1;
    /* Check which event should be processed */
    switch (u8Evt)
    {
        /* If it is a timer event */
        case EVENT_PERIODIC:       
        {
            T_TEST_MSG tMsg;

            DBG_PRINT("I am task 1 and I am working!!\n");

            tMsg.DATA.u32Data = u32Temp;
            if(SW_ERR == MOE_MSG_SEND(2, MSG_TYPE_TEST, tMsg))
            {
                DBG_PRINT("Heap is running out!!");
            };
            //Moe_Msg_Send(2, MSG_TYPE_TEST, sizeof(T_TEST_MSG), (void*)&tMsg);

            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a message event */
        case EVENT_MSG:       
        {
            
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a test event */
        case EVENT_TEST:       
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
            Moe_Timer_Periodic(1000);
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

/* End of file */


