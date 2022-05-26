/**
  **********************************************************************************
  * File Name          : BSP_QSPI_W25Q256.c
  * Auther             : Dragon Lin (Dragon_Lin@asus.com)
  * Description        : QuadSPI Flash  Driver For Winbond W25Q256
  *                      
  **********************************************************************************
  *
  * Copyright (c) 2019 AsusTek Computer Inc.  All rights reserved.
  *
  **********************************************************************************
  */

#include <stdint.h>
#include "quadspi.h"
#include "bsp_qspi_w25q256.h"




static uint8_t BSP_QSPI_W25Q256_WriteEnable(void)
{
    QSPI_CommandTypeDef     s_command = {0};
    QSPI_AutoPollingTypeDef s_config = {0};
    
    /* Enable write operations */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_WRITE_ENABLE;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Configure automatic polling mode to wait for write enabling */  
    s_config.Match              = W25Q256_FSR1_WEL;
    s_config.Mask               = W25Q256_FSR1_WEL;
    s_config.MatchMode          = QSPI_MATCH_MODE_AND;
    s_config.StatusBytesSize    = 1;
    s_config.Interval           = 0x10;
    s_config.AutomaticStop      = QSPI_AUTOMATIC_STOP_ENABLE;
    
    s_command.Instruction       = W25Q256_READ_STATUS_REG1;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.NbData            = 1;
    
    if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    return QSPI_OK;
}

static uint8_t BSP_QSPI_W25Q256_AutoPollingMemReady(uint32_t Timeout)
{
    QSPI_CommandTypeDef     s_command = {0};
    QSPI_AutoPollingTypeDef s_config = {0};
    
    /* Configure automatic polling mode to wait for memory ready */  
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_READ_STATUS_REG1;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    
    s_config.Match              = 0x00;
    s_config.Mask               = W25Q256_FSR1_BUSY;
    s_config.MatchMode          = QSPI_MATCH_MODE_AND;
    s_config.StatusBytesSize    = 1;
    s_config.Interval           = 0x80;
    s_config.AutomaticStop      = QSPI_AUTOMATIC_STOP_ENABLE;
    
    if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, Timeout) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    return QSPI_OK;
}

static uint8_t BSP_QSPI_W25Q256_AutoPolling_QE_Ready(uint32_t Timeout)
{
    QSPI_CommandTypeDef     s_command = {0};
    QSPI_AutoPollingTypeDef s_config = {0};
    
    /* Configure automatic polling mode to wait for memory ready */  
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_READ_STATUS_REG2;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    
    s_config.Match              = W25Q256_FSR2_QE;
    s_config.Mask               = W25Q256_FSR2_QE;
    s_config.MatchMode          = QSPI_MATCH_MODE_AND;
    s_config.StatusBytesSize    = 1;
    s_config.Interval           = 0x40;
    s_config.AutomaticStop      = QSPI_AUTOMATIC_STOP_ENABLE;
    
    if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, Timeout) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_ResetMemory(void)
{
    QSPI_CommandTypeDef s_command = {0};
	
    /* Initialize the reset enable command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_ENABLE_RESET;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    
    /* Send the command */
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Send the reset memory command */
    s_command.Instruction       = W25Q256_RESET;
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Configure automatic polling mode to wait the memory is ready */  
    if (BSP_QSPI_W25Q256_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_Enter4ByteMode(void)
{
    QSPI_CommandTypeDef s_command = {0};
	
    /* Initialize the reset enable command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_ENTER_4BYTE_ADDR_Mode;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    
    /* Send the command */
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
	#if 0
    /* Configure automatic polling mode to wait the memory is ready */  
    if (BSP_QSPI_W25Q256_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
	#endif
    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_Init(void)
{
    QSPI_CommandTypeDef s_command = {0};
    uint8_t wSFR[1];
	uint32_t Flash_ID;
    
    /* QSPI memory reset */
    if (BSP_QSPI_W25Q256_ResetMemory() != QSPI_OK)
    {
        return QSPI_NOT_SUPPORTED;
    }

	BSP_QSPI_W25Q256_ReadJedecID(&Flash_ID);

	
    /* Write Enable */
    if (BSP_QSPI_W25Q256_WriteEnable() != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Set Driver Strength */
    wSFR[0] = W25Q256_FSR3_DRV_100;
    /* Set status register for Driver Strength */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_WRITE_STATUS_REG3;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.NbData            = 1;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    /* Configure the command */
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    /* Transmit the data */
    if (HAL_QSPI_Transmit(&hqspi, &wSFR[0], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    /* automatic polling mode to wait for memory ready */  
    if (BSP_QSPI_W25Q256_AutoPollingMemReady(W25Q256_WRITE_STATUS_REG_MAX_TIME) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Write Enable */
    if (BSP_QSPI_W25Q256_WriteEnable() != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    /* Set Quad Enable */
    wSFR[0] = W25Q256_FSR2_QE;
    /* Set status register for Quad Enable,the Quad IO2 and IO3 pins are enable */
    s_command.Instruction       = W25Q256_WRITE_STATUS_REG2;
    /* Configure the command */
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    /* Transmit the data */
    if (HAL_QSPI_Transmit(&hqspi, &wSFR[0], HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    /* automatic polling mode to wait for memory ready */  
    if (BSP_QSPI_W25Q256_AutoPollingMemReady(W25Q256_WRITE_STATUS_REG_MAX_TIME) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    
    if (BSP_QSPI_W25Q256_AutoPolling_QE_Ready(W25Q256_WRITE_STATUS_REG_MAX_TIME) != QSPI_OK)
    {
        return QSPI_ERROR;
    }

    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_FastRead_QuadIO_4ByteAddr(uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
    QSPI_CommandTypeDef s_command = {0};
    
    /* Initialize the read command */
    s_command.Instruction           = W25Q256_FAST_READ_QUAD_IO_4B_ADDR;
    s_command.InstructionMode       = QSPI_INSTRUCTION_1_LINE;
    s_command.Address               = ReadAddr;
    s_command.AddressMode           = QSPI_ADDRESS_4_LINES;
    s_command.AddressSize           = QSPI_ADDRESS_32_BITS;
    s_command.AlternateBytes        = 0xFFFFFFFF;
    s_command.AlternateByteMode     = QSPI_ALTERNATE_BYTES_4_LINES;
    s_command.AlternateBytesSize    = QSPI_ALTERNATE_BYTES_8_BITS;
    s_command.DummyCycles           = 4;
	s_command.DataMode              = QSPI_DATA_4_LINES;
    s_command.NbData                = Size;
    s_command.DdrMode               = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle      = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode              = QSPI_SIOO_INST_EVERY_CMD;
    
    /* Configure the command */
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Reception of the data */
    if (HAL_QSPI_Receive(&hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_Erase_Sector_4K_4ByteAddr(uint32_t BlockAddress)
{
    QSPI_CommandTypeDef s_command = {0};
    
    /* Initialize the erase command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_SECTOR_ERASE_4K_4B_ADDR;
    s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
    s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
    s_command.Address           = BlockAddress;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    
    /* Enable write operations */
    if (BSP_QSPI_W25Q256_WriteEnable() != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Send the command */
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Configure automatic polling mode to wait for end of erase */  
    if (BSP_QSPI_W25Q256_AutoPollingMemReady(W25Q256_SUBSECTOR_ERASE_MAX_TIME) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    
    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_QuadPageWrite_4ByteAddr(uint8_t* pData, uint32_t WriteAddr, uint32_t Size)
{
    QSPI_CommandTypeDef s_command = {0};
    uint32_t end_addr, current_size, current_addr;
    
    /* Calculation of the size between the write address and the end of the page */
    current_addr = 0;
    
    while (current_addr <= WriteAddr)
    {
        current_addr += W25Q256_PAGE_SIZE;
    }
    current_size = current_addr - WriteAddr;
    
    /* Check if the size of the data is less than the remaining place in the page */
    if (current_size > Size)
    {
        current_size = Size;
    }
    
    /* Initialize the adress variables */
    current_addr = WriteAddr;
    end_addr = WriteAddr + Size;
    
    /* Initialize the program command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_QUAD_PAGE_PROGRAM_4B_ADDR;
    s_command.AddressMode       = QSPI_ADDRESS_1_LINE;
    s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DummyCycles       = 0;
    s_command.DataMode          = QSPI_DATA_4_LINES;
	s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    
    /* Perform the write page by page */
    do
    {
        s_command.Address = current_addr;
        s_command.NbData  = current_size;
        /* Enable write operations */
        if (BSP_QSPI_W25Q256_WriteEnable() != QSPI_OK)
        {
            return QSPI_ERROR;
        }
        
        /* Configure the command */
        if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        
        /* Transmission of the data */
        if (HAL_QSPI_Transmit(&hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return QSPI_ERROR;
        }
        
        /* Configure automatic polling mode to wait for end of program */  
        if (BSP_QSPI_W25Q256_AutoPollingMemReady(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != QSPI_OK)
        {
            return QSPI_ERROR;
        }
    
        /* Update the address and size variables for next page programming */
        current_addr += current_size;
        pData += current_size;
        current_size = ((current_addr + W25Q256_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : W25Q256_PAGE_SIZE;
  } while (current_addr < end_addr);
  
  return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_Erase_Chip(void)
{
    QSPI_CommandTypeDef s_command = {0};
    
    /* Initialize the erase command */
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.Instruction       = W25Q256_CHIP_ERASE;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_NONE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    
    /* Enable write operations */
    if (BSP_QSPI_W25Q256_WriteEnable() != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Send the command */
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    
    /* Configure automatic polling mode to wait for end of erase */  
    if (BSP_QSPI_W25Q256_AutoPollingMemReady(W25Q256_BULK_ERASE_MAX_TIME) != QSPI_OK)
    {
        return QSPI_ERROR;
    }
    
    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_ReadJedecID(uint32_t* JEDEC_ID)
{
    QSPI_CommandTypeDef s_command = {0};
    uint8_t pData[3];
	
    /* Read JEDEC ID */
    s_command.Instruction       = W25Q256_READ_JEDEC_ID;
    s_command.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    s_command.AddressMode       = QSPI_ADDRESS_NONE;
    s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    s_command.DataMode          = QSPI_DATA_1_LINE;
    s_command.DummyCycles       = 0;
    s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
    s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;
    s_command.NbData            = 3;
	
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
    if (HAL_QSPI_Receive(&hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return QSPI_ERROR;
    }
	*JEDEC_ID = (uint32_t)pData[0] | ((uint32_t)pData[1] << 8) | ((uint32_t)pData[2] << 16);
//    printf("FlashID=0x%06X\n\r",*JEDEC_ID);

    return QSPI_OK;
}

uint8_t BSP_QSPI_W25Q256_EnableMemoryMappedMode(void)
{
	QSPI_MemoryMappedTypeDef s_MemMappedCfg = {0};
	QSPI_CommandTypeDef s_command = {0};

	/* Initialize the read command */
	s_command.Instruction           = W25Q256_FAST_READ_QUAD_IO_4B_ADDR;
	s_command.InstructionMode       = QSPI_INSTRUCTION_1_LINE;
	s_command.Address               = 0;
	s_command.AddressMode           = QSPI_ADDRESS_4_LINES;
	s_command.AddressSize           = QSPI_ADDRESS_32_BITS;
	s_command.AlternateBytes        = 0xFFFFFFFF;
	s_command.AlternateByteMode     = QSPI_ALTERNATE_BYTES_4_LINES;
	s_command.AlternateBytesSize    = QSPI_ALTERNATE_BYTES_8_BITS;
	s_command.DummyCycles           = 4;
	s_command.DataMode              = QSPI_DATA_4_LINES;
	s_command.NbData                = 0;
	s_command.DdrMode               = QSPI_DDR_MODE_DISABLE;
	s_command.DdrHoldHalfCycle      = QSPI_DDR_HHC_ANALOG_DELAY;
	s_command.SIOOMode              = QSPI_SIOO_INST_EVERY_CMD;

	s_MemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
	s_MemMappedCfg.TimeOutPeriod     = 1;

	if (HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_MemMappedCfg) != HAL_OK)
	{
		return QSPI_ERROR;
	}

	return QSPI_OK;
}

