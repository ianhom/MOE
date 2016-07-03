/******************************************************************************
* File       : Board_Config.c
* Function   : Hardware configurations
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 3rd Jul 2016
* History    :  No.  When           Who           What
*               1    3/Jul/2016     Ian           Create
******************************************************************************/

#include "common.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "Board_Config.h"
#include "debug.h"
#include "KL25_Lpt_Time.h"
#include "Btn_SM_Config.h"
#include "Btn_SM_Module.h"

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
void Gpio_Init()
{
    PORTA_PCR12 = PORT_PCR_MUX(0x1);  /* Configure as GPIO  */
    PORTA_PCR5  = PORT_PCR_MUX(0x1);  /* Configure as GPIO  */
    PORTA_PCR4  = PORT_PCR_MUX(0x1);  /* Configure as GPIO  */
    GPIOA_PDDR  &= ~(1 << 12);        /* Configure as input */
    GPIOA_PDDR  &= ~(1 << 5);         /* Configure as input */
    GPIOA_PDDR  &= ~(1 << 4);         /* Configure as input */

    return;
}


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
uint8 Btn_St_Get(uint8 u8Ch)
{
    uint8 u8Temp;
    if(u8Ch == 1)  /* If it is the No.1 channel button */
    {   /* Get the voltage level of button pin */
        u8Temp = (!(GPIOA_PDIR & (1 << 5)));
    }
    if(u8Ch == 2)  /* If it is the No.2 channel button */
    {   /* Get the voltage level of button pin */
        u8Temp = (!(GPIOA_PDIR & (1 << 4)));
    }
    if(u8Ch == 3)  /* If it is the No.3 channel button */
    {   /* Get the voltage level of button pin */
        u8Temp = (!(GPIOA_PDIR & (1 << 12)));
    }

    return  u8Temp;
}


/* End of file */



