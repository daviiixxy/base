#ifndef _IOTAPP_PS_WRAPPER_H
#define _IOTAPP_PS_WRAPPER_H

#include <stdbool.h>
#include "ps_lib_api.h"

#define PRV_IMSI_MAX_LEN		16 //15 + 1 Max length of imsi + 1 for '\0''
#define IOTAPP_PS_INFO_BUF_SIZE	256
#define MAX_LEN_VAL				4
#define SMS_MAX_ADDRESS_LENGTH	40

#define PS_MAX_APN_LEN          100
#define PS_MAX_AUTH_STR_LEN     20

/* start <PORT> replace with DSS equivalent once available */
#define QAPI_DSS_CALL_INFO_USERNAME_MAX_LEN  PS_MAX_AUTH_STR_LEN  /**< Maxiumum length of the username. */
#define QAPI_DSS_CALL_INFO_PASSWORD_MAX_LEN  PS_MAX_AUTH_STR_LEN  /**< Maxiumum length of the password. */
#define QAPI_DSS_CALL_INFO_APN_MAX_LEN       PS_MAX_APN_LEN  /**< Maxiumum length of the APN. */

#define DATA_CALL_INFO_APN_MAX_LEN			PS_MAX_APN_LEN
#define DATA_CALL_INFO_USERNAME_MAX_LEN 	PS_MAX_AUTH_STR_LEN
#define DATA_CALL_INFO_PASSWORD_MAX_LEN		PS_MAX_AUTH_STR_LEN

#define WMS_ADDRESS_DIGIT_MAX_V01 21

#define SUCC 0
#define ERR  -1

#define START_MAPPED_CALL_SUCCESS 1
#define STOP_MAPPED_CALL_SUCCESS 2
#define MAXHANDLE 8
#define CE_REASON_UNKNOWN -1
#define INVALID_HANDLE 0xff
#define DSS_PS_MAX_APN_LEN          100
/*
 * IP address info
*/
#define DSS_MAX_IP_ADDR_LEN         16
#define DSS_PDN_MAX_NW_ADDR_NUM     4
#define MAX_CALL_QUEUE_SIZE    4
#define CALL_START_REQ_BIT  1
#define CALL_START_CNF_BIT  2
#define CALL_START_IND_BIT 3
#define CALL_STOP_REQ_BIT 5
#define CALL_STOP_CNF_BIT 6
#define CALL_STOP_IND_BIT 7
#define DATACALL_IND_SIG      (0x10)
#define PS_ASYNC_IND_SIG	  (0x20)

#define MAX_PROFILE_LIST_SIZE 11

/** @addtogroup qapi_status
@{ */
typedef int32_t qapi_Status_t;


typedef enum qapi_DSS_Auth_Pref_e
{
  QAPI_DSS_AUTH_PREF_PAP_CHAP_NOT_ALLOWED_E = 0x00,  /**< Neither of the authentication protocols (PAP, CHAP) are allowed. */
  QAPI_DSS_AUTH_PREF_PAP_ONLY_ALLOWED_E,             /**< Only PAP authentication protocol is allowed. */
  QAPI_DSS_AUTH_PREF_CHAP_ONLY_ALLOWED_E,            /**< Only CHAP authentication protocol is allowed. */
  QAPI_DSS_AUTH_PREF_PAP_CHAP_BOTH_ALLOWED_E         /**< Both PAP and CHAP authentication protocols are allowed. */
} qapi_DSS_Auth_Pref_t;

/** Call end reason type. */
typedef enum qapi_DSS_CE_Reason_Type_e
{
  QAPI_DSS_CE_TYPE_UNINIT_E  = -2,                 /**< No specific call end reason was received from the modem. */
  QAPI_DSS_CE_TYPE_INVALID_E = 0XFF,               /**< No valid call end reason was received. */
  QAPI_DSS_CE_TYPE_MOBILE_IP_E = 0x01,             /**< Mobile IP error. */
  QAPI_DSS_CE_TYPE_INTERNAL_E = 0x02,              /**< Data services internal error was sent by the modem. */
  QAPI_DSS_CE_TYPE_CALL_MANAGER_DEFINED_E = 0x03,  /**< Modem Protocol internal error. */
  QAPI_DSS_CE_TYPE_3GPP_SPEC_DEFINED_E = 0x06,     /**< 3GPP specification defined error. */
  QAPI_DSS_CE_TYPE_PPP_E = 0x07,                   /**< Error during PPP negotiation. */
  QAPI_DSS_CE_TYPE_EHRPD_E = 0x08,                 /**< Error during EHRPD. */
  QAPI_DSS_CE_TYPE_IPV6_E = 0x09                   /**< Error during IPv6 configuration. */
} /** @cond */qapi_DSS_CE_Reason_Type_t/** @endcond */;

typedef struct qapi_DSS_CE_Reason_s
{
  qapi_DSS_CE_Reason_Type_t reason_type; /**<  Discriminator for reason codes. */
  int reason_code;                       /**<  Overloaded cause codes discriminated by reason type. */
} /** @cond */qapi_DSS_CE_Reason_t/** @endcond */;

typedef struct qapi_DSS_Addr_s
{
  char valid_addr; /**< Indicates whether a valid address is available. */   
  union qapi_dss_ip_address_u /** Union of DSS IP addresses. */
  {
    uint32_t v4;            /**< Used to access the IPv4 address. */
    uint32_t v6_addr64[4];  /**< Used to access the IPv6 address. */
    uint32_t v6_addr32[4];  /**< Used to access the IPv6 address as four 32-bit integers. */
    uint16_t v6_addr16[8];  /**< Used to access octets of the IPv6 address. */
    uint8_t  v6_addr8[16];  /**< Used to access octets of the IPv6 address as 16 8-bit integers. */
  } addr;                   /**< Union of DSS IP addresses. */
} /** @cond */qapi_DSS_Addr_t/** @endcond */;

/** IP address-related information. */
typedef struct qapi_DSS_Addr_Info_s
{
  qapi_DSS_Addr_t   iface_addr_s; /**< Network interface address. */
  unsigned int      iface_mask;   /**< Interface subnet mask. */
  qapi_DSS_Addr_t   gtwy_addr_s;  /**< Gateway server address. */
  unsigned int      gtwy_mask;    /**< Gateway subnet mask. */
  qapi_DSS_Addr_t   dnsp_addr_s;  /**< Primary DNS server address. */  
  qapi_DSS_Addr_t   dnss_addr_s;  /**< Secondary DNS server address. */
} /** @cond */qapi_DSS_Addr_Info_t/** @endcond */;

/** Packet statistics. */
typedef struct DSS_Data_Pkt_Stats_s
{
  unsigned long pkts_tx;          /**< Number of packets transmitted. */
  unsigned long pkts_rx;          /**< Number of packets received. */
  long long     bytes_tx;         /**< Number of bytes transmitted. */
  long long     bytes_rx;         /**< Number of bytes received. */
  unsigned long pkts_dropped_tx;  /**< Number of transmit packets dropped. */
  unsigned long pkts_dropped_rx;  /**< Number of receive packets dropped. */
} /** @cond */DSS_Data_Pkt_Stats_t/** @endcond */;

typedef struct DSS_Apn_Rate_Control_Info_s
{
  uint32_t uplink_time_unit;          /**< Represents the time unit that the uplink data is restricted */
  uint32_t max_uplink_rate;        /**<   Maximum Number.of the uplink packets that can be sent within the uplink time limit*/
} DSS_Apn_Rate_Control_Info_t;

typedef enum DSS_Net_Evt_e
{
  QAPI_DSS_EVT_INVALID_E = 0x00,   /**< Invalid event. */
  QAPI_DSS_EVT_NET_IS_CONN_E,      /**< Call connected. */
  QAPI_DSS_EVT_NET_NO_NET_E,       /**< Call disconnected. */
  QAPI_DSS_EVT_NET_RECONFIGURED_E, /**< Call reconfigured. */
  QAPI_DSS_EVT_NET_NEWADDR_E,      /**< New address generated. */
  QAPI_DSS_EVT_NET_DELADDR_E,      /**< Delete generated. */
  QAPI_DSS_EVT_NIPD_DL_DATA_E,     /**< Non-IP downlink data. */
  QAPI_DSS_EVT_MAX_E
} /** @cond */DSS_Net_Evt_t/** @endcond */;

/* end <PORT_TODO> */


/* since only NB is supported these values will be hardcoded to srvc_type*/
#define IOTAPP_CIOT_MODE_NB1	2
#define IOTAPP_LTE_NB_IOT		7
#define IOTAPP_LTE				1

/** Call parameter identifier.  */
typedef enum DSS_Call_Info_Enum_e
{
  QAPI_DSS_CALL_INFO_MIN_E = 0x00,
  QAPI_DSS_CALL_INFO_APN_NAME_E,           /**< APN name. */
  QAPI_DSS_CALL_INFO_USERNAME_E,           /**< APN user name. */
  QAPI_DSS_CALL_INFO_PASSWORD_E,           /**< APN password. */
  QAPI_DSS_CALL_INFO_AUTH_PREF_E,          /**< Authentication preference. */
  QAPI_DSS_CALL_INFO_IP_VERSION_E,         /**< Preferred IP family for the call. */
  QAPI_DSS_CALL_INFO_MAX_E
} /** @cond */DSS_Call_Param_Identifier_t/** @endcond */;

/** Call status.  */
typedef enum DSS_Call_Status_Enum_e
{
  DSS_CALL_UNKNOWN = 0x00,
  DSS_CALL_START,           /**Call is up**/
  DSS_CALL_STOP             /**Call is down**/
} DSS_Call_Status_t;

#if 0
typedef enum PS_Attach_Trigger_State_Enum_e
{
  PS_TRIGGER_STATE_INVALID = 0x00,
  PS_TRIGGER_STATE_DETACH_REQUIRED_E,
  PS_TRIGGER_STATE_DETACH_TRIGGERED_E,
  PS_TRIGGER_STATE_ATTACH_REQUIRED_E,
  PS_TRIGGER_STATE_ATTACH_TRIGGERED_E
} PS_Attach_Trigger_State_t;
#endif

/** @name IP Versions
@{ */

#define QAPI_DSS_IP_VERSION_NON_IP 2   /**< IP version Non IP. */
#define QAPI_DSS_IP_VERSION_4      4   /**< IP version v4. */
#define QAPI_DSS_IP_VERSION_6      6   /**< IP version v6. */
#define QAPI_DSS_IP_VERSION_4_6    10   /**< IP version v4v6. */

/** @} */ /* end_namegroup */

#define IOTAPP_DEVICE_INFO_APN_NAME_MAX PS_MAX_APN_LEN
#define IOTAPP_DEVICE_INFO_USERNAME_MAX	PS_MAX_AUTH_STR_LEN
#define IOTAPP_DEVICE_INFO_PASSWORD_MAX	PS_MAX_AUTH_STR_LEN
#define REQ_TYPE_OBJ_11 0

/* Profile action required based on search result.*/
typedef enum
{
  PROFILE_ACTION_ENUM_MIN_ENUM_VAL = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  PROFILE_NO_ACTION = 0x00, 
  PROFILE_MODIFY = 0x01, 
  PROFILE_CREATE = 0x02, 
  PROFILE_ACTION_ENUM_MAX_ENUM_VAL = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
} profile_action_enum;

typedef enum {
  IOTAPP_WDS_PDP_TYPE_ENUM_MIN_ENUM_VAL_V01 = -0x7F, /**< To force a 8 bit signed enum.  Do not change or use*/
  IOTAPP_WDS_PDP_TYPE_PDP_PPP_V01 = 0x00, /**<  PDP-PPP \n  */
  IOTAPP_WDS_PDP_TYPE_PDP_IPV4_V01 = 0x01, /**<  PDP-IP (IPv4) \n  */
  IOTAPP_WDS_PDP_TYPE_PDP_IPV6_V01 = 0x02, /**<  PDP-IPv6 \n  */
  IOTAPP_WDS_PDP_TYPE_PDP_IPV4V6_V01 = 0x03, /**<  PDP-IPv4 and IPv6 \n  */
  IOTAPP_WDS_PDP_TYPE_PDP_UNUSED = 0x04,
  IOTAPP_WDS_PDP_TYPE_PDP_NON_IP_V01 = 0x05, /**<  PDP-NON IP   */
  IOTAPP_WDS_PDP_TYPE_ENUM_MAX_ENUM_VAL_V01 = 0x7F /**< To force a 8 bit signed enum.  Do not change or use*/
}iotapp_wds_pdp_type_enum_v01;

typedef iotapp_wds_pdp_type_enum_v01 qapi_Device_Info_PDP_Type_e;

typedef struct{
  bool pdp_type_valid;
  qapi_Device_Info_PDP_Type_e pdp_type;
  bool apn_name_valid;
  char apn_name[IOTAPP_DEVICE_INFO_APN_NAME_MAX];
} mandatory_res_changed_t;

typedef mandatory_res_changed_t mandatory_res_t;

typedef struct profile_params_s
{
  uint16_t instanceID;                                /* Object 11 instance id */
  profile_action_enum type;                           /* Profile creation/ modification  */
  char apn_name[IOTAPP_DEVICE_INFO_APN_NAME_MAX]; 	  /* APN name passed */
  bool disable_status;                                 /* APN is enabled or not*/
  uint8_t username_valid;                             /* Username is passed or not */
  char username[IOTAPP_DEVICE_INFO_USERNAME_MAX];	  /* Username passed */
  uint8_t password_valid;                             /* Password is passed or not */
  char password[IOTAPP_DEVICE_INFO_PASSWORD_MAX]; 	  /* Password passed */
  uint8_t authentication_preference_valid;            /* Auth type is passed or not */
  uint8_t authentication_preference;                  /* Auth type passed*/
  iotapp_wds_pdp_type_enum_v01 pdp_type;              /* PDP type */
  bool modified_pdp;                                  /* Modified pdp field is set or not */
  iotapp_wds_pdp_type_enum_v01 old_pdp_type;          /* Old pdp type */
  uint8_t req_type;                                   /* Request from Create/Write/Set operation */
  bool delay_timer;                                   /* Delay */
  uint16_t ssid;                                      /* SSID for create/write operation */
  uint8_t token_len;                                  /* Token length for sending message response */
  uint8_t token[8];                                   /* Token  for sending message response */
}profile_params_t;


typedef struct {

  uint8_t network_type;

  uint8_t lte_mode;

  uint8_t ciot_mode;

} network_bearer_t;

typedef enum {
	IOTAPP_PS_NETWORK_IND_E,
	IOTAPP_PS_ROAMING_E,
	IOTAPP_PS_WMS_EVENT_REPORT_E,
	IOTAPP_PS_ACTIVE_TIMER_E,
	IOTAPP_PS_PSM_TIMER_E,
	IOTAPP_PS_MCC_E,
	IOTAPP_PS_MNC_E,
	IOTAPP_PS_CELL_ID_E,
	IOTAPP_PS_4G_SIG_STRENGTH_E,
	IOTAPP_PS_LINK_QUALITY_E,
	IOTAPP_DEVICE_INFO_LINK_QUALITY_E,
	IOTAPP_DEVICE_INFO_4G_SIG_STRENGTH_E,
	IOTAPP_DEVICE_INFO_MNC_E,
	IOTAPP_DEVICE_INFO_MCC_E,
	IOTAPP_DEVICE_INFO_CELL_ID_E,
	IOTAPP_DEVICE_INFO_PS_DETACH_E,
	IOTAPP_DEVICE_INFO_PS_ATTACH_E,
	IOTAPP_PS_LAST_ID
} iotapp_Device_Info_ID_t;
	
typedef enum {
	IOTAPP_PS_BOOL,
	IOTAPP_PS_INT,
	IOTAPP_PS_BUFFER,
	IOTAPP_PS_INVAL
} iotapp_Device_Info_Type_t;

#define INT_STR_SIZE 11 /* 10 + 1 */

typedef struct {
  iotapp_Device_Info_ID_t id; /**< Required information ID. */
  iotapp_Device_Info_Type_t info_type; /**< Response type. */
/** Union of values. */
  union {
/** Union of buffer values. */
    struct {
      char buf[IOTAPP_PS_INFO_BUF_SIZE]; /**< Response buffer. */
      uint32_t len; /**< Length of the response string. */
    }valuebuf;    
    //int64_t valueint; /**< Response integer value. */
    int32_t valueint; /**< Response integer value. */
    bool valuebool; /**< Response Boolean value.*/
/** Union of integer array values. */
    struct 
    {
      int buf[MAX_LEN_VAL]; /**< Response type: integer array. */
      uint32_t len; /**< Length of the array. */
    }valint; 
    //void* device_info_extn; /**< Extented parameter */
  }u;   
}iotapp_Device_Info_t;

/* structure defines the data call details */
typedef struct DSS_Call_Param_s
{
  char *apn;
  char *user_name;
  char *password; 
  CmiSecurityProtocol auth_type;
  uint8_t apn_len;
  uint8_t user_name_len;
  uint8_t password_len;
  CmiPsPdnType ip_family; 
  CmiPsPdnType profile_ip_family;
} DSS_Call_Param_t;

typedef void *DSS_Evt_Payload_t;
typedef UINT8 DSS_Hndl_t;


/** Callback function prototype for DSS events.

   @param[in] hndl Handle to which this event is associated.
   @param[in] user_data Application-provided user data.
   @param[in] evt Event identifier.
   @param[in] payload_ptr Pointer to associated event information.

   @return
   None.
   @newpage   */

typedef void (*DSS_Net_Ev_CB_t)
(
  DSS_Hndl_t         hndl,          /**< Handle for which this event is associated. */
  void               *user_data,     /** Application-provided user data. */
  DSS_Net_Evt_t      evt,           /** Event identifier. */
  DSS_Evt_Payload_t  payload_ptr    /** Associated event information. */
); 


typedef struct handle
{
    UINT8 cid; 
	UINT8 callBitMask;
    DSS_Net_Ev_CB_t cbfunc;
    void *userData;
    UINT8 isOccupied;
	INT16 end_reason;
 }handleContext;

typedef struct callInd
{
   UINT8 handle;
   DSS_Call_Status_t callStatus;
}call_ind;

typedef struct queue{
	UINT8 curr_idx;	
	call_ind indications[MAX_CALL_QUEUE_SIZE];
}call_ind_queue;

typedef struct {
	UINT8 count;
	iotapp_Device_Info_t *indications[MAX_CALL_QUEUE_SIZE];
}async_ind_queue;

extern handleContext hdlArr[];
extern network_bearer_t srvc_type;
extern bool bPsmEventReg;

bool iotapp_get_service_status(void);

typedef enum {
	PARAM_INVAL,
	PARAM_ROAM_STATUS,		// to get roaming status
	PARAM_CELL_ID,			// to get cell id information
	PARAM_MCC,				// to get mcc information
	PARAM_MNC,				// to get mnc information
	PARAM_SIGNAL_STRENGTH	// to get the signal strength informationPARAM
} ue_info_t;

int64_t nas_get_ue_info(ue_info_t info);

typedef struct {
	uint32_t periodic_update_timer;
	uint32_t active_timer;
	bool periodic_update_timer_valid;
	bool active_timer_valid;
	bool psm_enabled_valid;
	uint8_t psm_enabled;
}psm_get_cfg_params_resp_msg_v01;

typedef profile_params_t apn_profile_t;

/* Profile search request structure.*/
typedef mandatory_res_t profile_search_request_t;


/* Profile search response structure.*/
typedef struct{
  qapi_Status_t rc_code;    /* Return code SUCC for success, ERR_* for failure */
  profile_action_enum search_result;    /* No Action, Create or Modify */
  bool old_pdp_type_valid;  /* Old PDP type field is set or not.*/
  uint8_t old_pdp_type;     /* If search result is Modify and PDP type is changed then 
                               this value is set.*/
} profile_search_response_t;


typedef psm_get_cfg_params_resp_msg_v01 psm_set_cfg_params_req_msg_v01;

int iotapp_find_and_update_profile(char *changed_apn_name, char *apn_name);
uint8_t *get_msisdn_frm_uim(void);


typedef void (*iotapp_PSEvent_cb)(iotapp_Device_Info_t *);
void register_ps_events(iotapp_PSEvent_cb fn, bool asyncIndNeeded);
int16_t nas_get_network_time(bool *dst);
int iotapp_Device_Info_Get_v2(iotapp_Device_Info_ID_t id, iotapp_Device_Info_t *info);
int8_t iotapp_sms_set_event_report_req(void);

int DSS_Get_CID(DSS_Hndl_t callhandle);

qapi_Status_t DSS_Init(void);
qapi_Status_t DSS_Get_Data_Srvc_Hndl(DSS_Net_Ev_CB_t user_cb_fn, void *user_data, DSS_Hndl_t *hndl);
qapi_Status_t DSS_Set_Data_Call_Param(DSS_Hndl_t hndl, DSS_Call_Param_t *info);
qapi_Status_t DSS_Start_Data_Call(DSS_Hndl_t hndl);
qapi_Status_t DSS_Stop_Data_Call(DSS_Hndl_t hndl);
//qapi_Status_t DSS_Get_IP_Addr_Count(DSS_Hndl_t hndl, UINT32* ip_addr_cnt);
qapi_Status_t DSS_Rel_Data_Srvc_Hndl(DSS_Hndl_t hndl);
qapi_Status_t DSS_Get_Subnet_Addr(PsIpAddr *v4addr, PsIpAddr *subnetAddr);
qapi_Status_t DSS_Get_IP_Addr(DSS_Hndl_t hndl, PsBearerCtxDynParam  *info_ptr, UINT32 *ip_addr_count, PsIpAddr *subnetAddr);
qapi_Status_t DSS_Get_Pkt_Stats(DSS_Hndl_t hndl, PktStat *dss_data_stats);
qapi_Status_t DSS_Get_Call_End_Reason(DSS_Hndl_t hndl, qapi_DSS_CE_Reason_t *ce_reason);
qapi_Status_t DSS_Get_Apn_Rate_Control(DSS_Hndl_t hndl, PsApnRateCtrlParam *apn_rate_control_info);
qapi_Status_t DSS_Get_Splmn_Rate_Control(DSS_Hndl_t hndl, uint32_t *splmn_rate_control);
qapi_Status_t DSS_Get_Link_Mtu(DSS_Hndl_t hndl, uint32_t *mtu);


//DSS call handling utility functions for bitmask
void set_bit(UINT8 *num, UINT8 bitToSet);
void reset_bit(UINT8 *num, UINT8 bitToReset);
UINT8 get_bit(UINT8 num, UINT8 bitToGet);
void reset_bitmask(UINT8 hndl, DSS_Call_Status_t call_state);

qapi_Status_t DSS_Add_Call_Ind_To_Queue(DSS_Hndl_t hndl, DSS_Call_Status_t call_status);
qapi_Status_t DSS_Trigger_Call_Ind(void);

//APN profile related APIs'
qapi_Status_t iotapp_get_profile_list(char *apn, UINT8 *profile_count);
qapi_Status_t iotapp_delete_profile(CmiPsPdnType pdn_type, UINT8 profile_count);
qapi_Status_t iotapp_create_profile(apn_profile_t *param);
qapi_Status_t iotapp_search_profile(profile_search_request_t *params, profile_search_response_t *response);
qapi_Status_t iotapp_auth_modify(apn_profile_t *param, UINT8 profile_count);
void init_default_bearer_params(SetAttachBearerParams *attachBearerInfo, UINT8 pdnType);
qapi_Status_t iotapp_modify_profile (apn_profile_t *param, uint8_t cmd_id, mandatory_res_changed_t c_info);
	
static inline char *get_imsi_frm_physical_slot()
{
	CHAR *imsi = malloc(PRV_IMSI_MAX_LEN);

	if ((imsi != NULL) && (0 != appGetImsiNumSync(imsi))) return NULL;
	return imsi;
}

static inline int16_t nas_get_signal_strength()
{
	BasicCellListInfo bcListInfo;
	if (CMS_RET_SUCC != appGetECBCInfoSync(0,1,8,&bcListInfo)) return -1;
	if (bcListInfo.sCellPresent == 0) return -1;
	return bcListInfo.sCellInfo.rsrp;
}

static inline uint8_t *iotapp_get_smsc_address()
{
	UINT8 *smsc_addr = calloc(1,SMS_MAX_ADDRESS_LENGTH);
	if (smsc_addr != NULL && CMS_RET_SUCC != appGetsmscaddress(smsc_addr))
	{
		free(smsc_addr);
		return NULL;
	}
	return (uint8_t *)smsc_addr;
}

static inline int8_t iotapp_set_smsc_address(uint8_t *sms_addr)
{
	if (CMS_RET_SUCC != appSetsmscaddress(sms_addr, strlen((const char *)sms_addr), 0)) return -1;
	return 0;
}

static inline psm_get_cfg_params_resp_msg_v01 *get_psm_params()
{
	UINT8 mode;
	UINT32 tau = 0, active = 0;
	psm_get_cfg_params_resp_msg_v01 *ret = NULL;
	if (CMS_RET_SUCC != appGetPSMSettingSync(&mode, &tau, &active)) return ret;
	ret = calloc(1, sizeof(psm_get_cfg_params_resp_msg_v01));
	if (ret != NULL) {
		ret->periodic_update_timer = tau;
		ret->active_timer_valid = ret->periodic_update_timer_valid = true;
		ret->active_timer = active;
	}
	return ret;
}
#define DISABLE_PSM		0
#define ENABLE_PSM 		1
#define ENABLE_EDRX		1
#define EDRX_NB_IOT		5
static inline int8_t set_psm_params(psm_get_cfg_params_resp_msg_v01 * params)
{
	UINT8 mode = ENABLE_PSM;
	UINT32 tau = 0, active = 0;
	//if (CMS_RET_SUCC != appGetPSMSettingSync(&mode, &tau, &active)) return -1;
	if (params->active_timer_valid) active = params->active_timer;
	if (params->periodic_update_timer_valid) tau = params->periodic_update_timer;
	if (params->psm_enabled_valid) mode = (params->psm_enabled) ? ENABLE_PSM : DISABLE_PSM;
	if (CMS_RET_SUCC != appSetPSMSettingSync(mode, tau, active)) return -1;
	return 0;
}

static inline void register_psm_cfg_change()
{
	bPsmEventReg = TRUE;
}

static inline int8_t iotapp_nas_set_erdx_params(uint8_t value)
{
	if (CMS_RET_SUCC != appSetEDRXPtwSettingSync(ENABLE_EDRX, EDRX_NB_IOT, value))
		return -1;
	return 0;
}

static inline int8_t iotapp_nas_get_edrx_params(uint8_t *value)
{
	if (value == NULL) return -1;
	if (CMS_RET_SUCC != appGetEDRXPtwSettingSync(value))
		return -1;
	return 0;
}

static inline void iotapp_set_sys_sel_pref(iotapp_Device_Info_ID_t id, uint8_t len, void * buff)
{
	bool attachMode;
	if (id == IOTAPP_DEVICE_INFO_PS_ATTACH_E)
		attachMode = true;
	else if (id == IOTAPP_DEVICE_INFO_PS_DETACH_E)
		attachMode = false;
	else
		return;
	appSetGPRSAttachedsync(attachMode);
}

static inline int iotapp_search_apn_profile(void *request, profile_search_response_t *response)
{
	if (SUCC != iotapp_search_profile((profile_search_request_t *)request, response))
		return -1;
	return 0;
}

static inline int iotapp_create_apn_profile(void *param, uint8_t cmd_id)
{
	if (SUCC != iotapp_create_profile((apn_profile_t *)param))
		return -1;
	return 0;
}

static inline bool iotapp_get_apn_disable_status(uint8_t pdp_type, char *apn_name)
{
	uint8_t status = 0;
	if (CMS_RET_SUCC != appGetAPNDisableSync(pdp_type, apn_name, &status))
		return FALSE;
	return (bool)status;
}

static inline int iotapp_modify_apn_profile(void *param, uint8_t cmd_id, mandatory_res_changed_t c_info)
{
	if (SUCC != iotapp_modify_profile((apn_profile_t *)param, cmd_id, c_info))
		return -1;
	return 0;
}

#endif //_IOTAPP_PS_WRAPPER_H
