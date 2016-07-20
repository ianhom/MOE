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
* Function   : Bind a sender SN address    
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
* Function   : Bind a sender SN address    
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

 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_DRV_11XX_H_ */

/* End of file */

