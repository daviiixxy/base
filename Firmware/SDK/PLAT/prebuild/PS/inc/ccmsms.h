#ifndef _CCM_SMS_H_
#define _CCM_SMS_H_
/****************************************************************************
*
* Copy right:   2017-, Copyrights of Qualcomm Ltd.
* File name:    ccmsms.h
* Description:  CCM(CIoT Connection Management) SMS sub-module
* History:      09/15/2017    Originated by xpliu
*
****************************************************************************/
#include "ccmcomm.h"
#include "cemmsig.h"
#include "ccmsig.h"
#include "ccmsim.h"
#include "ccmsmssig.h"
#include "cmisms.h"
#include "pssys.h"


#define     CCM_MAX_ADDR_LEN            40

/* UE support SMS Class 0, 1, 2 and 3 */
#define     MAX_SMS_CLASSES             4

#define     CCM_SMS_MAX_SMS_ID_NUM      7


/****************************************************************************
*
* STRUCT definition
*
****************************************************************************/
typedef enum CcmsmState_Tag
{
    CCM_SMS_INIT,           /* Initial state */
    CCM_SMS_REFRESH_INIT,   /* USAT refresh procedure */
    CCM_SMS_READY,          /* CCM is ready for SMS sending/receiving */
}CcmsmState;

typedef enum  MsgService_Tag{
    SMS_MESSAGE_SERVICE_NORMAL = 0,                 /* no ACK aiming receiving sms */
    SMS_MESSAGE_SERVICE_WITH_ACK = 1,               /* ACK aiming receiving sms  */
    SMS_MESSAGE_SERVICE_MANUFACTURER_SPECIFIC = 128 /* manufacturer specific */
}MsgService;

typedef struct CcmsmProfile_Tag
{
    BOOL                mtCnmiVal[MAX_SMS_CLASSES];
    MsgService          msgService;
    UINT8               dsCnmiVal;
    BOOL                meMsgStorageAvailable;
    UINT16              reserved0;
}CcmsmProfile;

typedef enum CcmSmsMoSmsProcState_Tag
{
    NO_MO_SMS,                           //no any SMS sending
    WAITING_FOR_REQ_TO_GET_SMC,  //start SMS sending and prepare to get smsc info from SIM
    WAITING_FOR_RSP_SMC_ADDR,        //SMS starts sending, but need get SC address from SIM
    WAITING_FOR_REPT_IND         //CCM SMS sent msg to CEMM SMS and wait for report indication
}CcmSmsMoSmsProcState;

typedef struct CcmSmsPpContextTag
{
    UINT32                   cmdRef;
    CemmSmtlDeliveredInd    *pSmtlDeliveredInd;
}CcmSmsPpContext;


typedef struct CcmSmsPpContextListTag
{
    CcmSmsPpContext                      data;
    struct CcmSmsPpContextListTag       *next;
}CcmSmsPpContextList;


typedef struct CcmSmsContext_Tag
{
    UINT8                moProc;    //CcmSmsMoSmsProcState
    BOOL                 smssAvailable; /*SIM SMSS storage file available TBD*/
    BOOL                 moreMsgsToSend;
    BOOL                 isReady;   /*SIM OK ind is received*/
    BOOL                 pendingMemAvailMsg;
    BOOL                 pendingSmsSend;
    BOOL                 ueMemCapFull;
    BOOL                 smInfo[CCM_SMS_MAX_SMS_ID_NUM];
    BOOL                 bSendCmd;
    UINT8                msgReference;
    CcmsmState           state;
    CcmsmProfile         profile;
    CcmSmsPpContextList  *pPpCtxList;
}CcmSmsContext;

typedef struct CcmSmsUnpackBcdArray_Tag
{
    UINT8           numLen;
    UINT8           resered0;
    UINT16          reserved1;
    UINT8           num[CCM_MAX_ADDR_LEN];
}CcmSmsUnpackBcdArray;

typedef struct CcmSmsPpData_Tag
{
    UINT8               smsId;
    UINT8               reserved0;
    UINT16              reserved1;
    SmsProtocolId       smsProtocolId;
    SmsDataCoding       smsDataCoding;
}CcmSmsPpData;

typedef enum CcmSimCnfRc_Tag
{
    CCMSI_CNF_NULL,
    CCMSI_CNF_OK,
    CCMSI_CNF_ERROR,
    CCMSI_CNF_FATAL,
    CCMSI_CNF_ERROR_OR_FATAL,
    NUM_OF_CCMSI_CNFS
}CcmSimCnfRc;

//Provided by USAT
typedef enum UsatMoSmControlResultTag
{
    USAT_MOSM_ALLOWED_NO_MODS    = 0x00,
    USAT_MOSM_NOT_ALLOWED        = 0x01,
    USAT_MOSM_ALLOWED_WITH_MODS  = 0x02,
    USAT_MOSM_DEFAULT            = 0x03
}UsatMoSmControlResult;

typedef enum NumberingPlan_Tag
{
    PLAN_UNKNOWN                     =   0,
    PLAN_ISDN                        =   1,
    PLAN_DATA                        =   3,
    PLAN_TELEX                       =   4,
    PLAN_NATIONAL                    =   8,
    PLAN_PRIVATE                     =   9,
    PLAN_ERMES                       =   10,
    PLAN_RESERVED                    =   15
}NumberingPlan;


typedef enum ProtInterWorking_Tag
{
    IMPLICIT                 =   0,
    TELEX,
    GRP3_FAX,
    GRP4_FAX,
    VOICE,
    ERMES,
    NAT_PAGING,
    VIDEOTEX,
    UNSPEC_TELETEX,
    PSPDN_TELETEX,
    CSPDN_TELETEX,
    PSTN_TELETEX,
    ISDN_TELETEX,
    UCI,

    MSG_HANDLING             =   16,
    X400,
    INTERNET_EMAIL,

    SC_SPECIFIC_1            =   24,
    SC_SPECIFIC_2,
    SC_SPECIFIC_3,
    SC_SPECIFIC_4,
    SC_SPECIFIC_5,
    SC_SPECIFIC_6,
    SC_SPECIFIC_7,
}ProtInterWorking;

typedef enum ProtScCommand_Tag
{
    SM_TYPE0                 =   0,
    REPLACE_SM_TYPE1,
    REPLACE_SM_TYPE2,
    REPLACE_SM_TYPE3,
    REPLACE_SM_TYPE4,
    REPLACE_SM_TYPE5,
    REPLACE_SM_TYPE6,
    REPLACE_SM_TYPE7,

    RETURN_CALL_MSG          = 0x1F
}ProtScCommand;

// Refer to TS23.040,when PID byte has bit7 = 0 and bit6 = 1
typedef enum ProtMeCommand_Tag
{
    DEPERSONALISATION_SM     = 0x3E,
    SIM_DATA_DOWNLOAD
}ProtMeCommand;

typedef enum CcmSimAlphaIdType_Tag
{
    USAT_SM_ALPHA_ID ,
} CcmSimAlphaIdType;

typedef enum GeneralResult_Tag
{
    USAT_PERF_OK               = 0x00,
    USAT_PART_COMP             = 0x01,
    USAT_PERF_MISS_INFO        = 0x02,
    USAT_SMS_RP_ERROR          = 0x03,
}GeneralResult;

typedef enum MeProblemInfo_Tag
{
    USAT_INFO_NO_CAUSE_GIVEN           = 0x00,
    USAT_INFO_SCREEN_BUSY              = 0x01,
    USAT_INFO_NO_SERVICE               = 0x02,
}MeProblemInfo;

typedef enum CcmSimRequestStatus_Tag
{
    CCM_SIM_REQ_OK,
    CCM_SIM_REQ_INVALID_PARAMS,
    CCM_SIM_REQ_FILE_NOT_FOUND,
    CCM_SIM_REQ_USAT_BUSY,
    CCM_SIM_REQ_SIM_GENERAL_FAULT,
    CCM_SIM_REQ_MEMORY_PROBLEM,
    CCM_SIM_REQ_ACCESS_DENIED,
    CCM_SIM_REQ_SM_FAULT,
    CCM_SIM_REQ_CODE_BLOCKED,
    CCM_SIM_REQ_SIM_DDL_ERROR
} CcmSimRequestStatus;

typedef enum CcmSmsRequestStatus_Tag
{
    CCM_SMS_REQ_OK,
    CCM_SMS_REQ_NOT_READY,  //SMS service is not ready
    CCM_SMS_REQ_SEND_READY,
    CCM_SMS_REQ_SIM_ERROR, //SIM report error
    CCM_SMS_REQ_PS_ERROR,    //PS report error
    CCM_SMS_REQ_INVALID_PARA,  //Invalid parameter
    CCM_SMS_REQ_PS_DEREG     //PS not registered
} CcmSmsRequestStatus;

typedef enum MoSmsControlResult_Tag
{
    USAT_MO_CONTROL_NOT_RESULT                 = 0x00,
    USAT_MO_CONTROL_ALLOWED_NO_MODIFICATION    = 0x01,
    USAT_MO_CONTROL_NOT_ALLOWED                = 0x02,
    USAT_MO_CONTROL_ALLOWED_WITH_MODIFICATION  = 0x03
} MoSmsControlResult;

typedef enum UsatSmsDownloadErrorType_Tag
{
    USAT_DOWNLOAD_NO_ERROR        = 0,
    USAT_DOWNLOAD_PP_ERROR        = 1
}UsatSmsDownloadErrorType;

extern MsgAddress        gScAddress;
extern BOOL              gGetSmscFromAP;

/****************************************************************************
*
* Functions
*
****************************************************************************/
void CcmSmsInit(BOOL  bWakeup);
void CcmSmsSimOkIndMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmSmsSimNokIndMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);

void CcmSimGetSmspInfoCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmSimWriteSmspInfoCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
/*
 * CCM-SMS API
 * When CCM-SIM receive SMSS status result from UICC CTRL task
 * call the API to inform CCM-SMS, then CCM SMS will store the status.
 * srcId = CCM_SIM
 * argvUint8 = requestStatus
 * argvUint16 = msgRef
 * argvUint32 = memoryCapExceeded;
*/
void CcmSimGetSmssInfoCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
/*
 * CCM-SMS API
 * When CCM-SIM receive SMSS update result from UICC CTRL task
 * call the API to inform CCM-SMS.
 * srcId = CCM_SIM
 * argvUint8 = requestStatus
 * argvUint16 = 0
 * argvUint32 = 0;
*/
void CcmSimWriteSmssInfoCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);


//void CcmSimSendSmCnfFunc(CcmUsatSmsSendSmRsp *pSmRsp,CcmSmsSendSmCnf *pSmCnf ); /* USAT SMS error state */
void CcmSmsSendMessageReq(CmiSmsSendMsgReq *pCmiSendMsgReq);
void CcmSmsSendCommandReq(CmiSmsSendCommandReq *pCmiSendCmdReq);
void CcmSmsSetSmsServiceReq(UINT8 smsService);
void CcmSmsGetSmsServiceReq(void);
void CcmSmsSendMoreMessageReqFunc(void);
BOOL CcmMsgConvertSmsAddrToBcdNum(CmiSmsAddressInfo *pAddrInfo, MsgAddress *pSmAddr);
void CcmSmsSendMsgRej (UINT8 msgRef);
void CcmMsgConvertSmsAddrToDigits(MsgAddress *pSmAddr, CmiSmsAddressInfo *pAddrInfo);
void CcmSmsProcessSignal(SignalBuf *sig);

/*
 * CCM-SMS API
 * When CCM-SIM receive CCM_USAT_SMS_PP_DOWNLOAD_CNF from UICC CTRL task about result for ENVELOP command
 * call the API to inform CCM-SMS, then CCM SMS will trigger RP report to NW.
 * CcmSimUsatSmsPpDownloadCnf *pSmsPpDownloadCnf
*/
void CcmSimSmsPpDownloadCnfFunc(CcmSimUsatSmsPpDownloadCnf *pSmsPpDownloadCnf);

/*
 * CCM-SMS API
 * When CCM-SIM receive CCM_USAT_MO_SM_CONTOL_CNF from UICC CTRL task about result for ENVELOP command
 * call the API to inform CCM-SMS, then CCM SMS will corresponding modification then trigger MO SMS to NW.
 * srcId = CCM_SIM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = CcmSimMoSmControCnf
*/

//void CcmSimMoSmControCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmSimMoSmControCnfMsg(CcmSimMoSmControlCnf *pMoSmControlCnf);


/*
 * CCM-SMS API
 * When CCM-SIM receive CCM_SIM_USAT_SEND_SM_IND from UICC CTRL task about result for proactive command to send SMS
 * call the API to inform CCM-SMS, then CCM SMS will trigger MO SMS to NW.
 * CcmSimUsatSendSmInd *pUsatSendSmInd
*/
void CcmSimSmsProactiveMessageIndFunc(CcmSimUsatSendSmInd *pUsatSendSmInd);


#endif

