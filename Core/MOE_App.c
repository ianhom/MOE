/******************************************************************************
* File       : MOE_App.c
* Function   : This file is an interface for user to add tasks to MOE.
*              This file should be modified according to your tasks.
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
#include "MOE_App.h"
#include "debug.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task_Demo_Queue.h"


/******************************************************************************
* Name       : void Moe_Tasks_Init()
* Function   : Init all tasks
* Input      : None
* Output:    : None
* Return     : None
* description: Init all tasks and pass the task ID into the tasks.
*              If the inited tasks count is NOT equals to the Max
*              number of tasks, it will enter forever loop to indicate
*              that error.
* Version    : V1.00
* Author     : Ian
* Date       : 3rd May 2016
******************************************************************************/
void Moe_Tasks_Init()
{
    uint8 u8TaskID = 1;            /* Task No. starts from 0, higher number ==> lower priority       */

    /*****************************************************************************************************/
    /*****************************************************************************************************/
    Task1_Init(u8TaskID++);        /* Task 1 init operation, Please add your init task function here */
    Task2_Init(u8TaskID++);        /* Task 2 init operation, Please add your init task function here */
//    Task3_Init(u8TaskID++);        /* Task 3 inti operation, Please add your init task function here */
//    Task_Demo_Queue_Init(u8TaskID++);
    /******************************************************************************************************/
    /******************************************************************************************************/

    /* If the inited tasks count is NOT equals to the max number of all tasks */
    if (u8TaskID != MAX_TASK_NUM + 1)
    {
        DBG_PRINT("Task number ERROR!!\n");
        while(1);                  /* Enter forever loop */
    }
    /* If the inited tasks count is right, then continue */
   
    return;
}

/* End of file */


