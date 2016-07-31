/******************************************************************************
* File       : SystemClockConfig.c
* Function   : Uart driver for stm32f10x
* description: Configure system clock.
* Version    : V1.00
* Author     : Ian
* Date       : 25th Jul 2016
* History    :  No.  When           Who           What
*               1    25/Jul/2016    Ian           Create
******************************************************************************/


#include "type_def.h"
#include "Sw_common.h"
#include "Pub.h"
#include "Boardctrl.h"
#include "Comm_interface.h"
#include "Hardware.h"
#include "Api.h"


/* Declaration of static function */
static WORD32 Prescaler_Cal(BYTE ucExtCrystal, BYTE ucSetClk, BYTE *pucHse, BYTE *pucPllMul, BYTE *pucAhb)

/* Div value of AHB clock */
static const WORD16 sg_awAhpPre[] = {1, 2, 4, 8, 16, 64, 128, 256, 512}; 

/**************************************************************************
* Function: WORD32 SysClk_Config(BYTE ucExtCrystal, BYTE ucSetClk)
* Descrip.: Configure system clock
* Input   : BYTE ucExtCrystal   External clock in MHz
*           BYTE ucSetClk       Desired clock in MHz
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    ：None
* Date             Version     Author	     Content
* -----------------------------------------------
* 2016/07/26	   V1.0	        Ian          Create 
**************************************************************************/
WORD32 Rcc_SysClk_Config(BYTE ucExtCrystal, BYTE ucSetClk)
{
    BYTE ucHse, ucPllMul, ucAhb;
    BYTE ucTemp   = 0;
    WORD32 dwCFGR = 0;

    /* Check if set clock is valid or NOT */
    if(ucSetClk > MAX_AHB_CLK_IN_MHZ)
    {
        return SW_ERR;
    }

    /* Check if any prescaler is available or NOT */
    if(SW_ERR == Prescaler_Cal(ucExtCrystal, ucSetClk, &ucHse, &ucPllMul, &ucAhb))
    {
        return SW_ERR;
    }

    /* Enable external clock */
 	RCC_CR |= RCC_CR_HSEON;           /* Enable external high-speed clock */
	while(!(RCC_CR & RCC_CR_HSERDY)); /* Wait for external clock statble  */
	
    /* Set HSE prescaler */
	if(2 == ucHse)
	{
        dwCFGR |= RCC_CFGR_PLLXTPRE;
	}

	/* Set PLLMUL */
	dwCFGR |= ((ucPllMul - 2) << RCC_CFGR_PLLMULL_POS);

    /* Set AHB clock */
    if(ucAhb)
    {
        dwCFGR |= ((ucAhb + 7) << RCC_CFGR_HPRE_POS)
    }
    
	RCC_CFGR = dwCFGR; /* Set entire prescaler */

    /* Enable PLL */
	RCC_CR | = RCC_CR_PLLON;           /* Enable PLL          */
   	while(!(RCC_CR & RCC_CR_PLLRDY));  /* Wait for PLL stable */

    /* Switch system clock */
	RCC_CFGR |= RCC_CFGR_SW_PLL;
	/* Wait for switching is done */
	while(((RCC_CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL));
	
    return SW_OK;  
}


/**************************************************************************
* Function: static WORD32 Prescaler_Cal(BYTE ucExtCrystal, BYTE ucSetClk, BYTE *pucHse, BYTE *pucPllMul, BYTE *pucAhb)
* Descrip.: Calculate system clock and return prescaler solution.
* Input   : BYTE  ucExtCrystal   External clock in MHz
*           BYTE  ucSetClk       Desired clock in MHz
*           BYTE *pucHse
*           BYTE *pucPllMul


*           BYTE *pucAhb
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    ：None
* Date             Version     Author	     Content
* -----------------------------------------------
* 2016/07/26	   V1.0	        Ian          Create 
**************************************************************************/
static WORD32 Prescaler_Cal(BYTE ucExtCrystal, BYTE ucSetClk, BYTE *pucHse, BYTE *pucPllMul, BYTE *pucAhb)
{
    BYTE ucHse, ucPllMul, ucAhb;

    /* Try every PLLMUL value */
    for(ucPllMul = 2; ucPllMul <= 16; ucPllMul++)
    {   /* Try every AHB prescaler value */
        for(ucAhb = 0; ucAhb < 9; ucAhb++)
        {   /* Tyr every HSE prescaler value */
            for(ucHse = 1; ucHse <= 2; ucHse++)
            {   /* if the combination is satisfied */
                if((ucSetClk * ucHse * sg_awAhpPre[ucAhb]) == (ucExtCrystal * ucPllMul))
                {   /* And MAX AHB clock is NOT exceeded */
                    if(ucExtCrystal / ucHse * ucPllMul <= MAX_AHB_CLK_IN_MHZ)
                    {   /* Return the solution */
                        *pucHse    = ucHse;
                        *pucPllMul = ucPllMul;
                        *pucAhb    = ucAhb;
                        return SW_OK;
                    }
                }
            }
        }
    }
    /* Do Not find the solution */
    return SW_ERR;
}


// End of Uart0.c




