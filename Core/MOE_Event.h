/******************************************************************************
* File       : OSAL_Timer.h
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




/******************************************************************************
* Name       : uint8 Osal_Timer_Init(PF_TIMER_SRC pfSysTm)
* Function   : Init OSAL timer
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Osal_Timer_Init(PF_TIMER_SRC pfSysTm);

/******************************************************************************
* Name       : T_TIMER_NODE* Osal_Timer_Start(uint8 u8TaskID, uint16 u16Evt, uint16 u16Cnt, uint32 u32TmOut)
* Function   : Start a timer
* Input      : T_TIMER *ptTm     Pointer of timers set by user.
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Osal_Timer_Start(T_TIMER *ptTm);

/******************************************************************************
* Name       : T_TIMER_NODE* Osal_Timer_Stop(T_TIMER_NODE* ptNode)
* Function   : Stop a started timer.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be stopped
* Output:    : None
* Return     : NULL           Fail to stop a timer.
*              T_TIMER_NODE*  The pointer of the timer which is stopped.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Osal_Timer_Stop(T_TIMER_NODE* ptNode);




/******************************************************************************
* Name       : static T_TIMER_NODE *Osal_Timer_Find(T_TIMER_NODE* ptNode)
* Function   : Try to find a node.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be found
* Output:    : None
* Return     : NULL           Fail to find the node.
*              T_TIMER_NODE*  The pointer of the founed node.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Osal_Timer_Restart(T_TIMER_NODE* ptNode);


/******************************************************************************
* Name       : uint8 Osal_Timer_Process(void)
* Function   : Main process for timer updating.
* Input      : None
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Osal_Timer_Process(void);

/******************************************************************************
* Name       : uint16 Osal_Timer_Test_Cnt()
* Function   : Get the count of timers
* Input      : None
* Output:    : None
* Return     : uint16   The count of timers
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint16 Osal_Timer_Test_Cnt();

/******************************************************************************
* Name       : void Osal_Timer_Test_General()
* Function   : General test
* Input      : None
* Output:    : None
* Return     : None
* description: To be done
*              **IT IS A TEST FUNCTION! DO NOT USE IT IN YOUR APPLICATION!**
* Version    : V1.00
* Author     : Ian
* Date       : 9th May 2016
******************************************************************************/
void Osal_Timer_Test_General();


 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_TIMER_H_ */

/* End of file */

