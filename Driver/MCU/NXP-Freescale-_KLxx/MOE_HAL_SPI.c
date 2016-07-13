/******************************************************************************
* File       : MOE_HAL_SPI.c
* Function   : Hardware Abstract Layer for SPI of NXP KLXX MCU.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
* History    :  No.  When           Who           What
*               1    13/Jul/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Msg.h"
#include "MOE_HAL.h"
#include "MOE_HAL_SPI.h"
#include "debug.h"

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
uint8 Moe_HAL_SPI_Init(void)
{  
    uint32 u32SpiC1 = 0;
    
    SIM_SCGC4 |=   SIM_SCGC4_SPI1_MASK;    /* Enoble SPI1 clock */

    /* Configure C1 */
    u32SpiC1  |= ( SPI_C1_SPE_MASK         /* Enable SPI1       */
                 | SPI_C1_MSTR_MASK        /* As Master         */
                 | SPI_C1_SSOE_MASK);      /* Slave select      */
    SPI1_C1    =   u32SpiC1;

    SPI1_C2   |=  SPI_C2_MODFEN_MASK; 
    SPI1_BR   |=  SPI_BR_SPPR(0) | SPI_BR_SPR(6);

    return SW_OK;

}

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
void Moe_HAL_SPI_Write(uint8 u8Data)
{   
    while((SPI1_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);           
    SPI1_D = u8Data;    
    return;
}


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
uint8 Moe_HAL_SPI_Read(void)
{
    uint8 u8Temp;
    
    while((SPI1_S & SPI_S_SPRF_MASK) != SPI_S_SPRF_MASK);             
    u8Temp = SPI1_D;
    return u8Temp;
}

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
void Moe_HAL_SPI_Cs_Ctrl(uint8 u8Val)
{
    if(MOE_SPI_CS_LOW == u8Val)    
    {
        GPIOE_PCOR |= (1 << 4);    /* Set Cs as low level  */
    }
    else
    {
        GPIOE_PSOR |= (1 << 4);    /* Set Cs as high level */
    }
    return;
}


/* end of file */

