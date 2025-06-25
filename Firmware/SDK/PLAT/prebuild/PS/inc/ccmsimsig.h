#ifndef __CCM_SIM_SIG_H__
#define __CCM_SIM_SIG_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - ccmsimsig.h
Description:    - Define the signals structure for CCM and UiccCtrl.
Function List:  - 
History:        - 09/05/2017, Originated by xlhu
******************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
#include "pssys.h"
//#include "pscommutil.h"
#include "uiccctrldata.h"
#include "uiccctrlsig.h"
#include "ccmsmssig.h"
/*********************************************************************************
* Macros
*********************************************************************************/
#define     LANGUAGE_LIST_SIZE      10
#define     MAX_IMSI_LENGTH         8
#define     MAX_DIAL_NUMBER_LIST_SIZE 4
#define     USAT_NUM_LANG_CODE_CHARS            2
    
#define    USIM_PNN_LIST_SIZE              10
#define    USIM_MAX_ALPHA_ID_SIZE            80
#define    USIM_ALPHA_LIST_SIZE            10
//#define    MAX_APN_NAME 30
#define    USAT_MAX_TP_SIZE                   64
#define    USIM_APN_LIST_SIZE               10
#define    USAT_MAX_SMS_PP_ACK_LEN        128

/*********************************************************************************
* Type Definition
*********************************************************************************/    


/********************************************************************************
* UiccCtrl->CCMSIM
*********************************************************************************/
/*********************************************************************************
* USIM
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/
typedef enum CardInsertStatusTag
{
    CARD_INSERTED_OK,    
    CARD_INSERTED_UNSUPPORTED,
    CARD_INSERTED_INIT_ERROR
}
CardInsertStatus;

typedef enum UiccInsertStatusTag
{
    UICC_INSERTED_OK,
    UICC_INSERTED_WRONG_SIM,
    UICC_INSERTED_ERROR,
    UICC_INSERTED_USIM_ERROR,
    UICC_INSERTED_UNSUPPORTED_VOLTAGE
}
UiccInsertStatus;

typedef enum LanguageTag
{
    USIM_LANG_GERMAN                 =   0x00,
    USIM_LANG_ENGLISH                =   0x01,
    USIM_LANG_ITALIAN                =   0x02,
    USIM_LANG_FRENCH                 =   0x03,
    USIM_LANG_SPANISH                =   0x04,
    USIM_LANG_DUTCH                  =   0x05,
    USIM_LANG_SWEDISH                =   0x06,
    USIM_LANG_DANISH                 =   0x07,
    USIM_LANG_PORTUGUESE             =   0x08,
    USIM_LANG_FINNISH                =   0x09,
    USIM_LANG_NORWEGIAN              =   0x0A,
    USIM_LANG_GREEK                  =   0x0B,
    USIM_LANG_TURKISH                =   0x0C,
    USIM_LANG_HUNGARIAN              =   0x0D,
    USIM_LANG_POLISH                 =   0x0E,
    USIM_LANG_UNSPECIFIED            =   0x0F,
    USIM_LANG_CZECH                  =   0x20,
    USIM_LANG_HEBREW                 =   0x21,
    USIM_LANG_ARABIC                 =   0x22,
    USIM_LANG_RUSSIAN                =   0x23,
    USIM_LANG_ICELANDIC              =   0x24,
    USIM_LANG_CHINESE                =   0x2F,
    USIM_LANG_NUMBER_OF              =   22,
    USIM_LANG_EMPTY                  =   0xff
}
Language;



typedef enum UiccAppInitStatusTag
{
    UICC_APP_INIT_OK,
    UICC_APP_INIT_FAILED,
    UICC_APP_INIT_FILE_INVALIDATED,
    UICC_APP_INIT_FAILED_ESIM_NO_PROFILE
}
UiccAppInitStatus;

typedef enum UiccRemovedCauseTag
{
    UICC_REMOVED,                    /* UICC removed physically */
    UICC_REMOVED_UNDETECTED,         /* Uicc was not detetced */
    UICC_REMOVED_INVALID_STATUS_RSP  /* Invalid response to STATUS command */
}
UiccRemovedCause;

typedef enum UiccConfirmStatusTag
{
    UICC_CNF_STATUS_OK                  = 0x00,                     /* request successful*/
    UICC_CNF_STATUS_INVALID_PARAMS,         /* invalid parameters in request signal*/
    UICC_CNF_STATUS_MEMORY_PROBLEM,         /*  memory problem in card */
    UICC_CNF_STATUS_FILE_NOT_FOUND,         
    UICC_CNF_STATUS_SERVICE_NOT_AVAILABLE,  
    UICC_CNF_STATUS_SIM_GENERAL_FAULT   = 0x05,      /*  general sim fault  */
    UICC_CNF_STATUS_ACCESS_DENIED,          /*  file access denied */
    UICC_CNF_STATUS_FILE_INVALIDATED,      
    UICC_CNF_STATUS_ALLOC_ERROR,            /*  no memory available in UiccCtrl task*/
    UICC_CNF_STATUS_UICCCTRL_FAULT,         /*  UiccCtrl internal problem*/
    UICC_CNF_STATUS_POWERING_DOWN       = 0x0a,          
    UICC_CNF_STATUS_INVALID_SIM_DATA,       /*  Data returned from the card could not be decoded/ is invalid*/
    UICC_CNF_STATUS_COMMAND_NOT_ALLOWED,    
    UICC_CNF_STATUS_NO_FREE_RECORD,         
    UICC_CNF_STATUS_OK_DATA_INVALID,        /*  the request is OK, but the data is invalid */
    UICC_CNF_STATUS_PIN_BLOCKED         = 0x0f,            /*  PIN code blocked*/
    UICC_CNF_STATUS_USAT_BUSY,             /*  SIM busy processing STK procedure*/
    UICC_CNF_STATUS_UICC_APP_ERROR,          /*  UICC Application Error*/
    UICC_CNF_STATUS_SMS_DDL_ERROR           /*  SIM SMS-PP Data Download Error*/
}
UiccConfirmStatus;

typedef enum TerminateSessionCauseTag
{
    TS_POWER_DOWN,
    TS_REFRESH_WARM_RESET,
    TS_REFRESH_APP_SESSION_RESET,
    TS_REFRESH_3G_SESSION_RESET,
    TS_REFRESH_USIM_INIT,
    TS_PWOER_SAVE_REQ
    
}
TerminateSessionCause;

typedef enum CcmReqItemTag
{
    CCM_REQ_R_ADMINDATA,
    CCM_REQ_R_IMSI,
    CCM_REQ_RW_SMSP,
    CCM_REQ_RW_SMSS,
    CCM_REQ_R_SPN,
    CCM_REQ_R_PNN,
    CCM_REQ_R_ACL,

    CCM_REQ_UNKOWN = 0xFF
}
CcmReqItem;

typedef enum UiccPinFunctionTag
{
    UICC_PIN_FUNCT_VERIFY = 0,
    UICC_PIN_FUNCT_CHANGE =1,
    UICC_PIN_FUNCT_ENABLE = 2,
    UICC_PIN_FUNCT_DISABLE = 3,
    UICC_PIN_FUNCT_UNBLOCK = 4
}
UiccPinFunction;

typedef enum UsatBcdTONTag
{
    USAT_TON_UNKNOWN = 0,
    USAT_TON_INTERNATIONAL =1,
    USAT_TON_NATIONAL = 2,
    USAT_TON_NW_SPEC = 3,
    USAT_TON_RESERVERD = 4
}
UsatBcdTON;

typedef enum UsatBcdNPITag
{
    USAT_NPI_UNKNOWN = 0,
    USAT_NPI_ISDN_TEL =1,
    USAT_NPI_X121_DATA = 3,
    USAT_NPI_F69_TELEX = 4,
    USAT_NPI_PRIVATE = 9,
    USAT_NPI_RESERVERD = 0xf
}
UsatBcdNPI;


/*********************************************************************************
* STRUCTS
*********************************************************************************/

typedef struct LanguagePrefListTag
{    
    UINT8           numEntries;    
    UINT16          firstEntry;
    UINT16          language[LANGUAGE_LIST_SIZE];
    UINT16          totalNumEntries; 
}
LanguagePrefList,LanguageIndList;



typedef struct SmsrRecDataTag
{
    UINT8                            smsrRecordNum;
}
SmsrRecData;

/*
typedef struct AccessPointNameTag
{
     UINT8 length;
     UINT8 name[MAX_APN_NAME];
}
AccessPointName;
*/
typedef struct ApnCtrlListTag
{
    UINT8                 totalNumApns;  
    UINT8                 numApns;  /*num APNs in list below*/
    AccessPointName       apn[USIM_APN_LIST_SIZE];   
} 
ApnCtrlList;

typedef struct UiccAlphaIdTag
{
    UINT16                  length;
    UINT8                   data[USIM_MAX_ALPHA_ID_SIZE];

}
UiccAlphaId;

typedef struct UpdateAclDataTag
{
    UINT8                        position;   /*Indicates the position in the APN list, starts from '0'*/
    AccessPointName              apn;        
    BOOL                         insert;     /* 'FALSE' means the existing APN will be overwritten*/
}
UpdateAclData;

typedef struct CcmSimUiccServiceTag
{
    BOOL              smss;
    BOOL              smsPP;        /* Data download via SMS-PP */
    BOOL              moSmsCtrl;    /* mo sms control by usim */
    UINT8             reserved;
    
}
CcmSimUiccService;

typedef struct CcmSimReadSmspCnfParam_Tag
{
    BOOL                 smspDataValid;
    UINT8                reserved1;
    UINT16               reserved2;
    SimSmsParams         smsp;
}CcmSimReadSmspCnfParam;


typedef struct CcmSimReadSmssCnfParam_Tag
{
    UINT8                rcCode; //CcmSimCnfRc
    UINT8                msgRef;
    BOOL                 capExceed;
    UINT8                reserved;
}CcmSimReadSmssCnfParam;

typedef struct SimDialNumber_Tag
{
    UINT8                   resvd1;
    UINT16                  resvd2;
    UINT8                   alphaIdLen;
    UINT8                   alphaId[SIM_ALPHA_ID_SIZE];
    UINT8                   type;
    UINT8                   dialNumLen;
    UINT8                   dialNum[MAX_SIM_DAIL_NUMBER_LEN];
}
SimDialNumber;

typedef struct SimDialNumberList_Tag
{
    UINT8                   resvd1;
    UINT16                  resvd2;
    UINT8                   totalNum;//total numbers of dialling number list
    SimDialNumber           dialNumberList[MAX_DIAL_NUMBER_LIST_SIZE];
}
SimDialNumberList;

/******************************************************************************
 *   Define signal structure 
******************************************************************************/
/*
*SIGID:SIG_CCM_SIM_APP_STARTED_IND
*/
typedef struct CcmSimAppStartedIndTag
{     
    UINT8                           cardStatus;  //CardInsertStatus
    UINT8                           reserved;
    UINT8                           iccidData[ICCID_LEN]; //Iccid
    
    UINT8                           pin1KeyReference;//UiccKeyRefValue
    UINT8                           pin2KeyReference;//UiccKeyRefValue
    BOOL                            universalPinSupportedByCard;
    BOOL                            verifyUniversalPin;   
    UiccPinStatus                   pin1Status;      
    UiccPinStatus                   pin2Status;  
    UiccPinStatus                   universalPinStatus;     
    UiccPinStatus                   unblockPin1Status;    
    UiccPinStatus                   unblockPin2Status;   
    UiccPinStatus                   unblockUniversalPinStatus;  
}
CcmSimAppStartedInd;

/*
*SIGID:SIG_CCM_SIM_CARD_REMOVED_IND
*/
typedef struct CcmSimCardRemovedIndTag
{
    UINT8                 rmCause;//UiccRemovedCause
    UINT8                 reserved1;
    UINT16                reserved2;
} 
CcmSimCardRemovedInd; 

/*
*SIGID:SIG_CCM_SIM_APP_INIT_CNF
*/
typedef struct CcmSimAppInitialiseCnfTag
{    
    UINT8                           status; //UiccAppInitStatus   
    BOOL                            fdnEnabled;
    BOOL                            aclEnabled;/* Access Point Names control list enabled*/
    UINT8                           keyRef;//UiccKeyRefValue
    UiccPinStatus                   pinStatus;
    Imsi                            imsi;  
    UiccPinStatus                   unblockPinStatus;
    CcmSimUiccService               ccmUsimService;
    BOOL                            proactiveSim;
    UINT8                           reserved1;
    UINT16                          reserved2;
}
CcmSimAppInitialiseCnf;

/*
*SIGID:SIG_CCM_SIM_GEN_ACCESS_CNF
*/
typedef struct CcmSimGenAccessCnfTag
{    
    UINT8                        cmdRef;
    BOOL                         success; /* The returned data from card is ok */
    UINT8                        logicChNum;
    UINT8                        reserved1;
    UINT16                       length;
    UINT16                       reserved2;
    UINT8                        *command;
}
CcmSimGenAccessCnf;

/*
*SIGID:SIG_CCM_SIM_GEN_LOGICAL_CHANNEL_ACCESS_CNF
*/
typedef struct CcmSimGenLogicalChAccessCnfTag
{
    BOOL                         success;
    UINT8                        logicChNum;
    UINT16                       length;
    UINT8                        *command;
}
CcmSimGenLogicalChAccessCnf;

/*
*SIGID:SIG_CCM_SIM_TERMINATE_SESSION_CNF
*/
typedef struct CcmSimTerminateSessionCnfTag     
{
    UINT8                       cnfStatus;//UiccConfirmStatus
    UINT8                       tsCause;//TerminateSessionCause
    UINT16                      reserved;
    
}CcmSimTerminateSessionCnf;

/*
*SIGID:SIG_CCM_SIM_READ_DATA_CNF
*/
typedef struct CcmSimReadDataCnfTag
{
    UINT8                     cnfStatus;//UiccConfirmStatus
    UINT8                     reqItem; //CcmReqItem   
    UINT16                    reserved;
    /*
    * CCM_REQ_RW_SMSP => CcmSimReadSmspCnfParam
    * CCM_REQ_RW_SMSP => CcmSimReadSmssCnfParam
    */
    UINT8                     respData[];
}
CcmSimReadDataCnf;

/*
*SIGID:SIG_CCM_SIM_UPDATE_DATA_CNF
*/
typedef struct CcmSimUpdateDataCnfTag
{
    UINT8                      cnfStatus; //UiccConfirmStatus 
    UINT8                      reqItem;   //CcmReqItem 
    UINT16                     reserved;
    UINT8                      respData[];

}
CcmSimUpdateDataCnf;

/*
*SIGID:SIG_CCM_SIM_PIN_OPERATE_CNF
*/
typedef struct CcmSimPinOperateCnfTag
{
    BOOL                         bClckSet;//if set by +CLCK
    UINT8                        cnfStatus; //UiccConfirmStatus
    UINT8                        pinFunction;//UiccPinFunction
    UINT8                        pinKeyReference;//UiccKeyRefValue
    UINT8                        altPinKeyReference;//UiccKeyRefValue
    BOOL                         pinOperSuccess;
    BOOL                         verifyUniversalPin;
    UINT8                        reserved;
    UiccPinStatus                pinStatus;
    UiccPinStatus                altPinStatus;
    UiccPinStatus                unblockPinStatus;
}
CcmSimPinOperateCnf;

typedef struct CcmSimRestoreDataCnfTag
{
    Imsi            imsi;
    Iccid           iccid;
}
CcmSimRestoreDataCnf;


/*
*SIGID:SIG_CCM_SIM_GET_SUBSCRIBER_NUMBER_CNF
*/
typedef struct CcmSimGetSubscriberNumberCnfTag
{
    UINT8                   srcId;
    UINT8                   cnfStatus; //UiccConfirmStatus
    UINT16                  resvd;
    SimDialNumberList       dialNumList;
}
CcmSimGetSubscriberNumberCnf;


/*
 * SIGID: SIG_CCM_SIM_EPS_CONNECTION_MODE_IND
*/
typedef struct CcmSimEpsConnectModeIndTag
{
    BOOL        isConnection;//TRUE:connection state; FALSE:Idle state
    UINT8       reserved1;
    UINT16      reserved2;
}
CcmSimEpsConnectModeInd;

/*
 * SIGID: SIG_CCM_SIM_OPEN_LOGICAL_CHANNEL_CNF
*/
typedef struct CcmSimOpenLogicalChannelCnfTag
{   
    UINT8                       cnfStatus;//UiccConfirmStatus
    UINT8                       sessionId;
    UINT16                      reserved2;
}
CcmSimOpenLogicalChannelCnf;

/*
 * SIGID: SIG_CCM_SIM_CLOSE_LOGICAL_CHANNEL_CNF
*/
typedef struct CcmSimCloseLogicalChannelCnfTag
{   
    UINT8                       cnfStatus;//UiccConfirmStatus
    UINT8                       reserved1;
    UINT16                      reserved2;
}
CcmSimCloseLogicalChannelCnf;

/*
 * SIGID: SIG_CCM_SIM_SET_SIM_WRITE_COUNTER_CNF
*/
typedef struct CcmSimSetSimWriteCntCnfTag
{   
    UINT8                       cnfStatus;//UiccConfirmStatus
    UINT8                       mode;//UiccWriteCounterMode
    UINT8                       reserved2;
    SimWriteCntList             swcList;
}
CcmSimSetSimWriteCntCnf;

/*
 * SIGID: SIG_CCM_SIM_SET_SIM_PRESENCE_DETECT_CNF
*/
typedef struct CcmSimSetSimPresenceDetectCnfTag
{
    UINT8                       cnfStatus;//UiccConfirmStatus
    UINT8                       resvd1;
    UINT16                      resvd2;
}
CcmSimSetSimPresenceDetectCnf;


/*********************************************************************************
*USAT
*********************************************************************************/
#define     USAT_FILES_MAX_NUM    5
#define     USAT_ALPHA_ID_SIZE    100
#define     USAT_TEXT_ATTRIBUTE_MAX_LEN 100
#define     USAT_MAX_ADDRESS_LEN        16
#define     USAT_MAX_TEXT_STRING_LEN    20    
/*********************************************************************************
* Enums
*********************************************************************************/
typedef enum UsatRefreshQualifierTag
{
    USAT_USIM_INIT_FULL_FILE_CHANGE         = 0x00,
    USAT_FILE_CHANGE_NOTIFICATION            = 0x01,
    USAT_USIM_INIT_FILE_CHANGE_NOTIFI       = 0x02,
    USAT_USIM_INIT                          = 0x03,
    USAT_UICC_RESET                         = 0x04,
    USAT_USIM_APP_RESET                     = 0x05,
    USAT_3G_SESSION_RESET                   = 0x06,
    USAT_STEERING_OF_ROAMING                = 0x07,
    USAT_EUICC_PROFILE_STATE_CHANGE         = 0x09
}
UsatRefreshQualifier;

typedef enum UsatRefreshEnforcePolicyEnumTag
{
    USAT_REFRESH_ENFOREMENT_POLICY_NULL               = 0x00,//indicate the item is not present
    USAT_FORCE_IMMEDIATE_REFRESH_BUSY_ON_MENU         = 0x01,
    USAT_FORCE_IMMEDIATE_REFRESH_BUSY_ON_DATA_CALL    = 0x02,
    USAT_FORCE_IMMEDIATE_REFRESH_BUSY_ON_VOICE_CALL   = 0x04,
    USAT_REFRESH_ENFOREMENT_POLICY_RESERVED           = 0xFF
}
UsatRefreshEnforcePolicyEnum;

typedef enum UsatProvideLocalInfoQualifierTag
{
    USAT_LOCATION_INFO                      = 0x00,
    USAT_IMEI                               = 0x01,
    USAT_NMR                                = 0x02,
    USAT_DATE_TIME_TIMEZONE                 = 0x03,
    USAT_LANGUAGE_SETTING                   = 0x04,
    USAT_TIMEING_ADVANCE                    = 0x05,
    USAT_ACCESS_TECHNOLOGY                  = 0x06,
    USAT_ESN                                = 0x07,
    USAT_IMEISV                             = 0x08
}
UsatProvideLocalInfoQualifier;

typedef enum UsatUtranEutranNmrQualifierTag
{
    USAT_UTRAN_INTRA_FREQUENCY_MEASUREMENTS    = 0x01,
    USAT_UTRAN_INTER_FREQUENCY_MEASUREMENTS    = 0x02,
    USAT_UTRAN_INTER_RAT_GERAN_MEASUREMENTS    = 0x03,
    USAT_UTRAN_INTER_RAT_EUTRAN_MEASUREMENTS   = 0x04,
    USAT_EUTRAN_INTRA_FREQUENCY_MEASUREMENTS   = 0x05,
    USAT_EUTRAN_INTER_FREQUENCY_MEASUREMENTS   = 0x06,
    USAT_EUTRAN_INTER_RAT_GERAN_MEASUREMENTS   = 0x07,
    USAT_EUTRAN_INTER_RAT_UTRAN_MEASUREMENTS   = 0x08
}
UsatUtranEutranNmrQualifier;

typedef enum UsatAddressTypeTag
{
    USAT_ADDRESS_IPV4 = 0x21,
    USAT_ADDRESS_IPV6 = 0x57
}
UsatAddressType;

typedef enum UsatTransportProtocolTypeTag
{
    UDP_UICC_IN_CLIENT_MODE_REMOTE_CONN = 0x01,
    TCP_UICC_IN_CLIENT_MODE_REMOTE_CONN = 0x02,
    TCP_UICC_IN_SERVER_MODE             = 0x03,
    UDP_UICC_IN_CLIENT_MODE_LOCAL_CONN  = 0x04,
    TCP_UICC_IN_CLIENT_MODE_LOCAL_CONN  = 0x05,
    DIRECT_COMMUNICATE_CHANNEL          = 0x06
}
UsatTransportProtocolType;


/*********************************************************************************
* Structs
*********************************************************************************/

typedef struct UsatFileListTag
{
    UINT8               fileNum;
    UINT8               reserved1;
    UINT16              reserved2;
    UiccFilePath        fileList[USAT_FILES_MAX_NUM];
}
UsatFileList;


typedef struct UsatAlphaIdTag
{
    UINT16                         length;
    UINT8                          data[USAT_ALPHA_ID_SIZE];
}
UsatAlphaId;

typedef struct UsatIconIdTag
{
    BOOL                        iconIdPresent;
    BOOL                        displayIconOnly;
    UINT8                       iconId;
    UINT8                       reserved;
}
UsatIconId;

typedef struct UsatTextAttributeTag
{
    UINT8                          length;
    UINT8                          textAttribute[USAT_TEXT_ATTRIBUTE_MAX_LEN];
}
UsatTextAttribute;

typedef struct UsatRefreshEnforcePolicyTag
{
    UINT8                   refreshEnforcePolicy; //UsatRefreshEnforcePolicyEnum
    UINT8                   reserved1;
    UINT16                  reserved2;
}
UsatRefreshEnforcePolicy;

typedef struct UsatEventListTag
{
    BOOL                       locationStatus;
    BOOL                       dataAvailable;
    BOOL                       channelStatus;
    //BOOL                       accessTechnologyChange;
    BOOL                       networkRejection;
}
UsatEventList;

typedef struct UsatOtherAddressTag
{
    BOOL                addressPresent;
    UsatAddressType     addressType;
    UINT8               reserved;
    UINT8               length;//=0/4/16
    UINT8               address[USAT_MAX_ADDRESS_LEN];//IPV4--4bytes; IPV6--16bytes
}
UsatOtherAddress;

typedef struct UsatTextStringTag
{
    //SmsDataCoding           dataCodingScheme;
    UINT8                  reserved1;
    BOOL                    textStringPresent;
    UINT16                   length;
    UINT8                   textString[USAT_MAX_TEXT_STRING_LEN];//tempvalue 20
}
UsatTextString;

typedef struct UsatTransportLevelTag
{
    BOOL                            transLevelPresent;
    UsatTransportProtocolType       transProtocolType;
    UINT16                          portNum;
}
UsatTransportLevel;

/******************************************************************************
 * signal structure 
******************************************************************************/
/*
*SIGID:SIG_CCM_SIM_USAT_TERMINAL_PROFILE_CNF
*/
typedef struct CcmSimUsatTerminalProfileCnfTag
{
    UINT8                      cnfStatus; //UiccConfirmStatus
    UINT8                      operMode; //UsatOperTerminalprofile
    BOOL                       bUsatCommEnable;//USAT common items except bip enable or not
    UINT8                      length;
    UINT8                      profileValue[MAX_TP_LEN];
}
CcmSimUsatTerminalProfileCnf;


/*
*SIGID:SIG_CCM_SIM_USAT_REFRESH_IND
*/
typedef struct CcmSimUsatRefreshIndTag
{
    UINT32                            cmdDetailsRef;
    //UINT8                             cmdQualifier;//UsatRefreshQualifier
    //UINT8                             refreshEnforcePolicy; //UsatRefreshEnforcePolicyEnum
    //UsatAlphaId                       alphaId;
    //UINT16                            alphaIdLength;
    //UINT8                             alphaIddata[USAT_ALPHA_ID_SIZE];
    //UsatIconId                        iconId;
    //UsatTextAttribute                 usatTextAttribute;
    //UINT8                             textAttrLength;
    //UINT8                             textAttribute[USAT_TEXT_ATTRIBUTE_MAX_LEN];
    //BOOL                              frameIdPresent;
    //UINT8                             frameId;
    //BOOL                              plmnListPresent;
    //UiccPlmnList                      plmnList; //TBD
}
CcmSimUsatRefreshInd;

/*
*SIGID:SIG_CCM_SIM_USAT_SET_UP_EVENT_LIST_IND
*/
typedef struct CcmSimUsatSetUpEventListIndTag
{
    UINT32                          cmdDetailsRef;
    BOOL                            rmExistingEventList;//remove the existing list of events
    UINT8                           reserved1;
    UINT16                          reserved2;
    UsatEventList                   eventList;
}
CcmSimUsatSetUpEventListInd;

/*
*SIGID:SIG_CCM_SIM_USAT_PROVIDE_LOCAL_INFO_IND
*/
typedef struct CcmSimUsatProvideLocalInfoIndTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           commandQualifier;//UsatProvideLocalInfoQualifier
    //BOOL                            utranEutranNmrQualPresent;
    //UINT8                           utranEutranNmrQual;//UsatUtranEutranNmrQualifier
    UINT16                          reserved1;
    UINT8                           reserved2;
}
CcmSimUsatProvideLocalInfoInd;

/*
*SIGID:SIG_CCM_SIM_USAT_OPEN_CHANNEL_IND
*/
typedef struct CcmSimUsatOpenChannelIndTag
{
    UINT32                            cmdDetailsRef;
    UsatBearerDescription             bearerDescription;
    //UINT16                            alphaIdLength;//if the length is not zero, the aid is present
    //UINT8                             alphaIddata[USAT_ALPHA_ID_SIZE];
    //UsatIconId                        iconId;
    UsatOtherAddress                  localAddress;
    UsatTextString                    userLogin;
    UsatTextString                    userPassword;
    UsatTransportLevel                transLevel;
    UsatOtherAddress                  destAddress;
    UINT16                            bufferSize;
    UINT8                             reserved;
    UINT8                             apnLength;//if the length is not zero, the apn is present
    UINT8                             apnName[MAX_APN_NAME];
    //BOOL                              frameIdPresent;
    //UINT8                             frameId;
    //UINT8                             textAttrlength;//if the length is not zero, the textAttribute is present
    //UINT8                             textAttribute[USAT_TEXT_ATTRIBUTE_MAX_LEN];
}
CcmSimUsatOpenChannelInd;

/*
*SIGID:SIG_CCM_SIM_USAT_CLOSE_CHANNEL_IND
*/
typedef struct CcmSimUsatCloseChannelIndTag
{
    UINT32                              cmdDetailsRef;
    UINT8                               channelId;
    UINT8                               reserved1;
    UINT16                              reserved2;
}
CcmSimUsatCloseChannelInd;

/*
*SIGID:SIG_CCM_SIM_USAT_SEND_DATA_IND
*/
typedef struct CcmSimUsatSendDataIndTag
{
    UINT32                          cmdDetailsRef;
    BOOL                            sendDataImmediately;//FALSE:store data in Tx buffer;
                                                        //TRUE:send data immediately.
    UINT8                           channelId;
    UINT8                           reserved;
    UINT8                           channelDataLength;
    UINT8                           channelData[USAT_SEND_DATA_MAX_LEN];
}
CcmSimUsatSendDataInd;

/*
*SIGID:SIG_CCM_SIM_USAT_RECEIVE_DATA_IND
*/
typedef struct CcmSimUsatReceiveDataIndTag
{
    UINT32                          cmdDetailsRef;
    UINT8                           channelDataLen;
    UINT8                           channelId;
    UINT16                          reserved2;
}
CcmSimUsatReceiveDataInd;

/*
*SIGID:SIG_CCM_SIM_USAT_GET_CHANNEL_STATUS_IND
*/
typedef struct CcmSimUsatGetChannelStatusIndTag
{
    UINT32                          cmdDetailsRef;
}
CcmSimUsatGetChannelStatusInd;

/*
*SIGID:SIG_CCM_SIM_USAT_EVENT_DOWNLOAD_CNF
*/
typedef struct CcmSimUsatEventDownloadCnfTag
{
    UINT8                      cnfStatus; //UiccConfirmStatus 
    UINT8                      eventType; //UsatEventType 
    UINT16                     reserved;
}
CcmSimUsatEventDownloadCnf;

/* SIG_CCM_SIM_USAT_SMS_PP_DOWNLOAD_CNF */
typedef struct CcmSimUsatSmsPpDownloadCnfTag
{
    UINT32                                cmdDetailsRef;
    UINT8                                 cnfStatus; //UiccConfirmStatus
    UINT8                                 rspDataLen;
    UINT16                                reserved0;
    UINT8                                 usatSmsPpAck[USAT_MAX_SMS_PP_ACK_LEN];
}CcmSimUsatSmsPpDownloadCnf;


/* CCM_SIM_USAT_MO_SM_CONTOL_CNF */
typedef struct CcmSimUsatMoSmControlCnfTag
{
    UINT8                          cnfStatus; //UiccConfirmStatus
    UINT8                          moSmResult;  //UsatMoSmControlResult;
    BOOL                           scAddrPresent;
    BOOL                           destAddrPresent;
    UsatAddress                    scAddr;
    UsatAddress                    destAddr;
    BOOL                           mosmInfoPresent;
    BOOL                           alphaIdPresent;
    UINT16                         reserved0;
    UsatAlphaId                    alphaId;

}CcmSimUsatMoSmControlCnf;

/* CCM_SIM_USAT_SEND_SM_IND */
typedef struct CcmSimUsatSendSmIndTag
{
     UINT32                                 cmdDetailsRef;
     UINT8                                  cnfStatus; //UiccConfirmStatus 
     BOOL                                   smsPackingNeeded;
     BOOL                                   scAddrPresent;
     BOOL                                   partialComprehen;
     UINT8                                  tpduType;
     UsatAddress                            scAddr;
     UsatSmsTpdu                            smsTpdu;
     BOOL                                   alphaIdPresent;
     BOOL                                   iconIdPresent;
     UINT16                                 reserved0;
     UsatAlphaId                            alphaId;
    //UINT16                                alphaIdLength;
    //UINT8                                 alphaIddata[USAT_ALPHA_ID_SIZE];
     UsatIconId                             iconId;
}CcmSimUsatSendSmInd;

#ifdef FEAT_RPM
typedef struct RpmParmeters_Tag
{
    UINT8                   N1;  /* Max number of SW resets per Hour allowed by RPM following "permanent" MM/GMM/EMM reject */
    UINT8                   T1;  /* Average time before RPM resets modem following permanent MM/GMM/EMM reject */
    UINT8                   F1;  /* Max number of PDP Activation Requests / PDN Connectivity Requests per Hour allowed by RPM following a PDP Activation Ignore Scenario */
    UINT8                   F2;  /* Max number of PDP Activation Requests / PDN Connectivity Requests per Hour allowed by RPM following a "Permanent" PDP Activation Reject */
    UINT8                   F3;  /* Max number of PDP Activation Requests / PDN Connectivity Requests per Hour allowed by RPM following a "Temporary" PDP Activation Reject */
    UINT8                   F4;  /* Max number of PDP Context or PDN Connectivity Activation/Deactivation Requests per Hour allowed by RPM */
    UINT8                   T1_ext; /* Average time before RPM resets modem following permanent MM/GMM/EMM reject if T1 = 0xFF */
    UINT8                   reserved;
}RpmParameters;

typedef struct RpmOMParmetersLeakRate_Tag
{
    UINT8                   LR1;  /* Leak rate for C-BR-1 */
    UINT8                   LR2; /* Leak rate for C-R-1 */
    UINT8                   LR3; /* Leak rate for CPDP-1 to C-PDP-4 */
    UINT8                   reserved;
}RpmOMParmetersLeakRate;

typedef struct RpmOMParmeters_Tag
{
    UINT8                   CBR1;  /* Counter related to N1 */
    UINT8                   CR1; /* Counter related to T1 */
    UINT8                   CPDP1; /* Counter related to F1 */
    UINT8                   CPDP2;  /* Counter related to F2 */
    UINT8                   CPDP3; /* Counter related to F3 */
    UINT8                   CPDP4; /* Counter related to F4 */
    UINT8                   reserved;
}RpmOMParmeters;

/*
 * SIGID: SIG_CCM_SIM_RPM_PARAM_IND
*/
typedef struct CcmSimRpmParamIndTag
{
    BOOL                        rpmParamsPresentOnSimCard;
    UINT8                        rpmEnabled;   /* RPM functionality on the device is to be enabled or disabled at power up */
    UINT8                        rpmVersion;   /* version of RPM that has been implemented and shall be updated by the IoT Device on each power up */
    RpmParameters                rpmParameters; /* RPM parameters that are used for the various scenarios */
    RpmOMParmetersLeakRate       rpmOmParamsLeakRate; /* leak rate for RPM operation management counters */
    BOOL                         rpmOmParamsValid;    /* Indicate if RPM OM params present on SIM card */
    RpmOMParmeters               rpmOmParams;  /* RPM operation management counters that are used to assist monitoring and debugging RPM operation issues */
}CcmSimRpmParamInd;

/*
 * SIGID: SIG_CCM_SIM_RPM_UPDATE_OM_PARAM_REQ
*/
typedef struct SimCcmUpdateRpmOmParamReqTag
{
	RpmOMParmeters               rpmOmParams;  /* RPM operation management counters that are used to assist monitoring and debugging RPM operation issues */

}SimCcmUpdateRpmOmParamReq;
#endif


#endif

