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
{   T_TIMER tTm1,tTm2,tTm3;  

    DBG_PRINT("\n***** OSAL-like scheduler V0.01 *****\n");
    
    Timer_Init();
    Osal_Timer_Init(App_GetSystemTime_ms);
    
    Osal_Init();

    tTm.u8TaskID     = 1;
    tTm.u16Evt       = EVENT_TEST;
    tTm.u16Cnt       = OSAL_TMR_INFINITE_CNT;
    tTm.u32TmOut     = 2000;
    tTm.pfTmCallback = NULL;
    tTm.pfTmCallback = NULL;
        
    Osal_Timer_Start(&tTm);
    
    Osal_Run_System();
 
}
/********************************************************************/

