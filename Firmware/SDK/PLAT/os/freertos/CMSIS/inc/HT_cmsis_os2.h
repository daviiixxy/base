#ifndef __HT_CMSIS_OS2_H__
#define __HT_CMSIS_OS2_H__

#include "cmsis_os2.h"

osStatus_t HT_osKernelInit(void);
osKernelState_t HT_osKernelGetState(void);
osStatus_t HT_osKernelStart(void);

#endif /* __HT_CMSIS_OS2_H__ */
