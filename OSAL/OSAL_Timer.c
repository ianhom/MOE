/******************************************************************************
* File       : OSAL_Timer.c
* Function   : Provide timer service.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
* History    :  No.  When           Who           What
*               1    06/May/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "OSAL.h"
#include "OSAL_Timer.h"

static T_TIMER_NODE *sg_ptTmHead = NULL;
static T_TIMER_NODE *sg_ptTmTail = NULL;

static PF_TIMER_SRC  sg_pfSysTm  = NULL;



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
uint8 Osal_Timer_Init(PF_TIMER_SRC pfSysTm)
{   /* Check if the input function is NULL or NOT */
    if (NULL == pfSysTm)
    {   /* If invalid, return error */
        return SW_ERR;    
    }
    /* If the input function is OK, then go on */

    sg_pfSysTm = pfSysTm;      /* Save the system time function for further using */

    return SW_OK;
}

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
T_TIMER_NODE* Osal_Timer_Add()
{
    T_TIMER_NODE* ptNode;

    /* 链表头结点已经存在 */
    ptNode = (T_TIMER_NODE*)malloc(sizeof(T_TIMER_NODE)); /* 申请定时器结点 */
    if (NULL == ptNode)
    {
        return NULL; /* 检查是否申请成功 */
    }

    /* 结点申请成功 */
    ptNode->next              = NULL;                   /* 下个结点地址置空 */

    if(NULL == sg_ptTmTail)
    {
        sg_ptTmHead = ptNode;
    }
    else
    {
        sg_ptTmTail->Next = ptNode;
    }
    sg_ptTmTail = ptNode;

    return ptNode;

}


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
T_TIMER_NODE* Osal_Timer_Start(uint8 u8TaskID, uint16 u16Evt, uint16 u16Cnt, uint16 u16TmOut)
{
    T_TIMER_NODE* ptNode;

    ptNode = Osal_Timer_Add();
    if (NULL == ptNode)
    {
        return NULL; /* 检查是否申请成功 */
    }

    /* 结点申请成功 */
    ptNode->tTimer.u16TmStart = sg_pfSysTm();           /* 获取计时起始时间 */
    ptNode->tTimer.u16TmNow   = sg_pfSysTm();           /* 获取当前时间 */
    ptNode->tTimer.u16TmOut   = u16TmOut;                      /* 已经过的时间 */
    ptNode->tTimer.u8Cnt      = u16Cnt;
    ptNode->tTimer.u16Evt     = u16Evt;
    ptNode->tTimer.u8TaskID   = u8TaskID;

    return ptNode;

}


/*************************************************************************
* 函数名称：int KillTimer(T_TIMER_NODE* ptNode)
* 功能说明：删除定时器结点
* 输入参数：T_TIMER_NODE* ptNode 定时器结点地址
* 输出参数：无
* 返 回 值：SW_ERR: 操作失败
           SW_OK 操作成功
* 其它说明：无
**************************************************************************/
T_TIMER_NODE* Osal_Timer_Del(T_TIMER_NODE* ptNode)
{
    T_TIMER_NODE* ptFind;

    if (NULL == ptNode)
    {
        return NULL; /* 检查定时器结点是否为空 */
    }

    if(ptNode == sg_ptTmHead)
    {
        if(ptNode == sg_ptTmTail)
        {
            sg_ptTmHead = NULL;
            sg_ptTmTail = NULL;
        }
        else
        {
            sg_ptTmHead = sg_ptTmHead->ptNext;
        }
        free(ptNode);
        return ptNode;
    }    

    ptFind = sg_ptTmHead; /* 先找到头结点 */
    while (ptFind) /* 如果不是末尾结点 */
    {
        if (ptFind->next == ptNode)      /* 检查下一结点是否为需删除结点 */
        {
            ptFind->next = ptNode->next; /* 重新链接上下结点 */
            free(ptNode);                /* 删除结点 */
            if(NULL == ptFind->next)
            {
                sg_ptTmTail = ptFind;
            }
            return SW_OK;                /* 操作成功，退出程序 */
        }
        ptFind = ptFind->next;           /* 继续查找下一结点 */
    }
    return NULL;                     /* 未找到，操作失败 */
}


T_TIMER_NODE* Osal_Timer_Find(T_TIMER_NODE* ptNode)
{
    T_TIMER_NODE *ptFind = sg_ptTmHead;

    while(ptFind)
    {
        if(ptFind == ptNode)
        {
            break;
        }
        ptFind = ptFind->ptNext;
    }
    return ptFind;
}


/*************************************************************************
* 函数名称：int ResetTimer(T_TIMER_NODE* ptNode)
* 功能说明：重启定时器结点
* 输入参数：T_TIMER_NODE* ptNode 定时器结点地址
* 输出参数：无
* 返 回 值：SW_ERR: 操作失败
           SW_OK 操作成功
* 其它说明：无
**************************************************************************/
T_TIMER_NODE* Osal_Timer_Restart(T_TIMER_NODE* ptNode)
{
    if (NULL == ptNode)
    {
        return NULL;                /* 检查定时器结点是否为空 */
    }

    if(NULL == Osal_Timer_Find())
    {
        return NULL;
    }

    ptNode->tTimer.start = sg_pfSysTm(); /* 更新定时器起始时间 */
    return ptNode;                       /* 操作成功 */
}


/*************************************************************************
* 函数名称：int ProcessTimer(void)
* 功能说明：更新定时器结点
* 输入参数：无
* 输出参数：无
* 返 回 值：SW_ERR: 操作失败
            SW_OK 操作成功
* 其它说明：无
**************************************************************************/
uint8 Osal_Timer_Process(void)
{
    T_TIMER_NODE* ptFind;
    T_TIMER_NODE* ptNodeFree;
    if (NULL == sg_ptTmHead)
    {
        return SW_OK; /* 没有定时器需要运行 */
    }
    ptFind = sg_ptTmHead;          /* 找到第一个有效结点 */
    while(ptFind)                         /* 如果不是末尾结点 */
    {
        ptFind->tTimer.now = sg_pfSysTm(); /* 更新时间 */

        /* 计算此刻时间与起始时间的时间差 */    
        if((ptFind->tTimer.now - ptFind->tTimer.start) >= ptFind->tTimer.timeout)          /* 如果时差大于等于设定的计时时间 */
        {
            Osal_Event_Set(ptFind->tTimer.u8TaskID,ptFind->tTimer.u16Evt);

            if(ptFind->tTimer.u16Cnt)
            {
                if(ptFind->tTimer.u16Cnt != FOREVER_PERIOD)
                {
                    ptFind->tTimer.u16Cnt--;
                }
                
                Osal_Timer_Restart(ptFind);                              /* 如果是周期性触发，重启定时器 */
            }
            else
            {                                                    /* 如果是单次触发，删除定时器 */
                ptNodeFree = ptFind;
                ptFind = ptFind->next;
                Osal_Timer_Del(ptNodeFree);
                continue;
            }            
        }
        ptFind = ptFind->next;                                   /* 继续更新下一个定时器结点 */
    }
    return SW_OK;                                                /* 操作成功 */
}

/* end of file */

