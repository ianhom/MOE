/*
 * File:        Moe_main.c
 * Purpose:     Main process for PT demo function 
 *              based on FRDM-KL25Z board
 */
#include "common.h"
#include "common_head.h"
#include "project_config.h"
#include "Moe_main.h"
#include "debug.h"
#include "MOE_Core.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "MOE_Queue.h"
#include "Board_Config.h"
#include "KL25_Lpt_Time.h"
#include "Btn_SM_Config.h"
#include "Btn_SM_Module.h"
#include "MOE_HAL_UART.h"
 
/********************************************************************/

__root const char cg_au8Version[] = MOE_VERSION" ("__DATE__" - " __TIME__ ")";

void Poll_Process(void)
{
    return;
}


int main (void)
{      
    uint8 u8Idx;

    Gpio_Init();     /* Init GPIOs */
    Timer_Init();    /* Init Timer */

    /* Print all loaded tasks */
    DBG_PRINT("\n***** %s *****\n", cg_au8Version);
    DBG_PRINT("Task count is %d:\n",MAX_TASK_NUM);
    for(u8Idx = 0; u8Idx < MAX_TASK_NUM; u8Idx++)
    {
        DBG_PRINT("---Task No. is %3d : %s.\n", (u8Idx+1),cg_apu8TaskName[u8Idx]);
    }
    DBG_PRINT("\n\n");

    /* Init MOE  */
    Moe_Init(App_GetSystemTime_ms, Poll_Process);   

    /* Run MOE */
    Moe_Run();
    
    /* Never reach here */
    return 0;
}
/********************************************************************/
