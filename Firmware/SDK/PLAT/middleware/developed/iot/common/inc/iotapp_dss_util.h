/******************************************************************************
 * @file    iotapp_dss_util.h
 * @author  Qualcomm Technologies Ltd.
 * @brief   Utitilies to establish and maintain datapath
 *
 *****************************************************************************/
/*===========================================================================
  Copyright (c) 2017-2018  by Qualcomm Technologies, Inc.  All Rights Reserved.
 
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
 ======================================================================*/
/*======================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  
 *
 *
 * when         who     what, where, why
 * ----------   ---     ------------------------------------------------
 ======================================================================*/  
#ifndef IOT_DSS_API_H_
#define IOT_DSS_API_H_
#include <stdbool.h>
#include "iotapp_ps_wrapper.h"

#define IOT_DSS_DATACALL_UP           0x01 
#define IOT_DSS_DATACALL_DOWN         0x02
#define IOT_DSS_NAS_DOWN_IND          0x04
#define IOT_DSS_NAS_UP_IND            0x08
#define IOT_DSS_DATACALL_FAILURE      0x10
#define IOT_DSS_MAX_RETRIES           0x20

#ifndef ESUCCESS
#define ESUCCESS 0
#endif
#ifndef EFAILURE
#define EFAILURE -1
#endif

#define PRV_ADDRSTRLEN  48

typedef void *iot_dss_call_hndl_t;
typedef void (*iot_dss_status_cb_t) (iot_dss_call_hndl_t dss_hndl, void *user_data, uint8_t call_status);

typedef DSS_Data_Pkt_Stats_t qapi_DSS_Data_Pkt_Stats_t;
typedef DSS_Apn_Rate_Control_Info_t qapi_DSS_Apn_Rate_Control_Info_t;

/* structure defines paramaters to iot_dss_register api */
typedef struct _iot_dss_regparams_
{
  iot_dss_status_cb_t dss_status_cb;
  char * apn;
  char *user_name;
  char *password; 
  qapi_DSS_Auth_Pref_t auth_type;
  uint8_t apn_class;
  uint8_t apn_profile_index;
  void *user_data;
  uint32_t retry_timeout;
  uint32_t retry_exponent_val;
  uint32_t *retry_timeout_lst;
  uint32_t retry_timeout_lst_len; 
  uint8_t ip_family;
  uint8_t profile_ip_family;
} iot_dss_regparams_t;

/**
 * @fn uint8_t iot_dss_init(void)
 * @brief This function is used to initialize iotapp dss utils
 * @return On success ESUCCESS (0), On failure EFAILURE(-1)
 */
int iot_dss_init(void);

/**
 * @brief Register IOT DSS handle
 * @param params IOT DSS parameters
 * @return  On success iot_dss_call_hndl_t , On failure NULL
 */
iot_dss_call_hndl_t iot_dss_register(iot_dss_regparams_t *params);

 /**
 * @brief Register IOT DSS handleer
 * @param callhdl Handler to be deregistered
 */
void iot_dss_deregister(iot_dss_call_hndl_t callhdl);

/**
 * @brief Start datacall
 * @param callhdl IOT DSS callhandle
 * @return ESUCCESS or EFAILURE
 */
int iot_dss_start_datacall(iot_dss_call_hndl_t callhdl);

/**
 * @brief Stop datacall
 * @param callhdl IOT DSS handle
 */
void iot_dss_stop_datacall(iot_dss_call_hndl_t callhdl);

/**
 * @brief This function is used to get id addr for a particular datacall
 * @param callhdl IOT DSS handle
 * @param[out] ipcount number of IPs
 * @return On success dss_addr_info_t*, on failure NULL
 */
qapi_DSS_Addr_Info_t *iot_dss_get_ip_info_by_hndl(iot_dss_call_hndl_t callhdl,  int *ipcount);

/**
 * @brief This function is used to get all ip related information for given apn
 * @param[out] number of IPs in addr_info
 * @return On success dss_addr_info_t *, on failure NULL
 */
qapi_DSS_Addr_Info_t* iot_dss_ip_info_by_apn(char *apn, int *ipcount, int family);

/**
 * @fn int iotapp_dss_get_packetstats(int)
 * @brief This function is used to get the packet stats
 * @return  On success ESUCCESS, on Failure EFAILURE
 */
int iotapp_dss_get_packetstats(qapi_DSS_Data_Pkt_Stats_t *pktStats);

/**
 * @brief This function is used to get the data interface name
 * @return  QAPI_OK - Data interface name was returned successfully. 
            QAPI_ERROR - Data interface name was not returned successfully.
 */
int iotapp_dss_get_iface_name(iot_dss_call_hndl_t callhdl, char *buf, int length);

/**
 * @brief Retrieve the DSS Netctrl data call handle associated with the call
 * @param iotapp_ctx_hndl IoT application context 
 */
void *get_data_call_hndl(void *iotapp_ctx_hndl);


#endif
