/******************************************************************************
* File       : MOE_Msg.c
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
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "MOE_Msg.h"
#include "debug.h"


static T_MSG_HEAD* Moe_Msg_Create(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg);

/******************************************************************************
* Name       : void Moe_Msg_Init(void)
* Function   : Init message function
* Input      : None
* Output:    : None
* Return     : None
* description: None
* Version    : V1.00
* Author     : Ian
* Date       : 27 Jun 2016
******************************************************************************/
void Moe_Msg_Init(void)
{
    return;
}

/******************************************************************************
* Name       : T_MSG_HEAD* Moe_Msg_Create(uint8 *pu8DestTask,uint8 u8MsgType,uint16 u16Size,void *ptMsg)
* Function   : Create a message
* Input      : uint8  pu8DestTask   1~254     The destination task number
*              uint8  u8MsgType     0~255     Type of message
*              uint16 u16Size       0~65535   Length of the Message
*              void *ptMsg                    Pointer of user message information
* Output:    : uint8  pu8DestTask   1~254     The destination task number
* Return     : Pointer of the message data struct.
*              NULL:  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th May 2016
******************************************************************************/
static T_MSG_HEAD* Moe_Msg_Create(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg)
{
    uint32 u32IntSt;
    T_MSG_HEAD *ptMsgHead;
    uint16 u16Idx;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptMsgHead = (T_MSG_HEAD*)MOE_MALLOC(u16Size + sizeof(T_MSG_HEAD));
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    if(NULL != ptMsgHead)
    {
        DBG_PRINT("Create a message successfully!!\n");      
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
            ptMsgHead->u8CopyCnt  = 0;                    /* Message for single tasks                        */
            ptMsgHead->u8DestTask = u8DestTask;
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
* Name       : uint8 Moe_Msg_Send(uint8 u8DestTask,uint8 u8MsgType,uint16 u16Size,void *ptMsg)
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
uint8 Moe_Msg_Send(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg)
{    
    T_MSG_HEAD *ptMsgNode;
       
    /* Check if the destination task is valid or NOT */
    MOE_CHECK_IF_RET_ST(((u8DestTask > MAX_TASK_NUM)\
                      && (TASK_ALL_TASK != u8DestTask)\
                      || (TASK_NO_TASK  == u8DestTask)),\
                          "The destination task of the sending message should be valid!!\n");

    /* If the length of message is less then a message head */
    MOE_CHECK_IF_RET_ST((0 == u16Size),"The length of creating message is 0\n");

    /* Check if the message pointer is valid or NOT */
    MOE_CHECK_IF_RET_ST((ptMsg == NULL),"The message pointer should NOT be NULL\n");

    ptMsgNode = Moe_Msg_Create(u8DestTask, u8MsgType, u16Size, ptMsg);
    
    MOE_CHECK_IF_RET_ST((NULL == ptMsgNode), "Message is NOT created!!\n");

    Moe_Event_Set(ptMsgNode->u8DestTask, EVENT_MSG, MOE_EVENT_NORMAL, ptMsgNode);/* Set a message event to call destination task      */
    
    DBG_PRINT("Message is sent successfully!!\n");
    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Moe_Msg_Forward(void *ptMsg, uint8 u8NextTask)
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
uint8 Moe_Msg_Forward(T_MSG_HEAD *ptMsg, uint8 u8NextTask)
{
    /* Check if the pointer is invalid or NOT */
    if(NULL == ptMsg)
    {
        DBG_PRINT("Invalid pointer for message!!\n");
        return SW_ERR;
    }

    /* The next task should NOT be bigger than the max task number                          */
    /* The next task should NOT be TASK_CURRENT_TASK, can NOT forward the message to itself */
    /* The next task should NOT be TASK_NO_TASK, it is meaningless                          */
    if((u8NextTask > MAX_TASK_NUM) || (TASK_CURRENT_TASK == u8NextTask) || (TASK_NO_TASK == u8NextTask))
    {
        DBG_PRINT("Invalid task number when forwarding a message!!\n");
        return SW_ERR;
    }

    /* If it is a message to all task, do NOT forward */
    if(0 != ptMsg->u8CopyCnt)
    {
        DBG_PRINT("It is a message to all task, do NOT forward!!\n");
        return SW_ERR;
    }

    /* Set the next task to receive such message */
    ptMsg->u8DestTask = u8NextTask;
    ptMsg->u8SrcTask  = TASK_CURRENT_TASK;
    Moe_Event_Set(u8NextTask, EVENT_MSG, MOE_EVENT_NORMAL, ptMsg); /* Call next task to receive message  */
    DBG_PRINT("The message is forwarded to task %d\n",u8NextTask);
    return SW_OK;
}



/******************************************************************************
* Name       : uint8 Moe_Msg_Process(void)
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
uint8 Moe_Msg_Process(T_MSG_HEAD *ptMsg)
{
    if(ptMsg->u8CopyCnt)
    {
        ptMsg->u8CopyCnt--;
        if(ptMsg->u8CopyCnt)
        {
#ifdef __WANTED_A_LIVE_FOX         
            ptMsg->u8DestTask = TASK_CURRENT_TASK % TASK_LAST_TASK + 1;/* Stop forward such message  */
            DBG_PRINT("Fox just killed %d!!\n", TASK_CURRENT_TASK);
#else
            /* If the next task is the one which sent this message */
            if(ptMsg->u8DestTask == ptMsg->u8SrcTask)
            {
                ptMsg->u8DestTask += 2;                      /* Forward to the next task   */
                DBG_PRINT("It is a self-message send by %d, ignore!!\n", TASK_CURRENT_TASK);
            }
            else
            {
                ptMsg->u8DestTask++;                         /* Forward to the next task   */  
            }                     
#endif
            Moe_Event_Set(ptMsg->u8DestTask, EVENT_MSG, MOE_EVENT_NORMAL, ptMsg);/* Set MSG event to next task */
            DBG_PRINT("The message to all tasks is processed by task %d, ready for next forwarding!!\n", TASK_CURRENT_TASK);
            return SW_OK;
        }
                        
        /* If such message is for all task and this is the last forwarding */
        /* Or it is a message for a single task                            */
        else
        {        
            /* If it is a message for all tasks */
#ifdef __WANTED_A_LIVE_FOX
            DBG_PRINT("Fox killed all except herself %d!!\n", ptMsg->u8SrcTask);                    
#endif
            DBG_PRINT("All tasks have received the message!!\n");
        }
    }

    MOE_FREE(ptMsg);

    return SW_OK;
}


/* end of file */

