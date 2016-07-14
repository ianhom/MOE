/******************************************************************************
* File       : Task_PT_IEC870_PL.c
* Function   : A demo task for PT application
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
* History    :  No.  When           Who           What
*               1    13/Jul/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "MOE_PT.h"
#include "Task_PT_IEC870_PL.h"
#include "debug.h"
#include "MOE_DRV_CC1101.h"


static uint8 sg_u8TaskID = TASK_NO_TASK;

static void (*const TASK_PT_DEMO_LED_Off)(uint8 u8Clr)    = TASK_PT_DEMO_LED_OFF;
static void (*const TASK_PT_DEMO_LED_On)(uint8 u8Clr)     = TASK_PT_DEMO_LED_ON;
//static void (*const TASK_PT_DEMO_LED_Toggle)(uint8 u8Clr) = TASK_PT_DEMO_LED_TOGGLE;

static void Manchester_Decode(uint8 *pu8Src, uint8 *pu8Des);


static uint8 sg_au8Test[100] = {0x96,\
                                0xA9, 0x6A, 0x9A, 0x9A, 0x55, 0x55, 0xAA, 0xA6, 0xAA, 0xA9,\
                                0xAA, 0xA6, 0xAA, 0xA5, 0xAA, 0x9A, 0xAA, 0x99, 0xAA, 0x96,\
                                0xA5, 0x65, 0x6A, 0x99, 0xA9, 0xA9, 0xA6, 0xA6, 0xA5, 0xA5,\
                                0x9A, 0x9A, 0x99, 0x99, 0xA6, 0x95, 0x95, 0x95, 0x6A, 0x6A,\
                                0x69, 0x69, 0x66, 0x66, 0x65, 0x65, 0x5A, 0x5A, 0x59, 0x59,\
                                0x56, 0x56, 0x55, 0x55, 0xA6, 0x69, 0x99, 0x6A, 0x55, 0x55,\
                                0x55, 0x55, 0x55, 0xF9};


static uint8 sg_au8RxFIFO[65] = {0x96};
static uint8 sg_au8RxData[32];

static uint8 sg_au8PaTabal[8]   = {0xc0 ,0xc0 ,0xc0 ,0xc0 ,0xc0 ,0xc0 ,0xc0 ,0xc0};

static uint8 sg_au8RxConfig[47] = {0x06, 0x2E, 0x02, 0x07, 0x54, 0x76, 0xFF, 0x80, 0x00, 0x00,\
                                   0x00, 0x08, 0x00, 0x21, 0x65, 0x6A, 0x6A, 0x4A, 0x05, 0x72,\
                                   0xF8, 0x47, 0x07, 0x30, 0x18, 0x2E, 0x6D, 0x04, 0x09, 0xB2,\
                                   0x87, 0x6B, 0xFB, 0xB6, 0x10, 0xEA, 0x2A, 0x00, 0x1F, 0x41,\
                                   0x00, 0x59, 0x7F, 0x3F, 0x81, 0x35, 0x09};

static uint8 sg_au8TxConfig[47] = {0x06, 0x2E, 0x02, 0x07, 0x54, 0x76, 0xFF, 0x80, 0x00, 0x00,\
                                   0x00, 0x08, 0x00, 0x21, 0x65, 0x6A, 0x6A, 0x4A, 0x05, 0x72,\
                                   0xF8, 0x47, 0x07, 0x30, 0x18, 0x2E, 0x6D, 0x04, 0x09, 0xB2,\
                                   0x87, 0x6B, 0xFB, 0xB6, 0x10, 0xEA, 0x2A, 0x00, 0x1F, 0x41,\
                                   0x00, 0x59, 0x7F, 0x3F, 0x81, 0x35, 0x09};


/******************************************************************************
* Name       : uint8 Task_PT_IEC870_PL_Process(uint8 u8Evt)
* Function   : IEC870 physical layer test
* Input      : uint8 u8Evt  1~254     Event for the task
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 Task_PT_IEC870_PL_Process(uint8 u8Evt)
{   
    PT_INIT();
    
    PT_BEGIN();

    /******************************************************************/
    MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
    /******************************************************************/

    CC1101_Init();
    PT_DELAY(1000);

    CC1101_Global_Config(sg_au8RxConfig);
    CC1101_PA_Config(sg_au8PaTabal);

    while(1)
    {
        TASK_PT_DEMO_LED_On(LED_RED);
        PL_RECEIVE(sg_au8RxFIFO);
        TASK_PT_DEMO_LED_Off(LED_RED);

        Manchester_Decode(&(sg_au8RxFIFO[1]), sg_au8RxData);

        for(uint8 u8Temp = 0; u8Temp < 64; u8Temp++)
        {
            printf("Addr is 0x%2x, Data is 0x%2x\n", u8Temp,sg_au8RxFIFO[u8Temp]);
        }
        printf("\n\n");
        for(uint8 u8Temp = 0; u8Temp < 32; u8Temp++)
        {
            printf("*********Addr is 0x%2x, Data is 0x%2x\n", u8Temp,sg_au8RxData[u8Temp]);
        }
        

        PT_DELAY(400);
           
        TASK_PT_DEMO_LED_On(LED_BLUE);
#if (1)        
        PL_SEND(sg_au8RxFIFO);
#else
        PL_SEND(sg_au8Test);
#endif 
        TASK_PT_DEMO_LED_Off(LED_BLUE);
        
        PT_DELAY(500);
    }

    PT_END();

    return SW_OK;

}


/******************************************************************************
* Name       : static void Manchester_Decode(uint8 *pu8Src, uint8 *pu8Des)
* Function   : Do manchester decoding
* Input      : uint8 *pu8Src      Pointer of raw data
*              uint8 *pu8Des      Pointer of decoded data
* Output:    : None
* Return     : None
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
static void Manchester_Decode(uint8 *pu8Src, uint8 *pu8Des)
{
    uint8 u8Index,u8Temp;
    for(u8Index = 0; u8Index < CC1101_MAX_ADDR; u8Index++)
    {
        switch(pu8Src[u8Index])
        {
            case 0xAA:  u8Temp = 0x00; break;
            case 0xA9:  u8Temp = 0x01; break;
            case 0xA6:  u8Temp = 0x02; break;
            case 0xA5:  u8Temp = 0x03; break;
            case 0x9A:  u8Temp = 0x04; break;
            case 0x99:  u8Temp = 0x05; break;
            case 0x96:  u8Temp = 0x06; break;
            case 0x95:  u8Temp = 0x07; break;
            case 0x6A:  u8Temp = 0x08; break;
            case 0x69:  u8Temp = 0x09; break;
            case 0x66:  u8Temp = 0x0a; break;
            case 0x65:  u8Temp = 0x0b; break;
            case 0x5A:  u8Temp = 0x0c; break;
            case 0x59:  u8Temp = 0x0d; break;
            case 0x56:  u8Temp = 0x0e; break;
            case 0x55:  u8Temp = 0x0f; break;
            default  :  u8Temp = 0x00; break;       
        }

        if(u8Index % 2)
        {
            pu8Des[u8Index/2] += u8Temp;  
        }
        else
        {        
            pu8Des[u8Index/2] = (u8Temp << 4); 
        }
    }
    return;    
}



/* End of file */
