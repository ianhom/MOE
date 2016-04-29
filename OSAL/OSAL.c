/******************************************************************************
* File       : OSAL.c
* Function   : Provide the main function of OSAL-like scheduler.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 28th Apr 2016
* History    :  No.  When           Who           What
*               1    28/Apr/2016    Ian           Create
******************************************************************************/

#include "OSAL.h"

static uint8 sg_u8ActiveTask = TASK_NO_TASK;  /* Save the current active task number */

/* Create a list of process function of all tasks */
const PF_TASK_PROCESS apfTaskFn[] = 
{
    Task1_Process,                   /* Task 1 process */
    Task2_Process,                   /* Task 2 process */
    Task3_Process                    /* Task 3 process */
};

const uint8 u8TaskCnt = sizeof(apfTaskFn) / sizeof(apfTaskFn[0]);   /* Get the quantity of tasks     */
uint16 au16TaskEvt[sizeof(uint16)*u8TaskCnt] = {0};                 /* Create a event list for tasks */

/******************************************************************************
* Name       : void Osal_Init_Tasks()
* Function   : Init all tasks
* Input      : None
* Output:    : None
* Return     : None
* description: 1. Clear tasks events list with all 0-value.
*              2. Init all tasks and pass the task ID into the tasks.
* Version    : V1.00
* Author     : Ian
* Date       : 29th Apr 2016
******************************************************************************/
void Osal_Init_Tasks()
{
    uint8 u8TaskID = 0;            /* Task No. starts from 0, higher number ==> lower priority */

    /* Init the task events list with all 0 value */
    for(uint8 u8Idx = 0; u8Idx < (sizeof(uint16)*u8TaskCnt); au16TaskEvt[u8Idx++] = 0;);
    
    Task1_Init(u8TaskID++);        /* Task 1 init operation */
    Task2_Init(u8TaskID++);        /* Task 2 init operation */
    Task3_Init(u8TaskID);          /* Task 3 inti operation */
    
    return;
}

/******************************************************************************
* Name       : void Osal_Run_System()
* Function   : The main function to schedule tasks.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 28th Apr 2016
******************************************************************************/
void Osal_Run_System()
{
    uint8 u8Idx;
    for(;;) /* The main loop */
    {
        OSAL_ProcessPoll();  /* Do polling process if needed */
        
        do
        {
            if(au16TaskEvt[u8Idx])  /* Check if events happen for such task */
            {        
               break;               /* If so, break loop */
            }
            /* If there is NO events for such task, do nothing and continue next task checking */
        }while(++u8Idx < u8TaskCnt); /* Check all tasks */
        /* Reach here if an event happens for a task, or No event for all tasks  */
        
        if(u8Idx < u8TaskCnt)  /* If an event happens for a task */
        {
            uint16 u16Evt;
            uint32 u32IntSt;
            
            ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly, save the interrupt status and disable all interrupts */
            u16Evt = au16TaskEvt[u8Idx];    /* Get the event */
            au16TaskEvt[u8Idx] = 0;         /* Clean the event temporary */
            EXIT_CRITICAL_ZONE(u32INtSt);   /* Exit the critical zone and restore the interrupt status and enable interrupts */
            
            sg_u8ActiveTask = u8Idx;                       /* Save the active task number    */
            u16Evt = (apfTaskFn[u8Idx](u8Idx, u16Evt));    /* Call the task process function */
            sg_u8ActiveTask = TASK_NO_TASK;                /* Finish task processing and cancel active task mark */
            
            ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly, save the interrupt status and disable all interrupts */
            au16TaskEvt[u8Idx] = u16Evt;    /* Add the rest events back */
            EXIT_CRITICAL_ZONE(u32INtSt);   /* Exit the critical zone and restore the interrupt status and enable interrupts */
        }
        /* If u8Idx is NOT lower than u8TaskCnt, it indicate that NO event happens and nothing need to be done */
    }
    return;
}

