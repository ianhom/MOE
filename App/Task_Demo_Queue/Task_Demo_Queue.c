/******************************************************************************
* File       : Task_Demo_Queue.c
* Function   : It is demo task for queue
* description: This task creates two queues,one is located in task space, and 
*              the other is created by Queue API. Task sends two messages with 
*              the two queues and recieves the two messages from the queues.           
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
* History    :  No.  When           Who      What
*               1    19/Jun/2016    Ian      V1.00: Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "MOE_Timer.h"
#include "MOE_Queue.h"
#include "MOE_Msg.h"
#include "Task_Demo_Queue.h"
#include "debug.h"


static uint8 sg_u8TaskID = TASK_NO_TASK;

static uint8 sg_au8Queue[TASK_DEMO_QUEUE_BUF_NUM * TASK_DEMO_QUEUE_BUF_SIZE] = {0};
static uint8 sg_au8DataW[TASK_DEMO_QUEUE_BUF_SIZE] = {1,2,3,4,5,6,7,8,9,10};
static uint8 sg_au8DataR[TASK_DEMO_QUEUE_BUF_SIZE] = {0,0,0,0,0,0,0,0,0,0};

static T_QUEUE_INFO sg_tQueue1,sg_tQueue2;

/******************************************************************************
* Name       : uint8 Task_Demo_Queue_Process(uint8 u8Evt, void *pPara)
* Function   : Task Demo Queue process
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
******************************************************************************/
uint8 Task_Demo_Queue_Process(uint8 u8Evt, void *pPara)

{   
    uint8 u8Idx;
    /* Check which event should be processed */
    switch (u8Evt)
    {
        /* If it is a timer event */
        case EVENT_PERIODIC:       
        {
            DBG_PRINT("I am task %d and I am working!!\n", sg_u8TaskID);
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a message event */
        case EVENT_MSG:       
        {
            uint8  u8MsgType;
            void  *ptMsg;

            ptMsg = (void*)Moe_Msg_Receive(sg_u8TaskID, &u8MsgType);
            while(ptMsg)
            {   
                switch(u8MsgType)
                {
                    case MSG_TYPE_QUEUE:
                    {
                        T_QUEUE_MSG *ptQueueMsg = (T_QUEUE_MSG*)ptMsg;
                        /* Queue 1 reading */
                        if(&sg_tQueue1 == ptQueueMsg->ptQueue)
                        {   /* If used buffer is available */
                            if(SW_OK ==Moe_Queue_Is_Not_Empty(ptQueueMsg->ptQueue))
                            {   /* Read the data from queue */
                                for(u8Idx = 0; u8Idx < sizeof(sg_au8DataR); u8Idx++)
                                {
                                    sg_au8DataR[u8Idx] = MOE_QUEUE_FIRST_USED(ptQueueMsg->ptQueue)[u8Idx];
                                }
                                Moe_Queue_Dec(ptQueueMsg->ptQueue);  /* Update the queue */
                                DBG_PRINT("Queue 1 reading successfully!!\n");
                            }
                            else/* If it a empty queue */
                            {
                                DBG_PRINT("Queue 1 is empty!\n");
                            }  
                        }
            
                        /**********************************************************/
                        /* Queue 2 reading */
                        else if(&sg_tQueue2 == ptQueueMsg->ptQueue)
                        {   /* If reading is successful */
                            if(SW_OK == Moe_Queue_Read(ptQueueMsg->ptQueue, sg_au8DataR, sizeof(sg_au8DataR)))
                            {
                                DBG_PRINT("Queue 2 reading successfully!!\n");
                            }
                            else/* If it a empty queue */
                            {
                                DBG_PRINT("Queue 2 is empty!\n");
                            }
                        }
                        else
                        {
                            DBG_PRINT("Wrong queue information");
                        }
                        break;
                    }
                }
                ptMsg = (void*)Moe_Msg_Receive(sg_u8TaskID, &u8MsgType);
            }
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a test event */
        case EVENT_TEST:       
        {
            DBG_PRINT("This is task %d process function\n", sg_u8TaskID);
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a timer event */
        case EVENT_TIMER:       
        {
            /* Queue 1 writing */
            if(SW_OK == Moe_Queue_Is_Free(&sg_tQueue1))
            {   /* If free buff is available */
                for (u8Idx = 0; u8Idx < sizeof(sg_au8DataW); u8Idx++)
                {   /* Write the data into the buffer */
                    MOE_QUEUE_LAST_FREE(&sg_tQueue1)[u8Idx] = sg_au8DataW[u8Idx];
                }
                Moe_Queue_Inc(&sg_tQueue1);  /* Update the queue */
                DBG_PRINT("Queue 1 writing successfully!!\n");
            }
            else /* If queue is NOT free */
            {
                DBG_PRINT("Queue 1 is NOT free!!\n");
            }
            
            Moe_Msg_Send(sg_u8TaskID,MSG_TYPE_QUEUE,sizeof(T_QUEUE_MSG*),&sg_tQueue1);
            
            /**********************************************************************/
            /* Queue 2 writing */
            if(SW_OK == Moe_Queue_Write(&sg_tQueue2, sg_au8DataW, sizeof(sg_au8DataW)))
            {   /* If free buff is available */
                DBG_PRINT("Queue 2 writing successfully!!\n");
            }
            else /* If queue is NOT free */
            {
                DBG_PRINT("Queue 2 is NOT free!!\n");
            }
            Moe_Msg_Send(sg_u8TaskID,MSG_TYPE_QUEUE,sizeof(T_QUEUE_MSG*),&sg_tQueue1);
            
            sg_au8DataW[0]++;
            return SW_OK;     /* Return SW_OK to indicate event is processed */
        }

        /* If it is a message event */
        case EVENT_INIT:       
        {
            /******************************************************************/
            MOE_MANDATORY_INIT();  /* Mandatory init, shout call it here only */
            /******************************************************************/
            
            /*--------------------   Add your init code here   ----------------------*/
            /* Init queue 1 which is located in task space */
            sg_tQueue1.pu8Addr  = sg_au8Queue;
            sg_tQueue1.u8Len    = TASK_DEMO_QUEUE_BUF_SIZE;
            sg_tQueue1.u8MaxCnt = TASK_DEMO_QUEUE_BUF_NUM;
            sg_tQueue1.u8Begin  = 0;
            sg_tQueue1.u8End    = 0;
            sg_tQueue1.u8Cnt    = 0;
            
            /* Init queue 2 by queue API */
            Moe_Queue_Create(&sg_tQueue2, TASK_DEMO_QUEUE_BUF_SIZE, TASK_DEMO_QUEUE_BUF_NUM);
            
            /* Init timer */
            T_TIMER tTm;
            tTm.u8TaskID     = sg_u8TaskID;
            tTm.u8Evt        = EVENT_TIMER;
            tTm.u16Cnt       = MOE_TMR_INFINITE_CNT;
            tTm.u32TmOut     = 1000;
#ifdef __TIMER_CALLBACK_SUPPORTED
            tTm.pfTmCallback = NULL;
            tTm.pPara        = NULL;
#endif
            
            Moe_Timer_Start(&tTm);
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
