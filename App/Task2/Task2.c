/******************************************************************************
* File       : Task2.c
* Function   : It is No. 2 task which is just a demo task
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "project_config.h"
#include "OSAL.h"
#include "Task2.h"
#include "debug.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : void Task2_Init(uint8 u8TaskID)
* Function   : Init task2
* Input      : To be done.
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Task2_Init(uint8 u8TaskID)
{

    sg_u8TaskID = u8TaskID;        /* Get the task ID */

    Osal_Reg_Tasks(Task2_Process);

    DBG_PRINT("Task 2 is inited successfully, Task ID is %d\n", sg_u8TaskID);
    
    return;
}

/******************************************************************************
* Name       : uint16 Task2_Process(uint16 u16Evt)
* Function   : Task 2 process
* Input      : To be done
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint16 Task2_Process(uint16 u16Evt)
{
    if (u16Evt & EVENT_TEST)
    {
        DBG_PRINT("This is task 2 process function, Task ID is %d\n", sg_u8TaskID);
        return (u16Evt ^ EVENT_TEST);
    }
    return u16Evt;
}

/* End of file */



