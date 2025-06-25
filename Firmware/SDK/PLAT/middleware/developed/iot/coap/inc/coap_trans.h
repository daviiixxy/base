/******************************************************************************

  @file    coap_trans.h
  @brief   File contains the implementation for CoAP transactions

  ---------------------------------------------------------------------------

  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _COAP_TRANS_H                                                            
#define _COAP_TRANS_H 

#include <stdlib.h>                                                             
#include <stdio.h>                                                              
#include <stdint.h>                                                             
#include <stdbool.h>
#include <time.h>
#include "qapi_coap.h"


#define COAP_OBJECT_STRING_ID_MAX_LEN 6 
#define COAP_INSTANCE_STRING_ID_MAX_LEN 6 
#define COAP_RESOURCE_STRING_ID_MAX_LEN 6 



typedef enum                                                                    
{                                                                               
  ENDPOINT_UNKNOWN = 0,                                                       
  ENDPOINT_CLIENT,                                                            
  ENDPOINT_SERVER                                                             
} lwm2m_endpoint_type_t;                                                        

typedef struct _coap_transaction_ coap_transaction_t;                         

typedef void (*coap_transaction_callback_t) (void * ,qapi_Coap_Transaction_t * transacP, void * message);

struct _coap_transaction_ 

{
  coap_transaction_t * next;  // matches lwm2m_list_t::next
  uint16_t              mID;   // matches lwm2m_list_t::id 
  void * message;
  uint8_t * buffer;
  void * userData;
  coap_transaction_callback_t callback;  
  uint16_t buffer_len;
  uint8_t               ack_received; // indicates, that the ACK was received 
  time_t                response_timeout; // timeout to wait for response, if token is used. When 0, use calculated acknowledge timeout.
  uint8_t  retrans_counter;                                                   
  time_t   retrans_time;
  void * sessionH;
  bool empty_ack_received;
};
#endif 

