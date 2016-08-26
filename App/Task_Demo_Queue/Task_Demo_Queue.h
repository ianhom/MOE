/******************************************************************************
* File       : Task_Demo_Queue.h
* Function   : It is demo task for queue
* description: This task creates two queues,one is located in task space, and 
*              the other is created by Queue API. Task sends two messages with 
*              the two queues and recieves the two messages from the queues.           
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
* History    :  No.  When           Who      What
*               1    19/Jun/2016    Ian      V1.00: Create
******************************************************************************/


#ifndef _TASK_DEMO_QUEUE_H_
#define _TASK_DEMO_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif




/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_APP_TASK__DEMO_QUEUE                    
#define __DEBUG_MODE      __DEBUG_NONE                          /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_APP_TASK__DEMO_QUEUE     /* According the set from project_config.h */
#endif

#define TASK_DEMO_QUEUE_BUF_NUM              (5)                /* Number of buffer blocks    */
#define TASK_DEMO_QUEUE_BUF_SIZE             (10)               /* Size of each buffer blocks */

/******************************************************************************
* Name       : uint8 Task_Demo_Queue_Process(uint8 u8Evt)
* Function   : Task Demo Queue process
* Input      : To be done
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
******************************************************************************/
uint8 Task_Demo_Queue_Process(uint8 u8Evt);





#ifdef __cplusplus
}
#endif

#endif /* _TASK_DEMO_QUEUE_H */

/* End of file */


