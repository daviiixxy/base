/******************************************************************************

  @file    connection.h

  ---------------------------------------------------------------------------

  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

/*******************************************************************************
 *
 * Copyright (c) 2013, 2014 Intel Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    David Navarro, Intel Corporation - initial API and implementation
 *    
 *******************************************************************************/

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <stdio.h>
#include <time.h>
//#include "qapi_ssl.h"
#include "qapi_mbedtls.h"
#include "qapi_coap.h"


#define INET4_ADDRSTRLEN  INET_ADDRSTRLEN

#define ESUCCESS 0
#define EFAILURE -1

//#define AF_NONIP 1 //<PORT_TODO> remove when NIDD is supported


/* The pad buffer in struct sockaddr_in passed to qapi_sendto is memset to zero,
 * but when received from qapi_recvfrom the pad has some bytes set with value 02,
 * hence to avoid memcmp failure pad buffer is not considered while comparing address */
#define SOCKADDRLEN (sizeof(struct sockaddr_in) - 8)

#define LWM2M_STANDARD_PORT_STR "5683"
#define LWM2M_STANDARD_PORT      5683
#define LWM2M_DTLS_PORT_STR     "5684"
#define LWM2M_DTLS_PORT          5684
#define LWM2M_BSSERVER_PORT_STR "5685"
#define LWM2M_BSSERVER_PORT      5685

extern const char* coap_malloc_error;
extern const char* coap_invalid_params;
extern const char* coap_ctx_fail;
#if 0
#ifndef MOB_TX
typedef struct timeval
{
   time_t tv_sec;     /* seconds */
   long   tv_usec;    /* and microseconds */
}timeval;
#endif
#endif
typedef struct _connection_t
{
  int                     sock;
  struct sockaddr         addr; 
  size_t                  addrLen;
  time_t last_conn_time;  /* every connection maintain the conn time when last downlink packet received */
  uint32_t callHandle;      /* Data Call Handle will be used for NIDD */
  int proto;              /* Transport Layer Protocol to be used */
#if 1 //<PORT_TODO> DTLS
#ifdef DTLS_SUPPORT
  SSL_Obj_Hdl_t ssl;
  //qapi_Net_SSL_Con_Hdl_t ssl;
#endif
#endif
}connection_t;

/* CoAP security mode */
typedef enum {
  COAP_PSK = 0,
  COAP_RPK,
  COAP_CERTIFICATE,
  COAP_NO_SEC
}coap_sec_mode;

//extern int  inet_pton(int afType, const char *src, void *dst); /* string to Binary addr */
//extern const char *inet_ntop(int afType, const void *src, char *dst, size_t size); /* Binary addr to string */

int create_socket(struct sockaddr client_addr, bool isBindRequired , uint32_t dataCallHdl);


connection_t * connection_new_incoming(int sock,struct sockaddr * addr,size_t addrLen);
int connection_create(void *contextP, qapi_Coap_Connection_Cfg_t * conn_config);
void connection_free(connection_t * connList);
int connection_send(connection_t *connP, uint8_t * buffer, size_t length);


#endif
