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

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Msg.h"
#include "MOE_HAL.h"
#include "debug.h"

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
uint8 Moe_HAL_Init()
{
    uint32 u32IntSt;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    
  
    return SW_OK;

}

/* end of file */

