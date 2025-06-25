/******************************************************************************

  @file    lwm2mclient.h

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

/*******************************************************************************
 *
 * Copyright (c) 2014 Bosch Software Innovations GmbH, Germany.
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
 *    Bosch Software Innovations GmbH - Please refer to git log
 *
 *******************************************************************************/
/*
 * lwm2mclient.h
 *
 *  General functions of lwm2m test client.
 *
 *  Created on: 22.01.2015
 *  Author: Achim Kraus
 *  Copyright (c) 2015 Bosch Software Innovations GmbH, Germany. All rights reserved.
 */

#ifndef LWM2MCLIENT_H_
#define LWM2MCLIENT_H_

#include "liblwm2m.h"

#define M2M_PRIMARY_APN_DC_MASK     0x01
#define M2M_SECONDARY_APN1_DC_MASK  0x02
#define M2M_SECONDARY_APN2_DC_MASK  0x04
#define M2M_SECONDARY_APN_DC_MASK   (M2M_SECONDARY_APN1_DC_MASK /*| M2M_SECONDARY_APN2_DC_MASK*/)

#define M2M_EXPRETRY_DEFTIMEOUT     30
#define M2M_EXPRETRY_MAXTIMEOUT     640

#define INVALID_TRANSPORT   (BINDING_UNKNOWN)
#define UDP_TRANSPORT       (BINDING_U)
#define NONIP_TRANSPORT     (BINDING_N)
#define UDP_NONIP_TRANSPORT (UDP_TRANSPORT | NONIP_TRANSPORT)

#define INVALID_PDN_TYPE   0x00
#define NONIP_PDN_TYPE     NONIP_TRANSPORT
#define IP_PDN_TYPE        UDP_TRANSPORT



#define DEVICE_STATE(S)                                \
((S) == LWM2M_CLIENT_STATE_DEVICE_NOT_CONNECTED ? "LWM2M_CLIENT_STATE_DEVICE_NOT_CONNECTED" :      \
((S) == LWM2M_CLIENT_STATE_DEVICE_DM_NOT_CONNECTED ? "LWM2M_CLIENT_STATE_DEVICE_DM_NOT_CONNECTED" :      \
((S) == LWM2M_CLIENT_STATE_DEVICE_DM_CONNECTED ? "LWM2M_CLIENT_STATE_DEVICE_DM_CONNECTED" :  \
((S) == LWM2M_CLIENT_STATE_DEVICE_M2M_OPERATIONAL ? "LWM2M_CLIENT_STATE_DEVICE_M2M_OPERATIONAL" :        \
"Unknown"))))

/*
#define GET_SMS_LIMIT(S)                                \
((S) == FACTORY_RESET ?  data.cfg_info.factory_reset_limit\
((S) == FACTORY_RESET ?  data.cfg_info.reg_update_limit\
))
*/
typedef enum {
  QMI_CHANGE_IND_SIGNALSTRENGTH = 1,
  QMI_CHANGE_IND_LINKQUALITY,
  QMI_CHANGE_IND_CELLID,
  QMI_CHANGE_IND_MNC,
  QMI_CHANGE_IND_MCC,
  QMI_CHANGE_IND_TXBYTES,
  QMI_CHANGE_IND_RXBYTES ,
  QMI_CHANGE_IND_NETWORKBEARER,
  QMI_CHANGE_IND_PSM_TIMER,
  QMI_CHANGE_IND_ACTIVE_TIMER,
} qmi_change_ind_type;

#define GET_SMS_LIMIT(operation, sms_cnt)    \
{\
  if (operation == FACTORY_RESET)   \
  { \
    sms_cnt = data.cfg_info.factory_reset_limit; \
  } \
  if (operation == REG_UPDATE) \
  { \
    sms_cnt = data.cfg_info.reg_update_limit;  \
  }  \
}


/**
 * This enum defines the SMS operation 
 */
typedef enum
{
  FACTORY_RESET = 0,
  REG_UPDATE = 1,
} lwm2m_sms_operation_E;


typedef enum _lwm2m_data_call_op
{
  LWM2M_START_BOOTSTRAP_DATA_CALL = 0,
  LWM2M_START_REGISTRATION_DATA_CALL,
  LWM2M_STOP_BOOTSTRAP_DATA_CALL,
  LWM2M_STOP_REGISTRATION_DATA_CALL,
} lwm2m_data_call_op_t; 


/**
 * Event associated with the data call 
 */ 
typedef enum lwm2m_data_call_event_e
{
  LWM2M_DATA_CALL_REGISTERED = 0,  
  LWM2M_DATA_CALL_DEREGISTERED,
  LWM2M_DATA_CALL_START,
  LWM2M_DATA_CALL_CONNECTED,
  LWM2M_DATA_CALL_STOP,
  LWM2M_DATA_CALL_DISCONNECTED,
  LWM2M_DATA_CALL_RECONFIGURED,  
  LWM2M_DATA_CALL_FAILURE,   
} lwm2m_data_call_event_t;


#ifdef LWM2M_SERVER_OBJECT                                                      
extern uint8_t updt_disabl_flag;
extern uint16_t short_serverId;
#endif

extern uint16_t bs_ssid;
extern uint32_t active_time;

//extern int  inet_pton(int af, const char *src, void *dst);
//extern const char * inet_ntop(int af, const void *addr, char *str, size_t size);


int8_t lwm2m_datacall_start(lwm2m_context_t *lwm2mH, lwm2m_data_call_op_t operation_type, uint16_t *short_serverID, bool start_call);
void lwm2m_datacall_stop(lwm2m_context_t *lwm2mH, lwm2m_data_call_op_t operation_type, uint16_t *short_serverID, bool validate_apn);
void lwm2m_datacall_handle_apn_change(lwm2m_context_t *lwm2mH, uint32_t signals);
void lwm2m_process_pending_location_read_observe(void);
void lwm2m_location_fetch(void);

void lwm2m_handle_location_pmin_update(void);
void lwm2m_free_apn_list(carrier_apn_cfg_t *apn_list);
carrier_apn_cfg_t *update_apn_conn_cfg(lwm2m_context_t *lwm2mH, uint16_t *short_serverID);
carrier_apn_cfg_t *find_dup_apn_entry(carrier_apn_cfg_t* head_apn_cfg, carrier_apn_cfg_t *apn_cfg);
uint32_t lwm2m_transport_selection(uint32_t bindings, uint32_t preferred_mode, uint32_t pdn_type, bool register_trigger, uint32_t reg_trigger_param);
bool data_call_conn_profile_change(uint16_t short_server_id);
void lwm2m_apn_obj_event_notification(void *hndl, uint16_t short_server_id, lwm2m_data_call_event_t event, uint32_t ip_family);
void update_bs_apn_info(lwm2m_context_t * context, uint16_t old_ssid, uint16_t new_ssid);
carrier_apn_cfg_t *populate_default_apn_info(uint16_t short_server_id, bool bs_server);
void lwm2m_process_profile_change(lwm2m_context_t *contextP, lwm2m_server_t *targetP);
bool bootstrap_server_apn_info_match(lwm2m_context_t *lwm2mH, carrier_apn_cfg_t *bs_apn_cfg);


/*
 * object_device.c
 */
lwm2m_object_t * get_object_device(void);
void free_object_device(lwm2m_object_t * objectP);
uint8_t device_change(lwm2m_data_t * dataArray, lwm2m_object_t * objectP);
/*
 * object_firmware.c
 */
lwm2m_object_t * get_object_firmware(void);
void free_object_firmware(lwm2m_object_t * objectP);
uint8_t firmware_change(lwm2m_data_t * dataArray, lwm2m_object_t * objectP);
#ifdef LOCATION_OBJ_SUPPORT
/*
 * object_location.c
 */
lwm2m_object_t * get_object_location(void);
void free_object_location(lwm2m_object_t * object);
void display_location_object(lwm2m_object_t * objectP);
#endif
/*
 * object_test.c
 */
#define TEST_OBJECT_ID 1024
lwm2m_object_t * get_test_object(void);
void free_test_object(lwm2m_object_t * object);
void display_test_object(lwm2m_object_t * objectP);

/*
 * object_connectivity_moni.c
 */
lwm2m_object_t * get_object_conn_m(void);
void free_object_conn_m(lwm2m_object_t * objectP);
uint8_t connectivity_moni_change(lwm2m_data_t * dataArray, 
        lwm2m_object_t * objectP);
int populate_carrier_apn_info_to_conn_m_obj(lwm2m_context_t * context);
int update_carrier_apn_info_to_conn_m_obj(lwm2m_context_t * context);
int load_conn_mon_persistent_info(lwm2m_context_t * context );
int m2m_set_network_bearer_to_conn_m_obj(lwm2m_context_t * context);
/*
 * object_connectivity_stat.c
 */
extern lwm2m_object_t * get_object_conn_s(void);
void free_object_conn_s(lwm2m_object_t * objectP);
extern void conn_s_updateTxStatistic(lwm2m_object_t * objectP,
            uint16_t txDataByte, bool smsBased);

extern void conn_s_updateRxStatistic(lwm2m_object_t * objectP, 
            uint16_t rxDataByte, bool smsBased);
uint8_t connectivity_stat_change(lwm2m_data_t * dataArray,
    lwm2m_object_t * objectP);
/*
 * lwm2mclient.c
 */
void handle_value_changed(lwm2m_context_t* lwm2mH, lwm2m_uri_t* uri, 
     const char * value, size_t valueLength);
void m2m_start_value_change_init (lwm2m_uri_t * uriP ,uint32_t defaultMinPeriod);
void lwm2m_trigger_registration(lwm2m_context_t *lwm2mH);
uint8_t get_battery_level_threshold(void);
/*
 * system_api.c
 */
void init_value_change(lwm2m_context_t * lwm2m);
void deinit_value_change(void);

void system_reboot(void);



/**
 * object_devicecap.c
 */
lwm2m_object_t * get_object_deviceCap(void);
void free_object_devicecap(lwm2m_object_t * objectP);



lwm2m_object_t * get_object_software_mgnt(void);
void free_object_softwaremgnt(lwm2m_object_t * objectP);

/**
 * object_device_host.c
 */
lwm2m_object_t * get_object_host_dev(void);
void free_object_host_device(lwm2m_object_t * object);

/*
 * object_cell_nw_connectivity.c
 */
lwm2m_object_t * get_object_cell_nw_conn(void);
void free_object_cell_nw_conn(lwm2m_object_t * objectP);


/*
 * object_apn_connection.c
 */
lwm2m_object_t * get_object_apn_conn(void);
void clean_apn_conn_object(lwm2m_object_t * objectP);


void m2m_indicate_value_change(qmi_change_ind_type type, char *value);

void check_roaming_status(void);
void lwm2m_handle_in_roaming_signal(void);

lwm2m_context_t * get_lwm2m_context(void);
carrier_apn_cfg_t *get_lwm2m_apn_cfg(void);


qapi_Status_t lwm2m_config_client(qapi_Net_LWM2M_Config_Data_t* config);
qapi_Status_t lwm2m_deconfig_client(void);
uint8_t         lwm2m_get_startup_mode(void);
bool          lwm2m_is_AppRegister_Allowed(void);
//<PORT_TODO> qapi_Device_Info_Hndl_t get_lwm2m_dev_info_hdl(void);
char* process_cfg_utility_open_file(const char* cfg_file, int* bytes_size_ret, int* cfg_fd_ret);

#endif /* LWM2MCLIENT_H_ */
