/******************************************************************************

  @file    platform.h
  @brief   Platform specific headers

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

******************************************************************************/

#ifndef PLATFORM_HDR_H
#define PLATFORM_HDR_H

//#include <stringl/stringl.h>
//#include "qapi_socket.h"
//#include "errno_codes.h"
//#include "timer.h"
//#include "fs_public.h"
#include <string.h>
#include "qurt_os.h"
#include "qurt_network.h"
#include "qurt_fs.h"

#include <time.h>                                                 
#include <errno.h>

#define LWM2M_STRCPY(d,s,n) strlcpy(d,s,n)
#define LWM2M_MEMCPY(d,dn,s,cn) memcpy(d,s,((cn < dn)?cn:dn))
#define LWM2M_MEMMOVE(d,dn,s,cn) memmove(d,s,((cn < dn)?cn:dn))
#define memscpy LWM2M_MEMCPY

bool lwm2m_isprint(char c);
bool lwm2m_isspace(char c);

#endif
