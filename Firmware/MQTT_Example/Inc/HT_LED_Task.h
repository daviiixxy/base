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
 * \file HT_LED_Task.h
 * \brief LED tasks functions. 
  * \author HT Micron Advanced R&D,
 *         Hêndrick Bataglin Gonçalves, Christian Roberto Lehmen,  Matheus da Silva Zorzeto, Felipe Kalinski Ferreira,
 *         Leandro Borges, Mauricio Carlotto Ribeiro, Henrique Kuhn, Cleber Haack, Eduardo Mendel
 *         Gleiser Alvarez Arrojo
 * 
 * \link https://github.com/htmicron
 * \version 0.1
 * \date February 23, 2023
 */

#ifndef __HT_LED_TASK_H__
#define __HT_LED_TASK_H__

#include "main.h"

/* Defines  ------------------------------------------------------------------*/

#define LED_TASK_STACK_SIZE    (1024*4)                     /**</ Bytes that will be allocated for this task. */

#define GREEN_LED_DELAY 1000                                /**</ Led blinking delay. */

/* Functions ------------------------------------------------------------------*/

/*!******************************************************************
 * \fn void HT_LED_GreenLedTask(void *arg)
 * \brief Initialize a task that will control the green led. In this
 * application, the green led means the device is connected.
 *
 * \param[in]  void *arg          Parameters that are supposed to be used in this task.
 * \param[out] none
 *
 * \retval none
 *******************************************************************/
void HT_LED_GreenLedTask(void *arg);

#endif /*__HT_LED_TASK_H__*/

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
