/******************************************************************************

  @file    object_cell_nw_connectivity.h
  @brief   API's related to Cellular network connectivity object 
           This object specifies resources to enable a device to connect to a 3GPP or 3GPP2 bearer, 
		   including GPRS/EDGE, UMTS, LTE, NB-IoT, SMS. 
  ---------------------------------------------------------------------------
  Copyright (c) 2019 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _OBJECT_CELL_NW_CONNECTIVITY_H
#define _OBJECT_CELL_NW_CONNECTIVITY_H

//#include "wireless_messaging_service_v01.h"

/* Resource ID's */

#define  RES_O_SMSC_ADDR                  0  /**< SMSC address. */
#define  RES_O_DISABLE_RADIO_PERIOD       1  /**< Disable Radio period. */
#define  RES_O_MOD_ACTIVATION_CODE        2  /**< Module activation code. */
#define  RES_O_OBJ_10_VENDOR_EXT          3  /**< Vendor specific extension. */
#define  RES_O_PSM_TIMER                  4  /**< PSM timer type. */
#define  RES_O_ACTIVE_TIMER               5  /**< Active timer. */
#define  RES_O_SERVING_PLMN_RATE_CONTROL  6  /**< Serving PLMN Rate control. */
#define  RES_O_EDRX_IU                    7  /**< eDRX parameters for Iu mode. */
#define  RES_O_EDRX_WB_S1                 8  /**< eDRX parameters for WB S1 mode */
#define  RES_O_EDRX_NB_S1                 9  /**< eDRX parameters for NB S1 mode. */
#define  RES_O_EDRX_AGB                   10  /**< eDRX parameters for A/Gb mode. */
#define  RES_M_ACTIVATED_PROF_NAME        11  /**< Activated profile names. */

typedef struct _act_profile_name_info_s
{
  struct _act_profile_name_info_s *next; 
  uint16_t                resInstId;
  uint32_t link_info; 
} act_profile_name_info_s;

/**
* @brief  Structure definition for cellular network connectivity instance.
*/
typedef struct _cell_nw_conn_instance_
{
  struct cell_nw_conn_instance_t * next;   // matches lwm2m_list_t::next
  uint16_t    instanceId;                     // matches lwm2m_list_t::id
  char smsc_addr[WMS_ADDRESS_DIGIT_MAX_V01 + 1];
  uint32_t    disable_radio_period;
  objlink_t   vendor_ext;
  uint32_t    psm_timer;
  uint32_t    active_timer;
  uint32_t splmn_rate_control;
  uint8_t     edrx_param_nbs1_mode;
  act_profile_name_info_s *act_prof_name;
  timer_type        ps_attach_timer;
} cell_nw_conn_instance_t;

typedef struct _cell_nw_conn_persistent_info_
{
  char smsc_addr[WMS_ADDRESS_DIGIT_MAX_V01 + 1];
  uint32_t    disable_radio_period;
  objlink_t   vendor_ext;
  uint32_t    psm_timer;
  uint32_t    active_timer;
  uint8_t     edrx_param_nbs1_mode;
  bool isValid;
} cell_nw_conn_persistent_info_t;

int load_cell_nw_conn_persistent_info(lwm2m_object_t * objectP);
uint8_t cell_nw_change(lwm2m_data_t * dataArray,lwm2m_object_t * objectP);

qapi_Status_t get_splmn_rate_control_by_apn_info(void *hndl,uint32_t *splmn_rate_control);


#endif
