#ifndef __HT_ADC_QCX212_H__
#define __HT_ADC_QCX212_H__

#include "adc_qcx212.h"

void HT_ADC_ChannelInit(adc_channel_t channel, adc_user_t userID, const adc_config_t *config, adc_callback_t callback);
int32_t HT_ADC_StartConversion(adc_channel_t channel, adc_user_t userID);
void HT_ADC_GetDefaultConfig(adc_config_t *config);

#endif /* __HT_ADC_QCX212_H__ */
