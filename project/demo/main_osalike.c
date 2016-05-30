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

    tTm1.u8TaskID     = 0;
    tTm1.u16Evt       = EVENT_TEST;
    tTm1.u16Cnt       = OSAL_TMR_INFINITE_CNT;
    tTm1.u32TmOut     = 1000;
    tTm1.pfTmCallback = NULL;
    tTm1.pfTmCallback = NULL;

    tTm2.u8TaskID     = 1;
    tTm2.u16Evt       = EVENT_TEST;
    tTm2.u16Cnt       = OSAL_TMR_INFINITE_CNT;
    tTm2.u32TmOut     = 1000;
    tTm2.pfTmCallback = NULL;
    tTm2.pfTmCallback = NULL;
    
    tTm3.u8TaskID     = 2;
    tTm3.u16Evt       = EVENT_TEST;
    tTm3.u16Cnt       = OSAL_TMR_INFINITE_CNT;
    tTm3.u32TmOut     = 1000;
    tTm3.pfTmCallback = NULL;
    tTm3.pfTmCallback = NULL;
        
    Osal_Timer_Start(&tTm1);
    Osal_Timer_Start(&tTm2);
    Osal_Timer_Start(&tTm3);
    
    Osal_Run_System();
 
}
/********************************************************************/

