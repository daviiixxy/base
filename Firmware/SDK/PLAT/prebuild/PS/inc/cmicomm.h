#ifndef __CMI_COMM_H__
#define __CMI_COMM_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm Ltd.
File name:      - cmicomm.h
Description:    - CMI (CIoT modem interface) common interface defination
History:        - 08/09/2017, Originated by jcweng
******************************************************************************/
#ifdef WIN32
#include "pssys.h"
#else
#include "osasys.h"
#endif


#define PS_BROADCAST_IND_HANDLER       0x0001

#if 0
/*
 * used in CAC, this reserved for CAC SYNC API
 * Same defination in: cms_def.h: CAC_CMI_SYNC_REQ_START_HANDLER
*/
#define CMI_SYNC_REQ_NUM                16
#define CMI_SYNC_REQ_START_HANDLER      0x0030
#define CMI_SYNC_REQ_END_HANDLER        (CMI_SYNC_REQ_START_HANDLER + CMI_SYNC_REQ_NUM - 1)
#endif

/******************************************************************************
 ******************************************************************************
 * STRUCT definition
 ******************************************************************************
******************************************************************************/

/******************************************************************************
 * MT error result code
 * refer: 27.007 9.2
******************************************************************************/
typedef enum MtErrorResultCode_TAG
{
    CME_SUCC = 0,
    /*
     * 0 - 100 are reserved for general errors
    */
    //CME_PHONE_FAILURE = 0, error 0 should not support for easy process
    CME_MT_NO_CONNECTION = 1,
    CME_MT_LINK_RESERVED,
    CME_OPERATION_NOT_ALLOW,
    CME_OPERATION_NOT_SUPPORT,
    CME_PH_SIM_PIN_REQ,
    CME_PH_FSIM_PIN_REQ,
    CME_PH_FSIM_PUK_REQ,

    CME_SIM_NOT_INSERT = 10,
    CME_SIM_PIN_REQ,
    CME_SIM_PUK_REQ,
    CME_SIM_FAILURE,
    CME_SIM_BUSY,
    CME_SIM_WRONG,
    CME_INCORRECT_PASSWORD,
    CME_SIM_PIN2_REQ,
    CME_SIM_PUK2_REQ,
    CME_MEMORY_FULL = 20,   /*accroding to 27.007 9.2.1*/
    CME_INVALID_INDEX,
    CME_NOT_FOUND,
    CME_MEMORY_FAILURE,
    CME_TEXT_STR_TOO_LONG,
    CME_INVALID_CHAR_IN_TXT_STR,
    CME_DIAL_STR_TOO_LONG,
    CME_INVALID_CHAR_IN_DIAL_STR = 27,
    CME_NO_NW_SERVICE = 30,
    CME_NW_TIMEOUT,
    CME_NW_NOT_ALLOWED_EC_ONLY,     /*network not allowed - emergency calls only*/
    CME_NW_PERSONAL_PIN_REQ = 40,   /*40 network personalization PIN required */
    CME_NW_PERSONAL_PUK_REQ,        /*41 network personalization PUK required*/
    CME_NW_SUBSET_PERSONAL_PIN_REQ, /*42 network subset personalization PIN required*/
    CME_NW_SUBSET_PERSONAL_PUK_REQ, /*43 network subset personalization PUK required*/
    CME_SRV_PROVIDER_PERSONAL_PIN_REQ,  /*44 service provider personalization PIN required*/
    CME_SRV_PROVIDER_PERSONAL_PUK_REQ,  /*45 service provider personalization PUK required*/
    CME_CORPORATE_PERSONAL_PIN_REQ,     /*46 corporate personalization PIN required*/
    CME_CORPORATE_PERSONAL_PUK_REQ,     /*47 corporate personalization PUK required*/
    CME_HIDDEN_KEY_REQ,                 /*48 hidden key required (See NOTE 2)*/
    CME_EAP_METHOD_NOT_SUPPORT,         /*49 EAP method not supported*/
    CME_INCORRECT_PARAM = 50,           /*50 Incorrect parameters*/
    CME_CMD_IMPLEMENTED_BUT_CUR_DISABLED,   /*51 command implemented but currently disabled*/
    CME_CMD_ABORT_BY_USER,              /*52 command aborted by user*/
    CME_NOT_ATTACHED_DUE_TO_RESTRICT,   /*53 not attached to network due to MT functionality restrictions*/
    CME_MODEM_NOT_ALLOWED_EC_ONLY,      /*54 modem not allowed - MT restricted to emergency calls only*/
    CME_OPER_NOT_ALLOWED_DUE_TO_RESTRICT,   /*55 operation not allowed because of MT functionality restrictions*/
    CME_FIXED_DIAL_NUM_ONLY,        /*56 fixed dial number only allowed - called number is not a fixed dial number (refer 3GPP TS 22.101 [147])*/
    CME_TEMP_OOS_DUE_TO_OTHER_USAGE,    /*57 temporarily out of service due to other MT usage*/
    CME_LANG_NOT_SUPPORT,           /*58 language/alphabet not supported*/
    CME_UNEXPECTED_DATA_VALUE,      /*59 unexpected data value*/
    CME_SYS_FAIL = 60,              /*60 system failure*/
    CME_DATA_MISSING,               /*61 data missing*/
    CME_CALL_BARRED,                /*62 call barred*/
    CME_MSG_WAIT_IND_SUB_FAIL,      /*63 message waiting indication subscription failure*/

    /* ... */
    CME_UNKNOWN = 100,
    /*
     * 101 - 150 are reserved for use by GPRS and EPS
    */
    CME_ILLEGAL_MS = 103,//#3
    CME_ILLEGAL_ME = 106,//#6
    CME_GPRS_SERVICES_NOT_ALLOWED = 107,//#7
    CME_GPRS_SERVICES_AND_NON_GPRS_SERVICES_NOT_ALLOWED = 108,//#8
    CME_PLMN_NOT_ALLOWED = 111,//#11
    CME_LOCATION_AREA_NOT_ALLOWED,//#12
    CME_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA,//#13
    CME_GPRS_SERVICES_NOT_ALLOWED_IN_THIS_PLMN,//#14
    CME_NO_SUITABLE_CELLS_IN_LOCATION_AREA,//#15
    CME_CONGESTION = 122,//#22
    CME_INSUFFICIENT_RESOURCES = 126, //#26
    CME_MISSING_OR_UNKNOWN_APN,//#27
    CME_UNKNOWN_PDP_ADDRESS_OR_PDP_TYPE,//#28
    CME_USER_AUTHENTICATION_FAILED,//#29
    CME_ACTIVATE_REJECT_BY_GGSN_SERVING_GW_OR_PDN_GW,//#30
    CME_ACTIVATE_REJECT_UNSPECIFIED,//#31
    CME_SERVICE_OPTION_NOT_SUPPORTED,//#32
    CME_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED,//#33
    CME_SERVICE_OPTION_TEMPORATILY_OUT_OF_ORDER,//#34
    CME_FEATURE_NOT_SUPPORTED = 140, //#40
    CME_SEMANTIC_ERRORS_IN_THE_TFT_OPERATION,//#41
    CME_SYNTACTICAL_ERRORS_IN_THE_TFT_OPERATION,//#42
    CME_UNKNOWN_PDP_CONTEXT,//#43
    CME_SEMANTIC_ERRORS_IN_PACKET_FILTERS,//#44
    CME_SYNTACTICAL_ERRORS_IN_PACKET_FILTERS,//#45
    CME_PDP_CONTEXT_WITHOUT_TFT_ALREADY_ACTIVATED,//#46
    CME_UNSPECIFIED_GPRS_ERROR = 148,
    CME_PDP_AUTHENTICATION_FAILURE = 149,
    CME_INVALID_MOBILE_CLASS,



    /*
     * 151 - 170 are reserved for use by VBS/VGCS and eMLPP
    */

    /*
     * 171 - 256 are reserved for use by GPRS or EPS
    */
    CME_LAST_PDN_DISCONNECTION_NOT_ALLOWED = 171,   /*Last PDN disconnection not allowed (#49)*/
    CME_SEMANTICALLY_INCORECT_MESSAGE,//#95
    CME_MANDATORY_INFORMATION_ELEMENT_ERROR,//#96
    CME_INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED,//#97
    CME_CONDITIONAL_IE_ERROR, // #99
    CME_PROTOCOL_ERROR_UNSPECIFIED, // #111
    CME_OPERATOR_DETERMINED_BARRING, //#8    /*Operator Determined Barring*/
    CME_MAX_NUMBER_OF_PDP_CONTEXTS_REACHED,//#65
    CME_REQUESTED_APN_NOT_SUPPORTED_IN_CURRENT_RAT_AND_PLMN_COMBINATION,//#66
    CME_REQUEST_REJECTED_BEARER_CONTROL_MODE_VIOLATION,//#48
    CME_UNSUPPORTED_QCI_VALUE,//#83
    CME_USER_DATA_TRANSMISSION_VIA_CONTROL_PLANE_IS_CONGESTED,
    /*
     * 257 - 300 are reserved for general errors
    */

    /*
     * 301 - 0xFFFF are reserved for internal
    */
    CME_INTERNAL_ERROR_BASE = 301,
    CME_UE_BUSY,
    //CME_OPERATION_NOT_SUPPORT,
    //CME_INVALID_INPUT_PARM,
    CME_NOT_POWER_ON,
    CME_PDN_NOT_ACTIVED,
    CME_PDN_NOT_VALID,
    CME_PDN_INVALID_TYPE,
    CME_PDN_NO_PARAM,

    CME_UE_FAIL,
    CME_PDP_APN_AND_PDN_TYPE_DUPLICATE_USED,//#309
    CME_PDP_PAP_AND_EITF_NOT_MATCHED,

    CME_SIM_PIN_DISABLED,
    CME_SIM_PIN_ALREADY_ENABLED,
    CME_SIM_PIN_BLOCKED,
    CME_SIM_PIN_WRONG_FORMAT,

    CME_PDN_NOT_ALLOWED_BY_RPM,
	
    CME_PS_INTERNAL_ERROR_MAX1 = 400,
    CME_INVALID_PLMN = 401,
    CME_PLMN_DUPLICATE_USED = 402,
    CME_PLMN_NOT_FOUND = 403,
    CME_PLMN_TABLE_EMPTY = 404,
    CME_PLMN_TABLE_FULL = 405,
    CME_NO_ESM_CAUSE =406,
    CME_UNKNOWN_ESM_CAUSE = 407,
    CME_COMMAND_NOT_SUCCESS = 408,

    /*
     * 401 - 500 are reserved for socket error.
     *  Defined in: cms_sock_mgr.h
    */


    CME_MAX_ERROR = 0xFFFF
}MtErrorResultCode;

typedef UINT16 CmiRcCode;

/******************************************************************************
 * SMS error result code
 * refer: 27.005 3.2.5
******************************************************************************/
typedef enum SmsErrorResultCode_TAG
{
    CMS_SMS_SUCC = 0,

    /*
     * 300 - 500 are reserved for SMS errors
    */
    CMS_SMS_ME_FAILURE = 300,
    CMS_SMS_SERVICE_OF_ME_RESV,
    CMS_SMS_OPERATION_NOT_ALLOWED,
    CMS_SMS_OPERATION_NOT_SUPPORTED,
    CMS_SMS_INVALID_PDU_MODE_PARAMETER,
    CMS_SMS_INVALID_TEXT_MODE_PARAMETER,
    CMS_SMS_USIM_NOT_INSERTED = 310,
    CMS_SMS_USIM_PIN_REQUIRED,
    CMS_SMS_PHSIM_PIN_REQUIRED,
    CMS_SMS_USIM_FAILURE,
    CMS_SMS_USIM_BUSY,
    CMS_SMS_USIM_WRONG,
    CMS_SMS_USIM_PUK_REQUIRED,
    CMS_SMS_USIM_PIN2_REQUIRED,
    CMS_SMS_USIM_PUK2_REQUIRED,
    CMS_SMS_MEMORY_FAILURE = 320,
    CMS_SMS_INVALID_MEM_INDEX,
    CMS_SMS_MEM_FULL,
    CMS_SMS_SMSC_ADDR_UNKNOWN = 330,
    CMS_SMS_NO_NETWORK_SERVICE,
    CMS_SMS_NETWORK_TIMEOUT,
    CMS_SMS_NO_CNMA_ACK_EXPECTED = 340,

    CMS_SMS_UNKNOWN_ERROR = 500,

    CMS_MAX_ERROR = 0xFFFF
}SmsErrorResultCode;

typedef UINT16 CmiSmsRcCode;

/******************************************************************************
 * CAC service group enum definition
******************************************************************************/
typedef enum CacSgIdEnum_Tag
{
    CAC_BASE = 1,//basic/common
    CAC_DEV = 2,
    CAC_MM = 3,
    CAC_PS = 4,
    CAC_SIM = 5,
    CAC_SMS = 6,

    CAC_MAX = 15
}CacSgIdEnum;

/*
 * CMI SIGNAL ID, between AtCmdSrv Task & CAC/CCM Task
*/
typedef enum CACCMISIGID_enum
{
    SIG_CAC_CMI_BASE = 0x11F0,
    SIG_CAC_CMI_REQ,
    SIG_CAC_CMI_CNF, /*in fact need to put into ATCMD task signal definition queue*/
    SIG_CAC_CMI_IND, /*in fact need to put into ATCMD task signal definition queue*/
    SIG_CAC_CMI_RSP,
//	SIG_CAC_CMI_SYNC_REQ,
    SIG_CAC_CMI_END = 0x11FF,
}CACCMISIGID;

/*
 * Numberic PLMN format, 4 bytes,
 * example: CMCC: 46000; mcc = 0x0460, mnc = 0xf000
*/
typedef struct CmiNumericPlmn_Tag
{
    UINT16 mcc;
    UINT16 mncWithAddInfo; // if 2-digit MNC type, the 4 MSB bits should set to 'F',
}CmiNumericPlmn;

#define CAC_GET_PURE_MNC(mncWithAddInfo) ((mncWithAddInfo)&0xFFF)
#define CAC_IS_2_DIGIT_MNC(mncWithAddInfo) (((mncWithAddInfo)>>12) == 0x0F)

#define CAC_SET_MNC_WITH_ADD_INFO(twoDigitType, pureMnc) ((twoDigitType)?((pureMnc)|0xF000):((pureMnc)&0xFFF))

/*
 * IP address info
*/
#define CMI_MAX_IP_ADDR_LEN         16

/*
 * Address IP type
*/
typedef enum CmiIpAddrTypeTag
{
    CMI_INVALID_IP_ADDR = 0,
    CMI_IPV4_ADDR,          // 4 bytes length
    CMI_FULL_IPV6_ADDR,     // 16 bytes length
    CMI_IPV6_INTERFACE_ADDR // 8 bytes length
}CmiIpAddrType;

typedef struct CmiIpAddrTag
{
    UINT8   addrType;    //CmiIpAddrType
    UINT8   subnetLength;
    UINT16  reserved0;
    UINT8   addrData[CMI_MAX_IP_ADDR_LEN];
}CmiIpAddr;    //20 bytes


#define CMI_SIM_MAX_IMSI_STRING_LENGTH        16
/*
 * IMSI string structure, 20 bytes
*/
typedef struct CmiSimImsiStrTag
{
    UINT8       length;
    BOOL        bThreeDigitalMnc;
    UINT16      reserved0;
    /*example: IMSI: "460002343454245" */
    CHAR        contents[CMI_SIM_MAX_IMSI_STRING_LENGTH];
}CmiSimImsiStr;


/******************************************************************************
 * CacCmiReq - SIG_CAC_CMI_REQ
 * CMI interface request, all other module (AT CMD server) use this signal to
 *  access the CIOT modem
 * Int16 reqId; 4 MSB bits SG ID | 12 bits PRIM ID;
 * Int16 srcHandler; ID use to identify which module send this request
 * Int8 body[0]; request PRIM entity
******************************************************************************/
typedef struct CacCmiReqTag
{
    struct {
        UINT16 reqId;
        UINT16 srcHandler;
    }header;

    UINT8 body[];
}CacCmiReq;

#define CAC_GET_SG_ID(reqId) (((reqId)>>12)&0x000f)
#define CAC_GET_PRIM_ID(reqId) ((reqId)&0x0fff)
#define CAC_SET_REQ_CNF_ID(sgId, primId) ((UINT16)(((sgId)<<12)|((primId)&0x0fff)))

/******************************************************************************
 * CacCmiCnf - SIG_CAC_CMI_CNF
******************************************************************************/
typedef struct CacCmiCnfTag
{
    struct {
        UINT16      cnfId;      //4 MSB bits SG ID | 12 bits PRIM ID
        UINT16      srcHandler; //Handler from CacCmiReq
        UINT16      rc;
        UINT16      reserved;
    }header;

    UINT8 body[];
}CacCmiCnf;

#define CAC_GET_CMICNF_FROM_BODY(pCmiBody) (CacCmiCnf *)(((UINT8 *)(pCmiBody)) - (UINT32)(OFFSETOF(CacCmiCnf, body)))

/******************************************************************************
 * CacCmiInd - SIG_CAC_CMI_IND
******************************************************************************/
typedef struct CacCmiIndTag
{
    struct {
        UINT16      indId;      //4 MSB bits SG ID | 12 bits PRIM ID
        /*
         * As some indication is triggered by some AT request, in such as need to fill this "reqHandler",
         *  otherwise set to "PS_BROADCAST_IND_HANDLER".
        */
        UINT16      reqHandler;
    }header;

    UINT8 body[];
}CacCmiInd;


/******************************************************************************
 * CacCmiRsp - SIG_CAC_CMI_RSP
******************************************************************************/
typedef struct CacCmiRspTag
{
    struct {
        UINT16      rspId;      //4 MSB bits SG ID | 12 bits PRIM ID
        UINT16      rspHandler;
    }header;

    UINT8 body[];
}CacCmiRsp;



#define CAC_GET_CMIIND_FROM_BODY(pCmiBody) (CacCmiInd *)(((UINT8 *)(pCmiBody)) - (UINT32)(OFFSETOF(CacCmiInd, body)))

#if 0
/******************************************************************************
 * CamCmiReq - SIG_CAM_CMI_SYNC_REQ
 * CMI interface request, all other module (AT CMD server) use this signal to
 *  access the CIOT modem, and syn confirm
******************************************************************************/
typedef struct CamCmiSyncReqTag
{
    osSemaphoreId_t     sem;

    /* output info */
    UINT32              *pCmiRc;            /* MtErrorResultCode/SmsErrorResultCode */
    UINT16              cnfBufSize;
    UINT16              rsvd0;
    void                *pOutCmiCnf;        /* CMI confirm struct, CMI CNF, copy to here */

    /* input info */
    CacCmiReq           cmiReq;
}CamCmiSyncReq;

#endif

/******************************************************************************
 * If no parameters carried in signal, just pass a reserved Int32
******************************************************************************/
typedef UINT32 CacCmiEmptySig;
//typedef UINT8 CacCmiEmptySig[]; // sizeof it == 0


/******************************************************************************
 ******************************************************************************
 * API definition
 ******************************************************************************
******************************************************************************/
/*
 * SIG_CAC_CMI_REQ to CAC task
*/
void CacCmiRequest(UINT16 srcHdr, UINT8 sgId, UINT16 primId, UINT16 primSize, void *primBody);

/******************************************************************************
 * CacMmGetCurCELevel
 * Description: return current UE (NB/EMTC) Coverage Enhancement level
 * input: UINT8 *pAct;  //output, current ACT: NB/EMTC
 *        UINT8 *pCeLevel;  //output, current CE level
 * output: void
 * Comment:
 * Return:
 * *pAct:
 *  0 CMI_MM_CES_NO_CE_ACT //UE not attached;
 *  1 CMI_MM_CES_EUTRAN_EMTC
 *  2 CMI_MM_CES_EC_GSM //not support
 *  3 CMI_MM_CES_EUTRAN_NB
 * *pCeLevel:
 *  0 No Coverage Enhancement in the serving cell
 *  1 Coverage Enhancement level 0
 *  2 Coverage Enhancement level 1
 *  3 Coverage Enhancement level 2
 *  4 Coverage Enhancement level 3   // for EMTC
******************************************************************************/
void CacMmGetCurCELevel(UINT8 *pAct, UINT8 *pCeLevel);

#endif

