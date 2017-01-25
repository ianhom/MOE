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
#include "../../../Pub/common_head.h"
#include "project_config.h"
#include "../../../Core/MOE_Core.h"
#include "../../../Core/MOE_Msg.h"
#include "../../../Core/MOE_HAL.h"
#include "./MOE_HAL_UART.h"
#include "../../../Pub/debug.h"

extern int periph_clk_khz;

static uint8 sg_u8RcvLen = 0;
static uint8 sg_u8Index  = 0;
static uint8 sg_au8RcvData[40] = {0}; 
static uint8 sg_u8GetTel = MOE_HAL_UART_NO_RCV_TEL;

/******************************************************************************
* Name       : uint8 Moe_HAL_UART_Cfg(T_MOE_DRV_PARA *ptCfg)
* Function   : Configure hardware abstract layer for UART
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jul 2016
******************************************************************************/
uint8 Moe_HAL_UART_Cfg(T_MOE_DRV_PARA *ptCfg)
{
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
    UART1_C2 |= UART_C2_RIE_MASK;
    NVIC_ISER = 1<<(13);
    /* Enable Error interrupt. */
    UART1_C3 |= (UART_C3_PEIE_MASK | UART_C3_FEIE_MASK | UART_C3_NEIE_MASK | UART_C3_ORIE_MASK); 

    return SW_OK;  
}

/******************************************************************************
* Name       : uint8 Moe_HAL_UART_Ctrl(T_MOE_DRV_PARA *ptCtrl)
* Function   : Send control command to UART
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jul 2016
******************************************************************************/
uint8 Moe_HAL_UART_Ctrl(T_MOE_DRV_PARA *ptCtrl)
{
    reutrn SW_OK;
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
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Byte_Receive(void)
{
    while (!(UART1_S1 & UART_S1_RDRF_MASK)); /* Check if any available data in receiving buffer */
    return UART1_D;
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
* Function   : Check rx buffer is free or NOT
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


/******************************************************************************
* Name       : uint8 Moe_HAL_Uart_Got_Telegram(void)
* Function   : Check gets an entire telegram or NOT
* Input      : None.
* Output:    : None.
* Return     : MOE_HAL_UART_RCV_TEL     Get a entire telegram
*              MOE_HAL_UART_NO_RCV_TEL  Get NO telegram
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Got_Telegram(void)
{
    return sg_u8GetTel;
}

/******************************************************************************
* Name       : uint8 Moe_HAL_Uart_Tele_Receive(uint8 *pu8Data)
* Function   : Get the entire byte data
* Input      : uint8 *pu8Data    pointer to save the telegram
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Uart_Tele_Receive(uint8 *pu8Data)
{
    uint8 u8Idx;
    
    /* If the telegram get flag is NOT set */
    if(MOE_HAL_UART_NO_RCV_TEL == sg_u8GetTel)
    {   /* Return error */
        return SW_ERR;
    }

    /* Copy the received telegram to desired address */
    for(u8Idx = 0; u8Idx < sg_u8RcvLen + 1; u8Idx++)
    {
        pu8Data[u8Idx] = sg_au8RcvData[u8Idx];
    }
    
    sg_u8GetTel = MOE_HAL_UART_NO_RCV_TEL;  /* Clear the flag */

    return SW_OK;
} 


/******************************************************************************
* Name       : void Moe_HAL_Uart_Rx_Int_Enable(void)
* Function   : Enable uart rx interrupt
* Input      : None.
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
void Moe_HAL_Uart_Rx_Int_Enable(void)
{
    UART1_C2 |= UART_C2_RIE_MASK;
    return;
}

/******************************************************************************
* Name       : void Moe_HAL_Uart_Rx_Int_Disable(void)
* Function   : Disable uart rx interrupt
* Input      : None.
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
void Moe_HAL_Uart_Rx_Int_Disable(void)
{
    UART1_C2 &= ~(UART_C2_RIE_MASK);
    return;
}


/******************************************************************************
* Name       : void Uart1_isr(void)
* Function   : Uart1 interrupt process
* Input      : None.
* Output:    : None.
* Return     : None.
* description: When rx interrupt, isr will get the length of telegram and then
*              automatically receive the rest bytes.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
void Uart1_isr(void)
{
    uint8 u8Temp;
    if(UART1_S1 & UART_S1_RDRF_MASK)
    {
        u8Temp = UART1_D;
        if(0 == sg_u8Index)
        {
            sg_u8RcvLen = u8Temp;
        }
        sg_au8RcvData[sg_u8Index] = u8Temp;
        sg_u8Index++;            

        if(sg_u8Index > sg_u8RcvLen)
        {
            sg_u8Index  = 0;
            sg_u8GetTel = MOE_HAL_UART_RCV_TEL;
        }
    }
    return;
}


/* end of file */

