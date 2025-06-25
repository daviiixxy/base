/******************************************************************************

  @file    liblwm2m.h

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

******************************************************************************/

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
 *    Fabien Fleutot - Please refer to git log
 *    Simon Bernard - Please refer to git log
 *    Toby Jaffey - Please refer to git log
 *    Julien Vermillard - Please refer to git log
 *    Bosch Software Innovations GmbH - Please refer to git log
 *    Pascal Rieux - Please refer to git log
 *******************************************************************************/

/*
 Copyright (c) 2013, 2014 Intel Corporation

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
     * Neither the name of Intel Corporation nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 THE POSSIBILITY OF SUCH DAMAGE.

 David Navarro <david.navarro@intel.com>

*/

#ifndef _LWM2M_CLIENT_H_
#define _LWM2M_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif
#ifdef MOB_TX
#include "efs_tx.h"
#endif
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include "platform.h"
#include "log_utils.h"
#include "lwm2m_intf.h"
#include "iotapp_queue.h"
#include "qapi_coap.h"
//#include "qapi_dss.h"
#include "iotapp_ps_wrapper.h"
//#include "iotapp_qmi_internal.h"

#ifdef PSM_LWM2M
//#include "qapi_psm.h"
#endif

#define ESUCCESS    0
#define EFAILURE    -1
#define LWM2M_FALSE	false
#define LWM2M_TRUE 	true

/* start <PORT_TODO> */
//#define AF_NONIP 1 //defined in sockets.h
#define AF_INET_DUAL46	4
/* end <PORT_TODO> */

/* Supported standard objects */ 
bool lwm2m_is_standard_object(uint16_t obj_id);

#define LWM2M_IS_INVALIDE_PACKETS(rsp_pkt) ((rsp_pkt) && \
	                                       ((rsp_pkt->code > QAPI_COAP_DELETE && rsp_pkt->code < QAPI_CREATED_2_01) || \
	                                       (rsp_pkt->code > QAPI_CONTENT_2_05 && rsp_pkt->code < QAPI_CONTINUE_2_31) || \
	                                       (rsp_pkt->code > QAPI_CONTINUE_2_31 && rsp_pkt->code < QAPI_BAD_REQUEST_4_00) || \
	                                       (rsp_pkt->code > QAPI_NOT_ACCEPTABLE_4_06 && rsp_pkt->code < QAPI_REQ_ENTITY_INCOMPLETE_4_08) || \
	                                       (rsp_pkt->code > QAPI_REQ_ENTITY_INCOMPLETE_4_08 && rsp_pkt->code < QAPI_PRECONDITION_FAILED_4_12) || \
	                                       (rsp_pkt->code > QAPI_REQUEST_ENTITY_TOO_LARGE_4_13 && rsp_pkt->code < QAPI_UNSUPPORTED_MEDIA_TYPE_4_15) || \
	                                       (rsp_pkt->code > QAPI_UNSUPPORTED_MEDIA_TYPE_4_15 && rsp_pkt->code < QAPI_INTERNAL_SERVER_ERROR_5_00) || \
	                                       (rsp_pkt->code > QAPI_PROXYING_NOT_SUPPORTED_5_05) || \
                                           (rsp_pkt->code >= QAPI_COAP_GET  && rsp_pkt->code <= QAPI_COAP_DELETE	&& (rsp_pkt->type == QAPI_COAP_TYPE_ACK || rsp_pkt->type == QAPI_COAP_TYPE_RST)) || \
                                           ((rsp_pkt->code >= QAPI_CREATED_2_01 && rsp_pkt->code <= QAPI_PROXYING_NOT_SUPPORTED_5_05) && rsp_pkt->type == QAPI_COAP_TYPE_RST) || \
                                           (rsp_pkt->code == QAPI_COAP_EMPTY && rsp_pkt->type == QAPI_COAP_TYPE_NON)))  

#define LWM2M_IS_TRANSACTION_CB(cmd_id) ((cmd_id == LWM2M_BOOTSTRAP_CB) || \
                                           (cmd_id == LWM2M_REGISTRATION_CB) || \
                                           (cmd_id == LWM2M_DEREGISTRATION_CB) || \
                                           (cmd_id == LWM2M_EXT_APPLICATION_CB) || \
                                           (cmd_id == LWM2M_REGISTRATION_UPDATE_CB))

#if 0
#define LWM2M_PERSITENT_OBSERVATION_STORAGE   "/datatx/lwm2m/observation_pr"
#define SERVER_PERSISTENCE_FILE               "/datatx/lwm2m/server_obj_pr"
#define ACL_PERSISTENCE_FILE                  "/datatx/lwm2m/acl_obj_pr"
#define SECURITY_PERSISTENCE_FILE             "/datatx/lwm2m/security_obj_pr"
#define FIRMWARE_PERSISTENCE_FILE              "/datatx/lwm2m/firmware_obj_pr"
#define REGISTRATION_STATUS_PERSISTENCE_FILE  "/datatx/lwm2m/m2m_regstatus"
#define CONN_MON_PERSISTENCE_FILE             "/datatx/lwm2m/conn_mon_obj_pr"
#define CONN_STATS_PERSISTENCE_FILE         "/datatx/lwm2m/conn_stats_obj_pr"
#define DEVICE_PERSISTENCE_FILE             "/datatx/lwm2m/device_obj_pr"
#define LWM2M_LOCATION_OBJ_PERSISTENCE_PATH "/datatx/lwm2m/location_obj_delete_pr"
#define LWM2M_DEVICE_OBJ_PERSISTENCE_PATH "/datatx/lwm2m/device_obj_delete_pr"
#define LWM2M_CONN_MON_OBJ_PERSISTENCE_PATH "/datatx/lwm2m/conn_mon_obj_obj_delete_pr"
#define LWM2M_CONN_STAT_OBJ_PERSISTENCE_PATH "/datatx/lwm2m/conn_stat_obj_delete_pr"
#define LWM2M_FIRMWARE_OBJ_PERSISTENCE_PATH "/datatx/lwm2m/firmware_obj_delete_pr"
#define LWM2M_APN_CONN_PERSISTENCE_FILE      "/datatx/lwm2m/apn_conn_obj_pr"
#define LWM2M_DEVICE_CAP_MGNT_PERSISTENCE_FILE      "/datatx/lwm2m/device_cap_mgnt_obj_pr"
#define LWM2M_SOFTWARE_MGNT_PERSISTENCE_FILE      "/datatx/lwm2m/software_mgnt_obj_pr"
#define LWM2M_CELL_NW_CONN_PERSISTENCE_FILE      "/datatx/lwm2m/cell_nw_conn_obj_pr"
/* Application extensible object persistence file */ 
#define LWM2M_APP_OBJ_PERSISTENCE_PATH "/datatx/lwm2m/application_obj_pr" 
/* Application persist re-bootstrapping configuration */
#define LWM2M_APP_REBOOTSTRAP_PERSISTENCE_PATH "/datatx/lwm2m/application_rebootstrap_pr"
#define BOOTSTRAP_STATUS_PERSISTENCE_FILE     "/datatx/lwm2m/m2m_bststus"
#define SMS_RATE_LIMIT_FILE                   "/datatx/lwm2m/sms_rate"
/* ExtObj that is registered*/
#define LWM2M_REGISTERED_EXTOBJ_PERSISTENCE_FILE  "/datatx/lwm2m/registed_ext_obj_pr"
/* LwM2M version */ 
#define LWM2M_VERSION_PERSISTENCE_FILE  "/datatx/lwm2m/version_pr"
/* LwM2M active server list */
#define LWM2M_ACTIVE_SERVER_LIST        "/datatx/lwm2m/active_server_list"
/* LWM2M configurations(MSIDN) */
#define LWM2M_CONFIG_PERSISTENCE_FILE "/datatx/lwm2m/config_pr"
#else

#define LWM2M_PERSITENT_OBSERVATION_STORAGE   "observation_pr"
#define SERVER_PERSISTENCE_FILE               "server_obj_pr"
#define ACL_PERSISTENCE_FILE                  "acl_obj_pr"
#define SECURITY_PERSISTENCE_FILE             "security_obj_pr"
#define FIRMWARE_PERSISTENCE_FILE              "firmware_obj_pr"
#define REGISTRATION_STATUS_PERSISTENCE_FILE  "m2m_regstatus"
#define CONN_MON_PERSISTENCE_FILE             "conn_mon_obj_pr"
#define CONN_STATS_PERSISTENCE_FILE         "conn_stats_obj_pr"
#define DEVICE_PERSISTENCE_FILE             "device_obj_pr"
#define LWM2M_LOCATION_OBJ_PERSISTENCE_PATH "location_obj_delete_pr"
#define LWM2M_DEVICE_OBJ_PERSISTENCE_PATH "device_obj_delete_pr"
#define LWM2M_CONN_MON_OBJ_PERSISTENCE_PATH "conn_mon_obj_obj_delete_pr"
#define LWM2M_CONN_STAT_OBJ_PERSISTENCE_PATH "conn_stat_obj_delete_pr"
#define LWM2M_FIRMWARE_OBJ_PERSISTENCE_PATH "firmware_obj_delete_pr"
#define LWM2M_APN_CONN_PERSISTENCE_FILE      "apn_conn_obj_pr"
#define LWM2M_DEVICE_CAP_MGNT_PERSISTENCE_FILE      "device_cap_mgnt_obj_pr"
#define LWM2M_SOFTWARE_MGNT_PERSISTENCE_FILE      "software_mgnt_obj_pr"
#define LWM2M_CELL_NW_CONN_PERSISTENCE_FILE      "cell_nw_conn_obj_pr"
/* Application extensible object persistence file */ 
#define LWM2M_APP_OBJ_PERSISTENCE_PATH "application_obj_pr" 
/* Application persist re-bootstrapping configuration */
#define LWM2M_APP_REBOOTSTRAP_PERSISTENCE_PATH "application_rebootstrap_pr"
#define BOOTSTRAP_STATUS_PERSISTENCE_FILE     "m2m_bststus"
#define SMS_RATE_LIMIT_FILE                   "sms_rate"
/* ExtObj that is registered*/
#define LWM2M_REGISTERED_EXTOBJ_PERSISTENCE_FILE  "registed_ext_obj_pr"
/* LwM2M version */ 
#define LWM2M_VERSION_PERSISTENCE_FILE  "version_pr"
/* LwM2M active server list */
#define LWM2M_ACTIVE_SERVER_LIST        "active_server_list"
/* LWM2M configurations(MSIDN) */
#define LWM2M_CONFIG_PERSISTENCE_FILE "config_pr"

#endif
/* LwM2M Versions */
#define LWM2M_V_1_0  (1.0)
#define LWM2M_V_1_1  (1.1)
#define LWM2M_MAX_SUPPORTED_VERSIONS 2

#define BUFFER_PADDING_LENGTH 2

/* Supported LwM2M versions */
extern float supported_lwm2m_ver[LWM2M_MAX_SUPPORTED_VERSIONS];

#define INVALID_OBJECT_ID 65535

#define LWM2M_APN_CLASS0     0   /* Invalid APN class */
#define LWM2M_APN_CLASS2     2
#define LWM2M_APN_CLASS3     3
#define LWM2M_APN_CLASS6     6
#define LWM2M_APN_CLASS7     7

#define INVALID_RES_INST_ID 0xFF

#define MAX_STRING_LEN 64

#define ABS_DIFF(v1, v2)  ((v1 >= v2) ? (v1 - v2) : (v2 - v1))
#define EPSILON 0.00001
extern const char* nullError;
extern const char* mallocError;

/*
 * Platform abstraction functions to be implemented by the user
 */

#ifndef LWM2M_MEMORY_TRACE
/* Allocate a block of size bytes of memory, returning a pointer to the 
 * beginning of the block.
 */
void * lwm2m_malloc(size_t s);
/* Allocates c blocks of memory of s bytes. The memory is initialized with
 * zero bits.
 */
void * lwm2m_calloc(size_t c, size_t s);
/* Deallocate a block of memory previously allocated by lwm2m_malloc() or 
 * lwm2m_strdup() 
 */
void lwm2m_free(void * p);
/* Allocate a memory block, duplicate the string str in it and return a 
* pointer to this new block.
*/
char * lwm2m_strdup(const char * str);
#endif
// Compare at most the n first bytes of s1 and s2, return 0 if they match
int lwm2m_strncmp(const char * s1, const char * s2, size_t n);
/* This function must return the number of seconds elapsed since origin.
 * The origin (Epoch, system boot, etc...) does not matter as this
 * function is used only to determine the elapsed time since the last
 * call to it.
 * In case of error, this must return a negative value.
 * Per POSIX specifications, time_t is a signed integer.
 */
time_t lwm2m_gettime(void);

#ifdef LWM2M_WITH_LOGS
// Same usage as C89 printf()
void lwm2m_printf(const char * format, ...);
#endif

// communication layer
#ifdef LWM2M_CLIENT_MODE
/* Returns a session handle that MUST uniquely identify a peer.
 * secObjInstID: ID of the Securty Object instance to open a connection to
 * userData: parameter to lwm2m_init()
 */
int32_t  lwm2m_connect_server(void * serverP,  void * userData) ;  

/* Close a session created by lwm2m_connect_server()
 * sessionH: session handle identifying the peer (opaque to the core)
 * userData: parameter to lwm2m_init()
 */
void lwm2m_close_connection(void * sessionH, void * userData);
#endif

/* Send data to a peer
 * Returns COAP_NO_ERROR or a COAP_NNN error code
 * sessionH: session handle identifying the peer (opaque to the core)
 * buffer, length: data to send
 * userData: parameter to lwm2m_init()
 * Compare two session handles
 * Returns true if the two sessions identify the same peer. false otherwise.
 * userData: parameter to lwm2m_init()
 */

/*
 * Error code
 */

#define LWM2M_NO_ERROR                       (uint8_t)0x00
#define LWM2M_IGNORE                         (uint8_t)0x01

#define LWM2M_201_CREATED                    (uint8_t)0x41
#define LWM2M_202_DELETED                    (uint8_t)0x42
#define LWM2M_204_CHANGED                    (uint8_t)0x44
#define LWM2M_205_CONTENT                    (uint8_t)0x45
#define LWM2M_400_BAD_REQUEST                (uint8_t)0x80
#define LWM2M_401_UNAUTHORIZED               (uint8_t)0x81
#define LWM2M_402_BAD_OPTION                 (uint8_t)0x82
#define LWM2M_403_FORBIDDEN                  (uint8_t)0x83
#define LWM2M_404_NOT_FOUND                  (uint8_t)0x84
#define LWM2M_405_METHOD_NOT_ALLOWED         (uint8_t)0x85
#define LWM2M_406_NOT_ACCEPTABLE             (uint8_t)0x86
#define LWM2M_412_PRECONDITION_FAILED        (uint8_t)0x8C
#define LWM2M_415_UNSUPPORTED_CONTENT_FORMAT (uint8_t)0x8F
#define LWM2M_500_INTERNAL_SERVER_ERROR      (uint8_t)0xA0
#define LWM2M_501_NOT_IMPLEMENTED            (uint8_t)0xA1
#define LWM2M_503_SERVICE_UNAVAILABLE        (uint8_t)0xA3

/*
 * Standard Object IDs
 */
#define LWM2M_SECURITY_OBJECT_ID            0
#define LWM2M_SERVER_OBJECT_ID              1
#define LWM2M_ACL_OBJECT_ID                 2
#define LWM2M_DEVICE_OBJECT_ID              3
#define LWM2M_CONN_MONITOR_OBJECT_ID        4
#define LWM2M_FIRMWARE_UPDATE_OBJECT_ID     5
#define LWM2M_LOCATION_OBJECT_ID            6
#define LWM2M_CONN_STATS_OBJECT_ID          7
#define LWM2M_SOFTWARE_MGNT_OBJECT_ID       9
#define LWM2M_CELL_NW_CONN_OBJECT_ID        10
#define LWM2M_APN_CONN_PROFILE_OBJECT_ID    11
#define LWM2M_DEVICE_CAP_OBJECT_ID          15
#define LWM2M_STANDARD_OBJECT_ID_MAX        LWM2M_DEVICE_CAP_OBJECT_ID
#define LWM2M_HOST_DEVICE_OBJECT_ID	        10255	//Added for host device object

/*
 * Ressource IDs for the LWM2M Security Object
 */

#define LWM2M_SECURITY_URI_ID                 0
#define LWM2M_SECURITY_BOOTSTRAP_ID           1
#define LWM2M_SECURITY_SECURITY_ID            2
#define LWM2M_SECURITY_PUBLIC_KEY_ID          3
#define LWM2M_SECURITY_SERVER_PUBLIC_KEY_ID   4
#define LWM2M_SECURITY_SECRET_KEY_ID          5
#define LWM2M_SECURITY_SMS_SECURITY_ID        6
#define LWM2M_SECURITY_SMS_KEY_PARAM_ID       7
#define LWM2M_SECURITY_SMS_SECRET_KEY_ID      8
#define LWM2M_SECURITY_SMS_SERVER_NUMBER_ID   9
#define LWM2M_SECURITY_SHORT_SERVER_ID        10
#define LWM2M_SECURITY_HOLD_OFF_ID            11
#define LWM2M_SECURITY_RESOURCE_30000         30000

/*
 * Ressource IDs for the LWM2M Server Object
 */
#define LWM2M_SERVER_SHORT_ID_ID                 0
#define LWM2M_SERVER_LIFETIME_ID                 1
#define LWM2M_SERVER_MIN_PERIOD_ID               2
#define LWM2M_SERVER_MAX_PERIOD_ID               3
#define LWM2M_SERVER_DISABLE_ID                  4
#define LWM2M_SERVER_TIMEOUT_ID                  5
#define LWM2M_SERVER_STORING_ID                  6
#define LWM2M_SERVER_BINDING_ID                  7
#define LWM2M_SERVER_UPDATE_ID                   8
#define LWM2M_SERVER_APN_LINK_ID                10
#define LWM2M_SERVER_REG_PRI_ORD_ID             13
#define LWM2M_SERVER_INITIAL_DELAY_TIMER_ID     14
#define LWM2M_SERVER_REG_FAILURE_BLOCK_ID       15
#define LWM2M_SERVER_BS_ON_REG_FAILURE_ID       16
#define LWM2M_SERVER_COMM_RETRY_COUNT_ID        17
#define LWM2M_SERVER_COMM_RETRY_TIMER_ID        18
#define LWM2M_SERVER_COMM_SEQ_DELAY_TIMER_ID    19
#define LWM2M_SERVER_COMM_SEQ_RETRY_COUNT_ID    20
#define LWM2M_SERVER_TRIGGER_ID                 21
#define LWM2M_SERVER_PREFERRED_TRANSPORT_ID     22
#define LWM2M_SERVER_RESOURCE_30000           30000


#define LWM2M_UPDATE_LIFETIME         0x0001
#define LWM2M_UPDATE_BINDING          0x0002
/* Skip the server disable (0x0004) and update ID (0x0008) - they are defined as part of the server resources  */
#define LWM2M_UPDATE_WITH_OBJECTS     0x0010
#define LWM2M_UPDATE_PROFILE_CHANGE   0x0020


/*
 * Ressource IDs for the LWM2M Device Object
 */
#define RES_O_MANUFACTURER          0
#define RES_O_MODEL_NUMBER          1
#define RES_O_SERIAL_NUMBER         2
#define RES_O_FIRMWARE_VERSION      3
#define RES_M_REBOOT                4
#define RES_O_FACTORY_RESET         5
#define RES_O_AVL_POWER_SOURCES     6
#define RES_O_POWER_SOURCE_VOLTAGE  7
#define RES_O_POWER_SOURCE_CURRENT  8
#define RES_O_BATTERY_LEVEL         9
#define RES_O_MEMORY_FREE           10
#define RES_M_ERROR_CODE            11
#define RES_O_RESET_ERROR_CODE      12
#define RES_O_CURRENT_TIME          13
#define RES_O_UTC_OFFSET            14
#define RES_O_TIMEZONE              15
#define RES_M_BINDING_MODES         16
// since TS 20141126-C:
#define RES_O_DEVICE_TYPE           17
#define RES_O_HARDWARE_VERSION      18
#define RES_O_SOFTWARE_VERSION      19
#define RES_O_BATTERY_STATUS        20
#define RES_O_MEMORY_TOTAL          21
#define RES_O_EXT_DEVICE_INFO       22


#define AVL_POWER_SOURCES           2
#define BATTERY_STATUS_NORMAL       0
#define BATTERY_STATUS_LOW          4
#define BATTERY_STATUS_NOT_PRESENT  5


#ifdef LWM2M_SERVER_OBJECT
#define LWM2M_SERVER_SET_UPDATE_ID(flag)               (flag = (flag | LWM2M_SERVER_UPDATE_ID))
#define LWM2M_SERVER_SET_UPDATE_LIFETIME(flag)         (flag = (flag | LWM2M_UPDATE_LIFETIME))
#define LWM2M_SERVER_SET_UPDATE_BINDING(flag)          (flag = (flag | LWM2M_UPDATE_BINDING))
#define LWM2M_SERVER_SET_DISABLE_ID(flag)              (flag = (flag | LWM2M_SERVER_DISABLE_ID))
#define LWM2M_SERVER_SET_UPDATE_WITH_OBJECTS(flag)     (flag = (flag | LWM2M_UPDATE_WITH_OBJECTS))
#define LWM2M_SERVER_SET_UPDATE_PROFILE_CHANGE(flag)   (flag = (flag | LWM2M_UPDATE_PROFILE_CHANGE))

#define LWM2M_SERVER_IS_UPDATE_SET(flag)                 ((flag & LWM2M_SERVER_UPDATE_ID) != 0) 
#define LWM2M_SERVER_IS_UPDATE_SET_LIFETIME(flag)        ((flag & LWM2M_UPDATE_LIFETIME) != 0) 
#define LWM2M_SERVER_IS_UPDATE_SET_BINDING(flag)         ((flag & LWM2M_UPDATE_BINDING) != 0) 
#define LWM2M_SERVER_IS_DISABLE_SET(flag)                ((flag & LWM2M_SERVER_DISABLE_ID) != 0)
#define LWM2M_SERVER_IS_UPDATE_SET_OBJECTS(flag)         ((flag & LWM2M_UPDATE_WITH_OBJECTS) != 0)
#define LWM2M_SERVER_IS_UPDATE_PROFILE_CHANGE_SET(flag)  ((flag & LWM2M_UPDATE_PROFILE_CHANGE) != 0)

#define LWM2M_SERVER_RESET_UPDATE_ID(flag)               (flag = (flag ^ LWM2M_SERVER_UPDATE_ID))
#define LWM2M_SERVER_RESET_UPDATE_LIFETIME(flag)         (flag = (flag ^ LWM2M_UPDATE_LIFETIME))
#define LWM2M_SERVER_RESET_UPDATE_BINDING(flag)          (flag = (flag ^ LWM2M_UPDATE_BINDING))
#define LWM2M_SERVER_RESET_SERVER_ID(flag)               (flag = (flag ^ LWM2M_SERVER_DISABLE_ID))
#define LWM2M_SERVER_RESET_UPDATE_SET_OBJECTS(flag)      (flag = (flag ^ LWM2M_UPDATE_WITH_OBJECTS))
#define LWM2M_SERVER_RESET_UPDATE_PROFILE_CHANGE(flag)   (flag = (flag ^ LWM2M_UPDATE_PROFILE_CHANGE))


#define LWM2M_SERVER_DEFAULT_DISABLE_TIMEOUT 86400
#endif

#define LWM2M_SECURITY_MODE_PRE_SHARED_KEY  0
#define LWM2M_SECURITY_MODE_RAW_PUBLIC_KEY  1
#define LWM2M_SECURITY_MODE_CERTIFICATE     2
#define LWM2M_SECURITY_MODE_NONE            3

/*
 * Enum carrier type indicates the type of the carrier to decide the behavior of the client 
 *
 */
typedef enum
{
  LWM2M_CARRIER_OPEN_MARKET = 0,
  LWM2M_CARRIER_VZW = 1,
  LWM2M_CARRIER_END = 2  
} lwm2m_carrier_type_e;

/*
 * Enum Endpoint name indicates the type that needs to be populated for ep= param in registration
 *
 */
typedef enum
{
  LWM2M_INVALID_URN = 0,	
  LWM2M_UUID_URN = 1,
  LWM2M_OPS_URN = 2,
  LWM2M_OS_URN = 3,
  LWM2M_IMEI_URN = 4,
  LWM2M_ESN_URN = 5,
  LWM2M_MEID_URN = 6,
  LWM2M_IMEI_MSISDN_URN = 7,
  LWM2M_IMEI_IMSI_URN = 8,
  LWM2M_IMEI_IMSI = 9,
  LWM2M_URN_END = 10,  
} lwm2m_ep_type_e;

typedef enum
{
  LWM2M_STARTUP_BOOTSTRAP_PRELOADED = 0,
  LWM2M_STARTUP_BOOTSTRAP_BYAPP     = 1,  	
  LWM2M_STARTUP_END = 2,  
}lwm2m_startup_mode_type_e;

/**
 * Firware object - State 
 */
 
enum lwm2m_firmware_state {
  LWM2M_FIRWARE_STATE_IDLE = 0,
  LWM2M_FIRWARE_STATE_DOWNLOADING,
  LWM2M_FIRWARE_STATE_DOWNLOADED,
  LWM2M_FIRWARE_STATE_UPDATING,
};

/**
 * Firware object - Update result
 */
 
enum lwm2m_firmware_uptate_result {
  LWM2M_FIRWARE_UPDATE_DEFAULT ,
  LWM2M_FIRWARE_UPDATE_SUCCESSFUL,
  LWM2M_FIRWARE_UPDATE_NOT_ENOUGH_STORAGE,
  LWM2M_FIRWARE_UPDATE_OUT_OF_MEMORY,
  LWM2M_FIRWARE_UPDATE_CONNECTION_LOST,
  LWM2M_FIRWARE_UPDATE_CRC_FAILED,
  LWM2M_FIRWARE_UPDATE_UNSUPPORTED_TYPE,
  LWM2M_FIRWARE_UPDATE_INVALID_URI,
  LWM2M_FIRMWARE_UPDATE_FAILED,
};


/*
 *  Misc define 
 */
#define TOKEN_LEN	8	//! size for token stored in watcher structure

/*
 *  Root CA Support through configuration file for LWM2M Servers 
 */

typedef enum
{
  /* No RootCA support for all LWM2M Server including BS Server. DI Cert
     authenticates all BS & LWM2M Servers */
  LWM2M_ROOTCA_NO_SUPPORT = 0,
  /* RootCA support only for BS Server. DI Cert authenticates all LWM2M Servers */
  LWM2M_ROOTCA_SUPPORT_BS_SERVERS = 1,
  /* RootCA support only to LWM2M Servers. DI Cert authenticates all BS LWM2M Servers */
  LWM2M_ROOTCA_SUPPORT_LWM2M_SERVERS = 2,
  /* RootCA Supports to all LWM2M Servers */  	
  LWM2M_ROOTCA_SUPPORT_BS_LWM2M_SERVERS = 3,  	
}lwm2m_rootca_support_mode_type_e;

/*
 * Utility functions for sorted linked list
 */

typedef struct _lwm2m_list_t
{
  struct _lwm2m_list_t *next;
  uint16_t    id;
} lwm2m_list_t;

// defined in list.c
// Add 'node' to the list 'head' and return the new list
lwm2m_list_t * lwm2m_list_add(lwm2m_list_t * head, lwm2m_list_t * node);
// Return the node with ID 'id' from the list 'head' or NULL if not found
lwm2m_list_t * lwm2m_list_find(lwm2m_list_t * head, uint16_t id);
// Remove the node with ID 'id' from the list 'head' and return the new list
lwm2m_list_t * lwm2m_list_remove(lwm2m_list_t * head, uint16_t id, lwm2m_list_t ** nodeP);
// Return the lowest unused ID in the list 'head'
uint16_t lwm2m_list_newId(lwm2m_list_t * head);
// Free a list. Do not use if nodes contain allocated pointers as it calls lwm2m_free on nodes only.
// If the nodes of the list need to do more than just "free()" their instances, don't use lwm2m_list_free().
void lwm2m_list_free(lwm2m_list_t * head);
// Count the node number of the list
uint16_t lwm2m_list_count(lwm2m_list_t * head);

#define LWM2M_LIST_ADD(H,N) lwm2m_list_add((lwm2m_list_t *)H, (lwm2m_list_t *)N);
#define LWM2M_LIST_RM(H,I,N) lwm2m_list_remove((lwm2m_list_t *)H, I, (lwm2m_list_t **)N);
#define LWM2M_LIST_FIND(H,I) lwm2m_list_find((lwm2m_list_t *)H, I)
#define LWM2M_LIST_FREE(H) lwm2m_list_free((lwm2m_list_t *)H)
#define LWM2M_LIST_COUNT(H) lwm2m_list_count((lwm2m_list_t *)H)

/*
 * URI
 *
 * objectId is always set
 * instanceId or resourceId are set according to the flag bit-field
 *
 */

#define LWM2M_MAX_ID   ((uint16_t)0xFFFF)

#define LWM2M_URI_FLAG_OBJECT_ID         (uint8_t)0x01
#define LWM2M_URI_FLAG_INSTANCE_ID       (uint8_t)0x02
#define LWM2M_URI_FLAG_RESOURCE_ID       (uint8_t)0x04
#define LWM2M_URI_FLAG_RESOURCE_INST_ID  (uint8_t)0x08

#define LWM2M_URI_IS_SET_OBJECT(uri) (((uri)->flag & LWM2M_URI_FLAG_OBJECT_ID) != 0)
#define LWM2M_URI_IS_SET_INSTANCE(uri) (((uri)->flag & LWM2M_URI_FLAG_INSTANCE_ID) != 0)
#define LWM2M_URI_IS_SET_RESOURCE(uri) (((uri)->flag & LWM2M_URI_FLAG_RESOURCE_ID) != 0)
#define LWM2M_URI_IS_SET_RESOURCE_INST(uri) (((uri)->flag & LWM2M_URI_FLAG_RESOURCE_INST_ID) != 0)


typedef struct lwm2m_uri_s
{
  uint32_t flag;           // indicates which segments are set
  uint16_t objectId;
  uint16_t instanceId;
  uint16_t resourceId;
  uint16_t resourceInstId;
} lwm2m_uri_t;

typedef struct lwm2m_sms_msg_s
{
  lwm2m_uri_t *uri;
  void *payload;
  uint32_t payload_len;
} lwm2m_sms_msg_t; 


#define LWM2M_STRING_ID_MAX_LEN 6

// Parse an URI in LWM2M format and fill the lwm2m_uri_t.
// Return the number of characters read from buffer or 0 in case of error.
// Valid URIs: /1, /1/, /1/2, /1/2/, /1/2/3
// Invalid URIs: /, //, //2, /1//, /1//3, /1/2/3/, /1/2/3/4
int lwm2m_stringToUri(const char * buffer, size_t buffer_len, lwm2m_uri_t * uriP);

/*
 * The lwm2m_data_t is used to store LWM2M resource values in a hierarchical way.
 * Depending on the type the value is different:
 * - LWM2M_TYPE_OBJECT, LWM2M_TYPE_OBJECT_INSTANCE, LWM2M_TYPE_MULTIPLE_RESOURCE: value.asChildren
 * - LWM2M_TYPE_STRING, LWM2M_TYPE_OPAQUE: value.asBuffer
 * - LWM2M_TYPE_INTEGER, LWM2M_TYPE_TIME: value.asInteger
 * - LWM2M_TYPE_FLOAT: value.asFloat
 * - LWM2M_TYPE_BOOLEAN: value.asBoolean
 *
 * LWM2M_TYPE_STRING is also used when the data is in text format.
 */

typedef qapi_Net_LWM2M_Value_Type_t lwm2m_data_type_t;
typedef qapi_Net_LWM2M_Flat_Data_t lwm2m_data_t;

#define LWM2M_TYPE_UNDEFINED            QAPI_NET_LWM2M_TYPE_UNDEFINED
#define LWM2M_TYPE_OBJECT               QAPI_NET_LWM2M_TYPE_OBJECT   
#define LWM2M_TYPE_OBJECT_INSTANCE      QAPI_NET_LWM2M_TYPE_OBJECT_INSTANCE
#define LWM2M_TYPE_MULTIPLE_RESOURCE    QAPI_NET_LWM2M_TYPE_MULTIPLE_RESOURCE
#define LWM2M_TYPE_STRING               QAPI_NET_LWM2M_TYPE_STRING_E         
#define LWM2M_TYPE_OPAQUE               QAPI_NET_LWM2M_TYPE_OPAQUE_E          
#define LWM2M_TYPE_INTEGER              QAPI_NET_LWM2M_TYPE_INTEGER_E        
#define LWM2M_TYPE_FLOAT                QAPI_NET_LWM2M_TYPE_FLOAT_E           
#define LWM2M_TYPE_BOOLEAN              QAPI_NET_LWM2M_TYPE_BOOLEAN_E        
#define LWM2M_TYPE_OBJECT_LINK          QAPI_NET_LWM2M_TYPE_OBJECT_LINK      

typedef enum
{
  LWM2M_CONTENT_TEXT      = 0,        // Also used as undefined
  LWM2M_CONTENT_LINK      = 40,
  LWM2M_CONTENT_OPAQUE    = 42,
  LWM2M_CONTENT_TLV       = 11542 ,    // Temporary value
  LWM2M_CONTENT_JSON      = 11543,     // Temporary value
  LWM2M_CONTENT_UNSUPPORTED      = 65534
} lwm2m_media_type_t;

typedef struct pers_resource_instance_int_list_s
{
  bool                    isValid;
  uint16_t                resInstId;  
  uint16_t                InstValue;
} pers_resource_instance_int_list_t;

typedef struct resource_instance_int_list_s
{
  struct resource_instance_int_list_s*   next; 
  uint16_t                resInstId;  
  uint16_t                InstValue;
} resource_instance_int_list_t;

typedef struct resource_instance_string_list_s
{
  struct resource_instance_string_list_s*   next; 
  uint16_t                resInstId;  
  char                    InstValue[MAX_STRING_LEN];
} resource_instance_string_list_t;

typedef struct resource_instance_time_list_s
{
  struct resource_instance_time_list_s*   next; 
  uint16_t                resInstId;  
  time_t                  InstValue;
} resource_instance_time_list_t;

/** Event message type. */
typedef struct  {
	qapi_Coap_Event_t lwm2m_event;
	void * event_info;
}lwm2m_event_msg;

lwm2m_data_t * lwm2m_data_new(int size);
int lwm2m_data_parse(lwm2m_uri_t * uriP, uint8_t * buffer, size_t bufferLen, lwm2m_media_type_t format, lwm2m_data_t ** dataP);
size_t lwm2m_data_serialize(lwm2m_uri_t * uriP, int size, lwm2m_data_t * dataP, lwm2m_media_type_t * formatP, uint8_t ** bufferP);
void lwm2m_data_free(int size, lwm2m_data_t * dataP);
int lwm2m_data_decode_objLink(const lwm2m_data_t * dataP, objlink_t * valueP);
void lwm2m_data_encode_string(const char * string, lwm2m_data_t * dataP);
void lwm2m_data_encode_nstring(const char * string, size_t length, lwm2m_data_t * dataP);
void lwm2m_data_encode_opaque(uint8_t * buffer, size_t length, lwm2m_data_t * dataP);
void lwm2m_data_encode_int(int64_t value, lwm2m_data_t * dataP);
int lwm2m_data_decode_int(const lwm2m_data_t * dataP, int64_t * valueP);
void lwm2m_data_encode_float(double value, lwm2m_data_t * dataP);
int lwm2m_data_decode_float(const lwm2m_data_t * dataP, double * valueP);
void lwm2m_data_encode_bool(bool value, lwm2m_data_t * dataP);
int lwm2m_data_decode_bool(const lwm2m_data_t * dataP, bool * valueP);
void lwm2m_data_encode_objLink(objlink_t value, lwm2m_data_t * dataP);
void lwm2m_data_encode_instances(lwm2m_data_t * subDataP, size_t count, lwm2m_data_t * dataP);
void lwm2m_data_include(lwm2m_data_t * subDataP, size_t count, lwm2m_data_t * dataP);
extern int32_t lwm2m_load_application_rebootstrap_info (uint32_t *rebootstrap_req);
extern uint8_t get_persisted_lwm2m_server_version(uint16_t short_id, float *version);
extern uint8_t persist_lwm2m_server_version(uint16_t short_id, float version);

uint8_t prv_mandatory_check(int numData, lwm2m_data_t * dataArray, uint16_t *mandatory_resource, uint8_t size);


/*
 * Utility function to parse TLV buffers directly
 *
 * Returned value: number of bytes parsed
 * buffer: buffer to parse
 * buffer_len: length in bytes of buffer
 * oType: (OUT) type of the parsed TLV record. can be:
 *          - LWM2M_TYPE_OBJECT
 *          - LWM2M_TYPE_OBJECT_INSTANCE
 *          - LWM2M_TYPE_MULTIPLE_RESOURCE
 *          - LWM2M_TYPE_OPAQUE
 * oID: (OUT) ID of the parsed TLV record
 * oDataIndex: (OUT) index of the data of the parsed TLV record in the buffer
 * oDataLen: (OUT) length of the data of the parsed TLV record
 */

#define LWM2M_TLV_HEADER_MAX_LENGTH 6

int lwm2m_decode_TLV(const uint8_t * buffer, size_t buffer_len, 
                     lwm2m_data_type_t * oType, uint16_t * oID, size_t * oDataIndex, 
                     size_t * oDataLen);




/*
 * LWM2M Servers
 *
 * Since LWM2M Server Object instances are not accessible to LWM2M servers,
 * there is no need to store them as lwm2m_objects_t
 */

typedef enum
{
  STATE_DEREGISTERED = 0,   // not registered or boostrap not started
  STATE_REG_PENDING,        // registration pending
  STATE_REGISTERED,         // successfully registered
  STATE_REG_FAILED,         // last registration failed
  STATE_REG_UPDATE_PENDING, // registration update pending
  STATE_DEREG_PENDING,      // deregistration pending
  STATE_BS_HOLD_OFF,        // bootstrap hold off time
  STATE_BS_INITIATED,       // bootstrap request sent
  STATE_BS_PENDING,         // boostrap on going
  STATE_BS_FINISHED,        // bootstrap done
  STATE_BS_FAILED,          // bootstrap failed
  STATE_REG_RETRYING,       // Registration retrying on failure
  STATE_BS_CONN_RETRYING,      // bootstrap Connection retrying on failure
  STATE_BS_REG_RETRYING,      // bootstrap Registration retrying on failure
} lwm2m_status_t;

typedef enum
{
  /* UDP binding is always assumed to be present - mandatory per specification */
  /* Bindings and modes allowed in LwM2Mv1.0 and LwM2Mv1.1 */ 
  BINDING_UNKNOWN = 0x0000,
  BINDING_U       = 0x0001,   // UDP
  BINDING_S       = 0x0002,   // SMS 
  BINDING_Q       = 0x0004,   // Queue mode
  BINDING_N       = 0x0008,   // Non-IP 
  BINDING_T       = 0x0010,   // TCP 
} lwm2m_binding_t;

/**
 * @brief LWM2M application object information 
 */
typedef struct lwm2m_app_obj_info_s
{
  struct lwm2m_app_obj_info_s *next;       /* Observe information list */
  uint16_t object_ID;                      /* Object ID */
  lwm2m_list_t *instance_list;             /* Instance list associated with the object ID */
} lwm2m_app_obj_info_t;


typedef struct _lwm2m_server_
{
  struct _lwm2m_server_ * next;   // matches lwm2m_list_t::next
  uint16_t          shortID;      // servers short ID, may be 0 for bootstrap server
  uint16_t          pri_order;    // LwM2M server priority (0 - 65534 for ordered, 65535 for unordered server / undefined priority)
  uint16_t          secObjInstID; // matches lwm2m_list_t::id  
  float             version;      // LwM2M server version 
  time_t            lifetime;     // lifetime of the registration in sec or 0 if default value (86400 sec), also used as hold off time for bootstrap servers
  time_t            registration; // date of the last registration in sec or end of client hold off time for bootstrap servers
  lwm2m_binding_t   binding;      // client connection mode with this server
  lwm2m_binding_t   pref_transport;
  objlink_t         apn_link;  
  int               sessionH;
  bool              trigger;   
  struct sockaddr   local_ip;
  lwm2m_status_t    status;
  char *            location;
  bool              dirty;
#ifdef LWM2M_SERVER_OBJECT
  uint8_t           update_disable_check; // used to verify the whether update required, disable required or not
  time_t            disable_timeOut;// disable timeout of a server
  time_t            disabled;
  bool              storing;
#endif
  time_t            prevAttemptTime;   
  time_t            retryTimeout;  
  /* This timer is used to unblock signal wait when reg 
     operations like disable or registration rety has to 
     be triggered. */
  timer_type        regOpTimer;
  bool              timer_init;
  void *	           coapHandle;
  uint32_t          defaultMinPeriod;	// used to set Min Period of observation
  uint32_t          defaultMaxPeriod;	//// used to set Max Period of observation
  bool              is_update_for_wakeup;
  bool              isBootstrapped ;
  bool              isBSServerAccountUpdated;
  uint16_t          isRgistered ; 
  bool              isRegupdate_for_sms;
  bool              bs_if_reg_fails;  
  bool              pending_reg_update;
  bool              trigger_registration;
  bool              conn_failed_with_v6;
  int               ip_family_configured;
  time_t            next_cycle_for_registration;
  bool              reg_update_for_lifetime_expiry;
  time_t            last_BS_Operation_Time;
  time_t            initial_holdoff_time;  // Time at which DM server will attempt registration for 1st time 
  uint32_t          intial_delay_time;     // Initial hold off timer for DM servers.
  bool              reg_failure;           // Blocking / Non-blocking server
  uint8_t           retry_count;           // No of attempts in single retry sequence 
  uint32_t          retry_timer;           // Initial retry timer for registration retries.
  uint8_t           seq_retry_count;       // No of retry sequences 
  uint32_t          seq_delay_timer;       // Time between two consecutive sequences.
  uint8_t           retry_attempt;         // Current retry count.
  uint8_t           seq_retry_attempt;     // Current sequence retry count.
  lwm2m_app_obj_info_t *registered_extobj_info;	  /* List of all object instances that are register */  
  lwm2m_app_obj_info_t *registering_extobj_info;  /* List of all object instances that are registering */  
} lwm2m_server_t;

/** Lwm2m transaction info for the request/response received from CoAP. */
typedef struct transaction_cb_info_s 
{
  qapi_Coap_Packet_t * message;          /**< Message in whose reply this CB is called. */
  void *               userData;         /**< Usr Data Passed in the message in whose reply this CB is called. */
  uint8_t              retrans_counter;  /**< Number for times this message was re-transmitted. */
  uint8_t              ack_received;     /**< If set, implies a response to our message, else a timeout has happened. */
}transaction_cb_info_t;


/* Default values for Server object retry resources.*/
#define UNDEFINED_PRIORITY               0xFFFF
#define DEFAULT_INITIAL_DELAY_TIMER      0
#define DEFAULT_REG_FAILURE              FALSE
#define DEFAULT_BS_ON_REG_FAILURE_1_1    TRUE
#define DEFAULT_BS_ON_REG_FAILURE_1_0    FALSE
#define DEFAULT_REG_RETRY_COUNT          5
#define DEFAULT_REG_RETRY_TIMER          60
#define DEFAULT_REG_SEQ_DELAY_COUNT_1_1  1
#define DEFAULT_REG_SEQ_DELAY_COUNT_1_0  0xFF
#define DEFAULT_REG_SEQ_DELAY_TIMER      86400


/*
 * LWM2M Objects
 *
 * For the read callback, if *numDataP is not zero, *dataArrayP is pre-allocated
 * and contains the list of resources to read.
 *
 */

typedef struct _lwm2m_object_t lwm2m_object_t;

typedef uint8_t (*lwm2m_read_callback_t) (uint16_t instanceId, int * numDataP, 
                  lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP,uint16_t resInstId, lwm2m_server_t *serverP);
typedef uint8_t (*lwm2m_discover_callback_t) (uint16_t instanceId, int * numDataP, 
                  lwm2m_data_t ** dataArrayP, lwm2m_object_t * objectP, lwm2m_server_t *serverP);

/* bool bs_true is set to FALSE when call from DM server otherwise set to TRUE*/

typedef uint8_t (*lwm2m_write_callback_t) (uint16_t instanceId, int numData,
                  lwm2m_data_t * dataArray, lwm2m_object_t * objectP, uint16_t resInstId, uint8_t write_method, bool bs_true);
				  
typedef uint8_t (*lwm2m_execute_callback_t) (uint16_t instanceId, uint16_t resourceId,
                  uint8_t * buffer, int length, lwm2m_object_t * objectP);

/* bool apiCall is set TRUE when call from API otherwise set to FALSE*/

typedef uint8_t (*lwm2m_create_callback_t) (uint16_t instanceId, int numData, 
                  lwm2m_data_t * dataArray, lwm2m_object_t * objectP, bool apiCall);

typedef uint8_t (*lwm2m_delete_callback_t) (uint16_t instanceId, 
                  lwm2m_object_t * objectP, bool persist_file);/* Adding persist_file for Single Instance Optional Objects*/
typedef uint8_t (*lwm2m_get_val_callback_t) (uint16_t instanceId, 
                  lwm2m_object_t * objectP, void * getval);

typedef int32_t (*lwm2m_setvalue_callback_t) (lwm2m_object_data_t * lwm2m_data , lwm2m_object_t * targetP);
typedef int32_t (*lwm2m_getvalue_callback_t)  (lwm2m_id_info_t id_info, lwm2m_object_data_t **lwm2m_dataP , lwm2m_object_t * targetP, lwm2m_resource_info_t **resource_info);



struct _lwm2m_object_t
{
  struct _lwm2m_object_t * next;           // for internal use only.
  uint16_t       objID;
  lwm2m_list_t *instanceList;
  lwm2m_read_callback_t     readFunc;
  lwm2m_write_callback_t    writeFunc;
  lwm2m_execute_callback_t  executeFunc;
  lwm2m_create_callback_t   createFunc;
  lwm2m_delete_callback_t   deleteFunc;
  lwm2m_discover_callback_t discoverFunc;
  lwm2m_get_val_callback_t  getValueFunc;
  lwm2m_setvalue_callback_t setValueFunc;
  lwm2m_getvalue_callback_t get_Value_Func;
  
  void * userData;
};


/*
 * LWM2M result callback
 *
 * When used with an observe, if 'data' is not nil, 'status' holds the observe counter.
 */
typedef void (*lwm2m_result_callback_t) (uint16_t clientID, lwm2m_uri_t * uriP, 
               int status, lwm2m_media_type_t format, uint8_t * data, int dataLength, 
               void * userData);

/*
 * LWM2M Observations
 *
 * Used to store observation of remote clients resources.
 * status STATE_REG_PENDING means the observe request was sent to the client but not yet answered.
 * status STATE_REGISTERED means the client acknowledged the observe request.
 * status STATE_DEREG_PENDING means the user canceled the request before the client answered it.
 */

typedef struct _lwm2m_observation_
{
  struct _lwm2m_observation_ * next;  // matches lwm2m_list_t::next
  uint16_t                     id;    // matches lwm2m_list_t::id
  struct _lwm2m_client_ * clientP;
  lwm2m_uri_t             uri;
  lwm2m_status_t          status;
  lwm2m_result_callback_t callback;
  void *                  userData;
} lwm2m_observation_t;

/*
 * LWM2M Link Attributes
 *
 * Used for observation parameters.
 *
 */

#define LWM2M_ATTR_FLAG_MIN_PERIOD      (uint8_t)0x01
#define LWM2M_ATTR_FLAG_MAX_PERIOD      (uint8_t)0x02
#define LWM2M_ATTR_FLAG_GREATER_THAN    (uint8_t)0x04
#define LWM2M_ATTR_FLAG_LESS_THAN       (uint8_t)0x08
#define LWM2M_ATTR_FLAG_STEP            (uint8_t)0x10

typedef struct
{
  uint8_t     toSet;
  uint8_t     toClear;
  uint32_t    minPeriod;
  uint32_t    maxPeriod;
  double      greaterThan;
  double      lessThan;
  double      step;
} lwm2m_attributes_t;

/*
 * LWM2M Clients
 *
 * Be careful not to mix lwm2m_client_object_t used to store list of objects of remote clients
 * and lwm2m_object_t describing objects exposed to remote servers.
 *
 */

typedef struct _lwm2m_client_object_
{
  struct _lwm2m_client_object_ * next; // matches lwm2m_list_t::next
  uint16_t                 id;         // matches lwm2m_list_t::id
  lwm2m_list_t *           instanceList;
} lwm2m_client_object_t;

typedef struct _lwm2m_client_
{
  struct _lwm2m_client_ * next;       // matches lwm2m_list_t::next
  uint16_t                internalID; // matches lwm2m_list_t::id
  char *                  name;
  lwm2m_binding_t         binding;
  char *                  msisdn;
  char *                  altPath;
  bool                    supportJSON;
  uint32_t                lifetime;
  time_t                  endOfLife;
  void *                  sessionH;
  lwm2m_client_object_t * objectList;
  lwm2m_observation_t *   observationList;
} lwm2m_client_t;

/*
 * LWM2M observed resources
 */
typedef struct _lwm2m_watcher_
{
  struct _lwm2m_watcher_ * next;

  bool active;
  bool update;
  lwm2m_server_t * server;
  lwm2m_attributes_t * parameters;
  uint8_t token[TOKEN_LEN];
  size_t tokenLen;
  lwm2m_media_type_t format;
  time_t lastTime;
  uint32_t counter;
  uint16_t lastMid;
  union
  {
     int64_t asInteger;
     double  asFloat;
  } lastValue;
  uint8_t pmin_wait_count;           // No of time pmin time crossed.
  uint8_t store_count;               // No of pending notifications needs to be stored.
} lwm2m_watcher_t;

typedef struct _lwm2m_pending_notify_
{
  struct _lwm2m_pending_notify_ * next;
  lwm2m_watcher_t * watcher_info;
  void * message;
} lwm2m_pending_notify_t;

typedef struct _lwm2m_observed_
{
  struct _lwm2m_observed_ * next;

  lwm2m_uri_t uri;
  lwm2m_watcher_t * watcherList;
} lwm2m_observed_t;

typedef struct _lwm2m_extobj_attr_
{
  struct _lwm2m_extobj_attr_ * next;

  lwm2m_uri_t uri;
  lwm2m_attributes_t * attr;
} lwm2m_extobj_attr_t;


typedef struct _lwm2m_persistent_watcher_
{
  lwm2m_attributes_t parameters;
  lwm2m_uri_t uri;
  uint8_t token[TOKEN_LEN];
  union
  {
     int64_t asInteger;
     double  asFloat;
  } lastValue;
  size_t tokenLen;  
  time_t lastTime;
  uint32_t counter;
  uint16_t lastMid;
  uint16_t serverID;
  bool active;
  bool isParameterSet;
  lwm2m_media_type_t format;
  uint8_t pmin_wait_count;     // No of time pmin time crossed.
} lwm2m_persistent_watcher_t;

typedef enum
{
  STATE_INITIAL = 0,
  STATE_BOOTSTRAP_REQUIRED,
  STATE_BOOTSTRAPPING,
  STATE_REGISTER_REQUIRED,
  STATE_REGISTERING,
  STATE_READY
} lwm2m_client_state_t;


#define CARRIER_APN_LEN  DATA_CALL_INFO_APN_MAX_LEN
#define USERNAME_LEN     DATA_CALL_INFO_USERNAME_MAX_LEN 
#define PASSWORD_LEN     DATA_CALL_INFO_PASSWORD_MAX_LEN

/*
 * LWM2M Context
 */
typedef struct _carrier_apn_cfg_
{ 
  struct _carrier_apn_cfg_ *next;
  uint16_t short_server_id;
  objlink_t apn_link;
  bool bootstrap_apn;
  bool registration_apn;  
  uint8_t auth_type;
  bool auth_type_obj_11;
  uint8_t pdn_type;
  bool pdn_type_obj_11;
  char apn_name[CARRIER_APN_LEN];
  bool apn_name_obj_11;   
  char user_name[USERNAME_LEN];
  bool user_name_obj_11; 
  char password[PASSWORD_LEN];
  bool password_obj_11;
  void *callHdl_v4_nip; /* Re-use for both IPv4 and Non-IP */
  void *callHdl_v6;
  void *bs_match_callHdl_v4_nip; /* Registration server APN match with bootstrap server */
  void *bs_match_callHdl_v6;     /* Registration server APN match with bootstrap server */
  uint8_t apn_class;
  bool bs_if_reg_fails;
  uint8_t ip_family;
  uint8_t non_ip_support; 
  uint8_t ip_support;   
  uint8_t transport_binding;
  uint32_t *retry_timeout_lst;
  uint32_t retry_timeout_lst_len;
  bool reconnect;
  bool send_update;  
  network_bearer_t srvc_type;
  uint32_t v4_nip_call_state;  
  uint32_t v6_call_state;
} carrier_apn_cfg_t;

typedef struct apn_ref_cnt_s
{ 
  char apn_name[CARRIER_APN_LEN];    
  uint8_t cntr; 
} apn_ref_cnt_t;

#define MAX_DATA_CALLS_SUPPORTED_NB_1    0x02
#define MAX_DATA_CALLS_SUPPORTED_M_1     0x04
#define MAX_DATA_CALLS_SUPPORTED MAX_DATA_CALLS_SUPPORTED_M_1

#ifdef PSM_LWM2M

/*
 * LWM2M PSM enums and Data structures
 */

typedef enum
{
  PSM_NODE_MIN,
  PSM_NODE_ADDED = 0x01,      /* PSM Node addition */
  PSM_NODE_REMOVED = 0x02,    /* PSM Node deletion */
  PSM_NODE_MODIFIED = 0x04,   /* PSM Node modified */
  PSM_NODE_MAX,
}psm_node_state_e;

typedef enum
{
  PSM_COMPUTATION_REQUIRED,     /* LwM2M PSM compute required */
  PSM_COMPUTATION_NOT_REQUIRED, /* LwM2M PSM compute not required */
} lwm2m_psm_compute_state_e;

typedef enum
{
  PSM_NODE_TYPE_MIN,
  PSM_NODE_SERVER,       /* PSM server request */
  PSM_NODE_OBSERVATION,  /* PSM observation request */
  PSM_NODE_REBOOTSTRAP,  /* PSM node for handling rebootstraping */
  PSM_NODE_TYPE_MAX,
} lwm2m_psm_node_type_e;

typedef enum
{
  PSM_NODE_UNCHANGED = 0x01,        /* PSM node not updated */
  PSM_NODE_UPDATE    = 0x02,        /* PSM node updated */
  PSM_NODE_UPDATE_ALL= 0x04,        /* All PSM nodes need to update */
} lwm2m_psm_modify_node_type_e;

typedef enum
{
  PSM_ADD_NODE,
  PSM_MODIFY_NODE,
  PSM_REMOVE_NODE,
}lwm2m_psm_operation_e;


typedef struct lwm2m_psm_scheduler_s
{
  struct lwm2m_psm_scheduler_s *next;  /* Next node */
  bool node_active;                    /* Node is active or not If node is active 
                                          then only consider for PSM computation */
  time_t node_active_time;             /* Time at which node is made active */
  uint16_t ssid;                       /* Short server id of server instance */
  lwm2m_uri_t uriP;                    /* Uri structure for Observation request */
  lwm2m_psm_node_type_e node_type;     /* Type of PSM node [Server / Observation]*/
  time_t node_start_interval;          /* PSM node start vote time (in secs) */
  time_t node_end_interval;            /* PSM node end vote time (in secs) */
  time_t node_delta;                   /* Delta to consider for overlapping period */
 //psm_wakeup_type_e node_wakeup_type;  /* PSM wakeup type. */
  uint8_t node_mask;                   /* PSM node state [Add, remove or modified] */
} lwm2m_psm_scheduler_t;

typedef struct
{
  bool  is_modem_loaded;             /* Modem is loaded or not.*/
  bool  psm_registered;              /* LwM2M client registered with PSM or not.*/
  bool  psm_enabled;                 /* PSM enabled from NW/Modem side or not*/
  bool  psm_voted;                   /* LwM2M client voted for PSM or not*/
  time_t  last_psm_vote_time;        /* Last PSM vote time */
  int32_t  client_id;                /* Client id recieved after registering with PSM daemon */
  //psm_status_msg_type  psm_msg;      /* Client id recieved after registering with PSM daemon */
  //psm_status_type_e  psm_status;     /* PSM status message type. */
  uint8_t  lifetime_delta_percentage;/* Lifetime percenatge for delta calculation.*/
  uint8_t  pmin_delta_percentage;    /* Pmin percenatge for delta calculation.*/
  uint8_t  pmax_delta_percentage;    /* Pmax percenatge for delta calculation.*/
  time_t  transport_guard;           /* Transport delta for lifetime expiry extension.*/
  time_t  default_psm_delta;         /* Time used for delta when pmin and pmax are not defined.*/
  time_t  lwm2m_wakeup_start_time;   /* PSM start vote time (in secs) */
  time_t  lwm2m_wakeup_end_time;     /* PSM end vote time (in secs) */
  //psm_wakeup_type_e  lwm2m_wakeup_type; /* PSM wakeup type. */
  bool  pmin_pmax_awake;                   /* If set then UE won't go PSM after Pmin expiry */
  lwm2m_psm_compute_state_e  compute_state; /* LwM2M PSM compute state */
  qurt_mutex_t  lwm2m_psm_mutex;           /* LwM2M PSM mutex */
  uint16_t  psm_node_count;                 /* Total PSM node added by LwM2M*/
  lwm2m_psm_scheduler_t  *psm_schedule_list; /* LwM2M PSM node list */
  uint8_t	timerId; /* Deep sleep timer ID */
} lwm2m_psm_context_t;

#endif

/* Structure to hold DM servers which are ready for registration sequence.*/
typedef struct _lwm2m_active_server_t
{
  struct _lwm2m_active_server_t *next;
  uint16_t ssid;
  uint16_t pri_order;
  time_t initial_holdoff_time;
}lwm2m_active_server_t;

typedef struct
{
#ifdef LWM2M_CLIENT_MODE
  lwm2m_client_state_t state;
  char *endpointName;
  char *bootstrapEpName;
  char *msisdn;
  char *altPath;
  lwm2m_server_t *bootstrapServer;
  lwm2m_server_t *serverList;
  lwm2m_object_t *objectList;
  lwm2m_observed_t *observedList;
  lwm2m_pending_notify_t *notifypendingList;
  lwm2m_list_t   *acObjInstList;
  lwm2m_server_t *activeServerP;
#endif
  uint16_t bs_apn_match_reg_id; /* Bootstrap APN matches the registration server(s) */ 
  apn_ref_cnt_t call_cntr[MAX_DATA_CALLS_SUPPORTED];  /* APN reference counter (filter duplicate APNs supporting call-sharing) */ 
  carrier_apn_cfg_t *apn_cfg;   /* Updated APN config information based on server APN link and carrier APN  */
  carrier_apn_cfg_t *c_apn_cfg; /* APN config from carrier APN file (unchanged) */
  void *userData;
  time_t time_for_bs;
#ifdef PSM_LWM2M
  lwm2m_psm_context_t *   lwm2m_psm_info;   // LwM2M PSM context information.
#endif
  lwm2m_active_server_t *activeServerList;  // LwM2M active server list to hold servers which are ready for registration sequence.
  lwm2m_active_server_t *lastActiveServer;  // Last ordered server which was made active.
} lwm2m_context_t;

typedef struct 
{
  float lwm2m_version;  
  char apn_info[CARRIER_APN_LEN];
  uint32_t ack_timeout;
  uint8_t ip_family;
  bool ip_support;
  bool non_ip_support;
  uint32_t *retry_timeout_lst;
  uint32_t retry_timeout_lst_len;
  bool roaming_feat;
  uint8_t carrier_type;
  uint8_t battery_level_threshold;  
  uint32_t max_rebootstrap_attempts;
  uint8_t  reg_endpoint_name;
  uint8_t  bootstrap_endpoint_name;
  uint32_t boot_up_sleep;
  uint32_t session_resumption_time;
  uint8_t max_bootstrap_wait;
  uint8_t lwm2m_startup_mode;
  uint8_t startup_wait_time_for_byapp_mode;
  bool reg_update_on_reconnect;
  uint32_t wait_time_for_rereg;
  uint8_t lwm2m_rootca_support_mode;
  uint16_t factory_reset_limit;
  uint16_t reg_update_limit;
  bool psm_enable;
  uint8_t lifetime_percentage;
  uint8_t pmin_percentage;
  uint8_t pmax_percentage;
  time_t  transport_guard;
  time_t  default_psm_delta;
  bool pmin_pmax_awake;
  bool enable_dtls_close_notify;
  uint8_t store_notifications;
  uint8_t connection_count;
/* the raw configuration item, will be used to caculate retry counter value */
  uint32_t max_retry_timeout; 
  uint32_t max_retries;
  uint32_t retry_timeout;
  uint32_t retry_exponent_val;
/* the raw configuration string item, will be used to derive the configured value */
  char ipFamily_str[16];
  char version_str[16];
  char binding_str[16];
  bool truncate_msisdn;
/* Blockwise related */
  uint32_t blockSize;
    
} lwm2m_cfg_info_t;

typedef struct
{
  qapi_Coap_Packet_t *dl_pkt;
} lwm2m_pending_pkt;

int lwm2m_profile_action(void *userData);

/**
 * @fn void prv_handleBootstrapReply()
 * @brief This function is used to handle bootstrap reply
 *
 * @param transaction   coap_transaction_t pointer
 * @param message       void message pointer
 *
 * @return      void
 */
void prv_handleBootstrapReply(qapi_Coap_Session_Hdl_t hdl ,transaction_cb_info_t * transaction,
    qapi_Coap_Packet_t * rsp_pkt);

/**
 * @fn prv_handleRegistrationReply()
 * @brief function to handle Registartion reply message
 * @param transacP transaction handle
 * @param message message received
 * @return  void
 */
void prv_handleRegistrationReply(qapi_Coap_Session_Hdl_t hdl,
     transaction_cb_info_t * transacP,
     qapi_Coap_Packet_t * rsp_pkt);

/**
 * @fn prv_handleRegistrationUpdateReply()
 * @brief function to handle registration update reply
 * @param transacP transaction handle
 * @param message message received
 * @return  void
 */
void prv_handleRegistrationUpdateReply(qapi_Coap_Session_Hdl_t hdl, 
    transaction_cb_info_t * transacP,
    qapi_Coap_Packet_t * rsp_pkt);


/**
 * @fn prv_handleDeregistrationReply()
 * @brief function to handle de-registration response
 * @param transacP transaction pointer
 * @param message response message
 * @return  void
 */
void prv_handleDeregistrationReply(qapi_Coap_Session_Hdl_t hdl ,transaction_cb_info_t * transacP,
    qapi_Coap_Packet_t * rsp_pkt);


#ifdef PSM_LWM2M

/*  LWM2M PSM function declarations. */

/**
 * @fn void lwm2m_psm_event_handle()
 *
 * @brief This function is used to handle different events recieved from PSM daemon.
 *
 * @param psm_status  PSM status message contains status and reject reason (if any)
 *
 * @return None
 */
//void lwm2m_psm_event_handle(psm_status_msg_type *psm_status);


/**
 * @fn lwm2m_psm_scheduler_t * lwm2m_psm_find_node()
 *
 * @brief This function is used to find PSM node based on server short server id,
 *        uri ( for watcher node ).and type of LwM2M PSM node.
 *
 * @param contextP  LwM2M client context
 * @param ssid      Short server id
 * @param uri       Uri of observed watcher
 * @param node_type Type of LwM2M PSM node
 *
 * @return Node if found or NULL is returned
 */
lwm2m_psm_scheduler_t * lwm2m_psm_find_node(lwm2m_context_t * contextP,
                                            uint16_t ssid,
                                            lwm2m_uri_t uri,
                                            lwm2m_psm_node_type_e node_type);

/**
 * @fn void lwm2m_psm_fill_psm_info()
 *
 * @brief This function is used to fill different fields realted to LwM2M PSM node
 *
 * @param contextP  LwM2M client context
 * @param ssid      Short server id
 * @param uri       Uri of observed watcher
 * @param node_type Type of LwM2M PSM node
 * @param node      LwM2M PSM node which needs to be updated.
 *
 * @return None
 */
void lwm2m_psm_fill_psm_info(lwm2m_context_t *contextP,
                             uint16_t ssid,
                             lwm2m_uri_t uri,
                             lwm2m_psm_node_type_e node_type,
                             lwm2m_psm_scheduler_t *node);

/**
 * @fn qapi_Status_t lwm2m_psm_add_node()
 *
 * @brief This function is used to add PSM node based on server short server id,
 *        uri ( for watcher node ).and type of LwM2M PSM node in global LwM2M PSM 
 *        node list.
 *
 * @param contextP  LwM2M client context
 * @param ssid      Short server id
 * @param uri       Uri of observed watcher
 * @param node_type Type of LwM2M PSM node
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_psm_add_node(lwm2m_context_t *contextP, 
                                 uint16_t ssid,
                                 lwm2m_uri_t uri,
                                 lwm2m_psm_node_type_e node_type);

/**
 * @fn qapi_Status_t lwm2m_psm_remove_node()
 *
 * @brief This function is used to remove PSM node based on server short server id,
 *        uri ( for watcher node ).and type of LwM2M PSM node in global LwM2M PSM 
 *        node list.
 *
 * @param contextP  LwM2M client context
 * @param ssid      Short server id
 * @param uri       Uri of observed watcher
 * @param node_type Type of LwM2M PSM node
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_psm_remove_node(lwm2m_context_t *contextP, 
                                    uint16_t ssid,
                                    lwm2m_uri_t uri,
                                    lwm2m_psm_node_type_e node_type);

/**
 * @fn qapi_Status_t lwm2m_psm_modify_node()
 *
 * @brief This function is used to modify PSM node based on server short server id,
 *        uri ( for watcher node ).and type of LwM2M PSM node in global LwM2M PSM 
 *        node list.
 *        If all_nodes is set to TRUE then all nodes in LwM2M PSM node list need 
 *        to be updated.
 *
 * @param contextP  LwM2M client context
 * @param ssid      Short server id
 * @param uri       Uri of observed watcher
 * @param node_type Type of LwM2M PSM node
 * @param update_type No update, single node update or all node update .
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_psm_modify_node(lwm2m_context_t *contextP, 
                                    uint16_t ssid,
                                    lwm2m_uri_t uri,
                                    lwm2m_psm_node_type_e node_type,
                                    lwm2m_psm_modify_node_type_e update_type);


/**
 * @fn qapi_Status_t lwm2m_psm_operation()
 *
 * @brief This function is used as a wrapper to call lwm2m_psm_add_node, lwm2m_psm_remove_node
 *        or lwm2m_psm_modify_node on the bases of lwm2m_psm_operation_e.
 *
 * @param contextP  LwM2M client context
 * @param ssid      Short server id
 * @param uri       Uri of observed watcher
 * @param node_type Type of LwM2M PSM node
 * @param update_type No update, single node update or all node update .
 * @param psm_operation Type of PSM operation to be performed(Add, Modify, Remove)
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */

qapi_Status_t lwm2m_psm_operation(lwm2m_context_t *contextP, 
                                    uint16_t ssid,
                                    lwm2m_uri_t *uri,
                                    lwm2m_psm_node_type_e node_type,
									lwm2m_psm_modify_node_type_e update_type,
									lwm2m_psm_operation_e psm_operation
									);

/**
 * @fn qapi_Status_t lwm2m_psm_init()
 *
 * @brief This function is used to allocate LwM2M PSM context and initialize the
 *        LwM2M PSM related information Configuration items are poulated.
 *
 * @param lwm2mP  LwM2M client context
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_psm_init(lwm2m_context_t *lwm2mP);

/**
 * @fn qapi_Status_t lwm2m_psm_deinit()
 *
 * @brief This function is used to de-allocate LwM2M PSM context and free 
 *        LwM2M PSM realted information .
 *
 * @param lwm2mP  LwM2M client context
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_psm_deinit(lwm2m_context_t *lwm2mP);

/**
 * @fn qapi_Status_t lwm2m_cancel_vote_for_psm()
 *
 * @brief This function is used to cancel PSM vote by LwM2M client.
 *
 * @param lwm2mP  LwM2M client context
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_cancel_vote_for_psm(lwm2m_context_t *contextP);

/**
 * @fn qapi_Status_t lwm2m_vote_for_psm()
 *
 * @brief This function is used to vote for PSM by LwM2M client.
 *
 * @param lwm2mP  LwM2M client context
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_vote_for_psm(lwm2m_context_t *contextP);

/**
 * @fn bool lwm2m_psm_node_modified()
 *
 * @brief This function is used to check that any PSM node is modified or not.
 *
 * @param lwm2mP  LwM2M client context
 *
 * @return TRUE if any node is modified else false
 */
bool lwm2m_psm_node_modified(lwm2m_context_t *contextP);

/**
 * @fn void lwm2m_psm_unlink_node()
 *
 * @brief This function is used to unlink LwM2M PSM node from global LwM2M PSM 
 *        node list.
 *
 * @param node_list  Head of global LwM2M PSM node list.
 * @param rm_node    Node to be unlinked from global LwM2M PSM node list.
 *
 * @return None
 */
void lwm2m_psm_unlink_node(lwm2m_psm_scheduler_t **node_list,
                           lwm2m_psm_scheduler_t *rm_node);

/**
 * @fn qapi_Status_t lwm2m_psm_compute_time()
 *
 * @brief This function is used to compute optimal time to vote for PSM by LwM2M
 *        client based on differnt nodes configured..
 *
 * @param lwm2mP  LwM2M client context
 *
 * @return See Section @xref{hdr:QAPIStatust}. \n
 * On success, QAPI_OK (0) is returned. Other value on error.
 */
qapi_Status_t lwm2m_psm_compute_time(lwm2m_context_t *contextP);

void psm_step(lwm2m_context_t *contextP,
              time_t currentTime,
              time_t * timeoutP);
#endif

void lwm2m_application_response_handler 
(
  qapi_Coap_Session_Hdl_t hdl,
  transaction_cb_info_t * transaction,
  qapi_Coap_Packet_t*message
);


/**
 * @brief LWM2M application observe information (standard objects only)
 */
typedef struct lwm2m_app_observe_info_s
{
  struct lwm2m_app_observe_info_s *next;   /* Observe information list */
  uint16_t object_ID;                      /* Object ID */  
  uint8_t instance_ID;                     /* Instance ID */
  uint8_t resource_ID;                     /* Resource ID */
  uint8_t id_set;                          /* ID is set for observation */
  qapi_Net_LWM2M_App_CB_t observe_cb_fn;   /* Observe applciation callback to indicate notifications */
} lwm2m_app_observe_info_t;

/**
 * @brief LWM2M application observe information (standard objects only) Version 2
 */
typedef struct lwm2m_app_observe_info_v2_s
{
  struct lwm2m_app_observe_info_v2_s *next;   /* Observe information list */
  uint16_t object_ID;                      /* Object ID */  
  uint16_t instance_ID;                     /* Instance ID */
  uint16_t resource_ID;                     /* Resource ID */
  uint8_t id_set;                          /* ID is set for observation */
  qapi_Net_LWM2M_App_CB_v2_t observe_cb_fn;   /* Observe applciation callback to indicate notifications */
} lwm2m_app_observe_info_v2_t;


/**
 * @brief LWM2M application object persistent information 
 */
typedef struct lwm2m_app_persist_obj_info_s
{
  uint16_t object_ID;                      /* Object ID */
  uint16_t instance_ID;                    /* Instance ID */
} lwm2m_app_persist_obj_info_t;

/**
 * @brief LWM2M application handle specific information  
 */
typedef struct lwm2m_handle_info_s
{
  struct lwm2m_handle_info_s *next;        /* Application handle list */
  uint16_t handle_id;                      /* Validate the LWM2M application client handle (internal) */
  uint32_t id;                             /* External handle identifier */
  uint32_t module_uid;
  uint32_t module_instance;
  lwm2m_app_observe_info_t *observe_info;  /* Observation information */  
  lwm2m_app_observe_info_v2_t *observe_info_v2; /* Updated observation information.*/
  void *user_data;                         /* Application cookie */
  qapi_Net_LWM2M_App_Extended_CB_t user_cb_fn;   /* Application callback to indicate internal indications and server requests */
  lwm2m_app_obj_info_t *obj_info;          /* List of object instances created/deleted by the application */  
  boolean version_v2;                      /* Determine which observation information to be used */ 
  boolean  handle_downlink_blockwise;      /* Enable handling of downlink blockwise packets  */
} lwm2m_handle_info_t;

/**
 * @brief LWM2M application context generic information 
 */
typedef struct lwm2m_app_ctx_s
{
  boolean lwm2m_app_inited;                    /* LWM2M application context initialization status */ 
  uint16_t handle_id_cntr;                     /* Generates and ID to the handle */   
  uint8_t bs_performed;                        /* LWM2M bootstrapping performed */
  uint8_t factory_bs;                          /* LWM2M factory re-bootstrapping */
  uint8_t device_active;                       /* LWM2M device active or sleep state */
  uint8_t rebootstrap_req;                     /* LWM2M re-bootstrapping required on reboot */
  uint8_t purged_app_obj_persistence;          /* LWM2M application object persistence deletion */
  lwm2m_client_state_t lwm2m_state;            /* Subset of LWM2M states mainly for object creation */
  qurt_mutex_t lwm2m_app_global_mutex;         /* Global LWM2M application synchronization mutex */  
  lwm2m_handle_info_t *handles;                /* LWM2M application handles */
  lwm2m_extobj_attr_t *extobj_attribute_list;  /* Write-attribute of extensible object(temporary variable) */
} lwm2m_app_ctx_t;

typedef struct 
{
  lwm2m_object_t  *securityObjP;
  lwm2m_object_t  *serverObject;
  lwm2m_context_t *lwm2mH;
  lwm2m_app_ctx_t  glwm2m_app_ctx;    /* LWM2M application global context */ 
  lwm2m_cfg_info_t cfg_info;
} client_data_t;

typedef struct lwm2m_location_read_observe_pending_s
{
  q_link_type link;
  uint8_t observe_req;
  lwm2m_uri_t uriP;
  uint32_t session_id;
  lwm2m_media_type_t format;
  lwm2m_media_type_t accept;
  uint16_t ssid;
  uint8_t token_len;
  uint8_t token[8];
}lwm2m_location_read_observe_pending_t;


/* Handle to the internal LWM2M context */ 
extern client_data_t data;

// initialize a liblwm2m context.
lwm2m_context_t * lwm2m_init(void * userData);
// close a liblwm2m context.
void lwm2m_close(lwm2m_context_t * contextP);

// close CoAP connection and destroy CoAP session.
void lwm2m_clean_coap_session(lwm2m_server_t *serverP);

// perform any required pending operation and adjust timeoutP to the maximal time interval to wait in seconds.
int lwm2m_step(lwm2m_context_t * contextP, time_t * timeoutP);
// dispatch received data to liblwm2m
//void lwm2m_handle_packet(lwm2m_context_t * contextP, uint8_t * buffer, int length, void * fromSessionH);
void lwm2m_handle_packet(void * contextP, uint8_t * buffer, int length, void * fromSessionH);
void reset_global_flags(bool val);
void purge_persistent_values(void);
#ifdef LWM2M_CLIENT_MODE
/* configure the client side with the Endpoint Name, binding, MSISDN 
 * (can be nil), alternative path for objects (can be nil) and a list of objects.
 * LWM2M Security Object (ID 0) must be present with either a bootstrap server 
 * or a LWM2M server and its matching LWM2M Server Object (ID 1) instance
 */
int lwm2m_configure(lwm2m_context_t * contextP,
                      const char * altPath, uint16_t numObject,
                    lwm2m_object_t * objectList[]);
int lwm2m_add_object(lwm2m_context_t * contextP, lwm2m_object_t * objectP);
int lwm2m_remove_object(lwm2m_context_t * contextP, uint16_t id);

int lwm2m_update_registration_for_server(lwm2m_context_t * contextP, lwm2m_server_t * targetP,
                              bool withObjects);

void resource_value_change(lwm2m_object_data_t *lwm2m_data);
void lwm2m_resource_value_changed(lwm2m_context_t * contextP, lwm2m_uri_t * uriP);
int prv_refreshServerList(lwm2m_context_t * contextP);
int prv_refreshBSServer(lwm2m_context_t * contextP);
void value_change(
    const char* uriPath,
    const char * value,
    size_t valueLength);
int sync_observations_to_persistence(lwm2m_context_t * contextP);
int sync_observations_from_persistence(lwm2m_context_t *contextP);
#endif
int lwm2m_get_server_count(lwm2m_context_t * contextP, bool isBSServer);

/* send a registration update to the server specified by the server short identifier
 * or all if the ID is 0.
 * If withObjects is true, the registration update contains the object list.
 */
int lwm2m_update_registration(lwm2m_context_t * contextP, uint16_t shortServerID,
                              bool withObjects);
void lwm2m_deregister(lwm2m_context_t * context);

int32_t lwm2m_get_object_info(lwm2m_object_info_t *lwm2m_info_req, lwm2m_object_data_t ** lwm2m_dataP);
int32_t lwm2m_set_object_info(lwm2m_object_data_t * lwm2m_data , uint16_t object_ID);
int32_t lwm2m_create_object_instance(lwm2m_data_t *dataArrayP ,uint16_t count , uint16_t object_id ,uint16_t instance_id);
bool lwm2m_check_if_observe_and_update_app(uint8_t id_set, uint16_t object_ID, uint16_t instance_ID, uint16_t resource_ID, lwm2m_object_data_t *data);
int32_t lwm2m_client_application_notification(lwm2m_server_data_t *server_data);
qapi_Status_t lwm2m_send_internal_ind_to_application(qapi_Net_LWM2M_Event_t event);
void lwm2m_send_wakeup_ind_to_at();


int lwm2m_remove_object_instance(uint16_t obj_id, uint16_t inst_id, bool api_call);
void m2m_intToString(char *str, int num);
void lwm2m_free_id_info (lwm2m_id_info_t *lwm2m_id_infoP);
void lwm2m_free_lwm2m_data(lwm2m_object_data_t *lwm2m_dataP);
void lwm2m_free_instance_info (  lwm2m_instance_info_t  *lwm2m_instanceP);
void lwm2m_free_resource_info (lwm2m_resource_info_t *lwm2m_resourceP);
bool prv_write_resource_inst_val(resource_instance_int_list_t** rsList, uint16_t resId, uint16_t resValue);
resource_instance_int_list_t * find_resource_inst(resource_instance_int_list_t * head, uint16_t id);
bool prv_write_string_resource_inst_val(resource_instance_string_list_t** rsList, uint16_t resId, char* resValue);
resource_instance_string_list_t * find_string_resource_inst(resource_instance_string_list_t * head, uint16_t id);  
resource_instance_time_list_t * find_time_resource_inst(resource_instance_time_list_t * head, uint16_t id);
bool prv_write_resource_time_val(resource_instance_time_list_t** rsList, uint16_t resId, time_t resValue);
bool prv_delete_resource_inst_val(resource_instance_int_list_t** rsList,uint16_t resId);
bool prv_delete_resource_time_val(resource_instance_time_list_t** rsList,uint16_t resId);
bool prv_delete_string_resource_inst_val(resource_instance_string_list_t** rsList,uint16_t resId);
bool prv_write_string_resource_val(resource_instance_string_list_t** rsList, char* resValue);
bool prv_delete_string_resource_val(resource_instance_string_list_t** rsList, char* resValue);
                            
#ifdef LWM2M_CLIENT_MODE                               
lwm2m_client_state_t lwm2m_get_client_state(void);
int get_ip_for_carrier_apn_cfg(carrier_apn_cfg_t *carrier_apn_cfg, lwm2m_server_t *server_info, char *server_ip);
#endif

lwm2m_watcher_t * prv_getWatcher(lwm2m_context_t * contextP, lwm2m_uri_t * uriP,lwm2m_server_t * serverP);
lwm2m_watcher_t * prv_findInheritedWatcher(lwm2m_context_t * contextP, lwm2m_uri_t *uriP,
                                           lwm2m_server_t *serverP, uint8_t flag);

bool write_Tlv_to_file (int fd, int tag, uint8_t length, uint8_t* value);
int  read_Tlv_from_file(int fd, int* tag, uint8_t* length, uint8_t** value);
bool lwm2m_set_extobj_write_attr(qapi_Net_LWM2M_Attributes_t *write_attr);
void lwm2m_clean_extobj_write_attr(void);
lwm2m_attributes_t * lwm2m_findByUri_extobj_attr(lwm2m_uri_t * uriP);

int  storeRegisteringExtObj(lwm2m_server_t* serverP, uint16_t objID, uint16_t insID, bool instance);
void storeRegisteredExtObj (lwm2m_server_t* serverP,bool bRegisterSuccess);
void deleteExtObjInfoList(lwm2m_app_obj_info_t* obj_info);
void cleanExtObjInfoList(lwm2m_server_t* serverP);
int  persistRegisterdExtObj(void);
int  loadRegisterdExtObj(lwm2m_context_t *lwm2mH);
void StartExtObjCreateWindow(lwm2m_context_t *lwm2mH);
bool IsInExtObjCreateWindow(void);
void StopExtObjCreateWindow(void);
void extObjCreateWindowTimercb(  int32_t time_ms, timer_cb_data_type userData );
void extObjRegUpdateCheck(lwm2m_server_t* serverP);
int load_software_mgnt_persistent_info(lwm2m_object_t * objectP);
int load_device_cap_manangement_persistent_info(lwm2m_object_t * objectP);

int sync_activeserverlist_to_persistence(lwm2m_context_t *contextP);
int sync_activeserverlist_from_persistence(lwm2m_context_t *contextP);

void lwm2m_sort_servers(lwm2m_server_t *server_lst,
                                uint8_t left, uint8_t right,
                                lwm2m_server_t *node);
void lwm2m_sort_servers_by_pri(void **server_lst);
void lwm2m_create_active_server_list(lwm2m_context_t *contextP);
void lwm2m_sort_active_server_list(lwm2m_context_t *contextP);
int populate_lower_version_retry_values(uint16_t shortId, uint16_t instanceId);
void get_1_0_retry_info(lwm2m_server_t * targetP);
void get_1_1_retry_info(lwm2m_object_t * objectP,
                             uint16_t instanceID,
                             lwm2m_server_t * targetP);
int prv_getServerInfo(lwm2m_object_t * objectP,
    uint16_t instanceID,
    lwm2m_server_t * targetP);
lwm2m_server_t *lwm2m_get_server(uint16_t shortId);
void prv_deleteServer(lwm2m_server_t * serverP, lwm2m_context_t * context, bool isUpdateACL);

carrier_apn_cfg_t *get_lwm2m_apn_cfg(void );

int prv_init_getvalue
(
 lwm2m_id_info_t id_info,
 lwm2m_object_data_t *lwm2m_dataP,
 lwm2m_resource_info_t **resource_info,
 lwm2m_data_t ** dataArrayP,
 int*numData
);

int prv_getvalue_resource_populate
(
 lwm2m_object_data_t **lwm2m_data,
 lwm2m_data_t * dataArrayP,
 lwm2m_resource_info_t **resource_info,
 int numData
);

uint8_t prv_init_resources
(
  lwm2m_object_data_t* lwm2m_data,
  uint8_t* id_set,
  uint16_t object_id,
  uint16_t instanceId,
  uint16_t resource_id
);

uint8_t prv_write_init_resources
(
	lwm2m_object_data_t* lwm2m_data,
	uint8_t* id_set,
	lwm2m_data_t * data,
	int object_id,
	int instanceId,
	lwm2m_value_type_t data_type
);

int get_msisdn_from_persistence(char* msisdn_buf);

int store_msisdn_to_persistence(char* msisdn_buf);

qapi_Status_t lwm2m_flat_data_release
( 
  size_t lwm2m_data_size,
  qapi_Net_LWM2M_Flat_Data_t **lwm2m_data
);
qapi_Status_t lwm2m_flat_data_copy_to_uspace
(
  size_t               in_lwm2m_data_size,  
  qapi_Net_LWM2M_Flat_Data_t  *in_lwm2m_data, 
  qapi_Net_LWM2M_Flat_Data_t **out_lwm2m_data
);

void free_lwm2m_copy_obj_info(qapi_Net_LWM2M_Object_Info_t **k_obj_info);

void free_lwm2m_copy_obj_info_v2(qapi_Net_LWM2M_Object_Info_v2_t **k_obj_info);

int lwm2m_copy_obj_info(uint32_t module_uid, uint32_t module_instance,
                                               qapi_Net_LWM2M_Object_Info_t *u_obj_info,
                                               qapi_Net_LWM2M_Object_Info_t **k_obj_info);

int lwm2m_copy_obj_info_v2(uint32_t module_uid, uint32_t module_instance,
                                                   qapi_Net_LWM2M_Object_Info_v2_t *u_obj_info,
                                                   qapi_Net_LWM2M_Object_Info_v2_t **k_obj_info);
void free_lwm2m_all_resource_instances
(
  qapi_Net_LWM2M_Resource_Info_t * resource_info_head,
  void *memory_pool
);
qapi_Status_t free_lwm2m_copy_data
(
  qapi_Net_LWM2M_Data_t **lwm2m_data,
  void *memory_pool
);
qapi_Status_t free_lwm2m_copy_data_v2
(
  qapi_Net_LWM2M_Data_v2_t **lwm2m_data,
  void *memory_pool
);
qapi_Status_t lwm2m_copy_resource_instances
(
  qapi_Net_LWM2M_Resource_Info_t* in_res_info ,
  qapi_Net_LWM2M_Resource_Info_t** out_res_info,
  int count,size_t in_res_info_size,
  uint32_t module_uid, uint32_t module_instance,
  void *memory_pool, qapi_Net_LWM2M_App_Handler_t handle
);

int lwm2m_copy_data(uint32_t module_uid, uint32_t module_instance,
                                         qapi_Net_LWM2M_Data_t *in_lwm2m_data, 
                                         qapi_Net_LWM2M_Data_t **out_lwm2m_data,
                                         qapi_Net_LWM2M_App_Handler_t handle);

int lwm2m_copy_data_v2(uint32_t module_uid, uint32_t module_instance,
                                             qapi_Net_LWM2M_Data_v2_t *in_lwm2m_data, 
                                             qapi_Net_LWM2M_Data_v2_t **out_lwm2m_data,
                                             qapi_Net_LWM2M_App_Handler_t handle);

qapi_Status_t free_lwm2m_copy_ext_obj_data
(
  qapi_Net_LWM2M_App_Ex_Obj_Data_t **lwm2m_data,
  void *memory_pool
);

int lwm2m_copy_ext_obj_data(uint32_t module_uid, uint32_t module_instance,
                                      qapi_Net_LWM2M_App_Ex_Obj_Data_t *in_lwm2m_data, 
                                      qapi_Net_LWM2M_App_Ex_Obj_Data_t **out_lwm2m_data,
                                      qapi_Net_LWM2M_App_Handler_t handle);

qapi_Status_t free_lwm2m_flat_data
( 
  size_t lwm2m_data_size,
  qapi_Net_LWM2M_Flat_Data_t **lwm2m_data,
  void *memory_pool
);

int lwm2m_flat_data_copy
(
  uint32_t module_uid, uint32_t module_instance,
  size_t               in_lwm2m_data_size,
  qapi_Net_LWM2M_Flat_Data_t  *in_lwm2m_data, 
  qapi_Net_LWM2M_Flat_Data_t **out_lwm2m_data,
  qapi_Net_LWM2M_App_Handler_t handle
);

void free_lwm2m_copy_config
(
  qapi_Net_LWM2M_Config_Data_t **config_info_head,
  void *memory_pool
);

int lwm2m_copy_config
(
  uint32_t module_uid, uint32_t module_instance,
  qapi_Net_LWM2M_Config_Data_t* in_data ,
  qapi_Net_LWM2M_Config_Data_t** out_data,
  qapi_Net_LWM2M_App_Handler_t handle
);

void free_lwm2m_attribute_copy(qapi_Net_LWM2M_Attributes_t **k_attributes);
int lwm2m_attribute_copy
(
  uint32_t module_uid, uint32_t module_instance,
  qapi_Net_LWM2M_Attributes_t *in_data, 
  qapi_Net_LWM2M_Attributes_t **out_data
);

void lwm2m_unlink_node(void **head, void *node);

void lwm2m_cb_util(qapi_Coap_Session_Hdl_t hdl,
     qapi_Coap_Transaction_t * transacP,
     qapi_Coap_Packet_t * rsp_pkt,
     uint8_t cmd_id);
qapi_Status_t lwm2m_parse_application_object_info 
(
  qapi_Net_LWM2M_Instance_Info_v2_t *instance_info,
  qapi_Net_LWM2M_Resource_Info_t *resource_info,
  lwm2m_data_t **parsed_data
);

void lwm2m_data_free_ext(int size,
                                 lwm2m_data_t * dataP);
void trigger_factory_reset_util(bool is_immediate, qapi_Net_LWM2M_Event_t event);

#ifdef __cplusplus
}
#endif

#endif
