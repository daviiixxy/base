/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    gpr_qcx212.h
 * Description:  QCX212 gpr driver header file
 * History:      Rev1.0   2018-11-14
 *
 ****************************************************************************/

#ifndef _GPR_QCX212_H
#define _GPR_QCX212_H

#include "qcx212_internal.h"
#include "qcx212.h"
#include "Driver_Common.h"

/**
  \addtogroup gpr_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef __CLOCK_DECLARATION_DEFINED__
#define __CLOCK_DECLARATION_DEFINED__

/** \brief List of clock IDs used for clock gate, clock source and divider setting */
typedef enum _clock_ID
{
    GPR_ALLClk            = 0,            /**< ALL clock           */
    GPR_RCClk             = 1U,           /**< RC clock            */
    GPR_204MClk           = 2U,           /**< 204M clock          */
    GPR_102MClk           = 3U,           /**< 102M clock          */
    GPR_51MClk            = 4U,           /**< 51M clock           */
    GPR_DAPFuncClk        = 5U,           /**< DAP Func clock      */

    GPR_SPISClk           = 6U,           /**< SPIS clock          */
    GPR_CLKCALClk         = 7U,           /**< CLK CAL clock       */
    GPR_AONFuncClk        = 8U,           /**< AON Func clock      */
    GPR_PMDIGAPBClk       = 9U,           /**< PMDIG APB clock     */
    GPR_RFDIGAPBClk       = 10U,          /**< RFDIG APB clock     */

    GPR_GPIO0APBClk       = 11U,          /**< GPIO0 APB clock     */
    GPR_GPIO1APBClk       = 12U,          /**< GPIO1 APB clock     */
    GPR_GPIOAPBClk        = 13U,          /**< GPIO APB clock      */
    GPR_I2C0FuncClk       = 14U,          /**< I2C0 Func clock     */
    GPR_I2C1FuncClk       = 15U,          /**< I2C1 Func clock     */

    GPR_I2C0APBClk        = 16U,          /**< I2C0 APB clock      */
    GPR_I2C1APBClk        = 17U,          /**< I2C1 APB clock      */
    GPR_PADAPBClk         = 18U,          /**< PAD APB clock       */
    GPR_RFFEFuncClk       = 19U,          /**< RFFE Func clock     */
    GPR_RFFEAPBClk        = 20U,          /**< RFFE APB clock      */

    GPR_SPI0FuncClk       = 21U,          /**< SPI0 Func clock     */
    GPR_SPI1FuncClk       = 22U,          /**< SPI1 Func clock     */
    GPR_SPI0APBClk        = 23U,          /**< SPI0 APB clock      */
    GPR_SPI1APBClk        = 24U,          /**< SPI0 APB clock      */
    GPR_UART0FuncClk      = 25U,          /**< UART0 Func clock    */

    GPR_UART1FuncClk      = 26U,          /**< UART1 Func clock    */
    GPR_UART2FuncClk      = 27U,          /**< UART2 Func clock    */
    GPR_UART0APBClk       = 28U,          /**< UART0 APB clock     */
    GPR_UART1APBClk       = 29U,          /**< UART1 APB clock     */
    GPR_UART2APBClk       = 30U,          /**< UART2 APB clock     */

    GPR_TIMER0FuncClk     = 32U,          /**< TIMER0 Func clock   */
    GPR_TIMER1FuncClk     = 33U,          /**< TIMER1 Func clock   */
    GPR_TIMER2FuncClk     = 34U,          /**< TIMER2 Func clock   */
    GPR_TIMER3FuncClk     = 35U,          /**< TIMER3 Func clock   */

    GPR_TIMER4FuncClk     = 36U,          /**< TIMER4 Func clock   */
    GPR_TIMER5FuncClk     = 37U,          /**< TIMER5 Func clock   */
    GPR_SystickFuncClk    = 38U,          /**< Systick Func clock  */
    GPR_TIMER0APBClk      = 40U,          /**< TIMER0 APB clock    */

    GPR_TIMER1APBClk      = 41U,          /**< TIMER1 APB clock    */
    GPR_TIMER2APBClk      = 42U,          /**< TIMER2 APB clock    */
    GPR_TIMER3APBClk      = 43U,          /**< TIMER3 APB clock    */
    GPR_TIMER4APBClk      = 44U,          /**< TIMER4 APB clock    */
    GPR_TIMER5APBClk      = 45U,          /**< TIMER5 APB clock    */

    GPR_WDGFuncClk        = 46U,          /**< WDG Func clock      */
    GPR_WDGAPBClk         = 47U,          /**< WDG APB clock       */
    GPR_USIMFuncClk       = 48U,          /**< USIM Func clock     */
    GPR_USIMAPBClk        = 49U,          /**< USIM APB clock      */
    GPR_EFUSEAPBClk       = 50U,          /**< EFUSE APB clock     */

    GPR_TRNGAPBClk        = 51U,          /**< TRNG APB clock      */

    GPR_BBRXFuncClk       = 56U,          /**< BB RX Func clock    */
    GPR_BBTXFuncClk       = 57U,          /**< BB TX Func clock    */
    GPR_SEQFuncClk        = 58U,          /**< SEQ Func clock      */
    GPR_BCNTClk           = 59U,          /**< BCNT clock          */

    GPR_CoreClk           = 60U,          /**< Core clock          */
    GPR_TRACEFuncClk      = 61U,          /**< TRACE Func clock    */

/*                    Internal use                                 */
    GPR_CLKMFClk          = 64U,          /**< CLK_MF clock       */
    GPR_DMAAHBClk         = 65U,          /**< DMA AHB clock       */
    GPR_DMAAPBClk         = 66U,          /**< DMA APB clock       */
    GPR_GPRAPBClk         = 67U,          /**< GPR APB clock       */

    GPR_ETMAHBClk         = 80U,          /**< ETM AHB clock       */
    GPR_ROMAHBClk         = 81U,          /**< ROM AHB clock       */
    GPR_TPIUAHBClk        = 82U,          /**< TPIU AHB clock      */

    GPR_TRACEAHBClk       = 83U,          /**< TRACE AHB clock     */
    GPR_CACHEAHBClk       = 84U,          /**< CACHE AHB clock     */
    GPR_BBRMIAHBClk       = 85U,          /**< BB RMI AHB clock    */
    GPR_SEQRMIAHBClk      = 86U,          /**< SEQ RMI AHB clock   */
    GPR_ICRMIClk          = 87U,          /**< IC RMI clock        */

    GPR_CIPHERRMIClk      = 88U,          /**< CIPHER RMI clock    */
    GPR_CIPHERAHBClk      = 89U,          /**< CIPHER AHB clock    */
    GPR_MAINFABAHBClk     = 90U,          /**< MAINFAB AHB clock   */
    GPR_SMBAHBClk         = 91U,          /**< SMB AHB clock       */
    GPR_FlashFuncClk      = 92U,          /**< Flash Func clock    */

    GPR_FlashAHBClk       = 93U,          /**< Flash AHB clock     */
    GPR_UNILOGAHBClk      = 94U,          /**< UNILOG AHB clock    */
    GPR_RMIAUTOCG         = 95U,          /**< RMI AUTOCG control  */
    GPR_InvalidClk        = 96U           /**< Invalid clock       */
}clock_ID_t;

/**
 |-----clockId-----|-----bitFieldPos-----|-----bitFieldWidth-----|-----value-----|-----parentClockId-----|
 |------8 bit------|--------5 bit--------|---------5 bit---------|-----6 bit-----|--------8 bit----------|
 Note: parentClockId field is not used in GPR driver, just for being compatile with CLOCK driver
 */
/** Macro to compose clock select value */
#define MAKE_CLOCK_SEL_VALUE(clockId, bitFieldPos, bitFieldWidth, value, parentClockId)   \
                  ((clockId << 24U) | (bitFieldPos << 19U) | (bitFieldWidth << 14U) | value << 8U | parentClockId)

/** Macro to extract clockId from clock select value */
#define GET_CLOCKID_FROM_CLOCK_SEL_VALUE(value)   ((value >> 24U) & 0xFFUL)

/** Macro to extract bitFieldPos from clock select value */
#define GET_BFP_FROM_CLOCK_SEL_VALUE(value)   ((value >> 19U) & 0x1FUL)

/** Macro to extract bitFieldWidth from clock select value */
#define GET_BFW_FROM_CLOCK_SEL_VALUE(value)   ((value >> 14U) & 0x1FUL)

/** Macro to extract value from clock select value */
#define GET_VALUE_FROM_CLOCK_SEL_VALUE(value)   ((value >> 8U) & 0x3FUL)


/** \brief List of all configurable module's functional clock sources */
typedef enum _clock_select
{
    /** Core clock sourced from 204M */
    GPR_CoreClkSel_204M = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 0, GPR_InvalidClk),
    /** Core clock sourced from 102M */
    GPR_CoreClkSel_102M = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 1U, GPR_InvalidClk),
    /** Core clock sourced from 51M */
    GPR_CoreClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 2U, GPR_InvalidClk),
    /** Core clock sourced from 32K  */
    GPR_CoreClkSel_32K  = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 3U, GPR_InvalidClk),

    /** RC clock sourced from 16M */
    GPR_RCClkSel_16M = MAKE_CLOCK_SEL_VALUE(GPR_RCClk, GPR_CLKSEL_RC_CLK_Pos, 2U, 0, GPR_InvalidClk),
    /** RC clock sourced from 8M */
    GPR_RCClkSel_8M = MAKE_CLOCK_SEL_VALUE(GPR_RCClk, GPR_CLKSEL_RC_CLK_Pos, 2U, 1U, GPR_InvalidClk),
    /** RC clock sourced from 4M */
    GPR_RCClkSel_4M = MAKE_CLOCK_SEL_VALUE(GPR_RCClk, GPR_CLKSEL_RC_CLK_Pos, 2U, 2U, GPR_InvalidClk),
    /** RC clock sourced from 2M  */
    GPR_RCClkSel_2M  = MAKE_CLOCK_SEL_VALUE(GPR_RCClk, GPR_CLKSEL_RC_CLK_Pos, 2U, 3U, GPR_InvalidClk),

    /** CLKCAL clock sourced from 102M  */
    GPR_CLKCALClkSel_102M = MAKE_CLOCK_SEL_VALUE(GPR_CLKCALClk, GPR_CLKSEL_CLKCAL_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** CLKCAL clock sourced from 16M  */
    GPR_CLKCALClkSel_16M = MAKE_CLOCK_SEL_VALUE(GPR_CLKCALClk, GPR_CLKSEL_CLKCAL_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** Flash clock sourced from 26M  */
    GPR_FlashClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_FlashFuncClk, GPR_CLKSEL_FLASH_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** Flash clock sourced from CoreClk  */
    GPR_FlashClkSel_CoreClk = MAKE_CLOCK_SEL_VALUE(GPR_FlashFuncClk, GPR_CLKSEL_FLASH_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** I2C0 clock sourced from 26M  */
    GPR_I2C0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_I2C0FuncClk, GPR_CLKSEL_I2C0_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** I2C0 clock sourced from 51M  */
    GPR_I2C0ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_I2C0FuncClk, GPR_CLKSEL_I2C0_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** I2C1 clock sourced from 26M  */
    GPR_I2C1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_I2C1FuncClk, GPR_CLKSEL_I2C1_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** I2C1 clock sourced from 51M  */
    GPR_I2C1ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_I2C1FuncClk, GPR_CLKSEL_I2C1_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** RFFE clock sourced from 26M  */
    GPR_RFFEClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_RFFEFuncClk, GPR_CLKSEL_RFFE_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** RFFE clock sourced from 51M  */
    GPR_RFFEClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_RFFEFuncClk, GPR_CLKSEL_RFFE_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** SPI0 clock sourced from 26M  */
    GPR_SPI0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_SPI0FuncClk, GPR_CLKSEL_SPI0_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** SPI0 clock sourced from 51M  */
    GPR_SPI0ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_SPI0FuncClk, GPR_CLKSEL_SPI0_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** SPI1 clock sourced from 26M  */
    GPR_SPI1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_SPI1FuncClk, GPR_CLKSEL_SPI1_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** SPI1 clock sourced from 51M  */
    GPR_SPI1ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_SPI1FuncClk, GPR_CLKSEL_SPI1_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** UART0 clock sourced from 26M  */
    GPR_UART0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_UART0FuncClk, GPR_CLKSEL_UART0_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** UART0 clock sourced from 51M  */
    GPR_UART0ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_UART0FuncClk, GPR_CLKSEL_UART0_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** UART1 clock sourced from 26M  */
    GPR_UART1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_UART1FuncClk, GPR_CLKSEL_UART1_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** UART1 clock sourced from 51M  */
    GPR_UART1ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_UART1FuncClk, GPR_CLKSEL_UART1_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** UART2 clock sourced from 26M  */
    GPR_UART2ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_UART2FuncClk, GPR_CLKSEL_UART2_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** UART2 clock sourced from 51M  */
    GPR_UART2ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_UART2FuncClk, GPR_CLKSEL_UART2_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** USIM clock sourced from 26M  */
    GPR_USIMClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_USIMFuncClk, GPR_CLKSEL_USIM_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** USIM clock sourced from 51M  */
    GPR_USIMClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_USIMFuncClk, GPR_CLKSEL_USIM_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** WDG clock sourced from 32K  */
    GPR_WDGClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_WDGFuncClk, GPR_CLKSEL_WDG_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** WDG clock sourced from 26M  */
    GPR_WDGClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_WDGFuncClk, GPR_CLKSEL_WDG_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** TIMER0 clock sourced from 32K  */
    GPR_TIMER0ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER0FuncClk, GPR_CLKSEL_TIMER0_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** TIMER0 clock sourced from 26M  */
    GPR_TIMER0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER0FuncClk, GPR_CLKSEL_TIMER0_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** TIMER1 clock sourced from 32K  */
    GPR_TIMER1ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER1FuncClk, GPR_CLKSEL_TIMER1_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** TIMER1 clock sourced from 26M  */
    GPR_TIMER1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER1FuncClk, GPR_CLKSEL_TIMER1_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** TIMER2 clock sourced from 32K  */
    GPR_TIMER2ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER2FuncClk, GPR_CLKSEL_TIMER2_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** TIMER2 clock sourced from 26M  */
    GPR_TIMER2ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER2FuncClk, GPR_CLKSEL_TIMER2_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** TIMER3 clock sourced from 32K  */
    GPR_TIMER3ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER3FuncClk, GPR_CLKSEL_TIMER3_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** TIMER3 clock sourced from 26M  */
    GPR_TIMER3ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER3FuncClk, GPR_CLKSEL_TIMER3_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** TIMER4 clock sourced from 32K  */
    GPR_TIMER4ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER4FuncClk, GPR_CLKSEL_TIMER4_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** TIMER4 clock sourced from 26M  */
    GPR_TIMER4ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER4FuncClk, GPR_CLKSEL_TIMER4_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** TIMER5 clock sourced from 32K  */
    GPR_TIMER5ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER5FuncClk, GPR_CLKSEL_TIMER5_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** TIMER5 clock sourced from 26M  */
    GPR_TIMER5ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER5FuncClk, GPR_CLKSEL_TIMER5_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** Systick clock sourced from 32K  */
    GPR_SystickClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_SystickFuncClk, GPR_CLKSEL_SYSTICK_CLK_Pos, 1U, 0, GPR_InvalidClk),
    /** Systick clock sourced from 26M  */
    GPR_SystickClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_SystickFuncClk, GPR_CLKSEL_SYSTICK_CLK_Pos, 1U, 1U, GPR_InvalidClk),

    /** DMA APB clock sourced from 26M  */
    GPR_DMAAPBClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_DMAAPBClk, GPRRMI_CLKEN_PDMA_PCLK_SEL_Pos, 1U, 0, GPR_InvalidClk),
    /** DMA APB clock sourced from 51M  */
    GPR_DMAAPBClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_DMAAPBClk, GPRRMI_CLKEN_PDMA_PCLK_SEL_Pos, 1U, 1U, GPR_InvalidClk),
} clock_select_t;

/** \brief List of IDs used for sw reset control */
typedef enum _sw_reset_ID
{
    GPR_ResetCache           = 0,            /**< Cache reset              */
    GPR_ResetSSFAB           = 1U,           /**< SSFAB reset              */
    GPR_ResetRMI             = 2U,           /**< RMI reset                */
    GPR_ResetModemRMI        = 3U,           /**< Modem RMI reset          */
    GPR_ResetSEQRMI          = 4U,           /**< SEQ RMI reset            */
    GPR_ResetICRMI           = 5U,           /**< IC RMI reset             */

    GPR_ResetCIPHERRMI       = 6U,           /**< CIPHER RMI domain reset  */
    GPR_ResetCIPHERAHB       = 7U,           /**< CIPHER AHB domain reset  */
    GPR_ResetMAINFAB         = 8U,           /**< MAINFAB reset            */
    GPR_ResetSMB             = 9U,           /**< SMB reset                */
    GPR_ResetUNILOG          = 10U,          /**< UNILOG reset             */

    GPR_ResetFlashFunc       = 11U,          /**< Flash Func domain reset  */
    GPR_ResetFlashAHB        = 12U,          /**< Flash AHB domain reset   */
    GPR_ResetCLKCAL          = 13U,          /**< CLKCAL reset             */
    GPR_ResetAONAPB          = 14U,          /**< AON APB reset            */
    GPR_ResetPMDIGAPB        = 15U,          /**< PMDIG APB reset          */

    GPR_ResetRFDIGAPB        = 16U,          /**< RFDIG APB reset          */
    GPR_ResetGPIO            = 17U,          /**< GPIO reset               */
    GPR_ResetI2C0Func        = 18U,          /**< I2C0 Func domain reset   */
    GPR_ResetI2C1Func        = 19U,          /**< I2C1 Func domain reset   */
    GPR_ResetI2C0APB         = 20U,          /**< I2C0 APB domain reset    */

    GPR_ResetI2C1APB         = 21U,          /**< I2C1 APB domain reset    */
    GPR_ResetPADAPB          = 22U,          /**< PAD APB reset            */
    GPR_ResetRFFEAPB         = 23U,          /**< RFFE APB reset           */
    GPR_ResetRFFEFunc        = 24U,          /**< RFFE Func reset          */
    GPR_ResetSPI0Func        = 25U,          /**< SPI0 Func domain reset   */

    GPR_ResetSPI1Func        = 26U,          /**< SPI1 Func domain reset   */
    GPR_ResetSPI0APB         = 27U,          /**< SPI0 APB domain reset    */
    GPR_ResetSPI1APB         = 28U,          /**< SPI1 APB domain reset    */
    GPR_ResetUART0Func       = 29U,          /**< UART0 Func domain reset  */
    GPR_ResetUART1Func       = 30U,          /**< UART1 Func domain reset  */

    GPR_ResetUART2Func       = 31U,          /**< UART2 Func domain reset  */
    GPR_ResetUART0APB        = 32U,          /**< UART0 APB domain reset   */
    GPR_ResetUART1APB        = 33U,          /**< UART1 APB domain reset   */
    GPR_ResetUART2APB        = 34U,          /**< UART2 APB domain reset   */
    GPR_ResetTIMER0Func      = 35U,          /**< TIMER0 Func domain reset */

    GPR_ResetTIMER1Func      = 36U,          /**< TIMER1 Func domain reset */
    GPR_ResetTIMER2Func      = 37U,          /**< TIMER2 Func domain reset */
    GPR_ResetTIMER3Func      = 38U,          /**< TIMER3 Func domain reset */
    GPR_ResetTIMER4Func      = 39U,          /**< TIMER4 Func domain reset */
    GPR_ResetTIMER5Func      = 40U,          /**< TIMER5 Func domain reset */

    GPR_ResetTIMER0APB       = 41U,          /**< TIMER0 APB domain reset  */
    GPR_ResetTIMER1APB       = 42U,          /**< TIMER1 APB domain reset  */
    GPR_ResetTIMER2APB       = 43U,          /**< TIMER2 APB domain reset  */
    GPR_ResetTIMER3APB       = 44U,          /**< TIMER3 APB domain reset  */
    GPR_ResetTIMER4APB       = 45U,          /**< TIMER4 APB domain reset  */

    GPR_ResetTIMER5APB       = 46U,          /**< TIMER5 APB domain reset  */
    GPR_ResetWDGFunc         = 47U,          /**< WDG Func domain reset    */
    GPR_ResetWDGAPB          = 48U,          /**< WDG APB domain reset     */
    GPR_ResetUSIMFunc        = 49U,          /**< USIM Func domain reset   */
    GPR_ResetUSIMAPB         = 50U,          /**< USIM APB domain reset    */

    GPR_ResetEFUSEFunc       = 51U,          /**< EFUSE Func domain reset  */
    GPR_ResetEFUSEAPB        = 52U,          /**< EFUSE APB domain reset   */
    GPR_ResetTRNGAPB         = 53U,          /**< TRNG APB domain reset    */
    GPR_ResetBBRXFunc        = 55U,          /**< BB RX Func reset         */

    GPR_ResetBBTXFunc        = 56U,          /**< BB TX Func reset         */
    GPR_ResetBBADC           = 57U,          /**< BB ADC reset             */
    GPR_ResetBBDAC           = 58U,          /**< BB DAC reset             */
    GPR_ResetBCNT            = 59U,          /**< BCNT logic reset         */
    GPR_ResetSEQ             = 60U,          /**< SEQ TPU reset            */

    GPR_ResetBBSEQ           = 61U,          /**< BB SEQ reset             */
    GPR_ResetRFSEQ           = 62U,          /**< RF SEQ reset             */
    GPR_ResetSPISAHB         = 63U,          /**< SPIS AHB domain reset    */

    GPR_ResetDMAAHB          = 132U,         /**< DMA AHB domain reset     */
    GPR_ResetDMAAPB          = 133U,         /**< DMA APB domain reset     */
    GPR_ResetGPRAPB          = 134U,         /**< GPR APB domain reset     */
}sw_reset_ID_t;

#endif //__CLOCK_DECLARATION_DEFINED__

/** \brief List of items for dma auto clock gate control */
typedef enum _dma_autocg_cfg
{
    GPR_AutocgDMAAPBEnable    = GPR_PDMAACG_PCLK_Msk,         /**< DMA APB autocg enable    */
    GPR_AutocgDMAAHBEnable    = GPR_PDMAACG_HCLK_Msk,         /**< DMA AHB autocg enable    */
    GPR_AutocgSMBEnable       = GPR_PDMAACG_SMB_Msk,          /**< SMB autocg enable        */
    GPR_AutocgRFDIGEnable     = GPR_PDMAACG_RFDIG_Msk,        /**< RFDIG autocg enable      */
    GPR_AutocgPMDIGEnable     = GPR_PDMAACG_PMDIG_Msk,        /**< PMDIG autocg enable      */
} dma_autocg_cfg_t;

/** \brief List of IDs for memory control */
typedef enum _memctrl_ID
{
    GPR_MemCtrlRF1P         = 0,         /**< RF1P     */
    GPR_MemCtrlRF2P         = 1U,        /**< RF2P     */
    GPR_MemCtrlSR1P         = 2U,        /**< SR1P     */
    GPR_MemCtrlSR2P         = 3U,        /**< SR2P     */
    GPR_MemCtrlROM          = 4U,        /**< ROM      */
} memctrl_ID_t;

/** \brief List of IDs for test pin select */
typedef enum _test_pin
{
    GPR_TESTPIN_USIM         = 0,         /**< USIM     */
    GPR_TESTPIN_CIPHER       = 1U,        /**< CIPHER   */
    GPR_TESTPIN_SEQ          = 2U,        /**< SEQ      */
    GPR_TESTPIN_TX           = 3U,        /**< TX       */
    GPR_TESTPIN_TXDFE        = 4U,        /**< TXDFE    */
    GPR_TESTPIN_ICS          = 5U,        /**< ICS      */
    GPR_TESTPIN_CE           = 6U,        /**< CE       */
    GPR_TESTPIN_DE           = 7U,        /**< DE       */
} test_pin_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
 extern "C" {
#endif

/** \name Clock Configuration */
/* \{ */

/**
  \fn    int32_t GPR_SetClockSrc(clock_ID_t id, clock_select_t select)
  \brief Set clock source for selected module
  \param[in] id          clock item to set
  \param[in] select      select one of clock sources \ref clock_select_t
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
  \note  Use \ref GPR_SetFlashClockSrc to set flash clock source
 */
int32_t GPR_SetClockSrc(clock_ID_t id, clock_select_t select);

/**
  \fn    int32_t GPR_SetClockDiv(clock_ID_t id, uint32 div)
  \brief Set clock divider for selected module
  \param[in] id          clock item to set
  \param[in] div         divider value
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id or div value is set to 0)
  \note  Use \ref GPR_SetFlashClockDiv to set flash clock divider
 */
int32_t GPR_SetClockDiv(clock_ID_t id, uint32_t div);

/**
  \fn    int32_t GPR_ClockEnable(clock_ID_t id)
  \brief Enable clock for selected module
  \param[in] id          clock item to set
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
  \note refer datasheet to check available clock IDs, use \ref GPR_FlashClockEnable to enable flash clock
 */
int32_t GPR_ClockEnable(clock_ID_t id);

/**
  \fn    int32_t GPR_ClockDisable(clock_ID_t id)
  \brief Disable clock for selected module
  \param[in] id          clock item to set
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
  \note refer datasheet to check available clock IDs, use \ref GPR_FlashClockDisable to disable flash clock
 */
int32_t GPR_ClockDisable(clock_ID_t id);

/**
  \fn    void GPR_SetFlashClockSrc(clock_select_t select)
  \brief Set flash functional clock source
  \param[in] select   clock source select, valid value: GPR_FlashClkSel_38M and GPR_FlashClkSel_204M
 */
void GPR_SetFlashClockSrc(clock_select_t select);

/**
  \fn    void GPR_SetFlashClockDiv(uint32_t div)
  \brief Set flash functional clock divider
  \param[in] div         divider value
 */
void GPR_SetFlashClockDiv(uint32_t div);

/**
  \fn    void GPR_FlashClockEnable(clock_ID_t id)
  \brief Enable flash functional or AHB clock
  \param[in] id    flash clock item to set, \ref GPR_FlashFuncClk or \ref GPR_FlashAHBClk
 */
void GPR_FlashClockEnable(clock_ID_t id);

/**
  \fn    void GPR_FlashClockDisable(clock_ID_t id)
  \brief Disable flash functional or AHB clock
  \param[in] id    flash clock item to set, \ref GPR_FlashFuncClk or \ref GPR_FlashAHBClk
 */
void GPR_FlashClockDisable(clock_ID_t id);

/**
  \fn    uint32_t GPR_GetClockFreq(clock_ID_t id)
  \brief Get clock frequency for selected module
  \param[in] id    clock item to get
  \return    clock frequency in unit of HZ
 */
uint32_t GPR_GetClockFreq(clock_ID_t id);

/**
  \fn    GPR_Is51MClockInUse(void)
  \brief Check whether 51M clock is in use
  \return   true or false
 */
bool GPR_Is51MClockInUse(void);

/** \} */

/** \name Reset control */
/* \{ */

/**
  \fn    void GPR_SWReset(sw_reset_ID_t id)
  \brief Reset selected module
  \param[in] id    module to reset
 */
void GPR_SWReset(sw_reset_ID_t id);

/**
  \fn    void GPR_FlashSWReset(sw_reset_ID_t id)
  \brief Reset flash module
  \param[in] id    flash item to reset, \ref GPR_ResetFlashFunc or \ref GPR_ResetFlashAHB
 */
void GPR_FlashSWReset(sw_reset_ID_t id);

/**
  \fn    void GPR_SeqSWReset(void)
  \brief Reset SEQ module
  \param void
 */
void GPR_SeqSWReset(void);

/** \} */

/** \name Misc */
/* \{ */

/**
  \fn    uint32_t GPR_GetChipFullID(void)
  \brief Get chip full ID
  \param void
  \return full chip ID
 */
uint32_t GPR_GetChipFullID(void);

/**
  \fn    uint32_t GPR_GetChipRevID(void)
  \brief Get chip rev ID
  \param void
  \return chip rev ID
 */
uint32_t GPR_GetChipRevID(void);

/**
  \fn    uint32_t GPR_GetChipID(void)
  \brief Get chip ID
  \param void
  \return chip ID
 */
uint32_t GPR_GetChipID(void);

/**
  \fn    void GPR_LockUpActionCtrl(bool enable)
  \brief Enable or disable lockup trigger reset feature
  \param[in] enable   true to enable, false to disable
 */
void GPR_LockUpActionCtrl(bool enable);
/**
  \fn    bool GPR_LockUpActionCheck(void);
  \brief Check lockup status
  \param[in] enable   true for enable, false for disable
 */
bool GPR_LockUpActionCheck(void);
/**
  \fn    void GPR_CacheBypassCtrl(bool enable)
  \brief Enable or disable cache bypass
  \param[in] enable   true to enable, false to disable
 */
void GPR_CacheBypassCtrl(bool enable);

/**
  \fn    void GPR_DMAAutoGateCtrl(uint32_t mask);
  \brief Set DMA auto gate function
  \param[in] mask   Mask of auto clock gates to be set, can be ORed by items list in \ref dma_autocg_cfg_t
 */
void GPR_DMAAutoGateCtrl(uint32_t mask);

/**
  \fn    void GPR_MemCtrl(memctrl_ID_t mem, uint32_t setVaule)
  \brief Memory control for selected item
  \param[in] mem        id to set
  \param[in] setVaule   control value
 */
void GPR_MemCtrl(memctrl_ID_t mem, uint32_t setVaule);

/**
  \fn    void GPR_TestPinSel(test_pin_t pin)
  \brief Select one of test pins
  \param[in] pin        pin to select
 */
void GPR_TestPinSel(test_pin_t pin);

/**
  \fn    void GPR_Initialize(void)
  \brief initialize GPR
  \param void
 */
void GPR_Initialize(void);

/** \} */

/** @} */

#ifdef __cplusplus
}
#endif

/** \}*/

#endif
