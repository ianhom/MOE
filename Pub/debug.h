
/******************************************************************************
* File       : debug.h
* Function   : debug control.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 24th May 2016
* History    :  No.  When           Who           What
*               1    24/May/2016    Ian           Create
******************************************************************************/

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __DEBUG_NONE
#define __DEBUG_NONE                0      /* No need to printf                                */
#define __DEBUG_BASIC_INFO          1      /* Provide basic printf function                    */
#define __DEBUG_FILE_LINE_INFO      2      /* Provide file and line information with printf    */
#define __DEBUG_FUNC_LINE_INFO      3      /* Provide function and line info with printf       */
#define __DEBUG_FILE_LINE_FUNC_INFO 4      /* Provode file, line and function info with printf */
#endif

#ifndef __DEBUG_MODE
#define __DEBUG_MODE       __DEBUG_BASIC_INFO//__DEBUG_FUNC_LINE_INFO
#endif

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

#define MOE_ASSERT(Cond, ret, reason,...)    if(!Cond) {DBG_PRINT(reason,##__VA_ARGS__);return ret;}

#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_H_ */

/* End of file */


