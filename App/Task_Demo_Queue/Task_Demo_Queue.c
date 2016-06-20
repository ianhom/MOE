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
#include "OSAL.h"
#include "OSAL_Timer.h"
#include "OSAL_Queue.h"
#include "Task_Demo_Queue.h"
#include "OSAL_Msg.h"
#include "debug.h"

static uint16 Task_Demo_Queue_Process(uint16 u16Evt);

static uint8 sg_u8TaskID = TASK_NO_TASK;

static uint8 sg_au8Queue[TASK_DEMO_QUEUE_BUF_NUM * TASK_DEMO_QUEUE_BUF_SIZE] = {0};
static uint8 sg_au8DataW[TASK_DEMO_QUEUE_BUF_SIZE] = {1,2,3,4,5,6,7,8,9,10};
static uint8 sg_au8DataR[TASK_DEMO_QUEUE_BUF_SIZE] = {0,0,0,0,0,0,0,0,0,0};

static T_QUEUE_INFO sg_tQueue1,sg_tQueue2;

/******************************************************************************
* Name       : void Task_Demo_Queue_Init(uint8 u8TaskID)
* Function   : Init task_Demo_Queue
* Input      : To be done.
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
******************************************************************************/
void Task_Demo_Queue_Init(uint8 u8TaskID)
{
    sg_u8TaskID = u8TaskID;        /* Get the task ID */
    Osal_Reg_Tasks(Task_Demo_Queue_Process);
    DBG_PRINT("Task Demo Queue is inited successfully, Task ID is %d\n", sg_u8TaskID);

    /*--------------------   Add your init code here   ----------------------*/
    /* Init queue 1 which is located in task space */
    sg_tQueue1.pu8Addr  = sg_au8Queue;
    sg_tQueue1.u8Len    = TASK_DEMO_QUEUE_BUF_SIZE;
    sg_tQueue1.u8MaxCnt = TASK_DEMO_QUEUE_BUF_NUM;
    sg_tQueue1.u8Begin  = 0;
    sg_tQueue1.u8End    = 0;
    sg_tQueue1.u8Cnt    = 0;
    
    /* Init queue 2 by queue API */
    Osal_Queue_Create(&sg_tQueue2, TASK_DEMO_QUEUE_BUF_SIZE, TASK_DEMO_QUEUE_BUF_NUM);

    /* Init timer */
    T_TIMER tTm;
    tTm.u8TaskID     = sg_u8TaskID;
    tTm.u16Evt       = EVENT_TIMER;
    tTm.u16Cnt       = OSAL_TMR_INFINITE_CNT;
    tTm.u32TmOut     = 1000;
    tTm.pfTmCallback = NULL;
    tTm.pPara        = NULL;

    Osal_Timer_Start(&tTm);
    /*-------------------   The end of your init code   ---------------------*/
    
    return;
}

/******************************************************************************
* Name       : uint16 Task_Demo_Queue_Process(uint16 u16Evt)
* Function   : Task Demo Queue process
* Input      : To be done
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 19th Jun 2016
******************************************************************************/
static uint16 Task_Demo_Queue_Process(uint16 u16Evt)
{
    uint8  u8MsgType,u8Idx;
    void  *ptMsg;

/******************************************************************************/
/* Process for timer event                                                    */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_TIMER);
    /*-----------------   Add your event process code here   -----------------*/
        /* Queue 1 writing */
        if(SW_OK == Osal_Queue_Is_Free(&sg_tQueue1))
        {   /* If free buff is available */
            for (u8Idx = 0; u8Idx < sizeof(sg_au8DataW); u8Idx++)
            {   /* Write the data into the buffer */
                OSAL_QUEUE_LAST_FREE(&sg_tQueue1)[u8Idx] = sg_au8DataW[u8Idx];
            }
            Osal_Queue_Inc(&sg_tQueue1);  /* Update the queue */
            DBG_PRINT("Queue 1 writing successfully!!\n");
        }
        else /* If queue is NOT free */
        {
            DBG_PRINT("Queue 1 is NOT free!!\n");
        }

        Osal_Msg_Send(sg_u8TaskID,MSG_TYPE_QUEUE,sizeof(T_QUEUE_MSG*),&sg_tQueue1);

        /**********************************************************************/
        /* Queue 2 writing */
        if(SW_OK == Osal_Queue_Write(&sg_tQueue2, sg_au8DataW, sizeof(sg_au8DataW)))
        {   /* If free buff is available */
            DBG_PRINT("Queue 2 writing successfully!!\n");
        }
        else /* If queue is NOT free */
        {
            DBG_PRINT("Queue 2 is NOT free!!\n");
        }
        Osal_Msg_Send(sg_u8TaskID,MSG_TYPE_QUEUE,sizeof(T_QUEUE_MSG*),&sg_tQueue1);

        sg_au8DataW[0]++;
    /*----------------  The end of your event process code  ------------------*/
    EVENT_PROCESS_END(EVENT_TIMER);
/******************************************************************************/


/******************************************************************************/
/* Process for message event                                                  */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_MSG); 
    /*-----------------   Add your event process code here   -----------------*/
        ptMsg = (void*)Osal_Msg_Receive(sg_u8TaskID, &u8MsgType);
        while(ptMsg)
        {   
            switch(u8MsgType)
            {
                case MSG_TYPE_QUEUE:
                {
                    T_QUEUE_MSG *ptQueueMsg = (T_QUEUE_MSG*)ptMsg;
                    /* Queue 1 reading */
                    if(&sg_tQueue1 == ptMsg->ptQueue)
                    {   /* If used buffer is available */
                        if(SW_OK ==Osal_Queue_Is_Not_Empty(ptMsg->ptQueue))
                        {   /* Read the data from queue */
                            for(u8Idx = 0; u8Idx < sizeof(sg_au8DataR); u8Idx++)
                            {
                                sg_au8DataR[u8Idx] = OSAL_QUEUE_FIRST_USED(ptMsg->ptQueue);
                            }
                            Osal_Queue_Dec(ptMsg->ptQueue);  /* Update the queue */
                            DBG_PRINT("Queue 1 reading successfully!!\n");
                        }
                        else/* If it a empty queue */
                        {
                            DBG_PRINT("Queue 1 is empty!\n");
                        }  
                    }
 
                    /**********************************************************/
                    /* Queue 2 reading */
                    else if(&sg_tQueue2 == ptMsg->ptQueue)
                    {   /* If reading is successful */
                        if(SW_OK == Osal_Queue_Read(ptMsg->ptQueue, sg_au8DataR, sizeof(sg_au8DataR)))
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
            ptMsg = (void*)Osal_Msg_Receive(sg_u8TaskID, &u8MsgType);
        }
    /*----------------  The end of your event process code  ------------------*/
    EVENT_PROCESS_END(EVENT_MSG);
/******************************************************************************/


/******************************************************************************/
/* Process for test event                                                     */
/******************************************************************************/
    EVENT_PROCESS_BEGIN(EVENT_TEST);
    /*-----------------   Add your event process code here   -----------------*/

        DBG_PRINT("This is task %d process function\n", sg_u8TaskID);

    /*----------------  The end of your event process code  ------------------*/
    EVENT_PROCESS_END(EVENT_TEST);
/******************************************************************************/

    return 0;
}

/* End of file */



