/******************************************************************************
* File       : MOE_SysTick.h
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

typedef struct _MOE_SysTick_Type
{
    volatile uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} MOE_SysTick_Type;

/* SysTick Control / Status Register Definitions */
#define MOE_SysTick_CTRL_COUNTFLAG_POS         16U                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define MOE_SysTick_CTRL_COUNTFLAG_MSK         (1UL << SysTick_CTRL_COUNTFLAG_POS)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define MOE_SysTick_CTRL_CLKSOURCE_POS          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define MOE_SysTick_CTRL_CLKSOURCE_MSK         (1UL << SysTick_CTRL_CLKSOURCE_POS)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define MOE_SysTick_CTRL_TICKINT_POS            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define MOE_SysTick_CTRL_TICKINT_MSK           (1UL << SysTick_CTRL_TICKINT_POS)              /*!< SysTick CTRL: TICKINT Mask */

#define MOE_SysTick_CTRL_ENABLE_POS             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define MOE_SysTick_CTRL_ENABLE_MSK            (1UL)                                          /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define MOE_SysTick_LOAD_RELOAD_POS             0U                                            /*!< SysTick LOAD: RELOAD Position */
#define MOE_SysTick_LOAD_RELOAD_MSK            (0xFFFFFFUL)                                   /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define MOE_SysTick_VAL_CURRENT_POS             0U                                            /*!< SysTick VAL: CURRENT Position */
#define MOE_SysTick_VAL_CURRENT_MSK            (0xFFFFFFUL)                                   /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define MOE_SysTick_CALIB_NOREF_POS            31U                                            /*!< SysTick CALIB: NOREF Position */
#define MOE_SysTick_CALIB_NOREF_MSK            (1UL << SysTick_CALIB_NOREF_POS)               /*!< SysTick CALIB: NOREF Mask */

#define MOE_SysTick_CALIB_SKEW_POS             30U                                            /*!< SysTick CALIB: SKEW Position */
#define MOE_SysTick_CALIB_SKEW_MSK             (1UL << SysTick_CALIB_SKEW_POS)                /*!< SysTick CALIB: SKEW Mask */

#define MOE_SysTick_CALIB_TENMS_POS             0U                                            /*!< SysTick CALIB: TENMS Position */
#define MOE_SysTick_CALIB_TENMS_MSK            (0xFFFFFFUL)                                   /*!< SysTick CALIB: TENMS Mask */

#define MOE_SysTick_BASE        (SCS_BASE +  0x0010UL)                                        /*!< SysTick Base Address */

#define MOE_SysTick             ((MOE_SysTick_Type   *)     MOE_SysTick_BASE  )               /*!< SysTick configuration struct */


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
