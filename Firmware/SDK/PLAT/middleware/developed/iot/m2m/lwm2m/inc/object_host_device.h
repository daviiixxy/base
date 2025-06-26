/******************************************************************************

  @file    object_host_device.h
  @brief   File contains the interface to for Host device object
  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/
#ifndef OBJECT_HOST_DEVICE_H
#define OBJECT_HOST_DEVICE_H

// ---- private "object host device" specific defines ----
// Resource Id's:
#define RES_M_HOST_DEV_MANUFACTURER     0
#define RES_M_HOST_DEV_MODEL            1
#define RES_M_HOST_DEV_ID               2

#define TEMP_LWM2M_MALLOC_SIZE          30   //Temporory Array size
#define PRV_EMPTY                       " "
typedef struct object_host_dev_
{
  struct object_host_dev_ *next;
  uint16_t instanceId;
  uint8_t *host_dev_manufacturer;
  uint8_t *host_dev_model;
  uint8_t *host_dev_id;
}object_host_dev_t;

#endif
