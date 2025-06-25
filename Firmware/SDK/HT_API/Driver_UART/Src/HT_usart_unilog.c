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

#include "HT_usart_unilog.h"
#include "HT_Peripheral_Config.h"
#include "htnb32lxxx_hal_usart.h"

static uint8_t unilog_uart_recv_buf[UNILOG_RECV_BUFFER_SIZE];
ARM_DRIVER_USART *UsartUnilogHandle = NULL;

#if (RTE_UART0 && USART_UNILOG_SELECT == HAL_USART0_SELECT)

extern const USART_HandleTypeDef huart0;

static ARM_USART_CAPABILITIES     HAL_UNILOG_USART0_GetCapabilities (void)                                                { return HAL_USART_GetCapabilities (&huart0); }
static int32_t                    HAL_UNILOG_USART0_Initialize      (ARM_USART_SignalEvent_t cb_event)                    { return HAL_USART_Initialize (cb_event, &huart0); }
static int32_t                    HAL_UNILOG_USART0_Uninitialize    (void)                                                { return HAL_USART_Uninitialize (&huart0); }
static int32_t                    HAL_UNILOG_USART0_PowerControl    (ARM_POWER_STATE state)                               { return HAL_USART_PowerControl (state, &huart0); }
static int32_t                    HAL_UNILOG_USART0_Send            (const void *data, uint32_t num)                      { return HAL_USART_Send (&huart0, (uint8_t *)data, num); }
static int32_t                    HAL_UNILOG_USART0_Receive         (void *data, uint32_t num)                            { return HAL_USART_ReceivePolling (&huart0, (uint8_t *)data, num); }
static int32_t                    HAL_UNILOG_USART0_Transfer        (const void *data_out, void *data_in, uint32_t num)   { return HAL_USART_Transfer (&huart0, data_out, data_in, num); }
static int32_t                    HAL_UNILOG_USART0_SendPolling     (const void *data, uint32_t num)                      { return HAL_USART_SendPolling (&huart0, (uint8_t *)data, num); }
static uint32_t                   HAL_UNILOG_USART0_GetTxCount      (void)                                                { return HAL_USART_GetTxCount (&huart0); }
PLAT_CODE_IN_RAM static uint32_t  HAL_UNILOG_USART0_GetRxCount      (void)                                                { return HAL_USART_GetRxCount (&huart0); }
static uint32_t                   HAL_UNILOG_USART0_GetBaudRate      (void)                                               { return HAL_USART_GetBaudRate (&huart0); }
static int32_t                    HAL_UNILOG_USART0_Control         (uint32_t control, uint32_t arg)                      { return HAL_USART_Control (control, arg, &huart0); }
static ARM_USART_STATUS           HAL_UNILOG_USART0_GetStatus       (void)                                                { return HAL_USART_GetStatus (&huart0); }
static int32_t                    HAL_UNILOG_USART0_SetModemControl (ARM_USART_MODEM_CONTROL control)                     { return HAL_USART_SetModemControl (control, &huart0); }
static ARM_USART_MODEM_STATUS     HAL_UNILOG_USART0_GetModemStatus  (void)                                                { return HAL_USART_GetModemStatus (&huart0); }
PLAT_CODE_IN_RAM       void       HAL_UNILOG_USART0_IRQHandler      (void)                                                {        USART_IRQHandler (&huart0); }

ARM_DRIVER_USART Driver_USART0 = {
    ARM_USART_GetVersion,
    HAL_UNILOG_USART0_GetCapabilities,
    HAL_UNILOG_USART0_Initialize,
    HAL_UNILOG_USART0_Uninitialize,
    HAL_UNILOG_USART0_PowerControl,
    HAL_UNILOG_USART0_Send,
    HAL_UNILOG_USART0_Receive,
    HAL_UNILOG_USART0_Transfer,
    HAL_UNILOG_USART0_GetTxCount,
    HAL_UNILOG_USART0_GetRxCount,
    HAL_UNILOG_USART0_Control,
    HAL_UNILOG_USART0_GetStatus,
    HAL_UNILOG_USART0_SetModemControl,
    HAL_UNILOG_USART0_GetModemStatus,
    HAL_UNILOG_USART0_GetBaudRate,
    HAL_UNILOG_USART0_SendPolling
};

#endif

#if (RTE_UART1 && USART_UNILOG_SELECT == HAL_USART1_SELECT)

extern const USART_HandleTypeDef huart1;

static ARM_USART_CAPABILITIES     HAL_UNILOG_USART1_GetCapabilities (void)                                                { return HAL_USART_GetCapabilities (&huart1); }
static int32_t                    HAL_UNILOG_USART1_Initialize      (ARM_USART_SignalEvent_t cb_event)                    { return HAL_USART_Initialize (cb_event, &huart1); }
static int32_t                    HAL_UNILOG_USART1_Uninitialize    (void)                                                { return HAL_USART_Uninitialize (&huart1); }
static int32_t                    HAL_UNILOG_USART1_PowerControl    (ARM_POWER_STATE state)                               { return HAL_USART_PowerControl (state, &huart1); }
static int32_t                    HAL_UNILOG_USART1_Send            (const void *data, uint32_t num)                      { return HAL_USART_Send (&huart1, (uint8_t *)data, num); }
static int32_t                    HAL_UNILOG_USART1_Receive         (void *data, uint32_t num)                            { return HAL_USART_ReceivePolling (&huart1, (uint8_t *)data, num); }
static int32_t                    HAL_UNILOG_USART1_Transfer        (const void *data_out, void *data_in, uint32_t num)   { return HAL_USART_Transfer (&huart1, data_out, data_in, num); }
static int32_t                    HAL_UNILOG_USART1_SendPolling     (const void *data, uint32_t num)                      { return HAL_USART_SendPolling (&huart1, (uint8_t *)data, num); }
static uint32_t                   HAL_UNILOG_USART1_GetTxCount      (void)                                                { return HAL_USART_GetTxCount (&huart1); }
PLAT_CODE_IN_RAM static uint32_t  HAL_UNILOG_USART1_GetRxCount      (void)                                                { return HAL_USART_GetRxCount (&huart1); }
static uint32_t                   HAL_UNILOG_USART1_GetBaudRate      (void)                                               { return HAL_USART_GetBaudRate (&huart1); }
static int32_t                    HAL_UNILOG_USART1_Control         (uint32_t control, uint32_t arg)                      { return HAL_USART_Control (control, arg, &huart1); }
static ARM_USART_STATUS           HAL_UNILOG_USART1_GetStatus       (void)                                                { return HAL_USART_GetStatus (&huart1); }
static int32_t                    HAL_UNILOG_USART1_SetModemControl (ARM_USART_MODEM_CONTROL control)                     { return HAL_USART_SetModemControl (control, &huart1); }
static ARM_USART_MODEM_STATUS     HAL_UNILOG_USART1_GetModemStatus  (void)                                                { return HAL_USART_GetModemStatus (&huart1); }
PLAT_CODE_IN_RAM       void       HAL_UNILOG_USART1_IRQHandler      (void)                                                {        USART_IRQHandler (&huart1); }

ARM_DRIVER_USART Driver_USART1 = {
    ARM_USART_GetVersion,
    HAL_UNILOG_USART1_GetCapabilities,
    HAL_UNILOG_USART1_Initialize,
    HAL_UNILOG_USART1_Uninitialize,
    HAL_UNILOG_USART1_PowerControl,
    HAL_UNILOG_USART1_Send,
    HAL_UNILOG_USART1_Receive,
    HAL_UNILOG_USART1_Transfer,
    HAL_UNILOG_USART1_GetTxCount,
    HAL_UNILOG_USART1_GetRxCount,
    HAL_UNILOG_USART1_Control,
    HAL_UNILOG_USART1_GetStatus,
    HAL_UNILOG_USART1_SetModemControl,
    HAL_UNILOG_USART1_GetModemStatus,
    HAL_UNILOG_USART1_GetBaudRate,
    HAL_UNILOG_USART1_SendPolling
};

#endif

#if (RTE_UART2 && USART_UNILOG_SELECT == HAL_USART2_SELECT)

extern const USART_HandleTypeDef huart2;

static ARM_USART_CAPABILITIES     HAL_UNILOG_USART2_GetCapabilities (void)                                                { return HAL_USART_GetCapabilities (&huart2); }
static int32_t                    HAL_UNILOG_USART2_Initialize      (ARM_USART_SignalEvent_t cb_event)                    { return HAL_USART_Initialize (cb_event, &huart2); }
static int32_t                    HAL_UNILOG_USART2_Uninitialize    (void)                                                { return HAL_USART_Uninitialize (&huart2); }
static int32_t                    HAL_UNILOG_USART2_PowerControl    (ARM_POWER_STATE state)                               { return HAL_USART_PowerControl (state, &huart2); }
static int32_t                    HAL_UNILOG_USART2_Send            (const void *data, uint32_t num)                      { return HAL_USART_Send (&huart2, (uint8_t *)data, num); }
static int32_t                    HAL_UNILOG_USART2_Receive         (void *data, uint32_t num)                            { return HAL_USART_ReceivePolling (&huart2, (uint8_t *)data, num); }
static int32_t                    HAL_UNILOG_USART2_Transfer        (const void *data_out, void *data_in, uint32_t num)   { return HAL_USART_Transfer (&huart2, data_out, data_in, num); }
static int32_t                    HAL_UNILOG_USART2_SendPolling     (const void *data, uint32_t num)                      { return HAL_USART_SendPolling (&huart2, (uint8_t *)data, num); }
static uint32_t                   HAL_UNILOG_USART2_GetTxCount      (void)                                                { return HAL_USART_GetTxCount (&huart2); }
PLAT_CODE_IN_RAM static uint32_t  HAL_UNILOG_USART2_GetRxCount      (void)                                                { return HAL_USART_GetRxCount (&huart2); }
static uint32_t                   HAL_UNILOG_USART2_GetBaudRate      (void)                                               { return HAL_USART_GetBaudRate (&huart2); }
static int32_t                    HAL_UNILOG_USART2_Control         (uint32_t control, uint32_t arg)                      { return HAL_USART_Control (control, arg, &huart2); }
static ARM_USART_STATUS           HAL_UNILOG_USART2_GetStatus       (void)                                                { return HAL_USART_GetStatus (&huart2); }
static int32_t                    HAL_UNILOG_USART2_SetModemControl (ARM_USART_MODEM_CONTROL control)                     { return HAL_USART_SetModemControl (control, &huart2); }
static ARM_USART_MODEM_STATUS     HAL_UNILOG_USART2_GetModemStatus  (void)                                                { return HAL_USART_GetModemStatus (&huart2); }
PLAT_CODE_IN_RAM       void       HAL_UNILOG_USART2_IRQHandler      (void)                                                {        USART_IRQHandler (&huart2); }

ARM_DRIVER_USART Driver_USART2 = {
    ARM_USART_GetVersion,
    HAL_UNILOG_USART2_GetCapabilities,
    HAL_UNILOG_USART2_Initialize,
    HAL_UNILOG_USART2_Uninitialize,
    HAL_UNILOG_USART2_PowerControl,
    HAL_UNILOG_USART2_Send,
    HAL_UNILOG_USART2_Receive,
    HAL_UNILOG_USART2_Transfer,
    HAL_UNILOG_USART2_GetTxCount,
    HAL_UNILOG_USART2_GetRxCount,
    HAL_UNILOG_USART2_Control,
    HAL_UNILOG_USART2_GetStatus,
    HAL_UNILOG_USART2_SetModemControl,
    HAL_UNILOG_USART2_GetModemStatus,
    HAL_UNILOG_USART2_GetBaudRate,
    HAL_UNILOG_USART2_SendPolling
};

#endif

void logToolCommandHandle(uint32_t event, uint8_t *cmd_buffer, uint32_t len) {
    (void)event;

    uint8_t * LogDbVserion=getDebugDVersion();

    if(ec_strnstr((const char *)cmd_buffer, "^logversion", len)){
        HT_STRING(UNILOG_PLA_INTERNAL_CMD, get_log_version, P_SIG, "LOGVERSION:%s",LogDbVserion);
    } else {
        HT_STRING(UNILOG_PLA_STRING, get_log_version_1, P_ERROR, "%s", (uint8_t*)"invalid command from EPAT");
    }

    return;
}

void SetUnilogUart(usart_port_t port, uint32_t baudrate, bool startRecv) {
    hal_uart_config_t halUartConfig = {0};
    hal_uart_hardware_config_t hwConfig = {
                                            ARM_POWER_FULL,
                                            ARM_USART_MODE_ASYNCHRONOUS | ARM_USART_DATA_BITS_8 |
                                            ARM_USART_PARITY_NONE       | ARM_USART_STOP_BITS_1 |
                                            ARM_USART_FLOW_CONTROL_NONE,
                                            baudrate
                                           };

    if (port == PORT_USART_0) {
#if (RTE_UART0 && USART_UNILOG_SELECT == HAL_USART0_SELECT)
        UsartUnilogHandle = &CREATE_SYMBOL(Driver_USART, 0);
#else
    __NOP();
#endif

    } else if (port == PORT_USART_1) {
#if (RTE_UART1 && USART_UNILOG_SELECT == HAL_USART1_SELECT)
        UsartUnilogHandle = &CREATE_SYMBOL(Driver_USART, 1);
#else
    __NOP();
#endif
    } else if (port == PORT_USART_2) {
#if (RTE_UART2 && USART_UNILOG_SELECT == HAL_USART2_SELECT)
        UsartUnilogHandle = &CREATE_SYMBOL(Driver_USART, 2);
#else
    __NOP();
#endif
    }

    if (UsartUnilogHandle == NULL)
        return;

    halUartConfig.uartDriverHandler = UsartUnilogHandle;
    halUartConfig.recv_cb = (hal_uart_recv_cb_t)logToolCommandHandle;
    halUartConfig.recvBuffPtr = unilog_uart_recv_buf;
    halUartConfig.recvBuffSize = UNILOG_RECV_BUFFER_SIZE;

    if(startRecv) {
        HAL_UART_InitHandler(port, &halUartConfig, &hwConfig, HAL_UART_TASK_CREATE_FLAG_RECV);
    } else {
        HAL_UART_InitHandler(port, &halUartConfig, &hwConfig, HAL_UART_TASK_CREATE_FLAG_NONE);
    }
}

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
