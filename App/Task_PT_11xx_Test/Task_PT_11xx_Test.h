/******************************************************************************
* File       : Task_PT_11xx_Test.h
* Function   : PT task for 11xx test
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 22nd May 2016
* History    :  No.  When           Who           What
*               1    22/Jul/2016    Ian           Create
******************************************************************************/


#ifndef _TASK_PT_11XX_TEST_H_
#define _TASK_PT_11XX_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_PT_11XX_TEST                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_PT_11XX_TEST   /* According the set from project_config.h */
#endif



/******************************************************************************
* Name       : uint8 Task_PT_11xx_Test(uint8 u8Evt)
* Function   : A test task for 11xx
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 22nd Jul 2016
******************************************************************************/
uint8 Task_PT_11xx_Test(uint8 u8Evt, void *pPara);



#ifdef __cplusplus
}
#endif

#endif /* _TASK_PT_11XX_TEST_H */

/* End of file */


