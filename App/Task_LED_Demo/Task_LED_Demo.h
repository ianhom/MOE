/******************************************************************************
* File       : Task_LED_Demo.h
* Function   : It is a LED demo task.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/


#ifndef _TASK_LED_DEMO_H_
#define _TASK_LED_DEMO_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_TASK_LED_DEMO                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_TASK_LED_DEMO  /* According the set from project_config.h */
#endif



/******************************************************************************
* Name       : uint8 LED_Demo_Process(uint8 u8Evt)
* Function   : LED demo process
* Input      : uint8 u8Evt  1~254     Event for the task
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 LED_Demo_Process(uint8 u8Evt);



#ifdef __cplusplus
}
#endif

#endif /* _TASK_LED_DEMO_H */

/* End of file */


