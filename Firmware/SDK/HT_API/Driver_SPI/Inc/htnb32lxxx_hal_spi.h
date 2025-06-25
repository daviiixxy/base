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
 * \file htnb32lxxx_hal_spi.h
 * \brief SPI HAL module driver. 
 *        This file provides a complete API to manage all SPI (Serial Peripheral Interface) functionalities of the iMCP HTNB32L-XXX.
 * 
 * \author HT Micron Advanced R&D,
 *         Hêndrick Bataglin Gonçalves, Christian Roberto Lehmen,  Matheus da Silva Zorzeto, Felipe Kalinski Ferreira,
 *         Leandro Borges, Mauricio Carlotto Ribeiro, Henrique Kuhn, Cleber Haack, Eduardo Mendel
 * 
 * \link https://github.com/htmicron
 * \version 1.0
 * \date January 22, 2024
 */

#ifndef  __HTNB32Lxxx_HAL_SPI_H__
#define  __HTNB32Lxxx_HAL_SPI_H__

#include <stdio.h>
#include "string.h"
#include "qcx212.h"
#include "bsp.h"
#include "HT_Peripheral_Config.h"

/* Defines  ------------------------------------------------------------------*/

// SPI flags
#define SPI_FLAG_INITIALIZED          (1UL << 0)     // SPI initialized
#define SPI_FLAG_POWERED              (1UL << 1)     // SPI powered on
#define SPI_FLAG_CONFIGURED           (1UL << 2)     // SPI configured
#define SPI_FLAG_DATA_LOST            (1UL << 3)     // SPI data lost occurred
#define SPI_FLAG_MODE_FAULT           (1UL << 4)     // SPI mode fault occurred

/* Typedefs  ------------------------------------------------------------------*/

typedef enum {
  SPI_TRANSMIT_RECEIVE = 0,
  SPI_TRANSMIT_ONLY,
  SPI_RECEIVE_ONLY
} SPI_TransferTypeDef;

// SPI IRQ
typedef const struct _SPI_IRQ {
  IRQn_Type             irq_num;        // SPI IRQ Number
  IRQ_Callback_t        cb_irq;
} SPI_IRQ;

// SPI DMA
typedef struct _SPI_DMA {
  int8_t               tx_ch;                                  // Transmit channel number
  uint8_t               tx_req;                                 // Transmit DMA request number
  void                  (*tx_callback)(uint32_t event);         // Transmit callback
  int8_t               rx_ch;                                  // Receive channel number
  uint8_t               rx_req;                                 // Receive DMA request number
  void                  (*rx_callback)(uint32_t event);         // Receive callback
  dma_descriptor_t      *descriptor;                            // Rx descriptor
} SPI_DMA;

// SPI PINS
typedef const struct _SPI_PIN {
  PIN               *pin_sclk;                                //  SCLK Pin identifier
  PIN               *pin_ssn;                                 //  SSn Pin identifier
  PIN               *pin_mosi;                                //  MOSI Pin identifier
  PIN               *pin_miso;                                //  MISO Pin identifier
} SPI_PINS;

typedef struct _SPI_STATUS {
  uint8_t busy;                         // Transmitter/Receiver busy flag
  uint8_t data_lost;                    // Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint8_t mode_fault;                   // Mode fault detected; optional (cleared on start of transfer operation)
} SPI_STATUS;

// SPI Transfer Information (Run-Time)
typedef struct _SPI_TRANSFER_INFO {
  uint32_t              num;            // Total number of transfers
  uint8_t              *rx_buf;         // Pointer to in data buffer
  uint8_t              *tx_buf;         // Pointer to out data buffer
  uint32_t              rx_cnt;         // Number of data received
  uint32_t              tx_cnt;         // Number of data sent
  uint32_t              dump_val;       // Variable for dumping DMA data
  uint16_t              def_val;        // Default transfer value
} SPI_TRANSFER_INFO;

// SPI information (Run-time)
typedef struct _SPI_INFO {
    ARM_SPI_SignalEvent_t cb_event;     // event callback
    SPI_STATUS            status;       // SPI status flags
    SPI_TRANSFER_INFO     xfer;         // SPI transfer information
    uint8_t               flags;        // SPI driver flags
    uint32_t              mode;         // SPI mode
    uint32_t              bus_speed;    // SPI bus speed
    uint8_t               data_width;   // SPI data bits select in unit of byte
    SPI_TransferTypeDef   transfer_type;
} SPI_INFO;


// SPI Resources definition
typedef struct {
  SPI_TypeDef                 *reg;                  // SPI register pointer
  SPI_PINS                     pins;                 // SPI PINS configuration
  SPI_DMA                     *dma;                  // SPI DMA configuration pointer
  SPI_IRQ                     *irq;                  // SPI IRQ configuration pointer
  SPI_INFO                    *info;                 // Run-Time Information
} SPI_HandleTypeDef;

/* Functions  ----------------------------------------------------------------*/

/*!******************************************************************
 * \fn void HAL_SPI_CleanRxFifo(SPI_HandleTypeDef *spi)
 * \brief Clean RX FIFO.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI_CleanRxFifo(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn void HAL_SPI_EnableIRQ(SPI_HandleTypeDef *spi)
 * \brief Enable the SPI IRQn.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI_EnableIRQ(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn void HAL_SPI_DisableIRQ(SPI_HandleTypeDef *spi)
 * \brief Disable all SPI IRQn.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI_DisableIRQ(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn void HAL_SPI_DmaTxEvent(uint32_t event, SPI_HandleTypeDef *spi)
 * \brief SPI DMA Tx Event handler.
 *
 * \param[in] uint32_t event 
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI_DmaTxEvent(uint32_t event, SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn void HAL_SPI_DmaRxEvent(uint32_t event, SPI_HandleTypeDef *spi)
 * \brief SPI DMA Rx Event handler.
 * 
 * \param[in]  uint32_t event DMA Rx Event
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 *
 * \retval none
 *******************************************************************/
void HAL_SPI_DmaRxEvent(uint32_t event, SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn  void HAL_SPI0_IRQHandler(void);
 * \brief SPI0 IRQn handler.
 * 
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI0_IRQHandler(void);

/*!******************************************************************
 * \fn  void HAL_SPI1_IRQHandler(void);
 * \brief SPI1 IRQn handler.
 * 
 * \param[in]  none
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI1_IRQHandler(void);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Initialize(ARM_SPI_SignalEvent_t cb_event, SPI_HandleTypeDef *spi)
 * \brief Initialize SPI peripheral.
 *
 * \param[in] ARM_SPI_SignalEvent_t cb_event      Pointer to the callback function.
 * \param[in]  SPI_HandleTypeDef *spi             spi handle.
 * \param[out] none
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Initialize(ARM_SPI_SignalEvent_t cb_event, SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Uninitialize(SPI_HandleTypeDef *spi)
 * \brief Uninitialize SPI peripheral.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Uninitialize(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn int32_t HAL_SPI_PowerControl(ARM_POWER_STATE state, SPI_HandleTypeDef *spi);
 * \brief Configures the power control of SPI peripheral, as well as initiliazes the SPI
 * clock and DMA or IRQn, if used.
 * 
 * \param[in] ARM_POWER_STATE state       Power mode state.  
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_PowerControl(ARM_POWER_STATE state, SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Control(uint32_t control, uint32_t arg, SPI_HandleTypeDef *spi)
 * \brief Configures the SPI mode (MASTER/SLAVE), bus speed, flow control options and
 * all ctrl registers.
 * 
 * \param[in]  uint32_t control           Control arg.
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
int32_t HAL_SPI_Control(uint32_t control, uint32_t arg, SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn int32_t HAL_SPI_TransmitReceive_Polling(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size)
 * \brief SPI polling transmit/receive (FULL-DUPLEX) in blocking mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint8_t *pTxData            TX buffer
 * \param[in] uint16_t size               TX/RX buffer size
 * \param[out] uint8_t *pRxData           RX buffer
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_TransmitReceive_Polling(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Transmit_Polling(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint16_t size)
 * \brief SPI polling transmit in blocking mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint8_t *pTxData            TX buffer
 * \param[in] uint16_t size               TX/RX buffer size
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Transmit_Polling(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Receive_Polling(SPI_HandleTypeDef *spi, uint8_t *pRxData, uint16_t size)
 * \brief SPI polling receive in blocking mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint16_t size               TX/RX buffer size
 * \param[out] uint8_t *pRxData           RX buffer
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Receive_Polling(SPI_HandleTypeDef *spi, uint8_t *pRxData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size)
 * \brief SPI transmit/receive in DMA mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint8_t *pTxData            TX buffer
 * \param[in] uint16_t size               TX/RX buffer size
 * \param[out] uint8_t *pRxData           RX buffer
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint16_t size)
 * \brief SPI transmit in DMA mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint8_t *pTxData            TX buffer
 * \param[in] uint16_t size               TX/RX buffer size
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Receive_DMA(SPI_HandleTypeDef *spi, uint8_t *pRxData, uint16_t size)
 * \brief SPI receive in DMA mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint16_t size               TX/RX buffer size
 * \param[out] uint8_t *pRxData           RX buffer
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Receive_DMA(SPI_HandleTypeDef *spi, uint8_t *pRxData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size)
 * \brief SPI transmit/receive in IRQn mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint8_t *pTxData            TX buffer
 * \param[in] uint16_t size               TX/RX buffer size
 * \param[out] uint8_t *pRxData           RX buffer
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Transmit_IT(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint16_t size)
 * \brief SPI transmit in IRQn mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint8_t *pTxData            TX buffer
 * \param[in] uint16_t size               TX/RX buffer size
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Transmit_IT(SPI_HandleTypeDef *spi, uint8_t *pData, uint16_t size);

/*!******************************************************************
 * \fn int32_t HAL_SPI_Receive_IT(SPI_HandleTypeDef *spi, uint8_t *pRxData, uint16_t size)
 * \brief SPI receive in IRQn mode.
 *
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[in] uint16_t size               TX/RX buffer size
 * \param[out] uint8_t *pRxData           RX buffer
 *
 * \retval Error code.
 *******************************************************************/
int32_t HAL_SPI_Receive_IT(SPI_HandleTypeDef *spi, uint8_t *pData, uint16_t size);

/*!******************************************************************
 * \fn void HAL_SPI1_DmaTxEvent(uint32_t event)
 * \brief SPI DMA Tx Event handler.
 *
 * \param[in] uint32_t event 
 * \param[in]  SPI_HandleTypeDef *spi     spi handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI1_DmaTxEvent(uint32_t event);

/*!******************************************************************
 * \fn void HAL_SPI1_DmaRxEvent(uint32_t event)
 * \brief SPI DMA Rx Event handler.
 * 
 * \param[in]  uint32_t event DMA Rx Event
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI1_DmaRxEvent(uint32_t event);

/*!******************************************************************
 * \fn void HAL_SPI0_DmaTxEvent(uint32_t event)
 * \brief SPI DMA Tx Event handler.
 *
 * \param[in] uint32_t event 
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI0_DmaTxEvent(uint32_t event);

/*!******************************************************************
 * \fn void HAL_SPI0_DmaRxEvent(uint32_t event)
 * \brief SPI DMA Rx Event handler.
 * 
 * \param[in]  uint32_t event DMA Rx Event
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HAL_SPI0_DmaRxEvent(uint32_t event);

#endif /* __HTNB32Lxxx_HAL_SPI_H__ */

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
