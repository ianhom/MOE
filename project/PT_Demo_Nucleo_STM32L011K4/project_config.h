/******************************************************************************
* File       : project_config.h
* Function   : project configuration.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 22nd Nov 2016
* History    :  No.  When           Who           What
*               1    22/Nov/2016    Ian           Create
******************************************************************************/

#ifndef _PROJECT_CONFIG_H_
#define _PROJECT_CONFIG_H_



#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define PLATFORM_NAME                         "STM32L011K4"    /* Platform name */  
  
#define _STR(a)     #a
#define STR(a)      _STR(a)
/* Configure Zone */

/* Add your task process here */
#define LIST_OF_REG_TASK \
        REG_TASK(Task_PT_Demo_Process)\
        REG_TASK(Task_PT_Demo2_Process)


#define REG_TASK(name) uint8 name(uint8 u8Evt, void *pPara);
LIST_OF_REG_TASK
#undef REG_TASK


static const PF_TASK_PROCESS cg_apfTaskFn[] = 
{
#define REG_TASK(name) name,
LIST_OF_REG_TASK
#undef REG_TASK
};

static const uint8* cg_apu8TaskName[] = 
{
#define REG_TASK(name) STR(name),
LIST_OF_REG_TASK
#undef REG_TASK
};

/* Critical zone define */
#define ENTER_CRITICAL_ZONE(x)   x=1;
#define EXIT_CRITICAL_ZONE(x)    if(1 == x) x=0;  

  
#define MAX_TASK_NUM                         (sizeof(cg_apfTaskFn)/sizeof(cg_apfTaskFn[0]))      /* Max number of tasks                      */

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
#define __MALLOC_OPTION                    __MALLOC_STD      /* Use standard malloc and free funciton  */

#ifdef __DEBUG_ENABLE
#define __DEBUG_MODE_MAIN                  __DEBUG_BASIC_INFO
#define __DEBUG_MODE_MOE_CORE              __DEBUG_NONE  
#define __DEBUG_MODE_MOE_APP               __DEBUG_NONE  
#define __DEBUG_MODE_MOE_TIMER             __DEBUG_NONE   
#define __DEBUG_MODE_MOE_QUEUE             __DEBUG_BASIC_INFO  
#define __DEBUG_MODE_MOE_MSG               __DEBUG_NONE  
#define __DEBUG_MODE_MOE_EVENT             __DEBUG_NONE
#define __DEBUG_MODE_BOARD_CONFIG          __DEBUG_BASIC_INFO
#define __DEBUG_MODE_MOE_HAL               __DEBUG_BASIC_INFO
#define __DEBUG_MODE_PT_DEMO               __DEBUG_BASIC_INFO
#define __DEBUG_MODE_PT_DEMO2              __DEBUG_BASIC_INFO
#endif
                    
#if (__MALLOC_OPTION == __MALLOC_MY)        /* If you want to use your malloc and free */
#define MOE_MALLOC(size)   My_Malloc(size)  /* Add your malloc function here           */
#define MOE_FREE(p)        My_Free(p)       /* Add your free function here             */
#endif

void LED_Off(uint8 u8Ch);
#define TASK_PT_DEMO_LED_OFF       LED_Off

void LED_On(uint8 u8Ch);
#define TASK_PT_DEMO_LED_ON        LED_On

#define LED_GREEN                  (3)     /* Green led       */

#ifdef __cplusplus
}
#endif

#endif /* _PROJECT_CONFIG_H_ */

/* End of file */


