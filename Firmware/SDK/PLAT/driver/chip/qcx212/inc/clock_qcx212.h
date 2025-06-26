/****************************************************************************
 *
 * Copy right:   2019-, Copyrigths of Qualcomm Ltd.
 * File name:    clock_qcx212.h
 * Description:  QCX212 clock driver header file
 * History:      Rev1.0   2019-02-20
 *
 ****************************************************************************/

#ifndef _CLOCK_QCX212_H
#define _CLOCK_QCX212_H

#include "qcx212.h"
#include "Driver_common.h"


/**
  \addtogroup clock_interface_gr
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
    GPR_204MClk           = 2U,           /**< 204M clock          */
    GPR_102MClk           = 3U,           /**< 102M clock          */
    GPR_51MClk            = 4U,           /**< 51M clock           */

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

    GPR_CoreClk           = 60U,          /**< Core clock          */
    GPR_32KClk            = 61U,          /**< 32K clock           */
    GPR_CLKMFClk          = 64U,          /**< CLK_MF clock        */
    GPR_DMAAHBClk         = 65U,          /**< DMA AHB clock       */
    GPR_DMAAPBClk         = 66U,          /**< DMA APB clock       */

    GPR_GPRAPBClk         = 67U,          /**< GPR APB clock       */
    GPR_CIPHERRMIClk      = 88U,          /**< CIPHER RMI clock    */
    GPR_CIPHERAHBClk      = 89U,          /**< CIPHER AHB clock    */
    GPR_MAINFABAHBClk     = 90U,          /**< MAINFAB AHB clock   */
    GPR_SMBAHBClk         = 91U,          /**< SMB AHB clock       */

    GPR_InvalidClk        = 96U           /**< Invalid clock       */
}clock_ID_t;

/**
 |-----clockId-----|-----bitFieldPos-----|-----bitFieldWidth-----|-----value-----|-----parentClockId-----|
 |------8 bit------|--------5 bit--------|---------5 bit---------|-----6 bit-----|--------8 bit----------|
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

/** Macro to extract parentClockId from clock select value */
#define GET_PARENTCLOCKID_FROM_CLOCK_SEL_VALUE(value)   (value & 0xFFUL)

/** \brief List of all configurable module's functional clock sources */
typedef enum _clock_select
{
    /** Core clock sourced from 204M */
    GPR_CoreClkSel_204M = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 0, GPR_204MClk),
    /** Core clock sourced from 102M */
    GPR_CoreClkSel_102M = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 1U, GPR_102MClk),
    /** Core clock sourced from 51M */
    GPR_CoreClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 2U, GPR_CLKMFClk),
    /** Core clock sourced from 32K  */
    GPR_CoreClkSel_32K  = MAKE_CLOCK_SEL_VALUE(GPR_CoreClk, GPR_CLKSEL_CCLK_Pos, 2U, 3U, GPR_32KClk),

    /** I2C0 clock sourced from 26M  */
    GPR_I2C0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_I2C0FuncClk, GPR_CLKSEL_I2C0_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** I2C0 clock sourced from 51M  */
    GPR_I2C0ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_I2C0FuncClk, GPR_CLKSEL_I2C0_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** I2C1 clock sourced from 26M  */
    GPR_I2C1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_I2C1FuncClk, GPR_CLKSEL_I2C1_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** I2C1 clock sourced from 51M  */
    GPR_I2C1ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_I2C1FuncClk, GPR_CLKSEL_I2C1_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** RFFE clock sourced from 26M  */
    GPR_RFFEClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_RFFEFuncClk, GPR_CLKSEL_RFFE_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** RFFE clock sourced from 51M  */
    GPR_RFFEClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_RFFEFuncClk, GPR_CLKSEL_RFFE_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** SPI0 clock sourced from 26M  */
    GPR_SPI0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_SPI0FuncClk, GPR_CLKSEL_SPI0_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** SPI0 clock sourced from 51M  */
    GPR_SPI0ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_SPI0FuncClk, GPR_CLKSEL_SPI0_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** SPI1 clock sourced from 26M  */
    GPR_SPI1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_SPI1FuncClk, GPR_CLKSEL_SPI1_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** SPI1 clock sourced from 51M  */
    GPR_SPI1ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_SPI1FuncClk, GPR_CLKSEL_SPI1_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** UART0 clock sourced from 26M  */
    GPR_UART0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_UART0FuncClk, GPR_CLKSEL_UART0_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** UART0 clock sourced from 51M  */
    GPR_UART0ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_UART0FuncClk, GPR_CLKSEL_UART0_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** UART1 clock sourced from 26M  */
    GPR_UART1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_UART1FuncClk, GPR_CLKSEL_UART1_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** UART1 clock sourced from 51M  */
    GPR_UART1ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_UART1FuncClk, GPR_CLKSEL_UART1_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** UART2 clock sourced from 26M  */
    GPR_UART2ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_UART2FuncClk, GPR_CLKSEL_UART2_CLK_Pos, 1U, 0, GPR_CLKMFClk),
    /** UART2 clock sourced from 51M  */
    GPR_UART2ClkSel_51M = MAKE_CLOCK_SEL_VALUE(GPR_UART2FuncClk, GPR_CLKSEL_UART2_CLK_Pos, 1U, 1U, GPR_51MClk),

    /** WDG clock sourced from 32K  */
    GPR_WDGClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_WDGFuncClk, GPR_CLKSEL_WDG_CLK_Pos, 1U, 0, GPR_32KClk),
    /** WDG clock sourced from 26M  */
    GPR_WDGClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_WDGFuncClk, GPR_CLKSEL_WDG_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

    /** TIMER0 clock sourced from 32K  */
    GPR_TIMER0ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER0FuncClk, GPR_CLKSEL_TIMER0_CLK_Pos, 1U, 0, GPR_32KClk),
    /** TIMER0 clock sourced from 26M  */
    GPR_TIMER0ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER0FuncClk, GPR_CLKSEL_TIMER0_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

    /** TIMER1 clock sourced from 32K  */
    GPR_TIMER1ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER1FuncClk, GPR_CLKSEL_TIMER1_CLK_Pos, 1U, 0, GPR_32KClk),
    /** TIMER1 clock sourced from 26M  */
    GPR_TIMER1ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER1FuncClk, GPR_CLKSEL_TIMER1_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

    /** TIMER2 clock sourced from 32K  */
    GPR_TIMER2ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER2FuncClk, GPR_CLKSEL_TIMER2_CLK_Pos, 1U, 0, GPR_32KClk),
    /** TIMER2 clock sourced from 26M  */
    GPR_TIMER2ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER2FuncClk, GPR_CLKSEL_TIMER2_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

    /** TIMER3 clock sourced from 32K  */
    GPR_TIMER3ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER3FuncClk, GPR_CLKSEL_TIMER3_CLK_Pos, 1U, 0, GPR_32KClk),
    /** TIMER3 clock sourced from 26M  */
    GPR_TIMER3ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER3FuncClk, GPR_CLKSEL_TIMER3_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

    /** TIMER4 clock sourced from 32K  */
    GPR_TIMER4ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER4FuncClk, GPR_CLKSEL_TIMER4_CLK_Pos, 1U, 0, GPR_32KClk),
    /** TIMER4 clock sourced from 26M  */
    GPR_TIMER4ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER4FuncClk, GPR_CLKSEL_TIMER4_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

    /** TIMER5 clock sourced from 32K  */
    GPR_TIMER5ClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_TIMER5FuncClk, GPR_CLKSEL_TIMER5_CLK_Pos, 1U, 0, GPR_32KClk),
    /** TIMER5 clock sourced from 26M  */
    GPR_TIMER5ClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_TIMER5FuncClk, GPR_CLKSEL_TIMER5_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

    /** Systick clock sourced from 32K  */
    GPR_SystickClkSel_32K = MAKE_CLOCK_SEL_VALUE(GPR_SystickFuncClk, GPR_CLKSEL_SYSTICK_CLK_Pos, 1U, 0, GPR_32KClk),
    /** Systick clock sourced from 26M  */
    GPR_SystickClkSel_26M = MAKE_CLOCK_SEL_VALUE(GPR_SystickFuncClk, GPR_CLKSEL_SYSTICK_CLK_Pos, 1U, 1U, GPR_CLKMFClk),

} clock_select_t;

/** \brief List of IDs used for sw reset control */
typedef enum _sw_reset_ID
{
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
}sw_reset_ID_t;

#endif // __CLOCK_DECLARATION_DEFINED__

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
 extern "C" {
#endif


/** \name Clock Configuration */
/* \{ */

/**
  \fn    void CLOCK_DriverInit(void);
  \brief Intialize CLOCK driver internal data, must be called before any other APIs
 */
void CLOCK_DriverInit(void);

/**
  \fn    void CLOCK_DriverDeInit(void);
  \brief De-Intialize CLOCK driver
 */
void CLOCK_DriverDeInit(void);

/**
  \fn    int32_t CLOCK_ClockEnable(clock_ID_t id)
  \brief Enable clock for selected module
  \param[in] id          clock item to enable
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
 */
int32_t CLOCK_ClockEnable(clock_ID_t id);

/**
  \fn    void CLOCK_ClockReset(clock_ID_t id)
  \brief Reset clock for selected module
  \param[in] id          clock item to reset
 */
void CLOCK_ClockReset(clock_ID_t id);

/**
  \fn    void CLOCK_ClockDisable(clock_ID_t id)
  \brief Disable clock for selected module
  \param[in] id          clock item to disable
 */
void CLOCK_ClockDisable(clock_ID_t id);

/**
  \fn    int32_t CLOCK_SetClockSrc(clock_ID_t id, clock_select_t select)
  \brief Set clock source for selected module
  \param[in] id          clock item to set
  \param[in] select      select one of clock sources \ref clock_select_t
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
             ARM_DRIVER_ERROR if specific clock has been enabled
 */
int32_t CLOCK_SetClockSrc(clock_ID_t id, clock_select_t select);

/**
  \fn    int32_t CLOCK_SetClockDiv(clock_ID_t id, uint32 div)
  \brief Set clock divider for selected module
  \param[in] id          clock item to set
  \param[in] div         divider value
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id or div value is set to 0)
             ARM_DRIVER_ERROR if specific clock has been enabled
 */
int32_t CLOCK_SetClockDiv(clock_ID_t id, uint32_t div);

/**
  \fn    uint32_t CLOCK_GetClockFreq(clock_ID_t id)
  \brief Get clock frequency for selected module
  \param[in] id    clock item to get
  \return    clock frequency in unit of HZ
 */
uint32_t CLOCK_GetClockFreq(clock_ID_t id);

/** \} */

/** \name HAL Driver declaration */
/* \{ */

int32_t GPR_SetClockSrc(clock_ID_t id, clock_select_t select);
int32_t GPR_SetClockDiv(clock_ID_t id, uint32_t div);
int32_t GPR_ClockEnable(clock_ID_t id);
int32_t GPR_ClockDisable(clock_ID_t id);
uint32_t GPR_GetClockFreq(clock_ID_t id);
void GPR_SWReset(sw_reset_ID_t id);
void GPR_Initialize(void);
void CLOCK_EnableClkRef(void);
void CLOCK_DisableClkRef(void);



/** \} */


#ifdef __cplusplus
}
#endif

/** \}*/

#endif
