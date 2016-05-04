
/******************************************************************************
* File       : common_head.h
* Function   : common definitions.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/

#ifndef _COMMON_HEAD_H_
#define _COMMON_HEAD_H_

#ifdef __cplusplus
extern "C" {
#endif



/* Definition of process function for tasks */
typedef uint16 (*PF_TASK_PROCESS)(uint16 u16Evt);

#define __DEBUG_NONE                0      /* No need to printf                                */
#define __DEBUG_BASIC_INFO          1      /* Provide basic printf function                    */
#define __DEBUG_FILE_LINE_INFO      2      /* Provide file and line information with printf    */
#define __DEBUG_FUNC_LINE_INFO      3      /* Provide function and line info with printf       */
#define __DEBUG_FILE_LINE_FUNC_INFO 4      /* Provode file, line and function info with printf */

#define __DEBUG_MODE       __DEBUG_FUNC_LINE_INFO

#if (__DEBUG_MODE  == __DEBUG_FILE_LINE_FUNC_INFO)
    #pragma message("*** Debug printf outputs file name, function name, line number and desired info!! ***")
    #define DBG_PRINT(x,...)        printf("FILE: "__FILE__", FUNC : %s, LINE: %d -- \n "x" \n", __func__ , __LINE__, ##__VA_ARGS__)

#elif (__DEBUG_MODE  == __DEBUG_FILE_LINE_INFO)
    #pragma message("*** Debug printf outputs file name, line number and desired info!! ***")
    #define DBG_PRINT(x,...)        printf("FILE: "__FILE__",  LINE: %d -- \n "x" \n", __LINE__, ##__VA_ARGS__)

#elif (__DEBUG_MODE  == __DEBUG_FUNC_LINE_INFO)
    #pragma message("*** Debug printf outputs function name, line number and desired info!! ***")
    #define DBG_PRINT(x,...)        printf("FUNC : %s, LINE: %d -- \n "x" \n", __func__ , __LINE__, ##__VA_ARGS__)

#elif (__DEBUG_MODE == __DEBUG_BASIC_INFO)
    #pragma message("*** Debug printf outputs desired basic info!! ***")
    #define DBG_PRINT(x,...)        printf(x, ##__VA_ARGS__)

#else
    #pragma message("*** Debug printf is DISABLED!! ***")
    #define DBG_PRINT(x,...)
#endif

#define ENTER_CRITICAL_ZONE(x) x=1;

#define EXIT_CRITICAL_ZONE(x) if(1 == x) x=0;


#ifdef __cplusplus
}
#endif

#endif /* _COMMON_HEAD_H_ */

/* End of file */


