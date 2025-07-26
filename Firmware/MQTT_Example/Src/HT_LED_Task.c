/**
 *
 * Copyright (c) 2023 HT Micron Semicondutores S.A.
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

#include "HT_LED_Task.h"

static StaticTask_t             green_led_thread;
static UINT8                    greenLedTaskStack[LED_TASK_STACK_SIZE];

extern volatile uint8_t button_irqn; 
extern volatile HT_Button button_color;

/* Function prototypes  ------------------------------------------------------------------*/

/*!******************************************************************
 * \fn static void HT_LED_GreenLedThread(void *arg)
 * \brief Thread created to keep the green led, used to show the network connection status, blinking.
 *
 * \param[in]  void *arg                Thread parameters.
 * \param[out] none
 *
 * \retval none.
 *******************************************************************/
static void HT_LED_GreenLedThread(void *arg);

/* ---------------------------------------------------------------------------------------*/

static void HT_LED_GreenLedThread(void *arg) {
    
    while (1) {
        HT_GPIO_WritePin(GREEN_LED_PIN, GREEN_LED_INSTANCE, LED_ON);
        osDelay(GREEN_LED_DELAY);
        HT_GPIO_WritePin(GREEN_LED_PIN, GREEN_LED_INSTANCE, LED_OFF);
        osDelay(GREEN_LED_DELAY);
    }

}

void HT_LED_GreenLedTask(void *arg) {
    osThreadAttr_t task_attr;

    memset(&task_attr,0,sizeof(task_attr));
    memset(greenLedTaskStack, 0xA5,LED_TASK_STACK_SIZE);
    task_attr.name = "green_led_thread";
    task_attr.stack_mem = greenLedTaskStack;
    task_attr.stack_size = LED_TASK_STACK_SIZE;
    task_attr.priority = osPriorityNormal;
    task_attr.cb_mem = &green_led_thread;
    task_attr.cb_size = sizeof(StaticTask_t);

    osThreadNew(HT_LED_GreenLedThread, NULL, &task_attr);
}
