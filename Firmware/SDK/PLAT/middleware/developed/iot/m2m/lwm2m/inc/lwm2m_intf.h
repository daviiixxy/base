/******************************************************************************

  @file    lwm2m_intf.h
  @brief   Interface File for LWM2M functions

           This file implements a part of interfacing between LWM2M TO COAP

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/
#ifndef __LWM2M_INTF_H__
#define __LWM2M_INTF_H__

#include "qapi_lwm2m.h"

typedef qapi_Net_LWM2M_ID_t lwm2m_id_t;
typedef qapi_Net_LWM2M_Value_Type_t lwm2m_value_type_t;

typedef qapi_Net_LWM2M_Id_Info_v2_t lwm2m_id_info_t;
typedef qapi_Net_LWM2M_Object_Info_v2_t lwm2m_object_info_t;
typedef qapi_Net_LWM2M_Resource_Info_t lwm2m_resource_info_t;
typedef qapi_Net_LWM2M_Instance_Info_v2_t lwm2m_instance_info_t;
typedef qapi_Net_LWM2M_Data_v2_t lwm2m_object_data_t;
typedef qapi_Net_LWM2M_Server_Data_t lwm2m_server_data_t; 

#endif 
