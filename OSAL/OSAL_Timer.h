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

#ifndef _OSAL_TIMER_H_
#define _OSAL_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16 (*PF_TIMER_SRC)(void);

/*******************************************************************************
* Structure  : T_TIMER
* Description: Structure of timer.
* Memebers   : uint16    u16TmStart;      0~0xFFFF        Start time point         
*              uint16    u16TmNow;        0~0xFFFF        Current time point       
*              uint16    u16TmOut;        0~0xFFFF        Timeout time             
*              uint16    u16Cnt;          0               Periodic
*                                         1~0xFFFF        Counts to start the timer  
*******************************************************************************/
typedef struct _T_TIMER
{
    uint16    u16TmStart;              /* Start time point         */
    uint16    u16TmNow;                /* Current time point       */
    uint16    u16TmOut;                /* Timeout time             */
    uint16    u16Cnt;                  /* Count to start the timer */
    uint16    u16Evt;                  /* Timeout event to be set  */
    uint8     u8TaskID;                /* Timeout event task ID    */
}T_TIMER;


typedef struct _T_TIMER_NODE
{
    T_TIMER                tTimer;    /* Timer data of such node     */
    struct _T_TIMER_NODE  *ptNext;    /* Pointer for next timer node */
}T_TIMER_NODE;

/* MACRO */




 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_TIMER_H_ */

/* End of file */

