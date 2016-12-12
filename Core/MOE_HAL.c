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

#include "../Pub/type_def.h"
#include "../Pub/common_head.h"
#include "project_config.h"
#include "./MOE_Core.h"
#include "./MOE_Msg.h"
#include "./MOE_HAL.h"
#include "../Pub/debug.h"
#ifdef __MOE_SPI_ENABLE
#include "../Driver/MCU/$(PLATFORM)/MOE_HAL_SPI.h"
#endif
#ifdef __MOE_I2C_ENABLE
#include "../Driver/MCU/$(PLATFORM)/MOE_HAL_I2C.h"
#endif
#ifdef __MOE_UART_ENABLE
#include "../Driver/MCU/$(PLATFORM)/MOE_HAL_UART.h"
#endif



/******************************************************************************
* Name       : uint8 Moe_HAL_Init(void)
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
uint8 Moe_HAL_Init(void)
{
    uint32 u32IntSt;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */    
#ifdef __MOE_SPI_ENABLE
    Moe_HAL_SPI_Init();
#endif

#ifdef __MOE_I2C_ENABLE
    Moe_HAL_I2C_Init();
#endif

#ifdef __MOE_UART_ENABLE
    Moe_HAL_UART_Init();
#endif




    return SW_OK;

}

/* end of file */

