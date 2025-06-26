#ifndef _FLASH_QCX212_RT_H
#define _FLASH_QCX212_RT_H

/* QSPI Error codes */
#define QSPI_OK            ((uint8_t)0x00)
#define QSPI_ERROR         ((uint8_t)0x01)
#define QSPI_BUSY          ((uint8_t)0x02)
#define QSPI_NOT_SUPPORTED ((uint8_t)0x04)
#define QSPI_SUSPENDED     ((uint8_t)0x08)

uint8_t BSP_QSPI_Cfg_Gran_Size(uint16_t WriteGranSize);
uint8_t BSP_QSPI_Erase_Safe(uint32_t SectorAddress, uint32_t Size);
uint8_t BSP_QSPI_Write_Safe(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_QSPI_Read_Safe(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);

#endif
