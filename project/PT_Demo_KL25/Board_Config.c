/******************************************************************************
* File       : Board_Config.c
* Function   : Hardware configurations
* Description: Used in PT_Demo_KL25 project.           
* Version    : V1.00
* Author     : Ian
* Date       : 4th Nov 2016
* History    :  No.  When           Who           What
*               1    04/Nov/2016    Ian           Create
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
#include "KL25_Lpt_Time.h"
#include "Btn_SM_Config.h"
#include "Btn_SM_Module.h"

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
* Date       : 3rd Jul 2016
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
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Jul 2016
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
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Jul 2016
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
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Jul 2016
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
*              SW_ERR                    Wrong channel number
* Description: To be done.
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
    else if(u8Ch == 2)  /* If it is the No.2 channel button */
    {   /* Get the voltage level of button pin */
        u8Temp = (!(GPIOA_PDIR & (1 << 4)));
    }
    else if(u8Ch == 3)  /* If it is the No.3 channel button */
    {   /* Get the voltage level of button pin */
        u8Temp = (!(GPIOA_PDIR & (1 << 12)));
    }
    else
    {
        return SW_ERR;
    }

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
* Date       : 3rd Jul 2016
******************************************************************************/
void Gpio_Init(void)
{
    /* Led configure */
    PORTB_PCR18 = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */
    PORTB_PCR19 = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */
    PORTD_PCR1  = PORT_PCR_MUX(0x1);   /* Configure as GPIO              */

    GPIOB_PSOR  |= (1<<18);            /* Turn off first                 */
    GPIOB_PSOR  |= (1<<19);            /* Turn off first                 */
    GPIOD_PSOR  |= (1<<1);             /* Turn off first                 */

    GPIOB_PDDR  |= (1<<18);            /* Configure as output LED RED    */
    GPIOB_PDDR  |= (1<<19);            /* Configure as output LED GREEN  */
    GPIOD_PDDR  |= (1<<1);             /* Configure as output LED BLUE   */

#ifdef __MOE_SPI_ENABLE
    /* SPI configure */
    PORTE_PCR1  = PORT_PCR_MUX(0x2);
    PORTE_PCR2  = PORT_PCR_MUX(0x2);
    PORTE_PCR3  = PORT_PCR_MUX(0x2);
    PORTE_PCR4  = PORT_PCR_MUX(0x1);
    GPIOE_PDDR  |= (1 << 4);
    
    PORTE_PCR20 = PORT_PCR_MUX(0x1);
    PORTE_PCR21 = PORT_PCR_MUX(0x1);
#endif

#ifdef __MOE_UART_ENABLE
    /* Enable the UART_TXD function on PTC4 */
    PORTC_PCR4 = PORT_PCR_MUX(0x3); // UART1 is alt3 function for this pin
            
    /* Enable the UART_RXD function on PTC3 */
    PORTC_PCR3 = PORT_PCR_MUX(0x3); // UART1 is alt3 function for this pin
#endif

    PORTA_PCR1 = PORT_PCR_MUX(0X1); /* PTA1 as a GPIO for 11XX reset */
    GPIOA_PSOR = (1 << 1);
    GPIOA_PDDR = (1 << 1);
    return;
}

void Board_Config_Reset_Ctrl(uint8 u8Val)
{
    if(u8Val)
    {
        GPIOA_PSOR = (1 << 1); 
    }
    else
    {
        GPIOA_PCOR = (1 << 1);
    }
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
* Date       : 4th Jul 2016
******************************************************************************/
void LED_Toggle(uint8 u8Ch)
{
    switch(u8Ch)
    { 
        case BOARD_CONFIG_LED_BLUE:  /* If it is blue led   */
        {
            GPIOD_PTOR |= (1<<1);
            break;
        }
        case BOARD_CONFIG_LED_RED:   /* If it is red led    */
        {
            GPIOB_PTOR |= (1<<18);
            break;
        }
        case BOARD_CONFIG_LED_GREEN: /* If it is green led  */
        {
            GPIOB_PTOR |= (1<<19);
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
* Date       : 4th Jul 2016
******************************************************************************/
void LED_Off(uint8 u8Ch)
{
    switch(u8Ch)
    { 
        case BOARD_CONFIG_LED_BLUE:  /* If it is blue led   */
        {
            GPIOD_PSOR |= (1<<1);
            break;
        }
        case BOARD_CONFIG_LED_RED:   /* If it is red led    */
        {
            GPIOB_PSOR |= (1<<18);
            break;
        }
        case BOARD_CONFIG_LED_GREEN: /* If it is green led  */
        {
            GPIOB_PSOR |= (1<<19);
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
* Date       : 4th Jul 2016
******************************************************************************/
void LED_On(uint8 u8Ch)
{
    switch(u8Ch)
    { 
        case BOARD_CONFIG_LED_BLUE:  /* If it is blue led   */
        {
            GPIOD_PCOR |= (1<<1);
            break;
        }
        case BOARD_CONFIG_LED_RED:   /* If it is red led    */
        {
            GPIOB_PCOR |= (1<<18);
            break;
        }
        case BOARD_CONFIG_LED_GREEN: /* If it is green led  */
        {
            GPIOB_PCOR |= (1<<19);
            break;
        }
        default:
        {
            break;
        }
    }
    return;
}

#endif

/* End of file */


