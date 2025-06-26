#ifndef __PS_COMM_TYPE_H__
#define __PS_COMM_TYPE_H__

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017, All rights reserved by Qualcomm Ltd.
 File name:      - pscommtype.h
 Description:    - PS common typedef structure
 History:        - 10/19/2018, Originated by jcweng
 ******************************************************************************
******************************************************************************/

#include "pssys.h"

/******************************************************************************
 *****************************************************************************
 * MACRO
 *****************************************************************************
******************************************************************************/
#define SUPPORT_MAX_BAND_NUM            32                         //Extend from 16 to 32, 2020-7-28
#define RRC_PHY_SUPPORT_BAND_NUM        SUPPORT_MAX_BAND_NUM       //this value should be the same as PHY_SUPPORT_BAND_NUM
#define SUPPORT_MAX_MCC_BAND            10
#define SUPPORT_MAX_FREQ_NUM            8
#define MAX_PLMN_LIST_SIZE              6       //this value is max number of plmn Id in SIB1, maxPLMN-r11
#define CE_INVALID_MCC                  0xFFFF
#define SUPPORT_MAX_PLMN_NUM            20      //TBD
#define CEMM_PLMN_LIST_MAX_NUM          16
#define MAX_BAND_MASK_NUM               3       //the max number of UINT32 bandmask, i.e. the max supported band num is 32*MAX_BAND_MASK_NUM
#define MAX_NAS_MSG_BITMAP_NUM          8       // equal to 256/32

#define PS_INVALID_PHY_CELL_ID          0xFFFF
#define PS_MAX_PHY_CELL_ID              503

//SHA-256 MACROS
#define SHA256_HASH_WORDS               8       /* number of words in H(0) */
#define SHA256_OUTPUT_SIZE              32      /* Block size (in bytes) of the output of the Approved hash function. */
#define SHA256_BLOCK_SIZE               64      /* Block size (in bytes) of the input to the Approved hash function. */

#ifndef MAX
#define MAX(a,b)                        (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)                        (((a) < (b)) ? (a) : (b))
#endif

#define NB_DRB_NUM                      2


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

typedef UINT16 AccessClass;
typedef UINT16 AccessTechnologyId;

/******************************************************************************
 * Plmn
 * Numberic PLMN format, 4 bytes,
 * example: CMCC: 46000; mcc = 0x0460, mnc = 0xf000
 *        00101; mcc = 0x0001, mnc = 0xf001
 *        46012; mcc = 0x0460, mnc = 0xf012
 *        460123; mcc = 0x0460, mnc = 0x0123
******************************************************************************/
typedef struct Plmn_Tag
{
    UINT16  mcc;
    UINT16  mncWithAddInfo; // if 2-digit MNC type, the 4 MSB bits should set to 'F',
}Plmn;

#define PLMN_GET_PURE_MNC(mncWithAddInfo) ((mncWithAddInfo)&0xFFF)
#define PLMN_IS_2_DIGIT_MNC(mncWithAddInfo) (((mncWithAddInfo)>>12) == 0x0F)

#define PLMN_SET_MNC_WITH_ADD_INFO(twoDigitType, pureMnc) ((twoDigitType)?((pureMnc)|0xF000):((pureMnc)&0xFFF))

#define IS_VALID_PLMN(plmn) (((plmn).mcc != 0) ? TRUE : FALSE)

#define IS_SAME_PLMN(plmn1, plmn2)  (((plmn1).mcc == (plmn2).mcc) && ((plmn1).mncWithAddInfo == (plmn2).mncWithAddInfo))

typedef enum PlmnMncDigitType_enum
{
    PLMN_UNKNOW_DIGIT_MNC = 0,
    PLMN_2_DIGIT_MNC = 2,
    PLMN_3_DIGIT_MNC = 3
}PlmnMncDigitType;

/******************************************************************************
 * NwMode
 * NB_IOT, EMTC, etc...
******************************************************************************/
typedef enum NwModeEnum_Tag
{
    NB_IOT = 0,
    EMTC_IOT
}NwMode;

/******************************************************************************
 * UeService
 * EPS/NON_EPS/EPS AND NON_EPS
******************************************************************************/
typedef enum UeServiceEnum_Tag
{
    EPS_ONLY        = 0, // NB
    NON_EPS         = 1,
    EPS_AND_NON_EPS = 2,
    NON_SERVICE
}UeService;

/******************************************************************************
 * PlmnType
 * HPLMN/EHPLMN/RPLMN/EPLMN.....
******************************************************************************/
typedef enum PlmnTypeEnum_Tag
{
    HPLMN = 0, //home PLMN, derived from IMSI
    EHPLMN,    //equivalent home PLMN
    //RPLMN,     //registered PLMN, not the same level meaning
    //EPLMN,     //equivalent PLMN, not the same level meaning
    VPLMN,     //visited PLMN
    UPLMN,     //user controlled PLMN
    OPLMN,     //operator controlled PLMN
    FPLMN,     //forbidden PLMN
    APLMN,     //available PLMN
}PlmnType;

/******************************************************************************
 * CipheringAlgorithm
 * EEA0/EEA1/EEA2/EEA3
******************************************************************************/
typedef enum CipheringAlgorithmTag
{
    // see TS 34.401 5.1.3.2
    EEA0 = 0,
    EEA1 = 1,
    EEA2 = 2,
    EEA3 = 3,
}CipheringAlgorithm;

/******************************************************************************
 * IntegrityAlgorithm
 * EIA0/EIA1/EIA2/EIA3
******************************************************************************/
typedef enum IntegrityAlgorithmTag
{
    // see TS 34.401 5.1.4.2
    EIA0 = 0,
    EIA1 = 1,
    EIA2 = 2,
    EIA3 = 3
}IntegrityAlgorithm;

/*
 * 24.301: 9.9.4.25 Release assistance indication
 * 0 0  No information regarding DDX is conveyed by the information element. If
 *      received it shall be interpreted as 'neither value "01" nor "10" applies'
 * 0 1  No further uplink or downlink data transmission subsequent to the uplink data
 *      transmission is expected
 * 1 0  Only a single downlink data transmission and no further uplink data
 *      transmission subsequent to the uplink data transmission is expected
 * 1 1  reserved
*/
typedef enum DataRelAssistIndEnum_Tag
{
    DATA_RAI_NO_INFO = 0,
    DATA_RAI_NO_UL_DL_FOLLOWED = 1,
    DATA_RAI_ONLY_DL_FOLLOWED = 2,
    DATA_RAI_RESERVED = 3
}DataRelAssistIndEnum;

/******************************************************************************
 * Tai
 * Tai = mcc + mnc + tac
******************************************************************************/
typedef struct Tai_Tag
{
    Plmn    plmn;
    UINT16  tac;
    UINT16  reserved;
}Tai;

/******************************************************************************
 * Kasme
******************************************************************************/
#define KASME_SIZE 32
typedef struct AsmeKey_Tag
{
    UINT8  data[KASME_SIZE];
}AsmeKey;

/******************************************************************************
 * NAS COUNT
******************************************************************************/
#define NAS_COUNT_SIZE 4
typedef struct NasCount_Tag
{
    UINT8  data[NAS_COUNT_SIZE];
}NasCount;

/******************************************************************************
 * IMSI
******************************************************************************/
#define MAX_IMSI_LENGTH     8
typedef struct Imsi_Tag
{
    UINT8               length;
    UINT8               mncType;    //PlmnMncDigitType
    AccessTechnologyId  accessTech;
    UINT8               contents[MAX_IMSI_LENGTH];
}Imsi;

/******************************************************************************
 * Additional Update Result
******************************************************************************/
typedef enum AdditionalUpdateResultTag
{
    NO_ADDITIONAL_INFORMATION = 0,
    CS_FALLBACK_NOT_PREFERRED = 1,
    SMS_ONLY                  = 2,
    RESERVED_VALUE            = 3
}
AdditionalUpdateResult;

/******************************************************************************
 * DCN ID
******************************************************************************/
typedef struct DedicatedCoreNetworkId_Tag
{
    Plmn    plmn;
    UINT16  dcnIdWithinPlmn;
}DedicatedCoreNetworkId;

typedef enum TimerUnitTag
{
    TIMER1_MULTIPLES_OF_TWO_SECONDS = 0,
    TIMER1_MULTIPLES_OF_ONE_MINUTE  = 1,
    TIMER1_MULTIPLES_OF_DECIHOURS   = 2,
    TIMER1_TIMER_DEACTIVATED        = 7
}
TimerUnit;

typedef TimerUnit Timer2Unit;

typedef enum Timer3UnitTag
{
    TIMER3_MULTIPLES_OF_TEN_MINUTES    = 0,
    TIMER3_MULTIPLES_OF_ONE_HOUR       = 1,
    TIMER3_MULTIPLES_OF_TEN_HOURS      = 2,
    TIMER3_MULTIPLES_OF_TWO_SECONDS    = 3,
    TIMER3_MULTIPLES_OF_THIRTY_SECONDS = 4,
    TIMER3_MULTIPLES_OF_ONE_MINUTE     = 5,
    TIMER3_MULTIPLES_OF_320_HOURS      = 6,
    TIMER3_TIMER_DEACTIVATED           = 7
}
Timer3Unit;

typedef struct GprsTimerTag
{
    UINT8           timerValue;
    TimerUnit       unit;
}
GprsTimer;

typedef struct GprsTimer2Tag
{
    UINT8           timerValue;
    Timer2Unit      unit;
}
GprsTimer2;

typedef struct GprsTimer3Tag
{
    UINT8           timerValue;
    Timer3Unit      unit;
}
GprsTimer3;

/* The field contains the PTW value in seconds for NB-S1 mode */
typedef enum PagingTimeWindowForNBModeTag
{
    PAGING_TIME_WINDOW_NB_2_SEC_560_MS  = 0,
    PAGING_TIME_WINDOW_NB_5_SEC_120_MS  = 1,
    PAGING_TIME_WINDOW_NB_7_SEC_680_MS  = 2,
    PAGING_TIME_WINDOW_NB_10_SEC_240_MS = 3,
    PAGING_TIME_WINDOW_NB_12_SEC_800_MS = 4,
    PAGING_TIME_WINDOW_NB_15_SEC_360_MS = 5,
    PAGING_TIME_WINDOW_NB_17_SEC_920_MS = 6,
    PAGING_TIME_WINDOW_NB_20_SEC_480_MS = 7,
    PAGING_TIME_WINDOW_NB_23_SEC_40_MS  = 8,
    PAGING_TIME_WINDOW_NB_25_SEC_600_MS = 9,
    PAGING_TIME_WINDOW_NB_28_SEC_160_MS = 10,
    PAGING_TIME_WINDOW_NB_30_SEC_720_MS = 11,
    PAGING_TIME_WINDOW_NB_33_SEC_280_MS = 12,
    PAGING_TIME_WINDOW_NB_35_SEC_840_MS = 13,
    PAGING_TIME_WINDOW_NB_38_SEC_400_MS = 14,
    PAGING_TIME_WINDOW_NB_40_SEC_960_MS = 15
}
PagingTimeWindowForNBMode;

/* The field contains the eDRX value for S1 mode */

/* -------------------------------------------------------------------------
    NOTE 4: The value is applicable only in WB-S1 mode. If received in NB-S1
    mode it is interpreted as if the Extended DRX parameters IE were not
    included in the message by this version of the protocol.

    NOTE 5: The value is applicable only in WB-S1 mode. If received in NB-S1
    mode it is interpreted as 0010 by this version of the protocol.

    NOTE 6: The value is applicable only in NB-S1 mode. If received in WB-S1
    mode it is interpreted as 1101 by this version of the protocol.
    --------------------------------------------------------------------------*/
typedef enum EdrxValueForS1ModeTag
{
    EDRX_CYCLE_LEN_5_SEC_120_MS     = 0,  /* Rfer to NOTE 4 */
    EDRX_CYCLE_LEN_10_SEC_240_MS    = 1,  /* Rfer to NOTE 4 */
    EDRX_CYCLE_LEN_20_SEC_480_MS    = 2,
    EDRX_CYCLE_LEN_40_SEC_960_MS    = 3,
    EDRX_CYCLE_LEN_61_SEC_440_MS    = 4,  /* Rfer to NOTE 5 */
    EDRX_CYCLE_LEN_81_SEC_920_MS    = 5,
    EDRX_CYCLE_LEN_102_SEC_400_MS   = 6,  /* Rfer to NOTE 5 */
    EDRX_CYCLE_LEN_122_SEC_880_MS   = 7,  /* Rfer to NOTE 5 */
    EDRX_CYCLE_LEN_143_SEC_360_MS   = 8,  /* Rfer to NOTE 5 */
    EDRX_CYCLE_LEN_163_SEC_840_MS   = 9,
    EDRX_CYCLE_LEN_327_SEC_680_MS   = 10,
    EDRX_CYCLE_LEN_655_SEC_360_MS   = 11,
    EDRX_CYCLE_LEN_1310_SEC_720_MS  = 12,
    EDRX_CYCLE_LEN_2621_SEC_440_MS  = 13,
    EDRX_CYCLE_LEN_5242_SEC_880_MS  = 14,  /* Rfer to NOTE 6 */
    EDRX_CYCLE_LEN_10485_SEC_760_MS = 15,  /* Rfer to NOTE 6 */
    EDRX_CYCLE_LEN_INVALID          = 0xFF /* Set to this value while AT+CEDRX=0(disable the use of eDRX and discard all parameters for eDRX) */
}
EdrxValueForS1Mode;

typedef struct ExtendedDrxParametersTag
{
    EdrxValueForS1Mode          edrxValue;
    PagingTimeWindowForNBMode   ptw;
}
ExtendedDrxParameters;

typedef enum CemmCiotOptTypeEnum_Tag
{
    CEMM_NO_CIOT_OPT = 0, // not support CIOT OPT, for NB, CP OPT is must, useless
    CEMM_CP_CIOT_OPT = 1,
    CEMM_UP_CIOT_OPT = 2,
    CEMM_CP_AND_UP_OPT = 3
}CemmCiotOptTypeEnum;

typedef enum CemmPsmReqModeEnum_Tag
{
    CEMM_DISABLE_PSM = 0,
    CEMM_ENABLE_PSM  = 1,
    CEMM_DISCARD_PSM = 2 /*disable PSM, and discard PSM PARMs*/
}CemmPsmReqModeEnum;

typedef enum CemmEdrxReqModeEnum_Tag
{
    CEMM_DISABLE_EDRX = 0,
    CEMM_ENABLE_EDRX  = 1,
    CEMM_DISCARD_EDRX = 2 /*disable EDRX, and discard EDRX PARMs*/
}CemmEdrxReqModeEnum;

/******************************************************************************
 * EPS update status
******************************************************************************/
typedef enum EpsUpdateStatus_Tag
{
    USIM_EUS_UPDATED             = 0,
    USIM_EUS_NOT_UPDATED         = 1,
    USIM_EUS_ROAMING_NOT_ALLOWED = 2,
    USIM_EUS_RESERVED            = 7
}EpsUpdateStatus;

/******************************************************************************
 * NAS key set identifier
******************************************************************************/
typedef enum NasKsiTag
{
    NAS_KSI_0           = 0,
    NAS_KSI_1           = 1,
    NAS_KSI_2           = 2,
    NAS_KSI_3           = 3,
    NAS_KSI_4           = 4,
    NAS_KSI_5           = 5,
    NAS_KSI_6           = 6,
    NO_KEY_IS_AVAILABLE = 7     /* no key is available(UE to network);reserved(network to UE) */
}NasKsi;

typedef enum CemmPlmnSelectTypeEnum_Tag
{
    CEMM_DEFAULT_PLMN_REG = 0,  // CEMM PLMN module decide by self
    CEMM_AUTO_PLMN_REG,
    CEMM_MANUAL_PLMN_REG,
    CEMM_MANUAL_THEN_AUTO_PLMN_REG, //if manual selection fails, automatic mode
}CemmPlmnSelectTypeEnum;

typedef enum PlmnSearchPowerLevelTag
{
    /*
     * OOS PLMN interval: 30s, 1 min, 2 mins
    */
    PLMN_SEARCH_POWER_LEVEL_NOT_CARE    = 0,
    /*
     * OOS PLMN interval: 5 mins, 10 mins, 15 mins, //default setting
    */
    PLMN_SEARCH_POWER_LEVEL_NORMAL_CARE = 1,
    /*
     * OOS PLMN interval: 10 mins, 30 mins, 1 hour
    */
    PLMN_SEARCH_POWER_LEVEL_MORE_CARE   = 2,
    /*
     * OOS PLMN interval: 30 s, then stop PLMN search, and let AT: AT$QCPLMNS to start PLMN search
    */
    PLMN_SEARCH_POWER_LEVEL_STRICT_CARE = 3,
    /*
     * Don't trigger PLMN search after OOS, let user decide to start PLMN search or not
    */
    PLMN_SEARCH_POWER_LEVEL_USER_CONTROL = 4
}PlmnSearchPowerLevel;

/******************************************************************************
 * Access Point Name
******************************************************************************/
#define MAX_APN_NAME            100
typedef struct AccessPointNameTag
{
    UINT8       length;
    UINT8       reserved0;
    UINT16      reserved1;
    UINT8       name[MAX_APN_NAME];
}AccessPointName;   //104 byte

typedef enum ConfigurationProtocolTag
{
    CONFIG_PROTOCOL_PPP = 0,
    CONFIG_PROTOCOL_OSP_IHOSS = 1
}
ConfigurationProtocol;

typedef enum PdnTypeTag
{
    PDN_IP_V4        = 0x01,
    PDN_IP_V6        = 0x02,
    PDN_IP_V4V6      = 0x03,
    PDN_UNUSED       = 0x04,
    PDN_NON_IP       = 0x05
}
PdnType;

/******************************************************************************
 * MSGADDRESS
******************************************************************************/
#define     MAX_SMS_ADDRESS_LENGTH          20
#define     MAX_SMS_LEN                     0xa0    //160
#define     UICC_MAX_ADDR_LEN               20

typedef struct MsgAddress_Tag
{
    UINT8      length;
    UINT8      typeOfNumber; //TypeOfNumber
    UINT8      numberingPlan; //NumberingPlan
    UINT8      reserved;
    UINT8      addressValue[MAX_SMS_ADDRESS_LENGTH];
}MsgAddress;

typedef struct UsatAddressTag
{
    UINT8                        TON; // UsatBcdTON
    UINT8                        NPI;//UsatBcdNPI
    UINT8                        len;
    UINT8                        addrValue[UICC_MAX_ADDR_LEN]; //Bcd number
}
UsatAddress;

typedef enum UsatSmsTpduType_Tag
{
    USAT_SMTPDU_DELIVER         = 0,
    USAT_SMTPDU_SUBMIT          = 1,
    USAT_SMTPDU_COMMAND         = 2
}UsatSmsTpduType;


/******************************************************************************
 * SMS Protocol ID
*****************************************************************************/
typedef struct SmsProtocolId_Tag
{
   UINT8                  protocolMeaning;  //ProtocolMeaning
   union
   {
        UINT8               smAlProtocolid;   //SM_AL_PROTOCOL
        UINT8               interWorkingProtocolId;   //TELEMATIC_INTERWORK
        UINT8               scCommandProtocolId;      //SM_FUNCTIONS
        UINT8               meCommandProtocolId;     //ME_FUNCTIONS
        UINT8               reservedProtocolId;      // RESERVED
        UINT8               scSpecificProtocolId;   // SC_SPECIFIC
        UINT8               rawData;    //Raw data format
   }protocolId;
   UINT16                   reserved;
}SmsProtocolId;

/******************************************************************************
 * SMS Data Coding
*****************************************************************************/

typedef enum WaitIndTyp_Tag
{
    MSG_IND_VOICEMAIL_MSG_WAITING          =0x00,
    MSG_IND_FAX_MSG_WAITING                =0x01,
    MSG_IND_ELECTRONIC_MAIL_MSG_WAITING    =0x02,
    MSG_IND_OTHER_MSG_WAITING              =0x03
}WaitIndTyp;

typedef struct MsgWaitInd_Tag
{
    BOOL            storeMsg;
    BOOL            setIndActive;
    UINT8           indType;    //WaitIndTyp
    UINT8           reserved;
}MsgWaitInd;

typedef struct SmsDataCodingTag
{
    UINT8                        smsCoding; //SmsCoding
    UINT8                        smsClass;  //SmsClass
    BOOL                         compressedText;
    BOOL                         isDataCodingMessageClass;
    BOOL                         msgWaitingIndPresent;
    MsgWaitInd                   msgWaitingInd;
}SmsDataCoding;

/*
 * Uicc Pin state
*/
typedef struct UiccPinStatusTag
{
    UINT8               alternativeKeyRef;      /* UiccKeyRefValue, alternative key reference */
    UINT8               numRemainingRetrys;
    UINT16              secretCodeInitialised:1;
    UINT16              enabled:1;
    UINT16              verified:1;
    UINT16              used:1;                 /* usage qualifier specifies whether the PIN should be used or not */
    UINT16              reserved:12;
}
UiccPinStatus;

/*
* Uicc File path
*/
#define MAX_FILE_PATH_ELEMENTS  10
typedef struct UiccFilePathTag
{
    UINT8     len;
    UINT8     reserved;
    UINT8     path[MAX_FILE_PATH_ELEMENTS];
}
UiccFilePath;

typedef struct EmmEventStatisNvmInfo_Tag
{
    UINT16  numAttachSucc;      /* count of Attach Success */
    UINT16  numAttachFail;      
    UINT16  numTauSucc;         /* count of TAU Success */    
    UINT16  numTauFail;             
    UINT16  numSrSucc;          /* count of Service request Success */
    UINT16  numSrFail;
    UINT16  numAuthFail;        /* count of Authentication Success */
    UINT16  numDetach;          /* count of Detach */
}
EmmEventStatisNvmInfo;


#endif

