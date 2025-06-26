#ifndef _NAS_COMMON_H_
#define _NAS_COMMON_H_
/*******************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    nascommon.h
 * Description:  define nas message structure
 * History:
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/

#include "cemmsig.h"
#include "uiccctrlsig.h"


/*******************************************************************************
* Macros
*******************************************************************************/

#define     NAS_MSG_HEADER_LENGTH                       2
#define     MAX_MOBILE_ID_LENGTH                        16
#define     MAX_UE_NETWORK_CAPABILITY_LEN               13
#define     MAX_PARTIAL_TAI_LIST_SIZE                   16
#define     MAX_TAI_LIST_SIZE                           16
#define     MAX_TAC_LIST_SIZE                           16
#define     MAX_EQUIVALENT_PLMNS                        16
#define     MAX_EMERGENCY_LIST_NUM                      10
#define     MAX_CALLED_BCD_NO_LEN                       80
#define     MAX_EPS_MOBILE_ID_IE_SIZE                   11
#define     MAX_EQUIVALENT_PLMNS_IE_SIZE                45
#define     MAX_EMERGENCY_NUMBER_LIST_IE_SIZE           48
#define     MAX_EPS_NETWORK_FEATURE_SUPPORT             2
#define     MAX_TRACKING_AREA_IDENTITY_LIST_IE_SIZE     96
#define     MAX_MOBILE_ID_IE_SIZE                       9
#define     MAX_AUTH_RES_IE_SIZE                        16
#define     MAX_NETWORK_NAME_LENGTH                     64
#define     MAX_UE_SECURITY_CAPABILITY_IE_SIZE          5
#define     MAX_HASH_VALUE_IE_SIZE                      8
#define     MAX_ADDITIONAL_INFORMATION_IE_SIZE          4
#define     MAX_DIAGNOSTIC_IE_SIZE                      28
#define     MAX_CAUSE_IE_SIZE                           30
#define     MAX_FACILITY_IE_SIZE                        255


/* EMM message IE size definition */
#define IE_LOCATION_AREA_ID_SIZE                            5
#define IE_TAI_SIZE                                         5
#define IE_DRX_PARAMETER_SIZE                               2
#define IE_ADDITIONAL_UPDATE_TYPE_SIZE                      1
#define IE_ADDITIONAL_UPDATE_RESULT_SIZE                    1
#define IE_DEVICE_PROPERTIES_SIZE                           1
#define IE_OLD_GUTI_TYPE_SIZE                               1
#define IE_MS_NETWORK_FEATURE_SUPPORT_SIZE                  1
#define IE_GPRS_TIMER_SIZE                                  1
#define IE_GPRS_TIMER_2_SIZE                                1
#define IE_GPRS_TIMER_3_SIZE                                1
#define IE_EXTENDED_DRX_PARAMETERS_SIZE                     1
#define IE_EMM_CAUSE_SIZE                                   1
#define IE_AUTH_PARAMETER_RAND_SIZE                         16
#define IE_AUTH_PARAMETER_AUTN_SIZE                         16
#define IE_LOCAL_TIME_ZONE_SIZE                             1
#define IE_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE_SIZE          7
#define IE_NETWORK_DAYLIGHT_SAVING_TIME_SIZE                1
#define IE_EPS_BEARER_CONTEXT_STATUS_SIZE                   2
#define IE_NONCE_SIZE                                       4
#define IE_SELECTED_NAS_SECURITY_ALGORITHMS_SIZE            1
#define IE_HEADER_COMPRESSION_CONFIGURATION_STATUS_SIZE     2
#define IE_DCN_ID_SIZE                                      2
#define IE_SMS_SERVICE_STATUS_SIZE                          1
#define IE_EXTENDED_EMM_CAUSE_SIZE                          1
#define IE_IMEISV_REQUEST_SIZE                              1
#define IE_HASH_MME_SIZE                                    8
#define IE_GENERIC_MESSAGE_CONTAINER_TYPE_SIZE              1

/*CESMS Related setting*/
#define   SMS_HEADER_SIZE               2
#define   NIBBLE_SIZE                   4
#define   CP_CAUSE_IE_SIZE              1
#define   MAX_RPPDU_LEN                 248
#define   MAX_CP_USER_DATA_IE_SIZE      248
#define   OCTET_SIZE                    8
#define   TIVALUE_RESERVED              7


/*CESS Related setting*/
#define   NAS_DOWNLINK_GENERIC_TRANSPORT_MIN_SIZE           6

/* Extract a single bit from an array of bytes
    Para1,  pointer to array of bytes   Para2  number of bit to extract   */
#define GetBit(P, B)  (BOOL)(((P)[((B)-1)/8] >> (((B)-1)%8)) & 1)


/* 24.007-11.2.4:Bit 8 of the IEI octet is set to "1" indicates a TIValue formatted
type 1 standard IE or a T formatted type 2 IEs. */

/* For EMM/ESM messages,type 2 information elements of format T with value part
consisting of 0 octets is not used,so not consider this case here*/
#define ExtractIei(X) (Iei)(((X) & 0x80) ? (X) & 0xF0 : (X))

/* the size of 'L' in TLV/LV is 1 octet */
#define LENGTH_SIZE_1_OCTET     1

/* the size of 'L' in TLV-E is 2 octet */
#define LENGTH_SIZE_2_OCTET     2

/** ESM message related **/
#define ESM_MSG_HEADER_SIZE      3
#define MAX_PCO_SIZE             250
#define MAX_CHAP_MSG_LENGTH     16
#define PRIM_DNS_ADDRESS_ID     0x81
#define PRIM_NBNS_ADDRESS_ID    0x82
#define SEC_DNS_ADDRESS_ID      0x83
#define SEC_NBNS_ADDRESS_ID     0x84

#define IPV4_ADDRESS            0x03
#define MOBILE_IPV4_ADDRESS     0x04
#define PDN_MAX_NW_ADDR_NUM     4
#define MAX_PDP_ADDR            20
#define USER_DATA_MAX_SIZE      1500
#define IPV4_ADDRESS_SIZE       4


/* ESM message IE size definition */
#define IE_MAX_ACCESS_POINT_NAME_SIZE   100
#define IE_MAX_PDN_ADDR_CONTENT_SIZE     13
#define IE_ESM_CAUSE_SIZE                1
#define IE_SPLMN_RATE_CTRL_SIZE          2
#define IE_MAX_PCO_SIZE                  251
#define IE_MAX_APN_AMBR_SIZE             6
#define IE_MAX_TFT_IE_SIZE               255
#define IE_MAX_ROHC_IE_SIZE              255
#define IE_GRPS_TIMER_3_SIZE             1
#define MAX_AUTH_STR_LEN_SIZE            81


#define MAX_FORBIDDEN_TAI_NUM_STORED_IN_TINY_CTX    3

/*******************************************************************************
* Type Definition
*******************************************************************************/

/*******************************************************************************
* Enums
*******************************************************************************/

/* The presence type of Information Element */
typedef enum IeTypeTag
{
    MANDATORY_IE,
    OPTIONAL_IE,
    CONDITIONAL_IE
}
IeType;


/******************************************************************************
 * UL air Message segments info
 * 1> These are AIR message which are before integrity check & cipher;
 * 2> Not contain the "Security protected NAS message" header
******************************************************************************/
typedef struct UlAirMessageSeg_Tag
{
    UINT16  dataLength;
    //UINT8   memType;    //DataPduMemType, disabled it, as memory not freed in securty function
    UINT8   reserved0;
    BOOL    needCipher; //as some AIR message, need partly cipher, this indicated whether need segment need to cipher
    UINT8   *data;
}UlAirMessageSeg;

/* 3 segs - for EMM signalling, 5 segs - for ESM (CESM_UL_UNIT_DATA_MAX_SEG) */
#define CEMM_UL_AIR_MSG_MAX_SEG     8   //UL must not extended 8 segments
typedef struct UlAirMessage_Tag
{
    UlAirMessageSeg airMsgSeg[CEMM_UL_AIR_MSG_MAX_SEG]; /*8*8 = 64 bytes*/
}UlAirMessage;

typedef struct DlAirMessageTag
{
    UINT16      dataLength;
    UINT8      *data;
}
DlAirMessage;

typedef struct NasPlainMsgTag
{
    UlAirMessage    ulPlainMsg;
    DlAirMessage    dlPlainMsg;
}
NasPlainMsg;

/* Refer to TS-24.301,subclause 7 */
typedef enum DecodeResultTag
{
    DECODE_SUCCEED = 0,                 /* Decode succeed */
    DECODE_FAIL,                        /* Decode fail */
    UNKNOWN_UNFORESEEN_MESSAGE_TYPE,    /* Unknown or Unforeseen message type */
    OUT_OF_SEQUENCE_IE,                 /* Out of sequence Information Element */
    REPEATED_IE ,                       /* Information Element which is a repeated one */
    COMPREHENSION_REQUIRED_IE,          /* A type 4 IE is encoded as 'comprehension required' if bits 5, 6, 7 and 8 of its IEI are set to zero */
    UNKNOWN_IE,                         /* Information Element with unknown IEI */
    WRONG_OPTIONAL_IE,                  /* Optional Information Element with wrong content */
    WRONG_MANDATORY_IE,                 /* Mandatory Information Element with wrong content */
    LACK_OF_MANDATORY_IE,               /* Lack of Mandatory Information Element */
    INVALID_TI_VALUE,                   /* Invalid transaction identifier */
    UNKNOWN_MESSAGE,                    /* Unknown message */
}
DecodeResult;

typedef enum NasProtocolDiscriminatorTag
{
    ESM_PD      = 0x02,     /* EPS session management messages */
    EMM_PD      = 0x07,     /* EPS mobility management messages */
    SMS_PD      = 0x09,     /* SMS messages */
    SS_PD       = 0x0B,     /* Non call related messages */
    TEST_PD     = 0x0F      /* used by tests procedures */
}
NasProtocolDiscriminator;

typedef enum IeiTag
{
    IEI_UNKNOWN_IE                              = 0,      /* IEs for which no IEI is defined */
    /************* EMM IEI ***************************/
    IEI_LOCATION_AREA_IDENTIFICATION            = 0x13,
    IEI_T3402_VALUE                             = 0x16,
    IEI_GPRS_TIMER                              = 0x17,
    IEI_MS_IDENTITY                             = 0x23,
    IEI_AUTHENTICATION_FAILURE_PARAMETER        = 0X30,
    IEI_EMERGENCY_NUMBER_LIST                   = 0x34,
    IEI_FULL_NETWORK_NAME                       = 0x43,
    IEI_SHORT_NETWORK_NAME                      = 0x45,
    IEI_LOCAL_TIME_ZONE                         = 0x46,
    IEI_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE      = 0x47,
    IEI_NETWORK_DAYLIGHT_SAVING_TIME            = 0x49,
    IEI_EQUIVALENT_PLMNS                        = 0x4A,
    IEI_HASH_MME                                = 0x4F,
    IEI_EPS_MOBILE_ID                           = 0x50,
    IEI_TAI                                     = 0x52,
    IEI_EMM_CAUSE                               = 0x53,
    IEI_TAI_LIST                                = 0x54,
    IEI_NONCE_UE                                = 0X55,
    IEI_NONCE_MME                               = 0X56,
    IEI_EPS_BEARER_CONTEXT_STATUS               = 0x57,
    IEI_UE_NETWORK_CAPABILITY                   = 0x58,
    IEI_T3423_VALUE                             = 0x59,
    IEI_T3412_VALUE                             = 0X5A,
    IEI_T3442_VALUE                             = 0x5B,
    IEI_DRX_PARAMETER                           = 0x5C,
    IEI_T3412_EXTENDED_VALUE                    = 0X5E,
    IEI_T3346_VALUE                             = 0x5F,
    IEI_EPS_EMM_NETWORK_FEATURE_SUPPORT         = 0x64,
    IEI_DCN_ID                                  = 0x65,
    IEI_ADDITIONAL_INFORMATION                  = 0x65,
    IEI_NAS_MESSAGE_CONTAINER                   = 0x67,
    IEI_HEADER_COMPRESSION_CONFIGURATION_STATUS = 0x68,
    IEI_T3324_VALUE                             = 0X6A,
    IEI_T3448_VALUE                             = 0x6B,
    IEI_EXTENDED_DRX_PARAMETERS                 = 0X6E,
    IEI_ESM_MESSAGE_CONTAINER                   = 0x78,
    IEI_REPLAYED_NAS_MESSAGE_CONTAINER_IE       = 0x79,
    IEI_EXTENDED_EMM_CAUSE                      = 0XA0,
    IEI_NAS_KEY_SET_IDENTIFIER                  = 0xB0,
    IEI_MS_NETWORK_FEATURE_SUPPORT              = 0XC0,
    IEI_IMEISV_REQUEST                          = 0xC0,
    IEI_DEVICE_PROPERTIES                       = 0xD0,
    IEI_OLD_GUTI_TYPE                           = 0xE0,
    IEI_SMS_SERVICE_STATUS                      = 0xE0,
    IEI_ADDITIONAL_UPDATE_TYPE                  = 0xF0,
    IEI_ADDITIONAL_UPDATE_RESULT                = 0xF0,
    IEI_SMS_USER_USER_IE                        = 0x7E,

    /************* ESM IEI ***************************/
    IEI_ESM_LLC_SAPI                            = 0x32,
    IEI_ESM_NEGOTIATED_QOS                      = 0x30,
    IEI_ESM_ACCESS_POINT_NAME                   = 0x28,
    IEI_ESM_RADIO_PRIORITY                      = 0x80,
    IEI_ESM_PROTOCOL_CONFIG_OPTIONS             = 0x27,
    IEI_ESM_BACK_OFF_TIMER_VALUE                = 0x37, /* T3396 value */
    IEI_ESM_TRANSACTION_IDENTIFIER              = 0x5D,
    IEI_ESM_PACKET_FLOW_IDENTIFIER              = 0x34,
    IEI_ESM_NEGOTIATED_LLC_SAPI                 = 0x32,
    IEI_ESM_APN_AMBR                            = 0x5E,
    IEI_ESM_ESM_CAUSE                           = 0x58,
    IEI_ESM_REQUIRED_TRAFFIC_FLOW_QOS           = 0x5B,
    IEI_ESM_NEW_EPS_QOS                         = 0x5B,
    IEI_ESM_TFT                                 = 0x36,
    IEI_ESM_NEW_QOS                             = 0x30,
    IEI_ESM_HEADER_COMP_CONFIG                  = 0x66,
    IEI_ESM_CONTROL_PLANE_ONLY_IND              = 0x90,
    IEI_ESM_EXTENDED_PCO                        = 0x7B,
    IEI_ESM_SERVING_PLMN_RATE_CONTROL           = 0x6E,
    IEI_ESM_INFORMATION_TRANSFER_FLAG           = 0xD0,
    IEI_ESM_AGGREGATE_MAX_BIT_RATE              = 0x5E,
    IEI_ESM_RELEASE_ASSISTANCE_INDICATION       = 0xF0,
    IEI_DEFAULT                                 = 0xFF,

    /************* SS IEI ***************************/
    IEI_CAUSE                                   = 0x08,
    IEI_FACILITY                                = 0x1C,
    IEI_SS_VERSION                              = 0x7F
}
Iei;

typedef enum SecurityHeaderTypeTag
{
    PLAIN_NAS_MESSAGE                                              = 0,
    INTEGRITY_PROTECTED                                            = 1,
    INTEGRITY_PROTECTED_AND_CIPHERED                               = 2,
    INTEGRITY_PROTECTED_WITH_NEW_EPS_SECURITY_CONTEXT              = 3,
    INTEGRITY_PROTECTED_AND_CIPHERED_WITH_NEW_EPS_SECURITY_CONTEXT = 4,
    INTEGRITY_PROTECTED_AND_PARTIALLY_CIPHERED                     = 5,
    SERVICE_REQUEST_MESSAGE                                        = 12
}
SecurityHeaderType;

typedef Tai TrackingAreaIdentity;

typedef enum TaiListTypeTag
{
   TAI_LIST_TYPE_0 = 0,
   TAI_LIST_TYPE_1 = 1,
   TAI_LIST_TYPE_2 = 2
}
TaiListType;

typedef struct PartialTaiList_0Tag
{
    Plmn    plmn;
    UINT16  tac[MAX_TAC_LIST_SIZE];
}
PartialTaiList_Type_0;

typedef PartialTaiList_Type_0   PartialTaiList_Type_1;

typedef struct PartialTaiList_2Tag
{
    Tai    tai[MAX_TAI_LIST_SIZE];
}
PartialTaiList_Type_2;

typedef union TaiListUnionTag
{
    PartialTaiList_Type_0            taiListType_0;
    PartialTaiList_Type_1            taiListType_1;
    PartialTaiList_Type_2            taiListType_2;
}TaiListUnion;

typedef struct PartialTaiListTag
{
    TaiListType                 taiListType;
    UINT8                       numOfElements;
    TaiListUnion                taiListUnion;
}
PartialTaiList;

typedef struct TaiListTag
{
    UINT8               numOfList;
    PartialTaiList      partialTaiList[MAX_PARTIAL_TAI_LIST_SIZE];
}
TaiList;

typedef struct TaiWithTypeTag
{
    Plmn            plmn;
    UINT16          tac;
    TaiListType     taiListType;
}
TaiWithType;

typedef enum EpsAttachResultTag
{
    EPS_ONLY_ATTACHED          = 1,
    COMBINED_EPS_IMSI_ATTACHED = 2
}
EpsAttachResult;

typedef enum EpsAttachTypeValueTag
{
    EPS_ATTACH              = 1,
    COMBINED_EPS_IMS_ATTACH = 2,
    EPS_EMERGENCY_ATTACH    = 6,
    ATTACH_TYPE_RESERVED    = 7
}
EpsAttachTypeValue;

typedef enum TscFlagTag
{
    NATIVE_SECURITY_CONTEXT,    /* for KSIASME */
    MAPPED_SECURITY_CONTEXT     /* for KSISGSN */
}
TscFlag;

typedef struct NasKeySetIdentifierTag
{
    TscFlag         tsc;
    NasKsi          eKsi;
}
NasKeySetIdentifier;

typedef struct LocationAreaIdTag
{
    UINT16         mcc;
    UINT16         mncWithAddInfo;
    UINT16         lac;
}
LocationAreaId;

typedef enum IdTypeTag
{
    NO_ID                   = 0,
    IMSI_ID                 = 1,
    IMEI_ID                 = 2,
    IMEISV_ID               = 3,
    TMSI_PTMSI_MTMSI_ID     = 4,
    TMGI_ID                 = 5,
    ID_TYPE_RESERVED
}
IdType;

typedef enum IdType2Tag
{
    TYPE2_IMSI_ID     = 1,
    TYPE2_IMEI_ID     = 2,
    TYPE2_IMEISV_ID   = 3,
    TYPE2_TMSI_ID     = 4
}
IdType2;

typedef struct MobileIdentityTag
{
    IdType      idType;
    UINT32      tmsi;
    UINT8       numOfDigit;
    UINT8       idDigit[MAX_MOBILE_ID_LENGTH];
}
MobileIdentity;

typedef enum EpsIdTypeTag
{
    EPS_NO_ID            = 0,
    EPS_IMSI_ID          = 1,
    EPS_IMEI_ID          = 3,
    EPS_GUTI_ID          = 6,
    EPS_ID_TYPE_RESERVED
}
EpsIdType;

typedef struct GutiTag
{
    UINT8   gutiContents[MAX_GUTI_SIZE];
}
Guti;

typedef struct EpsMobileIdentityTag
{
    EpsIdType       idType;
    UINT8           length;
    Guti            guti;
    UINT8           numOfDigit;
    UINT8           idDigit[MAX_MOBILE_ID_LENGTH];
}
EpsMobileIdentity;

typedef enum EmmCauseTag
{
    EMM_CAUSE_IMSI_UNKNOWN_IN_HSS                                  = 0x02,
    EMM_CAUSE_ILLEGAL_UE                                           = 0x03,
    EMM_CAUSE_IMEI_NOT_ACCEPTED                                    = 0x05,
    EMM_CAUSE_ILLEGAL_ME                                           = 0x06,
    EMM_CAUSE_EPS_SERVICES_NOT_ALLOWED                             = 0x07,
    EMM_CAUSE_EPS_AND_NON_EPS_SERVICES_NOT_ALLOWED                 = 0x08,
    EMM_CAUSE_UE_ID_CAN_NOT_BE_DERIVED_IN_NETWORK                  = 0x09,
    EMM_CAUSE_IMPLICITLY_DETACHED                                  = 0x0A,
    EMM_CAUSE_PLMN_NOT_ALLOWED                                     = 0X0B,
    EMM_CAUSE_TRACKING_AREA_NOT_ALLOWED                            = 0x0C,
    EMM_CAUSE_ROAMING_NOT_ALLOWED_IN_THIS_TRACKING_AREA            = 0X0D,
    EMM_CAUSE_EPS_SERVICE_NOT_ALLOWED_IN_THIS_PLMN                 = 0x0E,
    EMM_CAUSE_NO_SUITABLE_CELLS_IN_TRACKING_AREA                   = 0x0F,
    EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE                        = 0x10,
    EMM_CAUSE_NETWORK_FAILURE                                      = 0x11,
    EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE                              = 0x12,
    EMM_CAUSE_ESM_FAILURE                                          = 0x13,
    EMM_CAUSE_MAC_FAILURE                                          = 0X14,
    EMM_CAUSE_SYNCH_FAILURE                                        = 0X15,
    EMM_CAUSE_CONGESTION                                           = 0X16,
    EMM_CAUSE_UE_SECURITY_CAPAILITIES_MISMATCH                     = 0x17,
    EMM_CAUSE_SECURITY_MODE_REJECTED_UNSPECIFIED                   = 0x18,
    EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                          = 0x19,
    EMM_CAUSE_NON_EPS_AUTHENTICATION_UNACCEPTABLE                  = 0x1A,
    EMM_CAUSE_REQUESTED_SERVICE_OPTION_NOT_AUTHORIZED_IN_THIS_PLMN = 0X23,
    EMM_CAUSE_CS_SERVICE_TEMPORARILY_NOT_AVAILABLE                 = 0x27,
    EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED                      = 0x28,
    EMM_CAUSE_SERVERE_NETWORK_FAILURE                              = 0x2A,
    EMM_CAUSE_SYMANTICALLY_INCORRECT_MESSAGE                       = 0X5F,
    EMM_CAUSE_INVALID_MANDATORY_INFORMATION                        = 0X60,
    EMM_CAUSE_MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED         = 0X61,
    EMM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE  = 0X62,
    EMM_CAUSE_INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED  = 0X63,
    EMM_CAUSE_CONDITIONAL_IE_ERROR                                 = 0X64,
    EMM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE       = 0X65,
    EMM_CAUSE_PROTOCOL_ERROR_UNSPECIFIED                           = 0X6F,
    /* internal cause */
    EMM_CAUSE_AUTHENTICATION_REJECT                                = 0x101,
    EMM_CAUSE_NO_CAUSE                                             = 0XFFFF
}
EmmCause;

typedef struct EquivalentPlmnListTag
{
    UINT8               numOfPlmn;
    Plmn                eplmn[MAX_EQUIVALENT_PLMNS];
}
EquivalentPlmnList;

typedef enum EmergencyServiceCategoryTag
{
    POLICE                        = 0,
    AMBULANCE                     = 2,
    FIRE_BRIGADE                  = 4,
    MARINE_GUARD                  = 8,
    MOUNTAIN_RESCURE              = 16,
    MANUAL_INITIATED_ECALL        = 32,
    AUTOMATICALLY_INITIATED_ECALL = 64
}
EmergencyServiceCategory;

typedef struct EmergencyNumberTag
{
    EmergencyServiceCategory    serviceCategory;
    UINT8                       numOfDigit;
    UINT8                       numberDigit[MAX_CALLED_BCD_NO_LEN];
}
EmergencyNumber;

typedef struct EmergencyNumberListTag
{
    UINT8               numOfList;
    EmergencyNumber     information[MAX_EMERGENCY_LIST_NUM];
}
EmergencyNumberList;

typedef struct EpsNetworkFeatureSupportTag
{
    UINT16      imsVoiceSupported : 1;              /* IMS voice over PS session indicator (IMS VoPS) */
    UINT16      emerBearerServicesSupported : 1;    /* Emergency bearer services indicator (EMC BS) */
    UINT16      esrpsSupported : 1;                 /* Support of EXTENDED SERVICE REQUEST for packet services (ESRPS) */
    UINT16      withoutPdnSupported : 1;            /* EMM REGISTERED without PDN connectivity (ERw/oPDN) */
    UINT16      cpCiotSupported : 1;                /* Control plane CIoT EPS optimization (CP CIoT) */
    UINT16      upCiotSupported : 1;                /* User plane CIoT EPS optimization (UP CIoT) */
    UINT16      s1UdataSupported : 1;               /* This bit indicates the capability for S1-u data transfer */
    UINT16      hcCpCiotSupported : 1;              /* Header compression for control plane CIoT EPS optimization (HC-CP CIoT) */
    UINT16      ePcoSupported : 1;                  /* Extended protocol configuration options (ePCO) */
    UINT16      restrictEc : 1;                     /* Restriction on enhanced coverage (RestrictEC) */
}
EpsNetworkFeatureSupport;

typedef struct UeNetworkCapabilityTag
{
    UINT8       networkCapabilityLength;
    UINT8       networkCapability[MAX_UE_NETWORK_CAPABILITY_LEN];
}
UeNetworkCapability;

typedef struct EsmMessageContainerTag
{
    UINT16        messageLength;     /* 24.301-9.9.3.15,Max value of 65535 octets */
    UINT8        *pMessage;
}
EsmMessageContainer;

typedef enum NonDrxModeTag
{
    NO_NON_DRX_MODE         = 0,
    MAX_1_SEC_NON_DRX_MODE  = 1,
    MAX_2_SEC_NON_DRX_MODE  = 2,
    MAX_4_SEC_NON_DRX_MODE  = 3,
    MAX_8_SEC_NON_DRX_MODE  = 4,
    MAX_16_SEC_NON_DRX_MODE = 5,
    MAX_32_SEC_NON_DRX_MODE = 6,
    MAX_64_SEC_NON_DRX_MODE = 7
}
NonDrxMode;

/* -------------------------------------------------------------------------
    This field represents two separate values. For S1 mode, it represents
    the DRX cycle parameter 'T' as defined in 3GPP TS 36.304.
    --------------------------------------------------------------------------*/
typedef enum DrxCycleLengthAndValueForS1Tag
{
    DRX_VALUE_NOT_SPECIFIED_BY_THE_MS = 0,
    DRX_CYCLE_LEN_COEFFICIENT_6_T_32  = 6,
    DRX_CYCLE_LEN_COEFFICIENT_7_T_64  = 7,
    DRX_CYCLE_LEN_COEFFICIENT_8_T_128 = 8,
    DRX_CYCLE_LEN_COEFFICIENT_9_T_256 = 9
}
DrxCycleLengthAndValueForS1;

typedef struct DrxParameterTag
{
    UINT8                           splitPgCycleCode;
    NonDrxMode                      nonDrxTimer;
    BOOL                            splitOnCcch;
    DrxCycleLengthAndValueForS1     drxCycleLenAndValue;
}
DrxParameter;

typedef enum AutvTag
{
    AUTV_NO_ADDITIONAL_INFORMATION = 0,
    AUTV_SMS_ONLY                  = 1
}
Autv;

typedef enum PnbCIoTTag
{
    PNB_CIOT_NO_ADDITIONAL_INFORMATION  = 0,
    PNB_CIOT_CONTROL_PLANE_OPTIMIZATION = 1,
    PNB_CIOT_USER_PLANE_OPTIMIZATION    = 2,
    PNB_CIOT_RESERVED                   = 3
}
PnbCIoT;

typedef struct AdditionalUpdateTypeTag
{
    Autv        autv;
    BOOL        saf;
    PnbCIoT     pnbCiot;
}
AdditionalUpdateType;

typedef enum DevicePropertiesTag
{
    NOT_CONFIGURED_NAS_SIGNALLING_LOW_PRIORITY = 0,
    CONFIGURED_NAS_SIGNALLING_LOW_PRIORITY = 1
}
DeviceProperties;


typedef enum GutiTypeTag
{
    NATIVE_GUTI = 0,
    MAPPED_GUTI = 1
}
GutiType;

typedef struct MsNetworkFeatureSupportTag
{
    BOOL         extPeriodicTimer;  /*  0 MS does not support the extended periodic timer in this domain
                                        1 MS supports the extended periodic timer in this domain */
}
MsNetworkFeatureSupport;

typedef enum SmsServiceStatusTag
{
    SMS_SERVICE_NOT_AVAILABLE              = 0,
    SMS_SERVICE_NOT_AVAILABLE_IN_THIS_PLMN = 1,
    NETWORK_FAILURE                        = 2,
    CONGESTION                             = 3,
    SMS_SERVICE_ABNORMAL_CASE
}
SmsServiceStatus;

typedef enum eUtranAllowedTag
{
    EUTRAN_ALLOWED = 0,
    EUTRAN_NOT_ALLOWED = 1
}
eUtranAllowed;

typedef enum EpsOptimizationInfoTag
{
    NO_EPS_OPTIMIZATION_INFORMATION = 0,
    REQUESTED_EPS_OPTIMIZATION_NOT_SUPPORTED = 1
}
EpsOptimizationInfo;

typedef struct ExtendedEmmCauseTag
{
    eUtranAllowed           eUtranAllowed;
    EpsOptimizationInfo     epsOptimizationInfo;
}
ExtendedEmmCause;

typedef AuthRes AuthResponseParameter;

typedef enum TypeOfDetachMoTag
{
    EPS_DETACH               = 1,
    IMSI_DETACH              = 2,
    COMBINED_DETACH          = 3,
    MO_DETACH_TYPE_RESERVED1 = 6,
    MO_DETACH_TYPE_RESERVED2 = 7
}
TypeOfDetachMo;

typedef struct MoDetachTypeTag
{
    BOOL                switchOff;
    TypeOfDetachMo      detachType;
}
MoDetachType;

typedef enum MtDetachTypeTag
{
    REATTACH_REQUIRED        = 1,
    REATTACH_NOT_REQUIRED    = 2,
    MT_IMSI_DETACH           = 3,
    MT_DETACH_TYPE_RESERVED1 = 6,
    MT_DETACH_TYPE_RESERVED2 = 7
}
MtDetachType;

typedef struct NasMessageContainerTag
{
    UINT8   messageLength;
    UINT8   *pMessage;
}
NasMessageContainer;

typedef enum GenericMessageContainerTypeTag
{
    LPP_MESSAGE_CONTAINER = 1,
    LCS_MESSAGE_CONTAINER = 2
}
GenericMessageContainerType;

typedef struct GenericMessageContainerTag
{
    UINT16   messageLength;
    UINT8   *pMessage;
}
GenericMessageContainer;

typedef struct AdditionalInformationTag
{
    UINT8   length;
    UINT8   data[MAX_ADDITIONAL_INFORMATION_IE_SIZE];
}
AdditionalInformation;

typedef struct ReplayedNasMessageContainerTag
{
    UINT16   messageLength;
    UINT8   *pMessage;
    UINT8    reserved;
}
ReplayedNasMessageContainer;

typedef enum CodingSchemeTag
{
    CELL_BROADCAST_DATA_CODING  =  0,
    UCS2_CODING                 =  1
}
CodingScheme;

typedef struct NetworkNameTag
{
    UINT8            lenOfNwName;
    UINT8            numOfSpareBits;
    BOOL             addCi;
    CodingScheme     codingScheme;
    UINT8            textString[MAX_NETWORK_NAME_LENGTH];
}
NetworkName;

typedef UINT8 TimeZone;

typedef struct TimeZoneAndTimeTag
{
    UINT8       year;
    UINT8       month;
    UINT8       day;
    UINT8       hour;
    UINT8       minute;
    UINT8       second;
    UINT8       timeZone;
    UINT8       reserved;
}
TimeZoneAndTime;

typedef enum DaylightSavingTimeTag
{
    NO_ADJUSTMENT             = 0,
    PLUS_ONE_HOUR_ADJUSTMENT  = 1,
    PLUS_TWO_HOURS_ADJUSTMENT = 2
}
DaylightSavingTime;

typedef enum ExtendedServiceTypeTag
{
    MO_CS_FALLBACK_OR_1XCS_FALLBACK                = 0,
    MT_CS_FALLBACK_OR_1XCS_FALLBACK                = 1,
    MO_CS_FALLBACK_OR_1XCS_FALLBACK_EMERGENCY_CALL = 2,
    PACKET_SERVICE_VIA_S1                          = 8
}
ExtendedServiceType;

typedef struct NasSecurityAlgorithmsTag
{
    IntegrityAlgorithm      integrityAlgorithm;
    CipheringAlgorithm      encryptionAlgorithm;
}
NasSecurityAlgorithms;

typedef struct UeSecurityCapabilityTag
{
    UINT8   securitycapabilityLength;
    UINT8   securitycapability[MAX_UE_SECURITY_CAPABILITY_IE_SIZE];
}
UeSecurityCapability;

typedef enum ImeisvRequestTag
{
    IMEISV_NOT_REQUESTED    = 0,
    IMEISV_REQUESTED        = 1
}
ImeisvRequest;

typedef struct NonceTag
{
    UINT8   nonceValue[IE_NONCE_SIZE];
}
Nonce;

typedef struct HashMmeTag
{
    UINT8   hashMmeLength;
    UINT8   hashMmeValue[MAX_HASH_VALUE_IE_SIZE];
}
HashMme;

typedef struct KsiAndSnTag
{
    NasKsi      ksi;
    UINT8       sequenceNumber;
}
KsiAndSn;

typedef enum EpsUpdateResultTag
{
    TA_UPDATED                               = 0,
    COMBINED_TA_LA_UPDATED                   = 1,
    TA_UPDATED_AND_ISR_ACTIVATED             = 4,
    COMBINED_TA_LA_UPDATED_AND_ISR_ACTIVATED = 5
}
EpsUpdateResult;

typedef enum EpsUpdateTypeValueTag
{
    TA_UPDATING                              = 0,
    COMBINED_TA_LA_UPDATING                  = 1,
    COMBINED_TA_LA_UPDATING_WITH_IMSI_ATTACH = 2,
    PERIODIC_TA_UPDATING                     = 3
}
EpsUpdateTypeValue;

typedef struct EpsUpdateTypeTag
{
    BOOL                    activeFlag;
    EpsUpdateTypeValue      updateTypeValue;
}
EpsUpdateType;

typedef enum ControlPlaneServiceTypeValueTag
{
    MOBILE_ORIGINATING_REQUEST = 0,
    MOBILE_TERMINATING_REQUEST = 1
}
ControlPlaneServiceTypeValue;

typedef struct ControlPlaneServiceTypeTag
{
    BOOL                            activeFlag;
    ControlPlaneServiceTypeValue    serviceTypeValue;
}
ControlPlaneServiceType;


/*******************************************************************************
* EMM message structure
*******************************************************************************/

typedef struct EmmAttachAcceptTag
{
    EpsAttachResult                     epsAttachResult;
    GprsTimer                           t3412Value;
    TaiList                            *taiList;
    EsmMessageContainer                 esmMessageContainer;
    BOOL                                gutiPresent;
    EpsMobileIdentity                   guti;
    BOOL                                laiPresent;
    LocationAreaId                      lai;
    BOOL                                msIdentityPresent;
    MobileIdentity                      msIdentity;
    BOOL                                emmCausePresent;
    EmmCause                            emmCause;
    BOOL                                t3402ValuePresent;
    GprsTimer                           t3402Value;
    BOOL                                t3423ValuePresent;
    GprsTimer                           t3423Value;
    BOOL                                ePlmnListPresent;
    EquivalentPlmnList                 *ePlmnList;
    BOOL                                emergencyNumberListPresent;
    EmergencyNumberList                *emergencyNumberList;
    BOOL                                epsNetworkFeatureSupportPresent;
    EpsNetworkFeatureSupport            epsNetworkFeatureSupport;
    BOOL                                additionalUpdateResultPresent;
    AdditionalUpdateResult              additionalUpdateResult;
    BOOL                                t3412ExtendedValuePresent;
    GprsTimer3                          t3412ExtendedValue;
    BOOL                                t3324ValuePresent;
    GprsTimer2                          t3324Value;
    BOOL                                extendedDrxParameterPresent;
    ExtendedDrxParameters               extendedDrxParameters;
    BOOL                                dcnIdPresent;
    UINT16                              dcnId;
    BOOL                                smsServiceStatusPresent;
    SmsServiceStatus                    smsServiceStatus;
    BOOL                                t3448ValuePresent;
    GprsTimer2                          t3448Value;
}
EmmAttachAccept;

typedef struct EmmAttachCompleteTag
{
    EsmMessageContainer    esmMessageContainer;
}
EmmAttachComplete;

typedef struct EmmAttachRejectTag
{
    EmmCause                emmCause;
    BOOL                    esmMessageContainerPresent;
    EsmMessageContainer     esmMessageContainer;
    BOOL                    t3346ValuePresent;
    GprsTimer2              t3346Value;
    BOOL                    t3402ValuePresent;
    GprsTimer2              t3402Value;
    BOOL                    extendedEmmCausePresent;
    ExtendedEmmCause        extendedEmmCause;
}
EmmAttachReject;

typedef struct EmmAttachRequestTag
{
    EpsAttachTypeValue                  epsAttachType;
    NasKeySetIdentifier                 nasKsi;
    EpsMobileIdentity                   epsMobileIdentity;
    UeNetworkCapability                 ueNetworkCapability;
    EsmMessageContainer                 esmMessageContainer;
    BOOL                                lastVisitedRegisteredTaiPresent;
    TrackingAreaIdentity                lastVisitedRegisteredTai;
    BOOL                                drxParameterPresent;
    DrxParameter                        drxParameter;
    BOOL                                additionalUpdateTypePresent;
    AdditionalUpdateType                additionalUpdateType;
    BOOL                                devicePropertiesPresent;
    DeviceProperties                    deviceProperties;
    BOOL                                oldGutiTypePresent;
    GutiType                            oldGutiType;
    BOOL                                msNetworkFeaturePresent;
    MsNetworkFeatureSupport             msNetworkFeature;
    BOOL                                t3324ValuePresent;
    GprsTimer2                          t3324Value;
    BOOL                                t3412ExtendedValuePresent;
    GprsTimer3                          t3412ExtendedValue;
    BOOL                                extendedDrxParameterPresent;
    ExtendedDrxParameters               extendedDrxParameters;
}
EmmAttachRequest;

typedef struct EmmAuthenticationFailureTag
{
    EmmCause        emmCause;
    BOOL            autsParameterPresent;
    Auts            autsParameter;
}
EmmAuthenticationFailure;

typedef struct EmmAuthenticationRequestTag
{
    NasKeySetIdentifier     nasKsi;
    UINT8                   rand[RAND_SIZE];
    UINT8                   autn[AUTN_SIZE];
}
EmmAuthenticationRequest;

typedef struct EmmAuthenticationResponseTag
{
    AuthResponseParameter  response;
}
EmmAuthenticationResponse;

typedef struct EmmMoDetachRequestTag
{
    MoDetachType            moDetachType;
    NasKeySetIdentifier     nasKsi;
    EpsMobileIdentity       epsMobileIdentity;
}
EmmMoDetachRequest;

typedef struct EmmMtDetachRequestTag
{
    MtDetachType    mtDetachType;
    BOOL            emmCausePresent;
    EmmCause        emmCause;
}
EmmMtDetachRequest;

typedef struct EmmDownlinkNasTransportTag
{
    NasMessageContainer     nasMessageContainer;
}
EmmDownlinkNasTransport;

typedef struct EmmInformationTag
{
    BOOL                    fullNameForNwPresent;
    NetworkName             fullNameForNw;
    BOOL                    shortNameForNwPresent;
    NetworkName             shortNameForNw;
    BOOL                    locTimeZonePresent;
    TimeZone                locTimeZone;
    BOOL                    universalTimeAndLocTimeZonePresent;
    TimeZoneAndTime         universalTimeAndLocTimeZone;
    BOOL                    nwDaylightSavingTimePresent;
    DaylightSavingTime      nwDaylightSavingTime;
}
EmmInformation;

typedef struct EmmStatusTag
{
    EmmCause    emmCause;
}
EmmStatus;

typedef struct EmmExtendedServiceRequestTag
{
    ExtendedServiceType     serviceType;
    NasKeySetIdentifier     nasKsi;
    MobileIdentity          mTmsi;
    BOOL                    epsBearerContextStatusPresent;
    UINT16                  epsBearerContextStatus;
    BOOL                    devicePropertiesPresent;
    DeviceProperties        deviceProperties;
}
EmmExtendedServiceRequest;

typedef struct EmmGutiReallocCommandTag
{
    EpsMobileIdentity       guti;
    BOOL                    taiListPresent;
    TaiList                *taiList;
    BOOL                    dcnIdPresent;
    UINT16                  dcnId;
}
EmmGutiReallocCommand;

typedef struct EmmIdentityRequestTag
{
    IdType2     idType;
}
EmmIdentityRequest;

typedef struct EmmIdentityResponseTag
{
    MobileIdentity    mobileId;
}
EmmIdentityResponse;

typedef struct EmmSecurityModeCommandTag
{
    NasSecurityAlgorithms       selectedNasSecurityAlgorithms;
    NasKeySetIdentifier         nasKsi;
    UeSecurityCapability        replayedUeSecurityCapabilities;
    BOOL                        imeisvRequestPresent;
    ImeisvRequest               imeisvRequest;
    BOOL                        replayedNonceUePresent;
    Nonce                       replayedNonceUe;
    BOOL                        nonceMmePresent;
    Nonce                       nonceMme;
    BOOL                        hashMmePresent;
    HashMme                     hashMme;
}
EmmSecurityModeCommand;


/******************************************************************************
 * jcweng
 * Used to store Security Protected Nas Message, which is sent to/received from CERRC
 * 1> if not "Service request", maybe contain "Security protected NAS message" header (if UE has valid security context);
 * 2> if "Service Request", just the whole "Service Request" TLV encoded message;
******************************************************************************/
typedef struct CemmSecProtMsgPdu_Tag
{
    UINT16  length;
    UINT8   nasMsgFirstBitOffset;   // for UL, always set to 0;
    UINT8   reserved0;

    UINT8   *pData;
}CemmSecProtMsgPdu;

typedef struct SecurityProtectedNasMessageTag
{
    CemmSecProtMsgPdu   protectedMsg;
}
SecurityProtectedNasMessage;

typedef struct EmmServiceRejectTag
{
    EmmCause        emmCause;
    BOOL            t3442ValuePresent;
    GprsTimer       t3442Value;
    BOOL            t3346ValuePresent;
    GprsTimer2      t3346Value;
    BOOL            t3448ValuePresent;
    GprsTimer2      t3448Value;
}
EmmServiceReject;

typedef struct EmmSecurityModeCompleteTag
{
    BOOL                            imeisvPresent;
    MobileIdentity                  imeisv;
    BOOL                            replayedNasMsgContainerPresent;
    ReplayedNasMessageContainer     replayedNasMsgContainer;
}
EmmSecurityModeComplete;

typedef struct EmmSecurityModeRejectTag
{
    EmmCause    emmCause;
}
EmmSecurityModeReject;

typedef struct EmmServiceRequestTag
{
    KsiAndSn    ksiAndSn;
    UINT16      shortMac;
}
EmmServiceRequest;

typedef struct EmmTrackingAreaUpdateAcceptTag
{
    EpsUpdateResult                 epsUpdateResult;
    BOOL                            t3412ValuePresent;
    GprsTimer                       t3412Value;
    BOOL                            gutiPresent;
    EpsMobileIdentity               guti;
    BOOL                            taiListPresent;
    TaiList                        *taiList;
    BOOL                            epsBearerContextStatusPresent;
    UINT16                          epsBearerContextStatus;
    BOOL                            laiPresent;
    LocationAreaId                  lai;
    BOOL                            msIdentityPresent;
    MobileIdentity                  msIdentity;
    BOOL                            emmCausePresent;
    EmmCause                        emmCause;
    BOOL                            t3402ValuePresent;
    GprsTimer                       t3402Value;
    BOOL                            t3423ValuePresent;
    GprsTimer                       t3423Value;
    BOOL                            ePlmnListPresent;
    EquivalentPlmnList             *ePlmnList;
    BOOL                            emergencyNumberListPresent;
    EmergencyNumberList            *emergencyNumberList;
    BOOL                            epsNetworkFeatureSupportPresent;
    EpsNetworkFeatureSupport        epsNetworkFeatureSupport;
    BOOL                            additionalUpdateResultPresent;
    AdditionalUpdateResult          additionalUpdateResult;
    BOOL                            t3412ExtendedValuePresent;
    GprsTimer3                      t3412ExtendedValue;
    BOOL                            t3324ValuePresent;
    GprsTimer2                      t3324Value;
    BOOL                            extendedDrxParameterPresent;
    ExtendedDrxParameters           extendedDrxParameters;
    BOOL                            headerCompressionConfigurationStatusPresent;
    UINT16                          headerCompressionConfigurationStatus;
    BOOL                            dcnIdPresent;
    UINT16                          dcnId;
    BOOL                            smsServiceStatusPresent;
    SmsServiceStatus                smsServiceStatus;
    BOOL                            t3448ValuePresent;
    GprsTimer2                      t3448Value;
}
EmmTrackingAreaUpdateAccept;

typedef struct EmmTrackingAreaUpdateRejectTag
{
    EmmCause                emmCause;
    BOOL                    t3346ValuePresent;
    GprsTimer2              t3346Value;
    BOOL                    extendedEmmCausePresent;
    ExtendedEmmCause        extendedEmmCause;
}
EmmTrackingAreaUpdateReject;

typedef struct EmmTrackingAreaUpdateRequestTag
{
    EpsUpdateType               epsUpdateType;
    NasKeySetIdentifier         nasKsi;
    EpsMobileIdentity           oldGuti;
    BOOL                        ueNetworkCapabilityPresent;
    UeNetworkCapability         ueNetworkCapability;
    BOOL                        lastVisitedRegisteredTaiPresent;
    TrackingAreaIdentity        lastVisitedRegisteredTai;
    BOOL                        drxParametersPresent;
    DrxParameter                drxParameter;
    BOOL                        epsBearerContextStatusPresent;
    UINT16                      epsBearerContextStatus;
    BOOL                        additionalUpdateTypePresent;
    AdditionalUpdateType        additionalUpdateType;
    BOOL                        oldGutiTypePresent;
    GutiType                    oldGutiType;
    BOOL                        devicePropertiesPresent;
    DeviceProperties            deviceProperties;
    BOOL                        msNetworkFeaturePresent;
    MsNetworkFeatureSupport     msNetworkFeature;
    BOOL                        t3324ValuePresent;
    GprsTimer2                  t3324Value;
    BOOL                        t3412ExtendedValuePresent;
    GprsTimer3                  t3412ExtendedValue;
    BOOL                        extendedDrxParameterPresent;
    ExtendedDrxParameters       extendedDrxParameters;
}
EmmTrackingAreaUpdateRequest;

typedef struct EmmUplinkNasTransportTag
{
    NasMessageContainer  nasMessageContainer;
}
EmmUplinkNasTransport;

typedef struct EmmDownlinkGenericNasTransportTag
{
    GenericMessageContainerType     msgContainerType;
    GenericMessageContainer         genericMsgContainer;
    BOOL                            addInfoPresent;
    AdditionalInformation           addInfo;
}
EmmDownlinkGenericNasTransport;

typedef struct EmmUplinkGenericNasTransportTag
{
    GenericMessageContainerType     msgContainerType;
    GenericMessageContainer         genericMsgContainer;
    BOOL                            addInfoPresent;
    AdditionalInformation           addInfo;
}
EmmUplinkGenericNasTransport;

typedef struct EmmControlPlaneServiceRequestTag
{
    ControlPlaneServiceType     cplaneServiceType;
    NasKeySetIdentifier         nasKsi;
    BOOL                        esmMessageContainerPresent;
    EsmMessageContainer         esmMessageContainer;
    BOOL                        nasMessageContainerPresent;
    NasMessageContainer         nasMessageContainer;
    BOOL                        epsBearerContextStatusPresent;
    UINT16                      epsBearerContextStatus;
    BOOL                        devicePropertiesPresent;
    DeviceProperties            deviceProperties;
}
EmmControlPlaneServiceRequest;

typedef struct EmmServiceAcceptTag
{
    BOOL                        epsBearerContextStatusPresent;
    UINT16                      epsBearerContextStatus;
    BOOL                        t3448ValuePresent;
    GprsTimer2                  t3448Value;
}
EmmServiceAccept;

typedef enum EmmMessageTypeTag
{
    ATTACH_REQUEST                 = 0x41,
    ATTACH_ACCEPT                  = 0x42,
    ATTACH_COMPLETE                = 0x43,
    ATTACH_REJECT                  = 0x44,
    DETACH_REQUEST                 = 0x45,
    DETACH_ACCEPT                  = 0x46,
    TA_UPDATE_REQUEST              = 0x48,
    TA_UPDATE_ACCEPT               = 0x49,
    TA_UPDATE_COMPLETE             = 0x4a,
    TA_UPDATE_REJECT               = 0x4b,
    EXTENDED_SERVICE_REQUEST       = 0x4c,
    CONTROL_PLANE_SERVICE_REQUEST  = 0x4D,
    SERVICE_REJECT                 = 0x4e,
    SERVICE_ACCEPT                 = 0x4F,
    GUTI_REALLOC_COMMAND           = 0x50,
    GUTI_REALLOC_COMPLETE          = 0x51,
    AUTHENTICATION_REQUEST         = 0x52,
    AUTHENTICATION_RESPONSE        = 0x53,
    AUTHENTICATION_REJECT          = 0x54,
    AUTHENTICATION_FAILURE         = 0x5c,
    IDENTITY_REQUEST               = 0x55,
    IDENTITY_RESPONSE              = 0x56,
    SECURITY_MODE_COMMAND          = 0x5d,
    SECURITY_MODE_COMPLETE         = 0x5e,
    SECURITY_MODE_REJECT           = 0x5f,
    EMM_STATUS                     = 0x60,
    EMM_INFORMATION                = 0x61,
    DOWNLINK_NAS_TRANSPORT         = 0x62,
    UPLINK_NAS_TRANSPORT           = 0x63,
    DOWNLINK_GENERIC_NAS_TRANSPORT = 0x68,
    UPLINK_GENERIC_NAS_TRANSPORT   = 0x69,
    SERVICE_REQUEST                = 0x70,
    CM_LAYER_MESSAGE               = 0x99,
    MESSAGE_TYPE_RESERVED
}
EmmMessageType;

typedef struct EmmMessageHeaderTag
{
    NasProtocolDiscriminator        pd;
    SecurityHeaderType              secuHeaderType;
    EmmMessageType                  messageType;
}
EmmMessageHeader;

typedef union EmmMessageBodyTag
{
    EmmAttachAccept                 emmAttachAccept;
    EmmAttachComplete               emmAttachComplete;
    EmmAttachRequest                emmAttachRequest;
    EmmAttachReject                 emmAttachReject;
    EmmAuthenticationFailure        emmAuthenticationFailure;
    UINT8                           emmAuthenticationReject;
    EmmAuthenticationRequest        emmAuthenticationRequest;
    EmmAuthenticationResponse       emmAuthenticationResponse;
    UINT8                           emmMoDetachAccept;
    UINT8                           emmMtDetachAccept;
    EmmMoDetachRequest              emmMoDetachRequest;
    EmmMtDetachRequest              emmMtDetachRequest;
    EmmDownlinkNasTransport         emmDownlinkNasTransport;
    EmmInformation                  emmInformation;
    EmmStatus                       emmStatus;
    EmmExtendedServiceRequest       emmExtendedServiceRequest;
    EmmGutiReallocCommand           emmGutiReallocCommand;
    UINT8                           emmGutiReallocComplete;
    EmmIdentityRequest              emmIdentityRequest;
    EmmIdentityResponse             emmIdentityResponse;
    EmmSecurityModeCommand          emmSecurityModeCommand;
    EmmSecurityModeComplete         emmSecurityModeComplete;
    EmmSecurityModeReject           emmSecurityModeReject;
    SecurityProtectedNasMessage     emmSecurityProtectedNasMessage;
    EmmServiceReject                emmServiceReject;
    EmmServiceRequest               emmServiceRequest;
    EmmTrackingAreaUpdateAccept     emmTrackingAreaUpdateAccept;
    UINT8                           emmTrackingAreaUpdateComplete;
    EmmTrackingAreaUpdateReject     emmTrackingAreaUpdateReject;
    EmmTrackingAreaUpdateRequest    emmTrackingAreaUpdateRequest;
    EmmUplinkNasTransport           emmUplinkNasTransport;
    EmmDownlinkGenericNasTransport  emmDownlinkGenericNasTransport;
    EmmUplinkGenericNasTransport    emmUplinkGenericNasTransport;
    EmmControlPlaneServiceRequest   emmControlPlaneServiceRequest;
    EmmServiceAccept                emmServiceAccept;
}
EmmMessageBody;

typedef struct EmmMessageTag
{
    EmmMessageHeader                msgHeader;
    EmmMessageBody                  msgBody;
    DecodeResult                    decodeResult;
}
EmmMessage;


typedef struct TinyForbiddenTaiListTag
{
    Plmn    plmn;
    UINT16  tac;
    UINT8   forbiddenTaiType;                              /* forbidden Tai Type */
}
TinyForbiddenTaiList;

typedef struct TinyForbiddenTaiInfoTag
{
    UINT8                   taiNum;
    TinyForbiddenTaiList    tai[MAX_FORBIDDEN_TAI_NUM_STORED_IN_TINY_CTX];     /* fobidden Tai */
}
TinyForbiddenTaiInfo;

/*******************************************************************************
* Test Control message structure
*******************************************************************************/
typedef enum UeTestLoopModeTag
{
    TEST_LOOP_MODE_A = 0,
    TEST_LOOP_MODE_B = 1,
    TEST_LOOP_MODE_C = 2,
    TEST_LOOP_MODE_D = 3,
    TEST_LOOP_MODE_E = 4,
    TEST_LOOP_MODE_F = 5,
    TEST_LOOP_MODE_G = 6,
    TEST_LOOP_MODE_H = 7,
    TEST_LOOP_MODE_I = 8
}
UeTestLoopMode;

typedef struct LbSetupDrbIeTag
{
    UINT16  ulPdcpSduSize;  /* Uplink PDCP SDU size in bits 0.. 12160 */
    UINT8   drbIdNum;       /* Data Radio Bearer identity nuber,1..32((binary coded value of 'DRB-Identity'-1) */
}
LbSetupDrbIe;

typedef struct UeTestLoopModeALBSetupTag
{
    UINT8           numOfLBEntities;    /* The number of LB entities in the LB setup list */
    LbSetupDrbIe    lbSetupList[2];     /* LB setup list */
}
UeTestLoopModeALBSetup;

typedef UINT8   UeTestLoopModeBLBSetup;

typedef struct OperationModeAndRepetitionsTag
{
    UINT8   ulLoopbackOerationMode;     /* Uplink loopback operation mode */
    UINT8   numOfRepetitions;           /* Number of repetitions of received content of received user data in downlink in uplink. */
}
OperationModeAndRepetitions;

typedef struct UeTestLoopModeGHSetupTag
{
    OperationModeAndRepetitions     operationModeAndRepetitions;    /* Operation mode and repetitions */
    UINT8                           ulDataDelay;                    /* Uplink data delay */
}
UeTestLoopModeGHSetup;

typedef struct CloseUeTestLoopTag
{
    UeTestLoopMode              ueTestLoopMode;
    UeTestLoopModeALBSetup      modeALBSetup;
    UeTestLoopModeBLBSetup      modeBLBSetup;
    UeTestLoopModeGHSetup       modeGHSetup;
}
CloseUeTestLoop;

typedef struct ActivateTestModeTag
{
    UeTestLoopMode      ueTestLoopMode;
}
ActivateTestMode;

typedef enum UePositioningTechnologyTag
{
    UE_POSITIONING_TECHNOLOGY_AGNSS     = 0,
    UE_POSITIONING_TECHNOLOGY_OTDOA     = 1,
    UE_POSITIONING_TECHNOLOGY_MBS       = 2,
    UE_POSITIONING_TECHNOLOGY_WLAN      = 3,
    UE_POSITIONING_TECHNOLOGY_BLUETOOTH = 4,
    UE_POSITIONING_TECHNOLOGY_SENSOR    = 5
}
UePositioningTechnology;

typedef struct ResetUePositioningStoredInformationTag
{
    UePositioningTechnology     uePositioningTechnology;
}
ResetUePositioningStoredInformation;

typedef enum TcMessageTypeTag
{
    CLOSE_UE_TEST_LOOP                      = 0x80,
    CLOSE_UE_TEST_LOOP_COMPLETE             = 0x81,
    OPEN_UE_TEST_LOOP                       = 0x82,
    OPEN_UE_TEST_LOOP_COMPLETE              = 0x83,
    ACTIVATE_TEST_MODE                      = 0x84,
    ACTIVATE_TEST_MODE_COMPLETE             = 0x85,
    DEACTIVATE_TEST_MODE                    = 0x86,
    DEACTIVATE_TEST_MODE_COMPLETE           = 0x87,
    RESET_UE_POSITIONING_STORED_INFORMATION = 0x88
}
TcMessageType;

typedef union TcMessageBodyTag
{
    CloseUeTestLoop                         closeUeTestLoop;
    UINT8                                   closeUeTestLoopComplete;
    UINT8                                   openUeTestLoop;
    UINT8                                   openUeTestLoopComplete;
    ActivateTestMode                        activateTestMode;
    UINT8                                   activateTestModeComplete;
    UINT8                                   deactivateTestMode;
    UINT8                                   deactivateTestModeComplete;
    ResetUePositioningStoredInformation     resetUePositioningStoredInformation;
}
TcMessageBody;

typedef struct TcMessageTag
{
    TcMessageType       msgType;
    TcMessageBody       msgBody;
}
TcMessage;

/*******************************************************************************
* CESMS message structure
*******************************************************************************/
typedef struct CpUserDataElement_Tag
{
    UINT8           rpduInfoLength;
    UINT8           reserved0;
    UINT16          reserved1;
    UINT8           *rpduInformation;
}CpUserDataElement;

typedef enum CemmSmsMsgType_Tag
{
    CP_DATA             = 0x01,
    CP_ACK              = 0x04,
    CP_ERROR            = 0x10
}CemmSmsMsgType;

typedef struct CpDataMessage_Tag
{
    CpUserDataElement               cpUserData;
}
CpDataMessage;

typedef struct CpCauseElement_Tag
{
    UINT8           cause;  //CeNasSmsFailureCause
    UINT8           reserved0;
    UINT16          reserved1;
}
CpCauseElement;

typedef struct CpErrorMessage_Tag
{
    CpCauseElement      cpCause;
}
CpErrorMessage;

typedef struct SmsMessageHeader_Tag
{
    UINT8           pd;  //CemmSmsProtocolDiscriminator
    UINT8           tiValue;
    BOOL            tiFlag;
    UINT8           messageType;     //CemmSmsMsgType

}SmsMessageHeader;

typedef struct SmsMessageBody_Tag
{
    CpDataMessage           cpData;
    CpErrorMessage          cpError;
    GosEmptySignal          cpAck;
}SmsMessageBody;

typedef struct SmcmL3Message_Tag
{
    SmsMessageHeader        msgHeader;
    SmsMessageBody          msgBody;
    DecodeResult            decodeResult;
} SmcmL3Message;


/*******************************************************************************
************* ESM DATA STRUCT *************************************************/
/*******************************************************************************
* Enums
*******************************************************************************/

typedef enum EpsBearerIdTag
{
    EBI_NO_ASSIGNED = 0,
    EBI_5 = 5,
    EBI_6 = 6,
    EBI_7 = 7,
    EBI_8 = 8,
    EBI_9 = 9,
    EBI_10 = 10,
    EBI_11 = 11,
    EBI_12 = 12,
    EBI_13 = 13,
    EBI_14 = 14,
    EBI_15 = 15,
    EBI_UNKNOWN  = 0xFF
}
EpsBearerId ;

typedef enum EsmCauseTag
{
	ESM_NO_CAUSE                                                           =  0x0,
    ESM_OPERATOR_DETERMINED_BARRING                                        =  0x08,
    ESM_INSUFFICIENT_RESOURCES                                             =  0x1a,
    ESM_UNKNOWN_OR_MISSING_APN                                             =  0x1b,
    ESM_UNKNOWN_PDN_TYPE                                                   =  0x1c,
    ESM_USER_AUTHENTICATION_FAILED                                         =  0x1d,
    ESM_REQUEST_REJECTED_BY_SERVING_GW_OR_PDN_GW                           =  0x1e,
    ESM_REQUEST_REJECTED_UNSPECIFIED                                       =  0x1f,
    ESM_SERVICE_OPTION_NOT_SUPPORTED                                       =  0x20,
    ESM_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED                            =  0x21,
    ESM_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER                            =  0x22,
    ESM_PTI_ALREADY_IN_USE                                                 =  0x23,
    ESM_REGULAR_DEACTIVATION                                               =  0x24,
    ESM_EPS_QOS_NOT_ACCEPTED                                               =  0x25,
    ESM_NETWORK_FAILURE                                                    =  0x26,
    ESM_REACTIVATION_REQUESTED                                             =  0x27,
    ESM_SEMANTIC_ERROR_IN_THE_TFT_OPERATION                                =  0x29,
    ESM_SYNTACTICAL_ERROR_IN_THE_TFT_OPERATION                             =  0x2a,
    ESM_INVALID_EPS_BEARER_IDENTITY                                        =  0x2b,
    ESM_SEMANTIC_ERRORS_IN_PACKET_FILTER                                   =  0x2c,
    ESM_SYNTACTICAL_ERRORS_IN_PACKET_FILTER                                =  0x2d,
    ESM_EPS_BEARER_CONTEXT_WITHOUT_TFT_ALREADY_ACTIVATED                   =  0x2e,
    ESM_PTI_MISMATCH                                                       =  0x2f,
    ESM_LAST_PDN_DISCONNECTION_NOT_ALLOWED                                 =  0x31,
    ESM_PDN_TYPE_IPV4_ONLY_ALLOWED                                         =  0x32,
    ESM_PDN_TYPE_IPV6_ONLY_ALLOWED                                         =  0x33,
    ESM_SINGLE_ADDRESS_BEARERS_ONLY_ALLOWED                                =  0x34,
    ESM_ESM_INFORMATION_NOT_RECEIVED                                       =  0x35,
    ESM_PDN_CONNECTION_DOES_NOT_EXIST                                      =  0x36,
    ESM_MULTIPLE_PDN_CONNECTIONS_FOR_A_GIVEN_APN_NOT_ALLOWED               =  0x37,
    ESM_COLLISION_WITH_NETWORK_INITIATED_REQUEST                           =  0x38,
    ESM_PDN_TYPE_IPV4V6_ONLY_ALLOW                                         =  0x39,
    ESM_PDN_TYPE_NON_IP_ONLY_ALLOW                                         =  0x3a,
    ESM_UNSUPPORTED_QCI_VALUE                                              =  0x3b,
    ESM_INVALID_PTI_VALUE                                                  =  0x51,
    ESM_SEMANTICALLY_INCORRECT_MESSAGE                                     =  0x5f,
    ESM_INVALID_MANDATORY_INFORMATION                                      =  0x60,
    ESM_MESSAGE_TYPE_NONEXISTENT_OR_NOT_IMPLEMENTED                        =  0x61,
    ESM_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE                =  0x62,
    ESM_INFORMATION_ELEMENT_NONEXISTENT_OR_NOT_IMPLEMENTED                 =  0x63,
    ESM_CONDITIONAL_IE_ERROR                                               =  0x64,
    ESM_MESSAGE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE                     =  0x65,
    ESM_PROTOCOL_ERROR_OR_UNSPECIFIED                                      =  0x6f,
    ESM_APN_RESTRICTION_VALUE_INCOMPATIBLE_WITH_ACTIVE_EPS_BEARER_CONTEXT  =  0x70,
    ESM_MUTIPLE_ACCESSES_TO_A_PDN_CONNECTION_NOT_ALLOWED                   =  0x71,
    /* ESM internal cause, out of 3GPP defined values */
    ESM_INTERNAL_CAUSE_LOCAL_USED_BASE                                     =  0x0100,
    ESM_TIMER_EXPIRIED_FIVE_TIMES                                          =  0x0101,
    ESM_EPS_SERVICE_NOT_AVAILABLE                                          =  0x0102,
    ESM_UNKNOWN_BEARER_CONTEXT                                             =  0x0103,
    ESM_BEARER_CONTEXT_OPERATION_NOT_ALLOWED                               =  0x0104,
    ESM_APN_CONGESTION_CONTROL_BARRED                                      =  0x0105,
    ESM_ESTABLISH_REQ_TIMEOUT                                              =  0x0106,
    ESM_APN_AND_PDN_TYPE_DUPLICATE_USED                                    =  0x0107,

    ESM_CAUSE_UNKNOWN                                                      =  0xFFFF

}
EsmCause;

/******************************************************************************
 * PCO protocol ID, refer 24.008, 10.5.6.3
 - C021H (LCP);
 - C023H (PAP);
 - C223H (CHAP);
 - 8021H (IPCP).
******************************************************************************/
typedef enum PcoProtocolIDTag
{
    PCO_INVALID_PROTOCOL_ID = 0x0000,
    PCO_LCP_PROTOCOL_ID = 0xC021,
    PCO_PAP_PROTOCOL_ID = 0xC023,
    PCO_CHAP_PROTOCOL_ID = 0xC223,
    PCO_IPCP_PROTOCOL_ID = 0x8021,

    PCO_MAX_PROTOCOL_ID = 0xFFFF,
}
PcoProtocolID;

/******************************************************************************
 * PCO Container ID, refer 24.008, 10.5.6.3
******************************************************************************/
typedef enum PcoContainerIDTag
{
    PCO_INVALID_CONTAINER_ID        = 0x0000,
    PCO_PCSCF_IPV6_ADDRESS          = 0x0001,
    PCO_IM_CN_SUBSYSTEM_SIG_FLAG    = 0x0002,
    PCO_DNS_SERVER_IPV6_ADDRESS     = 0x0003,
    PCO_POLICY_CONTROL_REJ_CODE     = 0x0004,
    PCO_SELECT_BEARER_CTRL_MODE     = 0x0005,
    PCO_DSMIPV6_HOME_AGENT_ADDR     = 0x0007,
    PCO_DSMIPV6_HONE_NW_PREFIX      = 0x0008,
    PCO_DSMIPV6_IPV4_HOME_AGEN_ADDR = 0x0009,
    PCO_PCSCF_IPV4_ADDRESS          = 0x000C,
    PCO_DNS_SERVER_IPV4_ADDRESS     = 0x000D,
    PCO_MSISDN                      = 0x000E,
    PCO_IPV4_LINK_MTU               = 0x0010,
    PCO_NON_IP_LINK_MTU             = 0x0015,
    PCO_APN_RATE_CTRL_PARAM         = 0x0016,
    PCO_PS_DATA_OFF_IND             = 0x0017,
    PCO_RELIABLE_DATA_SERVICE       = 0x0018,
    PCO_ADDITIONAL_APN_RATE_CTRL_PARAM  = 0x0019,
    PCO_RESERVED_ID = 0xFFFF,
}
PcoContainerID;



typedef enum PcoSecurityProtocolTag
{
    PCO_SECURITY_PROTOCOL_NULL = 0,
    PCO_SECURITY_PROTOCOL_PAP = 1,
    PCO_SECURITY_PROTOCOL_CHAP = 2,
    PCO_SECURITY_PROTOCOL_LCP
}
PcoSecurityProtocol;

typedef enum PAPAutheticationTypeTag
{
    PAP_AUTH_REQUEST = 1,
    PAP_AUTH_ACK = 2,
    PAP_AUTH_NAK = 3
}
PAPAutheticationType;

typedef enum ChapCodeTag
{
    CHAP_CHALLENGE_TYPE = 1,
    CHAP_RESPONSE_TYPE = 2,
    CHAP_SUCCESS_TYPE = 3,
    CHAP_FAILURE_TYPE = 4
}
ChapCode;

typedef enum PsPdnAddrTypeTag
{
    PS_PDN_INVALID_ADDR = 0,
    PS_PDN_IPV4,          // 4 bytes length
    PS_PDN_FULL_IPV6,     // 16 bytes length
    PS_PDN_IPV6_INTERFACE // 8 bytes length
}
PsPdnAddrType;

typedef enum DnsToBeReadTypeTag
{
    IPV4_DNS_TO_BE_READ = 0,
    IPV6_DNS_TO_BE_READ
}
DnsToBeReadType;



typedef enum EsmMessageTypeTag
{
    ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REQUEST     = 0xC1,
    ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_ACCEPT      = 0xC2,
    ACTIVATE_DEFAULT_EPS_BEARER_CONTEXT_REJECT      = 0xC3,
    ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_REQUEST   = 0xC5,
    ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_ACCEPT    = 0xC6,
    ACTIVATE_DEDICATED_EPS_BEARER_CONTEXT_REJECT    = 0xC7,
    MODIFY_EPS_BEARER_CONTEXT_REQUEST               = 0xC9,
    MODIFY_EPS_BEARER_CONTEXT_ACCEPT                = 0xCA,
    MODIFY_EPS_BEARER_CONTEXT_REJECT                = 0xCB,
    DEACTIVATE_EPS_BEARER_CONTEXT_REQUEST           = 0xCD,
    DEACTIVATE_EPS_BEARER_CONTEXT_ACCEPT            = 0xCE,
    PDN_CONNECTIVITY_REQUEST                        = 0xD0,
    PDN_CONNECTIVITY_REJECT                         = 0xD1,
    PDN_DISCONNECT_REQUEST                          = 0xD2,
    PDN_DISCONNECT_REJECT                           = 0xD3,
    BEARER_RESOURCE_ALLOCATION_REQUEST              = 0xD4,
    BEARER_RESOURCE_ALLOCATION_REJECT               = 0xD5,
    BEARER_RESOURCE_MODIFICATION_REQUEST            = 0xD6,
    BEARER_RESOURCE_MODIFICATION_REJECT             = 0xD7,
    ESM_INFORMATION_REQUEST                         = 0xD9,
    ESM_INFORMATION_RESPONSE                        = 0xDA,
    ESM_NOTIFICATION                                = 0xDB,
    ESM_DUMMY_MESSAGE                               = 0xDC,
    ESM_STATUS                                      = 0xE8,
    REMOTE_UE_REPORT                                = 0xE9,
    REMOTE_UE_REPORT_RESPONSE                       = 0xEA,
    ESM_DATA_TRANSPORT                              = 0xEB,
    MESSAGE_TYPE_UNDEFINDED
}
EsmMessageType;


/*******************************************************************************
* Structs
*******************************************************************************/
typedef struct UlPcoInfoTag
{
    ConfigurationProtocol    protocol;
    UINT16                   length;
    UINT8                    data[MAX_PCO_SIZE];
}
UlPcoInfo;



typedef struct ULPcoPAPAuthTag
{
    UINT8                    authProtocol;    /*PcoSecurityProtocol */
    UINT8                    userIdLength;
    UINT8                    userId[MAX_AUTH_STR_LEN_SIZE];
    UINT8                    pwdLength;
    UINT8                    password[MAX_AUTH_STR_LEN_SIZE];
}ULPcoPAPAuth;



typedef struct EpsQualityOfServiceTag
{
    UINT8            qci;                   /*Quality of Service Class Identifier*/
    BOOL             mbrGbrPresent;         /* indicate MBR/GBR present */
    UINT32           maxBitRateOfUplink;
    UINT32           maxBitRateOfDownlink;
    UINT32           guaranteedBitRateOfUplink;
    UINT32           guaranteedBitRateOfDownlink;
}
EpsQualityOfService;

typedef struct PcoPAPEntityTag
{
    PAPAutheticationType     authenticationType;
    UINT8                    papID;
    UINT16                   contentLength;
    UINT8                    userNameLength;
    UINT8                    userName[32];
    UINT8                    pwdLength;
    UINT8                    password[16];
    UINT8                    messageLength;
    UINT8                    message[255];
}
PcoPAPEntity;

typedef struct PcoCHAPEntityTag
{
    UINT16                contentLength;
    ChapCode              chapCode;
    UINT8                 chapID;
    UINT16                msglength;
    UINT8                 msg[MAX_CHAP_MSG_LENGTH];
}
PcoCHAPEntity;

typedef struct PsPdnIpV4AddrTag
{
    UINT8            addrData[4];
}
PsPdnIpV4Addr;


typedef struct PsPdnIpAddrTag
{
    PsPdnAddrType    addrType;
    UINT16           subnetLength;
    UINT8            addrData[16];
}
PsPdnIpAddr;

typedef struct PsPcoIpcpEntityTag
{
    UINT8              code;
    UINT8              identifier;
    UINT16             ipcpLength;
    PsPdnIpAddr        primDnsAddr;
    PsPdnIpAddr        primNbnsAddr;
    PsPdnIpAddr        secDnsAddr;
    PsPdnIpAddr        secNbnsAddr;
    PsPdnIpAddr        Ipv4Addr;
    PsPdnIpAddr        mobileIpv4Addr;
}
PsPcoIpcpEntity;




typedef struct APNRateControl_Tag
{
   UINT32  present     : 1; //whether APN RATE CTRL configured
   UINT32  reserved    : 3;
   UINT32  aer         : 1; //Additional exception reports
   UINT32  timeUnit    : 3;   //CeDrApnRateCtrlUlTimeUnit
   UINT32  maxUlRate   : 24;
}APNRateControl;

typedef struct AdditionalAPNRateControl_Tag
{
   UINT32  present     : 1; //whether APN RATE CTRL configured
   UINT32  reserved0   : 4;
   UINT32  timeUnit    : 3;   //CeDrApnRateCtrlUlTimeUnit
   UINT32  reserved1   : 8;
   UINT32  maxUlRate   : 16;
}AdditionalAPNRateControl;



typedef struct DlPcoInfoTag
{
    ConfigurationProtocol   protocol;
    PcoProtocolID           pcoProtocolID;
    UINT8                    protocolLength;

    PsPcoIpcpEntity         dlIpcpEntity;

    //PcoSecurityProtocol    securityProtocol;
    //PcoPAPEntity           *pcoPapEntity;
    //PcoCHAPEntity          *pcoChapEntity;

    UINT8                   pCscfNum;
    UINT8                   dnsNum;
    PsPdnIpAddr            pCscfAddr[PDN_MAX_NW_ADDR_NUM]; // 0001H (P-CSCF IPv6 Address); 000CH (P-CSCF IPv4 Address);
    PsPdnIpAddr            dnsAddr[PDN_MAX_NW_ADDR_NUM]; // 0003H (DNS Server IPv6 Address); 000DH (DNS Server IPv4 Address);

    BOOL                imCnSubsystemFlag; // 0002H (IM CN Subsystem Signaling Flag);

    BOOL                pcRejectPresent; // 0004H (Policy Control rejection code); whether reject code exit
    UINT8                   pcRejestCode;

    BOOL                bearCtlModePresent; // 0005H (Selected Bearer Control Mode;)
    UINT8                   bearCtlMode;

    PsPdnIpAddr            dsmIpv6HAAddr;      // 0007H (DSMIPv6 Home Agent Address) ;

    PsPdnIpAddr            dsmIpv6Ipv4HAAddr; // 0009H (DSMIPv6 IPv4 Home Agent Address);

    BOOL                iformSupported;    // 000FH (IFOM-Support);

    BOOL                ipv4MtuPresent;    // 0010H (IPv4 Link MTU);
    UINT16              ipv4MtuSize;

    BOOL                nwLocalAddInTftInd; // 0011H (Network support of Local address in TFT indicator);

    BOOL                nonIpMtuPresent;    // 0015H (Non IP Link MTU);
    UINT16              nonIpMtuSize;

    APNRateControl     APNRC;  //0016H

    BOOL                psDataOffInd;          //0x17H

    BOOL                rdsPresent;    //0x18H
    UINT16              rds;

    AdditionalAPNRateControl     AdditionalAPNRC;  //0019H


    //UINT16         pcoLength;
    //UINT8          pcoData[256];

}DlPcoInfo;


typedef struct PdnAddressTag
{
    /*
     * 1> IPv4, the length is set to 4;
     * 2> IPv6, the length is set to 8, 8 bytes IPv6 interface identifier;
     * 3> IPv4v6, the length is set to 12:
     *    0 - 7: IPv6 interface identifier;
     *    8 - 11: IPv4 address
    */
    UINT8            length;
    UINT8            address[MAX_PDP_ADDR];
}PdnAddress;

typedef struct APNAMaxBitRateTag
{
    UINT32      APNAMBRDownlink;
    UINT32      APNAMBRUPlink;
}
APNAMaxBitRate;

typedef struct NotificationIndicatorTag
{
    UINT8            length;
    UINT8            value;
}
NotificationIndicator;

typedef struct UserDataContainerTag
{
    UINT16           length;
    UINT8            *userData; /* Deliver raw data pointer to CEDR module */
}
UserDataContainer;

/*=================================TFT  INFO BEGIN ==========================*/
#define MAX_PARA_DATA_LENGTH  16
#define MAX_PARA_LIST_LENGTH  16
#define MAX_PFS_IN_TFT        16
#define REMOTE_IPADDR_SUBNET_MASK_LEN    32
#define MAX_PORT_RANGE        12
#define PORT_RANGE_LEN        4
#define MAX_TOS_TRFCCLASS     8
#define TOS_TRFCCLASS_LEN     2


#define MAX_TFT 254

#define IPSEC_LEN   4
#define TOS_TRFCCLSS_LEN  2
#define FLOW_LABEL_LEN  3

#define IPV4_SRCADDR_LEN    8
#define IPV6_SRCADDR_LEN    32
#define REMOTE_IPADDR_SUBNET_MASK_LEN 32
#define IPV6_REMOTE_ADDR_PREFIX_LEN   17

#define PF_COMP_TYPE_ID_IPV4_REMOTE_ADDR     0x10
#define PF_COMP_TYPE_ID_IPV6_REMOTE_ADDR     0x20
#define PF_COMP_TYPE_ID_IPV6_REMOTE_ADDR_PREFIX_LENGTH    0x21
#define PF_COMP_TYPE_ID_PROTID_NXT_HDR    0x30
#define PF_COMP_TYPE_ID_SNGL_LOCAL_PORT    0x40
#define PF_COMP_TYPE_ID_LOCAL_PORT_RNGE    0x41
#define PF_COMP_TYPE_ID_SNGL_REMOTE_PORT     0x50
#define PF_COMP_TYPE_ID_REMOTE_PORT_RNGE     0x51
#define PF_COMP_TYPE_ID_SEC_PAR_IND       0x60
#define PF_COMP_TYPE_ID_TOS_TRFC_CLS      0x70
#define PF_COMP_TYPE_ID_FLOW_LBL          0x80


typedef enum TftOperationCodeTag
{
    TFT_OPCODE_SPARE                  =0,
    TFT_OPCODE_CREATE_NEW             =1,
    TFT_OPCODE_DEL_EXISTING           =2,
    TFT_OPCODE_ADD_PACKET_FILTERS     =3,
    TFT_OPCODE_REPLACE_PACKET_FILTERS =4,
    TFT_OPCODE_DEL_PACKET_FILTERS     =5,
    TFT_OPCODE_NO_TFT_OPERATION       =6,
}
TftOperationCode;

#if 0
typedef enum TftParaListIdTag
{
    TFT_PARA_AUTHOR_TOKEN    =1,
    TFT_PARA_FLOW_ID         =2,
    TFT_PARA_PARA_FILTER_ID  =3,
}TftParaListId;

typedef struct  ParameterListTag
{
    TftParaListId    paraId;
    UINT8            len;
    UINT8            paraData[MAX_PARA_DATA_LENGTH];
}
ParameterList;

typedef enum RemoteAddrTypeInTftTag
{
    INVALID_REMOTE_ADDR_TYPE    =0,
    IPV4_REMOTE_ADDR_TYPE       =1,
    IPV6_REMOTE_ADDR_TYPE       =2,
    IPV6_REMOTE_ADDR_PREFIX_TYPE=3,
    REMOTE_ADDR_TYPE_NUM
}RemoteAddrTypeInTft;

typedef struct RemoteAddrSubnetMaskTag
{
    RemoteAddrTypeInTft type;
    UINT8               val[REMOTE_IPADDR_SUBNET_MASK_LEN];

}RemoteAddrSubNetMask;

typedef struct ProtocolNumNextHdrTag
{
    BOOL     present;
    UINT8    val;
}ProtocolNumNextHdr;

typedef enum PortTypeInTftTag
{
    INVALID_PORT_TYPE    =0,
    SINGLE_PORT_TYPE,
    RANGE_PORT_TYPE,
    PORT_TYPE_NUM
}PortTypeInTft;

typedef struct PortRangeTag
{
    BOOL    present;
    PortTypeInTft    portType;
    UINT8            val[MAX_PORT_RANGE];
}PortRange;

typedef struct IpSecSpiTag
{
    BOOL    present;
    UINT32  val;
}IpSecSpi;

typedef struct TosTrfcClassTag
{
    BOOL     present;
    UINT8    len;
    UINT8    val[MAX_TOS_TRFCCLASS];
}TosTrfcClass;

typedef struct FlowLabelTag
{
    BOOL     present;
    UINT32   val;

}FlowLabel;

typedef struct packetFilterTag
{
    UINT8                   packetFilterId;
    UINT8                   evalPrecedenceIndex;
    UINT8                   direction;
    RemoteAddrSubNetMask    remoteAddrSubnetMask;   //36 bytes
    ProtocolNumNextHdr      protocolNumNextHdr;     //4 bytes
    PortRange               destPortRange;          //16 bytes
    PortRange               srcPortRange;           //16 bytes
    IpSecSpi                ipSecSpi;               //8 bytes
    TosTrfcClass            tosTrfcClass;           //12 bytes
    FlowLabel               flowLabel;              //8 bytes
    //UINT8                   epsBearerId;          //seems useless
}PacketFilter;  // 104 bytes, and not contain local address info



#endif

#if 1

typedef enum RemoteAddrTypeInTftTag
{
    INVALID_REMOTE_ADDR_TYPE    =0,
    IPV4_REMOTE_ADDR_TYPE       =1,
    IPV6_REMOTE_ADDR_TYPE       =2,
    IPV6_REMOTE_ADDR_PREFIX_TYPE=3,
    REMOTE_ADDR_TYPE_NUM
}RemoteAddrTypeInTft;

typedef enum PortTypeInTftTag
{
    INVALID_PORT_TYPE    =0,
    SINGLE_PORT_TYPE,
    RANGE_PORT_TYPE,
    PORT_TYPE_NUM
}PortTypeInTft;

/*
 * 0 0 0 1 0 0 0 0: IPv4 remote address type
 * 0 0 1 0 0 0 0 0: IPv6 remote address type
 * 0 0 1 0 0 0 0 1: IPv6 remote address/prefix length type
 * 0 0 0 1 0 0 0 1: IPv4 local address type
 * 0 0 1 0 0 0 1 1: IPv6 local address/prefix length type
*/
typedef union PacketFilterAddrInfo_Tag
{
    struct {
        UINT8   addr[4];
        UINT8   mask[4];
    } ipv4;
    struct {
        UINT8   addr[16];
        UINT8   mask[16];
    } ipv6;
    struct {
        UINT8   addr[16];
        UINT8   prefixLen;
    } ipv6Prefix;
}PacketFilterAddrInfo;  //32 bytes

/*
 * 0 1 0 0 0 0 0 0: Single local port type
 * 0 1 0 0 0 0 0 1: Local port range type
 * 0 1 0 1 0 0 0 0: Single remote port type
 * 0 1 0 1 0 0 0 1: Remote port range type
 * If Single port, min == max
*/
typedef struct PacketFilterPortInfo_Tag
{
    UINT16  min;
    UINT16  max;
}PacketFilterPortInfo;


typedef struct PacketFilterListTag
{
    UINT32      pfId        : 4;    //0 - 15
    UINT32      pfDir       : 2;
    UINT32      reserved0   : 2;
    UINT32      pfEpId      : 8;    //Packet filter evaluation precedence, 0 - 255

    UINT32      remoteAddrType  : 2; //RemoteAddrTypeInTft
    UINT32      localAddrType   : 2;
    UINT32      tosTcPresent    : 1;
    UINT32      protIdPresent   : 1;
    UINT32      ipSecSpiPresent : 1;
    UINT32      ipv6FLPresent   : 1;

    UINT32      localPortPresent    : 1;
    UINT32      LocalPortRangeType  : 2; //PortTypeInTft
    UINT32      remotePortPresent   : 1;
    UINT32      remotePortRangeType : 2; //PortTypeInTft
    UINT32      cid                 : 4;

    /*
     * 0 1 1 1 0 0 0 0: Type of service/Traffic class type
    */
    UINT8       tosTc;        //Type-of-Service/Traffic Class
    UINT8       tosTcMask;    //Type-of-Service/Traffic Class mask

    /*
     * 0 0 1 1 0 0 0 0: Protocol identifier/Next header type
    */
    UINT8       protId;

    UINT8       reserved2;

    /*
     * 0 0 0 1 0 0 0 0: IPv4 remote address type
     * 0 0 1 0 0 0 0 0: IPv6 remote address type
     * 0 0 1 0 0 0 0 1: IPv6 remote address/prefix length type
     * Can't coexist, only one shall be present in one packet filter
    */
    PacketFilterAddrInfo    remoteAddr;

    /*
     * 0 0 0 1 0 0 0 1: IPv4 local address type
     * 0 0 1 0 0 0 1 1: IPv6 local address/prefix length type
    */
    PacketFilterAddrInfo    localAddr;

    /*
     * 0 1 0 0 0 0 0 0: Single local port type
     * 0 1 0 0 0 0 0 1: Local port range type
    */
    PacketFilterPortInfo    localPort;

    /*
     * 0 1 0 1 0 0 0 0: Single remote port type
     * 0 1 0 1 0 0 0 1: Remote port range type
    */
    PacketFilterPortInfo    remotePort;

    /*
     * 0 1 1 0 0 0 0 0: Security parameter index type
    */
    UINT32      ipSecSpi;

    /*
     * 1 0 0 0 0 0 0 0: Flow label type
    */
    UINT32      ipv6FL;

    /*
     * next PF
    */
    struct PacketFilterListTag  *pNext;
}PacketFilterList;  // 92 bytes


typedef struct TrafficFlowTemplate_Tag
{
    UINT8       tftOpCode             : 3;  //TftOperationCode
    UINT8       eBit                  : 1;
    UINT8       PacketFilterNum       : 4;

    UINT8       reserved0;
    UINT16      reserved1;

    /*
     * if "tftOpCode" == "delete packet filters from existing TFT";
     * +---+---+---+---+---+---+---+---+
     * |   pfId0       |     pfId1     |
     * +---+---+---+---+---+---+---+---+
    */
    UINT8       delPfIdList[8];

    /*
     * if "tftOpCode" == "create new TFT"/"add packet filters to existing TFT"/"replace packet filters in existing TFT"
    */
    PacketFilterList    *pPFHdr;


    // PacketFilter        PacketFilterData[MAX_PFS_IN_TFT];   //104*16 = 1664 bytes
    /*
     * "Parameters list" is not support NOW, if recevied in DL, just print a WARNING, and ingore it
    UINT8               ParaNum;
    ParameterList       Paralist[MAX_PARA_LIST_LENGTH];
    */
}TrafficFlowTemplate;   //16 bytes

#endif



typedef struct RohcInfoTag
{
    UINT16  maxCID;
    UINT8   profiles;  //bit indicate whether enable of PDCP_Config_NB_r13_profiles_r13
    UINT8   reserved0;
}RohcInfo;

/*============================TFT info END===========================*/


typedef struct EsmBearerTinyCtxTag
{
    UINT32                  cid: 8;
    UINT32                  pCid: 8;
    UINT32                  ebi: 4;
    UINT32                  pdnType:3;
    UINT32                  cponly:1;            /*ctrl plane only ind*/
    UINT32                  contextState:3;
    UINT32                  needRetryAnotherIPType:1;

    UINT32                  dnsNum : 3;     //MAX number: PDN_MAX_NW_ADDR_NUM, 4
    UINT32                  ipv4MtuPresent : 1; // 0010H (IPv4 Link MTU);   - in fact not ipv4MTU only, also need nonIpMTU -TBD

    PdnAddress              pdnAddr;
    AccessPointName         apn;

    UINT16                  ipv4MtuSize;
    UINT16                  splmnRateCtrl;     /*Serving PLMN rate control 2 octets*/

    PsPdnIpAddr             dnsAddr[PDN_MAX_NW_ADDR_NUM];   //20*4 = 80 bytes
    PsPdnIpAddr             gwIpv4Addr;

    APNRateControl              APNRC;
    AdditionalAPNRateControl    additionalAPNRC;
    UINT32                  NSLPIPresent:1;
    UINT32                  NSLPI:1;
}EsmBearerTinyCtx;



/**********      ESM message    ***************/
typedef struct ActivateDedEpsBearerCtxAcceptTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
ActivateDedEpsBearerCtxAccept;

typedef struct ActivateDedEpsBearerCtxRejectTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
ActivateDedEpsBearerCtxReject;

typedef struct ActivateDedEpsBearerCtxRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EpsBearerId              linkedEbi;
    EpsQualityOfService      epsQos;
    TrafficFlowTemplate      tft;
    BOOL                     pPcoPresent;
    DlPcoInfo                pPcoInfo;
}
ActivateDedEpsBearerCtxRequest;

typedef struct ActivateDefEpsBearerCtxAcceptTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
ActivateDefEpsBearerCtxAccept;

typedef struct ActivateDefEpsBearerCtxRejectTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
ActivateDefEpsBearerCtxReject;

typedef struct ActivateDefEpsBearerCtxRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EpsQualityOfService      epsQos;
    AccessPointName          apn;
    PdnType                  pdnType;
    PdnAddress               pdnAddr;
    BOOL                     apnambrPresent;
    APNAMaxBitRate           apnambr;           /* APN aggregate maximum bit rate */
    BOOL                     esmcausePresent;
    EsmCause                 esmcause;
    DlPcoInfo                pcoInfo;
    BOOL                     cponly;            /*ctrl plane only ind*/
    UINT16                   splmnRateCtrl;     /*Serving PLMN rate control 2 octets*/
    BOOL                     rohcPresent;
    RohcInfo                 rohc;
}
ActivateDefEpsBearerCtxRequest;

typedef struct BearerResourceAllocationRejectTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    DlPcoInfo                pPcoInfo;
    BOOL                     T3396TimerPresent;
    GprsTimer3               T3396timer;
}
BearerResourceAllocationReject;

typedef struct BearerResourceAllocationRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EpsBearerId              linkedebi;
    BOOL                     tftPresent;
    TrafficFlowTemplate      tft;
    BOOL                     qosPresent;
    EpsQualityOfService      reqQos;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
    BOOL                     devicePropertyPresent;
    DeviceProperties         deviceProperty;
}
BearerResourceAllocationRequest;

typedef struct BearerResourceModificationRejectTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    DlPcoInfo                pPcoInfo;
    BOOL                     T3396TimerPresent;
    GprsTimer3               T3396timer;
}
BearerResourceModificationReject;

typedef struct BearerResourceModificationRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EpsBearerId              linkedebi;
    BOOL                     tftPresent;
    TrafficFlowTemplate      tft;
    BOOL                     qosPresent;
    EpsQualityOfService      qos;
    BOOL                     esmcausePresent;
    EsmCause                 esmcause;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
    BOOL                     devicePropertyPresent;
    DeviceProperties         deviceProperty;
    BOOL                     rohcPresent;
    RohcInfo                 rohc;
}
BearerResourceModificationRequest;

typedef struct DeactivateEPSBearerCtxAcceptTag
{
    EpsBearerId               ebi;
    UINT8                     pti;
    BOOL                      epcoFlag;
    UlPcoInfo                 pPcoInfo;
}
DeactivateEPSBearerCtxAccept;

typedef struct DeactivateEPSBearerCtxRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    DlPcoInfo                pPcoInfo;
    BOOL                     T3396TimerPresent;
    GprsTimer3               T3396timer;
}
DeactivateEPSBearerCtxRequest;

typedef struct ESMDummyMessageTag
{
    EpsBearerId               ebi;
    UINT8                     pti;
}
ESMDummyMessage;

typedef struct BearerResourceRequestTag
{
	BOOL isesmcause97;
	Plmn plmn;
}BearerResourceRequest;

typedef struct ESMInformationRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
}
ESMInformationRequest;

typedef struct ESMInformationResponseTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    BOOL                     apnPresent;
    AccessPointName          apn;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
ESMInformationResponse;

typedef struct ESMStatusTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
}
ESMStatus;


typedef struct ESMNotificationTag
{
    EpsBearerId                       ebi;
    UINT8                             pti;
    NotificationIndicator             indicator ;
}
ESMNotification;

typedef struct ModifyEPSBearerCtxAcceptTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
ModifyEPSBearerCtxAccept;

typedef struct ModifyEPSBearerCtxRejectTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
ModifyEPSBearerCtxReject;

typedef struct ModifyEPSBearerCtxRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    BOOL                     newEpsQosPresent;
    EpsQualityOfService      newEpsQos;
    BOOL                     tftPresent;
    TrafficFlowTemplate      tft;
    BOOL                     apnambrPresent;
    APNAMaxBitRate           apnambr;           /* APN aggregate maximum bit rate */
    BOOL                     pPcoPresent;
    DlPcoInfo                pPcoInfo;
    BOOL                     rohcPresent;
    RohcInfo                 rohc;
}
ModifyEPSBearerCtxRequest;

typedef struct PDNConnectivityRejectTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    DlPcoInfo                pPcoInfo;
    BOOL                     T3396TimerPresent;
    GprsTimer3               T3396timer;
}
PDNConnectivityReject;

typedef struct PDNConnectivityRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    PdnType                  pdnType;
    UINT8                    reqtype;
    BOOL                     eitfPresent;
    UINT8                    eitf;          /* ESM information transfer flag */
    BOOL                     apnPresent;
    AccessPointName          apn;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
    BOOL                     devicePropertyPresent;
    DeviceProperties         deviceProperty;
    BOOL                     rohc_present;
    RohcInfo                 rohc;
}
PDNConnectivityRequest;

typedef struct PDNDisconnectRejectTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EsmCause                 esmcause;
    DlPcoInfo                pPcoInfo;
}
PDNDisconnectReject;

typedef struct PDNDisconnectRequestTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    EpsBearerId              linkedebi;
    BOOL                     epcoFlag;
    UlPcoInfo                pPcoInfo;
}
PDNDisconnectRequest;

typedef struct ESMDataTransportTag
{
    EpsBearerId              ebi;
    UINT8                    pti;
    UserDataContainer        userDataContainer;
    BOOL                     relAssIndPresent;
    DataRelAssistIndEnum     relAssistanceInd;
}
ESMDataTransport;


typedef struct ESMDataTransportHeaderTag
{
    EpsBearerId             ebi;
    UINT8                   pti;
    UINT16                  userDataLength;
}
ESMDataTransportHeader;


typedef struct EsmMessageTag
{
    UINT8                       messageType; /* EsmMessageType */
    void                        *messageBody;
}
EsmMessage;


/*******************************************************************************
* Supplementary Services message structure
*******************************************************************************/
typedef enum SsMessageTypeTag
{
    MSG_RELEASE_COMPLETE = 0x2A,
    MSG_FACILITY         = 0x3A,
    MSG_REGISTER         = 0x3B
}
SsMessageType;

#define MAX_FACILITY_DATA_LENGTH 255 //TBD

typedef struct FacilityIeTag
{
    INT16      dataLength;
    UINT8      data[MAX_FACILITY_DATA_LENGTH];
}
FacilityIe;

typedef enum LocationTag
{
    USER = 0,
    PRIVATE_NETWORK_SERVING_THE_LOCAL_USER  = 1,
    PUBLIC_NETWORK_SERVING_THE_LOCAL_USER   = 2,
    TRANSIT_NETWORK                         = 3,
    PUBLIC_NETWORK_SERVING_THE_REMOTE_USER  = 4,
    PRIVATE_NETWORK_SERVING_THE_REMOTE_USER = 5,
    INTERNATIONAL_NETWORK                   = 7,
    NETWORK_BEYONGD_INTERWORKING_POINT      = 10
}
Location;

typedef enum CodingStandardTag
{
    CODING_AS_SPECIFIED_IN_Q931               = 0,
    RESERVED_FOR_OTHER_INTERNATIONAL_STANDARS = 1,
    NATIONAL_STANDARD                         = 2,
    STANDARD_FOR_GSM_PLMN                     = 3
}
CodingStandard;

typedef enum CauseValueTag
{
    UNASSIGNED_NUMBER                                                  = 1,
    NO_ROUTE_TO_DESTINATION                                            = 3,
    CHANNEL_UNACCEPTABLE                                               = 6,
    OPERATOR_DETERMINED_BARRING                                        = 8,
    CALL_COMPLETED_ELSEWHERE                                           = 13,
    NORMAL_CALL_CLEARING                                               = 16,
    USER_BUSY                                                          = 17,
    NO_USER_RESPONDING                                                 = 18,
    USER_ALERTING_NO_ANSWER                                            = 19,
    CALL_REJECTED                                                      = 21,
    NUMBER_CHANGED                                                     = 22,
    CALL_REJECTED_DUE_TO_FEATURE_AT_THE_DESTINATION                    = 24,
    PRE_EMPTION                                                        = 25,
    NON_SELECTED_USER_CLEARING                                         = 26,
    DESTINATION_OUT_OF_ORDER                                           = 27,
    INVALID_NUMBER_FORMAT                                              = 28,
    FACILITY_REJECTED                                                  = 29,
    RESPONSE_TO_STATUS_ENQUIRY                                         = 30,
    NORMAL_UNSPECIFIED                                                 = 31,
    NO_CIRCUIT_AVAILABLE                                               = 34,
    NETWORK_OUT_OF_ORDER                                               = 38,
    TEMPORARY_FAILURE                                                  = 41,
    SWITCHING_EQUIPMENT_CONGESTION                                     = 42,
    ACCESS_INFORMATION_DISCARDED                                       = 43,
    REQUESTED_CIRCUIT_NOT_AVAILABLE                                    = 44,
    RESOURCES_UNAVAILABLE_UNSPECIFIED                                  = 47,
    QUALITY_OF_SERVICE_UNAVAILABLE                                     = 49,
    REQUESTED_FACILITY_NOT_SUBSCRIBED                                  = 50,
    INCOMING_CALLS_BARRED_WITHIN_THE_CUG                               = 55,
    BEARER_CAPABILITY_NOT_AUTHORIZED                                   = 57,
    BEARER_CAPABILITY_NOT_PRESENTLY_AVAILABLE                          = 58,
    SERVICE_OR_OPTION_NOT_AVAILABLE_UNSPECIFIED                        = 63,
    BEARER_SERVICE_NOT_IMPLEMENTED                                     = 65,
    ACM_EQUAL_TO_OR_GREATER_THAN_ACM_MAX                               = 68,
    REQUESTED_FACILITY_NOT_IMPLEMENTED                                 = 69,
    ONLY_RESTRICTED_DIGITAL_INFORMATION_BEARER_CAPABILITY_IS_AVAILABLE = 70,
    SERVICE_OR_OPTION_NOT_IMPLEMENTED_UNSPECIFIED                      = 79,
    INVALID_TRANSACTION_IDENTIFIER_VALUE                               = 81,
    USER_NOT_MEMBER_OF_CUG                                             = 87,
    INCOMPATIBLE_DESTINATION                                           = 88,
    INVALID_TRANSIT_NETWORK_SELECTION                                  = 91,
    SEMANTICALLY_INCORRECT_MESSAGE                                     = 95,
    INVALID_MANDATORY_INFORMATION                                      = 96,
    MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED                       = 97,
    MESSAGE_TYPED_NOT_COMPATIBLE_WITH_PROTOCOL_STATE                   = 98,
    INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED                = 99,
    CONDITIONAL_IE_ERROR                                               = 100,
    MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE                         = 101,
    RECOVERY_ON_TIMER_EXPIRY                                           = 102,
    PROTOCOL_ERROR_UNSPECIFIED                                         = 111,
    INTERWORKING_UNSPECIFIED                                           = 127,
    CAUSE_VALUE_NO_CAUSE                                               = 0XFFFF
}
CauseValue;

typedef struct DiagnosticTag
{
    UINT8   length;
    UINT8   data[MAX_DIAGNOSTIC_IE_SIZE];
}
Diagnostic;

typedef struct CauseTag
{
    Location            location;
    CodingStandard      codingStandard;
    UINT8               recommendation;
    CauseValue          causeValue;
    Diagnostic          diagnostic;
}
Cause;

typedef struct SsRegisterTag
{
    BOOL        facilityPresent;
    FacilityIe  facility;
    BOOL        ssVersionPresent;
    INT8        ssVersion;
}
SsRegister;

typedef struct SsFacilityTag
{
    FacilityIe  facility;
}
SsFacility;

typedef struct SsReleaseCompleteTag
{
    BOOL        causePresent;
    Cause       cause;
    BOOL        facilityPresent;
    FacilityIe  facility;
}
SsReleaseComplete;

typedef union SsMessageBodyTag
{
    SsRegister              ssRegister;
    SsFacility              ssFacility;
    SsReleaseComplete       ssReleaseComplete;
}
SsMessageBody;

typedef struct SsMessageTag
{
    UINT8               tiValue;
    SsMessageType       msgType;
    SsMessageBody       msgBody;
    DecodeResult        decodeError;
}
SsMessage;



#endif
