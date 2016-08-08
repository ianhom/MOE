/******************************************************************************
* File       : MOE_Event.c
* Function   : Provide event services.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 21st Jun 2016
* History    :  No.  When           Who           What
*               1    21/Jun/2016    Ian           V1.00: Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "debug.h"

/* Declaration of static function */
static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg);


static uint16 sg_u16EvtFisrt = 0;  /* The fisrt available data position */
static uint16 sg_u16EvtCnt   = 0;  /* The count of availabe data        */
#ifndef __FLEXIBLE_EVENT_QUEUE     /* If use regular length fixed queue */
static T_EVENT sg_atEvtQueue[MAX_QUEUE_EVT_NUM] = {0};
#else                              /* Else if use flexible length queue */
static T_EVENT_QUEUE *sg_ptEvtHead = NULL;          /* Head node of event queue link list */
static T_EVENT_QUEUE *sg_ptEvtTail = NULL;          /* Tail node of event queue link list */
static uint16 sg_u16BlkCnt    = 1;                  /* Count of queue node block          */
static uint16 sg_u16EvtCntMax = MAX_QUEUE_EVT_NUM;  /* Max count of exsit events          */
#endif


/******************************************************************************
* Name       : uint8 Moe_Timer_Init(PF_TIMER_SRC pfSysTm)
* Function   : Init MOE timer
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Moe_Event_Init(void)
{   
    uint32 u32IntSt;
#ifndef __FLEXIBLE_EVENT_QUEUE      /* If use regular length fixed queue */
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    Moe_Memset((uint8*)sg_atEvtQueue, 0, (MAX_QUEUE_EVT_NUM * sizeof(T_EVENT)));
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    return SW_OK;
#else                               /* Else if use flexible length queue */
    uint8 u8Idx,u8Return;

    /* Check if head node is empty or NOT */
    if(NULL != sg_ptEvtHead)
    {   /* If it is NOT empty which means it had been inited, return error */
        return SW_ERR;
    }
 
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    sg_ptEvtHead = MOE_MALLOC(sizeof(T_EVENT_QUEUE));  /* Create a space for head node */
    if(NULL == sg_ptEvtHead)   /* If malloc is failed */
    {
        u8Return = SW_ERR;
    }
    else /* If new node is created successfully */
    {
        sg_ptEvtTail = sg_ptEvtHead;      
        sg_ptEvtHead->ptNext = NULL;    /* Update link list head and tail information */
        Moe_Memset((uint8*)(sg_ptEvtHead->atEvtQueue), 0, (MAX_QUEUE_EVT_NUM * sizeof(T_EVENT)));
        sg_u16BlkCnt++;                 /* Create the first event queue block */
        u8Return = SW_OK;
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    
    return u8Return;
#endif
}


/******************************************************************************
* Name       : uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg)
* Function   : This function is used to set event for tasks.
* Input      : uint8 u8TaskID   1~255               The task ID to receive such event
*              uint8 u8Evt      1~255               The event type
*              uint8 u8Urg      MOE_EVENT_URGENT    It is an urgent event
*                               MOE_EVENT_NORMAL    It is a normal event
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg) 
{  
    uint8  u8Idx;
    uint32 u32IntSt;

    if(TASK_ALL_TASK == u8TaskID)   /* If it is an event for all tasks */
    {
        DBG_PRINT("It is an event for all tasks\n");
        ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
        /**************************************************************************************************/
        for(u8Idx = 1; u8Idx <= MAX_TASK_NUM; u8Idx++)
        {
            Moe_Event_Setting(u8Idx, u8Evt,u8Urg);
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
    Moe_Event_Setting(u8TaskID, u8Evt,u8Urg);
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;
}

/******************************************************************************
* Name       : static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg)
* Function   : This function is used to set event for each tasks.
* Input      : uint8 u8TaskID   1~255               The task ID to receive such event
*              uint8 u8Evt      1~255               The event type
*              uint8 u8Urg      MOE_EVENT_URGENT    It is an urgent event
*                               MOE_EVENT_NORMAL    It is a normal event
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg)
{
    uint8  u8Idx;
    uint16 u16EvtLast;

/* If use  length fixed queue */    
#ifdef __FLEXIBLE_EVENT_QUEUE
    uint16 u16Blk,u16OffSet;
    T_EVENT_QUEUE *ptEvtQueue = sg_ptEvtHead;
    T_EVENT_QUEUE *ptPre      = sg_ptEvtHead;
    T_EVENT_QUEUE *ptTemp;

    /* If the current event counter is equal to the max limit */
    if(sg_u16EvtCntMax == sg_u16EvtCnt)
    {
        return SW_ERR;  /* Return error */
    }

    /* If it is an urgent event */
    if(MOE_EVENT_URGENT == u8Urg)
    {
        if(0 == sg_u16EvtFisrt)  /* If the first available data is in 0 position */
        {
            u16EvtLast = sg_u16EvtCntMax - 1;  /* Calculate the last empty position */
        }
        else  /* In other situations */
        {
            u16EvtLast = sg_u16EvtFisrt - 1;   /* Calculate the last empty position */
        }
        sg_u16EvtFisrt = u16EvtLast;           
    }
    else/* If it is a normal event */
    {   /* Calculate the last empty position */
        u16EvtLast = (sg_u16EvtFisrt + sg_u16EvtCnt) % sg_u16EvtCntMax;
    }

    u16Blk    = u16EvtLast % MAX_QUEUE_EVT_NUM;   /* Calculate the event queue block */
    u16OffSet = u16EvtLast / MAX_QUEUE_EVT_NUM;   /* Calculate the offset in block   */

    /* Find the block to be used */
    while(u16Blk)
    {
        ptEvtQueue = ptEvtQueue->ptNext;
        u16Blk--;
    }
    
    ptEvtQueue->atEvtQueue[u16OffSet].u8Task = u8TaskID; /* Fill the task ID   */
    ptEvtQueue->atEvtQueue[u16OffSet].u8Evt  = u8Evt;    /* Fill the evnet     */
    sg_u16EvtCnt++;                                      /* Update event count */

    /* Create more event queue block when current entire blocks are full */
    if(sg_u16EvtCnt == sg_u16EvtCntMax)
    {
        ptTemp = (T_EVENT_QUEUE*)MOE_MALLOC(sizeof(T_EVENT_QUEUE));
        if(NULL == ptTemp)
        {
            return SW_ERR;
        }

        u16Blk    = sg_u16EvtFisrt % MAX_QUEUE_EVT_NUM;   /* Calculate the event queue block */
        u16OffSet = sg_u16EvtFisrt / MAX_QUEUE_EVT_NUM;   /* Calculate the offset in block   */

        /* Find the block which has the fisrt available event */
        while(u16Blk)
        {
            ptEvtQueue = ptEvtQueue->ptNext;
            u16Blk--;
        }

        for(u8Idx = 0; u8Idx < u16OffSet; u8Idx++)
        {
            ptTemp->atEvtQueue[u8Idx].u8Evt  = ptEvtQueue->atEvtQueue[u8Idx].u8Evt;
            ptTemp->atEvtQueue[u8Idx].u8Task = ptEvtQueue->atEvtQueue[u8Idx].u8Task;
        }

        if(0 == u16Blk)
        {
            ptTemp->ptNext = ptEvtQueue;
            sg_ptEvtHead   = ptTemp;
        }
        else
        {
            u16Blk--;
            while(u16Blk)
            {
                ptPre = ptPre->ptNext;
                u16Blk--;
            }
            ptPre->ptNext  = ptTemp;
            ptTemp->ptNext = ptEvtQueue;
        }

        sg_u16EvtFisrt  += MAX_QUEUE_EVT_NUM;
        sg_u16EvtCntMax += MAX_QUEUE_EVT_NUM;
    }

    
/* If use regular length fixed queue */    
#else
    /* If the current event count is equal to the max limit */
    if(MAX_QUEUE_EVT_NUM == sg_u16EvtCnt)
    {   
        return SW_ERR;  /* Return error */
    }

    /* If it is an urgent event */
    if(MOE_EVENT_URGENT == u8Urg)
    {
        if(0 == sg_u16EvtFisrt)       /* If the first available data is in 0 position */
        {
            u16EvtLast = MAX_QUEUE_EVT_NUM - 1;  /* Calculate the last empty position */
        }
        else
        {
            u16EvtLast = sg_u16EvtFisrt - 1;     /* Calculate the last empty position */
        }
        sg_u16EvtFisrt = u16EvtLast;  /* Update the first event position */
    }
    else/* If it is a normal event */
    {   /* Calculate the position for new event */
        u16EvtLast = (sg_u16EvtFisrt + sg_u16EvtCnt) % MAX_QUEUE_EVT_NUM;    
    }
    sg_atEvtQueue[u16EvtLast].u8Task = u8TaskID;  /* Fill the task ID   */
    sg_atEvtQueue[u16EvtLast].u8Evt  = u8Evt;     /* Fill the evnet     */
    sg_u16EvtCnt++;                               /* Update event count */

#endif
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
uint16 Moe_Event_Get(T_EVENT *ptEvt)
{  
    uint32 u32IntSt;
#ifdef __FLEXIBLE_EVENT_QUEUE
    uint16 u16Blk,u16OffSet;
    T_EVENT_QUEUE *ptEvtQueue = sg_ptEvtHead,ptTemp;
#endif    
    /* Check if the task ID is invalid or NOT */
    if(NULL == ptEvt)
    {   /* If task ID is wrong, return error */
        return 0;
    }

    if(0 == sg_u16EvtCnt) 
    {
        return 0;
    }

#ifdef __FLEXIBLE_EVENT_QUEUE    
    u16Blk    = sg_u16EvtFisrt % MAX_QUEUE_EVT_NUM;
    u16OffSet = sg_u16EvtFisrt / MAX_QUEUE_EVT_NUM;
    
    while(u16Blk)
    {
        ptEvtQueue = ptEvtQueue->ptNext;
        u16Blk--;
    }

    ptEvt->u8Task  = ptEvtQueue->atEvtQueue[u16OffSet].u8Task;
    ptEvt->u8Evt   = ptEvtQueue->atEvtQueue[u16OffSet].u8Evt;
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    sg_u16EvtFisrt   = (sg_u16EvtFisrt + 1) % sg_u16EvtCntMax;
    sg_u16EvtCnt--;

    if((sg_u16BlkCnt > 1)\
    && (sg_u16EvtFisrt < MOE_EVENT_BLK_RM_THRD) \
    && ((sg_u16EvtFisrt + sg_u16EvtCnt) <MOE_EVENT_BLK_RM_THRD))
    {
        sg_u16EvtCntMax -= MAX_QUEUE_EVT_NUM;
        
        u16Blk = sg_u16BlkCnt - 2;
        ptEvtQueue = sg_ptEvtHead;
        while(u16Blk)
        {
            ptEvtQueue = ptEvtQueue->ptNext;
            u16Blk--;
        }
        ptTemp = ptEvtQueue->ptNext;
        ptEvtQueue->ptNext = NULL;
        MOE_FREE(ptTemp);
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

#else
    ptEvt->u8Task  = sg_atEvtQueue[sg_u16EvtFisrt].u8Task;
    ptEvt->u8Evt   = sg_atEvtQueue[sg_u16EvtFisrt].u8Evt;
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    sg_u16EvtFisrt   = (sg_u16EvtFisrt + 1) % MAX_QUEUE_EVT_NUM;
    sg_u16EvtCnt--;
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

#endif
    return (uint16)ptEvt->u8Task;
}





/* end of file */

