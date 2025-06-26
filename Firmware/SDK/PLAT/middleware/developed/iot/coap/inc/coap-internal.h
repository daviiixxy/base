/******************************************************************************

  @file    coap-internal.h
  @brief   File contains the information specific to CoAP

  ---------------------------------------------------------------------------

  Copyright (c) 2016-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/
#ifndef _COAP_INIT_H                                                        
#define _COAP_INIT_H     
#include <stdarg.h>


#include "er-coap-13.h"
#include "coap_trans.h"
//#include "qapi_diag.h"
//#include "qurt.h"
#include "qurt_os.h"
#include"app_coap.h"
#include "connection.h"
#include "iotapp_log_util.h"
//#include "mem_utility.h"
//#include "dummy.h"


#define INVALID_PARAMS -    -1
#define SOCKET_ERROR        -2
#define SSL_ERROR           -3
#define COAP_CONNECT_NO_ERROR 0

#define COAP_DTLS_RESUMPTION_FAILED      -3
#define COAP_TRANSACTION_CALLBACK_NOT_SET -4

#define MAX_BLOCK_SESSIONS 2    /* Max number of Block session permissible */
#define UL_REQ 0                /* Uplink Block request */
#define DL_REQ 1                /* downlink Block request */


#define COAP_STRCPY(d,s,n) strlcpy(d,s,n)
#define COAP_MEMCPY(d,dn,s,cn) memcpy(d,s,((cn < dn)?cn:dn))//memscpy(d,dn,s,cn)
#define COAP_MEMMOVE(d,dn,s,cn) memmove(d,s,((cn < dn)?cn:dn))//memsmove(d,dn,s,cn)
/*
 * Error code
 */

#ifndef MINI_QCLI
#define CoAP_MQTT_LOGGING_ENABLED 1
#endif

#define COAP_NO_ERROR                   (uint8_t)0x00
#define COAP_IGNORE                     (uint8_t)0x01

#define COAP_201_CREATED                (uint8_t)0x41
#define COAP_202_DELETED                (uint8_t)0x42
#define COAP_204_CHANGED                (uint8_t)0x44
#define COAP_205_CONTENT                (uint8_t)0x45
#define COAP_231_CONTINUE               (uint8_t)0x5f
#define COAP_400_BAD_REQUEST            (uint8_t)0x80
#define COAP_401_UNAUTHORIZED           (uint8_t)0x81
#define COAP_402_BAD_OPTION             (uint8_t)0x82
#define COAP_403_FORBIDDEN              (uint8_t)0x83  
#define COAP_404_NOT_FOUND              (uint8_t)0x84
#define COAP_405_METHOD_NOT_ALLOWED     (uint8_t)0x85
#define COAP_406_NOT_ACCEPTABLE         (uint8_t)0x86
#define COAP_408_REQ_ENTITY_INCOMPLETE  (uint8_t)0x88
#define COAP_413_ENTITY_TOO_LARGE       (uint8_t)0x8f
#define COAP_500_INTERNAL_SERVER_ERROR  (uint8_t)0xA0
#define COAP_501_NOT_IMPLEMENTED        (uint8_t)0xA1
#define COAP_503_SERVICE_UNAVAILABLE    (uint8_t)0xA3


#define COAP_LOG_DIAG 0
#define COAP_LOG_CLI  2
#define COAP_LOG_NONE 2
#define COAP_TIMEOUT_SEC 5

/* Maximum length of log message */
#define COAP_LOG_INFO(format, ...)  iotapp_log( __MODULE__, __LINE__, MSG_LEGACY_HIGH,  VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__); 
#define COAP_LOG_DEBUG(format, ...) iotapp_log( __MODULE__, __LINE__, MSG_LEGACY_LOW,   VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__);
#define COAP_LOG_ERROR(format, ...) iotapp_log( __MODULE__, __LINE__, MSG_LEGACY_ERROR, VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__);

int coap_mutex_lock(qurt_mutex_t * mutex, const char* file_name, uint32_t line_number);
int coap_mutex_unlock(qurt_mutex_t * mutex, const char* file_name, uint32_t line_number);


#define COAP_LOCK_MUTEX(mutex)  coap_mutex_lock(mutex, __FILE__, __LINE__)
#define COAP_UNLOCK_MUTEX(mutex)    coap_mutex_unlock(mutex, __FILE__, __LINE__)



typedef enum {
  BLOCKWISE_INVALID_REQUEST = 0,                    /* invalid blockwise transfer request */
  BLOCKWISE_TRANSFER_REQUEST_FALSE,             /* blockwise request false, normal coap packet */
  BLOCKWISE_COAP_HANDLE_REQUEST,                /* blockwise request true and coap will handle the request */
  BLOCKWISE_APPLICATION_HANDLE_REQUEST          /* blockwise request true and application will handle the request */
} blockWise_handling_status_t;


typedef struct _coap_block_session_info_s
{
   uint64_t                                 last_msg_send_time;                    // last message sent time in seconds
   uint64_t                                 first_bl_time;
   uint64_t                                 tv_expiry_time;                      // expiry time in ms
   uint8_t *                                complete_payload;                      // pointer to complete buffer
   size_t                                   complete_PaylodLen;                         // complete payload length
   uint8_t*                                 nextBlockP;                         // pointer to current block
   size_t                                   numByteSent;                          // size of total block sent till now
   uint32_t                                 lastBlockNum;                          // last block number sent
   uint32_t                                 numBlockSent;                   // total blocks sent or recieve
   qapi_Coap_Block_Wise_Options_t           block_type;                  // block type
   uint16_t                                 block_size;                            // block size for this session
   uint8_t                                  etag_len;                               // ETAG option length.
   uint8_t                                  etag[COAP_ETAG_LEN];		               // Option for differentiating between representations of the same resource that vary over time.  
   uint8_t                                  token_len;                              // Length of the Token ID .
   uint8_t                                  token[COAP_TOKEN_LEN];                  // Token ID of the CoAP message .
   qapi_Coap_Content_Type_t                 content_type;               // coap content type 
   qapi_Coap_Packet_t *                     original_pkt;
   qapi_Coap_Packet_t *                     master_pkt;                // coap packet containing complete payload to be transfered , to be given to app in cb for freeing
}coap_block_session_info_t;


typedef struct _client_context_t{                                                              

  int sock;
  boolean sock_error;
  coap_handle_request client_handle_request_cb;
  connection_t * conninfo;
  void * clientH ;
  void * server_sessionH;
  int trans_count;
  coap_transaction_t * transactionList;     
  uint16_t nextMID;
  void * clientData;
  struct sockaddr       client_addr; 
  size_t            client_addrLen;
  int session_resumption_time;
#if 1 //<PORT_TODO> DTLS
  SSL_Obj_Hdl_t ssl;
  SSL_Config_t cfg;
  char ssl_psk_name[SSL_MAX_CERT_NAME_LEN];
  char ssl_cert_name[SSL_MAX_CERT_NAME_LEN];
  char ssl_ca_list[SSL_MAX_CERT_NAME_LEN];
  char ssl_di_cert[SSL_MAX_CERT_NAME_LEN];
#endif
  boolean bIsCoAPUriIPLiteral;
  uint8_t ssl_mode;
  boolean isResumed;
  uint32_t coap_max_retransmits;        /* Max Number of COAP Rxmts for CON Messages */
  uint32_t coap_transaction_timeout;    /* Transaction Timeout for CON Messages */
  double coap_ack_random_factor;
  uint32_t coap_max_latency;
  uint32_t coap_max_transmit_span;
  uint32_t coap_exchange_lifetime;
  qurt_mutex_t  * CoapClientMutex;
  uint32_t cid;
  boolean  disable_close_notify;        /* disable Close-Notify when shutdown connection*/ 
  coap_block_session_info_t * bl_info_param[MAX_BLOCK_SESSIONS];    /* CoAP_Blockwsie : Block session Params */
  boolean  handle_downlink_blockwise;
  qapi_Coap_Block_Transfer_Info_t block_transfer_info;
  uint32_t blockwise_max_age; 
  struct _client_context_t *next; // self referencial pointer 
#ifdef DAM_SUPPORT
  uint32_t module_uid;       /* module id */
  uint32_t module_instance;  /* module instance */
  coap_packet_ext_t * uspace_pkt;
#endif
  coap_event_callback_t event_cb;
}client_context_t; 

typedef struct
{
  uint8_t  flag;           // indicates which segments are set
  uint16_t objectId;
  uint16_t instanceId;
  uint16_t resourceId;
} coap_uri_t;

extern int coapLogPath;

//define in coap_utils.c
int coap_utils_intCopy(char * buffer, size_t length, int32_t value);

void dump_packet(uint8_t * buffer, int length);
void coap_dump_packet(uint8_t * buffer, int length);

//defined in transaction.c
void transaction_remove(client_context_t * contextP, coap_transaction_t * transacP);
void transaction_step(client_context_t * contextP, time_t currentTime, time_t * timeoutP);   

void Callback_Invoke_If_Send_Failure(client_context_t* context , coap_transaction_t * transacP);

qapi_Status_t initialize_block_info(client_context_t * contextP, coap_block_session_info_t ** block_info , qapi_Coap_Packet_t * pkt , uint16_t bsize);
qapi_Status_t get_block_wise_packet(client_context_t * contextP, qapi_Coap_Packet_t * pkt, coap_block_session_info_t * block_info , qapi_Coap_Block_Params_t * dl_block_param );
qapi_Status_t params_validity_check(client_context_t * ctxt, qapi_Coap_Packet_t * pkt , qapi_Coap_Block_Wise_Options_t btype , uint16_t bsize);
qapi_Status_t process_blockwise_transfer(client_context_t * contextP , coap_transaction_t * transacP, qapi_Coap_Packet_t * dl_pkt);
void clean_block_info(client_context_t * ctxt, coap_block_session_info_t * block_info);
coap_block_session_info_t* get_block_info_from_pkt(client_context_t * contextP , coap_packet_t * dl_pkt);
blockWise_handling_status_t get_blockWise_handling_status(client_context_t * contextP, coap_packet_t * dl_pkt, bool transaction);

void block_step(client_context_t * contextP);
qapi_Status_t coap_validate_and_get_module_info(qapi_Coap_Session_Hdl_t handle, uint32_t *module_uid, uint32_t *module_instance);
qapi_Status_t coap_copy_from_usr_ext_coap_pkt(uint32_t module_uid, uint32_t module_instance, void ** kspace_coap_pkt, uint32_t *kspace_buf_size, void * uspace_coap_pkt, uint32_t uspace_pkt_size);
void free_ext_msg_option(coap_ext_msg_option_t *ext_option, void * umem);
qapi_Status_t coap_copy_to_usr_ext_coap_extended_header(uint32_t module_uid, uint32_t module_instance, void ** u_pkt_header, uint32_t *u_pkt_header_len, void * k_pkt_header , uint32_t k_pkt_header_len, void * mem_pool , uint8_t all_options , uint16_t opt_num);
void coap_free_pkt(qapi_Coap_Packet_t * k_coap_pkt , void * mem_pool);
qapi_Status_t coap_copy_to_usr_ext_set_option(uint32_t module_uid, uint32_t module_instance, void * u_ext_pkt , void * k_ext_pkt , void * mem_pool , uint16_t opt_num);
qapi_Status_t coap_copy_from_usr_ext_pkt_options(uint32_t module_uid, uint32_t module_instance, void * k_coap_pkt , void * u_coap_pkt);
qapi_Status_t coap_copy_from_usr_ext_pkt_ext_option(uint32_t module_uid, uint32_t module_instance, void * k_coap_pkt , void * u_coap_pkt);
qapi_Status_t coap_copy_from_usr_ext_multi_option(uint32_t module_uid, uint32_t module_instance, void ** k_option , const void * u_option);
qapi_Status_t coap_copy_to_usr_ext_coap_multi_option(uint32_t module_uid, uint32_t module_instance, void ** u_pkt , void * k_pkt, void * mem_pool);
qapi_Status_t coap_copy_to_usr_ext_coap_header(uint32_t module_uid, uint32_t module_instance, void * u_pkt , void * k_pkt , void * mem_pool , qapi_Coap_Header_type header_type);
qapi_Status_t coap_copy_to_usr_ext_coap_set_ext_header(uint32_t module_uid, uint32_t module_instance, coap_packet_ext_t * u_ext_pkt , coap_packet_ext_t * k_ext_pkt , void * mem_pool , uint16_t opt_num);
int get_header_option_size(qapi_Coap_Header_type header_type , qapi_Coap_Packet_t * pkt);

#endif
