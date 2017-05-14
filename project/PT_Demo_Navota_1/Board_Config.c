/******************************************************************************
* File       : Board_Config.c
* Function   : Hardware configurations
* Description: Used in PT_Demo_Navota_1 project.           
* Version    : V1.00
* Author     : Ian
* Date       : 7th Dec 2016
* History    :  No.  When           Who           What
*               1    7th/Dec/2016   Ian           Create
******************************************************************************/

#include "common.h"
#include "../../Pub/common_head.h"
#include "./project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "./Board_Config.h"
#include "../../Pub/debug.h"


/******************************************************************************
* Name       : void Gpio_Init(void)
* Function   : Init GPIOs
* Input      : None
* Output:    : None
* Return     : None
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 7th Dec 2016
******************************************************************************/
void Gpio_Init(void)
{
    /* Led configure */
    PORTC_PCR8  = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */
    GPIOC_PSOR  |= (1<<8);             /* Turn off first                 */
    GPIOC_PDDR  |= (1<<8);             /* Configure as output LED BLUE   */

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
* Date       : 7th Dec 2016
******************************************************************************/
void LED_Toggle(uint8 u8Ch)
{
    switch(u8Ch)
    { 
        case BOARD_CONFIG_LED_BLUE:  /* If it is blue led   */
        {
            GPIOC_PTOR |= (1<<8);
            break;
        }
        default:
        {
            break;
        }
    }
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
* Date       : 7th Dec 2016
******************************************************************************/
void LED_Off(uint8 u8Ch)
{
    switch(u8Ch)
    { 
        case BOARD_CONFIG_LED_BLUE:  /* If it is blue led   */
        {
            GPIOC_PSOR |= (1<<8);
            break;
        }
        default:
        {
            break;
        }
    }
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
* Date       : 7th Dec 2016
******************************************************************************/
void LED_On(uint8 u8Ch)
{
    switch(u8Ch)
    { 
        case BOARD_CONFIG_LED_BLUE:  /* If it is blue led   */
        {
            GPIOC_PCOR |= (1<<8);
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}


/* End of file */
