/*
 * File:        Moe_main.c
 * Purpose:        Main process
 *
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

__root const char version_string[] = MOE_VERSION" ("__DATE__" - " __TIME__ ")";


void Poll_Process(void)
{
    return;
}

int main (void)
{   

    Gpio_Init();
    Timer_Init();

    DBG_PRINT("\n***** %s *****\n", version_string);

    Moe_Init(App_GetSystemTime_ms, Poll_Process);   
    
    Moe_Run();
 
}
/********************************************************************/

