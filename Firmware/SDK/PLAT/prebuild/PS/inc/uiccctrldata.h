#ifndef __UICC_CTRL_DATA_H__
#define __UICC_CTRL_DATA_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm Ltd.
File name:      - uiccctrl.h
Description:    - UiccCtrl common data defination
Function List:  -
History:        - 08/30/2017, Originated by xlhu
******************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
#include "pssys.h"
//#include "pscommutil.h"
#include "cemmsig.h"


/*********************************************************************************
* Macros
*********************************************************************************/
#define MAX_TP_LEN   39
#define MAX_NUM_LOGICAL_CHANNELS 4

#define MAX_NUM_APP_PIN                 8
#define USIM_PIN_LENGTH                 8
#define MAX_PIN_ATTEMPTS                3
#define MAX_UNBLOCK_PIN_ATTEMPTS        10
#define MAX_NUM_KEY_REFERENCE          5
#define MAX_DIR_FREE_SPACE             4
#define MAX_NUM_VOLTAGE_CLASSES        3
#define MAX_NUM_PROTOCOLS              2
#define UICC_AID_MAX_SIZE              16
#define UICC_MAX_AID_COUNT             8

#define UICC_DATALEN_VERIFY_PIN   8
#define UICC_DATALEN_CHANGE_PIN   16
#define UICC_DATALEN_DISABLE_PIN  8
#define UICC_DATALEN_ENABLE_PIN   8
#define UICC_DATALEN_UNBLOCK_PIN  16
#define MAX_NUM_KEY_REF           2
#define UICC_LABEL_MAX_SIZE       32
#define UICC_PIN_VALUE_LENGTH     8
#define UICC_RESUME_TOKEN_LENGTH  8
#define UICC_AID_MAX_LEN          16
#define ICCID_LEN                 10
#define MAX_APDU_DATA_LEN         261
#define USAT_SEND_DATA_MAX_LEN    240
#define USAT_MAX_NUM_CHANNELS     7
#define USAT_MAX_TIMER_NUM        8
#define UICC_MAX_ADDR_LEN         20

#define UICC_CLOCK_STOP_TIMER_VALUE 3
#define UICC_POLLING_PRESENCE_DETECT_TIMER_DEFAULT_VALUE 28
#define UICC_WAIT_RESPONSE_TIMER_VALUE 20

#define MAX_SWC_EF_LIST_NUM    20
#define MAX_SIM_DAIL_NUMBER_LEN 10

/*********************************************************************************
* Type Definition
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/

typedef enum UiccCtrlStateTag
{
    UICC_CTRL_INIT_STATE,
    UICC_CTRL_APP_MGMT_STATE,
    UICC_CTRL_APP_ACTIVE_STATE,
    UICC_CTRL_RECOVERY_STATE
}
UiccCtrlState;

typedef enum RecoveryStatusTag
{
    REC_STATUS_OK,
    REC_STATUS_NO_CARD,
    REC_STATUS_ERR_IN_INIT,
    REC_STATUS_ERR_IN_MGMT,
    REC_STATUS_ERR_DIFF_CARD

}
RecoveryStatus;

typedef enum UiccFileStatusTag
{
    FILE_STATUS_OK,
    FILE_STATUS_INVALID,            /* The data does not contain EF status */
    FILE_STATUS_UNKNOWN_STRUCTURE,
    FILE_STATUS_UNEXPECTED_TYPE,
    FILE_STATUS_INVALID_LENGTH
}
UiccFileStatus;


typedef enum UiccSecAttributesFormatTag
{
   USIM_COMPACT_FORMAT,
   USIM_EXPANDED_FORMAT,
   USIM_REF_TO_EXPANDED_FORMAT,
   USIM_UNDEFINED_FORMAT
} UiccSecAttributesFormat;

typedef enum UiccSavedEfIndexTag
{
    UICC_SAVE_EF_DIR,
    UICC_SAVE_EF_SMS,
    UICC_SAVE_EF_MSISDN,
    UICC_SAVE_EF_ARR,
    UICC_SAVE_EF_SMSP,
    UICC_SAVE_EF_SMSR,
    UICC_SAVE_EF_PNN,
    UICC_SAVE_EF_OPL,
    UICC_SAVE_EF_NUM_ENTRIES
}
UiccSavedEfIndex;

typedef enum MeOperationModeTag
{
    ME_OPER_NORMAL                 =   0x00, /* normal operation */
    ME_OPER_TYPE_APPROVAL          =   0x80, /* type approval operation */
    ME_OPER_NORMAL_PLUS_SPECIFIC   =   0x01, /* normal + specific operation */
    ME_OPER_TA_PLUS_SPECIFIC       =   0x81, /* type approval + specific operation */
    ME_OPER_MAINTENANCE            =   0x02, /* maintenance operation */
    ME_OPER_CELL_TEST              =   0x04  /* cell test operation */
}
MeOperationMode;

typedef enum UiccDirIdTag
{
    UICC_DIR_MF                  =   0x3f00,
    UICC_DIR_DF_TELECOM          =   0x7f10,
    UICC_DIR_DF_PHONEBOOK        =   0x5f3a,
    UICC_DIR_ADF_USIM            =   0x7fff,
    UICC_DIR_DF_RPM              =   0x7f66,
    UICC_DIR_DF_ARMED_AGENT      =   0x5f40,
    UICC_DIR_INVALID             =   0x0000
}
UiccDirId;

typedef enum UiccEfIdTag
{
    UICC_EF_ARR_MF               =   0x2f06,
    UICC_EF_DIR                  =   0x2f00,
    UICC_EF_ICCID                =   0x2fe2,
    UICC_EF_PL                   =   0x2f05,
    UICC_EF_UMPC                 =   0x2f08,
    UICC_EF_ARR_TELECOM          =   0x6f06,

    UICC_EF_ACTING_HPLMN         =   0x4F34,
    /* Files under DF MEXE*/
    /* FIles under usim application */
    UICC_EF_LI                   =   0x6f05,
    UICC_EF_ARR                  =   0x6f06,
    UICC_EF_IMSI                 =   0x6f07,
    UICC_EF_KEYS                 =   0x6f08,
    UICC_EF_KEYS_PS              =   0x6f09,
    UICC_EF_DCK                  =   0x6f2c,
    UICC_EF_HPPLMN               =   0x6f31,
    UICC_EF_ACM_MAX              =   0x6f37,
    UICC_EF_UST                  =   0x6f38,
    UICC_EF_ACM                  =   0x6f39,
    UICC_EF_FDN                  =   0x6f3b,
    UICC_EF_SMS                  =   0x6f3c,
    UICC_EF_GID1                 =   0x6f3e,
    UICC_EF_GID2                 =   0x6f3f,
    UICC_EF_MSISDN               =   0x6f40,
    UICC_EF_PUCT                 =   0x6f41,
    UICC_EF_SMSP                 =   0x6f42,
    UICC_EF_SMSS                 =   0x6f43,
    UICC_EF_CBMI                 =   0x6f45,
    UICC_EF_SPN                  =   0x6f46,
    UICC_EF_SMSR                 =   0x6f47,
    UICC_EF_CBMID                =   0x6f48,
    UICC_EF_SDN                  =   0x6f49,
    UICC_EF_EXT2                 =   0x6f4b,
    UICC_EF_EXT3                 =   0x6f4c,
    UICC_EF_BDN                  =   0x6f4d,
    UICC_EF_EXT5                 =   0x6f4e,
    UICC_EF_CBMIR                =   0x6f50,
    UICC_EF_EXT4                 =   0x6f55,
    UICC_EF_EST                  =   0x6f56,
    UICC_EF_ACL                  =   0x6f57,
    UICC_EF_CMI                  =   0x6f58,
    UICC_EF_START_HFN            =   0x6f5b,
    UICC_EF_THRESHOLD            =   0x6f5c,
    UICC_EF_PLMN_ACT             =   0x6f60,
    UICC_EF_OPLMN_ACT            =   0x6f61,
    UICC_EF_HPLMN_ACT            =   0x6f62,
    UICC_EF_PS_LOCI              =   0x6f73,
    UICC_EF_ACC                  =   0x6f78,
    UICC_EF_FPLMN                =   0x6f7b,
    UICC_EF_LOCI                 =   0x6f7e,
    UICC_EF_ICI                 =   0x6f80,
    UICC_EF_OCI                 =   0x6f81,
    UICC_EF_ICT                 =   0x6f82,
    UICC_EF_OCT                 =   0x6f83,
    UICC_EF_AD                  =   0x6fad,
    UICC_EF_HIDDENKEY           =   0x6fc3,
    UICC_EF_NETPAR              =   0x6fc4,
    UICC_EF_PNN                 =   0x6fc5,
    UICC_EF_OPL                 =   0x6fc6,
    UICC_EF_MBDN                =   0x6fc7,
    UICC_EF_EXT6                =   0x6fc8,
    UICC_EF_MBI                 =   0x6fc9,
    UICC_EF_MWIS                =   0x6fca,
    UICC_EF_CFIS                =   0x6fcb,
    UICC_EF_EXT7                =   0x6fcc,
    UICC_EF_ATT_TST             =   0x6fd2,
    UICC_EF_EHPLMN              =   0x6fd9,
    UICC_EF_EHPLMNPI            =   0x6fdb,
    UICC_EF_LRPLMNSI            =   0x6fdc,
    UICC_EF_NCPIP               =   0x6fe2,
    UICC_EF_EPSLOCI             =   0x6fe3,
    UICC_EF_EPSNSC              =   0x6fe4,
    UICC_EF_NASCFG              =   0x6fe8,

#ifdef FEAT_RPM
    /* files under DF armed agent */
	UICC_EF_RPM_ENABLED          =   0x4f40,
	UICC_EF_RPM_PARAMS           =   0x4f41,
	UICC_EF_RPM_OM_PARAMS_LR     =   0x4f42,
	UICC_EF_RPM_OM_PARAMS        =   0x4f43,
	UICC_EF_RPM_VERSION          =   0x4f44,
#endif

    UICC_EF_INVALID              =   0x0000
}
UiccEfId;

typedef enum EfStructureTag
{
    EF_TRANSPARENT              =   0,
    EF_LINEAR_FIXED             =   1,
    EF_CYCLIC                   =   3,
    EF_STRUCT_UNKNOWN           =   0xff
}
EfStructure;

typedef enum UiccAccessConditionTag
{
    USIM_ACCESS_ALWAYS = 0x00,
    USIM_ACCESS_PIN    = 0x01,
    USIM_ACCESS_PIN2   = 0x02,
    USIM_ACCESS_RFU    = 0x03,
    USIM_ACCESS_ADM    = 0x04,
    USIM_ACCESS_NEVER  = 0xff
}
UiccAccessCondition;

typedef enum UiccFileTypeTag
{
    UICC_NO_SUCH_FILE    = 0,    /* No such file */
    UICC_MF              = 1,    /* Master file */
    UICC_DF              = 2,    /* Dedicated file */
    UICC_EF              = 3,    /* Elementary file */
    UICC_ADF             = 4,    /* Application DF*/
    UICC_MAX_NUM_FILES   = 5
}
UiccFileType;

typedef enum CommandStatusTag
{
    CMD_STATUS_OK,
    CMD_STATUS_OK_DATA_INVALID,        /* everything ok, but data not valid*/
    CMD_STATUS_NO_MEMORY,
    CMD_STATUS_COMMAND_ERROR,           /* SW1, SW2 implies error */
    CMD_STATUS_INVALID_RESPONSE_LENGTH,  /* unexpected rx data length (>2) */
    CMD_STATUS_NO_SW_DATA = 5,
    CMD_STATUS_SERVICE_NOT_AVAILABLE,
    CMD_STATUS_UICC_REMOVED,            /* the uicc card has been removed */
    CMD_STATUS_DRV_OVERRUN_ERROR,       /* rx problem with uicc driver */
    CMD_STATUS_DRV_RECEIVE_ERROR,       /* rx problem with uicc driver */
    CMD_STATUS_DRV_TRANSMIT_ERROR = 10,      /* tx problem with uicc driver */
    CMD_STATUS_DRV_NO_RESPONSE,         /* tx problem with uicc driver */
    CMD_STATUS_INVALID_MAC,            /* AUTHENTICATE : invalid MAC*/
    CMD_STATUS_PARSE_ERROR,           /* Parse FCP template error*/
    CMD_STATUS_POWER_DOWN,
    CMD_STATUS_USAT_BUSY = 15,             /* card is busy for USAT data */
    CMD_STATUS_UICC_APP_ERROR,          /* problem with the UICC Application     */
    CMD_STATUS_UICC_DDL_ERROR,           /* SMS-PP Data Download Error */
    CMD_STATUS_USAT_CS_SIM_APP_ERROR,
    CMD_STATUS_UICC_ESIM_NO_PROFILE				//Esim with no profile detected*/

}
CommandStatus;

typedef enum StatusWordsTag
{
    /*
    * SW1SW2
    */
    /* Normal processing */
    SW_NORMAL_ENDING                   = 0x9000,
    SW_NORMAL_END_WITH_EXTRA_INFO_PROCMD      = 0x9100, /* 91 xx-- length of data to fetch  */
    SW_NORMAL_END_WITH_EXTRA_INFO_RETRIES     = 0x9200, /* 92 xx-- an ongoing data transfer session */
    SW_USAT_IS_BUSY                    = 0x9300, /* USIM Application Toolkit is busy.*/

    /* Warinings */
    SW_NO_INFO_GIVEN                   = 0x6200,
    SW_PART_OF_RET_DATA_CORRUPTED      = 0x6281,
    SW_EOF_REACHED_BEFORE_LE           = 0x6282,
    SW_SELECTED_FILE_INVALID           = 0x6283,
    SW_SELECTED_FILE_TERMINATE         = 0x6285,
    SW_MORE_DATA_AVAILABLE             = 0x62F1,
    SW_MORE_DATA_AVALI_PROCMD_PENDING  = 0x62F2,
    SW_RESP_DATA_AVAILABLE             = 0x62F3,
    SW_MORE_DATA_EXPECTED              = 0x63F1,
    SW_MORE_DATA_EXP_PROCMD_PENDING    = 0x63F2,

    /* Execution errors*/
    SW_MEMORY_PROBLEM                  = 0x6581,

    /* Base checking error */
    SW_INCORRECT_P3             = 0x6700, /* 6700/67 xx--correct length */
    SW_INCORRECT_P1_OR_P2       = 0x6B00,
    SW_INS_NOT_SUPP_OR_INVALID        = 0x6D00,
    SW_CLASS_NOT_SUPPORT         = 0x6E00,
    SW_TECHNICAL_PROBLEM        = 0x6F00,

    /* Functions in Cla not supported */
    SW_FUNC_IN_CLA_NOT_SUP      = 0x6800,
    SW_LOGICAL_CHANNEL_NOT_SUP  = 0x6881,
    SW_SECURE_MSG_NOT_SUP       = 0x6882,

    /*  Command not allowed */
    SW_COM_NOT_ALLOWED          = 0x6900,
    SW_CMD_INCOMP_FILE_STRUC    = 0x6981,
    SW_SECU_NOT_SATISFIED       = 0x6982,
    SW_AUTH_PIN_MTH_BLOCKED     = 0x6983,
    SW_REF_DATA_INVALIDATED     = 0x6984,
    SW_COND_NOT_SATISFIED       = 0x6985,
    SW_CMD_NOT_ALLOWED1         = 0x6986,
    SW_CMD_NOT_ALLOWED2         = 0x6989,

    /*  Wrong parameters */
    SW_INCORRECT_DATA_PARAM     = 0x6A80,
    SW_FUNC_NOT_SUPPORTED       = 0x6A81,
    SW_FILE_NOT_FOUND           = 0x6A82,
    SW_RECORD_NOT_FOUND         = 0x6A83,
    SW_NOT_ENOUGH_MRY           = 0x6A84,
    SW_INCORRECT_P1_P2          = 0x6A86,
    SW_LC_INCONSISTENT          = 0x6A87,
    SW_REF_DATA_NOT_FOUND       = 0x6A88,

    /*Application error*/
    SW_MAX_VALUE_REACHED        = 0x9850,
    SW_INVALID_MAC              = 0x9862,
    SW_SECU_SESS_ASSOC_EXPIRED  = 0x9863,

    SW_UNKNOWN_STATUS           = 0xFFFF           /* unknown SW1 SW2 */

}
StatusWords;

typedef enum UiccFileStateTag
{
  UICC_FILE_NO_INFO_STATE     = 0x00,
  UICC_FILE_CREATION_STATE    = 0x01,
  UICC_FILE_INIT_STATE        = 0x03,
  UICC_FILE_DEACTIVATED_STATE = 0x04,
  UICC_FILE_ACTIVATED_STATE   = 0x05,
  UICC_FILE_TERMINATED_STATE  = 0x0c,

  UICC_FILE_PROPRIETARY_STATE =0xff

} UiccFileState;

typedef enum UiccSecEnvironmentTag
{
    UICC_SE00 = 0,
    UICC_SE01 = 1,
    UICC_SE_UNKNOWN

}
UiccSecEnvironment;

typedef enum UiccApplicationCodeTag
{
  APP_CODE_UICC,
  APP_CODE_USIM,
  APP_CODE_USAT,
  APP_CODE_ISIM,
  APP_CODE_UNKNOWN
}
UiccApplicationCode;

typedef enum AppSessionCtrlTag
{
    UICC_ACTIVATION_OR_RESET       = 0, /* Activation/reset of UICC App with FCP data returned*/
    UICC_TERMINATION               = 1, /* Termination of Uicc App*/
    UICC_ACTIVATION_With_NO_DATA   = 2, /* Activation with no data returned*/
    UICC_ACTIVATION_With_FMD       = 3, /* Activation with FMD data returned*/
    UICC_ACTIVATION_With_FCI       = 4, /* Activation with FCI data returned*/
    UICC_ACTIVATION_With_FCI_IF    = 5 /* Activation with FCI interfaces data returned*/
}
AppSessionCtrl;

typedef enum UiccKeyRefValueTag
{
    USIM_ACCESS_NO_PIN        = 0x00,
    USIM_ACCESS_PIN1_APP1     = 0x01,
    USIM_ACCESS_PIN1_APP2     = 0x02,
    USIM_ACCESS_PIN1_APP3     = 0x03,
    USIM_ACCESS_PIN1_APP4     = 0x04,
    USIM_ACCESS_PIN1_APP5     = 0x05,
    USIM_ACCESS_PIN1_APP6     = 0x06,
    USIM_ACCESS_PIN1_APP7     = 0x07,
    USIM_ACCESS_PIN1_APP8     = 0x08,
    USIM_ACCESS_UNIVERSAL_PIN = 0x11,
    USIM_ACCESS_PIN2_APP1     = 0x81,
    USIM_ACCESS_PIN2_APP2     = 0x82,
    USIM_ACCESS_PIN2_APP3     = 0x83,
    USIM_ACCESS_PIN2_APP4     = 0x84,
    USIM_ACCESS_PIN2_APP5     = 0x85,
    USIM_ACCESS_PIN2_APP6     = 0x86,
    USIM_ACCESS_PIN2_APP7     = 0x87,
    USIM_ACCESS_PIN2_APP8     = 0x88,
    USIM_ACCESS_ADM1          = 0x0a,
    USIM_ACCESS_ADM2          = 0x0b,
    USIM_ACCESS_ADM3          = 0x0c,
    USIM_ACCESS_ADM4          = 0x0d,
    USIM_ACCESS_ADM5          = 0x0e,
    USIM_ACCESS_ADM6          = 0x8a,
    USIM_ACCESS_ADM7          = 0x8b,
    USIM_ACCESS_ADM8          = 0x8c,
    USIM_ACCESS_ADM9          = 0x8d,
    USIM_ACCESS_ADM10         = 0x8e
}
UiccKeyRefValue;

typedef enum UiccVoltageTag
{
    UICC_5_VOLTS,
    UICC_3_VOLTS,
    UICC_1_8_VOLTS,
    SIM_WARM_RESET,
    UICC_VOLTAGE_UNKNOWN = 0xFF
}
UiccVoltage;

typedef enum UiccSuspendTypeTag
{
        UICC_SUSPEND = 0x00,
        UICC_RESUME  = 0x01
}
UiccSuspendType;

typedef enum UsatBearerTypeTag
{
    USAT_BEARER_TYPE_CSD                        = 0x01,
    USAT_BEARER_TYPE_GPRS                       = 0x02,
    USAT_BEARER_TYPE_DEFAULT                    = 0x03,
    USAT_BEARER_TYPE_PACKET_SERIVCE             = 0x09,
    USAT_BEARER_TYPE_EUTRAN_MAPPED_UTRAN_PS     = 0x0B
}
UsatBearerType;

typedef enum UsatPdnTypeTag
{
    USAT_PDN_TYPE_X25               = 0x01,
    USAT_PDN_TYPE_IP                = 0x02,
    USAT_PDN_TYPE_IPV6              = 0x03,
    USAT_PDN_TYPE_IPV4V6            = 0x04,
    USAT_PDN_TYPE_OSPIH             = 0x05,
    USAT_PDN_TYPE_PPP               = 0x06,
    USAT_PDN_TYPE_NONIP             = 0x07
}
UsatPdnType;

typedef enum UsatEventTypeTag
{
    USAT_EVENT_MT_CALL             = 0x00,
    USAT_EVENT_CALL_CONN           = 0x01,
    USAT_EVENT_CALL_DISCONN        = 0x02,
    USAT_EVENT_LOCATION_STATUS     = 0x03,
    USAT_EVENT_USER_ACTIVITY       = 0x04,
    USAT_EVENT_IDLE_SCRN_AVAIL     = 0x05,
    USAT_EVENT_CARD_READER_STATUS  = 0x06,
    USAT_EVENT_LANG_SELECTION      = 0x07,
    USAT_EVENT_BROWSER_TERM        = 0x08,
    USAT_EVENT_DATA_AVAILABLE      = 0x09,
    USAT_EVENT_CHANNEL_STATUS      = 0x0a,
    USAT_EVENT_ACCESS_TECHNOLOGY   = 0x0b,
    USAT_EVENT_DISPLAY_PARAMS      = 0x0c,
    USAT_EVENT_LOCAL_CONNECTION    = 0x0d,
    USAT_EVENT_NETWORK_REJECTION   = 0x12
}
UsatEventType;

/******************************************************************************
 * STRUCTS
******************************************************************************/
typedef struct UsimServiceTableTag
{
   UINT8   localPhoneBook:1;
   UINT8   fdn:1;
   UINT8   extension2:1;
   UINT8   sdn:1;
   UINT8   extension3:1;
   UINT8   bdn:1;
   UINT8   extension4:1;
   UINT8   oci:1; /*outgoing call information*/

   UINT8   ici:1; /*incoming call information*/
   UINT8   smss:1;
   UINT8   smsr:1;
   UINT8   smsp:1;
   UINT8   adviceOfCharge:1;
   UINT8   capabilityConfig:1;
   UINT8   cbmi:1;
   UINT8   cbmir:1;

   UINT8   gid1:1;
   UINT8   gid2:1;
   UINT8   spn:1;
   UINT8   userPlmnwAct:1;
   UINT8   msisdn:1;
   UINT8   image:1;
   UINT8   solsa:1;
   UINT8   emlpp:1;

   UINT8   aaEmlpp:1;
   UINT8   rfu:1;
   UINT8   gsmAccess:1;
   UINT8   ddSmsPp:1;
   UINT8   ddSmsCb:1;
   UINT8   cc:1;
   UINT8   moSms:1;
   UINT8   runAtCommand:1;

   UINT8   notUsed:1;
   UINT8   est:1;
   UINT8   apn:1;   /*access point name control list*/
   UINT8   dck:1;
   UINT8   cnl:1;
   UINT8   gsmSecurityContext:1;
   UINT8   cpbcchInfo:1;
   UINT8   investigationScan:1;

   UINT8   MExE:1;
   UINT8   operatorPlmnwAct:1;
   UINT8   hplmnwAct:1;
   UINT8   extension5:1;
   UINT8   plmnNetworkName:1;
   UINT8   operatorPlmnList:1;
   UINT8   mbdn:1;   /*mailbox dialling  number*/
   UINT8   mwis:1;   /*message waiting indication status*/

   UINT8   cfis:1;   /*call forwarding indication status*/
   UINT8   reserved1:1;
   UINT8   serviceProviderDisplayInfo:1;
   UINT8   mms:1;
   UINT8   extension8:1;
   UINT8   ccByGprs:1;
   UINT8   mmsUserConnectivityParam:1;
   UINT8   nia:1;

   UINT8   vgcsIdList:1;
   UINT8   vbsIdList:1;
   UINT8   pseudonym:1;
   UINT8   userControlledPlmnForWlan:1;
   UINT8   operatorControlledPlmnForWlan:1;
   UINT8   UserControlledWsidList:1;
   UINT8   OperatorControlledWsidList:1;
   UINT8   vgcsSecurity:1;

   UINT8   vbsSecurity:1;
   UINT8   wlanReauthenticationIdentity:1;
   UINT8   multimediaMessageStorage:1;
   UINT8   gba:1;
   UINT8   mbmsSecurity:1;
   UINT8   dataDownloadViaUssdAndUssdAppMode:1;
   UINT8   ehplmn:1;                  /*service n 71*/
   UINT8   AdditionalTerminalProfileAfterUiccActivation:1;

   UINT8   ehplmnpi:1;                /*service n 73*/
   UINT8   lastRplmnSI:1;       /* service n 74 */
   UINT8   omaBcastSmartCardProfile:1;    /*service n 75*/
   UINT8   gbaBasedLocKeyEstMech:1;     /*service n 76*/
   UINT8   terminalApplications:1;     /*service n 77*/
   UINT8   serviceProviderNameIcon:1;    /*service n 78*/
   UINT8   plmnNetworkNameIcon:1;      /*service n 79*/
   UINT8   connectivityParameters:1;    /*service n 80*/

   UINT8   homeIWlanSpecIdenList:1;     /*service n 81*/
   UINT8   iWlanEquivHplmnPreInd:1;     /*service n 82*/
   UINT8   iWlanHplmnPriInd:1;          /*service n 83*/
   UINT8   iWlanLastRegPlmn:1;         /*service n 84*/
   UINT8   epsMmInfo:1;                /*service n 85*/
   UINT8   allowedCsg:1;                  /*service n 86*/
   UINT8   ccOnEpsPdnConnection:1;       /*service n 87*/
   UINT8   hplmnDirectAccess:1;          /*service n 88*/

   UINT8    eCallData:1;                 /*service n 89*/
   UINT8    operatorCsg:1;                 /*service n 90*/
   UINT8    service91:1;
   UINT8    csgDisplayCtrl:1;
   UINT8    service93:1;
   UINT8    service94:1;
   UINT8    service95:1;
   UINT8    nasConfig:1;               /**< NAS configuration by SIM, no. 96 */

   UINT8    service97:1;
   UINT8    reserved2:7;

} UsimServiceTable;

typedef struct AtrParametersTag
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
}
AtrParameters;



/* Short File Identifier */
typedef struct UiccSfiTag
{
    BOOL        supported;
    UINT8       data;
}
UiccSfi;

typedef struct UiccSecurityConditionTag
{
  UiccAccessCondition       condition;
  UINT8                      numKeyRef;
  UiccKeyRefValue        keyRef[MAX_NUM_KEY_REF];
  BOOL                   orTemplate;
}
UiccSecurityCondition;

/* TS 102 221, section 9.2.4/5/6:
 * The access rules can be indicated in the FCP in one of the following formats:
 * 1) Compact,
 * 2) Expanded,
 * 3) Referenced to expanded format */
/* Define access conditions for a Ef file, ISO 7816-4 section 7. */
typedef struct UiccEfCompactFormatTag
{
    UiccAccessCondition    deleteFile;
    UiccAccessCondition    terminate;
    UiccAccessCondition    activate;
    UiccAccessCondition    deactivate;
    UiccAccessCondition    write;
    UiccAccessCondition    update;
    UiccAccessCondition    readAndSearch;
}
UiccEfCompactFormat;

typedef struct UiccEfExpandedFormatTag
{
   UiccSecurityCondition    deleteFile;
   UiccSecurityCondition    terminate;
   UiccSecurityCondition    activate;
   UiccSecurityCondition    deactivate;
   UiccSecurityCondition    write;
   UiccSecurityCondition    update;
   UiccSecurityCondition    readAndSearch;
}
UiccEfExpandedFormat;

typedef struct UiccRefToExpandedFormatTag
{
    UINT16        arrEfId;
    UINT8         recordNumCurrentSe;
    UINT8         recordNumSe00;
    UINT8         recordNumSe01;
}
UiccRefToExpandedFormat;

typedef union UiccSecAttributesTag
{
    UiccEfCompactFormat           compactFormat;
    UiccEfExpandedFormat          expandedFormat;
    UiccRefToExpandedFormat       refToExpandedFormat;
}
UiccSecAttributes;

typedef struct UiccAidTag
{
    UINT8       reserved1;
    UINT16      reserved2;
    UINT8       length;
    UINT8       data[UICC_AID_MAX_LEN];
}
UiccAid;

typedef struct UiccAidLabelTag
{
  UiccApplicationCode             applicationType;
  UINT8                            length;                         /* label length */
  UINT8                            data[UICC_LABEL_MAX_SIZE];      /* Application label */
}
UiccAidLabel;

typedef struct IccidTag
{
    UINT8                            data[ICCID_LEN];
    UINT16                           reserved;
}
Iccid;

typedef struct EfFcpDataTag
{
    UiccEfId                 fileId;
    UiccFileStatus           efStatus;
    UiccFileState            fileState;
    UINT8                    fileSize;
    UINT8                    recordLength;
    UINT8                    numberOfRecords;
    EfStructure              efStructure;
    UiccSecAttributesFormat  format;
    UiccSecAttributes        secAttributes;
    BOOL                     fileIsShareable;
    UiccFileType             fileType;
    UINT16                   totalFileSize;
    UiccSfi                  sfi;
    BOOL                     increaseAllowed;
    BOOL                     readWriteWhenInvalid;
}
EfFcpData;

typedef struct UiccDirFcpDataTag
{
    UiccFileStatus                  dirStatus;
    UiccFileType                    fileType;
    UINT16                          dirId;
}
UiccDirFcpData;

typedef struct UiccEfInfoTag
{
    UINT8            recordLength;
    UINT8            numRecords;
    UiccSfi          sfi;                 /* Short File Identifier */
}
UiccEfInfo;


typedef struct UiccUsimSpecDataTag
{
    UiccKeyRefValue              applicationPin;
    UiccPinStatus                pin1Status;     /* the application PIN*/
    UiccKeyRefValue              localPin;
    UiccPinStatus                pin2Status;    /* local PIN */
    UiccPinStatus                unblockPin2Status;    /*the UNBLOCK PIN2 (local PIN) */
    UiccFileState                fileState;
}
UiccUsimSpecData;

typedef struct AdminDataTag
{
    MeOperationMode                 meOperaMode;
    UINT8                           mncLength;
    UINT16                          additionalInfo;
}
AdminData;


typedef struct UiccAppDataTag
{
    UiccAid                       aid;     /* Only support USIM Application Id*/
    UiccUsimSpecData              usimSpecData;
    UiccPinStatus                 universalPin;
    BOOL                          universalPinSupportedByCard;
    UiccPinStatus                 unblockUniversalPin;
    UiccKeyRefValue               pin1;
    UiccPinStatus                 appPinStatus[MAX_NUM_APP_PIN]; /* the application PINs status */
    UiccPinStatus                 unblockAppPinStatus[MAX_NUM_APP_PIN]; /* the unblock PINs status */
    UsimServiceTable              serviceTable;
    BOOL                          fdnEnabled;
    /*BOOL                          bdnEnabled;*/
    BOOL                          aclEnabled;
    Imsi                          imsi;
    AdminData                     adminData;
    //BOOL                          epsLocInfoInvalid;
    //EpsLocationInfo               epsLocInfo;
}
UiccAppData;

typedef struct UiccFileOperaDataTag
{
    UINT16           currentDir;         /* the currently selected MF or DF*/
    UINT16           currentEf;          /* the currently selected EF*/
    EfFcpData        currEfFcpData;      /* the FCP data of the current EF       */
    UiccDirFcpData   currDirFcpData;     /* the FCP data of the current DIR       */
    UINT8            currDirFcpLen;
    UiccEfInfo       savedEfInfo[UICC_SAVE_EF_NUM_ENTRIES];
}
UiccFileOperaData;

typedef enum UiccCtrlTimerIdTag
{
    UICC_USAT_TIMER_1 = 0x01,
    UICC_USAT_TIMER_2,
    UICC_USAT_TIMER_3,
    UICC_USAT_TIMER_4,
    UICC_USAT_TIMER_5,
    UICC_USAT_TIMER_6,
    UICC_USAT_TIMER_7,
    UICC_USAT_TIMER_8 = 0x08,
    UICC_CLOCK_STOP_TID,
    UICC_POLLING_PRESENCE_DETECT_TID,
    UICC_WAIT_RESPONSE_TID,
    UICC_TIMER_ID_UNKNOWN = 0xFF
}
UiccCtrlTimerId;


typedef struct UiccCtrlTimerTag
{
    UiccCtrlTimerId    uiccTid;         /* the timer Id for UiccCtrl interal */
    UINT32             timerPeriod;     /* timer period, unit is TICKS */
    osTimerId_t        osTid;           /* timerId is allocated by OS */
}
UiccCtrlTimer;

typedef enum UiccSuspendDurationUnitTag
{
        UICC_SUSPEND_TIME_UNIT_SECONDS          = 0x00,
        UICC_SUSPEND_TIME_UNIT_MINUTES          = 0x01,
        UICC_SUSPEND_TIME_UNIT_HOURS            = 0x02,
        UICC_SUSPEND_TIME_UNIT_DAYS             = 0x03,
        UICC_SUSPEND_TIME_UNIT_TEN_DAYS         = 0x04
}
UiccSuspendDurationUnit;

typedef struct UiccSuspendDurationTag
{
    UiccSuspendDurationUnit             timeUnit;
    UINT8                               timeValue;
}
UiccSuspendDuration;

typedef enum UiccCfunPowerStateTag
{
    CFUN_POWER_OFF_STATE = 0,
    CFUN_AIR_PLANE_STATE = 1,
    CFUN_POWER_ON_STATE = 2
}UiccCfunPowerState;


typedef struct SimEfWriteCnt_Tag
{
    UINT16      fileId;
    UINT16      reserved;
    UINT32      writeCnt;//SIM write counter
}
SimEfWriteCnt;

/*
 * Counter the SIM write (update binary/update record) times of EF
*/
typedef struct SimWriteCntList_Tag
{
    UINT8               swcEfNum;
    UINT8               rsvd1;
    UINT16              rsvd2;
    SimEfWriteCnt       efWriteCnt[MAX_SWC_EF_LIST_NUM];
}
SimWriteCntList;


/******************************************************************************
 ************************** Tiny RAM ******************************************
 * UiccCtrlTinyContext
 * Note:
 *  Most important UiccCtrl context, which stored in the AON (always on line) memory
 *  need to control the size, totally don't exceed 64 bytes
 ******************************************************************************
******************************************************************************/
typedef struct UiccCtrlTinyContextTag
{
    UINT8                 iccidData[ICCID_LEN];
    BOOL                  bInPsmOrEdrx;
    BOOL                  supportSuspension;
    UINT8                 secData[UICC_PIN_VALUE_LENGTH];//save PIN code or resume token, 8 bytes
    Imsi                  imsi;
    AdminData             adminData;
    UsimServiceTable      serviceTable;
    EpsLocationInfo       epsLoci;
    UINT8                 ldosimEfuseTrim; //ldosim EFUSE trim value
    UINT8                 reserved1;
    UINT16                reserved2;
}
UiccCtrlTinyContext;


typedef struct UiccCtrlDataTag
{
    UiccCtrlState    state;
    BOOL             clockStopAllowed;
    BOOL             clockStopHigh;
    UiccVoltage      uiccVoltage;

    SignalBuf        *reqSignal;
    SignalBuf        *rspSignal;

    SignalQueue      mmSigQueue;
    SignalQueue      ccmSigQueue;
    SignalQueue      drvSigQueue;

    UiccAppData       uiccAppData;
    UINT16            adfUsimId;
    CommandStatus     cmdStatus;
    StatusWords       statusWords;

    UiccFileOperaData fileOperaData;

    Iccid             iccid;
    //AtrParameters     atrParameters;

    UINT8              isUiccClockStop:1;
    UINT8              supportSuspension:1;
    UINT8              errorStateOccurred:1;
    UINT8              reserved1:1;
    UINT8              leaveSleepMode:1; //indicate whether wake up from deep sleep (sleep2/hibernate) mode or leave PSM/EDRX
    UINT8              isPoweringdown:1;
    UINT8              emmConnectedMode:1;//TRUE-EMM in connected mode; FALSE-EMM in idle mode.
    UINT8              usatSupport:1;

    UINT8              usatProCmdQualifier;
    UINT8              usatCmdOngoing:1;//proactivve command is ongoing, no terminal response to uicc
    UINT8              inRefresh:1;
    UINT8              proactivePollingActive:1;
    UINT8              pendingFetch:1;
    UINT8              cfunState:2;//UiccCfunPowerState
    UINT8              bipSessionOpen:1;
    UINT8              reserved:1;
    UINT8              fetchSize;
    UINT32              proactivePollingInterval;
    UiccCtrlTimer       clockStopTimer;//stop the uicc clock after timer expired.
    UiccCtrlTimer       pollingPresenceDetectTimer;/* polling timer and presence detection timer, send STATUS command after timer expired.
                                                    * proactive polling timer used in Idle mode if support USAT.
                                                    * presence detection timer used in connected mode during CS/PS call.
                                                    */
    UiccCtrlTimer       waitResponseTimer;//set timer for waiting response from the uicc driver.
    UiccCtrlTimer       usatTimer[USAT_MAX_TIMER_NUM];
    UINT16              currGenAccessEF;
    UINT8               errorOccurCnt;/* error state occurred counter, if error return 3 times after recovery process the requests, stop recovery*/
    SimWriteCntList      *pSwcList;
	BOOL				eUiccSupport;
	BOOL                validEfImsi;

}
UiccCtrlData;


typedef struct ApduDataBlockTag
{
    UINT16                           length;
    UINT8                            reserved;
    UINT8                            data[MAX_APDU_DATA_LEN];
}
ApduDataBlock;

typedef struct UsatBearerParamsTag
{
    UsatPdnType         pdnType;
    UINT8               precedenceClass;
    UINT8               delayClass;
    UINT8               reliaClass;
    UINT8               peakTptClass;
    UINT8               meanTptClass;
    UINT8               qci;
    BOOL                gbrMbrPresent;  /* indicate the present of GBR/MBR*/
    UINT32              ulMBR;          /* UL_MBR, kbit/s */
    UINT32              dlMBR;          /* DL_MBR, kbit/s */
    UINT32              ulGBR;          /* UL_GBR, kbit/s */
    UINT32              dlGBR;          /* DL_GBR, kbit/s */
}
UsatBearerParams;

typedef struct UsatBearerDescriptionTag
{
    UsatBearerType          bearerType;
    UINT8                   reserved1;
    UINT16                  reserved2;
    UsatBearerParams        bearerParams;
}
UsatBearerDescription;

#endif


