
/*
 * Auto generated Run-Time-Environment Component Configuration File
 *      *** Do not modify ! ***
 *
 * Project: 'Blinky'
 * Target:  'Simulation'
 */

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H


/*
 * Define the Device Header File:
 */
#if defined CHIP_QCX212 || defined CHIP_QCX212_Z0
#define CMSIS_device_header "qcx212.h"
#elif defined CHIP_QCX212S
#define CMSIS_device_header "qcx212s.h"
#endif

#define RTE_CMSIS_RTOS2                 /* CMSIS-RTOS2 */
        #define RTE_CMSIS_RTOS2_FreeRTOS        /* CMSIS-RTOS2 FreeRTOS */
//#define RTE_Compiler_EventRecorder
//#define RTE_Compiler_EventRecorder_DAP
#define RTE_RTOS_FreeRTOS_CONFIG_RTOS2  /* RTOS FreeRTOS Config for CMSIS RTOS2 API */
#define RTE_RTOS_FreeRTOS_CORE          /* RTOS FreeRTOS Core */
#define RTE_RTOS_FreeRTOS_EVENTGROUPS   /* RTOS FreeRTOS Event Groups */
#ifdef HEAP_4_ENABLE
#define RTE_RTOS_FreeRTOS_HEAP_4        /* RTOS FreeRTOS Heap 4 */
#endif //HEAP_4_ENABLE
#define RTE_RTOS_FreeRTOS_TIMERS        /* RTOS FreeRTOS Timers */

#ifdef HEAP_5_ENABLE
#define RTE_RTOS_FreeRTOS_HEAP_5	/* RTOS FreeRTOS Heap 5 [ merged with heap 4 by QC ] */
#endif //HEAP_5_ENABLE

#endif /* RTE_COMPONENTS_H */
