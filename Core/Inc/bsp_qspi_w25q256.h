/**
  **********************************************************************************
  * File Name          : BSP_Flash_W25Q256.h
  * Auther             : Dragon Lin (Dragon_Lin@asus.com)
  * Description        : Winbond W23Q256 Serial Flash Memory With Dual, Quad SPI register
  *                      
  **********************************************************************************
  *
  * Copyright (c) 2019 AsusTek Computer Inc.  All rights reserved.
  *
  **********************************************************************************
  */
#ifndef BSP_QSPI_W25Q256_H
#define BSP_QSPI_W25Q256_H

#define QSPI_OK				0
#define QSPI_ERROR			1 
#define QSPI_NOT_SUPPORTED	2



/* W25Q256 Standard SPI Instructions */
#define W25Q256_WRITE_ENABLE                0x06 /* Write Enable instruction */
#define W25Q256_VOLATILE_SR_WRITE_ENABLE    0x50 /* Volatile SR Write Enable */
#define W25Q256_WRITE_DISABLE               0x04 /* Write Disable instruction */
#define W25Q256_RELEASE_POWER_DOWN_ID       0xAB /* Release from Deep Power-down */
#define W25Q256_MANUFACT_DEVICE_ID          0x90 /* Read Electronic Manufacturer and Device ID */
#define W25Q256_JEDEC_ID                    0x9F /* Read Identification */
#define W25Q256_READ_UNIQUE_ID              0x4B /*   */
#define W25Q256_READ_DATA                   0x03 /* Read Data */
#define W25Q256_FAST_READ_DATA              0x0B /* Fast Read Data */
#define W25Q256_PAGE_PROGRAM                0x02 /* Page Program */
#define W25Q256_SECTOR_ERASE_4K             0x20 /* Sector Erase (4KB) */
#define W25Q256_SECTOR_ERASE_4K_4B_ADDR     0x21 /* Sector Erase (4KB) 4Byte address*/
#define W25Q256_BLOCK_ERASE_32K             0x52 /* Block Erase (32KB) */
#define W25Q256_BLOCK_ERASE_64K             0xD8 /* Block Erase (64KB) */
#define W25Q256_CHIP_ERASE                  0xC7 /* 0x60 // Chip Erase */
#define W25Q256_READ_STATUS_REG1            0x05 /* Read Status Register 1 instruction */
#define W25Q256_WRITE_STATUS_REG1           0x01 /* Write Status Register 1 instruction */
#define W25Q256_READ_STATUS_REG2            0x35 /* Read Status Register 2 instruction */
#define W25Q256_WRITE_STATUS_REG2           0x31 /* Write Status Register 2 instruction */
#define W25Q256_READ_STATUS_REG3            0x15 /* Read Status Register 3 instruction */
#define W25Q256_WRITE_STATUS_REG3           0x11 /* Write Status Register 3 instruction */
#define W25Q256_READ_SFDP_REG               0x5A /* Read SFDP */
#define W25Q256_ERASE_SECURITY_REG          0x44 /* Erase Security Register */
#define W25Q256_PROGRAM_SECURITY_REG        0x42 /* Program Security Register */
#define W25Q256_READ_SECURITY_REG           0x48 /* Read Security Register */
#define W25Q256_GLOBAL_BLOCK_LOCK           0x7E /*  */
#define W25Q256_GLOBAL_BLOCK_UNLOCK         0x98 /*  */
#define W25Q256_READ_BLOCK_LOCK             0x3D /*  */
#define W25Q256_INDIVIDUAL_BLOCK_LOCK       0x36 /*  */
#define W25Q256_INDIVIDUAL_BLOCK_UNLOCK     0x39 /*  */
#define W25Q256_ERASE_PROGRAM_SUSPEND       0x75 /*  */
#define W25Q256_ERASE_PROGRAM_RESUME        0x7A /*  */
#define W25Q256_POWER_DOWN                  0xB9 /*  */
#define W25Q256_ENABLE_RESET                0x66 /*  */
#define W25Q256_RESET                       0x99 /*  */
/* W25Q256 Dual SPI Instructions */
#define W25Q256_FAST_READ_DUAL_OUTPUT       0x3B /* Dual Output mode */
#define W25Q256_FAST_READ_DUAL_IO           0xBB /*  */
#define W25Q256_MANUFACT_DEVICE_ID_DUALIO   0x92 /* Manufacture Device ID by Dual IO */
/* W25Q256 Quad SPI Instructions */
#define W25Q256_QUAD_PAGE_PROGRAM           0x32 /*  */
#define W25Q256_QUAD_PAGE_PROGRAM_4B_ADDR   0x34 /*  */
#define W25Q256_FAST_READ_QUAD_DATA         0x6B /*  */
#define W25Q256_MANUFACT_DEVICE_ID_QUAD     0x94 /* Manufacture Device ID by Quad IO */
#define W25Q256_READ_JEDEC_ID    			0x9F // Read Identification
#define W25Q256_FAST_READ_QUAD_IO           0xEB /*  */
#define W25Q256_FAST_READ_QUAD_IO_4B_ADDR   0xEC /*  */

#define W25Q256_SET_BURST_WITH_WRAP         0x77 /*  */
#define W25Q256_ENTER_4BYTE_ADDR_Mode		0xB7
#define W25Q256_EXIT_4BYTE_ADDR_Mode		0xB9

#define W25Q256_DUMMY_BYTE                  0xFF

#define W25Q256_MAPPED_ADDR					((uint32_t)0x90000000)

#define W25Q256_BLOCK_SIZE					0x10000     /*  64 KBytes per Sector */
#define W25Q256_SECTOR_SIZE              	0x1000      /*   4 KBytes per Sector */
#define W25Q256_PAGE_SIZE              		0x100       /*   256 Bytes per Sector */

#define W25Q256_FLASH_SIZE                  ((uint32_t)0x02000000)    /*  256 MBits => 32 MBytes */

#define W25Q256_SECTOR_NUMBER                (W25Q256_FLASH_SIZE/W25Q256_SECTOR_SIZE)      /*    64 Sectors    of  64 KBytes */

#define W25Q256_BULK_ERASE_MAX_TIME          100000  /* Chip Erase 80000 ~  400000 ms */
#define W25Q256_SECTOR_ERASE_MAX_TIME        2000    /* 64KB Erase   150 ~   2000 ms */
#define W25Q256_SUBSECTOR_ERASE_MAX_TIME     450     /*  4KB Erase    50 ~    400 ms */
#define W25Q256_WRITE_STATUS_REG_MAX_TIME    20      /*               10 ~     15 ms */

/* Flag Status Register 1 */
#define W25Q256_FSR1_BUSY                    ((uint8_t)0x01) /*!< Busy */
#define W25Q256_FSR1_WEL                     ((uint8_t)0x02) /*!< Write Enable Latch */
/* Flag Status Register 2 */
#define W25Q256_FSR2_QE                      ((uint8_t)0x02) /*!< Quad Enable */
/* Flag Status Register 3 */
#define W25Q256_FSR3_DRV_100                 ((uint8_t)0x00) /*!< Driver Strength 100% */
#define W25Q256_FSR3_DRV_75                  ((uint8_t)0x20) /*!< Driver Strength  75% */
#define W25Q256_FSR3_DRV_50                  ((uint8_t)0x40) /*!< Driver Strength  50% */
#define W25Q256_FSR3_DRV_25                  ((uint8_t)0x60) /*!< Driver Strength  25%, Default */

extern uint8_t BSP_QSPI_W25Q256_Init(void);
extern uint8_t BSP_QSPI_W25Q256_FastRead_QuadIO_4ByteAddr(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
extern uint8_t BSP_QSPI_W25Q256_Erase_Sector_4K_4ByteAddr(uint32_t BlockAddress);
extern uint8_t BSP_QSPI_W25Q256_QuadPageWrite_4ByteAddr(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
extern uint8_t BSP_QSPI_W25Q256_Erase_Chip(void);
extern uint8_t BSP_QSPI_W25Q256_ReadJedecID(uint32_t* JEDEC_ID);
extern uint8_t BSP_QSPI_W25Q256_EnableMemoryMappedMode(void);

#endif /* BSP_QSPI_W25Q256_H */

