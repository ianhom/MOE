/******************************************************************************
* File       : OSAL_Queue.c
* Function   : General queue function.
* description: This module realize common queue operations, You can create your 
*              own queue in task space or use  Osal_Queue_Create() create a queue
*              with malloc. Both method need a queue information data structure
*              to record basic information used for queue operation. 
*
*              There are two method to use the queue:
*              1。Use the simply API: Osal_Queue_Write() to fill the prepared
*                 data into the queue without checking free buffer block and queue
*                 increase operation; Osal_Queue_Read() to read the data from the
*                 queue into the prepared array without check 0-buffer-block and 
*                 decrease operation.
*              2. For more efficient use, You can fill the buffer block by yourself
*                 with the MARCO OSAL_QUEUE_LAST_FREE(p), or read data from queue 
*                 with the MARCO OSAL_QUEUE_FIRST_USED(p), please remember to 
*                 check queue is free/queue is NOT empty BEFORE wirting/reading 
*                 by calling Osal_Qeueu_Is_Free()/Osal_Queue_Is_NOT_Empty(); And
*                 increase/decrease the queue AFTER buffer block wirting/reading
*                 by calling Osal_Queue_Inc()/Osal_Queue_Dec.
*
*              Besides, this module provide a general test function which can be
*              used for testing.      
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
* Name       : uint8 Osal_Queue_Create(T_QUEUE_INFO *ptQueueInfo, uint8 u8Len, uint8 u8Cnt)
* Function   : Create a queue
* Input      : uint8         u8Len          The length of each block in the queue
*              uint8         u8Cnt          The count of blocks in th queue
* Output:    : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: This function is used to create a quque with malloc, the created
*              queue located in heap space. Also you could create your own queue
*              in your task space with T_QUEUE_INFO type, both way can use queue
*              operation functions: write/read/increase/deccrease.
* Version    : V1.00
* Author     : Ian
* Date       : 10th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Create(T_QUEUE_INFO *ptQueueInfo, uint8 u8Len, uint8 u8Cnt)
{
    uint32 u32IntSt;
    uint16 u16Size = u8Len * u8Cnt;

    /* If the buffer size is 0, return NULL */
    if(0 == u16Size)
    {
        DBG_PRINT("The length of buffer is invalid!!\n");
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueueInfo->pu8Addr  = (uint8*)OSAL_MALLOC(u16Size);  /* Create data space  */
    ptQueueInfo->u8Begin  = 0;                             /* Init begin pointer */
    ptQueueInfo->u8End    = 0;                             /* Init end pointer   */
    ptQueueInfo->u8Cnt    = 0;                             /* Init block count   */
    ptQueueInfo->u8Len    = u8Len;                         /* Set block length   */
    ptQueueInfo->u8MaxCnt = u8Cnt;                         /* Set block count    */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    
  
    DBG_PRINT("Create a queue successfully!!\n");
    return SW_OK;

}

/******************************************************************************
* Name       : uint8 Osal_Queue_Delete(T_QUEUE_INFO *ptQueueInfo)
* Function   : Delete a queue
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 10th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Delete(T_QUEUE_INFO *ptQueueInfo)
{
    uint32 u32IntSt;

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


/******************************************************************************
* Name       : uint8 Osal_Queue_Inc(T_QUEUE_INFO *ptQueue)
* Function   : Update the end pointer of used block.
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Inc(T_QUEUE_INFO *ptQueue)
{
    uint32 u32IntSt;
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    /* If the used count is NOT less then the max count */
    if(ptQueue->u8Cnt >= ptQueue->u8MaxCnt)
    {
        DBG_PRINT("The queue is full!!\n");
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueue->u8End = (ptQueue->u8End + 1) % ptQueue->u8MaxCnt;  /* Update end pointer */
    ptQueue->u8Cnt++;                                           /* Update used count  */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Osal_Queue_Inc(T_QUEUE_INFO *ptQueue)
* Function   : Update the begin pointer of used block.
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Dec(T_QUEUE_INFO *ptQueue)
{
    uint32 u32IntSt;
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    /* If the used count is 0 */
    if(0 == ptQueue->u8Cnt)
    {
        DBG_PRINT("The queue is empty!!\n");
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueue->u8Begin = (ptQueue->u8Begin + 1) % ptQueue->u8MaxCnt;  /* Update the begin pointer */
    ptQueue->u8Cnt--;                                               /* Update the used count    */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */   

    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Osal_Queue_Is_Free(T_QUEUE_INFO *ptQueue)
* Function   : Check if the queue is free
* Input      : T_QUEUE_INFO* ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Free.
*              SW_ERR  Not Free.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Is_Free(T_QUEUE_INFO *ptQueue)
{
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    /* If the used count is NOT less then the max count */
    if(ptQueue->u8Cnt >= ptQueue->u8MaxCnt)
    {
        DBG_PRINT("The queue is full!!\n");
        return SW_ERR;
    }
    DBG_PRINT("The queue is NOT full!!\n");
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Osal_Queue_Is_Not_Empty(T_QUEUE_INFO *ptQueue)
* Function   : Check if the queue is NOT empty
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Not empty.
*              SW_ERR  Empty.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Is_Not_Empty(T_QUEUE_INFO *ptQueue)
{
    /* If the pointer of queue info is invalid */
    if(NULL == ptQueue)
    {
        DBG_PRINT("Invalid pointer of queue informtion!!\n");
        return SW_ERR;
    }

    /* If the used count is NOT 0 */
    if(0 == ptQueue->u8Cnt)
    {
        DBG_PRINT("The queue is empty!!\n");
        return SW_ERR;
    }
    DBG_PRINT("The queue is NOT empty!!\n");
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Osal_Queue_Write(T_QUEUE_INFO *ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
* Function   : Write into the queue with the desired data
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
*              uint8        *pu8Data        The pointer of data to be writen
*              uint8         u8Len          The length of data to b ewriten
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: NOTE: When this function is called, Osal_Queue_Inc() should NOT be
*              called again because it will be done inside of such function.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Write(T_QUEUE_INFO *ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
{
    uint32 u32IntSt;

    /* If the pointer of queue information is invalid */
    if((NULL == ptQueueInfo)||(NULL == ptQueueInfo->pu8Addr) || (NULL == pu8Data))
    {
        DBG_PRINT("Invalid pointer of queue information or data!!\n");
        return SW_ERR;
    }
    
    /* Check if the length is wrong */
    if(u8Len > ptQueueInfo->u8Len)
    {
        DBG_PRINT("Invalid length to be writen!!\n");
        return SW_ERR;
    }
  
    /* If the used count is NOT less then the max count */
    if(ptQueueInfo->u8Cnt >= ptQueueInfo->u8MaxCnt)
    {
        DBG_PRINT("The queue is full!!\n");
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    for(uint8 u8Idx = 0; u8Idx < u8Len; u8Idx++)
    {
        OSAL_QUEUE_LAST_FREE(ptQueueInfo)[u8Idx] = pu8Data[u8Idx];
    }
    ptQueueInfo->u8End = (ptQueueInfo->u8End + 1) % ptQueueInfo->u8MaxCnt;  /* Update end pointer */
    ptQueueInfo->u8Cnt++;                                                   /* Update used count  */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return SW_OK;
    
}

/******************************************************************************
* Name       : uint8 Osal_Queue_Write(T_QUEUE_INFO *ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
* Function   : Write into the queue with the desired data
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
*              uint8        *pu8Data        The pointer of data to be writen
*              uint8         u8Len          The length of data to b ewriten
* Output:    : uint8        *pu8Data        The pointer of data to be writen
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: NOTE: When this function is called, Osal_Queue_Dec() should NOT be
*              called again because it will be done inside of such function.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Read(T_QUEUE_INFO* ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
{
    uint32 u32IntSt;

    /* If the pointer of queue information is invalid */
    if((NULL == ptQueueInfo)||(NULL == ptQueueInfo->pu8Addr) || (NULL == pu8Data))
    {
        DBG_PRINT("Invalid pointer of queue information or data!!\n");
        return SW_ERR;
    }
    
    /* Check if the length is wrong */
    if(u8Len > ptQueueInfo->u8Len)
    {
        DBG_PRINT("Invalid length to be read!!\n");
        return SW_ERR;
    }

    
    /* If the used count is 0 */
    if(0 == ptQueueInfo->u8Cnt)
    {
        DBG_PRINT("The queue is empty!!\n");
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    for(uint8 u8Idx = 0; u8Idx < u8Len; u8Idx++)
    {
         pu8Data[u8Idx] = OSAL_QUEUE_LAST_FREE(ptQueueInfo)[u8Idx];
    }
    ptQueueInfo->u8Begin = (ptQueueInfo->u8Begin + 1) % ptQueueInfo->u8MaxCnt;  /* Update the begin pointer */
    ptQueueInfo->u8Cnt--;                                               /* Update the used count    */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    Osal_Queue_Dec(ptQueueInfo); 

    return SW_OK;
    
}


/******************************************************************************
* Name       : void Osal_Queue_Test_General()
* Function   : General test for queue
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
void Osal_Queue_Test_General()
{
    static T_QUEUE_INFO sg_tQueue;
    static uint8 sg_au8DataW[4] = {4,3,2,1};
    static uint8 sg_au8DataR[4] = {0};
    
    Osal_Queue_Create(&sg_tQueue,4,5);
    DBG_PRINT("A queue with 4-byte-length, 5-blocks is created!!\n ");

    /* Fill up the queue with test data */
    while(SW_OK == Osal_Queue_Is_Free(&sg_tQueue))
    {
        Osal_Queue_Write(&sg_tQueue, sg_au8DataW,sizeof(sg_au8DataW));
    }
    
    /* Empty the queue */
    while(SW_OK == Osal_Queue_Is_Not_Empty(&sg_tQueue))
    {
        Osal_Queue_Read(&sg_tQueue, sg_au8DataR,sizeof(sg_au8DataR));
    }    
    
    return;
}

/* end of file */

