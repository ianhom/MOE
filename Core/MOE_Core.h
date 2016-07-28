/******************************************************************************
* File       : MOE.h
* Function   : Provide the main function of MOE-like scheduler.
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 29th Apr 2016
* History    :  No.  When           Who           What
*               1    29/Apr/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_H_
#define _MOE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE            /* According the set from project_config.h */
#endif

#define MOE_VERSION       "MOE V0.11"

/* Malloc MACRO */ 
#if (__MALLOC_OPTION != __MALLOC_MY)
#if (__MALLOC_OPTION == __MALLOC_MOE)
#define MOE_MALLOC(size)      Moe_Malloc(size)
#define MOE_FREE(p)           Moe_Free(p)
#else
#define MOE_MALLOC(size)      malloc(size)
#define MOE_FREE(p)           free(p)
#endif
#endif

typedef void* (*PF_MALLOC)(uint32 u32Size);
typedef void (*PF_FREE)(void *p);
typedef void (*PF_POLL)(void);

#ifndef PF_TIMER_SRC
#define PF_TIMER_SRC PF_TIMER_SRC
typedef uint32 (*PF_TIMER_SRC)(void);
#endif


/* MOE MACRO */
#define TASK_NO_TASK                (0x00)                    /* Task number which means there is no task */
#define TASK_ALL_TASK               (0xFF)                    /* Task number which means all tasks        */
#define TASK_FIRST_TASK             (0x01)                    /* Task number of the first one             */
#define TASK_LAST_TASK              MAX_TASK_NUM              /* Task number of the last one              */
#define TASK_CURRENT_TASK           Moe_Get_Acktive_Task()    /* Task number of current one               */

#define MOE_MANDATORY_INIT()        if(TASK_NO_TASK == sg_u8TaskID)\
                                    {\
                                        sg_u8TaskID = Moe_Get_Acktive_Task();\
                                    }\
                                    else\
                                    {\
                                        DBG_PRINT("Task is already inited!!");\
                                        return SW_ERR;\
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
uint8 Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len);


/******************************************************************************
* Name       : void Moe_Init(void)
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
uint8 Moe_Init(PF_TIMER_SRC pfSysTm, PF_POLL pfPoll);


/******************************************************************************
* Name       : void Moe_Run_System(void)
* Function   : The main function to schedule tasks.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 28th Apr 2016
******************************************************************************/
void Moe_Run(void);

/******************************************************************************
* Name       : uint8 Moe_Get_Acktive_Evt(void)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Get_Acktive_Evt(void);

/******************************************************************************
* Name       : uint8 Moe_Get_Acktive_Task(void)
* Function   : To be done.
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint8 Moe_Get_Acktive_Task(void);

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
void Moe_Reg_Malloc_Free(PF_MALLOC pfMalloc, PF_FREE pfFree);

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
void* Moe_Malloc(uint32 u32Size);

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
void Moe_Free(void *p);


 
#if (0) /* Those nice try */
#define __s(x)                        #x
#define s(x)                        __s(x)

#define __MOE_NAME(a,b)   a##b
#define _MOE_NAME(line)   __MOE_NAME(MARK_,line)
#define MOE_NAME          _MOE_NAME(__LINE__)

#define _MOE_NUNAME(a)    MARK_##a
#define MOE_NUNAME        _MOE_NUNAME(69)

#define MOE_EVT_ENTRY(evt)          case evt: goto MARK_##evt;  
#define MOE_DELAY(v,evt)            Moe_Timer_Delay(v);sg_u16FP = evt; MOE_EVT_PROCESS(evt);  

#define MOE_EVT_PROCESS(evt)        return SW_OK;MARK_##evt:

#define TASK_EVENT_PROCESS_LIST_START  switch(u8Evt){
#define TASK_EVENT_PROCESS_LIST_END    default:break;}


#define PROCESS_NAME(x)             TASK_##x
#define PROCESS(x)                  uint16 PROCESS_NAME(x)(uint8 u8Evt)

#define EVT_PARAM                   u8Evt

#define EVENT_PROCESS_BEGIN(x)      if(EVT_PARAM & x){

#define EVENT_PROCESS_END(x)        return (EVT_PARAM ^ x);}    


    TASK_EVENT_PROCESS_LIST_START;
    MOE_EVT_ENTRY(EVENT_TIMER);
    MOE_EVT_ENTRY(EVENT_MSG);
    MOE_EVT_ENTRY(EVENT_TEST);
    TASK_EVENT_PROCESS_LIST_END;

    DBG_PRINT("Hello\n");
    MOE_DELAY(3000,EVENT_DELAY);  

    DBG_PRINT("Goodbye\n");

 
    MOE_EVT_PROCESS(EVENT_MSG);



    MOE_EVT_PROCESS(EVENT_TEST);



    MOE_EVT_PROCESS(EVENT_TIMER);


#endif

#ifdef __cplusplus
}
#endif

#endif /* _MOE_H_ */

/* End of file */

