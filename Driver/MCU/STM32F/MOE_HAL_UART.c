/******************************************************************************
* File       : MOE_HAL_UART.c
* Function   : Hardware Abstract Layer for UART of STM32F10X.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
* History    :  No.  When           Who           What
*               1    26/Jul/2016    Ian           Create
******************************************************************************/

#include "common.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Msg.h"
#include "MOE_HAL.h"
#include "MOE_HAL_UART.h"
#include "debug.h"

extern int periph_clk_khz;

/******************************************************************************
* Name       : uint8 uint8 Moe_HAL_UART_Init(void)
* Function   : Init hardware abstract layer for UART
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
******************************************************************************/
uint8 Moe_HAL_UART_Init(void)
{
    return SW_OK;  
}



/******************************************************************************
* Name       : uint8 Moe_HAL_Uart_Byte_Receive()
* Function   : Get a single byte data from uart receiving buffer
* Input      : None.
* Output:    : None.
* Return     : uint8 Received data.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Byte_Receive()
{

}

/******************************************************************************
* Name       : void Moe_HAL_Uart_Byte_Send(uint8 u8Data)
* Function   : Send a single byte data to uart sending buffer.
* Input      : None.
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
******************************************************************************/
void Moe_HAL_Uart_Byte_Send(uint8 u8Data)
{
    return;
}

/******************************************************************************
* Name       : uint8 Moe_HAL_Uart_Free_Send_Buf(void)
* Function   : Check sending buffer is free or NOT
* Input      : None.
* Output:    : None.
* Return     : MOE_HAL_UART_SND_BUF_NOT_FREE  Sending buffer is NOT free
*              MOE_HAL_UART_SND_BUF_FREE      Sending buffer is free
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Free_Send_Buf(void)
{

}

/******************************************************************************
* Name       : uint8 Moe_HAL_Uart_Got_Data(void)
* Function   : Check sending buffer is free or NOT
* Input      : None.
* Output:    : None.
* Return     : MOE_HAL_UART_RCV_DATA     Get a data in receiving buffer
*              MOE_HAL_UART_NO_RCV_DATA  Get NONE data in receiving buffer
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Got_Data(void)
{

}


/* end of file */

