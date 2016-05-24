/******************************************************************************
* File       : OSAL_App.h
* Function   : User application definitions.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/

#ifndef _TASK_1_H_
#define _TASK_1_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_APP_TASK_1                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_APP_TASK_1     /* According the set from project_config.h */
#endif


void Task1_Init(uint8 u8TaskID);
uint16 Task1_Process(uint16 u16Evt);



#ifdef __cplusplus
}
#endif

#endif /* _TASK_1_H */

/* End of file */


