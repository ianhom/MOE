/******************************************************************************
* File       : OSAL.h
* Function   : Provide the main function of OSAL-like scheduler.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 29th Apr 2016
* History    :  No.  When           Who           What
*               1    29/Apr/2016    Ian           Create
******************************************************************************/

#ifndef _OSAL_H_
#define _OSAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_OSAL                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_OSAL           /* According the set from project_config.h */
#endif



/* MACRO */
#define TASK_NO_TASK                (0xFF)           /* Task number which means there is no task */

#define EVENT_NONE                  (0x00)           /* There is no events                       */
#define EVENT_TEST                  (0x01)           /* There is a test event                    */
#define EVENT_TIMER                 (0x02)           /* There is a timer event                   */
#define EVENT_MSG                   (0x04)           /* There is a message event                 */
#define EVENT_INT                   (0x08)           /* There is an interrupt event              */


void   Osal_Reg_Tasks(PF_TASK_PROCESS pfTaskFn);
uint8  Osal_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len);
uint8  Osal_Event_Set(uint8 u8TaskID, uint16 u16Evt);
uint8  Osal_Event_Clr(uint8 u8TaskID, uint16 u16Evt);
void   Osal_Init();
void   Osal_ProcessPoll();
void   Osal_Run_System();
uint8  Osal_Get_Acktive_Task();

 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_H_ */

/* End of file */

