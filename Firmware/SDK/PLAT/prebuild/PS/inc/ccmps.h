#ifndef __CCM_PS_H__
#define __CCM_PS_H__
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - ccmps.h
 Description:    - CCM (CIoT Connection Management) PS sub-module
 History:        - 21/12/2017, Originated by xlhu
 ******************************************************************************
******************************************************************************/

/******************************************************************************
* Includes
******************************************************************************/
#include "pssys.h"
#include "cmips.h"

#define CCM_PS_CGATT_GUARD_TIME_IN_SEC  40  //40s

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

typedef enum CcmPsProcEnum_Tag
{
    CCM_NONE_PS_PROC = 0,
    CCM_PS_ATTACH_PROC,
    CCM_PS_DETACH_PROC,
    CCM_PS_ACT_BEARER_PROC
}CcmPsProcEnum;

typedef struct CcmPsDynCtx_Tag
{
    CcmPsProcEnum   cgattProc;      //CGATT procedure, trigger to PS attach/detach
    GosTimerId      attGuardTimer;  //guard timer wait for PS attach result when process: AT+CGATT=1


    /*
     * CGACT/CGDATA to activate a bearer procedure
     * UICC maybe need ACL check, - TBD
    */
    CcmPsProcEnum   actBrProc;
    UINT8           actCid;

}CcmPsDynCtx;

typedef struct CcmPsVzwCtx_Tag
{
	UINT16			pdnConnCounter;  		// number of successful PDN connection requests made by the device
	UINT16          maxConnections;  		// maximum number of connections allowed to the given PDN in a maxConnTime time period

	UINT32          pdnConnTime;     		// time elapsed in seconds since the first time a PDN CONNECTIVITY REQUEST is made for the given PDN after both PDN_CONN_COUNTER and PDN_CONN_TIME for the given PDN are reset to 0
	UINT16          maxConnTime;     		// Time after which both pdnConnCounter and pdnConnTime are reset

	UINT32          LastPdnDisconnTime;     // Time elapsed since last PDN disconnection
	UINT16          waitTimeBeforeNewConn; 	// Mininmum required wait time in seconds after a successful UE initiated disconnect of a given PDN connection before the device can send a new PDN connection request for that given PDN
	UINT32          throttlRemainingDuration;      // Store the remaining duration throttling timer if timer is stopped due to power off
}CcmPsVzwCtx;


/******************************************************************************
 ******************************************************************************
 * Functions
 ******************************************************************************
******************************************************************************/
void CcmPsInit(BOOL wakeUp);
void CcmPsProcessSignal(SignalBuf *sig);
void CcmPsSendSetEpsBearerCtxReq(DefineBearerCtxInfo   *bearerCtxInfo);
void CcmPsSendDelEpsBearerCtxReq(UINT8 cid);
void CcmPsSendActEpsBearerCtxReq(UINT8 cid);
void CcmPsSendDeactEpsBearerCtxReq(UINT8 cid, UINT16 cause, BOOL is_rs_failed);
void CcmPsSendSetDedEpsBearerCtxReq(UINT8 cid,UINT8 pCid,BOOL imcnPresent,UINT8 imcnFlag);
void CcmPsSendDelDedEpsBearerCtxReq(UINT8 cid);
void CcmPsActEpsBearerReq(UINT8 cid);
CmiPsAttachStateEnum CcmPsGetPSAttachState(void);
BOOL CcmPsAttachReq(void);
BOOL CcmPsDetachReq(void);
void CcmPsSendSetAttachwithoutPdnFlagReq(UINT8 PdnAttach_flag);
void CcmPsModifyBearerCtxReq(UINT8 cid);
void CcmPsSetDefineTFTParamReq(CmiPsTftFilter *filter);
void CcmPsDeleteTFTParamReq(UINT8 cid);
void CcmPsSetDefineEpsQosReq(CmiPsEpsQosParams *qosParam);
void CcmPsDeleteEpsQosReq(UINT8 cid);
BOOL CcmPsSendOneUlData(UINT8 cid, UINT16 length, UINT8 *ptr, BOOL bExceptData, UINT8 esmRai, BOOL mustViaCp);
void CcmPsAttachedBearerCtxPresetReq(AttachedBearCtxPreSetParam* attBearCtxPresetParam);
void CcmPsGetAttachedBearerCtxReq(void);
void CcmPsSetMtCpDataReportCfgReq(UINT8 reporting);
void CcmPsGetMtCpDataReportCfgReq(void);
void CcmPsTransCiotPlaneReq(BOOL bViaUp);
void CcmPsSendCesmGetEpsBearerCtxReqSig(UINT16 psCmiId, UINT8 cid, BOOL bReqAll);
void CcmPsSendGetAllBearersBasicInfoReqSig(UINT8 reqCmdId);
void CcmPsProcTimerExpiry(GosTimerExpiry *pTimerExpiry);
void CcmPsSetDefineAuthReq(UINT8 cid,UINT8 proco,UINT8 userIdLength,UINT8* userId,UINT8 passwordLength,UINT8* password);
//BOOL CcmPsBeUnderCgatt0(void);
void CcmPsSendNoMorePsDataReq(void);
BOOL CcmPsVzwIsActBearerAllowed(void);
void CcmPsSetVzwContext(BOOL init, UINT16 maxConnections, UINT16 waitTime, UINT16 maxConnTime);
void CcmPsVzwThrottlTimerExpiry(void);
void CcmPsSetQcVzwApnClassReq(CmiPsSetQcPdpCfgReq *pSetQcPdpCfgReq);
void CacDevCmiPsSetQcVzwApnConfigReqCnf(UINT16 CmiRcCode);
void CcmPsGetApnDisableSyncStatusReqSig(CmiPsGetAPNDisableSyncStatusReq *pCmiGetApnDisableSyncStatusReq);
void CcmPsSetApnDisableSyncStatusReqSig(CmiPsSetAPNDisableSyncStatusReq *pCmiSetApnDisableSyncStatusReq);
void CcmPsProcCesmrejectcauseIndSig(CcmCesmEsmRejectCauseInd* pRejectCauseInd);
void CcmPsGetEsmCauseStatusCnfSig(CmiPsGetEsmCauseCnf *pCmiGetEsmStatus);

void CcmPsSendCedrPktStatsReq(UINT8 cid);
/*
 * internal MSG
*/
void CcmPsProcRegAttachIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmPsProcRegAttachCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmPsProcRegDetachCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmPsSendGetAllBearerBasicInfoReqSig(UINT8 reqCmdId);
void CcmPsSendCesmGetEpsBearersCtxReqSig(UINT16 psCmiId, UINT8 cid, BOOL bReqAll);

#endif

