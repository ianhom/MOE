/******************************************************************************
* File       : MOE_HAL_UART.h
* Function   : Hardware Abstract Layer for UART of STM32F10X.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 26th Jul 2016
* History    :  No.  When           Who           What
*               1    26/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_HAL_UART_H_
#define _MOE_HAL_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_HAL_UART                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_HAL_UART       /* According the set from project_config.h */
#endif

#define MOE_HAL_UART_SND_BUF_FREE                   (1)   /* Uart sending buffer is free             */
#define MOE_HAL_UART_SND_BUF_NOT_FREE               (0)   /* Uart sending buffer is NOT free         */

#define MOE_HAL_UART_NO_RCV_DATA                    (0)   /* Uart get NONE received data             */
#define MOE_HAL_UART_RCV_DATA                       (1)   /* Uart get a received data                */

/******************************************************************************/
/*                                                                            */
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for USART_SR register  *******************/
#define USART_SR_PE_POS                     (0U)                               
#define USART_SR_PE_MASK                    (0x1U << USART_SR_PE_POS)          /*!< 0x00000001 */
#define USART_SR_PE                         USART_SR_PE_MASK                   /*!< Parity Error */
#define USART_SR_FE_POS                     (1U)                               
#define USART_SR_FE_MASK                    (0x1U << USART_SR_FE_POS)          /*!< 0x00000002 */
#define USART_SR_FE                         USART_SR_FE_MASK                   /*!< Framing Error */
#define USART_SR_NE_POS                     (2U)                               
#define USART_SR_NE_MASK                    (0x1U << USART_SR_NE_POS)          /*!< 0x00000004 */
#define USART_SR_NE                         USART_SR_NE_MASK                   /*!< Noise Error Flag */
#define USART_SR_ORE_POS                    (3U)                               
#define USART_SR_ORE_MASK                   (0x1U << USART_SR_ORE_POS)         /*!< 0x00000008 */
#define USART_SR_ORE                        USART_SR_ORE_MASK                  /*!< OverRun Error */
#define USART_SR_IDLE_POS                   (4U)                               
#define USART_SR_IDLE_MASK                  (0x1U << USART_SR_IDLE_POS)        /*!< 0x00000010 */
#define USART_SR_IDLE                       USART_SR_IDLE_MASK                 /*!< IDLE line detected */
#define USART_SR_RXNE_POS                   (5U)                               
#define USART_SR_RXNE_MASK                  (0x1U << USART_SR_RXNE_POS)        /*!< 0x00000020 */
#define USART_SR_RXNE                       USART_SR_RXNE_MASK                 /*!< Read Data Register Not Empty */
#define USART_SR_TC_POS                     (6U)                               
#define USART_SR_TC_MASK                    (0x1U << USART_SR_TC_POS)          /*!< 0x00000040 */
#define USART_SR_TC                         USART_SR_TC_MASK                   /*!< Transmission Complete */
#define USART_SR_TXE_POS                    (7U)                               
#define USART_SR_TXE_MASK                   (0x1U << USART_SR_TXE_POS)         /*!< 0x00000080 */
#define USART_SR_TXE                        USART_SR_TXE_MASK                  /*!< Transmit Data Register Empty */
#define USART_SR_LBD_POS                    (8U)                               
#define USART_SR_LBD_MASK                   (0x1U << USART_SR_LBD_POS)         /*!< 0x00000100 */
#define USART_SR_LBD                        USART_SR_LBD_MASK                  /*!< LIN Break Detection Flag */
#define USART_SR_CTS_POS                    (9U)                               
#define USART_SR_CTS_MASK                   (0x1U << USART_SR_CTS_POS)         /*!< 0x00000200 */
#define USART_SR_CTS                        USART_SR_CTS_MASK                  /*!< CTS Flag */

#define USART_SR_ERR_MASK                   (USART_SR_ORE | USART_SR_NE | USART_SR_FE | USART_SR_PE) /* All kinds of error */


/*******************  Bit definition for USART_DR register  *******************/
#define USART_DR_DR_POS                     (0U)                               
#define USART_DR_DR_MASK                    (0x1FFU << USART_DR_DR_POS)        /*!< 0x000001FF */
#define USART_DR_DR                         USART_DR_DR_MASK                   /*!< Data value */

/******************  Bit definition for USART_BRR register  *******************/
#define USART_BRR_DIV_Fraction_POS          (0U)                               
#define USART_BRR_DIV_Fraction_MASK         (0xFU << USART_BRR_DIV_Fraction_POS) /*!< 0x0000000F */
#define USART_BRR_DIV_Fraction              USART_BRR_DIV_Fraction_MASK        /*!< Fraction of USARTDIV */
#define USART_BRR_DIV_Mantissa_POS          (4U)                               
#define USART_BRR_DIV_Mantissa_MASK         (0xFFFU << USART_BRR_DIV_Mantissa_POS) /*!< 0x0000FFF0 */
#define USART_BRR_DIV_Mantissa              USART_BRR_DIV_Mantissa_MASK        /*!< Mantissa of USARTDIV */

/******************  Bit definition for USART_CR1 register  *******************/
#define USART_CR1_SBK_POS                   (0U)                               
#define USART_CR1_SBK_MASK                  (0x1U << USART_CR1_SBK_POS)        /*!< 0x00000001 */
#define USART_CR1_SBK                       USART_CR1_SBK_MASK                 /*!< Send Break */
#define USART_CR1_RWU_POS                   (1U)                               
#define USART_CR1_RWU_MASK                  (0x1U << USART_CR1_RWU_POS)        /*!< 0x00000002 */
#define USART_CR1_RWU                       USART_CR1_RWU_MASK                 /*!< Receiver wakeup */
#define USART_CR1_RE_POS                    (2U)                               
#define USART_CR1_RE_MASK                   (0x1U << USART_CR1_RE_POS)         /*!< 0x00000004 */
#define USART_CR1_RE                        USART_CR1_RE_MASK                  /*!< Receiver Enable */
#define USART_CR1_TE_POS                    (3U)                               
#define USART_CR1_TE_MASK                   (0x1U << USART_CR1_TE_POS)         /*!< 0x00000008 */
#define USART_CR1_TE                        USART_CR1_TE_MASK                  /*!< Transmitter Enable */
#define USART_CR1_IDLEIE_POS                (4U)                               
#define USART_CR1_IDLEIE_MASK               (0x1U << USART_CR1_IDLEIE_POS)     /*!< 0x00000010 */
#define USART_CR1_IDLEIE                    USART_CR1_IDLEIE_MASK              /*!< IDLE Interrupt Enable */
#define USART_CR1_RXNEIE_POS                (5U)                               
#define USART_CR1_RXNEIE_MASK               (0x1U << USART_CR1_RXNEIE_POS)     /*!< 0x00000020 */
#define USART_CR1_RXNEIE                    USART_CR1_RXNEIE_MASK              /*!< RXNE Interrupt Enable */
#define USART_CR1_TCIE_POS                  (6U)                               
#define USART_CR1_TCIE_MASK                 (0x1U << USART_CR1_TCIE_POS)       /*!< 0x00000040 */
#define USART_CR1_TCIE                      USART_CR1_TCIE_MASK                /*!< Transmission Complete Interrupt Enable */
#define USART_CR1_TXEIE_POS                 (7U)                               
#define USART_CR1_TXEIE_MASK                (0x1U << USART_CR1_TXEIE_POS)      /*!< 0x00000080 */
#define USART_CR1_TXEIE                     USART_CR1_TXEIE_MASK               /*!< PE Interrupt Enable */
#define USART_CR1_PEIE_POS                  (8U)                               
#define USART_CR1_PEIE_MASK                 (0x1U << USART_CR1_PEIE_POS)       /*!< 0x00000100 */
#define USART_CR1_PEIE                      USART_CR1_PEIE_MASK                /*!< PE Interrupt Enable */
#define USART_CR1_PS_POS                    (9U)                               
#define USART_CR1_PS_MASK                   (0x1U << USART_CR1_PS_POS)         /*!< 0x00000200 */
#define USART_CR1_PS                        USART_CR1_PS_MASK                  /*!< Parity Selection */
#define USART_CR1_PCE_POS                   (10U)                              
#define USART_CR1_PCE_MASK                  (0x1U << USART_CR1_PCE_POS)        /*!< 0x00000400 */
#define USART_CR1_PCE                       USART_CR1_PCE_MASK                 /*!< Parity Control Enable */
#define USART_CR1_WAKE_POS                  (11U)                              
#define USART_CR1_WAKE_MASK                 (0x1U << USART_CR1_WAKE_POS)       /*!< 0x00000800 */
#define USART_CR1_WAKE                      USART_CR1_WAKE_MASK                /*!< Wakeup method */
#define USART_CR1_M_POS                     (12U)                              
#define USART_CR1_M_MASK                    (0x1U << USART_CR1_M_POS)          /*!< 0x00001000 */
#define USART_CR1_M                         USART_CR1_M_MASK                   /*!< Word length */
#define USART_CR1_UE_POS                    (13U)                              
#define USART_CR1_UE_MASK                   (0x1U << USART_CR1_UE_POS)         /*!< 0x00002000 */
#define USART_CR1_UE                        USART_CR1_UE_MASK                  /*!< USART Enable */

/******************  Bit definition for USART_CR2 register  *******************/
#define USART_CR2_ADD_POS                   (0U)                               
#define USART_CR2_ADD_MASK                  (0xFU << USART_CR2_ADD_POS)        /*!< 0x0000000F */
#define USART_CR2_ADD                       USART_CR2_ADD_MASK                 /*!< Address of the USART node */
#define USART_CR2_LBDL_POS                  (5U)                               
#define USART_CR2_LBDL_MASK                 (0x1U << USART_CR2_LBDL_POS)       /*!< 0x00000020 */
#define USART_CR2_LBDL                      USART_CR2_LBDL_MASK                /*!< LIN Break Detection Length */
#define USART_CR2_LBDIE_POS                 (6U)                               
#define USART_CR2_LBDIE_MASK                (0x1U << USART_CR2_LBDIE_POS)      /*!< 0x00000040 */
#define USART_CR2_LBDIE                     USART_CR2_LBDIE_MASK               /*!< LIN Break Detection Interrupt Enable */
#define USART_CR2_LBCL_POS                  (8U)                               
#define USART_CR2_LBCL_MASK                 (0x1U << USART_CR2_LBCL_POS)       /*!< 0x00000100 */
#define USART_CR2_LBCL                      USART_CR2_LBCL_MASK                /*!< Last Bit Clock pulse */
#define USART_CR2_CPHA_POS                  (9U)                               
#define USART_CR2_CPHA_MASK                 (0x1U << USART_CR2_CPHA_POS)       /*!< 0x00000200 */
#define USART_CR2_CPHA                      USART_CR2_CPHA_MASK                /*!< Clock Phase */
#define USART_CR2_CPOL_POS                  (10U)                              
#define USART_CR2_CPOL_MASK                 (0x1U << USART_CR2_CPOL_POS)       /*!< 0x00000400 */
#define USART_CR2_CPOL                      USART_CR2_CPOL_MASK                /*!< Clock Polarity */
#define USART_CR2_CLKEN_POS                 (11U)                              
#define USART_CR2_CLKEN_MASK                (0x1U << USART_CR2_CLKEN_POS)      /*!< 0x00000800 */
#define USART_CR2_CLKEN                     USART_CR2_CLKEN_MASK               /*!< Clock Enable */

#define USART_CR2_STOP_POS                  (12U)                              
#define USART_CR2_STOP_MASK                 (0x3U << USART_CR2_STOP_POS)       /*!< 0x00003000 */
#define USART_CR2_STOP                      USART_CR2_STOP_MASK                /*!< STOP[1:0] bits (STOP bits) */
#define USART_CR2_STOP_0                    (0x1U << USART_CR2_STOP_POS)       /*!< 0x00001000 */
#define USART_CR2_STOP_1                    (0x2U << USART_CR2_STOP_POS)       /*!< 0x00002000 */

#define USART_CR2_STOP_ONE_BIT              (0x0U << USART_CR2_STOP_POS)       /*!< 0x00000000 */
#define USART_CR2_STOP_HALF_BIT             (0x1U << USART_CR2_STOP_POS)       /*!< 0x00001000 */
#define USART_CR2_STOP_TWO_BIT              (0x2U << USART_CR2_STOP_POS)       /*!< 0x00002000 */
#define USART_CR2_STOP_ONE_HALF_BIT         (0x3U << USART_CR2_STOP_POS)       /*!< 0x00003000 */


#define USART_CR2_LINEN_POS                 (14U)                              
#define USART_CR2_LINEN_MASK                (0x1U << USART_CR2_LINEN_POS)      /*!< 0x00004000 */
#define USART_CR2_LINEN                     USART_CR2_LINEN_MASK               /*!< LIN mode enable */

/******************  Bit definition for USART_CR3 register  *******************/
#define USART_CR3_EIE_POS                   (0U)                               
#define USART_CR3_EIE_MASK                  (0x1U << USART_CR3_EIE_POS)        /*!< 0x00000001 */
#define USART_CR3_EIE                       USART_CR3_EIE_MASK                 /*!< Error Interrupt Enable */
#define USART_CR3_IREN_POS                  (1U)                               
#define USART_CR3_IREN_MASK                 (0x1U << USART_CR3_IREN_POS)       /*!< 0x00000002 */
#define USART_CR3_IREN                      USART_CR3_IREN_MASK                /*!< IrDA mode Enable */
#define USART_CR3_IRLP_POS                  (2U)                               
#define USART_CR3_IRLP_MASK                 (0x1U << USART_CR3_IRLP_POS)       /*!< 0x00000004 */
#define USART_CR3_IRLP                      USART_CR3_IRLP_MASK                /*!< IrDA Low-Power */
#define USART_CR3_HDSEL_POS                 (3U)                               
#define USART_CR3_HDSEL_MASK                (0x1U << USART_CR3_HDSEL_POS)      /*!< 0x00000008 */
#define USART_CR3_HDSEL                     USART_CR3_HDSEL_MASK               /*!< Half-Duplex Selection */
#define USART_CR3_NACK_POS                  (4U)                               
#define USART_CR3_NACK_MASK                 (0x1U << USART_CR3_NACK_POS)       /*!< 0x00000010 */
#define USART_CR3_NACK                      USART_CR3_NACK_MASK                /*!< Smartcard NACK enable */
#define USART_CR3_SCEN_POS                  (5U)                               
#define USART_CR3_SCEN_MASK                 (0x1U << USART_CR3_SCEN_POS)       /*!< 0x00000020 */
#define USART_CR3_SCEN                      USART_CR3_SCEN_MASK                /*!< Smartcard mode enable */
#define USART_CR3_DMAR_POS                  (6U)                               
#define USART_CR3_DMAR_MASK                 (0x1U << USART_CR3_DMAR_POS)       /*!< 0x00000040 */
#define USART_CR3_DMAR                      USART_CR3_DMAR_MASK                /*!< DMA Enable Receiver */
#define USART_CR3_DMAT_POS                  (7U)                               
#define USART_CR3_DMAT_MASK                 (0x1U << USART_CR3_DMAT_POS)       /*!< 0x00000080 */
#define USART_CR3_DMAT                      USART_CR3_DMAT_MASK                /*!< DMA Enable Transmitter */
#define USART_CR3_RTSE_POS                  (8U)                               
#define USART_CR3_RTSE_MASK                 (0x1U << USART_CR3_RTSE_POS)       /*!< 0x00000100 */
#define USART_CR3_RTSE                      USART_CR3_RTSE_MASK                /*!< RTS Enable */
#define USART_CR3_CTSE_POS                  (9U)                               
#define USART_CR3_CTSE_MASK                 (0x1U << USART_CR3_CTSE_POS)       /*!< 0x00000200 */
#define USART_CR3_CTSE                      USART_CR3_CTSE_MASK                /*!< CTS Enable */
#define USART_CR3_CTSIE_POS                 (10U)                              
#define USART_CR3_CTSIE_MASK                (0x1U << USART_CR3_CTSIE_POS)      /*!< 0x00000400 */
#define USART_CR3_CTSIE                     USART_CR3_CTSIE_MASK               /*!< CTS Interrupt Enable */

/******************  Bit definition for USART_GTPR register  ******************/
#define USART_GTPR_PSC_POS                  (0U)                               
#define USART_GTPR_PSC_MASK                 (0xFFU << USART_GTPR_PSC_POS)      /*!< 0x000000FF */
#define USART_GTPR_PSC                      USART_GTPR_PSC_MASK                /*!< PSC[7:0] bits (Prescaler value) */
#define USART_GTPR_PSC_0                    (0x01U << USART_GTPR_PSC_POS)      /*!< 0x00000001 */
#define USART_GTPR_PSC_1                    (0x02U << USART_GTPR_PSC_POS)      /*!< 0x00000002 */
#define USART_GTPR_PSC_2                    (0x04U << USART_GTPR_PSC_POS)      /*!< 0x00000004 */
#define USART_GTPR_PSC_3                    (0x08U << USART_GTPR_PSC_POS)      /*!< 0x00000008 */
#define USART_GTPR_PSC_4                    (0x10U << USART_GTPR_PSC_POS)      /*!< 0x00000010 */
#define USART_GTPR_PSC_5                    (0x20U << USART_GTPR_PSC_POS)      /*!< 0x00000020 */
#define USART_GTPR_PSC_6                    (0x40U << USART_GTPR_PSC_POS)      /*!< 0x00000040 */
#define USART_GTPR_PSC_7                    (0x80U << USART_GTPR_PSC_POS)      /*!< 0x00000080 */

#define USART_GTPR_GT_POS                   (8U)                               
#define USART_GTPR_GT_MASK                  (0xFFU << USART_GTPR_GT_POS)       /*!< 0x0000FF00 */
#define USART_GTPR_GT                       USART_GTPR_GT_MASK                 /*!< Guard time value */



/******************************************************************************
* Name       : uint8 Moe_HAL_Init_UART(void)
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
uint8 Moe_HAL_UART_Init(void);

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
uint8 Moe_HAL_Uart_Byte_Receive();

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
void Moe_HAL_Uart_Byte_Send(uint8 u8Data);

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
uint8 Moe_HAL_Uart_Free_Send_Buf(void);

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
uint8 Moe_HAL_Uart_Got_Data(void);

 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_HAL_UART_H_ */

/* End of file */

