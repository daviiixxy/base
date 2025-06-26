/**************************************************************************//**
 * @file     os_exception.h
 * @brief    CMSIS OS Tick header file
 * @version  V1.0.0
 * @date     05. June 2017
 ******************************************************************************/
/*
 * Copyright (c) 2017-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OS_EXCEPTION_H
#define OS_EXCEPTION_H
#include "cmsis_compiler.h"
#include "commontypedef.h"
#include "mem_map.h"

#define EC_FUNC_CALL_ADDR_DEPTH         4
#define EC_ASSERT_FUNC_CALL_ADDR_DEPTH  4
#define EC_EXCEP_STACK_DEPTH            32
#define EC_EXCEP_SECTOR_SIZE            4096
#define EC_EXCEP_MAGIC_NUMBER           (0x00ec00ec)

#define EC_FLASH_BASE_ADDR              FLASH_XIP_ADDR
#define EC_EXCEP_FLASH_SECTOR_BASE      EC_EXCEPTION_FLASH_BASE
#define EC_EXCEP_FLASH_BASE_ADDR        (EC_FLASH_BASE_ADDR+EC_EXCEP_FLASH_SECTOR_BASE)
#define EC_EXCEP_TASK_NAME_LEN          12


#define EC_SP_PSP_FLAG                  0x4

#define EC_REG_SYS_CTRL_STATE   (*(volatile unsigned int *) (0xE000ED24u))
#define EC_REG_MFSR             (*(volatile unsigned int *) (0xE000ED28u))
#define EC_REG_MMAR             (*(volatile unsigned int *) (0xE000ED34u))
#define EC_REG_BFSR             (*(volatile unsigned int *) (0xE000ED29u))
#define EC_REG_BFAR             (*(volatile unsigned int *) (0xE000ED38u))
#define EC_REG_UFSR             (*(volatile unsigned int *) (0xE000ED2Au))
#define EC_REG_HFSR             (*(volatile unsigned int *) (0xE000ED2Cu))
#define EC_REG_DFSR             (*(volatile unsigned int *) (0xE000ED30u))
#define EC_REG_AFSR             (*(volatile unsigned int *) (0xE000ED3Cu))


// magic number for fs assert indication "FS_Assert_sF", 12bytes/3 words 0x46535F41 0x73736572 0x745F7346
#define EC_FS_ASSERT_MAGIC_NUMBER0     (0x46535F41)
#define EC_FS_ASSERT_MAGIC_NUMBER1     (0x73736572)
#define EC_FS_ASSERT_MAGIC_NUMBER2     (0x745F7346)

#define EC_FS_ASSERT_REFORMAT_THRESHOLD     (10)

typedef struct _ec_m3_exception_regs
{
    struct
    {
        uint32_t r0;
        uint32_t r1;
        uint32_t r2;
        uint32_t r3;
        uint32_t r4;
        uint32_t r5;
        uint32_t r6;
        uint32_t r7;
        uint32_t r8;
        uint32_t r9;
        uint32_t r10;
        uint32_t r11;
        uint32_t r12;
        uint32_t sp;
        uint32_t lr;
        uint32_t pc;
        union
        {
            uint32_t value;
            struct
            {
                uint32_t IPSR : 8;
                uint32_t EPSR : 8;
                uint32_t APSR : 8;
            }bits;
        }psr;
        uint32_t exc_return;
        uint32_t msp;
        uint32_t psp;
        uint32_t CONTROL;
        uint32_t BASEPRI;
        uint32_t PRIMASK;
        uint32_t FAULTMASK;
    }stack_frame;

    union
    {
        uint32_t value;
        struct
        {
            uint32_t MEM_FAULT_ACT      : 1;
            uint32_t BUS_FAULT_ACT      : 1;
            uint32_t UNUSED_BITS1       : 1;
            uint32_t USAGE_FAULT_ACT    : 1;
            uint32_t UNUSED_BITS2       : 3;
            uint32_t SVCALLACT          : 1;
            uint32_t MONITORACT         : 1;
            uint32_t UNUSED_BITS3       : 1;
            uint32_t PENDSVACT          : 1;
            uint32_t SYSTICKACT         : 1;
            uint32_t USAGEFAULTPENDED   : 1;
            uint32_t MEMFAULTPENDED     : 1;
            uint32_t BUSFAULTPENDED     : 1;
            uint32_t SVCALLPENDED       : 1;
            uint32_t MEMFAULT_EN        : 1;
            uint32_t BUSFAULT_EN        : 1;
            uint32_t USAGEFAULT_EN      : 1;
        }bits;
    }sys_ctrl_stat;

    union
    {
        uint8_t value;
        struct
        {
            uint8_t IACCVIOL    : 1;
            uint8_t DACCVIOL    : 1;
            uint8_t UNUSED_BIT  : 1;
            uint8_t MUNSTKERR   : 1;
            uint8_t MSTKERR     : 1;
            uint8_t MLSPERR     : 1;
            uint8_t UNUSED_BIT2 : 1;
            uint8_t MMARVALID   : 1;
        }bits;
    }mfsr;

    union
    {
        uint8_t value;
        struct
        {
            uint8_t IBUSERR     : 1;
            uint8_t PRECISEER   : 1;
            uint8_t IMPREISEER  : 1;
            uint8_t UNSTKERR    : 1;
            uint8_t STKERR      : 1;
            uint8_t LSPERR      : 1;
            uint8_t UNUSED_BIT  : 1;
            uint8_t BFARVALID   : 1;
        }bits;
    }bfsr;

    union
    {
        unsigned short value;
        struct
        {
            unsigned short UNDEFINSTR   : 1;
            unsigned short INVSTATE     : 1;
            unsigned short INVPC        : 1;
            unsigned short NOCP         : 1;
            unsigned short UNUSED_BITS  : 4;
            unsigned short UNALIGNED    : 1;
            unsigned short DIVBYZERO    : 1;
        }bits;
    }ufsr;

    union
    {
        uint32_t value;
        struct
        {
            uint32_t UNUSED_BIT1    : 1;
            uint32_t VECTBL         : 1;
            uint32_t UNUSED_BIT2    : 28;
            uint32_t FORCED         : 1;
            uint32_t DEBUGEVT       : 1;
        }bits;
    }hfsr;

    union
    {
        uint32_t value;
        struct
        {
            uint32_t HALTED     : 1;
            uint32_t BKPT       : 1;
            uint32_t DWTTRAP    : 1;
            uint32_t VCATCH     : 1;
            uint32_t EXTERNAL   : 1;
        }bits;
    }dfsr;

    uint32_t mmfar;
    uint32_t bfar;
    uint32_t afar;
}ec_m3_exception_regs;
enum
{
    excep_r0=0,
    excep_r1,
    excep_r2,
    excep_r3,
    excep_r12,
    excep_lr,
    excep_pc,
    excep_psr,
};

typedef enum EXCEPTION_CONFIG_OPTION
{
    EXCEP_OPTION_DUMP_FLASH_EPAT_LOOP,      //0 -- dump full exception info to flash and EPAT tool then trapped in endless loop(while(1))

    EXCEP_OPTION_PRINT_RESET,               //1 -- print necessary exception info then reset
    EXCEP_OPTION_DUMP_FLASH_RESET,          //2 -- dump full exception info to flash then reset
    EXCEP_OPTION_DUMP_FLASH_EPAT_RESET,     //3 -- dump full exception info to flash and EPAT tool then reset
    EXCEP_OPTION_SILENT_RESET,              //4 -- reset directly
    EXCEP_OPTION_MAX

}ExcepConfigOp;



enum
{
    reg_r0=0,
    reg_r1,
    reg_r2,
    reg_r3,
    reg_r4,
    reg_r5,
    reg_r6,
    reg_r7,
    reg_r8,
    reg_r9,
    reg_r10,
    reg_r11,
    reg_r12,
    reg_sp,
    reg_lr,
    reg_pc,
};



typedef struct _ec_exception_store
{
    uint32_t ec_start_flag;
    uint32_t ec_hardfault_flag;
    uint32_t ec_assert_flag;
    uint32_t ec_exception_count;
    ec_m3_exception_regs excep_regs;
    uint32_t func_call_stack[EC_FUNC_CALL_ADDR_DEPTH];
    uint8_t curr_task_name[EC_EXCEP_TASK_NAME_LEN];
    uint32_t curr_time;
    uint32_t fw_info;
    uint32_t ec_end_flag;
}ec_exception_store;



typedef enum
{
    RESET_REASON_XICOVL = 0x90,
    RESET_REASON_CLEAR = 0xA0,
	RESET_REASON_HARDFAULT = 0xB0,
	RESET_REASON_ASSERT = 0xC0,
	RESET_REASON_WDT = 0xD0,
	RESET_REASON_BAT = 0xE0,
	RESET_REASON_FLHDRV = 0xF0,
}ResetReason_e;


typedef enum
{
	LAST_RESET_POR = 0,
	LAST_RESET_NORMAL,		// can be sleep2/hib
	LAST_RESET_SWRESET,
	LAST_RESET_HARDFAULT,
	LAST_RESET_ASSERT,
	LAST_RESET_WDT,
    LAST_RESET_FLHDRV,
	LAST_RESET_XICOVFL,
	LAST_RESET_UNKNOWN,
	LAST_RESET_MAXNUM,
}LastResetState_e;



void ResetReasonWrite(ResetReason_e reason);
void EC_SystemReset(void);	// using this api to execute a software reset instead of __NVIC_SystemReset
void ResetReasonInit(void);	// when using reset reason checker, this api should be called in bsp_customInit
LastResetState_e appGetLastResetReason(void); // API for user to check last reset reason, should be called after ResetReasonInit


#if defined ( __CC_ARM )
extern unsigned int __current_pc(void);   // arm_cc used to get pc, it cannot get pc directly
extern unsigned int __current_sp(void);   // arm_cc used to get sp

#elif defined(__GNUC__)
void *__current_pc(void);
#endif

extern void ec_assert(const char *func, uint32_t line, const char *file, uint32_t v1, uint32_t v2, uint32_t v3);
void ec_assert_task_inter_info(void);
BOOL is_in_excep_handler(void);
BOOL is_fs_assert(void);

#define EC_ASSERT_FLAG

#if defined ( __CC_ARM )
//extern __inline void ec_assert_regs(void);
extern  __INLINE __asm void ec_assert_regs(void);
extern void unilogAssertInfo(const char *func, uint32_t line, const char *file, uint32_t v1, uint32_t v2, uint32_t v3);
    #ifdef EC_ASSERT_FLAG
        #define EC_ASSERT(x,v1,v2,v3)    \
                            do {  \
                                    { \
                                        if((x) == 0) \
                                        { \
                                            ec_assert_regs(); \
                                            *((unsigned int *)EC_ASSERT_PC_ADDR) = __current_pc(); \
                                            *((unsigned int *)EC_EXCEPTION_MAGIC_ADDR) = EC_EXCEP_MAGIC_NUMBER; \
                                            ec_assert(__FUNCTION__, __LINE__, PNULL, (uint32_t)(v1),(uint32_t)(v2),(uint32_t)(v3)); \
                                            while(1); \
                                        }\
                                    } \
                            } while(0)
    #else
        #define EC_ASSERT(x,v1,v2,v3)    \
                            do {  \
                                    { \
                                        if((x) == 0) \
                                        { \
                                            printf("Assert, func:%s, file: %s, line: %d, val: 0x%x,0x%x,0x%x \r\n", __FUNCTION__, __FILE__, __LINE__, (uint32_t)(v1),(uint32_t)(v2),(uint32_t)(v3)); \
                                            __disable_irq();\
                                            *((unsigned int *)EC_ASSERT_LR_ADDR) = __GET_RETURN_ADDRESS(); \
                                            ec_assert_task_inter_info();\
                                            while(1);\
                                        }\
                                    } \
                            } while(0)
    #endif

#elif defined(__GNUC__)
extern void ec_assert_regs(void);
#define EC_ASSERT(x,v1,v2,v3)    \
                                 do {  \
                                    { \
                                        if((x) == 0) \
                                        { \
                                            ec_assert_regs(); \
                                            *((unsigned int *)EC_ASSERT_PC_ADDR) = (unsigned int)__current_pc(); \
                                            ec_assert_task_inter_info();\
                                            ec_assert(__FUNCTION__, __LINE__, PNULL, (uint32_t)(v1),(uint32_t)(v2),(uint32_t)(v3)); \
                                            while(1); \
                                        }\
                                    } \
                            } while(0)
#endif


#endif  /* OS_EXCEPTION_H */
