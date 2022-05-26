/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma2d.h
  * @brief   This file contains all the function prototypes for
  *          the dma2d.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DMA2D_H__
#define __DMA2D_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "ltdc.h"
/* USER CODE END Includes */

extern DMA2D_HandleTypeDef hdma2d;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_DMA2D_Init(void);

/* USER CODE BEGIN Prototypes */
void DMA2D_Fill( uint32_t pDst, uint32_t width, uint32_t height, uint32_t lineOff, uint32_t pixelFormat, uint32_t color);
void DMA2D_Convert_MemCopy(uint32_t pixelFormat, uint32_t pSrc, uint32_t pDst, int xSize, int ySize, int OffLineSrc, int OffLineDst,int OuptFormat);
void DMA2D_MemCopy(uint32_t pixelFormat, uint32_t pSrc, uint32_t pDst, int xSize, int ySize, int OffLineSrc, int OffLineDst);
void DMA2D_Copy_YCbCr_To_RGB(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y,uint8_t Alpha, uint16_t xsize, uint16_t ysize, uint32_t PixelFormat,uint32_t ChromaSampling);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DMA2D_H__ */

