/******************************************************************************
* File       : MOE_HAL.c
* Function   : Hardware Abstract Layer.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Jul 2016
* History    :  No.  When           Who           What
*               1    04/Jul/2016    Ian           Create
******************************************************************************/

#ifndef _MOE_HAL_H_
#define _MOE_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_HAL                    
#define __DEBUG_MODE      __DEBUG_NONE                    /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_HAL            /* According the set from project_config.h */
#endif
    
    
/* Driver configuration commmand type */
#define MOE_DRV_INIT                      (0)      /* Init command            */
#define MOE_DRV_CONFIG                    (1)      /* Configure command       */
#define MOE_DRV_CTRL                      (2)      /* Control command         */
#define MOE_DRV_FUNC_EN                   (3)      /* Enable driver function  */
#define MOE_DRV_FUNC_DIS                  (4)      /* Disable driver function */
#define MOE_DRV_INT_EN                    (5)      /* Enable interrupt        */
#define MOE_DRV_INT_DIS                   (6)      /* Disable interrupt       */
#define MOE_DRV_RX_EN                     (7)      /* Enable Rx               */
#define MOE_DRV_RX_DIS                    (8)      /* Disable RX              */
#define MOE_DRV_TX_EN                     (9)      /* Enable Tx               */
#define MOE_DRV_TX_DIS                    (10)     /* Disable TX              */
#define MOE_DRV_DMA_EN                    (11)     /* Enable DMA function     */
#define MOE_DRV_DMA_DIS                   (12)     /* Disable DMA function    */

/* Structure of driver parameters */
typedef struct _T_MOE_DRV_PARA
{
    void     (*pfCallBack)(void *pPara);    /* Callback pointer                 */  
    uint8   *pu8Buf;                        /* Pointer for parameter            */  
    uint16   u16BufLen;                     /* Length of pararmeters in byte    */
    uint8    u8Type;                        /* Type of command or configuration */                                            
}T_MOE_DRV_PARA;    
    
/* Structure of driver operation interface */
 typedef struct _T_MOE_DRV_OP
 {
     uint8 (*pfInit)(T_MOE_DRV_PARA *ptPara);   /* Init operation    */
     uint8 (*pfCtrl)(T_MOE_DRV_PARA *ptPara);   /* Control operation */
     uint8 (*pfRead)(T_MOE_DRV_PARA *ptPara);   /* Read operation    */
     uint8 (*pfWrite)(T_MOE_DRV_PARA *ptPara);  /* Write operation   */
 }T_MOE_DRV_OP;
    
    
/******************************************************************************
* Name       : uint8 Moe_HAL_Init()
* Function   : Init hardware abstract layer
* Input      : None.
* Output:    : None.
* Return     : SW_OK   Successful.
*              SW_ERR  Failed.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 4th Jul 2016
******************************************************************************/
uint8 Moe_HAL_Init();
 
 
#ifdef __cplusplus
}
#endif

#endif /* _MOE_HAL_H_ */

/* End of file */

