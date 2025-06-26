#ifndef __CCMCS_UICC_H__
#define __CCMCS_UICC_H__
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - ccmsim.h
 Description:    - CCM (CIoT Connection Management) SIM sub-module
 History:        - 21/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
#include "pssys.h"
#include "ccmsimsig.h"
#include "cmisim.h"
/*********************************************************************************
* Macros
*********************************************************************************/
#define USAT_BIP_DATA_BUF_MAX_LEN    1600  // Qualcomm's modification
/*********************************************************************************
* Type Definition
*********************************************************************************/

/******************************************************************************
 *****************************************************************************
 * Enums
 *****************************************************************************
******************************************************************************/

typedef enum CcmSimStateEnum_Tag
{
    CCM_SIM_POWER_OFF,   /* Init state, not powered */
    CCM_SIM_POWER_INIT,  /* Powere on, start the sim card init. */
    CCM_SIM_DETECT,      /* SIM detected and init ongoing*/
    CCM_SIM_READY,       /* SIM Ready */
    CCM_SIM_NOK,         /* SIM Failure */
    CCM_SIM_REMOVED,      /* SIM not inserted or removed */
    CCM_SIM_ESIM_NO_PROFILE	/*eSIM detected with No profile*/ 
}CcmSimStateEnum;

typedef enum CcmSimUiccNokCauseTag
{
    CS_UICC_NOK_NULL,

    CS_UICC_NOK_POWER_OFF,
    CS_UICC_NOK_REMOVED,                  /* Uicc removed or not detectedED_UNDETECTED */

    CS_UICC_NOK_INSERTED_ERROR,           /* from ccmSimAppstartedInd: INSERTED_ERROR/INSERTED_WRONG_SIM */
    CS_UICC_NOK_INVALID_STATUS_RSP,
    CS_UICC_NOK_INITIALISE_FAILED,        /* from ccmSimAppInitCnf */

    /* ccmRequestStatus */
    CS_UICC_NOK_INVALID_PARAMS,           /* CCM_SIM_REQ_INVALID_PARAMS                 */
    CS_UICC_NOK_MEMORY_PROBLEM,           /* CCM_SIM_REQ_MEMORY_PROBLEM                 */
    CS_UICC_NOK_FILE_NOT_FOUND,           /* CCM_SIM_REQ_FILE_NOT_FOUND                 */
    CS_UICC_NOK_SERVICE_NOT_AVAILABLE,    /* CCM_SIM_REQ_SERVICE_NOT_AVAILABLE          */
    CS_UICC_NOK_GENERAL_FAULT,            /* CCM_SIM_REQ_CS_UICC_GENERAL_FAULT          */
    CS_UICC_NOK_FILE_INVALIDATED,         /* CCM_SIM_REQ_FILE_INVALIDATED               */
    CS_UICC_NOK_ALLOC_ERROR,              /* CCM_SIM_REQ_ALLOC_ERROR                    */
    CS_UICC_NOK_SM_FAULT,                 /* CCM_SIM_REQ_SM_FAULT                       */

     /* PIN related */
    CS_UICC_NOK_PIN1_BLOCKED,
    CS_UICC_NOK_PIN2_BLOCKED,
    CS_UICC_NOK_PIN1_UNBLOCK_BLOCKED,
    CS_UICC_NOK_PIN2_UNBLOCK_BLOCKED,

    CS_UICC_NOK_REFRESH,
    CS_UICC_NOK_REFRESH_RESET,

    CS_UICC_NOK_NETWORK_REJECT,          /* UICC was invalidated by network reject */
    CS_UICC_NOK_INITIALISE_FAILED_ESIM_NO_PROFILE,

    CS_UICC_NOK_UNKNOWN
}
CcmSimUiccNokCause;

typedef enum CcmUiccServiceIndexTag
{
    CCM_UICC_SERVICE_SMS_STORAGE,
    CCM_UICC_SERVICE_MOSMS_CTRL,
    CCM_UICC_SERVICE_SMS_PP
}
CcmUiccServiceIndex;

typedef enum CcmSimCheckPinResTag
{
    CS_RES_PIN_DISABLE,
    CS_RES_PIN_UNBLOCKED,  /* need verify PIN code */
    CS_RES_PIN_BLOCKED,    /* PIN blocked, need PUK code to unblock it */
    CS_RES_PUK_BLOCKED,    /* PUK blocked means it's a invalid card */

    CS_RES_ERROR
}
CcmSimCheckPinRes;

typedef enum CcmSimCnfStatusTag
{
    CONFIRM_STATUS_NULL,
    CONFIRM_STATUS_OK,
    CONFIRM_STATUS_ERROR,
    CONFIRM_STATUS_FATAL

}
CcmSimCnfStatus;


/******************************************************************************
 *****************************************************************************
 * STRUCTS
 *****************************************************************************
******************************************************************************/
/*
* CcmSimRegStatusChangeInfo
* Notify register status info changed for USAT, as event download-location status/network reject
* Event download-location status: 1 regState (no service)
*                         2 regState (normal service) + plmn + tac + cellId
* Event download-network reject: deRegType + rejCause + access technology + plmn + tac
*/
typedef struct CcmSimRegStatusChangeInfo_Tag
{
    UINT8   regState; //CmiCeregStateEnum, indicate location status changed (normal service <-> no service)

    BOOL    bLocInfoChange; //indicate location info (tac/cellId/plmn) changed or update

    UINT16  tac;
    UINT32  cellId;
    Plmn    plmn;

    BOOL    deRegPresent; //indicate network reject (attach reject/TAU reject) present
    UINT8   deRegType; //CemmRegStatusEnum, reject type
    UINT16  rejCause; //reject cause

}CcmSimRegStatusChangeInfo;


typedef struct CcmSimUiccPinStatusTag
{
    UiccPinStatus                   pin1Status;
    UiccPinStatus                   pin2Status;
    UiccPinStatus                   universalPinStatus;
    UiccPinStatus                   unblockPin1Status;
    UiccPinStatus                   unblockPin2Status;
    UiccPinStatus                   unblockUniversalPinStatus;
    UiccKeyRefValue                 pin1KeyReference;
    UiccKeyRefValue                 pin2KeyReference;
    BOOL                            verifyUniversalPin;
    BOOL                            universalPinSupportedByCard;

}
CcmSimUiccPinStatus;

typedef struct BipDataPduTag
{
    UINT8                       channelId;
    UINT8                       reserved;
    UINT16                      length;
    UINT8                       *ptr;//USAT_BIP_DATA_BUF_MAX_LEN
    struct BipDataPduTag        *pNext;
}
BipDataPdu;


typedef struct CcmSimStaticCtxTag
{
    CcmSimStateEnum          uiccState;
    CcmSimUiccPinStatus      uiccPinStatus;
    Imsi                     imsi;
    Iccid                    iccid;
    CcmSimUiccService        ccmUiccService;
    BOOL                     isBusy;
}
CcmSimStaticCtx;

typedef struct CcmSimUsatDynCtxTag
{
    UINT32                   usatCmdDetailsRef;
    UsatEventList            eventList;
    UINT8                    resvd1;
    BOOL                     refreshOngoing;
    BOOL                     locStatusChange;
    UsatLocationStatus       locationStatus;
    UsatLocationInfo         locationInfo;
    BipDataPdu               *pUlDataHdr[USAT_MAX_NUM_CHANNELS];
    BipDataPdu               *pDlDataHdr[USAT_MAX_NUM_CHANNELS];
    UINT16                   resvd2;
    UINT16                   bipBufferSize;
    UsatChannelStatus        bipChannel[USAT_MAX_NUM_CHANNELS];
}
CcmSimUsatDynCtx;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
void CcmSimInit(BOOL wakeUp);
CcmSimStateEnum CcmSimGetSimState(void);
CcmSimUiccPinStatus CcmSimGetUiccPinState(void);
Imsi CcmSimGetImsiValue(void);
void CcmSimGetImsiStr(CmiSimImsiStr *pImsiStr);
#ifdef FEAT_JIO_PLMN_LOCK
void CCmSimgetPlmnLockList(CmiDevGetPlmnLockListCnf *getPlmnLockList);
#endif
Iccid CcmSimGetIccidValue(void);
void CcmSimHandleUiccFailure(CcmSimUiccNokCause cause);
void CcmSimHandleUiccReady(void);
void CcmSimProcPowerOnReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmSimProcPowerOffReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
#ifdef FEAT_RPM
void CcmSimUpdateRpmOmParamReq(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmSimReadRpmParamReq(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
#endif
void CcmSimUiccAppInitReq(void);
void CcmSimProcessSignal(SignalBuf *sig);
BOOL CcmSimCheckUsimServiceAvailable(CcmUiccServiceIndex serviceIndex);
void CcmSimOperatePinReqFunc(BOOL bClckSet, UiccPinFunction pinFunc, UINT8 pinNum, UINT8 *pinValue, UINT8 *newPinValue);
void CcmSimCmiGenAccessReqFunc(UINT8 cmdRef, UINT16 dataLen, UINT8 *data, CmiSimFilePath *filePath, UINT8 sessionId);
void CcmSimOpenLogicalChannelReqFunc(UINT8 aidLen, UINT8 *pAidData);
void CcmSimCloseLogicalChannelReqFunc(UINT8 sessionId);
void CcmSimSetSimWriteCounterReqFunc(UINT8 mode);
void CcmSimSetSimPresenceDetectReqFunc(UINT8 mode);
void CcmSimGetSubscriberNumReqFunc(UINT8 srcId);

void CcmSimUsatOpenChannelRspFunc(CmiSimUsatOpenChannelRsp *pCmiOpenChannelRsp);
void CcmSimUsatCloseChannelRspFunc(CmiSimUsatCmdResult  *cmdResult);
void CcmSimUsatSendDataRspFunc(CmiSimUsatCmdResult  *cmdResult, UINT16 remainBufLen);
void CcmSimUsatReceiveDataRspFunc(CmiSimUsatCmdResult *cmdResult, BipDataPdu *pDataPdu, UINT8 expLen);
void CcmSimUsatGetChannelStatusRspFunc(void);


void CcmSimGetSmspInfoReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmSimWriteSmspReqMsg(CcmSimWriteSmspReq *pWriteSmspReq);
/*
 * CCM-SIM API
 * When CCM-SMS need get smss status,send the msg to CCM SIM
 * srcId = CCM_SMS
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CcmSimGetSmssInfoReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmSimWriteSmssReqMsg(CcmSimWriteSmssReq *pWriteSmssReq);

//void CcmSimUsatEventMonitor(UINT16 sigId, void *sigbody);
/*
 * CCM-SIM API
 * When CCM-SMS receive MT SMS(CEMM_SMS_STL_DELIVER_IND), check it as CLASS2 message, call this internal Msg
 * then CCM-SIM module will trigger CCM_USAT_SMS_PP_DOWNLOAD_REQ to UICC CTRL task
*/
void CcmSimUsatSmsPpDownloadReqMsg(UINT32 cmdDetailsRef, CemmSmtlDeliveredInd *pDeliveredInd);
/*
 * CCM-SIM API
 * When CCM-SMS receive MO SMS, check mo sms ctrl by uicc, if true, call this internal Msg
 * then CCM-SIM module will trigger CCM_USAT_MO_SM_CONTOL_REQ to UICC CTRL task
 * srcId = CCM_SMS
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = CcmSimMoSmControlReq
*/

void CcmSimMoSmControlReqMsg(MsgAddress *pSmeAddr, MsgAddress *pScAddr);

/*
 * CCM-SIM API
 * When CCM-SMS receive RP-ACK for proactive SMS, call this internal Msg
 * then CCM-SIM module will trigger CCM_SIM_USAT_SEND_SM_RSP to UICC CTRL task
 * srcId = CCM_SMS
*/
void CcmSimSmsSendSmRspMsg(CcmSimSmsSendSmRsp *pCcmSimSmsSendSmRsp);

void CcmSimUsatSetTerminalProfileReq(BOOL bUsatCommEnable,UINT8 length, UINT8 *pTpValue);
void CcmSimUsatGetTerminalProfileReq(void);


void CcmSimSendUsatEventDownloadReq(UsatEventType eventType, void *pEventData);
void CcmSimProcUsatDataAvailableReq(BipDataPdu *pDataPdu);
void CcmSimDeepSlpEnterCallBack(UINT8 lowPowerState);

/*
 * CCM-SIM API
 * called by CCMREG after dereg conf for refresh procedure.
*/
void CcmSimUsatRefreshResetFunc(void);

void CcmSimSetSimSleepFunc(UINT8 sleepMode);

void CcmSimRegStatusChangeInfoInd(CcmSimRegStatusChangeInfo *changeInfo);


#endif

