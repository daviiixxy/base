/****************************************************************************
 *
 * Copy right:   2019-, Copyrigths of Qualcomm Ltd.
 * File name:    uart_qcx212.h
 * Description:  QCX212 uart driver header file
 * History:      Rev1.0   2019-03-14
 *
 ****************************************************************************/

#ifndef _UART_QCX212_H
#define _UART_QCX212_H

#include "qcx212.h"
#include "Driver_Common.h"

/**
  \addtogroup uart_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/**
  \fn          void UART_Init(uint32_t instance, uint32_t baudrate, bool enableFlowCtrl)
  \brief       Initialize UART with specific baudrate
  \param[in]   instance         UART instance number (0, 1, ...)
  \param[in]   baudrate         The desired baudrate
  \param[in]   enableFlowCtrl   Enable flow control or not
 */
void UART_Init(uint32_t instance, uint32_t baudrate, bool enableFlowCtrl);

/**
  \fn          uint32_t UART_Send(uint32_t instance, const uint8_t *data, uint32_t num, uint32_t timeout_us)
  \brief       Start sending data to USART transmitter in polling way
  \param[in]   instance    UART instance number (0, 1, ...)
  \param[in]   data        Pointer to buffer with data to send to USART transmitter
  \param[in]   num         Number of data items to send
  \param[in]   timeout_us  timeout value in unit of us
  \return      num of data items sent in the internal of timeout
 */
uint32_t UART_Send(uint32_t instance, const uint8_t *data, uint32_t num, uint32_t timeout_us);

/**
  \fn          uint32_t UART_Receive(uint32_t instance, uint8_t *data, uint32_t num, uint32_t timeout_us)
  \brief       Start receiving data from USART receiver in polling way
  \param[in]   instance    UART instance number (0, 1, ...)
  \param[out]  data        Pointer to buffer for data to receive from USART receiver
  \param[in]   num         Number of data items to receive
  \param[in]   timeout_us  timeout value in unit of us
  \return      num of data items received in the internal of timeout
 */
uint32_t UART_Receive(uint32_t instance, uint8_t *data, uint32_t num, uint32_t timeout_us);

/**
  \fn          void UART_Printf(uint32_t instance, const char* fmt, ...)
  \brief       Print formated data to USART transmitter
  \param[in]   instance    UART instance number (0, 1, ...)
  \param[in]   fmt         C string that contains the text to be sent to UART
  \param[in]   ...         __VA__ARGS
 */
void UART_Printf(uint32_t instance, const char* fmt, ...);

void UART_Flush(uint32_t instance);
void UART_PurgeRx(uint32_t instance);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _UART_QCX212_H */
