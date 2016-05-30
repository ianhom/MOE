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

static T_MSG_HEAD * sg_ptMsgListHead = NULL;  /* Head node of messages */ 
static T_MSG_HEAD * sg_ptMsgListTail = NULL;  /* Tail node of messages */

/******************************************************************************
* Name       : void* Osal_Msg_Create(uint16 u16Size,uint8 u8MsgType)
* Function   : Create a message
* Input      : uint16 u16Size       0~65535   Length of the Message    
*              uint8  u8MsgType     0~255     Type of message
* Output:    : None
* Return     : Pointer of the message data struct.
*              NULL:  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th May 2016
******************************************************************************/
void* Osal_Msg_Create(uint16 u16Size, uint8 u8MsgType, void *ptMsg)
{
    uint32 u32IntSt;
    T_MSG_HEAD *ptMsgHead;
    uint8      *pu8Data;
    
    /* If the length of message is less then a message head */
    if(0 == u16Size)
    {   
        DBG_PRINT("Can NOT create the message!! The length of message is invalid!!\n");
        return NULL;
    }

    /* Check if the message pointer is valid or NOT */
    if(NULL == ptMsg)
    {
        DBG_PRINT("Can NOT create the message!! The message pointer is invalid!!");
        return NULL;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptMsgHead = (T_MSG_HEAD*)OSAL_MALLOC(u16Size + sizeof(T_MSG_HEAD));
    if(NULL != ptMsgHead)
    {
        DBG_PRINT("Create a message successfully!!\n");
        ptMsgHead->ptNext     = NULL;
        ptMsgHead->u16Size    = u16Size;
        ptMsgHead->u8DestTask = TASK_NO_TASK;
        ptMsgHead->u8MsgType  = u8MsgType;
        
        pu8Data = (uint8*)(ptMsgHead + 1); 
        for(uint16 u16Index = 0; u16Index < u16Size; u16Index++)
        {
            *(pu8Data[u16Index] = *((uint8*)ptMsg)[u16Index]);
        }
        
        return (void*)ptMsgHead;
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    DBG_PRINT("Can NOT create the message!! the operation of malloc is failed!!\n");
    return NULL;   
}

/******************************************************************************
* Name       : uint8 Osal_Msg_Send(uint8 u8DestTask,T_MSG_HEAD *ptMsg)
* Function   : Send the message to the destination task.
* Input      : uint8       u8DestTask   0~254    The destination task number
*              T_MSG_HEAD *ptMsg                 The pointer of message 
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 28th May 2016
******************************************************************************/
uint8 Osal_Msg_Send(uint8 u8DestTask,T_MSG_HEAD *ptMsg)
{    
    uint32 u32IntSt;
    
    /* Check if the pointer is valid or NOT */
    if(NULL == ptMsg)
    {
        DBG_PRINT("The message to be sent is invalid!!\n");
        return SW_ERR;
    }
    
    /* Check if the destination task is valid or NOT */
    if(u8DestTask >= MAX_TASK_NUM)
    {
        DBG_PRINT("The destination task of the sending message is invalid!!\n");
        return SW_ERR;
    }

    ptMsg->ptNext = NULL;
    ptMsg->u8DestTask = u8DestTask;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    if(NULL == sg_ptMsgListHead)             /* If there is NO nodes            */
    {
        sg_ptMsgListHead = ptMsg;            /* Add new node as the fisrt one   */
    }
    else                                     /* If node exsits                  */
    {
        sg_ptMsgListTail->ptNext = ptMsg;    /* Add new node after the tail one */
    }
    sg_ptMsgListTail = ptMsg;                /* Update the tail node            */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    
    DBG_PRINT("Message is sent successfully!!\n");
    return SW_OK;
}

/* end of file */

