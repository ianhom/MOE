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
static T_MSG_HEAD* Osal_Msg_Del(T_MSG_HEAD *ptMsg);


static T_MSG_HEAD  *sg_ptMsgListHead = NULL;                     /* Head node of messages      */ 
static T_MSG_HEAD  *sg_ptMsgListTail = NULL;                     /* Tail node of messages      */
static uint8        sg_u8MsgPollFlag = OSAL_MSG_POLL_NONE;       /* Message poll request flag  */

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
        ptMsgHead->u8SrcTask  = TASK_CURRENT_TASK;
        if(TASK_ALL_TASK == u8DestTask)
        {
            ptMsgHead->u8CopyCnt  = MAX_TASK_NUM - 1;     /* Message for all tasks                           */
#ifdef __WANTED_A_LIVE_FOX
            ptMsgHead->u8DestTask = TASK_CURRENT_TASK % TASK_LAST_TASK + 1; /* Start with the next task      */
            DBG_PRINT("Fox is ready to kill the next one!!\n");
#else
            /* Check if it is the first task which sends a message to other tasks */
            /* If so, start with the second task                                  */
            /* Otherwise, start with the first task                               */
            ptMsgHead->u8DestTask = TASK_FIRST_TASK + (!(TASK_CURRENT_TASK - TASK_FIRST_TASK));
#endif        
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
                pu8Data[u16Idx] = ((uint8*)ptMsg)[u16Idx];
            }
        }
#else                                                     /* If the complier DO support flexible array       */
        /* Copy the data from user information to the message */
        for(u16Idx = 0; u16Idx < u16Size; u16Idx++)
        {
            ptMsgHead->au8Data[u16Idx] = ((uint8*)ptMsg)[u16Idx];
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
* Name       : uint8* Osal_Msg_Receive(uint8 u8DestTask, uint8 *pu8Type)
* Function   : Receive a message
* Input      : uint8  u8DestTask    1~254     The destination task number
* Output:    : uint8 *pu8Type       0~255     Type of message
* Return     : NULL  Failed.
*              The pointer of the message 
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 31st May 2016
******************************************************************************/
uint8* Osal_Msg_Receive(uint8 u8DestTask, uint8 *pu8Type)
{
    T_MSG_HEAD *ptFind  = sg_ptMsgListHead;
    T_MSG_HEAD *ptFound = NULL;

    /* Check if the task is valid or NOT                                     */
    /* The Destination task should NOT be TASK_NO_TASK, that is meaningless  */
    /* The Destination task should NOT be TASK_ALL_TASK, that is meaningless */
    if((TASK_NO_TASK == u8DestTask ) || (TASK_ALL_TASK == u8DestTask ))
    {
        DBG_PRINT("Invalid task number when receiving a message!!\n");
        return NULL;
    }
  
    /* Check if the pointer is invalid or NOT */
    if(NULL == pu8Type)
    {
        DBG_PRINT("Invalid pointer for message type!!\n");
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
        
        /* If such message is for all task and there are more than 1 forwarding */
        if(ptFound->u8CopyCnt > 1)
        {
            ptFound->u8CopyCnt--;                                        /* Count down the copy count  */
#ifdef __WANTED_A_LIVE_FOX         
            ptFound->u8DestTask = TASK_CURRENT_TASK % TASK_LAST_TASK + 1;/* Stop forward such message  */
            DBG_PRINT("Fox just killed %d!!\n", TASK_CURRENT_TASK);
#else
            /* If the next task is the one which sent this message */
            if(ptFound->u8DestTask == ptFound->u8SrcTask)
            {
                ptFound->u8DestTask += 2;                      /* Forward to the next task   */
                DBG_PRINT("It is a self-message send by %d, ignore!!\n", TASK_CURRENT_TASK);
            }
            else
            {
                ptFound->u8DestTask++;                         /* Forward to the next task   */  
            }                     
#endif
            Osal_Event_Set(ptFound->u8DestTask,EVENT_MSG);     /* Set MSG event to next task */
            DBG_PRINT("The message to all tasks is processed by task %d, ready for next forwarding!!\n", TASK_CURRENT_TASK);
        }
                
        /* If such message is for all task and this is the last forwarding */
        /* Or it is a message for a single task                            */
        else
        {
            ptFound->u8DestTask = TASK_NO_TASK;         /* Stop forwarding message            */
            sg_u8MsgPollFlag    = OSAL_MSG_POLL;        /* Set flag to delete the message     */
            /* If it is a message for all tasks */
            if(0 != ptFound->u8CopyCnt)
            {
#ifdef __WANTED_A_LIVE_FOX
                DBG_PRINT("Fox killed all except self %d!!\n", ptFound->u8SrcTask);                    
#endif
                DBG_PRINT("All tasks have received the message!!\n");
            } 
        }

#ifdef __FLEXIBLE_ARRAY_NOT_SUPPORTED
        return (uint8*)(ptFound + 1);                   /* Return the data of message         */
#else
        return (uint8*)ptFound->au8Data;                /* Return the data of message         */
#endif        
    }
   
    DBG_PRINT("No message is found for task %d!!\n",u8DestTask);
    return NULL;
}

/******************************************************************************
* Name       : uint8 Osal_Msg_Forward(void *ptMsg, uint8 u8NextTask)
* Function   : Forward a message
* Input      : void *ptMsg                    The pointer of the message
*              uint8  u8NextTask    0~254     The next task number which receives 
*                                             such forwarded message
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: Note: If the u8NextTask is the same with u8DestTask, the next task
*                    will be set as TASK_NO_TASK, forward the same message to 
*                    itself is meaningless.
* Version    : V1.00
* Author     : Ian
* Date       : 5th Jun 2016
******************************************************************************/
uint8 Osal_Msg_Forward(void *ptMsg, uint8 u8NextTask)
{
    T_MSG_HEAD *ptFind;

    /* Check if the pointer is invalid or NOT */
    if(NULL == ptMsg)
    {
        DBG_PRINT("Invalid pointer for message!!\n");
        return SW_ERR;
    }

    /* The next task should NOT be TASK_ALL_TASK, can NOT forward the message for all task here */
    /* The next task should NOT be TASK_CURRENT_TASK, can NOT forward the message to itself     */
    if((TASK_ALL_TASK == u8NextTask) || (TASK_CURRENT_TASK == u8NextTask))
    {
        DBG_PRINT("Invalid task number when forwarding a message!!\n");
        return SW_ERR;
    }

    ptFind = ((T_MSG_HEAD*)ptMsg - 1);   /* Get the head of the message */

    /* If it is a message to all task, do NOT forward */
    if(0 != ptFind->u8CopyCnt)
    {
        DBG_PRINT("It is a message to all task, do NOT forward!!\n");
        return SW_ERR;
    }

    /* Set the next task to receive such message */
    ptFind->u8DestTask = u8NextTask;
    Osal_Event_Set(u8NextTask,EVENT_MSG);         /* Call next task to receive message  */
    DBG_PRINT("The message is forwarded to task %d\n",u8NextTask);
    return SW_OK;
}


/******************************************************************************
* Name       : static T_MSG_HEAD* Osal_Msg_Del(T_MSG_HEAD *ptMsg)
* Function   : Detele a message
* Input      : T_MSG_HEAD *ptMsg  The message to be deteled.
* Output:    : None
* Return     : Pointer of the message data struct.
*              NULL:  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 31st May 2016
******************************************************************************/
static T_MSG_HEAD* Osal_Msg_Del(T_MSG_HEAD *ptMsg)
{
    /* Check if the pointer of message to be deteled is invalid or NOT */
    if(NULL == ptMsg)
    {
        DBG_PRINT("The pointer of message to be deteled is invalid!!\n");
        return NULL;
    }
    
    DBG_PRINT("Delete the message now.\n");
    OSAL_FREE(ptMsg);
    return ptMsg;
}

/******************************************************************************
* Name       : uint8 Osal_Msg_Process()
* Function   : Message process function, distribute "all task message" to each
*              task, and delete useless message.
* Input      : None
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 31st May 2016
******************************************************************************/
uint8 Osal_Msg_Process()
{
    T_MSG_HEAD *ptFind;
    T_MSG_HEAD *ptMsg;
    uint32      u32IntSt;
    
    /* If it is unnecessary to process message */
    if(OSAL_MSG_POLL_NONE == sg_u8MsgPollFlag)
    {   /* Return */
        return SW_OK;
    }

    /* Else, need to process message */    
    sg_u8MsgPollFlag = OSAL_MSG_POLL_NONE;       /* Clear the poll flag first */
    DBG_PRINT("Running message process!!\n");

    ptFind = sg_ptMsgListHead;
    while(ptFind != NULL)
    {   
        /* If we find a message with no destination task, detele it */
        if(TASK_NO_TASK == ptFind->u8DestTask)
        {
            ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
            /**************************************************************************************************/
            /* If such message is the first one */
            if(ptFind == sg_ptMsgListHead)
            {
                if(ptFind == sg_ptMsgListTail)                   /* And it is also the last one */
                {
                    sg_ptMsgListHead = NULL;                     
                    sg_ptMsgListTail = NULL;                     /* There is no message         */
                }
                else                                             /* If it is NOT the last one   */
                {
                    sg_ptMsgListHead = sg_ptMsgListHead->ptNext; /* Make next one as the head   */
                }
                Osal_Msg_Del(ptFind);                            /* Free the deleting node      */
            }
            else/* If such message is NOT the first one */                                                  
            {
                ptMsg = sg_ptMsgListHead;                        /* Start with the first one    */
                while(ptMsg != NULL)                             
                {
                    if(ptMsg->ptNext == ptFind)                  /* If we find the previous one */
                    {
                        ptMsg->ptNext = ptFind->ptNext;          /* Delete message from list    */
                        Osal_Msg_Del(ptFind);                    /* Free the deleting node      */
                        DBG_PRINT("The deleting node is free!!\n");
                        if(ptMsg->ptNext == NULL)                
                        {
                            sg_ptMsgListTail = ptMsg;            /* Update the tail message     */
                        }
                        break;
                    }
                    ptMsg = ptMsg->ptNext;                       /* Check next one              */
                }
            }
            /**************************************************************************************************/
            EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
        } 
        ptFind = ptFind->ptNext;
    }
    return SW_OK;
}
/* end of file */
