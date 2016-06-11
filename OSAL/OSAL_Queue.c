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
T_QUEUE_INFO* Osal_Queue_Create(T_QUEUE_INFO* ptQueueInfo, uint8 u8Len, uint8 u8Cnt)
{
    uint32        u32IntSt;
    uint16        u16Size     = u8Len * u8Cnt;

    /* If the buffer size is 0, return NULL */
    if(0 == u16Size)
    {
        DBG_PRINT("The length of buffer is invalid!!\n");
        return NULL;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueueInfo->pu8Addr  = (uint8*)OSAL_MALLOC(u16Size);
    ptQueueInfo->u8Begin  = 0;
    ptQueueInfo->u8End    = 0;
    ptQueueInfo->u8Len    = u8Len;
    ptQueueInfo->u8MaxCnt = u8Cnt;
    ptQueueInfo->u8Cnt    = 0;
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return ptQueueInfo;

}

uint8 Osal_Queue_Inc(T_QUEUE_INFO *ptQueue)
{
    uint32        u32IntSt;
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    if(SW_ERR == Osal_Queue_Is_Free(ptQueue))
    {
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueue->u8End = (ptQueue->u8End + 1) % ptQueue->u8MaxCnt;
    ptQueue->u8Cnt++;
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return SW_OK;
}

uint8 Osal_Queue_Dec(T_QUEUE_INFO *ptQueue)
{
    uint32        u32IntSt;
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    if(SW_OK == Osal_Queue_Is_Empty(ptQueue))
    {
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueue->u8Begin = (ptQueue->u8Begin + 1) % ptQueue->u8MaxCnt;
    ptQueue->u8Cnt--;
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */   

    return SW_OK;
}

uint8 Osal_Queue_Is_Free(T_QUEUE_INFO *ptQueue)
{
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    if(ptQueue->u8Cnt >= ptQueue->u8MaxCnt)
    {
        DBG_PRINT("The queue is full!!\n");
        return SW_ERR;
    }
    DBG_PRINT("The queue is NOT full!!\n");
    return SW_OK;
}

uint8 Osal_Queue_Is_Empty(T_QUEUE_INFO *ptQueue)
{
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    if(0 != ptQueue->u8Cnt)
    {
        DBG_PRINT("The queue is NOT empty!!\n");
        return SW_ERR;
    }
    DBG_PRINT("The queue is empty!!\n");
    return SW_OK;
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

void Osal_Queue_Test_General()
{
    static T_QUEUE_INFO sg_tQueue;
    
    Osal_Queue_Create(&sg_tQueue,5,5);

    while(SW_OK == Osal_Queue_Is_Free(&sg_tQueue))
    {
        for(uint8 u8Idx = 0; u8Idx < 5; u8Idx++)
        {
            OSAL_QUEUE_LAST_FREE(&sg_tQueue)[u8Idx] = u8Idx + 1;
        }
        Osal_Queue_Inc(&sg_tQueue);
    }
    return;
}

/* end of file */

