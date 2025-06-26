/******************************************************************************

  @file    lwm2m_signals.h
  @brief   Interface File Containing enums for the internal signals of the lwm2m

           This file declares the interfaces and data structures.

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2019 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

/**
 * This enums define the internal signals of lwm2m
 */
enum LWM2M_EVENTS
{
  DSS_M2M_APN_MAX_RETRIES           = 0x01,
  LWM2M_PS_DETACH                   = 0x02,
  DSS_M2M_PRIMARY_APN_CONN_v4       = 0x04,
  DSS_M2M_PRIMARY_APN_NO_NET_v4     = 0x08,
  DSS_M2M_SECONDARY_APN_CONN_v4     = 0x10,
  DSS_M2M_SECONDARY_APN_NO_NET_v4   = 0x20,
  DSS_M2M_PRIMARY_APN_CONN_v6       = 0x40,
  DSS_M2M_PRIMARY_APN_NO_NET_v6     = 0x80,
  DSS_M2M_SECONDARY_APN_CONN_v6     = 0x100,
  DSS_M2M_SECONDARY_APN_NO_NET_v6   = 0x200,
  LWM2M_TRIGGER_DISABLE             = 0x400,
  LWM2M_UNBLOCK_EVENT               = 0x800,
  WMS_MT_MESSAGE_IND                = 0x1000,
  LWM2M_IN_ROAMING_IND              = 0x2000,
  LWM2M_OUT_OF_ROAMING_IND          = 0x4000,
  LWM2M_REBOOT_SET                  = 0x8000,
  LWM2M_FACTORY_RESET_SET           = 0x10000,
  LWM2M_NAS_UP_SIG                  = 0x20000,
  LWM2M_CONN_MONI_CLASS7_APN_CHANGE = 0x40000,
  DSS_M2M_WAIT_FOR_NAS_UP           = 0x80000,
  LWM2M_RESTART                     = 0x100000,
  LWM2M_PS_ATTACH                   = 0x200000,
  LWM2M_CONN_MONI_CLASS6_APN_CHANGE = 0x400000,
  LWM2M_CONN_MONI_SCND_APN_CHANGE   = 0x800000,
  LWM2M_BATTERY_IND                 = 0x1000000,
  LOCATION_FETCH                    = 0x2000000,
  //LWM2M_DISABLE_TIMEDOUT          = 0x4000000,
  LWM2M_BOOTSTRAP_ONDEMAND_IND      = 0x8000000,
  LOCATION_SINGLE_SHOT_CALLBACK     = 0x10000000,
  LOCATION_PMIN_UPDATED             = 0x20000000
};

