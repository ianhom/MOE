/*/******************************************************************************
* File       : OSAL_Link_list.h
* Function   : General link list function.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 2nd Jun 2016
* History    :  No.  When           Who           What
*               1    02/Jun/2016    Ian           Create
******************************************************************************/

#ifndef _OSAL_LINK_LIST_H_
#define _OSAL_LINK_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_OSAL_LINK_LIST                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_OSAL_LINK_LIST     /* According the set from project_config.h */
#endif




 
#ifdef __cplusplus
}
#endif

#endif /* _OSAL_LINK_LIST_H_ */

/* End of file */

