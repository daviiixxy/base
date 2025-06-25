#ifndef _CEMM_GLOBALS_H_
#define _CEMM_GLOBALS_H_
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - cemmglobals.h
Description:    - Define the EMM globals.
Function List:  -
History:        - 12/12/2017, Originated by flxing
*******************************************************************************/

/******************************************************************************
 * Includes
*******************************************************************************/

#include "nascommon.h"
#include "cenascomm.h"
#include "cerrcsig.h"
#include "ccmsig.h"
#include "cemmesmmsg.h"
#include "cemmsmsmsg.h"
#include "cemmplmnmsg.h"
#include "cemmssmsg.h"

/******************************************************************************
* Macros
*******************************************************************************/

#define     TAI_DELETED                             0xFFFE
#define     MAX_NUM_FORBIDDEN_TAI_LIST              40
#define     MAX_PARTIAL_TAI_LIST_SIZE               16
#define     MAX_TAI_LIST_SIZE                       16
#define     MAX_TAC_LIST_SIZE                       16
#define     MAX_AUTHENTICATION_FAIL_COUNTER         3
#define     MAX_NUM_OF_MM_CONNECTION                7
#define     MAX_LENGTH_OF_EMM_MESSAGE               200
#define     MAX_NUM_OF_DCN_ID_LIST                  32
#define     ESTIMATED_MSG_LEN_OF_ATTACH_REQ         53
#define     ESTIMATED_MSG_LEN_OF_TAU_REQ            56
#define     ESTIMATED_MSG_LEN_OF_SERVICE_REQ        4
#define     ESTIMATED_MSG_LEN_OF_CTR_SERVICE_REQ    8
#define     ESTIMATED_MSG_LEN_OF_DETACH_REQ         15

#define     TAU_FOR_SMS_ONLY_MAX_COUNT              7
#define     DL_EMM_MSG_HASH_VALUE_MAX_LEN           8
#define     MAX_NUM_OF_TRANS_FAILURE_MESSAGE        5

#define     MAX_CP_DATA_CACHE_QUEUE_SIZE            3

#define     MIN_NAS_MSG_INDEX_OF_DATA               17
#define     MAX_NAS_MSG_INDEX_OF_DATA               255

#define     UL_MSG_SEND_DELAY_RECORDS_NUM           3

#define     MAX_DL_OVER_FLOW_COUNT_EST_NUM          50


/* Update USIM file flag */
#define     UPDATE_EPS_LOCI     0x01    /* EPS location information */
#define     UPDATE_EPS_SNSC     0x02    /* EPS NAS security context */
#define     DELETE_EPS_SNSC     0x04

/* Update ERRC flag */
#define     UPDPATE_GUTI        0x01    /* GUTI */
#define     UPDATE_EDRX         0x02    /* eDrx */
#define     UPDATE_SIM          0x04    /* SIM */
#define     UPDATE_RPLMN        0x08    /* SIM */
#define     UPDATE_RESTRIC_EC   0x10    /* Restriction of Enhanced Coverage */

#define     PLUS_TIMER_PERIOD_IN_NB_MODE    240

#define     TIMEOUT_PERIOD_T3325                SECONDS_TO_TICKS(60)
#define     TIMEOUT_PERIOD_T3402                MINUTES_TO_MILLISECONDS(12)
#define     TIMEOUT_PERIOD_T3410                SECONDS_TO_TICKS(15 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_T3411                SECONDS_TO_MILLISECONDS(10)
#define     TIMEOUT_PERIOD_T3412S               (54 * 60)
#define     TIMEOUT_PERIOD_T3416                SECONDS_TO_TICKS(30 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_T3417                SECONDS_TO_TICKS(5 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_T3418                SECONDS_TO_TICKS(20 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_T3420                SECONDS_TO_TICKS(15 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_T3421                SECONDS_TO_TICKS(15 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_T3430                SECONDS_TO_TICKS(15 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_T3440                SECONDS_TO_TICKS(10)
#define     TIMEOUT_PERIOD_T3449                SECONDS_TO_TICKS(5 + PLUS_TIMER_PERIOD_IN_NB_MODE)
#define     TIMEOUT_PERIOD_POWER_OFF            SECONDS_TO_TICKS(20)                    /* In order to shorten power off timer  */
#define     TIMEOUT_PERIOD_FORBIDDEN_TA         SECONDS_TO_MILLISECONDS(12 * 60 * 60)   /* The length of the timer shall be in the range 12 to 24 hours */
#define     TIMEOUT_PERIOD_SIG_RETRANSMIT       SECONDS_TO_MILLISECONDS(4)
#define     TIMEOUT_PERIOD_TIMER_DEACTIVATED    0xF00000A0                              /* Guaranteeed to be a multiple of 1000, because T3412 is in seconds */
#define     TIMEOUT_PERIOD_MAX_LOG_TIME         MINUTES_TO_TICKS(120)
#define     TIMEOUT_PERIOD_SR_THROT_TIME        SECONDS_TO_TICKS(60)

/* Operator defines  */
#define NO_OPERATOR 0x00
#define ATT 0x01
#define VZW 0x02
#define TMO 0x03
#define TELSTRA 0x05
#define KT 0x06
#define LGU 0x07
#define DT 0x08
#define TEST 0x10

#define SR_RETRY_MAX_COUNTER    3   /* Service Request retry max counter */
/******************************************************************************
* Enum and Structure
*******************************************************************************/

typedef struct TrackingInformationTag
{
    Guti                guti;
    Tai                 tai;
    UINT8               numOfTaiList;
    PartialTaiList     *pTaiList;
    EpsUpdateStatus     epsUpdateStatus;
}
TrackingInformation;

typedef struct KeyNasIntTag
{
    UINT8    data[IK_SIZE];
}
KeyNasInt;

typedef struct KeyNasEncTag
{
    UINT8    data[CK_SIZE];
}
KeyNasEnc;

typedef enum TypeOfNativeEpsSecurityContexTag
{
    FULL_NATIVE,
    PARTIAL_NATIVE
}
TypeOfNativeEpsSecurityContex;

typedef struct SecurityContextTag
{
    NasKeySetIdentifier                     nasKsi;
    AsmeKey                                 asmeKey;
    NasCount                                ulNasCount;
    NasCount                                dlNasCount;
    KeyNasInt                               nasIntKey;
    KeyNasEnc                               nasEncKey;
    IntegrityAlgorithm                      integrityAlgorithm;
    CipheringAlgorithm                      encryptionAlgorithm;
    TypeOfNativeEpsSecurityContex           nativeType;
}
SecurityContext;

typedef struct SecurityInformationTag
{
    SecurityContext     currentSecurityContext;     /* The security context which has been activated most recently. */
    SecurityContext     nonCurrentSecurityContext;  /* A native EPS security context that is not the current one */
    BOOL                resetUlCount;
    BOOL                useSpecialUlCount;
    NasCount            specialUlCount;
}
SecurityInformation;

typedef struct AuthenticateResultTag
{
    UINT8           sqnXorAK[6];
    UINT8           lastRand[RAND_SIZE];
    AuthRes         lastRes;
    Auts            auts;
    EmmCause        result;
    EmmCause        lastResult;
    UINT8           failTimes;
}
AuthenticateResult;

typedef struct SimInformationTag
{
    BOOL                    simPresent;
    BOOL                    simInvalidForEps;
    BOOL                    simInvalidForSms;
    Imsi                    imsi;
    UINT16                  accessClass;
    TrackingInformation     epsLocationInfo;
    UINT8                   writeSimFlag;
    CkIkContent             keys;
    AuthenticateResult      authticateResult;
    UINT8                   algorithmId;        /* The identifiers of selected NAS integrity and encryption algorithms */
    NasConfig               nasConfig;
    EPSFilePresentType      epsFilePresentType;
}
SimInformation;

typedef struct NwPsmInformationTag
{
    BOOL                t3324Valid;
    GprsTimer2          t3324Value;
    BOOL                t3412ExtValid;
    GprsTimer3          t3412ExtendedValue;
}
NwPsmInformation;

typedef struct UePsmInformationTag
{
    UINT8               t3324Mode;              //CemmPsmReqModeEnum
    GprsTimer2          t3324Value;
    UINT8               t3412ExtMode;           //CemmPsmReqModeEnum
    GprsTimer3          t3412ExtendedValue;
}
UePsmInformation;

typedef struct NwEdrxInformationTag
{
    ExtendedDrxParameters       extendedDrxParameters;
    BOOL                        valid;
}
NwEdrxInformation;

typedef struct UeEdrxInformationTag
{
    ExtendedDrxParameters       extendedDrxParameters;
    UINT8                       edrxMode;               //CemmEdrxReqModeEnum
}
UeEdrxInformation;

typedef struct EmmEventStatisInfo_Tag
{
    BOOL    eventMode;
    UINT16  numAttachSucc;      /* count of Attach Success */
    UINT16  numAttachFail;
    UINT16  numTauSucc;         /* count of TAU Success */
    UINT16  numTauFail;
    UINT16  numSrSucc;          /* count of Service request Success */
    UINT16  numSrFail;
    UINT16  numAuthFail;        /* count of Authentication Success */
    UINT16  numDetach;          /* count of Detach */
    UINT16  numOOS;             /* count of PLMN, OOS */
    UINT8   reverse0;

}
EmmEventStatisInfo;

typedef struct nvmInformationTag
{
    BOOL                    smsOnly;                /* UE requested EPS service and 'SMS only' */
    BOOL                    tauForSmsControl;       /* Control if sms register fail, need tau for sms */
    BOOL                    attachWithoutPdn;       /* UE requested EPS Attach without PDN connection */
    UINT32                  userSetT3324Value;
    UINT16                  minT3324Value;          /* AT+QCPSSLPCFG set minT3324 */
    UINT32                  minT3412Value;          /* AT+QCPSSLPCFG set minT3412 */
    UINT16                  minEdrxValue;           /* AT+QCPSSLPCFG set minEDRXPeriod */
    CemmCiotOptTypeEnum     ciotOptimization;
    CemmCiotOptTypeEnum     preferedCiotOptimization;
    MobileIdentity          imei;   /* The International Mobile station Equipment Identity */
    UINT8                   svn[2]; /* Software Version Number (SVN) identifies the software version number of the mobile equipment */
    UeNetworkCapability     ueNetworkCapability;    /* default value:{0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0xFC, 0x01} */
    UePsmInformation        uePsmInfo;              /* UE configured PSM information */
    UeEdrxInformation       ueEdrxInfo;             /* UE configured eDRX information */
    EmmEventStatisInfo      emmEventInfo;           /* Emm Event statis Info */
    UINT8                   CserviceCountDam;       /* Dam specific Cservice Count   */
    UINT8                   maxEventCounter;
    UINT16                  maxLogTime;
    UINT8                   overWriteLapi;          /* This setting can be used by user to overwrite LAPI functionality in SIM card */
    BOOL                    isPsmUpdated;
    BOOL                    isDRXUpdated;
    BOOL                    RoamingInfo;
    BOOL                    overrideLrplmnsi;
    UINT16                  userSetBarValue;
    UINT8                   bEnableHPPlmnSearch;
}
nvmInformation;

typedef struct MultiPlmnTag
{
    UINT8       numOfPlmn;
    UINT8       selectedIndex;
    Plmn        plmnIdentity[6];
}
MultiPlmn;

typedef struct SysInformationTag
{
    Tai         tai;
    BOOL        bTaiSame;
    BOOL        bPlmnSame;
    BOOL        attachWithoutPdn;
    UINT32      cellIdentity;
    UINT32      carrierFreq;
    UINT16      phyCellId;
    UINT8       freqBandIndicator;
    //MultiPlmn   multiPlmn;
}
SysInformation;

typedef enum EmmSpecificProceduresTag
{
    PROCEDURE_NONE = 0,
    PROCEDURE_EPS_ATTACH,
    PROCEDURE_EPS_AND_NON_EPS_ATTACH,
    PROCEDURE_PERIODIC_TAU,
    PROCEDURE_NORMAL_TAU,
    PROCEDURE_COMBINED_TAU,
    PROCEDURE_CONTROL_PLANE_SERVICE,
    PROCEDURE_EPS_DETACH
}
EmmSpecificProcedures;

typedef struct EmmProceduresTag
{
    BOOL                    bProcedureOngoing;
    EmmSpecificProcedures   emmSpecificProcedure;
}
EmmProcedures;

typedef struct CemmSignalBufferTag
{
    SignalBuf                       *rx;
    EmmMessage                      *pUlEmmMsg;
    EmmMessage                      *pDlEmmMsg;
    TcMessage                       *pDlTcMsg;
    SecurityProtectedNasMessage      ulProtectedEmmMsg;
    SecurityProtectedNasMessage      dlProtectedEmmMsg;
    CemmEsmUnitDataReq              *pendingUlEsmMsg;
    CemmEsmUnitDataReq              *pendingUlExceptioData;
    CemmEsmUnitDataInd               pendingDlEsmMsg;
    NasMessageContainer              pendingSmsMsg;
    CemmSsUnitDataReq               *pendingSsMsg;

    /*
     * PLAIN MSG: 24.301 - 9.7
     * NAS MSG don't contain "Security protected NAS message" header,
     * and raw message before/after cipher/decipher
    */
    NasPlainMsg                      nasPlainMsg;   // 70 bytes

    /* 9.9.3.51 Replayed NAS message container */
    ReplayedNasMessageContainer      replayedNasMsg;
}
CemmSignalBuffer;

/* TS-24.301 Subclause 5.1.3.2 EMM sublayer states in the UE */
typedef enum EmmSubStateTag
{
    /* Main states */
    EMM_NULL                                = 0,
    EMM_REGISTERED_INITIATED                = 1,
    EMM_DEREGISTERED_INITIATED              = 2,
    EMM_TRACKING_AREA_UPDATING_INITIATED    = 3,
    EMM_SERVICE_REQUEST_INITIATED           = 4,
    /* Substates of state EMM-DEREGISTERED */
    EMM_DEREGISTERED_NORMAL_SERVICE         = 5,
    EMM_DEREGISTERED_LIMITED_SERVICE        = 6,
    EMM_DEREGISTERED_ATTEMPTING_TO_ATTACH   = 7,
    EMM_DEREGISTERED_PLMN_SEARCH            = 8,
    EMM_DEREGISTERED_NO_IMSI                = 9,
    EMM_DEREGISTERED_ATTACH_NEEDED          = 10,
    EMM_DEREGISTERED_NO_CELL_AVAILABLE      = 11,
    EMM_DEREGISTERED_ECALL_INACTIVE         = 12,
    /* Substates of state EMM-REGISTERED */
    EMM_REGISTERED_NORMAL_SERVICE           = 13,
    EMM_REGISTERED_ATTEMPTING_TO_UPDATE     = 14,
    EMM_REGISTERED_LIMITED_SERVICE          = 15,
    EMM_REGISTERED_PLMN_SEARCH              = 16,
    EMM_REGISTERED_UPDATE_NEEDED            = 17,
    EMM_REGISTERED_NO_CELL_AVAILABLE        = 18,
    EMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM  = 19,
    EMM_REGISTERED_IMSI_DETACH_INITIATED    = 20
}
EmmSubState;

typedef struct CauseInformationTag
{
    EmmCause    rejectCause;
}
CauseInformation;

typedef enum MsgTransResultTag
{
    NOT_REQUESTED            = 0,
    REQUESTD_TRANSMITTING    = 1,
    REQUESTD_TRANSMIT_SUCC   = 2
}
MsgTransResult;

typedef struct AttachInformationTag
{
    UINT8                   attachCounter;
    BOOL                    needComplete;
    BOOL                    waitEsmMsgContainer;    /* This flag means EMM is waiting ESM message container to complete ATTACH REQUEST message */
    UeService               requestService;         /* User requested ATTACH or DETACH service type(default setting or AT command setting) */
    UeService               emmService;             /* EMM maintained registered service type,may different with requestService */
    NwMode                  nwMode;
    CemmPlmnSelectTypeEnum  plmnSelectType;
    Plmn                    requestedPlmn;
    MsgTransResult          attachCompleteTransResult;    /* Attach Comeplete transmit Result */
}
AttachInformation;

typedef struct TauBoolInformationTag
{
    UINT8               tauRequired : 1;
    UINT8               periodicTauNeed : 1;
    UINT8               loadBalancingTau : 1;
    UINT8               tauResponseToPaging : 1;
    UINT8               tauForSmsOnly : 1;
    UINT8               activeFlag : 1;                 /* Request to set active flag */
    UINT8               nwEpsBearerStatusPresent : 1;
    UINT8               pendingTau : 1;
}
TauBoolInformation;

typedef struct TauInformationTag
{
    UINT8               tauCounter;
    BOOL                waitEsmBearerContext;       /* This flag means EMM is waiting EPS bearer context status to complete TAU REQUEST message */
    TauBoolInformation  tauBoolInfo;
    UINT16              epsBearerContextStatus;
    MsgTransResult      tauCompleteTransResult;     /* Tau Comeplete trans Result */
}
TauInformation;

typedef enum SrReasonTag
{
    SR_ESM_SIGNALLING,
    SR_ESM_DATA,
    SR_SMS_SIGNALLING,
    SR_PAGING_RESPONSE,
    SR_DATA,
    SR_SS_SIGNALLING,
    SR_NONE
}
SrReason;

/* pendingRequest flags */
#define PENDING_ESM_SIGNALLING  0x01
#define PENDING_ESM_DATA        0x02
#define PENDING_SMS             0x04
#define PENDING_EPS_PAGING      0x08
#define PENDING_DATA            0x10
#define PENDING_SS              0x20
#define PENDING_GTP_REQUEST     0x40

typedef struct ServiceInformationTag
{
    SrReason        srReason;               /* Service request triggered reason */
    UINT16          pendingRequest;         /* Pending upper layer service request */
    BOOL            bSrTiggeredInIdle;      /* Service request is triggered in IDLE */
    BOOL            activeFlag;             /* Set active flag in Control Plane Service Request */
    BOOL            waitEsmBearerContext;   /* This flag means EMM is waiting EPS bearer context status to complete CONTROL SERVICE REQUEST message */
    UINT8           sigRetransmitCounter;   /* While RACH failed with CESTABLISH_FAIL_T300_EXPIRY,retry MAX 3 times */
	UINT8           serviceRejectCounter;   /* This is SERVICE REJECT Counter */
    UINT8           srCounter;              /* Service Request Attempt Counter */
    UINT8           srRetryCounter;         /* Service Request Retry Counter for the case when PRACH fail due to cell reselection */
}
ServiceInformation;

typedef struct EmmThrottlingInfoTag
{
   UINT8 throttlingCounter;
   Plmn  throttlingPlmn;
} EmmThrottlingInfo;

typedef struct DetachBoolInformationTag
{
    UINT8           bPowerOff : 1;          /* Power off detach */
    UINT8           bSimRefresh : 1;        /* SIM refresh triggered detach */
    UINT8           bSimRemoveDetach : 1;   /* SIM remove triggered detach */
    UINT8           bWaitDetachCnf : 1;     /* Sending detach confirm flag */
    UINT8           reserved : 4;
}
DetachBoolInformation;

typedef struct DetachInformationTag
{
    DetachBoolInformation   detachBoolInfo;
    UINT8                   detachCounter;      /* Detach attempt counter */
    CemmPlmnDeactCause      deactiveReason;     /* Deactivate reason */
}
DetachInformation;

typedef struct MmTimerInformationTag
{
    CenasHibTimer       t3245;
    CenasHibTimer       t3247;
    CenasHibTimer       t3324;
    CenasHibTimer       t3325;
    CenasHibTimer       t3346;
    CenasHibTimer       t3402;
    CenasTimer          t3410;
    CenasHibTimer       t3411;
    CenasHibTimer       t3412s;
    CenasTimer          t3416;
    CenasTimer          t3417;
    CenasTimer          t3418;
    CenasTimer          t3420;
    CenasTimer          t3421;
    CenasTimer          t3430;
    CenasTimer          t3440;
    CenasHibTimer       t3448;
    CenasTimer          t3449;
    CenasTimer          powerOffTimer;
    CenasHibTimer       forbiddenTaTimer;
    CenasHibTimer       blockPlmnTimer;     /* The PLMN + RAT combination provided the reject cause #42 (Severe network failure) */
    CenasTimer          sigRetransmitTimer;
	CenasHibTimer       maxLogTimer;
	CenasHibTimer       emmSrThrottlingTimer;
}
MmTimerInformation;

typedef struct ForbiddenTaiListTag
{
    Tai    data;
    struct ForbiddenTaiListTag  *pNext;
}
ForbiddenTaiList;

typedef struct ForbiddenTaiInformationTag
{
    ForbiddenTaiList        *forRegionalService;    /* #12 */
    ForbiddenTaiList        *forRoaming;            /* #13,#15 */
    UINT8                    numOfForbiddenService;
    UINT8                    numOfForbiddenRoaming;
    UINT16                   reserved;
}
ForbiddenTaiInformation;

typedef struct DcnIdListTag
{
    DedicatedCoreNetworkId   dcnId;
    struct DcnIdListTag     *pNext;
}
DcnIdList;

typedef struct DcnIdListInformationTag
{
    DcnIdList               *dcnIdList;
    UINT8                    numOfDcnIdList;
}
DcnIdListInformation;

typedef enum EmmAttachStateTag
{
    EMM_REG_STATE_ATTACHED,
    EMM_REG_STATE_DETACHED
}
EmmAttachState;

typedef enum EmmConnectionStateTag
{
    EMM_CONN_STATE_IDLE,
    EMM_CONN_STATE_CONNECTED,
    EMM_CONN_STATE_CONNECTING,
    EMM_CONN_STATE_NAS_RELEASE
}
EmmConnectionState;

typedef struct ReTransMsgTag
{
    EmmMessageType           reTransMsgType;
    UINT8                    reTransMsgIndex;
}
ReTransMsg;

typedef struct ReTransmissionTag
{
    EmmMessageType      msgType[MAX_NUM_OF_TRANS_FAILURE_MESSAGE];          /* Record of sent out messages */
    UINT8               msgIndexOfSignaling;                                /* Signaling index from 1 to 5 */
    UINT8               msgIndexOfData;                                     /* Data index from 17 to 255 */
    ReTransMsg          reTransMsg[MAX_NUM_OF_TRANS_FAILURE_MESSAGE];       /* Record of transmission failed message */
}
ReTransmission;

typedef struct MmConnectionTag
{
    UINT8                   tiValue;
    BOOL                    tiFlag;
    BOOL                    connUsed;
}
MmConnection;

typedef struct MmConnectionInformationTag
{
    MmConnection            connection[MAX_NUM_OF_MM_CONNECTION];
    ConnectionFailCause     failureCause;
    UINT8                   pendingConnection;
}
MmConnectionInformation;

typedef struct BlockedPlmnInformationTag
{
    Plmn        sms;                /* SMS services not available in this PLMN */
    Plmn        severeNwFailure;    /* #42 (Severe network failure) */
    Plmn        t3325;
    Plmn        t3402;
    UINT16      blockedTac;
}
BlockedPlmnInformation;

typedef struct MmBoolFlagsTag
{
    UINT32          bEpsAttached : 1;           /* EPS attached */
    UINT32          bAccessBarred : 1;          /* Access barred */
    UINT32          bEncrypted : 1;             /* ciphering of NAS messages is activated */
    UINT32          bIntegrityProtected : 1;    /* integrity protection of NAS messages is activated */
    UINT32          bSecureExchangeSet : 1;     /* secure exchange of NAS message is established */
    UINT32          bIntegrityProtectedMsg : 1; /* Message is integrity protected */
    UINT32          bRbSetUp : 1;               /* User plane radio bearers have been set up */
    UINT32          bStartT3440 : 1;            /* Need start T3440 */
    UINT32          bImeisvRequest : 1;         /* NW requested IMEISV during authentication */
    UINT32          bSuspendSignalling : 1;     /* NAS signalling connection suspend */
    UINT32          bCmMsg : 1;                 /* Cm layer air messages */
    UINT32          bSearchingPlmn : 1;         /* PLMN searching is ongoing */
    UINT32          bPendingPlmnSearch : 1;     /* Any PLMN searching is pending to be executed due to UE is in CONNECTED state */
    UINT32          bActivePsm : 1;             /* Pending Active PSM mode */
    UINT32          bT3324Valid : 1;            /* T3324 is valid means PSM mode is ok to use */
    UINT32          bIdleStateReq : 1;          /* Set to TRUE if received idle state req from PLMN module */
    UINT32          bSuspendedEsm : 1;          /* Has already suspended ESM */
    UINT32          bSuspendedSms : 1;          /* Has already suspended SMS */
    UINT32          bSuspendedSs : 1;           /* Has already suspended SS */
    UINT32          bExceptioData : 1;          /* An exceptional is event triggered */
    UINT32          bT3346ForException : 1;     /* T3346 was started when connection was established with cause set to  "MO exception data" */
    UINT32          bWaitCampInd : 1;           /* Received RRC connection release indication from AS,and waiting AS cell camping indication */
    UINT32          bTestLoopModeH : 1;
    UINT32          bChangeLowPriority : 1;
    UINT32          bDifferentHashValue :1;     /* HASHMME in the SECURITY MODE COMMAND message is different from the hash value locally calculated at the UE */
    UINT32          bLastSignallingPriority : 1;/* Last signalling priority in Attach/Tau/Control Ser Req */
    UINT32          bInLppMeasurement : 1;
    UINT32          bNwRel : 1;                 /* Newwork initiated Release Ind */
    UINT32          bUlMsgSuspend : 1;          /* Uplink NAS message transmission is suspended due to Control Plane RRCConnection re-establishment */
    UINT32          bPlmnSelectStateChange : 1;
    UINT32          bTestNasMessage : 1;
	UINT32          attachApnBlocked : 1;       /* Used for VZW operator if attach APN is blocked */
    UINT32          estFailReselection : 1;     /* Last time RRC connection setup fail with cause CESTABLISH_FAIL_RESELECTION */
	UINT32          bBlockUlEsmDataTrans : 1;   /*Uplink ESM_DATA_TRANSPORT will be blocked if T3440 is running */
   
}
MmBoolFlags;

typedef struct MmFlagsTag
{
    MmBoolFlags             mmBoolFlags;            /* BOOL flalgs */
    ActStatus               cellStatus;             /* active cell status */
    EmmCause                smcRejectCause;         /* Security mode reject cause */
    EmmCause                emmStatusCause;         /* Emm Status message cause */
    EmmMessageType          resumeMsgType;          /* Message type which triggered the resume of NAS signalling */
    UINT8                   updateAsFlag;           /* Flag for sending SIG_CERRC_NAS_INFO_UPDATE_REQ */
    AdditionalUpdateResult  additionalUpdateResult; /* Additional update result */
    DataRelAssistIndEnum    esmRelInd;              /* ESM Release assistance indication */
    BOOL                    waitActCnf;             /* Whether is waiting SIG_CERRC_ACT_CNF */
    BOOL                    updateEpslociToNvm;     /* Pending update EPS location information to NVM */
    BOOL                    updateEpsnscToNvm;      /* Pending uupdate EPS NAS security context to NVM */
    BOOL                    bReEstSucc;             /* Is Re-establishment Succ */
    BOOL                    erasedFlg;              /* Is emm event NVM memory has been cleared */
    BOOL                    eventChangedFlg;        /* Is emm event statis has increased */
    BOOL                    abortPlmn;              /* Is need abort current ongoing PLMN search */
}
MmFlags;

typedef struct EmmMsgHashInfoTag
{
    EmmMessageType      dlMsgType;
    EmmMessageType      ulTransSuccMsgType;
    UINT8               dlHashValue[DL_EMM_MSG_HASH_VALUE_MAX_LEN];
}
EmmMsgHashInfo;

typedef struct CpDataCacheQueueTag
{
    CemmEsmUnitDataReq      *CpData;
    UINT8                    CpDataIndex;
}
CpDataCacheQueue;

typedef struct UlMsgSendDelayTag
{
    UINT32              ulTick;
    UINT16              msgLen;
    UINT32              sendDelayTick;
}
UlMsgSendDelay;

typedef struct MmGlobalsTag
{
    SimInformation              simInfo;                /* contents from sim card */
    nvmInformation              nvmInfo;                /* contents from non-volatile memory */
    SysInformation              sysInfo;                /* values from system information */
    SecurityInformation         securityInfo;           /* NAS security information */
    CauseInformation            causeInfo;              /* Reject cause */
    AttachInformation           attachInfo;             /* ATTACH procedure related information */
    TauInformation              tauInfo;                /* TAU procedure related information */
    ServiceInformation          srInfo;                 /* SERVICE REQUEST procedure related information */
    DetachInformation           detachInfo;             /* DETACH procedure related information */
    MmTimerInformation          timerInfo;              /* Timer related information */
    ForbiddenTaiInformation     forbiddenTaiInfo;       /* Forbidden TAI list information */
    EpsNetworkFeatureSupport    nwFeatureSupportInfo;   /* Network feature support information */
    DcnIdListInformation        dcnId;                  /* Dedicated Core Networks ID */
    ReTransmission              retransmissionInfo;     /* Re-transmit message information */
    MmConnectionInformation     connectionInfo;         /* EMM connections for transport CM layer message */
    BlockedPlmnInformation      blockedPlmnInfo;        /* Blocked plmn information */
    CemmRegStatusEnum           regStatus;              /* Register status to upper layer */
    CemmSignalBuffer            signal;                 /* Signals and pending messages */
    EmmSubState                 emmState;               /* EMM sublayer states */
    EmmConnectionState          emmConnState;           /* EMM connection state */
    EmmProcedures               procedureInfo;          /* EMM specific procedures information */
    MmFlags                     flags;                  /* Event flags */
    EmmMsgHashInfo              emmMsgHashInfo;         /* Emm Msg Hash Info */
    CpDataCacheQueue            cacheCpData[MAX_CP_DATA_CACHE_QUEUE_SIZE];           /* Cache Cp Data (currently only used for conn state) */
    UlMsgSendDelay              ulMsgSendDelay[UL_MSG_SEND_DELAY_RECORDS_NUM];       /* Ul Msg Send Delay */    
	UINT8                       CurrentOperator;        /* Current Operator  */
	EmmThrottlingInfo           emmthrottlingInfo;
	UINT8         				pendingGtpRequest;
	UINT8                       t3402CounterForLgu;
	UINT8                       t3402CounterForCause17Lgu;
}
MmGlobals;


#endif  /* _CEMM_GLOBALS_H_ */

