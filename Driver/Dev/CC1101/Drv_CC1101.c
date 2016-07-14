/******************************************************************************
* File       : MOE_DRV_CC1101.c
* Function   : Driver for CC1101.
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
#include "MOE_DRV_CC1101.h"
#include "debug.h"

/******************************************************************************
* Name       : uint8 CC1101_Init(void)
* Function   : Init operation for CC1101.
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_Init(void)
{
    CC1101_Cmd(ADDR_CMD_SRES);
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 CC1101_Cmd(uint8 u8Cmd)
* Function   : Send a command of CC1101
* Input      : uint8 u8Cmd    0x30~0x3D     Control command of CC1101
* Output:    : None.
* Return     : uint8 Status of CC1101.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_Cmd(uint8 u8Cmd)
{
    uint8 u8Temp;

    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_LOW);
    Moe_HAL_SPI_Write(u8Cmd);            /* Send the command */
    u8Temp = Moe_HAL_SPI_Read();
    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_HIGH);

    return u8Temp;
}

/******************************************************************************
* Name       : uint8 CC1101_Reg_Read_Single(uint8 u8Reg)
* Function   : Read the value of a single register of CC1101
* Input      : uint8 u8Reg    0x00~0x2E     Register address of CC1101
* Output:    : None.
* Return     : uint8 Register value of CC1101.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_Reg_Read_Single(uint8 u8Reg)
{
    uint8 u8Temp;

    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_LOW);
    Moe_HAL_SPI_Write(u8Reg + READ_SINGLE_MASK);  /* Write register address first */
    Moe_HAL_SPI_Read();
    Moe_HAL_SPI_Write(DUMMY_BYTE);                /* Write a dummy byte for read  */
    u8Temp = Moe_HAL_SPI_Read();                  /* Get the register value       */
    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_HIGH);

    return u8Temp;
}

/******************************************************************************
* Name       : uint8 CC1101_Reg_Read_Multi(uint8 u8Addr, uint8 u8Len, uint8 *pu8Data)
* Function   : Read the value of multi registers or RX FIFO of CC1101
* Input      : uint8  u8Addr     0x00~0x2E     Register address of CC1101
*                                0x3F          RX FIFO address of CC1101
*              uint8  u8Len      0~64          Length of reading bytes
*              uint8 *pu8Data                  Pointer for reading bytes.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_Reg_Read_Multi(uint8 u8Reg, uint8 u8Len, uint8 *pu8Data)
{
    uint8 u8Index;

    /* Check input paramters */
    if((u8Len > CC1101_MAX_ADDR) || (u8Len > CC1101_MAX_ADDR) || (NULL == pu8Data))
    {
        return SW_ERR;
    }

    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_LOW);
    Moe_HAL_SPI_Write(u8Reg + READ_MULTI_MASK);   /* Write the first reading register */
    Moe_HAL_SPI_Read();
    for(u8Index = 0; u8Index < u8Len; u8Index++)
    {
        Moe_HAL_SPI_Write(DUMMY_BYTE);            /* Write dummy byte for reading     */
        pu8Data[u8Index] = Moe_HAL_SPI_Read();    /* Get the return bytes             */
    }
    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_HIGH);
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 CC1101_Reg_Write_Single(uint8 u8Reg, uint8 u8Val)
* Function   : Write the value into a single register of CC1101
* Input      : uint8 u8Reg    0x00~0x2E     Register address of CC1101
*              uint8 u8Val    0~255         Value to be writen
* Output:    : None.
* Return     : uint8 Register value of CC1101.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_Reg_Write_Single(uint8 u8Reg, uint8 u8Val)
{
    uint8 u8Temp;

    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_LOW);
    Moe_HAL_SPI_Write(u8Reg + WRITE_SINGLE_MASK);   /* Write register address first */
    Moe_HAL_SPI_Read();
    Moe_HAL_SPI_Write(u8Val);                       /* Write the desired value      */
    u8Temp = Moe_HAL_SPI_Read();
    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_HIGH);

    return u8Temp;
}


/******************************************************************************
* Name       : uint8 CC1101_Reg_Write_Multi(uint8 u8Reg, uint8 u8Len, uint8* pu8Data)
* Function   : Read the value of multi registers or TX FIFO of CC1101
* Input      : uint8  u8Addr     0x00~0x2E     Register address of CC1101
*                                0x3F          TX FIFO address of CC1101
*              uint8  u8Len      0~64          Length of reading bytes
*              uint8 *pu8Data                  Pointer for writing bytes.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_Reg_Write_Multi(uint8 u8Reg, uint8 u8Len, uint8* pu8Data)
{
    uint8 u8Index;

    /* Check input paramters */
    if((u8Len > CC1101_MAX_ADDR) || (u8Len > CC1101_MAX_ADDR) || (NULL == pu8Data))
    {
        return SW_ERR;
    }

    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_LOW);
    Moe_HAL_SPI_Write(u8Reg + WRITE_MULTI_MASK);
    Moe_HAL_SPI_Read();
    for(u8Index = 0; u8Index < u8Len; u8Index++)
    {
        Moe_HAL_SPI_Write(pu8Data[u8Index]);
        Moe_HAL_SPI_Read();
    }
    Moe_HAL_SPI_Cs_Ctrl(MOE_SPI_CS_HIGH);

    return SW_OK;
}


/******************************************************************************
* Name       : uint8 CC1101_FIFO_Read(uint8 *pu8Data)
* Function   : Read RX FIFO of CC1101
* Input      : uint8 *pu8Data                  Pointer for reading bytes.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_FIFO_Read(uint8 *pu8Data)
{
    /* Check input paramters */
    if(NULL == pu8Data)
    {
        return SW_ERR;
    }
    CC1101_Reg_Read_Multi(ADDR_FIFO_RX, CC1101_MAX_ADDR, pu8Data);
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 CC1101_FIFO_Write(uint8 *pu8Data)
* Function   : Read TX FIFO of CC1101
* Input      : uint8 *pu8Data                  Pointer for writing bytes.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_FIFO_Write(uint8 *pu8Data)
{
    /* Check input paramters */
    if(NULL == pu8Data)
    {
        return SW_ERR;
    }

    CC1101_Reg_Write_Multi(ADDR_FIFO_TX, CC1101_MAX_ADDR, pu8Data);
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 CC1101_Global_Config(uint8 *pu8Data)
* Function   : Read TX FIFO of CC1101
* Input      : uint8 *pu8Data                  Pointer for writing parameter.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_Global_Config(uint8 *pu8Data)
{
    /* Check input paramters */
    if(NULL == pu8Data)
    {
        return SW_ERR;
    }

    CC1101_Reg_Write_Multi(ADDR_REG_IOCFG2, CC1101_MAX_REG, pu8Data);
    return SW_OK;
}

/******************************************************************************
* Name       : uint8 CC1101_Global_Config(uint8 *pu8Data)
* Function   : Read TX FIFO of CC1101
* Input      : uint8 *pu8Data                  Pointer for writing parameter.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 CC1101_PA_Config(uint8 *pu8Data)
{
    /* Check input paramters */
    if(NULL == pu8Data)
    {
        return SW_ERR;
    }

    CC1101_Reg_Write_Multi(ADDR_PATABLE, CC1101_MAX_REG, pu8Data);
    return SW_OK;
}



/* end of file */

