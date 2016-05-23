/******************************************************************************
* File       : Task3.c
* Function   : It is No. 3 task which is just a demo task
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
* History    :  No.  When           Who           What
*               1    3/May/2016     Ian           Create
******************************************************************************/

#include "type_def.h"
#include "common_head.h"
#include "OSAL.h"
#include "Task3.h"

static uint8 sg_u8TaskID = TASK_NO_TASK;

/******************************************************************************
* Name       : void Task3_Init(uint8 u8TaskID)
* Function   : Init task3
* Input      : To be done.
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Task3_Init(uint8 u8TaskID)
{

    sg_u8TaskID = u8TaskID;        /* Get the task ID */

    Osal_Reg_Tasks(Task3_Process);

    DBG_PRINT("Task 3 is inited successfully, Task ID is %d\n", sg_u8TaskID);
    
    return;
}

/******************************************************************************
* Name       : uint16 Task3_Process(uint16 u16Evt)
* Function   : Task 3 process
* Input      : To be done
* Output:    : None
* Return     : To be done
* description: To be done
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
uint16 Task3_Process(uint16 u16Evt)
{
    if (u16Evt & EVENT_TEST)
    {
        DBG_PRINT("This is task 3 process function, Task ID is %d\n", sg_u8TaskID);
        return (u16Evt ^ EVENT_TEST);
    }
}

/* End of file */



