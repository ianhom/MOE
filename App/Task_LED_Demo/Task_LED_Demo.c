/******************************************************************************
* File       : Task_LED_Demo.c
* Function   : It is a LED demo task.
* Description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/

#include "../../Pub/type_def.h"
#include "../../Pub/common_head.h"
#include "project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "../../Core/MOE_Timer.h"
#include "../../Core/MOE_Msg.h"
#include "Task_LED_Demo.h"
#include "../../Pub/debug.h"
#include "Board_Config.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

static void (*const TASK1_LED_Off)(uint8 u8Clr) = TASK1_LED_OFF;
static void (*const TASK1_LED_On)(uint8 u8Clr)  = TASK1_LED_ON;

/******************************************************************************
* Name       : uint8 lED_Demo_Process(uint8 u8Evt)
* Function   : LEd demo process
* Input      : uint8 u8Evt  1~254     Event for the task
*              void  *pPara           Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* Description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 LED_Demo_Process(uint8 u8Evt, void *pPara)
{   
    /* Check which event should be processed */
    switch (u8Evt)
    {
        /* If it is a timer event */
        case EVENT_PERIODIC:       
        {
            DBG_PRINT("I am the task for LED demo and I am working!!\n");
               
            static uint8 s_u8Clr = BOARD_CONFIG_LED_BLUE;
            TASK1_LED_Off(s_u8Clr);
            s_u8Clr = (s_u8Clr + 1) % (BOARD_CONFIG_LED_BLUE+1);
            TASK1_LED_On(s_u8Clr);
            switch(s_u8Clr)
            {
                case BOARD_CONFIG_LED_BLUE:
                {
                    DBG_PRINT("Blue!!\n");
                    break;
                }
                case BOARD_CONFIG_LED_RED:
                {
                    DBG_PRINT("Red!!\n");
                    break;
                }
                case BOARD_CONFIG_LED_YELLOW:
                {
                    DBG_PRINT("Yellow!!\n");
                    break;
                }
                case BOARD_CONFIG_LED_GREEN:
                {
                    DBG_PRINT("Green!!\n");
                    break;
                }
                default:
                {
                    break;
                }
            }
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a message event */
        case EVENT_MSG:       
        {
            
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a test event */
        case EVENT_TEST:       
        {
            
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a timer event */
        case EVENT_TIMER:       
        {
            
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a message event */
        case EVENT_INIT:       
        {
            /******************************************************************/
            MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
            /******************************************************************/

            /*--------------------   Add your init code here   ----------------------*/
            Moe_Timer_Periodic(300);
            /*-------------------   The end of your init code   ---------------------*/
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is other event */
        default:       
        {
            return u8Evt;     /* Return event to indicate event is NOT processed */
        }
    }
}

/* End of file */



