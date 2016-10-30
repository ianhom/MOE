/******************************************************************************
* File       : Task_PT_Demo.c
* Function   : A demo task for PT application
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jul 2016
* History    :  No.  When           Who           What
*               1    08/Jul/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "MOE_PT.h"
#include "Task_PT_Demo.h"
#include "debug.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

static void (*const TASK_PT_DEMO_LED_Off)(uint8 u8Clr)    = TASK_PT_DEMO_LED_OFF;
static void (*const TASK_PT_DEMO_LED_On)(uint8 u8Clr)     = TASK_PT_DEMO_LED_ON;
//static void (*const TASK_PT_DEMO_LED_Toggle)(uint8 u8Clr) = TASK_PT_DEMO_LED_TOGGLE;

/******************************************************************************
* Name       : uint8 Task_PT_Demo_Process(uint8 u8Evt, void *pPara)
* Function   : A demo task for PT application
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter

* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jul 2016
******************************************************************************/
uint8 Task_PT_Demo_Process(uint8 u8Evt, void *pPara)
{   
    PT_INIT();
    
    PT_BEGIN();

    /******************************************************************/
    MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
    /******************************************************************/

    while(1)
    {
        TASK_PT_DEMO_LED_On(LED_RED);
        PT_DELAY(1000);
        TASK_PT_DEMO_LED_Off(LED_RED);

        TASK_PT_DEMO_LED_On(LED_GREEN);
        PT_DELAY(1000);
        TASK_PT_DEMO_LED_Off(LED_GREEN);

        TASK_PT_DEMO_LED_On(LED_BLUE);
        PT_DELAY(1000);
        TASK_PT_DEMO_LED_Off(LED_BLUE);
    }

    PT_END();

    return SW_OK;

}

/* End of file */

