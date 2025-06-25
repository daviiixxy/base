/******************************************************************************

  @file    object_location.h
  @brief   Location Object Interface File 
           This file declares the interfaces and data structures if any, of 
           location object implementation
  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/
#ifndef OBJECT_LOCATION_H
#define OBJECT_LOCATION_H

#define VELOCITY_OCTETS                      5  // for HORITZOL_VELOCITY_WITH_UNCERTAINTY 
#define DEG_DECIMAL_PLACES                   6  // configuration: degree decimals implementation


typedef struct location_data_
{
  uint16_t instanceId;
  double    latitude; //"359.12345" frag=5, 9+1=10! degrees +\0
  double    longitude;
  double    altitude;
  float    radius;
  uint8_t  velocity   [VELOCITY_OCTETS];        //3GPP notation 1st step: HORITZOL_VELOCITY_WITH_UNCERTAINTY
  uint64_t timestamp;
  float     speed;
} location_data_t;

extern void get_m2m_gps_data(location_data_t* loc_data, float *loc_bearing, float *loc_horUncertainity);
#endif
