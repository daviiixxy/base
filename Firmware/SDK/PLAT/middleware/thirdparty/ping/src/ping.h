#ifndef LWIP_PING_H
#define LWIP_PING_H

#include "lwip/ip_addr.h"

/**
 * PING_USE_SOCKETS: Set to 1 to use sockets, otherwise the raw api is used
 */
#ifndef PING_USE_SOCKETS
#define PING_USE_SOCKETS    LWIP_SOCKET
#endif

/*ping retry count*/
#define PING_TRY_COUNT 15
#define PING_ALWAYS 255
#define PING_PAYLOAD_MAX_LEN 1520

BOOL ping_init(const ip_addr_t* ping_addr, uint8_t t_flag, uint16_t payload_len, uint32_t timeout, BOOL raiFlag, uint16_t req_handle);
BOOL ping_url_init(const char* ping_url_addr, uint8_t t_flag, uint16_t payload_len, uint32_t timeout, BOOL raiFlag, uint16_t req_handle);

void ping_terminat(void);

int ping_get_addr_info_async(char *name, uint16_t src_hdr);

#if !PING_USE_SOCKETS
void ping_send_now(void);
#endif /* !PING_USE_SOCKETS */

#endif /* LWIP_PING_H */
