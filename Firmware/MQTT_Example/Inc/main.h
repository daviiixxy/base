/*

  _    _ _______   __  __ _____ _____ _____   ____  _   _
 | |  | |__   __| |  \/  |_   _/ ____|  __ \ / __ \| \ | |
 | |__| |  | |    | \  / | | || |    | |__) | |  | |  \| |
 |  __  |  | |    | |\/| | | || |    |  _  /| |  | | . ` |
 | |  | |  | |    | |  | |_| || |____| | \ \| |__| | |\  |
 |_|  |_|  |_|    |_|  |_|_____\_____|_|  \_\\____/|_| \_|
 =================== Advanced R&D ========================

 Copyright (c) 2023 HT Micron Semicondutores S.A.
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
 * \file main.h
 * \brief Main file of HTNB32L-XXX MQTT Example. 
  * \author HT Micron Advanced R&D,
 *         Hêndrick Bataglin Gonçalves, Christian Roberto Lehmen,  Matheus da Silva Zorzeto, Felipe Kalinski Ferreira,
 *         Leandro Borges, Mauricio Carlotto Ribeiro, Henrique Kuhn, Cleber Haack, Eduardo Mendel
 *         Gleiser Alvarez Arrojo
 * 
 * \link https://github.com/htmicron
 * \version 1.0
 * \date February 23, 2023
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#include "htnb32lxxx_hal_usart.h"
#include "HT_Fsm.h"
#include "HT_GPIO_Api.h"

#include "bsp.h"
#include "HT_BSP_Custom.h"
#include "osasys.h"
#include "ostask.h"
#include "queue.h"
#include "ps_event_callback.h"
#include "cmisim.h"
#include "cmimm.h"
#include "cmips.h"
#include "sockets.h"
#include "psifevent.h"
#include "ps_lib_api.h"
#include "lwip/netdb.h"
#include "debug_log.h"
#include "slpman_qcx212.h"
#include "MQTTClient.h"
#include "plat_config.h"
#include "debug_trace.h"
#include "hal_uart.h"
#include "HT_MQTT_Api.h"
#include "flash_qcx212.h"
#include "flash_qcx212_rt.h"
#include "slpman_qcx212.h"
#include "FreeRTOS.h"
#include "netmgr.h"
#include <stdio.h>

/* Defines  ------------------------------------------------------------------*/

#define QMSG_ID_BASE               (0x160) 
#define QMSG_ID_NW_IPV4_READY      (QMSG_ID_BASE)
#define QMSG_ID_NW_IPV6_READY      (QMSG_ID_BASE + 1)
#define QMSG_ID_NW_IPV4_6_READY    (QMSG_ID_BASE + 2)
#define QMSG_ID_NW_DISCONNECT      (QMSG_ID_BASE + 3)
#define QMSG_ID_SOCK_SENDPKG       (QMSG_ID_BASE + 4)
#define QMSG_ID_SOCK_RECVPKG       (QMSG_ID_BASE + 5)

#define INIT_TASK_STACK_SIZE    (1024*6)
#define RINGBUF_READY_FLAG      (0x06)
#define APP_EVENT_QUEUE_SIZE    (10)
#define MAX_PACKET_SIZE         (256)

#endif /* __MAIN_H__ */

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
