
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

#include "htnb32lxxx_hal_spi.h"
#include "slpman_qcx212.h"

#ifndef DISTANCE
#define DISTANCE(a,b)  ((a>b)?(a-b):(b-a))
#endif

#define SPI_RX_FIFO_TRIG_LVL      (4)

#define ARM_SPI_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) // driver version

#if ((!RTE_SPI0) && (!RTE_SPI1))
#error "spi not enabled in RTE_Device.h!"
#endif

#ifdef PM_FEATURE_ENABLE

/** \brief Internal used data structure */
typedef struct _spi_database
{
    bool                            isInited;            /**< Whether spi has been initialized */
    struct
    {
        uint32_t CR0;                                    /**< Control Register 0 */
        uint32_t CR1;                                    /**< Control Register 1 */
        uint32_t CPSR;                                   /**< Clock Prescale Register */
        uint32_t IMSC;                                   /**< Interrupt Mask Set or Clear Register */
        uint32_t DMACR;                                  /**< DMA Control Register */
    } backup_registers;                                  /**< Backup registers for low power restore */
} spi_database_t;

static spi_database_t g_spiDataBase[SPI_INSTANCE_NUM] = {0};

static SPI_TypeDef* const g_spiBases[SPI_INSTANCE_NUM] = {SPI0, SPI1};
#endif

static clock_ID_t g_spiClocks[SPI_INSTANCE_NUM*2] = {GPR_SPI0APBClk, GPR_SPI0FuncClk, GPR_SPI1APBClk, GPR_SPI1FuncClk};

#ifdef PM_FEATURE_ENABLE
/**
  \brief spi initialization counter, for lower power callback register/de-register
 */
static uint32_t g_spiInitCounter = 0;

/**
  \brief Bitmap of SPI working status, each instance is assigned 2 bits representing tx and rx status,
         when all SPI instances are not working, we can vote to enter to low power state.
 */
static uint32_t g_spiWorkingStatus = 0;

/*!******************************************************************
 * \fn static void SPI_EnterLowPowerStatePrepare(void* pdata, slpManLpState state)
 * \brief Perform necessary preparations before sleep.
 *        After recovering from SLPMAN_SLEEP1_STATE, SPI hareware is repowered, we backup
 *        some registers here first so that we can restore user's configurations after exit.
 *
 * \param[in] pdata pointer to user data, not used now
 * \param[in] state low power state
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_EnterLowPowerStatePrepare(void* pdata, slpManLpState state)
{
    uint32_t i;

    switch (state)
    {
        case SLPMAN_SLEEP1_STATE:

            for(i = 0; i < SPI_INSTANCE_NUM; i++)
            {
                if(g_spiDataBase[i].isInited == true)
                {
                    g_spiDataBase[i].backup_registers.CR0 = g_spiBases[i]->CR0;
                    g_spiDataBase[i].backup_registers.CR1 = g_spiBases[i]->CR1;
                    g_spiDataBase[i].backup_registers.CPSR = g_spiBases[i]->CPSR;
                    g_spiDataBase[i].backup_registers.IMSC = g_spiBases[i]->IMSC;
                    g_spiDataBase[i].backup_registers.DMACR = g_spiBases[i]->DMACR;
                }
            }
            break;
        default:
            break;
    }

}

/*!******************************************************************
 * \fn static void SPI_ExitLowPowerStateRestore(void* pdata, slpManLpState state)
 * \brief Restore after exit from sleep.
 *        After recovering from SLPMAN_SLEEP1_STATE, SPI hareware is repowered, we restore user's configurations
 *        by aidding of the stored registers.
 *
 * \param[in] void *pdata               pointer to user data, not used now
 * \param[in] slpManLpState state       low power state
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_ExitLowPowerStateRestore(void* pdata, slpManLpState state)
{
    uint32_t i;

    switch (state)
    {
        case SLPMAN_SLEEP1_STATE:

            for(i = 0; i < SPI_INSTANCE_NUM; i++)
            {
                if(g_spiDataBase[i].isInited == true)
                {
                    GPR_ClockEnable(g_spiClocks[2*i]);
                    GPR_ClockEnable(g_spiClocks[2*i+1]);

                    g_spiBases[i]->CR0 = g_spiDataBase[i].backup_registers.CR0;
                    g_spiBases[i]->CPSR = g_spiDataBase[i].backup_registers.CPSR;
                    g_spiBases[i]->IMSC = g_spiDataBase[i].backup_registers.IMSC;
                    g_spiBases[i]->DMACR = g_spiDataBase[i].backup_registers.DMACR;
                    g_spiBases[i]->CR1 = g_spiDataBase[i].backup_registers.CR1;
                }
            }
            break;

        default:
            break;
    }

}

#define  LOCK_SLEEP(instance)     do                                                                     \
                                          {                                                              \
                                              g_spiWorkingStatus |= (1 << instance);                    \
                                              slpManDrvVoteSleep(SLP_VOTE_SPI, SLP_ACTIVE_STATE);  \
                                          }                                                              \
                                          while(0)

#define  CHECK_TO_UNLOCK_SLEEP(instance)      do                                                                     \
                                                      {                                                              \
                                                          g_spiWorkingStatus &= ~(1 << instance);                   \
                                                          if(g_spiWorkingStatus == 0)                                \
                                                              slpManDrvVoteSleep(SLP_VOTE_SPI, SLP_SLP1_STATE); \
                                                      }                                                              \
                                                      while(0)

#endif

// Driver Version
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_SPI_API_VERSION,
    ARM_SPI_DRV_VERSION
};

// Driver Capabilities
static const ARM_SPI_CAPABILITIES DriverCapabilities = {
    0, // Simplex Mode (Master and Slave)
    1, // TI Synchronous Serial Interface
    1, // Microwire Interface
    0  // Signal Mode Fault event
};

static uint8_t *spi_tx_buffer = NULL;
static uint8_t *spi_rx_buffer = NULL;
static uint16_t spi_buffer_size = 0;

#if (RTE_SPI0)

static SPI_INFO  SPI0_Info = {0};
static PIN SPI0_pin_sclk  = {RTE_SPI0_SCLK_PAD_ID,   RTE_SPI0_SCLK_FUNC};
static PIN SPI0_pin_ssn   = {RTE_SPI0_SSN_BIT,    RTE_SPI0_SSN_FUNC};
static PIN SPI0_pin_mosi  = {RTE_SPI0_MOSI_PAD_ID,   RTE_SPI0_MOSI_FUNC};
static PIN SPI0_pin_miso  = {RTE_SPI0_MISO_PAD_ID,   RTE_SPI0_MISO_FUNC};


#if (RTE_SPI0_IO_MODE == DMA_MODE)

static dma_descriptor_t __ALIGNED(16) SPI0_DMA_RxDescriptor;

static SPI_DMA SPI0_DMA = {
                            -1,
                            RTE_SPI0_DMA_TX_REQID,
                            HAL_SPI0_DmaTxEvent,
                            -1,
                            RTE_SPI0_DMA_RX_REQID,
                            HAL_SPI0_DmaRxEvent,
                            &SPI0_DMA_RxDescriptor
                          };
#endif

#if (RTE_SPI0_IO_MODE == IRQ_MODE) || (RTE_SPI0_IO_MODE == DMA_MODE)

static SPI_IRQ SPI0_IRQ = {
                            PXIC_Spi0_IRQn,
                            HAL_SPI0_IRQHandler
                          };
#endif

SPI_HandleTypeDef hspi0 = {
    SPI0,
    {
       &SPI0_pin_sclk,
       &SPI0_pin_ssn,
       &SPI0_pin_mosi,
       &SPI0_pin_miso,
    },
#if (RTE_SPI0_IO_MODE == DMA_MODE)
    &SPI0_DMA,
#else
    NULL,
#endif

#if (RTE_SPI0_IO_MODE == IRQ_MODE) || (RTE_SPI0_IO_MODE == DMA_MODE)
    &SPI0_IRQ,
#else
    NULL,
#endif
    &SPI0_Info
};
#endif

#if (RTE_SPI1)

static SPI_INFO  SPI1_Info = {0};
static PIN SPI1_pin_sclk  = {RTE_SPI1_SCLK_PAD_ID,   RTE_SPI1_SCLK_FUNC};
static PIN SPI1_pin_ssn   = {RTE_SPI1_SSN_PAD_ID,    RTE_SPI1_SSN_FUNC};
static PIN SPI1_pin_mosi  = {RTE_SPI1_MOSI_PAD_ID,   RTE_SPI1_MOSI_FUNC};
static PIN SPI1_pin_miso  = {RTE_SPI1_MISO_PAD_ID,   RTE_SPI1_MISO_FUNC};

#if (RTE_SPI1_IO_MODE == DMA_MODE)

static dma_descriptor_t __ALIGNED(16) SPI1_DMA_RxDescriptor;

static SPI_DMA SPI1_DMA = {
                            -1,
                            RTE_SPI1_DMA_TX_REQID,
                            HAL_SPI1_DmaTxEvent,
                            -1,
                            RTE_SPI1_DMA_RX_REQID,
                            HAL_SPI1_DmaRxEvent,
                            &SPI1_DMA_RxDescriptor
                          };
#endif

#if (RTE_SPI1_IO_MODE == IRQ_MODE) || (RTE_SPI1_IO_MODE == DMA_MODE)

static SPI_IRQ SPI1_IRQ = {
                            PXIC_Spi1_IRQn,
                            HAL_SPI1_IRQHandler
                          };
#endif

SPI_HandleTypeDef hspi1 = {
    SPI1,
    {
       &SPI1_pin_sclk,
       &SPI1_pin_ssn,
       &SPI1_pin_mosi,
       &SPI1_pin_miso,
    },
#if (RTE_SPI1_IO_MODE == DMA_MODE)
    &SPI1_DMA,
#else
    NULL,
#endif

#if (RTE_SPI1_IO_MODE == IRQ_MODE) || (RTE_SPI1_IO_MODE == DMA_MODE)
    &SPI1_IRQ,
#else
    NULL,
#endif
    &SPI1_Info
};

#endif

static dma_transfer_config g_dmaTxConfig = { NULL, NULL,
                                             DMA_FlowControlTarget, DMA_AddressIncrementSource,
                                             DMA_DataWidthOneByte,
                                             DMA_Burst8Bytes, 0
                                           };

/* Function prototypes  ------------------------------------------------------------------*/

/*!******************************************************************
 * \fn int32_t HAL_SPI_Initialize(ARM_SPI_SignalEvent_t cb_event, SPI_HandleTypeDef *spi)
 * \brief Get SSP driver version.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval ARM Driver version.
 *******************************************************************/
ARM_DRIVER_VERSION SPI_GetVersion(void);

/*!******************************************************************
 * \fn ARM_SPI_CAPABILITIES SPI_GetCapabilities(void)
 * \brief Get driver capabilities.
 *
 * \param[in]  none
 * \param[out] none
 *
 * \retval ARM SPI Capabilities
 *******************************************************************/
ARM_SPI_CAPABILITIES SPI_GetCapabilities(void);

/*!******************************************************************
 * \fn static uint32_t HAL_SPI_GetInstanceNumber(SPI_HandleTypeDef *spi)
 * \brief Get instance number.
 *
 * \param[in] SPI_HandleTypeDef *spi        SPI handle.
 * \param[out] none
 *
 * \retval Instance number.
 *******************************************************************/
static uint32_t HAL_SPI_GetInstanceNumber(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn static int32_t SPI_SetBusSpeed(uint32_t bps, SPI_HandleTypeDef *spi)
 * \brief Get instance number.
 *
 * \param[in] uint32_t bsp                  Bus speed to set.
 * \param[in] SPI_HandleTypeDef *spi        SPI handle.
 * \param[out] none
 *
 * \retval Execution status.
 *******************************************************************/
static int32_t SPI_SetBusSpeed(uint32_t bps, SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn static void SPI_DMARxConfig(void* data_in, dma_address_increment_t option, SPI_HandleTypeDef *spi)
 * \brief Configures SPI RX DMA with specified setting.
 *        Due to hardware limits, that's the minimal burst size of DMA(8 bytes) exceeds
 *        SPI RX FIFO DMA request trigger level(4), DMA will over read RX FIFO if configured as no-descritor-fetch mode,
 *        as a workaround, descritor-fetch mode is used where the receiving data is transfered in unit of chunk of RX FIFO trigger level,
 *        if the number of remaining data can not reach watermark, we use cpu to retrieve these data.
 *
 * \param[in] void *data_in                        Pointer to buffer for data to receive from SPI receiver
 * \param[in] dma_address_increment_t option       DMA address inclement option
 * \param[in] SPI_HandleTypeDef *spi               SPI handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_DMARxConfig(void* data_in, dma_address_increment_t option, SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn static void SPI_Read2BytesFifo(SPI_HandleTypeDef *spi)
 * \brief Reads two bytes from the SPI RX FIFO.
 *
 * \param[inout] SPI_HandleTypeDef *spi        SPI handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_Read2BytesFifo(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn static void SPI_Read1ByteFifo(SPI_HandleTypeDef *spi)
 * \brief Reads one byte from the SPI RX FIFO.
 *
 * \param[inout] SPI_HandleTypeDef *spi        SPI handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_Read1ByteFifo(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn static void SPI_Write2BytesFifo(SPI_HandleTypeDef *spi)
 * \brief Writes two bytes to SPI TX FIFO.
 *
 * \param[inout] SPI_HandleTypeDef *spi        SPI handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_Write2BytesFifo(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn static void SPI_Write1ByteFifo(SPI_HandleTypeDef *spi)
 * \brief Writes one byte to SPI TX FIFO.
 *
 * \param[inout] SPI_HandleTypeDef *spi        SPI handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_Write1ByteFifo(SPI_HandleTypeDef *spi);

/*!******************************************************************
 * \fn static void SPI_ClearPendingIrq(SPI_HandleTypeDef *spi)
 * \brief Clear all pending IRQn flags.
 *
 * \param[inout] SPI_HandleTypeDef *spi        SPI handle.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
static void SPI_ClearPendingIrq(SPI_HandleTypeDef *spi);

/* ---------------------------------------------------------------------------------------*/

static uint32_t HAL_SPI_GetInstanceNumber(SPI_HandleTypeDef *spi) {
    return ((uint32_t)spi->reg - (uint32_t)SPI0) >> 16U;
}

ARM_DRIVER_VERSION SPI_GetVersion(void) {
    return DriverVersion;
}

ARM_SPI_CAPABILITIES SPI_GetCapabilities(void) {
    return DriverCapabilities;
}

static int32_t SPI_SetBusSpeed(uint32_t bps, SPI_HandleTypeDef *spi) {
    uint32_t instance, spi_clock = 0;

    uint32_t cpsr, scr, best_cpsr = 2, best_scr = 1;
    uint32_t div = 0, best_div = 2;

    if(bps == 0)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    instance = HAL_SPI_GetInstanceNumber(spi);

    spi_clock = GPR_GetClockFreq(g_spiClocks[instance*2+1]);

    // bps = clock_in / div where div = cpsr * scr

    // round to nearest even number
    div = spi_clock / bps;
    div += (div & 1);

    if (div == 0)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }
    /* divider range [2,512] = 2*[1,256] (cpsr = 2)
     * this range convers most cases, for 51.2M input clock,
     * the minimum generated bps can reach 51.2M/512 = 100K
     */
    else if (div <= 512U)
    {
        best_cpsr = 2;
        best_scr = div >> 1;
    }
    // divider range [512, 254*256]
    else
    {
        // for each cpsr, we can search scr from 1 to 256, however we can narrow down the range for symmetry nature
        for (cpsr = 4U; cpsr <= 254U; cpsr += 2)
        {
            uint32_t scr_mid;
            // search upper triangular matrix
            uint32_t scr_left = cpsr >> 1;
            uint32_t scr_right = 256U;

            // scr locates outside of current range [cpsr >> 1, 256]
            if (div >= (cpsr << 8U))
            {
                scr = 256U;
            }
            // scr locates in [cpsr >> 1, 256], then binary search
            else
            {
                while (scr_left <= scr_right)
                {
                    scr_mid = (scr_right + scr_left) >> 1;
                    if (div > cpsr * scr_mid)
                        scr_left = scr_mid + 1;
                    else
                        scr_right = scr_mid - 1;
                }
                if (cpsr * scr_left - div < div - cpsr * scr_right)
                {
                    scr = scr_left;
                }
                else
                {
                    scr = scr_right;
                }

            }
            // update best_div value
            if (DISTANCE(div, best_div) >= DISTANCE(div, cpsr * scr))
            {
                best_scr = scr;
                best_cpsr = cpsr;
                best_div = best_cpsr * best_scr;
                if (best_div == div)
                    break;
            }
        }
    }

    spi->reg->CPSR = best_cpsr & SPI_CPSR_CPSDVSR_Msk;
    spi->reg->CR0 = ((spi->reg->CR0 & ~SPI_CR0_SCR_Msk) | QCOM_VAL2FLD(SPI_CR0_SCR, best_scr - 1));

    spi->info->bus_speed = spi_clock / (best_cpsr * best_scr);

    return ARM_DRIVER_OK;

}

int32_t HAL_SPI_Initialize(ARM_SPI_SignalEvent_t cb_event, SPI_HandleTypeDef *spi) {
    int32_t returnCode;

#ifdef PM_FEATURE_ENABLE
    uint32_t instance;
#endif

    pad_config_t config;

    if (spi->info->flags & SPI_FLAG_INITIALIZED)
        return ARM_DRIVER_OK;

#ifdef PM_FEATURE_ENABLE
        instance = HAL_SPI_GetInstanceNumber(spi);
        g_spiDataBase[instance].isInited = true;
#endif

    // Initialize SPI PINS
    PAD_GetDefaultConfig(&config);

    config.pullSelect = PAD_PullInternal;
    config.pullUpEnable = PAD_PullUpDisable;
    config.pullDownEnable = PAD_PullDownEnable;

    config.mux = spi->pins.pin_sclk->funcNum;
    PAD_SetPinConfig(spi->pins.pin_sclk->pinNum, &config);
    config.mux = spi->pins.pin_ssn->funcNum;
    PAD_SetPinConfig(spi->pins.pin_ssn->pinNum, &config);
    config.mux = spi->pins.pin_mosi->funcNum;
    PAD_SetPinConfig(spi->pins.pin_mosi->pinNum, &config);

    config.mux = spi->pins.pin_miso->funcNum;
    PAD_SetPinConfig(spi->pins.pin_miso->pinNum, &config);

    // Input+pulldown
    PAD_SetPinPullConfig(spi->pins.pin_miso->pinNum, PAD_InternalPullDown);
    PAD_SetPinPullConfig(spi->pins.pin_mosi->pinNum, PAD_InternalPullDown);
    PAD_SetPinPullConfig(spi->pins.pin_sclk->pinNum, PAD_InternalPullDown);

    // Initialize SPI run-time resources
    spi->info->cb_event          = cb_event;

    spi->info->status.busy       = 0;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    // Clear transfer information
    memset(&(spi->info->xfer), 0, sizeof(SPI_TRANSFER_INFO));

    spi->info->mode              = 0;

    // Configure DMA if necessary
    if (spi->dma)
    {
        DMA_Init();
        returnCode = DMA_OpenChannel();

        if (returnCode == ARM_DMA_ERROR_CHANNEL_ALLOC)
            return ARM_DRIVER_ERROR;
        else
            spi->dma->tx_ch = returnCode;

        DMA_ChannelSetRequestSource(spi->dma->tx_ch, (dma_request_source_t)spi->dma->tx_req);
        DMA_ChannelRigisterCallback(spi->dma->tx_ch, spi->dma->tx_callback);

        returnCode = DMA_OpenChannel();

        if (returnCode == ARM_DMA_ERROR_CHANNEL_ALLOC)
            return ARM_DRIVER_ERROR;
        else
            spi->dma->rx_ch = returnCode;

        DMA_ChannelSetRequestSource(spi->dma->rx_ch, (dma_request_source_t)spi->dma->rx_req);
        DMA_ChannelRigisterCallback(spi->dma->rx_ch, spi->dma->rx_callback);
    }

    spi->info->flags = SPI_FLAG_INITIALIZED;  // SPI is initialized

#ifdef PM_FEATURE_ENABLE
    g_spiInitCounter++;

    if(g_spiInitCounter == 1)
    {
        g_spiWorkingStatus = 0;
        slpManRegisterPredefinedBackupCb(SLP_CALLBACK_SPI_MODULE, SPI_EnterLowPowerStatePrepare, NULL, SLPMAN_SLEEP1_STATE);
        slpManRegisterPredefinedRestoreCb(SLP_CALLBACK_SPI_MODULE, SPI_ExitLowPowerStateRestore, NULL, SLPMAN_SLEEP1_STATE);
    }
#endif

    return ARM_DRIVER_OK;

}

int32_t HAL_SPI_Uninitialize(SPI_HandleTypeDef *spi) {
#ifdef PM_FEATURE_ENABLE
    uint32_t instance;

    instance = HAL_SPI_GetInstanceNumber(spi);

    g_spiDataBase[instance].isInited = false;

    g_spiInitCounter--;

    if(g_spiInitCounter == 0) {
        g_spiWorkingStatus = 0;
        slpManUnregisterPredefinedBackupCb(SLP_CALLBACK_SPI_MODULE);
        slpManUnregisterPredefinedRestoreCb(SLP_CALLBACK_SPI_MODULE);
    }
#endif

    spi->info->flags = 0;                    // SPI is uninitialized

    return ARM_DRIVER_OK;
}

int32_t HAL_SPI_PowerControl(ARM_POWER_STATE state, SPI_HandleTypeDef *spi) {
    uint32_t instance = HAL_SPI_GetInstanceNumber(spi);

    switch (state) {
        case ARM_POWER_OFF:

            if(spi->irq) {
                // Disable SPI IRQ
                XIC_DisableIRQ(spi->irq->irq_num);

                // Clear pending SPI interrupts
                XIC_ClearPendingIRQ(spi->irq->irq_num);
            }

            // DMA disable
            if(spi->dma) {
                DMA_StopChannel(spi->dma->tx_ch, true);
                DMA_StopChannel(spi->dma->rx_ch, true);
            }

            // Reset register values
            spi->reg->IMSC  = 0;
            spi->reg->DMACR = 0;
            spi->reg->CR0   = 0;
            spi->reg->CR1   = 0;
            spi->reg->CPSR  = 0;
            spi->reg->ICR   = (SPI_ICR_RTIC_Msk | SPI_ICR_RORIC_Msk);

            // Disable SPI clock
            GPR_ClockDisable(g_spiClocks[instance*2]);
            GPR_ClockDisable(g_spiClocks[instance*2+1]);

            // Clear SPI run-time resources
            spi->info->status.busy       = 0;
            spi->info->status.data_lost  = 0;
            spi->info->status.mode_fault = 0;

            // Clear transfer information
            memset(&(spi->info->xfer), 0, sizeof(SPI_TRANSFER_INFO));

            spi->info->mode  = 0;

            spi->info->flags &= ~SPI_FLAG_POWERED;
            break;

        case ARM_POWER_FULL:
            if ((spi->info->flags & SPI_FLAG_INITIALIZED) == 0)
                return ARM_DRIVER_ERROR;

            if (spi->info->flags & SPI_FLAG_POWERED)
                return ARM_DRIVER_OK;

            // Enable spi clock
            GPR_ClockEnable(g_spiClocks[instance*2]);
            GPR_ClockEnable(g_spiClocks[instance*2+1]);

            // Clear interrupts
            spi->reg->IMSC = 0;
            spi->reg->ICR  = (SPI_ICR_RTIC_Msk | SPI_ICR_RORIC_Msk);

            // Reset SPI run-time resources
            spi->info->status.busy       = 0;
            spi->info->status.data_lost  = 0;
            spi->info->status.mode_fault = 0;

            // Set power flag
            spi->info->flags |= SPI_FLAG_POWERED;

            // Clear RX FIFO
            while((spi->reg->SR & SPI_SR_RNE_Msk) != 0)
                spi->reg->DR;

            // Enable spi interrupt
            if(spi->irq) {
                XIC_SetVector(spi->irq->irq_num, spi->irq->cb_irq);
                XIC_EnableIRQ(spi->irq->irq_num);
                XIC_SuppressOvfIRQ(spi->irq->irq_num);
            }

            break;
        case ARM_POWER_LOW:
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
    return ARM_DRIVER_OK;
}

static void SPI_DMARxConfig(void* data_in, dma_address_increment_t option, SPI_HandleTypeDef *spi) {

    dma_transfer_config dmaConfig;
    dma_extra_config extraConfig;

    dmaConfig.addressIncrement              = option;
    dmaConfig.burstSize                     = DMA_Burst8Bytes;
    dmaConfig.dataWidth                     = (dma_data_width_t)spi->info->data_width;
    dmaConfig.flowControl                   = DMA_FlowControlSource;
    dmaConfig.sourceAddress                 = (void*)&(spi->reg->DR);
    dmaConfig.targetAddress                 = data_in;

    // transfer data in chunk of fifo trigger level
    dmaConfig.totalLength                   = SPI_RX_FIFO_TRIG_LVL * spi->info->data_width;

    extraConfig.stopDecriptorFetch       = true;
    extraConfig.enableStartInterrupt     = false;
    extraConfig.enableEndInterrupt       = true;
    extraConfig.nextDesriptorAddress     = spi->dma->descriptor;

    DMA_BuildDescriptor(spi->dma->descriptor, &dmaConfig, &extraConfig);

    DMA_ResetChannel(spi->dma->rx_ch);
}

static void SPI_Read2BytesFifo(SPI_HandleTypeDef *spi) {
    while ((spi->reg->SR & SPI_SR_RNE_Msk) && (spi->info->xfer.rx_cnt < spi->info->xfer.num)) {
        *((uint16_t *)(spi->info->xfer.rx_buf + spi->info->xfer.rx_cnt)) = spi->reg->DR;
        spi->info->xfer.rx_cnt += 2;
    }
}

static void SPI_Read1ByteFifo(SPI_HandleTypeDef *spi) {
    while ((spi->reg->SR & SPI_SR_RNE_Msk) && (spi->info->xfer.rx_cnt < spi->info->xfer.num)) {
        spi->info->xfer.rx_buf[spi->info->xfer.rx_cnt] = (uint8_t)(spi->reg->DR);
        spi->info->xfer.rx_cnt++;
    }
}

static void SPI_Write2BytesFifo(SPI_HandleTypeDef *spi) {
    spi->reg->DR = *((uint16_t *)(spi->info->xfer.tx_buf + spi->info->xfer.tx_cnt));
    spi->info->xfer.tx_cnt += 2;
}

static void SPI_Write1ByteFifo(SPI_HandleTypeDef *spi) {
    spi->reg->DR = spi->info->xfer.tx_buf[spi->info->xfer.tx_cnt];
    spi->info->xfer.tx_cnt++;
}

void HAL_SPI_DisableIRQ(SPI_HandleTypeDef *spi) {
    spi->reg->IMSC &= (~SPI_IMSC_TXIM_Msk);
    //spi->reg->IMSC &= (~SPI_IMSC_RXIM_Msk);
}

void HAL_SPI_EnableIRQ(SPI_HandleTypeDef *spi) {
    spi->reg->IMSC |= SPI_IMSC_TXIM_Msk;
    //spi->reg->IMSC |= SPI_IMSC_RXIM_Msk;
}

static void SPI_ClearPendingIrq(SPI_HandleTypeDef *spi) {
    spi->reg->IMSC = 0;
    spi->reg->ICR  = (SPI_ICR_RTIC_Msk | SPI_ICR_RORIC_Msk);

#if (RTE_SPI1_IO_MODE == IRQ_MODE)
    XIC_ClearPendingIRQ(spi->irq->irq_num);
#endif
}

void HAL_SPI_CleanRxFifo(SPI_HandleTypeDef *spi) {

    while (spi->reg->SR & SPI_SR_BSY_Msk);

    /* Clear all remaining frames in RX FIFO */
    while (spi->reg->SR & SPI_SR_RNE_Msk) {
        (void)spi->reg->DR;
    }

    /* Clear interruption pending*/
    SPI_ClearPendingIrq(spi);
}

int32_t HAL_SPI_Receive_DMA(SPI_HandleTypeDef *spi, uint8_t *pRxData, uint16_t size) {
#ifdef PM_FEATURE_ENABLE
    uint32_t instance;
#endif
    uint8_t data_width;

    if ((pRxData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

#ifdef PM_FEATURE_ENABLE
    instance = HAL_SPI_GetInstanceNumber(spi);
#endif

    // set busy flag
    spi->info->status.busy       = 1U;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    spi->info->xfer.rx_buf   = pRxData;
    spi->info->xfer.tx_buf   = pRxData;
    spi->info->xfer.tx_cnt   = 0;
    spi->info->xfer.rx_cnt   = 0;
    spi->info->xfer.num      = size;

    spi_tx_buffer = pRxData; // Send Dummy data on Tx line and generate clock on CLK line
    spi_rx_buffer = pRxData;
    spi_buffer_size = size;

    // whether occupys 2 bytes
    data_width = spi->info->data_width;

    // Wait last operation end
    while(spi->reg->SR & SPI_SR_BSY_Msk);

        // transfer number shall exceeds rx trigger level
    if(size < SPI_RX_FIFO_TRIG_LVL)
        return ARM_DRIVER_ERROR_UNSUPPORTED;

#ifdef PM_FEATURE_ENABLE
        LOCK_SLEEP(instance);
#endif

    // Configure tx DMA and start it
    g_dmaTxConfig.dataWidth = (dma_data_width_t)data_width;
    g_dmaTxConfig.addressIncrement = DMA_AddressIncrementSource;
    g_dmaTxConfig.sourceAddress = (void *)pRxData; // Send Dummy data on Tx line and generate clock on CLK line
    g_dmaTxConfig.targetAddress = (void *)&(spi->reg->DR);
    g_dmaTxConfig.totalLength   = (size * data_width);

    DMA_TransferSetup(spi->dma->tx_ch, &g_dmaTxConfig);
    DMA_EnableChannelInterrupts(spi->dma->tx_ch, DMA_EndInterruptEnable);
    DMA_StartChannel(spi->dma->tx_ch);

    SPI_DMARxConfig(pRxData, DMA_AddressIncrementTarget, spi);
    DMA_ChannelLoadFirstDescriptor(spi->dma->rx_ch, (void *)spi->dma->descriptor);
    DMA_StartChannel(spi->dma->rx_ch);

    // Enable DMA
    spi->reg->DMACR |= (SPI_DMACR_TXDMAE_Msk | SPI_DMACR_RXDMAE_Msk);

    return ARM_DRIVER_OK;
}

int32_t HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint16_t size) {
#ifdef PM_FEATURE_ENABLE
    uint32_t instance;
#endif
    uint8_t data_width;

    if ((pTxData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

#ifdef PM_FEATURE_ENABLE
    instance = HAL_SPI_GetInstanceNumber(spi);
#endif

    // set busy flag
    spi->info->status.busy       = 1U;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    spi->info->xfer.tx_buf   = pTxData;
    spi->info->xfer.tx_cnt   = 0;
    spi->info->xfer.num      = size;

    spi_tx_buffer = pTxData;
    spi_buffer_size = size;

    // whether occupys 2 bytes
    data_width = spi->info->data_width;

    // Wait last operation end
    while(spi->reg->SR & SPI_SR_BSY_Msk);

        // transfer number shall exceeds rx trigger level
    if(size < SPI_RX_FIFO_TRIG_LVL)
        return ARM_DRIVER_ERROR_UNSUPPORTED;

#ifdef PM_FEATURE_ENABLE
        LOCK_SLEEP(instance);
#endif

    // Configure tx DMA and start it
    g_dmaTxConfig.dataWidth = (dma_data_width_t)data_width;
    g_dmaTxConfig.addressIncrement = DMA_AddressIncrementSource;
    g_dmaTxConfig.sourceAddress = (void *)pTxData;
    g_dmaTxConfig.targetAddress = (void *)&(spi->reg->DR);
    g_dmaTxConfig.totalLength   = (size * data_width);

    DMA_TransferSetup(spi->dma->tx_ch, &g_dmaTxConfig);
    DMA_EnableChannelInterrupts(spi->dma->tx_ch, DMA_EndInterruptEnable);
    DMA_StartChannel(spi->dma->tx_ch);

    // Enable DMA
    spi->reg->DMACR |= (SPI_DMACR_TXDMAE_Msk | SPI_DMACR_RXDMAE_Msk);

    return ARM_DRIVER_OK;
}

int32_t HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size) {
#ifdef PM_FEATURE_ENABLE
    uint32_t instance;
#endif
    uint8_t data_width;

    if ((pTxData == NULL) || (pRxData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

#ifdef PM_FEATURE_ENABLE
    instance = HAL_SPI_GetInstanceNumber(spi);
#endif

    // set busy flag
    spi->info->status.busy       = 1U;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    spi->info->xfer.rx_buf   = pRxData;
    spi->info->xfer.tx_buf   = pTxData;
    spi->info->xfer.tx_cnt   = 0;
    spi->info->xfer.rx_cnt   = 0;
    spi->info->xfer.num      = size;

    spi_tx_buffer = pTxData;
    spi_rx_buffer = pRxData;
    spi_buffer_size = size;

    // whether occupys 2 bytes
    data_width = spi->info->data_width;

    // Wait last operation end
    while(spi->reg->SR & SPI_SR_BSY_Msk);

        // transfer number shall exceeds rx trigger level
    if(size < SPI_RX_FIFO_TRIG_LVL)
        return ARM_DRIVER_ERROR_UNSUPPORTED;

#ifdef PM_FEATURE_ENABLE
        LOCK_SLEEP(instance);
#endif

    // Configure tx DMA and start it
    g_dmaTxConfig.dataWidth = (dma_data_width_t)data_width;
    g_dmaTxConfig.addressIncrement = DMA_AddressIncrementSource;
    g_dmaTxConfig.sourceAddress = (void *)pTxData;
    g_dmaTxConfig.targetAddress = (void *)&(spi->reg->DR);
    g_dmaTxConfig.totalLength   = (size * data_width);

    DMA_TransferSetup(spi->dma->tx_ch, &g_dmaTxConfig);
    DMA_EnableChannelInterrupts(spi->dma->tx_ch, DMA_EndInterruptEnable);
    DMA_StartChannel(spi->dma->tx_ch);

    SPI_DMARxConfig(pRxData, DMA_AddressIncrementTarget, spi);
    DMA_ChannelLoadFirstDescriptor(spi->dma->rx_ch, (void *)spi->dma->descriptor);
    DMA_StartChannel(spi->dma->rx_ch);

    // Enable DMA
    spi->reg->DMACR |= (SPI_DMACR_TXDMAE_Msk | SPI_DMACR_RXDMAE_Msk);

    return ARM_DRIVER_OK;
}

int32_t HAL_SPI_Receive_IT(SPI_HandleTypeDef *spi, uint8_t *pData, uint16_t size) {
    if ((pData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

    /* Check overrun error in RIS register */
	if(spi->reg->RIS & SPI_RIS_RORRIS_Msk) {
        return ARM_DRIVER_ERROR;
    }

    // set busy flag
    spi->info->status.busy       = 1;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;
    
    spi->info->xfer.rx_buf = pData;

    spi_rx_buffer = pData;
    spi_buffer_size = size;

    /* Clear RX FIFO */
    HAL_SPI_CleanRxFifo(&hspi1);

    if((spi->info->xfer.rx_cnt < spi->info->xfer.num)) {
        
        /* Wait for the end of unfinished processes (read/write SPI processes)*/
        while(spi->reg->SR & SPI_SR_BSY_Msk);

        //Write dummy data to TX FIFO
        if(spi->reg->SR & SPI_SR_TNF_Msk) {
            spi->reg->DR = 0xFF;
        }

        // Check overrun error in RIS register
        if(spi->reg->RIS & SPI_RIS_RORRIS_Msk) {
            return ARM_DRIVER_ERROR;
        }

        /* Wait for the end of unfinished processes (read/write SPI processes)*/
        while(spi->reg->SR & SPI_SR_BSY_Msk);

        // Check for data available in RX FIFO
        if(spi->info->data_width == 2)
            SPI_Read2BytesFifo(spi);
        else
            SPI_Read1ByteFifo(spi);
    }
    
    spi->info->status.busy = 0;
    return ARM_DRIVER_OK;
}

int32_t HAL_SPI_Transmit_IT(SPI_HandleTypeDef *spi, uint8_t *pData, uint16_t size) {
    if ((pData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

    /* Check overrun error in RIS register */
	if(spi->reg->RIS & SPI_RIS_RORRIS_Msk) {
        return ARM_DRIVER_ERROR;
    }

    // set busy flag
    spi->info->status.busy       = 1;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;
    
    spi->info->xfer.tx_buf = pData;
    
    spi_tx_buffer = pData;
    spi_buffer_size = size;

    /* Wait for the end of unfinished processes (read/write SPI processes)*/
    while(spi->reg->SR & SPI_SR_BSY_Msk);

    if((spi->info->xfer.tx_cnt < spi->info->xfer.num)) {

        // tx fifo not null
        if((spi->reg->SR & SPI_SR_TNF_Msk)) {
            if(spi->info->data_width == 2)
                SPI_Write2BytesFifo(spi);
            else
                SPI_Write1ByteFifo(spi);

            // Check overrun error in RIS register
            if(spi->reg->RIS & SPI_RIS_RORRIS_Msk) {
                return ARM_DRIVER_ERROR;
            }

            /* Wait for the end of unfinished processes (read/write SPI processes)*/
            while(spi->reg->SR & SPI_SR_BSY_Msk);
            
            // Clear dummy data in RF FIFO
            HAL_SPI_CleanRxFifo(&hspi1);
        }

        spi->info->status.busy = 0;
        return ARM_DRIVER_OK;
    }

    spi->info->status.busy = 0;
    return ARM_DRIVER_ERROR;
}

int32_t HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size) {
    if ((pTxData == NULL) || (pRxData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

    /* Check overrun error in RIS register */
	if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
        return ARM_DRIVER_ERROR;

    // set busy flag
    spi->info->status.busy       = 1;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    spi->info->xfer.tx_buf = pTxData;
    spi->info->xfer.rx_buf = pRxData;
    
    spi_tx_buffer = pTxData;
    spi_rx_buffer = pRxData;
    spi_buffer_size = size;

    /* Wait for the end of unfinished processes (read/write SPI processes)*/
    while(spi->reg->SR & SPI_SR_BSY_Msk);

    if((spi->info->xfer.tx_cnt != spi->info->xfer.num) || (spi->info->xfer.rx_cnt != spi->info->xfer.num)) {
        
        if(spi->info->data_width == 2)
            SPI_Read2BytesFifo(spi);
        else
            SPI_Read1ByteFifo(spi);

        //while tx fifo not null
        while ((spi->reg->SR & SPI_SR_TNF_Msk) && (spi->info->xfer.tx_cnt != spi->info->xfer.num)) {
            if(spi->info->data_width == 2)
                SPI_Write2BytesFifo(spi);
            else
                SPI_Write1ByteFifo(spi);

            // Check overrun error in RIS register
            if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
                return ARM_DRIVER_ERROR;

            /* Wait for the end of unfinished processes (read/write SPI processes)*/
            while(spi->reg->SR & SPI_SR_BSY_Msk);
            
            // Check for data available in RX fifo
            if(spi->info->data_width == 2)
                SPI_Read2BytesFifo(spi);
            else
                SPI_Read1ByteFifo(spi);
        }
        
        spi->info->status.busy = 0;
        return ARM_DRIVER_OK;
    }

    spi->info->status.busy = 0;
    return ARM_DRIVER_ERROR;
}

int32_t HAL_SPI_Receive_Polling(SPI_HandleTypeDef *spi, uint8_t *pRxData, uint16_t size) {
    if ((pRxData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

    /* Check overrun error in RIS register */
	if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
        return ARM_DRIVER_ERROR;

    // set busy flag
    spi->info->status.busy       = 1;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    spi->info->xfer.rx_buf = pRxData;

    /* Clear RX FIFO */
    HAL_SPI_CleanRxFifo(&hspi1);

    while((spi->info->xfer.rx_cnt < spi->info->xfer.num)) {
        
        /* Wait for the end of unfinished processes (read/write SPI processes)*/
        while(spi->reg->SR & SPI_SR_BSY_Msk);

        //Write dummy data to TX FIFO
        if(spi->reg->SR & SPI_SR_TNF_Msk)
            spi->reg->DR = 0xFF;

        // Check overrun error in RIS register
        if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
            return ARM_DRIVER_ERROR;

        /* Wait for the end of unfinished processes (read/write SPI processes)*/
        while(spi->reg->SR & SPI_SR_BSY_Msk);

        // Check for data available in RX FIFO
        if(spi->info->data_width == 2)
            SPI_Read2BytesFifo(spi);
        else
            SPI_Read1ByteFifo(spi);
    }
    
    spi->info->status.busy = 0;
    return ARM_DRIVER_OK;
}

int32_t HAL_SPI_Transmit_Polling(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint16_t size) {
    if ((pTxData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

    /* Check overrun error in RIS register */
	if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
        return ARM_DRIVER_ERROR;

    // set busy flag
    spi->info->status.busy       = 1;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    spi->info->xfer.tx_buf = pTxData;

    /* Clear RX FIFO */
    HAL_SPI_CleanRxFifo(&hspi1);

    SPI_ClearPendingIrq(spi);

    while((spi->info->xfer.tx_cnt < spi->info->xfer.num)) {
        
        /* Wait for the end of unfinished processes (read/write SPI processes)*/
        while(spi->reg->SR & SPI_SR_BSY_Msk);

        //Write data to FIFO
        if(spi->reg->SR & SPI_SR_TNF_Msk) {
            if(spi->info->data_width == 2)
                SPI_Write2BytesFifo(spi);
            else
                SPI_Write1ByteFifo(spi);
        }

        // Check overrun error in RIS register
        if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
            return ARM_DRIVER_ERROR;

        // Clear dummy data in RF FIFO
        HAL_SPI_CleanRxFifo(&hspi1);
    }
    
    spi->info->status.busy = 0;
    return ARM_DRIVER_OK;
}

// SPI TX/RX polling mode
int32_t HAL_SPI_TransmitReceive_Polling(SPI_HandleTypeDef *spi, uint8_t *pTxData, uint8_t *pRxData, uint16_t size) {
    if ((pTxData == NULL) || (pRxData == NULL) || (size == 0))
        return ARM_DRIVER_ERROR_PARAMETER;

    if (!(spi->info->flags & SPI_FLAG_CONFIGURED))
        return ARM_DRIVER_ERROR;

    if (spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

    /* Check overrun error in RIS register */
	if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
        return ARM_DRIVER_ERROR;

    // set busy flag
    spi->info->status.busy       = 1;
    spi->info->status.data_lost  = 0;
    spi->info->status.mode_fault = 0;

    spi->info->xfer.tx_buf = pTxData;
    spi->info->xfer.rx_buf = pRxData;

    /* Clear RX FIFO */
    HAL_SPI_CleanRxFifo(&hspi1);

    SPI_ClearPendingIrq(spi);

    /* Wait for the end of unfinished processes (read/write SPI processes)*/
    while(spi->reg->SR & SPI_SR_BSY_Msk);

    while((spi->info->xfer.tx_cnt < spi->info->xfer.num) || (spi->info->xfer.rx_cnt < spi->info->xfer.num)) {
        //Write data to FIFO
        if(spi->reg->SR & SPI_SR_TNF_Msk) {
            if(spi->info->data_width == 2)
                SPI_Write2BytesFifo(spi);
            else
                SPI_Write1ByteFifo(spi);
        }

        // Check overrun error in RIS register
        if(spi->reg->RIS & SPI_RIS_RORRIS_Msk)
            return ARM_DRIVER_ERROR;

        /* Wait for the end of unfinished processes (read/write SPI processes)*/
        while(spi->reg->SR & SPI_SR_BSY_Msk);

        // Check for data available in RX FIFO
        if(spi->info->data_width == 2)
            SPI_Read2BytesFifo(spi);
        else
            SPI_Read1ByteFifo(spi);
    }
    
    spi->info->status.busy = 0;
    return ARM_DRIVER_OK;
}

int32_t HAL_SPI_Control(uint32_t control, uint32_t arg, SPI_HandleTypeDef *spi) {
    int32_t ret;
    uint32_t dataBits;
    pad_config_t padConfig;
    gpio_pin_config_t gpioConfig;

    if(!(spi->info->flags & SPI_FLAG_POWERED))
        return ARM_DRIVER_ERROR;

    if((control & ARM_SPI_CONTROL_Msk) == ARM_SPI_ABORT_TRANSFER) {
        // abort SPI transfer
        // Disable SPI and SPI interrupts
        spi->reg->CR1 &= ~SPI_CR1_SSE_Msk;
        spi->reg->IMSC = 0;

        if(spi->info->status.busy) {
            // If DMA mode, disable DMA channel
            if(spi->dma) {
                DMA_StopChannel(spi->dma->tx_ch, true);
                DMA_StopChannel(spi->dma->rx_ch, true);
            }
        }

        // clear SPI run-time resources
        spi->info->status.busy = 0;
        memset(&(spi->info->xfer), 0, sizeof(SPI_TRANSFER_INFO));
        spi->reg->CR1 |= SPI_CR1_SSE_Msk;

        return ARM_DRIVER_OK;
    }

    if(spi->info->status.busy)
        return ARM_DRIVER_ERROR_BUSY;

    switch(control & ARM_SPI_CONTROL_Msk) {
        // SPI Inactive
        case ARM_SPI_MODE_INACTIVE:

            // Disable SPI
            spi->reg->CR1 &= ~SPI_CR1_SSE_Msk;
            // Disable interrupts
            spi->reg->IMSC = 0;
            spi->info->mode = ((spi->info->mode & ~ARM_SPI_CONTROL_Msk) | ARM_SPI_MODE_INACTIVE);
            spi->info->flags &= ~SPI_FLAG_CONFIGURED;

            return ARM_DRIVER_OK;

        // SPI Slave  (Output on MISO, Input on MOSI)
        case ARM_SPI_MODE_SLAVE:

            // Disable SPI first
            spi->reg->CR1 &= ~SPI_CR1_SSE_Msk;

            // Set slave mode and Enable SPI
            spi->reg->CR1 |= (SPI_CR1_MS_Msk | SPI_CR1_SSE_Msk);

            spi->info->mode = ((spi->info->mode & ~ARM_SPI_CONTROL_Msk) | ARM_SPI_MODE_SLAVE);
            spi->info->flags |= SPI_FLAG_CONFIGURED;

            break;

        // SPI Master (Output/Input on MOSI); arg = Bus Speed in bps
        case ARM_SPI_MODE_MASTER_SIMPLEX:

        // SPI Slave  (Output/Input on MISO)
        case ARM_SPI_MODE_SLAVE_SIMPLEX:
            return ARM_SPI_ERROR_MODE;

        // SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
        case ARM_SPI_MODE_MASTER:

        // Set Bus Speed in bps; arg = value
        case ARM_SPI_SET_BUS_SPEED:

            if((control & ARM_SPI_CONTROL_Msk) == ARM_SPI_MODE_MASTER) {
                // Disable SPI first
                spi->reg->CR1 &= ~SPI_CR1_SSE_Msk;

                // Disable interrupts
                spi->reg->IMSC = 0;

                // Set master mode and Enable SPI
                spi->reg->CR1 = ((spi->reg->CR1 & ~SPI_CR1_MS_Msk) | SPI_CR1_SSE_Msk);

                spi->info->mode = ((spi->info->mode & ~ARM_SPI_CONTROL_Msk) | ARM_SPI_MODE_MASTER);
                spi->info->flags |= SPI_FLAG_CONFIGURED;

            }

            ret = SPI_SetBusSpeed(arg, spi);

            if(ret != ARM_DRIVER_OK)
                return ARM_DRIVER_ERROR;

            if((control & ARM_SPI_CONTROL_Msk) == ARM_SPI_SET_BUS_SPEED)
                return ARM_DRIVER_OK;
            
            break;

        // Get Bus Speed in bps
        case ARM_SPI_GET_BUS_SPEED:
            return spi->info->bus_speed;

        // Set default Transmit value; arg = value
        case ARM_SPI_SET_DEFAULT_TX_VALUE:
            spi->info->xfer.def_val = (uint16_t)(arg & 0xffff);
            return ARM_DRIVER_OK;

        // Control Slave Select; arg = 0:inactive, 1:active
        case ARM_SPI_CONTROL_SS:
            if(SPI0 == spi->reg)
                GPIO_PinWrite(RTE_SPI0_SSN_GPIO_INSTANCE, 1 << RTE_SPI0_SSN_GPIO_INDEX, arg << RTE_SPI0_SSN_GPIO_INDEX);
            else if(SPI1 == spi->reg)
                GPIO_PinWrite(RTE_SPI1_SSN_GPIO_INSTANCE, 1 << RTE_SPI1_SSN_GPIO_INDEX, arg << RTE_SPI1_SSN_GPIO_INDEX);

            break;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;

    }

    // SPI slave select mode for master
    if((spi->info->mode & ARM_SPI_CONTROL_Msk) == ARM_SPI_MODE_MASTER) {
        switch(control & ARM_SPI_SS_MASTER_MODE_Msk) {
            // SPI Slave Select when Master: Not used(default)
            case ARM_SPI_SS_MASTER_UNUSED:
                spi->info->mode = (spi->info->mode & ~ARM_SPI_SS_MASTER_MODE_Msk) | ARM_SPI_SS_MASTER_UNUSED;
                break;

            case ARM_SPI_SS_MASTER_SW:

                PAD_GetDefaultConfig(&padConfig);
                padConfig.mux = PAD_MuxAlt0;
                PAD_SetPinConfig(spi->pins.pin_ssn->pinNum, &padConfig);

                gpioConfig.pinDirection = GPIO_DirectionOutput;
                gpioConfig.misc.initOutput = 1;

                if(SPI0 == spi->reg)
                    GPIO_PinConfig(RTE_SPI0_SSN_GPIO_INSTANCE, RTE_SPI0_SSN_GPIO_INDEX, &gpioConfig);
                else if(SPI1 == spi->reg)
                    GPIO_PinConfig(RTE_SPI1_SSN_GPIO_INSTANCE, RTE_SPI1_SSN_GPIO_INDEX, &gpioConfig);

                spi->info->mode = (spi->info->mode & ~ARM_SPI_SS_MASTER_MODE_Msk) | ARM_SPI_SS_MASTER_SW;

                break;
            case ARM_SPI_SS_MASTER_HW_OUTPUT:

                PAD_GetDefaultConfig(&padConfig);
                padConfig.mux = spi->pins.pin_ssn->funcNum;
                PAD_SetPinConfig(spi->pins.pin_ssn->pinNum, &padConfig);

                spi->info->mode = (spi->info->mode & ~ARM_SPI_SS_MASTER_MODE_Msk) | ARM_SPI_SS_MASTER_HW_OUTPUT;

                break;
            case ARM_SPI_SS_MASTER_HW_INPUT:
                return ARM_SPI_ERROR_SS_MODE;
            default:
                break;
        }
    }

    // SPI slave select mode for slave
    if((spi->info->mode & ARM_SPI_CONTROL_Msk) == ARM_SPI_MODE_SLAVE) {
        switch(control & ARM_SPI_SS_SLAVE_MODE_Msk) {
            case ARM_SPI_SS_SLAVE_HW:
                spi->info->mode &= ~ARM_SPI_SS_SLAVE_MODE_Msk;
                #if 0
                if (SPI0 == spi->reg) {
                    PAD_GetDefaultConfig(&padConfig);
                    padConfig.mux = PAD_MuxAlt0;
                    PAD_SetPinConfig(10, &padConfig);

                    gpioConfig.pinDirection = GPIO_DirectionOutput;
                    gpioConfig.misc.initOutput = 0;
                    // GPIO_1<-->SSP0_SSn
                    GPIO_PinConfig(0, 1, &gpioConfig);
                
                } else if (SPI1 == spi->reg) {
                    PAD_GetDefaultConfig(&padConfig);
                    padConfig.mux = PAD_MuxAlt0;
                    PAD_SetPinConfig(14, &padConfig);

                    gpioConfig.pinDirection = GPIO_DirectionOutput;
                    gpioConfig.misc.initOutput = 0;
                    // GPIO_5<-->SSP0_SSn
                    GPIO_PinConfig(0, 5, &gpioConfig);
                }

                #endif
                spi->info->mode |= ARM_SPI_SS_SLAVE_HW;
                break;
            case ARM_SPI_SS_SLAVE_SW:
                return ARM_SPI_ERROR_SS_MODE;
            default:
                break;
        }
    }

    // set SPI frame format
    switch(control & ARM_SPI_FRAME_FORMAT_Msk) {
        case ARM_SPI_CPOL0_CPHA0:
            spi->reg->CR0 &= ~(SPI_CR0_FRF_Msk | SPI_CR0_SPO_Msk | SPI_CR0_SPH_Msk);
            break;
        case ARM_SPI_CPOL0_CPHA1:
            spi->reg->CR0 = (spi->reg->CR0 & ~(SPI_CR0_FRF_Msk | SPI_CR0_SPO_Msk)) | SPI_CR0_SPH_Msk;
            break;
        case ARM_SPI_CPOL1_CPHA0:
            spi->reg->CR0 = (spi->reg->CR0 & ~(SPI_CR0_FRF_Msk | SPI_CR0_SPH_Msk)) | SPI_CR0_SPO_Msk;
            break;
        case ARM_SPI_CPOL1_CPHA1:
            spi->reg->CR0 = (spi->reg->CR0 & ~SPI_CR0_FRF_Msk) | SPI_CR0_SPO_Msk | SPI_CR0_SPH_Msk;
            break;
        case ARM_SPI_TI_SSI:
            spi->reg->CR0 = (spi->reg->CR0 & ~SPI_CR0_FRF_Msk) | (1 << SPI_CR0_FRF_Pos);
            break;
        case ARM_SPI_MICROWIRE:
            spi->reg->CR0 = (spi->reg->CR0 & ~SPI_CR0_FRF_Msk) | (2 << SPI_CR0_FRF_Pos);
        default:
            return ARM_SPI_ERROR_FRAME_FORMAT;
    }
    // set number of data bits
    dataBits = ((control & ARM_SPI_DATA_BITS_Msk) >> ARM_SPI_DATA_BITS_Pos);

    if((dataBits >= 4U) && (dataBits <= 16U)) {
        spi->reg->CR0 = (spi->reg->CR0 & ~SPI_CR0_DSS_Msk) | (dataBits - 1);
        spi->info->data_width = (dataBits > 8U) ? 2 : 1;
    } else {
        return ARM_SPI_ERROR_DATA_BITS;
    }

    // set SPI bit order
    if((control & ARM_SPI_BIT_ORDER_Msk) == ARM_SPI_LSB_MSB)
        return ARM_SPI_ERROR_BIT_ORDER;
        
    return ARM_DRIVER_OK;
}

void SPI_IRQHandler(SPI_HandleTypeDef *spi) {
    HAL_SPI_DisableIRQ(spi);

    if(!spi->dma) {
        if((spi->info->transfer_type == SPI_TRANSMIT_ONLY) && (spi->info->xfer.tx_cnt != spi->info->xfer.num)) {
            HAL_SPI_Transmit_IT(spi, spi_tx_buffer, spi_buffer_size);
            HAL_SPI_EnableIRQ(spi);
        } else if((spi->info->transfer_type == SPI_RECEIVE_ONLY) && (spi->info->xfer.rx_cnt != spi->info->xfer.num)) {
            HAL_SPI_Receive_IT(spi, spi_rx_buffer, spi_buffer_size);
            HAL_SPI_EnableIRQ(spi);
        } else if((spi->info->transfer_type == SPI_TRANSMIT_RECEIVE) && (spi->info->xfer.tx_cnt != spi->info->xfer.num) && (spi->info->xfer.rx_cnt != spi->info->xfer.num)) {
            HAL_SPI_TransmitReceive_IT(spi, spi_tx_buffer, spi_rx_buffer, spi_buffer_size);
            HAL_SPI_EnableIRQ(spi);
        } else {
            //Transmission done, generate user callback
            if(spi->info->cb_event) {
                if(spi->info->transfer_type == SPI_TRANSMIT_RECEIVE)
                    spi->info->cb_event(ARM_SPI_EVENT_TX_RX_COMPLETE);
                else if(spi->info->transfer_type == SPI_TRANSMIT_ONLY)
                    spi->info->cb_event(ARM_SPI_EVENT_TX_COMPLETE);
                else if(spi->info->transfer_type == SPI_RECEIVE_ONLY)
                    spi->info->cb_event(ARM_SPI_EVENT_RX_COMPLETE);
            }
        }    
    
    } else {
        if(spi->info->xfer.rx_cnt == spi->info->xfer.num) {
            // disable interrupts no matter what kind of trasaction is
            spi->reg->IMSC &= ~(SPI_IMSC_TXIM_Msk | SPI_IMSC_RXIM_Msk | SPI_IMSC_RTIM_Msk | SPI_IMSC_RORIM_Msk);
            spi->info->status.busy = 0;
            spi->info->cb_event(ARM_SPI_EVENT_TX_RX_COMPLETE);
            
#ifdef PM_FEATURE_ENABLE
            CHECK_TO_UNLOCK_SLEEP(instance);
#endif
        }
    }
    
}

void HAL_SPI_DmaTxEvent(uint32_t event, SPI_HandleTypeDef *spi) {

    switch (event) {
        case DMA_EVENT_END:
           
            // Disable DMA
            spi->reg->DMACR &= ~SPI_DMACR_TXDMAE_Msk;
            spi->info->xfer.tx_cnt = spi->info->xfer.num;
            
            if(spi->info->transfer_type == SPI_TRANSMIT_ONLY) {
                spi->info->status.busy = 0;
                if (spi->info->cb_event)
                    spi->info->cb_event(ARM_SPI_EVENT_TX_RX_COMPLETE);
                
            }
            
            break;
        case DMA_EVENT_ERROR:
        default:
            break;
    }
}

void HAL_SPI_DmaRxEvent(uint32_t event, SPI_HandleTypeDef *spi) {
#ifdef PM_FEATURE_ENABLE
    uint32_t instance = HAL_SPI_GetInstanceNumber(spi);
#endif
    uint32_t dma_rx_channel, remained_cnt;

    switch(event) {
        case DMA_EVENT_END:
            dma_rx_channel = spi->dma->rx_ch;
            spi->info->xfer.rx_cnt += SPI_RX_FIFO_TRIG_LVL;

            remained_cnt = spi->info->xfer.num - spi->info->xfer.rx_cnt;
            spi_buffer_size = remained_cnt;

            // the number of remaining data exceeds trigger level, reload descriptor to transfer next chunk of data
            if(remained_cnt >= SPI_RX_FIFO_TRIG_LVL) {
                spi->dma->descriptor->TAR =  (spi->info->xfer.rx_buf == NULL)? ((uint32_t)&spi->info->xfer.dump_val) : (uint32_t)(spi->info->xfer.rx_buf + spi->info->xfer.rx_cnt);

                // load descriptor and start DMA transfer
                extern void DMA_ChannelLoadDescriptorAndRun(uint32_t channel, void* descriptorAddress);
                DMA_ChannelLoadDescriptorAndRun(dma_rx_channel, spi->dma->descriptor);
            
            } else if(remained_cnt == 0) {
                DMA_StopChannel(dma_rx_channel, true);
                spi->reg->DMACR &= ~SPI_DMACR_RXDMAE_Msk;
                spi->info->status.busy = 0;
                spi_buffer_size = 0;

                if(spi->info->cb_event)
                    spi->info->cb_event(ARM_SPI_EVENT_TX_RX_COMPLETE);
                
#ifdef PM_FEATURE_ENABLE
                 CHECK_TO_UNLOCK_SLEEP(instance);
#endif
            }
            // let cpu transfer last tailing data
            else {
                DMA_StopChannel(dma_rx_channel, true);
                spi->reg->DMACR &= ~SPI_DMACR_RXDMAE_Msk;
                spi->reg->IMSC = SPI_IMSC_RXIM_Msk | SPI_IMSC_RTIM_Msk | SPI_IMSC_RORIM_Msk;

                spi_buffer_size = remained_cnt;
            }

            break;
        case DMA_EVENT_ERROR:
        default:
            break;
    }
}


#if (RTE_SPI0)

void HAL_SPI0_IRQHandler(void) {
    SPI_IRQHandler(&hspi0);
}

void HAL_SPI0_DmaTxEvent(uint32_t event) {
    HAL_SPI_DmaTxEvent(event, &hspi0);
}

void HAL_SPI0_DmaRxEvent(uint32_t event) {
    HAL_SPI_DmaRxEvent(event, &hspi0);
}

#endif

#if (RTE_SPI1)

void HAL_SPI1_IRQHandler(void) {
    SPI_IRQHandler(&hspi1);
}

void HAL_SPI1_DmaTxEvent(uint32_t event) {
    HAL_SPI_DmaTxEvent(event, &hspi1);
}

void HAL_SPI1_DmaRxEvent(uint32_t event) {
    HAL_SPI_DmaRxEvent(event, &hspi1);
}

#endif

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
