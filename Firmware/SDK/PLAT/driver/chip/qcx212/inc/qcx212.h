/**
 *****************************************************************************
 * @brief   Device Peripheral Access Layer Header File.
 *          This file contains all the peripheral register's definitions, bits
 *          definitions and memory mapping for QCX212 chip.
 *
 * @file   qcx212.h
 * @author
 * @date   12/Nov/2018
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; COPYRIGHT 2018 Qualcomm Technologies Ltd.</b>
 *
 *****************************************************************************
 */

#ifndef QCX212_H
#define QCX212_H

#ifdef __cplusplus
 extern "C" {
#endif
#include "commontypedef.h"
#include "HT_qcx212_types.h"

/** @addtogroup Interrupt_number_definiton Interrupt Number Definition
  * @{
  */
#ifndef IRQ_NUMBER_DEFINED
#define IRQ_NUMBER_DEFINED

typedef enum IRQn
{
/*  Cortex-M3 Processor Exceptions Numbers */
  NonMaskableInt_IRQn           = -14,      /**<  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,      /**<  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,      /**<  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,      /**<  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,      /**<  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,      /**< 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,      /**< 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,      /**< 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,      /**< 15 System Tick Interrupt */

/* ARMCM3 Specific Interrupt Numbers  */
  RTCWakeup_IRQn                =   0,      /**< RTC Wakeup Interrupt */
  PadWakeup0_IRQn               =   1,      /**< Pad Wakeup0 Interrupt */
  PadWakeup1_IRQn               =   2,      /**< Pad Wakeup1 Interrupt */
  PadWakeup2_IRQn               =   3,      /**< Pad Wakeup2 Interrupt */
  PadWakeup3_IRQn               =   4,      /**< Pad Wakeup3 Interrupt */
  PadWakeup4_IRQn               =   5,      /**< Pad Wakeup4 Interrupt */
  PadWakeup5_IRQn               =   6,      /**< Pad Wakeup5 Interrupt */
  PeripheralXIC_IRQn            =   7,      /**< Peripheral XIC Interrupt */
  ModemXIC_IRQn                 =   8,      /**< Modem XIC Interrupt */

/* Peripheral Specific Interrupt Numbers  */
  PXIC_Ovf_IRQn                 =   32,     /**< SW or HW Error Interrupt */
  Reserved45_IRQn               =   33,     /**< Reserved Interrupt */
  PXIC_Clock_Cal_IRQn           =   34,     /**< 32K and RC16M calibration Interrupt */
  PXIC_Adc_IRQn                 =   35,     /**< Adc Data Valid Interrupt */
  PXIC_Trng_IRQn                =   36,     /**< Trng Interrupt */
  PXIC_Efuse_Fail_IRQn          =   37,     /**< Efuse Fail Interrupt */
  PXIC_Efuse_Burn_IRQn          =   38,     /**< Efuse Burn Interrupt */
  PXIC_Efuse_Read_IRQn          =   39,     /**< Efuse Read Interrupt */
  PXIC_Timer0_IRQn              =   40,     /**< TIMER0 Interrupt */
  PXIC_Timer1_IRQn              =   41,     /**< TIMER1 Interrupt */
  PXIC_Timer2_IRQn              =   42,     /**< TIMER2 Interrupt */
  PXIC_Timer3_IRQn              =   43,     /**< TIMER3 Interrupt */
  PXIC_Timer4_IRQn              =   44,     /**< TIMER4 Interrupt */
  PXIC_Timer5_IRQn              =   45,     /**< TIMER5 Interrupt */
  PXIC_Gpio_IRQn                =   46,     /**< GPIO Interrupt */
  PXIC_Uart0_IRQn               =   47,     /**< Uart0 Interrupt */
  PXIC_Uart1_IRQn               =   48,     /**< Uart1 Interrupt */
  PXIC_Uart2_IRQn               =   49,     /**< Uart2 Interrupt */
  PXIC_I2c0_IRQn                =   50,     /**< I2C0 Interrupt */
  PXIC_I2c1_IRQn                =   51,     /**< I2C1 Interrupt */
  PXIC_Spi0_IRQn                =   52,     /**< SPI0 Interrupt */
  PXIC_Spi1_IRQn                =   53,     /**< SPI1 Interrupt */
  PXIC_Mipi_Rffe_IRQn           =   54,     /**< Mipi Rffe Interrupt */
  PXIC_Usim_IRQn                =   55,     /**< USIM Interrupt */
  PXIC_Flash_IRQn               =   56,     /**< FLASH Interrupt */
  PXIC_Unilog_IRQn              =   57,     /**< UNILOG Interrupt */
  PXIC_Pdma_IRQn                =   58,     /**< PDMA Interrupt */
  PXIC_Cipher_Ch0_IRQn          =   59,     /**< Cipher Channel0 Interrupt */
  PXIC_Cipher_Ch1_IRQn          =   60,     /**< Cipher Channel1 Interrupt */
  PXIC_Cipher_Tls_IRQn          =   61,     /**< Cipher Tls Interrupt */
  PXIC_Cipher_Flash_IRQn        =   62,     /**< Cipher Flash Interrupt */
  PXIC_Cipher_Err_IRQn          =   63,     /**< Cipher Error Interrupt */

} IRQn_Type;

#endif

/**
  * @}
  */ /* end of group Interrupt_number_definiton */

/* Start of section using anonymous unions and disabling warnings  */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/** @addtogroup Cortex_core_configuration Processor and Core Peripherals configuration
  * @{
  */

#define __CM3_REV                                0x0201U                        /**< Core revision r2p1 */
#define __MPU_PRESENT                            1U                             /**< MPU present */
#define __VTOR_PRESENT                           1U                             /**< VTOR present or not */
#define __NVIC_PRIO_BITS                         3U                             /**< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig                   0U                             /**< Set to 1 if different SysTick Config is used */

#include "core_cm3.h"                            /* Processor and core peripherals */
#include "system_qcx212.h"                        /* System Header */

/**
  * @}
  */ /* end of group Cortex_core_configuration */

/** @addtogroup Device_peripheral_access Device Peripheral Access
  * @{
  */


/** @addtogroup BASE_ADDR Peripheral instance base addresses
  * @{
  */

/**
  * @brief APB base address
  *
  */
#define APB_PERIPH_BASE                          ((unsigned int)0x44000000)   /**< APB peripheral base address */

#define ADC_BASE_ADDR                            (APB_PERIPH_BASE + 0x0201b0) /**< ADC base address */
#define GPIO_BASE_ADDR                           (APB_PERIPH_BASE + 0x040000) /**< GPIO base address */
#define I2C0_BASE_ADDR                           (APB_PERIPH_BASE + 0x060000) /**< I2C0 base address */
#define I2C1_BASE_ADDR                           (APB_PERIPH_BASE + 0x070000) /**< I2C1 base address */
#define PAD_BASE_ADDR                            (APB_PERIPH_BASE + 0x080000) /**< PAD base address */
#define TRNG_BASE_ADDR                           (APB_PERIPH_BASE + 0x0a0000) /**< TRNG base address */
#define SPI0_BASE_ADDR                           (APB_PERIPH_BASE + 0x0b0000) /**< SPI0 base address */
#define SPI1_BASE_ADDR                           (APB_PERIPH_BASE + 0x0c0000) /**< SPI1 base address */
#define USART0_BASE_ADDR                         (APB_PERIPH_BASE + 0x0d0000) /**< USART0 base address */
#define USART1_BASE_ADDR                         (APB_PERIPH_BASE + 0x0e0000) /**< USART1 base address */
#define USART2_BASE_ADDR                         (APB_PERIPH_BASE + 0x0f0000) /**< USART2 base address */
#define TIMER0_BASE_ADDR                         (APB_PERIPH_BASE + 0x110000) /**< TIMER0 base address */
#define TIMER1_BASE_ADDR                         (APB_PERIPH_BASE + 0x120000) /**< TIMER1 base address */
#define TIMER2_BASE_ADDR                         (APB_PERIPH_BASE + 0x130000) /**< TIMER2 base address */
#define TIMER3_BASE_ADDR                         (APB_PERIPH_BASE + 0x140000) /**< TIMER3 base address */
#define TIMER4_BASE_ADDR                         (APB_PERIPH_BASE + 0x150000) /**< TIMER4 base address */
#define TIMER5_BASE_ADDR                         (APB_PERIPH_BASE + 0x160000) /**< TIMER5 base address */
#define WDT_BASE_ADDR                            (APB_PERIPH_BASE + 0x170000) /**< WDT base address */

/**
  * @}
  */ /* end of group BASE_ADDR */

/** @addtogroup ADC ADC(Analog-to-Digital converter)
  * @{
  */

/**
  * @brief ADC register layout typedef
  *
  */
typedef struct {
    __IO uint32_t AIOCFG;                        /**< AIO configuration Register,                   offset: 0x0 */
    __IO uint32_t CFG;                           /**< ADC configuration Register,                   offset: 0x4 */
    __IO uint32_t CTRL;                          /**< ADC control Register,                         offset: 0x8 */
         uint32_t RESERVED[5];
    __I  uint32_t STATUS;                        /**< ADC status Register,                          offset: 0x20 */
    __I  uint32_t RESULT;                        /**< ADC data result Register,                     offset: 0x24 */
} ADC_TypeDef;

/** @name AIOCFG - ADC_AIOCFG register */
/** @{ */
#define ADC_AIOCFG_THM_SEL_Pos                   (0)
#define ADC_AIOCFG_THM_SEL_Msk                   (0x3UL << ADC_AIOCFG_THM_SEL_Pos)

#define ADC_AIOCFG_VBATSEN_RDIV_Pos              (2)
#define ADC_AIOCFG_VBATSEN_RDIV_Msk              (0x7UL << ADC_AIOCFG_VBATSEN_RDIV_Pos)

#define ADC_AIOCFG_RDIV_Pos                      (5)
#define ADC_AIOCFG_RDIV_Msk                      (0x7UL << ADC_AIOCFG_RDIV_Pos)

#define ADC_AIOCFG_RDIV_BYP_Pos                  (8)
#define ADC_AIOCFG_RDIV_BYP_Msk                  (0x1UL << ADC_AIOCFG_RDIV_BYP_Pos)

#define ADC_AIOCFG_THM_EN_Pos                    (9)
#define ADC_AIOCFG_THM_EN_Msk                    (0x1UL << ADC_AIOCFG_THM_EN_Pos)

#define ADC_AIOCFG_BATSENS_EN_Pos                (10)
#define ADC_AIOCFG_BATSENS_EN_Msk                (0x1UL << ADC_AIOCFG_BATSENS_EN_Pos)

#define ADC_AIOCFG_AIO4_EN_Pos                   (11)
#define ADC_AIOCFG_AIO4_EN_Msk                   (0x1UL << ADC_AIOCFG_AIO4_EN_Pos)

#define ADC_AIOCFG_AIO3_EN_Pos                   (12)
#define ADC_AIOCFG_AIO3_EN_Msk                   (0x1UL << ADC_AIOCFG_AIO3_EN_Pos)

#define ADC_AIOCFG_AIO2_EN_Pos                   (13)
#define ADC_AIOCFG_AIO2_EN_Msk                   (0x1UL << ADC_AIOCFG_AIO2_EN_Pos)

#define ADC_AIOCFG_AIO1_EN_Pos                   (14)
#define ADC_AIOCFG_AIO1_EN_Msk                   (0x1UL << ADC_AIOCFG_AIO1_EN_Pos)
/** @} */

/** @name CFG - ADC_CFG register */
/** @{ */
#define ADC_CFG_IBIAS_SEL_Pos                    (0)
#define ADC_CFG_IBIAS_SEL_Msk                    (0x3UL << ADC_CFG_IBIAS_SEL_Pos)

#define ADC_CFG_WAIT_CTRL_Pos                    (2)
#define ADC_CFG_WAIT_CTRL_Msk                    (0x3UL << ADC_CFG_WAIT_CTRL_Pos)

#define ADC_CFG_OFFSET_CTRL_Pos                  (4)
#define ADC_CFG_OFFSET_CTRL_Msk                  (0x7UL << ADC_CFG_OFFSET_CTRL_Pos)

#define ADC_CFG_SAMPLE_AVG_Pos                   (7)
#define ADC_CFG_SAMPLE_AVG_Msk                   (0x1UL << ADC_CFG_SAMPLE_AVG_Pos)

#define ADC_CFG_VREF_BS_Pos                      (8)
#define ADC_CFG_VREF_BS_Msk                      (0x1UL << ADC_CFG_VREF_BS_Pos)

#define ADC_CFG_VREF_SEL_Pos                     (9)
#define ADC_CFG_VREF_SEL_Msk                     (0x7UL << ADC_CFG_VREF_SEL_Pos)

#define ADC_CFG_CLKIN_DIV_Pos                    (12)
#define ADC_CFG_CLKIN_DIV_Msk                    (0x3UL << ADC_CFG_CLKIN_DIV_Pos)

#define ADC_CFG_CLK_DRIVE_Pos                    (14)
#define ADC_CFG_CLK_DRIVE_Msk                    (0x7UL << ADC_CFG_CLK_DRIVE_Pos)

#define ADC_CFG_CLK_SEL_Pos                      (17)
#define ADC_CFG_CLK_SEL_Msk                      (0x1UL << ADC_CFG_CLK_SEL_Pos)
/** @} */

/** @name CTRL - ADC_CTRL register */
/** @{ */
#define ADC_CTRL_EN_Pos                          (0)
#define ADC_CTRL_EN_Msk                          (0x1UL << ADC_CTRL_EN_Pos)

#define ADC_CTRL_RSTN_Pos                        (1)
#define ADC_CTRL_RSTN_Msk                        (0x1UL << ADC_CTRL_RSTN_Pos)
/** @} */

/** @name STATUS - ADC_STATUS register */
/** @{ */
#define ADC_STATUS_DATA_VALID_Pos                (0)
#define ADC_STATUS_DATA_VALID_Msk                (0x1UL << ADC_STATUS_DATA_VALID_Pos)
/** @} */

/** @name RESULT - ADC_RESULT register */
/** @{ */
#define ADC_RESULT_DATA_Pos                      (0)
#define ADC_RESULT_DATA_Msk                      (0xFFFUL << ADC_RESULT_DATA_Pos)
/** @} */

/** Peripheral ADC base pointer */
#define ADC                                      ((ADC_TypeDef *)ADC_BASE_ADDR)

/**
  * @}
  */ /* end of group ADC */


/** @addtogroup GPIO GPIO
  * @{
  */

/**
  * @brief GPIO register layout typedef
  *
  */
typedef struct {
    __IO uint32_t DATA;                          /**< Data Input Register,                offset: 0x0 */
    __IO uint32_t DATAOUT;                       /**< Data Output Register,               offset: 0x4 */
         uint32_t RESERVED_0[2];
    __IO uint32_t OUTENSET;                      /**< Output Enable Set Register,         offset: 0x10 */
    __IO uint32_t OUTENCLR;                      /**< Output Enable Clear Register,       offset: 0x14 */
         uint32_t RESERVED_1[2];
    __IO uint32_t INTENSET;                      /**< Interrupt Enable Set Register,      offset: 0x20 */
    __IO uint32_t INTENCLR;                      /**< Interrupt Enable Clear Register,    offset: 0x24 */
    __IO uint32_t INTTYPESET;                    /**< Interrupt Type set Register,        offset: 0x28 */
    __IO uint32_t INTTYPECLR;                    /**< Interrupt Type Clear Register,      offset: 0x2C */
    __IO uint32_t INTPOLSET;                     /**< Interrupt Polarity Set Register,    offset: 0x30 */
    __IO uint32_t INTPOLCLR;                     /**< Interrupt Polarity Clear Register,  offset: 0x34 */
    __IO uint32_t INTSTATUS;                     /**< Interrupt Status Register,          offset: 0x38 */
         uint32_t RESERVED_3[241];
    __IO uint32_t MASKLOWBYTE[256];              /**< Lower Eight Bits Masked Access Register, array offset: 0x400, array step: 0x4 */
    __IO uint32_t MASKHIGHBYTE[256];             /**< Higher Eight Bits Masked Access Register, array offset: 0x800, array step: 0x4 */
} GPIO_TypeDef;

/** @name DATA - GPIO_DATA register */
/** @{ */
#define GPIO_DATA_DVAL_Pos                       (0)
#define GPIO_DATA_DVAL_Msk                       (0xFFFFUL << GPIO_DATA_DVAL_Pos)
/** @} */

/** @name DATAOUT - GPIO_DATAOUT register */
/** @{ */
#define GPIO_DATAOUT_DOVAL_Pos                   (0)
#define GPIO_DATAOUT_DOVAL_Msk                   (0xFFFFUL << GPIO_DATAOUT_DOVAL_Pos)
/** @} */

/** @name OUTENSET - GPIO_OUTENSET register */
/** @{ */
#define GPIO_OUTENSET_OEN_Pos                    (0)
#define GPIO_OUTENSET_OEN_Msk                    (0xFFFFUL << GPIO_OUTENSET_OEN_Pos)
/** @} */

/** @name OUTENCLR - GPIO_OUTENCLR register */
/** @{ */
#define GPIO_OUTENCLR_OCLR_Pos                   (0)
#define GPIO_OUTENCLR_OCLR_Msk                   (0xFFFFUL << GPIO_OUTENCLR_OCLR_Pos)
/** @} */

/** @name INTENSET - GPIO_INTENSET register */
/** @{ */
#define GPIO_INTENSET_INEN_Pos                   (0)
#define GPIO_INTENSET_INEN_Msk                   (0xFFFFUL << GPIO_INTENSET_INEN_Pos)
/** @} */

/** @name INTENCLR - GPIO_INTENCLR register */
/** @{ */
#define GPIO_INTENCLR_INCLR_Pos                  (0)
#define GPIO_INTENCLR_INCLR_Msk                  (0xFFFFUL << GPIO_INTENCLR_INCLR_Pos)
/** @} */

/** @name INTTYPESET - GPIO_INTTYPESET register */
/** @{ */
#define GPIO_INTTYPESET_INTYPE_Pos               (0)
#define GPIO_INTTYPESET_INTYPE_Msk               (0xFFFFUL << GPIO_INTTYPESET_INTYPE_Pos)
/** @} */

/** @name INTTYPECLR - GPIO_INTTYPECLR register */
/** @{ */
#define GPIO_INTTYPECLR_INTYPECLR_Pos            (0)
#define GPIO_INTTYPECLR_INTYPECLR_Msk            (0xFFFFUL << GPIO_INTTYPECLR_INTYPECLR_Pos)
/** @} */

/** @name INTPOLSET - GPIO_INTPOLSET register */
/** @{ */
#define GPIO_INTPOLSET_INPOL_Pos                 (0)
#define GPIO_INTPOLSET_INPOL_Msk                 (0xFFFFUL << GPIO_INTPOLSET_INPOL_Pos)
/** @} */

/** @name INTPOLCLR - GPIO_INTPOLCLR register */
/** @{ */
#define GPIO_INTPOLCLR_INPOLCLR_Pos              (0)
#define GPIO_INTPOLCLR_INPOLCLR_Msk              (0xFFFFUL << GPIO_INTPOLCLR_INPOLCLR_Pos)
/** @} */

/** @name INTSTATUS - GPIO_INTSTATUS register */
/** @{ */
#define GPIO_INTSTATUS_INSTAT_Pos                (0)
#define GPIO_INTSTATUS_INSTAT_Msk                (0xFFFFUL << GPIO_INTSTATUS_INSTAT_Pos)
/** @} */

/** @name MASKLOWBYTE - GPIO_MASKLOWBYTE N register */
/** @{ */
#define GPIO_MASKLOWBYTE_MASK_Pos                (0)
#define GPIO_MASKLOWBYTE_MASK_Msk                (0xFFFFUL << GPIO_MASKLOWBYTE_MASK_Pos)
/** @} */

/** @name MASKHIGHBYTE - GPIO_MASKHIGHBYTE N register */
/** @{ */
#define GPIO_MASKHIGHBYTE_MASK_Pos               (0)
#define GPIO_MASKHIGHBYTE_MASK_Msk               (0xFFFFUL << GPIO_MASKHIGHBYTE_MASK_Pos)
/** @} */

/** Peripheral GPIO0 base address */
#define GPIO0_BASE_ADDR                          (GPIO_BASE_ADDR + 0x0000)

/** Peripheral GPIO0 base pointer */
#define GPIO_0                                   ((GPIO_TypeDef *) GPIO0_BASE_ADDR)

/** Peripheral GPIO1 base address */
#define GPIO1_BASE_ADDR                          (GPIO_BASE_ADDR + 0x1000)

/** Peripheral GPIO1 base pointer */
#define GPIO_1                                   ((GPIO_TypeDef *) GPIO1_BASE_ADDR)

/** @brief GPIO peripheral instance number */
#define GPIO_INSTANCE_NUM                        (2)

/**
  * @}
  */ /* end of group GPIO */

/** @addtogroup GPR GPR
  * @{
  */

/** @name CLKSEL - GPR_CLKSEL register */
/** @{ */
#define GPR_CLKSEL_CCLK_Pos                      (0)
#define GPR_CLKSEL_CCLK_Msk                      (0x3UL << GPR_CLKSEL_CCLK_Pos)

#define GPR_CLKSEL_RC_CLK_Pos                    (2)
#define GPR_CLKSEL_RC_CLK_Msk                    (0x3UL << GPR_CLKSEL_RC_CLK_Pos)

#define GPR_CLKSEL_CLKCAL_CLK_Pos                (4)
#define GPR_CLKSEL_CLKCAL_CLK_Msk                (0x1UL << GPR_CLKSEL_CLKCAL_CLK_Pos)

#define GPR_CLKSEL_FLASH_CLK_Pos                 (5)
#define GPR_CLKSEL_FLASH_CLK_Msk                 (0x1UL << GPR_CLKSEL_FLASH_CLK_Pos)

#define GPR_CLKSEL_I2C0_CLK_Pos                  (8)
#define GPR_CLKSEL_I2C0_CLK_Msk                  (0x1UL << GPR_CLKSEL_I2C0_CLK_Pos)

#define GPR_CLKSEL_I2C1_CLK_Pos                  (9)
#define GPR_CLKSEL_I2C1_CLK_Msk                  (0x1UL << GPR_CLKSEL_I2C1_CLK_Pos)

#define GPR_CLKSEL_RFFE_CLK_Pos                  (10)
#define GPR_CLKSEL_RFFE_CLK_Msk                  (0x1UL << GPR_CLKSEL_RFFE_CLK_Pos)

#define GPR_CLKSEL_SPI0_CLK_Pos                  (11)
#define GPR_CLKSEL_SPI0_CLK_Msk                  (0x1UL << GPR_CLKSEL_SPI0_CLK_Pos)

#define GPR_CLKSEL_SPI1_CLK_Pos                  (12)
#define GPR_CLKSEL_SPI1_CLK_Msk                  (0x1UL << GPR_CLKSEL_SPI1_CLK_Pos)

#define GPR_CLKSEL_UART0_CLK_Pos                 (13)
#define GPR_CLKSEL_UART0_CLK_Msk                 (0x1UL << GPR_CLKSEL_UART0_CLK_Pos)

#define GPR_CLKSEL_UART1_CLK_Pos                 (14)
#define GPR_CLKSEL_UART1_CLK_Msk                 (0x1UL << GPR_CLKSEL_UART1_CLK_Pos)

#define GPR_CLKSEL_UART2_CLK_Pos                 (15)
#define GPR_CLKSEL_UART2_CLK_Msk                 (0x1UL << GPR_CLKSEL_UART2_CLK_Pos)

#define GPR_CLKSEL_USIM_CLK_Pos                  (16)
#define GPR_CLKSEL_USIM_CLK_Msk                  (0x1UL << GPR_CLKSEL_USIM_CLK_Pos)

#define GPR_CLKSEL_WDG_CLK_Pos                   (17)
#define GPR_CLKSEL_WDG_CLK_Msk                   (0x1UL << GPR_CLKSEL_WDG_CLK_Pos)

#define GPR_CLKSEL_TIMER0_CLK_Pos                (18)
#define GPR_CLKSEL_TIMER0_CLK_Msk                (0x1UL << GPR_CLKSEL_TIMER0_CLK_Pos)

#define GPR_CLKSEL_TIMER1_CLK_Pos                (19)
#define GPR_CLKSEL_TIMER1_CLK_Msk                (0x1UL << GPR_CLKSEL_TIMER1_CLK_Pos)

#define GPR_CLKSEL_TIMER2_CLK_Pos                (20)
#define GPR_CLKSEL_TIMER2_CLK_Msk                (0x1UL << GPR_CLKSEL_TIMER2_CLK_Pos)

#define GPR_CLKSEL_TIMER3_CLK_Pos                (21)
#define GPR_CLKSEL_TIMER3_CLK_Msk                (0x1UL << GPR_CLKSEL_TIMER3_CLK_Pos)

#define GPR_CLKSEL_TIMER4_CLK_Pos                (22)
#define GPR_CLKSEL_TIMER4_CLK_Msk                (0x1UL << GPR_CLKSEL_TIMER4_CLK_Pos)

#define GPR_CLKSEL_TIMER5_CLK_Pos                (23)
#define GPR_CLKSEL_TIMER5_CLK_Msk                (0x1UL << GPR_CLKSEL_TIMER5_CLK_Pos)

#define GPR_CLKSEL_SYSTICK_CLK_Pos               (24)
#define GPR_CLKSEL_SYSTICK_CLK_Msk               (0x1UL << GPR_CLKSEL_SYSTICK_CLK_Pos)
/** @} */

/**
  * @}
  */ /* end of group GPR */


/** @addtogroup I2C I2C
  * @{
  */

/**
  * @brief I2C register layout typedef
  *
  */
typedef struct {
    __IO uint32_t MCR;                           /**< Main Control Register,           offset: 0x0 */
    __IO uint32_t SCR;                           /**< Secondary Control Register,      offset: 0x4 */
    __IO uint32_t SAR;                           /**< Slave Address Register,          offset: 0x8 */
    __IO uint32_t TPR;                           /**< Timing Parameter Register,       offset: 0xC */
    union{
    __IO uint32_t TDR;                           /**< Transmit Data Register,          offset: 0x10 */
    __IO uint32_t RDR;                           /**< Receive Data Register,           offset: 0x10 */
    };
    __IO uint32_t TOR;                           /**< Timeout Register,                offset: 0x14 */
    __IO uint32_t ISR;                           /**< Interrupt Status Register,       offset: 0x18 */
    __IO uint32_t IER;                           /**< Interrupt Enable Register,       offset: 0x1C */
    __IO uint32_t IMR;                           /**< Interrupt Mask Register,         offset: 0x20 */
    __IO uint32_t STR;                           /**< Status Register,                 offset: 0x24 */
    __IO uint32_t FSR;                           /**< FIFO Status Register,            offset: 0x28 */
} I2C_TypeDef;

/** @name MCR - I2C_MCR register */
/** @{ */
#define I2C_MCR_I2C_EN_Pos                       (0)
#define I2C_MCR_I2C_EN_Msk                       (0x1UL << I2C_MCR_I2C_EN_Pos)

#define I2C_MCR_DISABLE_SCL_STRETCH_Pos          (1)
#define I2C_MCR_DISABLE_SCL_STRETCH_Msk          (0x1UL << I2C_MCR_DISABLE_SCL_STRETCH_Pos)

#define I2C_MCR_START_BYTE_EN_Pos                (2)
#define I2C_MCR_START_BYTE_EN_Msk                (0x1UL << I2C_MCR_START_BYTE_EN_Pos)

#define I2C_MCR_CONTROL_MODE_Pos                 (3)
#define I2C_MCR_CONTROL_MODE_Msk                 (0x1UL << I2C_MCR_CONTROL_MODE_Pos)

#define I2C_MCR_TX_DMA_EN_Pos                    (4)
#define I2C_MCR_TX_DMA_EN_Msk                    (0x1UL << I2C_MCR_TX_DMA_EN_Pos)

#define I2C_MCR_RX_DMA_EN_Pos                    (5)
#define I2C_MCR_RX_DMA_EN_Msk                    (0x1UL << I2C_MCR_RX_DMA_EN_Pos)

#define I2C_MCR_AGGRESSIVE_MASTER_Pos            (6)
#define I2C_MCR_AGGRESSIVE_MASTER_Msk            (0x1UL << I2C_MCR_AGGRESSIVE_MASTER_Pos)

#define I2C_MCR_AUTOCG_EN_Pos                    (7)
#define I2C_MCR_AUTOCG_EN_Msk                    (0x1UL << I2C_MCR_AUTOCG_EN_Pos)

#define I2C_MCR_DISABLE_MASTER_Pos               (8)
#define I2C_MCR_DISABLE_MASTER_Msk               (0x1UL << I2C_MCR_DISABLE_MASTER_Pos)

#define I2C_MCR_TX_FIFO_THRESHOLD_Pos            (16)
#define I2C_MCR_TX_FIFO_THRESHOLD_Msk            (0xFUL << I2C_MCR_TX_FIFO_THRESHOLD_Pos)

#define I2C_MCR_RX_FIFO_THRESHOLD_Pos            (20)
#define I2C_MCR_RX_FIFO_THRESHOLD_Msk            (0xFUL << I2C_MCR_RX_FIFO_THRESHOLD_Pos)
/** @} */

/** @name SCR - I2C_SCR register */
/** @{ */
#define I2C_SCR_TARGET_SLAVE_ADDR_Pos            (0)
#define I2C_SCR_TARGET_SLAVE_ADDR_Msk            (0x3FFUL << I2C_SCR_TARGET_SLAVE_ADDR_Pos)

#define I2C_SCR_TARGET_SLAVE_ADDR_MODE_Pos       (13)
#define I2C_SCR_TARGET_SLAVE_ADDR_MODE_Msk       (0x1UL << I2C_SCR_TARGET_SLAVE_ADDR_MODE_Pos)

#define I2C_SCR_TARGET_RWN_Pos                   (14)
#define I2C_SCR_TARGET_RWN_Msk                   (0x1UL << I2C_SCR_TARGET_RWN_Pos)

#define I2C_SCR_START_Pos                        (15)
#define I2C_SCR_START_Msk                        (0x1UL << I2C_SCR_START_Pos)

#define I2C_SCR_RESTART_Pos                      (16)
#define I2C_SCR_RESTART_Msk                      (0x1UL << I2C_SCR_RESTART_Pos)

#define I2C_SCR_STOP_Pos                         (17)
#define I2C_SCR_STOP_Msk                         (0x1UL << I2C_SCR_STOP_Pos)

#define I2C_SCR_ACK_Pos                          (18)
#define I2C_SCR_ACK_Msk                          (0x1UL << I2C_SCR_ACK_Pos)

#define I2C_SCR_ACK_VALUE_Pos                    (19)
#define I2C_SCR_ACK_VALUE_Msk                    (0x1UL << I2C_SCR_ACK_VALUE_Pos)

#define I2C_SCR_FLUSH_TX_FIFO_Pos                (20)
#define I2C_SCR_FLUSH_TX_FIFO_Msk                (0x1UL << I2C_SCR_FLUSH_TX_FIFO_Pos)

#define I2C_SCR_FLUSH_RX_FIFO_Pos                (21)
#define I2C_SCR_FLUSH_RX_FIFO_Msk                (0x1UL << I2C_SCR_FLUSH_RX_FIFO_Pos)

#define I2C_SCR_BYTE_NUM_UNKNOWN_Pos             (22)
#define I2C_SCR_BYTE_NUM_UNKNOWN_Msk             (0x1UL << I2C_SCR_BYTE_NUM_UNKNOWN_Pos)

#define I2C_SCR_BYTE_NUM_Pos                     (23)
#define I2C_SCR_BYTE_NUM_Msk                     (0x1FFUL << I2C_SCR_BYTE_NUM_Pos)
/** @} */

/** @name SAR - I2C_SAR register */
/** @{ */
#define I2C_SAR_SLAVE_ADDR_Pos                   (0)
#define I2C_SAR_SLAVE_ADDR_Msk                   (0x3FFUL << I2C_SAR_SLAVE_ADDR_Pos)

#define I2C_SAR_SLAVE_ADDR_EN_Pos                (12)
#define I2C_SAR_SLAVE_ADDR_EN_Msk                (0x1UL << I2C_SAR_SLAVE_ADDR_EN_Pos)

#define I2C_SAR_SLAVE_ADDR_MODE_Pos              (13)
#define I2C_SAR_SLAVE_ADDR_MODE_Msk              (0x1UL << I2C_SAR_SLAVE_ADDR_MODE_Pos)

#define I2C_SAR_GENERAL_CALL_EN_Pos              (16)
#define I2C_SAR_GENERAL_CALL_EN_Msk              (0x1UL << I2C_SAR_GENERAL_CALL_EN_Pos)
/** @} */

/** @name TPR - I2C_TPR register */
/** @{ */
#define I2C_TPR_SCLL_Pos                         (0)
#define I2C_TPR_SCLL_Msk                         (0xFFUL << I2C_TPR_SCLL_Pos)

#define I2C_TPR_SCLH_Pos                         (8)
#define I2C_TPR_SCLH_Msk                         (0xFFUL << I2C_TPR_SCLH_Pos)

#define I2C_TPR_SDA_SETUP_TIME_Pos               (16)
#define I2C_TPR_SDA_SETUP_TIME_Msk               (0x7UL << I2C_TPR_SDA_SETUP_TIME_Pos)

#define I2C_TPR_SDA_HOLD_TIME_Pos                (20)
#define I2C_TPR_SDA_HOLD_TIME_Msk                (0x7UL << I2C_TPR_SDA_HOLD_TIME_Pos)

#define I2C_TPR_SPIKE_FILTER_CNUM_Pos            (24)
#define I2C_TPR_SPIKE_FILTER_CNUM_Msk            (0xFUL << I2C_TPR_SPIKE_FILTER_CNUM_Pos)
/** @} */

/** @name TDR - I2C_TDR register */
/** @{ */
#define I2C_TDR_TX_DATA_Pos                      (0)
#define I2C_TDR_TX_DATA_Msk                      (0xFFUL << I2C_TDR_TX_DATA_Pos)
/** @} */

/** @name RDR - I2C_RDR register */
/** @{ */
#define I2C_RDR_RX_DATA_Pos                      (0)
#define I2C_RDR_RX_DATA_Msk                      (0xFFUL << I2C_RDR_RX_DATA_Pos)
/** @} */

/** @name TOR - I2C_TOR register */
/** @{ */
#define I2C_TOR_WAIT_IDLE_TIMEOUT_TIME_Pos       (0)
#define I2C_TOR_WAIT_IDLE_TIMEOUT_TIME_Msk       (0x3FFUL << I2C_TOR_WAIT_IDLE_TIMEOUT_TIME_Pos)

#define I2C_TOR_SCL_STRETCH_TIMEOUT_TIME_Pos     (16)
#define I2C_TOR_SCL_STRETCH_TIMEOUT_TIME_Msk     (0x3FFUL << I2C_TOR_SCL_STRETCH_TIMEOUT_TIME_Pos)
/** @} */

/** @name ISR - I2C_ISR register */
/** @{ */
#define I2C_ISR_TX_FIFO_EMPTY_Pos                (0)
#define I2C_ISR_TX_FIFO_EMPTY_Msk                (0x1UL << I2C_ISR_TX_FIFO_EMPTY_Pos)

#define I2C_ISR_TX_FIFO_UNDERRUN_Pos             (1)
#define I2C_ISR_TX_FIFO_UNDERRUN_Msk             (0x1UL << I2C_ISR_TX_FIFO_UNDERRUN_Pos)

#define I2C_ISR_TX_FIFO_OVERFLOW_Pos             (2)
#define I2C_ISR_TX_FIFO_OVERFLOW_Msk             (0x1UL << I2C_ISR_TX_FIFO_OVERFLOW_Pos)

#define I2C_ISR_RX_FIFO_FULL_Pos                 (3)
#define I2C_ISR_RX_FIFO_FULL_Msk                 (0x1UL << I2C_ISR_RX_FIFO_FULL_Pos)

#define I2C_ISR_RX_FIFO_OVERFLOW_Pos             (4)
#define I2C_ISR_RX_FIFO_OVERFLOW_Msk             (0x1UL << I2C_ISR_RX_FIFO_OVERFLOW_Pos)

#define I2C_ISR_TX_ONE_DATA_Pos                  (5)
#define I2C_ISR_TX_ONE_DATA_Msk                  (0x1UL << I2C_ISR_TX_ONE_DATA_Pos)

#define I2C_ISR_RX_ONE_DATA_Pos                  (6)
#define I2C_ISR_RX_ONE_DATA_Msk                  (0x1UL << I2C_ISR_RX_ONE_DATA_Pos)

#define I2C_ISR_RX_NACK_Pos                      (7)
#define I2C_ISR_RX_NACK_Msk                      (0x1UL << I2C_ISR_RX_NACK_Pos)

#define I2C_ISR_SLAVE_ADDR_MATCHED_Pos           (8)
#define I2C_ISR_SLAVE_ADDR_MATCHED_Msk           (0x1UL << I2C_ISR_SLAVE_ADDR_MATCHED_Pos)

#define I2C_ISR_TRANSFER_DONE_Pos                (9)
#define I2C_ISR_TRANSFER_DONE_Msk                (0x1UL << I2C_ISR_TRANSFER_DONE_Pos)

#define I2C_ISR_DETECT_STOP_Pos                  (10)
#define I2C_ISR_DETECT_STOP_Msk                  (0x1UL << I2C_ISR_DETECT_STOP_Pos)

#define I2C_ISR_BUS_ERROR_Pos                    (11)
#define I2C_ISR_BUS_ERROR_Msk                    (0x1UL << I2C_ISR_BUS_ERROR_Pos)

#define I2C_ISR_ARBITRATATION_LOST_Pos           (12)
#define I2C_ISR_ARBITRATATION_LOST_Msk           (0x1UL << I2C_ISR_ARBITRATATION_LOST_Pos)

#define I2C_ISR_WAIT_TX_FIFO_Pos                 (13)
#define I2C_ISR_WAIT_TX_FIFO_Msk                 (0x1UL << I2C_ISR_WAIT_TX_FIFO_Pos)

#define I2C_ISR_WAIT_RX_FIFO_Pos                 (14)
#define I2C_ISR_WAIT_RX_FIFO_Msk                 (0x1UL << I2C_ISR_WAIT_RX_FIFO_Pos)

#define I2C_ISR_WAIT_FOR_BUS_IDLE_TIMEOUT_Pos    (15)
#define I2C_ISR_WAIT_FOR_BUS_IDLE_TIMEOUT_Msk    (0x1UL << I2C_ISR_WAIT_FOR_BUS_IDLE_TIMEOUT_Pos)

#define I2C_ISR_STRETCH_SCL_TIMEOUT_Pos          (16)
#define I2C_ISR_STRETCH_SCL_TIMEOUT_Msk          (0x1UL << I2C_ISR_STRETCH_SCL_TIMEOUT_Pos)

#define I2C_ISR_DEDICATE_POINT_Pos               (17)
#define I2C_ISR_DEDICATE_POINT_Msk               (0x1UL << I2C_ISR_DEDICATE_POINT_Pos)
/** @} */

/** @name IER - I2C_IER register */
/** @{ */
#define I2C_IER_TX_FIFO_EMPTY_Pos                (0)
#define I2C_IER_TX_FIFO_EMPTY_Msk                (0x1UL << I2C_IER_TX_FIFO_EMPTY_Pos)

#define I2C_IER_TX_FIFO_UNDERRUN_Pos             (1)
#define I2C_IER_TX_FIFO_UNDERRUN_Msk             (0x1UL << I2C_IER_TX_FIFO_UNDERRUN_Pos)

#define I2C_IER_TX_FIFO_OVERFLOW_Pos             (2)
#define I2C_IER_TX_FIFO_OVERFLOW_Msk             (0x1UL << I2C_IER_TX_FIFO_OVERFLOW_Pos)

#define I2C_IER_RX_FIFO_FULL_Pos                 (3)
#define I2C_IER_RX_FIFO_FULL_Msk                 (0x1UL << I2C_IER_RX_FIFO_FULL_Pos)

#define I2C_IER_RX_FIFO_OVERFLOW_Pos             (4)
#define I2C_IER_RX_FIFO_OVERFLOW_Msk             (0x1UL << I2C_IER_RX_FIFO_OVERFLOW_Pos)

#define I2C_IER_TX_ONE_DATA_Pos                  (5)
#define I2C_IER_TX_ONE_DATA_Msk                  (0x1UL << I2C_IER_TX_ONE_DATA_Pos)

#define I2C_IER_RX_ONE_DATA_Pos                  (6)
#define I2C_IER_RX_ONE_DATA_Msk                  (0x1UL << I2C_IER_RX_ONE_DATA_Pos)

#define I2C_IER_RX_NACK_Pos                      (7)
#define I2C_IER_RX_NACK_Msk                      (0x1UL << I2C_IER_RX_NACK_Pos)

#define I2C_IER_SLAVE_ADDR_MATCHED_Pos           (8)
#define I2C_IER_SLAVE_ADDR_MATCHED_Msk           (0x1UL << I2C_IER_SLAVE_ADDR_MATCHED_Pos)

#define I2C_IER_TRANSFER_DONE_Pos                (9)
#define I2C_IER_TRANSFER_DONE_Msk                (0x1UL << I2C_IER_TRANSFER_DONE_Pos)

#define I2C_IER_DETECT_STOP_Pos                  (10)
#define I2C_IER_DETECT_STOP_Msk                  (0x1UL << I2C_IER_DETECT_STOP_Pos)

#define I2C_IER_BUS_ERROR_Pos                    (11)
#define I2C_IER_BUS_ERROR_Msk                    (0x1UL << I2C_IER_BUS_ERROR_Pos)

#define I2C_IER_ARBITRATATION_LOST_Pos           (12)
#define I2C_IER_ARBITRATATION_LOST_Msk           (0x1UL << I2C_IER_ARBITRATATION_LOST_Pos)

#define I2C_IER_WAIT_TX_FIFO_Pos                 (13)
#define I2C_IER_WAIT_TX_FIFO_Msk                 (0x1UL << I2C_IER_WAIT_TX_FIFO_Pos)

#define I2C_IER_WAIT_RX_FIFO_Pos                 (14)
#define I2C_IER_WAIT_RX_FIFO_Msk                 (0x1UL << I2C_IER_WAIT_RX_FIFO_Pos)

#define I2C_IER_WAIT_FOR_BUS_IDLE_TIMEOUT_Pos    (15)
#define I2C_IER_WAIT_FOR_BUS_IDLE_TIMEOUT_Msk    (0x1UL << I2C_IER_WAIT_FOR_BUS_IDLE_TIMEOUT_Pos)

#define I2C_IER_STRETCH_SCL_TIMEOUT_Pos          (16)
#define I2C_IER_STRETCH_SCL_TIMEOUT_Msk          (0x1UL << I2C_IER_STRETCH_SCL_TIMEOUT_Pos)

#define I2C_IER_DEDICATE_POINT_Pos               (17)
#define I2C_IER_DEDICATE_POINT_Msk               (0x1UL << I2C_IER_DEDICATE_POINT_Pos)
/** @} */

/** @name IMR - I2C_IMR register */
/** @{ */
#define I2C_IMR_TX_FIFO_EMPTY_Pos                (0)
#define I2C_IMR_TX_FIFO_EMPTY_Msk                (0x1UL << I2C_IMR_TX_FIFO_EMPTY_Pos)

#define I2C_IMR_TX_FIFO_UNDERRUN_Pos             (1)
#define I2C_IMR_TX_FIFO_UNDERRUN_Msk             (0x1UL << I2C_IMR_TX_FIFO_UNDERRUN_Pos)

#define I2C_IMR_TX_FIFO_OVERFLOW_Pos             (2)
#define I2C_IMR_TX_FIFO_OVERFLOW_Msk             (0x1UL << I2C_IMR_TX_FIFO_OVERFLOW_Pos)

#define I2C_IMR_RX_FIFO_FULL_Pos                 (3)
#define I2C_IMR_RX_FIFO_FULL_Msk                 (0x1UL << I2C_IMR_RX_FIFO_FULL_Pos)

#define I2C_IMR_RX_FIFO_OVERFLOW_Pos             (4)
#define I2C_IMR_RX_FIFO_OVERFLOW_Msk             (0x1UL << I2C_IMR_RX_FIFO_OVERFLOW_Pos)

#define I2C_IMR_TX_ONE_DATA_Pos                  (5)
#define I2C_IMR_TX_ONE_DATA_Msk                  (0x1UL << I2C_IMR_TX_ONE_DATA_Pos)

#define I2C_IMR_RX_ONE_DATA_Pos                  (6)
#define I2C_IMR_RX_ONE_DATA_Msk                  (0x1UL << I2C_IMR_RX_ONE_DATA_Pos)

#define I2C_IMR_RX_NACK_Pos                      (7)
#define I2C_IMR_RX_NACK_Msk                      (0x1UL << I2C_IMR_RX_NACK_Pos)

#define I2C_IMR_SLAVE_ADDR_MATCHED_Pos           (8)
#define I2C_IMR_SLAVE_ADDR_MATCHED_Msk           (0x1UL << I2C_IMR_SLAVE_ADDR_MATCHED_Pos)

#define I2C_IMR_TRANSFER_DONE_Pos                (9)
#define I2C_IMR_TRANSFER_DONE_Msk                (0x1UL << I2C_IMR_TRANSFER_DONE_Pos)

#define I2C_IMR_DETECT_STOP_Pos                  (10)
#define I2C_IMR_DETECT_STOP_Msk                  (0x1UL << I2C_IMR_DETECT_STOP_Pos)

#define I2C_IMR_BUS_ERROR_Pos                    (11)
#define I2C_IMR_BUS_ERROR_Msk                    (0x1UL << I2C_IMR_BUS_ERROR_Pos)

#define I2C_IMR_ARBITRATATION_LOST_Pos           (12)
#define I2C_IMR_ARBITRATATION_LOST_Msk           (0x1UL << I2C_IMR_ARBITRATATION_LOST_Pos)

#define I2C_IMR_WAIT_TX_FIFO_Pos                 (13)
#define I2C_IMR_WAIT_TX_FIFO_Msk                 (0x1UL << I2C_IMR_WAIT_TX_FIFO_Pos)

#define I2C_IMR_WAIT_RX_FIFO_Pos                 (14)
#define I2C_IMR_WAIT_RX_FIFO_Msk                 (0x1UL << I2C_IMR_WAIT_RX_FIFO_Pos)

#define I2C_IMR_WAIT_FOR_BUS_IDLE_TIMEOUT_Pos    (15)
#define I2C_IMR_WAIT_FOR_BUS_IDLE_TIMEOUT_Msk    (0x1UL << I2C_IMR_WAIT_FOR_BUS_IDLE_TIMEOUT_Pos)

#define I2C_IMR_STRETCH_SCL_TIMEOUT_Pos          (16)
#define I2C_IMR_STRETCH_SCL_TIMEOUT_Msk          (0x1UL << I2C_IMR_STRETCH_SCL_TIMEOUT_Pos)

#define I2C_IMR_DEDICATE_POINT_Pos               (17)
#define I2C_IMR_DEDICATE_POINT_Msk               (0x1UL << I2C_IMR_DEDICATE_POINT_Pos)
/** @} */

/** @name STR - I2C_STR register */
/** @{ */
#define I2C_STR_BUSY_Pos                         (0)
#define I2C_STR_BUSY_Msk                         (0x1UL << I2C_STR_BUSY_Pos)

#define I2C_STR_ADDRESS_PHASE_Pos                (1)
#define I2C_STR_ADDRESS_PHASE_Msk                (0x1UL << I2C_STR_ADDRESS_PHASE_Pos)

#define I2C_STR_DATA_PHASE_Pos                   (2)
#define I2C_STR_DATA_PHASE_Msk                   (0x1UL << I2C_STR_DATA_PHASE_Pos)

#define I2C_STR_SLAVE_ADDRESSED_FLAG_Pos         (8)
#define I2C_STR_SLAVE_ADDRESSED_FLAG_Msk         (0x1UL << I2C_STR_SLAVE_ADDRESSED_FLAG_Pos)

#define I2C_STR_SLAVE_ADDRESSED_IND_Pos          (9)
#define I2C_STR_SLAVE_ADDRESSED_IND_Msk          (0x1UL << I2C_STR_SLAVE_ADDRESSED_IND_Pos)

#define I2C_STR_SLAVE_RWN_Pos                    (10)
#define I2C_STR_SLAVE_RWN_Msk                    (0x1UL << I2C_STR_SLAVE_RWN_Pos)

#define I2C_STR_TXRX_DATA_NUM_Pos                (16)
#define I2C_STR_TXRX_DATA_NUM_Msk                (0x1FFUL << I2C_STR_TXRX_DATA_NUM_Pos)
/** @} */

/** @name FSR - I2C_FSR register */
/** @{ */
#define I2C_FSR_TX_FIFO_FREE_NUM_Pos             (0)
#define I2C_FSR_TX_FIFO_FREE_NUM_Msk             (0x1FUL << I2C_FSR_TX_FIFO_FREE_NUM_Pos)

#define I2C_FSR_RX_FIFO_DATA_NUM_Pos             (8)
#define I2C_FSR_RX_FIFO_DATA_NUM_Msk             (0x1FUL << I2C_FSR_RX_FIFO_DATA_NUM_Pos)
/** @} */

/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_TypeDef *)I2C0_BASE_ADDR)

/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_TypeDef *)I2C1_BASE_ADDR)

/** @brief I2C peripheral instance number */
#define I2C_INSTANCE_NUM                         (2)

/**
  * @}
  */ /* end of group I2C */

/** @addtogroup PAD PAD
  * @{
  */

/** max number of pins in PAD */
#define PAD_PIN_MAX_NUM                          (43U)

/**
  * @brief PAD register layout typedef
  *
  */
typedef struct {
    __IO uint32_t PCR[PAD_PIN_MAX_NUM];          /**< PAD Control Register n, array offset: 0x0, array step:0x4 */
} PAD_TypeDef;

/** @name PCR - PAD_PCR register */
/** @{ */
#define PAD_PCR_MUX_Pos                          (4)
#define PAD_PCR_MUX_Msk                          (0x7UL << PAD_PCR_MUX_Pos)

#define PAD_PCR_PULL_UP_ENABLE_Pos               (8)
#define PAD_PCR_PULL_UP_ENABLE_Msk               (0x1UL << PAD_PCR_PULL_UP_ENABLE_Pos)

#define PAD_PCR_PULL_DOWN_ENABLE_Pos             (9)
#define PAD_PCR_PULL_DOWN_ENABLE_Msk             (0x1UL << PAD_PCR_PULL_DOWN_ENABLE_Pos)

#define PAD_PCR_PULL_SELECT_Pos                  (10)
#define PAD_PCR_PULL_SELECT_Msk                  (0x1UL << PAD_PCR_PULL_SELECT_Pos)

#define PAD_PCR_INPUT_BUFFER_ENABLE_Pos          (13)
#define PAD_PCR_INPUT_BUFFER_ENABLE_Msk          (0x1UL << PAD_PCR_INPUT_BUFFER_ENABLE_Pos)
/** @} */

/** Peripheral PAD base pointer */
#define PAD                                      ((PAD_TypeDef *) PAD_BASE_ADDR)

/**
  * @}
  */ /* end of group PAD */

/** @addtogroup SPI SPI
  * @{
  */

/**
  * @brief SPI register layout typedef
  *
  */
typedef struct {
    __IO uint32_t CR0;          /**< Control Register 0. Selects the serial clock rate, bus type, and data size.         offset: 0x0 */
    __IO uint32_t CR1;          /**< Control Register 1. Selects master/slave and other modes.                           offset: 0x4 */
    __IO uint32_t DR;           /**< Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO.     offset: 0x8 */
    __IO uint32_t SR;           /**< Status Register                                                                     offset: 0xC */
    __IO uint32_t CPSR;         /**< Clock Prescale Register                                                             offset: 0x10 */
    __IO uint32_t IMSC;         /**< Interrupt Mask Set and Clear Register                                               offset: 0x14 */
    __IO uint32_t RIS;          /**< Raw Interrupt Status Register                                                       offset: 0x18 */
    __IO uint32_t MIS;          /**< Masked Interrupt Status Register                                                    offset: 0x1C */
    __IO uint32_t ICR;          /**< Interrupt Clear Register                                                            offset: 0x20 */
    __IO uint32_t DMACR;        /**< DMA control register                                                                offset: 0x24 */
} SPI_TypeDef;

/** @name CR0 - SPI Control Register 0 */
/** @{ */

/** SPI data size select, must be 4 bits to 16 bits */
#define SPI_CR0_DSS_Pos                          (0)
#define SPI_CR0_DSS_Msk                          (0xFUL << SPI_CR0_DSS_Pos)

/** SPI Frame Format */
#define SPI_CR0_FRF_Pos                          (4)
#define SPI_CR0_FRF_Msk                          (0x3UL << SPI_CR0_FRF_Pos)

/** SPI Clock Out Polarity */
#define SPI_CR0_SPO_Pos                          (6)
#define SPI_CR0_SPO_Msk                          (0x1UL << SPI_CR0_SPO_Pos)

/** SPI Clock Out Phase */
#define SPI_CR0_SPH_Pos                          (7)
#define SPI_CR0_SPH_Msk                          (0x1UL << SPI_CR0_SPH_Pos)

/** SPI Serial Clock Rate */
#define SPI_CR0_SCR_Pos                          (8)
#define SPI_CR0_SCR_Msk                          (0xFFUL << SPI_CR0_SCR_Pos)
/** @} */

/** @name CR1 - SPI_CR1 register */
/** @{ */

/** SPI Loop Back Mode */
#define SPI_CR1_LBM_Pos                          (0)
#define SPI_CR1_LBM_Msk                          (0x1UL << SPI_CR1_LBM_Pos)

/** SPI Enable */
#define SPI_CR1_SSE_Pos                          (1)
#define SPI_CR1_SSE_Msk                          (0x1UL << SPI_CR1_SSE_Pos)

/** SPI Master/Slave Mode. */
#define SPI_CR1_MS_Pos                           (2)
#define SPI_CR1_MS_Msk                           (0x1UL << SPI_CR1_MS_Pos)

/** SPI Slave Output Disable. */
#define SPI_CR1_SOD_Pos                          (3)
#define SPI_CR1_SOD_Msk                          (0x1UL << SPI_CR1_SOD_Pos)
/** @} */

/** @name DR - SPI Data register */
/** @{ */
#define SPI_DR_DATA_Pos                          (0)
#define SPI_DR_DATA_Msk                          (0xFFFFUL << SPI_DR_DATA_Pos)
/** @} */

/** @name SR - SPI Status Register */
/** @{ */

/** SPI Transmit FIFO Empty. */
#define SPI_SR_TFE_Pos                           (0)
#define SPI_SR_TFE_Msk                           (0x1UL << SPI_SR_TFE_Pos)

/** SPI Transmit FIFO Not Empty. */
#define SPI_SR_TNF_Pos                           (1)
#define SPI_SR_TNF_Msk                           (0x1UL << SPI_SR_TNF_Pos)

/** SPI Receive FIFO Not Empty. */
#define SPI_SR_RNE_Pos                           (2)
#define SPI_SR_RNE_Msk                           (0x1UL << SPI_SR_RNE_Pos)

/** SPI Receive FIFO Full. */
#define SPI_SR_RFF_Pos                           (3)
#define SPI_SR_RFF_Msk                           (0x1UL << SPI_SR_RFF_Pos)

/** SPI Busy Status. */
#define SPI_SR_BSY_Pos                           (4)
#define SPI_SR_BSY_Msk                           (0x1UL << SPI_SR_BSY_Pos)
/** @} */

/** @name CPSR - SPI Clock Prescale Register */
/** @{ */
#define SPI_CPSR_CPSDVSR_Pos                     (0)
#define SPI_CPSR_CPSDVSR_Msk                     (0xFFUL << SPI_CPSR_CPSDVSR_Pos)
/** @} */

/** @name IMSC - SPI Interrupt Mask Set/Clear Register */
/** @{ */

/** SPI Receive Overrun Interruption. */
#define SPI_IMSC_RORIM_Pos                       (0)
#define SPI_IMSC_RORIM_Msk                       (0x1UL << SPI_IMSC_RORIM_Pos)

/** SPI Receive Timeout Interruption. */
#define SPI_IMSC_RTIM_Pos                        (1)
#define SPI_IMSC_RTIM_Msk                        (0x1UL << SPI_IMSC_RTIM_Pos)

/** SPI RX FIFO At Least Half Full Interrupt. */
#define SPI_IMSC_RXIM_Pos                        (2)
#define SPI_IMSC_RXIM_Msk                        (0x1UL << SPI_IMSC_RXIM_Pos)

/** SPI TX FIFO At Least Half Empty Interrupt. */
#define SPI_IMSC_TXIM_Pos                        (3)
#define SPI_IMSC_TXIM_Msk                        (0x1UL << SPI_IMSC_TXIM_Pos)
/** @} */

/** @name RIS - SPI Raw Interrupt Register */
/** @{ */

/** SPI Receive Overrun Status. */
#define SPI_RIS_RORRIS_Pos                       (0)
#define SPI_RIS_RORRIS_Msk                       (0x1UL << SPI_RIS_RORRIS_Pos)

/** SPI RX FIFO is not empty and has not been read for a period of 32 bit times. */
#define SPI_RIS_RTRIS_Pos                        (1)
#define SPI_RIS_RTRIS_Msk                        (0x1UL << SPI_RIS_RTRIS_Pos)

/** SPI RX FIFO At Least Half Full. */
#define SPI_RIS_RXRIS_Pos                        (2)
#define SPI_RIS_RXRIS_Msk                        (0x1UL << SPI_RIS_RXRIS_Pos)

/** SPI TX FIFO At Least Half Empty. */
#define SPI_RIS_TXRIS_Pos                        (3)
#define SPI_RIS_TXRIS_Msk                        (0x1UL << SPI_RIS_TXRIS_Pos)

/** @} */

/** @name MIS - SPI Masked Interrupt Status Register */
/** @{ */

/** SPI This bit is 1 if another frame was completely received while the RxFIFO was full, and this interrupt is enabled. */
#define SPI_MIS_RORMIS_Pos                       (0)
#define SPI_MIS_RORMIS_Msk                       (0x1UL << SPI_MIS_RORMIS_Pos)

/** SPI This bit is 1 if the Rx FIFO is not empty, has not been read for a period of 32 bit times, and this interrupt is enabled. */
#define SPI_MIS_RTMIS_Pos                        (1)
#define SPI_MIS_RTMIS_Msk                        (0x1UL << SPI_MIS_RTMIS_Pos)

/** SPI This bit is 1 if the Rx FIFO is at least half full, and this interrupt is enabled. */
#define SPI_MIS_RXMIS_Pos                        (2)
#define SPI_MIS_RXMIS_Msk                        (0x1UL << SPI_MIS_RXMIS_Pos)

/** SPI This bit is 1 if the Tx FIFO is at least half empty, and this interrupt is enabled. */
#define SPI_MIS_TXMIS_Pos                        (3)
#define SPI_MIS_TXMIS_Msk                        (0x1UL << SPI_MIS_TXMIS_Pos)
/** @} */

/** @name ICR - SPI Interrupt Clear Register */
/** @{ */

/** SPI Writing a 1 to this bit clears the “frame was received when RxFIFO was full” interrupt. */
#define SPI_ICR_RORIC_Pos                        (0)
#define SPI_ICR_RORIC_Msk                        (0x1UL << SPI_ICR_RORIC_Pos)

/** SPI Writing a 1 to this bit clears the "Rx FIFO was not empty and has not been read for a period of 32 bit times" interrupt. */
#define SPI_ICR_RTIC_Pos                         (1)
#define SPI_ICR_RTIC_Msk                         (0x1UL << SPI_ICR_RTIC_Pos)

//HBG
#define SPI_ICR_INT_CLEAR_Pos                     (3)
#define SPI_ICR_INT_CLEAR_Msk                     (0x1UL << SPI_ICR_INT_CLEAR_Pos)

/** @} */

/** @name DMACR - SPI DMA Control Register */
/** @{ */

/** SPI Receive DMA Enable. */
#define SPI_DMACR_RXDMAE_Pos                     (0)
#define SPI_DMACR_RXDMAE_Msk                     (0x1UL << SPI_DMACR_RXDMAE_Pos)

/** SPI Transmit DMA Enable. */
#define SPI_DMACR_TXDMAE_Pos                     (1)
#define SPI_DMACR_TXDMAE_Msk                     (0x1UL << SPI_DMACR_TXDMAE_Pos)

#define SPI_DMACR_BITMASK                         (uint32_t)0x03

/** @} */

/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_TypeDef *)SPI0_BASE_ADDR)

/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_TypeDef *)SPI1_BASE_ADDR)

/** @brief SPI peripheral instance number */
#define SPI_INSTANCE_NUM                         (2)

/**
  * @}
  */ /* end of group SPI */

/** @addtogroup TIMER Timer
  * @{
  */

/**
  * @brief TIMER register layout typedef
  *
  */
typedef struct {
    __IO uint32_t TCCR;                          /**< Timer Clock Control Register,                offset: 0x0 */
    __IO uint32_t TCTLR;                         /**< Timer Control Register,                      offset: 0x4 */
    __IO uint32_t TSR;                           /**< Timer Status Register,                       offset: 0x8 */
    __IO uint32_t TIVR;                          /**< Timer Init Value Register,                   offset: 0xC */
    __IO uint32_t TMR[3];                        /**< Timer Match N Register, array offset: 0x10, array step: 0x4 */
    __I  uint32_t TCR;                           /**< Timer Counter Register,                      offset: 0x1C */
    __IO uint32_t TCLR;                          /**< Timer Counter Latch Register,                offset: 0x20 */
} TIMER_TypeDef;

/** @name TCCR - TIMER_TCCR register */
/** @{ */
#define TIMER_TCCR_ENABLE_Pos                    (0)
#define TIMER_TCCR_ENABLE_Msk                    (0x1UL << TIMER_TCCR_ENABLE_Pos)
/** @} */

/** @name TCTLR - TIMER_TCTLR register */
/** @{ */
#define TIMER_TCTLR_MODE_Pos                     (0)
#define TIMER_TCTLR_MODE_Msk                     (0x1UL << TIMER_TCTLR_MODE_Pos)

#define TIMER_TCTLR_MCS_Pos                      (1)
#define TIMER_TCTLR_MCS_Msk                      (0x3UL << TIMER_TCTLR_MCS_Pos)

#define TIMER_TCTLR_IE_0_Pos                     (3)
#define TIMER_TCTLR_IE_0_Msk                     (0x1UL << TIMER_TCTLR_IE_0_Pos)

#define TIMER_TCTLR_IE_1_Pos                     (4)
#define TIMER_TCTLR_IE_1_Msk                     (0x1UL << TIMER_TCTLR_IE_1_Pos)

#define TIMER_TCTLR_IE_2_Pos                     (5)
#define TIMER_TCTLR_IE_2_Msk                     (0x1UL << TIMER_TCTLR_IE_1_Pos)

#define TIMER_TCTLR_IT_0_Pos                     (6)
#define TIMER_TCTLR_IT_0_Msk                     (0x1UL << TIMER_TCTLR_IT_0_Pos)

#define TIMER_TCTLR_IT_1_Pos                     (7)
#define TIMER_TCTLR_IT_1_Msk                     (0x1UL << TIMER_TCTLR_IT_1_Pos)

#define TIMER_TCTLR_IT_2_Pos                     (8)
#define TIMER_TCTLR_IT_2_Msk                     (0x1UL << TIMER_TCTLR_IT_2_Pos)

#define TIMER_TCTLR_PWMOUT_Pos                   (9)
#define TIMER_TCTLR_PWMOUT_Msk                   (0x1UL << TIMER_TCTLR_PWMOUT_Pos)
/** @} */

/** @name TSR - TIMER_TSR register */
/** @{ */
#define TIMER_TSR_ICLR_0_Pos                     (0)
#define TIMER_TSR_ICLR_0_Msk                     (0x1UL << TIMER_TSR_ICLR_0_Pos)

#define TIMER_TSR_ICLR_1_Pos                     (1)
#define TIMER_TSR_ICLR_1_Msk                     (0x1UL << TIMER_TSR_ICLR_1_Pos)

#define TIMER_TSR_ICLR_2_Pos                     (2)
#define TIMER_TSR_ICLR_2_Msk                     (0x1UL << TIMER_TSR_ICLR_2_Pos)
/** @} */

/** @name TIVR - TIMER_TIVR register */
/** @{ */
#define TIMER_TIVR_VALUE_Pos                     (0)
#define TIMER_TIVR_VALUE_Msk                     (0xFFFFFFFFUL << TIMER_TIVR_VALUE_Pos)
/** @} */

/** @name TMR - TIMER_TMR N register */
/** @{ */
#define TIMER_TMR_MATCH_Pos                      (0)
#define TIMER_TMR_MATCH_Msk                      (0xFFFFFFFFUL << TIMER_TMR_MATCH_Pos)
/** @} */

/** @name TCR - TIMER_TCR register */
/** @{ */
#define TIMER_TCR_VALUE_Pos                      (0)
#define TIMER_TCR_VALUE_Msk                      (0xFFFFFFFFUL << TIMER_TCR_VALUE_Pos)
/** @} */

/** @name TCLR - TIMER_TCLR register */
/** @{ */
#define TIMER_TCLR_LATCH_Pos                      (0)
#define TIMER_TCLR_LATCH_Msk                      (0x1UL << TIMER_TCLR_LATCH_Pos)
/** @} */


/** @brief TIMER peripheral instance number */
#define TIMER_INSTANCE_NUM                       (6)

/**
  * @}
  */ /* end of group TIMER */


/** @addtogroup USART USART
  * @{
  */

/**
  * @brief USART register layout typedef
  *
  */
typedef struct {
    union{
    __IO uint32_t RBR;                           /**< Receive Buffer Register,                  offset: 0x0 */
    __IO uint32_t THR;                           /**< Transmit Holding Register,                offset: 0x0 */
    __IO uint32_t DLL;                           /**< Divisor Latch Low,                        offset: 0x0 */
    };
    union{
    __IO uint32_t DLH;                           /**< Divisor Latch High,                       offset: 0x4 */
    __IO uint32_t IER;                           /**< Interrupt Enable Register,                offset: 0x4 */
    };
    union{
    __IO uint32_t IIR;                           /**< Interrupt Identification Register,        offset: 0x8 */
    __IO uint32_t FCR;                           /**< FIFO Control Register,                    offset: 0x8 */
    };
    __IO uint32_t LCR;                           /**< Line Control Register,                    offset: 0xC */
    __IO uint32_t MCR;                           /**< Modem Control Register,                   offset: 0x10 */
    __IO uint32_t LSR;                           /**< Line Status Register,                     offset: 0x14 */
    __IO uint32_t MSR;                           /**< Modem Status Register,                    offset: 0x18 */
    __IO uint32_t SCR;                           /**< Scratchpad Register,                      offset: 0x1C */
    __IO uint32_t MFCR;                          /**< Main Function Control Register,           offset: 0x20 */
    __IO uint32_t EFCR;                          /**< Extended Function Control Register,       offset: 0x24 */
    __IO uint32_t LPDR;                          /**< SIR Divisor Register,                     offset: 0x28 */
    __IO uint32_t FCNR;                          /**< Tx and Rx FIFO Character Number Register, offset: 0x2C */
    __IO uint32_t ADCR;                          /**< Auto-baud Detect Control Register,        offset: 0x30 */
    __IO uint32_t ADRR;                          /**< Auto-baud Detect Result Register,         offset: 0x34 */
} USART_TypeDef;

/** @name RBR - USART_RBR register */
/** @{ */
#define USART_RBR_RX_BUF_Pos                     (0)
#define USART_RBR_RX_BUF_Msk                     (0xFFUL << USART_RBR_RX_BUF_Pos)
/** @} */

/** @name THR - USART_THR register */
/** @{ */
#define USART_THR_TX_HOLDING_Pos                 (0)
#define USART_THR_TX_HOLDING_Msk                 (0xFFUL << USART_THR_TX_HOLDING_Pos)
/** @} */

/** @name DLL - USART_DLL register */
/** @{ */
#define USART_DLL_DLL_Pos                        (0)
#define USART_DLL_DLL_Msk                        (0xFFUL << USART_DLL_DLL_Pos)
/** @} */

/** @name DLH - USART_DLH register */
/** @{ */
#define USART_DLH_DLH_Pos                        (0)
#define USART_DLH_DLH_Msk                        (0xFFUL << USART_DLH_DLH_Pos)
/** @} */

/** @name IER - USART_IER register */
/** @{ */
#define USART_IER_RX_DATA_REQ_Pos                (0)
#define USART_IER_RX_DATA_REQ_Msk                (0x1UL << USART_IER_RX_DATA_REQ_Pos)

#define USART_IER_TX_DATA_REQ_Pos                (1)
#define USART_IER_TX_DATA_REQ_Msk                (0x1UL << USART_IER_TX_DATA_REQ_Pos)

#define USART_IER_RX_LINE_STATUS_Pos             (2)
#define USART_IER_RX_LINE_STATUS_Msk             (0x1UL << USART_IER_RX_LINE_STATUS_Pos)

#define USART_IER_MODEM_STATUS_Pos               (3)
#define USART_IER_MODEM_STATUS_Msk               (0x1UL << USART_IER_MODEM_STATUS_Pos)

#define USART_IER_RX_TIMEOUT_Pos                 (4)
#define USART_IER_RX_TIMEOUT_Msk                 (0x1UL << USART_IER_RX_TIMEOUT_Pos)
/** @} */

/** @name IIR - USART_IIR register */
/** @{ */
#define USART_IIR_INT_PENDING_Pos                (0)
#define USART_IIR_INT_PENDING_Msk                (0x1UL << USART_IIR_INT_PENDING_Pos)

#define USART_IIR_INT_ID_Pos                     (1)
#define USART_IIR_INT_ID_Msk                     (0xFUL << USART_IIR_INT_ID_Pos)
/** @} */

/** @name FCR - USART_FCR register */
/** @{ */
#define USART_FCR_FIFO_EN_Pos                    (0)
#define USART_FCR_FIFO_EN_Msk                    (0x1UL << USART_FCR_FIFO_EN_Pos)

#define USART_FCR_RESET_RX_FIFO_Pos              (1)
#define USART_FCR_RESET_RX_FIFO_Msk              (0x1UL << USART_FCR_RESET_RX_FIFO_Pos)

#define USART_FCR_RESET_TX_FIFO_Pos              (2)
#define USART_FCR_RESET_TX_FIFO_Msk              (0x1UL << USART_FCR_RESET_TX_FIFO_Pos)

#define USART_FCR_DMA_MODE_Pos                   (3)
#define USART_FCR_DMA_MODE_Msk                   (0x1UL << USART_FCR_DMA_MODE_Pos)

#define USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos   (4)
#define USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Msk   (0x3UL << USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos)

#define USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos   (6)
#define USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Msk   (0x3UL << USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos)
/** @} */

/** @name LCR - USART_LCR register */
/** @{ */
#define USART_LCR_CHAR_LEN_Pos                   (0)
#define USART_LCR_CHAR_LEN_Msk                   (0x3UL << USART_LCR_CHAR_LEN_Pos)

#define USART_LCR_STOP_BIT_NUM_Pos               (2)
#define USART_LCR_STOP_BIT_NUM_Msk               (0x1UL << USART_LCR_STOP_BIT_NUM_Pos)

#define USART_LCR_PARITY_EN_Pos                  (3)
#define USART_LCR_PARITY_EN_Msk                  (0x1UL << USART_LCR_PARITY_EN_Pos)

#define USART_LCR_EVEN_PARITY_Pos                (4)
#define USART_LCR_EVEN_PARITY_Msk                (0x1UL << USART_LCR_EVEN_PARITY_Pos)

#define USART_LCR_STICKY_PARITY_Pos              (5)
#define USART_LCR_STICKY_PARITY_Msk              (0x1UL << USART_LCR_STICKY_PARITY_Pos)

#define USART_LCR_SET_BREAK_Pos                  (6)
#define USART_LCR_SET_BREAK_Msk                  (0x1UL << USART_LCR_SET_BREAK_Pos)

#define USART_LCR_ACCESS_DIVISOR_LATCH_Pos       (7)
#define USART_LCR_ACCESS_DIVISOR_LATCH_Msk       (0x1UL << USART_LCR_ACCESS_DIVISOR_LATCH_Pos)
/** @} */

/** @name MCR - USART_MCR register */
/** @{ */
#define USART_MCR_DTR_Pos                        (0)
#define USART_MCR_DTR_Msk                        (0x1UL << USART_MCR_DTR_Pos)

#define USART_MCR_RTS_Pos                        (1)
#define USART_MCR_RTS_Msk                        (0x1UL << USART_MCR_RTS_Pos)

#define USART_MCR_OUT1_Pos                       (2)
#define USART_MCR_OUT1_Msk                       (0x1UL << USART_MCR_OUT1_Pos)

#define USART_MCR_OUT2_Pos                       (3)
#define USART_MCR_OUT2_Msk                       (0x1UL << USART_MCR_OUT2_Pos)

#define USART_MCR_LOOPBACK_MODE_Pos              (4)
#define USART_MCR_LOOPBACK_MODE_Msk              (0x1UL << USART_MCR_LOOPBACK_MODE_Pos)
/** @} */

/** @name LSR - USART_LSR register */
/** @{ */
#define USART_LSR_RX_DATA_READY_Pos              (0)
#define USART_LSR_RX_DATA_READY_Msk              (0x1UL << USART_LSR_RX_DATA_READY_Pos)

#define USART_LSR_RX_OVERRUN_ERROR_Pos           (1)
#define USART_LSR_RX_OVERRUN_ERROR_Msk           (0x1UL << USART_LSR_RX_OVERRUN_ERROR_Pos)

#define USART_LSR_RX_PARITY_ERROR_Pos            (2)
#define USART_LSR_RX_PARITY_ERROR_Msk            (0x1UL << USART_LSR_RX_PARITY_ERROR_Pos)

#define USART_LSR_RX_FRAME_ERROR_Pos             (3)
#define USART_LSR_RX_FRAME_ERROR_Msk             (0x1UL << USART_LSR_RX_FRAME_ERROR_Pos)

#define USART_LSR_RX_BREAK_Pos                   (4)
#define USART_LSR_RX_BREAK_Msk                   (0x1UL << USART_LSR_RX_BREAK_Pos)

#define USART_LSR_TX_DATA_REQ_Pos                (5)
#define USART_LSR_TX_DATA_REQ_Msk                (0x1UL << USART_LSR_TX_DATA_REQ_Pos) /*!< Line status: Transmit holding register empty */

#define USART_LSR_TX_EMPTY_Pos                   (6)
#define USART_LSR_TX_EMPTY_Msk                   (0x1UL << USART_LSR_TX_EMPTY_Pos)

#define USART_LSR_RX_FIFO_ERROR_Pos              (7)
#define USART_LSR_RX_FIFO_ERROR_Msk              (0x1UL << USART_LSR_RX_FIFO_ERROR_Pos)

#define USART_LSR_RX_BUSY_Pos                    (10)
#define USART_LSR_RX_BUSY_Msk                    (0x1UL << USART_LSR_RX_BUSY_Pos)
/** @} */

/** @name MSR - USART_MSR register */
/** @{ */
#define USART_MSR_CTS_CHANGED_Pos                (0)
#define USART_MSR_CTS_CHANGED_Msk                (0x1UL << USART_MSR_CTS_CHANGED_Pos)

#define USART_MSR_DSR_CHANGED_Pos                (1)
#define USART_MSR_DSR_CHANGED_Msk                (0x1UL << USART_MSR_DSR_CHANGED_Pos)

#define USART_MSR_RI_CHANGED_Pos                 (2)
#define USART_MSR_RI_CHANGED_Msk                 (0x1UL << USART_MSR_RI_CHANGED_Pos)

#define USART_MSR_DCD_CHANGED_Pos                (3)
#define USART_MSR_DCD_CHANGED_Msk                (0x1UL << USART_MSR_DCD_CHANGED_Pos)

#define USART_MSR_CTS_Pos                        (4)
#define USART_MSR_CTS_Msk                        (0x1UL << USART_MSR_CTS_Pos)

#define USART_MSR_DSR_Pos                        (5)
#define USART_MSR_DSR_Msk                        (0x1UL << USART_MSR_DSR_Pos)

#define USART_MSR_RI_Pos                         (6)
#define USART_MSR_RI_Msk                         (0x1UL << USART_MSR_RI_Pos)

#define USART_MSR_DCD_Pos                        (7)
#define USART_MSR_DCD_Msk                        (0x1UL << USART_MSR_DCD_Pos)
/** @} */

/** @name SCR - USART_SCR register */
/** @{ */
#define USART_SCR_SCRATCH_Pos                    (0)
#define USART_SCR_SCRATCH_Msk                    (0xFFUL << USART_SCR_SCRATCH_Pos)
/** @} */

/** @name MFCR - USART_MFCR register */
/** @{ */
#define USART_MFCR_UART_EN_Pos                   (0)
#define USART_MFCR_UART_EN_Msk                   (0x1UL << USART_MFCR_UART_EN_Pos)

#define USART_MFCR_NRZ_CODING_Pos                (1)
#define USART_MFCR_NRZ_CODING_Msk                (0x1UL << USART_MFCR_NRZ_CODING_Pos)

#define USART_MFCR_DMA_EN_Pos                    (2)
#define USART_MFCR_DMA_EN_Msk                    (0x1UL << USART_MFCR_DMA_EN_Pos)

#define USART_MFCR_AUTO_FLOW_RTS_EN_Pos          (4)
#define USART_MFCR_AUTO_FLOW_RTS_EN_Msk          (0x1UL << USART_MFCR_AUTO_FLOW_RTS_EN_Pos)

#define USART_MFCR_AUTO_FLOW_CTS_EN_Pos          (5)
#define USART_MFCR_AUTO_FLOW_CTS_EN_Msk          (0x1UL << USART_MFCR_AUTO_FLOW_CTS_EN_Pos)

#define USART_MFCR_PRESCALE_FACTOR_Pos           (8)
#define USART_MFCR_PRESCALE_FACTOR_Msk           (0x3UL << USART_MFCR_PRESCALE_FACTOR_Pos)

/** @} */

/** @name EFCR - USART_EFCR register */
/** @{ */
#define USART_EFCR_TX_MODE_Pos                   (0)
#define USART_EFCR_TX_MODE_Msk                   (0x1UL << USART_EFCR_TX_MODE_Pos)

#define USART_EFCR_RX_MODE_Pos                   (1)
#define USART_EFCR_RX_MODE_Msk                   (0x1UL << USART_EFCR_RX_MODE_Pos)

#define USART_EFCR_SIR_LOW_POWER_Pos             (2)
#define USART_EFCR_SIR_LOW_POWER_Msk             (0x1UL << USART_EFCR_SIR_LOW_POWER_Pos)

#define USART_EFCR_TX_POLARITY_Pos               (3)
#define USART_EFCR_TX_POLARITY_Msk               (0x1UL << USART_EFCR_TX_POLARITY_Pos)

#define USART_EFCR_RX_POLARITY_Pos               (4)
#define USART_EFCR_RX_POLARITY_Msk               (0x1UL << USART_EFCR_RX_POLARITY_Pos)

#define USART_EFCR_FRAC_DIVISOR_Pos              (8)
#define USART_EFCR_FRAC_DIVISOR_Msk              (0xFUL << USART_EFCR_FRAC_DIVISOR_Pos)
/** @} */

/** @name LPDR - USART_LPDR register */
/** @{ */
#define USART_LPDR_SIR_DIVISOR_Pos               (0)
#define USART_LPDR_SIR_DIVISOR_Msk               (0xFFFFUL << USART_LPDR_SIR_DIVISOR_Pos)
/** @} */

/** @name FCNR - USART_FCNR register */
/** @{ */
#define USART_FCNR_TX_FIFO_NUM_Pos               (0)
#define USART_FCNR_TX_FIFO_NUM_Msk               (0xFFUL << USART_FCNR_TX_FIFO_NUM_Pos)

#define USART_FCNR_RX_FIFO_NUM_Pos               (16)
#define USART_FCNR_RX_FIFO_NUM_Msk               (0xFFUL << USART_FCNR_RX_FIFO_NUM_Pos)
/** @} */

/** @name ADCR - USART_ADCR register */
/** @{ */
#define USART_ADCR_AUTO_BAUD_EN_Pos              (0)
#define USART_ADCR_AUTO_BAUD_EN_Msk              (0x1UL << USART_ADCR_AUTO_BAUD_EN_Pos)

#define USART_ADCR_AUTO_BAUD_INT_EN_Pos          (1)
#define USART_ADCR_AUTO_BAUD_INT_EN_Msk          (0x1UL << USART_ADCR_AUTO_BAUD_INT_EN_Pos)

#define USART_ADCR_AUTO_BAUD_PROG_SEL_Pos        (2)
#define USART_ADCR_AUTO_BAUD_PROG_SEL_Msk        (0x1UL << USART_ADCR_AUTO_BAUD_PROG_SEL_Pos)
/** @} */

/** @name ADRR - USART_ADRR register */
/** @{ */
#define USART_ADRR_AUTO_BAUD_INTE_Pos            (0)
#define USART_ADRR_AUTO_BAUD_INTE_Msk            (0xFFFFUL << USART_ADRR_AUTO_BAUD_INTE_Pos)

#define USART_ADRR_AUTO_BAUD_FRAC_Pos            (16)
#define USART_ADRR_AUTO_BAUD_FRAC_Msk            (0xFUL << USART_ADRR_AUTO_BAUD_FRAC_Pos)
/** @} */

/** Peripheral USART_0 base pointer */
#define USART_0                                  ((USART_TypeDef *)USART0_BASE_ADDR)

/** Peripheral USART_1 base pointer */
#define USART_1                                  ((USART_TypeDef *)USART1_BASE_ADDR)

/** Peripheral USART_2 base pointer */
#define USART_2                                  ((USART_TypeDef *)USART2_BASE_ADDR)


/** @brief USART peripheral instance number */
#define USART_INSTANCE_NUM                       (3)

/**
  * @}
  */ /* end of group USART */

/** @addtogroup WDT Watchdog
  * @{
  */

/**
  * @brief WDT register layout typedef
  *
  */
typedef struct {
    __IO uint32_t CTRL;                          /**< WDT Control Register,               offset: 0x0 */
    __IO uint32_t TOVR;                          /**< WDT Timerout Value Register,        offset: 0x4 */
    __O  uint32_t CCR;                           /**< WDT Counter Clear Register,         offset: 0x8 */
    __O  uint32_t ICR;                           /**< WDT Interrupt Clear Register,       offset: 0xC */
    __O  uint32_t LOCK;                          /**< WDT Lock Register,                  offset: 0x10 */
    __I  uint32_t STAT;                          /**< WDT Status Register,                offset: 0x14 */
} WDT_TypeDef;

/** @name CTRL - WDT_CTRL register */
/** @{ */
#define WDT_CTRL_ENABLE_Pos                      (0)
#define WDT_CTRL_ENABLE_Msk                      (0x1UL << WDT_CTRL_ENABLE_Pos)

#define WDT_CTRL_MODE_Pos                        (1)
#define WDT_CTRL_MODE_Msk                        (0x1UL << WDT_CTRL_MODE_Pos)
/** @} */

/** @name TOVR - WDT_TOVR register */
/** @{ */
#define WDT_TOVR_VAL_Pos                         (0)
#define WDT_TOVR_VAL_Msk                         (0xFFFFUL << WDT_TOVR_VAL_Pos)
/** @} */

/** @name CCR - WDT_CCR register */
/** @{ */
#define WDT_CCR_CNT_CLR_Pos                      (0)
#define WDT_CCR_CNT_CLR_Msk                      (0x1UL << WDT_CCR_CNT_CLR_Pos)
/** @} */

/** @name ICR - WDT_ICR register */
/** @{ */
#define WDT_ICR_ICLR_Pos                         (0)
#define WDT_ICR_ICLR_Msk                         (0x1UL << WDT_ICR_ICLR_Pos)
/** @} */

/** @name LOCK - WDT_LOCK register */
/** @{ */
#define WDT_LOCK_LOCK_VAL_Pos                    (0)
#define WDT_LOCK_LOCK_VAL_Msk                    (0xFFFFUL << WDT_LOCK_LOCK_VAL_Pos)
/** @} */

/** @name STAT - WDT_STAT register */
/** @{ */
#define WDT_STAT_CV_Pos                          (0)
#define WDT_STAT_CV_Msk                          (0xFFFFUL << WDT_STAT_CV_Pos)

#define WDT_STAT_ISTAT_Pos                       (16)
#define WDT_STAT_ISTAT_Msk                       (0x1UL << WDT_STAT_ISTAT_Pos)
/** @} */

/** Peripheral WDT base pointer */
#define WDT                                      ((WDT_TypeDef *)WDT_BASE_ADDR)

/**
  * @}
  */ /* end of group WDT */
/** @addtogroup XIC XIC(external interrupt controller)
  * @{
  */

/**
  * @brief XIC register layout typedef
  *
  */
typedef struct {
    __IO uint32_t LATCHIRQ;                      /**< Latch IRQ Register,                           offset: 0x0 */
    __IO uint32_t IRQSTATUS;                     /**< IRQ Status Register,                          offset: 0x4 */
    __IO uint32_t MASK;                          /**< IRQ Mask Register,                            offset: 0x8 */
    __IO uint32_t PEND;                          /**< Pend Register,                                offset: 0xC */
    __IO uint32_t SWGENIRQ;                      /**< Software Generat IRQ Register,                offset: 0x10 */
    __IO uint32_t CLRIRQ;                        /**< IRQ Clear Register,                           offset: 0x14 */
    __IO uint32_t CLROVF;                        /**< Clear IRQ Overflow Register,                  offset: 0x18 */
    __IO uint32_t OVFSTATUS;                     /**< IRQ Overflow Status Register,                 offset: 0x1C */
} XIC_TypeDef;

/** Peripheral XIC_0 base pointer */
#define XIC_0                                    ((XIC_TypeDef *)XIC0_BASE_ADDR)

/** Peripheral XIC_1 base pointer */
#define XIC_1                                    ((XIC_TypeDef *)XIC1_BASE_ADDR)

/**
  * @}
  */ /* end of group XIC */
/** @addtogroup DMA DMA
  * @{
  */

/** @brief Number of DMA channel */
#define DMA_NUMBER_OF_HW_CHANNEL_SUPPORTED       (8U)

/** @brief List of DMA request sources */
typedef enum _dma_request_source
{
    DMA_MemoryToMemory = -1,                     /**< Dummy for memory to memory transfer */
    DMA_RequestI2C0TX = 3,                       /**< I2C0 TX                             */
    DMA_RequestI2C0RX,                           /**< I2C0 RX                             */
    DMA_RequestI2C1TX,                           /**< I2C1 TX                             */
    DMA_RequestI2C1RX,                           /**< I2C1 RX                             */
    DMA_RequestRFFETX,                           /**< RFFE TX                             */
    DMA_RequestRFFERX,                           /**< RFFE RX                             */
    DMA_RequestSPI0TX,                           /**< SPI0 TX                             */
    DMA_RequestSPI0RX,                           /**< SPI0 RX                             */
    DMA_RequestSPI1TX,                           /**< SPI1 TX                             */
    DMA_RequestSPI1RX,                           /**< SPI1 RX                             */
    DMA_RequestUSART0TX,                         /**< USART0 TX                           */
    DMA_RequestUSART0RX,                         /**< USART0 RX                           */
    DMA_RequestUSART1TX,                         /**< USART1 TX                           */
    DMA_RequestUSART1RX,                         /**< USART1 RX                           */
    DMA_RequestUSART2TX,                         /**< USART2 TX                           */
    DMA_RequestUSART2RX,                         /**< USART2 RX                           */
    DMA_RequestUSIMTX,                           /**< USIM TX                             */
    DMA_RequestUSIMRX,                           /**< USIM RX                             */

    DMA_RequestFLASHTX = 44,                     /**< FLASH TX                            */
    DMA_RequestFLASHRX,                          /**< FLASH RX                            */
    DMA_RequestUNILOGTX,                         /**< UNILOG TX                           */
} dma_request_source_t;

/** @brief DMA channel mapping */
#define UNILOG_TX_CHANNEL                        (0)
#define DMA_CHANNEL_DYNAMIC_ALLOC_START          (1U)
#define DMA_CHANNEL_DYNAMIC_ALLOC_END            (DMA_NUMBER_OF_HW_CHANNEL_SUPPORTED)
/**
  * @}
  */ /* end of group DMA */


/*  End of section using anonymous unions and disabling warnings   */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/** @addtogroup Bit_Field_Access_Macros Macros for use with bit field definitions (xxx_Pos, xxx_Msk)
  * @{
  */

/**
 * @brief   Mask and shift a bit field value for use in a register bit range
 *
 * @param[in] field  Name of the register bit field
 * @param[in] value  Value of the bit field
 * @return           Masked and shifted value
 */
#define QCOM_VAL2FLD(field, value)    (((value) << field ## _Pos) & field ## _Msk)

/**
 * @brief     Mask and shift a register value to extract a bit filed value
 *
 * @param[in] field  Name of the register bit field
 * @param[in] value  Value of register
 * @return           Masked and shifted bit field value
*/
#define QCOM_FLD2VAL(field, value)    (((value) & field ## _Msk) >> field ## _Pos)

/**
  * @}
  */ /* end of group Bit_Field_Access_Macros */

/**
  * @}
  */ /* end of group Device_peripheral_access */

#ifdef __cplusplus
}
#endif

#endif /* QCX212_H */
