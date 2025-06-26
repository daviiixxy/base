/******************************************************************************

  @file    object_connectivity_moni.h
  @brief   Connectivity monitoring Object Interface File 
 
           This file declares the interfaces and data structures if any, of 
           connectivity monitoring object implementation
  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef OBJ_CONNECTIVITY_MON_H
#define OBJ_CONNECTIVITY_MON_H

//#include "iotapp_qmi_internal.h"
#include "liblwm2m.h"


//TODO: Need to take the APN as per Carrier requirement
#define VALUE_APN_1		"ims.carrier.com"
#define VALUE_APN_2         	"cda.vodafone.de"

#define MAX_AVAIL_BEARER	15

#define NUM_OF_IP_ADDR          4 	// Limited to 2
#define NUM_OF_ROUTER_ADDR      4	//Limited to 2
#define IP_ADDR_LEN             16

/*	For m2m_get_connectivity_info*/
#define MASK_SIGNAL_STRENGTH    0x01
#define MASK_LINK_QUALITY       0x02
#define MASK_CELL_ID            0x04
#define MASK_MCC                0x08
#define MASK_MNC                0x0A

typedef struct conn_m_data_
{
  uint16_t instanceId; 
  resource_instance_string_list_t*    ipAddresses;
  resource_instance_string_list_t*    routerIpAddresses;
  int64_t cellId;
  int signalStrength;
  int linkQuality;
  int32_t mcc;
  int32_t mnc;
  int linkUtilization;
  uint16_t networkBearer;
  uint8_t availNetworkBearerLength;
  uint16_t availNetworkBearer[MAX_AVAIL_BEARER];
  resource_instance_string_list_t*    apnList;
  resource_instance_string_list_t*    apn_name_list;
} conn_m_data_t;


#endif
