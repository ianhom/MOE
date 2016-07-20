/******************************************************************************
* File       : MOE_HAL_UART.c
* Function   : Hardware Abstract Layer for UART of KL25Z.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jul 2016
* History    :  No.  When           Who           What
*               1    19/Jul/2016    Ian           Create
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
* Date       : 19th Jul 2016
******************************************************************************/
uint8 Moe_HAL_UART_Init(void)
{
#if (1)
    volatile uint8 u8Data = 0;
    uint16         U16SBR = 0; 
    
    /*-------------------Set Uart clock ------------------------*/
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;                       /* MCGPLLCLK clock with fixed divide by 2 and get 24MHz */ 
    SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
    
    /*----Disable TX/RX first before UART init -----------------*/
    UART1_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);            /* Disable TX/RX first before UART init */
    
    /*----Disable TX/RX interrupt first before UART init -------*/
    UART1_C2 &= (~(UART_C2_TIE_MASK | UART_C2_RIE_MASK));
    UART1_C3 &= (~(UART_C3_PEIE_MASK | UART_C3_FEIE_MASK | UART_C3_NEIE_MASK | UART_C3_ORIE_MASK)); /* Disable all interrupt */
    
    /*----Config stop bit, bit mode, parity and Buad rate-------*/
    UART1_C1 &= ~(UART_C1_M_MASK);                             // 0:8-bit mode     

    UART1_BDH &= ~UART_BDH_SBNS_MASK;                          // 0: 1 stop bit

    UART1_C1 &= ~UART_C1_PE_MASK;                              // 0: No parity

    U16SBR = (periph_clk_khz * 1000) / (16 * 19200);

    UART1_BDH = (U16SBR >> 8);
    UART1_BDL = (U16SBR & UART_BDL_SBR_MASK);
    
 
    /* clear error flag. */
    UART1_S1 |= (UART_S1_PF_MASK | UART_S1_FE_MASK | UART_S1_NF_MASK | UART_S1_OR_MASK | UART_S1_IDLE_MASK);
    
    /*-----------------Clear data buffer------------------------*/
    u8Data = UART1_D;                                               /* dummy read to clear data register. */
    
    /*------------Enable TX/RX after UART init -----------------*/
    UART1_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);                //Enasable TX/RX first before UART init 
    
    /*------------Enable TX/RX interrupt after UART init -------*/
    //UART1_C2 |= UART_C2_RIE_MASK;
    
    /* Enable Error interrupt. */
    //UART1_C3 |= (UART_C3_PEIE_MASK | UART_C3_FEIE_MASK | UART_C3_NEIE_MASK | UART_C3_ORIE_MASK); 
#else
    
    uart_init (UART1_BASE_PTR, periph_clk_khz, 19200);
    
#endif

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
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Byte_Receive()
{
    while (!(UART1_S1 & UART_S1_RDRF_MASK)); /* Check if any available data in receiving buffer */
    return UART1_D;                          /* Return the received data                        */
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
* Date       : 20th Jul 2016
******************************************************************************/
void Moe_HAL_Uart_Byte_Send(uint8 u8Data)
{
    while(!(UART1_S1 & UART_S1_TDRE_MASK)); /* Check sending buffer is free or NOT */
    UART1_D = u8Data;                       /* Send the desired data               */
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
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Free_Send_Buf(void)
{
    return (!!(UART1_S1 & UART_S1_TDRE_MASK));
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
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Got_Data(void)
{
    return (!!(UART1_S1 & UART_S1_RDRF_MASK));
}

/* end of file */

