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
static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara);

static uint16 sg_u16EvtFirst = 0;  /* The fisrt available data position */
static uint16 sg_u16EvtCnt   = 0;  /* The count of availabe data        */
#ifndef __FLEXIBLE_EVENT_QUEUE     /* If use regular length fixed queue */
static T_EVENT sg_atEvtQueue[MAX_QUEUE_EVT_NUM] = {0};
#else                              /* Else if use flexible length queue */
static uint32 Moe_Event_Queue_Block_Add(void);
static void Moe_Event_Queue_Block_Del(void);

static T_EVENT_QUEUE *sg_ptEvtHead = NULL;          /* Head node of event queue link list */
static uint16 sg_u16BlkCnt    = 0;                  /* Count of queue node block          */
static uint16 sg_u16EvtCntMax = MAX_QUEUE_EVT_NUM;  /* Max count of exsit events          */
#endif



#ifndef __FLEXIBLE_EVENT_QUEUE     /* If use regular length fixed queue */
/******************************************************************************
* Name       : uint8 Moe_Event_Init(void)
* Function   : Init event queue
* Input      : None
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

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    Moe_Memset((uint8*)sg_atEvtQueue, 0, (MAX_QUEUE_EVT_NUM * sizeof(T_EVENT)));
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    
    return SW_OK;
}


/******************************************************************************
* Name       : uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara)
* Function   : This function is used to set event for tasks.
* Input      : uint8 u8TaskID   1~255               The task ID to receive such event
*              uint8 u8Evt      1~255               The event type
*              uint8 u8Urg      MOE_EVENT_URGENT    It is an urgent event
*                               MOE_EVENT_NORMAL    It is a normal event
*              uint8 pPara                          Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara) 
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
    MOE_CHECK_IF_RET_ST((u8TaskID > MAX_TASK_NUM),"Task ID should be valid\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    Moe_Event_Setting(u8TaskID, u8Evt, u8Urg, pPara);
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;
}

/******************************************************************************
* Name       : static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara)
* Function   : This function is used to set event for each tasks.
* Input      : uint8 u8TaskID   1~255               The task ID to receive such event
*              uint8 u8Evt      1~255               The event type
*              uint8 u8Urg      MOE_EVENT_URGENT    It is an urgent event
*                               MOE_EVENT_NORMAL    It is a normal event
*              uint8 pPara                          Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara)
{
    uint8  u8Idx;
    uint16 u16EvtLast;

    /* If the current event count is equal to the max limit */
    MOE_CHECK_IF_RET_ST((MAX_QUEUE_EVT_NUM == sg_u16EvtCnt), "Event queue is full\n");

    /* If it is an urgent event */
    if(MOE_EVENT_URGENT == u8Urg)
    {
        if(0 == sg_u16EvtFirst)       /* If the first available data is in 0 position */
        {
            u16EvtLast = MAX_QUEUE_EVT_NUM - 1;  /* Calculate the last empty position */
        }
        else
        {
            u16EvtLast = sg_u16EvtFirst - 1;     /* Calculate the last empty position */
        }
        sg_u16EvtFirst = u16EvtLast;  /* Update the first event position */
    }
    else/* If it is a normal event */
    {   /* Calculate the position for new event */
        u16EvtLast = (sg_u16EvtFirst + sg_u16EvtCnt) % MAX_QUEUE_EVT_NUM;    
    }
    sg_atEvtQueue[u16EvtLast].pPara  = pPara;             /* Fill the parameter           */
    sg_atEvtQueue[u16EvtLast].u8Src  = TASK_CURRENT_TASK; /* Fill the source task ID      */
    sg_atEvtQueue[u16EvtLast].u8Task = u8TaskID;          /* Fill the destination task ID */
    sg_atEvtQueue[u16EvtLast].u8Evt  = u8Evt;             /* Fill the evnet               */
    sg_u16EvtCnt++;                                       /* Update event count           */

    return SW_OK;
}


/******************************************************************************
* Name       : T_EVENT* Moe_Event_Get(void)
* Function   : To get a event from quque
* Input      : None
* Output:    : None
* Return     : NULL :     No event
*              Other:     Event pointer
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
T_EVENT* Moe_Event_Get(void)
{      
    /* If there is no event */
    MOE_CHECK_IF_RET_VAL((0 == sg_u16EvtCnt), NULL, "Event count is 0\n");

    /* Get the evenet information */
    return &sg_atEvtQueue[sg_u16EvtFirst];
}

/******************************************************************************
* Name       : void Moe_Event_Remove(void)
* Function   : Remove the processed event
* Input      : None
* Output:    : None
* Return     : None
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Moe_Event_Remove(void)
{  
    uint32 u32IntSt;
        
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    sg_u16EvtFirst = (sg_u16EvtFirst + 1) % MAX_QUEUE_EVT_NUM; /* Update the position of first available event */
    sg_u16EvtCnt--;                                            /* Update the event count */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return;
}



    


#else  /* If use flexible length queue */
/******************************************************************************
* Name       : uint8 Moe_Event_Init(void)
* Function   : Init event queue
* Input      : None
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
    uint8 u8Idx,u8Return;

    /* Check if head node is empty or NOT */
    MOE_ASSERT_INFO((NULL == sg_ptEvtHead),"Moe Event should NOT inited again!!");
 
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    sg_ptEvtHead = MOE_MALLOC(sizeof(T_EVENT_QUEUE));  /* Create a space for head node */
    if(NULL == sg_ptEvtHead)   /* If malloc is failed */
    {
        u8Return = SW_ERR;
    }
    else /* If new node is created successfully */
    {
        /* Update link list head information */
        sg_ptEvtHead->ptNext = NULL;    
        sg_ptEvtHead->ptPre  = NULL;
        Moe_Memset((uint8*)(sg_ptEvtHead->atEvtQueue), 0, (MAX_QUEUE_EVT_NUM * sizeof(T_EVENT)));
        sg_u16BlkCnt++;                 /* Create the first event queue block */
        u8Return = SW_OK;
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    
    return u8Return;
}


/******************************************************************************
* Name       : uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara)
* Function   : This function is used to set event for tasks.
* Input      : uint8 u8TaskID   1~255               The task ID to receive such event
*              uint8 u8Evt      1~255               The event type
*              uint8 u8Urg      MOE_EVENT_URGENT    It is an urgent event
*                               MOE_EVENT_NORMAL    It is a normal event
*              uint8 pPara                          Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Event_Set(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara) 
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
            Moe_Event_Setting(u8Idx, u8Evt, u8Urg, pPara);
        }
        /**************************************************************************************************/
        EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
        return SW_OK;
    }

    /* Check if the task ID is invalid or NOT */
    MOE_CHECK_IF_RET_ST((u8TaskID > MAX_TASK_NUM),"Task ID should be valid\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    Moe_Event_Setting(u8TaskID, u8Evt,u8Urg);
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;
}

/******************************************************************************
* Name       : static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara)
* Function   : This function is used to set event for each tasks.
* Input      : uint8 u8TaskID   1~255               The task ID to receive such event
*              uint8 u8Evt      1~255               The event type
*              uint8 u8Urg      MOE_EVENT_URGENT    It is an urgent event
*                               MOE_EVENT_NORMAL    It is a normal event
*              uint8 pPara                          Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
static uint8 Moe_Event_Setting(uint8 u8TaskID, uint8 u8Evt, uint8 u8Urg, void *pPara)
{
    uint8  u8Idx;
    uint16 u16EvtLast;
    uint16 u16Blk,u16OffSet;
    T_EVENT_QUEUE *ptEvtQueue = sg_ptEvtHead;

    /* If the current event counter is equal to the max limit */
    MOE_CHECK_IF_RET_ST((sg_u16EvtCnt >= sg_u16EvtCntMax),"Event queue is full\n");

    /* If it is an urgent event */
    if(MOE_EVENT_URGENT == u8Urg)
    {
        if(0 == sg_u16EvtFirst)  /* If the first available data is in 0 position */
        {
            u16EvtLast = sg_u16EvtCntMax - 1;  /* Calculate the last empty position */
        }
        else  /* In other situations */
        {
            u16EvtLast = sg_u16EvtFirst - 1;   /* Calculate the last empty position */
        }
        sg_u16EvtFirst = u16EvtLast;           
    }
    else/* If it is a normal event */
    {   /* Calculate the last empty position */
        u16EvtLast = (sg_u16EvtFirst + sg_u16EvtCnt) % sg_u16EvtCntMax;
    }

    u16Blk    = u16EvtLast % MAX_QUEUE_EVT_NUM;   /* Calculate the event queue block */
    u16OffSet = u16EvtLast / MAX_QUEUE_EVT_NUM;   /* Calculate the offset in block   */

    /* Find the block to be used */
    while(u16Blk)
    {
        ptEvtQueue = ptEvtQueue->ptNext;
        u16Blk--;
    }

    ptEvtQueue->atEvtQueue[u16OffSet].pPara  = pPara;             /* Fill the parameter           */
    ptEvtQueue->atEvtQueue[u16OffSet].u8Src  = TASK_CURRENT_TASK; /* Fill the source task ID      */
    ptEvtQueue->atEvtQueue[u16OffSet].u8Task = u8TaskID;          /* Fill the destination task ID */
    ptEvtQueue->atEvtQueue[u16OffSet].u8Evt  = u8Evt;             /* Fill the evnet               */
    sg_u16EvtCnt++;                                               /* Update event count           */

    /* Create more event queue block when current entire blocks are full */
    if(sg_u16EvtCnt == sg_u16EvtCntMax)
    {   /* Try to add new event queue block */
        if(SW_ERR == Moe_Event_Queue_Block_Add())
        {
            return SW_ERR;
        }
    }

    return SW_OK;
}


/******************************************************************************
* Name       : T_EVENT* Moe_Event_Get(void)
* Function   : To get a event from quque
* Input      : None
* Output:    : None
* Return     : NULL :     No event
*              Other:     Event pointer
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
T_EVENT* Moe_Event_Get(void)
{  
    uint16 u16Blk,u16OffSet;
    T_EVENT_QUEUE *ptEvtQueue = sg_ptEvtHead;

    /* If there is no event */
    MOE_CHECK_IF_RET_VAL((0 == sg_u16EvtCnt), NULL,  "Event count is 0\n");

    u16Blk    = sg_u16EvtFirst % MAX_QUEUE_EVT_NUM;   /* Calculate the event queue block for the first available event */
    u16OffSet = sg_u16EvtFirst / MAX_QUEUE_EVT_NUM;   /* Calculate the offset in block for the first available event   */

    /* Find the block which has the fisrt available event */
    while(u16Blk)
    {
        ptEvtQueue = ptEvtQueue->ptNext;
        u16Blk--;
    }

    /* Get the Task and event */
    return &(ptEvtQueue->atEvtQueue[u16OffSet]);
}


/******************************************************************************
* Name       : void Moe_Event_Remove(void)
* Function   : Remove the processed event
* Input      : None
* Output:    : None
* Return     : None
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Moe_Event_Remove(void)
{  
    uint32 u32IntSt;
    uint16 u16Blk,u16OffSet;
    
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    sg_u16EvtFirst = (sg_u16EvtFirst + 1) % sg_u16EvtCntMax;  /* Update the position of first available event */
    sg_u16EvtCnt--;                                           /* Update the event count */

    /* If there are more then 1 event queue block */
    /* And all events are located in safe zone (The last block) */
    if((sg_u16BlkCnt > 1)\
    && (sg_u16EvtFirst > (sg_u16EvtCntMax - MAX_QUEUE_EVT_NUM))\
    && (sg_u16EvtFirst < (sg_u16EvtCntMax - (MAX_QUEUE_EVT_NUM >> 1))\
    && (sg_u16EvtCnt < (MAX_QUEUE_EVT_NUM >> 1)))
    {   

        Moe_Event_Queue_Block_Del();  /* Delete the last unused event queue block */
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return;
}


/******************************************************************************
* Name       : static uint32 Moe_Event_Queue_Block_Add(void)
* Function   : Add a new event queue block.
* Input      : None
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 8th Aug 2016
******************************************************************************/
static uint32 Moe_Event_Queue_Block_Add(void)
{
    uint8  u8Idx;
    uint16 u16Blk,u16OffSet;
    T_EVENT_QUEUE *ptFirst = sg_ptEvtHead, *ptPre, *ptAdd;

    /* Create a new event queue block */
    ptAdd = (T_EVENT_QUEUE*)MOE_MALLOC(sizeof(T_EVENT_QUEUE));
    MOE_CHECK_IF_RET_ST((NULL == ptAdd),"Malloc failed\n")!!

    u16Blk    = sg_u16EvtFirst % MAX_QUEUE_EVT_NUM;   /* Calculate the event queue block for the first available event */
    u16OffSet = sg_u16EvtFirst / MAX_QUEUE_EVT_NUM;   /* Calculate the offset in block for the first available event   */

    /* Find the block which has the fisrt available event */
    while(u16Blk)
    {
        ptFirst = ptFirst->ptNext;
        u16Blk--;
    }

    /* Copy the last events into the new event queue block */
    for(u8Idx = 0; u8Idx < u16OffSet; u8Idx++)
    {
        ptAdd->atEvtQueue[u8Idx].u8Evt  = ptFirst->atEvtQueue[u8Idx].u8Evt;
        ptAdd->atEvtQueue[u8Idx].u8Task = ptFirst->atEvtQueue[u8Idx].u8Task;
    }

    /* If the first available event is located in the first event queue block */
    if(NULL == ptFirst->ptPre)
    {   /* Set the new block as the fisrt block */
        ptFirst->ptPre = ptAdd;
        ptAdd->ptPre   = NULL;
        ptAdd->ptNex   = ptFirst;
        sg_ptEvtHead   = ptAdd;    
    }
    else
    {   /* Calculate the previous event queue block of first available event */
        ptPre          = ptFirst->ptPre;
        ptAdd->ptPre   = ptPre;
        ptAdd->ptNext  = ptFirst;
        ptPre->ptNext  = ptAdd;
        ptFirst->ptPre = ptAdd;
    }

    sg_u16BlkCnt++;
    sg_u16EvtFirst  += MAX_QUEUE_EVT_NUM;  /* Update the first available event position */
    sg_u16EvtCntMax += MAX_QUEUE_EVT_NUM;  /* Update the max number of events           */

    return SW_OK;
}

/******************************************************************************
* Name       : static void Moe_Event_Queue_Block_Del(void)
* Function   : Delete the last unused event queue block.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 8th Aug 2016
******************************************************************************/
static void Moe_Event_Queue_Block_Del(void)
{
    uint16 u16Blk,u16OffSet;
    T_EVENT_QUEUE *ptEvtQueue = sg_ptEvtHead;

    /* Delete the first block */
    ptEvtQueue->ptNext->ptPre = NULL;      
    sg_ptEvtHead = ptEvtQueue->ptNext;
    MOE_FREE(ptEvtQueue);
        
    sg_u16EvtCntMax -= MAX_QUEUE_EVT_NUM;  /* Update the max limit of event count */
    sg_u16BlkCnt--;                        /* Update the event queue block count  */
          
    return;
}

#endif /* #ifndef __FLEXIBLE_EVENT_QUEUE  */


/* end of file */


