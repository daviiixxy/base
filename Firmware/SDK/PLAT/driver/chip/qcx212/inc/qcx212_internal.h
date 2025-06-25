/**
 *****************************************************************************
 * @brief   Device Peripheral(internal) Access Layer Header File.
 *          This file contains all the peripheral register's definitions, bits
 *          definitions and memory mapping for QCX212 chip.
 *
 * @file   qcx212_internal.h
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

#ifndef QCX212_INTERNAL_H
#define QCX212_INTERNAL_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

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

/* Modem Specific Interrupt Numbers  */
  MXIC_Ovf_IRQn                 =   64,     /**< Modem SW or HW Error Interrupt */
  MXIC_RxLog_Err_IRQn           =   65,     /**< Modem RX Log Overflow Interrupt */
  MXIC_TxLog_Err_IRQn           =   66,     /**< Modem TX Log Overflow Interrupt */
  MXIC_SqLog_Err_IRQn           =   67,     /**< Modem SQ Log Overflow Interrupt */
  MXIC_SqIfRd_Err_IRQn          =   68,     /**< Modem SW Behavior Error Interrupt */
  MXIC_SwIfRd_Err_IRQn          =   69,     /**< Modem SW Behavior Error Interrupt */
  MXIC_SqIfSqAccess_Err_IRQn    =   70,     /**< Modem SW Behavior Error Interrupt */
  MXIC_SqIfSwAccess_Err_IRQn    =   71,     /**< Modem SW Behavior Error Interrupt */
  MXIC_BBDmaDump_Lost_IRQn      =   72,     /**< Modem HW DMA Error Interrupt */
  MXIC_RxTxWork_Err_IRQn        =   73,     /**< Modem HW Error Interrupt */
  MXIC_RxClkReq_Err_IRQn        =   74,     /**< Modem HW Error Interrupt */
  MXIC_TxAdpt_Err_IRQn          =   75,     /**< Modem Scheduler Error Interrupt */
  MXIC_RxDec_IRQn               =   76,     /**< Modem DEC Calculation Interrupt */
  MXIC_RxCe_Axc_IRQn            =   77,     /**< Modem AXC Interrupt */
  MXIC_RxCe_Blkdet_IRQn         =   78,     /**< Modem Change Blocker config Interrupt */
  MXIC_RxIcs_IRQn               =   79,     /**< Modem ICS Calculation Interrupt */
  MXIC_RxDfe_Blkdet_IRQn        =   80,     /**< Modem Change Blocker config Interrupt */
  MXIC_TxEnc_IRQn               =   81,     /**< Modem TxEnc Interrupt */
  MXIC_SqSwTpuCollid_IRQn       =   82,     /**< Modem SW Behavior Error Interrupt */
  MXIC_SqTpuTimesigInt0_IRQn    =   83,     /**< Modem Tpu to SW Indication0 Interrupt */
  MXIC_SqTpuTimesigInt1_IRQn    =   84,     /**< Modem Tpu to SW Indication1 Interrupt */
  MXIC_SqTpuTimesigInt2_IRQn    =   85,     /**< Modem Tpu to SW Indication2 Interrupt */
  MXIC_SqTpuTimesigInt3_IRQn    =   86,     /**< Modem Tpu to SW Indication3 Interrupt */
  MXIC_SqL1Time0_IRQn           =   87,     /**< Modem L1 Timer0 Interrupt */
  MXIC_SqL1Time1_IRQn           =   88,     /**< Modem L1 Timer1 Interrupt */
  MXIC_SqL1Time2_IRQn           =   89,     /**< Modem L1 Timer2 Interrupt */
  MXIC_SqL1Time3_IRQn           =   90,     /**< Modem L1 Timer3 Interrupt */
  MXIC_SqPsTimer_IRQn           =   91,     /**< Modem PS Timer Interrupt */
  MXIC_SqBcLatch_IRQn           =   92,     /**< Modem BC Latch Interrupt */
  MXIC_SqBcLoad_IRQn            =   93,     /**< Modem BC Load Interrupt */
  MXIC_TpuL1Timer0_IRQn         =   94,     /**< Modem Tpu L1 Timer0 Interrupt */
  MXIC_TpuL1Timer1_IRQn         =   95,     /**< Modem Tpu L1 Timer1 Interrupt */

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

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/** @addtogroup Device_peripheral_access Device Peripheral Access
  * @{
  */


/** @addtogroup BASE_ADDR Peripheral instance base addresses
  * @{
  */

/**
  * @brief XIC base address
  *
  */
#define XIC_BASE_ADDR                            ((unsigned int)0x47030000)

#define XIC0_BASE_ADDR                           (XIC_BASE_ADDR+0x000000)     /**< XIC0(manage APB peripheral interrupt) base address */
#define XIC1_BASE_ADDR                           (XIC_BASE_ADDR+0x008000)     /**< XIC1(manage Modem related interupt) base address */

/**
  * @brief APB base address
  *
  */
#define APB_PERIPH_BASE                          ((unsigned int)0x44000000)   /**< APB peripheral base address */

#define PMU_BASE_ADDR                            (APB_PERIPH_BASE + 0x000000) /**< PMU base address */
#define PMUDIG_BASE_ADDR                         (APB_PERIPH_BASE + 0x010000) /**< PMUDIG base address */
#define RFDIG_BASE_ADDR                          (APB_PERIPH_BASE + 0x020000) /**< RFDIG base address */
#define EFUSE_BASE_ADDR                          (APB_PERIPH_BASE + 0x030000) /**< EFUSE base address */
#define GPR_BASE_ADDR                            (APB_PERIPH_BASE + 0x050000) /**< GPR base address */
#define RFFE_BASE_ADDR                           (APB_PERIPH_BASE + 0x090000) /**< RFFE base address */
#define USIM_BASE_ADDR                           (APB_PERIPH_BASE + 0x100000) /**< USIM base address */
#define DMA_HW_BASE_ADDR                         (APB_PERIPH_BASE + 0x1f0000) /**< DMA base address */

#define GPR_RMI_BASE_ADDR                        (0x47000000UL)               /**< GPR_RMI base address */

#define QSPI_R_BASE                              (0x0FFF0000UL)               /**< QSPI base address */

#define QCOM_CACHE_BASE                         (0x47010000UL)               /**< CACHE base address */

#define UNILOG_BASE_ADDR                         (0x10000000UL)               /**< UNILOG base address */

#define BB_BASE_ADDR                             (0x46000000UL)               /**< Modem BB base address */

#define SQ_BASE_ADDR                             (0x47040000UL)               /**< Modem SQ base address */

/**
  * @}
  */ /* end of group BASE_ADDR */

/** @addtogroup CACHE Cache
  * @{
  */

/**
  * @brief CACHE register layout typedef
  *
  */
typedef struct {
    __IO uint32_t CCR;                           /**< Configuration and Control Register,               offset: 0x0 */
    __I  uint32_t SR;                            /**< Status Register,                                  offset: 0x4 */
    __IO uint32_t IRQMASK;                       /**< Interrupt Request Mask Register,                  offset: 0x8 */
    __IO uint32_t IRQSTAT;                       /**< Interrupt Request Status Register,                offset: 0xC */
    __I  uint32_t HWPARAMS;                      /**< Hardware Parameters Register,                     offset: 0x10 */
    __IO uint32_t CSHR;                          /**< Cache Statistic Hit Register,                     offset: 0x14 */
    __IO uint32_t CSMR;                          /**< Cache Statistic Miss Register,                    offset: 0x18 */
} CACHE_TypeDef;

/** @name CCR - CACHE_CCR register */
/** @{ */
#define CACHE_CCR_EN_Pos                         (0)
#define CACHE_CCR_EN_Msk                         (0x1UL << CACHE_CCR_EN_Pos)

#define CACHE_CCR_INV_REQ_Pos                    (1)
#define CACHE_CCR_INV_REQ_Msk                    (0x1UL << CACHE_CCR_INV_REQ_Pos)

#define CACHE_CCR_POW_REQ_Pos                    (2)
#define CACHE_CCR_POW_REQ_Msk                    (0x1UL << CACHE_CCR_POW_REQ_Pos)

#define CACHE_CCR_SET_MAN_POW_Pos                (3)
#define CACHE_CCR_SET_MAN_POW_Msk                (0x1UL << CACHE_CCR_SET_MAN_POW_Pos)

#define CACHE_CCR_SET_MAN_INV_Pos                (4)
#define CACHE_CCR_SET_MAN_INV_Msk                (0x1UL << CACHE_CCR_SET_MAN_INV_Pos)

#define CACHE_CCR_SET_PREFETCH_Pos               (5)
#define CACHE_CCR_SET_PREFETCH_Msk               (0x1UL << CACHE_CCR_SET_PREFETCH_Pos)

#define CACHE_CCR_STATISTIC_EN_Pos               (6)
#define CACHE_CCR_STATISTIC_EN_Msk               (0x1UL << CACHE_CCR_STATISTIC_EN_Pos)
/** @} */

/** @name SR - CACHE_SR register */
/** @{ */
#define CACHE_SR_CS_Pos                          (0)
#define CACHE_SR_CS_Msk                          (0x3UL << CACHE_SR_CS_Pos)

#define CACHE_SR_INV_STAT_Pos                    (2)
#define CACHE_SR_INV_STAT_Msk                    (0x1UL << CACHE_SR_INV_STAT_Pos)

#define CACHE_SR_POW_STAT_Pos                    (4)
#define CACHE_SR_POW_STAT_Msk                    (0x1UL << CACHE_SR_POW_STAT_Pos)
/** @} */

/** @name IRQMASK - CACHE_IRQMASK register */
/** @{ */
#define CACHE_IRQMASK_POW_ERR_Pos                (0)
#define CACHE_IRQMASK_POW_ERR_Msk                (0x1UL << CACHE_IRQMASK_POW_ERR_Pos)

#define CACHE_IRQMASK_MAN_INV_ERR_Pos            (1)
#define CACHE_IRQMASK_MAN_INV_ERR_Msk            (0x1UL << CACHE_IRQMASK_MAN_INV_ERR_Pos)
/** @} */

/** @name IRQSTAT - CACHE_IRQSTAT register */
/** @{ */
#define CACHE_IRQSTAT_POW_ERR_Pos                (0)
#define CACHE_IRQSTAT_POW_ERR_Msk                (0x1UL << CACHE_IRQSTAT_POW_ERR_Pos)

#define CACHE_IRQSTAT_MAN_INV_ERR_Pos            (1)
#define CACHE_IRQSTAT_MAN_INV_ERR_Msk            (0x1UL << CACHE_IRQSTAT_MAN_INV_ERR_Pos)
/** @} */

/** @name HWPARAMS - CACHE_HWPARAMS register */
/** @{ */
#define CACHE_HWPARAMS_AW_Pos                    (0)
#define CACHE_HWPARAMS_AW_Msk                    (0x1FUL << CACHE_HWPARAMS_AW_Pos)

#define CACHE_HWPARAMS_CW_Pos                    (5)
#define CACHE_HWPARAMS_CW_Msk                    (0x1FUL << CACHE_HWPARAMS_CW_Pos)

#define CACHE_HWPARAMS_CACHE_WAY_Pos             (10)
#define CACHE_HWPARAMS_CACHE_WAY_Msk             (0x3UL << CACHE_HWPARAMS_CACHE_WAY_Pos)

#define CACHE_HWPARAMS_RESET_ALL_REGS_Pos        (12)
#define CACHE_HWPARAMS_RESET_ALL_REGS_Msk        (0x1UL << CACHE_HWPARAMS_RESET_ALL_REGS_Pos)

#define CACHE_HWPARAMS_GEN_STAT_LOGIC_Pos        (13)
#define CACHE_HWPARAMS_GEN_STAT_LOGIC_Msk        (0x1UL << CACHE_HWPARAMS_GEN_STAT_LOGIC_Pos)
/** @} */

/** @name CSHR - CACHE_CSHR register */
/** @{ */
#define CACHE_CSHR_CSHR_Pos                      (0)
#define CACHE_CSHR_CSHR_Msk                      (0xFFFFFFFFUL << CACHE_CSHR_CSHR_Pos)
/** @} */

/** @name CSMR - CACHE_CSMR register */
/** @{ */
#define CACHE_CSMR_CSMR_Pos                      (0)
#define CACHE_CSMR_CSMR_Msk                      (0xFFFFFFFFUL << CACHE_CSMR_CSMR_Pos)
/** @} */

/** Peripheral CACHE base pointer */
#define QCOM_CACHE                              ((CACHE_TypeDef *) QCOM_CACHE_BASE)

/**
  * @}
  */ /* end of group CACHE */


/** @addtogroup DMA DMA
  * @{
  */

/** @brief Number of DMA channel */
#define DMA_NUMBER_OF_HW_CHANNEL_SUPPORTED       (8U)

/** @brief Maxium number of DMA request sources */
#define DMA_NUMBER_OF_REQUEST_SUPPORTED          (52U)

/**
  * @brief DMA register layout typedef
  *
  */
typedef struct {
    __IO uint32_t CSR[8];                        /**< DMA Control and Status Register,  array offset: 0x0, array step: 0x4 */
         uint32_t RESERVED_0[8];
    __IO uint32_t ACR[8];                        /**< DMA Align Control Register,                       array offset: 0x40, array step: 0x4 */
         uint32_t RESERVED_1[11];
    __IO uint32_t CHIIR;                         /**< DMA Channel Interrupt Indication Register,                   offset: 0x8C */
         uint32_t RESERVED_2[28];
    __IO uint32_t RCMR[52];                      /**< DMA Request to Channel Map Register,      array offset: 0x100, array step: 0x4 */
         uint32_t RESERVED_3[12];
    struct {
    __IO uint32_t DAR;                           /**< DMA Descriptor Address Register,          array offset: 0x200, array step: 0x10 */
    __IO uint32_t SAR;                           /**< DMA Source Address Register,              array offset: 0x204, array step: 0x10  */
    __IO uint32_t TAR;                           /**< DMA Target Address Register,              array offset: 0x208, array step: 0x10  */
    __IO uint32_t CMDR;                          /**< DMA Command Register,                     array offset: 0x20C, array step: 0x10  */
    } DESC[8];
} DMA_TypeDef;

/** @name CSR - DMA_CSR N register */
/** @{ */
#define DMA_CSR_BUSERRIRQ_Pos                    (0)
#define DMA_CSR_BUSERRIRQ_Msk                    (0x1UL << DMA_CSR_BUSERRIRQ_Pos)

#define DMA_CSR_STARTIRQ_Pos                     (1)
#define DMA_CSR_STARTIRQ_Msk                     (0x1UL << DMA_CSR_STARTIRQ_Pos)

#define DMA_CSR_ENDIRQ_Pos                       (2)
#define DMA_CSR_ENDIRQ_Msk                       (0x1UL << DMA_CSR_ENDIRQ_Pos)

#define DMA_CSR_STOPIRQ_Pos                      (3)
#define DMA_CSR_STOPIRQ_Msk                      (0x1UL << DMA_CSR_STOPIRQ_Pos)

#define DMA_CSR_REQAS_Pos                        (4)
#define DMA_CSR_REQAS_Msk                        (0x1UL << DMA_CSR_REQAS_Pos)

#define DMA_CSR_REQPENDING_Pos                   (8)
#define DMA_CSR_REQPENDING_Msk                   (0x1UL << DMA_CSR_REQPENDING_Pos)

#define DMA_CSR_EORIRQ_Pos                       (9)
#define DMA_CSR_EORIRQ_Msk                       (0x1UL << DMA_CSR_EORIRQ_Pos)

#define DMA_CSR_REQASEN_Pos                      (23)
#define DMA_CSR_REQASEN_Msk                      (0x1UL << DMA_CSR_REQASEN_Pos)

#define DMA_CSR_EORSTOPEN_Pos                    (26)
#define DMA_CSR_EORSTOPEN_Msk                    (0x1UL << DMA_CSR_EORSTOPEN_Pos)

#define DMA_CSR_EORJMPEN_Pos                     (27)
#define DMA_CSR_EORJMPEN_Msk                     (0x1UL << DMA_CSR_EORJMPEN_Pos)

#define DMA_CSR_EORIRQEN_Pos                     (28)
#define DMA_CSR_EORIRQEN_Msk                     (0x1UL << DMA_CSR_EORIRQEN_Pos)

#define DMA_CSR_STOPIRQEN_Pos                    (29)
#define DMA_CSR_STOPIRQEN_Msk                    (0x1UL << DMA_CSR_STOPIRQEN_Pos)

#define DMA_CSR_MODESEL_Pos                      (30)
#define DMA_CSR_MODESEL_Msk                      (0x1UL << DMA_CSR_MODESEL_Pos)

#define DMA_CSR_RUN_Pos                          (31)
#define DMA_CSR_RUN_Msk                          (0x1UL << DMA_CSR_RUN_Pos)
/** @} */

/** @name ACR - DMA_ACR N register */
/** @{ */
#define DMA_ACR_ALIGN_Pos                        (0)
#define DMA_ACR_ALIGN_Msk                        (0x1UL << DMA_ACR_ALIGN_Pos)
/** @} */

/** @name CHIIR - DMA_CHIIR register */
/** @{ */
#define DMA_CHIIR_CH0IRQ_Pos                     (0)
#define DMA_CHIIR_CH0IRQ_Msk                     (0x1UL << DMA_CHIIR_CH0IRQ_Pos)

#define DMA_CHIIR_CH1IRQ_Pos                     (1)
#define DMA_CHIIR_CH1IRQ_Msk                     (0x1UL << DMA_CHIIR_CH1IRQ_Pos)

#define DMA_CHIIR_CH2IRQ_Pos                     (2)
#define DMA_CHIIR_CH2IRQ_Msk                     (0x1UL << DMA_CHIIR_CH2IRQ_Pos)

#define DMA_CHIIR_CH3IRQ_Pos                     (3)
#define DMA_CHIIR_CH3IRQ_Msk                     (0x1UL << DMA_CHIIR_CH3IRQ_Pos)

#define DMA_CHIIR_CH4IRQ_Pos                     (4)
#define DMA_CHIIR_CH4IRQ_Msk                     (0x1UL << DMA_CHIIR_CH4IRQ_Pos)

#define DMA_CHIIR_CH5IRQ_Pos                     (5)
#define DMA_CHIIR_CH5IRQ_Msk                     (0x1UL << DMA_CHIIR_CH5IRQ_Pos)

#define DMA_CHIIR_CH6IRQ_Pos                     (6)
#define DMA_CHIIR_CH6IRQ_Msk                     (0x1UL << DMA_CHIIR_CH6IRQ_Pos)

#define DMA_CHIIR_CH7IRQ_Pos                     (7)
#define DMA_CHIIR_CH7IRQ_Msk                     (0x1UL << DMA_CHIIR_CH7IRQ_Pos)

#define DMA_CHIIR_CH8IRQ_Pos                     (8)
#define DMA_CHIIR_CH8IRQ_Msk                     (0x1UL << DMA_CHIIR_CH8IRQ_Pos)

#define DMA_CHIIR_CH9IRQ_Pos                     (9)
#define DMA_CHIIR_CH9IRQ_Msk                     (0x1UL << DMA_CHIIR_CH9IRQ_Pos)

#define DMA_CHIIR_CH10IRQ_Pos                    (10)
#define DMA_CHIIR_CH10IRQ_Msk                    (0x1UL << DMA_CHIIR_CH10IRQ_Pos)

#define DMA_CHIIR_CH11IRQ_Pos                    (11)
#define DMA_CHIIR_CH11IRQ_Msk                    (0x1UL << DMA_CHIIR_CH11IRQ_Pos)

#define DMA_CHIIR_CH12IRQ_Pos                    (12)
#define DMA_CHIIR_CH12IRQ_Msk                    (0x1UL << DMA_CHIIR_CH12IRQ_Pos)

#define DMA_CHIIR_CH13IRQ_Pos                    (13)
#define DMA_CHIIR_CH13IRQ_Msk                    (0x1UL << DMA_CHIIR_CH13IRQ_Pos)

#define DMA_CHIIR_CH14IRQ_Pos                    (14)
#define DMA_CHIIR_CH14IRQ_Msk                    (0x1UL << DMA_CHIIR_CH14IRQ_Pos)

#define DMA_CHIIR_CH15IRQ_Pos                    (15)
#define DMA_CHIIR_CH15IRQ_Msk                    (0x1UL << DMA_CHIIR_CH15IRQ_Pos)
/** @} */

/** @name RCMR - DMA_RCMR N register */
/** @{ */
#define DMA_RCMR_CHIDX_Pos                       (0)
#define DMA_RCMR_CHIDX_Msk                       (0xFUL << DMA_RCMR_CHIDX_Pos)

#define DMA_RCMR_MAPVLD_Pos                      (7)
#define DMA_RCMR_MAPVLD_Msk                      (0x1UL << DMA_RCMR_MAPVLD_Pos)
/** @} */

/** @name DAR - DMA_DAR N register */
/** @{ */
#define DMA_DAR_STOP_Pos                         (0)
#define DMA_DAR_STOP_Msk                         (0x1UL << DMA_DAR_STOP_Pos)

#define DMA_DAR_ADDR_Pos                         (4)
#define DMA_DAR_ADDR_Msk                         (0xFFFFFFFUL << DMA_DAR_ADDR_Pos)
/** @} */

/** @name SAR - DMA_SAR N register */
/** @{ */
#define DMA_SAR_ADDR_Pos                         (0)
#define DMA_SAR_ADDR_Msk                         (0xFFFFFFFFUL << DMA_SAR_ADDR_Pos)
/** @} */

/** @name TAR - DMA_TAR N register */
/** @{ */
#define DMA_TAR_ADDR_Pos                         (0)
#define DMA_TAR_ADDR_Msk                         (0xFFFFFFFFUL << DMA_TAR_ADDR_Pos)
/** @} */

/** @name CMDR - DMA_CMDR N register */
/** @{ */
#define DMA_CMDR_LEN_Pos                         (0)
#define DMA_CMDR_LEN_Msk                         (0x1FFFUL << DMA_CMDR_LEN_Pos)

#define DMA_CMDR_OVRD_Pos                        (13)
#define DMA_CMDR_OVRD_Msk                        (0x1UL << DMA_CMDR_OVRD_Pos)

#define DMA_CMDR_WIDTH_Pos                       (14)
#define DMA_CMDR_WIDTH_Msk                       (0x3UL << DMA_CMDR_WIDTH_Pos)

#define DMA_CMDR_SIZE_Pos                        (16)
#define DMA_CMDR_SIZE_Msk                        (0x7UL << DMA_CMDR_SIZE_Pos)

#define DMA_CMDR_ENDIRQEN_Pos                    (21)
#define DMA_CMDR_ENDIRQEN_Msk                    (0x1UL << DMA_CMDR_ENDIRQEN_Pos)

#define DMA_CMDR_STARTIRQEN_Pos                  (22)
#define DMA_CMDR_STARTIRQEN_Msk                  (0x1UL << DMA_CMDR_STARTIRQEN_Pos)

#define DMA_CMDR_TRGFLOWCTR_Pos                  (28)
#define DMA_CMDR_TRGFLOWCTR_Msk                  (0x1UL << DMA_CMDR_TRGFLOWCTR_Pos)

#define DMA_CMDR_SRCFLOWCTR_Pos                  (29)
#define DMA_CMDR_SRCFLOWCTR_Msk                  (0x1UL << DMA_CMDR_SRCFLOWCTR_Pos)

#define DMA_CMDR_TRGADDRINC_Pos                  (30)
#define DMA_CMDR_TRGADDRINC_Msk                  (0x1UL << DMA_CMDR_TRGADDRINC_Pos)

#define DMA_CMDR_SRCADDRINC_Pos                  (31)
#define DMA_CMDR_SRCADDRINC_Msk                  (0x1UL << DMA_CMDR_SRCADDRINC_Pos)
/** @} */

/** Peripheral DMA base pointer */
#define DMA                                      ((DMA_TypeDef *) DMA_HW_BASE_ADDR)

/**
  * @}
  */ /* end of group DMA */


/** @addtogroup GPR GPR
  * @{
  */

/**
  * @brief GPR register layout typedef
  *
  */
typedef struct {
         uint32_t RESERVED_0;
    __IO uint32_t LOCKUPCTRL;                    /**< Lockup Control Register,                      offset: 0x4 */
    __IO uint32_t CACHEBYPASS;                   /**< Cache Bypass Control Register,                offset: 0x8 */
         uint32_t RESERVED_1;
    __IO uint32_t CLKEN0;                        /**< Clock Enable Register 0,                      offset: 0x10 */
    __IO uint32_t CLKEN1;                        /**< Clock Enable Register 1,                      offset: 0x14 */
    __IO uint32_t CLKSEL;                        /**< Clock Source Select Register,                 offset: 0x18 */
    __IO uint32_t CLKDIV0;                       /**< Clock Divide Register 0,                      offset: 0x1C */
    __IO uint32_t CLKDIV1;                       /**< Clock Divide Register 1,                      offset: 0x20 */
    __IO uint32_t CLKDIV2;                       /**< Clock Divide Register 2,                      offset: 0x24 */
    __IO uint32_t CLKDIV3;                       /**< Clock Divide Register 3,                      offset: 0x28 */
    __IO uint32_t SWRSTCTRL0;                    /**< SW Reset Control Reister 0,                   offset: 0x2C */
    __IO uint32_t SWRSTCTRL1;                    /**< SW Reset Control Reister 1,                   offset: 0x30 */
         uint32_t RESERVED_2[6];
    __IO uint32_t PDMAACG;                       /**< DMA Auto Clock Gate Control Reister,          offset: 0x4C */
    __IO uint32_t RXEVEN;                        /**< RXEV Enable Reister,                          offset: 0x50 */
    __IO uint32_t MEMCTRL;                       /**< Memory Control Reister,                       offset: 0x54 */
    __IO uint32_t TESTPIN;                       /**< Test Pin Control Reister,                     offset: 0x58 */
    __I  uint32_t CHIPID;                        /**< Chip ID Reister,                              offset: 0x5C */
    __IO uint32_t SPIS;                          /**< SPIS Control Reister,                         offset: 0x60 */
         uint32_t RESERVED_3;
    __IO uint32_t EFUSE;                         /**< EFUSE Control Reister,                        offset: 0x68 */
         uint32_t RESERVED_4;
    __IO uint32_t CLKCALCTRL;                    /**< Clock Cal Control Reister,                    offset: 0x70 */
    __IO uint32_t CLKCALFC;                      /**< Clock Cal FC Reister,                         offset: 0x74 */
    __IO uint32_t CLKCALSC;                      /**< Clock Cal SC Reister,                         offset: 0x78 */
} GPR_TypeDef;

/** @name LOCKUPCTRL - GPR_LOCKUPCTRL register */
/** @{ */
#define GPR_LOCKUPCTRL_RST_EN_Pos                (0)
#define GPR_LOCKUPCTRL_RST_EN_Msk                (0x1UL << GPR_LOCKUPCTRL_RST_EN_Pos)
/** @} */

/** @name CACHEBYPASS - GPR_CACHEBYPASS register */
/** @{ */
#define GPR_CACHEBYPASS_EN_Pos                   (0)
#define GPR_CACHEBYPASS_EN_Msk                   (0x1UL << GPR_CACHEBYPASS_EN_Pos)
/** @} */

/** @name CLKEN0 - GPR_CLKEN0 register */
/** @{ */
#define GPR_CLKEN0_ALL_CLK_Pos                   (0)
#define GPR_CLKEN0_ALL_CLK_Msk                   (0x1UL << GPR_CLKEN0_ALL_CLK_Pos)

#define GPR_CLKEN0_RC_CLK_Pos                    (1)
#define GPR_CLKEN0_RC_CLK_Msk                    (0x1UL << GPR_CLKEN0_RC_CLK_Pos)

#define GPR_CLKEN0_CLK_204M_Pos                  (2)
#define GPR_CLKEN0_CLK_204M_Msk                  (0x1UL << GPR_CLKEN0_CLK_204M_Pos)

#define GPR_CLKEN0_CLK_102M_Pos                  (3)
#define GPR_CLKEN0_CLK_102M_Msk                  (0x1UL << GPR_CLKEN0_CLK_102M_Pos)

#define GPR_CLKEN0_CLK_51M_Pos                   (4)
#define GPR_CLKEN0_CLK_51M_Msk                   (0x1UL << GPR_CLKEN0_CLK_51M_Pos)

#define GPR_CLKEN0_DAP_CLK_Pos                   (5)
#define GPR_CLKEN0_DAP_CLK_Msk                   (0x1UL << GPR_CLKEN0_DAP_CLK_Pos)

#define GPR_CLKEN0_SPIS_CLK_Pos                  (6)
#define GPR_CLKEN0_SPIS_CLK_Msk                  (0x1UL << GPR_CLKEN0_SPIS_CLK_Pos)

#define GPR_CLKEN0_CLKCAL_CLK_Pos                (7)
#define GPR_CLKEN0_CLKCAL_CLK_Msk                (0x1UL << GPR_CLKEN0_CLKCAL_CLK_Pos)

#define GPR_CLKEN0_AON_CLK_Pos                   (8)
#define GPR_CLKEN0_AON_CLK_Msk                   (0x1UL << GPR_CLKEN0_AON_CLK_Pos)

#define GPR_CLKEN0_PMDIG_CLK_Pos                 (9)
#define GPR_CLKEN0_PMDIG_CLK_Msk                 (0x1UL << GPR_CLKEN0_PMDIG_CLK_Pos)

#define GPR_CLKEN0_RFDIG_CLK_Pos                 (10)
#define GPR_CLKEN0_RFDIG_CLK_Msk                 (0x1UL << GPR_CLKEN0_RFDIG_CLK_Pos)

#define GPR_CLKEN0_GPIO_0_PCLK_Pos               (11)
#define GPR_CLKEN0_GPIO_0_PCLK_Msk               (0x1UL << GPR_CLKEN0_GPIO_0_PCLK_Pos)

#define GPR_CLKEN0_GPIO_1_PCLK_Pos               (12)
#define GPR_CLKEN0_GPIO_1_PCLK_Msk               (0x1UL << GPR_CLKEN0_GPIO_1_PCLK_Pos)

#define GPR_CLKEN0_GPIO_PCLK_Pos                 (13)
#define GPR_CLKEN0_GPIO_PCLK_Msk                 (0x1UL << GPR_CLKEN0_GPIO_PCLK_Pos)

#define GPR_CLKEN0_I2C0_CLK_Pos                  (14)
#define GPR_CLKEN0_I2C0_CLK_Msk                  (0x1UL << GPR_CLKEN0_I2C0_CLK_Pos)

#define GPR_CLKEN0_I2C1_CLK_Pos                  (15)
#define GPR_CLKEN0_I2C1_CLK_Msk                  (0x1UL << GPR_CLKEN0_I2C1_CLK_Pos)

#define GPR_CLKEN0_I2C0_PCLK_Pos                 (16)
#define GPR_CLKEN0_I2C0_PCLK_Msk                 (0x1UL << GPR_CLKEN0_I2C0_PCLK_Pos)

#define GPR_CLKEN0_I2C1_PCLK_Pos                 (17)
#define GPR_CLKEN0_I2C1_PCLK_Msk                 (0x1UL << GPR_CLKEN0_I2C1_PCLK_Pos)

#define GPR_CLKEN0_PAD_PCLK_Pos                  (18)
#define GPR_CLKEN0_PAD_PCLK_Msk                  (0x1UL << GPR_CLKEN0_PAD_PCLK_Pos)

#define GPR_CLKEN0_RFFE_CLK_Pos                  (19)
#define GPR_CLKEN0_RFFE_CLK_Msk                  (0x1UL << GPR_CLKEN0_RFFE_CLK_Pos)

#define GPR_CLKEN0_RFFE_PCLK_Pos                 (20)
#define GPR_CLKEN0_RFFE_PCLK_Msk                 (0x1UL << GPR_CLKEN0_RFFE_PCLK_Pos)

#define GPR_CLKEN0_SPI0_CLK_Pos                  (21)
#define GPR_CLKEN0_SPI0_CLK_Msk                  (0x1UL << GPR_CLKEN0_SPI0_CLK_Pos)

#define GPR_CLKEN0_SPI1_CLK_Pos                  (22)
#define GPR_CLKEN0_SPI1_CLK_Msk                  (0x1UL << GPR_CLKEN0_SPI1_CLK_Pos)

#define GPR_CLKEN0_SPI0_PCLK_Pos                 (23)
#define GPR_CLKEN0_SPI0_PCLK_Msk                 (0x1UL << GPR_CLKEN0_SPI0_PCLK_Pos)

#define GPR_CLKEN0_SPI1_PCLK_Pos                 (24)
#define GPR_CLKEN0_SPI1_PCLK_Msk                 (0x1UL << GPR_CLKEN0_SPI1_PCLK_Pos)

#define GPR_CLKEN0_UART0_CLK_Pos                 (25)
#define GPR_CLKEN0_UART0_CLK_Msk                 (0x1UL << GPR_CLKEN0_UART0_CLK_Pos)

#define GPR_CLKEN0_UART1_CLK_Pos                 (26)
#define GPR_CLKEN0_UART1_CLK_Msk                 (0x1UL << GPR_CLKEN0_UART1_CLK_Pos)

#define GPR_CLKEN0_UART2_CLK_Pos                 (27)
#define GPR_CLKEN0_UART2_CLK_Msk                 (0x1UL << GPR_CLKEN0_UART2_CLK_Pos)

#define GPR_CLKEN0_UART0_PCLK_Pos                (28)
#define GPR_CLKEN0_UART0_PCLK_Msk                (0x1UL << GPR_CLKEN0_UART0_PCLK_Pos)

#define GPR_CLKEN0_UART1_PCLK_Pos                (29)
#define GPR_CLKEN0_UART1_PCLK_Msk                (0x1UL << GPR_CLKEN0_UART1_PCLK_Pos)

#define GPR_CLKEN0_UART2_PCLK_Pos                (30)
#define GPR_CLKEN0_UART2_PCLK_Msk                (0x1UL << GPR_CLKEN0_UART2_PCLK_Pos)
/** @} */

/** @name CLKEN1 - GPR_CLKEN1 register */
/** @{ */
#define GPR_CLKEN1_TIMER0_CLK_Pos                (0)
#define GPR_CLKEN1_TIMER0_CLK_Msk                (0x1UL << GPR_CLKEN1_TIMER0_CLK_Pos)

#define GPR_CLKEN1_TIMER1_CLK_Pos                (1)
#define GPR_CLKEN1_TIMER1_CLK_Msk                (0x1UL << GPR_CLKEN1_TIMER1_CLK_Pos)

#define GPR_CLKEN1_TIMER2_CLK_Pos                (2)
#define GPR_CLKEN1_TIMER2_CLK_Msk                (0x1UL << GPR_CLKEN1_TIMER2_CLK_Pos)

#define GPR_CLKEN1_TIMER3_CLK_Pos                (3)
#define GPR_CLKEN1_TIMER3_CLK_Msk                (0x1UL << GPR_CLKEN1_TIMER3_CLK_Pos)

#define GPR_CLKEN1_TIMER4_CLK_Pos                (4)
#define GPR_CLKEN1_TIMER4_CLK_Msk                (0x1UL << GPR_CLKEN1_TIMER4_CLK_Pos)

#define GPR_CLKEN1_TIMER5_CLK_Pos                (5)
#define GPR_CLKEN1_TIMER5_CLK_Msk                (0x1UL << GPR_CLKEN1_TIMER5_CLK_Pos)

#define GPR_CLKEN1_SYSTICK_CLK_Pos               (6)
#define GPR_CLKEN1_SYSTICK_CLK_Msk               (0x1UL << GPR_CLKEN1_SYSTICK_CLK_Pos)

#define GPR_CLKEN1_TIMER0_PCLK_Pos               (8)
#define GPR_CLKEN1_TIMER0_PCLK_Msk               (0x1UL << GPR_CLKEN1_TIMER0_PCLK_Pos)

#define GPR_CLKEN1_TIMER1_PCLK_Pos               (9)
#define GPR_CLKEN1_TIMER1_PCLK_Msk               (0x1UL << GPR_CLKEN1_TIMER1_PCLK_Pos)

#define GPR_CLKEN1_TIMER2_PCLK_Pos               (10)
#define GPR_CLKEN1_TIMER2_PCLK_Msk               (0x1UL << GPR_CLKEN1_TIMER2_PCLK_Pos)

#define GPR_CLKEN1_TIMER3_PCLK_Pos               (11)
#define GPR_CLKEN1_TIMER3_PCLK_Msk               (0x1UL << GPR_CLKEN1_TIMER3_PCLK_Pos)

#define GPR_CLKEN1_TIMER4_PCLK_Pos               (12)
#define GPR_CLKEN1_TIMER4_PCLK_Msk               (0x1UL << GPR_CLKEN1_TIMER4_PCLK_Pos)

#define GPR_CLKEN1_TIMER5_PCLK_Pos               (13)
#define GPR_CLKEN1_TIMER5_PCLK_Msk               (0x1UL << GPR_CLKEN1_TIMER5_PCLK_Pos)

#define GPR_CLKEN1_WDG_CLK_Pos                   (14)
#define GPR_CLKEN1_WDG_CLK_Msk                   (0x1UL << GPR_CLKEN1_WDG_CLK_Pos)

#define GPR_CLKEN1_WDG_PCLK__Pos                 (15)
#define GPR_CLKEN1_WDG_PCLK__Msk                 (0x1UL << GPR_CLKEN1_WDG_PCLK__Pos)

#define GPR_CLKEN1_USIM_CLK_Pos                  (16)
#define GPR_CLKEN1_USIM_CLK_Msk                  (0x1UL << GPR_CLKEN1_USIM_CLK_Pos)

#define GPR_CLKEN1_USIM_PCLK_Pos                 (17)
#define GPR_CLKEN1_USIM_PCLK_Msk                 (0x1UL << GPR_CLKEN1_USIM_PCLK_Pos)

#define GPR_CLKEN1_EFUSE_PCLK_Pos                (18)
#define GPR_CLKEN1_EFUSE_PCLK_Msk                (0x1UL << GPR_CLKEN1_EFUSE_PCLK_Pos)

#define GPR_CLKEN1_TRNG_PCLK_Pos                 (19)
#define GPR_CLKEN1_TRNG_PCLK_Msk                 (0x1UL << GPR_CLKEN1_TRNG_PCLK_Pos)

#define GPR_CLKEN1_BB_RX_CLK_Pos                 (24)
#define GPR_CLKEN1_BB_RX_CLK_Msk                 (0x1UL << GPR_CLKEN1_BB_RX_CLK_Pos)

#define GPR_CLKEN1_BB_TX_CLK_Pos                 (25)
#define GPR_CLKEN1_BB_TX_CLK_Msk                 (0x1UL << GPR_CLKEN1_BB_TX_CLK_Pos)

#define GPR_CLKEN1_SEQ_CLK_Pos                   (26)
#define GPR_CLKEN1_SEQ_CLK_Msk                   (0x1UL << GPR_CLKEN1_SEQ_CLK_Pos)

#define GPR_CLKEN1_BCNT_CLK_Pos                  (27)
#define GPR_CLKEN1_BCNT_CLK_Msk                  (0x1UL << GPR_CLKEN1_BCNT_CLK_Pos)
/** @} */

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

/** @name CLKDIV0 - GPR_CLKDIV0 register */
/** @{ */
#define GPR_CLKDIV0_FLASH_CLK_Pos                (4)
#define GPR_CLKDIV0_FLASH_CLK_Msk                (0x3UL << GPR_CLKDIV0_FLASH_CLK_Pos)

#define GPR_CLKDIV0_WDG_CLK_Pos                  (8)
#define GPR_CLKDIV0_WDG_CLK_Msk                  (0xFFUL << GPR_CLKDIV0_WDG_CLK_Pos)

#define GPR_CLKDIV0_TIMER0_CLK_Pos               (16)
#define GPR_CLKDIV0_TIMER0_CLK_Msk               (0xFFUL << GPR_CLKDIV0_TIMER0_CLK_Pos)

#define GPR_CLKDIV0_TIMER1_CLK_Pos               (24)
#define GPR_CLKDIV0_TIMER1_CLK_Msk               (0xFFUL << GPR_CLKDIV0_TIMER1_CLK_Pos)
/** @} */

/** @name CLKDIV1 - GPR_CLKDIV1 register */
/** @{ */
#define GPR_CLKDIV1_TIMER2_CLK_Pos               (0)
#define GPR_CLKDIV1_TIMER2_CLK_Msk               (0xFFUL << GPR_CLKDIV1_TIMER2_CLK_Pos)

#define GPR_CLKDIV1_TIMER3_CLK_Pos               (8)
#define GPR_CLKDIV1_TIMER3_CLK_Msk               (0xFFUL << GPR_CLKDIV1_TIMER3_CLK_Pos)

#define GPR_CLKDIV1_TIMER4_CLK_Pos               (16)
#define GPR_CLKDIV1_TIMER4_CLK_Msk               (0xFFUL << GPR_CLKDIV1_TIMER4_CLK_Pos)

#define GPR_CLKDIV1_TIMER5_CLK_Pos               (24)
#define GPR_CLKDIV1_TIMER5_CLK_Msk               (0xFFUL << GPR_CLKDIV1_TIMER5_CLK_Pos)
/** @} */

/** @name CLKDIV2 - GPR_CLKDIV2 register */
/** @{ */
#define GPR_CLKDIV2_SYSTICK_CLK_Pos              (0)
#define GPR_CLKDIV2_SYSTICK_CLK_Msk              (0xFFUL << GPR_CLKDIV2_SYSTICK_CLK_Pos)

#define GPR_CLKDIV2_I2C0_CLK_Pos                 (8)
#define GPR_CLKDIV2_I2C0_CLK_Msk                 (0x3UL << GPR_CLKDIV2_I2C0_CLK_Pos)

#define GPR_CLKDIV2_I2C1_CLK_Pos                 (10)
#define GPR_CLKDIV2_I2C1_CLK_Msk                 (0x3UL << GPR_CLKDIV2_I2C1_CLK_Pos)

#define GPR_CLKDIV2_RFFE_CLK_Pos                 (14)
#define GPR_CLKDIV2_RFFE_CLK_Msk                 (0x3UL << GPR_CLKDIV2_RFFE_CLK_Pos)

#define GPR_CLKDIV2_SPI0_CLK_Pos                 (16)
#define GPR_CLKDIV2_SPI0_CLK_Msk                 (0x3UL << GPR_CLKDIV2_SPI0_CLK_Pos)

#define GPR_CLKDIV2_SPI1_CLK_Pos                 (18)
#define GPR_CLKDIV2_SPI1_CLK_Msk                 (0x3UL << GPR_CLKDIV2_SPI1_CLK_Pos)

#define GPR_CLKDIV2_UART0_CLK_Pos                (20)
#define GPR_CLKDIV2_UART0_CLK_Msk                (0xFUL << GPR_CLKDIV2_UART0_CLK_Pos)

#define GPR_CLKDIV2_UART1_CLK_Pos                (24)
#define GPR_CLKDIV2_UART1_CLK_Msk                (0xFUL << GPR_CLKDIV2_UART1_CLK_Pos)

#define GPR_CLKDIV2_UART2_CLK_Pos                (28)
#define GPR_CLKDIV2_UART2_CLK_Msk                (0xFUL << GPR_CLKDIV2_UART2_CLK_Pos)
/** @} */

/** @name CLKDIV3 - GPR_CLKDIV3 register */
/** @{ */
#define GPR_CLKDIV3_AON_CLK_Pos                  (0)
#define GPR_CLKDIV3_AON_CLK_Msk                  (0x7FFUL << GPR_CLKDIV3_AON_CLK_Pos)
/** @} */

/** @name SWRST0 - GPR_SWRST0 register */
/** @{ */
#define GPR_SWRST0_CACHE_Pos                     (0)
#define GPR_SWRST0_CACHE_Msk                     (0x1UL << GPR_SWRST0_CACHE_Pos)

#define GPR_SWRST0_SSFAB_Pos                     (1)
#define GPR_SWRST0_SSFAB_Msk                     (0x1UL << GPR_SWRST0_SSFAB_Pos)

#define GPR_SWRST0_RMI_Pos                       (2)
#define GPR_SWRST0_RMI_Msk                       (0x1UL << GPR_SWRST0_RMI_Pos)

#define GPR_SWRST0_RMI_MODEM_LOGIC_Pos           (3)
#define GPR_SWRST0_RMI_MODEM_LOGIC_Msk           (0x1UL << GPR_SWRST0_RMI_MODEM_LOGIC_Pos)

#define GPR_SWRST0_RMI_SEQ_LOGIC_Pos             (4)
#define GPR_SWRST0_RMI_SEQ_LOGIC_Msk             (0x1UL << GPR_SWRST0_RMI_SEQ_LOGIC_Pos)

#define GPR_SWRST0_RMI_IC_LOGIC_Pos              (5)
#define GPR_SWRST0_RMI_IC_LOGIC_Msk              (0x1UL << GPR_SWRST0_RMI_IC_LOGIC_Pos)

#define GPR_SWRST0_RMI_CIPHER_LOGIC_Pos          (6)
#define GPR_SWRST0_RMI_CIPHER_LOGIC_Msk          (0x1UL << GPR_SWRST0_RMI_CIPHER_LOGIC_Pos)

#define GPR_SWRST0_HCLK_CIPHER_LOGIC_Pos         (7)
#define GPR_SWRST0_HCLK_CIPHER_LOGIC_Msk         (0x1UL << GPR_SWRST0_HCLK_CIPHER_LOGIC_Pos)

#define GPR_SWRST0_MFAB_Pos                      (8)
#define GPR_SWRST0_MFAB_Msk                      (0x1UL << GPR_SWRST0_MFAB_Pos)

#define GPR_SWRST0_SMB_Pos                       (9)
#define GPR_SWRST0_SMB_Msk                       (0x1UL << GPR_SWRST0_SMB_Pos)

#define GPR_SWRST0_UNILOG_Pos                    (10)
#define GPR_SWRST0_UNILOG_Msk                    (0x1UL << GPR_SWRST0_UNILOG_Pos)

#define GPR_SWRST0_FLASH_FUNC_LOGIC_Pos          (11)
#define GPR_SWRST0_FLASH_FUNC_LOGIC_Msk          (0x1UL << GPR_SWRST0_FLASH_FUNC_LOGIC_Pos)

#define GPR_SWRST0_FLASH_HCLK_LOGIC_Pos          (12)
#define GPR_SWRST0_FLASH_HCLK_LOGIC_Msk          (0x1UL << GPR_SWRST0_FLASH_HCLK_LOGIC_Pos)

#define GPR_SWRST0_CLKCAL_CLK_LOGIC_Pos          (13)
#define GPR_SWRST0_CLKCAL_CLK_LOGIC_Msk          (0x1UL << GPR_SWRST0_CLKCAL_CLK_LOGIC_Pos)

#define GPR_SWRST0_AON_PCLK_LOGIC_Pos            (14)
#define GPR_SWRST0_AON_PCLK_LOGIC_Msk            (0x1UL << GPR_SWRST0_AON_PCLK_LOGIC_Pos)

#define GPR_SWRST0_PMDIG_PCLK_LOGIC_Pos          (15)
#define GPR_SWRST0_PMDIG_PCLK_LOGIC_Msk          (0x1UL << GPR_SWRST0_PMDIG_PCLK_LOGIC_Pos)

#define GPR_SWRST0_RFDIG_PCLK_LOGIC_Pos          (16)
#define GPR_SWRST0_RFDIG_PCLK_LOGIC_Msk          (0x1UL << GPR_SWRST0_RFDIG_PCLK_LOGIC_Pos)

#define GPR_SWRST0_GPIO_Pos                      (17)
#define GPR_SWRST0_GPIO_Msk                      (0x1UL << GPR_SWRST0_GPIO_Pos)

#define GPR_SWRST0_I2C0_FUNC_LOGIC_Pos           (18)
#define GPR_SWRST0_I2C0_FUNC_LOGIC_Msk           (0x1UL << GPR_SWRST0_I2C0_FUNC_LOGIC_Pos)

#define GPR_SWRST0_I2C1_FUNC_LOGIC_Pos           (19)
#define GPR_SWRST0_I2C1_FUNC_LOGIC_Msk           (0x1UL << GPR_SWRST0_I2C1_FUNC_LOGIC_Pos)

#define GPR_SWRST0_I2C0_PCLK_LOGIC_Pos           (20)
#define GPR_SWRST0_I2C0_PCLK_LOGIC_Msk           (0x1UL << GPR_SWRST0_I2C0_PCLK_LOGIC_Pos)

#define GPR_SWRST0_I2C1_PCLK_LOGIC_Pos           (21)
#define GPR_SWRST0_I2C1_PCLK_LOGIC_Msk           (0x1UL << GPR_SWRST0_I2C1_PCLK_LOGIC_Pos)

#define GPR_SWRST0_PAD_Pos                       (22)
#define GPR_SWRST0_PAD_Msk                       (0x1UL << GPR_SWRST0_PAD_Pos)

#define GPR_SWRST0_RFFE_FUNC_LOGIC_Pos           (23)
#define GPR_SWRST0_RFFE_FUNC_LOGIC_Msk           (0x1UL << GPR_SWRST0_RFFE_FUNC_LOGIC_Pos)

#define GPR_SWRST0_RFFE_PCLK_LOGIC_Pos           (24)
#define GPR_SWRST0_RFFE_PCLK_LOGIC_Msk           (0x1UL << GPR_SWRST0_RFFE_PCLK_LOGIC_Pos)

#define GPR_SWRST0_SPI0_FUNC_LOGIC_Pos           (25)
#define GPR_SWRST0_SPI0_FUNC_LOGIC_Msk           (0x1UL << GPR_SWRST0_SPI0_FUNC_LOGIC_Pos)

#define GPR_SWRST0_SPI1_FUNC_LOGIC_Pos           (26)
#define GPR_SWRST0_SPI1_FUNC_LOGIC_Msk           (0x1UL << GPR_SWRST0_SPI1_FUNC_LOGIC_Pos)

#define GPR_SWRST0_SPI0_PCLK_LOGIC_Pos           (27)
#define GPR_SWRST0_SPI0_PCLK_LOGIC_Msk           (0x1UL << GPR_SWRST0_SPI0_PCLK_LOGIC_Pos)

#define GPR_SWRST0_SPI1_PCLK_LOGIC_Pos           (28)
#define GPR_SWRST0_SPI1_PCLK_LOGIC_Msk           (0x1UL << GPR_SWRST0_SPI1_PCLK_LOGIC_Pos)

#define GPR_SWRST0_UART0_FUNC_LOGIC_Pos          (29)
#define GPR_SWRST0_UART0_FUNC_LOGIC_Msk          (0x1UL << GPR_SWRST0_UART0_FUNC_LOGIC_Pos)

#define GPR_SWRST0_UART1_FUNC_LOGIC_Pos          (30)
#define GPR_SWRST0_UART1_FUNC_LOGIC_Msk          (0x1UL << GPR_SWRST0_UART1_FUNC_LOGIC_Pos)

#define GPR_SWRST0_UART2_FUNC_LOGIC_Pos          (31)
#define GPR_SWRST0_UART2_FUNC_LOGIC_Msk          (0x1UL << GPR_SWRST0_UART2_FUNC_LOGIC_Pos)
/** @} */

/** @name SWRST1 - GPR_SWRST1 register */
/** @{ */
#define GPR_SWRST1_UART0_PCLK_LOGIC_Pos          (0)
#define GPR_SWRST1_UART0_PCLK_LOGIC_Msk          (0x1UL << GPR_SWRST1_UART0_PCLK_LOGIC_Pos)

#define GPR_SWRST1_UART1_PCLK_LOGIC_Pos          (1)
#define GPR_SWRST1_UART1_PCLK_LOGIC_Msk          (0x1UL << GPR_SWRST1_UART1_PCLK_LOGIC_Pos)

#define GPR_SWRST1_UART2_PCLK_LOGIC_Pos          (2)
#define GPR_SWRST1_UART2_PCLK_LOGIC_Msk          (0x1UL << GPR_SWRST1_UART2_PCLK_LOGIC_Pos)

#define GPR_SWRST1_TIMER0_FUNC_LOGIC_Pos         (3)
#define GPR_SWRST1_TIMER0_FUNC_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER0_FUNC_LOGIC_Pos)

#define GPR_SWRST1_TIMER1_FUNC_LOGIC_Pos         (4)
#define GPR_SWRST1_TIMER1_FUNC_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER1_FUNC_LOGIC_Pos)

#define GPR_SWRST1_TIMER2_FUNC_LOGIC_Pos         (5)
#define GPR_SWRST1_TIMER2_FUNC_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER2_FUNC_LOGIC_Pos)

#define GPR_SWRST1_TIMER3_FUNC_LOGIC_Pos         (6)
#define GPR_SWRST1_TIMER3_FUNC_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER3_FUNC_LOGIC_Pos)

#define GPR_SWRST1_TIMER4_FUNC_LOGIC_Pos         (7)
#define GPR_SWRST1_TIMER4_FUNC_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER4_FUNC_LOGIC_Pos)

#define GPR_SWRST1_TIMER5_FUNC_LOGIC_Pos         (8)
#define GPR_SWRST1_TIMER5_FUNC_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER5_FUNC_LOGIC_Pos)

#define GPR_SWRST1_TIMER0_PCLK_LOGIC_Pos         (9)
#define GPR_SWRST1_TIMER0_PCLK_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER0_PCLK_LOGIC_Pos)

#define GPR_SWRST1_TIMER1_PCLK_LOGIC_Pos         (10)
#define GPR_SWRST1_TIMER1_PCLK_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER1_PCLK_LOGIC_Pos)

#define GPR_SWRST1_TIMER2_PCLK_LOGIC_Pos         (11)
#define GPR_SWRST1_TIMER2_PCLK_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER2_PCLK_LOGIC_Pos)

#define GPR_SWRST1_TIMER3_PCLK_LOGIC_Pos         (12)
#define GPR_SWRST1_TIMER3_PCLK_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER3_PCLK_LOGIC_Pos)

#define GPR_SWRST1_TIMER4_PCLK_LOGIC_Pos         (13)
#define GPR_SWRST1_TIMER4_PCLK_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER4_PCLK_LOGIC_Pos)

#define GPR_SWRST1_TIMER5_PCLK_LOGIC_Pos         (14)
#define GPR_SWRST1_TIMER5_PCLK_LOGIC_Msk         (0x1UL << GPR_SWRST1_TIMER5_PCLK_LOGIC_Pos)

#define GPR_SWRST1_WDG_FUNC_LOGIC_Pos            (15)
#define GPR_SWRST1_WDG_FUNC_LOGIC_Msk            (0x1UL << GPR_SWRST1_WDG_FUNC_LOGIC_Pos)

#define GPR_SWRST1_WDG_PCLK_LOGIC_Pos            (16)
#define GPR_SWRST1_WDG_PCLK_LOGIC_Msk            (0x1UL << GPR_SWRST1_WDG_PCLK_LOGIC_Pos)

#define GPR_SWRST1_USIM_FUNC_LOGIC_Pos           (17)
#define GPR_SWRST1_USIM_FUNC_LOGIC_Msk           (0x1UL << GPR_SWRST1_USIM_FUNC_LOGIC_Pos)

#define GPR_SWRST1_USIM_PCLK_LOGIC_Pos           (18)
#define GPR_SWRST1_USIM_PCLK_LOGIC_Msk           (0x1UL << GPR_SWRST1_USIM_PCLK_LOGIC_Pos)

#define GPR_SWRST1_EFUSE_FUNC_LOGIC_Pos          (19)
#define GPR_SWRST1_EFUSE_FUNC_LOGIC_Msk          (0x1UL << GPR_SWRST1_EFUSE_FUNC_LOGIC_Pos)

#define GPR_SWRST1_EFUSE_PCLK_LOGIC_Pos          (20)
#define GPR_SWRST1_EFUSE_PCLK_LOGIC_Msk          (0x1UL << GPR_SWRST1_EFUSE_PCLK_LOGIC_Pos)

#define GPR_SWRST1_TRNG_PCLK_LOGIC_Pos           (21)
#define GPR_SWRST1_TRNG_PCLK_LOGIC_Msk           (0x1UL << GPR_SWRST1_TRNG_PCLK_LOGIC_Pos)

#define GPR_SWRST1_BB_RX_Pos                     (23)
#define GPR_SWRST1_BB_RX_Msk                     (0x1UL << GPR_SWRST1_BB_RX_Pos)

#define GPR_SWRST1_BB_TX_Pos                     (24)
#define GPR_SWRST1_BB_TX_Msk                     (0x1UL << GPR_SWRST1_BB_TX_Pos)

#define GPR_SWRST1_BB_ADC_LOGIC_Pos              (25)
#define GPR_SWRST1_BB_ADC_LOGIC_Msk              (0x1UL << GPR_SWRST1_BB_ADC_LOGIC_Pos)

#define GPR_SWRST1_BB_DAC_LOGIC_Pos              (26)
#define GPR_SWRST1_BB_DAC_LOGIC_Msk              (0x1UL << GPR_SWRST1_BB_DAC_LOGIC_Pos)

#define GPR_SWRST1_BCNT_LOGIC_Pos                (27)
#define GPR_SWRST1_BCNT_LOGIC_Msk                (0x1UL << GPR_SWRST1_BCNT_LOGIC_Pos)

#define GPR_SWRST1_SEQ_Pos                       (28)
#define GPR_SWRST1_SEQ_Msk                       (0x1UL << GPR_SWRST1_SEQ_Pos)

#define GPR_SWRST1_BB_SEQ_Pos                    (29)
#define GPR_SWRST1_BB_SEQ_Msk                    (0x1UL << GPR_SWRST1_BB_SEQ_Pos)

#define GPR_SWRST1_RF_SEQ_Pos                    (30)
#define GPR_SWRST1_RF_SEQ_Msk                    (0x1UL << GPR_SWRST1_RF_SEQ_Pos)

#define GPR_SWRST1_SPIS_HCLK_LOGIC_Pos           (31)
#define GPR_SWRST1_SPIS_HCLK_LOGIC_Msk           (0x1UL << GPR_SWRST1_SPIS_HCLK_LOGIC_Pos)
/** @} */

/** @name PDMAACG - GPR_PDMAACG register */
/** @{ */
#define GPR_PDMAACG_PCLK_Pos                     (0)
#define GPR_PDMAACG_PCLK_Msk                     (0x1UL << GPR_PDMAACG_PCLK_Pos)

#define GPR_PDMAACG_HCLK_Pos                     (1)
#define GPR_PDMAACG_HCLK_Msk                     (0x1UL << GPR_PDMAACG_HCLK_Pos)

#define GPR_PDMAACG_SMB_Pos                      (2)
#define GPR_PDMAACG_SMB_Msk                      (0x1UL << GPR_PDMAACG_SMB_Pos)

#define GPR_PDMAACG_RFDIG_Pos                    (3)
#define GPR_PDMAACG_RFDIG_Msk                    (0x1UL << GPR_PDMAACG_RFDIG_Pos)

#define GPR_PDMAACG_PMDIG_Pos                    (4)
#define GPR_PDMAACG_PMDIG_Msk                    (0x1UL << GPR_PDMAACG_PMDIG_Pos)
/** @} */

/** @name RXEVEN - GPR_RXEVEN register */
/** @{ */
#define GPR_RXEVEN_EN_Pos                        (0)
#define GPR_RXEVEN_EN_Msk                        (0x1UL << GPR_RXEVEN_EN_Pos)
/** @} */

/** @name MEMCTRL - GPR_MEMCTRL register */
/** @{ */
#define GPR_MEMCTRL_RF1P_Pos                     (0)
#define GPR_MEMCTRL_RF1P_Msk                     (0x1FUL << GPR_MEMCTRL_RF1P_Pos)

#define GPR_MEMCTRL_RF2P_Pos                     (5)
#define GPR_MEMCTRL_RF2P_Msk                     (0x3FUL << GPR_MEMCTRL_RF2P_Pos)

#define GPR_MEMCTRL_SR1P_Pos                     (11)
#define GPR_MEMCTRL_SR1P_Msk                     (0x1FUL << GPR_MEMCTRL_SR1P_Pos)

#define GPR_MEMCTRL_SR2P_Pos                     (16)
#define GPR_MEMCTRL_SR2P_Msk                     (0x3FFUL << GPR_MEMCTRL_SR2P_Pos)

#define GPR_MEMCTRL_ROM_Pos                      (26)
#define GPR_MEMCTRL_ROM_Msk                      (0x7UL << GPR_MEMCTRL_ROM_Pos)
/** @} */

/** @name TESTPIN - GPR_TESTPIN register */
/** @{ */
#define GPR_TESTPIN_USIM_Pos                     (0)
#define GPR_TESTPIN_USIM_Msk                     (0x1UL << GPR_TESTPIN_USIM_Pos)

#define GPR_TESTPIN_CIPHER_Pos                   (1)
#define GPR_TESTPIN_CIPHER_Msk                   (0x1UL << GPR_TESTPIN_CIPHER_Pos)

#define GPR_TESTPIN_SEQ_Pos                      (2)
#define GPR_TESTPIN_SEQ_Msk                      (0x1UL << GPR_TESTPIN_SEQ_Pos)

#define GPR_TESTPIN_TX_Pos                       (3)
#define GPR_TESTPIN_TX_Msk                       (0x1UL << GPR_TESTPIN_TX_Pos)

#define GPR_TESTPIN_RXDFE_Pos                    (4)
#define GPR_TESTPIN_RXDFE_Msk                    (0x1UL << GPR_TESTPIN_RXDFE_Pos)

#define GPR_TESTPIN_ICS_Pos                      (5)
#define GPR_TESTPIN_ICS_Msk                      (0x1UL << GPR_TESTPIN_ICS_Pos)

#define GPR_TESTPIN_CE_Pos                       (6)
#define GPR_TESTPIN_CE_Msk                       (0x1UL << GPR_TESTPIN_CE_Pos)

#define GPR_TESTPIN_DE_Pos                       (7)
#define GPR_TESTPIN_DE_Msk                       (0x1UL << GPR_TESTPIN_DE_Pos)

#define GPR_TESTPIN_TP_SEL_Pos                   (28)
#define GPR_TESTPIN_TP_SEL_Msk                   (0x7UL << GPR_TESTPIN_TP_SEL_Pos)
/** @} */

/** @name CHIPID - GPR_CHIPID register */
/** @{ */
#define GPR_CHIPID_REVISION_ID_Pos               (0)
#define GPR_CHIPID_REVISION_ID_Msk               (0xFFUL << GPR_CHIPID_REVISION_ID_Pos)

#define GPR_CHIPID_CHIP_ID_Pos                   (8)
#define GPR_CHIPID_CHIP_ID_Msk                   (0xFFFFFFUL << GPR_CHIPID_CHIP_ID_Pos)
/** @} */

/** @name SPIS - GPR_SPIS register */
/** @{ */
#define GPR_SPIS_AHB_HSIZE_Pos                   (0)
#define GPR_SPIS_AHB_HSIZE_Msk                   (0x3UL << GPR_SPIS_AHB_HSIZE_Pos)

#define GPR_SPIS_ADDR_KEEP_Pos                   (2)
#define GPR_SPIS_ADDR_KEEP_Msk                   (0x1UL << GPR_SPIS_ADDR_KEEP_Pos)

#define GPR_SPIS_BIDIR_Pos                       (3)
#define GPR_SPIS_BIDIR_Msk                       (0x1UL << GPR_SPIS_BIDIR_Pos)

#define GPR_SPIS_NO_PREFETCH_Pos                 (4)
#define GPR_SPIS_NO_PREFETCH_Msk                 (0x1UL << GPR_SPIS_NO_PREFETCH_Pos)

#define GPR_SPIS_PA_CTRL_READ_Pos                (5)
#define GPR_SPIS_PA_CTRL_READ_Msk                (0x1UL << GPR_SPIS_PA_CTRL_READ_Pos)
/** @} */

/** @name EFUSE - GPR_EFUSE register */
/** @{ */
#define GPR_EFUSE_BURN_ANYCLK_Pos                (0)
#define GPR_EFUSE_BURN_ANYCLK_Msk                (0x1UL << GPR_EFUSE_BURN_ANYCLK_Pos)
/** @} */

/** @name CLKCALCTRL - GPR_CLKCALCTRL register */
/** @{ */
#define GPR_CLKCALCTRL_ENABLE_Pos                (0)
#define GPR_CLKCALCTRL_ENABLE_Msk                (0x1UL << GPR_CLKCALCTRL_ENABLE_Pos)
/** @} */

/** @name CLKCALFC - GPR_CLKCALFC register */
/** @{ */
#define GPR_CLKCALFC_CNT_Pos                     (0)
#define GPR_CLKCALFC_CNT_Msk                     (0xFFFFFFUL << GPR_CLKCALFC_CNT_Pos)
/** @} */

/** @name CLKCALSC - GPR_CLKCALSC register */
/** @{ */
#define GPR_CLKCALSC_CNT_Pos                     (0)
#define GPR_CLKCALSC_CNT_Msk                     (0x1FFFFFFFUL << GPR_CLKCALSC_CNT_Pos)
/** @} */

/** Peripheral GPR base pointer */
#define GPR                                      ((GPR_TypeDef *) GPR_BASE_ADDR)

/**
  * @}
  */ /* end of group GPR */

/** @addtogroup GPR_RMI GPR_RMI(clock en and reset module)
  * @{
  */

/**
  * @brief GPR_RMI register layout typedef
  *
  */
typedef struct {
    __IO uint32_t CLKEN;                         /**< Clock Enable Register,                      offset: 0x0 */
         uint32_t RESERVED_0;
    __IO uint32_t DCXO_TRIM_OVWRT_CTRL;          /**< DCXO Trim Overwrite Enable Register,        offset: 0x8 */
    __IO uint32_t DCXO_TRIM_OVWRT_VAL;           /**< DCXO Trim Overwrite Value Register,         offset: 0xC */
} GPRRMI_TypeDef;

/** @name CLKEN - GPRRMI_CLKEN register */
/** @{ */
#define GPRRMI_CLKEN_CLK_MF_EN_Pos               (0)
#define GPRRMI_CLKEN_CLK_MF_EN_Msk               (0x1UL << GPRRMI_CLKEN_CLK_MF_EN_Pos)

#define GPRRMI_CLKEN_PDMA_HCLK_EN_Pos            (1)
#define GPRRMI_CLKEN_PDMA_HCLK_EN_Msk            (0x1UL << GPRRMI_CLKEN_PDMA_HCLK_EN_Pos)

#define GPRRMI_CLKEN_PDMA_PCLK_EN_Pos            (2)
#define GPRRMI_CLKEN_PDMA_PCLK_EN_Msk            (0x1UL << GPRRMI_CLKEN_PDMA_PCLK_EN_Pos)

#define GPRRMI_CLKEN_GPR_PCLK_EN_Pos             (3)
#define GPRRMI_CLKEN_GPR_PCLK_EN_Msk             (0x1UL << GPRRMI_CLKEN_GPR_PCLK_EN_Pos)

#define GPRRMI_CLKEN_PDMA_HRST_Pos               (4)
#define GPRRMI_CLKEN_PDMA_HRST_Msk               (0x1UL << GPRRMI_CLKEN_PDMA_HRST_Pos)

#define GPRRMI_CLKEN_PDMA_PRST_Pos               (5)
#define GPRRMI_CLKEN_PDMA_PRST_Msk               (0x1UL << GPRRMI_CLKEN_PDMA_PRST_Pos)

#define GPRRMI_CLKEN_GPR_PRSTN_Pos               (6)
#define GPRRMI_CLKEN_GPR_PRSTN_Msk               (0x1UL << GPRRMI_CLKEN_GPR_PRSTN_Pos)

#define GPRRMI_CLKEN_PDMA_PCLK_SEL_Pos           (7)
#define GPRRMI_CLKEN_PDMA_PCLK_SEL_Msk           (0x1UL << GPRRMI_CLKEN_PDMA_PCLK_SEL_Pos)

#define GPRRMI_CLKEN_ETM_HCLK_EN_Pos             (16)
#define GPRRMI_CLKEN_ETM_HCLK_EN_Msk             (0x1UL << GPRRMI_CLKEN_ETM_HCLK_EN_Pos)

#define GPRRMI_CLKEN_ROMTABLE_HCLK_EN_Pos        (17)
#define GPRRMI_CLKEN_ROMTABLE_HCLK_EN_Msk        (0x1UL << GPRRMI_CLKEN_ROMTABLE_HCLK_EN_Pos)

#define GPRRMI_CLKEN_TPIU_HCLK_EN_Pos            (18)
#define GPRRMI_CLKEN_TPIU_HCLK_EN_Msk            (0x1UL << GPRRMI_CLKEN_TPIU_HCLK_EN_Pos)

#define GPRRMI_CLKEN_TRACE_ICLK_EN_Pos           (19)
#define GPRRMI_CLKEN_TRACE_ICLK_EN_Msk           (0x1UL << GPRRMI_CLKEN_TRACE_ICLK_EN_Pos)

#define GPRRMI_CLKEN_CACHE_HCLK_EN_Pos           (20)
#define GPRRMI_CLKEN_CACHE_HCLK_EN_Msk           (0x1UL << GPRRMI_CLKEN_CACHE_HCLK_EN_Pos)

#define GPRRMI_CLKEN_BB_RMI_HCLK_EN_Pos          (21)
#define GPRRMI_CLKEN_BB_RMI_HCLK_EN_Msk          (0x1UL << GPRRMI_CLKEN_BB_RMI_HCLK_EN_Pos)

#define GPRRMI_CLKEN_SEQ_RMI_HCLK_EN_Pos         (22)
#define GPRRMI_CLKEN_SEQ_RMI_HCLK_EN_Msk         (0x1UL << GPRRMI_CLKEN_SEQ_RMI_HCLK_EN_Pos)

#define GPRRMI_CLKEN_IC_RMI_HCLK_EN_Pos          (23)
#define GPRRMI_CLKEN_IC_RMI_HCLK_EN_Msk          (0x1UL << GPRRMI_CLKEN_IC_RMI_HCLK_EN_Pos)

#define GPRRMI_CLKEN_CIPHER_RMI_HCLK_EN_Pos      (24)
#define GPRRMI_CLKEN_CIPHER_RMI_HCLK_EN_Msk      (0x1UL << GPRRMI_CLKEN_CIPHER_RMI_HCLK_EN_Pos)

#define GPRRMI_CLKEN_CIPHER_HCLK_EN_Pos          (25)
#define GPRRMI_CLKEN_CIPHER_HCLK_EN_Msk          (0x1UL << GPRRMI_CLKEN_CIPHER_HCLK_EN_Pos)

#define GPRRMI_CLKEN_MFAB_HCLK_EN_Pos            (26)
#define GPRRMI_CLKEN_MFAB_HCLK_EN_Msk            (0x1UL << GPRRMI_CLKEN_MFAB_HCLK_EN_Pos)

#define GPRRMI_CLKEN_SMB_HCLK_EN_Pos             (27)
#define GPRRMI_CLKEN_SMB_HCLK_EN_Msk             (0x1UL << GPRRMI_CLKEN_SMB_HCLK_EN_Pos)

#define GPRRMI_CLKEN_FLASH_CLK_EN_Pos            (28)
#define GPRRMI_CLKEN_FLASH_CLK_EN_Msk            (0x1UL << GPRRMI_CLKEN_FLASH_CLK_EN_Pos)

#define GPRRMI_CLKEN_FLASH_HCLK_EN_Pos           (29)
#define GPRRMI_CLKEN_FLASH_HCLK_EN_Msk           (0x1UL << GPRRMI_CLKEN_FLASH_HCLK_EN_Pos)

#define GPRRMI_CLKEN_UNILOG_HCLK_EN_Pos          (30)
#define GPRRMI_CLKEN_UNILOG_HCLK_EN_Msk          (0x1UL << GPRRMI_CLKEN_UNILOG_HCLK_EN_Pos)

#define GPRRMI_CLKEN_RMI_AUTOCG_EN_Pos           (31)
#define GPRRMI_CLKEN_RMI_AUTOCG_EN_Msk           (0x1UL << GPRRMI_CLKEN_RMI_AUTOCG_EN_Pos)
/** @} */

/** @name DCXO_TRIM_OVWRT_CTRL - GPRRMI_DCXO_TRIM_OVWRT_CTRL register */
/** @{ */
#define GPRRMI_DCXO_TRIM_OVWRT_CTRL_EN_Pos       (0)
#define GPRRMI_DCXO_TRIM_OVWRT_CTRL_EN_Msk       (0x1UL << GPRRMI_DCXO_TRIM_OVWRT_CTRL_EN_Pos)
/** @} */

/** @name DCXO_TRIM_OVWRT_VAL - GPRRMI_DCXO_TRIM_OVWRT_VAL register */
/** @{ */
#define GPRRMI_DCXO_TRIM_OVWRT_VAL_VAL_Pos       (0)
#define GPRRMI_DCXO_TRIM_OVWRT_VAL_VAL_Msk       (0xFFUL << GPRRMI_DCXO_TRIM_OVWRT_VAL_VAL_Pos)
/** @} */

/** GPR_RMI base pointer */
#define GPR_RMI                                  ((GPRRMI_TypeDef *)GPR_RMI_BASE_ADDR)
/**
  * @}
  */ /* end of group GPR_RMI */

/** @addtogroup QSPI QSPI
  * @{
  */

/**
  * @brief QSPI register layout typedef
  *
  */
typedef struct
{
    __IO uint32_t QMCR;                          /**< QUADSPI Main Control Register,                      offset: 0x0 */
    __IO uint32_t QSCR;                          /**< QUADSPI Secondary Control Register,                 offset: 0x4 */
    __IO uint32_t QTCR;                          /**< QUADSPI Timing Control Register,                    offset: 0x8 */
    __IO uint32_t QFDR;                          /**< QUADSPI Frame Directive Register,                   offset: 0xC */
    __IO uint32_t QFIR;                          /**< QUADSPI Frame Instruction Register,                 offset: 0x10 */
    __IO uint32_t QFAR;                          /**< QUADSPI Frame Address Register,                     offset: 0x14 */
    __IO uint32_t QFCR;                          /**< QUADSPI Frame Continuous Mode Register,             offset: 0x18 */
    __IO uint32_t QFLR;                          /**< QUADSPI Data Length Register,                       offset: 0x1C */
    __IO uint32_t QSDR;                          /**< QUADSPI Data Register,                              offset: 0x20 */
    __IO uint32_t QSSR;                          /**< QUADSPI Status Register,                            offset: 0x24 */
    __IO uint32_t QIER;                          /**< QUADSPI Interrupt Enable Register,                  offset: 0x28 */
    __IO uint32_t QISR;                          /**< QUADSPI Interrupt Status Register,                  offset: 0x2C */
    __IO uint32_t QIMR;                          /**< QUADSPI Interrupt Mask Register,                    offset: 0x30 */
} QUADSPI_TypeDef;

/** @name QMCR - QSPI_QMCR register */
/** @{ */
#define QSPI_QMCR_EN_Pos                         (0)
#define QSPI_QMCR_EN_Msk                         (0x1UL << QSPI_QMCR_EN_Pos)
#define QSPI_QMCR_EN                             QSPI_QMCR_EN_Msk

#define QSPI_QMCR_DMAEN_Pos                      (1)
#define QSPI_QMCR_DMAEN_Msk                      (0x1UL << QSPI_QMCR_DMAEN_Pos)
#define QSPI_QMCR_DMAEN                          QSPI_QMCR_DMAEN_Msk

#define QSPI_QMCR_CSPLR_Pos                      (2)
#define QSPI_QMCR_CSPLR_Msk                      (0x1UL << QSPI_QMCR_CSPLR_Pos)
#define QSPI_QMCR_CSPLR                          QSPI_QMCR_CSPLR_Msk

#define QSPI_QMCR_TXFTHRES_Pos                   (4)
#define QSPI_QMCR_TXFTHRES_Msk                   (0x7UL << QSPI_QMCR_TXFTHRES_Pos)
#define QSPI_QMCR_TXFTHRES                       QSPI_QMCR_TXFTHRES_Msk
#define QSPI_QMCR_TXFTHRES_0                     (0x01UL << QSPI_QMCR_TXFTHRES_Pos)
#define QSPI_QMCR_TXFTHRES_1                     (0x02UL << QSPI_QMCR_TXFTHRES_Pos)
#define QSPI_QMCR_TXFTHRES_2                     (0x04UL << QSPI_QMCR_TXFTHRES_Pos)

#define QSPI_QMCR_RXFTHRES_Pos                   (8)
#define QSPI_QMCR_RXFTHRES_Msk                   (0x7UL << QSPI_QMCR_RXFTHRES_Pos)
#define QSPI_QMCR_RXFTHRES                       QSPI_QMCR_RXFTHRES_Msk
#define QSPI_QMCR_RXFTHRES_0                     (0x01UL << QSPI_QMCR_RXFTHRES_Pos)
#define QSPI_QMCR_RXFTHRES_1                     (0x02UL << QSPI_QMCR_RXFTHRES_Pos)
#define QSPI_QMCR_RXFTHRES_2                     (0x04UL << QSPI_QMCR_RXFTHRES_Pos)

#define QSPI_QMCR_CSEN_Pos                       (12)
#define QSPI_QMCR_CSEN_Msk                       (0xFUL << QSPI_QMCR_CSEN_Pos)
#define QSPI_QMCR_CSEN                           QSPI_QMCR_CSEN_Msk
#define QSPI_QMCR_CSEN_0                         (0x01UL << QSPI_QMCR_CSEN_Pos)
#define QSPI_QMCR_CSEN_1                         (0x02UL << QSPI_QMCR_CSEN_Pos)
#define QSPI_QMCR_CSEN_2                         (0x04UL << QSPI_QMCR_CSEN_Pos)
#define QSPI_QMCR_CSEN_3                         (0x08UL << QSPI_QMCR_CSEN_Pos)

#define QSPI_QMCR_XIP_Pos                        (16)
#define QSPI_QMCR_XIP_Msk                        (0x1UL << QSPI_QMCR_XIP_Pos)
#define QSPI_QMCR_XIP                            QSPI_QMCR_XIP_Msk

#define QSPI_QMCR_DFM_Pos                        (17)
#define QSPI_QMCR_DFM_Msk                        (0x1UL << QSPI_QMCR_DFM_Pos)
#define QSPI_QMCR_DFM                            QSPI_QMCR_DFM_Msk

#define QSPI_QMCR_FSIZE_Pos                      (20)
#define QSPI_QMCR_FSIZE_Msk                      (0x1FUL << QSPI_QMCR_FSIZE_Pos)
#define QSPI_QMCR_FSIZE                          QSPI_QMCR_FSIZE_Msk
#define QSPI_QMCR_FSIZE_0                        (0x01UL << QSPI_QMCR_FSIZE_Pos)
#define QSPI_QMCR_FSIZE_1                        (0x02UL << QSPI_QMCR_FSIZE_Pos)
#define QSPI_QMCR_FSIZE_2                        (0x04UL << QSPI_QMCR_FSIZE_Pos)
#define QSPI_QMCR_FSIZE_3                        (0x08UL << QSPI_QMCR_FSIZE_Pos)
#define QSPI_QMCR_FSIZE_4                        (0x10UL << QSPI_QMCR_FSIZE_Pos)
/** @} */

/** @name QSCR - QSPI_QSCR register */
/** @{ */
#define QSPI_QSCR_STFRM_Pos                      (0)
#define QSPI_QSCR_STFRM_Msk                      (0x1UL << QSPI_QSCR_STFRM_Pos)
#define QSPI_QSCR_STFRM                          QSPI_QSCR_STFRM_Msk

#define QSPI_QSCR_ABTTRX_Pos                     (1)
#define QSPI_QSCR_ABTTRX_Msk                     (0x1UL << QSPI_QSCR_ABTTRX_Pos)
#define QSPI_QSCR_ABTTRX                         QSPI_QSCR_ABTTRX_Msk

#define QSPI_QSCR_FLHTXFIFO_Pos                  (2)
#define QSPI_QSCR_FLHTXFIFO_Msk                  (0x1UL << QSPI_QSCR_FLHTXFIFO_Pos)
#define QSPI_QSCR_FLHTXFIFO                      QSPI_QSCR_FLHTXFIFO_Msk

#define QSPI_QSCR_FLHRXFIFO_Pos                  (3)
#define QSPI_QSCR_FLHRXFIFO_Msk                  (0x1UL << QSPI_QSCR_FLHRXFIFO_Pos)
#define QSPI_QSCR_FLHRXFIFO                      QSPI_QSCR_FLHRXFIFO_Msk
/** @} */

/** @name QTCR - QSPI_QTCR register */
/** @{ */
#define QSPI_QTCR_BAUDR_Pos                      (0)
#define QSPI_QTCR_BAUDR_Msk                      (0xFFUL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR                          QSPI_QTCR_BAUDR_Msk
#define QSPI_QTCR_BAUDR_0                        (0x01UL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR_1                        (0x02UL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR_2                        (0x04UL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR_3                        (0x08UL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR_4                        (0x10UL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR_5                        (0x01UL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR_6                        (0x02UL << QSPI_QTCR_BAUDR_Pos)
#define QSPI_QTCR_BAUDR_7                        (0x04UL << QSPI_QTCR_BAUDR_Pos)

#define QSPI_QTCR_CPHA_Pos                       (16)
#define QSPI_QTCR_CPHA_Msk                       (0x1UL << QSPI_QTCR_CPHA_Pos)
#define QSPI_QTCR_CPHA                           QSPI_QTCR_CPHA_Msk

#define QSPI_QTCR_CPOL_Pos                       (17)
#define QSPI_QTCR_CPOL_Msk                       (0x1UL << QSPI_QTCR_CPOL_Pos)
#define QSPI_QTCR_CPOL                           QSPI_QTCR_CPOL_Msk

#define QSPI_QTCR_SAMDLY_Pos                     (20)
#define QSPI_QTCR_SAMDLY_Msk                     (0x3UL << QSPI_QTCR_SAMDLY_Pos)
#define QSPI_QTCR_SAMDLY                         QSPI_QTCR_SAMDLY_Msk
#define QSPI_QTCR_SAMDLY_0                       (0x01UL << QSPI_QTCR_SAMDLY_Pos)
#define QSPI_QTCR_SAMDLY_1                       (0x02UL << QSPI_QTCR_SAMDLY_Pos)

#define QSPI_QTCR_FRMINTER_Pos                   (22)
#define QSPI_QTCR_FRMINTER_Msk                   (0x3UL << QSPI_QTCR_FRMINTER_Pos)
#define QSPI_QTCR_FRMINTER                       QSPI_QTCR_FRMINTER_Msk
#define QSPI_QTCR_FRMINTER_0                     (0x01UL << QSPI_QTCR_FRMINTER_Pos)
#define QSPI_QTCR_FRMINTER_1                     (0x02UL << QSPI_QTCR_FRMINTER_Pos)

#define QSPI_QTCR_DATINTER_Pos                   (24)
#define QSPI_QTCR_DATINTER_Msk                   (0x3UL << QSPI_QTCR_DATINTER_Pos)
#define QSPI_QTCR_DATINTER                       QSPI_QTCR_DATINTER_Msk
#define QSPI_QTCR_DATINTER_0                     (0x01UL << QSPI_QTCR_DATINTER_Pos)
#define QSPI_QTCR_DATINTER_1                     (0x02UL << QSPI_QTCR_DATINTER_Pos)

#define QSPI_QTCR_DATFNIS_Pos                    (26)
#define QSPI_QTCR_DATFNIS_Msk                    (0x3UL << QSPI_QTCR_DATFNIS_Pos)
#define QSPI_QTCR_DATFNIS                        QSPI_QTCR_DATFNIS_Msk
#define QSPI_QTCR_DATFNIS_0                      (0x01UL << QSPI_QTCR_DATFNIS_Pos)
#define QSPI_QTCR_DATFNIS_1                      (0x02UL << QSPI_QTCR_DATFNIS_Pos)

#define QSPI_QTCR_DATCHAG_Pos                    (28)
#define QSPI_QTCR_DATCHAG_Msk                    (0x3UL << QSPI_QTCR_DATCHAG_Pos)
#define QSPI_QTCR_DATCHAG                        QSPI_QTCR_DATCHAG_Msk
#define QSPI_QTCR_DATCHAG_0                      (0x01UL << QSPI_QTCR_DATCHAG_Pos)
#define QSPI_QTCR_DATCHAG_1                      (0x02UL << QSPI_QTCR_DATCHAG_Pos)
/** @} */

/** @name QFDR - QSPI_QFDR register */
/** @{ */
#define QSPI_QFDR_IMODE_Pos                      (0)
#define QSPI_QFDR_IMODE_Msk                      (0x3UL << QSPI_QFDR_IMODE_Pos)
#define QSPI_QFDR_IMODE                          QSPI_QFDR_IMODE_Msk
#define QSPI_QFDR_IMODE_0                        (0x1UL << QSPI_QFDR_IMODE_Pos)
#define QSPI_QFDR_IMODE_1                        (0x2UL << QSPI_QFDR_IMODE_Pos)

#define QSPI_QFDR_IONCE_Pos                      (2)
#define QSPI_QFDR_IONCE_Msk                      (0x1UL << QSPI_QFDR_IONCE_Pos)
#define QSPI_QFDR_IONCE                          QSPI_QFDR_IONCE_Msk

#define QSPI_QFDR_ADMODE_Pos                     (4)
#define QSPI_QFDR_ADMODE_Msk                     (0x3UL << QSPI_QFDR_ADMODE_Pos)
#define QSPI_QFDR_ADMODE                         QSPI_QFDR_ADMODE_Msk
#define QSPI_QFDR_ADMODE_0                       (0x1UL << QSPI_QFDR_ADMODE_Pos)
#define QSPI_QFDR_ADMODE_1                       (0x2UL << QSPI_QFDR_ADMODE_Pos)

#define QSPI_QFDR_ADSIZE_Pos                     (6)
#define QSPI_QFDR_ADSIZE_Msk                     (0x3UL << QSPI_QFDR_ADSIZE_Pos)
#define QSPI_QFDR_ADSIZE                         QSPI_QFDR_ADSIZE_Msk
#define QSPI_QFDR_ADSIZE_0                       (0x1UL << QSPI_QFDR_ADSIZE_Pos)
#define QSPI_QFDR_ADSIZE_1                       (0x2UL << QSPI_QFDR_ADSIZE_Pos)

#define QSPI_QFDR_MDMODE_Pos                     (8)
#define QSPI_QFDR_MDMODE_Msk                     (0x3UL << QSPI_QFDR_MDMODE_Pos)
#define QSPI_QFDR_MDMODE                         QSPI_QFDR_MDMODE_Msk
#define QSPI_QFDR_MDMODE_0                       (0x1UL << QSPI_QFDR_MDMODE_Pos)
#define QSPI_QFDR_MDMODE_1                       (0x2UL << QSPI_QFDR_MDMODE_Pos)

#define QSPI_QFDR_MDSIZE_Pos                     (10)
#define QSPI_QFDR_MDSIZE_Msk                     (0x3UL << QSPI_QFDR_MDSIZE_Pos)
#define QSPI_QFDR_MDSIZE                         QSPI_QFDR_MDSIZE_Msk
#define QSPI_QFDR_MDSIZE_0                       (0x1UL << QSPI_QFDR_MDSIZE_Pos)
#define QSPI_QFDR_MDSIZE_1                       (0x2UL << QSPI_QFDR_MDSIZE_Pos)

#define QSPI_QFDR_DUMEXT_Pos                     (12)
#define QSPI_QFDR_DUMEXT_Msk                     (0x1UL << QSPI_QFDR_DUMEXT_Pos)
#define QSPI_QFDR_DUMEXT                         QSPI_QFDR_DUMEXT_Msk

#define QSPI_QFDR_DUMMYNUM_Pos                   (13)
#define QSPI_QFDR_DUMMYNUM_Msk                   (0x7UL << QSPI_QFDR_DUMMYNUM_Pos)
#define QSPI_QFDR_DUMMYNUM                       QSPI_QFDR_DUMMYNUM_Msk
#define QSPI_QFDR_DUMMYNUM_0                     (0x1UL << QSPI_QFDR_DUMMYNUM_Pos)
#define QSPI_QFDR_DUMMYNUM_1                     (0x2UL << QSPI_QFDR_DUMMYNUM_Pos)
#define QSPI_QFDR_DUMMYNUM_2                     (0x3UL << QSPI_QFDR_DUMMYNUM_Pos)

#define QSPI_QFDR_DATMDOE_Pos                    (16)
#define QSPI_QFDR_DATMDOE_Msk                    (0x3UL << QSPI_QFDR_DATMDOE_Pos)
#define QSPI_QFDR_DATMDOE                        QSPI_QFDR_DATMDOE_Msk
#define QSPI_QFDR_DATMDOE_0                      (0x1UL << QSPI_QFDR_DATMDOE_Pos)
#define QSPI_QFDR_DATMDOE_1                      (0x2UL << QSPI_QFDR_DATMDOE_Pos)

#define QSPI_QFDR_DATTXEN_Pos                    (18)
#define QSPI_QFDR_DATTXEN_Msk                    (0x1UL << QSPI_QFDR_DATTXEN_Pos)
#define QSPI_QFDR_DATTXEN                        QSPI_QFDR_DATTXEN_Msk

#define QSPI_QFDR_DATRXEN_Pos                    (19)
#define QSPI_QFDR_DATRXEN_Msk                    (0x1UL << QSPI_QFDR_DATRXEN_Pos)
#define QSPI_QFDR_DATRXEN                        QSPI_QFDR_DATRXEN_Msk

#define QSPI_QFDR_ENDLESS_Pos                    (20)
#define QSPI_QFDR_ENDLESS_Msk                    (0x1UL << QSPI_QFDR_ENDLESS_Pos)
#define QSPI_QFDR_ENDLESS                        QSPI_QFDR_ENDLESS_Msk
/** @} */

/** @name QFIR - QSPI_QFIR register */
/** @{ */
#define QSPI_QFIR_INSTRUCTION_Pos                (0)
#define QSPI_QFIR_INSTRUCTION_Msk                (0xFFUL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION                    QSPI_QFIR_INSTRUCTION_Msk
#define QSPI_QFIR_INSTRUCTION_0                  (0x01UL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION_1                  (0x02UL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION_2                  (0x04UL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION_3                  (0x08UL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION_4                  (0x10UL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION_5                  (0x20UL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION_6                  (0x40UL << QSPI_QFIR_INSTRUCTION_Pos)
#define QSPI_QFIR_INSTRUCTION_7                  (0x80UL << QSPI_QFIR_INSTRUCTION_Pos)
/** @} */

/** @name QFAR - QSPI_QFAR register */
/** @{ */
#define QSPI_QFAR_ADDRESS_Pos                    (0)
#define QSPI_QFAR_ADDRESS_Msk                    (0xFFFFFFFFUL << QSPI_QFAR_ADDRESS_Pos)
#define QSPI_QFAR_ADDRESS                        QSPI_QFAR_ADDRESS_Msk
/** @} */

/** @name QFCR - QSPI_QFCR register */
/** @{ */
#define QSPI_QFCR_MODE_Pos                       (0)
#define QSPI_QFCR_MODE_Msk                       (0xFFUL << QSPI_QFCR_MODE_Pos)
#define QSPI_QFCR_MODE                           QSPI_QFCR_MODE_Msk

#define QSPI_QFCR_LEN_Pos                        (0)
#define QSPI_QFCR_LEN_Msk                        (0xFFFUL << QSPI_QFCR_LEN_Pos)
#define QSPI_QFCR_LEN                            QSPI_QFCR_LEN_Msk

#define QSPI_QFCR_INFI_Pos                       (12)
#define QSPI_QFCR_INFI_Msk                       (0x1UL << QSPI_QFCR_INFI_Pos)
#define QSPI_QFCR_INFI                           QSPI_QFCR_INFI_Msk
/** @} */

/** @name QSDR - QSPI_QSDR register */
/** @{ */
#define QSPI_QSDR_DATA_Pos                       (0)
#define QSPI_QSDR_DATA_Msk                       (0xFFFFFFFFUL << QSPI_QSDR_DATA_Pos)
#define QSPI_QSDR_DATA                           QSPI_QSDR_DATA_Msk
/** @} */

/** @name QSSR - QSPI_QSSR register */
/** @{ */
#define QSPI_QSSR_BUSY_Pos                       (0)
#define QSPI_QSSR_BUSY_Msk                       (0x1UL << QSPI_QSSR_BUSY_Pos)
#define QSPI_QSSR_BUSY                           QSPI_QSSR_BUSY_Msk

#define QSPI_QSSR_ABORT_Pos                      (1)
#define QSPI_QSSR_ABORT_Msk                      (0x1UL << QSPI_QSSR_ABORT_Pos)
#define QSPI_QSSR_ABORT                          QSPI_QSSR_ABORT_Msk

#define QSPI_QSSR_TXTRESH_Pos                    (2)
#define QSPI_QSSR_TXTRESH_Msk                    (0x1UL << QSPI_QSSR_TXTRESH_Pos)
#define QSPI_QSSR_TXTRESH                        QSPI_QSSR_TXTRESH_Msk

#define QSPI_QSSR_RXTRESH_Pos                    (3)
#define QSPI_QSSR_RXTRESH_Msk                    (0x1UL << QSPI_QSSR_RXTRESH_Pos)
#define QSPI_QSSR_RXTRESH                        QSPI_QSSR_RXTRESH_Msk

#define QSPI_QSSR_CSSTAT_Pos                     (4)
#define QSPI_QSSR_CSSTAT_Msk                     (0xFUL << QSPI_QSSR_CSSTAT_Pos)
#define QSPI_QSSR_CSSTAT                         QSPI_QSSR_CSSTAT_Msk
#define QSPI_QSSR_CSSTAT_0                       (0x01UL << QSPI_QSSR_CSSTAT_Pos)
#define QSPI_QSSR_CSSTAT_1                       (0x02UL << QSPI_QSSR_CSSTAT_Pos)
#define QSPI_QSSR_CSSTAT_2                       (0x04UL << QSPI_QSSR_CSSTAT_Pos)
#define QSPI_QSSR_CSSTAT_3                       (0x08UL << QSPI_QSSR_CSSTAT_Pos)

#define QSPI_QSSR_IONCE_Pos                      (8)
#define QSPI_QSSR_IONCE_Msk                      (0x1UL << QSPI_QSSR_IONCE_Pos)
#define QSPI_QSSR_IONCE                          QSPI_QSSR_IONCE_Msk

#define QSPI_QSSR_TXFLEVEL_Pos                   (16)
#define QSPI_QSSR_TXFLEVEL_Msk                   (0x1FUL << QSPI_QSSR_TXFLEVEL_Pos)
#define QSPI_QSSR_TXFLEVEL                       QSPI_QSSR_TXFLEVEL_Msk
#define QSPI_QSSR_TXFLEVEL_0                     (0x01UL << QSPI_QSSR_TXFLEVEL_Pos)
#define QSPI_QSSR_TXFLEVEL_1                     (0x02UL << QSPI_QSSR_TXFLEVEL_Pos)
#define QSPI_QSSR_TXFLEVEL_2                     (0x04UL << QSPI_QSSR_TXFLEVEL_Pos)
#define QSPI_QSSR_TXFLEVEL_3                     (0x08UL << QSPI_QSSR_TXFLEVEL_Pos)
#define QSPI_QSSR_TXFLEVEL_4                     (0x10UL << QSPI_QSSR_TXFLEVEL_Pos)

#define QSPI_QSSR_RXFLEVEL_Pos                   (24)
#define QSPI_QSSR_RXFLEVEL_Msk                   (0x1FUL << QSPI_QSSR_RXFLEVEL_Pos)
#define QSPI_QSSR_RXFLEVEL                       QSPI_QSSR_RXFLEVEL_Msk
#define QSPI_QSSR_RXFLEVEL_0                     (0x01UL << QSPI_QSSR_RXFLEVEL_Pos)
#define QSPI_QSSR_RXFLEVEL_1                     (0x02UL << QSPI_QSSR_RXFLEVEL_Pos)
#define QSPI_QSSR_RXFLEVEL_2                     (0x04UL << QSPI_QSSR_RXFLEVEL_Pos)
#define QSPI_QSSR_RXFLEVEL_3                     (0x08UL << QSPI_QSSR_RXFLEVEL_Pos)
#define QSPI_QSSR_RXFLEVEL_4                     (0x10UL << QSPI_QSSR_RXFLEVEL_Pos)
/** @} */

/** @name QIER - QSPI_QIER register */
/** @{ */
#define QSPI_QIER_DONE_Pos                       (0)
#define QSPI_QIER_DONE_Msk                       (0x1UL << QSPI_QIER_DONE_Pos)
#define QSPI_QIER_DONE                           QSPI_QIER_DONE_Msk

#define QSPI_QIER_ERROR_Pos                      (1)
#define QSPI_QIER_ERROR_Msk                      (0x1UL << QSPI_QIER_ERROR_Pos)
#define QSPI_QIER_ERROR                          QSPI_QIER_ERROR_Msk

#define QSPI_QIER_TXUDFLOW_Pos                   (2)
#define QSPI_QIER_TXUDFLOW_Msk                   (0x1UL << QSPI_QIER_TXUDFLOW_Pos)
#define QSPI_QIER_TXUDFLOW                       QSPI_QIER_TXUDFLOW_Msk

#define QSPI_QIER_TXOVFLOW_Pos                   (3)
#define QSPI_QIER_TXOVFLOW_Msk                   (0x1UL << QSPI_QIER_TXOVFLOW_Pos)
#define QSPI_QIER_TXOVFLOW                       QSPI_QIER_TXOVFLOW_Msk

#define QSPI_QIER_TXEMPTY_Pos                    (4)
#define QSPI_QIER_TXEMPTY_Msk                    (0x1UL << QSPI_QIER_TXEMPTY_Pos)
#define QSPI_QIER_TXEMPTY                        QSPI_QIER_TXEMPTY_Msk

#define QSPI_QIER_TXFULL_Pos                     (5)
#define QSPI_QIER_TXFULL_Msk                     (0x1UL << QSPI_QIER_TXFULL_Pos)
#define QSPI_QIER_TXFULL                         QSPI_QIER_TXFULL_Msk

#define QSPI_QIER_RXUDFLOW_Pos                   (6)
#define QSPI_QIER_RXUDFLOW_Msk                   (0x1UL << QSPI_QIER_RXUDFLOW_Pos)
#define QSPI_QIER_RXUDFLOW                       QSPI_QIER_RXUDFLOW_Msk

#define QSPI_QIER_RXOVFLOW_Pos                   (7)
#define QSPI_QIER_RXOVFLOW_Msk                   (0x1UL << QSPI_QIER_RXOVFLOW_Pos)
#define QSPI_QIER_RXOVFLOW                       QSPI_QIER_RXOVFLOW_Msk

#define QSPI_QIER_RXEMPTY_Pos                    (8)
#define QSPI_QIER_RXEMPTY_Msk                    (0x1UL << QSPI_QIER_RXEMPTY_Pos)
#define QSPI_QIER_RXEMPTY                        QSPI_QIER_RXEMPTY_Msk

#define QSPI_QIER_RXFULL_Pos                     (9)
#define QSPI_QIER_RXFULL_Msk                     (0x1UL << QSPI_QIER_RXFULL_Pos)
#define QSPI_QIER_RXFULL                         QSPI_QIER_RXFULL_Msk

#define QSPI_QIER_XIPFAIL_Pos                    (10)
#define QSPI_QIER_XIPFAIL_Msk                    (0x1UL << QSPI_QIER_XIPFAIL_Pos)
#define QSPI_QIER_XIPFAIL                        QSPI_QIER_XIPFAIL_Msk
/** @} */

/** @name QISR - QSPI_QISR register */
/** @{ */
#define QSPI_QISR_DONE_Pos                       (0)
#define QSPI_QISR_DONE_Msk                       (0x1UL << QSPI_QISR_DONE_Pos)
#define QSPI_QISR_DONE                           QSPI_QISR_DONE_Msk

#define QSPI_QISR_ERROR_Pos                      (1)
#define QSPI_QISR_ERROR_Msk                      (0x1UL << QSPI_QISR_ERROR_Pos)
#define QSPI_QISR_ERROR                          QSPI_QISR_ERROR_Msk

#define QSPI_QISR_TXUDFLOW_Pos                   (2)
#define QSPI_QISR_TXUDFLOW_Msk                   (0x1UL << QSPI_QISR_TXUDFLOW_Pos)
#define QSPI_QISR_TXUDFLOW                       QSPI_QISR_TXUDFLOW_Msk

#define QSPI_QISR_TXOVFLOW_Pos                   (3)
#define QSPI_QISR_TXOVFLOW_Msk                   (0x1UL << QSPI_QISR_TXOVFLOW_Pos)
#define QSPI_QISR_TXOVFLOW                       QSPI_QISR_TXOVFLOW_Msk

#define QSPI_QISR_TXEMPTY_Pos                    (4)
#define QSPI_QISR_TXEMPTY_Msk                    (0x1UL << QSPI_QISR_TXEMPTY_Pos)
#define QSPI_QISR_TXEMPTY                        QSPI_QISR_TXEMPTY_Msk

#define QSPI_QISR_TXFULL_Pos                     (5)
#define QSPI_QISR_TXFULL_Msk                     (0x1UL << QSPI_QISR_TXFULL_Pos)
#define QSPI_QISR_TXFULL                         QSPI_QISR_TXFULL_Msk

#define QSPI_QISR_RXUDFLOW_Pos                   (6)
#define QSPI_QISR_RXUDFLOW_Msk                   (0x1UL << QSPI_QISR_RXUDFLOW_Pos)
#define QSPI_QISR_RXUDFLOW                       QSPI_QISR_RXUDFLOW_Msk

#define QSPI_QISR_RXOVFLOW_Pos                   (7)
#define QSPI_QISR_RXOVFLOW_Msk                   (0x1UL << QSPI_QISR_RXOVFLOW_Pos)
#define QSPI_QISR_RXOVFLOW                       QSPI_QISR_RXOVFLOW_Msk

#define QSPI_QISR_RXEMPTY_Pos                    (8)
#define QSPI_QISR_RXEMPTY_Msk                    (0x1UL << QSPI_QISR_RXEMPTY_Pos)
#define QSPI_QISR_RXEMPTY                        QSPI_QISR_RXEMPTY_Msk

#define QSPI_QISR_RXFULL_Pos                     (9)
#define QSPI_QISR_RXFULL_Msk                     (0x1UL << QSPI_QISR_RXFULL_Pos)
#define QSPI_QISR_RXFULL                         QSPI_QISR_RXFULL_Msk

#define QSPI_QISR_XIPFAIL_Pos                    (10)
#define QSPI_QISR_XIPFAIL_Msk                    (0x1UL << QSPI_QISR_XIPFAIL_Pos)
#define QSPI_QISR_XIPFAIL                        QSPI_QISR_XIPFAIL_Msk
/** @} */

/** @name QIMR - QSPI_QIMR register */
/** @{ */
#define QSPI_QIMR_DONE_Pos                       (0)
#define QSPI_QIMR_DONE_Msk                       (0x1UL << QSPI_QIMR_DONE_Pos)
#define QSPI_QIMR_DONE                           QSPI_QIMR_DONE_Msk

#define QSPI_QIMR_ERROR_Pos                      (1)
#define QSPI_QIMR_ERROR_Msk                      (0x1UL << QSPI_QIMR_ERROR_Pos)
#define QSPI_QIMR_ERROR                          QSPI_QIMR_ERROR_Msk

#define QSPI_QIMR_TXUDFLOW_Pos                   (2)
#define QSPI_QIMR_TXUDFLOW_Msk                   (0x1UL << QSPI_QIMR_TXUDFLOW_Pos)
#define QSPI_QIMR_TXUDFLOW                       QSPI_QIMR_TXUDFLOW_Msk

#define QSPI_QIMR_TXOVFLOW_Pos                   (3)
#define QSPI_QIMR_TXOVFLOW_Msk                   (0x1UL << QSPI_QIMR_TXOVFLOW_Pos)
#define QSPI_QIMR_TXOVFLOW                       QSPI_QIMR_TXOVFLOW_Msk

#define QSPI_QIMR_TXEMPTY_Pos                    (4)
#define QSPI_QIMR_TXEMPTY_Msk                    (0x1UL << QSPI_QIMR_TXEMPTY_Pos)
#define QSPI_QIMR_TXEMPTY                        QSPI_QIMR_TXEMPTY_Msk

#define QSPI_QIMR_TXFULL_Pos                     (5)
#define QSPI_QIMR_TXFULL_Msk                     (0x1UL << QSPI_QIMR_TXFULL_Pos)
#define QSPI_QIMR_TXFULL                         QSPI_QIMR_TXFULL_Msk

#define QSPI_QIMR_RXUDFLOW_Pos                   (6)
#define QSPI_QIMR_RXUDFLOW_Msk                   (0x1UL << QSPI_QIMR_RXUDFLOW_Pos)
#define QSPI_QIMR_RXUDFLOW                       QSPI_QIMR_RXUDFLOW_Msk

#define QSPI_QIMR_RXOVFLOW_Pos                   (7)
#define QSPI_QIMR_RXOVFLOW_Msk                   (0x1UL << QSPI_QIMR_RXOVFLOW_Pos)
#define QSPI_QIMR_RXOVFLOW                       QSPI_QIMR_RXOVFLOW_Msk

#define QSPI_QIMR_RXEMPTY_Pos                    (8)
#define QSPI_QIMR_RXEMPTY_Msk                    (0x1UL << QSPI_QIMR_RXEMPTY_Pos)
#define QSPI_QIMR_RXEMPTY                        QSPI_QIMR_RXEMPTY_Msk

#define QSPI_QIMR_RXFULL_Pos                     (9)
#define QSPI_QIMR_RXFULL_Msk                     (0x1UL << QSPI_QIMR_RXFULL_Pos)
#define QSPI_QIMR_RXFULL                         QSPI_QIMR_RXFULL_Msk

#define QSPI_QIMR_XIPFAIL_Pos                    (10)
#define QSPI_QIMR_XIPFAIL_Msk                    (0x1UL << QSPI_QIMR_XIPFAIL_Pos)
#define QSPI_QIMR_XIPFAIL                        QSPI_QIMR_XIPFAIL_Msk
/** @} */

/** Peripheral QUADSPI base pointer */
#define QUADSPI                                  ((QUADSPI_TypeDef *) QSPI_R_BASE)

/**
  * @}
  */ /* end of group QSPI */

/** @addtogroup UNILOG Unilog
  * @{
  */

/**
  * @brief UNILOG register layout typedef
  *
  */
typedef struct
{
    __IO uint32_t ENABLEA;                       /**< Unilog Enable Register,       offset: 0x0 */
    __IO uint32_t HWLOGEN;                       /**< HWLOG Enable Register,        offset: 0x4 */
    __IO uint32_t SWHEADER;                      /**< SWLOG Header Register,        offset: 0x8 */
    __IO uint32_t SWBODY;                        /**< SWLOG Body Register,          offset: 0xC */
    __IO uint32_t SWENDING;                      /**< SWLOG Ending Register,        offset: 0x10 */
    __IO uint32_t SWFIFOSTATE;                   /**< SWFIFO State Register,        offset: 0x14 */
    __IO uint32_t COCFG;                         /**< Cooperate Config Register,    offset: 0x18 */
    __IO uint32_t HWCFG;                         /**< HW Config Register,           offset: 0x1C */
    __IO uint32_t DROPBITMAP;                    /**< Drop Bitmap Register,         offset: 0x20 */
    __IO uint32_t HWDROPCNT;                     /**< Drop Counter Register,        offset: 0x24 */
    __IO uint32_t OUTFIFOSTATE;                  /**< Out FIFO State Register,      offset: 0x28 */
    __IO uint32_t RESERVED_0;
    __IO uint32_t UNILOGOUT;                     /**< UNILOG Out Register,          offset: 0x30 */
    __IO uint32_t INTSTATE;                      /**< Interrupt State Register,     offset: 0x34 */
    __IO uint32_t INTMASK;                       /**< Interrupt Mask Register,      offset: 0x38 */
    __IO uint32_t SQRTRGEN0;                     /**< Sqr Trg En0 Register,         offset: 0x3C */
    __IO uint32_t SQRTRGEN1;                     /**< Sqr Trg En1 Register,         offset: 0x40 */
} UNILOG_TypeDef;

/** @name ENABLEA - UNILOG_ENABLEA register */
/** @{ */
#define UNILOG_ENABLEA_EN_Pos                    (0)
#define UNILOG_ENABLEA_EN_Msk                    (0x1UL << UNILOG_ENABLEA_EN_Pos)
/** @} */

/** @name HWLOGEN - UNILOG_HWLOGEN register */
/** @{ */
#define UNILOG_HWLOGEN_DE_Pos                    (0)
#define UNILOG_HWLOGEN_DE_Msk                    (0x1UL << UNILOG_HWLOGEN_DE_Pos)

#define UNILOG_HWLOGEN_CE1_Pos                   (1)
#define UNILOG_HWLOGEN_CE1_Msk                   (0x1UL << UNILOG_HWLOGEN_CE1_Pos)

#define UNILOG_HWLOGEN_CE2_Pos                   (2)
#define UNILOG_HWLOGEN_CE2_Msk                   (0x1UL << UNILOG_HWLOGEN_CE2_Pos)

#define UNILOG_HWLOGEN_ICS_Pos                   (3)
#define UNILOG_HWLOGEN_ICS_Msk                   (0x1UL << UNILOG_HWLOGEN_ICS_Pos)

#define UNILOG_HWLOGEN_RXDFE_Pos                 (4)
#define UNILOG_HWLOGEN_RXDFE_Msk                 (0x1UL << UNILOG_HWLOGEN_RXDFE_Pos)

#define UNILOG_HWLOGEN_TX_Pos                    (5)
#define UNILOG_HWLOGEN_TX_Msk                    (0x1UL << UNILOG_HWLOGEN_TX_Pos)

#define UNILOG_HWLOGEN_SEQUENCER_CODER_Pos       (6)
#define UNILOG_HWLOGEN_SEQUENCER_CODER_Msk       (0x1UL << UNILOG_HWLOGEN_SEQUENCER_CODER_Pos)

#define UNILOG_HWLOGEN_SEQUENCER_Pos             (7)
#define UNILOG_HWLOGEN_SEQUENCER_Msk             (0x1UL << UNILOG_HWLOGEN_SEQUENCER_Pos)
/** @} */

/** @name SWHEADER - UNILOG_SWHEADER register */
/** @{ */
#define UNILOG_SWHEADER_HEADER_Pos               (0)
#define UNILOG_SWHEADER_HEADER_Msk               (0x1UL << UNILOG_SWHEADER_HEADER_Pos)
/** @} */

/** @name SWBODY - UNILOG_SWBODY register */
/** @{ */
#define UNILOG_SWBODY_BODY_Pos                   (0)
#define UNILOG_SWBODY_BODY_Msk                   (0xFFFFFFFFUL << UNILOG_SWBODY_BODY_Pos)
/** @} */

/** @name SWENDING - UNILOG_SWENDING register */
/** @{ */
#define UNILOG_SWENDING_END_Pos                  (0)
#define UNILOG_SWENDING_END_Msk                  (0xFFFFFFFFUL << UNILOG_SWENDING_END_Pos)
/** @} */

/** @name SWFIFOSTATE - UNILOG_SWFIFOSTATE register */
/** @{ */
#define UNILOG_SWFIFOSTATE_SIZE_Pos              (0)
#define UNILOG_SWFIFOSTATE_SIZE_Msk              (0x7FUL << UNILOG_SWFIFOSTATE_SIZE_Pos)
/** @} */

/** @name COCFG - UNILOG_COCFG register */
/** @{ */
#define UNILOG_COCFG_DMAREQTH_Pos                (0)
#define UNILOG_COCFG_DMAREQTH_Msk                (0x3FUL << UNILOG_COCFG_DMAREQTH_Pos)

#define UNILOG_COCFG_PERIPHEN_Pos                (6)
#define UNILOG_COCFG_PERIPHEN_Msk                (0x1FUL << UNILOG_COCFG_PERIPHEN_Pos)
/** @} */

/** @name HWCFG - UNILOG_HWCFG register */
/** @{ */
#define UNILOG_HWCFG_HWINFODROPTIME_Pos          (0)
#define UNILOG_HWCFG_HWINFODROPTIME_Msk          (0x1FUL << UNILOG_HWCFG_HWINFODROPTIME_Pos)

#define UNILOG_HWCFG_HWTRIGDROPTIME_Pos          (5)
#define UNILOG_HWCFG_HWTRIGDROPTIME_Msk          (0x1FUL << UNILOG_HWCFG_HWTRIGDROPTIME_Pos)

#define UNILOG_HWCFG_DISPATCHMETHOD_Pos          (10)
#define UNILOG_HWCFG_DISPATCHMETHOD_Msk          (0x7UL << UNILOG_HWCFG_DISPATCHMETHOD_Pos)

#define UNILOG_HWCFG_HWTIMESTAMPMODE_Pos         (13)
#define UNILOG_HWCFG_HWTIMESTAMPMODE_Msk         (0x1UL << UNILOG_HWCFG_HWTIMESTAMPMODE_Pos)

#define UNILOG_HWCFG_OUTFIFOAFULLTH_Pos          (14)
#define UNILOG_HWCFG_OUTFIFOAFULLTH_Msk          (0x3FUL << UNILOG_HWCFG_OUTFIFOAFULLTH_Pos)

#define UNILOG_HWCFG_PERIPHWATCHDOG_Pos          (20)
#define UNILOG_HWCFG_PERIPHWATCHDOG_Msk          (0x7UL << UNILOG_HWCFG_PERIPHWATCHDOG_Pos)

#define UNILOG_HWCFG_AUTOCLKGATING_Pos           (23)
#define UNILOG_HWCFG_AUTOCLKGATING_Msk           (0x1UL << UNILOG_HWCFG_AUTOCLKGATING_Pos)
/** @} */

/** @name DROPBITMAP - UNILOG_DROPBITMAP register */
/** @{ */
#define UNILOG_DROPBITMAP_STATUS_Pos             (0)
#define UNILOG_DROPBITMAP_STATUS_Msk             (0xFFFFFFFFUL << UNILOG_DROPBITMAP_STATUS_Pos)
/** @} */

/** @name HWDROPCNT - UNILOG_HWDROPCNT register */
/** @{ */
#define UNILOG_HWDROPCNT_VALUE_Pos               (0)
#define UNILOG_HWDROPCNT_VALUE_Msk               (0xFFFFUL << UNILOG_HWDROPCNT_VALUE_Pos)
/** @} */

/** @name OUTFIFOSTATE - UNILOG_OUTFIFOSTATE register */
/** @{ */
#define UNILOG_OUTFIFOSTATE_DEPTH_Pos            (0)
#define UNILOG_OUTFIFOSTATE_DEPTH_Msk            (0x7FUL << UNILOG_OUTFIFOSTATE_DEPTH_Pos)
/** @} */

/** @name UNILOGOUT - UNILOG_UNILOGOUT register */
/** @{ */
#define UNILOG_UNILOGOUT_OUT_Pos                 (0)
#define UNILOG_UNILOGOUT_OUT_Msk                 (0xFFFFFFFFUL << UNILOG_UNILOGOUT_OUT_Pos)
/** @} */

/** @name INTSTATE - UNILOG_INTSTATE register */
/** @{ */
#define UNILOG_INTSTATE_HWDROP_Pos               (0)
#define UNILOG_INTSTATE_HWDROP_Msk               (0x1UL << UNILOG_INTSTATE_HWDROP_Pos)

#define UNILOG_INTSTATE_SWFIFOOVERFLOW_Pos       (1)
#define UNILOG_INTSTATE_SWFIFOOVERFLOW_Msk       (0x1UL << UNILOG_INTSTATE_SWFIFOOVERFLOW_Pos)
/** @} */

/** @name INTMASK - UNILOG_INTMASK register */
/** @{ */
#define UNILOG_INTMASK_HWDROP_Pos                (0)
#define UNILOG_INTMASK_HWDROP_Msk                (0x1UL << UNILOG_INTMASK_HWDROP_Pos)

#define UNILOG_INTMASK_SWFIFOOVERFLOW_Pos        (1)
#define UNILOG_INTMASK_SWFIFOOVERFLOW_Msk        (0x1UL << UNILOG_INTMASK_SWFIFOOVERFLOW_Pos)
/** @} */

/** Peripheral UNILOG base pointer */
#define UNILOG                                   ((UNILOG_TypeDef *)UNILOG_BASE_ADDR)

/**
  * @}
  */ /* end of group UNILOG */



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

/**
  * @}
  */ /* end of group Device_peripheral_access */

#ifdef __cplusplus
}
#endif

#endif /* QCX212_INTERNAL_H */
