/**
  ******************************************************************************
  * @file    w9825g6jb.h
  * @author  MCD Application Team
  * @brief   This file contains all the description of the W9825G6JB SDRAM
  *          memory.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef W9825G6JB_H
#define W9825G6JB_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "w9825g6jb_conf.h"
/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup W9825G6JB
  * @{
  */

/** @defgroup W9825G6JB_Exported_Types W9825G6JB Exported Types
  * @{
  */
typedef struct 
{
  uint32_t TargetBank;           /*!< Target Bank                             */
  uint32_t RefreshMode;          /*!< Refresh Mode                            */
  uint32_t RefreshRate;          /*!< Refresh Rate                            */
  uint32_t BurstLength;          /*!< Burst Length                            */
  uint32_t BurstType;            /*!< Burst Type                              */
  uint32_t CASLatency;           /*!< CAS Latency                             */
  uint32_t OperationMode;        /*!< Operation Mode                          */
  uint32_t WriteBurstMode;       /*!< Write Burst Mode                        */
} W9825G6JB_Context_t;

/**
  * @}
  */

/** @defgroup W9825G6JB_Exported_Constants W9825G6JB Exported Constants
  * @{
  */
#define W9825G6JB_OK                (0)
#define W9825G6JB_ERROR             (-1)

/* Register Mode */
#define W9825G6JB_BURST_LENGTH_1              0x00000000U
#define W9825G6JB_BURST_LENGTH_2              0x00000001U
#define W9825G6JB_BURST_LENGTH_4              0x00000002U
#define W9825G6JB_BURST_LENGTH_8              0x00000004U
#define W9825G6JB_BURST_TYPE_SEQUENTIAL       0x00000000U
#define W9825G6JB_BURST_TYPE_INTERLEAVED      0x00000008U
#define W9825G6JB_CAS_LATENCY_2               0x00000020U
#define W9825G6JB_CAS_LATENCY_3               0x00000030U
#define W9825G6JB_OPERATING_MODE_STANDARD     0x00000000U
#define W9825G6JB_WRITEBURST_MODE_PROGRAMMED  0x00000000U 
#define W9825G6JB_WRITEBURST_MODE_SINGLE      0x00000200U 

/* Command Mode */
#define W9825G6JB_NORMAL_MODE_CMD             0x00000000U
#define W9825G6JB_CLK_ENABLE_CMD              0x00000001U
#define W9825G6JB_PALL_CMD                    0x00000002U
#define W9825G6JB_AUTOREFRESH_MODE_CMD        0x00000003U
#define W9825G6JB_LOAD_MODE_CMD               0x00000004U
#define W9825G6JB_SELFREFRESH_MODE_CMD        0x00000005U
#define W9825G6JB_POWERDOWN_MODE_CMD          0x00000006U

/**
  * @}
  */ 

/** @addtogroup W9825G6JB_Exported_Functions
  * @{
  */
int32_t W9825G6JB_Init(SDRAM_HandleTypeDef *Ctx, W9825G6JB_Context_t *pRegMode);
int32_t W9825G6JB_ClockEnable(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t W9825G6JB_Precharge(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t W9825G6JB_ModeRegConfig(SDRAM_HandleTypeDef *Ctx, W9825G6JB_Context_t *pRegMode);
int32_t W9825G6JB_TimingConfig(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_TimingTypeDef *pTiming);
int32_t W9825G6JB_RefreshMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface, uint32_t RefreshMode);
int32_t W9825G6JB_RefreshRate(SDRAM_HandleTypeDef *Ctx, uint32_t RefreshCount);
int32_t W9825G6JB_EnterPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t W9825G6JB_ExitPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface);
int32_t W9825G6JB_Sendcmd(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_CommandTypeDef *SdramCmd);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* W9825G6JB_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
