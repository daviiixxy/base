/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    timer_qcx212.h
 * Description:  QCX212 timer driver header file
 * History:      Rev1.0   2018-07-18
 *               Rev1.1   2019-10-24       Fix pwm period and duty cycle setting bug
 *
 ****************************************************************************/

#ifndef _TIMER_QCX212_H
#define _TIMER_QCX212_H

#include "qcx212.h"
#include "Driver_Common.h"

/**
  \addtogroup timer_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief List of TIMER clock source */
typedef enum _timer_clock_source
{
    TIMER_InternalClock  = 0U,  /**< Internal clock */
    TIMER_ExternalClock  = 1U,  /**< External clock */
} timer_clock_source_t;

/** \brief List of TIMER match value select */
typedef enum _timer_match_select
{
    TIMER_Match0Select    = 0U,  /**< Select Match0 */
    TIMER_Match1Select    = 1U,  /**< Select Match1 */
    TIMER_Match2Select    = 2U,  /**< Select Match2 */
} timer_match_select_t;

/** \brief List of TIMER reload option, counter will be reloaded to init value upon reach it */
typedef enum _timer_reload_option
{
    TIMER_ReloadDisabled    = 0U,  /**< Counter will run freely */
    TIMER_ReloadOnMatch0    = 1U,  /**< Counter will be reloaded on reaching match0 value */
    TIMER_ReloadOnMatch1    = 2U,  /**< Counter will be reloaded on reaching match1 value */
    TIMER_ReloadOnMatch2    = 3U,  /**< Counter will be reloaded on reaching match1 value */
} timer_reload_option_t;

/** \brief PWM configuration structure */
typedef struct _timer_pwm_config
{
    uint32_t pwmFreq_HZ;             /**< PWM signal frequency in HZ */
    uint32_t srcClock_HZ;            /**< TIMER counter clock in HZ */
    uint32_t dutyCyclePercent;       /**< PWM pulse width, the valid range is 0 to 100 */
} timer_pwm_config_t;

/** \brief TIMER configuration structure */
typedef struct _timer_config
{
    timer_clock_source_t  clockSource;     /**< Clock source */
    timer_reload_option_t reloadOption;    /**< Reload option */
    uint32_t              initValue;       /**< Counter init value */
    uint32_t              match0;          /**< Match0 value */
    uint32_t              match1;          /**< Match1 value */
    uint32_t              match2;          /**< Match2 value */
} timer_config_t;

/** \brief TIMER interrupt configuration */
typedef enum _timer_interrupt_config
{
    TIMER_InterruptDisabled    = 0U,  /**< Disable interrupt */
    TIMER_InterruptLevel       = 1U,  /**< Level interrupt, a high level interrupt signal is generated */
    TIMER_InterruptPulse       = 2U,  /**< Pulse interrupt, a pulse of one clock width
                                           is generated after counter matches */
} timer_interrupt_config_t;


/** \brief List of TIMER interrupts */
typedef enum _timer_interrupt_enable
{
    TIMER_Match0InterruptEnable  = TIMER_TCTLR_IE_0_Msk,  /**< Match0 interrupt */
    TIMER_Match1InterruptEnable  = TIMER_TCTLR_IE_1_Msk,  /**< Match1 interrupt */
    TIMER_Match2InterruptEnable  = TIMER_TCTLR_IE_2_Msk,  /**< Match2 interrupt */
} timer_interrupt_enable_t;

/** \brief List of TIMER interrupt flags */
typedef enum _timer_interrupt_flags
{
    TIMER_Match0InterruptFlag  = TIMER_TSR_ICLR_0_Msk,  /**< Match0 interrupt flag */
    TIMER_Match1InterruptFlag  = TIMER_TSR_ICLR_1_Msk,  /**< Match1 interrupt flag */
    TIMER_Match2InterruptFlag  = TIMER_TSR_ICLR_2_Msk,  /**< Match2 interrupt flag */
} timer_interrupt_flags_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/** \name TIMER Driver Initialization */
/** \{ */

/**
  \fn    void TIMER_DriverInit(void);
  \brief Intialize TIMER driver internal data, must be called before any other APIs
 */
void TIMER_DriverInit(void);

/** \} */

/** \name TIMER Configuration */
/** \{ */

/**
  \fn    void TIMER_GetDefaultConfig(timer_config_t *config)
  \brief Gets the TIMER default configuartion.
         This function sets the configuration structure to default values as below:
  \code
         config->clockSource = TIMER_InternalClock;
         config->reloadOption = TIMER_ReloadOnMatch1;
         config->initValue = 0;
         config->match0 = 0x10000 >> 1;
         config->match1 = 0x10000;
         config->match2 = 0xFFFFFFFF;
  \endcode

  \param[in] config      Pointer to TIMER configuration structure
 */
void TIMER_GetDefaultConfig(timer_config_t *config);

/**
  \fn    void TIMER_Init(uint32_t instance, const timer_config_t *config)
  \brief Intialize TIMER
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] config      Pointer to TIMER configuration
  \note      PWM out is disabled after this function's call, use \ref TIMER_SetupPwm function to eable PWM
 */
void TIMER_Init(uint32_t instance, const timer_config_t *config);

/**
  \fn    void TIMER_DeInit(uint32_t instance)
  \brief Deintialize TIMER
  \param[in] instance    TIMER instance number (0, 1, ...)
 */
void TIMER_DeInit(uint32_t instance);

/**
  \fn    void TIMER_SetMatch(uint32_t instance, timer_match_select_t match)
  \brief Sets one of TIMER match values
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] matchNum    TIMER match select
  \param[in] matchValue  TIMER match value
 */
void TIMER_SetMatch(uint32_t instance, timer_match_select_t matchNum, uint32_t matchValue);

/**
  \fn    void TIMER_SetMatch(uint32_t instance, timer_match_select_t match)
  \brief Sets TIMER counter initial value
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] initValue   TIMER initial value
 */
void TIMER_SetInitValue(uint32_t instance, uint32_t initValue);

/**
  \fn    void TIMER_SetMatch(uint32_t instance, timer_match_select_t match)
  \brief Sets TIMER counter reload option
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] option      TIMER counter reload option
 */
void TIMER_SetReloadOption(uint32_t instance, timer_reload_option_t option);

/** \} */

/** \name TIMER Counter */
/** \{ */

/**
  \fn    void TIMER_Start(uint32_t instance)
  \brief Starts TIMER counter
  \param[in] instance    TIMER instance number (0, 1, ...)
 */
void TIMER_Start(uint32_t instance);

/**
  \fn    void TIMER_Stop(uint32_t instance)
  \brief Stops TIMER counter
  \param[in] instance    TIMER instance number (0, 1, ...)
 */
void TIMER_Stop(uint32_t instance);

/**
  \fn    uint32_t TIMER_GetCount(uint32_t instance)
  \brief Reads current TIMER counter value
  \param[in] instance    TIMER instance number (0, 1, ...)
  \return                current TIMER counter value
 */
uint32_t TIMER_GetCount(uint32_t instance);

/** \} */

/** \name TIMER PWM */
/** \{ */

/**
  \fn    int32_t TIMER_SetupPwm(uint32_t instance, const timer_pwm_config_t *config)
  \brief Configures the PWM signals period, mode, etc.
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] config      Pointer to PWM parameter
  \return    ARM_DRIVER_OK if the PWM setup is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure
 */
int32_t TIMER_SetupPwm(uint32_t instance, const timer_pwm_config_t *config);

/**
  \fn    void TIMER_UpdatePwmDutyCycle(uint32_t instance, uint32_t dutyCyclePercent)
  \brief Updates the duty cycle of PWM signal
  \param[in] instance              TIMER instance number (0, 1, ...)
  \param[in] dutyCyclePercent      New PWM pulse width, value shall be between 0 to 100,
                                   if the value exceeds 100, dutyCyclePercent is set to 100.
 */
void TIMER_UpdatePwmDutyCycle(uint32_t instance, uint32_t dutyCyclePercent);

/** \} */

/** \name TIMER Interrupt */
/** \{ */

/**
  \fn    void TIMER_InterruptConfig(uint32_t instance, TIMER_match_select_t match, timer_interrupt_config_t config)
  \brief Configures the selected TIMER interrupt
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] match       TIMER match select
  \param[in] config      TIMER interrupt configuration
  */
void TIMER_InterruptConfig(uint32_t instance, timer_match_select_t match, timer_interrupt_config_t config);

/**
  \fn    timer_interrupt_config_t TIMER_GetInterruptConfig(uint32_t instance, timer_match_select_t match)
  \brief Gets current configuration of the selected TIMER interrupt
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] match       TIMER match select
  \return                Current TIMER interrupt configuration
  */
timer_interrupt_config_t TIMER_GetInterruptConfig(uint32_t instance, timer_match_select_t match);

/**
  \fn    uint32_t TIMER_GetInterruptFlags(uint32_t instance)
  \brief Reads TIMER interrupt status flags
  \param[in] instance    TIMER instance number (0, 1, ...)
  \return    Interrupt flags. This is the logical OR of members of the
             enumeration \ref timer_interrupt_flags_t
 */
uint32_t TIMER_GetInterruptFlags(uint32_t instance);

/**
  \fn    void TIMER_ClearInterruptFlags(uint32_t instance, uint32_t mask)
  \brief Clears TIMER interrupt flags
  \param[in] instance    TIMER instance number (0, 1, ...)
  \param[in] mask        Interrupt flags to clear. This is a logic OR of members of the
                         enumeration \ref timer_interrupt_flags_t
 */
void TIMER_ClearInterruptFlags(uint32_t instance, uint32_t mask);

/**
  \fn    void TIMER_Netlight_Enable(uint32_t instance)
  \brief Set Netlight Enable, called by user in bsp_custom.c to define specific timer instance for netlight
  \param[in] instance    TIMER instance number (0, 1, ...)
 */
void TIMER_Netlight_Enable(uint8_t instance);

/** \} */

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _TIMER_QCX212_H */
