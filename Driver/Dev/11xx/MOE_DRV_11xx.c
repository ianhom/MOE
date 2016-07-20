/******************************************************************************
* File       : MOE_DRV_11xx.c
* Function   : Driver for 11xx.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
* History    :  No.  When           Who           What
*               1    20/Jul/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Msg.h"
#include "MOE_HAL.h"
#include "MOE_HAL_UART.h"
#include "MOE_DRV_11xx.h"
#include "debug.h"

static uint8 sg_au8RegRead[256] = {0};

/******************************************************************************
* Name       : uint8 Drv_11xx_Init(void)
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
uint8 Drv_11xx_Init(void)
{
    uint8 u8Temp = 0;
    
    
    Moe_HAL_Uart_Byte_Send(DRV_11XX_CFG_MODE);
    if(DRV_11XX_RSPON = Moe_HAL_Uart_Byte_Receive())
    {
        Moe_HAL_Uart_Byte_Send(DRV_11XX_IDLE);
    }
    else
    {
        DBG_PRINT("Wrong operating mode of 11xx!!\n");
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Simple_Cmd(uint8 u8Cmd)
* Function   : Send command to 11xx
* Input      : uint8 u8Cmd
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Simple_Cmd(uint8 u8Cmd)
{
    Moe_HAL_Uart_Byte_Send(DRV_11XX_CFG_MODE);
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive())
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(u8Cmd);
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive())
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(DRV_11XX_IDLE);
    return SW_OK;
}



/* end of file */

