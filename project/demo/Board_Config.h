/******************************************************************************
* File       : Board_Config.h
* Function   : Hardware configurations
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 3rd Jul 2016
* History    :  No.  When           Who           What
*               1    3/Jul/2016     Ian           Create
******************************************************************************/

#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_BOARD_CONFIG                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_BOARD_CONFIG   /* According the set from project_config.h */
#endif




#ifdef __cplusplus
}
#endif

#endif /* _BOARD_CONFIG_H */

/* End of file */


