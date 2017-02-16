/******************************************************************************
* File       : MOE_SysTick.c
* Function   : Set SysTick for 1 ms
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

/* System ms counter */
volatile static uint32 sg_u32SysClk = 0;

/******************************************************************************
* Name       : void SysTick_Ms_Int_Init(uint32_t u32Tick)
* Function   : Init SysTick Register
* Input      : uint32_t u32Tick    1~0xFFFFFFFF     The tick count for 1 ms
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
void SysTick_Ms_Int_Init(uint32_t u32Tick)
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;  /* Set clock source = core clock */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;    /* Enable systick interrupt      */
    SysTick->LOAD  = u32Tick;                     /* Set tick count for 1ms        */
    SysTick->VAL   = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Enable SysTick                */
    return;   
}

/******************************************************************************
* Name       : uint32 SysTick_GetSysClk(void)
* Function   : Return the current system ms counter(system clock)
* Input      : uint32_t u32Tick    1~0xFFFFFFFF     The tick count for 1 ms
* Output:    : None.
* Return     : 1~0xFFFFFFFF   The current system ms counter.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
uint32 SysTick_GetSysClk(void)
{
    return sg_u32SysClk;  /* System ms counter */
}

/******************************************************************************
* Name       : void SysTick_Handler(void)
* Function   : SysTick interrupt handler
* Input      : None.
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
void SysTick_Handler(void)
{
    volatile uint32 u32Temp;
    u32Temp = SysTick->CTRL;
    sg_u32SysClk++;            /* Update the system ms counter */
    return;
}

/* End of file */
