/**
 *
 * Copyright (c) 2024 HT Micron Semicondutores S.A.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "htnb32lxxx_hal_usart.h"
#include "slpman_qcx212.h"
#include "HT_Peripheral_Config.h"
#include "HT_usart_unilog.h"

/* Function prototypes  ------------------------------------------------------------------*/

// declearation for DMA API
extern void DMA_StopChannelNoWait(uint32_t channel);
extern uint32_t DMA_SetDescriptorTransferLen(uint32_t dcmd, uint32_t len);
extern void DMA_ChannelLoadDescriptorAndRun(uint32_t channel, void* descriptorAddress);
extern uint32_t DMA_ChannelGetCurrentTargetAddress(uint32_t channel, bool sync);

/*!******************************************************************
 * \fn PLAT_CODE_IN_RAM static uint32_t HAL_USART_GetInstanceNumber(USART_HandleTypeDef *usart)
 * \brief Gets USART instance number.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval USART instance number.
 *******************************************************************/
PLAT_CODE_IN_RAM static uint32_t HAL_USART_GetInstanceNumber(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn static int32_t HAL_USART_SetBaudrate (uint32_t baudrate, USART_HandleTypeDef *usart)
 * \brief Sets the USART baudrate.
 *        When uart input clock is 26000000, the supported baudrate is:
 *        300,600,1200,2400,
 *        4800,9600,14400,19200,
 *        28800,38400,56000,57600,
 *        115200,230400,460800,921600,
 *        1000000,1500000,2000000,3000000
 *
 * \param[in] uint32_t baudrate                    USART baudrate.
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval Error status.
 *******************************************************************/
static int32_t HAL_USART_SetBaudrate (uint32_t baudrate, USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn static void HAL_USART_DmaRxConfig(USART_HandleTypeDef *usart)
 * \brief Configures the USART RX to operate in DMA mode.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
static void HAL_USART_DmaRxConfig(USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn PLAT_CODE_IN_RAM static void HAL_USART_DmaUpdateRxConfig(USART_HandleTypeDef *usart, uint32_t targetAddress, uint32_t num)
 * \brief Updates the USART RX in DMA mode.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[in] uint32_t targetAddress               Target address of the RX buffer.
 * \param[in] uint32_t num                         Number of bytes that will be received.
 *
 * \retval none.
 *******************************************************************/
PLAT_CODE_IN_RAM static void HAL_USART_DmaUpdateRxConfig(USART_HandleTypeDef *usart, uint32_t targetAddress, uint32_t num);

/*!******************************************************************
 * \fn static void __attribute__((unused)) HAL_USART_SetupFifo(USART_HandleTypeDef *huart, uint32_t fcr)
 * \brief Set up the USART FIFO.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[in] uint32_t fc                          FCR register value.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
static void __attribute__((unused)) HAL_USART_SetupFifo(USART_HandleTypeDef *huart, uint32_t fcr);

/*!******************************************************************
 * \fn static uint32_t HAL_USART_ReadLineStatus(USART_HandleTypeDef *huart)
 * \brief Read the line status.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval Read line status.
 *******************************************************************/
static uint32_t HAL_USART_ReadLineStatus(USART_HandleTypeDef *huart);

/*!******************************************************************
 * \fn static void HAL_USART_SendByte(USART_HandleTypeDef *huart, uint8_t data)
 * \brief Sends a byte through the USART peripheral.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[in] uint8_t data                         USART TX data.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
static void HAL_USART_SendByte(USART_HandleTypeDef *huart, uint8_t data);

/*!******************************************************************
 * \fn static uint8_t HAL_USART_ReadByte(USART_HandleTypeDef *huart)
 * \brief Reads a byte from the USART peripheral.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval Byte that was read from the USART.
 *******************************************************************/
static uint8_t HAL_USART_ReadByte(USART_HandleTypeDef *huart);

/*!******************************************************************
 * \fn static void HAL_USART_Transmit_IRQn(USART_HandleTypeDef *huart)
 * \brief Handles the USART transmission in interruption mode.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
static void HAL_USART_Transmit_IRQn(USART_HandleTypeDef *huart);

/*!******************************************************************
 * \fn static void HAL_USART_Receive_IRQn(USART_HandleTypeDef *huart)
 * \brief Handles the USART receive process in interruption mode.
 *
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
static void HAL_USART_Receive_IRQn(USART_HandleTypeDef *huart);

#if (RTE_UART0)

/*!******************************************************************
 * \fn void HAL_USART0_IRQHandler(void)
 * \brief USART0 interruption handler.
 *
 * \param[in] none
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART0_IRQHandler(void);

#endif

#if (RTE_UART1)

/*!******************************************************************
 * \fn void HAL_USART1_IRQHandler(void)
 * \brief USART0 interruption handler.
 *
 * \param[in] none
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART1_IRQHandler(void);

#endif

#if (RTE_UART2)

/*!******************************************************************
 * \fn void HAL_USART2_IRQHandler(void)
 * \brief USART0 interruption handler.
 *
 * \param[in] none
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART2_IRQHandler(void);

#endif

/*!******************************************************************
 * \fn void HAL_USART_DmaTxEvent(uint32_t event, USART_HandleTypeDef *usart)
 * \brief USART DMA TX Event handler.
 *
 * \param[in] uint32_t event                       Event that triggered the DMA callback.
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART_DmaTxEvent(uint32_t event, USART_HandleTypeDef *usart);

/*!******************************************************************
 * \fn void HAL_USART_DmaRxEvent(uint32_t event, USART_HandleTypeDef *usart)
 * \brief USART DMA RX Event handler.
 *
 * \param[in] uint32_t event                       Event that triggered the DMA callback.
 * \param[in] USART_HandleTypeDef *usart           USART handle.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
void HAL_USART_DmaRxEvent(uint32_t event, USART_HandleTypeDef *usart);

/* ---------------------------------------------------------------------------------------*/

#ifdef PM_FEATURE_ENABLE
/** \brief Internal used data structure */
typedef struct _usart_database
{
    bool                            isInited;            /**< Whether usart has been initialized */
    struct
    {
        uint32_t DLL;                                    /**< Divisor Latch Low */
        uint32_t DLH;                                    /**< Divisor Latch High */
        uint32_t IER;                                    /**< Interrupt Enable Register */
        uint32_t FCR;                                    /**< FIFO Control Register */
        uint32_t LCR;                                    /**< Line Control Register */
        uint32_t MCR;                                    /**< Modem Control Register */
        uint32_t MFCR;                                   /**< Main Function Control Register */
        uint32_t EFCR;                                   /**< Extended Function Control Register */
        uint32_t ADCR;                                   /**< Auto-baud Detect Control Register*/
    } backup_registers;                                  /**< Backup registers for low power restore */
    bool     autoBaudRateDone;                           /**< Flag indication whether auto baud dection is done */
    uint32_t iir_reg;                                    /**< IIR register for debug purpose */
    uint32_t fcnr_reg;                                   /**< FCNR register for debug purpose */
} usart_database_t;

static usart_database_t g_usartDataBase[USART_INSTANCE_NUM] = {0};

static USART_TypeDef* const g_usartBases[USART_INSTANCE_NUM] = {USART_0, USART_1, USART_2};
#endif

static clock_ID_t g_uartClocks[USART_INSTANCE_NUM*2] = {GPR_UART0APBClk, GPR_UART0FuncClk,
                                                        GPR_UART1APBClk, GPR_UART1FuncClk,
                                                        GPR_UART2APBClk, GPR_UART2FuncClk
                                                        };

static sw_reset_ID_t g_uartResetClocks[USART_INSTANCE_NUM*2] = {GPR_ResetUART0APB, GPR_ResetUART0Func,
                                                                GPR_ResetUART1APB, GPR_ResetUART1Func,
                                                                GPR_ResetUART2APB, GPR_ResetUART2Func,
                                                                };

#ifdef PM_FEATURE_ENABLE
/**
  \brief usart initialization counter, for lower power callback register/de-register
 */
static uint32_t g_usartInitCounter = 0;

/**
  \brief Bitmap of USART working status,
         when all USART instances are not working, we can vote to enter to low power state.
 */
static uint32_t g_usartWorkingStatus = 0;


/**
  \fn        static void USART_EnterLowPowerStatePrepare(void* pdata, slpManLpState state)
  \brief     Perform necessary preparations before sleep.
             After recovering from SLPMAN_SLEEP1_STATE, USART hareware is repowered, we backup
             some registers here first so that we can restore user's configurations after exit.
  \param[in] pdata pointer to user data, not used now
  \param[in] state low power state
 */
static void USART_EnterLowPowerStatePrepare(void* pdata, slpManLpState state) {
    uint32_t i;

    switch (state) {
        case SLPMAN_SLEEP1_STATE:

            for(i = 0; i < USART_INSTANCE_NUM; i++) {
                if(g_usartDataBase[i].isInited == true) {
                    g_usartDataBase[i].backup_registers.IER = g_usartBases[i]->IER;
                    g_usartDataBase[i].backup_registers.LCR = g_usartBases[i]->LCR;
                    g_usartDataBase[i].backup_registers.MCR = g_usartBases[i]->MCR;
                    g_usartDataBase[i].backup_registers.MFCR = g_usartBases[i]->MFCR;
                    g_usartDataBase[i].backup_registers.EFCR = g_usartBases[i]->EFCR;
                    g_usartDataBase[i].backup_registers.ADCR = g_usartBases[i]->ADCR;
                }
            }
            break;
        default:
            break;
    }

}

/**
  \fn        static void USART_ExitLowPowerStateRestore(void* pdata, slpManLpState state)
  \brief     Restore after exit from sleep.
             After recovering from SLPMAN_SLEEP1_STATE, USART hareware is repowered, we restore user's configurations
             by aidding of the stored registers.

  \param[in] pdata pointer to user data, not used now
  \param[in] state low power state

 */
static void USART_ExitLowPowerStateRestore(void* pdata, slpManLpState state) {
    uint32_t i;
    extern bool pmuGetSleepedFlag(void);

    switch (state) {
        case SLPMAN_SLEEP1_STATE:

            // no need to restore if failing to sleep
            if(pmuGetSleepedFlag() == false)
                break;

            for(i = 0; i < USART_INSTANCE_NUM; i++) {
                if(g_usartDataBase[i].isInited == true) {
                    GPR_ClockEnable(g_uartClocks[2*i]);
                    GPR_ClockEnable(g_uartClocks[2*i+1]);

                    if(g_usartDataBase[i].backup_registers.ADCR == 0x3) {
                        // baudrate is set to 500, 26000000/16/(DLH:DLL) = 500 => DLH:DLL = 3250 = 0xCB2
                        g_usartBases[i]->LCR |= USART_LCR_ACCESS_DIVISOR_LATCH_Msk;
                        g_usartBases[i]->DLL = 0xB2;
                        g_usartBases[i]->DLH = 0xC;
                        g_usartBases[i]->LCR &= ~USART_LCR_ACCESS_DIVISOR_LATCH_Msk;
                        g_usartBases[i]->IER = g_usartDataBase[i].backup_registers.IER;
                        g_usartBases[i]->LCR = g_usartDataBase[i].backup_registers.LCR;
                        g_usartBases[i]->MCR = 0x10; //loop back mode
                        g_usartBases[i]->EFCR = 0;
                        g_usartBases[i]->FCR = g_usartDataBase[i].backup_registers.FCR;
                        g_usartBases[i]->MFCR = g_usartDataBase[i].backup_registers.MFCR;
                        g_usartBases[i]->THR = 0xA5;
                    
                    } else {
                        g_usartBases[i]->LCR |= USART_LCR_ACCESS_DIVISOR_LATCH_Msk;
                        g_usartBases[i]->DLL = g_usartDataBase[i].backup_registers.DLL;
                        g_usartBases[i]->DLH = g_usartDataBase[i].backup_registers.DLH;
                        g_usartBases[i]->LCR &= ~USART_LCR_ACCESS_DIVISOR_LATCH_Msk;
                        g_usartBases[i]->IER = g_usartDataBase[i].backup_registers.IER;
                        g_usartBases[i]->LCR = g_usartDataBase[i].backup_registers.LCR;
                        g_usartBases[i]->MCR = g_usartDataBase[i].backup_registers.MCR;
                        g_usartBases[i]->EFCR = g_usartDataBase[i].backup_registers.EFCR;
                        g_usartBases[i]->FCR = g_usartDataBase[i].backup_registers.FCR;
                        g_usartBases[i]->MFCR = g_usartDataBase[i].backup_registers.MFCR;
                    }

                }
            }
            break;

        default:
            break;
    }

}

#define  LOCK_SLEEP(instance, tx, rx)     do                                                                   \
                                          {                                                                    \
                                              g_usartWorkingStatus |= (rx << (2 * instance));                    \
                                              g_usartWorkingStatus |= (tx << (2 * instance + 1));                \
                                              slpManDrvVoteSleep(SLP_VOTE_USART, SLP_ACTIVE_STATE);     \
                                          }                                                                   \
                                          while(0)

#define  CHECK_TO_UNLOCK_SLEEP(instance, tx, rx)      do                                                                  \
                                                      {                                                                   \
                                                          g_usartWorkingStatus &= ~(rx << (2 * instance));                  \
                                                          g_usartWorkingStatus &= ~(tx << (2 * instance + 1));              \
                                                          if(g_usartWorkingStatus == 0)                                   \
                                                              slpManDrvVoteSleep(SLP_VOTE_USART, SLP_SLP1_STATE);    \
                                                      }                                                                   \
                                                      while(0)
#endif

// Driver Version
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_USART_API_VERSION,
    ARM_USART_DRV_VERSION
};

// Driver Capabilities
static const ARM_USART_CAPABILITIES DriverCapabilities = {
    1, /* supports UART (Asynchronous) mode */
    0, /* supports Synchronous Master mode */
    0, /* supports Synchronous Slave mode */
    0, /* supports UART Single-wire mode */
    0, /* supports UART IrDA mode */
    0, /* supports UART Smart Card mode */
    0, /* Smart Card Clock generator available */
    0, /* RTS Flow Control available */
    0, /* CTS Flow Control available */
    0, /* Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE */
    0, /* Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT */
    0, /* RTS Line: 0=not available, 1=available */
    0, /* CTS Line: 0=not available, 1=available */
    0, /* DTR Line: 0=not available, 1=available */
    0, /* DSR Line: 0=not available, 1=available */
    0, /* DCD Line: 0=not available, 1=available */
    0, /* RI Line: 0=not available, 1=available */
    0, /* Signal CTS change event: \ref ARM_USART_EVENT_CTS */
    0, /* Signal DSR change event: \ref ARM_USART_EVENT_DSR */
    0, /* Signal DCD change event: \ref ARM_USART_EVENT_DCD */
    0  /* Signal RI change event: \ref ARM_USART_EVENT_RI */
};

#if (RTE_UART0)

static USART_INFO USART0_Info = {0};
static PIN USART0_pin_tx  = {RTE_UART0_TX_PAD_ID,   RTE_UART0_TX_FUNC};
static PIN USART0_pin_rx  = {RTE_UART0_RX_PAD_ID,   RTE_UART0_RX_FUNC};

#if (RTE_UART0 && USART_UNILOG_SELECT == HAL_USART0_SELECT)
extern ARM_DRIVER_USART Driver_USART0;
#else
ARM_DRIVER_USART Driver_USART0;
#endif

#if (RTE_UART0_CTS_PIN_EN == 1)
static PIN USART0_pin_cts  = {RTE_UART0_CTS_PAD_ID,   RTE_UART0_CTS_FUNC};
#endif
#if (RTE_UART0_RTS_PIN_EN == 1)
static PIN USART0_pin_rts  = {RTE_UART0_RTS_PAD_ID,   RTE_UART0_RTS_FUNC};
#endif

#if (RTE_UART0_TX_IO_MODE == DMA_MODE)

static void HAL_USART0_DmaTxEvent(uint32_t event);
static USART_TX_DMA USART0_DMA_Tx = {
                                    -1,
                                    RTE_UART0_DMA_TX_REQID,
                                    HAL_USART0_DmaTxEvent
                                 };
#endif

#if (RTE_UART0_RX_IO_MODE == DMA_MODE)

static void HAL_USART0_DmaRxEvent(uint32_t event);

static dma_descriptor_t __ALIGNED(16) USART0_DMA_Rx_Descriptor[2];

static USART_RX_DMA USART0_DMA_Rx = {
                                    -1,
                                    RTE_UART0_DMA_RX_REQID,
                                    USART0_DMA_Rx_Descriptor,
                                    HAL_USART0_DmaRxEvent
                                 };

#endif

#if (RTE_UART0_TX_IO_MODE == IRQ_MODE) || (RTE_UART0_RX_IO_MODE == IRQ_MODE) || (RTE_UART0_RX_IO_MODE == DMA_MODE)
static USART_IRQ USART0_IRQ = {
                                PXIC_Uart0_IRQn,
                                HAL_USART0_IRQHandler
                              };
#endif


const USART_HandleTypeDef huart0 = {
    USART_0,
    {
      &USART0_pin_tx,
      &USART0_pin_rx,
#if (RTE_UART0_CTS_PIN_EN == 1)
      &USART0_pin_cts,
#else
      NULL,
#endif
#if (RTE_UART0_RTS_PIN_EN == 1)
      &USART0_pin_rts,
#else
      NULL,
#endif
    },

#if (RTE_UART0_TX_IO_MODE == DMA_MODE)
    &USART0_DMA_Tx,
#else
    NULL,
#endif

#if (RTE_UART0_RX_IO_MODE == DMA_MODE)
    &USART0_DMA_Rx,
#else
    NULL,
#endif
#if (RTE_UART0_TX_IO_MODE == IRQ_MODE) || (RTE_UART0_RX_IO_MODE == IRQ_MODE) || (RTE_UART0_RX_IO_MODE == DMA_MODE)
    &USART0_IRQ,
#else
    NULL,
#endif
    USART0_TX_TRIG_LVL,
    USART0_RX_TRIG_LVL,
    &USART0_Info,
#if (RTE_UART0_TX_IO_MODE == UNILOG_MODE)
    1,
#else
    0
#endif
};

#endif

#if (RTE_UART1)

static USART_INFO USART1_Info  = {0};
static PIN USART1_pin_tx  = {RTE_UART1_TX_PAD_ID,   RTE_UART1_TX_FUNC};
static PIN USART1_pin_rx  = {RTE_UART1_RX_PAD_ID,   RTE_UART1_RX_FUNC};

#if (RTE_UART1 && USART_UNILOG_SELECT == HAL_USART1_SELECT)
extern ARM_DRIVER_USART Driver_USART1;
#else
ARM_DRIVER_USART Driver_USART1;
#endif

#if (RTE_UART1_CTS_PIN_EN == 1)
static PIN USART1_pin_cts  = {RTE_UART1_CTS_PAD_ID,   RTE_UART1_CTS_FUNC};
#endif
#if (RTE_UART1_RTS_PIN_EN == 1)
static PIN USART1_pin_rts  = {RTE_UART1_RTS_PAD_ID,   RTE_UART1_RTS_FUNC};
#endif

#if (RTE_UART1_TX_IO_MODE == DMA_MODE)

static void HAL_USART1_DmaTxEvent(uint32_t event);
static USART_TX_DMA USART1_DMA_Tx = {
                                    -1,
                                    RTE_UART1_DMA_TX_REQID,
                                    HAL_USART1_DmaTxEvent
                                 };
#endif

#if (RTE_UART1_RX_IO_MODE == DMA_MODE)

static void HAL_USART1_DmaRxEvent(uint32_t event);

static dma_descriptor_t __ALIGNED(16) USART1_DMA_Rx_Descriptor[2];

static USART_RX_DMA USART1_DMA_Rx = {
                                    -1,
                                    RTE_UART1_DMA_RX_REQID,
                                    USART1_DMA_Rx_Descriptor,
                                    HAL_USART1_DmaRxEvent
                                 };

#endif

#if (RTE_UART1_TX_IO_MODE == IRQ_MODE) || (RTE_UART1_RX_IO_MODE == IRQ_MODE) || (RTE_UART1_RX_IO_MODE == DMA_MODE)
static USART_IRQ USART1_IRQ = {
                                PXIC_Uart1_IRQn,
                                HAL_USART1_IRQHandler
                              };
#endif

const USART_HandleTypeDef huart1 = {
    USART_1,
    {
      &USART1_pin_tx,
      &USART1_pin_rx,
#if (RTE_UART1_CTS_PIN_EN == 1)
      &USART1_pin_cts,
#else
      NULL,
#endif
#if (RTE_UART1_RTS_PIN_EN == 1)
      &USART1_pin_rts,
#else
      NULL,
#endif
    },

#if (RTE_UART1_TX_IO_MODE == DMA_MODE)
    &USART1_DMA_Tx,
#else
    NULL,
#endif

#if (RTE_UART1_RX_IO_MODE == DMA_MODE)
    &USART1_DMA_Rx,
#else
    NULL,
#endif
#if (RTE_UART1_TX_IO_MODE == IRQ_MODE) || (RTE_UART1_RX_IO_MODE == IRQ_MODE) || (RTE_UART1_RX_IO_MODE == DMA_MODE)
    &USART1_IRQ,
#else
    NULL,
#endif
    USART1_TX_TRIG_LVL,
    USART1_RX_TRIG_LVL,
    &USART1_Info,
#if (RTE_UART1_TX_IO_MODE == UNILOG_MODE)
    1,
#else
    0
#endif
};
#endif

#if (RTE_UART2)

static USART_INFO USART2_Info  = {0};
static PIN USART2_pin_tx  = {RTE_UART2_TX_PAD_ID,   RTE_UART2_TX_FUNC};
static PIN USART2_pin_rx  = {RTE_UART2_RX_PAD_ID,   RTE_UART2_RX_FUNC};

#if (RTE_UART2 && USART_UNILOG_SELECT == HAL_USART2_SELECT)
extern ARM_DRIVER_USART Driver_USART2;
#else
ARM_DRIVER_USART Driver_USART2;
#endif

#if (RTE_UART2_CTS_PIN_EN == 1)
static PIN USART2_pin_cts  = {RTE_UART2_CTS_BIT,   RTE_UART2_CTS_FUNC};
#endif
#if (RTE_UART2_RTS_PIN_EN == 1)
static PIN USART2_pin_rts  = {RTE_UART2_RTS_BIT,   RTE_UART2_RTS_FUNC};
#endif

#if (RTE_UART2_TX_IO_MODE == DMA_MODE)

static void HAL_USART2_DmaTxEvent(uint32_t event);
static USART_TX_DMA USART2_DMA_Tx = {
                                    -1,
                                    RTE_UART2_DMA_TX_REQID,
                                    HAL_USART2_DmaTxEvent
                                 };
#endif

#if (RTE_UART2_RX_IO_MODE == DMA_MODE)

static void HAL_USART2_DmaRxEvent(uint32_t event);

static dma_descriptor_t __ALIGNED(16) USART2_DMA_Rx_Descriptor[2];

static USART_RX_DMA USART2_DMA_Rx = {
                                    -1,
                                    RTE_UART2_DMA_RX_REQID,
                                    USART2_DMA_Rx_Descriptor,
                                    HAL_USART2_DmaRxEvent
                                 };

#endif

#if (RTE_UART2_TX_IO_MODE == IRQ_MODE) || (RTE_UART2_RX_IO_MODE == IRQ_MODE) || (RTE_UART2_RX_IO_MODE == DMA_MODE)
static USART_IRQ USART2_IRQ = {
                                PXIC_Uart2_IRQn,
                                HAL_USART2_IRQHandler
                              };
#endif

const USART_HandleTypeDef huart2 = {
    USART_2,
    {
      &USART2_pin_tx,
      &USART2_pin_rx,
#if (RTE_UART2_CTS_PIN_EN == 1)
      &USART2_pin_cts,
#else
      NULL,
#endif
#if (RTE_UART2_RTS_PIN_EN == 1)
      &USART2_pin_rts,
#else
      NULL,
#endif
    },

#if (RTE_UART2_TX_IO_MODE == DMA_MODE)
    &USART2_DMA_Tx,
#else
    NULL,
#endif

#if (RTE_UART2_RX_IO_MODE == DMA_MODE)
    &USART2_DMA_Rx,
#else
    NULL,
#endif
#if (RTE_UART2_TX_IO_MODE == IRQ_MODE) || (RTE_UART2_RX_IO_MODE == IRQ_MODE) || (RTE_UART2_RX_IO_MODE == DMA_MODE)
    &USART2_IRQ,
#else
    NULL,
#endif
    USART2_TX_TRIG_LVL,
    USART2_RX_TRIG_LVL,
    &USART2_Info,
#if (RTE_UART2_TX_IO_MODE == UNILOG_MODE)
    1,
#else
    0
#endif
};
#endif

static dma_transfer_config dmaTxConfig = {NULL, NULL,
                                       DMA_FlowControlTarget, DMA_AddressIncrementSource,
                                       DMA_DataWidthOneByte, DMA_Burst16Bytes, 0
                                      };

/* Variable Declarations  ----------------------------------------------------------------*/

uint8_t *usart_tx_buffer = NULL;
uint8_t *usart_rx_buffer = NULL;
volatile uint32_t usart_tx_buffer_size = 0;
volatile uint32_t usart_rx_buffer_size = 0;
volatile USART_DMA_TypeDef dma_event = USART_DMA_NONE_EVENT;

ARM_DRIVER_USART *UsartPrintHandle = NULL;

/* ---------------------------------------------------------------------------------------*/

ARM_DRIVER_VERSION ARM_USART_GetVersion(void) {
    return DriverVersion;
}

ARM_USART_CAPABILITIES HAL_USART_GetCapabilities(USART_HandleTypeDef *usart) {
    return DriverCapabilities;
}

PLAT_CODE_IN_RAM static uint32_t HAL_USART_GetInstanceNumber(USART_HandleTypeDef *usart) {
    return ((uint32_t)usart->reg - (uint32_t)USART_0) >> 16;
}

static int32_t HAL_USART_SetBaudrate (uint32_t baudrate, USART_HandleTypeDef *usart) {
    uint8_t frac = 0;
    uint32_t uart_clock = 0;
    uint32_t div, instance;
    int32_t i;

    instance = HAL_USART_GetInstanceNumber(usart);

    uart_clock = GPR_GetClockFreq(g_uartClocks[instance*2+1]);

    if(baudrate == 0) {
#ifdef PM_FEATURE_ENABLE
        if(slpManGetLastSlpState() == SLP_ACTIVE_STATE)
#else
        if(1)
#endif
        {
            usart->reg->ADCR = 0x3;
        }
        else {
            // only need to delay when wakeup from sleep2 or hib
            usart->reg->LCR |= USART_LCR_ACCESS_DIVISOR_LATCH_Msk;
            usart->reg->DLL = 0xB2;
            usart->reg->DLH = 0xC;
            usart->reg->LCR &= ~USART_LCR_ACCESS_DIVISOR_LATCH_Msk;
            usart->reg->MCR = 0x10; //loop back mode
            usart->reg->EFCR = 0;
        }

    } else {
        /*
         * formula to calculate baudrate, baudrate = clock_in / (prescalar * divisor_value),
         * where prescalar = MFCR_PRESCALE_FACTOR(4,8,16), divisor_value = DLH:DLL.EFCR_FRAC
         */
        for(i = 0; i <= 2; i++) {
            div = (1 << i) * uart_clock / baudrate;
            frac = div & 0xf;
            div >>= 4;
            // Integer part of divisor value shall not be zero, otherwise, the result is invalid
            if (div != 0)
                break;
        }

        if (i > 2)
            return ARM_DRIVER_ERROR_PARAMETER;

        // Disable uart first
        usart->reg->MFCR &= ~USART_MFCR_UART_EN_Msk;

        // Enable latch bit to change divisor
        usart->reg->LCR |= USART_LCR_ACCESS_DIVISOR_LATCH_Msk;
        usart->reg->MFCR = ((usart->reg->MFCR & ~USART_MFCR_PRESCALE_FACTOR_Msk) | QCOM_VAL2FLD(USART_MFCR_PRESCALE_FACTOR, i));
        usart->reg->DLL = (div >> 0) & 0xff;
        usart->reg->DLH = (div >> 8) & 0xff;
        usart->reg->EFCR = ((usart->reg->EFCR & ~USART_EFCR_FRAC_DIVISOR_Msk) | (frac << USART_EFCR_FRAC_DIVISOR_Pos));
        // Reset latch bit
        usart->reg->LCR &= (~USART_LCR_ACCESS_DIVISOR_LATCH_Msk);

#ifdef PM_FEATURE_ENABLE
        // backup setting
        g_usartDataBase[instance].backup_registers.DLL = (div >> 0) & 0xff;
        g_usartDataBase[instance].backup_registers.DLH = (div >> 8) & 0xff;
#endif
    }

    usart->info->baudrate = baudrate;

    return ARM_DRIVER_OK;
}

uint32_t HAL_USART_GetBaudRate(USART_HandleTypeDef *usart) {
    return usart->info->baudrate;
}

static void HAL_USART_DmaRxConfig(USART_HandleTypeDef *usart) {

    dma_transfer_config dmaConfig;
    dma_extra_config extraConfig;

    dmaConfig.addressIncrement              = DMA_AddressIncrementTarget;
    dmaConfig.burstSize                     = DMA_Burst8Bytes;
    dmaConfig.dataWidth                     = DMA_DataWidthOneByte;
    dmaConfig.flowControl                   = DMA_FlowControlSource;
    dmaConfig.sourceAddress                 = (void*)&(usart->reg->RBR);
    dmaConfig.targetAddress                 = NULL;
    dmaConfig.totalLength                   = UART_DMA_BURST_SIZE;

    extraConfig.stopDecriptorFetch          = false;
    extraConfig.enableStartInterrupt        = false;
    extraConfig.enableEndInterrupt          = true;
    extraConfig.nextDesriptorAddress        = &usart->dma_rx->descriptor[1];

    DMA_BuildDescriptor(&usart->dma_rx->descriptor[0], &dmaConfig, &extraConfig);

    extraConfig.stopDecriptorFetch          = true;
    extraConfig.nextDesriptorAddress        = &usart->dma_rx->descriptor[0];

    DMA_BuildDescriptor(&usart->dma_rx->descriptor[1], &dmaConfig, &extraConfig);

    DMA_ResetChannel(usart->dma_rx->channel);

}

ARM_USART_MODEM_STATUS HAL_USART_GetModemStatus(USART_HandleTypeDef *usart) {
    ARM_USART_MODEM_STATUS status = {0};
    return status;
}

PLAT_CODE_IN_RAM static void HAL_USART_DmaUpdateRxConfig(USART_HandleTypeDef *usart, uint32_t targetAddress, uint32_t num) {
    usart->dma_rx->descriptor[0].TAR = targetAddress;
    usart->dma_rx->descriptor[1].TAR = usart->dma_rx->descriptor[0].TAR + UART_DMA_BURST_SIZE;
    usart->dma_rx->descriptor[1].CMDR = DMA_SetDescriptorTransferLen(usart->dma_rx->descriptor[1].CMDR, num - UART_DMA_BURST_SIZE);
}

int32_t HAL_USART_Initialize(ARM_USART_SignalEvent_t cb_event, USART_HandleTypeDef *usart) {
    int32_t returnCode;
#ifdef PM_FEATURE_ENABLE
    uint32_t instance;
#endif

    if (usart->info->flags & USART_FLAG_INITIALIZED)
        return ARM_DRIVER_OK;

    // Pin initialize
    pad_config_t config;
    PAD_GetDefaultConfig(&config);

    config.mux = usart->pins.pin_tx->funcNum;
    PAD_SetPinConfig(usart->pins.pin_tx->pinNum, &config);

    config.pullSelect = PAD_PullInternal;
    config.pullUpEnable = PAD_PullUpEnable;
    config.pullDownEnable = PAD_PullDownDisable;
    config.mux = usart->pins.pin_rx->funcNum;

    PAD_SetPinConfig(usart->pins.pin_rx->pinNum, &config);

    if(usart->pins.pin_cts) {
        config.mux = usart->pins.pin_cts->funcNum;
        PAD_SetPinConfig(usart->pins.pin_cts->pinNum, &config);
    }

    if(usart->pins.pin_rts) {
        config.mux = usart->pins.pin_rts->funcNum;
        PAD_SetPinConfig(usart->pins.pin_rts->pinNum, &config);
    }

#ifdef PM_FEATURE_ENABLE
    instance = HAL_USART_GetInstanceNumber(usart);
    g_usartDataBase[instance].isInited = true;
#endif

    // Initialize USART run-time resources
    usart->info->cb_event = cb_event;
    memset(&(usart->info->rx_status), 0, sizeof(USART_STATUS));

    usart->info->xfer.send_active           = 0U;
    usart->info->xfer.tx_def_val            = 0U;

    if (usart->dma_tx) {
        DMA_Init();

        returnCode = DMA_OpenChannel();

        if (returnCode == ARM_DMA_ERROR_CHANNEL_ALLOC)
            return ARM_DRIVER_ERROR;
        else
            usart->dma_tx->channel = returnCode;

        DMA_ChannelSetRequestSource(usart->dma_tx->channel, (dma_request_source_t)usart->dma_tx->request);
        DMA_ChannelRigisterCallback(usart->dma_tx->channel, usart->dma_tx->callback);
    }
    
    if (usart->dma_rx) {
        DMA_Init();

        returnCode = DMA_OpenChannel();

        if (returnCode == ARM_DMA_ERROR_CHANNEL_ALLOC)
            return ARM_DRIVER_ERROR;
        else
            usart->dma_rx->channel = returnCode;

        DMA_ChannelSetRequestSource(usart->dma_rx->channel, (dma_request_source_t)usart->dma_rx->request);
        HAL_USART_DmaRxConfig(usart);
        DMA_ChannelRigisterCallback(usart->dma_rx->channel, usart->dma_rx->callback);
    }

    usart->info->flags = USART_FLAG_INITIALIZED;  // USART is initialized

#ifdef PM_FEATURE_ENABLE
    g_usartInitCounter++;

    if(g_usartInitCounter == 1) {
        g_usartWorkingStatus = 0;
        slpManRegisterPredefinedBackupCb(SLP_CALLBACK_USART_MODULE, USART_EnterLowPowerStatePrepare, NULL, SLPMAN_SLEEP1_STATE);
        slpManRegisterPredefinedRestoreCb(SLP_CALLBACK_USART_MODULE, USART_ExitLowPowerStateRestore, NULL, SLPMAN_SLEEP1_STATE);
    }
#endif
    return ARM_DRIVER_OK;
}

int32_t HAL_USART_Uninitialize(USART_HandleTypeDef *usart) {
#ifdef PM_FEATURE_ENABLE
    uint32_t instance;
    instance = HAL_USART_GetInstanceNumber(usart);
#endif

    usart->info->flags = 0U;
    usart->info->cb_event = NULL;

    if(usart->dma_tx)
        DMA_CloseChannel(usart->dma_tx->channel);

    if(usart->dma_rx)
        DMA_CloseChannel(usart->dma_rx->channel);

#ifdef PM_FEATURE_ENABLE

    g_usartDataBase[instance].isInited = false;

    g_usartInitCounter--;

    if(g_usartInitCounter == 0) {
        g_usartWorkingStatus = 0;
        slpManUnregisterPredefinedBackupCb(SLP_CALLBACK_USART_MODULE);
        slpManUnregisterPredefinedRestoreCb(SLP_CALLBACK_USART_MODULE);
    }
#endif

    return ARM_DRIVER_OK;
}

int32_t HAL_USART_PowerControl(ARM_POWER_STATE state, USART_HandleTypeDef *usart) {
    uint32_t instance;
    uint32_t val = 0;

    instance = HAL_USART_GetInstanceNumber(usart);

    switch (state) {
        case ARM_POWER_OFF:

            // Reset USART registers
            GPR_SWReset(g_uartResetClocks[instance*2]);
            GPR_SWReset(g_uartResetClocks[instance*2+1]);

            // DMA disable
            if(usart->dma_tx)
                DMA_StopChannel(usart->dma_tx->channel, false);
            if(usart->dma_rx)
                DMA_StopChannel(usart->dma_rx->channel, false);


            // Disable power to usart clock
            GPR_ClockDisable(g_uartClocks[instance*2]);
            GPR_ClockDisable(g_uartClocks[instance*2+1]);

            // Clear driver variables
            memset(&(usart->info->rx_status), 0, sizeof(USART_STATUS));
            usart->info->mode             = 0U;
            usart->info->xfer.send_active = 0U;

            // Disable USART IRQ
            if(usart->usart_irq) {
                XIC_ClearPendingIRQ(usart->usart_irq->irq_num);
                XIC_DisableIRQ(usart->usart_irq->irq_num);
            }

            usart->info->flags &= ~(USART_FLAG_POWERED | USART_FLAG_CONFIGURED);

            break;

        case ARM_POWER_LOW:
            return ARM_DRIVER_ERROR_UNSUPPORTED;

        case ARM_POWER_FULL:
            if ((usart->info->flags & USART_FLAG_INITIALIZED) == 0U)
                return ARM_DRIVER_ERROR;
            
            if (usart->info->flags & USART_FLAG_POWERED)
                return ARM_DRIVER_OK;
            
            // Enable power to usart clock
            GPR_ClockEnable(g_uartClocks[instance*2]);
            GPR_ClockEnable(g_uartClocks[instance*2+1]);

            // Disable interrupts
            usart->reg->IER = 0U;
            // Clear driver variables
            memset(&(usart->info->rx_status), 0, sizeof(USART_STATUS));
            usart->info->mode             = 0U;
            usart->info->xfer.send_active = 0U;

            // Configure FIFO Control register
            val = USART_FCR_FIFO_EN_Msk | USART_FCR_RESET_RX_FIFO_Msk | USART_FCR_RESET_TX_FIFO_Msk;

            switch(usart->rx_fifo_trig_lvl) {
                case RX_FIFO_TRIG_LVL_8BYTE:
                    val |= (1U << USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos);
                    break;

                case RX_FIFO_TRIG_LVL_16BYTE:
                    val |= (2U << USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos);
                    break;

                case RX_FIFO_TRIG_LVL_30BYTE:
                    val |= (3U << USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos);
                    break;
                default:
                    break;
            }

            switch(usart->tx_fifo_trig_lvl) {
                case TX_FIFO_TRIG_LVL_2BYTE:
                    val |= (1U << USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos);
                    break;

                case TX_FIFO_TRIG_LVL_8BYTE:
                    val |= (2U << USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos);
                    break;

                case TX_FIFO_TRIG_LVL_16BYTE:
                    val |= (3U << USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos);
                    break;
                default:
                    break;
            }

            usart->reg->FCR = val;

#ifdef PM_FEATURE_ENABLE
            g_usartDataBase[instance].backup_registers.FCR = val;
#endif

            if(usart->dma_tx || usart->dma_rx || usart->is_unilog_mode == 1)
                usart->reg->MFCR |= USART_MFCR_DMA_EN_Msk;

            if(usart->usart_irq) {
                XIC_SetVector(usart->usart_irq->irq_num, usart->usart_irq->cb_irq);
                XIC_EnableIRQ(usart->usart_irq->irq_num);
                XIC_SuppressOvfIRQ(usart->usart_irq->irq_num);
            }

            usart->info->flags |= USART_FLAG_POWERED;  // USART is powered on

            break;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    return ARM_DRIVER_OK;
}

int32_t HAL_USART_SetModemControl(ARM_USART_MODEM_CONTROL control, USART_HandleTypeDef *usart) {
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

int32_t HAL_USART_GetTxCount(USART_HandleTypeDef *usart) {
    uint32_t cnt;
    if (!(usart->info->flags & USART_FLAG_CONFIGURED))
        return 0U;
    if(usart->dma_tx)
        cnt = DMA_ChannelGetCount(usart->dma_tx->channel);
    else
        cnt = usart->info->xfer.tx_cnt;
    return cnt;
}

PLAT_CODE_IN_RAM int32_t HAL_USART_GetRxCount(USART_HandleTypeDef *usart) {
    if (!(usart->info->flags & USART_FLAG_CONFIGURED))
        return 0U;
    return usart->info->xfer.rx_cnt;
}

int32_t HAL_USART_Control(uint32_t control, uint32_t arg, USART_HandleTypeDef *usart) {
    uint32_t mode, val, mfcr;
    uint8_t lcr = usart->reg->LCR;

    switch (control & ARM_USART_CONTROL_Msk) {
        // Control TX
        case ARM_USART_CONTROL_TX:
            return ARM_DRIVER_OK;
        // Control RX
        case ARM_USART_CONTROL_RX:
            return ARM_DRIVER_OK;
        // Control break
        case ARM_USART_CONTROL_BREAK:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        // Abort Send
        case ARM_USART_ABORT_SEND:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        // Abort receive
        case ARM_USART_ABORT_RECEIVE:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        // Abort transfer
        case ARM_USART_ABORT_TRANSFER:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        case ARM_USART_MODE_ASYNCHRONOUS:
            mode = ARM_USART_MODE_ASYNCHRONOUS;
            break;
        // Flush TX fifo
        case ARM_USART_CONTROL_FLUSH_TX:

            if(usart->reg->MFCR & USART_MFCR_AUTO_FLOW_CTS_EN_Msk) {
                while(((usart->reg->LSR & USART_LSR_TX_EMPTY_Msk) == 0) && ((usart->reg->MSR & USART_MSR_CTS_Msk) == USART_MSR_CTS_Msk));
            } else {
                while((usart->reg->LSR & USART_LSR_TX_EMPTY_Msk) == 0);
            }
            return ARM_DRIVER_OK;

        case ARM_USART_CONTROL_PURGE_COMM:

            mfcr = usart->reg->MFCR;
            usart->reg->MFCR = 0;

            // reconfigure FIFO Control register
            val = USART_FCR_FIFO_EN_Msk | USART_FCR_RESET_RX_FIFO_Msk | USART_FCR_RESET_TX_FIFO_Msk;

            switch(usart->rx_fifo_trig_lvl) {
                case RX_FIFO_TRIG_LVL_8BYTE:
                    val |= (1U << USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos);
                    break;

                case RX_FIFO_TRIG_LVL_16BYTE:
                    val |= (2U << USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos);
                    break;

                case RX_FIFO_TRIG_LVL_30BYTE:
                    val |= (3U << USART_FCR_RX_FIFO_AVAIL_TRIG_LEVEL_Pos);
                    break;
                default:
                    break;
            }

            switch(usart->tx_fifo_trig_lvl) {
                case TX_FIFO_TRIG_LVL_2BYTE:
                    val |= (1U << USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos);
                    break;

                case TX_FIFO_TRIG_LVL_8BYTE:
                    val |= (2U << USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos);
                    break;

                case TX_FIFO_TRIG_LVL_16BYTE:
                    val |= (3U << USART_FCR_TX_FIFO_EMPTY_TRIG_LEVEL_Pos);
                    break;
                default:
                    break;
            }

            usart->reg->FCR = val;
            usart->reg->MFCR = mfcr;

            return ARM_DRIVER_OK;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (control & ARM_USART_DATA_BITS_Msk) {
        case ARM_USART_DATA_BITS_5:
            lcr &= ~USART_LCR_CHAR_LEN_Msk;
            break;
        case ARM_USART_DATA_BITS_6:
            lcr &= ~USART_LCR_CHAR_LEN_Msk;
            lcr |= 1U;
            break;
        case ARM_USART_DATA_BITS_7:
            lcr &= ~USART_LCR_CHAR_LEN_Msk;
            lcr |= 2U;
            break;
        case ARM_USART_DATA_BITS_8:
            lcr &= ~USART_LCR_CHAR_LEN_Msk;
            lcr |= 3U;
            break;
        default:
            return ARM_USART_ERROR_DATA_BITS;
    }

    // USART Parity
    switch (control & ARM_USART_PARITY_Msk) {
        case ARM_USART_PARITY_NONE:
            lcr &= ~USART_LCR_PARITY_EN_Msk;
            break;
        case ARM_USART_PARITY_EVEN:
            lcr |= (USART_LCR_PARITY_EN_Msk | USART_LCR_EVEN_PARITY_Msk);
            break;
        case ARM_USART_PARITY_ODD:
            lcr |= USART_LCR_PARITY_EN_Msk;
            lcr &= ~USART_LCR_EVEN_PARITY_Msk;
            break;
        default:
            return (ARM_USART_ERROR_PARITY);
    }

    // USART Stop bits
    switch (control & ARM_USART_STOP_BITS_Msk) {
        case ARM_USART_STOP_BITS_1:
            lcr &=~ USART_LCR_STOP_BIT_NUM_Msk;
            break;
        case ARM_USART_STOP_BITS_1_5:
            if ((control & ARM_USART_DATA_BITS_Msk) == ARM_USART_DATA_BITS_5) {
                lcr |= USART_LCR_STOP_BIT_NUM_Msk;
                break;
            }
            else
                return ARM_USART_ERROR_STOP_BITS;
                
        case ARM_USART_STOP_BITS_2:
            lcr |= USART_LCR_STOP_BIT_NUM_Msk;
            break;
        default:
            return ARM_USART_ERROR_STOP_BITS;
    }

    // work around to suppress jitter of baudrate change interrupt
    if(usart->usart_irq)
        XIC_DisableIRQ(usart->usart_irq->irq_num);

    // USART Flow Control
    switch (control & ARM_USART_FLOW_CONTROL_Msk) {
        case ARM_USART_FLOW_CONTROL_NONE:
        case ARM_USART_FLOW_CONTROL_RTS:
        case ARM_USART_FLOW_CONTROL_CTS:
            break;
        case ARM_USART_FLOW_CONTROL_RTS_CTS:
            usart->reg->MFCR |= (USART_MFCR_AUTO_FLOW_RTS_EN_Msk | USART_MFCR_AUTO_FLOW_CTS_EN_Msk);
            break;
    }

    // USART Baudrate
    if(ARM_DRIVER_OK != HAL_USART_SetBaudrate (arg, usart))
        return ARM_USART_ERROR_BAUDRATE;

    // Configuration is OK - Mode is valid
    usart->info->mode = mode;

    usart->reg->LCR = lcr;
    // usart enable
    usart->reg->MFCR |= USART_MFCR_UART_EN_Msk;

#ifdef PM_FEATURE_ENABLE
    uint32_t instance = HAL_USART_GetInstanceNumber(usart);

    g_usartDataBase[instance].backup_registers.MFCR = usart->reg->MFCR;

    // enable loopback mode to delay a while when auto baud is enabled after wakeup from sleep2 or hib
    if((usart->info->baudrate == 0) && slpManGetLastSlpState() != SLP_ACTIVE_STATE) {
        usart->reg->THR = 0xA5;
    }

#endif
    
    if(usart->usart_irq)
        XIC_EnableIRQ(usart->usart_irq->irq_num);

    usart->info->flags |= USART_FLAG_CONFIGURED;
    return ARM_DRIVER_OK;
}

ARM_USART_STATUS __attribute__((unused)) HAL_USART_GetStatus(USART_HandleTypeDef *usart) {
    ARM_USART_STATUS status;

    status.tx_busy          = usart->info->xfer.send_active;
    status.rx_busy          = usart->info->rx_status.rx_busy;
    status.tx_underflow     = 0U;
    status.rx_overflow      = usart->info->rx_status.rx_overflow;
    status.rx_break         = usart->info->rx_status.rx_break;
    status.rx_framing_error = usart->info->rx_status.rx_framing_error;
    status.rx_parity_error  = usart->info->rx_status.rx_parity_error;
    status.is_send_block    = (usart->dma_tx == NULL);
    return status;
}

static void __attribute__((unused)) HAL_USART_SetupFifo(USART_HandleTypeDef *huart, uint32_t fcr) {
    huart->reg->FCR = fcr;
}

void HAL_USART_IRQnDisable(USART_HandleTypeDef *huart, uint32_t intMask) {
    huart->reg->IER &= ~intMask;
}

void HAL_USART_IRQnEnable(USART_HandleTypeDef *huart, uint32_t intMask) {
    huart->reg->IER = intMask;
}

static void HAL_USART_SendByte(USART_HandleTypeDef *huart, uint8_t data) {
    huart->reg->THR = (uint32_t)data;
}

static uint32_t HAL_USART_ReadLineStatus(USART_HandleTypeDef *huart) {
    return huart->reg->LSR;
}

int32_t HAL_USART_Transfer(USART_HandleTypeDef *huart, const void *data_out, void *data_in, uint8_t size) {
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

int32_t HAL_USART_Send(USART_HandleTypeDef *huart, uint8_t *data, uint32_t size) {
	int32_t sent = 0;

	/* Send until the transmit FIFO is full or out of bytes */
	while ((sent < size) && ((HAL_USART_ReadLineStatus(huart) & USART_LSR_TX_DATA_REQ_Msk) != 0)) {
		HAL_USART_SendByte(huart, *data);
		data++;
		sent++;
	}

	return sent;
}

int32_t HAL_USART_SendPolling(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size) {
	int32_t pass;

	while (size > 0) {
		pass = HAL_USART_Send(huart, pTxBuff, size);
		size -= pass;
		pTxBuff += pass;
	}

    return ARM_DRIVER_OK;
}

static uint8_t HAL_USART_ReadByte(USART_HandleTypeDef *huart) {
    return (uint8_t)(huart->reg->RBR & USART_RBR_RX_BUF_Msk);
}

int32_t HAL_USART_ReceivePolling(USART_HandleTypeDef *huart, uint8_t *pRxBuff, uint32_t size) {
	int32_t readBytes = 0;

	while ((readBytes < size)) {
        while (!(HAL_USART_ReadLineStatus(huart) & USART_LSR_RX_DATA_READY_Msk));
        pRxBuff[readBytes] = HAL_USART_ReadByte(huart);
		readBytes++;
	}

    return ARM_DRIVER_OK;
}

int32_t HAL_USART_Transmit_DMA(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size) {
    uint32_t mask;
#ifdef PM_FEATURE_ENABLE
    uint32_t instance = HAL_USART_GetInstanceNumber(huart);
#endif

    if ((pTxBuff == NULL) || (size == 0U))
        return ARM_DRIVER_ERROR_PARAMETER;
    if ((huart->info->flags & USART_FLAG_CONFIGURED) == 0U)
        return ARM_DRIVER_ERROR;

#ifdef PM_FEATURE_ENABLE
    if(huart->reg->MCR == 0x10)
        return ARM_DRIVER_OK;

    if((huart->reg->ADCR & USART_ADCR_AUTO_BAUD_INT_EN_Msk) && (g_usartDataBase[instance].autoBaudRateDone == false)) {
        if(huart->info->cb_event && huart->dma_tx)
            huart->info->cb_event(ARM_USART_EVENT_SEND_COMPLETE);

        return ARM_DRIVER_OK;
    }
#endif

    mask = SaveAndSetIRQMask();
    if (huart->info->xfer.send_active != 0) {
        RestoreIRQMask(mask);
        return ARM_DRIVER_ERROR_BUSY;
    }

    huart->info->xfer.send_active = 1U;
    RestoreIRQMask(mask);

    // Save transmit buffer info
    huart->info->xfer.tx_buf = pTxBuff;
    huart->info->xfer.tx_num = size;
    huart->info->xfer.tx_cnt = 0U;

    // wait until tx is empty
    while((huart->reg->LSR & USART_LSR_TX_EMPTY_Msk) == 0);

#ifdef PM_FEATURE_ENABLE
    mask = SaveAndSetIRQMask();
    LOCK_SLEEP(instance, 1, 0);
    RestoreIRQMask(mask);
#endif

    if(size == 1) {
        mask = SaveAndSetIRQMask();
    
        huart->reg->IER |= USART_IER_TX_DATA_REQ_Msk;
        huart->reg->THR = huart->info->xfer.tx_buf[0];
    
        RestoreIRQMask(mask);
   
    } else {
        dmaTxConfig.sourceAddress = (void *)pTxBuff;
        dmaTxConfig.targetAddress = (void *)&(huart->reg->THR);
        dmaTxConfig.totalLength = size-1;
        
        // Configure tx DMA and start it
        DMA_TransferSetup(huart->dma_tx->channel, &dmaTxConfig);
        DMA_EnableChannelInterrupts(huart->dma_tx->channel, DMA_EndInterruptEnable);
        DMA_StartChannel(huart->dma_tx->channel);
    }

    return ARM_DRIVER_OK;
}

void HAL_USART_Transmit_IT(USART_HandleTypeDef *huart, uint8_t *pTxBuff, uint32_t size) {
    usart_tx_buffer = pTxBuff;
    usart_tx_buffer_size = size;

    HAL_USART_IRQnDisable(huart, USART_IER_TX_DATA_REQ_Msk);

	/* Fill FIFO until full or until TX buffer is empty */
	while ((HAL_USART_ReadLineStatus(huart) & USART_LSR_TX_DATA_REQ_Msk) && (usart_tx_buffer_size > 0)) {
		HAL_USART_SendByte(huart, *usart_tx_buffer);
        usart_tx_buffer++;
        usart_tx_buffer_size--;
	}

    HAL_USART_IRQnEnable(huart, USART_IER_TX_DATA_REQ_Msk);
}

static void HAL_USART_Transmit_IRQn(USART_HandleTypeDef *huart) {

    HAL_USART_IRQnDisable(huart, USART_IER_TX_DATA_REQ_Msk);

	/* Fill FIFO until full or until TX buffer is empty */
	while ((HAL_USART_ReadLineStatus(huart) & USART_LSR_TX_DATA_REQ_Msk) && (usart_tx_buffer_size > 0)) {
		HAL_USART_SendByte(huart, *usart_tx_buffer);
        usart_tx_buffer++;
        usart_tx_buffer_size--;
	}

    HAL_USART_IRQnEnable(huart, USART_IER_TX_DATA_REQ_Msk);
}

int32_t HAL_USART_Receive_DMA(USART_HandleTypeDef *huart, uint8_t *pRxBuff, uint32_t size) {
    if ((pRxBuff == NULL) || size == 0U)
        return ARM_DRIVER_ERROR_PARAMETER;

    // save num of data to be received
    huart->info->xfer.rx_num = size;
    huart->info->xfer.rx_buf = pRxBuff;
    huart->info->xfer.rx_cnt = 0U;
    
    huart->reg->IER |= USART_IER_RX_TIMEOUT_Msk   | USART_IER_RX_LINE_STATUS_Msk;
    
    huart->info->rx_status.rx_dma_triggered = 0;
    
    // Enable DMA tansfer only if there is enough space for supplied buffer
    if(size >= UART_DMA_BURST_SIZE) {
        HAL_USART_DmaUpdateRxConfig(huart, (uint32_t)pRxBuff, size);
        DMA_ChannelLoadDescriptorAndRun(huart->dma_rx->channel, &huart->dma_rx->descriptor[0]);
    }
    
    return ARM_DRIVER_OK;
}

static void HAL_USART_Receive_IRQn(USART_HandleTypeDef *huart) {
	uint32_t i = 0;

	while ((HAL_USART_ReadLineStatus(huart) & USART_LSR_RX_DATA_READY_Msk) && (i < usart_rx_buffer_size)) {
		usart_rx_buffer[i] = HAL_USART_ReadByte(huart);
        i++;
	}
}

void HAL_USART_Receive_IT(uint8_t *pRxBuff, uint32_t size) {
    usart_rx_buffer = pRxBuff;
    usart_rx_buffer_size = size;
}

__attribute__((weak)) void HT_USART_Callback(uint32_t event) {
    __NOP();
}

void HAL_USART_InitPrint(USART_HandleTypeDef *huart, clock_select_t uartClkSel, uint32_t control, uint32_t baudrate) {

#if (RTE_UART0 && USART_PRINT_SELECT == HAL_USART0_SELECT)
    UsartPrintHandle = &CREATE_SYMBOL(Driver_USART, 0);
    HT_GPR_ClockDisable(GPR_UART0FuncClk);        
    HT_GPR_SetClockSrc(GPR_UART0FuncClk, uartClkSel);
    HT_GPR_ClockEnable(GPR_UART0FuncClk);

#elif (RTE_UART1 && USART_PRINT_SELECT == HAL_USART1_SELECT)
    UsartPrintHandle = &CREATE_SYMBOL(Driver_USART, 1);
    HT_GPR_ClockDisable(GPR_UART1FuncClk);        
    HT_GPR_SetClockSrc(GPR_UART1FuncClk, uartClkSel);
    HT_GPR_ClockEnable(GPR_UART1FuncClk);

#elif (RTE_UART2 && USART_PRINT_SELECT == HAL_USART2_SELECT)
    UsartPrintHandle = &CREATE_SYMBOL(Driver_USART, 2);
    HT_GPR_ClockDisable(GPR_UART2FuncClk);        
    HT_GPR_SetClockSrc(GPR_UART2FuncClk, GPR_UART2ClkSel_26M);
    HT_GPR_ClockEnable(GPR_UART2FuncClk);

#else
    //Default is USART0 as print interface
    HT_GPR_ClockDisable(GPR_UART1FuncClk);        
    HT_GPR_SetClockSrc(GPR_UART1FuncClk, uartClkSel);
    HT_GPR_ClockEnable(GPR_UART1FuncClk);
#endif

    HAL_USART_Initialize(HT_USART_Callback, huart);
    HAL_USART_PowerControl(ARM_POWER_FULL, huart);
    HAL_USART_Control(control, baudrate, huart);
}

void HAL_USART_SetUARTLogClk(clock_select_t uartClkSel) {

#if USART_UNILOG_SELECT == HAL_USART0_SELECT
    HT_GPR_ClockDisable(GPR_UART0FuncClk);
    HT_GPR_SetClockSrc(GPR_UART0FuncClk, uartClkSel);
    HT_GPR_ClockEnable(GPR_UART0FuncClk);
    HT_GPR_SWReset(GPR_ResetUART0Func);
#endif

#if USART_UNILOG_SELECT == HAL_USART1_SELECT
    HT_GPR_ClockDisable(GPR_UART1FuncClk);
    HT_GPR_SetClockSrc(GPR_UART1FuncClk, uartClkSel);
    HT_GPR_ClockEnable(GPR_UART1FuncClk);
    HT_GPR_SWReset(GPR_ResetUART1Func);
#endif

#if USART_UNILOG_SELECT == HAL_USART2_SELECT
    HT_GPR_ClockDisable(GPR_UART2FuncClk);
    HT_GPR_SetClockSrc(GPR_UART2FuncClk, uartClkSel);
    HT_GPR_ClockEnable(GPR_UART2FuncClk);
    HT_GPR_SWReset(GPR_ResetUART2Func);
#endif

}

void HAL_USART_ConfigUartUnilog(void) {
    plat_config_raw_flash_t *rawFlashPlatConfig;

    HT_BSP_LoadPlatConfigFromRawFlash();
    rawFlashPlatConfig = (plat_config_raw_flash_t *)HT_BSP_GetRawFlashPlatConfig();

    if(rawFlashPlatConfig && (rawFlashPlatConfig->logControl != 0 )) {
#if USART_UNILOG_SELECT == HAL_USART0_SELECT
        HT_SetUnilogUart(PORT_USART_0, rawFlashPlatConfig->uartBaudRate, true);
        uniLogInitStart(UART_0_FOR_UNILOG);
#elif USART_UNILOG_SELECT == HAL_USART1_SELECT
        HT_SetUnilogUart(PORT_USART_1, rawFlashPlatConfig->uartBaudRate, true);
        uniLogInitStart(UART_1_FOR_UNILOG);
#else
        HT_SetUnilogUart(PORT_USART_2, rawFlashPlatConfig->uartBaudRate, true);
        uniLogInitStart(UART_2_FOR_UNILOG);
#endif
    }
}

int io_putchar(int ch) {

#if USART_PRINT_SELECT == HAL_USART0_SELECT
    HAL_USART_SendPolling(&huart0, (uint8_t*)&ch, 1);
#elif USART_PRINT_SELECT == HAL_USART1_SELECT
    HAL_USART_SendPolling(&huart1, (uint8_t*)&ch, 1);
#else
    HAL_USART_SendPolling(&huart2, (uint8_t*)&ch, 1);
#endif

    return 0;
}

int io_getchar(void) {
    uint8_t ch = 0;

#if USART_PRINT_SELECT == HAL_USART0_SELECT    
    HAL_USART_ReceivePolling(&huart0, &ch, 1);
#elif USART_PRINT_SELECT == HAL_USART1_SELECT
    HAL_USART_ReceivePolling(&huart1, &ch, 1);
#else
    HAL_USART_ReceivePolling(&huart2, &ch, 1);
#endif
    return (ch);
}

int fgetc(FILE *f) {
    uint8_t ch = 0;

#if USART_PRINT_SELECT == HAL_USART0_SELECT    
    HAL_USART_ReceivePolling(&huart0, &ch, 1);
#elif USART_PRINT_SELECT == HAL_USART1_SELECT
    HAL_USART_ReceivePolling(&huart1, &ch, 1);
#else
    HAL_USART_ReceivePolling(&huart2, &ch, 1);
#endif
    
    return (ch);
}

__attribute__((weak,noreturn))
void __aeabi_assert (const char *expr, const char *file, int line) {
  printf("Assert, expr:%s, file: %s, line: %d\r\n", expr, file, line);
  while(1);
}

int _write(int file, char *ptr, int len) {
	//extern int io_putchar(int ch);
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++) {
		io_putchar(*ptr++);
    }
    return len;
}

PLAT_CODE_IN_RAM void USART_IRQHandler(USART_HandleTypeDef *usart) {
    uint32_t i = 0;
    uint32_t current_cnt = 0, total_cnt = 0, left_to_recv = 0, bytes_in_fifo = 0;

#ifdef PM_FEATURE_ENABLE
    uint32_t instance = HAL_USART_GetInstanceNumber(usart);;
#endif

    if(!usart->dma_rx && !usart->dma_tx) {
        /* Handle transmit interrupt if enabled */
        if(usart->reg->IER & USART_IER_TX_DATA_REQ_Msk) {
            HAL_USART_Transmit_IRQn(usart);
            usart->info->cb_event(ARM_USART_EVENT_TX_COMPLETE);
        }

        if(usart->reg->IER & USART_IER_RX_DATA_REQ_Msk) {
            HAL_USART_Receive_IRQn(usart);
            usart->info->cb_event(ARM_USART_EVENT_RECEIVE_COMPLETE);
        }
    
    } else if(usart->dma_rx && dma_event == USART_DMA_RX_EVENT) {
        usart->info->rx_status.rx_busy = 1U;

        current_cnt = usart->info->xfer.rx_cnt;

        if(usart->info->rx_status.rx_dma_triggered) {
            // Sync with undergoing DMA transfer, wait until DMA burst transfer(8 bytes) done and update current_cnt
            do {
                current_cnt = DMA_ChannelGetCurrentTargetAddress(usart->dma_rx->channel, true) - (uint32_t) usart->info->xfer.rx_buf;
            } while(((current_cnt - usart->info->xfer.rx_cnt) & (UART_DMA_BURST_SIZE - 1)) != 0);
            
            usart->info->rx_status.rx_dma_triggered = 0;
        }
        /*
           No matter DMA transfer is started or not(left recv buffer space is not enough),
           now we can stop DMA saftely for next transfer and handle tailing bytes in FIFO
        */
        DMA_StopChannelNoWait(usart->dma_rx->channel);

        total_cnt = usart->info->xfer.rx_num;
        bytes_in_fifo = usart->reg->FCNR >> USART_FCNR_RX_FIFO_NUM_Pos;
        left_to_recv = total_cnt - current_cnt;

        i = MIN(bytes_in_fifo, left_to_recv);

        // if still have space to recv
        if(left_to_recv > 0) {
            while(i--)
                usart->info->xfer.rx_buf[current_cnt++] = usart->reg->RBR;
            
        }

        usart->info->xfer.rx_cnt = current_cnt;
        // Check if required amount of data is received
        if (current_cnt == total_cnt) {
            //Disable RDA interrupt
            usart->reg->IER &= ~(USART_IER_RX_DATA_REQ_Msk | USART_IER_RX_TIMEOUT_Msk | USART_IER_RX_LINE_STATUS_Msk);

            usart->info->cb_event(ARM_USART_EVENT_DMA_RX_COMPLETE);

        } else {
            if(usart->dma_rx) {
                // Prepare for next recv
                left_to_recv = total_cnt - usart->info->xfer.rx_cnt;
                // shall not start DMA transfer, next recv event would be timeout or overflow
                if(left_to_recv >= UART_DMA_BURST_SIZE) {
                    HAL_USART_DmaUpdateRxConfig(usart, (uint32_t)usart->info->xfer.rx_buf + usart->info->xfer.rx_cnt, left_to_recv);
                    // load descriptor and start DMA transfer
                    DMA_ChannelLoadDescriptorAndRun(usart->dma_rx->channel, &usart->dma_rx->descriptor[0]);
                }

                dma_event = USART_DMA_NONE_EVENT;
                usart->info->cb_event(ARM_USART_EVENT_RX_TIMEOUT);
            }
        }
        usart->info->rx_status.rx_busy = 0U;
    
    } else if(usart->dma_tx && dma_event == USART_DMA_TX_EVENT) {

        if(((usart->reg->IER & USART_IER_TX_DATA_REQ_Msk) && ((usart->reg->FCNR & USART_FCNR_TX_FIFO_NUM_Msk) == 0))) {
            usart->info->xfer.tx_cnt = usart->info->xfer.tx_num;
            usart->info->xfer.send_active = 0U;
            usart->reg->IER &= ~USART_IER_TX_DATA_REQ_Msk;
            dma_event = USART_DMA_NONE_EVENT;
            usart->info->cb_event(ARM_USART_EVENT_DMA_TX_COMPLETE);

#ifdef PM_FEATURE_ENABLE
            CHECK_TO_UNLOCK_SLEEP(instance, 1, 0);
#endif
        }

    }
    
}

void HAL_USART_DmaTxEvent(uint32_t event, USART_HandleTypeDef *usart) {
    switch (event)
    {
        case DMA_EVENT_END:

            dma_event = USART_DMA_TX_EVENT;

            // TXFIFO may still have data not sent out
            usart->reg->IER |= USART_IER_TX_DATA_REQ_Msk;
            usart->reg->THR = usart->info->xfer.tx_buf[usart->info->xfer.tx_num-1];

            break;
        case DMA_EVENT_ERROR:
        default:
            break;
    }
}

void HAL_USART_DmaRxEvent(uint32_t event, USART_HandleTypeDef *usart) {

#ifdef PM_FEATURE_ENABLE
    uint32_t instance = HAL_USART_GetInstanceNumber(usart);
#endif

    uint32_t dmaCurrentTargetAddress = DMA_ChannelGetCurrentTargetAddress(usart->dma_rx->channel, false);

    switch (event) {
        case DMA_EVENT_END:

            dma_event = USART_DMA_RX_EVENT;

#if USART_DEBUG
            HT_TRACE(UNILOG_PLA_DRIVER, USART_DmaRxEvent_0, P_SIG, 2, "uart dma rx event, fcnr:%x, cnt:%d", usart->reg->FCNR, dmaCurrentTargetAddress - (uint32_t)usart->info->xfer.rx_buf);
#endif

#ifdef PM_FEATURE_ENABLE
            LOCK_SLEEP(instance, 0, 1);
#endif
            usart->info->rx_status.rx_busy = 1U;
            usart->info->rx_status.rx_dma_triggered = 1;

            if(dmaCurrentTargetAddress == ( (uint32_t)usart->info->xfer.rx_buf + usart->info->xfer.rx_num)) {
#if USART_DEBUG
                HT_TRACE(UNILOG_PLA_DRIVER, USART_DmaRxEvent_1, P_SIG, 0, "uart dma rx complete");
#endif
                usart->info->xfer.rx_cnt = usart->info->xfer.rx_num;

                //Disable all recv interrupt
                usart->reg->IER &= ~(USART_IER_RX_DATA_REQ_Msk | USART_IER_RX_TIMEOUT_Msk | USART_IER_RX_LINE_STATUS_Msk);
                usart->info->rx_status.rx_busy = 0;

                if(usart->info->cb_event)
                    usart->info->cb_event(ARM_USART_EVENT_RECEIVE_COMPLETE);

#ifdef PM_FEATURE_ENABLE
                CHECK_TO_UNLOCK_SLEEP(instance, 0, 1);
#endif
            }

            break;
        case DMA_EVENT_ERROR:
        default:
            break;
    }
}

#if (RTE_UART0)

#if (RTE_UART0_TX_IO_MODE == DMA_MODE)

void HAL_USART0_DmaTxEvent(uint32_t event) { 
    HAL_USART_DmaTxEvent(event, &huart0);
}

#endif

#if (RTE_UART0_RX_IO_MODE == DMA_MODE)

void HAL_USART0_DmaRxEvent(uint32_t event) { 
    HAL_USART_DmaRxEvent(event, &huart0);
}

#endif

void HAL_USART0_IRQHandler(void) {
    USART_IRQHandler(&huart0);
}

#endif

#if (RTE_UART1)

#if (RTE_UART1_TX_IO_MODE == DMA_MODE)

void HAL_USART1_DmaTxEvent(uint32_t event) { 
    HAL_USART_DmaTxEvent(event, &huart1);
}

#endif

#if (RTE_UART1_RX_IO_MODE == DMA_MODE)

void HAL_USART1_DmaRxEvent(uint32_t event) { 
    HAL_USART_DmaRxEvent(event, &huart1);
}

#endif

void HAL_USART1_IRQHandler(void) {
    USART_IRQHandler(&huart1);
}

#endif

#if (RTE_UART2)

#if (RTE_UART2_TX_IO_MODE == DMA_MODE)

void HAL_USART2_DmaTxEvent(uint32_t event) { 
    HAL_USART_DmaTxEvent(event, &huart2);
}

#endif

#if (RTE_UART2_RX_IO_MODE == DMA_MODE)

void HAL_USART2_DmaRxEvent(uint32_t event) { 
    HAL_USART_DmaRxEvent(event, &huart2);
}

#endif

void HAL_USART2_IRQHandler(void) {
    USART_IRQHandler(&huart2);
}

#endif

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
