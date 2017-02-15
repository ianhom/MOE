/******************************************************************************
* File       : MOE_SysTick.c
* Function   : set SysTick for 1 ms
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 15th Feb 2017
* History    :  No.  When           Who           What
*               1    15/Feb/2017    Ian           Create
******************************************************************************/
#include "type_def.h"
#include "../../Pub/common_head.h"
#include "./project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "../../Core/MOE_Timer.h"
#include "../../Core/MOE_Msg.h"
#include "./Board_Config.h"
#include "../../Pub/debug.h"
//#include "core_cm0plus.h"

volatile static uint32 sg_u32SysClk = 0;

void SysTick_Ms_Int_Init(uint32_t u32Tick)
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;  /* Set clock source = core clock */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;    /* Enable systick interrupt      */
    SysTick->LOAD  = u32Tick;                     /* Set tick count for 1ms        */
    SysTick->VAL   = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Enable SysTick                */
    return;   
}

uint32 SysTick_GetSysClk(void)
{
    return sg_u32SysClk;
}

void SysTick_Handler(void)
{
    volatile uint32 u32Temp;
    u32Temp = SysTick->CTRL;
    sg_u32SysClk++;
    return;
}

/* End of file */
