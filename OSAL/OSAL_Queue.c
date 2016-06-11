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

static uint8  sg_u8No = 0;


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
T_QUEUE_INFO* Osal_Queue_Create(uint8 u8Len, uint8 u8Cnt)
{
    uint32        u32IntSt;
    uint16        u16Size     = u8Len * u8Cnt;
    T_QUEUE_INFO *ptQueueInfo = NULL;

    /* If the buffer size is 0, return NULL */
    if(0 == u16Size)
    {
        DBG_PRINT("The length of buffer is invalid!!\n");
        return NULL;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueueInfo->pu8Addr = (uint8*)OSAL_MALLOC(u16Size);
    ptQueueInfo->u8No    = sg_u8No++;

    /* If the Queue number is bigger than 255 */
    if(0xFF == sg_u8No)
    {
        DBG_PRINT("Too many queue are created!!\n")
        return NULL;
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return ptQueueInfo;

}

void Osal_Queue_Inc(T_QUEUE_INFO *ptQueue)
{
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        
    }
}

/******************************************************************************
* Name       : uint8 Osal_Queue_Delete(T_QUEUE_INFO* ptQueueInfo)
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
uint8 Osal_Queue_Delete(T_QUEUE_INFO* ptQueueInfo)
{
    uint32        u32IntSt;
    T_QUEUE_INFO *ptQueueInfo = NULL;

    /* If the pointer of queue information is invalid */
    if(NULL == ptQueueInfo)
    {
        DBG_PRINT("The length of buffer is invalid!!\n");
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    OSAL_FREE(ptQueueInfo->pu8Addr);
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return SW_OK;


}



/* end of file */

