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

/* MOE MACRO */
#define TASK_NO_TASK                (0x00)                    /* Task number which means there is no task */
#define TASK_ALL_TASK               (0xFF)                    /* Task number which means all tasks        */
#define TASK_FIRST_TASK             (0x01)                    /* Task number of the first one             */
#define TASK_LAST_TASK              MAX_TASK_NUM              /* Task number of the last one              */
#define TASK_CURRENT_TASK           Moe_Get_Acktive_Task()    /* Task number of current one               */

#define EVENT_NONE                  (0x0000)                  /* There is no events                       */
#define EVENT_TEST                  (0x0001)                  /* There is a test event                    */
#define EVENT_TIMER                 (0x0002)                  /* There is a timer event                   */
#define EVENT_MSG                   (0x0004)                  /* There is a message event                 */
#define EVENT_INT                   (0x0008)                  /* There is an interrupt event              */
#define EVENT_DELAY                 (0x0010)

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



void   Moe_Reg_Tasks(PF_TASK_PROCESS pfTaskFn);
uint8  Moe_Memset(uint8* pDes, uint8 u8Val, uint8 u8Len);a
void   Moe_Init();
void   Moe_Run();
uint8  Moe_Get_Acktive_Task();
void   Moe_Reg_Malloc_Free();
void*  Moe_Malloc(uint32 u32Size);
void   Moe_Free(void *p);

 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_H_ */

/* End of file */

