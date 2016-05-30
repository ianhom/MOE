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
* Input      : uint8  u8DestTask    0~254     The destination task number
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
    uint16 u16Index;

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
        ptMsgHead->u8DestTask = u8DestTask;
        ptMsgHead->u8MsgType  = u8MsgType;
        
#ifdef __FLEXIBLE_ARRAY_NOT_SUPPORTED                     /* If the complier does NOT support flexible array */
        {
            uint8 *pu8Data;
            pu8Data = (uint8*)(ptMsgHead + 1);            /* Calculate the address of the field for data     */
            /* Copy the data from user information to the message */
            for(u16Index = 0; u16Index < u16Size; u16Index++)
            {
                *(pu8Data[u16Index] = *((uint8*)ptMsg)[u16Index]);
            }
        }
#else                                                     /* If the complier DO support flexible array       */
        /* Copy the data from user information to the message */
        for(u16Index = 0; u16Index < u16Size; u16Index++)
        {
            *(ptMsgHead->au8Data[u16Index] = *((uint8*)ptMsg)[u16Index]);
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
* Input      : uint8  u8DestTask    0~254     The destination task number
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
    if(u8DestTask >= MAX_TASK_NUM)
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
    
    DBG_PRINT("Message is sent successfully!!\n");
    return SW_OK;
}

/* end of file */

