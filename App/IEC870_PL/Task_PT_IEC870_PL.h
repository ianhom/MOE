/******************************************************************************
* File       : Task_PT_IEC870_PL.h
* Function   : A demo task for PT application
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 8th Jul 2016
* History    :  No.  When           Who           What
*               1    08/Jul/2016    Ian           Create
******************************************************************************/


#ifndef _TASK_PT_IEC870_PL_H_
#define _TASK_PT_IEC870_PL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_PT_IEC870_PL                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_PT_IEC870_PL   /* According the set from project_config.h */
#endif

//#define __PL_RCV_ENABLE
#define __PL_SND_ENABLE


#define PL_SEND(p) {\
    CC1101_FIFO_Write(p);\
    CC1101_Cmd(ADDR_CMD_SIDLE);\
    CC1101_Cmd(ADDR_CMD_STX);\
    DBG_PRINT("I am sending telegram!!\n");\
    PT_DELAY(500);\
    CC1101_Cmd(ADDR_CMD_SFTX);\
}

#define PL_RECEIVE(p) {\
    CC1101_Cmd(ADDR_CMD_SIDLE);\
    CC1101_Cmd(ADDR_CMD_SRX);\
    do\
    {\
        PT_DELAY(1);\
    }\
    while(0x6F != CC1101_Cmd(ADDR_CMD_SNOP));\
    TASK_PT_DEMO_LED_On(LED_RED);\
    CC1101_Cmd(ADDR_CMD_SIDLE);\
    CC1101_FIFO_Read(p);\
    CC1101_Cmd(ADDR_CMD_SFRX);\
}




/******************************************************************************
* Name       : uint8 Task_PT_IEC870_PL_Process(uint8 u8Evt)
* Function   : IEC870 physical layer test
* Input      : uint8  u8Evt  1~254     Event for the task
*              void  *pPara            Pointer of parameter
* Output:    : None
* Return     : SW_OK   Successful operation
*            : SW_ERR  Failed operation
*              1~254   Event which is not processed.
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 13th Jul 2016
******************************************************************************/
uint8 Task_PT_IEC870_PL_Process(uint8 u8Evt, void *pPara);




#ifdef __cplusplus
}
#endif

#endif /* _TASK_PT_IEC870_PL_H */

/* End of file */

