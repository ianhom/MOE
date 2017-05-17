/******************************************************************************
* File       : Moe_main.c
* Function   : Main-start of the project.
* Description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 21st Nov 2016
* History    :  No.  When           Who           What
*               1    21/Nov/2016    Ian           Create
******************************************************************************/
#include "type_def.h"
#include "../../Pub/common_head.h"
#include "./project_config.h"
#include "./Moe_main.h"
#include "../../Pub/debug.h"
#include "../../Core/MOE_Core.h"
#include "Board_Config.h"

const char cg_au8Version[] = MOE_VERSION" ("__DATE__" - " __TIME__ ")";

int main (void)
{      
    uint8 u8Idx;

    Board_Init();  /* Board init */

    /* Print all loaded tasks */
    DBG_PRINT("\n***** %s for %s*****\n", cg_au8Version, PLATFORM_NAME);
    DBG_PRINT("Task count is %d:\n",MAX_TASK_NUM);
    for(u8Idx = 0; u8Idx < MAX_TASK_NUM; u8Idx++)
    {
        DBG_PRINT("---Task No. is %3d : %s.\n", (u8Idx+1),cg_apu8TaskName[u8Idx]);
    }
    DBG_PRINT("\n\n");

    /* Init MOE  */
    Moe_Init(SysTick_GetSysClk, NULL);   

    /* Run MOE */
    Moe_Run();
    
    /* Never reach here */
    return 0;
}

/* End of file */


