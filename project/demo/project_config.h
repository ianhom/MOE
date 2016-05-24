
/******************************************************************************
* File       : project_config.h
* Function   : project configuration.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 24th May 2016
* History    :  No.  When           Who           What
*               1    24/May/2016    Ian           Create
******************************************************************************/

#ifndef _PROJECT_CONFIG_H_
#define _PROJECT_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

//#define __DEBUG_ENABLE

#ifdef __DEBUG_ENABLE
#define __DEBUG_MODE_MAIN           __DEBUG_BASIC_INFO
#define __DEBUG_MODE_OSAL           __DEBUG_BASIC_INFO
#define __DEBUG_MODE_OSAL_APP       __DEBUG_BASIC_INFO
#define __DEBUG_MODE_OSAL_TIMER     __DEBUG_NONE  
#define __DEBUG_MODE_APP_TASK_1     __DEBUG_BASIC_INFO//__DEBUG_FILE_LINE_INFO 
#define __DEBUG_MODE_APP_TASK_2     __DEBUG_BASIC_INFO//__DEBUG_FUNC_LINE_INFO 
#define __DEBUG_MODE_APP_TASK_3     __DEBUG_BASIC_INFO//__DEBUG_FILE_LINE_FUNC_INFO 
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif

#endif /* _PROJECT_CONFIG_H_ */

/* End of file */


