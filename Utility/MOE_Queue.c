/******************************************************************************
* File       : MOE_Queue.c
* Function   : General queue function.
* description: This module realize common queue operations, You can create your 
*              own queue in task space or use Moe_Queue_Create() create a queue
*              with malloc. Both methods need a queue information data structure
*              to record basic information used for queue operation. 
*
*              There are two method to use the queue:
*              1。Use the simply API: Moe_Queue_Write() to fill the prepared
*                 data into the queue without checking free buffer block and queue
*                 increase operation; Moe_Queue_Read() to read the data from the
*                 queue into the prepared array without check 0-buffer-block and 
*                 decrease operation.
*              2. For more efficient use, You can fill the buffer block by yourself
*                 with the MACRO MOE_QUEUE_LAST_FREE(p), or read data from queue 
*                 with the MACRO MOE_QUEUE_FIRST_USED(p), please remember to 
*                 check queue is free/queue is NOT empty BEFORE wirting/reading 
*                 by calling Moe_Qeueu_Is_Free()/Moe_Queue_Is_NOT_Empty(); And
*                 increase/decrease the queue AFTER buffer block wirting/reading
*                 by calling Moe_Queue_Inc()/Moe_Queue_Dec.
*
*              Besides, this module provide a general test function which can be
*              used for testing.      
* Version    : V1.00
* Author     : Ian
* Date       : 10th Jun 2016
* History    :  No.  When           Who           What
*               1    10/Jun/2016    Ian           Create
******************************************************************************/

#include "../Pub/type_def.h"
#include "../Pub/common_head.h"
#include "project_config.h"
#include "../Core/MOE_Core.h"
#include "./MOE_Queue.h"
#include "../Pub/debug.h"

/******************************************************************************
* Name       : uint8 Moe_Queue_Create(T_QUEUE_INFO *ptQueueInfo, uint8 u8Len, uint8 u8Cnt)
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
*              If the queue which created by this function is unnecessary, please
*              Call Moe_Queue_Delete() to delete it.
* Version    : V1.00
* Author     : Ian
* Date       : 10th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Create(T_QUEUE_INFO *ptQueueInfo, uint8 u8Len, uint8 u8Cnt)
{
    uint32 u32IntSt;
    uint16 u16Size = u8Len * u8Cnt;

    /* If the buffer size is 0, return NULL */
    MOE_CHECK_IF_RET_ST((NULL == ptQueueInfo), "Invalid pointer!\n");
    MOE_CHECK_IF_RET_ST((0 == u16Size), "The length of buffer is invalid!!\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueueInfo->pu8Addr  = (uint8*)MOE_MALLOC(u16Size);   /* Create data space  */
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
* Name       : uint8 Moe_Queue_Delete(T_QUEUE_INFO *ptQueueInfo)
* Function   : Delete a queue
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: This function is used to free the queue which is created by 
*              Moe_Queue_Create(), NOTE: Please do NOT call this function to 
*              free user queue located in task space (task static RAM usually).
* Version    : V1.00
* Author     : Ian
* Date       : 10th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Delete(T_QUEUE_INFO *ptQueueInfo)
{
    uint32 u32IntSt;

    /* If the pointer of queue information is invalid */
    MOE_CHECK_IF_RET_ST((NULL == ptQueueInfo), "The length of buffer is invalid!!\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    MOE_FREE(ptQueueInfo->pu8Addr);
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Moe_Queue_Inc(T_QUEUE_INFO *ptQueue)
* Function   : Update the end pointer of used block.
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: This function increases the end buffer pointer of the queue, please
*              call this function after free buffer checking and wirting operation.
*              NOTE: Do NOT call such function if  "Moe_Queue_Write()" function is
*              called.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Inc(T_QUEUE_INFO *ptQueue)
{
    uint32 u32IntSt;
    /* If the pointer of queue info is invalid */
    MOE_CHECK_IF_RET_ST((NULL == ptQueue), "Invalid pointer of queue information!!\n");

    /* If the used count is NOT less then the max count */
    MOE_CHECK_IF_RET_ST((ptQueue->u8Cnt >= ptQueue->u8MaxCnt), "The queue is full!!\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueue->u8End = (ptQueue->u8End + 1) % ptQueue->u8MaxCnt;  /* Update end pointer */
    ptQueue->u8Cnt++;                                           /* Update used count  */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Moe_Queue_Inc(T_QUEUE_INFO *ptQueue)
* Function   : Update the begin pointer of used block.
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: This function increases the start buffer pointer of the queue, please
*              call this function after empty buffer checking and reading operation.
*              NOTE: Do NOT call such function if  "Moe_Queue_Read()" function is
*              called.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Dec(T_QUEUE_INFO *ptQueue)
{
    uint32 u32IntSt;
    /* If the pointer of queue info is invalid */
    MOE_CHECK_IF_RET_ST((NULL == ptQueue), "Invalid pointer of queue information!!\n");

    /* If the used count is 0 */
    MOE_CHECK_IF_RET_ST((0 == ptQueue->u8Cnt), "The queue is empty!!\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptQueue->u8Begin = (ptQueue->u8Begin + 1) % ptQueue->u8MaxCnt;  /* Update the begin pointer */
    ptQueue->u8Cnt--;                                               /* Update the used count    */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */   

    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Moe_Queue_Is_Free(T_QUEUE_INFO *ptQueue)
* Function   : Check if the queue is free
* Input      : T_QUEUE_INFO* ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Free.
*              SW_ERR  Not Free.
* description: This function checks if queue is free or NOT by used buffer blocks.
*              Please call this function before queue writing except calling API 
*              "Moe_Queue_Write()".
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Is_Free(T_QUEUE_INFO *ptQueue)
{
    /* If the pointer of queue info is invalid */
    MOE_CHECK_IF_RET_ST((NULL == ptQueue), "Invalid pointer of queue information!!\n");

    /* If the used count is NOT less then the max count */
    MOE_CHECK_IF_RET_ST((ptQueue->u8Cnt >= ptQueue->u8MaxCnt), "The queue is full!!\n");

    DBG_PRINT("The queue is NOT full!!\n");
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Moe_Queue_Is_Not_Empty(T_QUEUE_INFO *ptQueue)
* Function   : Check if the queue is NOT empty
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Not empty.
*              SW_ERR  Empty.
* description: This function checks if queue is Not empty or NOT by used buffer 
*              blocks. Please call this function before queue writing except 
*              calling API "Moe_Queue_Read()".
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Is_Not_Empty(T_QUEUE_INFO *ptQueue)
{
    /* If the pointer of queue info is invalid */
    MOE_CHECK_IF_RET_ST((NULL == ptQueue), "Invalid pointer of queue information!!\n");

    /* If the used count is NOT 0 */
    MOE_CHECK_IF_RET_ST((0 == ptQueue->u8Cnt), "The queue is empty!!\n");

    DBG_PRINT("The queue is NOT empty!!\n");
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Moe_Queue_Write(T_QUEUE_INFO *ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
* Function   : Write into the queue with the desired data
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
*              uint8        *pu8Data        The pointer of data to be writen
*              uint8         u8Len          The length of data to b ewriten
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: This function checks if the queue is free or NOT before data writing,
*              and increases the queue after data writing inside.
*              NOTE: When this function is called, Moe_Queue_Inc() should NOT be
*              called again because it will be done inside of such function.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Write(T_QUEUE_INFO *ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
{
    uint32 u32IntSt;

    /* If the pointer of queue information is invalid */
    MOE_CHECK_IF_RET_ST((NULL == ptQueueInfo)\
                     || (NULL == ptQueueInfo->pu8Addr)\
                     || (NULL == pu8Data),\
                     "Invalid pointer of queue information or data!!\n");
    
    /* Check if the length is wrong */
    MOE_CHECK_IF_RET_ST((u8Len > ptQueueInfo->u8Len), "Invalid length to be writen!!\n");
  
    /* If the used count is NOT less then the max count */
    MOE_CHECK_IF_RET_ST((ptQueueInfo->u8Cnt >= ptQueueInfo->u8MaxCnt), "The queue is full!!\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    for(uint8 u8Idx = 0; u8Idx < u8Len; u8Idx++)
    {
        MOE_QUEUE_LAST_FREE(ptQueueInfo)[u8Idx] = pu8Data[u8Idx];
    }
    ptQueueInfo->u8End = (ptQueueInfo->u8End + 1) % ptQueueInfo->u8MaxCnt;  /* Update end pointer */
    ptQueueInfo->u8Cnt++;                                                   /* Update used count  */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    

    return SW_OK;
    
}

/******************************************************************************
* Name       : uint8 Moe_Queue_Write(T_QUEUE_INFO *ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
* Function   : Write into the queue with the desired data
* Input      : T_QUEUE_INFO *ptQueueInfo    The pointer of queue information data structure
*              uint8        *pu8Data        The pointer of data to be writen
*              uint8         u8Len          The length of data to b ewriten
* Output:    : uint8        *pu8Data        The pointer of data to be writen
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: This function checks if the queue is not empty or NOT before data
*              reading, and decreases the queue after data reading inside.
*              NOTE: When this function is called, Moe_Queue_Dec() should NOT be
*              called again because it will be done inside of such function.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Moe_Queue_Read(T_QUEUE_INFO* ptQueueInfo, uint8 *pu8Data, uint8 u8Len)
{
    uint32 u32IntSt;

    /* If the pointer of queue information is invalid */
    MOE_CHECK_IF_RET_ST((NULL == ptQueueInfo)\
                     || (NULL == ptQueueInfo->pu8Addr)
                     || (NULL == pu8Data),\
                     "Invalid pointer of queue information or data!!\n");
    
    /* Check if the length is wrong */
    MOE_CHECK_IF_RET_ST((u8Len > ptQueueInfo->u8Len), "Invalid length to be read!!\n");
    
    /* If the used count is 0 */
    MOE_CHECK_IF_RET_ST((0 == ptQueueInfo->u8Cnt), "The queue is empty!!\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    for(uint8 u8Idx = 0; u8Idx < u8Len; u8Idx++)
    {
        pu8Data[u8Idx] = MOE_QUEUE_LAST_FREE(ptQueueInfo)[u8Idx];
    }
    ptQueueInfo->u8Begin = (ptQueueInfo->u8Begin + 1) % ptQueueInfo->u8MaxCnt;  /* Update the begin pointer */
    ptQueueInfo->u8Cnt--;                                               /* Update the used count    */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    
    
    return SW_OK;
    
}


/******************************************************************************
* Name       : void Moe_Queue_Test_General(void)
* Function   : General test for queue
* Input      : None
* Output:    : None
* Return     : None
* description: This function is just used for testing, Please do NOT call it
*              in your application codes.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
void Moe_Queue_Test_General(void)
{
    static T_QUEUE_INFO sg_tQueue;
    static uint8 sg_au8DataW[4] = {4,3,2,1};
    static uint8 sg_au8DataR[4] = {0};
    
    Moe_Queue_Create(&sg_tQueue,4,5);
    DBG_PRINT("A queue with 4-byte-length, 5-blocks is created!!\n ");

    /* Fill up the queue with test data */
    while(SW_OK == Moe_Queue_Is_Free(&sg_tQueue))
    {
        Moe_Queue_Write(&sg_tQueue, sg_au8DataW,sizeof(sg_au8DataW));
    }
    
    /* Empty the queue */
    while(SW_OK == Moe_Queue_Is_Not_Empty(&sg_tQueue))
    {
        Moe_Queue_Read(&sg_tQueue, sg_au8DataR,sizeof(sg_au8DataR));
    }    
    
    return;
}

/* end of file */

