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
 * \file HT_usart_unilog.h
 * \brief USART unilog configuration file.
 * 
 * \author HT Micron Advanced R&D,
 *         Hêndrick Bataglin Gonçalves, Christian Roberto Lehmen,  Matheus da Silva Zorzeto, Felipe Kalinski Ferreira,
 *         Leandro Borges, Mauricio Carlotto Ribeiro, Henrique Kuhn, Cleber Haack, Eduardo Mendel
 * 
 * \link https://github.com/htmicron
 * \version 1.0
 * \date February 27, 2024
 */

#ifndef __HT_USART_UNILOG_H__
#define __HT_USART_UNILOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "clock_qcx212.h"
#include "bsp.h"
#include "system_qcx212.h"
#include "debug_log.h"
#include "hal_uart.h"
#include "mem_map.h"

/* Defines  ------------------------------------------------------------------*/

#define UNILOG_RECV_BUFFER_SIZE       96

/* Functions  ----------------------------------------------------------------*/

/*!******************************************************************
 * \fn void logToolCommandHandle(uint32_t event, uint8_t *cmd_buffer, uint32_t len)
 * \brief Handle downlink command sent from unilog tool EPAT
 *          if need to handle more command in future, add command-handler table
 *
 * \param[in] uint32_t event         UART event, note used in this function
 * \param[in] uint8_t *cmd_buffer    Command received from UART
 * \param[in] uin32_t len            Command length
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void logToolCommandHandle(uint32_t event, uint8_t *cmd_buffer, uint32_t len);

/*!******************************************************************
 * \fn void SetUnilogUart(usart_port_t port, uint32_t baudrate, bool startRecv)
 * \brief Initialize an USART instance to operate as unilog transmitter.
 *
 * \param[in] usart_port_t port        USART port.
 * \param[in] uint32_t baudrate        USART unilog baudrate.
 * \param[in] bool startRecv           Receive flag.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void SetUnilogUart(usart_port_t port, uint32_t baudrate, bool startRecv);

#endif /*__HT_USART_UNILOG_H__*/

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
