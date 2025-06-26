/****************************************************************************
 *
 * Copy right:   2019-, Copyrigths of Qualcomm Ltd.
 * File name:    adc_qcx212.h
 * Description:  QCX212 adc driver header file
 * History:      Rev1.0   2019-03-18
 *               Rev1.1   2019-07-30    vbat resdiv ratio update
 *               Rev1.2   2019-12-11    Reimplement driver to support multi-users conversion
 *
 ****************************************************************************/

#ifndef _ADC_QCX212_H
#define _ADC_QCX212_H

#include "qcx212.h"
#include "Driver_Common.h"

/**
  \addtogroup adc_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief List of ADC clock source */
typedef enum _adc_clock_source
{
    ADC_ClockSourceDCXO   = 0U,  /**< ADC clock sourced from DCXO */
    ADC_ClockSourceRC16M  = 1U,  /**< ADC clock sourced from RC16M */
} adc_clock_source_t;

/** \brief List of ADC clock source divider */
typedef enum _adc_clock_divider
{
    ADC_ClockDiv4   = 0U,  /**< ADC clock is divided by 4 from input clock */
    ADC_ClockDiv8   = 1U,  /**< ADC clock is divided by 8 from input clock */
    ADC_ClockDiv16  = 2U,  /**< ADC clock is divided by 16 from input clock */
} adc_clock_divider_t;

/** \brief List of ADC channels */
typedef enum _adc_channel
{
    ADC_ChannelThermal          = 0,      /**< ADC Thermal channel */
    ADC_ChannelVbat             = 1,      /**< ADC VBAT channel */
    ADC_ChannelAio4             = 2,      /**< ADC AIO4 channel */
    ADC_ChannelAio3             = 3,      /**< ADC AIO3 channel */
    ADC_ChannelAio2             = 4,      /**< ADC AIO2 channel */
    ADC_ChannelAio1             = 5,      /**< ADC AIO1 channel */
} adc_channel_t;

/** \brief List of AIO resdiv select options */
typedef enum _adc_aio_resdiv_ratio
{
    ADC_AioResDivRatio1          = 0U,  /**< ADC AIO RESDIV select as VIN */
    ADC_AioResDivRatio14Over16   = 1U,  /**< ADC AIO RESDIV select as 14/16 VIN */
    ADC_AioResDivRatio12Over16   = 2U,  /**< ADC AIO RESDIV select as 12/16 VIN */
    ADC_AioResDivRatio10Over16   = 3U,  /**< ADC AIO RESDIV select as 10/16 VIN */
    ADC_AioResDivRatio8Over16    = 4U,  /**< ADC AIO RESDIV select as 8/16 VIN */
    ADC_AioResDivRatio7Over16    = 5U,  /**< ADC AIO RESDIV select as 7/16 VIN */
    ADC_AioResDivRatio6Over16    = 6U,  /**< ADC AIO RESDIV select as 6/16 VIN */
    ADC_AioResDivRatio5Over16    = 7U,  /**< ADC AIO RESDIV select as 5/16 VIN */
    ADC_AioResDivRatio4Over16    = 8U,  /**< ADC AIO RESDIV select as 4/16 VIN */
    ADC_AioResDivRatio3Over16    = 9U,  /**< ADC AIO RESDIV select as 3/16 VIN */
    ADC_AioResDivRatio2Over16    = 10U, /**< ADC AIO RESDIV select as 2/16 VIN */
    ADC_AioResDivRatio1Over16    = 11U, /**< ADC AIO RESDIV select as 1/16 VIN */
} adc_aio_resdiv_ratio_t;

/** \brief List of VBAT resdiv select options */
typedef enum _adc_vbat_resdiv_ratio
{
    ADC_VbatResDivRatio8Over16     = 0U,  /**< ADC AIO RESDIV select as 8/16 VBAT */
    ADC_VbatResDivRatio7Over16     = 1U,  /**< ADC AIO RESDIV select as 7/16 VBAT */
    ADC_VbatResDivRatio6Over16     = 2U,  /**< ADC AIO RESDIV select as 6/16 VBAT */
    ADC_VbatResDivRatio5Over16     = 3U,  /**< ADC AIO RESDIV select as 5/16 VBAT */
    ADC_VbatResDivRatio4Over16     = 4U,  /**< ADC AIO RESDIV select as 4/16 VBAT */
    ADC_VbatResDivRatio3Over16     = 5U,  /**< ADC AIO RESDIV select as 3/16 VBAT */
    ADC_VbatResDivRatio2Over16     = 6U,  /**< ADC AIO RESDIV select as 2/16 VBAT */
    ADC_VbatResDivRatio1Over16     = 7U,  /**< ADC AIO RESDIV select as 1/16 VBAT */
} adc_vbat_resdiv_ratio_t;

/** \brief List of themal input select options */
typedef enum _adc_thermal_input
{
    ADC_ThermalInputDisable  = 0U,  /**< ADC Thermal input disabled */
    ADC_ThermalInputAio4     = 1U,  /**< ADC Thermal input select as AIO4 */
    ADC_ThermalInputVbat     = 2U,  /**< ADC Thermal input select as VBAT */
} adc_thermal_input_t;

/** \brief ADC channel configuration */
typedef union _adc_channel_config
{
    adc_aio_resdiv_ratio_t  aioResDiv;     /**< resdiv setting, valid only for AIO channel */
    adc_vbat_resdiv_ratio_t vbatResDiv;    /**< resdiv setting, valid only for VBAT channel */
    adc_thermal_input_t     thermalInput;  /**< Input source select, valid only for Thermal channel */
} adc_channel_config_t;

/** \brief ADC configuration structure */
typedef struct _adc_config
{
    adc_clock_source_t              clockSource;                 /**< ADC work clock source setting */
    adc_clock_divider_t             clockDivider;                /**< ADC work clock source divider setting */
    adc_channel_config_t            channelConfig;               /**< ADC channel configuration */
} adc_config_t;

/** \brief List of ADC channel users, used to compose logical channel combining with ADC physical channel
    each channel can be occupied by these users at the same time, conversion request gets serviced one by one in FIFO ordering.
    */
typedef enum _adc_user
{
    ADC_UserPHY    = 0U,  /**< Internal user ID for PHY */
    ADC_UserPLAT   = 1U,  /**< Internal user ID for PLAT */
    ADC_UserAPP    = 2U,  /**< user ID for APP */
    ADC_UserMax           /**< Total number of users for one channel */
} adc_user_t;


/**
  \brief Defines callback function prototype.
         Callback function will be called in ADC interrupt service routine after sample completes
  \param result ADC sample result
 */
typedef void (*adc_callback_t)(uint32_t result);

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/** \name ADC Configuration */
/** \{ */

/**
  \fn        void ADC_GetDefaultConfig(adc_config_t *config)
  \brief     Gets the ADC default configuartion.
             This function sets the configuration structure to default values as below:
  \code
             config->clockSource = ADC_ClockSourceDCXO;
             config->clockDivider = ADC_ClockDiv8;
             config->channalConfig.aioResDiv = ADC_AioResDivRatio1;  // Note: channelConfig field is union
  \endcode

  \param[in] config      Pointer to ADC configuration structure
 */
void ADC_GetDefaultConfig(adc_config_t *config);

/**
  \fn        void ADC_ChannelInit(adc_channel_t channel, const adc_config_t *config, adc_callback_t callback)
  \brief     Initialize ADC specific channel
  \param[in] channel     ADC physical channel to be configured
  \param[in] userID      user ID of specific channel, customer user is assigned with ADC_UserAPP, used to compose logical channel combining with channel parameter
  \param[in] config      Pointer to ADC configuration
  \param[in] callback    Function to be called when ADC conversion completes
 */
void ADC_ChannelInit(adc_channel_t channel, adc_user_t userID, const adc_config_t *config, adc_callback_t callback);

/**
  \fn        void ADC_ChannelDeInit(adc_channel_t channel)
  \brief     Deinitialize ADC channel
  \param[in] channel     physical channel to be de-initialized, configuration of specific logical channel is invalid after this API call.
  \param[in] userID      user ID of specific channel, customer user is assigned with ADC_UserAPP, used to compose logical channel combining with channel parameter
 */
void ADC_ChannelDeInit(adc_channel_t channel, adc_user_t userID);

/**
  \fn        void ADC_StartConversion(uint32_t channels)
  \brief     Starts ADC conversion. Conversion is performed imediately when ADC is free, otherwise, the start request is put into a request queue and will be serviced later.

  \param[in] channel     ADC physical channel to converse
  \param[in] userID      user ID of specific channel, customer user is assigned with ADC_UserAPP, used to compose logical channel combining with channel parameter
  \return                0 on success, -1 if request queue is full, -2 if channel has not been initialized yet
  \note      The frequency of ADC work clock func_clk is adc_clock_source_t / adc_clock_divider_t / 16.
 */
int32_t ADC_StartConversion(adc_channel_t channel, adc_user_t userID);

/** \} */

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _ADC_QCX212_H */
