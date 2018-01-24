/******************************************************************************
* File       : SleepSort.h
* Function   : To be done.
* Description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 24th Jan 2018
* History    :  No.  When           Who           What
*               1    24/Jan/2018    Ian           Create
******************************************************************************/

#ifndef _SLEEP_SORT_H_
#define _SLEEP_SORT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_APP_SLEEP_SORT                 
#define __DEBUG_MODE      __DEBUG_NONE                  /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_APP_SLEEP_SORT   /* According the set from project_config.h */
#endif



/******************************************************************************
* Name       : uint8 SleepSort_Process(uint8 u8Evt, void *pPara)
* Function   : To be done.
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* Description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 24th Jan 2018
******************************************************************************/
uint8 Task1_Process(uint8 u8Evt, void *pPara);



#ifdef __cplusplus
}
#endif

#endif /* _SLEEP_SORT_H_ */

/* End of file */

