/******************************************************************************
* File       : MOE_SysTick.c
* Function   : Set SysTick for 1 ms
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 15th Feb 2017
* History    :  No.  When           Who           What
*               1    15/Feb/2017    Ian           Create
******************************************************************************/

#ifndef _MOE_SYSTICK_H_
#define _MOE_SYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Check if specified option is set for debugging */
#ifndef __DEBUG_MODE_MOE_SYSTICK                   
#define __DEBUG_MODE      __DEBUG_NONE                /* Default: None debugging info            */
#else
#ifdef __DEBUG_MODE
#undef __DEBUG_MODE
#endif
#define __DEBUG_MODE      __DEBUG_MODE_MOE_SYSTICK   /* According the set from project_config.h */
#endif

typedef struct
{
    volatile uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16U                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1UL << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0U                                            /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<< SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0U                                            /*!< SysTick VAL: CURRENT Position */
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<< SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31U                                            /*!< SysTick CALIB: NOREF Position */
#define SysTick_CALIB_NOREF_Msk            (1UL << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define SysTick_CALIB_SKEW_Pos             30U                                            /*!< SysTick CALIB: SKEW Position */
#define SysTick_CALIB_SKEW_Msk             (1UL << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define SysTick_CALIB_TENMS_Pos             0U                                            /*!< SysTick CALIB: TENMS Position */
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<< SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */

#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */

#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */


/******************************************************************************
* Name       : void SysTick_Ms_Int_Init(uint32_t u32Tick)
* Function   : Init SysTick Register
* Input      : uint32_t u32Tick    1~0xFFFFFFFF     The tick count for 1 ms
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
void SysTick_Ms_Int_Init(uint32_t u32Tick);

/******************************************************************************
* Name       : uint32 SysTick_GetSysClk(void)
* Function   : Return the current system ms counter(system clock)
* Input      : uint32_t u32Tick    1~0xFFFFFFFF     The tick count for 1 ms
* Output:    : None.
* Return     : 1~0xFFFFFFFF   The current system ms counter.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
uint32 SysTick_GetSysClk(void);
/******************************************************************************
* Name       : void SysTick_Handler(void)
* Function   : SysTick interrupt handler
* Input      : None.
* Output:    : None.
* Return     : None.
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 16th Feb 2017
******************************************************************************/
void SysTick_Handler(void);

void Board_Init(void);
void Board_Config_Reset_Ctrl(uint8 u8Val);
void SysTick_Ms_Int_Init(uint32 u32Tick);
uint32 SysTick_GetSysClk(void);

#ifdef __cplusplus
}
#endif

#endif /* _BOARD_CONFIG_H */

/* End of file */
