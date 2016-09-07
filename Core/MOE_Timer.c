/******************************************************************************
* File       : MOE_Timer.c
* Function   : Provide timer services.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
* History    :  No.  When           Who           What
*               1    06/May/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "MOE_Core.h"
#include "MOE_Timer.h"
#include "debug.h"
#include "MOE_Event.h"

static void Moe_Timer_Time_Up(T_TIMER_NODE *ptFind);
static void Moe_Timer_Update_Left_Time(uint32 *pu32TmDiff);
static T_TIMER_NODE* Moe_Timer_Add(void);
static T_TIMER_NODE* Moe_Timer_Find(T_TIMER_NODE *ptNode);
static T_TIMER_NODE* Moe_Timer_Del(T_TIMER_NODE *ptNode);
static uint16 Moe_Timer_Test_Max_Cnt(void);
static uint8  Moe_Timer_Test_StartStop(void);


static T_TIMER_NODE *sg_ptTmHead = NULL;               /* Head node of timer link list                 */
static T_TIMER_NODE *sg_ptTmTail = NULL;               /* Tail node of timer link list                 */

static uint32 sg_u32TmDiff = 0;                        /* Time difference between all left time update */
static uint32 sg_u32OldTm  = 0;                        /* Old time of last comming left time update    */
static uint32 sg_u32Coming = 0xFFFFFFFF;               /* The left time of the comming timer           */
static uint8  sg_u8DelReq  = MOE_TIMER_DEL_REQ_NONE;   /* Flag for timer node deleting                 */

static PF_TIMER_SRC  sg_pfSysTm  = NULL;               /* Function of system timer                     */

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
uint8 Moe_Timer_Init(PF_TIMER_SRC pfSysTm)
{   /* Check if the input function is NULL or NOT */ 
    MOE_ASSERT_INFO((NULL != pfSysTm), "System time function pointer is invalid!!")
    /* If the input function is OK, then go on */

    sg_pfSysTm  = pfSysTm;      /* Save the system time function for further using */
    sg_u32OldTm = sg_pfSysTm();
    DBG_PRINT("MOE timer inited successfully!!\n");   
 
    return SW_OK;
}

/******************************************************************************
* Name       : static T_TIMER_NODE* Moe_Timer_Add(void)
* Function   : Add a timer node
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
static T_TIMER_NODE* Moe_Timer_Add(void)
{
    T_TIMER_NODE* ptNode;

    ptNode = (T_TIMER_NODE*)MOE_MALLOC(sizeof(T_TIMER_NODE)); /* Allocate a timer node */
    /* If the allocation is FAILED */
    MOE_CHECK_IF_RET_VAL((NULL == ptNode), NULL, "No more heap space for timer node!!\n");
    /* Else, new timer node is allocated */

    /* Update all left time before new timer node is added */
    Moe_Timer_Update_Left_Time(&sg_u32TmDiff);

    ptNode->ptNext = NULL;               /* Set the next node as NULL       */

    if(NULL == sg_ptTmTail)              /* If there is NO nodes            */
    {
        sg_ptTmHead = ptNode;            /* Add new node as the fisrt one   */
    }
    else                                 /* If node exsits                  */
    {
        sg_ptTmTail->ptNext = ptNode;    /* Add new node after the tail one */
    }
    sg_ptTmTail = ptNode;                /* Update the tail node            */

    return ptNode;

}

/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Periodic(uint32 u32TmOut)
* Function   : Start a timer for current task and set "EVENT_DELAY"
* Input      : uint32 u32TmOut   0~2^32   Time out in ms
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jun 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Periodic(uint32 u32TmOut)
{
    T_TIMER tTmr;

    tTmr.u16Cnt       = MOE_TMR_INFINITE_CNT;   /* Infinite count  */
    tTmr.u8Evt        = EVENT_PERIODIC;         /* Periodic event  */
    tTmr.u8TaskID     = TASK_CURRENT_TASK;      /* Call itself     */
    tTmr.u32TmOut     = u32TmOut;               /* Set time out    */
#ifdef __TIMER_CALLBACK_SUPPORTED
    tTmr.pfTmCallback = NULL;                   /* Callback        */
    tTmr.pPara        = NULL;                   /* Prarmeters      */
#endif

    return (Moe_Timer_Start(&tTmr));            /* Start the timer */
}


/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Delay(uint32 u32TmOut)
* Function   : Start a timer for current task and set "EVENT_DELAY"
* Input      : uint32 u32TmOut   0~2^32   Time out in ms
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jun 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Delay(uint32 u32TmOut)
{
    T_TIMER tTmr;

    tTmr.u16Cnt       = 1;                 /* Just once       */
    tTmr.u8Evt        = EVENT_DELAY;       /* Delay event     */
    tTmr.u8TaskID     = TASK_CURRENT_TASK; /* Call itself     */
    tTmr.u32TmOut     = u32TmOut;          /* Set time out    */
#ifdef __TIMER_CALLBACK_SUPPORTED
    tTmr.pfTmCallback = NULL;              /* Callback        */
    tTmr.pPara        = NULL;              /* Prarmeters      */
#endif

    return (Moe_Timer_Start(&tTmr));       /* Start the timer */
}

/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Easy_Start(uint8 u8DesTask, uint8 u8Evt,uint32 u32TmOut)
* Function   : Start a timer for current task and set "EVENT_DELAY"
* Input      : uint8 u8DesTask   1~254    The destination task ID
*              uint8 u8Evt       0~255    The event which will be create when time is up.
*              uint32 u32TmOut   0~2^32   Time out in ms
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 23rd Jun 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Easy_Start(uint8 u8DesTask, uint8 u8Evt,uint32 u32TmOut)
{
    T_TIMER tTmr;

    tTmr.u16Cnt       = 1;           /* Just once            */
    tTmr.u8Evt        = u8Evt;       /* Set time up event    */
    tTmr.u8TaskID     = u8DesTask;   /* Set destination task */
    tTmr.u32TmOut     = u32TmOut;    /* Set time out         */
#ifdef __TIMER_CALLBACK_SUPPORTED
    tTmr.pfTmCallback = NULL;        /* Callback             */
    tTmr.pPara        = NULL;        /* Prarmeters           */
#endif

    return (Moe_Timer_Start(&tTmr)); /* Start the timer      */
}


/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Start(uint8 u8TaskID, uint8 u8Evt, uint16 u16Cnt, uint32 u32TmOut)
* Function   : Start a timer
* Input      : T_TIMER *ptTm     Pointer of timers set by user.
* Output:    : None
* Return     : NULL           Fail to start a timer.
*              T_TIMER_NODE*  The pointer of the timer which is started.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Start(T_TIMER *ptTm)
{
    T_TIMER_NODE* ptNode;
    uint32 u32IntSt;

    MOE_CHECK_IF_RET_VAL(((NULL == ptTm) || (0 == ptTm->u16Cnt)), NULL ,"Invalid timer info\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptNode = Moe_Timer_Add();                             /* Allocate a timer node              */    
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    MOE_CHECK_IF_RET_VAL((NULL == ptNode), NULL,"New timer node is failed to start\n")

    /* A timer node was added successfully */        
    ptNode->tTimer.u32TmOut     = ptTm->u32TmOut;         /* Set the timeout time               */    
    ptNode->tTimer.u32TmLeft    = ptTm->u32TmOut;         /* Set the timeout time               */
    ptNode->tTimer.u16Cnt       = ptTm->u16Cnt;           /* Set the restart count              */
    ptNode->tTimer.u8Evt        = ptTm->u8Evt;            /* Set the event                      */
    ptNode->tTimer.u8TaskID     = ptTm->u8TaskID;         /* Set the task ID                    */
#ifdef __TIMER_CALLBACK_SUPPORTED
    ptNode->tTimer.pfTmCallback = ptTm->pfTmCallback;     /* Set the callback function          */
    /* If the parameter is NULL */
    if(NULL == ptTm->pPara)                               
    {
        ptNode->tTimer.pPara    = (void*)ptNode;          /* If the parameter is NULL           */
    }
    else
    {
        ptNode->tTimer.pPara    = ptTm->pPara;            /* Set the parameter of callback      */
    }
#endif

    /* Update the comming left time */
    if(ptTm->u32TmOut <= sg_u32Coming)
    {
        sg_u32Coming = ptTm->u32TmOut;
    }

    DBG_PRINT("New timer is started!!\n");

    return ptNode;

}

/******************************************************************************
* Name       : static void Moe_Timer_Update_Left_Time(uint32 *pu32TmDiff)
* Function   : Start a timer
* Input      : uint32 *pu32TmDiff     The pointer of time difference bewteen all left time update
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th Aug 2016
******************************************************************************/
static void Moe_Timer_Update_Left_Time(uint32 *pu32TmDiff)
{
    uint32 u32IntSt;
    uint32 u32TmDiff = *pu32TmDiff;
    T_TIMER_NODE* ptNode = sg_ptTmHead;
    
    MOE_CHECK_IF_RET_VOID((0 == *pu32TmDiff),"Unnecessary to update!!\n");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    *pu32TmDiff = 0;  /* Reset time difference between all left time update */
    while(ptNode)
    {
        if(ptNode->tTimer.u32TmLeft > u32TmDiff)           /* If time is NOT up     */
        {
            ptNode->tTimer.u32TmLeft -= u32TmDiff;         /* Update the left time  */

            /* Update the comming left time */
            if(ptNode->tTimer.u32TmLeft <= sg_u32Coming)
            {
                sg_u32Coming = ptNode->tTimer.u32TmLeft;
            }
        }
        else                                               /* If time is up         */
        {
            ptNode->tTimer.u32TmLeft = 0;                  /* Set left time as 0    */
            Moe_Timer_Time_Up(ptNode);                     /* Call time up process  */
        }
        
        ptNode = ptNode->ptNext;                           /* Check next timer node */
    }    
    
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return;
}


/******************************************************************************
* Name       : static T_TIMER_NODE* Moe_Timer_Del(T_TIMER_NODE *ptNode)
* Function   : Delete a timer node
* Input      : T_TIMER_NODE *ptNode  The timer node to be delete.
* Output:    : None
* Return     : NULL           Fail to delete a timer.
*              T_TIMER_NODE*  The pointer of the timer which is deleted.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
static T_TIMER_NODE* Moe_Timer_Del(T_TIMER_NODE *ptNode)
{
    T_TIMER_NODE* ptFind;

    uint32 u32IntSt;

    MOE_CHECK_IF_RET_VAL((NULL == ptNode), NULL, "Invalid pointer");

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/

    if(ptNode == sg_ptTmHead)                   /* If the deleting node is the head node */
    {
        if(ptNode == sg_ptTmTail)               /* And if it is the unique node          */
        {
            DBG_PRINT("The last timer node is deleted!!\n");
            sg_ptTmHead = NULL;                 /* Set NULL to head node                 */
            sg_ptTmTail = NULL;                 /* Set NULL to tail node                 */
        }
        else                                    /* Else if it is NOT the unique node     */
        {
            sg_ptTmHead = sg_ptTmHead->ptNext;  /* Make head pointing to the next node   */
        }
        MOE_FREE(ptNode);                       /* Free the deleting node                */
        DBG_PRINT("The deleting node is free!!\n");
        return ptNode;                          
    }    
    /* Else, the deleting node is NOT the head node, then go on */

    ptFind = sg_ptTmHead;                       /* Get the head node                     */
    while (ptFind)                              /* If such node is NOT null              */
    {
        if (ptFind->ptNext == ptNode)           /* Check if the next node is the one     */
        {
            ptFind->ptNext = ptNode->ptNext;    /* Delete the node                       */
            MOE_FREE(ptNode);                   /* Free the deleting node                */
            DBG_PRINT("The deleting node is free!!\n");
            if(NULL == ptFind->ptNext)          /* If the tail node is deleted           */
            {
                sg_ptTmTail = ptFind;           /* Update the tail node                  */
            }
            return ptFind;                      /* Return the deteled node pointer       */
        }
        ptFind = ptFind->ptNext;                /* Update the searching node             */
    }

    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return NULL;                    /* Have NOT found the done */
}


/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Stop(T_TIMER_NODE *ptNode)
* Function   : Stop a started timer.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be stopped
* Output:    : None
* Return     : NULL           Fail to stop a timer.
*              T_TIMER_NODE*  The pointer of the timer which is stopped.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Stop(T_TIMER_NODE *ptNode)
{
    T_TIMER_NODE* ptFind;

    uint32 u32IntSt;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptFind = Moe_Timer_Find(ptNode);      /* Search the timer node    */    
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    MOE_CHECK_IF_RET_VAL((NULL == ptFind), NULL,"The timer node to be stopped is NOT found!!\n");

    /* Else, the timer node is found */
    ptNode->tTimer.u16Cnt = 0;            /* Set the count as 0       */
    sg_u8DelReq = MOE_TIMER_DEL_REQ;      /* Set flag indicating that it is necessary to delete time node */

    DBG_PRINT("Timer is stopped!!\n");
    return ptNode;
}


/******************************************************************************
* Name       : static T_TIMER_NODE* Moe_Timer_Find(T_TIMER_NODE *ptNode)
* Function   : Try to find a node.
* Input      : T_TIMER_NODE *ptNode  The pointer of node to be found
* Output:    : None
* Return     : NULL           Fail to find the node.
*              T_TIMER_NODE*  The pointer of the founed node.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
static T_TIMER_NODE* Moe_Timer_Find(T_TIMER_NODE *ptNode)
{
    T_TIMER_NODE *ptFind;
    
    ptFind = sg_ptTmHead;             /* Get the head node of timers          */
    while(ptFind)                     /* If such node is avaliable            */
    {                                
        if(ptFind == ptNode)          /* And if it is the searched node       */
        {
            DBG_PRINT("Find the timer node!!\n");
            break;                    /* Find it and break the loop           */
        }
        ptFind = ptFind->ptNext;      /* Update the node pointer              */
    }
    return ptFind;
}

/******************************************************************************
* Name       : T_TIMER_NODE* Moe_Timer_Restart(T_TIMER_NODE *ptNode)
* Function   : Try to restart a timer.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be restarted
* Output:    : None
* Return     : NULL           Fail to find the node.
*              T_TIMER_NODE*  The pointer of the founed node.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
T_TIMER_NODE* Moe_Timer_Restart(T_TIMER_NODE *ptNode)
{
    T_TIMER_NODE *ptFind;
    uint32 u32IntSt;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptFind = Moe_Timer_Find(ptNode);           /* Search the timer node    */    
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    MOE_CHECK_IF_RET_VAL((NULL == ptFind), NULL, "The timer node to be restarted is NOT found!!\n");

    /* Else, the timer node is found */
    Moe_Timer_Update_Left_Time(&sg_u32TmDiff);           /* Update all left time first */
    ptNode->tTimer.u32TmLeft = ptNode->tTimer.u32TmOut;  /* Reset the left time        */

    /* Update the comming left time */
    if(ptNode->tTimer.u32TmLeft <= sg_u32Coming)
    {
        sg_u32Coming = ptNode->tTimer.u32TmLeft;
    }
    
    DBG_PRINT("Timer is restarted!!\n");
    return ptNode;                      
}


/******************************************************************************
* Name       : static void Moe_Timer_Time_Up(T_TIMER_NODE *ptFind)
* Function   : Process when time is up.
* Input      : T_TIMER_NODE *ptFind  The pointer of time up node
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 25th Aug 2016
******************************************************************************/
static void Moe_Timer_Time_Up(T_TIMER_NODE *ptFind)
{   
    /* Set the desired evnet */
    Moe_Event_Set(ptFind->tTimer.u8TaskID,ptFind->tTimer.u8Evt,MOE_EVENT_NORMAL, NULL);  
    DBG_PRINT("Time is up, Task %d has a 0x%x type event\n",ptFind->tTimer.u8TaskID,ptFind->tTimer.u8Evt);
#ifdef __TIMER_CALLBACK_SUPPORTED
    if (NULL != ptFind->tTimer.pfTmCallback)                /* If we have callback for such timer */
    {
        ptFind->tTimer.pfTmCallback(ptFind->tTimer.pPara);  /* Call the callback function         */
    }
#endif
 
    /* If the it is NOT infinite count */
    if(ptFind->tTimer.u16Cnt != MOE_TMR_INFINITE_CNT)              
    {
        ptFind->tTimer.u16Cnt--;     /* Update the count     */
    }
    /* If the timing count is NOT 0 */
    if(ptFind->tTimer.u16Cnt)
    {
        DBG_PRINT("Timer is restarted, %d times left\n",ptFind->tTimer.u16Cnt);
        Moe_Timer_Restart(ptFind);   /* Restart the timer    */   
    }
    else/* If the timing count is 0 */
    {
        sg_u8DelReq = MOE_TIMER_DEL_REQ;  /* Set flag indicating that is is necessary to delete timer node */
    }
    return;
}


/******************************************************************************
* Name       : uint8 Moe_Timer_Process(void)
* Function   : Main process for timer updating.
* Input      : None
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint8 Moe_Timer_Process(void)
{
    T_TIMER_NODE* ptFind = sg_ptTmHead;
    T_TIMER_NODE* ptNodeFree;
    
    uint32 u32IntSt;
    uint32 u32TmDiff = sg_pfSysTm() - sg_u32OldTm;   /* Get the time difference */

    sg_u32OldTm  += u32TmDiff;  /* Update the old time                                     */
    sg_u32TmDiff += u32TmDiff;  /* Update the time difference bewteen all left time update */

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    if(MOE_TIMER_DEL_REQ == sg_u8DelReq)            /* If the deleting flag is set */
    {
        sg_u8DelReq = MOE_TIMER_DEL_REQ_NONE;       /* Clear the flag              */
        while(ptFind)
        {
            if(0 == ptFind->tTimer.u16Cnt)          /* If the timing count is 0    */
            {                                     
                ptNodeFree = ptFind;                /* Get the deleting timer      */
                ptFind = ptFind->ptNext;            /* Point the next timer        */
                Moe_Timer_Del(ptNodeFree);          /* Delete the timer            */
                continue;                           /* Go on check next timer      */
            }
            ptFind = ptFind->ptNext;
        }
    }
    
    if(sg_u32Coming > u32TmDiff)                    /* If the comming left time is NOT up */
    {
        sg_u32Coming -= u32TmDiff;                  /* Update the comming left time       */
    }
    else                                            /* If the comming left time is up     */
    {
        sg_u32Coming  = 0xFFFFFFFF;                 /* Reset comming left time            */
        Moe_Timer_Update_Left_Time(&sg_u32TmDiff);  /* Update all left time               */
    }
    
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return SW_OK;                                               
}

/******************************************************************************
* Name       : uint16 Moe_Timer_Cnt(void)
* Function   : Get the count of timers
* Input      : None
* Output:    : None
* Return     : uint16   The count of timers
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint16 Moe_Timer_Cnt(void)
{
    T_TIMER_NODE *ptFind;
    uint16 u16TmrCnt = 0;

    uint32 u32IntSt;

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptFind = sg_ptTmHead;           /* Get the head timer         */
    while(ptFind)                   /* If such timer is avaliable */
    {
        u16TmrCnt++;                /* Increase the count         */
        ptFind = ptFind->ptNext;    /* Check the next one         */
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    DBG_PRINT("The count of the timer is %d\n",u16TmrCnt);
    return u16TmrCnt;
}

/******************************************************************************
* Name       : static uint16 Moe_Timer_Test_Max_Cnt(void)
* Function   : Get the Max. count of timers
* Input      : None
* Output:    : None
* Return     : uint16   The Max. count of timers
* description: Warning: This test function is just show how many timers can be 
*              allocated in heap space. It will run out all heap space and free
*              all of them after about 100ms.
*              **IT IS A TEST FUNCTION! DO NOT USE IT IN YOUR APPLICATION!**
* Version    : V1.00
* Author     : Ian
* Date       : 9th May 2016
******************************************************************************/
static uint16 Moe_Timer_Test_Max_Cnt(void)
{
    uint16 u16Idx;
    uint32 u32IntSt;

    T_TIMER_NODE *ptNode = (T_TIMER_NODE*)(&sg_ptTmHead); /* Make it a non-NULL value       */

    T_TIMER tTm;
    /* Set time parameter */
    tTm.u8TaskID = 0;
    tTm.u8Evt    = 0;
    tTm.u16Cnt   = 1;
    tTm.u32TmOut = 10;

    DBG_PRINT("**IT IS A TEST FUNCTION! DO NOT USE IT IN YOUR APPLICATION!**\n");
    DBG_PRINT("Warning: This test function is just show how many timers can be allocated in heap space.\n");
    
    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/    
    /* Check how many timers can be added */
    for (u16Idx = 0; ptNode != NULL ; u16Idx++)
    {
        ptNode = Moe_Timer_Start(&tTm);                   /* Set 10ms timeout for each timer */
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    DBG_PRINT("Max timer count is %d, Heap is full currently, please wait 100ms for heap free operation!!\n",u16Idx);
    return u16Idx;
}

/******************************************************************************
* Name       : static uint8 Moe_Timer_Test_StartStop(void)
* Function   : Test start and stop function
* Input      : None
* Output:    : None
* Return     : To be done
* description: To be done.
*              **IT IS A TEST FUNCTION! DO NOT USE IT IN YOUR APPLICATION!**
* Version    : V1.00
* Author     : Ian
* Date       : 9th May 2016
******************************************************************************/
static uint8 Moe_Timer_Test_StartStop(void)
{
    T_TIMER_NODE *ptNode;

    T_TIMER tTm;
    /* Set time parameter */
    tTm.u8TaskID = 0;
    tTm.u8Evt    = 0;
    tTm.u16Cnt   = 1;
    tTm.u32TmOut = 10;

    DBG_PRINT("Try to start timer for 10ms\n"); 
    ptNode = Moe_Timer_Start(&tTm);                     /* Start a timer               */
    MOE_CHECK_IF_RET_ST((NULL == ptNode), "Failed to start a timer!!\n");
    DBG_PRINT("The time is started successfully\n");

    /* Find the started timer */
    if(Moe_Timer_Find(ptNode) == ptNode)
    {
        DBG_PRINT("The started timer is found in the timer talbe.\n");
    }
    else
    {
        DBG_PRINT("The started timer is NOT found!!\n");
        return SW_ERR;
    }

    DBG_PRINT("Try to stop the timer\n"); 
    ptNode = Moe_Timer_Stop(ptNode);                    /* Stop the timer              */
    MOE_CHECK_IF_RET_ST((NULL == ptNode), "Failed to stop a timer!!\n");

    DBG_PRINT("The time is stopped successfully\n");
    
    Moe_Timer_Process();                                /* To delete the stopped timer */

    DBG_PRINT("Try to start another timer for 5000ms\n"); 
    tTm.u32TmOut = 5000;
    ptNode = Moe_Timer_Start(&tTm);                     /* Start a timer               */

    MOE_CHECK_IF_RET_ST((NULL == ptNode),"Failed to start a timer!!\n");

    DBG_PRINT("The time is started successfully\n");

    DBG_PRINT("Wait a time up message after 5000ms\n");
    while(NULL != sg_ptTmHead)
    {
        Moe_Timer_Process();                            /* Wait for time up            */
    }
    DBG_PRINT("Time up!! Is it a 5000ms delay?\n");

    DBG_PRINT("Try to stopped a deleted timer\n");
    ptNode = Moe_Timer_Stop(ptNode);                    /* Stop the timer              */
    if(NULL == ptNode)                                  /* Check if successful or NOT  */
    {
        DBG_PRINT("Failed to stop a timer!!\n");
    } 

    DBG_PRINT("Start a 10-times 1 second timer!!\n");
    tTm.u32TmOut = 1000;
    ptNode = Moe_Timer_Start(&tTm);                     /* Start a timer               */
    MOE_CHECK_IF_RET_ST((NULL == ptNode), "Failed to start a timer!!\n");
    if(NULL == ptNode)                                  /* Check if successful or NOT  */

    while(NULL != sg_ptTmHead)
    {
        Moe_Timer_Process();                            /* Wait for time up            */
    }
    DBG_PRINT("General test for timer is finished!\n");

    return SW_OK;
}

/******************************************************************************
* Name       : void Moe_Timer_Test_General(void)
* Function   : General test
* Input      : None
* Output:    : None
* Return     : None
* description: To be done
*              **IT IS A TEST FUNCTION! DO NOT USE IT IN YOUR APPLICATION!**
* Version    : V1.00
* Author     : Ian
* Date       : 9th May 2016
******************************************************************************/
void Moe_Timer_Test_General(void)
{
    Moe_Timer_Cnt();               /* Get the current timer count          */
    Moe_Timer_Test_Max_Cnt();      /* Check how many timers can be created */
    while(NULL != sg_ptTmHead)     /* Wait all timers timeout              */
    {
        Moe_Timer_Process();       /* Process all timers                   */
    }

    Moe_Timer_Cnt();               /* Get the current timer count          */

    Moe_Timer_Test_StartStop();    /* Test the start & stop function       */
    return;
}
/* end of file */


