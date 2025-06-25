
#include <stdint.h>
#include "cmsis_compiler.h"
#include "ramboot_qcx212.h"


__WEAK void Mcu_Reset_Fork_Handler(void)
{
    extern void Mcu_Reset_Handler(void);

    Mcu_Reset_Handler();
}



__WEAK RAM_BOOT_RET16K_CODE void Mcu_NMI_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_HardFault_Handler(void)
{
    while(1);
}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_MemManage_Handler(void)
{
	while(1);

}


__WEAK RAM_BOOT_RET16K_CODE void Mcu_BusFault_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_UsageFault_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_SVC_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_DebugMon_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_PendSV_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Systick_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_RTC_WakeupIntHandler(void)
{
}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Pad0_WakeupIntHandler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Pad1_WakeupIntHandler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Pad2_WakeupIntHandler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Pad3_WakeupIntHandler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Pad4_WakeupIntHandler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Pad5_WakeupIntHandler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Peripheral_Handler(void)
{

}

__WEAK RAM_BOOT_RET16K_CODE void Mcu_Default_Handler(void)
{

}

__WEAK void Mcu_Mode_SystemInit(void)
{

}

__WEAK void Mcu_Mode_Precinit(void)
{

}

__WEAK void Mcu_Mode_Main(uint32_t target_rtc, uint8_t slpDepth)
{

}

