
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

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Configure Zone */
#define MAX_TASK_NUM                         (2)      /* Max number of tasks                      */

#define MAX_QUEUE_EVT_NUM                    (MAX_TASK_NUM * 10)
 
#define __FLEXIBLE_ARRAY_NOT_SUPPORTED                /* Complier does NOT support flexible array */

#define __TIMER_CALLBACK_SUPPORTED                    /* Timer callback is supported              */

#define __DEBUG_ENABLE                                /* Debug mode is enabled                    */

#define __WANTED_A_LIVE_FOX                           /* Wanted: a live fox.                      */

/*********************************************************
NOTE: You have four ways to use malloc:
1. Do not define __MALLOC_OPTION or define __MALLOC_OPTION
   as __MALLOC_STD, and Do not re-write the malloc and 
   free function, you will use the standard malloc and
   free function in lib.
2. Do not define __MALLOC_OPTION or define __MALLOC_OPTION
   as __MALLOC_STD, and re-write the malloc and free 
   function, you will use your malloc and free function, 
   Please NOTE that the whole project use your malloc and 
   free function
3. Define __MALLOC_OPTION as __MALLOC_MY, now your can use
   your own malloc and free function, however, if you use
   the same name with "malloc" and "free", whole project
   use your malloc and free just like situation 2.
4. Define __MALLOC_OPTION as __MALLOC_MOE, the Moe_Malloc
   and Moe_Free will be used.

Options for __MALLOC_OPTION:
    __MALLOC_STD             Use standard malloc and free 
    __MALLOC_MOE            Use MOE malloc and free     
    __MALLOC_MY              Use your malloc and free     
**********************************************************/  
#define __MALLOC_OPTION                 __MALLOC_STD      /* Use standard malloc and free funciton  */


#ifdef __DEBUG_ENABLE
#define __DEBUG_MODE_MAIN                  __DEBUG_BASIC_INFO
#define __DEBUG_MODE_MOE                   __DEBUG_NONE  //__DEBUG_BASIC_INFO
#define __DEBUG_MODE_MOE_APP               __DEBUG_NONE  //__DEBUG_BASIC_INFO
#define __DEBUG_MODE_MOE_TIMER             __DEBUG_NONE  //__DEBUG_NONE  
#define __DEBUG_MODE_MOE_LINK_LIST         __DEBUG_BASIC_INFO  //__DEBUG_BASIC_INFO
#define __DEBUG_MODE_MOE_QUEUE             __DEBUG_BASIC_INFO  //__DEBUG_BASIC_INFO
#define __DEBUG_MODE_MOE_MSG               __DEBUG_BASIC_INFO 
#define __DEBUG_MODE_APP_TASK_1            __DEBUG_BASIC_INFO//__DEBUG_FILE_LINE_INFO 
#define __DEBUG_MODE_APP_TASK_2            __DEBUG_BASIC_INFO//__DEBUG_FUNC_LINE_INFO 
#define __DEBUG_MODE_APP_TASK_3            __DEBUG_BASIC_INFO//__DEBUG_FILE_LINE_FUNC_INFO 
#define __DEBUG_MODE_APP_TASK__DEMO_QUEUE  __DEBUG_BASIC_INFO//__DEBUG_FILE_LINE_FUNC_INFO 
#define __DEBUG_MODE_MOE_EVENT             __DEBUG_BASIC_INFO//__DEBUG_FILE_LINE_FUNC_INFO 
#endif

                           
#if (__MALLOC_OPTION == __MALLOC_MY)         /* If you want to use your malloc and free */
#define MOE_MALLOC(size)   My_Malloc(size)  /* Add your malloc function here           */
#define MOE_FREE(p)        My_Free(p)       /* Add your free function here             */
#endif


#ifdef __cplusplus
}
#endif

#endif /* _PROJECT_CONFIG_H_ */

/* End of file */


