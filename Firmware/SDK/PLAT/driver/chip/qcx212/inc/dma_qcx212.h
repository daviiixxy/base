/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    dma_qcx212.h
 * Description:  QCX212 dma controller driver header file
 * History:      Rev1.0   2018-08-08
 *
 ****************************************************************************/

#ifndef _DMA_QCX212_H
#define _DMA_QCX212_H

#include "Driver_Common.h"

/**
  \addtogroup dma_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief List of DMA source/target address increment control options */
typedef enum _dma_address_increment
{
    DMA_AddressIncrementNone     = 0,   /**< Increment neither source or target address */
    DMA_AddressIncrementSource   = 1U,  /**< Increment source address                   */
    DMA_AddressIncrementTarget   = 2U,  /**< Increment target address                   */
    DMA_AddressIncrementBoth     = 3U,  /**< Increment both source and target address   */
} dma_address_increment_t;

/** \brief List of DMA flow control options */
typedef enum _dma_flow_control
{
    DMA_FlowControlNone          = 0U,  /**< No flow control */
    DMA_FlowControlSource        = 1U,  /**< Only source     */
    DMA_FlowControlTarget        = 2U,  /**< Only target     */
} dma_flow_control_t;

/** \brief List of DMA transfer data width in peripheral involved case */
typedef enum _dma_data_width
{
    DMA_DataWidthNoUse           = 0,   /**< Data width is set to 0 in memory to memory transfer    */
    DMA_DataWidthOneByte         = 1U,  /**< Data widath is 1 byte in peripheral involved transfer  */
    DMA_DataWidthTwoBytes        = 2U,  /**< Data widath is 2 bytes in peripheral involved transfer */
    DMA_DataWidthFourBytes       = 3U,  /**< Data widath is 4 bytes in peripheral involved transfer */
} dma_data_width_t;

/** \brief Maximum burst size of each data transfer */
typedef enum _dma_burst_size
{
    DMA_BurstInvalid             = 0,   /**< Burst size is set to reserved */
    DMA_Burst8Bytes              = 1U,  /**< Burst size is set to 8 bytes  */
    DMA_Burst16Bytes             = 2U,  /**< Burst size is set to 16 bytes */
    DMA_Burst32Bytes             = 3U,  /**< Burst size is set to 32 bytes */
    DMA_Burst64Bytes             = 4U,  /**< Burst size is set to 64 bytes */
} dma_burst_size_t;

/** \brief DMA transfer configuration structure */
typedef struct _dma_transfer_config
{
    void*                     sourceAddress;        /**< Source address                  */
    void*                     targetAddress;        /**< Target address                  */
    dma_flow_control_t        flowControl;          /**< Flow control setting            */
    dma_address_increment_t   addressIncrement;     /**< Address increment setting       */
    dma_data_width_t          dataWidth;            /**< Data width setting              */
    dma_burst_size_t          burstSize;            /**< Burst size setting              */
    uint32_t                  totalLength;          /**< Total transfer length, in bytes */
 } dma_transfer_config;

/** \brief DMA descriptor extra configuration structure for descriptor-chain mode */
typedef struct _dma_extra_config
{
    void*                  nextDesriptorAddress;        /**< Next descriptor address                        */
    bool                   stopDecriptorFetch;          /**< Indicate whether this is the last descriptor   */
    bool                   enableStartInterrupt;        /**< Start interrupt control */
    bool                   enableEndInterrupt;          /**< End interrupt control */
} dma_extra_config;

/** \brief DMA descriptor structure */
typedef struct _dma_descriptor
{
    uint32_t      DAR;      /**< DMA Descriptor Address */
    uint32_t      SAR;      /**< DMA Source Address     */
    uint32_t      TAR;      /**< DMA Target Address     */
    uint32_t      CMDR;     /**< DMA Command            */
} dma_descriptor_t;

/** \brief List of DMA interrupt sources */
typedef enum _dma_interrupt_enable
{
    /** Stop interrupt enable, when enabled, interrupt is triggered after the channel stops */
    DMA_StopInterruptEnable  = (1U << 29U),
    /** EOR interrupt enable, when enabled, interrupt is triggered on End-Of-Receive condition */
    DMA_EORInterruptEnable   = (1U << 28U),
    /** Start interrupt enable, when enabled, interrupt is triggered as soon as descriptor is loaded, valid for descriptor-chain-mode */
    DMA_StartInterruptEnable = (1U << 22U),
    /** End interrupt enable, when enabled, interrupt is triggered when transfer length decrements to 0 */
    DMA_EndInterruptEnable   = (1U << 21U),
} dma_interrupt_enable_t;

/** DMA specific error codes */
#define     ARM_DMA_ERROR_CHANNEL_ALLOC        (ARM_DRIVER_ERROR_SPECIFIC - 1)     /**< No free channel any more        */
#define     ARM_DMA_ERROR_CHANNEL_NOT_OPEN     (ARM_DRIVER_ERROR_SPECIFIC - 2)     /**< Specific channel not open       */
#define     ARM_DMA_ERROR_CHANNEL_NOT_STOPPED  (ARM_DRIVER_ERROR_SPECIFIC - 3)     /**< Specific channel not stopped    */
#define     ARM_DMA_ERROR_ADDRESS_NOT_ALIGNED  (ARM_DRIVER_ERROR_SPECIFIC - 4)     /**< Address alignment check failure */


/** List of events reported to application */
#define DMA_EVENT_ERROR    (1)        /**< Bus error                    */
#define DMA_EVENT_START    (2)        /**< Descriptor load successfully */
#define DMA_EVENT_END      (3)        /**< Transaction end              */
#define DMA_EVENT_EOR      (4)        /**< Receive EOR signal           */
#define DMA_EVENT_STOP     (5)        /**< Channel has stopped          */

/**
  \brief Defines callback function prototype.
         Callback function will be called in DMA interrupt service routine after a transaction is complete
  \param event  transaction event for the current transaction, application can get the tansaction
                    result from this paramter, available events: DMA_EVENT_ERROR, DMA_EVENT_START, DMA_EVENT_END, DMA_EVENT_EOR, DMA_EVENT_STOP
 */
typedef void (*dma_callback_t)(uint32_t event);

/** \brief timeout value when stopping channel */
#define DMA_STOP_TIMEOUT             (5000U)

/*******************************************************************************
 * API
 ******************************************************************************/


#ifdef __cplusplus
 extern "C" {
#endif

/**
  \fn    void DMA_Init(void)
  \brief Intialize DMA hareware and internal used structure, call this function before any other DMA APIs
 */
void DMA_Init(void);

/** \name DMA Channel operation API */
/** \{ */

/**
  \fn        int32_t DMA_OpenChannel(void)
  \brief     Opens a DMA channel
  \return    Channel on successful allocate
             ARM_DMA_ERROR_CHANNEL_ALLOC when no free channel is found
  \note      Caller shall check the return code
 */
int32_t DMA_OpenChannel(void);

/**
  \fn        int32_t DMA_CloseChannel(uint32_t channel)
  \brief     Closes a DMA channel
  \param[in] channel    DMA channel number
  \return    ARM_DRIVER_OK if no error happens
             ARM_DMA_ERROR_CHANNEL_NOT_OPEN when channel is not open
  \note      This API will call \ref DMA_StopChannel to stop channel first if channel is running before close
 */
int32_t DMA_CloseChannel(uint32_t channel);

/**
  \fn        void DMA_StartChannel(uint32_t channel)
  \brief     Activates the DMA channel
  \param[in] channel    DMA channel number
 */
void DMA_StartChannel(uint32_t channel);

/**
  \fn        int32_t DMA_StopChannel(uint32_t channel, bool waitForStop)
  \brief     Stops the DMA channel from running
  \param[in] channel        DMA channel number
  \param[in] waitForStop    whether to wait channel to fully stop or not
  \return    ARM_DRIVER_OK if stops successfully
             ARM_DMA_ERROR_CHANNEL_NOT_STOPPED if channel fails to stop until timeout expires
  \note      staus and interrupt flags will be cleared in this function call
 */
int32_t DMA_StopChannel(uint32_t channel, bool waitForStop);

/**
  \fn        void DMA_ResetChannel(uint32_t channel)

  \brief     Put the DMA channel to reset state
  \param[in] channel        DMA channel number
  \note      Make sure DMA is stopped before calling this function
 */
void DMA_ResetChannel(uint32_t channel);

/**
  \fn        void DMA_ChannelRigisterCallback(uint32_t channel, dma_callback_t callback)
  \brief     Registers a DMA callback
  \param[in] channel        DMA channel number
  \param[in] callback       Given by the application and will be called in DMA interrupt service routine
 */
void DMA_ChannelRigisterCallback(uint32_t channel, dma_callback_t callback);

/**
  \fn        void DMA_EnableChannelInterrupts(uint32_t channel, uint32_t mask)
  \brief     Enables DMA interrupts
  \param[in] channel        DMA channel number
  \param[in] mask           Mask of interrupt source to be set, can be ORed by items list in \ref dma_interrupt_enable_t
  \note      In no-descriptor-fetch mode, all interrupt sources can be enabled by calling this API, however, in descritor-fetch
             mode, only \ref DMA_StopInterruptEnable \ref DMA_EORInterruptEnable can be done by this function call,
             the \ref DMA_StartInterruptEnable and \ref DMA_EndInterruptEnable is controlled by setting in \ref dma_extra_config respectively.
 */
void DMA_EnableChannelInterrupts(uint32_t channel, uint32_t mask);

/**
  \fn        void DMA_DisableChannelInterrupts(uint32_t channel, uint32_t mask)
  \brief     Disables DMA interrupts
  \param[in] channel        DMA channel number
  \param[in] mask           Mask of interrupt source to be disabled, can be ORed by items list in \ref dma_interrupt_enable_t
  \note      In no-descriptor-fetch mode, all interrupt sources can be disabled by calling this API, however, in descritor-fetch
             mode, only \ref DMA_StopInterruptEnable \ref DMA_EORInterruptEnable can be done by this function call ,
             the \ref DMA_StartInterruptEnable and \ref DMA_EndInterruptEnable is controlled by setting in \ref dma_extra_config respectively.
 */
void DMA_DisableChannelInterrupts(uint32_t channel, uint32_t mask);

/**
  \fn        uint32_t DMA_GetEnabledInterrupts(uint32_t channel)
  \brief     Gets current enabled DMA channel interrupts
  \param[in] channel    DMA channel number
  \return    The logical OR of members of the enumeration \ref dma_interrupt_enable_t
 */
uint32_t DMA_GetEnabledInterrupts(uint32_t channel);

/**
  \fn        uint32_t DMA_ChannelGetCount(uint32_t channel)
  \brief     Obtains courrent transferred data length of a transaction in unit of byte
  \param[in] channel        DMA channel number
  \return    Size of data has been transferred
  \note      In descritor-fetch mode, Start Interrupt shall be enabled by enableStartInterrupt setting in \ref dma_extra_config
             so that driver can load total transfer number for calculation before transferring.
 */
uint32_t DMA_ChannelGetCount(uint32_t channel);

/**
  \fn        void DMA_ChannelSetRequestSource(uint32_t channel, dma_request_source_t request)
  \brief     Configures DMA request source
  \param[in] channel        DMA channel number
  \param[in] request        DMA request binded to this channel
 */
void DMA_ChannelSetRequestSource(uint32_t channel, dma_request_source_t request);

/** \} */

/** \name DMA register mode API */
/** \{ */

/**
  \fn        int32_t DMA_TransferSetup(uint32_t channel, const dma_transfer_config* config)
  \brief     Setups DMA channel according to user's transfer configuration, usded for register mode
  \param[in] channel        DMA channel number
  \param[in] config         Pointer to transfer configuration
  \note      user configuration shall be retaining(global variable) for it will be used again after exit from low power
 */
void DMA_TransferSetup(uint32_t channel, const dma_transfer_config* config);
/** \} */

/** \name DMA descriptor chain mode API */
/** \{ */

/**
  \fn         int32_t DMA_BuildDescriptor(dma_descriptor_t* descriptor, const dma_transfer_config* config, const dma_extra_config* extraConfig)
  \brief      Builds a descritor for DMA chain mode use
  \param[out] descriptor     Pointer to DMA descriptor instance
  \param[in]  config         Pointer to transfer configuration
  \param[in]  extraConfig    Pointer to extra configuration which is invalid in descriptor-chain-mode only
  \note       descriptor shall be retaining(global variable) for it will be used again after exit from low power
 */

void DMA_BuildDescriptor(dma_descriptor_t* descriptor, const dma_transfer_config* config, const dma_extra_config* extraConfig);

/**
  \fn        int32_t DMA_ChannelLoadFirstDescriptor(uint32_t channel, void* descriptorAddress)
  \brief     Loads first descritor
  \param[in] channel              DMA channel number
  \param[in] descriptorAddress    Address of descriptor from which to load, shall be aligend on a 16-byte boundary in memory
  \return    ARM_DRIVER_OK if success
             ARM_DMA_ERROR_ADDRESS_NOT_ALIGNED on address alignment check failure
 */
int32_t DMA_ChannelLoadFirstDescriptor(uint32_t channel, void* descriptorAddress);

/** \} */

/** \} */

#ifdef __cplusplus
}
#endif

#endif

