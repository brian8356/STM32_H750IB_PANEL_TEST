/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
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
#include "ltdc.h"

/* USER CODE BEGIN 0 */
extern __IO uint32_t Jpeg_HWDecodingEnd;
/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IIPC;
  hltdc.Init.HorizontalSync = 3;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 46;
  hltdc.Init.AccumulatedVBP = 15;
  hltdc.Init.AccumulatedActiveW = 526;
  hltdc.Init.AccumulatedActiveH = 287;
  hltdc.Init.TotalWidth = 534;
  hltdc.Init.TotalHeigh = 295;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg.Alpha = 0xFF;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = 0;
  pLayerCfg1.WindowX1 = 480;
  pLayerCfg1.WindowY0 = 0;
  pLayerCfg1.WindowY1 = 272;
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg1.Alpha = 0xFF;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg1.FBStartAdress = 0xC007F800;
  pLayerCfg1.ImageWidth = 480;
  pLayerCfg1.ImageHeight = 272;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLL3.PLL3M = 30;
    PeriphClkInitStruct.PLL3.PLL3N = 127;
    PeriphClkInitStruct.PLL3.PLL3P = 2;
    PeriphClkInitStruct.PLL3.PLL3Q = 2;
    PeriphClkInitStruct.PLL3.PLL3R = 30;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_1;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PG13     ------> LTDC_R0
    PE4     ------> LTDC_B0
    PE5     ------> LTDC_G0
    PE6     ------> LTDC_G1
    PG12     ------> LTDC_B4
    PG11     ------> LTDC_B3
    PG10     ------> LTDC_B2
    PI7     ------> LTDC_B7
    PI6     ------> LTDC_B6
    PI5     ------> LTDC_B5
    PI9     ------> LTDC_VSYNC
    PD3     ------> LTDC_G7
    PH15     ------> LTDC_G4
    PA10     ------> LTDC_B1
    PI10     ------> LTDC_HSYNC
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PI0     ------> LTDC_G5
    PA9     ------> LTDC_R5
    PA8     ------> LTDC_R6
    PH3     ------> LTDC_R1
    PC7     ------> LTDC_G6
    PG7     ------> LTDC_CLK
    PG6     ------> LTDC_R7
    PF10     ------> LTDC_DE
    PH10     ------> LTDC_R4
    PH8     ------> LTDC_R2
    PH9     ------> LTDC_R3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_7
                          |GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3
                          |GPIO_PIN_10|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PG13     ------> LTDC_R0
    PE4     ------> LTDC_B0
    PE5     ------> LTDC_G0
    PE6     ------> LTDC_G1
    PG12     ------> LTDC_B4
    PG11     ------> LTDC_B3
    PG10     ------> LTDC_B2
    PI7     ------> LTDC_B7
    PI6     ------> LTDC_B6
    PI5     ------> LTDC_B5
    PI9     ------> LTDC_VSYNC
    PD3     ------> LTDC_G7
    PH15     ------> LTDC_G4
    PA10     ------> LTDC_B1
    PI10     ------> LTDC_HSYNC
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PI0     ------> LTDC_G5
    PA9     ------> LTDC_R5
    PA8     ------> LTDC_R6
    PH3     ------> LTDC_R1
    PC7     ------> LTDC_G6
    PG7     ------> LTDC_CLK
    PG6     ------> LTDC_R7
    PF10     ------> LTDC_DE
    PH10     ------> LTDC_R4
    PH8     ------> LTDC_R2
    PH9     ------> LTDC_R3
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_10
                          |GPIO_PIN_7|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_3
                          |GPIO_PIN_10|GPIO_PIN_8|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void LTDC_Fill_Rec(uint8_t pixelFormat,uint16_t x0,uint16_t y0,uint16_t Width,uint16_t Height,uint32_t color,uint32_t Layer)
{
	uint32_t pDst;
	
	if(Layer == Layer0){
		pDst = Layer0_Start_Address+Layer_Width*y0*Pixel_Byte+x0*Pixel_Byte;
	}
		else	{
			pDst = Layer1_Start_Address+Layer_Width*y0*Pixel_Byte+x0*Pixel_Byte;
		}

	DMA2D_Fill(pDst,Width,Height,Layer_Width-Width,pixelFormat,color);
}

void LTDC_Jpeg(uint32_t* pSrc,uint32_t* Jpegbuf,uint32_t jpeg_Length,uint16_t x0,uint16_t y0,uint8_t Alpha,uint8_t pixelFormat,uint32_t Layer)
{
	JPEG_ConfTypeDef JPEG_Info={0};
	
	JPEG_Decode_DMA(&hjpeg, (uint32_t)pSrc, jpeg_Length , (uint32_t)Jpegbuf);
	
	while(Jpeg_HWDecodingEnd!=1){
		
	}
	
	HAL_JPEG_GetInfo(&hjpeg, &JPEG_Info);
	
	if(Layer == Layer0){
		Layer = Layer0_Start_Address;
	}
		else {
			Layer = Layer1_Start_Address;
		}
	
	DMA2D_Copy_YCbCr_To_RGB(Jpegbuf,(uint32_t*)Layer,x0,y0,Alpha,JPEG_Info.ImageWidth,JPEG_Info.ImageHeight,pixelFormat,JPEG_Info.ChromaSubsampling);
}

void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
{
	
}
/* USER CODE END 1 */
