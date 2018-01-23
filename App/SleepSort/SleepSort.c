/******************************************************************************
* File       : SleepSort.c
* Function   : Sorting by sleep way
* Description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jan 2018
* History    :  No.  When           Who           What
*               1    23/Jan/2018    Ian           Create
******************************************************************************/

#include "../../Pub/type_def.h"
#include "../../Pub/common_head.h"
#include "project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "../../Core/MOE_Timer.h"
#include "../../Core/MOE_Msg.h"
#include "./SleepSort.h
#include "../../Pub/debug.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : uint8 SleepSort_Process(uint8 u8Evt, void *pPara)
* Function   : Sleep sorting
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* Description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jan 2018
******************************************************************************/
uint8 SleepSort_Process(uint8 u8Evt, void *pPara)
{   
    static uint32 u32Temp = 0x0;
    u32Temp++;
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
            }

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
            Moe_Timer_Periodic(100);
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

