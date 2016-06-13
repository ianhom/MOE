/******************************************************************************
* File       : OSAL_Queue.h
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

#ifndef _OSAL_QUEUE_H_
#define _OSAL_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_OSAL_QUEUE                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_OSAL_QUEUE         /* According the set from project_config.h */
#endif

/* THe last free block can be write */
#define OSAL_QUEUE_LAST_FREE(p)        ((p)->pu8Addr + (p)->u8End * (p)->u8Len)
/* The first used block can be read */
#define OSAL_QUEUE_FIRST_USED(p)       ((p)->pu8Addr + (p)->u8Begin * (p)->u8Len)

/*******************************************************************************
* Structure  : T_QUEUE_INFO
* Description: Structure of queue information.
* Memebers   : uint8 *pu8Addr                  Address of the queue 
*              uint8  u8Begin   0~u8MaxCnt-1   The begin pointer--first used block
*              uint8  u8End     0~u8MaxCnt-1   The end pointer--last free block 
*              uint8  u8Cnt     0~255          The count of used blocks
*              uint8  u8Len     0~255          The length of each block
*              uint8  u8MaxCnt  0~255          The count of total blocks
*******************************************************************************/
typedef struct _T_QUEUE_INFO
{
    uint8 *pu8Addr;                    /* Address of the queue                */
    uint8  u8Begin;                    /* The begin pointer--first used block */
    uint8  u8End;                      /* The end pointer--last free block    */
    uint8  u8Cnt;                      /* The count of used blocks            */
    uint8  u8Len;                      /* The length of each block            */
    uint8  u8MaxCnt;                   /* The count of total blocks           */
}T_QUEUE_INFO;


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
uint8 Osal_Queue_Create(T_QUEUE_INFO *ptQueueInfo, uint8 u8Len, uint8 u8Cnt);

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
uint8 Osal_Queue_Delete(T_QUEUE_INFO *ptQueueInfo);


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
uint8 Osal_Queue_Inc(T_QUEUE_INFO *ptQueue);

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
uint8 Osal_Queue_Dec(T_QUEUE_INFO *ptQueue);

/******************************************************************************
* Name       : uint8 Osal_Queue_Is_Free(T_QUEUE_INFO *ptQueue)
* Function   : Check if the queue is free
* Input      : T_QUEUE_INFO* ptQueueInfo    The pointer of queue information data structure
* Output:    : None
* Return     : SW_OK   Free.
*              SW_ERR  Not free.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 11th Jun 2016
******************************************************************************/
uint8 Osal_Queue_Is_Free(T_QUEUE_INFO *ptQueue);

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
uint8 Osal_Queue_Is_Not_Empty(T_QUEUE_INFO *ptQueue);

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
uint8 Osal_Queue_Write(T_QUEUE_INFO *ptQueueInfo, uint8 *pu8Data, uint8 u8Len);

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
uint8 Osal_Queue_Read(T_QUEUE_INFO* ptQueueInfo, uint8 *pu8Data, uint8 u8Len);


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
void Osal_Queue_Test_General();

 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_QUEUE_H_ */

/* End of file */

