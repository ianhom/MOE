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

/* Definition of process function for tasks */
typedef uint16 (*PF_TASK_PROCESS)(uint16 u16Evt);


/* MACRO */
#deinfe TASK_NO_TASK                (0xFF)           /* Task number which means there is no task */


#ifdef __cplusplus
}
#endif

#endif /* _BTN_SM_MODULE_ */

/* End of file */
