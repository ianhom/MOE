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

static uint8 sg_au8Num[10] = [2,4,1,6,10,8,1,5,7,3,8,9];
static T_TIMER_NODE tNode;
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
    /* Check which event should be processed */
    switch (u8Evt)
    {
        /* If it is a delay event */
        case EVENT_DELAY:       
        {
            printf("%d",*((uint8*)pPara));
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }
            

        /* If it is a message event */
        case EVENT_INIT:       
        {
            /******************************************************************/
            MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
            /******************************************************************/

            /*--------------------   Add your init code here   ----------------------*/
            tNode.u16Cnt    = 1;
            tNode.u8Evt     = EVENT_DELAY;
            tNode.u8TaskID  = TASK_CURRENT_TASK;
            for(uint8 u8Index = 0; u8Index < 10; u8Index++)
            {
                tNode.u32TmOut  = sg_au8Num[u8Index];
                tNode.u32TmLeft = sg_au8Num[u8Index];
                tTmr.pTskPara   = (void*)(&sg_au8Num[u8Index]);
                Moe_Timer_Start(tNode);
            }
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

