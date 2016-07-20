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
* Name       : uint8 Drv_11xx_Cmd(uint8 u8Cmd)
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
uint8 Drv_11xx_Cmd(uint8 u8Cmd)
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

/******************************************************************************
* Name       : uint8 Drv_11xx_Simple_Cmd(uint8 u8Cmd)
* Function   : Send command with 1 byte value to 11xx
* Input      : uint8 u8Cmd    0~255    Command code
*              uint8 u8Val    0~255    Value after command
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_1Val(uint8 u8Cmd, uint8 u8Val)
{
    Moe_HAL_Uart_Byte_Send(DRV_11XX_CFG_MODE);          /* Enter to configure mode */
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive())   /* Wait respons            */
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(u8Cmd);                      /* Send command first      */
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive())   /* Wait respons            */
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(u8Val);                      /* Send value              */
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive())   /* Wait respons            */
    {
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_IDLE);              /* Return to IDLE          */
    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Drv_11xx_Bind(uint8 u8Ch, uint8 *pu8Addr)
* Function   : Bind a sender SN address
* Input      : uint8  u8Ch       1~64      Index of address
*              uint8 *pu8Addr              Pointer for SN address
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Bind(uint8 u8Ch, uint8 *pu8Addr)
{
    uint8 u8Idx;

    /* Check if the input parameters are invalid or NOT */
    if(((u8Ch - 1) > (DRV_11XX_MAX_BIND_ADDR - 1)) || (NULL == pu8Addr))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_CFG_MODE);  /* Enter to configure mode */
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons      */
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(u8Ch);              /* Select index             */
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons      */
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(0xFF);              /* First byte of address    */
    Moe_HAL_Uart_Byte_Send(0x00);              /* Second byte of address   */
    for(u8Idx = 0; u8Idx < DRV_11XX_SN_LEN; u8Idx++)
    {
        Moe_HAL_Uart_Byte_Send(pu8Addr[u8Idx]);/* SN address               */
    }
    if(DRV_11XX_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons      */
    {
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_IDLE);     /* Return back to IDLE      */
    return SW_OK;
}



/******************************************************************************
* Name       : uint8 Drv_11xx_Mode_Sel(uint8 u8Mode)
* Function   : Bind a sender SN address    
* Input      : uint8  u8Mode    DRV_11XX_MODE_S1    S1 sending only mode
*                               DRV_11XX_MODE_S2    S2 bi-direction mode
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Mode_Sel(uint8 u8Mode)
{
    uint8 u8Idx;

    /* Check if the input parameter is invalid or NOT */
    if((DRV_11XX_MODE_S1 != u8Mode) && (DRV_11XX_MODE_S2 != u8Mode))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command and value */
    if(!Drv_11xx_Cmd_1Val(DRV_11XX_MODE_SEL_CMD, u8Mode))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Rcv_Mode(uint8 u8Mode)
* Function   : Bind a sender SN address    
* Input      : uint8  u8Mode    DRV_11XX_NORMAL_RCV    Receive normal telegram
*                               DRV_11XX_ALL_RCV       Receive all telegram
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Rcv_Mode(uint8 u8Mode)
{
    uint8 u8Idx;

    /* Check if the input parameter is invalid or NOT */
    if((DRV_11XX_NORMAL_RCV != u8Mode) && (DRV_11XX_ALL_RCV != u8Mode))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command and value */
    if(!Drv_11xx_Cmd_1Val(DRV_11XX_RCV_MODE_CMD, u8Mode))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}



/* end of file */

