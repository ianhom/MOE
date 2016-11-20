
Skip to content
This repository

    Pull requests
    Issues
    Gist

    @ianhom

2
4

    4

ianhom/MOE
Code
Issues 10
Pull requests 0
Projects 1
Wiki
Pulse
Graphs
Settings
MOE/project/PT_Demo_KL25/MOE_main.h
7f2a874 14 days ago
@ianhom ianhom Update MOE_main.h
39 lines (29 sloc) 965 Bytes
/******************************************************************************
* File       : Moe_main.h
* Function   : Main-start of the project.
* description: To be done.          
* Version    : V1.00
* Author     : Ian
* Date       : 4th Noc 2016
* History    :  No.  When           Who           What
*               1    04/Nov/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_MAIN_H_
#define _MOE_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MAIN                    
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MAIN           /* According the set from project_config.h */
#endif



#ifdef __cplusplus
}
#endif

#endif /* _MOE_MAIN_H */

/* End of file */

    Contact GitHub API Training Shop Blog About 

    © 2016 GitHub, Inc. Terms Privacy Security Status Help 

