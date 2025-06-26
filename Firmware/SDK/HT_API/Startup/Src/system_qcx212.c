/**************************************************************************//**
 * @file     system_ARMCM3.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM3 Device Series
 * @version  V5.00
 * @date     07. September 2016
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
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

#include "qcx212.h"
#include "mpu_armv7.h"
#include "driver_common.h"
#include "cache_qcx212.h"
#include "mem_map.h"
#include "slpman_qcx212.h"

#define SYS_ADDRESS  APP_FLASH_LOAD_ADDR


extern void CopyRWDataFromBin(void);
extern void SetZIDataToZero(void);
extern void CopyDataRamtoImage(void);
extern void CopyRamCodeForDeepSleep(void);
extern void CopyDataRWZIForDeepSleep(void);
extern void mpu_init(void);


/*----------------------------------------------------------------------------
  Externals
 *----------------------------------------------------------------------------*/
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
#if defined(__CC_ARM)
   extern uint32_t __Vectors;
#elif defined(__GNUC__)
   extern uint32_t __isr_vector;
#endif
#endif

/*
 *  This function is called in flash erase or write apis to prevent 
 *  unexpected access the bootloader and system image read only area.
 *  Be careful if you want change this function.
 *  Parameter:      Addr: flash erase or write addr
 */
uint8_t BSP_QSPI_Check_ROAddr(uint32_t Addr)
{
    if(Addr <(BOOTLOADER_FLASH_LOAD_ADDR+BOOTLOADER_FLASH_LOAD_SIZE-FLASH_XIP_ADDR))
    {
        return 1;
    }


    if((Addr >=(APP_FLASH_LOAD_ADDR-FLASH_XIP_ADDR)) 
        && (Addr <(APP_FLASH_LOAD_ADDR+APP_FLASH_LOAD_SIZE-FLASH_XIP_ADDR)))
    {
        return 1;
    }

    return 0;
}

/*
 *  This function is called in flash erase or write apis to prevent 
 *  unexpected access the image read only area.
 *  Be careful if you want change this function.
 *  Parameter:      Addr: flash erase or write addr
 *  Parameter:      Addr: flash erase or write size
 
 */
uint8_t BSP_QSPI_Check_ROSpace(uint32_t Addr, uint32_t Size)
{
    if(BSP_QSPI_Check_ROAddr(Addr))
    {
        return 1;
    }
    if (BSP_QSPI_Check_ROAddr(Addr+Size - 1))
    {
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
#define  CORE_CLOCK_REGISER_ADDRESS    (0x44050018)
uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/*----------------------------------------------------------------------------
  System Core Clock update function
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
    switch((*((uint32_t *)CORE_CLOCK_REGISER_ADDRESS)) & 0x3)
    {
        case 0:
            SystemCoreClock = 204800000U;
            break;
        case 1:
            SystemCoreClock = 102400000U;
            break;
        case 2:
            SystemCoreClock = 26000000U;
            break;
        case 3:
            SystemCoreClock = 32768U;
            break;
    }
}

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/
void SystemFullImageInit (void)
{
    uint32_t ResetStat = (*(uint32_t *)0x44000078)&0x7;        //areg0


    if(ResetStat == BOOT_FROM_SLEEP1)           //sleep1
        return;

    /*move the RW data in the image to its excution region*/
    CopyRWDataFromBin();

    /*append the ZI region. TODO: maybe ZI data need not to be 0,
    random value maybe aslo fine for application, if so we could
    remove this func call, since it takes a lot of time*/
    SetZIDataToZero();

    CopyDataRWZIForDeepSleep();

#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
#if defined(__CC_ARM)
    SCB->VTOR = (uint32_t) &__Vectors;
#elif defined (__GNUC__)
    SCB->VTOR = (uint32_t) &__isr_vector;
#endif
#endif

  /*set NVIC priority group as 4(bits 7,6,5 is group priority bits ),
    3 bits for group priority. Since our CM3 core only implemented 3
    bits for priority and freertos recommend all bits should be
    group priority bits*/
    NVIC_SetPriorityGrouping(4);

    //enable div 0 trap,then div 0 operation will trigger hardfault
    SCB->CCR|=(SCB_CCR_DIV_0_TRP_Msk | SCB_CCR_STKALIGN_Msk);


    SystemCoreClockUpdate();

    mpu_init();
}


#define BOOT_TIME_TEST 0

void SystemInit (void)
{
	uint32_t ResetStat = (*(uint32_t *)0x44000078)&0x7;        //areg0

#if BOOT_TIME_TEST
    *((uint32_t *)0x2010) = PmuSlowCntRead_Flash();
#endif

    DisableICache();

    EnableICache();

    if(ResetStat == BOOT_FROM_SLEEP1)           //sleep1
    {
        return;
    }

    CopyRamCodeForDeepSleep();
#if BOOT_TIME_TEST
    *((uint32_t *)0x2014) = PmuSlowCntRead_Flash();
#endif
    CopyDataRWZIForDeepSleep();
#if BOOT_TIME_TEST
    *((uint32_t *)0x2018) = PmuSlowCntRead_Flash();
#endif
#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
#if defined(__CC_ARM)
    SCB->VTOR = (uint32_t) &__Vectors;
#elif defined (__GNUC__)
    SCB->VTOR = (uint32_t) &__isr_vector;
#endif
#endif

  /*set NVIC priority group as 4(bits 7,6,5 is group priority bits ),
    3 bits for group priority. Since our CM3 core only implemented 3
    bits for priority and freertos recommend all bits should be
    group priority bits*/
    NVIC_SetPriorityGrouping(4);

    //enable div 0 trap,then div 0 operation will trigger hardfault
    SCB->CCR|=(SCB_CCR_DIV_0_TRP_Msk | SCB_CCR_STKALIGN_Msk);


    SystemCoreClockUpdate();

//need add MPU configuration later
}

