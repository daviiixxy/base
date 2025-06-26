#ifndef _CEMM_ESM_MSG_H_
#define _CEMM_ESM_MSG_H_

/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - cemmesmmsg.h
Description:    - Define the interface between EMM and ESM.
Function List:  -
History:        - 12/12/2017, Originated by flxing
*******************************************************************************/

/*******************************************************************************
 * Includes
*******************************************************************************/

#include "pssys.h"
#include "nascommon.h"
#include "ccmsig.h"

/*******************************************************************************
 *******************************************************************************
 * ENUM
 *******************************************************************************
*******************************************************************************/

/*******************************************************************************
 * CEMM->ESM
*******************************************************************************/
typedef struct CemmEsmMessageContainerIndTag
{
    UINT8           msgType;    /* EsmMessageType :PDN CONNECTIVITY REQUEST/ESM DUMMY MESSAGE */
    UINT8           reserved0;
    UINT16          reserved1;
}
CemmEsmMessageContainerInd;

typedef struct CemmEsmEstCnfTag
{
    BOOL            success;
    UINT8           reserved0;
    UINT16          reserved1;
}
CemmEsmEstCnf;

typedef struct CemmEsmUnitDataIndTag
{
    UINT16          messageLength;
    UINT8          *pMessage;
    UINT8           reserved0;
}
CemmEsmUnitDataInd;

typedef struct CemmEsmBearerContextStatusIndTag
{
    UINT16          bearerContextStatus;
    UINT16          reserved0;
}
CemmEsmBearerContextStatusInd;

typedef struct CemmEsmFeatureSupportIndTag
{
    UINT8   ueSuptOptType;      /* UE supported CIOT OPT type, CemmCiotOptTypeEnum: 1 & 3 */
    UINT8   uePreferOpt;        /* CemmCiotOptTypeEnum: 0, 1, 2 */
    UINT8   nwSupCiotOpt;       /* CemmCiotOptTypeEnum */
    UINT8   hcCIoT;             /* Header compression for control plane CIoT EPS optimization (HC-CP CIoT) */
    UINT8   ePCO;               /* Extended protocol configuration options (ePCO) */
    BOOL    attachWithoutPdn;   /* UE initiate ATTACH without PDN */
    UINT16  reserved1;
}
CemmEsmFeatureSupportInd;

typedef struct CemmEsmNasConfigIndTag
{
    UINT8   nasSignallingPriority;  /* NasSignallingPriority */
    BOOL    overrideNasSignallingLowPriority;
    UINT8   smRetryWaitTime;
    BOOL    exceptionDataReportingAllowed;
}
CemmEsmNasConfigInd;

typedef struct CemmEsmRegIndTag
{
   Plmn plmn;
}
CemmEsmRegInd;

typedef GosEmptySignal CemmEsmTransmissionFailureInd;

typedef GosEmptySignal CemmEsmSuspendInd;

typedef GosEmptySignal CemmEsmResumeInd;

typedef GosEmptySignal CemmEsmReleaseInd;

typedef GosEmptySignal CemmEsmAbortInd;


/*******************************************************************************
 * ESM->CEMM
*******************************************************************************/
typedef struct CemmEsmMessageContainerRspTag
{
    UINT16      messageLength;
    UINT16      reserved0;
    UINT8       *pMessage;  /* EsmMessageType */
}CemmEsmMessageContainerRsp;

/* For ESM messages transport except 'ESM DATA TRANSPORT',will trigger Service Request */
typedef GosEmptySignal CemmEsmEstReq;

/*
 * As user data maybe ROHC compressed, and compressed pkg just as following:
 *  After ROHC:
 *  1> if (ip/udp/other hdr length) >= (comp len): (most case)
 *  +---------+--------+-----------------------------------+
 *  |         |comp hdr|        payload                    |
 *  +---------+--------+-----------------------------------+
 *  ^
 *  |ptr
 *  |<------->|validOffset
 *  |         |<-------------- length -------------------->|
 * Here, need involve a new member: "validOffset", as the real pkg header start from: ptr + validOffset
*/
typedef struct CemmEsmUnitDataSeg_Tag
{
    UINT16      length;
    UINT8       memType;    /* DataPduMemType */
    UINT8       validOffset;

    UINT8       *ptr;
}CemmEsmUnitDataSeg;

/* 2 seg - for ESM signalling, 3 seg - for one USER DATA */
#define CESM_UL_UNIT_DATA_MAX_SEG   5

typedef struct CemmEsmUnitDataReqTag
{
    BOOL                bExceptData;    /* Transmit user data related to an exceptional event */
    UINT8               msgType;        /* EsmMessageType */
    UINT8               relAssistInd;   /* DataRelAssistIndEnum */
    UINT8               tickType;       /* UlPduTickType, indicate the "sysTick" type */

    /*
     * Note:
     * 1> if "systick" is "UL_PDU_DISCARD_TICK", then PS (EMM) MAYBE (not must) discard this pkg, if "current sys tick" > "sysTick";
     *    LWIP could set this if has a clear valid period for this UL PKG, such as: TCP pkg, or DNS/IPv6 RS pkg (as has retry timer);
     * 2> if "systick" is "UL_PDU_START_TICK", then PS (EMM) MAYBE (not must) discard this pkg in case:
     *     a> the time passed more than 20s, and b> has anyother UL pkg followed;
     * 3> if "systick" is "UL_PDU_NO_TICK_INFO", then PS (EMM) could try best to send it, don't discard it easily;
    */
    UINT32              sysTick;

    CemmEsmUnitDataSeg  segMsg[CESM_UL_UNIT_DATA_MAX_SEG];  /* 40 bytes*/
}CemmEsmUnitDataReq;    //48 bytes

typedef struct CmmEsmBearerContextStatusRspTag
{
    UINT16          bearerContextStatus;
    UINT16          reserved0;
}CemmEsmBearerContextStatusRsp;

/* Local EPS bearer context deactivation without NAS signalling,UE need locally detach
and then attach again */
typedef GosEmptySignal CemmEsmLocalDetachReAttachInd;

/******************************************************************************
 * INTERNAL MSG API
*******************************************************************************/

/*
 * CESM API
 * When CEMM trigger ATTACH procedure,query esm message container
 * srcId = CE_NAS_CEMM
 * argvUint8 = msgType
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcMsgContainerIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles the confirm of establish request
 * srcId = CE_NAS_CEMM
 * argvUint8 = success
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcEstablishCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles downlink ESM message/CemmEsmUnitDataInd
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = messageLength
 * argvUint32 = 0
 * argvPtr = pMessage
*/
void CemmEsmProcUnitDataIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles eps bearer context status query
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = bearerContextStatus
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcBearerContextStatusIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles network rohc support ind
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = bearerContextStatus
 * argvUint32 = 0
 * argvPtr = PNULL
*/

void CemmEsmProcRohcStatusIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
/*
 * CESM API
 * CESM handles transmission failure indication
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcTransmissionFailureIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles suspend indication
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcSuspendIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles resume indication
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcResumeIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles release indication
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcReleaseIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles abort indication
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcAbortIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles ESM DATA TRANSPORT succeed indication
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmProcDataTransportSucceedIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESM API
 * CESM handles Feature Support indication
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = CemmEsmFeatureSupportInd
*/
void CemmEsmProcFeatureSupportIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
/*
 * CESM API
 * CESM handles powerRecovery
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/

void CemmEsmProcPowerRecoveryIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

void CemmEsmRecoverBearerContext(void);

/*
 * CESM API
 * CESM handles NAS config ind
 * srcId = CE_NAS_CEMM
 * argvUint8 = nasSignallingPriority
 * argvUint16 = overrideNasSignallingLowPriority
 * argvUint32 = 0
 * argvPtr = PNULL
*/

void CemmEsmProcNasConfigIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * CEMM handling response of CemmEsmMessageContainerInd
 * srcId = CE_NAS_CESM
 * argvUint8 = 0
 * argvUint16 = messageLength
 * argvPtr = pMessage
*/
void CemmEsmMsgContainerRspMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * CEMM handling CESM establish request
 * srcId = CE_NAS_CESM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmEsmEstablishReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * CEMM handling CESM uplink data transport
 * srcId = CE_NAS_CESM
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = CemmEsmUnitDataReq
*/
void CemmEsmUnitDataRequestMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * CEMM handling CESM eps bearer context status
 * srcId = CE_NAS_CESM
 * argvUint8/argvUint32 = 0
 * argvUint16 = bearerContextStatus
 * argvPtr = CemmEsmUnitDataReq
*/
void CemmEsmBearerContextRspMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * CEMM handling CESM locally detach and then attach indication
 * srcId = CE_NAS_CESM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0

 * argvPtr = PNULL
*/
void CemmEsmLocalDetachReAttachIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

void CemmEsmCheckCause27Msg  (UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

void CemmEsmProcRegIndIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
/*
 * CEMM API
 * CESM get T3346 is running or not
 * TRUE:running;FALSE:not running
*/
BOOL CemmIsT3346Running(void);

BOOL CemmIsAllowSendExceptionDataInSuspendState(void);

BOOL CemmIsAllowSendNormalPriSignallingInSuspendState(void);
void CemmEsmStopAndRestrartT3402IndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
BOOL CemmIsConfiguredUseAc11To15(void);
void T3396ExpiryHandle(void);
void Cemmesmupdatepsapn(BOOL updatetinycontext);

/******************************************************************************
 * CemmEsmPendingStatusInd to Emm
 * Description: CESM API, Cesm  signaling/data Pending status indication
 * input: NULL
 * output:ESM pending status
 * Comment:
******************************************************************************/
BOOL CemmEsmPendingStatusInd(void);

void CemmEsmGetEMEsmStatusParm(CcmGetNasStatusCnf *pNasStatusCnf);


/******************************************************************************
 * CemmEsmSetEpcoFlag API to Emm
 * Description: CESM API, Cemm set EPCO flag to cesm
 * input: epcoFlag
 * output:
 * Comment:
******************************************************************************/
extern void CemmEsmSetEpcoFlag(BOOL epcoFlag);


/******************************************************************************
 * CemmEsmGetEpcoFlag API to Emm
 * Description: CESM API, Cemm Get EPCO flag from cesm
 * input: NULL
 * output:epcoFlag
 * Comment:
******************************************************************************/

extern BOOL CemmEsmGetEpcoFlag(void);

/******************************************************************************
 * CemmEsmSetDnsToBeReadFlag API to Emm
 * Description: CESM API, Cemm set DnsToBeRead flag to cesm
 * input: dnsToBeRead,flag
 * output:
 * Comment:
******************************************************************************/
extern void CemmEsmSetDnsToBeReadFlag(DnsToBeReadType dnsToBeRead,BOOL flag);

/******************************************************************************
 * CemmEsmGetDnsToBeReadFlag API to Emm
 * Description: CESM API, Cemm get DnsToBeRead flag from cesm
 * input: BOOL* Ipv4dnsToBeRead, BOOL* flag;
 * output:
 * Comment:
******************************************************************************/
extern void CemmEsmGetDnsToBeReadFlag(BOOL *Ipv4dnsToBeRead,BOOL *Ipv6dnsToBeRead);

/*
 * CEMM API
 * CEMM handling response of CemmEsmMsgSetApnContext
 * srcId = CE_NAS_CESM
 * argvUint8 = 0
 * argvUint16 = messageLength
 * argvPtr = pMessage
*/
void CemmEsmMsgSetApnContext(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

void CemmEsmProcSetOpConfigMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CemmEsmProcUpdatPsApnInTinyContextIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

#endif


