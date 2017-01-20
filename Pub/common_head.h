
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


/* Definition of init and process function for tasks */
typedef void  (*PF_TASK_INIT)(uint8 u8Task, void *pPara);
typedef uint8 (*PF_TASK_PROCESS)(uint8 u8Evt, void *pPara);

#define __DEBUG_NONE                  (0)      /* No need to printf                                */
#define __DEBUG_BASIC_INFO            (1)      /* Provide basic printf function                    */
#define __DEBUG_FILE_LINE_INFO        (2)      /* Provide file and line information with printf    */
#define __DEBUG_FUNC_LINE_INFO        (3)      /* Provide function and line info with printf       */
#define __DEBUG_FILE_LINE_FUNC_INFO   (4)      /* Provode file, line and function info with printf */

#define __MALLOC_STD                  (0)      /* Use standard malloc and free */
#define __MALLOC_MOE                  (1)      /* Use MOE malloc and free      */
#define __MALLOC_MY                   (2)      /* Use your malloc and free     */

#define SW_OK             (0)         /* Return: Successful */
#define SW_ERR            (0xFF)      /* Return: Failed     */


#ifdef __cplusplus
}
#endif

#endif /* _COMMON_HEAD_H_ */

/* End of file */


