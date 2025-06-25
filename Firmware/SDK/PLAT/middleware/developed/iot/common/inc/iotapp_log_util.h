/******************************************************************************

  @file    iotapp_log_util.h
  @brief   header file provides utility for logging

  ---------------------------------------------------------------------------
  Copyright (c) 2017-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

******************************************************************************/

#ifndef IOTAPP_LOG_H
#define IOTAPP_LOG_H

#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
//#include "qapi_diag.h"
#include "debug_trace.h"
#include "debug_log.h"

#define MSG_LEGACY_HIGH P_INFO

#define MSG_LEGACY_LOW P_DEBUG

#define MSG_LEGACY_ERROR P_ERROR

// Macro to get argument count considering max 9 args will be passed in va list
#define VAR_NARG(...) VAR_NARG_(__VA_ARGS__,VAR_RSEQ_N())
#define VAR_NARG_(...) VAR_ARG_N(__VA_ARGS__)
#define VAR_ARG_N(_0,_1,_2,_3,_4_5,_6_7,_8,_9,N,...) N
#define VAR_RSEQ_N() 9,8,7,6,5,4,3,2,1,0

/***************************
 Function declarations
**************************/

void iotapp_write_ulog(
	uint32_t mask, 
    uint8_t argnum,
    char* buf,
    const char *fmt, 	
    va_list ap);
void iot_log_print
(
  /*const char* file_name, uint32_t line_number, */uint32_t mask,
  uint8_t argnum,   
  const char *fmt, 
  ...
);

#define iotapp_log(file, line, mask, number, format, ...) iot_log_print(mask, number, format, ##__VA_ARGS__)

#ifdef ENABLE_COMMON_ERR_LOG
#define IOTAPP_LOG_ERR(format, ...) iot_log_print(  MSG_LEGACY_ERROR, VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__)
#else
#define IOTAPP_LOG_ERR(...)
#endif

#ifdef ENABLE_COMMON_INFO_LOG
#define IOTAPP_LOG_INFO(format,...) iot_log_print( MSG_LEGACY_LOW, VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__)
#else
#define IOTAPP_LOG_INFO(...) 
#endif

#define LOG_ERR(format,...) iot_log_print(  MSG_LEGACY_ERROR, VAR_NARG(format, ## __VA_ARGS__), format, ##__VA_ARGS__)


#endif
