/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    nvram.h
 * Description:  Caterpiller interrupt controller header file
 * History:      11/29/2017    Originated by cheng fang
 *
 ****************************************************************************/

#ifndef _NVRAM_H
#define _NVRAM_H

#ifdef __cplusplus
 extern "C" {
#endif
#ifndef WIN32
#if defined CHIP_QCX212 || defined CHIP_QCX212_Z0
#include "qcx212.h"
#elif defined CHIP_QCX212S
#include "qcx212s.h"
#endif

#else
#pragma pack(1)
#include "win32_config.h"
#endif

#define NVRAM_SECTOR_SIZE	4096
#define NVRAM_PAGE_SIZE		256

typedef enum _NVRAM_ERR
{
	NVRAM_OK=0,
	NVRAM_ERR,
	NVRAM_FORMAT_ERR,
	NVRAM_ERASE_FLASH_ERR,
	NVRAM_WRITE_FLASH_ERR,
	NVRAM_CHECK_ITEM_ERR,
	NVRAM_CHECK_ITEM_NO_EXIST,
} NVRAM_ERR_E;

typedef enum NVBn
{
	NV_BANK0 = 0x0,
	NV_BANK1,
	NV_FAC,
	NV_BANK_MAX,
} NV_BANK_Type;

typedef enum NVFAC
{
	SAVE_ALL = 0x0,
	SAVE_CALI,
	SAVE_OTHER,
} NV_SAVEFAC_E;

typedef enum NVn
{
	NV1 = 0x0,
	NV2,
	NV3,
	NV4,
	NV5,
	NV6,
	NV7,
	NV8,
	NV9,
	NV10,
	NV_MAX,
} NV_Type;

typedef struct
{
	uint32_t nv_flag;
	uint32_t time_counter;
	uint16_t used_size;
	uint16_t chksum;
} NV_HEADER;

NVRAM_ERR_E nvram_init(void);
uint32_t nvram_read(NV_Type nvt,uint8_t * data,uint32_t size,uint32_t offset);
uint32_t nvram_write(NV_Type nvt,uint8_t * data,uint32_t size);
uint32_t nvram_get_addr(NV_Type nvt);
uint32_t nvram_sav2fac(void);
uint32_t nvram_sav2fac_at(NV_SAVEFAC_E sel);

uint16_t nvram_chksum(void *dataptr, uint16_t len);
uint16_t nvram_crc16_ccitt(void *dataptr, int len);

#ifdef __cplusplus
}
#endif

#endif /* _NVRAM_H */
