/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    flash_qcx212.h
 * Description:  QCX212 flash header file
 * History:      11/29/2017    Originated by bchang
 *
 ****************************************************************************/

#ifndef _FLASH_QCX212_H
#define _FLASH_QCX212_H
#include "qcx212_internal.h"
#include "qcx212.h"

//#define FLASH_PUYA_SUPPORT
/* Private typedef -----------------------------------------------------------*/
//#define  sFLASH_ID                       0xEF3015     //W25X16
//#define  sFLASH_ID                       0xEF4015	    //W25Q16
#define  sFLASH_ID                         0XEF6016     //W25Q32
//#define  sFLASH_ID                       0XEF4017     //W25Q64
//#define  sFLASH_ID                       0XEF4018     //W25Q128
#define FLASH_PUYA_MFID                    0x85
#define FLASH_GD_MFID                      0xC8




/* W25Q32BV Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE            23     /*0--23 Address bus width to access whole memory space */
#define QSPI_PAGE_SIZE             256	  /*256B page size*/
#define BSP_QSPI_WRITE_GRAN_SIZE_ALIGNED_16(size) ((size + 0xf)&(~0xf))
#define BSP_QSPI_WRITE_GRAN_SIZE gBspQspiWriteGranSize
#define BSP_QSPI_RT_STATISTIC 0


/* QSPI Info */
typedef struct {
  uint32_t FlashSize;          /*!< Size of the flash */
  uint32_t EraseSectorSize;    /*!< Size of sectors for the erase operation */
  uint32_t EraseSectorsNumber; /*!< Number of sectors for the erase operation */
  uint32_t ProgPageSize;       /*!< Size of pages for the program operation */
  uint32_t ProgPagesNumber;    /*!< Number of pages for the program operation */
} QSPI_Info;


typedef enum{
    ERASE_SECTOR_TYPE = 0,
    ERASE_32K_BLK_TYPE,
    ERASE_64K_BLK_TYPE,
}ERASE_TYPE;


typedef enum {
    OP_PROGRESS_ERASE = 0,
    OP_PROGRESS_PROGRAM = 1
}FLASH_OP_PROGRESS_TYPE;

typedef struct
{
    uint8_t                MFID;    /* Flash Manufacture ID, 0xc8/0x85 GD/puya */
}TFlashInfo;

/* Private define ------------------------------------------------------------*/
/*命令定义-开头*******************************/
/**
  * @brief  W25Q32BV Configuration
  */
#define W25Q32BV_FLASH_SIZE                  0x400000 /* 32 Mbits => 4MBytes */
#define W25Q32BV_BLOCK_SIZE                  0x10000   /* 64 blocks of 64KBytes */
#define W25Q32BV_SECTOR_SIZE                   0x1000    /* 4096 subsectors of 4kBytes */
#define W25Q32BV_PAGE_SIZE                   0x100     /* 65536 pages of 256 bytes */

#define W25Q32BV_DUMMY_CYCLES_FAST_READ                  8  //0x0b instruction
#define W25Q32BV_DUMMY_CYCLES_FAST_READ_DUAL_OUTPUT      8 //0x3b instruction
#define W25Q32BV_DUMMY_CYCLES_FAST_READ_QUAD_OUTPUT      8 //0x6b instruction
#define W25Q32BV_DUMMY_CYCLES_FAST_READ_QUAD_IO          4 //0xeb instruction

#define W25Q32BV_BULK_ERASE_MAX_TIME         250000
#define W25Q32BV_SECTOR_ERASE_MAX_TIME       3000
#define W25Q32BV_SUBSECTOR_ERASE_MAX_TIME    800

#define W25Q32BV_SET_WRITE_EN_MAX_TIME    100




/**
  * @brief  W25Q32BV Commands--totally 35 commands
  */

/*********GROUP 1:16 commands*******************************************/
/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

#define WRITE_VOLATILE_REG_CMD                    0x50

/* Register Operations */
#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define WRITE_STATUS_REG1_CMD                 0x01
#define WRITE_STATUS_REG2_CMD                 0x31

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QUAD_INPUT_PAGE_PROG_CMD             0x32

/* Erase Operations */
#define SECTOR_ERASE_CMD                     0x20
#define BLOCK_ERASE_32K_CMD                     0x52
#define BLOCK_ERASE_64K_CMD                     0xD8
#define CHIP_ERASE_CMD                       0xC7//or 0x60



#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

#define PUYA_ERASE_RESUME_CMD              0x30
#define PUYA_ERASE_SUSPEND_CMD             0xB0


#define PWR_DOWN_CMD               0xB9

#define CONTINUOUS_READ_MODE_RESET_CMD               0xFF

#define RESET_ENABLE_QUAD_SPI				0x66
#define RESET_QUAD_SPI						0x99

/*********GROUP 2:9 commands*******************************************/
/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_INOUT_FAST_READ_CMD             0xEB

#define QUAD_INOUT_WORD_READ_CMD             0xE7
#define QUAD_INOUT_QCTAL_WORD_READ_CMD             0xEB3
#define SET_BURST_WITH_WRAP_CMD               0x77


/*********GROUP 3:10 commands*******************************************/

#define REL_PWRD_DEV_ID_CMD                          0xAB

/* Identification Operations */
#define READ_ID_CMD                          0x90
#define DUAL_READ_ID_CMD                     0x92
#define QUAD_READ_ID_CMD                     0x94
#define READ_JEDEC_ID_CMD                    0x9F

#define READ_UNIQUE_ID_CMD                    0x4B
#define READ_SFDP_REG_CMD                    0x5A
#define ERASE_SECURITY_REG_CMD                    0x44
#define PROG_SECURITY_REG_CMD                    0x42
#define READ_SECURITY_REG_CMD                    0x48



/* Flag Status Register */
#define W25Q32BV_FSR1_BUSY                    ((uint8_t)0x01)    /*!< busy */
#define W25Q32BV_FSR1_WREN                    ((uint8_t)0x02)    /*!< write enable */
#define W25Q32BV_FSR2_QE                      ((uint8_t)0x02)    /*!< quad enable */
#define W25Q32BV_FSR2_QE_BP_3M                ((uint8_t)0x42)    /*!< quad enable and CMP=1 */
#define W25Q32BV_FSR1_BP_3M                   ((uint8_t)0x14)    /*!< protect 0x0000-0x2fffff bottom 3MB */

#define W25Q32BV_FSR1_BP_64K                  ((uint8_t)0x24)    /*!< protect 0x0000-0x7fff bottom 32KB */
#define W25Q32BV_FSR1_BP_2M                   ((uint8_t)0x38)    /*!< protect 0x0000-0x1fffff bottom 2MB */


/* CONTINUOUS_READ_MODE Register */
#define CONTINUOUS_READ_ENABLE                     ((uint8_t)0x20)    /*!< busy */
#define CONTINUOUS_READ_DISABLE                    ((uint8_t)0x00)    /*!< write enable */

#define SUS1_FLAG_ERS_Msk 0x80
#define SUS2_FLAG_PRG_Msk 0x04
#define SUS_FLAG_Msk (SUS1_FLAG_ERS_Msk|SUS2_FLAG_PRG_Msk)


uint8_t BSP_QSPI_Init(void);
uint8_t BSP_QSPI_Erase_Sector(uint32_t BlockAddress);
uint8_t BSP_QSPI_Erase_Block(uint32_t BlockAddress);
uint8_t BSP_QSPI_Erase_Sector_Cmd(uint32_t SectorAddress);
uint8_t BSP_QSPI_Erase_Block_Cmd(uint32_t BlockAddress);
uint8_t BSP_QSPI_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t BSP_QSPI_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_QSPI_Write_Exception(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_QSPI_XIP_Mode_Enable(void);
uint8_t BSP_QSPI_XIP_Mode_Disable(void);


uint32_t QSPI_FLASH_ReadDeviceID(void);
uint32_t QSPI_FLASH_ReadID(void);
uint8_t QSPI_CheckQEnFlag(void);

void Flash_MFID_Set(uint8_t MFId);
uint8_t FlashMFID_Check(uint8_t MFId);
uint8_t BSP_QSPI_Write_Status_Reg(uint8_t reg1,uint8_t reg2);
BOOL FLASH_ProtectCheck(uint32_t OperAddr, uint32_t Size);
void FLASH_RestoreProtect(void);

extern uint8_t BSP_QSPI_Check_ROAddr(uint32_t Addr);
uint8_t BSP_QSPI_Check_ROSpace(uint32_t Addr, uint32_t Size);
uint8_t BSP_QSPI_SWReset(void);

#endif

