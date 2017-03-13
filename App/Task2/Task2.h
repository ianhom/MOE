/******************************************************************************
* File       : Task2.h
* Function   : To be doen.
* Description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/

#ifndef _TASK_2_H_
#define _TASK_2_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_APP_TASK_2                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_APP_TASK_2     /* According the set from project_config.h */
#endif



/******************************************************************************
* Name       : uint8 Task2_Process(uint8 u8Evt, void *pPara)
* Function   : Task 2 process
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* Description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Task2_Process(uint8 u8Evt, void *pPara);


#ifdef __cplusplus
}
#endif

#endif /* _TASK_2_H */

/* End of file */


