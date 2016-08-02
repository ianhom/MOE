/******************************************************************************
* File       : rcc.c
* Function   : Reset and clock control
* description: Configure system clock.
* Version    : V1.00
* Author     : Ian
* Date       : 30th Jul 2016
* History    :  No.  When           Who           What
*               1    30/Jul/2016    Ian           Create
******************************************************************************/


#include "type_def.h"
#include "Sw_common.h"
#include "Pub.h"
#include "Boardctrl.h"
#include "Comm_interface.h"
#include "Hardware.h"
#include "Api.h"
#include "rcc.h"


/* Declaration of static function */
static WORD32 Rcc_Prescaler_Cal(BYTE ucSetClk);

/* Div value of AHB clock */
static const WORD16 sg_awAhbPre[] = {1, 2, 4, 8, 16, 64, 128, 256, 512}; 

/* Div and Mul values */
static BYTE sg_ucHse, sg_ucPllMul, sg_ucAhbIdx, sg_ucApb1, sg_ucApb2;
/**************************************************************************
* Function: WORD32 Rcc_SysClk_Config(BYTE ucExtCrystal, BYTE ucSetClk)
* Descrip.: Configure system clock
* Input   : BYTE ucSetClk       Desired clock in MHz
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_SysClk_Config(BYTE ucSetClk)
{
    WORD32 dwCFGR = 0;

    /* Check if set clock is valid or NOT */
    if(ucSetClk > MAX_AHB_CLK_IN_MHZ)
    {
        return SW_ERR;
    }

    /* Check if any prescaler is available or NOT */
    if(SW_ERR == Rcc_Prescaler_Cal(ucSetClk))
    {
        return SW_ERR;
    }

    /* Enable external clock */
    RCC_CR |= RCC_CR_HSEON;           /* Enable external high-speed clock */
    while(!(RCC_CR & RCC_CR_HSERDY)); /* Wait for external clock statble  */
    
    /* Set HSE prescaler */
    if(2 == sg_ucHse)
    {
        dwCFGR |= RCC_CFGR_PLLXTPRE;
    }

    /* Set PLLMUL */
    dwCFGR |= ((sg_ucPllMul - 2) << RCC_CFGR_PLLMULL_POS);

    /* Set AHB clock */
    if(sg_ucAhbIdx)
    {
        dwCFGR |= ((sg_ucAhbIdx + 7) << RCC_CFGR_HPRE_POS);
    }
    
    RCC_CFGR = dwCFGR; /* Set entire prescaler */

    /* Enable PLL */
    RCC_CR |= RCC_CR_PLLON;            /* Enable PLL          */
    while(!(RCC_CR & RCC_CR_PLLRDY));  /* Wait for PLL stable */

    /* Switch system clock */
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    /* Wait for switching is done */
    while(((RCC_CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL));
    
    return SW_OK;  
}


/**************************************************************************
* Function: static WORD32 Rcc_Prescaler_Cal(BYTE ucSetClk)
* Descrip.: Calculate system clock and return prescaler solution.
* Input   : BYTE  ucSetClk       Desired clock in MHz
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
static WORD32 Rcc_Prescaler_Cal(BYTE ucSetClk)
{
    /* Try every PLLMUL value */
    for(sg_ucPllMul = 2; sg_ucPllMul <= 16; sg_ucPllMul++)
    {   /* Try every AHB prescaler value */
        for(sg_ucAhbIdx = 0; sg_ucAhbIdx < 9; sg_ucAhbIdx++)
        {   /* Tyr every HSE prescaler value */
            for(sg_ucHse = 1; sg_ucHse <= 2; sg_ucHse++)
            {   /* if the combination is satisfied */
                if((ucSetClk * sg_ucHse * sg_awAhbPre[sg_ucAhbIdx]) == ((EXT_CRYSTAL_FREQ /1000000) * sg_ucPllMul))
                {   /* And MAX AHB clock is NOT exceeded */
                    if((EXT_CRYSTAL_FREQ / 1000000) / sg_ucHse * sg_ucPllMul <= MAX_AHB_CLK_IN_MHZ)
                    {   
                        /* Return the solution */
                        return SW_OK;
                    }
                }
            }
        }
    }
    /* Do Not find the solution */
    return SW_ERR;
}

/**************************************************************************
* Function: WORD32 Rcc_Get_SYSCLK(void)
* Descrip.: Get SYSCLK in Hz
* Input   : None
* Output  : None
* Return  : WORD32 SYSCLK in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_SYSCLK(void)
{
    return (EXT_CRYSTAL_FREQ / sg_ucHse * sg_ucPllMul);
}

/**************************************************************************
* Function: WORD32 Rcc_Get_HCLK(void)
* Descrip.: Get HCLK in Hz
* Input   : None
* Output  : None
* Return  : WORD32 HCLK in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_HCLK(void)
{
    return (EXT_CRYSTAL_FREQ / sg_ucHse * sg_ucPllMul / sg_awAhbPre[sg_ucAhbIdx]);
}

/**************************************************************************
* Function: WORD32 Rcc_Get_PCLK1(void)
* Descrip.: Get PCLK1 in Hz
* Input   : None
* Output  : None
* Return  : WORD32 PCLK1 in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_PCLK1(void)
{
    /* Get APB1 div value */
    sg_ucApb1 = ((RCC_CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_POS);  /* Get Apb1 setting */
    /* If Apb1 does not div clcok */
    if(sg_ucApb1 < (RCC_CFGR_PPRE1_DIV2 >> RCC_CFGR_PPRE1_POS))
    {
        sg_ucApb1 = 1;
    }
    else/* Else, according the register map to get div value */
    {
        sg_ucApb1 = 1 << (sg_ucApb1 - 3);
    }

    return (EXT_CRYSTAL_FREQ / sg_ucHse * sg_ucPllMul / sg_awAhbPre[sg_ucAhbIdx] / sg_ucApb1);
}

/**************************************************************************
* Function: WORD32 Rcc_Get_PCLK2(void)
* Descrip.: Get PCLK2 in Hz
* Input   : None
* Output  : None
* Return  : WORD32 PCLK2 in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
WORD32 Rcc_Get_PCLK2(void)
{
    /* Get APB2 div value */
    sg_ucApb2 = ((RCC_CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_POS);  /* Get Apb2 setting */
    /* If Apb2 does not div clcok */
    if(sg_ucApb2 < (RCC_CFGR_PPRE2_DIV2 >> RCC_CFGR_PPRE2_POS))
    {
        sg_ucApb2 = 1;
    }
    else/* Else, according the register map to get div value */
    {
        sg_ucApb2 = 1 << (sg_ucApb2 - 3);
    }

    return (EXT_CRYSTAL_FREQ / sg_ucHse * sg_ucPllMul / sg_awAhbPre[sg_ucAhbIdx] / sg_ucApb2);
}

/* End of file */

