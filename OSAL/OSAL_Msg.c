/******************************************************************************
* File       : OSAL_Msg.c
* Function   : Provide message services.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 26th May 2016
* History    :  No.  When           Who           What
*               1    26/May/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "OSAL.h"
#include "OSAL_Msg.h"
#include "debug.h"

static T_MSG_HEAD* Osal_Msg_Create(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg);


static T_MSG_HEAD * sg_ptMsgListHead = NULL;  /* Head node of messages */ 
static T_MSG_HEAD * sg_ptMsgListTail = NULL;  /* Tail node of messages */

/******************************************************************************
* Name       : T_MSG_HEAD* Osal_Msg_Create(uint8 u8DestTask,uint8 u8MsgType,uint16 u16Size,void *ptMsg)
* Function   : Create a message
* Input      : uint8  u8DestTask    1~254     The destination task number
*              uint8  u8MsgType     0~255     Type of message
*              uint16 u16Size       0~65535   Length of the Message
*              void *ptMsg                    Pointer of user message information
* Output:    : None
* Return     : Pointer of the message data struct.
*              NULL:  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th May 2016
******************************************************************************/
static T_MSG_HEAD* Osal_Msg_Create(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg)
{
    uint32 u32IntSt;
    T_MSG_HEAD *ptMsgHead;
    uint16 u16Idx;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptMsgHead = (T_MSG_HEAD*)OSAL_MALLOC(u16Size + sizeof(T_MSG_HEAD));
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    if(NULL != ptMsgHead)
    {
        DBG_PRINT("Create a message successfully!!\n");
        ptMsgHead->ptNext     = NULL;         
        ptMsgHead->u16Size    = u16Size;
        ptMsgHead->u8MsgType  = u8MsgType;
        if(TASK_ALL_TASK == u8DestTask)
        {
            ptMsgHead->u8DestTask = TASK_NO_TASK;
            ptMsgHead->u8CopyCnt  = MAX_TASK_NUM;         /* Message for all tasks                           */
        }
        else
        {
            ptMsgHead->u8DestTask = u8DestTask;
            ptMsgHead->u8CopyCnt  = 0;                    /* Message for single tasks                        */
        }
#ifdef __FLEXIBLE_ARRAY_NOT_SUPPORTED                     /* If the complier does NOT support flexible array */
        {
            uint8 *pu8Data;
            pu8Data = (uint8*)(ptMsgHead + 1);            /* Calculate the address of the field for data     */
            /* Copy the data from user information to the message */
            for(u16Idx = 0; u16Idx < u16Size; u16Idx++)
            {
                *(pu8Data[u16Idx] = *((uint8*)ptMsg)[u16Idx]);
            }
        }
#else                                                     /* If the complier DO support flexible array       */
        /* Copy the data from user information to the message */
        for(u16Idx = 0; u16Idx < u16Size; u16Idx++)
        {
            *(ptMsgHead->au8Data[u16Idx] = *((uint8*)ptMsg)[u16Idx]);
        }
#endif        
        return ptMsgHead;
    }

    DBG_PRINT("Can NOT create the message!! the operation of malloc is failed!!\n");
    return NULL;   
}

/******************************************************************************
* Name       : uint8 Osal_Msg_Send(uint8 u8DestTask,uint8 u8MsgType,uint16 u16Size,void *ptMsg)
* Function   : Send the message to the destination task.
* Input      : uint8  u8DestTask    1~254     The destination task number
*              uint8  u8MsgType     0~255     Type of message
*              uint16 u16Size       0~65535   Length of the Message
*              void *ptMsg                    Pointer of user message information
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 28th May 2016
******************************************************************************/
uint8 Osal_Msg_Send(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg)
{    
    uint32 u32IntSt;
    T_MSG_HEAD *ptMsgNode;
       
    /* Check if the destination task is valid or NOT */
    if((u8DestTask > MAX_TASK_NUM) && (u8DestTask != TASK_ALL_TASK))
    {
        DBG_PRINT("The destination task of the sending message is invalid!!\n");
        return SW_ERR;
    }

    /* If the length of message is less then a message head */
    if(0 == u16Size)
    {   
        DBG_PRINT("Can NOT create the message!! The length of message is invalid!!\n");
        return SW_ERR;
    }

    /* Check if the message pointer is valid or NOT */
    if(NULL == ptMsg)
    {
        DBG_PRINT("Can NOT create the message!! The message pointer is invalid!!\n");
        return SW_ERR;
    }

    ptMsgNode = Osal_Msg_Create(u8DestTask, u8MsgType, u16Size, ptMsg);
    if(NULL == ptMsgNode)
    {
        DBG_PRINT("Message is NOT created!!\n");
        return SW_ERR;
    }


    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    if(NULL == sg_ptMsgListHead)                 /* If there is NO nodes            */
    {
        sg_ptMsgListHead = ptMsgNode;            /* Add new node as the fisrt one   */
    }
    else                                         /* If node exsits                  */
    {
        sg_ptMsgListTail->ptNext = ptMsgNode;    /* Add new node after the tail one */
    }
    sg_ptMsgListTail = ptMsgNode;                /* Update the tail node            */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    
    Osal_Event_Set(u8DestTask,EVENT_MSG);        /* Set a message event to call destination task      */

    DBG_PRINT("Message is sent successfully!!\n");
    return SW_OK;
}

/******************************************************************************
* Name       : uint8* Osal_Msg_Receive(uint8 u8DestTask , uint8 u8NextTask)
* Function   : Send the message to the destination task.
* Input      : uint8  u8DestTask    1~254     The destination task number
*              uint8  u8NextTask    0~254     The next task number which receives 
*                                             such forwarded message
* Output:    : uint8 *pu8Type       0~255     Type of message
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: Note: If the u8NextTask is the same with u8DestTask, the next task
*                    will be set as TASK_NO_TASK, forward the same message to 
*                    itself is meaningless.
* Version    : V1.00
* Author     : Ian
* Date       : 31st May 2016
******************************************************************************/
uint8* Osal_Msg_Receive(uint8 u8DestTask , uint8 u8NextTask, uint8 *pu8Type)
{
    T_MSG_HEAD *ptFind  = sg_ptMsgListHead;
    T_MSG_HEAD *ptFound = NULL;
    uint8      *ptData  = NULL;

    /* Check if the task is valid or NOT                                                        */
    /* The Destination task should NOT be TASK_NO_TASK, that is meaningless                     */
    /* The Destination task should NOT be TASK_ALL_TASK, that is meaningless                    */
    /* The Next task should NOT be TASK_ALL_TASK, can NOT forward the message for all task here */
    if((TASK_NO_TASK == u8DestTask ) || (TASK_ALL_TASK == u8DestTask ) ||(TASK_ALL_TASK == u8NextTask))
    {
        DBG_PRINT("Invalid task number when receiving a message!!\n");
        return NULL;
    }

    /* Try to find the message */
    while(ptFind != NULL)
    {
        if(ptFind->u8DestTask == u8DestTask)           /* If the message is found            */
        {
            if(NULL == ptFound)                        /* If we have NOT found anyone before */
            {
                DBG_PRINT("A new message is found!!\n");
                ptFound = ptFind;                      /* Set such as the one we found       */
            }
            else                                       /* If we have found one before        */
            {
                DBG_PRINT("There are more messages for task %d!!\n",u8DestTask);
                Osal_Event_Set(u8DestTask ,EVENT_MSG); /* Set message event for next receive */
                break;                                 /* Stop following message checking    */
            }
        }
        ptFind = ptFind->ptNext;                       /* Continue check next message        */
    }

    /* If we have found a message */
    if(NULL != ptFound)
    {
        *pu8Type = ptFound->u8MsgType;                 /* Output the type of message         */
        
        /* If such message is for all task */
        /* Or, if next task is itself      */
        if((0 != ptFound->u8CopyCnt) || (u8DestTask == u8NextTask))
        {
            ptFound->u8DestTask = TASK_NO_TASK;        /* Stop forward such message          */
            DBG_PRINT("The message is unnecessary to be forwarded!!\n");
        }
        else
        {
            ptFound->u8DestTask = u8NextTask;          /* Otherwise, forward such message    */
            DBG_PRINT("The message is forwarded to task %d\n",u8NextTask);

        }
#ifdef __FLEXIBLE_ARRAY_NOT_SUPPORTED
        return (uint8*)(ptFind + 1);                   /* Return the data of message         */
#else
        return (uint8*)ptFind->au8Data;                /* Return the data of message         */
#endif        
    }
   
    DBG_PRINT("No message is found for task %d!!\n",u8DestTask);
    return NULL;
}

uint8* Osal_Msg_Process()
{
    T_MSG_HEAD *ptFind = sg_ptMsgListHead;
    
    while(ptFind != NULL)
    {
        if(TASK_NO_TASK == ptFind->u8DestTask)
        {
            if(0 != ptFind->u8CopyCnt)
            {
                ptFind->u8DestTask = 1 + MAX_TASK_NUM - ptFind->u8CopyCnt;
                ptFind->u8CopyCnt--;
                Osal_Event_Set(ptFind->u8DestTask,EVENT_MSG);
            }
            
            
        }
        
        ptFind = ptFind->ptNext;
    }
}
/* end of file */

