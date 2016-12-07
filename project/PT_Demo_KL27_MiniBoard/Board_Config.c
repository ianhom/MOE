/******************************************************************************
* File       : Board_Config.c
* Function   : Hardware configurations
* description: Used in PT_Demo_KL27_MiniBoard project.           
* Version    : V1.00
* Author     : Ian
* Date       : 4th Nov 2016
* History    :  No.  When           Who           What
*               1   04/Nov/2016    Ian           Create
******************************************************************************/

#include "common.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "Board_Config.h"
#include "debug.h"
#include "Btn_SM_Config.h"
#include "Btn_SM_Module.h"

/******************************************************************************
* Name       : void Gpio_Init(void)
* Function   : Init GPIOs
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Nov 2016
******************************************************************************/
void Gpio_Init(void)
{
    /* Button configure */
    PORTA_PCR12 = PORT_PCR_MUX(0x1);   /* Configure as GPIO           */
    PORTA_PCR5  = PORT_PCR_MUX(0x1);   /* Configure as GPIO           */
    PORTA_PCR4  = PORT_PCR_MUX(0x1);   /* Configure as GPIO           */
    GPIOA_PDDR  &= ~(1 << 12);         /* Configure as input button 2 */
    GPIOA_PDDR  &= ~(1 << 5);          /* Configure as input button 1 */
    GPIOA_PDDR  &= ~(1 << 4);          /* Configure as input button 0 */

    /* Led configure */
    PORTC_PCR8  = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */
    PORTC_PCR9  = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */
    PORTA_PCR13 = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */
    PORTD_PCR5  = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */

    GPIOC_PSOR  |= (1<<8);             /* Turn off first                 */
    GPIOC_PSOR  |= (1<<9);             /* Turn off first                 */
    GPIOA_PSOR  |= (1<<13);            /* Turn off first                 */
    GPIOD_PSOR  |= (1<<5);             /* Turn off first                 */

    GPIOC_PDDR  |= (1<<8);             /* Configure as output LED BLUE   */
    GPIOC_PDDR  |= (1<<9);             /* Configure as output LED RED    */
    GPIOA_PDDR  |= (1<<13);            /* Configure as output LED YELLOW */
    GPIOD_PDDR  |= (1<<5);             /* Configure as output LED GREEN  */

    return;
}

/******************************************************************************
* Name       : void LED_Toggle(uint8 u8Ch)
* Function   : LED toggle control
* Input      : uint8 u8Ch    0~255    Channel number of led
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Nov 2016
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
        case BOARD_CONFIG_LED_RED:   /* If it is red led    */
        {
            GPIOC_PTOR |= (1<<9);
            break;

        }
        case BOARD_CONFIG_LED_YELLOW:/* If it is yellow led */
        {
            GPIOA_PTOR |= (1<<13);
            break;
        }
        case BOARD_CONFIG_LED_GREEN: /* If it is green led  */
        {
            GPIOD_PTOR |= (1<<5);
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
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Nov 2016
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
        case BOARD_CONFIG_LED_RED:   /* If it is red led    */
        {
            GPIOC_PSOR |= (1<<9);
            break;

        }
        case BOARD_CONFIG_LED_YELLOW:/* If it is yellow led */
        {
            GPIOA_PSOR |= (1<<13);
            break;
        }
        case BOARD_CONFIG_LED_GREEN: /* If it is green led  */
        {
            GPIOD_PSOR |= (1<<5);
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
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Nov 2016
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
        case BOARD_CONFIG_LED_RED:   /* If it is red led    */
        {
            GPIOC_PCOR |= (1<<9);
            break;

        }
        case BOARD_CONFIG_LED_YELLOW:/* If it is yellow led */
        {
            GPIOA_PCOR |= (1<<13);
            break;
        }
        case BOARD_CONFIG_LED_GREEN: /* If it is green led  */
        {
            GPIOD_PCOR |= (1<<5);
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
* Name       : uint8 Btn_St_Get(uint8 u8Ch)
* Function   : Get the current state of buttons.
* Input      : uint8 u8Ch     1~255    The channel number of button
* Output:    : None
* Return     : BOARD_CONFIG_BTN_ST_HIGH  Pin with high voltage level
*              BOARD_CONFIG_BTN_ST_LOW   Pin with low voltage level
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Nov 2016
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
