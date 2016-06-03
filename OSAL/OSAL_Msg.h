/******************************************************************************
* File       : OSAL_Msg.h
* Function   : Provide message services.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 26th May 2016
* History    :  No.  When           Who           What
*               1    26/May/2016    Ian           Create
******************************************************************************/

#ifndef _OSAL_MSG_H_
#define _OSAL_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_OSAL_MSG                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_OSAL_MSG       /* According the set from project_config.h   */
#endif

#define OSAL_MSG_POLL_NONE          (0)               /* Unnecessary to poll message process       */
#define OSAL_MSG_POLL               (1)               /* Need to poll message process              */

/*******************************************************************************
* Structure  : T_MSG_HEAD
* Description: Structure of message head.
* Memebers   : struct _T_MSG_HEAD   *ptNext                 Next node of message
*              uint16                u16Size      1~65535   Length of message(NOT includes the head)
*              uint8                 u8DestTask   1~254     The Destination task number
*              uint8                 u8MsgType    0~255     Kind of message types
*              uint8                 u8CopyCnt    0~255     Count for message copy
*              uint8                 u8SrcTask    1~254     The task which sends this message
*              uint8                 au8Data[0];            Data information of the message           
*******************************************************************************/
typedef struct _T_MSG_HEAD
{
    struct _T_MSG_HEAD   *ptNext;   /* Next node of message                      */
    uint16  u16Size;                /* Length of message(NOT includes the head)  */
    uint8   u8DestTask;             /* The Destination task number               */
    uint8   u8MsgType;              /* Kind of message types                     */
    uint8   u8CopyCnt;              /* Count for message copy                    */
    uint8   u8SrcTask;              /* The task which sends this message         */
#ifndef __FLEXIBLE_ARRAY_NOT_SUPPORTED
    uint8   au8Data[0];             /* Data information of the message           */
#endif
}T_MSG_HEAD;



typedef struct _T_TEST_MSG
{
    union _DATA
    {
        uint32 u32Data;
        uint16 au16Data[2];
        uint8  au8Data[4];
    };
}T_TEST_MSG;

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
uint8 Osal_Msg_Send(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg);


 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_MSG_H_ */

/* End of file */

