/******************************************************************************
* File       : MOE_Msg.h
* Function   : Provide message services.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 26th May 2016
* History    :  No.  When           Who           What
*               1    26/May/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_MSG_H_
#define _MOE_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_MSG                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_MSG        /* According the set from project_config.h */
#endif

#define MOE_MSG_POLL_NONE          (0)                /* Unnecessary to poll message process     */
#define MOE_MSG_POLL               (1)                /* Need to poll message process            */

#define MOE_MSG_RCV_DONE           (1)                /* Task has received the message           */
#define MOE_MSG_RCV_DONE_NONE      (0)                /* Task has NOT received the message       */

#define MSG_TYPE_TEST              (1)                /* The message type for test               */
#define MSG_TYPE_QUEUE             (2)                /* The message type for queue              */

#define MOE_MSG_SEND(DstTsk, MsgType, Msg)     Moe_Msg_Send(DstTsk, MsgType, sizeof(Msg), (void*)(&Msg))

#ifdef __FLEXIBLE_ARRAY_NOT_SUPPORTED
#define MOE_MSG_CONTENT(p)  (p + 1);                  /* Return the data of message         */
#else
#define MOE_MSG_CONTENT(p)  (p->au8Data);             /* Return the data of message         */
#endif      


/*******************************************************************************
* Structure  : T_MSG_HEAD
* Description: Structure of message head.
* Memebers   : uint8                 u8DestTask   1~254     The Destination task number
*              uint8                 u8SrcTask    1~254     The task which sends this message
*              uint8                 u8MsgType    0~255     Kind of message types
*              uint8                 u8CopyCnt    0~255     Count for message copy
*              uint8                 au8Data[0];            Data information of the message           
*******************************************************************************/
typedef struct _T_MSG_HEAD
{
    uint8   u8DestTask;             /* The Destination task number               */    
    uint8   u8SrcTask;              /* The task which sends this message         */
    uint8   u8MsgType;              /* Kind of message types                     */
    uint8   u8CopyCnt;              /* Count for message copy                    */
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


/******************************************************************************
* Name       : void Moe_Msg_Init(void)
* Function   : Init message function
* Input      : None
* Output:    : None
* Return     : None
* description: This function init the receive_done_flag array with all 0
* Version    : V1.00
* Author     : Ian
* Date       : 27 Jun 2016
******************************************************************************/
void Moe_Msg_Init(void);

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
uint8 Moe_Msg_Send(uint8 u8DestTask, uint8 u8MsgType, uint16 u16Size, void *ptMsg);


/******************************************************************************
* Name       : uint8* Moe_Msg_Receive(uint8 u8DestTask, uint8 *pu8Type)
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
uint8* Moe_Msg_Receive(uint8 u8DestTask, uint8 *pu8Type);


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
uint8 Moe_Msg_Forward(void *ptMsg, uint8 u8NextTask);


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
uint8 Moe_Msg_Process(void);

/******************************************************************************
* Name       : void Moe_Msg_Never_Rcv_Check(uint8 u8Task, uint8 u8Evt)
* Function   : Check is the message is received or NOT after the EVENT_MSG task
*              process. 
* Input      : uint8     u8Task   1~254      Task number
*              uint8     u8Evt    0~255      Event number
* Output:    : None 
* Return     : None
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 27th Jun 2016
******************************************************************************/
void Moe_Msg_Never_Rcv_Check(uint8 u8Task, uint8 u8Evt);

/******************************************************************************
* Name       : uint16 Moe_Msg_Total_Cnt(void)
* Function   : Get the max number of total messages in message link list.
* Input      : None
* Output:    : None
* Return     : The max number of total messages in message link list.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th Jun 2016
******************************************************************************/
uint16 Moe_Msg_Total_Cnt(void);


/******************************************************************************
* Name       : uint16 Moe_Msg_Read_Cnt(void)
* Function   : Get the max number of read messages
* Input      : None
* Output:    : None
* Return     : The max number of read messages
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jun 2016
******************************************************************************/
uint16 Moe_Msg_Read_Cnt(void);


/******************************************************************************
* Name       : uint16 Moe_Msg_Unread_Cnt(void)
* Function   : Get the max number of unread messages
* Input      : None
* Output:    : None
* Return     : The max number of unread messages
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th Jun 2016
******************************************************************************/
uint16 Moe_Msg_Unread_Cnt(void);

/******************************************************************************
* Name       : void Moe_Msg_Test_General(void)
* Function   : General test for message
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th Jun 2016
******************************************************************************/
void Moe_Msg_Test_General(void);

 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_MSG_H_ */

/* End of file */

