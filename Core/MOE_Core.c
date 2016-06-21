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

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "OSAL.h"
#include "debug.h"
#include "OSAL_App.h"
#include "OSAL_Timer.h"
#include "OSAL_Msg.h"


static PF_MALLOC sg_pfMalloc = NULL;
static PF_FREE   sg_pfFree   = NULL;


static uint8 sg_u8ActiveTask = TASK_NO_TASK;            /* Save the current active task number            */

static PF_TASK_PROCESS sg_apfTaskFn[MAX_TASK_NUM];      /* Create a list of process function of all tasks */

uint16 au16TaskEvt[MAX_TASK_NUM];                       /* Create a event list for tasks                  */

/******************************************************************************
* Name       : void Osal_Reg_Tasks(PF_TASK_PROCESS pfTaskFn)
* Function   : Register task process function into the table.
* Input      : PF_TASK_PROCESS pfTaskFn    Task process function pointer
* Output:    : None
* Return     : None
* description: 1. Check if the input function pointer is invalid.
*              2. Check if the registered task number is invlide.
*              3. Store the function pointer into the table.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Osal_Reg_Tasks(PF_TASK_PROCESS pfTaskFn)
{
    static uint8 s_u8RegTaskCnt = 0;  /* Start the index of task process function array */

    /* Check if the input task process function pointer is invalid or NOT */
    if(NULL == pfTaskFn)
    {
        DBG_PRINT("The process function of Task %d is invalid \n", (s_u8RegTaskCnt+1));
        return;
    }

    /* If the inited tasks count is NOT lower than the max number of all tasks */
    if (s_u8RegTaskCnt > MAX_TASK_NUM)
    {
        DBG_PRINT("Task number ERROR!!\n");
        while(1);                  /* Enter forever loop */
    }

    sg_apfTaskFn[s_u8RegTaskCnt++] = pfTaskFn;  /* Save the task process function pointer into the task table */

    return;
}

/******************************************************************************
* Name       : void Osal_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
* Function   : Set a memory block with a desired value
* Input      : uint8* pDes   The destination pointer
*              uint8 u8Val   The desired set to be set
*              uint8 u8Len   The length of memory block in byte
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: Set a memory block with a desired value
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Osal_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
{   
    uint8 u8Idx;
    /* Check if the pointer is invalid or NOT */
    if (NULL == pDes)
    {   /* Return error if invalid pointer */
        return SW_ERR;
    }
    /* Loop for the desired length bytes to be set */
    for(u8Idx = 0; u8Idx < u8Len; u8Idx++)
    {
        pDes[u8Idx] = u8Val;   /* Set with the desired value */
    }

    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Osal_Event_Set(uint8 u8TaskID, uint16 Event)
* Function   : To be done
* Input      : uint8  u8TaskID
*              uint16 u16Evt
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Osal_Event_Set(uint8 u8TaskID, uint16 u16Evt)
{  
    uint8  u8Idx;
    uint32 u32IntSt;

    if(TASK_ALL_TASK == u8TaskID)   /* If it is an event for all tasks */
    {
        DBG_PRINT("It is an event for all tasks\n");
        ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
        /**************************************************************************************************/
        for(u8Idx = 0; u8Idx < MAX_TASK_NUM; u8Idx++)
        {
            au16TaskEvt[u8Idx] |= u16Evt;              /* Set all tasks with the event */
        }
        /**************************************************************************************************/
        EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
        return SW_OK;
    }

    /* Check if the task ID is invalid or NOT */
    if(u8TaskID > MAX_TASK_NUM)
    {   /* If task ID is wrong, return error */
        return SW_ERR;
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    au16TaskEvt[u8TaskID - 1] |= u16Evt;
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;
}

/******************************************************************************
* Name       : uint8 Osal_Event_Set(uint8 u8TaskID, uint16 Event)
* Function   : To be done
* Input      : uint8  u8TaskID
*              uint16 u16Evt
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Osal_Event_Clr(uint8 u8TaskID, uint16 u16Evt)
{  
    uint8  u8Idx;
    uint32 u32IntSt;

    if(TASK_ALL_TASK == u8TaskID)   /* If it is an event for all tasks */
    {
        DBG_PRINT("It is an event for all tasks\n");
        ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
        /**************************************************************************************************/
        for(u8Idx = 0; u8Idx < MAX_TASK_NUM; u8Idx++)
        {
            au16TaskEvt[u8Idx] &= (~u16Evt);           /* Clear all tasks with the event */
        }
        /**************************************************************************************************/
        EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
        return SW_OK;
    }

    /* Check if the task ID is invalid or NOT */
    if(u8TaskID > MAX_TASK_NUM)
    {   /* If task ID is wrong, return error */
        return SW_ERR;
    }
    
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    au16TaskEvt[u8TaskID - 1] &= (~u16Evt);
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;
}


/******************************************************************************
* Name       : void Osal_Init()
* Function   : Init all tasks
* Input      : None
* Output:    : None
* Return     : None
* description: 1. Clear tasks events list with NO EVENT.
*              2. Clear task process function pointer table with NULL.
*              3. Init all tasks and pass the task ID into the tasks.
*              4. Check all tasks are registered.
* Version    : V1.00
* Author     : Ian
* Date       : 29th Apr 2016
******************************************************************************/
void Osal_Init()
{
    uint32 u8Idx;    

    /* Init the task events list with NO EVENT                */
    Osal_Memset((uint8*)au16TaskEvt, EVENT_NONE, sizeof(uint16)*MAX_TASK_NUM);
   
    /* Init the task process function pointer table with NULL */
    Osal_Memset((uint8*)sg_apfTaskFn, NULL, sizeof(uint16*)*MAX_TASK_NUM);

    /* Init all tasks */
    Osal_Tasks_Init();

    /* Check all task process function pointers are registered */
    for(u8Idx = 0; u8Idx < MAX_TASK_NUM; u8Idx++)
    {   /* If the pointer is NULL */
        if(NULL == sg_apfTaskFn[u8Idx])
        {
            DBG_PRINT("Task function pointer table is wrong\n");
            while(1);                  /* Enter forever loop */
        }
    }
   
    return;
}

/******************************************************************************
* Name       : void Osal_ProcessPoll()
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Osal_ProcessPoll()
{
    /* To be done... */
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
    uint8 u8Idx = 0;
    for(;;)                               /* The main loop                */
    {
        Osal_Timer_Process();             /* Update all timers            */
        Osal_Msg_Process();               /* Process messageas            */
        Osal_ProcessPoll();               /* Do polling process if needed */
       
        do
        {
            if(au16TaskEvt[u8Idx])        /* Check if events happen for such task */
            {       
                break;                     /* If so, break loop                    */
            }
            /* If there is NO events for such task, do nothing and continue next task checking */
        }while(++u8Idx < MAX_TASK_NUM);   /* Check all tasks */
        /* Reach here if an event happens for a task, or No event for all tasks   */
       
        if(u8Idx < MAX_TASK_NUM)          /* If an event happens for a task       */
        {
            uint16 u16Evt;
            uint32 u32IntSt;
           
            ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
            /**************************************************************************************************/
            u16Evt = au16TaskEvt[u8Idx];    /* Get the event             */
            au16TaskEvt[u8Idx] = 0;         /* Clean the event temporary */
            /**************************************************************************************************/
            EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
            
            sg_u8ActiveTask = u8Idx + 1;                   /* Save the active task number    */
            u16Evt = (sg_apfTaskFn[u8Idx](u16Evt));        /* Call the task process function */
            sg_u8ActiveTask = TASK_NO_TASK;                /* Finish task processing and cancel active task mark */
           
           ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
           /**************************************************************************************************/
            au16TaskEvt[u8Idx] |= u16Evt;  /* Add the rest events back */
           /**************************************************************************************************/
           EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
        }
        /* If u8Idx is NOT lower than u8TaskCnt, it indicate that NO event happens and nothing need to be done */
        u8Idx = 0;
    }
    return;
}

/******************************************************************************
* Name       : uint8 Osal_Get_Acktive_Task()
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Osal_Get_Acktive_Task()
{
    return sg_u8ActiveTask;
}

/******************************************************************************
* Name       : void Osal_Reg_Malloc_Free(PF_MALLOC pfMalloc, PF_FREE pfFree)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th May 2016
******************************************************************************/
void Osal_Reg_Malloc_Free(PF_MALLOC pfMalloc, PF_FREE pfFree)
{
    sg_pfMalloc = pfMalloc;  /* Get malloc function */
    sg_pfFree   = pfFree;    /* Get free function   */
    return;
}

/******************************************************************************
* Name       : void* Osal_Malloc(uint32 u32Size)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th May 2016
******************************************************************************/
void* Osal_Malloc(uint32 u32Size)
{   
    /* Check if malloc and free function is registered */
    if((NULL != sg_pfMalloc) && (NULL != sg_pfFree) )
    {   /* If so, use the registered malloc */
        return sg_pfMalloc(u32Size);
    }

    /* A malloc function to be done here later */
    return NULL;
}

/******************************************************************************
* Name       : void Osal_Free(void *p)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th May 2016
******************************************************************************/
void Osal_Free(void *p)
{
    /* Check if malloc and free function is registered */
    if((NULL != sg_pfMalloc) && (NULL != sg_pfFree) )
    {   /* If so, use the registered free */
        sg_pfFree(p);
        return;
    }

    /* A malloc function to be done here later */
    return;    
}


/* End of file */




