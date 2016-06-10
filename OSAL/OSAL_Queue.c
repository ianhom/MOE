/******************************************************************************
* File       : OSAL_Queue.c
* Function   : General queue function.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 10th Jun 2016
* History    :  No.  When           Who           What
*               1    10/Jun/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "OSAL.h"
#include "OSAL_Queue.h"
#include "debug.h"


/******************************************************************************
* Name       : uint8 Osal_Queue_Create(uint8 u8Len, uint8 u8Num)
* Function   : Create a queue and return the queue number
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 2nd Jun 2016
******************************************************************************/
uint8 Osal_Queue_Create(uint8 u8Len, uint8 u8Num)
{
    uint32 u32IntSt;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return e;

}


/* end of file */

