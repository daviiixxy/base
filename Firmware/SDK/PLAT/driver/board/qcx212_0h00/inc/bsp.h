#ifndef  BSP_H
#define  BSP_H

#ifdef __cplusplus
extern "C" {
#endif
#include "version.h"
#include "Driver_Common.h"
#include "Driver_I2C.h"
#include "Driver_SPI.h"
#include "Driver_USART.h"
#include "HT_Peripheral_Config.h"
#include "pad_qcx212.h"
#include "gpio_qcx212.h"
#include "ic_qcx212.h"
#include "dma_qcx212.h"
#include "clock_qcx212.h"

#define STRING_EOL      "\r\n"
#define BOARD_NAME      "QCX212_EVK"

#define SDK_VERSION     "QCX212_SW_V"SDK_MAJOR_VERSION"."SDK_MINOR_VERSION"."SDK_PATCH_VERSION
#define EVB_VERSION     "QCX212_HW_V"EVB_MAJOR_VERSION"."EVB_MINOR_VERSION
#define VERSION_INFO    "-- SDK Version: "SDK_VERSION" -- "STRING_EOL"-- EVB Version: "EVB_VERSION" -- "STRING_EOL


#define BSP_HEADER       STRING_EOL"-- Board: "BOARD_NAME " -- "STRING_EOL \
                         VERSION_INFO \
                        "-- Compiled: "__DATE__" "__TIME__" -- "STRING_EOL

#define SOFTVERSION     "V"SDK_MAJOR_VERSION"."SDK_MINOR_VERSION"."SDK_PATCH_VERSION   // should be no longer than 15 byte

#define CREATE_SYMBOL(name, port) name##port


#define HIGH_TEMPR_HIB_THR 255


/** @brief UART port index
 * | UART port | Hardware Flow Control |
 * |-----------|-----------------------|
 * |  UART0    |           Y           |
 * |  UART1    |           Y           |
 * |  UART2    |           N           |
 */
typedef enum usart_port
{
    PORT_USART_0,                           /**< USART port 0. */
    PORT_USART_1,                           /**< USART port 1. */
    PORT_USART_2,                           /**< USART port 2. */
    PORT_USART_MAX,                         /**< The total number of USART ports (invalid UART port number). */
    PORT_USART_INVALID                     /**< USART invalid. */
} usart_port_t;

/** @brief IRQ Callback functions
 */
typedef void (*IRQ_Callback_t)();

/** @brief     delay time in microseconds
 *  @param[in] us   time to delay
 *  @note      Given the maximum cpu frequency is 204.8MHz and the limit in calculation,
 *             the maximum time can be delayed is 0xFFFFFFFF / 2048 = 2097151 us = 2097 ms
 */
void delay_us(uint32_t us);

char * ec_strnstr(const char * s, const char *find, size_t slen);
uint8_t* getBuildInfo(void);
uint8_t* getVersionInfo(void);
void FlushUnilogOutput(uint32_t flush_data);
void SetUnilogUart(usart_port_t port, uint32_t baudrate, bool startRecv);
void BSP_CommonInit(void);
void setOSState(uint8_t state);
uint8_t * getDebugDVersion(void);
void BSP_SetPrintUart(usart_port_t port);
uint8_t getHighTempThreshold(void);
uint8_t * getSdkMajorVerion(void);
uint32_t getUnilogUartPort(void);


#ifdef __cplusplus
}
#endif

#endif /* BSP_H */
