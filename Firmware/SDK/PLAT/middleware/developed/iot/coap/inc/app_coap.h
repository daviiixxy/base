/******************************************************************************

  @file    app_coap.h
  @brief File contains the application interface to CoAP

  ---------------------------------------------------------------------------

  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef APP_COAP__H_                                                              
#define APP_COAP__H_    

#include <stdint.h>                                                             
#include <stddef.h> 
#include "qurt_network.h"
#include "er-coap-13.h"
#include "coap_trans.h"
#include "qapi_coap.h"


typedef  int32_t (*coap_handle_request)(qapi_Coap_Session_Hdl_t  hdl, qapi_Coap_Packet_t * message , void * usr_data);

typedef void (*coap_event_callback_t) (qapi_Coap_Session_Hdl_t hdl , qapi_Coap_Packet_t * coap_pkt , qapi_Coap_Event_t coap_event , void * event_info);


typedef struct coap_transacation {
  void *coapHandle;
  uint8_t* token;
  void *message ;
  uint8_t token_len ;
} coap_transac_new_param_t;


typedef struct coap_register {
  struct sockaddr         client_addr; 
  void *clientH;
  void *server_sessionH;
  coap_handle_request cleint_handle_request_cb;        
} coap_register_t;

void coap_thread_start(void); 

void * coap_register_client( qapi_Coap_Session_Info_t * coap_session_config );

void coap_close(void *coapHandle) ;

int coap_reconnect(void *coap_handle, void* session, char *new_local_ip, int session_resumption_time);
int coap_session_resumption(void *coap_handle, void* session, int session_resumption_time);

void transaction_free(coap_transaction_t * transacP);

coap_transaction_t * transaction_new(coap_transac_new_param_t *transac_newP);

int transaction_send(void * context, coap_transaction_t * transacP);

void coap_handle_packet(void * contextP, uint8_t * buffer, unsigned int length, void *fromSessionH);

coap_status_t message_send(void * context,coap_packet_t * message,void *sessionH , uint16_t *lastMid);

bool transaction_handleResponse(void * context,
    void * fromSessionH,
    coap_packet_t * message,
    coap_packet_t * response,
    void * umem);


void coap_close_connection(void *sessionH , void * userData, bool sessionResumption) ;

int16_t coap_buffer_send(void * sessionH, uint8_t * buffer, size_t length, void * userData , coap_transaction_t * transacP);

bool coap_session_is_equal(void * session1, void * session2, void * userData);

uint16_t coap_get_message_id( void *coap_Handle);

#endif

