/*/******************************************************************************
* File       : OSAL_Queue.h
* Function   : General queue function.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 10th Jun 2016
* History    :  No.  When           Who           What
*               1    10/Jun/2016    Ian           Create
******************************************************************************/

#ifndef _OSAL_QUEUE_H_
#define _OSAL_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_OSAL_QUEUE                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_OSAL_QUEUE         /* According the set from project_config.h */
#endif




 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_QUEUE_H_ */

/* End of file */

