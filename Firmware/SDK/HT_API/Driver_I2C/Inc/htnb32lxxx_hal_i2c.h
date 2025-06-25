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
 * \file htnb32lxxx_hal_i2c.h
 * \brief I2C Driver for HTNB32L.
  * \author HT Micron Advanced R&D,
 *         Hêndrick Bataglin Gonçalves, Christian Roberto Lehmen,  Matheus da Silva Zorzeto, Felipe Kalinski Ferreira,
 *         Leandro Borges, Mauricio Carlotto Ribeiro, Henrique Kuhn, Cleber Haack, Eduardo Mendel
 * 
 * \link https://github.com/htmicron
 * \version 1.0
 * \date April 18, 2024
 */

#ifndef  __HTNB32LXXX_HAL_I2C_H__
#define  __HTNB32LXXX_HAL_I2C_H__

#include <stdio.h>
#include "string.h"
#include "qcx212.h"
#include "bsp.h"
#include "HT_Peripheral_Config.h"
#include "HT_bsp.h"

/* Defines  ------------------------------------------------------------------*/

// I2C Driver state flags
#define I2C_FLAG_INIT        BIT(0)        // Driver initialized
#define I2C_FLAG_POWER       BIT(1)        // Driver power on
#define I2C_FLAG_SETUP       BIT(2)        // Master configured, clock set
#define I2C_FLAG_MASTER_TX   BIT(3)        // Master tx
#define I2C_FLAG_MASTER_RX   BIT(4)        // Master rx
#define I2C_FLAG_SLAVE_TX    BIT(5)        // Slave  tx
#define I2C_FLAG_SLAVE_RX    BIT(6)        // Slave  rx

#define  I2C_NO_STARTSTOP               (0x00000000U)
#define  I2C_GENERATE_STOP              (I2C_SCR_STOP_Msk)
#define  I2C_GENERATE_START_READ        (I2C_SCR_START_Msk | I2C_SCR_TARGET_RWN_Msk)
#define  I2C_GENERATE_START_WRITE       (I2C_SCR_START_Msk)
#define  I2C_GENERATE_RESTART_READ      (I2C_SCR_RESTART_Msk | I2C_SCR_TARGET_RWN_Msk)
#define  I2C_GENERATE_RESTART_WRITE     (I2C_SCR_RESTART_Msk)

#define I2C_MEMADD_SIZE_8BIT            (0x00000001U)
#define I2C_MEMADD_SIZE_16BIT           (0x00000002U)

#define I2C_AUTOMATIC_MODE1              (0x01)    // byte_num_unknown = 0
#define I2C_AUTOMATIC_MODE2              (0x02)    // byte_num_unknown = 1
#define I2C_DEDICATED_MODE               (0x03)

#define I2C_OWN_ADDRESS_MASK (1 << 0)
#define I2C_BUS_SPEED_MASK  (1 << 1)
#define I2C_BUS_CLEAR_MASK (1 << 2)
#define I2C_ABORT_TRANSFER_MASK (1 << 3)

/* Typedefs  ------------------------------------------------------------------*/

// I2C IRQ
typedef const struct _I2C_IRQ {
  IRQn_Type             irq_num;         // I2C IRQ Number
  IRQ_Callback_t        cb_irq;
} I2C_IRQ;

// I2C PINS
typedef const struct _I2C_PIN {
  PIN               *pin_scl;                                //  SCL Pin identifier
  PIN               *pin_sda;                                //  SDA Pin identifier
} I2C_PINS;

// I2C DMA
typedef struct _I2C_DMA {
  int8_t                tx_ch;                                  // Transmit channel number
  uint8_t               tx_req;                                 // Transmit DMA request number
  void                  (*tx_callback)(uint32_t event);         // Transmit callback
  int8_t                rx_ch;                                  // Receive channel number
  uint8_t               rx_req;                                 // Receive DMA request number
  void                  (*rx_callback)(uint32_t event);         // Receive callback
  dma_descriptor_t      *descriptor;                            // Rx descriptor
} I2C_DMA;


// I2C Control Information
typedef struct {
  ARM_I2C_SignalEvent_t cb_event;           // Event callback
  ARM_I2C_STATUS        status;             // Status flags
  uint8_t               flags;              // Control and state flags
  uint8_t               sla_rw;             // Slave address and RW bit
  bool                  pending;            // Transfer pending (no STOP)
  uint8_t               stalled;            // Stall mode status flags
  uint8_t               con_aa;             // I2C slave CON flag
  uint32_t              cnt;                // Master transfer count
  uint8_t              *data;               // Master data to transfer
  uint32_t              num;                // Number of bytes to transfer
  uint8_t              *sdata;              // Slave data to transfer
  uint32_t              snum;               // Number of bytes to transfer
} I2C_CTRL;


// I2C Resources definition
typedef struct {
  I2C_TypeDef                 *reg;                  // I2C peripheral register interface
  I2C_PINS                     pins;                 // I2C PINS config
  I2C_DMA*                     dma;                  // I2C DMA configuration
  I2C_IRQ*                     irq;                  // I2C IRQ
  I2C_CTRL                    *ctrl;                 // Run-Time control information
} const I2C_HandleTypeDef;

typedef enum {
    HT_I2C0 = 0,
    HT_I2C1
} HAL_I2C_Type;

/* Functions  ----------------------------------------------------------------*/

/*!******************************************************************
 * \fn void HAL_I2C_MasterReceive_Polling(I2C_HandleTypeDef *hi2c, uint32_t addr, uint8_t *pRxData, uint32_t size);
 * \brief I2C master receive in polling mode.
 *
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[in] uint32_t addr                     I2C slave address.
 * \param[in] uint32_t size                     Amount of data to be received.
 * \param[out] uint8_t *pRxData                 RX buffer.
 *
 * \retval none
 *******************************************************************/
void HAL_I2C_MasterReceive_Polling(I2C_HandleTypeDef *hi2c, uint32_t addr, uint8_t *pRxData, uint32_t size);

/*!******************************************************************
 * \fn void HAL_I2C_MasterTransmit_Polling(I2C_HandleTypeDef *hi2c, uint32_t addr, const uint8_t *data, uint32_t size);
 * \brief I2C master transmit in polling mode.
 *
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[in] uint32_t addr                     I2C slave address.
 * \param[in] const uint8_t *data               TX buffer.
 * \param[in] uint32_t size                     Amount of data to be sent.
 *
 * \retval none
 *******************************************************************/
void HAL_I2C_MasterTransmit_Polling(I2C_HandleTypeDef *hi2c, uint32_t addr, const uint8_t *data, uint32_t size);

/*!******************************************************************
 * \fn int32_t HAL_I2C_MasterTransmit_IT(I2C_HandleTypeDef *hi2c, uint32_t addr, uint8_t *pTxData, uint32_t size);
 * \brief I2C master transmit in IRQn mode.
 *
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[in] uint32_t addr                     I2C slave address.
 * \param[in] uint8_t *pTxData                  TX buffer.
 * \param[in] uint32_t size                     Amount of data to be sent.
 *
 * \retval ARM driver status.
 *******************************************************************/
int32_t HAL_I2C_MasterTransmit_IT(I2C_HandleTypeDef *hi2c, uint32_t addr, uint8_t *pTxData, uint32_t size);

/*!******************************************************************
 * \fn int32_t HAL_I2C_MasterReceive_IT(I2C_HandleTypeDef *hi2c, uint32_t addr, uint8_t *pRxData, uint32_t size);
 * \brief I2C master receive in IRQn mode.
 *
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[in] uint32_t addr                     I2C slave address.
 * \param[in] uint32_t size                     Amount of data to be received.
 * \param[out] uint8_t *pRxData                  RX buffer.
 *
 * \retval ARM driver status.
 *******************************************************************/
int32_t HAL_I2C_MasterReceive_IT(I2C_HandleTypeDef *hi2c, uint32_t addr, uint8_t *pRxData, uint32_t size);

/*!******************************************************************
 * \fn void I2C_IRQHandler(I2C_HandleTypeDef *i2c)
 * \brief I2C Event Interrupt handler.
 *
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void I2C_IRQHandler(I2C_HandleTypeDef *i2c);

/*!******************************************************************
 * \fn int32_t HAL_I2C_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_HandleTypeDef *i2c)
 * \brief Initialize I2C peripheral.
 *
 * \param[in] ARM_I2C_SignalEvent_t cb_event    I2C callback function ptr.
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[out] none
 *
 * \retval ARM Driver status.
 *******************************************************************/
int32_t HAL_I2C_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_HandleTypeDef *i2c);

/*!******************************************************************
 * \fn int32_t HAL_I2C_Initialize(ARM_I2C_SignalEvent_t cb_event, I2C_HandleTypeDef *i2c)
 * \brief De-initialize I2C peripheral.
 *
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[out] none
 *
 * \retval ARM Driver status.
 *******************************************************************/
int32_t HAL_I2C_Uninitialize(I2C_HandleTypeDef *i2c);

/*!******************************************************************
 * \fn int32_t HAL_I2C_PowerControl(ARM_POWER_STATE state, I2C_HandleTypeDef *i2c)
 * \brief Initialize I2C peripheral.
 *
 * \param[in] ARM_POWER_STATE state             Power state.
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[out] none
 *
 * \retval ARM Driver status.
 *******************************************************************/
int32_t HAL_I2C_PowerControl(ARM_POWER_STATE state, I2C_HandleTypeDef *i2c);

/*!******************************************************************
 * \fn int32_t HAL_I2C_Control(uint32_t control, uint32_t arg, I2C_HandleTypeDef *i2c)
 * \brief Control I2C peripheral.
 *
 * \param[in] uint32_t control                  Control operation.
 * \param[in] uint32_t arg                      Argument of the operation.
 * \param[in] I2C_HandleTypeDef *hi2c           I2C handle.
 * \param[out] none
 *
 * \retval ARM Driver status.
 *******************************************************************/
int32_t HAL_I2C_Control(uint32_t control, uint32_t arg, I2C_HandleTypeDef *i2c);

/*!******************************************************************
 * \fn void HAL_I2C_InitClock(HAL_I2C_Type i2c_id)
 * \brief Initialize I2C clock.
 *
 * \param[in] HAL_I2C_Type                      I2C peripheral ID.       
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_I2C_InitClock(HAL_I2C_Type i2c_id);

#endif /* __HTNB32LXXX_HAL_I2C_H__ */

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
