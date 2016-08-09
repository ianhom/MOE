
/******************************************************************************
* File       : MOE_PT.h
* Function   : PT definitions.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jul 2016
* History    :  No.  When           Who           What
*               1   0 8/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _PT_H_
#define _PT_H_

#ifdef __cplusplus
extern "C" {
#endif
 #define PT_INIT()               static unsigned char sg_u8RunPoint = 0;
 
 #define PT_BEGIN()              unsigned char u8YieldFlag = 1;\
                                 switch(sg_u8RunPoint)\
                                 {\
                                      case 0:
 
 #define PT_END()                }\
                                 u8YieldFlag   = 0;\
                                 sg_u8RunPoint = 0;
 
 #define PT_YIELD()              do\
                                 {\
                                     u8YieldFlag = 0;\
                                     sg_u8RunPoint = __LINE__;case __LINE__:\
                                     if(0 == u8YieldFlag)\
                                     {\
                                         return SW_OK;\
                                     }\
                                 }\
                                 while(0)


#define PT_YIELD_UNTIL(c)       do\
                                {\
                                    u8YieldFlag = 0;\
                                    sg_u8RunPoint = __LINE__;case __LINE__:\
                                    if((0 == u8YieldFlag) || !(c))\
                                    {\
                                        return SW_OK;\
                                    }\
                                }\
                                while(0)

   
#define PT_WAIT_UNTIL(c)       do\
                               {\
                                   u8YieldFlag = 0;\
                                   sg_u8RunPoint = __LINE__;case __LINE__:\
                                   if(!(c))\
                                   {\
                                       return SW_OK;\
                                   }\
                               }\
                               while(0)

#define PT_WAIT_CALL()          PT_YIELD()
#define PT_WAIT_EVENT(e)        PT_YIELD_UNTIL(e == u8Evt)
#define PT_WAIT_COND(c)         PT_YIELD_UNTIL(c)
#define PT_CHECK_COND(c)        PT_WAIT_UNTIL(c)

#define PT_DELAY(t)             Moe_Timer_Delay(t);\
                                PT_WAIT_EVENT(EVENT_DELAY)

#define PT_BREAK()              Moe_Event_Set(sg_u8TaskID, EVENT_BREAK, MOE_EVENT_NORMAL);\
                                PT_YIELD()

#define PT_WAIT_MSG()           PT_WAIT_EVENT(EVENT_MSG)

#define PTV                     static

        

#ifdef __cplusplus
}
#endif

#endif /* _PT_H_ */

/* End of file */


