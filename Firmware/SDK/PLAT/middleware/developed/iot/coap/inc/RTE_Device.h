#ifndef __RTE_DEVICE_H
#define __RTE_DEVICE_H

#include "qcx212.h"

/*  Peripheral IO Mode Select, Must Configure First !!!
    Note, when receiver works in DMA_MODE, interrupt is also enabled to transfer tailing bytes.
*/

#define POLLING_MODE            0x1
#define DMA_MODE                0x2
#define IRQ_MODE                0x3
#define UNILOG_MODE             0x4

#define RTE_UART0_TX_IO_MODE    UNILOG_MODE
#define RTE_UART0_RX_IO_MODE    DMA_MODE
#define USART0_RX_TRIG_LVL      (30)

#define RTE_UART1_TX_IO_MODE    POLLING_MODE
#define RTE_UART1_RX_IO_MODE    DMA_MODE

#define RTE_UART2_TX_IO_MODE    POLLING_MODE
#define RTE_UART2_RX_IO_MODE    DMA_MODE

#define RTE_SPI0_IO_MODE          POLLING_MODE

#define RTE_SPI1_IO_MODE          POLLING_MODE

#define I2C0_INIT_MODE          POLLING_MODE
#define I2C1_INIT_MODE          POLLING_MODE


// I2C0 (Inter-integrated Circuit Interface) [Driver_I2C0]
// Configuration settings for Driver_I2C0 in component ::Drivers:I2C
#define RTE_I2C0                        1

// { PAD_PIN25},  // 0 : gpio10 / 1 : I2C0 SCL
// { PAD_PIN26},  // 0 : gpio8  / 1 : I2C0 SDA
#define RTE_I2C0_SCL_PAD_ID                25
#define RTE_I2C0_SCL_FUNC               PAD_MuxAlt1

#define RTE_I2C0_SDA_PAD_ID                26
#define RTE_I2C0_SDA_FUNC               PAD_MuxAlt1

// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_I2C0_DMA_TX_EN              0
#define RTE_I2C0_DMA_TX_REQID           DMA_RequestI2C0TX
//   Rx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_I2C0_DMA_RX_EN              0
#define RTE_I2C0_DMA_RX_REQID           DMA_RequestI2C0RX

// I2C1 (Inter-integrated Circuit Interface) [Driver_I2C1]
// Configuration settings for Driver_I2C1 in component ::Drivers:I2C
#define RTE_I2C1                        1

// { PAD_PIN27},  // 0 : gpio17 / 1 : I2C1 SCL
// { PAD_PIN28},  // 0 : gpio9  / 1 : I2C1 SDA
#define RTE_I2C1_SCL_PAD_ID                27
#define RTE_I2C1_SCL_FUNC               PAD_MuxAlt1

#define RTE_I2C1_SDA_PAD_ID                28
#define RTE_I2C1_SDA_FUNC               PAD_MuxAlt1

// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_I2C1_DMA_TX_EN              1
#define RTE_I2C1_DMA_TX_REQID           DMA_RequestI2C1TX
//   Rx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_I2C1_DMA_RX_EN              1
#define RTE_I2C1_DMA_RX_REQID           DMA_RequestI2C1RX


// UART0 (Universal asynchronous receiver transmitter) [Driver_USART0]
// Configuration settings for Driver_USART0 in component ::Drivers:USART
#define RTE_UART0                       1
#define RTE_UART0_CTS_PIN_EN            1
#define RTE_UART0_RTS_PIN_EN            1

// { PAD_PIN13},  // 0 : gpio2 / 1 : UART0 RTSn / 3 : SPI1 SSn
// { PAD_PIN14},  // 0 : gpio3 / 1 : UART0 CTSn / 3 : SPI1 MOSI
// { PAD_PIN15},  // 0 : gpio4 / 1 : UART0 RXD  / 3 : SPI1 MISO
// { PAD_PIN16},  // 0 : gpio5 / 1 : UART0 TXD  / 3 : SPI1 SCLK
#define RTE_UART0_RTS_PAD_ID               13
#define RTE_UART0_RTS_FUNC              PAD_MuxAlt1

#define RTE_UART0_CTS_PAD_ID               14
#define RTE_UART0_CTS_FUNC              PAD_MuxAlt1

#define RTE_UART0_RX_PAD_ID                15
#define RTE_UART0_RX_FUNC               PAD_MuxAlt1

#define RTE_UART0_TX_PAD_ID                16
#define RTE_UART0_TX_FUNC               PAD_MuxAlt1

// DMA
//  Tx
//    Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_UART0_DMA_TX_REQID          DMA_RequestUSART0TX
//  Rx
//    Channel    <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_UART0_DMA_RX_REQID          DMA_RequestUSART0RX

// UART1 (Universal asynchronous receiver transmitter) [Driver_USART1]
// Configuration settings for Driver_USART1 in component ::Drivers:USART
#define RTE_UART1                       1
#define RTE_UART1_CTS_PIN_EN            0
#define RTE_UART1_RTS_PIN_EN            0
// { PAD_PIN17},  // 0 : gpio6   / 3 : UART1 RTS
// { PAD_PIN18},  // 0 : gpio7   / 3 : UART1 CTS
// { PAD_PIN19},  // 0 : gpio13  / 3 : UART1 RXD
// { PAD_PIN20},  // 0 : gpio12  / 3 : UART1 TXD
#define RTE_UART1_RTS_PAD_ID               17
#define RTE_UART1_RTS_FUNC              PAD_MuxAlt3

#define RTE_UART1_CTS_PAD_ID               18
#define RTE_UART1_CTS_FUNC              PAD_MuxAlt3

#define RTE_UART1_RX_PAD_ID                19
#define RTE_UART1_RX_FUNC               PAD_MuxAlt3

#define RTE_UART1_TX_PAD_ID                20
#define RTE_UART1_TX_FUNC               PAD_MuxAlt3

// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_UART1_DMA_TX_REQID          DMA_RequestUSART1TX
//   Rx
//     Channel    <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_UART1_DMA_RX_REQID          DMA_RequestUSART1RX

// UART2 (Universal asynchronous receiver transmitter) [Driver_USART2]
// Configuration settings for Driver_USART2 in component ::Drivers:USART
#define RTE_UART2                       0
#define RTE_UART2_CTS_PIN_EN            0
#define RTE_UART2_RTS_PIN_EN            0

// { PAD_PIN29},  // 0 : gpio18 / 1 : UART2 RXD
// { PAD_PIN30},  // 0 : gpio19 / 1 : UART2 TXD
#define RTE_UART2_RX_PAD_ID                29
#define RTE_UART2_RX_FUNC               PAD_MuxAlt1

#define RTE_UART2_TX_PAD_ID                30
#define RTE_UART2_TX_FUNC               PAD_MuxAlt1


// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_UART2_DMA_TX_REQID          DMA_RequestUSART2TX
//   Rx
//     Channel    <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_UART2_DMA_RX_REQID          DMA_RequestUSART2RX

// SPI0 (Serial Peripheral Interface) [Driver_SPI0]
// Configuration settings for Driver_SPI0 in component ::Drivers:SPI
#define RTE_SPI0                        1

// { PAD_PIN21},  // 0 : gpio16 / 1 : UART1 RTS / 2 : SPI0 SSn
// { PAD_PIN22},  // 0 : gpio11 / 1 : UART1 CTS / 2 : SPI0 MOSI
// { PAD_PIN23},  // 0 : gpio14 / 1 : UART1 RXD / 2 : SPI0 MISO
// { PAD_PIN24},  // 0 : gpio15 / 1 : UART1 TXD / 2 : SPI0 SCLK
#define RTE_SPI0_SSN_BIT                21
#define RTE_SPI0_SSN_FUNC               PAD_MuxAlt2

#define RTE_SPI0_MOSI_PAD_ID               22
#define RTE_SPI0_MOSI_FUNC              PAD_MuxAlt2

#define RTE_SPI0_MISO_PAD_ID               23
#define RTE_SPI0_MISO_FUNC              PAD_MuxAlt2

#define RTE_SPI0_SCLK_PAD_ID               24
#define RTE_SPI0_SCLK_FUNC              PAD_MuxAlt2

#define RTE_SPI0_SSN_GPIO_INSTANCE      1
#define RTE_SPI0_SSN_GPIO_INDEX         0

// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI0_DMA_TX_REQID           DMA_RequestSPI0TX

//   Rx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI0_DMA_RX_REQID           DMA_RequestSPI0RX

// SPI1 (Serial Peripheral Interface) [Driver_SPI1]
// Configuration settings for Driver_SPI1 in component ::Drivers:SPI
#define RTE_SPI1                        0

// { PAD_PIN13},  // 0 : gpio2 / 1 : UART0 RTSn / 3 : SPI1 SSn
// { PAD_PIN14},  // 0 : gpio3 / 1 : UART0 CTSn / 3 : SPI1 MOSI
// { PAD_PIN15},  // 0 : gpio4 / 1 : UART0 RXD  / 3 : SPI1 MISO
// { PAD_PIN16},  // 0 : gpio5 / 1 : UART0 TXD  / 3 : SPI1 SCLK
#define RTE_SPI1_SSN_PAD_ID                13
#define RTE_SPI1_SSN_FUNC               PAD_MuxAlt3

#define RTE_SPI1_MOSI_PAD_ID               14
#define RTE_SPI1_MOSI_FUNC              PAD_MuxAlt3

#define RTE_SPI1_MISO_PAD_ID               15
#define RTE_SPI1_MISO_FUNC              PAD_MuxAlt3

#define RTE_SPI1_SCLK_PAD_ID               16
#define RTE_SPI1_SCLK_FUNC              PAD_MuxAlt3

#define RTE_SPI1_SSN_GPIO_INSTANCE      0
#define RTE_SPI1_SSN_GPIO_INDEX         2

// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI1_DMA_TX_REQID           DMA_RequestSPI1TX

//   Rx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI1_DMA_RX_REQID           DMA_RequestSPI1RX


// PWM0 Controller [Driver_PWM0]
// Configuration settings for Driver_PWM0 in component ::Drivers:PWM
#define RTE_PWM                         1

#define EFUSE_INIT_MODE POLLING_MODE
#define L2CTLS_INIT_MODE POLLING_MODE

#define FLASH_BARE_RW_MODE 1

#endif  /* __RTE_DEVICE_H */
