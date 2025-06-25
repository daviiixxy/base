#ifndef  __HT_BSP_H__
#define  __HT_BSP_H__

#include "bsp.h"

void HT_BSP_CommonInit(void);

void HT_logToolCommandHandle(uint32_t event, uint8_t *cmd_buffer, uint32_t len);
uint8_t * HT_getUnilogRecvBuffer(void);
void HT_SetUnilogUart(usart_port_t port, uint32_t baudrate, bool startRecv);
void HT_delay_us(uint32_t us);

#endif /* __HT_BSP_H__ */
