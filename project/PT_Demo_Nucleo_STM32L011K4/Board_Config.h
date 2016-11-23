/******************************************************************************
* File       : Board_Config.h
* Function   : Hardware configurations
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 22nd Novl 2016
* History    :  No.  When           Who           What
*               1    22/Nov/2016    Ian           Create
******************************************************************************/

#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_BOARD_CONFIG                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_BOARD_CONFIG   /* According the set from project_config.h */
#endif

#define SYSTICK_CNT_FOR_1_MS                  (32000)

#define BOARD_CONFIG_BTN_ST_HIGH              (1)     /* The voltage state of pin is HIGH */
#define BOARD_CONFIG_BTN_ST_LOW               (0)     /* The voltage state of pin is LOW  */

#define BOARD_CONFIG_LED_BLUE                 (3)     /* Blue led        */
#define BOARD_CONFIG_LED_RED                  (2)     /* Red led         */
#define BOARD_CONFIG_LED_YELLOW               (1)     /* Yellow led      */
#define BOARD_CONFIG_LED_GREEN                (0)     /* Green led       */

#define BOARD_CONFIG_LED_ON                   (0)     /* led ON mode     */
#define BOARD_CONFIG_LED_OFF                  (1)     /* led OFF mode    */
#define BOARD_CONFIG_LED_TOGGLE               (3)     /* led Toggle mode */


/******************************************************************************
* Name       : void LED_Off(uint8 u8Ch)
* Function   : LED Off control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 22nd Nov 2016
******************************************************************************/
void LED_Off(uint8 u8Ch);
 
/******************************************************************************
* Name       : void LED_On(uint8 u8Ch)
* Function   : LED On control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 22nd Nov 2016
******************************************************************************/
void LED_On(uint8 u8Ch);

void Board_Init(void);
void Board_Config_Reset_Ctrl(uint8 u8Val);
void SysTick_Ms_Int_Init(uint32 u32Tick);
uint32 SysTick_GetSysClk(void);

#ifdef __cplusplus
}
#endif

#endif /* _BOARD_CONFIG_H */

/* End of file */


