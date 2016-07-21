/******************************************************************************
* File       : MOE_DRV_11xx.h
* Function   : Driver for 11xx.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
* History    :  No.  When           Who           What
*               1    20/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_DRV_11XX_H_
#define _MOE_DRV_11XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_DRV_11XX                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_DRV_11XX       /* According the set from project_config.h */
#endif

#define __11XX_2

#define DRV_11XX_CFG_MODE               (0x00)            /* Command to enter configuration mode     */
#define DRV_11XX_IDLE                   (0x58)            /* Command to enter IDLE state (normal)    */
#define DRV_11XX_END_M                  (0xFF)            /* Command to exit "M" sub-mode            */   
#define DRV_11XX_RSPON                  (0x3E)            /* Responing code                          */

#define DRV_11XX_MAX_BIND_ADDR          (64)              /* Max number of bind sender address       */
#define DRV_11XX_SN_LEN                 (6)               /* The length of SN address                */    

#define DRV_11XX_MODE_SEL_CMD           (0x47)            /* Command to select operating mode        */

#define DRV_11XX_MODE_S1                (3)               /* S1 sending only uni-direction mode      */
#define DRV_11XX_MODE_S2                (0)               /* S2 bi-direction mode                    */     

#define DRV_11XX_RCV_MODE_CMD           (0x49)            /* Command to select receiving mode        */

#define DRV_11XX_NORMAL_RCV             (0)               /* Receive telegram with normal operation  */
#define DRV_11XX_ALL_RCV                (2)               /* Receive all telegram                    */

#define DRV_11XX_OUTPUT_PWR_CMD         (0x50)            /* Command to select output power          */



#define DRV_11XX_REG_OUTPUT_PWR         (0x01)            /* Reg address: Output power               */
#define DRV_11XX_REG_OP_MODE            (0x03)            /* Reg address: Operating mode             */
#define DRV_11XX_REG_SLEEP_MODE         (0x04)            /* Reg address: Sleep mode                 */
#define DRV_11XX_REG_SHOW_RSSI          (0x05)            /* Reg address: Show RSSI info in rcv data */
#define DRV_11XX_REG_PREAMBLE_TYPE      (0x0A)            /* Reg address: long/short preamble type   */
#define DRV_11XX_REG_BTY_THR            (0x0B)            /* Reg address: Battery threshold setting  */
#define DRV_11XX_REG_TM_OUT             (0x10)            /* Reg address: Time out for uart sending  */
#define DRV_11XX_REG_ROLE               (0x12)            /* Reg address: Network role               */
#define DRV_11XX_REG_SN                 (0x1B)            /* Reg address: First byte of SN address   */
#define DRV_11XX_REG_DOA                (0x21)            /* Reg address: First byte of DoA address  */
#define DRV_11XX_REG_BAUD_RATE          (0x30)            /* Reg address: Uart baud rate setting     */
#define DRV_11XX_REG_FLOW_CTRL          (0x35)            /* Reg address: Flow control setting       */
#define DRV_11XX_REG_D_INTERFACE        (0x36)            /* Reg address: Data interface             */
#define DRV_11XX_REG_FREQ_CAL           (0x39)            /* Reg address: Frequence calibration      */
#define DRV_11XX_REG_LED_CTRL           (0x3A)            /* Reg address: Led control                */
#define DRV_11XX_REG_RCV_MODE           (0x3D)            /* Reg address: Receiving mode             */
#define DRV_11XX_REG_MULTI_MODE         (0x60)            /* Reg address: Multi mode setting         */
#define DRV_11XX_REG_CALL_CH            (0x61)            /* Reg address: Call channel               */
#define DRV_11XX_REG_GRP_ADDR_NUM       (0x62)            /* Reg address: Gruop address number store */
#define DRV_11XX_REG_F3_ENABLE          (0x64)            /* Reg address: Fast channel F3 enable     */
#define DRV_11XX_REG_REPEATER           (0x66)            /* Reg address: Repeat mode setting        */
#define DRV_11XX_REG_UART_ACK           (0x68)            /* Reg address: Enable ACK & NACK on uart  */
#ifdef __11XX_1
#define DRV_11XX_REG_PART_NUM           (0x61)            /* Reg address: Part number of module      */
#define DRV_11XX_REG_HW_REV             (0x6D)            /* Reg address: Hardware version           */
#define DRV_11XX_REG_FW_REV             (0x72)            /* Reg address: Firmware version           */
#elif (defined (__11XX_2))
#define DRV_11XX_REG_DEV_SERIAL         (0x96)            /* Reg address: Module serial (NOT SN)     */
#define DRV_11XX_REG_PART_NUM           (0x9E)            /* Reg address: Part number of module      */
#define DRV_11XX_REG_HW_REV             (0xAA)            /* Reg address: Hardware version           */
#define DRV_11XX_REG_FW_REV             (0xAF)            /* Reg address: Firmware version           */
#endif


      
/******************************************************************************
* Name       : uint8 Drv_11XX_Init(void);
* Function   : Init operation for 11xx.
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11XX_Init(void);

/******************************************************************************
* Name       : uint8 Drv_11xx_Simple_Cmd(uint8 u8Cmd)
* Function   : Send command to 11xx
* Input      : uint8 u8Cmd
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd(uint8 u8Cmd);

/******************************************************************************
* Name       : uint8 Drv_11xx_Simple_Cmd(uint8 u8Cmd)
* Function   : Send command with 1 byte value to 11xx
* Input      : uint8 u8Cmd    0~255    Command code
*              uint8 u8Val    0~255    Value after command
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Cmd_1Val(uint8 u8Cmd, uint8 u8Val);


/******************************************************************************
* Name       : uint8 Drv_11xx_Bind(uint8 u8Ch, uint8 *pu8Addr)
* Function   : Bind a sender SN address
* Input      : uint8  u8Ch       1~64      Index of address
*              uint8 *pu8Addr              Pointer for SN address
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Bind(uint8 u8Ch, uint8 *pu8Addr);

/******************************************************************************
* Name       : uint8 Drv_11xx_Mode_Sel(uint8 u8Mode)
* Function   : Select operating mode 
* Input      : uint8  u8Mode    DRV_11XX_MODE_S1    S1 sending only mode
*                               DRV_11XX_MODE_S2    S2 bi-direction mode
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Mode_Sel(uint8 u8Mode);

/******************************************************************************
* Name       : uint8 Drv_11xx_Rcv_Mode(uint8 u8Mode)
* Function   : Select receving mode  
* Input      : uint8  u8Mode    DRV_11XX_NORMAL_RCV    Receive normal telegram
*                               DRV_11XX_ALL_RCV       Receive all telegram
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 20th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Rcv_Mode(uint8 u8Mode);

/******************************************************************************
* Name       : uint8 Drv_11xx_Power_Sel(uint8 u8Lv)
* Function   : Select output power
* Input      : uint8  u8Lv    1~5         Output level
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21th Jul 2016
******************************************************************************/
uint8 Drv_11xx_Power_Sel(uint8 u8Lv);

 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_DRV_11XX_H_ */

/* End of file */

