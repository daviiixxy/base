
#ifndef BAT_MON_H
#define BAT_MON_H

#include <stdint.h>
#include <stdbool.h>

#define BATMON_ENABLE	1

#define V_THRESHOLD 2100

typedef struct
{
	bool bBatLow;
	uint8_t cnt;
}BatMonInfo_t;


void BatMonInit(void);

void BatMonStop(void);

bool BatVoltIsLow(void);

void BatMonRestart(void);

bool BatVoltIsLowCheckCurrentRaw(uint32_t sampleDelayUs);

bool BatVoltIsLowCheckBuffer(void);

bool BatVoltIsLowCheckCurrentOS(uint32_t sampleDelayUs);

int32_t BatMon_SampleVbatVoltagePolling(uint32_t timeout_ms, int32_t *rawData);

uint32_t BatMon_CalibrateRawCode(uint32_t input);

void BatMon_EfuseDataGet(uint16_t *code500, uint16_t *code900);

void BatVoltLowProcessRaw(void);


#endif

