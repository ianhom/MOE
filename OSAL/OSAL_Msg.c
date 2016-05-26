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
* Name       : void* Osal_Msg_alloc(uint16 u16Size,uint8 u8MsgType)
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
void* Osal_Msg_alloc(uint16 u16Size,uint8 u8MsgType)
{
    uint32 u32IntSt;
    T_MSG_HEAD *ptMsgHead;
    
    if(u16Size <= sizeof(T_MSG_HEAD))
    {
        return NULL;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptMsgHead = (T_MSG_HEAD*)OSAL_MALLOC(u16Size);
    if(NULL != ptMsgHead)
    {
        ptMsgHead->ptNext     = NULL;
        ptMsgHead->u16Size    = u16Size - sizeof(T_MSG_HEAD);
        ptMsgHead->u8DestTask = TASK_NO_TASK;
        ptMsgHead->u8MsgType  = u8MsgType;
        return (void*)ptMsgHead;
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    return NULL;
}

/* end of file */

