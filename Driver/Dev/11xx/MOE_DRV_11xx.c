/******************************************************************************
* File       : MOE_DRV_11xx.c
* Function   : Driver for 11xx.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
* History    :  No.  When           Who           What
*               1    20/Jul/2016    Ian           Create
******************************************************************************/

#include "../../../Pub/type_def.h"
#include "../../../Pub/common_head.h"
#include "project_config.h"
#include "../../../Core/MOE_Core.h"
#include "../../../Core/MOE_Msg.h"
#include "../../../Core/MOE_HAL.h"
#include "MOE_HAL_UART.h"
#include "./MOE_DRV_11xx.h"
#include "../../../Pub/debug.h"
#include "Board_Config.h"

/******************************************************************************
* Name       : uint8 Drv_11xx_Init(void)
* Function   : Init operation for 11xx.
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Init(void)
{
    Board_Config_Reset_Ctrl(0);
    Delay_ms(10);
    Board_Config_Reset_Ctrl(1);
    Delay_ms(10);
    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd(uint8 u8Cmd, uint8 u8Para, uint8 u8Val, uint16 u16Len, uint8 *pu8Data)
* Function   : Send command to 11xx
* Input      : uint8  u8Cmd    0~255                      Command code
*              uint8  u8Para   DRV_11XX_CMD_WITHOUT_VAL   No value after command
*                              DRV_11XX_CMD_WITH_VAL      A byte value after command
*              uint8  u8Val    0~255                      Value after command
*              uint16 u16Len   0~65536                    Return bytes of command        
* Output:    : uint8 *pu8Data                             Pointer to save return bytes     
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd(uint8 u8Cmd, uint8 u8Para, uint8 u8Val, uint16 u16Len, uint8 *pu8Data)
{
    uint16 u16Idx;

    /* Check if input parameter is invalid or NOT */
    if((0 != u16Len) && (NULL == pu8Data))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_CFG_MODE);          /* Enter to configure mode */
    while(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive());/* Wait respons           */
    
    Moe_HAL_Uart_Byte_Send(u8Cmd);                          /* Send command first      */

    
    if(DRV_11XX_CMD_WITH_VAL == u8Para)                     /* If need to send a value */
    {
        Moe_HAL_Uart_Byte_Send(u8Val);                      /* Send value              */
    }
        
    for(u16Idx = 0; u16Idx < u16Len; u16Idx++)              /* Get return data         */
    {
        pu8Data[u16Idx] = Moe_HAL_Uart_Byte_Receive();
    }
    if(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive())   /* Wait respons            */
    {
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_IDLE);              /* Return to IDLE          */
    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Bind(uint8 u8Ch, uint8 *pu8Addr)
* Function   : Bind a sender SN address
* Input      : uint8  u8Ch       1~64      Index of address
*              uint8 *pu8Addr              Pointer for SN address
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Bind(uint8 u8Ch, uint8 *pu8Addr)
{
    uint8 u8Idx;

    /* Check if the input parameters are invalid or NOT */
    if(((u8Ch - 1) > (DRV_11XX_MAX_BIND_ADDR - 1)) || (NULL == pu8Addr))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_CFG_MODE);/* Enter to configure mode */
    if(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons    */
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(u8Ch);              /* Select index               */
    if(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons    */
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(0xFF);              /* First byte of address      */
    Moe_HAL_Uart_Byte_Send(0x00);              /* Second byte of address     */
    for(u8Idx = 0; u8Idx < DRV_11XX_SN_LEN; u8Idx++)
    {
        Moe_HAL_Uart_Byte_Send(pu8Addr[u8Idx]);/* SN address                 */
    }
    if(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons    */
    {
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_IDLE);     /* Return back to IDLE    */
    return SW_OK;
}



/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Mode_Sel(uint8 u8Mode)
* Function   : Select operating mode 
* Input      : uint8  u8Mode    DRV_11XX_MODE_S1    S1 sending only mode
*                               DRV_11XX_MODE_S2    S2 bi-direction mode
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Mode_Sel(uint8 u8Mode)
{
    /* Check if the input parameter is invalid or NOT */
    if((DRV_11XX_MODE_S1 != u8Mode) && (DRV_11XX_MODE_S2 != u8Mode))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command and value */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_MODE_SEL, DRV_11XX_CMD_WITH_VAL, u8Mode, 0, NULL))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Rcv_Mode(uint8 u8Mode)
* Function   : Select receving mode  
* Input      : uint8  u8Mode    DRV_11XX_NORMAL_RCV    Receive normal telegram
*                               DRV_11XX_ALL_RCV       Receive all telegram
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Rcv_Mode(uint8 u8Mode)
{
    /* Check if the input parameter is invalid or NOT */
    if((DRV_11XX_NORMAL_RCV != u8Mode) && (DRV_11XX_ALL_RCV != u8Mode))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }
    
    /* Write the command and value */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_RCV_MODE, DRV_11XX_CMD_WITH_VAL, u8Mode, 0, NULL))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Power_Sel(uint8 u8Lv)
* Function   : Select output power
* Input      : uint8  u8Lv    1~5         Output level
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Power_Sel(uint8 u8Lv)
{
    /* Check if the input parameter is invalid or NOT */
    if((u8Lv - 1) > 4)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command and value */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_OUTPUT_PWR, DRV_11XX_CMD_WITH_VAL, u8Lv, 0, NULL))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_List_Bind(uint8 u8Num, uint8 *pu8Addr)
* Function   : List a bind SN address
* Input      : uint8  u8Num     1~64         Index of bind SN address
* Output:    : uint8 *pu8Addr                Pointer to save SN address
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_List_Bind(uint8 u8Num, uint8 *pu8Addr)
{
    /* Check if the input parameters are invalid or NOT */
    if(((u8Num - 1) > (DRV_11XX_MAX_BIND_ADDR - 1)) ||(NULL == pu8Addr))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command and value */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_LIST_BIND, DRV_11XX_CMD_WITH_VAL, u8Num, 8, pu8Addr))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Quality_Ind(uint8 *pu8Data)
* Function   : Get the quality indicator value
* Input      : None.
* Output:    : uint8 *pu8Data                Pointer to save quality value
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Quality_Ind(uint8 *pu8Data)
{
    /* Check if the input parameters are invalid or NOT */
    if(NULL == pu8Data)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_QUALITY_IND, DRV_11XX_CMD_WITHOUT_VAL, 0, 1, pu8Data))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Get_Rssi(uint8 *pu8Data)
* Function   : Get the RSSI value
* Input      : None.
* Output:    : uint8 *pu8Data                Pointer to save RSSI value
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Get_Rssi(uint8 *pu8Data)
{
    /* Check if the input parameters are invalid or NOT */
    if(NULL == pu8Data)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_RSSI, DRV_11XX_CMD_WITHOUT_VAL, 0, 1, pu8Data))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Reg_Read(uint8 *pu8Data)
* Function   : Get the all register value
* Input      : None.
* Output:    : uint8 *pu8Data                Pointer to register value
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Reg_Read(uint8 *pu8Data)
{
    /* Check if the input parameters are invalid or NOT */
    if(NULL == pu8Data)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command */
    if(SW_ERR == Drv_11xx_Cmd(DRV_11XX_CMD_REG_READ, DRV_11XX_CMD_WITHOUT_VAL, 0, DRV_11XX_MAX_REG_NUM, pu8Data))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Get_Des_Addr_Tab (uint8 *pu8Data)
* Function   : Get the destination address table
* Input      : None.
* Output:    : uint8 *pu8Data                Pointer to register value
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Get_Des_Addr_Tab (uint8 *pu8Data)
{
    /* Check if the input parameters are invalid or NOT */
    if(NULL == pu8Data)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_DES_ADDR_TAB, DRV_11XX_CMD_WITHOUT_VAL, 0, DRV_11XX_CMD_DES_ADDR_TAB_LEN, pu8Data))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Get_All_Addr_Tab (uint8 *pu8Data)
* Function   : Get the all address table
* Input      : None.
* Output:    : uint8 *pu8Data                Pointer to register value
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Get_All_Addr_Tab (uint8 *pu8Data)
{
    /* Check if the input parameters are invalid or NOT */
    if(NULL == pu8Data)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_ALL_ADDR_TAB, DRV_11XX_CMD_WITHOUT_VAL, 0, DRV_11XX_CMD_ALL_ADDR_TAB_LEN, pu8Data))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}



/******************************************************************************
* Name       : uint8 Drv_11xx_Cmd_Reg_Read(uint8 *pu8Data)
* Function   : Get the all register value
* Input      : None.
* Output:    : uint8 *pu8Data                Pointer to register value
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_Channel_Sel(uint8 u8Ch)
{
    /* Check if the input parameters are invalid or NOT */
    if((u8Ch - 1) > 2)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    /* Write the command and value */
    if(!Drv_11xx_Cmd(DRV_11XX_CMD_CH_SEL, DRV_11XX_CMD_WITH_VAL, u8Ch, 0, NULL))
    {
        DBG_PRINT("Something wrong with command!!\n");
        return SW_ERR;
    }
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Write_Reg(uint8 u8Reg, uint8 u8Cnt, uint8 *pu8Addr)
* Function   : Write value into register and store in Flash.
* Input      : uint8  u8Reg      0~255     Register address.
*              uint8  u8Cnt      1~255     Count of register to be writen
*              uint8 *pu8Addr              Pointer for SN address
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Write_Reg(uint8 u8Reg, uint8 u8Cnt, uint8 *pu8Addr)
{
    uint8 u8Idx;

    /* Check if the input parameters are invalid or NOT */
    if((0 == u8Cnt) || (NULL == pu8Addr))
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_CFG_MODE);/* Enter to configure mode */
    if(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons    */
    {
        return SW_ERR;
    }
    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_WIRTE_REG);/* Enter M sub-mode       */
    if(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons    */
    {
        return SW_ERR;
    }

    for(u8Idx = 0; u8Idx < u8Cnt; u8Idx++)
    {
        Moe_HAL_Uart_Byte_Send(u8Reg + u8Idx); /* Send register address      */
        Moe_HAL_Uart_Byte_Send(pu8Addr[u8Idx]);/* Send register value        */
    }
    
    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_END_M);/* First byte of address      */
    if(DRV_11XX_CMD_RSPON != Moe_HAL_Uart_Byte_Receive()) /* Wait respons    */
    {
        return SW_ERR;
    }

    Moe_HAL_Uart_Byte_Send(DRV_11XX_CMD_IDLE);     /* Return back to IDLE    */
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Drv_11xx_Write_Reg(uint8 u8Reg, uint8 u8Cnt, uint8 *pu8Addr)
* Function   : Send telegram with 11xx
* Input      : uint8 *pu8Data              Pointer for sending telegram
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Send_Telegram(uint8 *pu8Data)
{
    uint8 u8Idx;
    uint8 u8Len = *pu8Data + 1;

    /* Check if the input parameters are invalid or NOT */
    if(NULL == pu8Data)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    for(u8Idx = 0; u8Idx < u8Len; u8Idx++)
    {
        Moe_HAL_Uart_Byte_Send(pu8Data[u8Idx]);   /* Send each byte of data  */
    }

    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Drv_11xx_Receive_Telegram(uint8 *pu8Data)
* Function   : Receive telegram with 11xx
* Input      : None.
* Output:    : uint8  *pu8Data              Pointer for received telegram
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jul 2016
******************************************************************************/
uint8 Drv_11xx_Receive_Telegram(uint8 *pu8Data)
{
    uint8 u8Idx;
    uint8 u8Len;

    /* Check if the input parameters are invalid or NOT */
    if(NULL == pu8Data)
    {
        DBG_PRINT("Invalid input\n");
        return SW_ERR;
    }

    u8Len    = Moe_HAL_Uart_Byte_Receive();          /* Get the length of telegram  */
    *pu8Data = u8Len;                                /* Fill the first byte         */

    for(u8Idx = 1; u8Idx < u8Len + 1; u8Idx++)
    {
        pu8Data[u8Idx] = Moe_HAL_Uart_Byte_Receive();/* Received each byte of data  */
    }

    return SW_OK;
}



/* end of file */

