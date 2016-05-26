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

/*******************************************************************************
* Structure  : T_MSG_HEAD
* Description: Structure of message head.
* Memebers   : void   *ptNext                 Next node of message
*              uint16  u16Size      1~655XX   Length of message(NOT includes the head)
*              uint8   u8DestTask   0~254     The Destination task number
*              uint8   u8MsgType    0~255     Kind of message types
*******************************************************************************/
typedef struct _T_MSG_HEAD
{
    void   *ptNext;             /* Next node of message                     */
    uint16  u16Size;            /* Length of message(NOT includes the head) */
    uint8   u8DestTask;         /* The Destination task number              */
    uint8   u8MsgType;          /* Kind of message types                    */
}T_MSG_HEAD;


 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_MSG_H_ */

/* End of file */

