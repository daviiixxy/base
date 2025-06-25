#ifndef _CEMM_SMS_SIG_H_
#define _CEMM_SMS_SIG_H_
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - cemmsmsmsg.h
Description:    - Define the interface between EMM and SMS.
Function List:  - 
History:        - 12/13/2017, Originated by flxing
*******************************************************************************/

/*******************************************************************************
 * Includes
*******************************************************************************/

#include "pssys.h"

/*******************************************************************************
 * ENUM
*******************************************************************************/

typedef enum ConnectionFailCauseTag
{
    CONN_FAIL_NO_EPS_SERVICE,
    CONN_FAIL_NETWORK_FAILED,
    CONN_FAIL_EMM_PROCEDURE_ONGOING,
    CONN_FAIL_REACH_MAX_CONNECTION,
    CONN_FAIL_NORMAL_RELEASE,
    CONN_FAIL_BUTT
}
ConnectionFailCause;

/*******************************************************************************
 * SMS->CEMM
*******************************************************************************/

typedef struct CemmSmsEstReqTag
{
    UINT8       tiValue;
    BOOL        tiFlag;
    UINT8       messageLength;
    UINT8       reserved;
    UINT8      *pMessage;
}
CemmSmsEstReq;

typedef struct CemmSmsRelReqTag
{
    UINT8       tiValue;
    BOOL        tiFlag;
    UINT16      reserved0;
}
CemmSmsRelReq;

typedef struct CemmSmsUnitDataReqTag
{
    UINT8       messageLength;
    UINT8       reserved0;
    UINT16      reserved1;
    UINT8      *pMessage;
}
CemmSmsUnitDataReq;

/*******************************************************************************
 * CEMM->SMS
*******************************************************************************/

typedef struct CemmSmsEstCnfTag
{
    UINT8       tiValue;
    BOOL        tiFlag;
    UINT16      reserved0;
}
CemmSmsEstCnf;

typedef struct CemmSmsErrorIndTag
{
    UINT8       tiValue;
    BOOL        tiFlag;
    UINT8       cause;          /* ConnectionFailCause */
    UINT8       reserved;
}
CemmSmsErrorInd;

typedef struct CemmSmsUnitDataIndTag
{
    UINT8       messageLength;
    UINT8       reserved0;
    UINT16      reserved1;
    UINT8      *pMessage;

}
CemmSmsUnitDataInd;

typedef struct CemmSmsServiceAvailableIndTag
{
    BOOL        serviceAvailable;
    UINT8       reserved0;
    UINT16      reserved1;
}
CemmSmsServiceAvailableInd;

typedef GosEmptySignal CemmSmsSuspendInd;

typedef GosEmptySignal CemmSmsResumeInd;

/******************************************************************************
 * INTERNAL MSG API
******************************************************************************/

/*
 * CEMM API
 * When SMS request sending SMS,call this internal Msg
 * then CEMM module will trigger service request/control service request
 * srcId = CE_NAS_SMS
 * argvUint8 = tiValue
 * argvUint16 = tiFlag
 * argvUint32 = messageLength
 * argvPtr = pMessage
*/
void CemmSmsEstRequest(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * When SMS request release SMS connection,call this internal Msg
 * then CEMM module will release SMS connection
 * srcId = CE_NAS_SMS
 * argvUint8 = tiValue
 * argvUint16 = tiFlag
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsRelRequest(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * When SMS request sending SMS,call this internal Msg
 * then CEMM module will trigger service request/control service request
 * srcId = CE_NAS_SMS
 * argvUint8 = messageLength
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = pMessage
*/
void CemmSmsUnitDataRequest(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When radio link for SMS sending is established successfully, call this internal Msg
 * then CESMS module will trigger CP data sending.
 * srcId = CE_NAS_CEMM
 * argvUint8 = tiValue
 * argvUint16 = tiFlag
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsProcEstCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When radio link for SMS sending/receiving is broken, call this internal Msg
 * then CESMS module will stop ongoing timer, release radio link.
 * srcId = CE_NAS_CEMM
 * argvUint8 = tiValue
 * argvUint16 = tiFlag
 * argvUint32 = cause
 * argvPtr = PNULL
*/
void CemmSmsProcErrorIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When MT SMS is received or peer side send response data for MO SMS,call this internal Msg
 * then CESMS module will decode the data and deliver to uplayer.
 * srcId = CE_NAS_CEMM
 * argvUint8 = messageLength
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = pMessage
*/
void CemmSmsProcUnitDataIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When CEMM submodule is in TAU/PLMN Search or other state that can not process service request from uplayer,
 * call this internal Msg, then CESMS module will suspend SMS sending from uplayer if have and not send any SMS
 * sending request to CEMM until resume ind is received.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsProcSuspendIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When CEMM submodule resumes to process service request from uplayer,call this internal Msg
 * then CESMS module will start SMS sending from uplayer if have.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsProcResumeIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When CEMM submodule ACTIVATE TEST MODE, call this function to inform CESMS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsActTestModeIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When CEMM submodule DEACTIVATE TEST MODE, call this function to inform CESMS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsDeactTestModeIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);


/*
 * CESMS API
 * When CEMM submodule CLOSE UE TEST LOOP H, call this function to inform CESMS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsCloseTestModeIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When CEMM submodule OPEN UE TEST LOOP H, call this function to inform CESMS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsOpenTestModeIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CemmSmsPendingStatusInd to Emm
 * Description: CESMS API, Cesms signaling Pending status indication
 * input: NULL
 * output:SMS pending status
 * Comment: 
*/
BOOL CemmSmsPendingStatusInd(void);

/*
 * CESMS API
 * When SMS service status change, call this internal Msg
 * srcId = CE_NAS_CEMM
 * argvUint8 = serviceAvailable
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsProcServiceAvailableIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESMS API
 * When UE detached, call this internal Msg
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSmsProcDetachIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

#endif



