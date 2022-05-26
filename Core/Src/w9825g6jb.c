                                                 /**
 ******************************************************************************
 * @file    w9825g6jb.c
 * @author  MCD Application Team
 * @brief   w9825g6jb sdram 128Mb driver file
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

/* Includes ------------------------------------------------------------------*/
#include "w9825g6jb.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup Components
  * @{
  */ 

/** @defgroup W9825G6JB W9825G6JB
  * @brief     This file provides a set of functions needed to drive the 
  *            W9825G6JB SDRAM memory.
  * @{
  */
 
/** @defgroup W9825G6JB_Private_Variables W9825G6JB Private Variables
  * @{
  */
static FMC_SDRAM_CommandTypeDef Command;
/**
  * @}
  */ 

/** @defgroup W9825G6JB_Function_Prototypes W9825G6JB Function Prototypes
  * @{
  */
static int32_t W9825G6JB_Delay(uint32_t Delay);

/**
  * @}
  */ 

/** @defgroup W9825G6JB_Exported_Functions W9825G6JB Exported Functions
  * @{
  */
/**
  * @brief  Initializes the W9825G6JB SDRAM memory
  * @param  Ctx : Component object pointer
  * @param  pRegMode : Pointer to Register Mode stucture
  * @retval error status
  */
int32_t W9825G6JB_Init(SDRAM_HandleTypeDef *Ctx, W9825G6JB_Context_t *pRegMode) 
{
  int32_t ret = W9825G6JB_ERROR;
  
  /* Step 1: Configure a clock configuration enable command */
  if(W9825G6JB_ClockEnable(Ctx, pRegMode->TargetBank) == W9825G6JB_OK)
  {
  
    /* Step 2: Insert 100 us minimum delay */ 
    /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
    (void)W9825G6JB_Delay(1);
    
    /* Step 3: Configure a PALL (precharge all) command */ 
    if(W9825G6JB_Precharge(Ctx, pRegMode->TargetBank) == W9825G6JB_OK)
    {
    
      /* Step 4: Configure a Refresh command */ 
      if(W9825G6JB_RefreshMode(Ctx, pRegMode->TargetBank, pRegMode->RefreshMode) == W9825G6JB_OK)
      {
      
        /* Step 5: Program the external memory mode register */
        if(W9825G6JB_ModeRegConfig(Ctx, pRegMode) == W9825G6JB_OK)
        {
        
          /* Step 6: Set the refresh rate counter */
          if(W9825G6JB_RefreshRate(Ctx, pRegMode->RefreshRate) == W9825G6JB_OK)
          {
          
            ret = W9825G6JB_OK;
          }
        }
      }
    }
  } 
  return ret;
}

/**
  * @brief  Enable SDRAM clock
  * @param  Ctx : Component object pointer
  * @param  Interface : Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  * @retval error status
  */
int32_t W9825G6JB_ClockEnable(SDRAM_HandleTypeDef *Ctx, uint32_t Interface) 
{
  Command.CommandMode            = W9825G6JB_CLK_ENABLE_CMD;
  Command.CommandTarget          = Interface;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(Ctx, &Command, W9825G6JB_TIMEOUT) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Precharge all sdram banks
  * @param  Ctx : Component object pointer
  * @param  Interface : Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  * @retval error status
  */
int32_t W9825G6JB_Precharge(SDRAM_HandleTypeDef *Ctx, uint32_t Interface) 
{
  Command.CommandMode            = W9825G6JB_PALL_CMD;
  Command.CommandTarget          = Interface;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(Ctx, &Command, W9825G6JB_TIMEOUT) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Program the external memory mode register
  * @param  Ctx : Component object pointer
  * @param  pRegMode : Pointer to Register Mode stucture
  * @retval error status
  */
int32_t W9825G6JB_ModeRegConfig(SDRAM_HandleTypeDef *Ctx, W9825G6JB_Context_t *pRegMode) 
{
  uint32_t tmpmrd;

  /* Program the external memory mode register */
  tmpmrd = (uint32_t)pRegMode->BurstLength   |\
                     pRegMode->BurstType     |\
                     pRegMode->CASLatency    |\
                     pRegMode->OperationMode |\
                     pRegMode->WriteBurstMode;
  
  Command.CommandMode            = W9825G6JB_LOAD_MODE_CMD;
  Command.CommandTarget          = pRegMode->TargetBank;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = tmpmrd;
  
  /* Send the command */
  if(HAL_SDRAM_SendCommand(Ctx, &Command, W9825G6JB_TIMEOUT) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Program the SDRAM timing
  * @param  Ctx : Component object pointer
  * @param  pTiming : Pointer to SDRAM timing configuration stucture
  * @retval error status
  */
int32_t W9825G6JB_TimingConfig(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_TimingTypeDef *pTiming) 
{
  /* Program the SDRAM timing */
  if(HAL_SDRAM_Init(Ctx, pTiming) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Configure Refresh mode
  * @param  Ctx : Component object pointer
  * @param  Interface : Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2 
  * @param  RefreshMode : Could be W9825G6JB_CMD_AUTOREFRESH_MODE or
  *                      W9825G6JB_CMD_SELFREFRESH_MODE
  * @retval error status
  */
int32_t W9825G6JB_RefreshMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface, uint32_t RefreshMode) 
{
  Command.CommandMode            = RefreshMode;
  Command.CommandTarget          = Interface;
  Command.AutoRefreshNumber      = 8;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(Ctx, &Command, W9825G6JB_TIMEOUT) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Set the device refresh rate
  * @param  Ctx : Component object pointer
  * @param  RefreshCount : The refresh rate to be programmed
  * @retval error status
  */
int32_t W9825G6JB_RefreshRate(SDRAM_HandleTypeDef *Ctx, uint32_t RefreshCount) 
{
  /* Set the device refresh rate */
  if(HAL_SDRAM_ProgramRefreshRate(Ctx, RefreshCount) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Enter Power mode
  * @param  Ctx : Component object pointer
  * @param  Interface : Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  * @retval error status
  */
int32_t W9825G6JB_EnterPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface) 
{
  Command.CommandMode            = W9825G6JB_POWERDOWN_MODE_CMD;
  Command.CommandTarget          = Interface;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(Ctx, &Command, W9825G6JB_TIMEOUT) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Exit Power mode
  * @param  Ctx : Component object pointer
  * @param  Interface : Could be FMC_SDRAM_CMD_TARGET_BANK1 or FMC_SDRAM_CMD_TARGET_BANK2
  * @retval error status
  */
int32_t W9825G6JB_ExitPowerMode(SDRAM_HandleTypeDef *Ctx, uint32_t Interface) 
{
  Command.CommandMode            = W9825G6JB_NORMAL_MODE_CMD;
  Command.CommandTarget          = Interface;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  if(HAL_SDRAM_SendCommand(Ctx, &Command, W9825G6JB_TIMEOUT) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @brief  Sends command to the SDRAM bank.
  * @param  Ctx : Component object pointer
  * @param  SdramCmd : Pointer to SDRAM command structure 
  * @retval SDRAM status
  */  
int32_t W9825G6JB_Sendcmd(SDRAM_HandleTypeDef *Ctx, FMC_SDRAM_CommandTypeDef *SdramCmd)
{
  if(HAL_SDRAM_SendCommand(Ctx, SdramCmd, W9825G6JB_TIMEOUT) != HAL_OK)
  {
    return W9825G6JB_ERROR;
  }
  else
  {
    return W9825G6JB_OK;
  }
}

/**
  * @}
  */ 

/** @defgroup W9825G6JB_Private_Functions W9825G6JB Private Functions
  * @{
  */ 

/**
  * @brief This function provides accurate delay (in milliseconds)
  * @param Delay: specifies the delay time length, in milliseconds
  * @retval W9825G6JB_OK
  */
static int32_t W9825G6JB_Delay(uint32_t Delay)
{  
  uint32_t tickstart;
  tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < Delay)
  {
  }
  return W9825G6JB_OK;
}

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
