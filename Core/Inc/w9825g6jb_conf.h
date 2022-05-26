/**
  ******************************************************************************
  * @file    w9825g6jb_conf.h
  * @author  MCD Application Team
  * @brief   This file contains some configurations required for the
  *          w9825g6jb SDRAM memory.
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
#ifndef W9825G6JB_CONF_H
#define W9825G6JB_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup w9825g6jb
  * @{
  */

/** @addtogroup w9825g6jb_Exported_Constants
  * @{
  */
#define REFRESH_COUNT                    ((uint32_t)0x1E80)// /* SDRAM refresh counter (120Mhz SD clock) */ //Refresh Cycle time is 64ms. 64ms/(1/120MHz)= 7680 = 0x1E00

#define W9825G6JB_TIMEOUT             ((uint32_t)0xFFFF)

#ifdef __cplusplus
}
#endif

#endif /* W9825G6JB_CONF_H */
/**
  * @}
  */

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
