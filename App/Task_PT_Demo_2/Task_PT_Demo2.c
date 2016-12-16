/******************************************************************************
* File       : Task_PT_Demo2.c
* Function   : Another demo task for PT application
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jul 2016
* History    :  No.  When           Who           What
*               1    08/Jul/2016    Ian           Create
******************************************************************************/

#include "../../Pub/type_def.h"
#include "../../Pub/common_head.h"
#include "../../Core/project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "../../Core/MOE_Timer.h"
#include "../../Core/MOE_Msg.h"
#include "../../Core/MOE_PT.h"
#include "./Task_PT_Demo.h"
#include "../../Pub/debug.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : uint8 Task_PT_Demo2_Process(uint8 u8Evt, void *pPara)
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
uint8 Task_PT_Demo2_Process(uint8 u8Evt, void *pPara)
{    
    PT_INIT();
    
    PT_BEGIN();

    /******************************************************************/
    MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
    /******************************************************************/

    while(1)
    {
        printf("I am another Task!!\n");
        PT_DELAY(1000);
    }

    PT_END();

    return SW_OK;

}

/* End of file */


