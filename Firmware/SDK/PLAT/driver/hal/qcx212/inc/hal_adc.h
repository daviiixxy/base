/****************************************************************************
 *
 * Copy right:   2019-, Copyrigths of Qualcomm Ltd.
 * File name:    hal_adc.h
 * Description:  QCX212 adc hal driver header file
 * History:      Rev1.0   2019-12-12
 *               Rev1.1   2020-02-29  Add api to get internal thermal temperature
 *               Rev1.2   2020-07-17  Add conversion protection for reentry issue
 *
 ****************************************************************************/

#ifndef _HAL_ADC_H
#define _HAL_ADC_H

#include "stdint.h"

/**
  \addtogroup hal_adc_interface_gr
  \{
 */

/**
  \brief Calibarte ADC raw sample code
  \param[in] input     ADC conversion raw register value
  \return              calibrated voltage in unit of mV
 */
uint32_t HAL_ADC_CalibrateRawCode(uint32_t input);

/**
  \brief Convert ADC thermal channel raw sample to temperature in unit of degree centigrade
  \param[in] input     ADC thermal channel register value
  \return              temperature in unit of centidegree, if EFUSE ratio value is invalid, 0x7FFFFFFF is returned
  */
int32_t HAL_ADC_ConvertThermalRawCodeToTemperature(uint32_t input);

/**
  \brief Get Vbat voltage in unit of mV in given time
  \param[in] timeout_ms  timeout value in unit of ms
  \return                error code or calibrated Vbat voltage
                         - -256: previous conversion is ongoing
                         - -2  : timeout
                         - -1  : other errors
                         - > 0 : calibrated Vbat voltage in unit of mV
  \note  This API shall only be used in task context since semphore is used for synchronization
 */
int32_t HAL_ADC_SampleVbatVoltage(uint32_t timeout_ms);

/**
  \brief Get ADC thermal temperature in unit of degree centigrade in given time
  \param[in]     timeout_ms      timeout value in unit of ms
  \param[in,out] temperatruePtr  pointer to temperature
  \return                error code
                         - -256: previous conversion is ongoing
                         - -2  : timeout
                         - -1  : other errors
  \note  This API shall only be used in task context since semphore is used for synchronization
 */
int32_t HAL_ADC_GetThermalTemperature(uint32_t timeout_ms, int32_t* temperatruePtr);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _HAL_ADC_H */
