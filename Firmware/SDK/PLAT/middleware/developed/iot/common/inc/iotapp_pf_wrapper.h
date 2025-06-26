#ifndef _IOTAPP_PF_WRAPPER_H
#define _IOTAPP_PF_WRAPPER_H

#include "bsp.h"
#include "os_exception.h"
#include "ps_lib_api.h"

extern UINT32 gTotalHeapSize;
typedef struct _mem_heap_totals_type_ {
	int64_t		free_bytes;
	int64_t		total_physical_bytes;
}mem_heap_totals_type;

#define IOT_BATTERY_NORMAL	0
#define IOT_BATTERY_NOTPRESENT	0xFF
#define IOT_BATTERY_FAILURE		0xFE

extern size_t xPortGetFreeHeapSize( void );

int iotapp_Get_Battery_Status(uint8_t *Batterylevel);

static inline uint8_t *get_device_imei_number(void)
{
	uint8_t *imei = calloc(1,18); //imei would not be longer than 17 bytes
	if (imei != NULL && 0 == appGetImeiNumSync(imei))
	{
		return imei;
		//free(imei);
		//return NULL;
	}
	
	return NULL;
	//return imei;
}

static inline uint8_t *get_device_serial_number()
{
	uint8_t *sn = calloc(1,32); //serial no would not be longer than 32 bytes
	if (sn != NULL && 0 == appGetSNNumSync(sn))
	{
		free(sn);
		return NULL;
	}
	return sn;
}

static inline uint8_t *get_device_hw_version()
{
	return strdup(EVB_VERSION);
}

static inline uint8_t *get_device_sw_version()
{
	return strdup(SOFTVERSION);
}

static inline uint8_t *get_device_fw_version()
{
	return strdup(VERSION_INFO);
}

char *get_device_model_number(void);

char *get_device_manufacturer(void);

static inline void mem_heap_get_totals(mem_heap_totals_type *memP)
{
	if (memP == NULL) return;
	memP->total_physical_bytes = gTotalHeapSize;
	memP->free_bytes = xPortGetFreeHeapSize();
}

int8_t sys_time_set(uint32_t currTime);

static inline void sys_m_reset(void)
{
	EC_SystemReset();
	return;
}

int qc_decrypt_msg(char *in_dec_buffer, char *out_dec_buffer, uint32_t size);
int qc_encrypt_msg(char *in_enc_buffer, char *out_enc_buffer, uint32_t size);


#endif //_IOTAPP_PF_WRAPPER_H
