/******************************************************************************
* File       : Board_Config.c
* Function   : Hardware configurations
* Description: Used in PT_Demo_KL25 project.           
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
* History    :  No.  When           Who           What
*               1    30/Nov/2017    Ian           Create
******************************************************************************/

#include "common.h"
#include "../../Pub/common_head.h"
#include "./project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "../../Core/MOE_Timer.h"
#include "../../Core/MOE_Msg.h"
#include "./Board_Config.h"
#include "../../Pub/debug.h"


#ifdef __FRDM_MINI_SHIELD_SUPPORTED
/******************************************************************************
* Name       : void Gpio_Init(void)
* Function   : Init GPIOs
* Input      : None
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void Gpio_Init(void)
{
    /* To be done... */
    return;
}

/******************************************************************************
* Name       : void LED_Toggle(uint8 u8Ch)
* Function   : LED toggle control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void LED_Toggle(uint8 u8Ch)
{
    /* To be done... */
    return;
}

/******************************************************************************
* Name       : void LED_Off(uint8 u8Ch)
* Function   : LED Off control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void LED_Off(uint8 u8Ch)
{
    /* To be done... */
    return;
}


/******************************************************************************
* Name       : void LED_On(uint8 u8Ch)
* Function   : LED On control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void LED_On(uint8 u8Ch)
{
    /* To be done... */
    return;
}


/******************************************************************************
* Name       : uint8 Btn_St_Get(uint8 u8Ch)
* Function   : Get the current state of buttons.
* Input      : uint8 u8Ch     1~255    The channel number of button
* Output:    : None
* Return     : BOARD_CONFIG_BTN_ST_HIGH  Pin with high voltage level
*              BOARD_CONFIG_BTN_ST_LOW   Pin with low voltage level
*              SW_ERR                    Wrong channel number
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
uint8 Btn_St_Get(uint8 u8Ch)
{
    uint8 u8Temp;
    /* To be done... */
    
    return  u8Temp;
}
#else
/******************************************************************************
* Name       : void Gpio_Init(void)
* Function   : Init GPIOs
* Input      : None
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void Gpio_Init(void)
{
    /* To be done... */
    return
}

/******************************************************************************
* Name       : void LED_Toggle(uint8 u8Ch)
* Function   : LED toggle control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void LED_Toggle(uint8 u8Ch)
{
    /* To be done... */
    return;
}

/******************************************************************************
* Name       : void LED_Off(uint8 u8Ch)
* Function   : LED Off control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void LED_Off(uint8 u8Ch)
{
    /* To be done... */
    return;
}


/******************************************************************************
* Name       : void LED_On(uint8 u8Ch)
* Function   : LED On control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Nov 2017
******************************************************************************/
void LED_On(uint8 u8Ch)
{
    /* To be done... */
    return;
}

#endif

/* End of file */


