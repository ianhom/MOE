/*
 * File:        Moeike.c
 * Purpose:        Main process
 *
 */
#include "common.h"
#include "common_head.h"
#include "project_config.h"
#include "Moe_main.h"
#include "debug.h"
#include "MOE_Core.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "MOE_Queue.h"
#include "KL25_Lpt_Time.h"
#include "Btn_SM_Config.h"
#include "Btn_SM_Module.h"

/********************************************************************/

uint8 Btn_St_Get(uint8 u8Ch)
{
    uint8 u8Temp;
    if(u8Ch == 1)
    {
        u8Temp = (!(GPIOA_PDIR & (1 << 5)));
    }
    if(u8Ch == 2)
    {
        u8Temp = (!(GPIOA_PDIR & (1 << 4)));
    }
    if(u8Ch == 3)
    {
        u8Temp = (!(GPIOA_PDIR & (1 << 12)));
    }
    return  u8Temp;
}

uint16 System_Time(void)
{
    uint16 u16Temp = (uint16)App_GetSystemTime_ms();
    return u16Temp;
}

void Gpio_Init()
{
    PORTA_PCR12 = PORT_PCR_MUX(0x1);
    PORTA_PCR5  = PORT_PCR_MUX(0x1);
    PORTA_PCR4  = PORT_PCR_MUX(0x1);
    GPIOA_PDDR  &= ~(1 << 12);
    GPIOA_PDDR  &= ~(1 << 5);
    GPIOA_PDDR  &= ~(1 << 4);
}

void Poll_Process()
{
    return;
}

int main (void)
{   

    Gpio_Init();
    Timer_Init();

    DBG_PRINT("\n***** MOE scheduler V0.01 *****\n");

    Moe_Init(App_GetSystemTime_ms, Poll_Process);   
    
    Moe_Run();
 
}
/********************************************************************/

