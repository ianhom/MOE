/******************************************************************************
* File       : Task_PT_11xx_Test.c
* Function   : PT task for 11xx test
* Description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 22nd May 2016
* History    :  No.  When           Who           What
*               1    22/Jul/2016    Ian           Create
******************************************************************************/

#include "../../Pub/type_def.h"
#include "../../Pub/common_head.h"
#include "project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "../../Core/MOE_Timer.h"
#include "../../Core/MOE_Msg.h"
#include "../../Core/MOE_PT.h"
#include "Task_PT_11xx_Test.h"
#include "../../Pub/debug.h"
#include "MOE_HAL_UART.h"
#include "../../Driver/Dev/11xx/MOE_DRV_11xx.h"
#include "Board_Config.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;
static uint8 sg_u8LFNIdx = 0;
static uint8 sg_au8LFN[] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C, 0x8E};
static uint8 sg_au8SndTele[]   = {0x09, 0x00, 0x11, 0x22, 0x33, 0x44, 0x01, 0x00, 0x00, 0x00};
static uint8 sg_au8RcvTele[50] = {0x00};

static uint8 sg_au8SnAddr[6]   = {0x66, 0x55, 0x44, 0x33, 0x22, 0x11};
static uint8 sg_au8ComAddr[8]  = {0x00};
static uint8 sg_au8ShtAddr[2]  = {0x00};
static uint8 sg_au8RegVal[256] = {0x01};

static void (*const TASK_PT_DEMO_LED_Off)(uint8 u8Clr)    = TASK_PT_DEMO_LED_OFF;
static void (*const TASK_PT_DEMO_LED_On)(uint8 u8Clr)     = TASK_PT_DEMO_LED_ON;
//static void (*const TASK_PT_DEMO_LED_Toggle)(uint8 u8Clr) = TASK_PT_DEMO_LED_TOGGLE;

/******************************************************************************
* Name       : uint8 Task_PT_11xx_Test(uint8 u8Evt, void *pPara)
* Function   : A test task for 11xx
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* Description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 22nd Jul 2016
******************************************************************************/
uint8 Task_PT_11xx_Test(uint8 u8Evt, void *pPara)
{   
    uint16 u16Idx;
    uint8  u8Temp = 0x07;
    
    PT_INIT();
    
    PT_BEGIN();

    /******************************************************************/
    MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
    /******************************************************************/

    Drv_11xx_Init();
//    Moe_HAL_Uart_Byte_Receive();
    //Drv_11xx_Write_Reg(DRV_11XX_REG_TM_OUT, 1, &u8Temp);
//    Drv_11xx_Write_Reg(0x60, 1, &u8Temp);
     
    Drv_11xx_Cmd_Reg_Read(sg_au8RegVal);
    for (u16Idx = 0; u16Idx < DRV_11XX_MAX_REG_NUM; u16Idx++)
    {
        DBG_PRINT("0x%2x ", sg_au8RegVal[u16Idx]);
    }

    Moe_HAL_Uart_Rx_Int_Enable();
    while(1)
    {
#if (1)
        //TASK_PT_DEMO_LED_On(BOARD_CONFIG_LED_BLUE);
        //Drv_11xx_Receive_Telegram(sg_au8RcvTele);
        //TASK_PT_DEMO_LED_Off(BOARD_CONFIG_LED_BLUE);
        //PT_DELAY(500);
        TASK_PT_DEMO_LED_On(BOARD_CONFIG_LED_GREEN);
        Drv_11xx_Send_Telegram(sg_au8SndTele);
        //Drv_11xx_Send_Telegram(sg_au8RcvTele);
        PT_DELAY(50);
        sg_au8SndTele[9]++;
        sg_au8SndTele[6] = sg_au8LFN[sg_u8LFNIdx];
        sg_u8LFNIdx = ((sg_u8LFNIdx + 1)%8);
        TASK_PT_DEMO_LED_Off(BOARD_CONFIG_LED_GREEN);
#else
        TASK_PT_DEMO_LED_On(BOARD_CONFIG_LED_BLUE);
        if(MOE_HAL_UART_RCV_TEL == Moe_HAL_Uart_Got_Telegram())
        {
            Moe_HAL_Uart_Tele_Receive(sg_au8RcvTele);
            TASK_PT_DEMO_LED_Off(BOARD_CONFIG_LED_BLUE);
//            PT_DELAY(500);
//            TASK_PT_DEMO_LED_On(BOARD_CONFIG_LED_GREEN);
//            Drv_11xx_Send_Telegram(sg_au8RcvTele);
//            PT_DELAY(100);
//            TASK_PT_DEMO_LED_Off(BOARD_CONFIG_LED_GREEN);
        }
        PT_BREAK();
#endif
    }

    PT_END();

    return SW_OK;

}

/* End of file */


