/*===========================================================================

  Copyright (c) 2008-2020 Qualcomm Technologies, Inc. All Rights Reserved

  Qualcomm Technologies Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

===========================================================================*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header:

when       who     what, where, why
--------   ---     ----------------------------------------------------------
25/04/18   leo     (TechComm) Edited/added Doxygen comments and markup.
13/09/17   leo     (TechComm) Edited/added Doxygen comments and markup.
27/08/17  vpulimi  Added support for extensible LWM2M objects.
===========================================================================*/

/*
!! IMPORTANT NOTE: "DATA SERVICES" VERSION CATEGORY. 
*/

/**
  @file
  qapi_lwm2m.h

  LWM2M interface file to interact with the LWM2M client module. 
*/

#ifndef LWM2M_QAPI_H
#define LWM2M_QAPI_H
#include <stdint.h>
#include "stdbool.h"
//#include "qapi_status.h"
//#include "qapi_data_txm_base.h"
//#include "qapi_driver_access.h"
//#include "qapi_socket.h"
#include "qurt_network.h"
//#include "dummy.h"
/** @addtogroup qapi_lwm2m_datatypes
@{ */


#if 1 //<PORT_TODO> to be removed at later point 
typedef int32_t qapi_Status_t;
#endif
/**
*  Maximum allowed LWM2M message ID size.
*/
#define QAPI_MAX_LWM2M_MSG_ID_LENGTH  10

/**
*  Maximum allowed length for LWM2M string resource.
*/
#define RESOURCE_MAXLEN  255

/**
*  Retrieve the LWM2M server short ID from the message ID information.
*  @hideinitializer
*/
#define QAPI_LWM2M_SERVER_ID_INFO(msg_buf, msg_len, server_id) \
{                                                              \
  server_id = 0x00;                                            \
  if (msg_len)                                                 \
    server_id = *((uint16_t *)(msg_buf + (msg_len - 2)));     \
}

#ifndef QAPI_OK
#define QAPI_OK                              ((qapi_Status_t)(0)) /**< Success.                   */
#endif
#ifndef QAPI_ERROR
#define QAPI_ERROR                           ((qapi_Status_t)-1)  /**< General error.             */
#endif
#define QAPI_ERR_INVALID_PARAM               ((qapi_Status_t)- 2) /**< Invalid parameter.         */
#define QAPI_ERR_NO_MEMORY                   ((qapi_Status_t)- 3) /**< Memory allocation error.   */
#define QAPI_ERR_NO_RESOURCE                 ((qapi_Status_t)- 4) /**< Resource allocation error. */
#define QAPI_ERR_BUSY                        ((qapi_Status_t)- 6) /**< Opertion busy.             */
#define QAPI_ERR_NO_ENTRY                    ((qapi_Status_t)- 7) /**< Entry not found.           */
#define QAPI_ERR_NOT_SUPPORTED               ((qapi_Status_t)- 8) /**< Feature not supported.     */
#define QAPI_ERR_TIMEOUT                     ((qapi_Status_t)- 9) /**< Operation timed out.       */
#define QAPI_ERR_BOUNDS                      ((qapi_Status_t)-10) /**< Out of bounds.             */
#define QAPI_ERR_BAD_PAYLOAD                 ((qapi_Status_t)-11) /**< Bad payload.               */
#define QAPI_ERR_EXISTS                      ((qapi_Status_t)-12) /**< Entry already exists.      */
#define QAPI_ERR_NOT_INITIALIZED             ((qapi_Status_t)-13) /**< Unintialized.              */
#define QAPI_ERR_API_DEPRACATED              ((qapi_Status_t)-14) /**< QAPI function is deprecated. */
#define QAPI_ERR_INVALID_STATE               ((qapi_Status_t)-15) /**< Invalid state.             */


/**
*  Handler provide by LWM2M client to the application.
*/
typedef void * qapi_Net_LWM2M_App_Handler_t;


typedef uint32_t objlink_t; /**< Object link. */

/**
 *  Enumerations used to identify a particular object with an object ID.
*/
typedef enum qapi_Net_LWM2M_Object_ID_e 
{
  QAPI_NET_LWM2M_SECURITY_OBJECT_ID_E        =  0,  /**< Security object ID. */
  QAPI_NET_LWM2M_SERVER_OBJECT_ID_E          =  1,  /**< Server object ID. */
  QAPI_NET_LWM2M_ACCESS_CONTROL_OBJECT_ID_E  =  2,  /**< ACL object ID. */
  QAPI_NET_LWM2M_DEVICE_OBJECT_ID_E          =  3,  /**< Device object ID. */
  QAPI_NET_LWM2M_FIRMWARE_UPDATE_OBJECT_ID_E =  5,  /**< Firmware update object ID. */
  QAPI_NET_LWM2M_LOCATION_OBJECT_ID_E        =  6,  /**< Location object ID. */
  QAPI_NET_LWM2M_SOFTWARE_MGNT_OBJECT_ID_E   =  9,  /**< Software management object ID. */
  QAPI_NET_LWM2M_CELL_NW_CONN_OBJECT_ID_E    =  10,  /**< Cellular network connectivity object ID. */
  QAPI_NET_LWM2M_APN_CONN_OBJECT_ID_E       =  11,  /**< APN connection object ID. */
  QAPI_NET_LWM2M_DEVICE_CAP_OBJECT_ID_E      = 15,  /**< Device capability object ID. */
} qapi_Net_LWM2M_Object_ID_t;

/**
 * Enumerations used to identify a particular resource of a security object.
*/  
typedef enum qapi_Net_LWM2M_Security_Resource_Id_e 
{
  QAPI_NET_LWM2M_SECURITY_RES_M_SERVER_URI_E        = 0,  /**< Server URI (string). */
  QAPI_NET_LWM2M_SECURITY_RES_M_BOOTSTRAP_SERVER_E  = 1,  /**< Bootstrap Server (boolean). */
  QAPI_NET_LWM2M_SECURITY_RES_M_SECURITY_MODE_E     = 2,  /**< Security Mode (integer). */
  
  QAPI_NET_LWM2M_SECURITY_RES_O_PUBLIC_KEY_E        = 3,  /**< Public Key or Identify (opaque). */
  QAPI_NET_LWM2M_SECURITY_RES_O_SERVER_PUBLIC_KEY_E = 4,  /**< Server Public Key (opaque). */
  QAPI_NET_LWM2M_SECURITY_RES_O_SECRET_KEY_E        = 5,  /**< Secrect Key (opaque). */
  
  QAPI_NET_LWM2M_SECURITY_RES_O_SMS_SERVER_NUMBER_E = 9,  /**< LwM2M Server SMS Number (string). */
  QAPI_NET_LWM2M_SECURITY_RES_O_SHORT_SERVER_ID_E   = 10, /**< Short Server ID (integer). */
  QAPI_NET_LWM2M_SECURITY_RES_O_HOLDOFF_TIME_E      = 11, /**< Client Hold Off Time (integer). */
} qapi_Net_LWM2M_Security_Resource_Id_t;

/*------------------------------------------------------------------------------
  MACRO declaration
------------------------------------------------------------------------------*/

typedef enum lwm2m_at_device_res_id_e
{
  LWM2M_AT_DEVICE_RES_MANUFACTURER   = 0,
  LWM2M_AT_DEVICE_RES_MODEL_NUMBER   = 1,
  LWM2M_AT_DEVICE_RES_SERIAL_NUMBER  = 2,
  LWM2M_AT_DEVICE_RES_FIRMEWARE_VER  = 3,
  LWM2M_AT_DEVICE_RES_DEVICE_TYPE    = 17,
  LWM2M_AT_DEVICE_RES_HARDWARE_VER   = 18,
  LWM2M_AT_DEVICE_RES_SOFTWARE_VER   = 19,
  LWM2M_AT_DEVICE_RES_DEVICE_INFO    = 22,
}lwm2m_at_device_res_id_t;




/**
 * Enumerations used to identify a particular resource of a server object.
*/  
typedef enum qapi_Net_LWM2M_Server_Resource_Id_e 
{
  QAPI_NET_LWM2M_SERVER_RES_M_SHORT_SERVER_ID_E      = 0,  /**< Short Server ID (integer).*/
  QAPI_NET_LWM2M_SERVER_RES_M_LIFE_TIME_E            = 1,  /**< Life Time (integer). */
  QAPI_NET_LWM2M_SERVER_RES_O_DEFAULT_PMIN_E         = 2,  /**< Default PMin (integer). */
  QAPI_NET_LWM2M_SERVER_RES_O_DEFAULT_PMAX_E         = 3,  /**< Default PMax (integer). */
  QAPI_NET_LWM2M_SERVER_RES_O_DISABLE_TIMEOUT_ID_E   = 5,  /**< Disable Timerout (integer). */
  QAPI_NET_LWM2M_SERVER_RES_M_STORING_ID_E           = 6,  /**< Notification Storing (boolean). */
  QAPI_NET_LWM2M_SERVER_RES_M_BINDING_ID_E           = 7,  /**< Binding (string). */
  QAPI_NET_LWM2M_SERVER_RES_O_APN_LINK_E             = 10, /**< APN Link (obj link). */
  QAPI_NET_LWM2M_SERVER_RES_O_REG_PRI_ORD_E          = 13, /**< Registration Priority Order (integer) */
  QAPI_NET_LWM2M_SERVER_RES_O_INITIAL_DELAY_TIMER_E  = 14, /**< Initial Registration Delay Timer (integer) */
  QAPI_NET_LWM2M_SERVER_RES_O_REG_FAILURE_BLOCK_E    = 15, /**< Registration Failure Block (boolean) */
  QAPI_NET_LWM2M_SERVER_RES_O_BS_ON_REG_FAILURE_E    = 16, /**< Bootstrap on Registration Failure (boolean) */
  QAPI_NET_LWM2M_SERVER_RES_O_COMM_RETRY_COUNT_E     = 17, /**< Communication Retry Count (integer) */
  QAPI_NET_LWM2M_SERVER_RES_O_COMM_RETRY_TIMER_E     = 18, /**< Communication Retry Timer (integer) */
  QAPI_NET_LWM2M_SERVER_RES_O_COMM_SEQ_DELAY_TIMER_E = 19, /**< Communication Sequence Delay Timer (integer) */
  QAPI_NET_LWM2M_SERVER_RES_O_COMM_SEQ_RETRY_COUNT_E = 20, /**< Communication Sequence Retry Count (integer) */
  QAPI_NET_LWM2M_SERVER_RES_O_TRIGGER_E              = 21, /**< Trigger (boolean). */
  QAPI_NET_LWM2M_SERVER_RES_O_PREFERRED_TRANSPORT_E  = 22, /**< Preferred Transport (string). */

} qapi_Net_LWM2M_Server_Resource_Id_t;

/**
 * Enumerations used to identify a particular resource of a server object.
*/  
typedef enum qapi_Net_LWM2M_Acl_Resource_Id_e 
{
  QAPI_NET_LWM2M_ACL_RES_M_OBJECT_ID_E          = 0,  /**< Object ID. (integer)*/
  QAPI_NET_LWM2M_ACL_RES_M_OBJECT_INSTANCE_ID_E = 1,  /**< Object Instance ID. (integer)*/
  QAPI_NET_LWM2M_ACL_RES_M_ACL_ID               = 2,  /**< ACL.(Multiple resource instance, integer) */
  QAPI_NET_LWM2M_ACL_RES_M_ACL_OWNER            = 3,  /**< Access control owner. (integer)*/
} qapi_Net_LWM2M_Acl_Resource_Id_t;

/**
 * Enumerations used to identify a particular resource of a device capability object.
*/  
typedef enum qapi_Net_LWM2M_Devicecap_Resource_Id_e 
{
  QAPI_NET_LWM2M_DEVICE_RES_M_PROPERTY_E         = 0,  /**< Property resource. */
  QAPI_NET_LWM2M_DEVICE_RES_M_GROUP_E            = 1,  /**< Group resource. */
  QAPI_NET_LWM2M_DEVICE_RES_O_DESCRIPTION_E      = 2,  /**< Description resource. */
  QAPI_NET_LWM2M_DEVICE_RES_O_ATTACHED_E         = 3,  /**< Attached resource. */
  QAPI_NET_LWM2M_DEVICE_RES_M_ENABLED_E          = 4,  /**< Enabled resource. */
  QAPI_NET_LWM2M_DEVICE_RES_M_OP_ENABLE_E        = 5,  /**< Operation enable. */
  QAPI_NET_LWM2M_DEVICE_RES_M_OP_DISBALE_E       = 6,  /**< Operation disable. */
  QAPI_NET_LWM2M_DEVICE_RES_O_NOTIFY_EN_E        = 7   /**< Notify enable. */
} qapi_Net_LWM2M_Devicecap_Resource_Id_t;

/**  Enumerations to identify valid firmware update resource IDs.
*/ 
typedef enum qapi_Net_LWM2M_Fota_Resource_Id_e 
{
  QAPI_NET_LWM2M_FOTA_RES_M_PACKAGE_E                 =  0,  /**< Package resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_PACKAGE_URI_E             =  1,  /**< Package URI resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_UPDATE_E                  =  2,  /**< Update resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_STATE_E                   =  3,  /**< State resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_UPDATE_RESULT_E           =  5,  /**< Update result resource. */
  QAPI_NET_LWM2M_FOTA_RES_O_PACKAGE_NAME_E            =  6,  /**< Package name resource. */
  QAPI_NET_LWM2M_FOTA_RES_O_PACKAGE_VERSION_E         =  7,  /**< Package version resource. */
  QAPI_NET_LWM2M_FOTA_RES_O_UPDATE_PROTOCOL_SUPPORT_E =  8,  /**< Update protocol support resource. */
  QAPI_NET_LWM2M_FOTA_RES_M_UPDATE_DELIVERY_METHOD_E  =  9,  /**< Update delivery method resource. */
} qapi_Net_LWM2M_Fota_Resource_Id_t;

/**  Enumerations to identify valid firmware update results.
*/
typedef enum  qapi_Net_LWM2M_Fota_Result_t_e 
{
  QAPI_NET_LWM2M_FOTA_RESULT_INITIAL_E                  = 0,  /**< Initial result. */
  QAPI_NET_LWM2M_FOTA_RESULT_UPDATE_SUCCESS_E           = 1,  /**< Update success. */
  QAPI_NET_LWM2M_FOTA_RESULT_NOT_ENOUGH_STORAGE_E       = 2,  /**< Not enough storage. */
  QAPI_NET_LWM2M_FOTA_RESULT_OUT_OF_MEMORY_E            = 3,  /**< Out of memory. */
  QAPI_NET_LWM2M_FOTA_RESULT_CONNECTION_LOST_E          = 4,  /**< Connection was lost. */
  QAPI_NET_LWM2M_FOTA_RESULT_CRC_CHECK_FAIL_E           = 5,  /**< CRC check failed. */
  QAPI_NET_LWM2M_FOTA_RESULT_UNSUPPORTED_PACKAGE_TYPE_E = 6,  /**< Unsupported package type. */
  QAPI_NET_LWM2M_FOTA_RESULT_INVAILD_URI_E              = 7,  /**< Invalid URI. */
  QAPI_NET_LWM2M_FOTA_RESULT_UPDATE_FAILED_E            = 8,  /**< Update failed. */
  QAPI_NET_LWM2M_FOTA_RESULT_UNSUPPORTED_PROTOCOL_E     = 9,  /**< Unsupported protocol. */
} qapi_Net_LWM2M_Fota_Result_t;


/** Enumerations to identify valid nw connectivity resource IDs.
*/
typedef enum  qapi_Net_LWM2M_NW_Conn_Resource_Id_e 
{
  QAPI_NET_LWM2M_NW_CONN_O_SMSC_ADDR_E                  = 0,  /**< SMSC address. */
  QAPI_NET_LWM2M_NW_CONN_O_DISABLE_RADIO_PERIOD_E       = 1,  /**< Disable Radio period. */
  QAPI_NET_LWM2M_NW_CONN_O_MOD_ACTIVATION_CODE_E        = 2,  /**< Module activation code. */
  QAPI_NET_LWM2M_NW_CONN_O_VENDOR_EXT_E                 = 3,  /**< Vendor specific extension. */
  QAPI_NET_LWM2M_NW_CONN_O_PSM_TIMER_E                  = 4,  /**< PSM timer type. */
  QAPI_NET_LWM2M_NW_CONN_O_ACTIVE_TIMER_E               = 5,  /**< Active timer. */
  QAPI_NET_LWM2M_NW_CONN_O_SERVING_PLMN_RATE_CONTROL_E  = 6,  /**< Serving PLMN Rate control. */
  QAPI_NET_LWM2M_NW_CONN_O_EDRX_IU_E                    = 7,  /**< eDRX parameters for Iu mode. */
  QAPI_NET_LWM2M_NW_CONN_O_EDRX_WB_S1_E                 = 8,  /**< eDRX parameters for WB S1 mode */
  QAPI_NET_LWM2M_NW_CONN_O_EDRX_NB_S1_E                 = 9,  /**< eDRX parameters for NB S1 mode. */
  QAPI_NET_LWM2M_NW_CONN_O_EDRX_AGB_E                   = 10,  /**< eDRX parameters for A/Gb mode. */
  QAPI_NET_LWM2M_NW_CONN_M_ACTIVATED_PROF_NAME_E        = 11,  /**< Activated profile names. */
} qapi_Net_LWM2M_NW_Conn_Resource_Id_t;



/** Enumerations to identify valid apn profile connection resource IDs.
*/
typedef enum  qapi_Net_LWM2M_APN_Resource_Id_e 
{
  QAPI_NET_LWM2M_APN_M_PROFILE_NAME_E            = 0,  /**< Profile name. */
  QAPI_NET_LWM2M_APN_O_APN_E                     = 1,  /**< APN name. */
  QAPI_NET_LWM2M_APN_O_AUTO_SELECT_APN_E         = 2,  /**< Auto select APN by device. */
  QAPI_NET_LWM2M_APN_O_ENABLE_STATUS_E           = 3,  /**< Connection status. */
  QAPI_NET_LWM2M_APN_M_AUTH_TYPE_E               = 4,  /**< Authentication type. */
  QAPI_NET_LWM2M_APN_O_USER_NAME_E               = 5,  /**< User name. */
  QAPI_NET_LWM2M_APN_O_SECRET_E                  = 6,  /**<  Password. */
  QAPI_NET_LWM2M_APN_O_RECONN_SCHEDULE_E         = 7,  /**< Reconnect schedule. */
  QAPI_NET_LWM2M_APN_O_VALIDITY_E                = 8,  /**< MCC, MNC information */
  QAPI_NET_LWM2M_APN_O_CONN_ESTB_TIME_E          = 9,  /**< Connection establishment time. */
  QAPI_NET_LWM2M_APN_O_CONN_ESTB_RESULT_E        = 10,  /**< Connection establishment result. */
  QAPI_NET_LWM2M_APN_O_CONN_ESTB_REJECT_CAUSE_E  = 11,  /**< Connection establishment reject cause. */
  QAPI_NET_LWM2M_APN_O_CONN_END_TIME_E           = 12,  /**< Connection end time. */
  QAPI_NET_LWM2M_APN_O_TOT_BYTES_SENT_E          = 13,  /**< Total bytes sent on interface. */
  QAPI_NET_LWM2M_APN_O_TOT_PKTS_SENT_E           = 23,  /**< Total packets sent on interface. */
  QAPI_NET_LWM2M_APN_O_TOT_BYTES_RECV_E          = 14,  /**< Total bytes recieved on interface. */
  QAPI_NET_LWM2M_APN_O_IP_ADDR_E                 = 15,  /**< IP address (IPv4 / IPv6). */
  QAPI_NET_LWM2M_APN_O_PREFIX_LEN_E              = 16,  /**< Prefix length for IPv6. */
  QAPI_NET_LWM2M_APN_O_SUBNET_MASK_E             = 17,  /**< Subnet mask. */
  QAPI_NET_LWM2M_APN_O_GATEWAY_E                 = 18,  /**< Gateway. */
  QAPI_NET_LWM2M_APN_O_PRI_DNS_E                 = 19,  /**< Primary DNS address. */
  QAPI_NET_LWM2M_APN_O_SEC_DNS_E                 = 20,  /**< Secondary DNS address. */
  QAPI_NET_LWM2M_APN_O_QCI_E                     = 21,  /**< QCI. */
  QAPI_NET_LWM2M_APN_O_VENDOR_EXT_E              = 22,  /**< Vendor specfic extensions. */
  QAPI_NET_LWM2M_APN_O_PDN_TYPE_E                = 24,  /**< PDN type. */
  QAPI_NET_LWM2M_APN_O_APN_CONTROL_E             = 25,  /**< APN control. */
} qapi_Net_LWM2M_APN_Resource_Id_t;

/** Enumerations to identify supported protocols.
*/
typedef enum qapi_Net_LWM2M_Fota_Supported_Protocols_e 
{
  QAPI_NET_LWM2M_FOTA_PROTOCOL_COAP  = 0,    /**< COAP Protocol. */
  QAPI_NET_LWM2M_FOTA_PROTOCOL_COAPS = 1,    /**< COAPS Protocol. */
  QAPI_NET_LWM2M_FOTA_PROTOCOL_HTTP  = 2,    /**< HTTP Protocol. */
  QAPI_NET_LWM2M_FOTA_PROTOCOL_HTTPS = 3,    /**< HTTPS Protocol. */
} qapi_Net_LWM2M_Fota_Supported_Protocols_t;

/**  Enumerations to identify the update delivery method.
*/
typedef enum qapi_Net_LWM2M_Fota_Update_Delivery_Method_e 
{
  QAPI_NET_LWM2M_FOTA_UPDATE_PULL_E = 0,  /**< Supports only the package method. */
  QAPI_NET_LWM2M_FOTA_UPDATE_PUSH_E = 1,  /**< Supports only the package URI method. */
  QAPI_NET_LWM2M_FOTA_UPDATE_BOTH_E = 2,  /**< Supports both the package and package URI methods. */
} qapi_Net_LWM2M_Fota_Update_Delivery_Method_t;

/**  Enumerations to identify the location resource ID.
*/
typedef enum qapi_Net_LWM2M_Location_Resource_Id_e
{
  QAPI_NET_LWM2M_LOCATION_RES_O_RADIUS_E = 3,  /**< Location resource is the radius. */
} qapi_Net_LWM2M_Location_Resource_Id_t;

/**
 *  Enumerations to identify a particular resource of a software management object.
*/ 
typedef enum qapi_Net_LWM2M_SW_Mgnt_Resource_Id_e 
{
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_NAME_E      = 0,  /**< Resource ID for Package Name. */
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_VERSION_E   = 1,  /**< Resource ID for Package Version. */
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_E           = 2,  /**< Resource ID for Package. */
  QAPI_NET_LWM2M_SW_MGNT_RES_O_PACKAGE_URI_E       = 3,  /**< Resource ID for Package URI. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_INSTALL_E           = 4,  /**< Resource ID for Install. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_UNINSTALL_E         = 6,  /**< Resource ID for Uninstall. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_UPDATE_STATE_E      = 7,  /**< Resource ID for Update State. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_UPDATE_RESULT_E     = 9,  /**< Resource ID for Update Result. */   
  QAPI_NET_LWM2M_SW_MGNT_RES_M_ACTIVATE_E          = 10, /**< Resource ID for Activate. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_DEACTIVATE_E        = 11, /**< Resource ID for Deactivate. */
  QAPI_NET_LWM2M_SW_MGNT_RES_M_ACTIVATION_STATE_E  = 12, /**< Resource ID for Activation State. */
} qapi_Net_LWM2M_SW_Mgnt_Resource_Id_t;

/**
 * Enumerations to identify a particular error value of a software management object.
*/ 
typedef enum qapi_Net_LWM2M_SW_Mgnt_Error_Value_e 
{
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INITIAL_E            = 0 , /**< Update result is Initial. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_DOWNLOADING_E        = 1 , /**< Update result is Downloading. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INSTALL_SUCCESS_E    = 2 , /**< Update result is Install Success. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_NO_ENOUGH_STORAGE_E  = 50, /**< Update result is Not Enough Storage. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_OUT_OF_MEMORY_E      = 51, /**< Update result is Device is Out of Memory. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_CONNECTION_LOST_E    = 52, /**< Update result is Connection Lost. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_PKG_CHECK_FAILURE_E  = 53, /**< Update result is Package Check Failure. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_PKG_UNSUPPORTED_E    = 54, /**< Update result is Package Unsupported. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INVALID_URI_E        = 56, /**< Update result is Invalid URI. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_UPDATE_ERROR_E       = 57, /**< Update result is Update Error. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_INSTALL_ERROR_E      = 58, /**< Update result is Install Error. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_RES_UNINSTALL_ERROR_E    = 59, /**< Update result is Uninstall Error. */
} qapi_Net_LWM2M_SW_Mgnt_Error_Value_t;

/**
 *   Enumerations to identify the particular state of a software management object.
*/
typedef enum qapi_Net_LWM2M_SW_Mgnt_State_e
{
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_INITIAL_E           = 0, /**< Update state is Initial. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_DOWNLOAD_STARTED_E  = 1, /**< Update state is Download Started. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_DOWNLOADED_E        = 2, /**< Update state is Downloaded. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_DELIVERED_E         = 3, /**< Update state is Delivered. */
  QAPI_NET_LWM2M_SW_MGNT_UPDATE_STATE_INSTALLED_E         = 4, /**< Update state is Installed. */
} qapi_Net_LWM2M_SW_Mgnt_State_t;

/**
 *   Enumerations to identify the particular state of a firmware object.
*/
typedef enum qapi_Net_Firmware_State_e 
{
  QAPI_NET_LWM2M_FIRWARE_STATE_IDLE_E = 0,     /**< Firmware state is Idle. */
  QAPI_NET_LWM2M_FIRWARE_STATE_DOWNLOADING_E,  /**< Firmware state is Downloading. */
  QAPI_NET_LWM2M_FIRWARE_STATE_DOWNLOADED_E,   /**< Firmware state is Downloaded. */
  QAPI_NET_LWM2M_FIRWARE_STATE_UPDATING_E,     /**< Firmware state is Updating. */
} qapi_Net_Firmware_State_t;

/**
*   Enumerations to identify the type of ID set in the LWM2M object information.
*/
typedef enum qapi_Net_LWM2M_ID_e
{
  QAPI_NET_LWM2M_OBJECT_ID_E             = 0x01,  /**< Object ID. */
  QAPI_NET_LWM2M_INSTANCE_ID_E           = 0x02,  /**< Instance ID. */
  QAPI_NET_LWM2M_RESOURCE_ID_E           = 0x04,  /**< Resource ID. */
  QAPI_NET_LWM2M_RESOURCE_INSTANCE_ID_E  = 0x08,  /**< Resource instance ID. */
} qapi_Net_LWM2M_ID_t;

/**
*   Enumerations to identify the type of resource value.
*/
typedef enum qapi_Net_LWM2M_Value_Type_e
{
  QAPI_NET_LWM2M_TYPE_UNDEFINED         = 0,  /**< Resource value type is Undefined. */
  QAPI_NET_LWM2M_TYPE_OBJECT            = 1,  /**< Resource value type is Object. */
  QAPI_NET_LWM2M_TYPE_OBJECT_INSTANCE   = 2,  /**< Resource value type is Object Instance. */
  QAPI_NET_LWM2M_TYPE_MULTIPLE_RESOURCE = 3,  /**< Resource value type is Multiple Resource. */
  QAPI_NET_LWM2M_TYPE_STRING_E          = 4,  /**< Resource value type is String. */
  QAPI_NET_LWM2M_TYPE_OPAQUE_E          = 5,  /**< Resource value type is Opaque. */
  QAPI_NET_LWM2M_TYPE_INTEGER_E         = 6,  /**< Resource value type is Integer. */
  QAPI_NET_LWM2M_TYPE_FLOAT_E           = 7,  /**< Resource value type is Float. */
  QAPI_NET_LWM2M_TYPE_BOOLEAN_E         = 8,  /**< Resource value type is Boolean. */
  QAPI_NET_LWM2M_TYPE_OBJECT_LINK       = 9,  /**< Resource value type is Object Link. */
} qapi_Net_LWM2M_Value_Type_t;

/**
*   LWM2M write attribute types.
*/
typedef enum qapi_Net_LWM2M_Write_Attr_e
{
  QAPI_NET_LWM2M_MIN_PERIOD_E   = 1,   /**< Minimum period. */
  QAPI_NET_LWM2M_MAX_PERIOD_E   = 2,   /**< Maximum period. */
  QAPI_NET_LWM2M_GREATER_THAN_E = 4,   /**< Greater than. */
  QAPI_NET_LWM2M_LESS_THAN_E    = 8,   /**< Less than. */
  QAPI_NET_LWM2M_STEP_E         = 16,  /**< Step. */
  QAPI_NET_LWM2M_DIM_E          = 32,  /**< Dimension. */
} qapi_Net_LWM2M_Write_Attr_t;

/**
*   LWM2M downlink message types.
*/
typedef enum qapi_Net_LWM2M_DL_Msg_e
{
  QAPI_NET_LWM2M_READ_REQ_E                  = 1,   /**< Read request. */
  QAPI_NET_LWM2M_WRITE_REPLACE_REQ_E         = 2,   /**< Write replace request. */
  QAPI_NET_LWM2M_WRITE_PARTIAL_UPDATE_REQ_E  = 3,   /**< Write partial update request. */
  QAPI_NET_LWM2M_WRITE_ATTR_REQ_E            = 4,   /**< Write attribute request. */
  QAPI_NET_LWM2M_DISCOVER_REQ_E              = 5,   /**< Discover request. */
  QAPI_NET_LWM2M_EXECUTE_REQ_E               = 6,   /**< Execute request. */
  QAPI_NET_LWM2M_DELETE_REQ_E                = 7,   /**< Delete request. */
  QAPI_NET_LWM2M_OBSERVE_REQ_E               = 8,   /**< Observe request. */
  QAPI_NET_LWM2M_CANCEL_OBSERVE_REQ_E        = 9,   /**< Cancel observe request. */
  QAPI_NET_LWM2M_ACK_MSG_E                   = 10,  /**< Acknowledge message. */
  QAPI_NET_LWM2M_INTERNAL_CLIENT_IND_E       = 11,  /**< Internal client indication. */
  QAPI_NET_LWM2M_CREATE_REQ_E                = 12,  /**< Create request. */
  QAPI_NET_LWM2M_DELETE_ALL_REQ_E            = 13,  /**< Delete all request. */
} qapi_Net_LWM2M_DL_Msg_t;

/**
*   LWM2M uplink message types.
*/
typedef enum qapi_Net_LWM2M_UL_Msg_e
{
  QAPI_NET_LWM2M_RESPONSE_MSG_E              = 1,  /**< Response message. */
  QAPI_NET_LWM2M_NOTIFY_MSG_E                = 2,  /**< Notify message. */
  QAPI_NET_LWM2M_CREATE_RESPONSE_MSG_E       = 3,  /**< Create response message. */
} qapi_Net_LWM2M_UL_Msg_t;

/**
*   LWM2M event information.
*/
typedef enum qapi_Net_LWM2M_Event_e
{
  QAPI_NET_LWM2M_STATE_INITIAL_E                 = 0,   /**< Initial state. */
  QAPI_NET_LWM2M_BOOTSTRAP_REQUIRED_E            = 1,   /**< Bootstrap required event. */
  QAPI_NET_LWM2M_BOOTSTRAP_COMPLETED_E           = 2,   /**< Bootstrap completed event. */
  QAPI_NET_LWM2M_BOOTSTRAP_FAILED_E              = 3,   /**< Bootstrap failed event. */
  QAPI_NET_LWM2M_REGISTERTION_COMPELTED_E        = 4,   /**< Registration completed event. */
  QAPI_NET_LWM2M_REGISTRATION_FAILED_E           = 5,   /**< Registration failed event. */
  QAPI_NET_LWM2M_DEVICE_REBOOT_E                 = 6,   /**< Device reboot event. */
  QAPI_NET_LWM2M_DEVICE_FACTORY_RESET_E          = 7,   /**< Device factory reset event. */
  QAPI_NET_LWM2M_DEVICE_REBOOTSTRAPPING_E        = 8,   /**< Device rebootstrapping event. */
  QAPI_NET_LWM2M_TX_MESSAGE_MAX_RETRY_FAILURE_E  = 9,  /**< Tx message maximum retry failure event. */
  QAPI_NET_LWM2M_RX_MESSAGE_INTERNAL_FAILURE_E   = 10,  /**< Rx message internal failure event. */
  QAPI_NET_LWM2M_SLEEP_E                         = 11,  /**< Sleep event. */
  QAPI_NET_LWM2M_WAKEUP_E                        = 12,  /**< Wake-up event. */
  QAPI_NET_LWM2M_CLIENT_RESET_E                  = 13,  /**< Reset event. */
  QAPI_NET_LWM2M_LIFETIME_UPDATE_E               = 14,  /**< Lifetime update event. */
  QAPI_NET_LWM2M_REGISTER_UPDATE_E               = 15,  /**< Register update event. */
  QAPI_NET_LWM2M_BOOTSTRAP_START_E		 = 16,	/**< Bootstrap required event. */
  QAPI_NET_LWM2M_BLOCKING_REGISTRATION_FAILURE_E = 18,  /**< Blocking registration failed event. */
} qapi_Net_LWM2M_Event_t;

/**
*   LWM2M response status codes.
*/
typedef enum qapi_Net_LWM2M_Response_Code_e
{
  QAPI_NET_LWM2M_IGNORE_E                      = 0x00,  /**< Ignore. */
  QAPI_NET_LWM2M_201_CREATED_E                 = 0x41,  /**< 201 - Created. */
  QAPI_NET_LWM2M_202_DELETED_E                 = 0x42,  /**< 202 - Deleted. */
  QAPI_NET_LWM2M_204_CHANGED_E                 = 0x44,  /**< 204 - Changed. */
  QAPI_NET_LWM2M_205_CONTENT_E                 = 0x45,  /**< 205 - Content. */
  QAPI_NET_LWM2M_400_BAD_REQUEST_E             = 0x80,  /**< 400 - Bad request. */
  QAPI_NET_LWM2M_401_UNAUTHORIZED_E            = 0x81,  /**< 401 - Unauthorized. */
  QAPI_NET_LWM2M_402_BAD_OPTION_E              = 0x82,  /**< 402 - Bad option. */
  QAPI_NET_LWM2M_403_FORBIDDEN_E               = 0x83,  /**< 403 - Forbidden. */
  QAPI_NET_LWM2M_404_NOT_FOUND_E               = 0x84,  /**< 404 - Not found. */
  QAPI_NET_LWM2M_405_METHOD_NOT_ALLOWED_E      = 0x85,  /**< 405 - Method is not allowed. */
  QAPI_NET_LWM2M_406_NOT_ACCEPTABLE_E          = 0x86,  /**< 406 - Not acceptable. */
  QAPI_NET_LWM2M_408_ENTITY_INCOMPLETE_E       = 0x88,  /**< 408 - Request Entity Incomplete. */
  QAPI_NET_LWM2M_413_ENTITY_TOO_LARGE_E        = 0x8D,  /**< 413 - Request entity too large. */
  QAPI_NET_LWM2M_415_UNSUPPORTED_DATA_FORMAT_E = 0x8F,  /**< 415 - Unsupported content format. */
  QAPI_NET_LWM2M_500_INTERNAL_SERVER_E         = 0xA0,  /**< 500 - Internal server. */
} qapi_Net_LWM2M_Response_Code_t;

/**
*   LWM2M message content type.
*/
typedef enum qapi_Net_LWM2M_Content_Type_t
{
  QAPI_NET_LWM2M_TEXT_PLAIN                    = 0,      /**< Plain text. */
  QAPI_NET_LWM2M_TEXT_XML                      = 1,      /**< XML text. */
  QAPI_NET_LWM2M_TEXT_CSV                      = 2,      /**< CSV text. */
  QAPI_NET_LWM2M_TEXT_HTML                     = 3,      /**< HTML text. */
  QAPI_NET_LWM2M_APPLICATION_LINK_FORMAT       = 40,     /**< Application link format. */
  QAPI_NET_LWM2M_APPLICATION_XML               = 41,     /**< Application XML. */
  QAPI_NET_LWM2M_APPLICATION_OCTET_STREAM      = 42,     /**< Application Octet stream. */
  QAPI_NET_LWM2M_APPLICATION_RDF_XML           = 43,     /**< Application RDF XML. */
  QAPI_NET_LWM2M_APPLICATION_SOAP_XML          = 44,     /**< Application SOAP XML. */
  QAPI_NET_LWM2M_APPLICATION_ATOM_XML          = 45,     /**< Application ATOM XML. */
  QAPI_NET_LWM2M_APPLICATION_XMPP_XML          = 46,     /**< Application XMPP XML. */
  QAPI_NET_LWM2M_APPLICATION_EXI               = 47,     /**< Application EXI. */
  QAPI_NET_LWM2M_APPLICATION_FASTINFOSET       = 48,     /**< Application FastInfoSet. */
  QAPI_NET_LWM2M_APPLICATION_SOAP_FASTINFOSET  = 49,     /**< Application SOAP FastInfoSet. */
  QAPI_NET_LWM2M_APPLICATION_JSON              = 50,     /**< Application JSON. */
  QAPI_NET_LWM2M_APPLICATION_X_OBIX_BINARY     = 51,     /**< Application X OBIX binary. */
  QAPI_NET_LWM2M_M2M_TLV                       = 11542,  /**< M2M TLV. */
  QAPI_NET_LWM2M_M2M_JSON                      = 11543   /**< M2M JSON. */
}qapi_Net_LWM2M_Content_Type_t;

/**
*   LWM2M configuration parameter type. 
*/
typedef enum qapi_Net_LWM2M_Config_Type_t
{
  QAPI_NET_LWM2M_CONFIG_BOOTSTRAP_URL   = 0,  /**< @deprecated Value is deprecated in version 2.1, Configure the bootstrap URL. */
  QAPI_NET_LWM2M_CONFIG_APN_NAME        = 1,  /**< @deprecated Value is deprecated in version 2.1, Configure the APN name. */
  QAPI_NET_LWM2M_CONFIG_SECURITY_MODE   = 2,  /**< @deprecated Value is deprecated in version 2.1, Configure the security mode. */

  QAPI_NET_LWM2M_CONFIG_BOOTSTRAP_INFO  = 3,  /**< Configure the bootstrap info with value.lwm2m_data filled in qapi_Net_LWM2M_Config_Data_t. */
  QAPI_NET_LWM2M_START                  = 4,  /**< Start LwM2M. */
  QAPI_NET_LWM2M_STOP                   = 5,  /**< Stop  LwM2M. */
  QAPI_NET_LWM2M_DEREGISTER_AND_STOP    = 6,  /**< Deregister all LwM2M DM server and then Stop LwM2M. */
  QAPI_NET_LWM2M_FACTORY_RESET          = 7,  /**< Factory Reset LwM2M. */
    
}qapi_Net_LWM2M_Config_Type_t;

/**
*   LWM2M security mode type. 
*/
typedef enum qapi_Net_LWM2M_Security_Mode_t
{
  QAPI_NET_LWM2M_SECURITY_MODE_PRE_SHARED_KEY  = 0,  /**< Preshared Key mode. */
  QAPI_NET_LWM2M_SECURITY_RAW_PUBLIC_KEY       = 1,  /**< Raw Public Key mode. */
  QAPI_NET_LWM2M_SECURITY_CERTIFICATE          = 2,  /**< Security Certificate mode. */
  QAPI_NET_LWM2M_SECURITY_NONE                 = 3,  /**< No security mode. */
}qapi_Net_LWM2M_Security_Mode_t;


/**
*   LWM2M extented config option. 
*/

typedef enum {
  QAPI_LWM2M_EXTENDED_CONFIG_NONE,                               /**< EXTENDED_CONFIG_NONE. */
}qapi_LWM2M_Extended_Config_Options_t;



/**
* @deprecated Structure is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Id_Info_v2_t instead.
*
*   Structure to indicate the object/instance/resource ID for which the 
*         application is interested in monitoring or getting the value.
*/
typedef struct qapi_Net_LWM2M_Id_Info_s
{
  struct qapi_Net_LWM2M_Id_Info_s *next;  /**< Pointer to the next ID information. */
  uint8_t id_set;       /**< ID category defined in qapi_lwm2m_id. */
  uint16_t object_ID;   /**< Object ID. */
  uint8_t instance_ID;  /**< Object instance ID. */
  uint8_t resource_ID;  /**< Resource ID. */
} qapi_Net_LWM2M_Id_Info_t;

/**
*   Structure to indicate the object/instance/resource ID for which the 
*         application is interested in monitoring or getting the value.
*         Version 2
*/
typedef struct qapi_Net_LWM2M_Id_Info_v2_s
{
  struct qapi_Net_LWM2M_Id_Info_v2_s *next;  /**< Pointer to the next ID information. */
  uint8_t id_set;       /**< ID category defined in qapi_lwm2m_id. */
  uint16_t object_ID;   /**< Object ID. */
  uint16_t instance_ID;  /**< Object instance ID. */
  uint16_t resource_ID;  /**< Resource ID. */
} qapi_Net_LWM2M_Id_Info_v2_t;

/**
* @deprecated Structure is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Object_Info_v2_t instead
*
*   Structure to indicate the object/instance/resource for which the 
*   application is interested in monitoring or getting the value.
*/
typedef struct qapi_Net_LWM2M_Object_Info_s
{
  uint8_t no_object_info;             /**< Number of object information blocks. */
  qapi_Net_LWM2M_Id_Info_t *id_info;  /**< Pointer to the ID information. */
} qapi_Net_LWM2M_Object_Info_t;

/**
*   Structure to indicate the object/instance/resource for which the 
*   application is interested in monitoring or getting the value.
*   Version 2.
*/
typedef struct qapi_Net_LWM2M_Object_Info_v2_s
{
  uint16_t no_object_info;             /**< Number of object information blocks. */
  qapi_Net_LWM2M_Id_Info_v2_t *id_info;  /**< Pointer to the ID information. */
} qapi_Net_LWM2M_Object_Info_v2_t;

/**
*   LWM2M resource information (in flat format) to encode/decode data payload.
*/
typedef struct qapi_Net_LWM2M_Flat_Data_s
{
  qapi_Net_LWM2M_Value_Type_t type;  /**< Value type.  */
  uint16_t  id;                      /**< Resource ID. */
  /** Union of value types. */
  union
  {
    bool       asBoolean;  /**< Value in boolean format. */
    int64_t    asInteger;  /**< Value as an integer. */
    double     asFloat;    /**< Value as a floating point. */
    objlink_t  asObjLink;  /**< Value as a object link. */
    struct
    {
      size_t    length;        /**< String length. */
      uint8_t  *buffer;        /**< Pointer to the string buffer. */
      uint8_t   block1_more;   /**< More blocks to be received. */
      uint32_t  block1_num;    /**< Block number. */                                             
      uint16_t  block1_size;   /**< Block size. */                         
      uint32_t  block1_offset; /**< Block offset. */
      uint32_t  size1;         /**< Size indication. */ 
    } asBuffer;                /**< Value as a string. */
    struct
    {
      size_t   count;    /**< Count of the children. */
      struct qapi_Net_LWM2M_Flat_Data_s  *array;  /**< Flat data array. */
    } asChildren;        /**< Value as children. */
  } value;
} qapi_Net_LWM2M_Flat_Data_t;

/**
*   Structure that indicates the resource information that is to be created.
*/
typedef struct qapi_Net_LWM2M_Resource_Info_s
{
  struct qapi_Net_LWM2M_Resource_Info_s *next;  /**< Pointer to the next resource information. */
  uint16_t resource_ID;                         /**< Resource ID. */
  qapi_Net_LWM2M_Value_Type_t type;             /**< Type of resource. */
  /** Union of resource values. */
  union
  {
    bool asBoolean;      /**< Value in Boolean format. */
    int64_t asInteger;   /**< Value as an integer. */
    double asFloat;      /**< Value as a floating point. */
    objlink_t asObjLink; /**< Value as a object link. */    
    struct
    {
      size_t length;          /**< String length. */
      uint8_t *buffer;        /**< Pointer to the string buffer. */
      uint8_t  block1_more;   /**< More blocks to be received. */
      uint32_t block1_num;    /**< Block number. */                                            
      uint16_t block1_size;   /**< Block size. */                        
      uint32_t block1_offset; /**< Block offset. */
      uint32_t size1;         /**< Size indication. */
    } asBuffer;  /**< Value as a string. */
    struct
    {
      size_t        count;  /**< Number of resources in the array. */
      qapi_Net_LWM2M_Flat_Data_t *array;  /**< Array of resources. */ 
    } asChildren;  /**< Value as a multi-resource instance. */
  } value;  
} qapi_Net_LWM2M_Resource_Info_t;

/**
* @deprecated Structure is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Instance_Info_v2_t instead
*
*   Structure to indicate the instance information that is to be created.
*/
typedef struct qapi_Net_LWM2M_Instance_Info_s
{
  struct qapi_Net_LWM2M_Instance_Info_s *next;  /**< Pointer to the next object instance. */
  uint8_t instance_ID;    /**< Instance ID. */
  uint8_t no_resources;   /**< Number of resources. */
  qapi_Net_LWM2M_Resource_Info_t * resource_info;  /**< Pointer to the resource information. */
} qapi_Net_LWM2M_Instance_Info_t;

/**
*   Structure to indicate the instance information that is to be created.
*         Version 2
*/
typedef struct qapi_Net_LWM2M_Instance_Info_v2_s
{
  struct qapi_Net_LWM2M_Instance_Info_v2_s *next;  /**< Pointer to the next object instance. */
  uint16_t instance_ID;    /**< Instance ID. */
  uint16_t no_resources;   /**< Number of resources. */
  qapi_Net_LWM2M_Resource_Info_t * resource_info;  /**< Pointer to the resource information. */
} qapi_Net_LWM2M_Instance_Info_v2_t;

/**
* @deprecated Structure is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Data_v2_t instead
*
*   Structure that is populated by the application and provided to an LWM2M client
*         when the application wants to create an instance of the LWM2M object to perform 
*         set and get operations. 
*/
typedef struct qapi_Net_LWM2M_Data_s
{
  struct qapi_Net_LWM2M_Data_s *next;  /**< Pointer to the next object data. */
  uint16_t object_ID;    /**< Object ID. */
  uint8_t no_instances;  /**< Number of instances. */
  qapi_Net_LWM2M_Instance_Info_t *instance_info;  /**< Pointer to the instance information. */
} qapi_Net_LWM2M_Data_t;

/**
*   Structure that is populated by the application and provided to an LWM2M client
*         when the application wants to create an instance of the LWM2M object to perform 
*         set and get operations.
*         Version 2 
*/
typedef struct qapi_Net_LWM2M_Data_v2_s
{
  struct qapi_Net_LWM2M_Data_v2_s *next;  /**< Pointer to the next object data. */
  uint16_t object_ID;    /**< Object ID. */
  uint16_t no_instances;  /**< Number of instances. */
  qapi_Net_LWM2M_Instance_Info_v2_t *instance_info;  /**< Pointer to the instance information. */
} qapi_Net_LWM2M_Data_v2_t;

/**
*   LWM2M object/URI-related information.
*/
typedef struct qapi_Net_LWM2M_Obj_Info_s
{
  qapi_Net_LWM2M_ID_t    obj_mask;         /**< Bitmap indicating valid object fields. */
  uint16_t               obj_id;           /**< Object ID. */
  uint16_t               obj_inst_id;      /**< Object instance ID. */
  uint16_t               res_id;           /**< Resource ID. */
  uint16_t               res_inst_id;      /**< Resource instance ID. */
} qapi_Net_LWM2M_Obj_Info_t;

/**
*   LWM2M write attribute information.
*/
typedef struct qapi_Net_LWM2M_Attributes_s
{
  qapi_Net_LWM2M_Obj_Info_t     obj_info;       /**< LWM2M object information associated with write attributes. */ 
  qapi_Net_LWM2M_Write_Attr_t   set_attr_mask;  /**< Bitmap indicating valid attribute fields to set. */
  qapi_Net_LWM2M_Write_Attr_t   clr_attr_mask;  /**< Bitmap indicating attribute fields to clear. */
  uint8_t                       dim;            /**< Dimension. */
  uint32_t                      minPeriod;      /**< Minimum period. */
  uint32_t                      maxPeriod;      /**< Maximum period. */
  double                        greaterThan;    /**< Greater than. */
  double                        lessThan;       /**< Less than. */
  uint8_t                       step_valid;     /**< Step validity. */
  double                        step;           /**< Step. */
  struct qapi_Net_LWM2M_Attributes_s *next;     /**< Pointer to the next attributes information. */
} qapi_Net_LWM2M_Attributes_t;

/**
*   LWM2M server request message data and internal LWM2M client state information.
*/
typedef struct qapi_Net_LWM2M_Server_Data_s
{
  qapi_Net_LWM2M_DL_Msg_t         msg_type;        /**< DL message type (requests, acknowledgements, or internal). */
  qapi_Net_LWM2M_Obj_Info_t       obj_info;        /**< Object information. */
  uint8_t                         msg_id_len;      /**< Message ID length.  */
  uint8_t                         msg_id[QAPI_MAX_LWM2M_MSG_ID_LENGTH];   
  /**< Message ID. \n
   * The message ID is transparent to the application, but is passed to the application for every message
   * received from the server. The expectation is that the application stores the message ID associated
   * with the message and passes it to the LWM2M client when a response or notification must be sent to
   * the server. After the transaction pertaining to the message is complete, the message ID can be
   * discarded from the application. */
  uint16_t                        notification_id;
  /**< Notification ID.\n
   * When a notification is sent using qapi_Net_LWM2M_Send_Message(), the notification ID associated
   * with the message is returned to the caller. It is the caller's responsibility to maintain the
   * notification ID for observation mapping. Later, when the network does a Cancel Observation for
   * a particular notification using RESET, it is indicated using the notification ID to the caller.
   * Using this notification ID, the caller can cancel the observation. If the cancel observation was not using
   * RESET, obj_info should have the information based on the observation that is to be cancelled. */  
  qapi_Net_LWM2M_Content_Type_t   content_type;    /**< Current encoded data payload content type. */
  uint32_t                        payload_len;     /**< Encoded data payload length. */
  uint8_t                        *payload;         /**< Encoded data payload. */
  qapi_Net_LWM2M_Attributes_t    *lwm2m_attr;      /**< Write attributes. */
  qapi_Net_LWM2M_Event_t          event;           /**< Internal events. */
  bool                            accept_is_valid; /**< Flag to check accept field is set or not. */
  qapi_Net_LWM2M_Content_Type_t   accept;          /**< Intended data payload content type. */
} qapi_Net_LWM2M_Server_Data_t;

/**
*   LWM2M application response message data and notification-related information. 
*/
typedef struct qapi_Net_LWM2M_App_Ex_Obj_Data_s
{
  qapi_Net_LWM2M_UL_Msg_t         msg_type;        /**< UL message type (response or notification). */
  qapi_Net_LWM2M_Obj_Info_t       obj_info;        /**< Object information. */
  qapi_Net_LWM2M_Response_Code_t  status_code;     /**< Application message status (applicable for responses only). */
  uint8_t                         conf_msg;        /**< Confirmable (ACK) or nonconfirmable application response/notifications. */  
  uint8_t                         msg_id_len;      /**< Message ID length. */ 
  uint8_t                         msg_id[QAPI_MAX_LWM2M_MSG_ID_LENGTH];
  /**< Message ID. \n
   * The message ID is transparent to the application, but is passed to the application for every message
   * received from the server. The expectation is that the application stores the message ID associated
   * with the message and passes it to the LWM2M client when a response or notification must be sent to
   * the server. After the transaction pertaining to the message is complete, the message ID can be
   * discarded from the application. */
  uint32_t                        observation_seq_num; /**< Observation sequence number. */ 
  uint16_t                        notification_id;
  /**< Notification ID. \n
   * When a notification is sent using qapi_Net_LWM2M_Send_Message(), the notification ID associated
   * with the message is returned to the caller. It is the caller's responsibility to maintain the
   * notification ID for observation mapping. Later, when the network does a Cancel Observation for
   * a particular notification using RESET, it is indicated using the notification ID to the caller.
   * Using this notification ID, the caller can cancel the observation. If the cancel observation was not using
   * RESET, obj_info should have the information based on the observation that is to be cancelled. */
  qapi_Net_LWM2M_Content_Type_t   content_type;    /**< Encoded data payload content type. */
  uint32_t                        payload_len;     /**< Encoded data payload length. */
  uint8_t                        *payload;         /**< Encoded data payload. */
} qapi_Net_LWM2M_App_Ex_Obj_Data_t;

/**
*   LWM2M config message data.
*/
typedef struct qapi_Net_LWM2M_Config_Data_s
{
  struct qapi_Net_LWM2M_Config_Data_s *next;       /**< Pointer to the next object data. */     
  qapi_Net_LWM2M_Config_Type_t        config_type; /**< Configuration type. */
  union
  {
    bool     asBoolean;	 /**< Present as a boolean value. */
    int64_t  asInteger;	 /**< Present as an integer value. */
    double   asFloat;	 /**< Present as a float value. */
    struct
    {
      size_t    length;	  /**< Length of the buffer. */
      uint8_t  *buffer;	  /**< Pointer to the buffer. */
    } asBuffer;			  /**< Present as a buffer. */
	qapi_Net_LWM2M_Data_v2_t* lwm2m_data; /**< Pointer to the lwm2w data, used to create instance of security/server/acl object. */
  }value;				  /**< Union of values. */
}qapi_Net_LWM2M_Config_Data_t;

/** @} */ /* end_addtogroup qapi_lwm2m_datatypes */

/** @addtogroup qapi_lwm2m_apis
@{ */

/**
*   Callback registered from the application, which is used by the LWM2M 
*         client to indicate the resource value change to the application.
*
* @param[in] handle  Handle received from qapi_Net_LWM2M_Register_App_Extended().
* @param[in] lwm2m_data  Pointer to the LWM2M data.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
*/
typedef qapi_Status_t (*qapi_Net_LWM2M_App_CB_t)
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Data_t *lwm2m_data
);

/**
*   Callback registered from the application, which is used by the LWM2M 
*         client to indicate the resource value change to the application. 
*         Version 2
*
* @param[in] handle  Handle received from qapi_Net_LWM2M_Register_App_Extended().
* @param[in] lwm2m_data  Pointer to the LWM2M data.
* @param[out] result  Result returned from application side
*
* @return Void.
*
*/
typedef void (*qapi_Net_LWM2M_App_CB_v2_t)
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Data_v2_t *lwm2m_data,
  qapi_Status_t            *result
);

/**
*  Callback registered from the application, which is used by the LWM2M client to indicate 
*         any extended object-specific messages from the server to the appropriate application. Each server 
*         message request is associated with a message ID and passed to the caller as part of the LWM2M server. 
*         The application must maintain the message ID to message mapping and use the message ID for 
*         any futher transactions that involve responses or notification events pertaining to the message.
*
* @param[in] handle  Handle received from qapi_Net_LWM2M_Register_App_Extended().
* @param[in] lwm2m_srv_data  Pointer to the LWM2M server data.
* @param[in] user_data  Pointer to the user data.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
*/
typedef qapi_Status_t (*qapi_Net_LWM2M_App_Extended_CB_t)
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Server_Data_t *lwm2m_srv_data,
  void *user_data
);


/**
* @deprecated Registers an application with an LWM2M client. The application gets a handle
*         on successful registration with the LWM2M client.
*
* @param[in,out] handle  Handle that is provided to the application on successful registration.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Register_App 
(
  qapi_Net_LWM2M_App_Handler_t *handle
);


/**
*   Registers an application with an LWM2M client along with a callback handle. The application
*         gets a handle on successful registration with the LWM2M client and must use this handle for
*         subsequent calls to the LWM2M client in the APIs.
*
*   Any messages/events to the application are forwarded through the registered application 
*   callback. Resources allocated for the messages or events in the callback are released internally
*   after the callback is returned. The application should not release the resources. 
*
* @param[in,out] handle  Handle that is provided to the application on successful registration.
* @param[in] user_data  Transparent user data payload (to be returned in the user callback).
* @param[in] user_cb_fn  User client callback handle to forward data to the application.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Register_App_Extended
(
  qapi_Net_LWM2M_App_Handler_t *handle, 
  void *user_data, 
  qapi_Net_LWM2M_App_Extended_CB_t user_cb_fn
);

/**
*   Deregisters an application. Any object instances associated with the handle are 
*         automatically cleaned up as a result of deregistration.
*
* @param[in] handle  Handle that was provided to the application on successful registration.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_DeRegister_App
(
  qapi_Net_LWM2M_App_Handler_t handle
);

/**
* @deprecated API is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Observe_v2 instead
*
*   Used by the application to indicate to the LWM2M client the object/instance/resource that 
*         the application is interested in observing. Only allowed for standard objects.
*
*   Any messages or events to the application are forwarded through the registered application 
*   callback. Resources allocated for the messages or events in the callback should be released by
*   the application before the callback returns. 
*
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] observe_cb_fn  Application callback to be invoked on a value change.
* @param[in] observe_info  Object/instance/resource information that the application is interested
*                          in monitoring on on the LWM2M client.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Observe 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_App_CB_t observe_cb_fn, 
  qapi_Net_LWM2M_Object_Info_t *observe_info
);

/**
*   Used by the application to indicate to the LWM2M client the object/instance/resource that 
*         the application is interested in observing. Only allowed for standard objects.
*
*   Any messages or events to the application are forwarded through the registered application 
*   callback. Resources allocated for the messages or events in the callback should be released by
*   the application before the callback returns. 
*
*         Version 2
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] observe_cb_fn  Application callback to be invoked on a value change.
* @param[in] observe_info  Object/instance/resource information that the application is interested
*                          in monitoring on on the LWM2M client.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Observe_v2 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_App_CB_v2_t observe_cb_fn, 
  qapi_Net_LWM2M_Object_Info_v2_t *observe_info
);

/**
* @deprecated API is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Cancel_Observe_v2 instead
*
*   Used by the application to cancel the observation.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] observe_info  Object/instance/resource information for which the application
*                          is to cancel the observation.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Cancel_Observe 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_Object_Info_t *observe_info
);

/**
*   Used by the application to cancel the observation.
*         Version 2
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] observe_info  Object/instance/resource information for which the application
*                          is to cancel the observation.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Cancel_Observe_v2 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_Object_Info_v2_t *observe_info
);

/**
* @deprecated API is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Create_Object_Instance_v2 instead
*
*   Creates standard/custom LWM2M object instances from the application. Only one object 
*         instance is allowed at a time. Applications are allowed to create instances of 
*         standard objects at any time and can pass the information associated with the instance. 
*         However, custom/extensible object instances can only be created by the application within 
*         the bootstrap window during the bootstrap phase. If the application missed the 
*         bootstrap window internally, rebootstrapping can be set to force the device to perform 
*         rebootstrapping on the next reboot, and the application is then allowed to create the 
*         new object instance. It is not required by the application to pass the information of the
*         custom object instance. 
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_data  LWM2M object instance and its resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Create_Object_Instance 
(
  qapi_Net_LWM2M_App_Handler_t handle,   
  qapi_Net_LWM2M_Data_t *lwm2m_data
);

/**
*   Creates standard/custom LWM2M object instances from the application. Only one object 
*         instance is allowed at a time. Applications are allowed to create instances of 
*         standard objects at any time and can pass the information associated with the instance. 
*         However, custom/extensible object instances can only be created by the application within 
*         the bootstrap window during the bootstrap phase. If the application missed the 
*         bootstrap window internally, rebootstrapping can be set to force the device to perform 
*         rebootstrapping on the next reboot, and the application is then allowed to create the 
*         new object instance. It is not required by the application to pass the information of the
*         custom object instance.
*         Version 2
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_data  LWM2M object instance and its resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Create_Object_Instance_v2 
(
  qapi_Net_LWM2M_App_Handler_t handle,   
  qapi_Net_LWM2M_Data_v2_t *lwm2m_data
);

/**
* @deprecated API is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Delete_Object_Instance_v2 instead
*
*   Deletes an LWM2M object instance from the application. Only one object instance deletion 
*   is allowed at a time.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] instance_info  LWM2M object instance and its resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Delete_Object_Instance 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_Object_Info_t *instance_info
);

/**
*   Deletes an LWM2M object instance from the application. Only one object instance deletion 
*   is allowed at a time.
*   Version 2
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] instance_info  LWM2M object instance and its resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Delete_Object_Instance_v2 
(
  qapi_Net_LWM2M_App_Handler_t handle,  
  qapi_Net_LWM2M_Object_Info_v2_t *instance_info
);

/**
* @deprecated API is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Get_v2 instead
*
*   Gets the value of the LWM2M object/instance/resource from the application. Only one query of 
*   an object instance is allowed at a time.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_info_req  Object/instance/resource information requested from the application.
* @param[out] lwm2m_data  Value of the LWM2M object/instance/resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Get
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Object_Info_t *lwm2m_info_req, 
  qapi_Net_LWM2M_Data_t **lwm2m_data
);

/**
*   Gets the value of the LWM2M object/instance/resource from the application. Only one query of 
*   an object instance is allowed at a time.
*   Version 2
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_info_req  Object/instance/resource information requested from the application.
* @param[out] lwm2m_data  Value of the LWM2M object/instance/resource information.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Get_v2
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Object_Info_v2_t *lwm2m_info_req, 
  qapi_Net_LWM2M_Data_v2_t **lwm2m_data
);

/**
* @deprecated API is deprecated in version 2.0
* @see        Use qapi_Net_LWM2M_Set_v2 instead
*
* Sets the value of LWM2M resources. Only one object instance setting is allowed at a time.
*
* Note that only the following resources are available to be set (per the OMA Specificaion):
*
* - Firmware update (by kernel applications only) \n
*   -- (3) State \n
*   -- (5) Update Result \n
*   -- (6) PkgName \n
*   -- (7) PkgVersion \n
*   -- (8) Firmware Update Protocol Support \n
*   -- (9) Firmware Update Delivery Method \n
* - Software management object \n
*   -- (7) Update State \n
*   -- (9) Update Result \n
*   -- (12) Activation State \n
* - Device capability \n
*   -- (0) Property \n
*   -- (1) Group \n
*   -- (2) Description \n
*   -- (3) Attached \n
*   -- (4) Enabled \n
* - Device object \n
*   -- (0) Manufacturer \n
*   -- (1) Model Number \n
*   -- (2) Serial Number (by kernel applications only) \n
*   -- (3) Firmware Version (by kernel applications only) \n
*   -- (18) Hardware Version (by kernel applications only) \n
*   -- (19) Software Version (by kernel applications only) \n
* - Cellular network connectivity object \n
*   -- (0) SMSC address \n
*   -- (1) Disable radio period \n
*   -- (3) Vendor specific extensions \n
*   -- (4) PSM timer \n
*   -- (5) Active timer \n
*   -- (9) eDRX parameters for NB S1 mode \n
*   -- (11) Activated profile names \n
* - APN connection object \n
*   -- (0) Profile name \n
*   -- (1) APN \n
*   -- (2) Auto select APN by device \n
*   -- (4) Authentication type \n
*   -- (5) User Name \n
*   -- (6) Secret \n
*   -- (7) Reconnect schedule \n
*   -- (22) Vendor specific extensions \n
*   -- (24) PDN type \n
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_data  Value of the LWM2M resource to be set.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Set 
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Data_t *lwm2m_data
);

/**
*   Sets the value of LWM2M resources. Only one object instance setting is allowed at a time.
*
* Note that only the following resources are available to be set (per the OMA Specificaion):
*
* - Firmware update (by kernel applications only) \n
*   -- (3) State \n
*   -- (5) Update Result \n
*   -- (6) PkgName \n
*   -- (7) PkgVersion \n
*   -- (8) Firmware Update Protocol Support \n
*   -- (9) Firmware Update Delivery Method \n
* - Software management object \n
*   -- (7) Update State \n
*   -- (9) Update Result \n
*   -- (12) Activation State \n
* - Device capability \n
*   -- (0) Property \n
*   -- (1) Group \n
*   -- (2) Description \n
*   -- (3) Attached \n
*   -- (4) Enabled \n
* - Device object \n
*   -- (0) Manufacturer \n
*   -- (1) Model Number \n
*   -- (2) Serial Number (by kernel applications only) \n
*   -- (3) Firmware Version (by kernel applications only) \n
*   -- (18) Hardware Version (by kernel applications only) \n
*   -- (19) Software Version (by kernel applications only) \n
* - Cellular network connectivity object \n
*   -- (0) SMSC address \n
*   -- (1) Disable radio period \n
*   -- (3) Vendor specific extensions \n
*   -- (4) PSM timer \n
*   -- (5) Active timer \n
*   -- (9) eDRX parameters for NB S1 mode \n
*   -- (11) Activated profile names \n
* - APN connection object \n
*   -- (0) Profile name \n
*   -- (1) APN \n
*   -- (2) Auto select APN by device \n
*   -- (4) Authentication type \n
*   -- (5) User Name \n
*   -- (6) Secret \n
*   -- (7) Reconnect schedule \n
*   -- (22) Vendor specific extensions \n
*   -- (24) PDN type \n
*       Version 2
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] lwm2m_data  Value of the LWM2M resource to be set.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Set_v2 
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  qapi_Net_LWM2M_Data_v2_t *lwm2m_data
);

/**
*   Sends application data, which can be responses or notification events, to the server. For 
*         notifications, a notification ID is returned by the LWM2M client, and it is the application's
*         responsiblity to store this notification ID. If there is an observation cancellation, the LWM2M
*         client will send this notification ID through the registered callback. Applications can 
*         encode the data payload using their own encode functions.  
*
* @param[in] handle  Handle received after successful application registration.
* @param[in,out] lwm2m_app_data  Value of the LWM2M extended/custom object information to be sent.
*                                The application is responsible for releasing any allocated resources.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Send_Message 
(
  qapi_Net_LWM2M_App_Handler_t handle,
  qapi_Net_LWM2M_App_Ex_Obj_Data_t *lwm2m_app_data
);


/**
* @deprecated Utility function to encode application response/notification data before
*         sending them to the server. If applications have their own encoding functions,
*         they are free to use those functions to encode the data payload.
*         
*         API Deprecated for DAM application
*
* @param[in] obj_info  Object/URI information.
* @param[in] in_dec_data  Input data that is to be encoded.
* @param[in] in_dec_data_size  Input data size (in buffers).
* @param[in] write_attr  Write attribute information.
* @param[in] enc_content_type  Encoding format of the data.
* @param[out] out_enc_data  Output data buffer in encoded format. Resources are allocated internally.
*                           The application is responsible for releasing any allocated resources.  
* @param[out] out_enc_data_len  Output encoded data buffer length.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Encode_App_Payload 
(
  qapi_Net_LWM2M_Obj_Info_t *obj_info,
  qapi_Net_LWM2M_Flat_Data_t *in_dec_data,
  size_t in_dec_data_size,
  qapi_Net_LWM2M_Attributes_t *write_attr,  
  qapi_Net_LWM2M_Content_Type_t enc_content_type,
  uint8_t **out_enc_data,
  uint32_t *out_enc_data_len
);


/**
*   Utility function to encode application response/notification data before sending them to 
*         the server. If applications have their own encoding functions, they are free to use those 
*         functions to encode the data payload.  
*
* @param[in] handle           Handle received after successful application registration.
* @param[in] obj_info         Object/URI information.
* @param[in] in_dec_data      Input data that is to be encoded.
* @param[in] in_dec_data_size Input data size (in buffers).
* @param[in] write_attr       Write attribute information.
* @param[in] enc_content_type Encoding format of the data.
* @param[out] out_enc_data    Output data buffer in encoded format. Resources are allocated internally.
*                             The application is responsible for releasing any allocated resources.  
* @param[out] out_enc_data_len  Output encoded data buffer length.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Encode_Data
(
  qapi_Net_LWM2M_App_Handler_t handle,
  qapi_Net_LWM2M_Obj_Info_t *obj_info,
  qapi_Net_LWM2M_Flat_Data_t *in_dec_data,
  size_t in_dec_data_size,
  qapi_Net_LWM2M_Attributes_t *write_attr,  
  qapi_Net_LWM2M_Content_Type_t enc_content_type,
  uint8_t **out_enc_data,
  uint32_t *out_enc_data_len
);


/**
*  @deprecated Utility function to decode the server request data received through the
*         registered application callback. If applications have their own decoding
*         functions, they are free to use those functions to decode the data payload.
*
*         API Deprecated for DAM application.
*
* @param[in] obj_info  Object/URI information.
* @param[in] in_enc_data  Input data that is to be decoded.
* @param[in] in_enc_data_len  Input data length.
* @param[in] dec_content_type  Decoding format of the input data.
* @param[out] out_dec_data  Output data buffer in decoded format. Resources are allocated internally.
*                           The application is responsible for releasing any allocated resources.  
* @param[out] out_dec_data_size  Output decoded data size (in buffers).
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Decode_App_Payload 
(
  qapi_Net_LWM2M_Obj_Info_t *obj_info,
  uint8_t *in_enc_data,
  uint32_t in_enc_data_len,
  qapi_Net_LWM2M_Content_Type_t dec_content_type,
  qapi_Net_LWM2M_Flat_Data_t **out_dec_data,
  size_t *out_dec_data_size
);


/**
*   Utility function to decode the server request data received through the registered application 
*         callback. If applications have their own decoding functions, they are free to use those functions 
*         to decode the data payload.
*
* @param[in] handle           Handle received after successful application registration.
* @param[in] obj_info         Object/URI information.
* @param[in] in_enc_data      Input data that is to be decoded.
* @param[in] in_enc_data_len  Input data length.
* @param[in] dec_content_type Decoding format of the input data.
* @param[out] out_dec_data    Output data buffer in decoded format. Resources are allocated internally.
*                             The application is responsible for releasing any allocated resources.  
* @param[out] out_dec_data_size  Output decoded data size (in buffers).
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Decode_Data
(
  qapi_Net_LWM2M_App_Handler_t handle,
  qapi_Net_LWM2M_Obj_Info_t *obj_info,
  uint8_t *in_enc_data,
  uint32_t in_enc_data_len,
  qapi_Net_LWM2M_Content_Type_t dec_content_type,
  qapi_Net_LWM2M_Flat_Data_t **out_dec_data,
  size_t *out_dec_data_size
);


/**
*   Wakes up the LWM2M client module to send notifications to the server.
*
* Wake-up and Sleep states of the LWM2M client are indicated to the application
* using the qapi_net_LWM2M_Server_Data_t.event registered callback. The application is
* responsible for tracking the states of the LWM2M client.
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] msg_id  Message ID information associated with the request.
* @param[in] msg_id_len  Message ID information length.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/

extern qapi_Status_t qapi_Net_LWM2M_Wakeup 
(
  qapi_Net_LWM2M_App_Handler_t handle,
  uint8_t *msg_id,
  uint8_t  msg_id_len
);


/**
*   Sends initialization configuration parameters to the LWM2M client module.
*
*
* @param[in] handle       Handle received after successful registration of the application. 
* @param[in] config_data  Configuration parameter associated with the request. 
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
* On failure, QAPI_ERR_NOT_SUPPORTED(-8)  is returned, LwM2M not in BOOTSTRAP_BYAPP mode, or unsupported config type
* On failure, QAPI_ERR_INVALID_STATE(-13) is returned, Client trigger start but Lwm2m is already started 
* On failure, QAPI_ERR_NO_ENTRY(-7)       is returned, Client trigger start but no bootstrap info configured
* On failure, QAPI_ERR_EXISTS(-12)        is returned, Client trigger config bootstrap-info but bootstrap-info was present in lwm2m already(were configured before)
* On failure, QAPI_ERR_INVALID_PARAM(-2)  is returned, bootstrap-info provided is invalid or mandatory item is not provided in bootstrap-info.
*/
extern qapi_Status_t qapi_Net_LWM2M_ConfigClient
(
  qapi_Net_LWM2M_App_Handler_t handle,
  qapi_Net_LWM2M_Config_Data_t* config_data
);

/**
*    Gets the value of the default Pmin and Pmax information for a specific server.
*               
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] server_id  Server ID information (use QAPI_LWM2M_SERVER_ID_INFO macro). 
* @param[out] p_min  Default "p_min" server attribute value. 
* @param[out] p_max  Default "p_max" server attribute value. 

*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK(0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Default_Attribute_Info 
(
  qapi_Net_LWM2M_App_Handler_t handle,
  uint16_t server_id,
  uint32_t *p_min,
  uint32_t *p_max
);

/**
*   Configures the server life time information in the LWM2M client from the application. 
*         If the device is connected to only a single server, it is optional to pass the 
*         URL information.  
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] url_info  URL information of the server.  
* @param[in] life_time  Server life time information to be configured.  
* 
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Set_ServerLifeTime 
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  uint8_t *url_info, 
  uint32_t life_time
);

/**
*   Retrieves the server life time information from the LWM2M client to the application. 
*         If the device is connected to only a single server, it is optional to pass the 
*         URL information.  
*
* @param[in] handle  Handle received after successful application registration.
* @param[in] url_info  URL information of the server.  
* @param[out] life_time  Server life time information that is configured.  
* 
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
extern qapi_Status_t qapi_Net_LWM2M_Get_ServerLifeTime 
(
  qapi_Net_LWM2M_App_Handler_t handle, 
  uint8_t *url_info, 
  uint32_t *life_time
);


/**
* @brief    This function which is used to set extended.
 *          configuration parameters. It is expected that the user will call this API
 *          before these parameters are being used in another API. 
*
* @param[in] handle  Handle received after successful application registration.
* @param   option  Option type to be set.
* @param   val     Values to be set.
* @param   len     Option length.

* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/

qapi_Status_t qapi_Net_LWM2M_Set_Extended_Config_Option (qapi_Net_LWM2M_App_Handler_t handle, qapi_LWM2M_Extended_Config_Options_t option,
                                                                                                       void * val , int32_t len);



typedef struct lwm2m_at_M2MSET_s
{
  qapi_Net_LWM2M_Data_v2_t * obj_data_ptr;
  qapi_Net_LWM2M_Obj_Info_t id_info; //Last inputed obj_info
  int last_value_tbc; //last inputed value to be continue
  int last_type; //last inputed value type
}lwm2m_at_M2MSET_t;

typedef struct lwm2m_at_M2MSETMSGDATA_s
{
  UINT16 req_id;
  qapi_Net_LWM2M_Obj_Info_t obj_info;
  qapi_Net_LWM2M_Attributes_t * lwm2m_attr; //Attribute list
  qapi_Net_LWM2M_Flat_Data_t * lwm2m_flat_data; //Flat Data root
  qapi_Net_LWM2M_Content_Type_t enc_content_type;
  int last_more_value_tbc; //last inputed input_value_tbc
  int last_input_type; //last inputed value type
}lwm2m_at_M2MSETMSGDATA_t;

typedef struct util_at_list_s
{
  struct util_at_list_s * next;
  UINT16 id;
  void * ptr;
}util_at_list_t;

typedef enum {
    LWM2M_CMD_NONE   = 0,
    LWM2M_CMD_UPDATE = 1,
    LWM2M_CMD_NOTIFY = 2,
    LWM2M_CMD_ADDOBJ = 3,
    LWM2M_CMD_CREATEOBJ,
    LWM2M_CMD_DELETEOBJ,
    LWM2M_CMD_GETATTRINFO,
    LWM2M_CMD_SETLIFETIME,
    LWM2M_CMD_GETLIFETIME,
    LWM2M_CMD_WAKEUP,
    LWM2M_CMD_EVENT,
    LWM2M_CMD_EVENT_READ,
    LWM2M_CMD_GET,
    LWM2M_CMD_SET,
    LWM2M_CMD_SUBSCRIBE,
    LWM2M_CMD_SETMSGDATA,
    LWM2M_CMD_SENDMSG,
    LWM2M_CMD_REQ,
    LWM2M_CMD_REQ_READ,
    LWM2M_AT_URC,
    LWM2M_CMD_FILE,
    LWM2M_CMD_INIT
} lwm2m_cmd_type_t;
#endif

