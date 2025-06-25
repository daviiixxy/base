#ifndef __UICC_CTRL_SIG_H__
#define __UICC_CTRL_SIG_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - uiccctrlsig.h
Description:    - define all signals received by UiccCtrl module.
Function List:  -
History:        - 09/05/2017, Originated by xlhu
******************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
//#include "pscommutil.h"
#include "uiccctrldata.h"
#include "pssys.h"
#include "ccmsmssig.h"
/*********************************************************************************
* Macros
*********************************************************************************/
#define     MAX_SELECTION_PATH_LEN              10

//AccessTechnologyId
#define     UICC_NB_DEFAULT_ACCESS_TECH_ID      0x40
#define     UICC_MAX_MOBILE_ID_LENGTH                        16


#define COMBINE_UINT16(highByte,lowByte)     ((((UINT16)(highByte)) << 8) | (lowByte))
#define GET_HIGH_BYTE(Uint16)             ((UINT8)(((Uint16)) >> 8))
#define GET_LOW_BYTE(Uint16)              ((UINT8)((Uint16) & 0x00ff))

/*********************************************************************************
* Type Definition
*********************************************************************************/


/********************************************************************************
* MM->UiccCtrl
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/
typedef enum UsatRefreshTypeTag
{
    USAT_REFRESH_FILE_CHANGE_NOTIFY,
    USAT_REFRESH_STEER_OF_ROAMING,
    USAT_REFRESH_UNKNOWN = 0xFF
}
UsatRefreshType;

typedef enum CemmSimPowerReduceTypeTag
{
    CEMM_SIM_PR_TY_ENTER_PSM = 0x01,
    CEMM_SIM_PR_TY_ENTER_EDRX,
    CEMM_SIM_PR_TY_LEAVE_PSM_EDRX
}
CemmSimPowerReduceType;




/*********************************************************************************
* STRUCTS
*********************************************************************************/


/*
 * CEMM -> UICC, read PLMN info request
*/
typedef struct SimPlmnReadReqDataTag
{
    UINT16  startField; /* First read start from 0, then caculate from last readCnf with totalEntries*/
}SimPlmnReadReqData;

/*
 * SIGID: SIG_CEMM_SIM_READ_DATA_REQ
*/
typedef struct CemmSimReadDataReqTag
{
    UINT8   reqItem;   /*CemmSimReqItem: request item determined to the uicc file Id */
    UINT8   reserved0;
    UINT16  reserved1;

    /*
     * CEMM_REQ_RW_EPSLOCI => PNULL;
     * CEMM_REQ_RW_EPSNSC => PNULL;
     * CEMM_REQ_R_FPLMN/CEMM_REQ_R_UPLMN/CEMM_REQ_R_HPLMN/CEMM_REQ_R_OPLMN/CEMM_REQ_R_EHPLMN => SimPlmnReadReqData
    */
    UINT8   reqData[];  /*request parameter for read uicc file data, e.g. (SimPlmnReadReqData *)reqData used for PLMN read */
}CemmSimReadDataReq;


/*
 * CEMM -> UICC, DEL PLMN info request
*/
typedef struct SimPlmnDelReqDataTag
{
    BOOL    bDelAllFplmn;
    UINT8   reserved0;
    UINT16  reserved1;

    UiccPlmnList    plmn;
}SimPlmnDelReqData;


/*
 * SIGID: SIG_CEMM_SIM_WRITE_DATA_REQ
*/
typedef struct CemmSimWriteDataReqTag
{
    UINT8   reqItem;     /* CemmSimReqItem: request item determined to the uicc file Id */
    UINT8   reserved0;
    UINT16  reserved1;
    /*
     * CEMM_REQ_RW_EPSLOCI => EpsLocationInfo;
     * CEMM_REQ_RW_EPSNSC => EpsNscInfo;
     * CEMM_REQ_ADD_FPLMN => UiccPlmnList
     * CEMM_REQ_DEL_FPLMN => SimPlmnDelReqData
    */
    UINT8   reqData[];
}CemmSimWriteDataReq;


/******************************************************************************
 * Authentication parameter RAND
 *
******************************************************************************/
/*
#define RAND_SIZE   16
typedef struct RandTag
{
    UINT8   length;
    UINT8   reserved0;
    UINT16  reserved1;
    UINT8   data[RAND_SIZE];
}Rand;

#define AUTN_SIZE   16
typedef struct  AutnTag
{
    UINT8   length;
    UINT8   reserved0;
    UINT16  reserved1;
    UINT8   data[AUTN_SIZE];
}Autn;
*/
#define RAND_SIZE   16
#define AUTN_SIZE   16

/*
 * SIGID: SIG_CEMM_SIM_AUTHENTICATE_REQ
*/
typedef struct CemmSimAuthenticateReqTag
{
    UINT8   ksi;    //NasKsi
    UINT8   reserved0;
    UINT16  reserved1;
    UINT8   rand[RAND_SIZE];
    UINT8   autn[AUTN_SIZE];
}CemmSimAuthenticateReq;

/*
 * SIGID: SIG_CEMM_SIM_ECM_STATE_IND
*/
typedef struct CemmSimEcmStateIndTag
{
    BOOL        isConnection;//TRUE:connection state; FALSE:Idle state
    UINT8       reserved1;
    UINT16      reserved2;
}
CemmSimEcmStateInd;

/*
 * SIGID: SIG_CEMM_SIM_USAT_REFRESH_RSP
*/
typedef struct CemmSimUsatRefreshRspTag
{
    UINT32                            cmdDetailsRef;
}
CemmSimUsatRefreshRsp;


/*
 * SIGID: SIG_CEMM_SIM_USAT_IMEI_SV_CNF
*/
typedef struct CemmSimUsatImeiSVCnfTag
{
    UINT32                            cmdDetailsRef;
    UINT8                             reserved1;
    UINT16                            reserved2;
    UINT8                             numOfDigit;
    UINT8                             idDigit[UICC_MAX_MOBILE_ID_LENGTH];
}
CemmSimUsatImeiSVCnf;

/*
* SIG_CEMM_SIM_POWER_REDUCE_IND
*/
typedef struct CemmSimPowerReduceIndTag
{
    UINT8                       type;//CemmSimPowerReduceType
    UINT8                       reserved1;
    UINT16                      reserved2;
}
CemmSimPowerReduceInd;

/********************************************************************************
* CCM->UiccCtrl
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/
typedef enum UsatOperTerminalprofileTag
{
    USAT_TERMINAL_PROFILE_READ,
    USAT_TERMINAL_PROFILE_SET
}
UsatOperTerminalprofile;

typedef enum UsatAddiInfoChannlStatusTag
{
    CHANNEL_STATUS_NO_FURTHER_INFO_GIVEN = 0x00,
    CHANNEL_STATUS_LINK_DROPPED = 0x05
}
UsatAddiInfoChannlStatus;

typedef enum UsatLocationStatusTag
{
    LOCATION_STATUS_NORMAL_SERVICE = 0x00,
    LOCATION_STATUS_LIMITED_SERVICE = 0x01,
    LOCATION_STATUS_NO_SERVICE = 0x02,
    LOCATION_STATUS_UNDEFINE = 0xFF
}
UsatLocationStatus;

typedef enum UsatUpdateAttachTypeTag
{
    USAT_EPS_ATTACH                 = 0x09,
    USAT_COMBINED_EPS_IMSI_ATTACH   = 0x0A,
    USAT_TA_UPDATING                = 0x0B,
    USAT_PERIODIC_UPDATING          = 0x0E

}
UsatUpdateAttachType;

typedef enum UsatGeneralResultTag
{
    USAT_GR_CMD_PERFORMED_OK               = 0x00,
    USAT_GR_CMD_PERFORMED_PARTIAL_COMPREHENSION      = 0x01,
    USAT_GR_CMD_PERFORMED_MISS_INFO        = 0x02,
    USAT_GR_REFRESH_ADDITIONAL_EF_READ      = 0x03,
    USAT_GR_CMD_PERFORMED_OK_NO_ICON       = 0x04,
    USAT_GR_CMD_PERFORMED_OK_MOD_BY_CC     = 0x05,
    USAT_GR_CMD_PERFORMED_OK_LIMIT_SERVICE      = 0x06,
    USAT_GR_CMD_PERFORMED_OK_WITH_MOD      = 0x07,
    USAT_GR_REFRESH_APP_INACTIVE           = 0x08,
    USAT_GR_PROAC_SESSION_TERMINATE_BY_USER          = 0x10,
    USAT_GR_USER_REQ_BACK_MOVE         = 0x11,
    USAT_GR_USER_NO_RESPONSE           = 0x12,
    USAT_GR_USER_REQ_HELP_INFO         = 0x13,
    USAT_GR_USSD_SS_TRANS_USER_TERMINATE    = 0x14,
    USAT_GR_ME_CANNOT_PROC_COMMAND     = 0x20,
    USAT_GR_NET_CANNOT_PROC_COMMAND    = 0x21,
    USAT_GR_USER_REJ_PROACTIVE_CMD     = 0x22,
    USAT_GR_USER_CLEAR_DOWN            = 0x23,
    USAT_GR_CONTRADICT_CURR_TIMER_STATE      = 0x24,
    USAT_GR_MOD_BY_CC_TEMP_PROB        = 0x25,
    USAT_GR_BROWSER_GEN_ERROR          = 0x26,
    USAT_GR_CMD_BEYOND_ME_CAP         = 0x30,
    USAT_GR_CMD_TYPE_UNKNOWN_BY_ME    = 0x31,
    USAT_GR_CMD_DATA_UNKNOWN_BY_ME    = 0x32,
    USAT_GR_CMD_NUM_UNKNOWN_BY_ME     = 0x33,
    USAT_GR_SS_RETURN_ERROR            = 0x34,
    USAT_GR_SMS_RP_ERROR               = 0x35,
    USAT_GR_ERR_REQ_VALUES_MISSING      = 0x36,
    USAT_GR_USSD_RETURN_ERROR          = 0x37,
    USAT_GR_CC_OR_MOSM_PERM_PROB       = 0x39,
    USAT_GR_BIP_ERROR                  = 0x3A,
    USAT_GR_ACCESS_TECHNO_UNAVAILABLE  = 0x3B
}
UsatGeneralResult;

typedef enum UsatAddiInfoMeProblemTag
{
    USAT_ADDI_INFO_NO_CAUSE_GIVEN           = 0x00,
    USAT_ADDI_INFO_SCREEN_BUSY              = 0x01,
    USAT_ADDI_INFO_ME_BUSY_ON_CALL          = 0x02,
    USAT_ADDI_INFO_ME_BUSY_ON_SS            = 0x03,
    USAT_ADDI_INFO_NO_SERVICE               = 0x04,
    USAT_ADDI_INFO_ACC_CONT_CLASS_BAR       = 0x05,
    USAT_ADDI_INFO_RAD_RES_NOT_GRANTED      = 0x06,
    USAT_ADDI_INFO_NOT_IN_SPEECH_CALL       = 0x07,
    USAT_ADDI_INFO_ME_BUSY_ON_USSD          = 0x08,
    USAT_ADDI_INFO_ME_BUSY_ON_DTMF          = 0x09,
    USAT_ADDI_INFO_ME_NO_APP_ACTIVE         = 0x0a
}
UsatAddiInfoMeProblem;

typedef enum UsatAddiInfoBipProblemTag
{
    USAT_ADDI_INFO_BIP_NO_CAUSE_GIVEN       = 0x00,
    USAT_ADDI_INFO_BIP_NO_CHANNEL_AVAIL     = 0x01,
    USAT_ADDI_INFO_BIP_CHANNEL_CLOSED       = 0x02,
    USAT_ADDI_INFO_BIP_CHANNEL_ID_INVALID   = 0x03,
    USAT_ADDI_INFO_BIP_REQ_BUFFER_SIZE_UNAVAIL = 0x04,
    USAT_ADDI_INFO_BIP_SECURITY_ERROR       = 0x05,
    USAT_ADDI_INFO_BIP_TRANS_LEVEL_UNAVAIL  = 0x06,
    USAT_ADDI_INFO_BIP_REMOTE_DEV_NOT_REACH = 0x07,
    USAT_ADDI_INFO_BIP_SERVICE_ERROR        = 0x08,
    USAT_ADDI_INFO_BIP_SERVICE_ID_UNKNOWN   = 0x09,
    USAT_ADDI_INFO_BIP_PORT_UNAVAIL         = 0x10

}
UsatAddiInfoBipProblem;

typedef enum UiccWriteCounterModeTag
{
    UICC_WRITE_COUNTER_DISBALE = 0,
    UICC_WRITE_COUNTER_ENBALE = 1,
    UICC_WRITE_COUNTER_QUERY = 2,
    UICC_WRITE_COUNTER_CLEAR = 3,
    UICC_WRITE_COUNTER_UNDEF = 0xFF
}
UiccWriteCounterMode;

typedef enum UiccSleepModeTag
{
    UICC_SLEEP_DISABLE = 0,
    UICC_SLEEP_ENABLE = 1,
    UICC_SLEEP_NUM = 0xFF
}
UiccSleepMode;


/*********************************************************************************
* STRUCTS
*********************************************************************************/
typedef struct UiccPathTag
 {
    UINT8           reserved1;
    UINT16          reserved2;
    UINT8           length;
    UINT8           data[MAX_SELECTION_PATH_LEN];
 }
 UiccPath;

 typedef struct UiccPinValueTag
 {
     UINT8                            pinValue[UICC_PIN_VALUE_LENGTH];
 }
 UiccPinValue;

typedef struct UiccSmspReadReqParamTag
{
    UINT8                  recordNum;
    UINT8                  reserved1;
    UINT16                 reserved2;
}
UiccSmspReadReqParam;

typedef struct UiccSmspUpdateReqParamTag
{
    UINT8                  recordNum;
    UINT8                  reserved1;
    UINT16                 reserved2;
    SimSmsParams           smsp;
}
UiccSmspUpdateReqParam;

typedef CcmSimWriteSmssReq  UiccSmssUpdateReqParam;

typedef struct UsatLocationInfoTag
{
    Plmn            plmn;
    UINT16          tac;
    UINT16          reserved;
    UINT32          cellId;
}
UsatLocationInfo;

typedef struct UsatChannelStatusTag
{
    UINT8                           channelId;
    BOOL                            linkEstOrPsActive;
    UsatAddiInfoChannlStatus        addiInfo;
    UINT8                           reserved;
}
UsatChannelStatus;

typedef struct UsatEventLocationStatusTag
{
    UsatLocationStatus              locationStatus;
    UINT8                           reserved1;
    UINT16                          reserved2;
    UsatLocationInfo                locationInfo;
}
UsatEventLocationStatus;

typedef struct UsatEventNetworkRejectTag
{
    Plmn                        plmn;
    UINT16                      tac;
    UINT16                      accessTech;//UsatAccessTechnology
    UsatUpdateAttachType        updateAttachType;
    UINT16                      rejectCause;//EmmCause
    UINT8                       reserved;
}
UsatEventNetworkReject;

typedef struct UsatEventDataAvailableTag
{
    UsatChannelStatus           channelStatus;
    UINT8                       channelDataLength;
    UINT8                       reserved1;
    UINT16                      reserved2;
}
UsatEventDataAvailable;

typedef struct UsatEventChannelStatusTag
{
    UsatChannelStatus           channelStatus;
}
UsatEventChannelStatus;

/*********************************************************************************
*SIGNAL STRUCT
*********************************************************************************/
/*
 * SIGID: SIG_CCM_SIM_APP_INIT_REQ
*/
typedef GosEmptySignal CcmSimAppInitialiseReq;
#if 0
typedef struct CcmSimAppInitialiseReqTag
{
    UINT8                    keyRefValue;   //UiccKeyRefValue
    BOOL                     verifyPin1;
    BOOL                     unblockPin1;
    UINT8                    reserved;
    UiccPinValue             pinValue;     //PIN1 value
    UiccPinValue             unblockPinValue; /* Unblock pin value */
}
CcmSimAppInitialiseReq;
#endif
/*
 * SIGID: SIG_CCM_SIM_GEN_ACCESS_REQ
*/
typedef struct CcmSimGenAccessReqTag
{
    UiccPath                    path;
    UINT8                       cmdRef;
    UINT8                       logicChNum;
    UINT16                      length;
    UINT8                       command[];//MAX_APDU_DATA_LEN
}
CcmSimGenAccessReq;


/*
 * SIGID: SIG_CCM_SIM_GEN_LOGICAL_CHANNEL_ACCESS_REQ
*/
typedef struct CcmSimGenLogicalChAccessReqTag
{
    UINT8                       resvd;
    UINT8                       logicChNum;
    UINT16                      length;
    UINT8                       command[];//MAX_APDU_DATA_LEN
}
CcmSimGenLogicalChAccessReq;


/*
 * SIGID: SIG_CCM_SIM_TERMINATE_SESSION_REQ
*/
typedef struct CcmSimTerminateSessionReqTag
{
    UINT8          tsCause;/* TerminateSessionCause */
    UINT8          reserved1;
    UINT16         reserved2;
}
CcmSimTerminateSessionReq;

/*
 * SIGID: SIG_CCM_SIM_READ_DATA_REQ
*/
typedef struct CcmSimReadDataReqTag
{
    UINT8                 reqItem; /* CcmReqItem */
    UINT8                 reserved1;
    UINT16                reserved2;
    /*
    *  CCM_REQ_R_ADMINDATA/CCM_REQ_R_IMSI/CCM_REQ_R_SPN/CCM_REQ_R_PNN/CCM_REQ_R_ACL => PNULL
    *  CCM_REQ_RW_SMSP  => UiccSmspReadReqParam
    *  CCM_REQ_RW_SMSS  => NULL
    */
    UINT8                 reqData[];/*request parameter for read uicc file data, e.g. (SimPlmnReadReqData *)reqData used for EFsmsp read */
}
CcmSimReadDataReq;

/*
 * SIGID: SIG_CCM_SIM_UPDATE_DATA_REQ
*/
typedef struct CcmSimUpdateDataReqTag
{
    UINT8                   reqItem; /* CcmReqItem */
    UINT8                   reserved1;
    UINT16                  reserved2;
    /*
    *  CCM_REQ_RW_SMSP  => UiccSmspUpdateReqParam
    *  CCM_REQ_RW_SMSS  => UiccSmssUpdateReqParam
    */
    UINT8                   reqData[];/*request parameter for write uicc file data, e.g. (UiccSmspUpdateReqParam *)reqData used for EFsmsp read */

}
CcmSimUpdateDataReq;

/*
 * SIGID: SIG_CCM_SIM_PIN_OPERATE_REQ
*/
typedef struct CcmSimPinOperateReqTag
{
    BOOL                         bClckSet;//if set by +CLCK
    UINT8                        pinFunction; // UiccPinFunction
    UINT8                        pinKeyReference;//UiccKeyRefValue
    UINT8                        altPinKeyReference;//UiccKeyRefValue
    UiccPinValue                 pinValue;
    UiccPinValue                 newPinValue;
}
CcmSimPinOperateReq;

/*
 * SIGID: SIG_CCM_SIM_OPEN_LOGICAL_CHANNEL_REQ
*/
typedef struct CcmSimOpenLogicalChannelReqTag
{
    UINT8                       aidLength;
    UINT8                       reserved1;
    UINT16                      reserved2;
    UINT8                       aidData[UICC_AID_MAX_LEN];
}
CcmSimOpenLogicalChannelReq;

/*
 * SIGID: SIG_CCM_SIM_CLOSE_LOGICAL_CHANNEL_REQ
*/
typedef struct CcmSimCloseLogicalChannelReqTag
{
    UINT8                       sessionId;
    UINT8                       reserved1;
    UINT16                      reserved2;
}
CcmSimCloseLogicalChannelReq;

/*
 * SIGID: SIG_CCM_SIM_SET_SIM_WRITE_COUNTER_REQ
*/
typedef struct CcmSimSetSimWriteCntReqTag
{
    UINT8                       mode;//UiccWriteCounterMode
    UINT8                       reserved1;
    UINT16                      reserved2;
}
CcmSimSetSimWriteCntReq;


/*
 * SIGID: SIG_CCM_SIM_SET_SIM_PRESENCE_DETECT_REQ
*/
typedef struct CcmSimSetSimPresenceDetectReqTag
{
    BOOL                        bPresenceDetect;
    UINT8                       reserved1;
    UINT16                      reserved2;
}
CcmSimSetSimPresenceDetectReq;

/*
 *SIGID:SIG_CCM_SIM_RESTORE_DATA_REQ
*/
typedef struct CcmSimRestoreDataReqTag
{
    UINT8           cfunState;//CcmDevPowerStateEnum
    UINT8           reserved1;
    UINT16          reserved2;
}
CcmSimRestoreDataReq;

/*
 *SIGID:SIG_CCM_SIM_GET_SUBSCRIBER_NUMBER_REQ
*/
typedef struct CcmSimGetSubscriberNumberReqTag
{
    UINT8                       srcId;
    UINT8                       reserved1;
    UINT16                      reserved2;
}
CcmSimGetSubscriberNumberReq;

/*
 * SIGID: SIG_CCM_SIM_SET_SIM_SLEEP_REQ
*/
typedef struct CcmSimSetSimSleepReqTag
{
    UINT8                       mode;//UiccSleepMode
    UINT8                       reserved1;
    UINT16                      reserved2;
}
CcmSimSetSimSleepReq;


/*********************************************************************************
*CCM_USAT -> UiccCtrl
*********************************************************************************/

/*
 * SIGID: SIG_CCM_SIM_USAT_TERMINAL_PROFILE_REQ
*/
typedef struct CcmSimUsatTerminalProfileReqTag
{
    UINT8               operMode;//UsatOperTerminalprofile
    BOOL                bUsatCommEnable;//USAT common except bip enable or not
    UINT8               reserved;
    UINT8               length;
    UINT16              reserved2;
    UINT8               profileValue[MAX_TP_LEN];
}
CcmSimUsatTerminalProfileReq;



/*
 * SIGID: SIG_CCM_SIM_USAT_REFRESH_RSP
*/
typedef struct CcmSimUsatRefreshRspTag
{
    UINT32                            cmdDetailsRef;
    UINT8                             generalResult;//UsatGeneralResult
    BOOL                              addiInfoMeProblemPresent;
    UINT8                             addiInfoMeProblem;//UsatAddiInfoMeProblem
    UINT8                             reserved;
}
CcmSimUsatRefreshRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_PROVIDE_LOCAL_INFO_RSP
*/
typedef struct CcmSimUsatProvideLocalInfoRspTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           generalResult;//UsatGeneralResult
    BOOL                            addiInfoMeProblemPresent;
    UINT8                           addiInfoMeProblem;//UsatAddiInfoMeProblem
    UsatLocationInfo                locationInfo;
}
CcmSimUsatProvideLocalInfoRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_SET_UP_EVENT_LIST_RSP
*/
typedef struct CcmSimUsatSetUpEventListRspTag
{
    UINT32                          cmdDetailsRef;
    //UINT8                           generalResult;//UsatGeneralResult
    //BOOL                            addiInfoMeProblemPresent;
    //UINT8                           addiInfoMeProblem;//UsatAddiInfoMeProblem
    //UINT8                           reserved;
}
CcmSimUsatSetUpEventListRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_OPEN_CHANNEL_RSP
*/
typedef struct CcmSimUsatOpenChannelRspTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           generalResult;//UsatGeneralResult
    BOOL                            addiInfoMeProblemPresent;
    UINT8                           addiInfoMeProblem;//UsatAddiInfoMeProblem
    BOOL                            addiInfoBipProblemPresent;
    UINT8                           addiInfoBipProblem;//UsatAddiInfoBipProblem
    UINT8                           reserved;
    UINT16                          bufferSize;
    UsatChannelStatus               channelStatus;
    UsatBearerDescription           bearerDesc;
}
CcmSimUsatOpenChannelRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_CLOSE_CHANNEL_RSP
*/
typedef struct CcmSimUsatCloseChannelRspTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           generalResult;//UsatGeneralResult
    BOOL                            addiInfoMeProblemPresent;
    UINT8                           addiInfoMeProblem;//UsatAddiInfoMeProblem
    BOOL                            addiInfoBipProblemPresent;
    UINT8                           addiInfoBipProblem;//UsatAddiInfoBipProblem
    UINT8                           reserved1;
    UINT16                          reserved2;
}
CcmSimUsatCloseChannelRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_SEND_DATA_RSP
*/
typedef struct CcmSimUsatSendDataRspTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           generalResult;//UsatGeneralResult
    BOOL                            addiInfoMeProblemPresent;
    UINT8                           addiInfoMeProblem;//UsatAddiInfoMeProblem
    BOOL                            addiInfoBipProblemPresent;
    UINT8                           addiInfoBipProblem;//UsatAddiInfoBipProblem
    UINT8                           availTxBufferLen;
    UINT16                          reserved;
}
CcmSimUsatSendDataRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_RECEIVE_DATA_RSP
*/
typedef struct CcmSimUsatReceiveDataRspTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           generalResult;//UsatGeneralResult
    BOOL                            addiInfoMeProblemPresent;
    UINT8                           addiInfoMeProblem;//UsatAddiInfoMeProblem
    BOOL                            addiInfoBipProblemPresent;
    UINT8                           addiInfoBipProblem;//UsatAddiInfoBipProblem
    UINT8                           reserved;
    UINT8                           remainChannelDataLen;
    UINT8                           channelDataLength;
    UINT8                           channelData[USAT_SEND_DATA_MAX_LEN];

}
CcmSimUsatReceiveDataRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_GET_CHANNEL_STATUS_RSP
*/
typedef struct CcmSimUsatGetChannelStatusRspTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           generalResult;//UsatGeneralResult
    BOOL                            addiInfoMeProblemPresent;
    UINT8                           addiInfoMeProblem;//UsatAddiInfoMeProblem
    BOOL                            addiInfoBipProblemPresent;
    UINT8                           addiInfoBipProblem;//UsatAddiInfoBipProblem
    UINT16                          reserved;
    UINT8                           numChannels;
    UsatChannelStatus               channel[USAT_MAX_NUM_CHANNELS];
}
CcmSimUsatGetChannelStatusRsp;

/*
*SIGID:SIG_CCM_SIM_USAT_EVENT_DOWNLOAD_REQ
*/
typedef struct CcmSimUsatEventDownloadReqTag
{
    UINT8                   eventType; /* UsatEventType */
    UINT8                   reserved1;
    UINT16                  reserved2;
    /*
    * eventType                     =>      eventDownloadBody
    *
    * USAT_EVENT_LOCATION_STATUS    =>      UsatEventLocationStatus
    * USAT_EVENT_DATA_AVAILABLE     =>      UsatEventDataAvailable
    * USAT_EVENT_NETWORK_REJECTION  =>      UsatEventNetworkReject
    * USAT_EVENT_CHANNEL_STATUS     =>      UsatEventChannelStatus
    */
    UINT8                   eventDownloadBody[];
}
CcmSimUsatEventDownloadReq;


/*
 * SIGID: SIG_CCM_SIM_USAT_SMS_PP_DOWNLOAD_REQ
*/

/*typedef struct CcmSimUsatSmsPpDownloadReqTag
{
    UsatAddress                        scAddress;
    BOOL                               smeAddressPresent;
    UINT8                              tpduLen;
    UINT16                                  reserved;
    UINT8                             *tpdu;
    UsatAddress                        smeAddress;
}
CcmSimUsatSmsPpDownloadReq;
*/
typedef struct CcmSimUsatSmsPpDownloadReqTag
{
    UINT32                          cmdDetailsRef;
    CemmSmtlDeliveredInd             deliveredInd;
}
CcmSimUsatSmsPpDownloadReq;


/*
 * SIGID: CCM_SIM_USAT_MOSM_CONTOL_REQ
*/
typedef struct CcmSimUsatMoSmControlReqTag
{
    UsatAddress                        scAddress;
    UsatAddress                        smeAddress;
    BOOL                               locationInfoPresent;
    UINT8                              reserved;
    UINT16                             reserved1;
    UsatLocationInfo                   locationInfo;
}
CcmSimUsatMoSmControlReq;

/*
 * SIGID: SIG_CCM_SIM_USAT_SEND_SM_RSP
*/
typedef struct CcmSimUsatSendSmRspTag
{
    UINT32                            cmdDetailsRef;
    UINT8                             generalResult;//UsatGeneralResult
    BOOL                              smsProblemPresent;
    UINT8                             smsProblem;
    BOOL                              meProblemPresent;
    UINT8                             meProblem;
    UINT8                             reserved;
    UINT16                            reserved1;
}
CcmSimUsatSendSmRsp;

/********************************************************************************
* UiccDrv->UiccCtrl
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/
typedef enum UiccErrorTag
{
    UICC_OVERRUN_ERROR,
    UICC_RECEIVE_ERROR,
    UICC_TRANSMIT_ERROR,
    UICC_NOT_RESPONDING
}
UiccError;

/*********************************************************************************
* STRUCTS
*********************************************************************************/

/*
 * SIGID: SIG_UICC_CTRL_DRV_CARD_INSERTED_IND
 * Sent when a card insertion detected and establish init Communication(ATR/PPS).
*/
typedef struct  UiccCtrlDrvCardInsertedIndTag
{
    UINT8                    uiccVoltage;     //UiccVoltage
    BOOL                     globalIfBytes;
    BOOL                     efDirPresent;                  /*EF DIR present on the UICC ?*/
    BOOL                     selectByFullDf;                /*select by full DF allowed ? */
    BOOL                     selectByPartialDf;             /*select by partial DF allowed ? */
    BOOL                     selectByPath;                  /*select by PATH allowed ? */
    BOOL                     selectBySfi;                   /*select by SFI allowed ? */
    BOOL                     logicalChAssignedByCard;
    BOOL                     logicalChAssignedByMe;
    UINT8                    logicalChannelMaxNum;          /* 0- not supported,  value 8 - means 8 and more */
    BOOL                     clockStopAllowed;               /*Clock stop mode support ? */
    UINT8                    reserved;
	BOOL					 eUiccSupport;					/*ESIM support? */
}
UiccCtrlDrvCardInsertedInd;

/*
 * SIGID: SIG_UICC_CTRL_DRV_CMD_RSP
 * Returned data has been received from the card. It consists of a data block
 * containing a R-APDU coded as described in TS 102 221 section 11.
 */
typedef struct  UiccCtrlDrvCmdRspTag
{
    UINT16                           rspApduLength;          /* response apdu data length */
    UINT8                            rspApduData[];          /* response apdu data contents */
}
UiccCtrlDrvCmdRsp;

/*
 * SIGID: SIG_UICC_CTRL_DRV_LARGE_APDU_RSP
 *
 */
typedef struct  UiccCtrlDrvLargeApduRspTag
{
    UINT16                           rspApduLength;          /* response apdu data length */
    UINT8                            *rspApduData;          /* response apdu data contents */
}
UiccCtrlDrvLargeApduRsp;


/*
 * SIGID: SIG_UICC_CTRL_DRV_CARD_REMOVED_IND
*/
typedef GosEmptySignal UiccCtrlDrvCardRemovedInd;

/*
 * SIGID: SIG_UICC_CTRL_DRV_ERROR_IND
*/
typedef struct UiccCtrlDrvErrorIndTag
{
    UINT8                      uiccError;//UiccError
    UINT8                      reserved1;
    UINT16                     reserved2;
}
UiccCtrlDrvErrorInd;

/********************************************************************************
* UiccCtrl->UiccCtrl
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/

/*********************************************************************************
* STRUCTS
*********************************************************************************/

/*
 * SIGID:SIG_USAT_PROACTIVE_CMD_TO_FETCH_REQ
*/
typedef struct UiccUsatProactiveCmdToFetchReqTag
{
    UINT8           fetchSize;
    UINT8           reserved1;
    UINT16          reserved2;
}
UiccUsatProactiveCmdToFetchReq;


#endif
