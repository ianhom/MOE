/******************************************************************************
* File       : Board_Config.c
* Function   : Hardware configurations
* description: To be done.           
* Version    : V1.00
* Author     : Ian
* Date       : 22nd Nov 2016
* History    :  No.  When           Who           What
*               1    22/Nov/2016    Ian           Create
******************************************************************************/
#include "type_def.h"
#include "../../Pub/common_head.h"
#include "./project_config.h"
#include "../../Core/MOE_Core.h"
#include "../../Core/MOE_Event.h"
#include "../../Core/MOE_Timer.h"
#include "../../Core/MOE_Msg.h"
#include "./Board_Config.h"
#include "../../Pub/debug.h"
#include "stm32f4xx_hal.h"
//#include "core_cm0plus.h"
//#include "stm32l0xx_hal.h"

UART_HandleTypeDef huart;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_USART_UART_Init(void);

volatile static uint32 sg_u32SysClk = 0;

static uint16        au16LedPin[2] = {LED_1_PIN , LED_2_PIN};
static GPIO_TypeDef *aptLedPort[2] = {LED_1_PORT, LED_2_PORT};
/******************************************************************************
* Name       : void Board_Init(void)
* Function   : Init board includes system clock, GPIOs, Uart and Systick
* Input      : None
* Output:    : None
* Return     : None
* description: To be done.
* Version    : V1.00
* Author     : Ian
* Date       : 21st Nov 2016
******************************************************************************/
void Board_Init(void)
{
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART_UART_Init();

    SysTick_Ms_Int_Init(SYSTICK_CNT_FOR_1_MS);
    return;
}

void SysTick_Ms_Int_Init(uint32_t u32Tick)
{
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;  /* Set clock source = core clock */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;    /* Enable systick interrupt      */
    SysTick->LOAD  = u32Tick;                     /* Set tick count for 1ms        */
    SysTick->VAL   = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Enable SysTick                */
    return;   
}

uint32 SysTick_GetSysClk(void)
{
    return sg_u32SysClk;
}

void SysTick_Handler(void)
{
    volatile uint32 u32Temp;
    u32Temp = SysTick->CTRL;
    sg_u32SysClk++;
    return;
}

int fputc(int u8C, FILE *p)
{
    while(!(USART1->SR & USART_SR_TXE));  
    USART1->DR = u8C;
    return 0;
}

/** System Clock Configuration*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART init function */
static void MX_USART_UART_Init(void)
{

  huart.Instance = USART_INSTANCE;
  huart.Init.BaudRate = 115200;
  huart.Init.WordLength = UART_WORDLENGTH_8B;
  huart.Init.StopBits = UART_STOPBITS_1;
  huart.Init.Parity = UART_PARITY_NONE;
  huart.Init.Mode = UART_MODE_TX_RX;
  huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart) != HAL_OK)
  {
    Error_Handler();
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void Board_LED_Toggle(uint8 u8Ch)
{
	  switch(u8Ch)
		{
		    case LED_1:
				case LED_2:
				{
				    HAL_GPIO_TogglePin(aptLedPort[u8Ch - LED_1], au16LedPin[u8Ch - LED_1]);
				    break;
		    }
				default:
			  {
				    break;
				}
		}
    return;
}

void Error_Handler(void)
{
    while(1);
}




/* End of file */

