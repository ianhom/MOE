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
void* Osal_Msg_Create(uint16 u16Size,uint8 u8MsgType)
{
    uint32 u32IntSt;
    T_MSG_HEAD *ptMsgHead;
    
    /* If the length of message is less then a message head */
    if(u16Size <= sizeof(T_MSG_HEAD))
    {   
        DBG_PRINT("Can NOT create the message!! The length of message is invalid!!\n");
        return NULL;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptMsgHead = (T_MSG_HEAD*)OSAL_MALLOC(u16Size);
    if(NULL != ptMsgHead)
    {
        DBG_PRINT("Create a message successfully!!\n");
        ptMsgHead->ptNext     = NULL;
        ptMsgHead->u16Size    = u16Size - sizeof(T_MSG_HEAD);
        ptMsgHead->u8DestTask = TASK_NO_TASK;
        ptMsgHead->u8MsgType  = u8MsgType;
        return (void*)ptMsgHead;
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    DBG_PRINT("Can NOT create the message!! the operation of malloc is failed!!\n");
    return NULL;   
}

uint8 Osal_Msg_Send(T_MSG_HEAD *ptMsg)
{
    /* Check if the pointer is invalid or NOT */
    if(NULL == ptMsg)
    {
        DBG_PRINT("The message to be sent is invalid!!\n");
        return SW_ERR;
    }
}

/* end of file */

