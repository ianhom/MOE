/******************************************************************************
* File       : MOE_Core.c
* Function   : Provide the main function of scheduler.
* Description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 28th Apr 2016
* History    :  No.  When           Who           What
*               1    28/Apr/2016    Ian           Create
******************************************************************************/

#include "../Pub/type_def.h"
#include "../Pub/common_head.h"
#include "project_config.h"
#include "./MOE_Core.h"
#include "../Pub/debug.h"
#include "./MOE_HAL.h"
#include "./MOE_Event.h"
#include "./MOE_Timer.h"
#include "./MOE_Msg.h"

static PF_MALLOC sg_pfMalloc = NULL;
static PF_FREE   sg_pfFree   = NULL;
static PF_POLL   sg_pfPoll   = NULL;

static T_EVENT sg_tEvt = {NULL};
static T_EVENT *sg_ptEvt = &sg_tEvt;
/******************************************************************************
* Name       : void Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
* Function   : Set a memory block with a desired value
* Input      : uint8* pDes   The destination pointer
*              uint8 u8Val   The desired set to be set
*              uint8 u8Len   The length of memory block in byte
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: Set a memory block with a desired value
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len)
{   
    uint8 u8Idx;
    /* Check if the pointer is invalid or NOT */
    MOE_CHECK_IF_RET_ST((pDes == NULL),"Memset invalid input\n");
    
    /* Loop for the desired length bytes to be set */
    for(u8Idx = 0; u8Idx < u8Len; u8Idx++)
    {
        pDes[u8Idx] = u8Val;   /* Set with the desired value */
    }

    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Moe_Init(PF_TIMER_SRC pfSysTm, PF_POLL pfPoll)
* Function   : Init MOE
* Input      : PF_TIMER_SRC pfSysTm   Free running system clock in ms
*              PF_POLL      pfPoll    The function to be polled(could be NULL)
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: 1. Check system clock function parameter
*              2. Save poll function (even it is NULL)
*              3. Init timer
*              4. Init HAL
*              5. Init Message
*              6. Init event processing 
*              7. Init all tasks.
* Version    : V1.00
* Author     : Ian
* Date       : 29th Apr 2016
******************************************************************************/
uint8 Moe_Init(PF_TIMER_SRC pfSysTm, PF_POLL pfPoll)
{
    /* Check if the input parameter is invalid or NOT */
    MOE_ASSERT_INFO((NULL != pfSysTm),"Timer function should NOT be NULL!");
   
    /* Get poll process function */
    sg_pfPoll = pfPoll;

    /* Init timer */
    Moe_Timer_Init(pfSysTm);

    /* Init HAL */
    Moe_HAL_Init();

    /* Init message */
    Moe_Msg_Init();

    /* Init event mechanism */
    Moe_Event_Init();
    
    /* Init all tasks */
    sg_ptEvt      = &sg_tEvt;       /* Make sure tasks get the correct IDs */
    sg_tEvt.u8Evt = EVENT_INIT;
    for(sg_tEvt.u8Task = 1; sg_tEvt.u8Task <= MAX_TASK_NUM; sg_tEvt.u8Task++)
    {
        cg_apfTaskFn[sg_tEvt.u8Task - 1](sg_tEvt.u8Evt, sg_tEvt.pPara);
    }
   
    sg_tEvt.u8Task = TASK_NO_TASK;
    sg_tEvt.u8Evt  = EVENT_NONE;

    return SW_OK;
}



/******************************************************************************
* Name       : void Moe_Run_System(void)
* Function   : The main function to schedule tasks.
* Input      : None
* Output:    : None
* Return     : None
* Description: 1. Process timers
*              2. Do poll function if available
*              3. Get event and process task
* Version    : V1.00
* Author     : Ian
* Date       : 28th Apr 2016
******************************************************************************/
void Moe_Run(void)
{
    while(1)                             /* The main loop                */
    {
        Moe_Timer_Process();             /* Update all timers            */
        if (sg_pfPoll)
        {
            sg_pfPoll();                 /* Do polling process if needed */
        }

        if(sg_ptEvt = Moe_Event_Get())   /* Check events                 */
        {
            cg_apfTaskFn[sg_ptEvt->u8Task - 1](sg_ptEvt->u8Evt, sg_ptEvt->pPara); /* Call the task process function */
            /* If it is a message event */
            /* AND the message destination task is such one(NOT forwarding) */
            /* AND the message pointer is valid */
            if((EVENT_MSG == sg_ptEvt->u8Evt)\
            && (((T_MSG_HEAD*)(sg_ptEvt->pPara))->u8DestTask == sg_ptEvt->u8Task)\
            && (NULL != sg_ptEvt->pPara))
            {
                Moe_Msg_Process((T_MSG_HEAD*)(sg_ptEvt->pPara)); /* Call message process */
            }
            sg_ptEvt->u8Task = TASK_NO_TASK;                     /* Finish task processing and cancel active task mark */
            sg_ptEvt = &sg_tEvt;                                 /* Point to a none event & task "event struct"        */   
        }
    }
}

/******************************************************************************
* Name       : uint8 Moe_Get_Active_Task(void)
* Function   : Get the current active task number.
* Input      : None
* Output:    : None
* Return     : uint8   0~255   The current active task number
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Get_Active_Task(void)
{
    return sg_ptEvt->u8Task;
}

/******************************************************************************
* Name       : uint8 Moe_Get_Active_Evt(void)
* Function   : Get the currentactive event.
* Input      : None
* Output:    : None
* Return     : uint8   0~255   The current active event
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Get_Active_Evt(void)
{
    return sg_ptEvt->u8Evt;
}

/******************************************************************************
* Name       : void Moe_Reg_Malloc_Free(PF_MALLOC pfMalloc, PF_FREE pfFree)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* Description: To be done.
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
* Description: To be done.
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
* Description: To be done.
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

/* End of file */
