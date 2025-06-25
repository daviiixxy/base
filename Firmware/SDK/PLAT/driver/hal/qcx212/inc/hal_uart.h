/****************************************************************************
 *
 * Copy right:   2019-, Copyrigths of Qualcomm Ltd.
 * File name:    hal_uart.h
 * Description:  QCX212 uart hal driver header file
 * History:      Rev1.0   2020-03-24
 *
 ****************************************************************************/

#ifndef _HAL_UART_H
#define _HAL_UART_H

#include "Driver_USART.h"
/**
\defgroup hal_uart_interface_gr HAL UART Interface
\details
 HAL UART is designed to manage all available UART resources, two daemon tasks are created for sending and receiving and
 they can be created seperately if UART is only working in half-duplex way.

 The data sent through uart is categorized into different types and customized action can be performed with hook machenism
 provided before and after data is sent out. Also, user pre-supplied callback is called upon data is received from UART or
 on some other events, like auto baud rate dection is done.

 HOW TO USE:

 \code

 \endcode
\addtogroup hal_uart_interface_gr
\{
 */

/*
msg type layout
|----------type-------|---uart idx---|
|----------12---------|------4-------|
*/
/** \brief HAL UART send message type bit field layout */
#define HAL_UART_SEND_MSG_TYPE_POS        (4)
#define HAL_UART_SEND_MSG_TYPE_MASK       (0xFFF0UL)
#define HAL_UART_SEND_MSG_UART_IDX_POS    (0)
#define HAL_UART_SEND_MSG_UART_IDX_MASK   (0xFUL)

/** \brief List of HAL UART task create flag */
typedef enum
{
    HAL_UART_TASK_CREATE_FLAG_NONE      = 0x0,  /**< None of send and recv task is created */
    HAL_UART_TASK_CREATE_FLAG_SEND      = 0x1,  /**< Will create send task during uart handler initialization */
    HAL_UART_TASK_CREATE_FLAG_RECV      = 0x2,  /**< Will create recv task during uart handler initialization and start to recv after successful call */
    HAL_UART_TASK_CREATE_FLAG_SEND_RECV = 0x3   /**< Will create both send and recv task during uart handler initialization and start to recv after successful call */
} hal_uart_task_create_flag_t;

#define HAL_UART_CREATE_SEND_TASK         (0x)

/** \brief List of HAL UART send message type sent to HAL UART Send task */
typedef enum
{
    HAL_UART_SEND_MSG_TYPE_CNF,           /**< CNF type data(string), for AT CMD CNF reply */
    HAL_UART_SEND_MSG_TYPE_URC,           /**< URC type data(string), for AT CMD URC */
    HAL_UART_SEND_MSG_TYPE_STR,           /**< raw string need to be sent out, like debug info */
    HAL_UART_ACT_CHANGE_CONFIG,           /**< used to notify UART to change config */
    HAL_UART_ACT_RESET_CHIP,              /**< used to notify UART to reset chip */
    HAL_UART_ACT_SLEEP_MODE_SWITCH,       /**< used to notify UART to switch sleep mode */
    HAL_UART_HTTP_RECVIND_FLOW_CONTROL,   /**< used to HTTP RECVIND flow control */
    HAL_UART_MAX_MSG = 0xFFF              /**< max number of send message type */
} hal_uart_send_msg_type_t;

/**
  \brief Defines UART recv callback function prototype.
         Callback function will be called on EVENT occured
  \param event     uart event, available events: ARM_USART_EVENT_RX_TIMEOUT, ARM_USART_EVENT_RECEIVE_COMPLETE, ARM_USART_EVENT_AUTO_BAUDRATE_DONE
  \param dataPtr   pointer to data block passed to user
  \param dataLen   length of data block in unit of byte
 */
typedef void (*hal_uart_recv_cb_t)(uint32_t event, void* dataPtr, uint32_t dataLen);

/**
  \brief Defines UART pre-send callback function prototype.
         Callback function will be called before specifed type message is sent out
  \param msgType   HAL UART send message type
  \param dataPtr   pointer to data block passed to user
  \param dataLen   length of data block in unit of byte
 */
typedef void (*hal_uart_pre_send_cb_t)(hal_uart_send_msg_type_t msgType, void* dataPtr, uint32_t dataLen);

/**
  \brief Defines UART post-send callback function prototype.
         Callback function will be called after specifed type message is sent out
  \param msgType   HAL UART send message type
  \param dataPtr   pointer to data block passed to user
  \param dataLen   length of data block in unit of byte
 */
typedef void (*hal_uart_post_send_cb_t)(hal_uart_send_msg_type_t msgType, void* dataPtr, uint32_t dataLen);

/** \brief configuration structure for initializing HAL UART handler */
typedef struct _hal_uart_config
{
    ARM_DRIVER_USART*       uartDriverHandler;    /**< uart driver handler */
    uint8_t*                recvBuffPtr;          /**< pointer to recv buffer */
    uint32_t                recvBuffSize;         /**< size of recv buffer */
    hal_uart_recv_cb_t      recv_cb;              /**< user-supplied receive callback */
    hal_uart_pre_send_cb_t  pre_send_cb;          /**< user-supplied pre-send callback */
    hal_uart_post_send_cb_t post_send_cb;         /**< user-supplied post-send callback */
} hal_uart_config_t;

/** \brief configuration struct for initializing UART hardware */
typedef struct _hal_uart_hardware_config
{
    ARM_POWER_STATE        powerMode;                    /**< UART power mode, ARM_POWER_FULL or ARM_POWER_LOW */
    uint32_t               controlSetting;               /**< setting value passed to ARM Control API */
    uint32_t               baudRate;                     /**< baudrate value */
} hal_uart_hardware_config_t;

/**
  \brief Initilize HAL UART handler
  \param[in] uartIndex          uart index
  \param[in] config             pointer to configuration for initialization
  \param[in] hwConfig           pointer to uart hardware configuration for initialization
  \param[in] taskCreateFlag     flag to control whether to create send or receive task or not
  \return    error code
 */
int32_t HAL_UART_InitHandler(uint8_t uartIndex, hal_uart_config_t* config, hal_uart_hardware_config_t* hwConfig, hal_uart_task_create_flag_t taskCreateFlag);

/**
  \brief Initilize HAL UART handler
  \param[in] uartIndex     uart index
  \param[in] newHwConfig   pointer to new uart hardware configuration
  \param[in] startRecv     flag for indicating whether start to receive after successful call or not
  \return    error code
 */
int32_t HAL_UART_ResetUartSetting(uint8_t uartIndex, hal_uart_hardware_config_t* newHwConfig, bool startRecv);

/**
  \brief De-initilize HAL UART handler
  \param[in] uartIndex  uart index
  \return    void
  */
void HAL_UART_DeInitHandler(uint8_t uartIndex);

/**
  \brief    Send msg to uart send task
  \param[in] type         message type, \ref hal_uart_send_msg_type_t
  \param[in] uartIdx      uart index indicating which UART port the message will be sent to
  \param[in] msgPtr       pointer to message data
  \param[in] msgLen       lengh of message data in unit of byte
  \return    void
 */
void HAL_UART_SendMsg(uint16_t type, uint8_t uartIdx, uint8_t* msgPtr, uint16_t msgLen);

/**
  \brief    Send string to uart send task for print
  \param[in] uartIdx      uart index indicating which UART port the message will be sent to
  \param[in] strPtr       pointer to string body
  \param[in] strLen       string length
  \return    void
 */
void HAL_UART_SendStr(uint8_t uartIdx, uint8_t* strPtr, uint16_t strLen);

/**
  \brief    Bypass SEND task and send string to uart directly
  \param[in] uartIdx      uart index indicating which UART port the message will be sent to
  \param[in] strPtr       pointer to string body
  \param[in] strLen       string length
  \return    void
  \note     Used only in specific cases, such as sleep entering procedure where we should not switch out from IDLE task
 */
void HAL_UART_DirectSendStr(uint8_t uartIdx, uint8_t* strPtr, uint16_t strLen);


/**
  \brief    HAL UART Recv flow control
  \param[in] on           recv control flag, set true to disable recv and false to enable recv
  \return    void
 */
void HAL_UART_RecvFlowControl(bool on);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* _HAL_UART_H */
