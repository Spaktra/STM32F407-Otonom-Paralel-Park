/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dwt_stm32_delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
uint32_t time_1;
uint16_t distance_1;
uint32_t time_2;
uint16_t distance_2;
uint32_t time_3;
uint16_t distance_3;
int count = 0;
int yer = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint32_t Read_HCSR04() // sureyi tutacagiz
{
	uint32_t local_time = 0; //echodaki sureyi tutacagiz

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // pini tetikledik
	DWT_Delay_us(10); // 10mikro saniye tetiklememiz lazimdi 10msaniye delay yaptik
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);// pini kapattik

	while(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)); // A portunun 2.pinin okur deger gelince donguden cikar

	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)) // echodan deger gelince girer
	{
		local_time++;
		DWT_Delay_us(1); // 1 mikro saniye bekle
		// her mikro saniyede local time artar
	}

	return local_time;
}

uint32_t Read_HCSR04_2() // sureyi tutacagiz
{
	uint32_t local_time = 0; //echodaki sureyi tutacagiz

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET); // pini tetikledik
	DWT_Delay_us(10); // 10mikro saniye tetiklememiz lazimdi 10msaniye delay yaptik
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);// pini kapattik

	while(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)); // A portunun 2.pinin okur deger gelince donguden cikar

	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)) // echodan deger gelince girer
	{
		local_time++;
		DWT_Delay_us(1); // 1 mikro saniye bekle
		// her mikro saniyede local time artar
	}

	return local_time;
}

uint32_t Read_HCSR04_3() // sureyi tutacagiz
{
	uint32_t local_time = 0; //echodaki sureyi tutacagiz

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // pini tetikledik
	DWT_Delay_us(10); // 10mikro saniye tetiklememiz lazimdi 10msaniye delay yaptik
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);// pini kapattik

	while(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)); // A portunun 2.pinin okur deger gelince donguden cikar

	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)) // echodan deger gelince girer
	{
		local_time++;
		DWT_Delay_us(1); // 1 mikro saniye bekle
		// her mikro saniyede local time artar
	}

	return local_time;
}

void Teker_geri()
{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET); // 1. tekerlegi ileri yonde dondur
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3,GPIO_PIN_SET);// 2. tekerlegi ileri yonde dondur
}

void Teker_ileri()
{
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET); // 1. tekerlegi geri yonde dondur
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // 2. tekerlegi geri yonde dondur
}

void Teker_dur()
{
	  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0,GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1,GPIO_PIN_RESET); // 1.tekerlegi durdur
	  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2,GPIO_PIN_RESET);
	  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // 2. tekerlegi durdur
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  DWT_Delay_Init();
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  /* USER CODE END 2 */
	TIM4->CCR1=1040;
	HAL_Delay(1000);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  time_1 = Read_HCSR04();
	  distance_1 = time_1 / 58 ;// zamani 58 e bolerek cm cinsinden uzakligi bulduk HCSR04 formulu

	  time_2 = Read_HCSR04_2();
	  distance_2 = time_2 / 58;

	  time_3 = Read_HCSR04_3();
	  distance_3 = time_3 / 58 ;

	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13 , GPIO_PIN_SET);

	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
	  	  {
	  		  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));
	  		  HAL_Delay(100);

	  		  count++;
	  	  }

	  if(count%2 == 1)
	  	  {
		  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
		  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET); // 1. tekerlegi ileri yonde dondur
		  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
		  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); // 2. tekerlegi ileri yonde dondur

		  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14 , GPIO_PIN_SET);
		  	  if(distance_1 < 5)
		  	  {
		  		  Teker_dur();
		  		  while(1)
		  		  {

		  		  }
		  	  }
		  	  if(distance_2 > 15)
		  	  {
		  		  HAL_Delay(210);
		  		  yer++;

		  		  if(yer > 5)
		  		  {
		  			  HAL_Delay(100);
		  			  Teker_dur();
		  			  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15 , GPIO_PIN_SET);
			   	  	  HAL_Delay(100);
			  		  TIM4->CCR1=1550; //1700=180 derece
			  		  HAL_Delay(200);
			  		  time_3 = Read_HCSR04_3();
			  		  distance_3 = time_3 / 58 ;
			  		  while(distance_3 > 13 )
			  		 {
			  			  time_3 = Read_HCSR04_3();
			   			  distance_3 = time_3 / 58 ;
			  	  		  Teker_geri();
			  		 }
			    	  Teker_dur();
			   	  	  HAL_Delay(200);
			  		  TIM4->CCR1=1100; //1100=90 derece
			  		  HAL_Delay(200);
			  		  time_3 = Read_HCSR04_3();
			  		  distance_3 = time_3 / 58 ;
			  		  while(distance_3 > 7 )
			  		  {
			  			  time_3 = Read_HCSR04_3();
			  			  distance_3 = time_3 / 58 ;
			  			  Teker_geri();
			  		  }
			  		  Teker_dur();
			  		  HAL_Delay(200);
			  		  while(1)
			  		  {
			  			  if(distance_3 > 2)
			  			  {
			  				TIM4->CCR1=760; //600 = 0 derece
			  				HAL_Delay(200);
			  				Teker_geri();
			  				break;
			  			  }
			  		  }
			  		  Teker_dur();
			  		  HAL_Delay(200);
			  		  time_2 = Read_HCSR04_2();
			  		  distance_2 = time_2 / 58;
			  		  while(distance_2 < 3)
			  		  {
				  		  time_2 = Read_HCSR04_2();
				  		  distance_2 = time_2 / 58;
				  		  TIM4->CCR1=1350; //1700=180 derece
				  		  HAL_Delay(200);
				  		  Teker_ileri();
			  		  }
			  		  Teker_dur();
			  		  HAL_Delay(200);
			  		  time_3 = Read_HCSR04_3();
			  		  distance_3 = time_3 / 58 ;
			  		  while(distance_3 < 7)
			  		  {
				  		  time_3 = Read_HCSR04_3();
				  		  distance_3 = time_3 / 58 ;
				  		  TIM4->CCR1=760; //600 = 0 derece
				  		  Teker_geri();
			  		  }
			  		  Teker_dur();
			  		  HAL_Delay(200);
			  		  TIM4->CCR1=1100; //1100=90 derece
			  		  HAL_Delay(200);
			  		  time_3 = Read_HCSR04_3();
			  		  distance_3 = time_3 / 58 ;
			  		  while(distance_3 > 7 )
			  		  {
			  			  time_3 = Read_HCSR04_3();
			  			  distance_3 = time_3 / 58 ;
			  			  Teker_geri();
			  		  }
			  		  Teker_dur();
			  		  while(1)
			  		  {
			  			  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15 , GPIO_PIN_SET);
			  		  }

		  		  }
		  	  }


	  	  }
  /* USER CODE END 3 */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 83;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 19999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE0 PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA3 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
