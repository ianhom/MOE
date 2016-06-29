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
#include "MOE_Core.h"
#include "MOE_Event.h"
#include "MOE_App.h"
#include "debug.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task_Demo_Queue.h"

/* Add your task process here */
const PF_TASK_PROCESS cg_apfTaskFn[] = 
{
    Task1_Process
};

/* Calculate the total task number */
const uint8 cg_u8TaskNum = sizeof(cg_apfTaskFn)/sizeof(PF_TASK_PROCESS);

#if (0)
/* End of file */


