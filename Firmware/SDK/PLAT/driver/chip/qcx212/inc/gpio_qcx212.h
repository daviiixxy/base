 /****************************************************************************
  *
  * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
  * File name:    gpio_qcx212.h
  * Description:  QCX212 gpio driver header file
  * History:      Rev1.0   2018-07-12
  *
  ****************************************************************************/

#ifndef _GPIO_QCX212_H
#define _GPIO_QCX212_H

#include "qcx212.h"
#include "Driver_Common.h"

/**
  \addtogroup gpio_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief GPIO pin direction */
typedef enum _gpio_pin_direction
{
    GPIO_DirectionInput  = 0U,  /**< Set pin as input */
    GPIO_DirectionOutput = 1U,  /**< Set pin as output */
} gpio_pin_direction_t;

/** \brief GPIO pin interrupt configuration */
typedef enum _gpio_interrupt_config
{
    GPIO_InterruptDisabled    = 0U,  /**< Disable interrupt */
    GPIO_InterruptLowLevel    = 1U,  /**< Low-level interrupt */
    GPIO_InterruptHighLevel   = 2U,  /**< High-level interrupt */
    GPIO_InterruptFallingEdge = 3U,  /**< Falling edge interrupt */
    GPIO_InterruptRisingEdge  = 4U,  /**< Rising edge interrupt */
} gpio_interrupt_config_t;

/** \brief GPIO pin configuration structure */
typedef struct _gpio_pin_config
{
    gpio_pin_direction_t pinDirection; /**< GPIO direction, input or output */
    union
    {
        gpio_interrupt_config_t    interruptConfig;   /**< Pin's interrupt configuration, valid when pinDirection is input */
        uint32_t                   initOutput;        /**< Initial pin output value, valid when pinDirection is output*/
    } misc;
} gpio_pin_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/** \name GPIO Driver Initialization */
/** \{ */

/**
  \fn    void GPIO_DriverInit(void);
  \brief Intialize GPIO driver internal data
  \note  It is not necessarty to call this function before using GPIO driver since it has been
         called in \ref GPIO_PinConfig() api.
 */
void GPIO_DriverInit(void);

/**
  \fn    void GPIO_DriverDeInit(void);
  \brief De-Intialize GPIO driver, disable GPIO clock and perform some clearups
 */
void GPIO_DriverDeInit(void);

/** \} */

/** \name GPIO Configuration */
/** \{ */

/**
  \fn    void GPIO_PinConfig(uint32_t port, uint16_t pin, const gpio_pin_config_t *config);
  \brief Configure a GPIO pin
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \param[in] config  Pointer to GPIO pin configuration
 */
void GPIO_PinConfig(uint32_t port, uint16_t pin, const gpio_pin_config_t *config);

/**
  \fn    void GPIO_InterruptConfig(uint32_t port, uint16_t pin, gpio_interrupt_config_t config);
  \brief Configure a GPIO pin's interrupt type(valid when this pin has been set as input)
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \param[in] config  GPIO interrupt configuration
 */
void GPIO_InterruptConfig(uint32_t port, uint16_t pin, gpio_interrupt_config_t config);

/** \} */

/** \name GPIO Output Operations */
/** \{ */

/**
  \fn    void GPIO_PinWrite(uint32_t port, uint16_t pinMask, uint16_t output);
  \brief Sets output level of multiple GPIO pins to logic 1 or 0

  \code
  Example to set bits[15,1:0] to 1 and clear bits[12:11, 7:6]

  // pinMask shall be b10011000 11000011 = 0x98C3
  // output shall be  b10000000 00000011 = 0x8003
  GPIO_PinWrite(0, 0x98C3, 0x8003);
  // To set a single pin, let's say, pin 12 of GPIO0
  GPIO_PinWrite(0, 1 << 12, 1 << 12);
  // To clear a single pin, let's say, pin 12 of GPIO0
  GPIO_PinWrite(0, 1 << 12, 0);

  \endcode

  \param[in] port        GPIO number (0, 1, ...)
  \param[in] pinMask     GPIO pin mask to set
  \param[in] output      GPIO pin output logic level.
          - 0: corresponding pin output low-logic level.
          - 1: corresponding pin output high-logic level.
 */
void GPIO_PinWrite(uint32_t port, uint16_t pinMask, uint16_t output);

/** \} */

/** \name GPIO Input Operations */
/** \{ */

/**
  \fn    uint32_t GPIO_PinRead(uint32_t port, uint16_t pin)
  \brief Reads current input value of GPIO specific pin
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \return            GPIO corresponding pin input value
 */
uint32_t GPIO_PinRead(uint32_t port, uint16_t pin);

/** \} */

/** \name GPIO Interrupt */
/** \{ */

/**
  \fn    uint16_t GPIO_GetInterruptFlags(uint32_t port)
  \brief Reads GPIO port interrupt status flags
  \param[in]  port    GPIO number (0, 1, ...)
  \return     current GPIO interrupt status flag
 */
uint16_t GPIO_GetInterruptFlags(uint32_t port);

/**
  \fn    void GPIO_ClearInterruptFlags(uint32_t port, uint16_t mask)
  \brief Clears multiple GPIO pin interrupt status flags
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] mask    GPIO pin number macro
 */
void GPIO_ClearInterruptFlags(uint32_t port, uint16_t mask);

/**
  \fn    uint16_t GPIO_SaveAndSetIRQMask(uint32_t port)
  \brief Reads GPIO port interrupt enable mask and diables whole port interrupts
  \param[in]  port    GPIO number (0, 1, ...)
  \return     current GPIO port interrupt enable mask
  \note  Used in GPIO ISR to disable GPIO interrupts temporarily
 */
uint16_t GPIO_SaveAndSetIRQMask(uint32_t port);

/**
  \fn    void GPIO_RestoreIRQMask(uint32_t port, uint16_t mask)
  \brief Restore GPIO port interrupt enable setting
  \param[in]  port    GPIO number (0, 1, ...)
  \param[in]  mask    GPIO interrupt enable mask
  \note  Used in GPIO ISR to restore GPIO enable setting upon exit
 */
void GPIO_RestoreIRQMask(uint32_t port, uint16_t mask);

/** \} */

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_QCX212_H */
