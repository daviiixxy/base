/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    nvram_flash.h
 * Description:  QCX212 NVRAM header file
 * History:      11/29/2017    Originated by cheng fang
 *
 ****************************************************************************/

#ifndef _NVRAM_FLASH_H
#define _NVRAM_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef WIN32
#if defined CHIP_QCX212 || defined CHIP_QCX212_Z0
#include "flash_qcx212.h"
#elif defined CHIP_QCX212S
#include "flash_qcx212s.h"
#endif
#define nvram_flash_init()	HAL_QSPI_Init()
#define nvram_flash_earse(a)	BSP_QSPI_Erase_Safe(a, 0x1000)
#define nvram_flash_write(a,b,c) BSP_QSPI_Write_Safe(a,b,c)
#define nvram_flash_earse_raw(a)	BSP_QSPI_Erase_Sector(a)
#define nvram_flash_write_raw(a,b,c) BSP_QSPI_Write(a,b,c)
#define nvram_flash_read(a,b,c) BSP_QSPI_Read_Safe(a,b,c)
#else
#include "ramflash.h"
#define nvram_flash_init() init_ramflash()
#define nvram_flash_earse(a) ramflash_erase(a)
#define nvram_flash_write(a,b,c) ramflash_write(a,b,c)
#define nvram_flash_earse_raw(a)	ramflash_erase(a)
#define nvram_flash_write_raw(a,b,c) ramflash_write(a,b,c)
#define nvram_flash_read(a,b,c) ramflash_read(a,b,c)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _NVRAM_FLASH_H */
