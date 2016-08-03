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
static uint32 Rcc_Prescaler_Cal(uint u8SetClk);

/* Div value of AHB clock */
static const uint16 sg_au16AhbPre[] = {1, 2, 4, 8, 16, 64, 128, 256, 512}; 

/* Div and Mul values */
static uint8 sg_u8Hse, sg_u8PllMul, sg_u8AhbIdx, sg_u8Apb1, sg_u8Apb2;
/**************************************************************************
* Function: uint32 Rcc_SysClk_Config(uint8 u8SetClk)
* Descrip.: Configure system clock
* Input   : uint8 ucSetClk       Desired clock in MHz
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
uint32 Rcc_SysClk_Config(uint8 u8SetClk)
{
    uint32 dwCFGR = 0;

    /* Check if set clock is valid or NOT */
    if(u8SetClk > MAX_AHB_CLK_IN_MHZ)
    {
        return SW_ERR;
    }

    /* Check if any prescaler is available or NOT */
    if(SW_ERR == Rcc_Prescaler_Cal(u8SetClk))
    {
        return SW_ERR;
    }

    /* Enable external clock */
    RCC_CR |= RCC_CR_HSEON;           /* Enable external high-speed clock */
    while(!(RCC_CR & RCC_CR_HSERDY)); /* Wait for external clock statble  */
    
    /* Set HSE prescaler */
    if(2 == sg_u8Hse)
    {
        u32CFGR |= RCC_CFGR_PLLXTPRE;
    }

    /* Set PLLMUL */
    u32CFGR |= ((sg_u8PllMul - 2) << RCC_CFGR_PLLMULL_POS);

    /* Set AHB clock */
    if(sg_u8AhbIdx)
    {
        u32CFGR |= ((sg_u8AhbIdx + 7) << RCC_CFGR_HPRE_POS);
    }
    
    RCC_CFGR = u32CFGR; /* Set entire prescaler */

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
* Function: static uint32 Rcc_Prescaler_Cal(uint8 u8SetClk)
* Descrip.: Calculate system clock and return prescaler solution.
* Input   : uint8  u8SetClk       Desired clock in MHz
* Output  : None
* Return  : SW_OK    Successful
*           SW_ERR   Failed
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/07/26       V1.0         Ian          Create 
**************************************************************************/
static uint32 Rcc_Prescaler_Cal(uint8 u8SetClk)
{
    /* Try every PLLMUL value */
    for(sg_u8PllMul = 2; sg_u8PllMul <= 16; sg_u8PllMul++)
    {   /* Try every AHB prescaler value */
        for(sg_u8AhbIdx = 0; sg_u8AhbIdx < 9; sg_u8AhbIdx++)
        {   /* Tyr every HSE prescaler value */
            for(sg_u8Hse = 1; sg_u8Hse <= 2; sg_u8Hse++)
            {   /* if the combination is satisfied */
                if((u8SetClk * sg_u8Hse * sg_au16AhbPre[sg_u8AhbIdx]) == ((EXT_CRYSTAL_FREQ /1000000) * sg_u8PllMul))
                {   /* And MAX AHB clock is NOT exceeded */
                    if((EXT_CRYSTAL_FREQ / 1000000) / sg_u8Hse * sg_u8PllMul <= MAX_AHB_CLK_IN_MHZ)
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
* Function: uint32 Rcc_Get_SYSCLK(void)
* Descrip.: Get SYSCLK in Hz
* Input   : None
* Output  : None
* Return  : uint32 SYSCLK in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
uint32 Rcc_Get_SYSCLK(void)
{
    return (EXT_CRYSTAL_FREQ / sg_u8Hse * sg_u8PllMul);
}

/**************************************************************************
* Function: uint32 Rcc_Get_HCLK(void)
* Descrip.: Get HCLK in Hz
* Input   : None
* Output  : None
* Return  : uint32 HCLK in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
uint32 Rcc_Get_HCLK(void)
{
    return (EXT_CRYSTAL_FREQ / sg_u8Hse * sg_u8PllMul / sg_au16AhbPre[sg_u8AhbIdx]);
}

/**************************************************************************
* Function: uint32 Rcc_Get_PCLK1(void)
* Descrip.: Get PCLK1 in Hz
* Input   : None
* Output  : None
* Return  : uint32 PCLK1 in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
uint32 Rcc_Get_PCLK1(void)
{
    /* Get APB1 div value */
    sg_u8Apb1 = ((RCC_CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_POS);  /* Get Apb1 setting */
    /* If Apb1 does not div clcok */
    if(sg_u8Apb1 < (RCC_CFGR_PPRE1_DIV2 >> RCC_CFGR_PPRE1_POS))
    {
        sg_u8Apb1 = 1;
    }
    else/* Else, according the register map to get div value */
    {
        sg_u8Apb1 = 1 << (sg_u8Apb1 - 3);
    }

    return (EXT_CRYSTAL_FREQ / sg_u8Hse * sg_u8PllMul / sg_au16AhbPre[sg_u8AhbIdx] / sg_u8Apb1);
}

/**************************************************************************
* Function: uint32 Rcc_Get_PCLK2(void)
* Descrip.: Get PCLK2 in Hz
* Input   : None
* Output  : None
* Return  : uint32 PCLK2 in Hz
* Note    ：None
* Date             Version     Author        Content
* -----------------------------------------------
* 2016/08/01       V1.0         Ian          Create 
**************************************************************************/
uint32 Rcc_Get_PCLK2(void)
{
    /* Get APB2 div value */
    sg_u8Apb2 = ((RCC_CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_POS);  /* Get Apb2 setting */
    /* If Apb2 does not div clcok */
    if(sg_u8Apb2 < (RCC_CFGR_PPRE2_DIV2 >> RCC_CFGR_PPRE2_POS))
    {
        sg_u8Apb2 = 1;
    }
    else/* Else, according the register map to get div value */
    {
        sg_u8Apb2 = 1 << (sg_u8Apb2 - 3);
    }

    return (EXT_CRYSTAL_FREQ / sg_u8Hse * sg_u8PllMul / sg_au16AhbPre[sg_ucAhbIdx] / sg_u8Apb2);
}

/* End of file */

