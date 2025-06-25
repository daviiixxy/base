
#ifndef RAMBOOT_QCX212_H
#define RAMBOOT_QCX212_H

#include <stdbool.h>
#include <stdint.h>

#ifndef RAM_BOOT_RET16K
#define RAM_BOOT_RET16K
#define RAM_BOOT_RET16K_CODE      __attribute__((__section__(".ramBootCode")))
#define RAM_BOOT_RET16K_RWDATA      __attribute__((__section__(".ramBootRWData")))
#define RAM_BOOT_RET16K_ZIDATA      __attribute__((__section__(".ramBootZIData")))
#define UNINIT_RET16K_ZIDATA      __attribute__((__section__(".UnInitData16K")))

#endif

#ifndef USED
#define USED      __attribute__((used))
#endif


void Mcu_NMI_Handler(void);
void Mcu_HardFault_Handler(void);
void Mcu_MemManage_Handler(void);
void Mcu_BusFault_Handler(void);
void Mcu_UsageFault_Handler(void);
void Mcu_SVC_Handler(void);
void Mcu_DebugMon_Handler(void);
void Mcu_PendSV_Handler(void);
void Mcu_Systick_Handler(void);
void Mcu_RTC_WakeupIntHandler(void);
void Mcu_Pad0_WakeupIntHandler(void);
void Mcu_Pad1_WakeupIntHandler(void);
void Mcu_Pad2_WakeupIntHandler(void);
void Mcu_Pad3_WakeupIntHandler(void);
void Mcu_Pad4_WakeupIntHandler(void);
void Mcu_Pad5_WakeupIntHandler(void);
void Mcu_Peripheral_Handler(void);
void Mcu_Default_Handler(void);
void Mcu_Mode_SystemInit(void);
void Mcu_Mode_Precinit(void);
void Mcu_Mode_Main(uint32_t target_rtc, uint8_t slpDepth);




typedef struct
{
    uint32_t PhyWakeupSCCounter;
	uint32_t mcuModeEnterThd;
	uint32_t firstMcuModeSlpTime;
	bool mcu_mode_en;
	bool mcu_mode;
	uint8_t flash_off;
    uint8_t SlpDepth;
}mcumode_info_t;

void pmuPowerOnFlash(uint32_t wakeupTime);
void ramBootSaveWakeupSrc(void);
void mcu_go_sleep2(void);
void mcu_go_sleep1(void);



#endif

