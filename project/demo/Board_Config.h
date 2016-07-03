/******************************************************************************
* File       : Board_Config.h
* Function   : Hardware configurations
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 3rd Jul 2016
* History    :  No.  When           Who           What
*               1    3/Jul/2016     Ian           Create
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


#define BOARD_CONFIG_BTN_ST_HIGH              (1)     /* The voltage state of pin is HIGH */
#define BOARD_CONFIG_BTN_ST_LOW               (0)     /* The voltage state of pin is LOW  */


/******************************************************************************
* Name       : void Gpio_Init()
* Function   : Init GPIOs
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd Jul 2016
******************************************************************************/
void Gpio_Init();

/******************************************************************************
* Name       : uint8 Btn_St_Get(uint8 u8Ch)
* Function   : Get the current state of buttons.
* Input      : uint8 u8Ch     1~255    The channel number of button
* Output:    : None
* Return     : BOARD_CONFIG_BTN_ST_HIGH  Pin with high voltage level
*              BOARD_CONFIG_BTN_ST_LOW   Pin with low voltage level
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd Jul 2016
******************************************************************************/
uint8 Btn_St_Get(uint8 u8Ch);




#ifdef __cplusplus
}
#endif

#endif /* _BOARD_CONFIG_H */

/* End of file */


