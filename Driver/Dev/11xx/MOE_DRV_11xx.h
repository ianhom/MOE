/******************************************************************************
* File       : MOE_DRV_11xx.h
* Function   : Driver for 11xx.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
* History    :  No.  When           Who           What
*               1    20/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_DRV_11XX_H_
#define _MOE_DRV_11XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_DRV_11XX                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_DRV_11XX       /* According the set from project_config.h */
#endif

#define READ_SINGLE_MASK           (0x80)                 /* Mask of single register reading */


/******************************************************************************
* Name       : uint8 Drv_11XX_Init(void);
* Function   : Init operation for 11xx.
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11XX_Init(void);



 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_DRV_11XX_H_ */

/* End of file */

