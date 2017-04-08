/******************************************************************************
* File       : MOE_PT.h
* Function   : PT definitions.
* Description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jul 2016
* History    :  No.  When           Who           What
*               1    08/Jul/2016    Ian           Create
*               2    25/Nov/2016    Ian           Extend the range of running point
******************************************************************************/

#ifndef _PT_H_
#define _PT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* PT init, use this macro at the beginning of PT task */
#define PT_INIT()               static unsigned short int sg_u16RunPoint = 0;

/* PT begin, use it with PT_END to contain the pt process */
#define PT_BEGIN()              unsigned char u8YieldFlag = 1;\
                                switch(sg_u16RunPoint)\
                                {\
                                     case 0:

/* PT end, use it with PT_BEGIN to contain the pt process */
#define PT_END()                }\
                                u8YieldFlag   = 0;\
                                sg_u16RunPoint = 0;

/* PT yield, return from process */
#define PT_YIELD()              do\
                                {\
                                    u8YieldFlag = 0;\
                                    sg_u16RunPoint = __LINE__;case __LINE__:\
                                    if(0 == u8YieldFlag)\
                                    {\
                                        return SW_OK;\
                                    }\
                                }\
                                while(0)

/* PT yield until a condition */
#define PT_YIELD_UNTIL(c)       do\
                                {\
                                    u8YieldFlag = 0;\
                                    sg_u16RunPoint = __LINE__;case __LINE__:\
                                    if((0 == u8YieldFlag) || !(c))\
                                    {\
                                        return SW_OK;\
                                    }\
                                }\
                                while(0)

/* Wait a condition */   
#define PT_WAIT_UNTIL(c)       do\
                               {\
                                   u8YieldFlag = 0;\
                                   sg_u16RunPoint = __LINE__;case __LINE__:\
                                   if(!(c))\
                                   {\
                                       return SW_OK;\
                                   }\
                               }\
                               while(0)

/* Wait for calling */
#define PT_WAIT_CALL()          PT_YIELD()

/* Wait an event */
#define PT_WAIT_EVENT(e)        PT_YIELD_UNTIL(e == u8Evt)

/* Wait a condition */
#define PT_WAIT_COND(c)         PT_YIELD_UNTIL(c)

/* Check a condition */
#define PT_CHECK_COND(c)        PT_WAIT_UNTIL(c)

/* Return and recall after t ms delay */
#define PT_DELAY(t)             Moe_Timer_Delay(t);\
                                PT_WAIT_EVENT(EVENT_DELAY)

/* Return and recall as soon as possible, leave a chance for other task */
#define PT_BREAK()              Moe_Event_Set(sg_u8TaskID, EVENT_BREAK, MOE_EVENT_NORMAL, NULL);\
                                PT_YIELD()

/* Wait for a message event */
#define PT_WAIT_MSG()           PT_WAIT_EVENT(EVENT_MSG)

/* Because PT process should NOT use stack, we need static local variable */
#define PTV                     static

        

#ifdef __cplusplus
}
#endif

#endif /* _PT_H_ */

/* End of file */


