/******************************************************************************

  @file    log_utils.h
  @brief   Log Utitilities Interface File
           This file declares the interfaces and data structures if any, used for 
           logging messages on to remote host 

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _LOG_UTILS_H
#define _LOG_UTILS_H

#include <stdarg.h>
#include <stdbool.h>
#include "iotapp_log_util.h"
//#include "qapi_diag.h"

void m2m_log
(
  /*const char* file_name, uint16_t line_number,*/
  uint32_t mask,
  uint8_t argnum,  
  const char *fmt, 
  ...
);
#define LOG_INFO(format, ...)  m2m_log(MSG_LEGACY_HIGH,  VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__); 
#define LOG_ERROR(format, ...) m2m_log(MSG_LEGACY_ERROR, VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__); 


//! Log macro for debug logs
#ifdef M2M_DEBUG
#define LOG_DEBUG(format, ...) m2m_log(MSG_LEGACY_LOW,  VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__); 

#else
#define LOG_DEBUG(...)
#endif
#define PRINT_SIZE 256  // added 

bool lwm2m_isprint(char c);
int m2m_log_printf(const char *fmt,...);

#endif // End of #ifndef _LOG_UTILS_H
