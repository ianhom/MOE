/*
 * File:        osalike.c
 * Purpose:        Main process
 *
 */

#include "common.h"
#include "common_head.h"
#include "OSAL.h"
#include "OSAL_Timer.h"
#include "KL25_Lpt_Time.h"


/********************************************************************/
int main (void)
{  

    DBG_PRINT("\n\n\n\n");
    
    Timer_Init();
    Osal_Timer_Init(App_GetSystemTime_ms);

    Osal_Timer_Test_General();
    
    Osal_Init();
    
    Osal_Event_Set(1,EVENT_TEST);
    Osal_Event_Set(1,EVENT_TEST);
    Osal_Event_Clr(1,EVENT_TEST);
    
    Osal_Run_System();
 
}
/********************************************************************/

