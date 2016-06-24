/******************************************************************************
* File       : MOE.c
* Function   : Provide the main function of MOE-like scheduler.
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
#include "MOE_Core.h"
#include "debug.h"
#include "MOE_App.h"
#include "MOE_Timer.h"
#include "MOE_Msg.h"
#include "MOE_Event.h"


static PF_MALLOC sg_pfMalloc = NULL;
static PF_FREE   sg_pfFree   = NULL;


static uint8 sg_u8ActiveTask = TASK_NO_TASK;            /* Save the current active task number            */

static PF_TASK_PROCESS sg_apfTaskFn[MAX_TASK_NUM];      /* Create a list of process function of all tasks */

uint16 au16TaskEvt[MAX_TASK_NUM];                       /* Create a event list for tasks                  */

T_EVENT sg_tEvt;


/******************************************************************************
* Name       : void Moe_Reg_Tasks(PF_TASK_PROCESS pfTaskFn)
* Function   : Register task process function into the table.
* Input      : PF_TASK_PROCESS pfTaskFn    Task process function pointer
* Output:    : None
* Return     : None
* description: 1. Check if the input function pointer is invalid.
*              2. Check if the registered task number is invalid.
*              3. Store the function pointer into the table.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Moe_Reg_Tasks(PF_TASK_PROCESS pfTaskFn)
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
* Name       : void Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
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
uint8 Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
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
* Name       : uint8 Moe_Event_Set(uint8 u8TaskID, uint16 Event)
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
uint8 Moe_Event_Clr(uint8 u8TaskID, uint16 u16Evt)
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
* Name       : void Moe_Init()
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
void Moe_Init()
{
    uint32 u8Idx;    
   
    sg_tEvt.u8Task = TASK_NO_TASK;
    sg_tEvt.u8Evt  = EVENT_NONE;
    
    /* Init the task events list with NO EVENT                */
    Moe_Memset((uint8*)au16TaskEvt, EVENT_NONE, sizeof(uint8)*MAX_TASK_NUM);
   
    /* Init the task process function pointer table with NULL */
    Moe_Memset((uint8*)sg_apfTaskFn, NULL, sizeof(uint16*)*MAX_TASK_NUM);

    /* Init event mechanism */
    Moe_Event_Init();
    
    /* Init all tasks */
    Moe_Tasks_Init();

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
* Name       : void Moe_ProcessPoll()
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Moe_ProcessPoll()
{
    /* To be done... */
    return;
}


/******************************************************************************
* Name       : void Moe_Run_System()
* Function   : The main function to schedule tasks.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 28th Apr 2016
******************************************************************************/
void Moe_Run_System()
{
    while(1)                             /* The main loop                */
    {
        Moe_Timer_Process();             /* Update all timers            */
        Moe_Msg_Process();               /* Process messageas            */
        Moe_ProcessPoll();               /* Do polling process if needed */

        if(Moe_Event_Get(&sg_tEvt))
        {
            sg_apfTaskFn[sg_tEvt.u8Task - 1](sg_tEvt.u8Evt);    /* Call the task process function */
            sg_tEvt.u8Task = TASK_NO_TASK;             /* Finish task processing and cancel active task mark */
            
        }
    }
    return;
}

/******************************************************************************
* Name       : uint8 Moe_Get_Acktive_Task()
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Get_Acktive_Task()
{
    return sg_tEvt.u8Task;
}

/******************************************************************************
* Name       : void Moe_Reg_Malloc_Free(PF_MALLOC pfMalloc, PF_FREE pfFree)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th May 2016
******************************************************************************/
void Moe_Reg_Malloc_Free(PF_MALLOC pfMalloc, PF_FREE pfFree)
{
    sg_pfMalloc = pfMalloc;  /* Get malloc function */
    sg_pfFree   = pfFree;    /* Get free function   */
    return;
}

/******************************************************************************
* Name       : void* Moe_Malloc(uint32 u32Size)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th May 2016
******************************************************************************/
void* Moe_Malloc(uint32 u32Size)
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
* Name       : void Moe_Free(void *p)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th May 2016
******************************************************************************/
void Moe_Free(void *p)
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


uint8 Moe_Process_Task(uint8 u8Task)
{   
    uint8  u8Idx;
    uint16 u16Evt;
    uint32 u32IntSt;

    if((TASK_NO_TASK == u8Task) ||(u8Task > MAX_TASK_NUM))
    {
        return SW_ERR;
    }

    u8Idx = u8Task - 1;


    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    u16Evt = au16TaskEvt[u8Idx];    /* Get the event             */
    au16TaskEvt[u8Idx] = 0;         /* Clean the event temporary */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    
    sg_u8ActiveTask = u8Task;                   /* Save the active task number    */
    u16Evt = (sg_apfTaskFn[u8Idx](u16Evt));     /* Call the task process function */
    sg_u8ActiveTask = TASK_NO_TASK;             /* Finish task processing and cancel active task mark */
    
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    au16TaskEvt[u8Idx] |= u16Evt;   /* Add the rest events back */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;
}



/* End of file */




