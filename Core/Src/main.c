/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma2d.h"
#include "jpeg.h"
#include "ltdc.h"
#include "mdma.h"
#include "quadspi.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_qspi_w25q256.h"
#include "w9825g6jb.h"
#include <stdio.h>
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

/* USER CODE BEGIN PV */
int fputc(int c, FILE *stream)    //??fputc??
{

    HAL_UART_Transmit(&huart4, (unsigned char *)&c, 1, 1000);   
    return 1;
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
extern unsigned char image_320_240_jpg[23127];
extern __IO uint32_t Jpeg_HWDecodingEnd;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */	
	JPEG_ConfTypeDef JPEG_Info={0};
	
	int count;
	
	W9825G6JB_Context_t SDRAM_REG={0};
	
	SDRAM_REG.BurstLength=W9825G6JB_BURST_LENGTH_1;
	SDRAM_REG.BurstType=W9825G6JB_BURST_TYPE_SEQUENTIAL;
	SDRAM_REG.CASLatency=W9825G6JB_CAS_LATENCY_3;
	SDRAM_REG.OperationMode=W9825G6JB_OPERATING_MODE_STANDARD;
	SDRAM_REG.RefreshMode=W9825G6JB_AUTOREFRESH_MODE_CMD;
	SDRAM_REG.RefreshRate=REFRESH_COUNT;
	SDRAM_REG.TargetBank=FMC_SDRAM_CMD_TARGET_BANK1;
	SDRAM_REG.WriteBurstMode=W9825G6JB_WRITEBURST_MODE_SINGLE;
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
  MX_FMC_Init();
  MX_QUADSPI_Init();
  MX_LTDC_Init();
  MX_DMA2D_Init();
  MX_MDMA_Init();
  MX_JPEG_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	if(BSP_QSPI_W25Q256_Init() != QSPI_OK)
	{
		//printf("BSP_QSPI_W25Q256_Init fail\r\n");
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	if(BSP_QSPI_W25Q256_EnableMemoryMappedMode() != QSPI_OK)
	{
		//printf("BSP_QSPI_W25Q256_EnableMemoryMappedMode fail\r\n");
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	if(W9825G6JB_Init(&hsdram1,&SDRAM_REG))
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	
	printf("Hello\r\n");
	
	//HAL_LTDC_SetAlpha(&hltdc,0x80,Layer1);
	
	DMA2D_Convert_MemCopy(LTDC_PIXEL_FORMAT_RGB888,0x90000000,Layer0_Start_Address,480,270,0,0,LTDC_PIXEL_FORMAT_ARGB8888);
	
	//Fill_Rec_DMA2D(0,0,480,272,0x00FF0000,Layer0);
	
//	LTDC_Fill_Rec(LTDC_PIXEL_FORMAT_ARGB8888,0,0,480,272,0xFFFFFFFF,Layer1);
	
	
	count = JPEG_Length_Check(Bird);
	
	LTDC_Jpeg((uint32_t*)Bird,(uint32_t*)JPEG_PFC_BUFFER,count,0,0,0xFF,LTDC_PIXEL_FORMAT_ARGB8888,Layer1);
	
	if(LTDC->SRCR & 0x01){
		LTDC_Fill_Rec(LTDC_PIXEL_FORMAT_ARGB8888,400,200,70,60,0xFFFF0000,Layer1);
	}
		else if (LTDC->SRCR & 0x02){
			LTDC_Fill_Rec(LTDC_PIXEL_FORMAT_ARGB8888,400,200,70,60,0xFF00FF00,Layer1);
		}
			else LTDC_Fill_Rec(LTDC_PIXEL_FORMAT_ARGB8888,400,200,70,60,0xFFFFFFFF,Layer1);

	
	//DMA2D_Convert_MemCopy(LTDC_PIXEL_FORMAT_RGB888,0x90000000,Layer1_Start_Address,480,270,0,0,LTDC_PIXEL_FORMAT_ARGB8888);
	
//		LTDC_Jpeg((uint32_t*)0x90060000,(uint32_t*)0xC0100000,(uint32_t*)Layer1_Start_Address,0x15F4,0,0,LTDC_PIXEL_FORMAT_ARGB8888,1);
	
//	JPEG_Decode_DMA(&hjpeg, 0x90060000, 0x15F4, 0xC0100000);
//	
//	while(Jpeg_HWDecodingEnd!=1){
//		
//	}
//	
//	HAL_JPEG_GetInfo(&hjpeg, &JPEG_Info);
//	
//	DMA2D_Copy_YCbCr_To_RGB((uint32_t*)0xC0100000,(uint32_t*)0xC007F800,0,0,JPEG_Info.ImageWidth,JPEG_Info.ImageHeight,LTDC_PIXEL_FORMAT_ARGB8888,JPEG_Info.ChromaSubsampling);
//  
//	while(Jpeg_HWDecodingEnd!=1){
//		
//	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 32;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

