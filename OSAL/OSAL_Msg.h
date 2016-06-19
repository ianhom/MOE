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
#define __DEBUG_MODE      __DEBUG_MODE_OSAL_MSG       /* According the set from project_config.h */
#endif

#define OSAL_MSG_POLL_NONE          (0)               /* Unnecessary to poll message process     */
#define OSAL_MSG_POLL               (1)               /* Need to poll message process            */

#define MSG_TYPE_TEST               (1)               /* The message type for test               */
#define MSG_TYPE_QUEUE              (2)               /* The message type for queue              */
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


/*******************************************************************************
* Structure  : T_TEST_MSG
* Description: Structure of test message.
* Memebers   : uint32 u32Data                 4-byte format data
*              uint16 au16Data[2]             2-byte format data
*              uint8  au8Data[4]              1-byte format data
*******************************************************************************/
typedef struct _T_TEST_MSG
{
    union
    {
        uint32 u32Data;                       /* 4-byte format data */
        uint16 au16Data[2];                   /* 2-byte format data */
        uint8  au8Data[4];                    /* 1-byte format data */
    }DATA;
}T_TEST_MSG;

/*******************************************************************************
* Structure  : T_QUEUE_MSG
* Description: Structure of queue message.
* Memebers   : T_QUEUE_INFO *ptQueue         Pointer of queue information
*******************************************************************************/
typedef struct _T_QUEUE_MSG
{
    T_QUEUE_INFO *ptQueue;
}T_QUEUE_MSG;


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
uint8* Osal_Msg_Receive(uint8 u8DestTask, uint8 *pu8Type);

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
uint8 Osal_Msg_Forward(void *ptMsg, uint8 u8NextTask);


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
uint8 Osal_Msg_Process();

/******************************************************************************
* Name       : uint16 Osal_Msg_Total_Cnt()
* Function   : Get the max number of total messages in message link list.
* Input      : None
* Output:    : None
* Return     : The max number of total messages in message link list.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th Jun 2016
******************************************************************************/
uint16 Osal_Msg_Total_Cnt();


/******************************************************************************
* Name       : uint16 Osal_Msg_Read_Cnt()
* Function   : Get the max number of read messages
* Input      : None
* Output:    : None
* Return     : The max number of read messages
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jun 2016
******************************************************************************/
uint16 Osal_Msg_Read_Cnt();


/******************************************************************************
* Name       : uint16 Osal_Msg_Unread_Cnt()
* Function   : Get the max number of unread messages
* Input      : None
* Output:    : None
* Return     : The max number of unread messages
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th Jun 2016
******************************************************************************/
uint16 Osal_Msg_Unread_Cnt();

/******************************************************************************
* Name       : void Osal_Msg_Test_General()
* Function   : General test for message
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th Jun 2016
******************************************************************************/
void Osal_Msg_Test_General();

 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_MSG_H_ */

/* End of file */

