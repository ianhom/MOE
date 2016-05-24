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

#ifndef _OSAL_APP_H_
#define _OSAL_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_OSAL_APP                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_OSAL_APP       /* According the set from project_config.h */
#endif


#define MAX_TASK_NUM             (3)      /* Max number of tasks */

void Osal_Tasks_Init();

#ifdef __cplusplus
}
#endif

#endif /* OSAL_APP_H */

/* End of file */

