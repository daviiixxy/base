#ifndef _QURT_NETWORK_H
#define _QURT_NETWORK_H

#include "sockets.h"
#include "netdb.h"

#define QAPI_OK 0

#define print_ipad(ip) inet_ntoa((ip))

static inline int qapi_socket(int32_t family, int32_t type, int32_t protocol)
{
	return lwip_socket(family, type, protocol);
}

static inline int qapi_bind(int32_t handle, struct sockaddr *addr, int32_t addrlen)
{
	return lwip_bind(handle, addr, (socklen_t)addrlen);
}

static inline int qapi_connect(int32_t handle, struct sockaddr *srvaddr, int32_t addrlen)
{
	return lwip_connect(handle, srvaddr, (socklen_t) addrlen);
}

static inline int qapi_setsockopt(int32_t handle, int32_t level, int32_t optname, void *optval, int32_t optlen)
{
	return lwip_setsockopt(handle, level, optname, optval, (socklen_t) optlen);
}
static inline int qapi_getsockopt(int32_t handle, int32_t level, int32_t optname, void *optval, int32_t optlen)
{
	return lwip_getsockopt(handle, level, optname, optval, (socklen_t *) &optlen);
}

static inline int qapi_socketclose(int32_t handle)
{
	return lwip_close(handle);
}

static inline int qapi_errno(int32_t handle)
{
	return sock_get_errno(handle);
}

static inline int qapi_recvfrom(int32_t handle, char *buf, int32_t len, int32_t flags, struct sockaddr *from, int32_t *fromlen)
{
	return lwip_recvfrom(handle, buf, len, flags, from, (socklen_t *)fromlen);
}

static inline int qapi_sendto(int32_t handle, char *buf, int32_t len, int32_t flags, struct sockaddr *to, int32_t tolen)
{
	return lwip_sendto(handle, buf, len, flags, to, (socklen_t) tolen);
}

static inline int qapi_select(fd_set *rd, fd_set *wr, fd_set *ex, int32_t timeout_ms)
{
	struct timeval timeout = {0};
	timeout.tv_usec = timeout_ms * 1000;
	return lwip_select(FD_SETSIZE, rd, wr, ex, &timeout);
}

#endif //_QURT_NETWORK_H
