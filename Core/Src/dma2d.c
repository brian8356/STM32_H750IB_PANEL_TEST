/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma2d.c
  * @brief   This file provides code for the configuration
  *          of the DMA2D instances.
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
#include "dma2d.h"

/* USER CODE BEGIN 0 */
uint32_t DMA2D_READY_START;
/* USER CODE END 0 */

DMA2D_HandleTypeDef hdma2d;

/* DMA2D init function */
void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
  hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR;
  hdma2d.LayerCfg[1].ChromaSubSampling = DMA2D_NO_CSS;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef* dma2dHandle)
{

  if(dma2dHandle->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspInit 0 */

  /* USER CODE END DMA2D_MspInit 0 */
    /* DMA2D clock enable */
    __HAL_RCC_DMA2D_CLK_ENABLE();
  /* USER CODE BEGIN DMA2D_MspInit 1 */

  /* USER CODE END DMA2D_MspInit 1 */
  }
}

void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef* dma2dHandle)
{

  if(dma2dHandle->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspDeInit 0 */

  /* USER CODE END DMA2D_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DMA2D_CLK_DISABLE();
  /* USER CODE BEGIN DMA2D_MspDeInit 1 */

  /* USER CODE END DMA2D_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void DMA2D_Fill(uint32_t pDst, uint32_t width, uint32_t height, uint32_t lineOff, uint32_t pixelFormat, uint32_t color)
{
	DMA2D->CR = 0x00030000UL; 
	DMA2D->OCOLR = color; 
	DMA2D->OMAR = (uint32_t)pDst; 
	DMA2D->OOR = lineOff; 
	DMA2D->OPFCCR = pixelFormat; 
	DMA2D->NLR = (uint32_t)(width << 16) | (uint16_t)height; 
	
	DMA2D->CR |= DMA2D_CR_START;
	
 while (DMA2D->CR & DMA2D_CR_START) {}
}

void DMA2D_Convert_MemCopy(uint32_t pixelFormat, uint32_t pSrc, uint32_t pDst, int xSize, int ySize, int OffLineSrc, int OffLineDst,int OuptFormat)
{
	DMA2D->CR = 0x00010000UL;
	DMA2D->FGMAR = pSrc;
	DMA2D->OMAR = pDst;
	DMA2D->FGOR = OffLineSrc;
	DMA2D->OOR = OffLineDst;
	DMA2D->FGPFCCR = pixelFormat | (1<<16) | 0xFF<<24;
	DMA2D->OPFCCR = OuptFormat;
	DMA2D->NLR = (uint32_t)(xSize << 16) | (uint16_t)ySize;
	
	DMA2D->CR |= DMA2D_CR_START;

 while (DMA2D->CR & DMA2D_CR_START) {}
}

void DMA2D_MemCopy(uint32_t pixelFormat, uint32_t pSrc, uint32_t pDst, int xSize, int ySize, int OffLineSrc, int OffLineDst)
{
 DMA2D->CR = 0x00000000UL;
 DMA2D->FGMAR = pSrc;
 DMA2D->OMAR = pDst;
 DMA2D->FGOR = OffLineSrc;
 DMA2D->OOR = OffLineDst;
 DMA2D->FGPFCCR = pixelFormat;
 DMA2D->NLR = (uint32_t)(xSize << 16) | (uint16_t)ySize;

 DMA2D->CR |= DMA2D_CR_START;

 while (DMA2D->CR & DMA2D_CR_START) {}
}

void DMA2D_Copy_YCbCr_To_RGB(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y,uint8_t Alpha, uint16_t xsize, uint16_t ysize, uint32_t PixelFormat,uint32_t ChromaSampling)
{
	uint32_t cssMode = DMA2D_CSS_420;
	uint32_t inputLineOffset = 0;  
	uint32_t destination = 0; 
	
	/* 处理输入行偏移 */
	if(ChromaSampling == JPEG_420_SUBSAMPLING)
	{
		cssMode = DMA2D_CSS_420;

		inputLineOffset = xsize % 16;
		if(inputLineOffset != 0)
		{
			inputLineOffset = 16 - inputLineOffset;
		}    
	}
	else if(ChromaSampling == JPEG_444_SUBSAMPLING)
	{
		cssMode = DMA2D_NO_CSS;

		inputLineOffset = xsize % 8;
		if(inputLineOffset != 0)
		{
			inputLineOffset = 8 - inputLineOffset;
		}    
	}
	else if(ChromaSampling == JPEG_422_SUBSAMPLING)
	{
		cssMode = DMA2D_CSS_422;

		inputLineOffset = xsize % 16;
		if(inputLineOffset != 0)
		{
			inputLineOffset = 16 - inputLineOffset;
		}      
	}  

	/* 输出地址，特别注意末尾乘以2对应RGB565，如果输出格式是ARGB8888，需要乘以4 */
	destination = (uint32_t)pDst + ((y * Layer_Width) + x) * 3;
	  
  
	/* DMA2D采用存储器到存储器模式，并且执行FPC颜色格式转换, 这种模式是前景层作为DMA2D输入 */  
	DMA2D->CR      = 0x00010000;
	DMA2D->OOR     = Layer_Width - xsize;
	
	/* 输出格式 */
	DMA2D->OPFCCR  = PixelFormat 
				     | (DMA2D_REGULAR_ALPHA << 20) 
				     | (DMA2D_RB_REGULAR << 21);  
	
	/* 前景层输入格式 */	
	DMA2D->FGPFCCR = DMA2D_INPUT_YCBCR 
			         | (DMA2D_REPLACE_ALPHA << 16) 
			         | (DMA2D_REGULAR_ALPHA << 20)
			         | (DMA2D_RB_REGULAR << 21)   
			         | (Alpha << 24)              
			         | (cssMode << 18);		

	DMA2D->FGOR    = inputLineOffset;
	DMA2D->NLR     = (uint32_t)(xsize << 16) | (uint16_t)ysize;      
	DMA2D->OMAR    = (uint32_t)destination;
	DMA2D->FGMAR   = (uint32_t)pSrc;  

	/* 启动传输 */
	
	//HAL_LTDC_ProgramLineEvent(&hltdc,0);

	DMA2D->CR   |= DMA2D_CR_START;   

	/* 等待DMA2D传输完成 */
	while (DMA2D->CR & DMA2D_CR_START) {} 
}
/* USER CODE END 1 */
