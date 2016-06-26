/******************************************************************************
* File       : MOE_Timer.h
* Function   : Provide timer services.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
* History    :  No.  When           Who           What
*               1    06/May/2016    Ian           Create
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

#define MOE_EVENT_URGENT         (1)
#define MOE_EVENT_NORMAL         (0)


typedef struct _T_EVENT
{
    uint8 u8Task;
    uint8 u8Evt;
}T_EVENT;


typedef struct _T_EVENT_QUEUE
{
    struct _T_EVENT_QUEUE  *ptNext;      /* Pointer for next timer node */
    T_EVENT atEvtQueue[MAX_QUEUE_EVT_NUM];
}T_EVENT_QUEUE;



uint8 Moe_Event_Init();

uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt, uint8 u8Urg);

uint16 Moe_Event_Get(T_EVENT *ptEvt);




 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_EVENT_H_ */

/* End of file */

