/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    pad_qcx212.h
 * Description:  QCX212 pad driver header file
 * History:      Rev1.0   2018-11-14
 *               Rev1.1   2019-09-06       Pull up/down option rename
 *
 ****************************************************************************/

#ifndef _PAD_QCX212_H_
#define _PAD_QCX212_H_

#include "qcx212.h"
#include "Driver_Common.h"


/**
  \addtogroup pad_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief PAD pin mux selection */
typedef enum _pad_mux
{
    PAD_MuxAlt0 = 0U,             /**< Chip-specific */
    PAD_MuxAlt1 = 1U,             /**< Chip-specific */
    PAD_MuxAlt2 = 2U,             /**< Chip-specific */
    PAD_MuxAlt3 = 3U,             /**< Chip-specific */
    PAD_MuxAlt4 = 4U,             /**< Chip-specific */
    PAD_MuxAlt5 = 5U,             /**< Chip-specific */
    PAD_MuxAlt6 = 6U,             /**< Chip-specific */
    PAD_MuxAlt7 = 7U,             /**< Chip-specific */
} pad_mux_t;


/** \brief Internal pull-up resistor configuration */
enum _pad_pull_up
{
    PAD_PullUpDisable = 0U,      /**< Internal pull-up resistor is disabled */
    PAD_PullUpEnable  = 1U,      /**< Internal pull-up resistor is enabled */
};

/** \brief Internal pull-down resistor configuration */
enum _pad_pull_down
{
    PAD_PullDownDisable = 0U,      /**< Internal pull-down resistor is disabled */
    PAD_PullDownEnable  = 1U,      /**< Internal pull-down resistor is enabled */
};

/** \brief Pull feature selection */
enum _pad_pull_sel
{
    PAD_PullAuto      = 0U,      /**< Pull up/down is controlled by muxed alt function */
    PAD_PullInternal  = 1U,      /**< Use internal pull-up/down resistor */
};

/** \brief Input buffer enable/disable */
enum _pad_input_buffer
{
    PAD_InputBufferDisable = 0U,     /**< Input Buffer is disabled */
    PAD_InputBufferEnable  = 1U,     /**< Input Buffer is enabled */
};

/** \brief Configures pull feature */
typedef enum _pad_pull_config
{
    PAD_InternalPullUp   = 0U,  /**< select internal pull up */
    PAD_InternalPullDown = 1U,  /**< select internal pull down */
    PAD_AutoPull         = 2U,  /**< Pull up/down is controlled by muxed alt function */
} pad_pull_config_t;

/** \brief PAD configuration structure */
typedef struct _pad_config
{
    uint32_t                                    : 4;
    uint32_t         mux                        : 3;   /**< Pad mux configuration */
    uint32_t                                    : 1;
    uint32_t         pullUpEnable               : 1;   /**< Enable pull-up */
    uint32_t         pullDownEnable             : 1;   /**< Enable pull-down */
    uint32_t         pullSelect                 : 1;   /**< Pull select, external or internal control */
    uint32_t                                    : 2;
    uint32_t         inputBufferEnable          : 1;   /**< Enable/disable input buffer */
    uint32_t                                    : 18;
} pad_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/** \name PAD Driver Initialization */
/** \{ */

/**
  \fn    void PAD_DriverInit(void);
  \brief Intialize PAD driver internal data, must be called before any other APIs
 */
void PAD_DriverInit(void);

/**
  \fn    void PAD_DriverInit(void);
  \brief De-Intialize PAD driver, disable PAD clock and perform some clearups
 */
void PAD_DriverDeInit(void);

/** \} */

/** \name Configuration */
/* \{ */

/**
  \fn    void PAD_GetDefaultConfig(pad_config_t *config)
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
void PAD_GetDefaultConfig(pad_config_t *config);

/**
  \fn    void PAD_SetPinConfig(uint32_t pin, const pad_config_t *config)
  \brief Sets the pad PCR register
  \param pin       PAD pin number
  \param config    Pointer to PAD configuration structure
 */
void PAD_SetPinConfig(uint32_t pin, const pad_config_t *config);

/**
  \fn    void PAD_SetPinMux(uint32_t pin, pad_mux_t mux)
  \brief Configures pin mux
  \param pin       PAD pin number
  \param mux       pin signal source selection
 */
void PAD_SetPinMux(uint32_t pin, pad_mux_t mux);

/**
  \fn    void PAD_EnablePinInputBuffer(uint32_t pin, bool enable)
  \brief Enable/disable pin's input buffer
  \param pin       PAD pin number
  \param enable    true to enable, false to disable
 */
void PAD_EnablePinInputBuffer(uint32_t pin, bool enable);

/**
  \fn    void PAD_SetPinPullConfig(uint32_t pin, pad_pull_config_t config)
  \brief Configures pin's pull feature
  \param pin       PAD pin number
  \param config    PAD pin pull configuration
 */
void PAD_SetPinPullConfig(uint32_t pin, pad_pull_config_t config);

/** \} */

/** \}*/

#if defined(__cplusplus)
}
#endif

#endif /* _PAD_QCX212_H_ */
