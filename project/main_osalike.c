/*
 * File:        osalike.c
 * Purpose:        Main process
 *
 */

#include "common.h"
#include "common_head.h"
#include "project_config.h"
#include "osalike.h"
#include "debug.h"
#include "OSAL.h"
#include "OSAL_Timer.h"
#include "KL25_Lpt_Time.h"




/********************************************************************/
int main (void)
{  

    DBG_PRINT("\n***** OSAL-like scheduler V0.01 *****\n");
    
    Timer_Init();
    Osal_Timer_Init(App_GetSystemTime_ms);
    
    Osal_Init();
    
    Osal_Timer_Start(0,EVENT_TEST,OSAL_TMR_INFINITE_CNT,1000);
    Osal_Timer_Start(1,EVENT_TEST,OSAL_TMR_INFINITE_CNT,1000);
    Osal_Timer_Start(2,EVENT_TEST,OSAL_TMR_INFINITE_CNT,1000);
    
    Osal_Run_System();
 
}
/********************************************************************/

