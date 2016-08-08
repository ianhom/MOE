/******************************************************************************
* File       : MOE_Event.h
* Function   : Provide event services.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jun 2016
* History    :  No.  When           Who           What
*               1    21/Jun/2016    Ian           V1.00: Create
******************************************************************************/


#ifndef _MOE_EVENT_H_
#define _MOE_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_EVENT                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_EVENT     /* According the set from project_config.h */
#endif


/* MACRO */
#define MOE_EVENT_BLK_RM_THRD    ((((sg_u16BlkCnt << 1) - 3) * MAX_QUEUE_EVT_NUM) >> 1)

#define MOE_EVENT_URGENT            (1)
#define MOE_EVENT_NORMAL            (0)

#define EVENT_NONE                  (0x00)                    /* There is no events                       */
#define EVENT_INIT                  (0x01)                    /* There is a test event                    */
#define EVENT_TIMER                 (0x02)                    /* There is a timer event                   */
#define EVENT_MSG                   (0x03)                    /* There is a message event                 */
#define EVENT_INT                   (0x04)                    /* There is an interrupt event              */
#define EVENT_DELAY                 (0x05)
#define EVENT_PERIODIC              (0x06)
#define EVENT_TEST                  (0X07)

/*******************************************************************************
* Structure  : T_EVENT
* Description: Structure of event information including task ID and event.
* Memebers   : uint8 u8Task    1~255     The task ID for such event
*              uint8 u8Evt     1~255     The event
*******************************************************************************/
typedef struct _T_EVENT
{
    uint8 u8Task;
    uint8 u8Evt;
}T_EVENT;

/*******************************************************************************
* Structure  : T_EVENT_QUEUE
* Description: Structure of event queue.
* Memebers   : struct _T_EVENT_QUEUE  *ptNext           Pointer for next event queue node
*              T_EVENT atEvtQueue[MAX_QUEUE_EVT_NUM]    Event queue block
*******************************************************************************/
typedef struct _T_EVENT_QUEUE
{
    struct _T_EVENT_QUEUE  *ptNext;      /* Pointer for next event queue node */
    T_EVENT atEvtQueue[MAX_QUEUE_EVT_NUM];
}T_EVENT_QUEUE;


/******************************************************************************
* Name       : uint8 Moe_Event_Init(void)
* Function   : Init event queue
* Input      : None
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Moe_Event_Init(void);

/******************************************************************************
* Name       : uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg)
* Function   : This function is used to set event for tasks.
* Input      : uint8 u8TaskID   1~255               The task ID to receive such event
*              uint8 u8Evt      1~255               The event type
*              uint8 u8Urg      MOE_EVENT_URGENT    It is an urgent event
*                               MOE_EVENT_NORMAL    It is a normal event
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg) ;

/******************************************************************************
* Name       : uint8 Moe_Event_Get(T_EVENT *ptEvt)
* Function   : To get a event from quque
* Input      : None
* Output:    : T_EVENT *ptEvt            Pointer to get event
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Event_Get(T_EVENT *ptEvt);




 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_EVENT_H_ */

/* End of file */

