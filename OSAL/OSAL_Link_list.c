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



/* end of file */

