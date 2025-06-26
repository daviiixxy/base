
#ifndef RAMBOOT_QCX212_H
#define RAMBOOT_QCX212_H


#ifndef MCU_CODE
#define MCU_CODE      __attribute__((__section__(".mcuCode")))
#endif

#ifndef MCU_RW_DATA
#define MCU_RW_DATA      __attribute__((__section__(".mcuRWData")))
#endif

#ifndef MCU_ZI_DATA
#define MCU_ZI_DATA      __attribute__((__section__(".mcuZIData")))
#endif


void Mcu_Mode_SystemInit(void);


void Mcu_Mode_Precinit(void);

void Mcu_Mode_Main(void);


#endif

