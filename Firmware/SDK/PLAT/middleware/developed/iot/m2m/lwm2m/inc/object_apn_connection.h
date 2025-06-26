/******************************************************************************

  @file    object_apn_connection.h
  @brief   APN connection profile object interface file
           This file declares the interfaces and data structures if any, of 
           apn connection object implementation
           This object specifies resources to enable a device to connect to an APN.
  ---------------------------------------------------------------------------
  Copyright (c) 2018-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _OBJECT_APN_CONNECTION_H
#define _OBJECT_APN_CONNECTION_H

#include "iotapp_dss_util.h"
#include "lwm2mclient.h"


#define APN_NAME_MAX_LEN        QAPI_DSS_CALL_INFO_APN_MAX_LEN        // Max length of APN.
#define USER_NAME_MAX_LEN       QAPI_DSS_CALL_INFO_USERNAME_MAX_LEN   // Max length of Username.
#define PASSWORD_MAX_LEN        QAPI_DSS_CALL_INFO_PASSWORD_MAX_LEN   // Max length of Password.
#define PROFILE_NAME_MAX_LEN    50                                    // Max length of Profile.
#define MAX_RECONN_LEN          256                                   // Max length of Reconnect schedule.

#define INET4_ADDRSTRLEN  INET_ADDRSTRLEN
//#define INET6_ADDRSTRLEN  46


/* Resource ID's */

#define RES_M_PROFILE_NAME                0    /* Profile name */
#define RES_O_APN                         1    /* APN name */
#define RES_O_AUTO_SELECT_APN             2    /* Auto select APN by device */
#define RES_O_ENABLE_STATUS               3    /* Connection status */
#define RES_M_AUTH_TYPE                   4    /* Authentication type */
#define RES_O_USER_NAME                   5    /* User name */
#define RES_O_SECRET                      6    /* Password */
#define RES_O_RECONN_SCHEDULE             7    /* Reconnect schedule */
#define RES_O_VALIDITY                    8    /* MCC, MNC information */
#define RES_O_CONN_ESTB_TIME              9    /* Connection establishment time */
#define RES_O_CONN_ESTB_RESULT           10    /* Connection establishment result */
#define RES_O_CONN_ESTB_REJECT_CAUSE     11    /* Connection establishment reject cause */
#define RES_O_CONN_END_TIME              12    /* Connection end time */
#define RES_O_TOT_BYTES_SENT             13    /* Total bytes sent on interface */
#define RES_O_TOT_PKTS_SENT              23    /* Total packets sent on interface */
#define RES_O_TOT_BYTES_RECV             14    /* Total bytes recieved on interface */
#define RES_O_IP_ADDR                    15    /* IP address (IPv4 / IPv6) */
#define RES_O_PREFIX_LEN                 16    /* Prefix length for IPv6 */
#define RES_O_SUBNET_MASK                17    /* Subnet mask */
#define RES_O_GATEWAY                    18    /* Gateway */
#define RES_O_PRI_DNS                    19    /* Primary DNS address */
#define RES_O_SEC_DNS                    20    /* Secondary DNS address */
#define RES_O_QCI                        21    /* QCI */
#define RES_O_VENDOR_EXT                 22    /* Vendor specfic extensions */
#define RES_O_PDN_TYPE                   24    /* PDN type */
#define RES_O_APN_CONTROL                25    /* APN control */

typedef struct resource_instance_conn_list_s
{
  struct resource_instance_conn_list_s*   next; 
  uint16_t                resInstId;
  uint8_t                 family;
  uint8_t                 conn_estblsh_time_isValid;
  time_t                  conn_estblsh_time;
  uint8_t                 conn_end_time_isValid;
  time_t                  conn_end_time;
  uint8_t                 conn_estblsh_result_isValid;
  uint16_t                conn_estblsh_result;
  uint8_t                 conn_reject_cause_isValid;
  uint16_t                conn_reject_cause;
} resource_instance_conn_list_t;

/**
* @brief  Structure definition for APN connection profile instance.
*/

typedef struct _apn_conn_profile_instance_
{
  struct _apn_conn_profile_instance_ * next;   // matches lwm2m_list_t::next
  uint16_t    instanceId;                     // matches lwm2m_list_t::id
  void *apn_hndl_v4;                          /* Handle associated with DSS v4 call handle*/
  void *apn_hndl_v6;                          /* Handle associated with DSS v6 call handle.*/
  char profile_name[PROFILE_NAME_MAX_LEN + 1];
  bool apn_name_valid;
  char apn_name[APN_NAME_MAX_LEN + 1];
  bool auto_apn;
  bool enable_status;   // Always TRUE
  uint8_t auth_type;
  char username[USER_NAME_MAX_LEN + 1];
  char secret[PASSWORD_MAX_LEN + 1];
  char reconn_schedule[MAX_RECONN_LEN];
  resource_instance_string_list_t *validity;
  resource_instance_conn_list_t *connection_stats;
  unsigned long long tot_bytes_sent;
  unsigned long long tot_pkts_sent;
  unsigned long long tot_bytes_recv;
  resource_instance_string_list_t *ip_addr;
  resource_instance_string_list_t *prefix_len;
  resource_instance_string_list_t *subnet_mask;
  resource_instance_string_list_t *gateway;
  resource_instance_string_list_t *pri_dns_addr;
  resource_instance_string_list_t *sec_dns_addr;
  uint8_t qci;               // Support not decided.
  objlink_t vendor_ext;
  uint8_t pdn_type;
  int64_t apn_rate_control;
  uint8_t params_set;
} apn_conn_profile_instance_t;

/**
* @brief  Resource value set enum
*/
typedef enum apn_info_set_params_e
{
  PROFILE_NAME_SET                      = 0x01,
  APN_NAME_SET                          = 0x02,
  AUTO_SELECT_SET                       = 0x04,
  AUTH_TYPE_SET                         = 0x08,
  USER_NAME_SET                         = 0x10,
  SECRET_SET                            = 0x20,
  RECONNECT_SET                         = 0x40,
  PDN_TYPE_SET                          = 0x80,
  ENABLE_STATUS_SET                     = 0x100,
} apn_info_set_params_t;

/**
* @brief  Structure definition for input APN connection profile instance.
*/

typedef struct apn_conn_input_params_s
{
  uint8_t params_set;    // Bit mask to determine following values are set or not.
  char apn_name[APN_NAME_MAX_LEN + 1];
  qapi_DSS_Auth_Pref_t auth_type;
  char username[USER_NAME_MAX_LEN + 1];
  char secret[PASSWORD_MAX_LEN + 1];
  uint8_t  reconn_count;
  uint32_t *reconn_schedule;
  uint8_t pdn_type;
  bool enable_status;
} apn_conn_input_params_t;

/**
* @brief  Structure definition for storing peristent values of APN connection 
          profile instance.
*/
typedef struct apn_conn_persistent_instance_s
{
  uint16_t    instanceId;
  uint8_t params_set;    // Bit mask to determine following values are set or not.
  char profile_name[PROFILE_NAME_MAX_LEN + 1];
  bool apn_name_valid;
  char apn_name[APN_NAME_MAX_LEN + 1];
  uint8_t auth_type;
  char username[USER_NAME_MAX_LEN + 1];
  char secret[PASSWORD_MAX_LEN + 1];
  char reconn_schedule[MAX_RECONN_LEN];
  uint8_t pdn_type;
  bool enable_status;
  bool isValid;
} apn_conn_persistent_instance_t;

/**
 * @brief Enum used to identify a PDN type
*/  
typedef enum apn_pdn_type_e
{
  APN_PDN_TYPE_NON_IP = 0x0B,
  APN_PDN_TYPE_IPv4 = 0x02,
  APN_PDN_TYPE_IPv6 = 0x03,
  APN_PDN_TYPE_IPv4v6 = 0x04
}apn_pdn_type_t;

/* Specific to Auth type resource set from server */
#define APN_AUTH_PREF_PAP_CHAP_NOT_ALLOWED  0x03
#define APN_AUTH_PREF_PAP_ONLY_ALLOWED      0x00
#define APN_AUTH_PREF_CHAP_ONLY_ALLOWED     0x01
#define APN_AUTH_PREF_PAP_CHAP_BOTH_ALLOWED 0x02

/**
* @brief  API to retrieve packets sent/ recieved on particular interface.
*
* @param[in]  handle  Handle received after linking successfully with APN Link resource.
* @param[out] pktStats  Packet statistics .
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
qapi_Status_t get_packet_info_by_apn_info(void *hndl,
                                          qapi_DSS_Data_Pkt_Stats_t *pktStats);

/**
* @brief  API to retrieve IP address info for particular interface.
*
* @param[in]  handle  Handle received after linking successfully with APN Link resource.
* @param[out] addr_info  IP Address information .
* @param[in] family  IP family type (IPv4 or IPv6) For Dual IP and NonIP error will be returned.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
qapi_Status_t get_ip_info_by_apn_info(void *hndl,
                                      qapi_DSS_Addr_Info_t *addr_info,
                                      int family);

/**
* @brief  API to retrieve connection failure parameters for particular interface.
*
* @param[in]  handle  Handle received after linking successfully with APN Link resource.
* @param[out] info  Connection related information .(Call end reason and type)
* @param[in] family  IP family type (IPv4/ IPv6 / Non-IP)
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
qapi_Status_t get_apn_conn_failure_reason(void *hndl,
                                          qapi_DSS_CE_Reason_t *conn_reject_cause,
                                           int family);

/**
* @brief  API to retrieve parameters required for Data Call bring up.
*
* @param[in]  value   Object link resource value (Object_id:Instance_id)
* @param[out] params  Data call input parameters.
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
int8_t get_apn_conn_params(objlink_t value, apn_conn_input_params_t *params);

/**
* @brief  API for receiving different data call management events.
*
* @param[in]  handle  Handle will be valid only for register and deregister event.
* @param[in]  value   Object link resource value (Object_id:Instance_id)
* @param[in]  event   Call management event.
* @param[in]  family  IP type (IPv4 / IPv6 ) or Non-IP
*
* @return See Section @xref{hdr:QAPIStatust}. \n
* On success, QAPI_OK (0) is returned. Other value on error.
*/
void apn_info_event_notify(void *hndl, objlink_t value, lwm2m_data_call_event_t event, int family);

/**
 * @fn uint8_t store_apn_info_persistent_info()
 * @brief This function is used to store the apn connection profile into persistent storage
 * 
 * @param targetP pointer to APN conn object instance
 * @param store   to check whether instance stored is valid or not.
 * 
 * @return return error code
 */
int store_apn_info_persistent_info(apn_conn_profile_instance_t * targetP, bool store);

/**
 * @fn uint8_t load_apn_info_persistent_info()
 * @brief This function is used to fetch the apn connection profile from persistent storage
 * 
 * @param objectP pointer to APN conn object
 * 
 * @return return error code
 */
int load_apn_info_persistent_info(lwm2m_object_t * objectP);

/**
 * @brief This function sets default values for APN connection
 * profile object instance 
 * @param instanceP (IN/OUT) Instance whose values to be set.
 * @return none
 */ 
void prv_apn_conn_default_values(apn_conn_profile_instance_t *instanceP);

/**
* @brief  API to check whether object instance of APN link info exists or not..
*
* @param[in]  apn_link  Object link resource value (Object_id:Instance_id)
*
* @return On success - true, on failure - false
*/
bool find_apn_link_info(objlink_t apn_link);

qapi_Status_t get_apn_rate_control(void *hndl,
                                          qapi_DSS_Apn_Rate_Control_Info_t *apn_rate_control);


#endif

