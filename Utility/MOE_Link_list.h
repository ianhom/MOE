/*/******************************************************************************
* File       : MOE_Link_list.h
* Function   : General link list function.
* Description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 2nd Jun 2016
* History    :  No.  When           Who           What
*               1    02/Jun/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_LINK_LIST_H_
#define _MOE_LINK_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_LINK_LIST                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_LINK_LIST     /* According the set from project_config.h */
#endif

/******************************************************************************
* Name       : static T_TIMER_NODE* Moe_Timer_Add()
* Function   : Add a timer node
* Input      : PF_TIMER_SRC pfSysTm   Funtion which returns system time
* Output:    : None
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 2nd Jun 2016
******************************************************************************/
void* Moe_Link_List_Add(void **pptHead, void **pptTail, void* ptNode);



/******************************************************************************
* Name       : static T_TIMER_NODE* Moe_Timer_Del(T_TIMER_NODE* ptNode)
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
void* Moe_Link_list_Del(void **pptHead, void **pptTail, void* ptNode);


/******************************************************************************
* Name       : static T_TIMER_NODE *Moe_Timer_Find(T_TIMER_NODE* ptNode)
* Function   : Try to find a node.
* Input      : T_TIMER_NODE* ptNode  The pointer of node to be found
* Output:    : None
* Return     : NULL           Fail to find the node.
*              T_TIMER_NODE*  The pointer of the founed node.
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
void *Moe_Link_list_Find(void **pptHead, uint16 u16OffSet, uint8 u8Size,uint8 u8Node, void **pptPre);


/******************************************************************************
* Name       : uint16 Moe_Timer_Cnt()
* Function   : Get the count of timers
* Input      : None
* Output:    : None
* Return     : uint16   The count of timers
* Description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 6th May 2016
******************************************************************************/
uint16 Moe_Link_list_Cnt(void **pptHead);




 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_LINK_LIST_H_ */

/* End of file */

