/******************************************************************************

  @file    lwm2m_carrier.h
  @brief   Interface File Containing Interfaces and DS w.r.t carrier specific 
           implementations

           This file declares the interfaces and data structures if any, used for 
           carrier specific implementations

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

int lwm2m_carrier_init_regstatus(lwm2m_context_t *lwm2mH);

void lwm2m_carrier_update_regstatus(lwm2m_server_t *serverP);

