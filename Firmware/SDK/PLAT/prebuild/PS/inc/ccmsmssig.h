#ifndef __CCM_SMS_SIG_H__
#define __CCM_SMS_SIG_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - ccmsmssig.h
Description:    - Define the signals structure for CCM SMS.
Function List:  -
History:        - 11/03/2017, Originated by xpliu
******************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
#include "pssys.h"
//#include "pscommutil.h"
#include "cemmsig.h"

#define     SIM_ALPHA_ID_SIZE              32


typedef struct SimAlphaId_Tag
{
    UINT8            length;
    UINT8            reserved1;
    UINT16           reserved2;
    UINT8            data[SIM_ALPHA_ID_SIZE];

}SimAlphaId;

typedef struct SimSmsParams_Tag
{
    SimAlphaId                 alphaId;
    BOOL                       destAddrPresent;
    BOOL                       scAddrPresent;
    BOOL                       protocolIdPresent;
    BOOL                       codingSchemePresent;
    MsgAddress                 destAddr;
    MsgAddress                 scAddr;
    SmsProtocolId              smsProtocolId;
    SmsDataCoding              smsDataCodingScheme;
    BOOL                       validityPeriodPresent;
    UINT8                      validityPeriod;
    UINT16                     reserved;
}SimSmsParams;

typedef struct CcmSimMoSmControlCnf_Tag
{
    UINT8                         requestStatus;  //CcmSimRequestStatus
    UINT8                         moSmResult;  //UsatMoSmControlResult
    BOOL                          scAddrPresent;
    BOOL                          destAddrPresent;
    MsgAddress                    destAddr;
    MsgAddress                    scAddr;
    BOOL                          alphaIdPresent;
    UINT8                         reserved1;
    UINT16                        reserved2;
    SimAlphaId                    alphaId;
}CcmSimMoSmControlCnf;

typedef struct  CcmSimSmControlReq_Tag
{
    SignalBuf     originalSig;
} CcmSimSmControlReq;

typedef struct  CcmSimMoSmControlReq_Tag
{
    MsgAddress                       smeAddr;
    MsgAddress                       scAddr;
} CcmSimMoSmControlReq;

typedef struct CcmSimReadSmspReq_Tag
{
    UINT8               recordNum;  /* currently support recordNum = 1 */
    UINT8               reserved0;
    UINT16              reserved1;
}CcmSimReadSmspReq;

typedef struct CcmSimReadSmspCnf_Tag
{
    UINT8                rcCode; //CcmSimCnfRc
    BOOL                 smspDataValid;
    UINT16               reserved;
    SimSmsParams         smsp;
}CcmSimReadSmspCnf;

typedef struct CcmSimWriteSmspReq_Tag
{
    UINT8               recordNum;  /* currently support recordNum = 1 */
    UINT8               reserved0;
    UINT16              reserved1;
    SimSmsParams        smsp;
}CcmSimWriteSmspReq;


typedef struct CcmSimWriteSmspCnf_Tag
{
    UINT8                 rcCode; //CcmSimCnfRc
}CcmSimWriteSmspCnf;

typedef struct CcmSimWriteSmssReq_Tag
{
    BOOL                msgRefPresent;
    BOOL                capExceedPresent;
    UINT8               msgRef;
    BOOL                capExceed;
}CcmSimWriteSmssReq;

typedef enum USATMeProblemAddInfo_Tag
{
    USAT_NO_CAUSE_GIVEN          = 0x00,
    USAT_SMS_NOT_ALLOWED         = 0x01
}USATMeProblemAddInfo;


typedef struct CcmSmsSendMsgCnf_Tag
{
    UINT8        msgReference;//TP Message Reference
    UINT8        statusReport; //SmsStatusOfReport CP/RP/TP error indication
    UINT8        rpCause;   //CP and RP failure cause  RpCause
    UINT8        tpCause;   //TpCause
    UINT8        requestStatus;   //CcmSmsRequestStatus
    UINT8        pduLen;
    BOOL         meProblemPresent;
    UINT8        meProblem; //USATMeProblemAddInfo  TODO
    UINT8       *pdu;

}CcmSmsSendMsgCnf;

typedef struct CcmSmsCommandCnf_Tag
{
    UINT8        msgReference;//TP Message Reference
    UINT8        requestStatus;   //CcmSmsRequestStatus
}CcmSmsCommandCnf;


/******************************************************************************
 * CemmSmtlDeliveredInd
 * SIG_CEMM_SMTL_DELIVERED_IND,
 * New MT SMS received indication from CEMM
******************************************************************************/
#define     RP_DIAGNOSTIC_OK                  0
#define     MAX_SMS_RAW_ADDRESS               11
#define     MAX_SMS_TPDU_INFO_LEN             0xE8
#define     SMS_MAX_PDU_DATA_LEN              0x8C


typedef enum VpFormat_Tag
{
    VP_NOT_PRESENT               =   0,
    VP_ENHANCED,
    VP_INTEGER_FORMAT,
    VP_SEMI_OCTET,
    VP_RESERVED
}VpFormat;

typedef enum SmsCoding_Tag
{
    SMS_CODING_DEFAULT           = 0x00,
    SMS_CODING_8BIT              = 0x01,
    SMS_CODING_UCS2              = 0x02,
    SMS_CODING_RESERVED          = 0x03,
}SmsCoding;

typedef enum SmsClass_Tag
{
    SMS_CLASS0                   = 0x00,
    SMS_CLASS1                   = 0x01,
    SMS_CLASS2                   = 0x02,
    SMS_CLASS3                   = 0x03,
    SMS_CLASS_NOT_GIVEN,
}SmsClass;

typedef enum ProtocolMeaning_Tag
{
    SM_AL_PROTOCOL            = 0x00,
    TELEMATIC_INTERWORK       = 0x20,
    SM_FUNCTIONS              = 0x40,
    ME_FUNCTIONS              = 0x60,
    RESERVED                  = 0x80,
    SC_SPECIFIC               = 0xc0,
}ProtocolMeaning;

typedef enum TypeOfNumber_Tag
{
    NUM_UNKNOWN                      =   0,
    NUM_INTERNATIONAL,
    NUM_NATIONAL,
    NUM_NETWORK_SPEC,
    NUM_SUBSCRIBER,
    NUM_ALPHANUMERIC,
    NUM_ABBREVIATED,
    NUM_RESERVED
}TypeOfNumber;

typedef struct RawSmsAddress_Tag
{
    UINT8 len;
    UINT8 data[MAX_SMS_RAW_ADDRESS];
}RawSmsAddress;

typedef struct RpUserDataElement_Tag
{
    UINT16    tpduLen;
    UINT16    reserved0;
    UINT8    *tpduInfo;
}RpUserDataElement;

typedef struct RpUserData_Tag
{
    UINT16     len;
    UINT16     reserved0;
    UINT8     *rpUserData;
}RpUserData;


typedef struct CemmSmtlDeliveredInd_Tag
{
   MsgAddress                        smeAddr;
   MsgAddress                        scAddr;
   SmsProtocolId                     smsProtocolId;
   SmsDataCoding                     smsDataCodingScheme;
   UINT8                             smsId;
   BOOL                              tpRpSetting;   /*reply path setting*/
   BOOL                              tpSriSetting;  /*status report setting*/
   UINT8                             smsLen;
   UINT8                             *smsData;
   UINT8                             scTimeStamp[MAX_SMS_TIMESTAMP_LEN];
   UINT16                            reserved0;
   BOOL                              tpMMSsetting;
   BOOL                              udhPresent; /*user Data Header Present or not setting*/
   UINT8                             smsRef;
   UINT8                             reserved1;
   RawSmsAddress                     rawScAddr;
   RpUserDataElement                 rawTpdu;
}CemmSmtlDeliveredInd;

typedef struct RpCauseElement_Tag
{
    UINT8               cause;  //RpCause
    UINT8               diagnostic;
    UINT16              reserved0;
}RpCauseElement;


/******************************************************************************
 * CemmSmtlReportInd
 * SIG_CEMM_SMTL_REPORT_IND,
 * MO SMS sending status from CEMM
******************************************************************************/

typedef enum SmsStatusOfReport_Tag
{
    TRANSFER_OK   =0,
    TRANSFER_ERROR
}SmsStatusOfReport;

typedef enum RpCause_Tag
{
    /* CEMM-SMRL Cause */
    RP_CAUSE_NO_ERROR                       = 0,
    RP_CAUSE_UNALLOCATED_NUM                = 1,
    RP_CAUSE_CALL_BARRED                    = 10,
    RP_CAUSE_SMS_TRANSFER_REJ               = 21,
    RP_CAUSE_MEMORY_EXCEED                  = 22,
    RP_CAUSE_DEST_OUT_OF_ORDER              = 27,
    RP_CAUSE_TEMPORARY_FAILURE              = 41,
    RP_CAUSE_CONGESTION                     = 42,
    RP_CAUSE_RESOURCE_UNAVAILABLE           = 47,
    RP_CAUSE_INVALID_SMS_TRANSFER_REF_VALUE = 81,
    RP_CAUSE_INVALID_MANDATORY_INFO         = 96,
    RP_CAUSE_MESSAGE_TYPE_NON_EXIST         = 97,
    RP_CAUSE_UNSPECIFIED_PROTOCOL_ERR       = 111,

    /* CEMM-SMCM Cause */
    CP_CAUSE_NO_ERROR   ,
    CP_CAUSE_ACK_NOT_RECEIVED,
    CP_CAUSE_SERVICE_TEMP_OUT_OF_ORDER,

    CP_CAUSE_ACCESS_CLASS_BARRED
}RpCause;

typedef enum TpCause_Tag
{
    TP_CAUSE_NO_ERROR                       =   0,
    /* TP-PID Errors 80-8F */
    TP_CAUSE_TELEMATIC_INTERWORKING_NOT_SUPPORT        =   0x80,
    TP_CAUSE_SMS_TYPE0_NOT_SUPPORTED,
    TP_CAUSE_CANT_REPLACE_SMS,
    TP_CAUSE_UNSPECIFIED_TPPID_ERROR        =   0x8F,

    /* TP-DCS Errors 90-9F */
    TP_CAUSE_DCS_NOT_SUPPORTED         =   0x90,
    TP_CAUSE_MSG_CLASS_NOT_SUPPORTED,
    TP_CAUSE_UNSPECIFIED_TP_DCS_ERROR  =   0x9F,

    /* TP-Command Errors  A0-AF */
    TP_CAUSE_COMMAND_CANT_ACTION            =   0xA0,
    TP_CAUSE_COMMAND_UNSUPPORTED,
    TP_CAUSE_UNSPECIFIED_TP_COMMAND_ERROR      =   0xAF,

    /* Others */
    TP_CAUSE_TPDU_NOT_SUPPORTED             =   0xB0,

    TP_CAUSE_SC_BUSY                        =   0xC0,
    TP_CAUSE_NO_SC_SUBSCRIPTION,
    TP_CAUSE_SC_SYSTEM_FAILURE,
    TP_CAUSE_INVALID_SME_ADDRESS,
    TP_CAUSE_DESTINATION_SME_BARRED,
    TP_CAUSE_SM_REJECTED_DUPLICATE_SM,
    TP_CAUSE_VPF_NOT_SUPPORTED,
    TP_CAUSE_VP_NOT_SUPPORTED,

    TP_CAUSE_USIM_STORAGE_FULL               =   0xD0,
    TP_CAUSE_NO_SMS_CAPABILITY_IN_SIM,
    TP_CAUSE_ERROR_IN_MS,
    TP_CAUSE_MEMORY_CAPACITY_EXCEEDED,
    TP_CAUSE_USIM_APPLICATION_TOOLKIT_BUSY,
    TP_CAUSE_USIM_DATA_DOWNLOAD_ERROR,

    TP_CAUSE_UNSPECIFIED_ERR              =   0xFF
}TpCause;

typedef enum CcmSmsAbortCause_Tag
{
    SIM_NOT_OK    =0,  /* SIM NOT cause */

    //TBD

}CcmSmsAbortCause;

typedef struct CemmSmtlReportInd_Tag
{
   UINT8                            shortMsgId;
   UINT8                            msgRef; //Message Reference
   UINT8                            statusOfReport;  //SmsStatusOfReport
   UINT8                            tpCause;    //TpCause
   RpCauseElement                   rpCause;    //RpCause
   RpUserData                       rpUserData;
   UINT16                           tpduRawDatLen;
   UINT16                           reserved0;
   UINT8                           *tpduRawDat;
}CemmSmtlReportInd;

typedef struct CcmSmsAbortReq_Tag
{
    UINT8                        cause; //CcmSmsAbortCause
}CcmSmsAbortReq;

typedef enum SmsStatusReportQualifier_Tag
{
    SMS_ST_RESULT_FOR_SUBMIT,
    SMS_ST_RESULT_FOR_COMMAND
}SmsStatusReportQualifier;

/*refer TS23.040 9.2.3.15*/
typedef enum TpStatus_Tag
{
   TP_ST_SMS_RECEIVED_BY_SME            =   0,
   TP_ST_SMS_FWD_TO_SME_BY_SC,
   TP_ST_SMS_REPLACED_BY_SC,
    /*Temporary error*/
   TP_ST_TEMP_CONGESTION             =   32,
   TP_ST_TEMP_SME_BUSY,
   TP_ST_TEMP_NO_RESPONSE_FROM_SME,
   TP_ST_TEMP_SERVICE_REJ,
   TP_ST_TEMP_QUALITY_SER_NOT_AVALIABLE,
   TP_ST_TEMP_ERROR_IN_SME,
    /*Permanent error*/
   TP_ST_PER_REMOTE_PROC_ERR            =   64,
   TP_ST_PER_INCOMPAT_DEST,
   TP_ST_PER_CONN_REJ_BY_SME,
   TP_ST_PER_NOT_OBTAINABLE,
   TP_ST_PER_QUALITY_SER_NOT_AVAILABLE,
   TP_ST_PER_NO_INTERWORK_AVAILABLE,
   TP_ST_PER_SM_VALIDITY_EXPIRED,
   TP_ST_PER_SM_DELETE_BY_ORIG_SME,
   TP_ST_PER_SM_DELETE_BY_SC_ADMIN,
   TP_ST_PER_SM_NOT_EXIST,

   TP_ST_TEMP_SC_CONGESTION             =   96,
   TP_ST_TEMP_SC_SME_BUSY,
   TP_ST_TEMP_SC_NO_RESPONSE,
   TP_ST_TEMP_SC_SERVICE_REJ,
   TP_ST_TEMP_SC_QUAL_SER_NAV,
   TP_ST_TEMP_SC_ERROR_IN_SME,

}TpStatus;

typedef struct CemmSmtlStusReptInd_Tag
{
    UINT8                            smsId;
    UINT8                            msgRef; //Message Reference
    BOOL                             moreMsgSent;
    UINT8                            stReptQualifier; //SmsStatusReportQualifier
    MsgAddress                       scAddr;
    MsgAddress                       reciptAddr;
    UINT8                            scTimeStamp[MAX_SMS_TIMESTAMP_LEN];
    UINT16                           reserved0;
    UINT8                            destTime[MAX_SMS_TIMESTAMP_LEN];
    UINT8                            tpStatus; //TpStatus
    UINT8                            reserved1;
}CemmSmtlStusReptInd;

typedef struct CemmSmtlSmsServiceAvailInd_Tag
{
    BOOL                            serviceAvailable;
}CemmSmtlSmsServiceAvailInd;

typedef struct CcmSimSmsPpDownloadReq_Tag
{
    MsgAddress                        scAddr;
    UINT8                             tpduLen;
    UINT8                            *tpdu;
    BOOL                              smeAddrPresent;
    MsgAddress                        smeAddr;
}CcmSimSmsPpDownloadReq;

typedef struct CcmSimSmsDisplayAlphaIdReq_Tag
{
    UINT8                          moSmsResult;  //MoSmsControlResult
    BOOL                           alphaIdPresent;
    UINT8                          type;  //CcmSimAlphaIdType
    SimAlphaId                     alphaId;
} CcmSimSmsDisplayAlphaIdReq;

typedef struct CcmSimSendSmQual_Tag
{
    BOOL          smsPackingRequired;
}CcmSimSendSmQual;


typedef union UsatSmsTpdu_Tag
{
    CemmSmsCommandReq           command;
    CemmSmsSendMessageReq       submit;
}UsatSmsTpdu;

typedef struct CcmSimSmsProactiveMessageInd_Tag
{
    UINT32                          cmdDetailsRef;
    UINT8                           tpduType;
    UsatSmsTpdu                     smsTpdu;
} CcmSimSmsProactiveMessageInd;


typedef struct CcmSimSmsSendSmRsp_Tag
{
    UINT32                        cmdDetailsRef;
    UINT8                         generalResult;  //UsatGeneralResult
    BOOL                          smsProblemPresent;
    UINT8                         smsProblem;  //CeNasSmsFailureCause
    BOOL                          meProblemPresent;
    UINT8                         meProblem;
    UINT8                         reserved;
    UINT16                        reserved1;
}CcmSimSmsSendSmRsp;




#endif

