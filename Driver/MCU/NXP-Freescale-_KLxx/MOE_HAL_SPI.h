/******************************************************************************
* File       : MOE_HAL_SPI.h
* Function   : Hardware Abstract Layer for SPI of NXP KLXX MCU.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
* History    :  No.  When           Who           What
*               1    13/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_HAL_SPI_H_
#define _MOE_HAL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_HAL_SPI                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_HAL_SPI        /* According the set from project_config.h */
#endif

#define MOE_SPI_CS_HIGH           (1)     /* High level for SPI Cs pin */
#define MOE_SPI_CS_LOW            (0)     /* Low level for SPI Cs pin  */

/******************************************************************************
* Name       : uint8 uint8 Moe_HAL_SPI_Init(void)
* Function   : Init hardware abstract layer for SPI
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 Moe_HAL_SPI_Init(void);

/******************************************************************************
* Name       : void Moe_HAL_SPI_Write(uint8 u8Data)
* Function   : SPI write operation
* Input      : uint8 u8Data  0~255    Data byte to be writen
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
void Moe_HAL_SPI_Write(uint8 u8Data);


/******************************************************************************
* Name       : uint8 Moe_HAL_SPI_Read(void)
* Function   : SPI read operation
* Input      : None.
* Output:    : None.
* Return     : uint8
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 Moe_HAL_SPI_Read(void);

/******************************************************************************
* Name       : void Moe_HAL_SPI_Write(uint8 ucData)
* Function   : SPI write operation
* Input      : uint8 u8Val    MOE_SPI_CS_LOW    Set Cs as low level
*                             MOE_SPI_CS_HIGH   Set Cs as high level
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
void Moe_HAL_SPI_Cs_Ctrl(uint8 u8Val);


 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_HAL_SPI_H_ */

/* End of file */

