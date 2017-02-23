/******************************************************************************
* File       : MOE_SysTick.c
* Function   : Set SysTick for 1 ms
* Description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 15th Feb 2017
* History    :  No.  When           Who           What
*               1    15/Feb/2017    Ian           Create
******************************************************************************/
#include "type_def.h"
#include "../../Pub/common_head.h"
#include "./project_config.h"
#include "./MOE_sysTick.h"
#include "../../Pub/debug.h"

/* Init system ms counter */
volatile static uint32 sg_u32SysClk = 0;

/******************************************************************************
* Name       : void SysTick_Ms_Int_Init(uint32_t u32Tick)
* Function   : Init SysTick Register
* Input      : uint32_t u32Tick    1~0xFFFFFFFF     The tick count for 1 ms
* Output:    : None.
* Return     : None.
* Description: Configura clock source, Enable interrupt and Enable Systick function.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
void SysTick_Ms_Int_Init(uint32_t u32Tick)
{
    MOE_SysTick->CTRL |= MOE_SysTick_CTRL_CLKSOURCE_MSK;  /* Set clock source = core clock */
    MOE_SysTick->CTRL |= MOE_SysTick_CTRL_TICKINT_MSK;    /* Enable systick interrupt      */
    MOE_SysTick->LOAD  = u32Tick;                         /* Set tick count for 1ms        */
    MOE_SysTick->VAL   = 0;
    MOE_SysTick->CTRL |= MOE_SysTick_CTRL_ENABLE_MSK;     /* Enable SysTick                */
    return;   
}

/******************************************************************************
* Name       : uint32 SysTick_GetSysClk(void)
* Function   : Return the current system ms counter(system clock)
* Input      : uint32_t u32Tick    1~0xFFFFFFFF     The tick count for 1 ms
* Output:    : None.
* Return     : 1~0xFFFFFFFF   The current system ms counter.
* Description: None.
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
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
void SysTick_Handler(void)
{
    volatile uint32 u32Temp;
    u32Temp = MOE_SysTick->CTRL;
    sg_u32SysClk++;               /* Update the system ms counter */
    return;
}

/* End of file */
