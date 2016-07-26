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

