/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    qspi_qcx212.h
 * Description:  QCX212 qspi controller header file
 * History:      11/29/2017    Originated by bchang
 *
 ****************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _QSPI_QCX212_H
#define _QSPI_QCX212_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "qcx212_internal.h"
#include "qcx212.h"

#define HAL_QSPI_MODULE_ENABLED

#define QSPI_CODE_IN_RAM             __attribute__((__section__(".ramCode")))

typedef struct
{


  uint32_t TxFifoThreshold;      /* Specifies the tx  threshold number of bytes in the FIFO (used only in CPU mode)
                                  This parameter can be a value between 1 and 7 */

  uint32_t RxFifoThreshold;    /* Specifies the rx  threshold number of bytes in the FIFO (used only in CPU mode)
                                  This parameter can be a value between 1 and 7 */

  uint32_t FlashSize;          /* Specifies the Flash Size. FlashSize+1 is effectively the number of address bits
                                  required to address the flash memory. we use 24 bits adddress for 4MB flash
                                  This parameter can be a number between 0 and 31 */

  uint32_t CsPolarity;          /* Specifies the CS valid  porlarity. for winbond flash it should be 0
                                    This parameter can be a value of 0 or 1 */

  uint32_t CSEn;                 /* Specifies the  which CS pin will be used,
                                  This parameter can be a value of 0 or 1 if CSEn=1, then cs will be valid during the following transfer */

  uint32_t DualFlash;          /* Specifies the Dual Flash Mode State
                                  This parameter can be a value of 0 or 1 */


  uint32_t ClockMode;          /* Specifies the Clock Mode. It indicates the level that clock takes between commands.
                                   This parameter can be a value of 0--3 */
  uint32_t BaudRate;           /* Specifies the BaudRate factor for generating clock based on the Function clock.
                                  SPI frequency = Function clock frequency / ( 2 * ( baud_rate + 1 ) ) */
  uint32_t SampleDelay;     /* Specifies the Sample delay. currently it should keep default value 0  */

  /**maybe need to add other timing control field in future, currently timing control register could keep default value**/


}QSPI_InitTypeDef;

/**
  * @brief HAL QSPI State structures definition
  */
typedef enum
{
  HAL_QSPI_STATE_RESET             = 0x00U,    /*!< Peripheral not initialized                            */
  HAL_QSPI_STATE_READY             = 0x01U,    /*!< Peripheral initialized and ready for use              */
  HAL_QSPI_STATE_BUSY              = 0x02U,    /*!< Peripheral in indirect mode and busy                  */
  HAL_QSPI_STATE_BUSY_SOFTWARE_TX  = 0x12U,    /*!< Peripheral in indirect mode with transmission ongoing */
  HAL_QSPI_STATE_BUSY_SOFTWARE_RX  = 0x22U,    /*!< Peripheral in indirect mode with reception ongoing    */
  HAL_QSPI_STATE_BUSY_XIP          = 0x82U,    /*!< Peripheral in memory mapped mode ongoing              */
  HAL_QSPI_STATE_ABORT             = 0x08U,    /*!< Peripheral with abort request ongoing                 */
  HAL_QSPI_STATE_ERROR             = 0x04U     /*!< Peripheral in error                                   */
}HAL_QSPI_StateTypeDef;


typedef enum
{
  HAL_OK                           = 0x00U,    /*!< Peripheral not initialized                            */
  HAL_ERROR                        = 0x01U,    /*!< Peripheral initialized and ready for use              */
  HAL_BUSY                         = 0x02U    /*!< Peripheral in indirect mode and busy               */
}HAL_StatusTypeDef;



/**
  * @brief  QSPI Handle Structure definition
  */

#define DMA_HandleTypeDef uint32_t

#define HAL_LockTypeDef   uint32_t
#define  HAL_UNLOCKED 0

typedef struct
{
  QUADSPI_TypeDef            *Instance;        /* QSPI registers base address        */
  QSPI_InitTypeDef           Init;             /* QSPI communication parameters      */
  uint8_t                    *pTxBuffPtr;      /* Pointer to QSPI Tx transfer Buffer */
  __IO uint32_t              TxXferSize;       /* QSPI Tx Transfer size              */
  __IO uint32_t              TxXferCount;      /* QSPI Tx Transfer Counter           */
  uint8_t                    *pRxBuffPtr;      /* Pointer to QSPI Rx transfer Buffer */
  __IO uint32_t              RxXferSize;       /* QSPI Rx Transfer size              */
  __IO uint32_t              RxXferCount;      /* QSPI Rx Transfer Counter           */
  DMA_HandleTypeDef          *hdma;            /* QSPI Rx/Tx DMA Handle parameters   */
  __IO HAL_LockTypeDef       Lock;             /* Locking object                     */
  __IO HAL_QSPI_StateTypeDef State;            /* QSPI communication state           */
  __IO uint32_t              ErrorCode;        /* QSPI Error code                    */
  uint32_t                   Timeout;          /* Timeout for the QSPI memory access */
}QSPI_HandleTypeDef;

/**
  * @brief  QSPI Command structure definition
  */
typedef struct
{

    uint32_t Instruction;        /* Specifies the Instruction to be sent
                                    This parameter can be a value (8-bit) between 0x00 and 0xFF */
    uint32_t Address;            /* Specifies the Address to be sent (Size from 1 to 4 bytes according AddressSize)
                                    This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
    uint32_t FrameDataLen;       /* Specifies the number of data to transfer.
                                    This parameter can be any value between 0 and 0xFFF (0 means undefined length
                                            until end of memory)*/
    uint32_t FrameDirectCfg;
}QSPI_CommandTypeDef;




/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup QSPI_Exported_Constants QSPI Exported Constants
  * @{
  */
/** @defgroup QSPI_ErrorCode QSPI Error Code
  * @{
  */
#define HAL_QSPI_ERROR_NONE            ((uint32_t)0x00000000U) /*!< No error           */
#define HAL_QSPI_ERROR_TIMEOUT         ((uint32_t)0x00000001U) /*!< Timeout error      */
#define HAL_QSPI_ERROR_TRANSFER        ((uint32_t)0x00000002U) /*!< Transfer error     */
#define HAL_QSPI_ERROR_DMA             ((uint32_t)0x00000004U) /*!< DMA transfer error */
#define HAL_QSPI_ERROR_INVALID_PARAM   ((uint32_t)0x00000008U) /*!< Invalid parameters error */
/**
  * @}
  */

/** @defgroup QSPI_SampleShifting QSPI Sample Shifting,nedd to confirm with ASIC,maybe default value is fine !!!!!!!
  * @{
  */
#define QSPI_SAMPLE_DELAY_NONE                  ((uint32_t)0x00000000U)        /*!<No clock cycle shift to sample data*/
#define QSPI_SAMPLE_DELAY_HALFCYCLE                 ((uint32_t)QSPI_QTCR_SAMDLY_0) /*!<1/2 clock cycle shift to sample data*/
#define QSPI_SAMPLE_DELAY_1_CYCLE               ((uint32_t)QSPI_QTCR_SAMDLY_1) /*!<1 clock cycle shift to sample data*/
#define QSPI_SAMPLE_DELAY_1_AND_HALFCYCLE       ((uint32_t)QSPI_QTCR_SAMDLY_0|QSPI_QTCR_SAMDLY_1) /*!<1.5 clock cycle shift to sample data*/







/** @defgroup QSPI_ClockMode QSPI Clock Mode
  * @{
  */
#define QSPI_CLOCK_MODE_0                   ((uint32_t)0x00000000U)         /*!<Clk stays low while nCS is released*/
#define QSPI_CLOCK_MODE_3                   ((uint32_t)QSPI_QTCR_CPHA|QSPI_QTCR_CPOL) /*!<Clk goes high while nCS is released*/
/**
  * @}
  */

/** @defgroup QSPI_Flash_Select QSPI Flash Select
  * @{
  */
#define QSPI_FLASH_CS0_DISABLE           ((uint32_t)0x00000000U)
#define QSPI_FLASH_CS0_ENABLE            ((uint32_t)QSPI_QMCR_CSEN_0) /*is this fine,need check with ASIC!!!!!!!!!!!!*/

/**
  * @}
  */

  /** @defgroup QSPI_DualFlash_Mode  QSPI Dual Flash Mode
  * @{
  */
#define QSPI_DUALFLASH_ENABLE            ((uint32_t)QSPI_QMCR_DFM)
#define QSPI_DUALFLASH_DISABLE           ((uint32_t)0x00000000U)
/**
  * @}
  */

/** @defgroup QSPI_AddressSize QSPI Address Size
  * @{
  */
#define QSPI_ADDRESS_8_BITS            ((uint32_t)0x00000000U)           /*!<1 bytes 8-bit address*/
#define QSPI_ADDRESS_16_BITS           ((uint32_t)QSPI_QFDR_ADSIZE_0) /*!<2 bytes 16-bit address*/
#define QSPI_ADDRESS_24_BITS           ((uint32_t)QSPI_QFDR_ADSIZE_1) /*!<3 bytes 24-bit address*/
#define QSPI_ADDRESS_32_BITS           ((uint32_t)QSPI_QFDR_ADSIZE)   /*!<4 bytes 32-bit address*/
/**
  * @}
  */

/** @defgroup QSPI_AlternateBytesSize QSPI Alternate Bytes Size
  * @{
  */
#define QSPI_ALTERNATE_BYTES_8_BITS    ((uint32_t)0x00000000U)           /*!<8-bit alternate bytes*/
#define QSPI_ALTERNATE_BYTES_16_BITS   ((uint32_t)QSPI_QFDR_MDSIZE_0) /*!<16-bit alternate bytes*/
#define QSPI_ALTERNATE_BYTES_24_BITS   ((uint32_t)QSPI_QFDR_MDSIZE_1) /*!<24-bit alternate bytes*/
#define QSPI_ALTERNATE_BYTES_32_BITS   ((uint32_t)QSPI_QFDR_MDSIZE)   /*!<32-bit alternate bytes*/
/**
  * @}
  */

/** @defgroup QSPI_InstructionMode QSPI Instruction Mode
* @{
*/
#define QSPI_INSTRUCTION_NONE          ((uint32_t)0x00000000U)          /*!<No instruction*/
#define QSPI_INSTRUCTION_1_LINE        ((uint32_t)QSPI_QFDR_IMODE_0) /*!<Instruction on a single line*/
#define QSPI_INSTRUCTION_2_LINES       ((uint32_t)QSPI_QFDR_IMODE_1) /*!<Instruction on two lines*/
#define QSPI_INSTRUCTION_4_LINES       ((uint32_t)QSPI_QFDR_IMODE)   /*!<Instruction on four lines*/
/**
  * @}
  */

/** @defgroup QSPI_AddressMode QSPI Address Mode
* @{
*/
#define QSPI_ADDRESS_NONE              ((uint32_t)0x00000000U)           /*!<No address*/
#define QSPI_ADDRESS_1_LINE            ((uint32_t)QSPI_QFDR_ADMODE_0) /*!<Address on a single line*/
#define QSPI_ADDRESS_2_LINES           ((uint32_t)QSPI_QFDR_ADMODE_1) /*!<Address on two lines*/
#define QSPI_ADDRESS_4_LINES           ((uint32_t)QSPI_QFDR_ADMODE)   /*!<Address on four lines*/
/**
  * @}
  */

/** @defgroup QSPI_AlternateBytesMode  QSPI Alternate Bytes Mode
* @{
*/
#define QSPI_ALTERNATE_BYTES_NONE      ((uint32_t)0x00000000U)           /*!<No alternate bytes*/
#define QSPI_ALTERNATE_BYTES_1_LINE    ((uint32_t)QSPI_QFDR_MDMODE_0) /*!<Alternate bytes on a single line*/
#define QSPI_ALTERNATE_BYTES_2_LINES   ((uint32_t)QSPI_QFDR_MDMODE_1) /*!<Alternate bytes on two lines*/
#define QSPI_ALTERNATE_BYTES_4_LINES   ((uint32_t)QSPI_QFDR_MDMODE)   /*!<Alternate bytes on four lines*/
/**
  * @}
  */

/** @defgroup QSPI_DataMode QSPI Data Mode
  * @{
  */
#define QSPI_DATA_NONE                 ((uint32_t)0X00000000)           /*!<No data*/
#define QSPI_DATA_1_LINE               ((uint32_t)QSPI_QFDR_DATMDOE_0) /*!<Data on a single line*/
#define QSPI_DATA_2_LINES              ((uint32_t)QSPI_QFDR_DATMDOE_1) /*!<Data on two lines*/
#define QSPI_DATA_4_LINES              ((uint32_t)QSPI_QFDR_DATMDOE)   /*!<Data on four lines*/


/**
  * @}
  */

/** @defgroup QSPI_SIOOMode QSPI SIOO Mode
  * @{
  */
#define QSPI_SIOO_INST_EVERY_CMD       ((uint32_t)0x00000000U)       /*!<Send instruction on every transaction*/
#define QSPI_SIOO_INST_ONLY_FIRST_CMD  ((uint32_t)QSPI_QFDR_IONCE) /*!<Send instruction only for the first command, this is only valid in XIP mode!!!!!!!*/


/** @defgroup QSPI_Flags  QSPI Status Flags
  * @{
  */
#define QSPI_FLAG_BUSY                     QSPI_QSSR_BUSY /*!<Busy flag: operation is ongoing*/
#define QSPI_FLAG_ABORT                    QSPI_QSSR_ABORT /*!<Abort flag: operation is abort*/
#define QSPI_FLAG_TX_TRESH                 QSPI_QSSR_TXTRESH /*!<TX fifo flag: tx fifo threshold  is reached*/
#define QSPI_FLAG_RX_TRESH                 QSPI_QSSR_RXTRESH /*!<RX fifo flag: rx fifo threshold  is reached*/
#define QSPI_FLAG_CS0_STATE                QSPI_QSSR_CSSTAT_0 /*!<CS STATE flag: CS state*/
#define QSPI_FLAG_INS_ONCE                 QSPI_QSSR_IONCE /*!<Instruction send only once flag : the instruction section has been sent and it only needs to send only once.*/


/**
  * @}
  */

/** @defgroup QSPI_Interrupts  QSPI Interrupts enable
  * @{
  */
//#define QSPI_IT_TO                          QUADSPI_CR_TOIE /*!<Interrupt on the timeout flag*/
//#define QSPI_IT_SM                          QUADSPI_CR_SMIE /*!<Interrupt on the status match flag*/

//we did not has such int now, need to add it
#define QSPI_IT_TXFT                   QSPI_QIER_TXFTIE /*!<Interrupt on the fifo threshold flag*/
#define QSPI_IT_RXFT                   QSPI_QIER_RXFTIE /*!<Interrupt on the fifo threshold flag*/
//we did not has such int now, need to add it



#define QSPI_IT_TC                   QSPI_QIER_DONE  /*!<Transfer complete flag: programmed number of data have been transferred or the transfer has been aborted*/
#define QSPI_IT_TE                   QSPI_QIER_ERROR  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_IT_XIP_FAIL             QSPI_QIER_XIPFAIL  /*!<XIP fail flag: xip access was failed*/
#define QSPI_IT_TX_UNDERFLOW         QSPI_QIER_TXUDFLOW/*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_IT_TX_OVERFLOW            QSPI_QIER_TXOVFLOW
#define QSPI_IT_TX_EMPTY               QSPI_QIER_TXEMPTY                 /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_IT_TX_FULL                QSPI_QIER_TXFULL
#define QSPI_IT_RX_UNDERFLOW         QSPI_QIER_RXUDFLOW  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_IT_RX_OVERFLOW          QSPI_QIER_RXOVFLOW
#define QSPI_IT_RX_EMPTY             QSPI_QIER_RXEMPTY  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_IT_RX_FULL              QSPI_QIER_RXFULL



/** @defgroup QSPI_INT_Flags  QSPI Interrupt Status Flags
  * @{
  */

//we did not has such int now, need to add it
#define QSPI_FLAG_TXFT                   QSPI_QISR_TXFTIE /*!<Interrupt on the fifo threshold flag*/
#define QSPI_FLAG_RXFT                   QSPI_QISR_RXFTIE /*!<Interrupt on the fifo threshold flag*/
//we did not has such int now, need to add it

#define QSPI_FLAG_TC                   QSPI_QISR_DONE  /*!<Transfer complete flag: programmed number of data have been transferred or the transfer has been aborted*/
#define QSPI_FLAG_TE                   QSPI_QISR_ERROR  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_FLAG_XIP_FAIL             QSPI_QISR_XIPFAIL  /*!<XIP fail flag: xip access was failed*/
#define QSPI_FLAG_TX_UNDERFLOW         QSPI_QISR_TXUDFLOW /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_FLAG_TX_OVERFLOW          QSPI_QISR_TXOVFLOW
#define QSPI_FLAG_TX_EMPTY             QSPI_QISR_TXEMPTY                 /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_FLAG_TX_FULL              QSPI_QISR_TXFULL

#define QSPI_FLAG_RX_UNDERFLOW         QSPI_QISR_RXUDFLOW  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_FLAG_RX_OVERFLOW          QSPI_QISR_RXOVFLOW
#define QSPI_FLAG_RX_EMPTY             QSPI_QISR_RXEMPTY  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_FLAG_RX_FULL              QSPI_QISR_RXFULL



/** @defgroup QSPI_INT_MASK_Flags  QSPI Interrupt Mask
  * @{
  */

//we did not has such int now, need to add it
#define QSPI_MASK_TXFT                   QSPI_QIMR_TXFTIE /*!<Interrupt on the fifo threshold flag*/
#define QSPI_MASK_RXFT                   QSPI_QIMR_RXFTIE /*!<Interrupt on the fifo threshold flag*/
//we did not has such int now, need to add it

#define QSPI_MASK_TC                   QSPI_QIMR_DONE  /*!<Transfer complete flag: programmed number of data have been transferred or the transfer has been aborted*/
#define QSPI_MASK_TE                   QSPI_QIMR_ERROR  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_MASK_XIP_FAIL             QSPI_QIMR_XIPFAIL  /*!<XIP fail flag: xip access was failed*/
#define QSPI_MASK_TX_UNDERFLOW         QSPI_QIMR_TXUDFLOW/*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_MASK_TX_OVERFLOW          QSPI_QIMR_TXOVFLOW
#define QSPI_MASK_TX_EMPTY             QSPI_QIMR_TXEMPTY                 /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_MASK_TX_FULL              QSPI_QIMR_TXFULL
#define QSPI_MASK_RX_UNDERFLOW         QSPI_QIMR_RXUDFLOW  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_MASK_RX_OVERFLOW          QSPI_QIMR_RXOVFLOW
#define QSPI_MASK_RX_EMPTY             QSPI_QIMR_RXEMPTY  /*!<Transfer error flag: invalid address is being accessed*/
#define QSPI_MASK_RX_FULL              QSPI_QIMR_RXFULL





/**
  * @}
  */

/** @defgroup QSPI_Timeout_definition QSPI Timeout definition
  * @{
  */
#define HAL_QPSI_TIMEOUT_DEFAULT_VALUE ((uint32_t)250000)
/**
  * @}
  */


/**
  * @}
  */

/** @defgroup QSPI_Timeout_definition QSPI Timeout definition
  * @{
  */
#define HAL_FLS_TIMEOUT_DEFAULT_VALUE         ((uint32_t)250000)

#define HAL_FLS_TIMEOUT_SECTOR_ERASE_VALUE    ((uint32_t)250000*30)
#define HAL_FLS_TIMEOUT_32K_ERASE_VALUE       ((uint32_t)250000*30)
#define HAL_FLS_TIMEOUT_64K_ERASE_VALUE       ((uint32_t)250000*30)
#define HAL_FLS_TIMEOUT_CHIP_ERASE_VALUE      ((uint32_t)250000*200)

#define HAL_FLS_TIMEOUT_PAGE_PRGO_VALUE       ((uint32_t)250000)
#define HAL_FLS_TIMEOUT_WRITE_STATUS_VALUE    ((uint32_t)250000)

/**
  * @}
  */


/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup QSPI_Exported_Macros QSPI Exported Macros
  * @{
  */

/** @brief Reset QSPI handle state
  * @param  __HANDLE__: QSPI handle.
  * @retval None
  */
#define __HAL_QSPI_RESET_HANDLE_STATE(__HANDLE__)           ((__HANDLE__)->State = HAL_QSPI_STATE_RESET)

/** @brief  Enable QSPI
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @retval None
  */
#define __HAL_QSPI_ENABLE(__HANDLE__)                       SET_BIT((__HANDLE__)->Instance->QMCR, QSPI_QMCR_EN)

/** @brief  Disable QSPI
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @retval None
  */
#define __HAL_QSPI_DISABLE(__HANDLE__)                      CLEAR_BIT((__HANDLE__)->Instance->QMCR, QSPI_QMCR_EN)

/** @brief  Enables the specified QSPI interrupt.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __INTERRUPT__: specifies the QSPI interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg QSPI_IT_TO: QSPI Time out interrupt
  *            @arg QSPI_IT_SM: QSPI Status match interrupt
  *            @arg QSPI_IT_FT: QSPI FIFO threshold interrupt
  *            @arg QSPI_IT_TC: QSPI Transfer complete interrupt
  *            @arg QSPI_IT_TE: QSPI Transfer error interrupt
  * @retval None
  */
#define __HAL_QSPI_ENABLE_IT(__HANDLE__, __INTERRUPT__)     SET_BIT((__HANDLE__)->Instance->QIER, (__INTERRUPT__))


/** @brief  Disables the specified QSPI interrupt.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __INTERRUPT__: specifies the QSPI interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg QSPI_IT_TO: QSPI Timeout interrupt
  *            @arg QSPI_IT_SM: QSPI Status match interrupt
  *            @arg QSPI_IT_FT: QSPI FIFO threshold interrupt
  *            @arg QSPI_IT_TC: QSPI Transfer complete interrupt
  *            @arg QSPI_IT_TE: QSPI Transfer error interrupt
  * @retval None
  */
#define __HAL_QSPI_DISABLE_IT(__HANDLE__, __INTERRUPT__)    CLEAR_BIT((__HANDLE__)->Instance->QIER, (__INTERRUPT__))

/** @brief  Checks whether the specified QSPI interrupt source is enabled.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __INTERRUPT__: specifies the QSPI interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg QSPI_IT_TO: QSPI Time out interrupt
  *            @arg QSPI_IT_SM: QSPI Status match interrupt
  *            @arg QSPI_IT_FT: QSPI FIFO threshold interrupt
  *            @arg QSPI_IT_TC: QSPI Transfer complete interrupt
  *            @arg QSPI_IT_TE: QSPI Transfer error interrupt
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */

/** @brief  Mask the specified QSPI interrupt.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __INTERRUPT__: specifies the QSPI interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg QSPI_IT_TO: QSPI Time out interrupt
  *            @arg QSPI_IT_SM: QSPI Status match interrupt
  *            @arg QSPI_IT_FT: QSPI FIFO threshold interrupt
  *            @arg QSPI_IT_TC: QSPI Transfer complete interrupt
  *            @arg QSPI_IT_TE: QSPI Transfer error interrupt
  * @retval None
  */
#define __HAL_QSPI_MASK_IT(__HANDLE__, __INTERRUPT__)     SET_BIT((__HANDLE__)->Instance->QIMR, (__INTERRUPT__))


#define __HAL_QSPI_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) (READ_BIT((__HANDLE__)->Instance->QISR, (__INTERRUPT__)) == (__INTERRUPT__))

/**
  * @brief  Get the selected QSPI's flag status.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __FLAG__: specifies the QSPI flag to check.
  *          This parameter can be one of the following values:
  *            @arg QSPI_FLAG_BUSY: QSPI Busy flag
  *            @arg QSPI_FLAG_TO:   QSPI Time out flag
  *            @arg QSPI_FLAG_SM:   QSPI Status match flag
  *            @arg QSPI_FLAG_FT:   QSPI FIFO threshold flag
  *            @arg QSPI_FLAG_TC:   QSPI Transfer complete flag
  *            @arg QSPI_FLAG_TE:   QSPI Transfer error flag
  * @retval None
  */
#define __HAL_QSPI_GET_FLAG(__HANDLE__, __FLAG__)           (READ_BIT((__HANDLE__)->Instance->QSSR, (__FLAG__)) != 0)

/** @brief  Clears the specified QSPI's flag status.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __FLAG__: specifies the QSPI clear register flag that needs to be set
  *          This parameter can be one of the following values:
  *            @arg QSPI_FLAG_TO: QSPI Time out flag
  *            @arg QSPI_FLAG_SM: QSPI Status match flag
  *            @arg QSPI_FLAG_TC: QSPI Transfer complete flag
  *            @arg QSPI_FLAG_TE: QSPI Transfer error flag
  * @retval None
  */
#define __HAL_QSPI_CLEAR_FLAG(__HANDLE__, __FLAG__)         WRITE_REG((__HANDLE__)->Instance->QISR, (__FLAG__))



/**
  * @brief  Get the selected QSPI's Interrupt  status.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __FLAG__: specifies the QSPI flag to check.
  *          This parameter can be one of the following values:
  *            @arg QSPI_FLAG_BUSY: QSPI Busy flag
  *            @arg QSPI_FLAG_TO:   QSPI Time out flag
  *            @arg QSPI_FLAG_SM:   QSPI Status match flag
  *            @arg QSPI_FLAG_FT:   QSPI FIFO threshold flag
  *            @arg QSPI_FLAG_TC:   QSPI Transfer complete flag
  *            @arg QSPI_FLAG_TE:   QSPI Transfer error flag
  * @retval None
  */
#define __HAL_QSPI_GET_IT_STATUS(__HANDLE__, __FLAG__)           (READ_BIT((__HANDLE__)->Instance->QISR, (__FLAG__)) != 0)

/** @brief  Clears the specified QSPI's flag status.
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @param  __FLAG__: specifies the QSPI clear register flag that needs to be set
  *          This parameter can be one of the following values:
  *            @arg QSPI_FLAG_TO: QSPI Time out flag
  *            @arg QSPI_FLAG_SM: QSPI Status match flag
  *            @arg QSPI_FLAG_TC: QSPI Transfer complete flag
  *            @arg QSPI_FLAG_TE: QSPI Transfer error flag
  * @retval None
  */
#define __HAL_QSPI_CLEAR_IT_STATUS(__HANDLE__, __FLAG__)         WRITE_REG((__HANDLE__)->Instance->QISR, (__FLAG__))





/** @brief  START FRAME
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @retval None
  */
#define __HAL_QSPI_ENABLE_TX(__HANDLE__)                        SET_BIT((__HANDLE__)->Instance->QFDR, QSPI_QFDR_DATTXEN)
#define __HAL_QSPI_DISABLE_TX(__HANDLE__)                       CLEAR_BIT((__HANDLE__)->Instance->QFDR, QSPI_QFDR_DATTXEN)


#define __HAL_QSPI_ENABLE_RX(__HANDLE__)                        SET_BIT((__HANDLE__)->Instance->QFDR, QSPI_QFDR_DATRXEN)
#define __HAL_QSPI_DISABLE_RX(__HANDLE__)                       CLEAR_BIT((__HANDLE__)->Instance->QFDR, QSPI_QFDR_DATRXEN)




/** @brief  START FRAME
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @retval None
  */
#define __HAL_QSPI_START_FRAME(__HANDLE__)                       SET_BIT((__HANDLE__)->Instance->QSCR, QSPI_QSCR_STFRM)


/** @brief  ABORT TRANSFER
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @retval None
  */
#define __HAL_QSPI_ABORT_TRANSFER(__HANDLE__)                     SET_BIT((__HANDLE__)->Instance->QSCR, QSPI_QSCR_ABTTRX)



/** @brief  FLUASH TX FIFO
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @retval None
  */
#define __HAL_QSPI_FLUSH_TXFIFO(__HANDLE__)                       SET_BIT((__HANDLE__)->Instance->QSCR, QSPI_QSCR_FLHTXFIFO)


/** @brief  FLUASH RX FIFO
  * @param  __HANDLE__: specifies the QSPI Handle.
  * @retval None
  */
#define __HAL_QSPI_FLUSH_RXFIFO(__HANDLE__)                       SET_BIT((__HANDLE__)->Instance->QSCR, QSPI_QSCR_FLHRXFIFO)




/* Exported functions --------------------------------------------------------*/
/** @addtogroup QSPI_Exported_Functions
  * @{
  */

/** @addtogroup QSPI_Exported_Functions_Group1
  * @{
  */
/* Initialization/de-initialization functions  ********************************/
HAL_StatusTypeDef     HAL_QSPI_Init     (void);
HAL_StatusTypeDef     HAL_QSPI_DeInit   (void);

/**
  * @}
  */

/** @addtogroup QSPI_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
/* QSPI IRQ handler method */
void                  HAL_QSPI_IRQHandler(QSPI_HandleTypeDef *hqspi);

/* QSPI indirect mode */
HAL_StatusTypeDef     HAL_QSPI_Command      (QSPI_CommandTypeDef *cmd);
HAL_StatusTypeDef     HAL_QSPI_Transmit     (uint8_t *pData);
HAL_StatusTypeDef     HAL_QSPI_Receive      (uint8_t *pData);





/** @addtogroup QSPI_Exported_Functions_Group4
  * @{
  */
/* Peripheral Control and State functions  ************************************/
HAL_QSPI_StateTypeDef HAL_QSPI_GetState        (void);
uint32_t              HAL_QSPI_GetError        (void);

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup QSPI_Private_Macros QSPI Private Macros
  * @{
  */
/** @defgroup QSPI_ClockPrescaler QSPI Clock Prescaler
  * @{
  */


  /****************************** QSPI Instances *********************************/
#define IS_QSPI_ALL_INSTANCE(__INSTANCE__) ((__INSTANCE__) == QUADSPI)



  #define IS_QSPI_BAUDRATE(BAUDRATE)  ((BAUDRATE) <= 0xFF)
/**
  * @}
  */

/** @defgroup QSPI_FifoThreshold  QSPI Fifo Threshold
  * @{
  */
#define IS_QSPI_FIFO_THRESHOLD(THR)         (((THR) >= 0) && ((THR) <= 8))
/**
  * @}
  */

#define IS_QSPI_SDELAY(DELAY)              (((DELAY) == QSPI_SAMPLE_DELAY_NONE) || \
                                            ((DELAY) == QSPI_SAMPLE_DELAY_HALFCYCLE) || \
                                            ((DELAY) == QSPI_SAMPLE_DELAY_1_CYCLE)|| \
                                             ((DELAY) == QSPI_SAMPLE_DELAY_1_AND_HALFCYCLE))


/** @defgroup QSPI_FlashSize QSPI Flash Size
  * @{
  */
#define IS_QSPI_FLASH_SIZE(FSIZE)           (((FSIZE) <= 31))
/**
  * @}
  */



#define IS_QSPI_CLOCK_MODE(CLKMODE)         (((CLKMODE) == QSPI_CLOCK_MODE_0) || \
                                             ((CLKMODE) == QSPI_CLOCK_MODE_3))

#define IS_QSPI_CS0(CS0)    (((CS0) == QSPI_FLASH_CS0_ENABLE) || \
                                  ((CS0) == QSPI_FLASH_CS0_DISABLE))

#define IS_QSPI_DUAL_FLASH_MODE(MODE)    (((MODE) == QSPI_DUALFLASH_ENABLE) || \
                                          ((MODE) == QSPI_DUALFLASH_DISABLE))


/** @defgroup QSPI_Instruction QSPI Instruction
  * @{
  */
#define IS_QSPI_INSTRUCTION(INSTRUCTION)    ((INSTRUCTION) <= 0xFF)
/**
  * @}
  */

#define IS_QSPI_ADDRESS_SIZE(ADDR_SIZE)     (((ADDR_SIZE) == QSPI_ADDRESS_8_BITS)  || \
                                             ((ADDR_SIZE) == QSPI_ADDRESS_16_BITS) || \
                                             ((ADDR_SIZE) == QSPI_ADDRESS_24_BITS) || \
                                             ((ADDR_SIZE) == QSPI_ADDRESS_32_BITS))

#define IS_QSPI_ALTERNATE_BYTES_SIZE(SIZE)  (((SIZE) == QSPI_ALTERNATE_BYTES_8_BITS)  || \
                                             ((SIZE) == QSPI_ALTERNATE_BYTES_16_BITS) || \
                                             ((SIZE) == QSPI_ALTERNATE_BYTES_24_BITS) || \
                                             ((SIZE) == QSPI_ALTERNATE_BYTES_32_BITS))


/** @defgroup QSPI_DummyCycles QSPI Dummy Cycles
  * @{
  */
#define IS_QSPI_DUMMY_CYCLES(DCY)           ((DCY) <= 31)
/**
  * @}
  */

#define IS_QSPI_INSTRUCTION_MODE(MODE)      (((MODE) == QSPI_INSTRUCTION_NONE)    || \
                                             ((MODE) == QSPI_INSTRUCTION_1_LINE)  || \
                                             ((MODE) == QSPI_INSTRUCTION_2_LINES) || \
                                             ((MODE) == QSPI_INSTRUCTION_4_LINES))

#define IS_QSPI_ADDRESS_MODE(MODE)          (((MODE) == QSPI_ADDRESS_NONE)    || \
                                             ((MODE) == QSPI_ADDRESS_1_LINE)  || \
                                             ((MODE) == QSPI_ADDRESS_2_LINES) || \
                                             ((MODE) == QSPI_ADDRESS_4_LINES))

#define IS_QSPI_ALTERNATE_BYTES_MODE(MODE)  (((MODE) == QSPI_ALTERNATE_BYTES_NONE)    || \
                                             ((MODE) == QSPI_ALTERNATE_BYTES_1_LINE)  || \
                                             ((MODE) == QSPI_ALTERNATE_BYTES_2_LINES) || \
                                             ((MODE) == QSPI_ALTERNATE_BYTES_4_LINES))

#define IS_QSPI_DATA_MODE(MODE)             (((MODE) == QSPI_DATA_NONE)    || \
                                             ((MODE) == QSPI_DATA_1_LINE)  || \
                                             ((MODE) == QSPI_DATA_2_LINES) || \
                                             ((MODE) == QSPI_DATA_4_LINES))


#define IS_QSPI_SIOO_MODE(SIOO_MODE)      (((SIOO_MODE) == QSPI_SIOO_INST_EVERY_CMD) || \
                                             ((SIOO_MODE) == QSPI_SIOO_INST_ONLY_FIRST_CMD))




#define IS_QSPI_GET_FLAG(FLAG)              (((FLAG) == QSPI_FLAG_BUSY) || \
                                             ((FLAG) == QSPI_FLAG_TO)   || \
                                             ((FLAG) == QSPI_FLAG_SM)   || \
                                             ((FLAG) == QSPI_FLAG_FT)   || \
                                             ((FLAG) == QSPI_FLAG_TC)   || \
                                             ((FLAG) == QSPI_FLAG_TE))

#define IS_QSPI_IT(IT)                      ((((IT) & (uint32_t)0xFFE0FFFFU) == 0x00000000U) && ((IT) != 0x00000000U))


typedef enum
{
  RESET = 0U,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0U,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))


typedef enum
{
    QSPI_CLOCK_10M,
    QSPI_CLOCK_CORECLK_DIV_4,
    QSPI_CLOCK_CORECLK_DIV_3,
    QSPI_CLOCK_CORECLK_DIV_2

}HalQspiClkFreq;


/*some register operation macro,maybe need to move to proper header file
this is ST defined, need to modify later */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))


#ifdef ASSERT
#undef ASSERT
#endif

#define ASSERT(x) \
    if (!(x)) {\
         while (1) { \
         } \
    }



typedef enum
{
    QSPI_QSSR_BUSY_FLAG_TYPE = 0,
    QSPI_QSSR_TX_TRESH_FLAG_TYPE,
    QSPI_QISR_TC_FLAG_TYPE,
    QSPI_QISR_TC_QSSR_RX_TRESH_FLAG_TYPE, //RX available flag
}SpecFlagType;

typedef enum
{
    QSPI_FLASH_CLK_50M = 0,
    QSPI_FLASH_CLK_68M = 1,
}QSPIFlashClkType;


HAL_StatusTypeDef HAL_QSPI_Transmit_Exception(uint8_t *pData);

uint32_t HAL_QSPI_Read_Status_Data(void);
HAL_StatusTypeDef HAL_QSPI_Config(uint32_t TxFifoTh,uint32_t RxFifoTh);
HAL_StatusTypeDef HAL_QSPI_XIP_Enable(QSPI_CommandTypeDef *cmd);
void HAL_QSPI_Set_Clk(QSPIFlashClkType clk);


#define HAL_QSPI_Set_Clk_50M() HAL_QSPI_Set_Clk(QSPI_FLASH_CLK_50M)
#define HAL_QSPI_Set_Clk_68M() HAL_QSPI_Set_Clk(QSPI_FLASH_CLK_68M)

#ifdef __cplusplus
}
#endif

#endif /* _QSPI_QCX212_H */


