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
#include "OSAL.h"
#include "MOE_Event.h"
#include "debug.h"

static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt);




static uint16 sg_u16EvtFisrt  = 0;
static uint16 sg_u16EvtCnt    = 0;
#ifndef __FLEXIBLE_EVENT_QUEUE
static T_EVENT sg_atEvtQueue[MAX_QUEUE_EVT_NUM] = {0};
#else
static T_EVENT_QUEUE *sg_ptEvtHead = NULL;
static T_EVENT_QUEUE *sg_ptEvtTail = NULL;
static uint16 sg_u16BlkCnt    = 1;
static uint16 sg_u16EvtCntMax = MAX_QUEUE_EVT_NUM;
#endif


/******************************************************************************
* Name       : uint8 Osal_Timer_Init(PF_TIMER_SRC pfSysTm)
* Function   : Init OSAL timer
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Moe_Event_Init()
{   
    uint32 u32IntSt;
#ifndef __FLEXIBLE_EVENT_QUEUE
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    Osal_Memset((uint8*)sg_atEvtQueue, 0, (MAX_QUEUE_EVT_NUM * sizeof(T_EVENT)));
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    return SW_OK;
#else
    uint8 u8Idx,u8Return;

    if(NULL != sg_ptEvtHead)
    {
        return SW_ERR;
    }
 
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    sg_ptEvtHead = OSAL_MALLOC(sizeof(T_EVENT_QUEUE));
    if(NULL == sg_ptEvtHead)
    {
        u8Return = SW_ERR;
    }
    else
    {

        sg_ptEvtTail = sg_ptEvtHead;
        sg_ptEvtHead->ptNext = NULL;
        Osal_Memset((uint8*)(sg_ptEvtHead->atEvtQueue), 0, (MAX_QUEUE_EVT_NUM * sizeof(T_EVENT)));
        sg_u16BlkCnt++;
        u8Return = SW_OK;
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    
    return u8Return;
#endif
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
uint8 Moe_Event_Set(uint8 u8TaskID, uint16 u16Evt)
{  
    uint8  u8Idx;
    uint16 u16EvtLast,u16Blk,u16OffSet;
    uint32 u32IntSt;
    T_EVENT_QUEUE *ptEvtQueue;
    T_EVENT       *ptEvt;

    if(TASK_ALL_TASK == u8TaskID)   /* If it is an event for all tasks */
    {
        DBG_PRINT("It is an event for all tasks\n");
        ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
        /**************************************************************************************************/
        for(u8Idx = 1; u8Idx <= MAX_TASK_NUM; u8Idx++)
        {
            Moe_Event_Setting(u8Idx, u16Evt);
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
    Moe_Event_Setting(u8TaskID, u16Evt);
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;
}


static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt)
{
    uint16 u16EvtLast;
#ifdef __FLEXIBLE_EVENT_QUEUE
    uint16 u16Blk,u16OffSet;
    T_EVENT_QUEUE *ptEvtQueue = sg_ptEvtHead;

    if(sg_u16EvtCntMax == sg_u16EvtCnt)
    {
        return SW_ERR;
    }

    u16EvtLast = (sg_u16EvtFisrt + sg_u16EvtCnt) % sg_u16EvtCntMax;
    u16Blk     = u16EvtLast % MAX_QUEUE_EVT_NUM;
    u16OffSet  = u16EvtLast / MAX_QUEUE_EVT_NUM;
    while(u16Blk)
    {
        ptEvtQueue = ptEvtQueue->ptNext;
        u16Blk--;
    }
    ptEvtQueue->atEvtQueue[u16OffSet].u8Task = u8TaskID;
    ptEvtQueue->atEvtQueue[u16OffSet].u8Evt  = u8Evt;

    sg_u16EvtCnt++;

    if(sg_u16EvtCnt == sg_u16EvtCntMax)
    {
        sg_ptEvtTail->ptNext = (T_EVENT_QUEUE*)OSAL_MALLOC(sizeof(T_EVENT_QUEUE));
        if(NULL == sg_ptEvtTail->ptNext)
        {
            return SW_ERR;
        }
        sg_ptEvtTail = sg_ptEvtTail->ptNext;
        sg_ptEvtTail->ptNext = NULL;
        Osal_Memset(sg_ptEvtTail->au8EvtQueue, 0, (MAX_QUEUE_EVT_NUM * sizeof(T_EVENT)));
        sg_u16EvtCntMax += MAX_QUEUE_EVT_NUM;
    }
#else
    if(MAX_QUEUE_EVT_NUM == sg_u16EvtCnt)
    {
        return SW_ERR;
    }
    u16EvtLast = (sg_u16EvtFisrt + sg_u16EvtCnt) % MAX_QUEUE_EVT_NUM;
    sg_atEvtQueue[u16EvtLast].u8Task = u8TaskID;
    sg_atEvtQueue[u16EvtLast].u8Evt  = u8Evt;
    sg_u16EvtCnt++;

#endif
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
    sg_u16EvtFisrt = (sg_u16EvtFisrt + 1) % sg_u16EvtCntMax;
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
        OSAL_FREE(ptTemp);
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

#else
    ptEvt->u8Task  = sg_atEvtQueue[sg_u16EvtFisrt].u8Task;
    ptEvt->u8Evt   = sg_atEvtQueue[sg_u16EvtFisrt].u8Evt;
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/    
    sg_u16EvtFisrt = (sg_u16EvtFisrt + 1) % MAX_QUEUE_EVT_NUM;
    sg_u16EvtCnt--
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

#endif
    return SW_OK;
}





/* end of file */

