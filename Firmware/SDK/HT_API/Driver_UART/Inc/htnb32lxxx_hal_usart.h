/*

  _    _ _______   __  __ _____ _____ _____   ____  _   _
 | |  | |__   __| |  \/  |_   _/ ____|  __ \ / __ \| \ | |
 | |__| |  | |    | \  / | | || |    | |__) | |  | |  \| |
 |  __  |  | |    | |\/| | | || |    |  _  /| |  | | . ` |
 | |  | |  | |    | |  | |_| || |____| | \ \| |__| | |\  |
 |_|  |_|  |_|    |_|  |_|_____\_____|_|  \_\\____/|_| \_|
 =================== Advanced R&D ========================

 Copyright (c) 2024 HT Micron Semicondutores S.A.
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

*/

/*!
 * \file htnb32lxxx_hal_usart.h
 * \brief USART HAL module driver. 
 *        This file provides a complete API to manage all USART (Universal Synchronous Asynchronous Receiver Transmitter) 
 *        functionalities of the iMCP HTNB32L-XXX.
 * 
 * \author HT Micron Advanced R&D,
 *         Hêndrick Bataglin Gonçalves, Christian Roberto Lehmen,  Matheus da Silva Zorzeto, Felipe Kalinski Ferreira,
 *         Leandro Borges, Mauricio Carlotto Ribeiro, Henrique Kuhn, Cleber Haack, Eduardo Mendel
 * 
 * \link https://github.com/htmicron
 * \version 1.0
 * \date February 27, 2024
 */

#ifndef  __HTNB32LXXX_HAL_USART_H__
#define  __HTNB32LXXX_HAL_USART_H__

#include <stdio.h>
#include "string.h"
#include "qcx212.h"
#include "bsp.h"
#include "Driver_USART.h"
#include "HT_clock_qcx212.h"
#include "plat_config.h"
#include "HT_bsp.h"
#include "HT_plat_config.h"
#include "hal_uart.h"

/* Defines  ------------------------------------------------------------------*/

// USART flags
#define USART_FLAG_INITIALIZED          (1U << 0)     // USARTinitialized
#define USART_FLAG_POWERED              (1U << 1)     // USART powered on
#define USART_FLAG_CONFIGURED           (1U << 2)     // USART configured
#define USART_FLAG_TX_ENABLED           (1U << 3)     // USART TX enabled
#define USART_FLAG_RX_ENABLED           (1U << 4)     // USART RX enabled
#define USART_FLAG_SEND_ACTIVE          (1U << 5)     // USART send active

#define USART_TFE_INT          (0x2<<USART_IIR_INT_ID_Pos)
#define USART_RDA_INT          (0x4<<USART_IIR_INT_ID_Pos)
#define USART_RLS_INT          (0x6<<USART_IIR_INT_ID_Pos)
#define USART_CTI_INT          (0xC<<USART_IIR_INT_ID_Pos)
#define USART_INT_TYPE_MSK     (0xF<<USART_IIR_INT_ID_Pos)

#ifdef PM_FEATURE_ENABLE
#define USART_DEBUG  1
#endif

#if USART_DEBUG
#include "debug_log.h"
#endif

#define ARM_USART_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0)  /* driver version */

#if ((!RTE_UART0) && (!RTE_UART1)) && (!RTE_UART2)
#error "UART not enabled in RTE_Device.h!"
#endif

#define UART_DMA_BURST_SIZE      8

// Trigger level definitions
#ifndef USART0_RX_TRIG_LVL

#if (RTE_UART0_RX_IO_MODE == DMA_MODE)
#define USART0_RX_TRIG_LVL   RX_FIFO_TRIG_LVL_16BYTE
#else
#define USART0_RX_TRIG_LVL   RX_FIFO_TRIG_LVL_30BYTE
#endif

#endif

#ifndef USART1_RX_TRIG_LVL

#if (RTE_UART1_RX_IO_MODE == DMA_MODE)
#define USART1_RX_TRIG_LVL   RX_FIFO_TRIG_LVL_16BYTE
#else
#define USART1_RX_TRIG_LVL   RX_FIFO_TRIG_LVL_30BYTE
#endif

#endif

#ifndef USART2_RX_TRIG_LVL

#if (RTE_UART2_RX_IO_MODE == DMA_MODE)
#define USART2_RX_TRIG_LVL   RX_FIFO_TRIG_LVL_16BYTE
#else
#define USART2_RX_TRIG_LVL   RX_FIFO_TRIG_LVL_30BYTE
#endif

#endif

#define USART0_TX_TRIG_LVL   TX_FIFO_TRIG_LVL_0BYTE
#define USART1_TX_TRIG_LVL   TX_FIFO_TRIG_LVL_0BYTE
#define USART2_TX_TRIG_LVL   TX_FIFO_TRIG_LVL_0BYTE

/* Typedefs  ------------------------------------------------------------------*/

// USART IRQ
typedef const struct _USART_IRQ {
  IRQn_Type             irq_num;         // USART IRQ Number
  IRQ_Callback_t        cb_irq;
} USART_IRQ;

// USART TX DMA
typedef struct _USART_TX_DMA {
  int8_t                channel;                                //  Channel number
  uint8_t               request;                                //  DMA request number
  void                  (*callback)(uint32_t event);            //  Tx callback
} USART_TX_DMA;

// USART RX DMA
typedef struct _USART_RX_DMA {
  int8_t                channel;                                //  Channel number
  uint8_t               request;                                //  DMA request number
  dma_descriptor_t      *descriptor;                            //  Rx descriptor
  void                  (*callback)(uint32_t event);            //  Rx callback
} USART_RX_DMA;

// USART PINS
typedef const struct _USART_PIN {
  const PIN               *pin_tx;                                //  TX Pin identifier
  const PIN               *pin_rx;                                //  RX Pin identifier
  const PIN               *pin_cts;                               //  CTS Pin identifier
  const PIN               *pin_rts;                               //  RTS Pin identifier
} USART_PINS;

typedef struct _USART_TRANSFER_INFO {
  uint32_t              rx_num;         // Total number of receive data
  uint32_t              tx_num;         // Total number of transmit data
  uint8_t              *rx_buf;         // Pointer to in data buffer
  uint8_t              *tx_buf;         // Pointer to out data buffer
  uint32_t              rx_cnt;         // Number of data received
  uint32_t              tx_cnt;         // Number of data sent
  uint16_t              tx_def_val;     // Default transmit value
  uint16_t              rx_dump_val;    // Receive dump value
  uint8_t               send_active;    // Send active flag
  uint32_t              sync_mode;      // Synchronous mode flag
} USART_TRANSFER_INFO;

typedef struct _USART_STATUS {
  uint8_t rx_busy;                      // Receiver busy flag
  uint8_t rx_dma_triggered;             // Receive DMA transfer triggered (cleared on start of next receive operation)
  uint8_t rx_overflow;                  // Receive data overflow detected (cleared on start of next receive operation)
  uint8_t rx_break;                     // Break detected on receive (cleared on start of next receive operation)
  uint8_t rx_framing_error;             // Framing error detected on receive (cleared on start of next receive operation)
  uint8_t rx_parity_error;              // Parity error detected on receive (cleared on start of next receive operation)
} USART_STATUS;

typedef struct _USART_INFO {
  ARM_USART_SignalEvent_t cb_event;            // Event Callback
  USART_STATUS            rx_status;           // Recieve Status flags
  USART_TRANSFER_INFO     xfer;                // USART transfer information
  uint8_t                 flags;               // Current USART flags
  uint32_t                mode;                // Current USART mode
  uint32_t                baudrate;            // Baudrate
} USART_INFO;

// USART Resources definition
typedef const struct {
  USART_TypeDef           *reg;                  // USART peripheral pointer
  USART_PINS               pins;                 // USART PINS config
  USART_TX_DMA            *dma_tx;               // USART DMA register interface
  USART_RX_DMA            *dma_rx;               // USART DMA register interface
  USART_IRQ               *usart_irq;            // USART IRQ
  uint32_t                 tx_fifo_trig_lvl;     // USART TX FIFO trigger level
  uint32_t                 rx_fifo_trig_lvl;     // USART RX FIFO trigger level
  USART_INFO              *info;                 // Run-Time Information
  uint8_t                  is_unilog_mode;       // Act as unilog output
} USART_HandleTypeDef;

// USAR DMA events typedef.
typedef enum {
  USART_DMA_NONE_EVENT = 0,                       // USART DMA event none (default)
  USART_DMA_TX_EVENT,                             // USART TX event.
  USART_DMA_RX_EVENT                              // USART RX event.
} USART_DMA_TypeDef;

enum _USART_RX_FIFO_TRIG_LVL {
    RX_FIFO_TRIG_LVL_1BYTE   = 1U,
    RX_FIFO_TRIG_LVL_8BYTE   = 8U,
    RX_FIFO_TRIG_LVL_16BYTE  = 16U,
    RX_FIFO_TRIG_LVL_30BYTE  = 30U
};

enum _USART_TX_FIFO_TRIG_LVL {
    TX_FIFO_TRIG_LVL_0BYTE,
    TX_FIFO_TRIG_LVL_2BYTE,
    TX_FIFO_TRIG_LVL_8BYTE,
    TX_FIFO_TRIG_LVL_16BYTE
};

/* Functions  ----------------------------------------------------------------*/

/*!******************************************************************
 * \fn ARM_DRIVER_VERSION ARM_USART_GetVersion(void)
 * \brief Gets ARM driver version.
 *
 * \param[in] none
 * \param[out] none
 *
 * \retval Drive version.
 *******************************************************************/
ARM_DRIVER_VERSION ARM_USART_GetVersion(void);

/*!******************************************************************
 * \fn ARM_USART_CAPABILITIES HAL_USART_GetCapabilities(USART_HandleTypeDef *usart)
 * \brief Gets USART capabilities.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval ARM USART capabilities.
 *******************************************************************/
ARM_USART_CAPABILITIES HAL_USART_GetCapabilities(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn void HAL_USART_SendPolling(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size)
 * \brief Send a buffer through USART in blocking mode.
 *
 * \param[in] USART_HandleTypeDef *huart      USART handle.
 * \param[in] uint8_t *pTxBuff                TX buffer.
 * \param[in] uint32_t size                   TX buffer size.
 * \param[out] none
 *
 * \retval ARM Driver status.
 *******************************************************************/
int32_t HAL_USART_SendPolling(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size);

/*!******************************************************************
 * \fn int32_t HAL_USART_ReceivePolling(USART_HandleTypeDef *huart, uint8_t *pRxBuff, uint32_t size)
 * \brief Receive a buffer through USART in blocking mode.
 *
 * \param[in] USART_HandleTypeDef *huart      USART handle.
 * \param[in] uint32_t size                   RX buffer size.
 * \param[out] uint8_t *pRxBuff                RX buffer.
 *
 * \retval ARM Driver status.
 *******************************************************************/
int32_t HAL_USART_ReceivePolling(USART_HandleTypeDef *huart, uint8_t *pRxBuff, uint32_t size);

/*!******************************************************************
 * \fn int32_t HAL_USART_Initialize(ARM_USART_SignalEvent_t cb_event, USART_HandleTypeDef *usart)
 * \brief Initialize USART peripheral.
 *
 * \param[in] ARM_USART_SignalEvent_t cb_event  User callback function.
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval Error status.
 *******************************************************************/
int32_t HAL_USART_Initialize(ARM_USART_SignalEvent_t cb_event, USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn int32_t HAL_USART_Uninitialize(USART_HandleTypeDef *usart)
 * \brief Uninitialize USART peripheral.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval Error status.
 *******************************************************************/
int32_t HAL_USART_Uninitialize(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn int32_t HAL_USART_PowerControl(ARM_POWER_STATE state, USART_HandleTypeDef *usart)
 * \brief Configures the power control of the USART peripheral, as well as initializes the clock
 *        and DMA or IRQn, if used.
 *
 * \param[in] ARM_POWER_STATE state             Power mode state.
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval Error status.
 *******************************************************************/
int32_t HAL_USART_PowerControl(ARM_POWER_STATE state, USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn int32_t HAL_USART_Control(uint32_t control, uint32_t arg, USART_HandleTypeDef *usart)
 * \brief Configures the USART peripheral parameters, such as stop bit, parity bit, flw control and
 *        baudrate.
 *
 * \param[in] uint32_t control                  Control parameters.
 * \param[in] uint32_t args                     Control args, such as baudrate.
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval Error status.
 *******************************************************************/
int32_t HAL_USART_Control(uint32_t control, uint32_t arg, USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn void HAL_USART_IRQnDisable(USART_HandleTypeDef *huart, uint32_t intMask)
 * \brief Disable the USART IRQn.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[in] uint32_t intMask                  Interruption mask.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART_IRQnDisable(USART_HandleTypeDef *huart, uint32_t intMask);

/*!******************************************************************
 * \fn void HAL_USART_IRQnEnable(USART_HandleTypeDef *huart, uint32_t intMask)
 * \brief Enable the USART IRQn.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[in] uint32_t intMask                  Interruption mask.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART_IRQnEnable(USART_HandleTypeDef *huart, uint32_t intMask);

/*!******************************************************************
 * \fn void HAL_USART_InitPrint(USART_HandleTypeDef *huart, clock_select_t uartClkSel, uint32_t control, uint32_t baudrate)
 * \brief Initializes an USART instance to work as the interface for printing debug logs.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[in] clock_select_t uartClkSel         USART clock option.
 * \param[in] uint32_t control                  USART control parameter.
 * \param[in] uint32_t baudrate                 USART baudrate.
 * \param[out] none 
 *
 * \retval none.
 *******************************************************************/
void HAL_USART_InitPrint(USART_HandleTypeDef *huart, clock_select_t uartClkSel, uint32_t control, uint32_t baudrate);

/*!******************************************************************
 * \fn static int32_t HAL_USART_Send(USART_HandleTypeDef *huart, uint8_t *data, uint32_t size)
 * \brief Sends a buffer through the USART peripheral.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[in] uint8_t *data                        USART TX buffer.
 * \param[in] uint32_t  size                       TX buffer size.
 * \param[out] none
 *
 * \retval Number of bytes sent.
 *******************************************************************/
int32_t HAL_USART_Send(USART_HandleTypeDef *huart, uint8_t *data, uint32_t size);

/*!******************************************************************
 * \fn void HAL_USART_Transmit_IT(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size)
 * \brief Transmit a buffer through USART peripheral in interruption mode.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[in] uint8_t *pTxBuff                  TX buffer.
 * \param[in] uint32_t size                     Size of the buffer that will be transmitted.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART_Transmit_IT(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size);

/*!******************************************************************
 * \fn void HAL_USART_Receive_IT(uint8_t *pRxBuff, uint32_t size)
 * \brief Receive a buffer through USART peripheral in interruption mode.
 *
 * \param[in] uint8_t *pRxBuff                  RX buffer.
 * \param[in] uint32_t size                     Size of the buffer that will be received.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART_Receive_IT(uint8_t *pRxBuff, uint32_t size);

/*!******************************************************************
 * \fn int32_t HAL_USART_Receive_DMA(USART_HandleTypeDef *huart, uint8_t *pRxBuff, uint32_t size)
 * \brief Receive a buffer through USART peripheral in DMA mode.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[in] uint8_t *pRxBuff                  RX buffer.
 * \param[in] uint32_t size                     Size of the buffer that will be received.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
int32_t HAL_USART_Receive_DMA(USART_HandleTypeDef *huart, uint8_t *pRxBuff, uint32_t size);

/*!******************************************************************
 * \fn int32_t HAL_USART_Transmit_DMA(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size)
 * \brief Transmit a buffer through USART peripheral in DMA mode.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[in] uint8_t *pTxBuff                  TX buffer.
 * \param[in] uint32_t size                     Size of the buffer that will be transmitted.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
int32_t HAL_USART_Transmit_DMA(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size);

/*!******************************************************************
 * \fn int32_t HAL_USART_Transfer(USART_HandleTypeDef *huart, const void *data_out, void *data_in, uint8_t size)
 * \brief Not implemented.
 *
 * \param[in] none
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
int32_t HAL_USART_Transfer(USART_HandleTypeDef *huart, const void *data_out, void *data_in, uint8_t size);

/*!******************************************************************
 * \fn ARM_USART_MODEM_STATUS HAL_USART_GetModemStatus(USART_HandleTypeDef *usart)
 * \brief Gets the modem status..
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval ARM USART Modem Status.
 *******************************************************************/
ARM_USART_MODEM_STATUS HAL_USART_GetModemStatus(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn PLAT_CODE_IN_RAM int32_t HAL_USART_GetRxCount(USART_HandleTypeDef *usart)
 * \brief Gets the USART rx count. NOT IMPLEMENTED IN THIS SDK VERSION.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval RX count value.
 *******************************************************************/
PLAT_CODE_IN_RAM int32_t HAL_USART_GetRxCount(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn int32_t HAL_USART_SetModemControl(ARM_USART_MODEM_CONTROL control, USART_HandleTypeDef *usart)
 * \brief Not implemented.
 *
 * \param[in] none
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
int32_t HAL_USART_SetModemControl(ARM_USART_MODEM_CONTROL control, USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn PLAT_CODE_IN_RAM void USART_IRQHandler(USART_HandleTypeDef *usart)
 * \brief USART IRQn handler.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
PLAT_CODE_IN_RAM void USART_IRQHandler(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn uint32_t HAL_USART_GetBaudRate(USART_HandleTypeDef *usart)
 * \brief Gets the USART baudrate.
 *
 * \param[in] USART_HandleTypeDef *huart        USART handle.
 * \param[out] none
 *
 * \retval USART baudrate in uint32_t.
 *******************************************************************/
uint32_t HAL_USART_GetBaudRate(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn int32_t HAL_USART_GetTxCount(USART_HandleTypeDef *usart)
 * \brief Gets the TX count.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval TX count.
 *******************************************************************/
int32_t HAL_USART_GetTxCount(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn ARM_USART_STATUS HAL_USART_GetStatus(USART_HandleTypeDef *usart);
 * \brief Gets the USART status.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval ARM USART status.
 *******************************************************************/
ARM_USART_STATUS HAL_USART_GetStatus(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn void HT_USART_Callback(uint32_t event)
 * \brief USART interruption callback.
 *
 * \param[in] uint32_t event                    USART event that triggered the interruption.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HT_USART_Callback(uint32_t event);

#endif /* __HTNB32LXXX_HAL_USART_H__ */

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
