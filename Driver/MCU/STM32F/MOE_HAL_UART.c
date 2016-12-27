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
#include "../../../Pub/common_head.h"
#include "project_config.h"
#include "../../../Core/MOE_Core.h"
#include "../../../Core/MOE_Msg.h"
#include "../../../Core/MOE_HAL.h"
#include "./MOE_HAL_UART.h"
#include "../../../Pub/debug.h"

static const uin32 sg_au32UartAddr[] = 
{
    UART1_BASE,
    UART2_BASE,
    UART3_BASE,
    UART4_BASE,
    UART5_BASE
};

extern int periph_clk_khz;

/******************************************************************************
* Name       : uint8 Moe_HAL_UART_Init(uint8 u8No)
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
uint8 Moe_HAL_UART_Init(uint8 u8No)
{
    volatile uint16 u16Data = 0;
    uint32 u32UartNo;

    /* Check if the uart number is valid or NOT */
    if((u8No - 1) > (MAX_UART_DEVICE_NUM - 1))
    {
        return SW_ERR;
    }
    
    u32UartNo = sg_au32UartAddr[u8No - 1];
    
    /* Enable uart clock and reset */
    if(UART_1 == u8No) /* If it is uart1 */
    {
        RCC->APB2ENR  |= RCC_APB2ENR_USART1EN;        /* Enable uart clock */
        RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;      /* Reset uart device */
        RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST);   /* Stop reset uart   */     
    }    
    else /* If it is uart 2~5 */
    {
        RCC->APB1ENR  |= (RCC_APB1ENR_USART2EN    << (u8No - UART_2)); /* Enable uart clock */
        RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST  << (u8No - UART_2)); /* Reset uart device */
        RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST << (u8No - UART_2)); /* Reset uart device */
    }

    /* Disable Tx/Rx function, Tx/Rx interrupt and Error interrupt before uart init operation */
    UARTX_CR1(dwUartNo) &= ~(USART_CR1_RE\
                           | USART_CR1_TE\
                           | USART_CR1_UE\
                           | USART_CR1_RXNEIE\
                           | USART_CR1_TXEIE\
                           | USART_CR1_PEIE);
    UARTX_CR3(dwUartNo) &= ~(USART_CR3_EIE);

    
    /* Configure stop bit, bit mode, parity and Buad rate */
    if (SW_ERR == Uartx_Ctrl(ptPara))
    {
        return SW_ERR;
    }
    
    /* Clear error flags and data buffer */
    u16Data = UARTX_SR(dwUartNo);
    u16Data = UARTX_DR(dwUartNo);
    
    /* Enable Tx/Rx function, Rx interrupt and Error interrupt */
    UARTX_CR1(dwUartNo) |= (USART_CR1_RE\
                          | USART_CR1_TE\
                          | USART_CR1_UE\
                          | USART_CR1_RXNEIE\
                          | USART_CR1_PEIE);
    UARTX_CR3(dwUartNo) |=  USART_CR3_EIE;
    
    return SW_OK;
}



/******************************************************************************
* Name       : uint8 Moe_HAL_Uart_Byte_Receive(void)
* Function   : Get a single byte data from uart receiving buffer
* Input      : None.
* Output:    : None.
* Return     : uint8 Received data.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Byte_Receive(void)
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

