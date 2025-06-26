#ifndef SW_CNT_H
#define SW_CNT_H

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    uint32_t old_sc;        // store slow cnt
    uint16_t sw2048_res;
	uint32_t valid;
    uint64_t sw2048_cnt;        // sw timer with 2048 HZ
    
}SW_CNT_T;


void SwCntSetValidFlag(bool valid);
uint64_t SwCntGet(void);
void SwCntPowerOn(void);
void SwTimerIntEnter(void);
void SwCntUpdate(uint32_t current_sc, bool fromWakeup, uint64_t sleep_scdiff );

uint32_t SwCntGetOldSc(void);
//void SwGetBcValue(uint32_t *bcHighValue, uint32_t *bcLowValue);
void SwCntWakeup(uint64_t PhyMeasSleepCycle, uint32_t current_sc);
void SwCntPreSleep(uint32_t current_sc);
void SwTimerRollAvoidTimerInit(void);



#endif
