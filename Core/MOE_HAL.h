/******************************************************************************
* File       : MOE_HAL.c
* Function   : Hardware Abstract Layer.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Jul 2016
* History    :  No.  When           Who           What
*               1    04/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_HAL_H_
#define _MOE_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_HAL                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_HAL            /* According the set from project_config.h */
#endif

/******************************************************************************
* Name       : uint8 Moe_HAL_Init()
* Function   : Init hardware abstract layer
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Init();

 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_HAL_H_ */

/* End of file */

