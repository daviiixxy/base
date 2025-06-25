/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    wdt_qcx212.h
 * Description:  QCX212 wdt driver header file
 * History:      Rev1.0   2018-07-18
 *
 ****************************************************************************/

#ifndef _WDT_QCX212_H
#define _WDT_QCX212_H

#include "qcx212.h"
#include "Driver_Common.h"

/**
  \addtogroup wdt_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief List of WDT mode */
typedef enum _wdt_mode
{
    WDT_InterruptOnlyMode   = 0U,  /**< Only generate an interrupt upon timeout */
    WDT_InterruptResetMode  = 1U,  /**< Reset upon timeout if the first interrupt is not cleared */
} wdt_mode_t;

/** \brief WDT configuration structure */
typedef struct _wdt_config
{
    wdt_mode_t           mode;
    uint16_t             timeoutValue;
} wdt_config_t;

/** \brief List of WDT interrupt flags */
typedef enum _wdt_interrupt_flags
{
    WDT_InterruptFlag  = WDT_STAT_ISTAT_Msk,  /**< Wdt interrupt flag */
} wdt_interrupt_flags_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/** \name WDT Configuration */
/** \{ */

/**
  \fn    void WDT_GetDefaultConfig(wdt_config_t *config)
  \brief Gets the WDT default configuartion.
         This function sets the configuration structure to default values as below:
  \code
         config->mode = WDT_InterruptOnlyMode;
         config->timeoutValue = 0xFFFF;
  \endcode

  \param[in] config      Pointer to WDT configuration structure
 */
void WDT_GetDefaultConfig(wdt_config_t *config);

/**
  \fn    void WDT_Init(const wdt_config_t *config)
  \brief Initialize WDT
  \param[in] config      Pointer to WDT configuration
 */
void WDT_Init(const wdt_config_t *config);

/**
  \fn    void WDT_DeInit(void)
  \brief Deinitialize WDT
 */
void WDT_DeInit(void);

/** \} */

/** \name WDT Unlock and Kick */
/** \{ */

/**
  \fn    void WDT_Unlock(void)
  \brief Unlocks the WDT register written
 */
void WDT_Unlock(void);

/**
  \fn    void WDT_Kick(void)
  \brief Refreshes WDT counter
 */
void WDT_Kick(void);

/** \} */

/** \name WDT Start and Stop */
/** \{ */

/**
  \fn    void WDT_Start(void)
  \brief Starts WDT counter
 */
void WDT_Start(void);

/**
  \fn    void WDT_Stop(void)
  \brief Stops WDT counter
 */
void WDT_Stop(void);

/** \} */

/** \name WDT Interrupt and Status */
/** \{ */

/**
  \fn    uint32_t WDT_GetInterruptFlags(void)
  \brief Reads WDT interrupt status flags
  \return    Interrupt flags. This is the logical OR of members of the
             enumeration \ref wdt_interrupt_flags_t
 */
uint32_t WDT_GetInterruptFlags(void);

/**
  \fn    void WDT_ClearInterruptFlags(uint32_t mask)
  \brief Clears WDT interrupt flags
  \param[in] mask        Interrupt flags to clear. This is a logic OR of members of the
                         enumeration \ref wdt_interrupt_flags_t
 */
void WDT_ClearInterruptFlags(uint32_t mask);

/**
  \fn    wdt_mode_t WDT_GetMode(void)
  \brief Gets current WDT mode
  \return                WDT mode, see \ref wdt_mode_t
 */
wdt_mode_t WDT_GetMode(void);

/**
  \fn    bool WDT_GetStartStatus(void)
  \brief Checks if WDT is started or stopped
  \return                true if WDT is counting
                         false if WDT is stopped
 */
bool WDT_GetStartStatus(void);

/** \} */

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _WDT_QCX212_H */
