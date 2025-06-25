#ifndef __HT_PAD_QCX212_H__
#define __HT_PAD_QCX212_H__

#include "pad_qcx212.h"

/**
  \fn    void HT_PAD_GetDefaultConfig(pad_config_t *config)
  \brief Gets the PAD default configuartion
         This function sets the configuration structure to default values as below:
  \code
         config->mux = PAD_MuxAlt0;
         config->inputBufferEnable = PAD_InputBufferDisable;
         config->pullSelect = PAD_PullAuto;
         config->pullUpEnable = PAD_PullUpDisable;
         config->pullDownEnable = PAD_PullDownDisable;
  \endcode
  \param config Pointer to PAD configuration structure
 */
void HT_PAD_GetDefaultConfig(pad_config_t *config);

/**
  \fn    void HT_PAD_SetPinConfig(uint32_t pin, const pad_config_t *config)
  \brief Sets the pad PCR register
  \param pin       PAD pin number
  \param config    Pointer to PAD configuration structure
 */
void HT_PAD_SetPinConfig(uint32_t pin, const pad_config_t *config);

/**
  \fn    void HT_PAD_SetPinMux(uint32_t pin, PAD_mux_t mux)
  \brief Configures pin mux
  \param pin       PAD pin number
  \param mux       pin signal source selection
 */
void HT_PAD_SetPinMux(uint32_t pin, pad_mux_t mux);

#endif /* __HT_PAD_QCX212_H__ */
