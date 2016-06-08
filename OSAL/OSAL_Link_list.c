/******************************************************************************
* File       : OSAL_Link_list.c
* Function   : General link list function.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 2nd Jun 2016
* History    :  No.  When           Who           What
*               1    02/Jun/2016    Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "OSAL.h"
#include "OSAL_Link_List.h"
#include "debug.h"

/******************************************************************************
* Name       : static T_TIMER_NODE* Osal_Timer_Add()
* Function   : Add a timer node
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 2nd Jun 2016
******************************************************************************/
void* Osal_Link_List_Add(void **pptHead, void **pptTail, void* ptNode)
{
    uint32 u32IntSt;
    /* If the input node pointer is invalid  */
    if ((NULL ==  ptNode) \
     || (NULL ==  pptHead) \
     || (NULL ==  pptTail) \
     || (NULL == *pptHead) \
     || (NULL == *pptTail))                         
    {                        
        DBG_PRINT("Invalid pointer when node deteling");
        return NULL;                  /* Return NULL, no node to be added */
    }

    ptNode->ptNext = NULL;            /* Set the next node as NULL        */

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    if(NULL == *pptTail)              /* If there is NO nodes             */
    {
        *pptHead = ptNode;            /* Add new node as the fisrt one    */
        DBG_PRINT("The added node is the head one!!\n");
    }
    else                              /* If node exsits                   */
    {
        *pptTail->ptNext = ptNode;    /* Add new node after the tail one  */
        DBG_PRINT("The added node is the tail one!!\n");
    }
    *pptTail = ptNode;                /* Update the tail node             */
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */

    return ptNode;

}

/******************************************************************************
* Name       : static T_TIMER_NODE* Osal_Timer_Del(T_TIMER_NODE* ptNode)
* Function   : Delete a timer node
* Input      : T_TIMER_NODE* ptNode  The timer node to be delete.
* Output:    : None
* Return     : NULL           Fail to delete a timer.
*              T_TIMER_NODE*  The pointer of the timer which is deleted.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
void* Osal_Link_list_Del(void **pptHead, void **pptTail, void* ptNode)
{
    void* ptFind;
    uint32 u32IntSt;

    /* If the input node pointer is invalid  */
    if ((NULL ==  ptNode) \
     || (NULL ==  pptHead) \
     || (NULL ==  pptTail) \
     || (NULL == *pptHead) \
     || (NULL == *pptTail))                         
    {
        DBG_PRINT("Invalid pointer when node deteling");
        return NULL;                        /* Return NULL, no node to be deleted    */
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/

    if(ptNode == *pptHead)                      /* If the deleting node is the head node */
    {
        if(ptNode == *pptTail)                  /* And if it is the unique node          */
        {
            DBG_PRINT("The last node is deleted!!\n");
            *pptHead = NULL;                    /* Set NULL to head node                 */
            *pptTail = NULL;                    /* Set NULL to tail node                 */
        }
        else                                    /* Else if it is NOT the unique node     */
        {
            *pptHead = (*pptHead)->ptNext;      /* Make head pointing to the next node   */
        }
        OSAL_FREE(ptNode);                      /* Free the deleting node                */
        DBG_PRINT("The deleting node is free!!\n");
        return ptNode;                          
    }    
    /* Else, the deleting node is NOT the head node, then go on */

    ptFind = *pptHead;                          /* Get the head node                     */
    while (ptFind)                              /* If such node is NOT null              */
    {
        if (ptFind->ptNext == ptNode)           /* Check if the next node is the one     */
        {
            ptFind->ptNext = ptNode->ptNext;    /* Delete the node                       */
            OSAL_FREE(ptNode);                  /* Free the deleting node                */
            DBG_PRINT("The deleting node is free!!\n");
            if(NULL == ptFind->ptNext)          /* If the tail node is deleted           */
            {
                pptTail = ptFind;               /* Update the tail node                  */
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
* Name       : static T_TIMER_NODE *Osal_Timer_Find(T_TIMER_NODE* ptNode)
* Function   : Try to find a node.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be found
* Output:    : None
* Return     : NULL           Fail to find the node.
*              T_TIMER_NODE*  The pointer of the founed node.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
void *Osal_Link_list_Find(void **pptHead, uint16 u16OffSet, uint8 u8Size,void Node, void **pptPre)
{
    void  *ptFind;
    uint8  u8Idx,u8Flag = 1;

    /* If the input node pointer is invalid  */
    if ((NULL == *pptHead) || (NULL == pptHead))                         
    {
        DBG_PRINT("Invalid pointer when node deteling");
        return NULL;                 /* Return NULL, no node to be deleted    */
    }

    if(NULL != pptPre)
    {
        *pptPre = NULL;
    }
    ptFind = *pptHead;                /* Get the head node of timers          */
    while(ptFind)                     /* If such node is avaliable            */
    {                   
        for(u8Idx = 0; u8Idx < u8Size; u8Idx++)
        {
            if(*((uint8*)ptFind+u16OffSet+u8Idx) != (uint8)(Node >>(u8Idx * 8)))
            {
                u8Flag = 0;
                break
            }
        }
                  
        if(0 == u8Flag)          /* And if it is the searched node       */
        {
            DBG_PRINT("Find the node!!\n");
            break;                    /* Find it and break the loop           */
        }
        if(NULL != pptPre)
        {
            *pptPre = ptFind;
        }
        ptFind = ptFind->ptNext;      /* Update the node pointer              */
    }
    return ptFind;
}

/******************************************************************************
* Name       : uint16 Osal_Timer_Cnt()
* Function   : Get the count of timers
* Input      : None
* Output:    : None
* Return     : uint16   The count of timers
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint16 Osal_Link_list_Cnt(void **pptHead)
{
    T_TIMER_NODE *ptFind;
    uint16 u16Cnt = 0;
    uint32 u32IntSt;

    /* If the input node pointer is invalid  */
    if ((NULL ==  pptHead) || (NULL == *pptHead))                         
    {
        DBG_PRINT("Invalid pointer when node deteling");
        return NULL;                        /* Return NULL, no node to be deleted    */
    }

    ENTER_CRITICAL_ZONE(u32IntSt);  /* Enter the critical zone to prevent event updating unexpectedly */
    /**************************************************************************************************/
    ptFind = *pptHead;              /* Get the head timer         */
    while(ptFind)                   /* If such timer is avaliable */
    {
        u16Cnt++;                   /* Increase the count         */
        ptFind = ptFind->ptNext;    /* Check the next one         */
    }
    /**************************************************************************************************/
    EXIT_CRITICAL_ZONE(u32IntSt);   /* Exit the critical zone                                         */
    DBG_PRINT("The count of the Nodes is %d\n",u16Cnt);
    return u16Cnt;
}


/* end of file */

