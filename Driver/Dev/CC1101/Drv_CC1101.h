/******************************************************************************
* File       : MOE_DRV_CC1101.h
* Function   : Driver for CC1101.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
* History    :  No.  When           Who           What
*               1    13/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_DRV_CC1101_H_
#define _MOE_DRV_CC1101_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_DRV_CC1101                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_DRV_CC1101     /* According the set from project_config.h */
#endif

#define READ_SINGLE_MASK           (0x80)                 /* Mask of single register reading */
#define READ_MULTI_MASK            (0xC0)                 /* Mask of multi register reading  */
#define WRITE_SINGLE_MASK          (0x00)                 /* Mask of single register writing */
#define WRITE_MULTI_MASK           (0x40)                 /* Mask of multi register writing  */

#define DUMMY_BYTE                 (0x3D)                 /* Dummy byte for reading          */

#define CC1101_MAX_ADDR            (0x40)                 /* Max register number of CC1101   */
#define CC1101_MAX_REG             (0x2F)                 /* Max config register number      */
#define CC1101_MAX_PA_NUM          (0x08)                 /* Max number of PA table          */

#define ADDR_REG_IOCFG2            (0x00)                 /* GDO2 configuration              */
#define ADDR_REG_IOCFG1            (0x01)                 /* GDO1 configuration              */
#define ADDR_REG_IOCFG0            (0x02)                 /* GDO0 configuration              */
#define ADDR_REG_FIFOTHR           (0x03)                 /* Thrshold for RX & TX FIFO       */
#define ADDR_REG_SYNC1             (0x04)                 /* Sync word high byte             */
#define ADDR_REG_SYNC0             (0x05)                 /* Sync word low byte              */
#define ADDR_REG_PKTLEN            (0x06)                 /* Length of packet                */
#define ADDR_REG_PKTCTRL1          (0x07)                 /* Auto packet control             */
#define ADDR_REG_PKTCTRL0          (0x08)                 /* Auto packet control             */
#define ADDR_REG_ADDR              (0x09)                 /* Local address                   */
#define ADDR_REG_CHANNR            (0x0A)                 /* Channel number                  */
#define ADDR_REG_FSCTRL1           (0x0B)                 /* Freq mixer control              */
#define ADDR_REG_FSCTRL0           (0x0C)                 /* Freq mixer control              */
#define ADDR_REG_FREQ2             (0x0D)                 /* Freq control byte               */
#define ADDR_REG_FREQ1             (0x0E)                 /* Freq control byte               */
#define ADDR_REG_FREQ0             (0x0F)                 /* Freq control byte               */
#define ADDR_REG_MDMCFG4           (0x10)                 /* Modem control                   */
#define ADDR_REG_MDMCFG3           (0x11)                 /* Modem control                   */
#define ADDR_REG_MDMCFG2           (0x12)                 /* Modem control                   */
#define ADDR_REG_MDMCFG1           (0x13)                 /* Modem control                   */
#define ADDR_REG_MDMCFG0           (0x14)                 /* Modem control                   */
#define ADDR_REG_DEVIATN           (0x15)                 /* Deviatn control                 */
#define ADDR_REG_MCSM2             (0x16)                 /* Main wireless state control     */
#define ADDR_REG_MCSM1             (0x17)                 /* Main wireless state control     */
#define ADDR_REG_MCSM0             (0x18)                 /* Main wireless state control     */
#define ADDR_REG_FOCCFG            (0x19)                 /* Freq offset cali                */
#define ADDR_REG_BSCFG             (0x1A)                 /* Bit sync configuration          */
#define ADDR_REG_AGCTRL2           (0x1B)                 /* AGC control                     */
#define ADDR_REG_AGCTRL1           (0x1C)                 /* AGC control                     */
#define ADDR_REG_AGCTRL0           (0x1D)                 /* AGC control                     */
#define ADDR_REG_WOREVT1           (0x1E)                 /* WOR event 1                     */
#define ADDR_REG_WOREVT0           (0x1F)                 /* WOR event 0                     */
#define ADDR_REG_WORCTRL           (0x20)                 /* WOR control                     */
#define ADDR_REG_FREND1            (0x21)                 /* RX configuration                */
#define ADDR_REG_FREND0            (0x22)                 /* TX configuration                */
#define ADDR_REG_FSCAL3            (0x23)                 /* Freq mixer cali                 */
#define ADDR_REG_FSCAL2            (0x24)                 /* Freq mixer cali                 */
#define ADDR_REG_FSCAL1            (0x25)                 /* Freq mixer cali                 */
#define ADDR_REG_FSCAL0            (0x26)                 /* Freq mixer cali                 */
#define ADDR_REG_RCCTRL1           (0x27)                 /* RC configuration                */
#define ADDR_REG_RCCTRL0           (0x28)                 /* RC configuration                */
#define ADDR_REG_FSTEST            (0x29)                 /* Freq mixer cali test            */
#define ADDR_REG_PTEST             (0x2A)                 /* Production test                 */
#define ADDR_REG_AGCTEST           (0x2B)                 /* AGC test                        */
#define ADDR_REG_TEST2             (0x2C)                 /* Test 1                          */
#define ADDR_REG_TEST1             (0x2D)                 /* Test 2                          */
#define ADDR_REG_TEST0             (0x2E)                 /* Test 3                          */

#define ADDR_CMD_SRES              (0x30)                 /* Command: rest                   */
#define ADDR_CMD_SFSTXON           (0x31)                 /* Command: Enable Freq cali       */
#define ADDR_CMD_SXOFF             (0x32)                 /* Command: Disable cycstal        */
#define ADDR_CMD_SCAL              (0x33)                 /* Command: Cali Freq              */
#define ADDR_CMD_SRX               (0x34)                 /* Command: Enable RX              */
#define ADDR_CMD_STX               (0x35)                 /* Command: Enable TX              */
#define ADDR_CMD_SIDLE             (0x36)                 /* Command: Enter IDLE             */
#define ADDR_CMD_SWOR              (0x38)                 /* Command: Enter WOR              */
#define ADDR_CMD_SPWD              (0x39)                 /* Command: Power off when Cs low  */
#define ADDR_CMD_SFRX              (0x3A)                 /* Command: Flush RX FIFO          */
#define ADDR_CMD_SFTX              (0x3B)                 /* Command: Flush TX FIFO          */
#define ADDR_CMD_SWORRST           (0x3C)                 /* Command: Rest RT as event 1     */
#define ADDR_CMD_SNOP              (0x3D)                 /* Command: No operation           */

#define ADDR_PATABLE               (0x3E)                 /* Address of PA table             */

#define ADDR_FIFO_TX               (0x3F)                 /* Address of TX FIFO              */
#define ADDR_FIFO_RX               (0x3F)                 /* Address of RX FIFO              */


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
uint8 CC1101_Init(void);

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
uint8 CC1101_Cmd(uint8 u8Cmd);

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
uint8 CC1101_Reg_Read_Single(uint8 u8Reg);

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
uint8 CC1101_Reg_Read_Multi(uint8 u8Reg, uint8 u8Len, uint8 *pu8Data);

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
uint8 CC1101_Reg_Write_Single(uint8 u8Reg, uint8 u8Val);

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
uint8 CC1101_Reg_Write_Multi(uint8 u8Reg, uint8 u8Len, uint8* pu8Data);

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
uint8 CC1101_FIFO_Read(uint8 *pu8Data);

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
uint8 CC1101_FIFO_Write(uint8 *pu8Data);

 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_DRV_CC1101_H_ */

/* End of file */

