/******************************************************************************
* File       : Moe_main.h
* Function   : To be done.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 24th May 2016
* History    :  No.  When           Who           What
*               1    22/Nov/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_MAIN_H_
#define _MOE_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MAIN                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MAIN           /* According the set from project_config.h */
#endif


#ifdef __cplusplus
}
#endif

#endif /* _MOE_MAIN_H */

/* End of file */


