#ifndef __HT_CLOCK_QCX212_H__
#define __HT_CLOCK_QCX212_H__

#include "qcx212.h"
#include "Driver_common.h"
#include "clock_qcx212.h"

/**
  \fn    void HT_CLOCK_DriverInit(void);
  \brief Intialize CLOCK driver internal data, must be called before any other APIs
 */
void HT_CLOCK_DriverInit(void);

/**
  \fn    void HT_CLOCK_DriverDeInit(void);
  \brief De-Intialize CLOCK driver
 */
void HT_CLOCK_DriverDeInit(void);

/**
  \fn    int32_t HT_CLOCK_ClockEnable(clock_ID_t id)
  \brief Enable clock for selected module
  \param[in] id          clock item to enable
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
 */
int32_t HT_CLOCK_ClockEnable(clock_ID_t id);

/**
  \fn    void HT_CLOCK_ClockReset(clock_ID_t id)
  \brief Reset clock for selected module
  \param[in] id          clock item to reset
 */
void HT_CLOCK_ClockReset(clock_ID_t id);

/**
  \fn    void HT_CLOCK_ClockDisable(clock_ID_t id)
  \brief Disable clock for selected module
  \param[in] id          clock item to disable
 */
void HT_CLOCK_ClockDisable(clock_ID_t id);

/**
  \fn    int32_t HT_CLOCK_SetClockSrc(clock_ID_t id, clock_select_t select)
  \brief Set clock source for selected module
  \param[in] id          clock item to set
  \param[in] select      select one of clock sources \ref clock_select_t
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id)
             ARM_DRIVER_ERROR if specific clock has been enabled
 */
int32_t HT_CLOCK_SetClockSrc(clock_ID_t id, clock_select_t select);

/**
  \fn    int32_t CLOCK_SetClockDiv(clock_ID_t id, uint32 div)
  \brief Set clock divider for selected module
  \param[in] id          clock item to set
  \param[in] div         divider value
  \return    ARM_DRIVER_OK if the setting is successful
             ARM_DRIVER_ERROR_PARAMETER on parameter check failure(setting is not available for specified clock id or div value is set to 0)
             ARM_DRIVER_ERROR if specific clock has been enabled
 */
int32_t HT_CLOCK_SetClockDiv(clock_ID_t id, uint32_t div);

/**
  \fn    uint32_t CLOCK_GetClockFreq(clock_ID_t id)
  \brief Get clock frequency for selected module
  \param[in] id    clock item to get
  \return    clock frequency in unit of HZ
 */
uint32_t HT_CLOCK_GetClockFreq(clock_ID_t id);

/** \} */

/** \name HAL Driver declaration */
/* \{ */

int32_t HT_GPR_SetClockSrc(clock_ID_t id, clock_select_t select);
int32_t HT_GPR_SetClockDiv(clock_ID_t id, uint32_t div);
int32_t HT_GPR_ClockEnable(clock_ID_t id);
int32_t HT_GPR_ClockDisable(clock_ID_t id);
uint32_t HT_GPR_GetClockFreq(clock_ID_t id);
void HT_GPR_SWReset(sw_reset_ID_t id);
void HT_GPR_Initialize(void);
void HT_CLOCK_EnableClkRef(void);
void HT_CLOCK_DisableClkRef(void);



/** \} */


#ifdef __cplusplus
}
#endif

/** \}*/

#endif /* __HT_CLOCK_QCX212_H__ */
