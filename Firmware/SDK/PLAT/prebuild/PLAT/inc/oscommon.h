/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    psoscommon.h
 * Description:  common define for ps/l1
 * History:      08/23/2017    Originated by bchang
 *
 ****************************************************************************/

#ifndef _PS_OSCOMMON_H
#define _PS_OSCOMMON_H

#include "commontypedef.h"
#include "qcx212_internal.h"
#include "FreeRTOSConfig.h"

#define SECONDS_TO_TICKS(S)         (UINT32)((S)*configTICK_RATE_HZ)
#define MINUTES_TO_TICKS(M)         (SECONDS_TO_TICKS((M)*60))

//
#define MILLISECONDS_TO_TICKS(MS)   (SECONDS_TO_TICKS((MS))/1000)

#define SECONDS_TO_MILLISECONDS(S)  (UINT32)((S) * 1000)
#define MINUTES_TO_MILLISECONDS(M)  (SECONDS_TO_MILLISECONDS((M)*60))

#define TICKS_TO_SECONDS(T)         (UINT32)((T)/configTICK_RATE_HZ)

#define TICKS_TO_MILLISECONDS(T)    (UINT32)(((T)*1000)/configTICK_RATE_HZ)

#endif

