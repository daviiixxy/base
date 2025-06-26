#ifndef __HT_GPIO_QCX212_H__
#define __HT_GPIO_QCX212_H__

#include "gpio_qcx212.h"
#include "pad_qcx212.h"

typedef enum {
  GPIO_EXTI_DISABLED = 0,
  GPIO_EXTI_ENABLE
} GPIO_EXTI_En;

typedef struct {
  uint32_t instance;
  uint16_t gpio_pin;
  uint16_t pad_id;
  pad_mux_t af;
  pad_pull_config_t pull;
  gpio_pin_direction_t pin_direction;
  uint32_t init_output;
  GPIO_EXTI_En exti;
  gpio_interrupt_config_t interrupt_config;
} GPIO_InitType;


/**
  \fn    void HT_GPIO_DriverInit(void);
  \brief Intialize GPIO driver internal data
  \note  It is not necessarty to call this function before using GPIO driver since it has been
         called in \ref HT_GPIO_PinConfig() api.
 */
void HT_GPIO_DriverInit(void);

/**
  \fn    void HT_GPIO_DriverDeInit(void);
  \brief De-Intialize GPIO driver, disable GPIO clock and perform some clearups
 */
void HT_GPIO_DriverDeInit(void);

/** \} */

/** \name GPIO Configuration */
/** \{ */

/**
  \fn    void HT_GPIO_PinConfig(uint32_t port, uint16_t pin, const gpio_pin_config_t *config);
  \brief Configure a GPIO pin
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \param[in] config  Pointer to GPIO pin configuration
 */
void HT_GPIO_PinConfig(uint32_t port, uint16_t pin, const gpio_pin_config_t *config);

/**
  \fn    void GPIO_InterruptConfig(uint32_t port, uint16_t pin, gpio_interrupt_config_t config);
  \brief Configure a GPIO pin's interrupt type(valid when this pin has been set as input)
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \param[in] config  GPIO interrupt configuration
 */
void HT_GPIO_InterruptConfig(uint32_t port, uint16_t pin, gpio_interrupt_config_t config);

/** \} */

/** \name HT_GPIO Output Operations */
/** \{ */

/**
  \fn    void HT_GPIO_PinWrite(uint32_t port, uint16_t pinMask, uint16_t output);
  \brief Sets output level of multiple HT_GPIO pins to logic 1 or 0

  \code
  Example to set bits[15,1:0] to 1 and clear bits[12:11, 7:6]

  // pinMask shall be b10011000 11000011 = 0x98C3
  // output shall be  b10000000 00000011 = 0x8003
  HT_GPIO_PinWrite(0, 0x98C3, 0x8003);
  // To set a single pin, let's say, pin 12 of HT_GPIO0
  HT_GPIO_PinWrite(0, 1 << 12, 1 << 12);
  // To clear a single pin, let's say, pin 12 of HT_GPIO0
  HT_GPIO_PinWrite(0, 1 << 12, 0);

  \endcode

  \param[in] port        GPIO number (0, 1, ...)
  \param[in] pinMask     GPIO pin mask to set
  \param[in] output      GPIO pin output logic level.
          - 0: corresponding pin output low-logic level.
          - 1: corresponding pin output high-logic level.
 */
void HT_GPIO_PinWrite(uint32_t port, uint16_t pinMask, uint16_t output);

/** \} */

/** \name GPIO Input Operations */
/** \{ */

/**
  \fn    uint32_t HT_GPIO_PinRead(uint32_t port, uint16_t pin)
  \brief Reads current input value of GPIO specific pin
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] pin     GPIO pin number
  \return            GPIO corresponding pin input value
 */
uint32_t HT_GPIO_PinRead(uint32_t port, uint16_t pin);

/** \} */

/** \name GPIO Interrupt */
/** \{ */

/**
  \fn    uint16_t HT_GPIO_GetInterruptFlags(uint32_t port)
  \brief Reads GPIO port interrupt status flags
  \param[in]  port    GPIO number (0, 1, ...)
  \return     current GPIO interrupt status flag
 */
uint16_t HT_GPIO_GetInterruptFlags(uint32_t port);

/**
  \fn    void HT_GPIO_ClearInterruptFlags(uint32_t port, uint16_t mask)
  \brief Clears multiple GPIO pin interrupt status flags
  \param[in] port    GPIO number (0, 1, ...)
  \param[in] mask    GPIO pin number macro
 */
void HT_GPIO_ClearInterruptFlags(uint32_t port, uint16_t mask);

/**
  \fn    uint16_t HT_GPIO_SaveAndSetIRQMask(uint32_t port)
  \brief Reads GPIO port interrupt enable mask and diables whole port interrupts
  \param[in]  port    GPIO number (0, 1, ...)
  \return     current GPIO port interrupt enable mask
  \note  Used in GPIO ISR to disable GPIO interrupts temporarily
 */
uint16_t HT_GPIO_SaveAndSetIRQMask(uint32_t port);

/**
  \fn    void HT_GPIO_RestoreIRQMask(uint32_t port, uint16_t mask)
  \brief Restore GPIO port interrupt enable setting
  \param[in]  port    GPIO number (0, 1, ...)
  \param[in]  mask    GPIO interrupt enable mask
  \note  Used in GPIO ISR to restore GPIO enable setting upon exit
 */
void HT_GPIO_RestoreIRQMask(uint32_t port, uint16_t mask);

void HT_GPIO_Init(GPIO_InitType *gpio);
void HT_GPIO_WritePin(uint16_t pin, uint32_t instance, uint16_t value);

#endif /* __HT_GPIO_QCX212_H__ */
