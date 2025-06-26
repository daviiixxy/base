#ifndef __CMI_SMS_H__
#define __CMI_SMS_H__
/******************************************************************************
Copyright:      - 2017- Copyrights of Qualcomm Ltd.
File name:      - cmisms.h
Description:    - CMI (CIoT modem interface) SMS handling interface defination
History:        - 10/12/2017, Originated by xpliu
******************************************************************************/
#include "cmicomm.h"


typedef enum CMI_SMS_PRIM_ID_TAG
{
    CMI_SMS_PRIM_BASE = 0,

    CMI_SMS_SEND_MSG_REQ,//AT+CMGS=...<ctrl+z>
    CMI_SMS_SEND_MSG_CNF,

    CMI_SMS_SEND_COMMAND_REQ,//AT+CMGC=...<ctrl+z>
    CMI_SMS_SEND_COMMAND_CNF,

    CMI_SMS_NEW_MSG_INDEX_IND,//+CMTI
    CMI_SMS_NEW_MSG_IND,//+CMT
    CMI_SMS_NEW_MSG_RSP,//+CNMA

    CMI_SMS_GET_SMSC_ADDR_REQ,//AT+CSCA?
    CMI_SMS_GET_SMSC_ADDR_CNF,
    CMI_SMS_SET_SMSC_ADDR_REQ,//AT+CSCA=
    CMI_SMS_SET_SMSC_ADDR_CNF,

    CMI_SMS_SELECT_SMS_SERVICE_REQ,   //AT+CSMS=
    CMI_SMS_SELECT_SMS_SERVICE_CNF,
    CMI_SMS_GET_CURRENT_SMS_SERVICE_REQ,      //AT+CSMS?
    CMI_SMS_GET_CURRENT_SMS_SERVICE_CNF,
    CMI_SMS_GET_SUPPORTED_SMS_SERVICE_REQ,      //AT+CSMS=?
    CMI_SMS_GET_SUPPORTED_SMS_SERVICE_CNF,

    CMI_SMS_PRIM_END = 0x0fff
}CMI_SMS_PRIM_ID;

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/******************************************************************************
 * CMI_SMS_SEND_MSG_REQ
******************************************************************************/
#define CMI_SMS_MAX_PDU_SIZE 180
#define CMI_SMS_MAX_ADDRESS_LENGTH 40


typedef struct CmiSmsPdu_Tag
{
    UINT16   len;
    UINT16   reserved0;
    UINT8    pduData[CMI_SMS_MAX_PDU_SIZE];
}CmiSmsPdu;

typedef enum CmiSmsNumTypeEnum_Tag
{
    CMI_SMS_NUMTYPE_UNKNOWN = 0,//Unknown
    CMI_SMS_NUMTYPE_INTERNATIONAL = 1, // Internation Number
    CMI_SMS_NUMTYPE_NATIONAL = 2,//National Number
    CMI_SMS_NUMTYPE_NETWORK = 3,//Network Specific
    CMI_SMS_NUMTYPE_DEDICATED = 4,//Dedicated Access Number
    CMI_SMS_NUMTYPE_EXTENSION = 7,//Reserved for Extension

}CmiSmsNumTypeEnum;

typedef enum CmiSmsNumPlanEnum_Tag
{
    CMI_SMS_NUMPLAN_UNKNOWN = 0,//Unknown
    CMI_SMS_NUMPLAN_E164_E163 = 1, // ISDN/Telephony(E.164/E.163)
    CMI_SMS_NUMPLAN_DATA_X121 = 3,//Data Numbering Plan(X.121)
    CMI_SMS_NUMPLAN_TELEX_F69 = 4,//Telex Numbering Plan(F.69)
    CMI_SMS_NUMPLAN_NATIONAL = 8,//National Number Plan
    CMI_SMS_NUMPLAN_PRIVATE = 9,//Private Numbering Plan
    CMI_SMS_NUMPLAN_RSVD_CTS = 0xb,//Reserved for CTS
    CMI_SMS_NUMPLAN_EXTENSION = 0xf//Reserved for Extension

}CmiSmsNumPlanEnum;


typedef struct CmiSmsAddressType_Tag
{
    UINT8    numType;//Type of Number  CmiSmsNumTypeEnum
    UINT8    numPlan;//Number Plan Identification  CmiSmsNumPlanEnum
    UINT16   reserved0;
}CmiSmsAddressType;


typedef struct CmiSmsAddressInfo_Tag
{
    CmiSmsAddressType    addrType;//Address Type Information
    UINT8                len;//Address Length in digits
    UINT8                reserved0;
    UINT16               reserved1;
    UINT8                digits[CMI_SMS_MAX_ADDRESS_LENGTH];//Address digits
}CmiSmsAddressInfo;


typedef struct CmiSmsOptAddressInfo_Tag
{
    BOOL                 present;//Address info present or not
    UINT8                reserved0;
    UINT16               reserved1;
    CmiSmsAddressInfo    addressInfo;
}CmiSmsOptAddressInfo;

typedef enum CmiSmsRPCause_Tag
{
    CMI_SMS_RP_CAUSE_UNASSIGNED_NUMBER = 1,
    CMI_SMS_RP_CAUSE_OPERATOR_DETERMIN_BARRING = 8,
    CMI_SMS_RP_CAUSE_BARRED = 10,
    CMI_SMS_RP_CAUSE_RESERVD = 11,
    CMI_SMS_RP_CAUSE_TRANSFER_REJECTED = 21,
    CMI_SMS_RP_CAUSE_NEMORY_EXCEED = 22,
    CMI_SMS_RP_CAUSE_DESTION_OUT_OF_ORDER = 27,
    CMI_SMS_RP_CAUSE_UNIDENTIFIED_FORMAT = 28,
    CMI_SMS_RP_CAUSE_FACILITY_REJECTED = 29,
    CMI_SMS_RP_CAUSE_UNKNOWN_SUBSCRIBER = 30,
    CMI_SMS_RP_CAUSE_NETWORK_OUT_OF_ORDER = 38,
    CMI_SMS_RP_CAUSE_TEMP_FAILURE = 41,
    CMI_SMS_RP_CAUSE_CONGETION = 42,
    CMI_SMS_RP_CAUSE_RESOURCE_UNAVAILABLE = 47,
    CMI_SMS_RP_CAUSE_REQ_FAC_NOT_SUBSCR = 50,
    CMI_SMS_RP_CAUSE_REQ_FACILITY_NOT_IMPLEMENT = 69,
    CMI_SMS_RP_CAUSE_INVALID_TI_VALUE = 81,
    CMI_SMS_RP_CAUSE_INVALID_MSG_SEMANTICALLY = 95,
    CMI_SMS_RP_CAUSE_MANDATORY_IE_ERROR = 96,
    CMI_SMS_RP_CAUSE_MSG_TYPE_NO_EXISTENT = 97,
    CMI_SMS_RP_CAUSE_MSG_NOT_COMPATIABLE = 98,
    CMI_SMS_RP_CAUSE_IE_NON_EXISTENT = 99,
    CMI_SMS_RP_CAUSE_PROTOCOL_ERROR = 111,
    CMI_SMS_RP_CAUSE_INTERWORKING = 127

}CmiSmsRPCause;


typedef struct CmiSmsSendMsgReq_Tag
{
    BOOL                     bMoreMessage;
    UINT8                    reserved0;
    UINT16                   reserved1;
    CmiSmsOptAddressInfo     optSca;
    CmiSmsPdu                pdu;
}CmiSmsSendMsgReq;

typedef struct CmiSmsSendMsgCnf_Tag
{
    UINT8           msgReference;//Message Reference
    UINT8           rpCause;
    UINT8           tpCause;
    BOOL            ackPduPresent;
    CmiSmsPdu       pdu;
}CmiSmsSendMsgCnf;

typedef struct CmiSmsRspInfo_Tag
{
    CmiSmsRcCode   rc;
    UINT8          msgRef;  //Message Reference
    UINT8          rpCause;
    UINT8          tpCause;
}CmiSmsRspInfo;

/******************************************************************************
 * CMI_SMS_SEND_COMMAND_REQ
******************************************************************************/

typedef struct CmiSmsCmdRspInfo_Tag
{
    CmiSmsRcCode   rc;
    UINT8          msgRef;  //Message Reference
}CmiSmsCmdRspInfo;

typedef struct CmiSmsSendCommandReq_Tag
{
    CmiSmsPdu                pdu;
}CmiSmsSendCommandReq;

typedef struct CmiSmsSendCommandCnf_Tag
{
    UINT8           msgReference;//Message Reference
    BOOL            ackPduPresent;
    CmiSmsPdu       pdu;
}CmiSmsSendCommandCnf;


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/******************************************************************************
 * CMI_SMS_NEWMSG_IND
******************************************************************************/
typedef enum CmiSmsMsgCoding_Tag
{
    CMI_SMS_CODING_DEFAULT_ALPHABET = 0,//Default 7 bit coding
    CMI_SMS_CODING_8_BIT_DATA = 1, // 8bit coding
    CMI_SMS_CODING_UCS2_ALPHABET = 3,//UCS2 coding

}CmiSmsMsgCoding;

typedef enum CmiSmsMsgType_Tag
{
    CMI_SMS_TYPE_DELIVER = 0,//SMS-Deliver PDU
    CMI_SMS_TYPE_DELIVER_REPORT, // SMS-Deliver Report PDU
    CMI_SMS_TYPE_STATUS_REPORT//SMS-Status Report PDU

}CmiSmsMsgType;

typedef enum CmiSmsStorage_Tag
{
    CMI_SMS_STORAGE_ME = 0,//ME Storage
    CMI_SMS_STORAGE_MT,     //MT Storage
    CMI_SMS_STORAGE_SM,     //SIM Storage
    CMI_SMS_STORAGE_SR     //SMS-Status Report Storage

}CmiSmsStorage;


typedef struct CmiNewSmsInfo_Tag
{
    UINT8                smsType;  //CmiSmsMsgType
    UINT8                smsId;
    UINT8                smsCoding; //CmiSmsMsgCoding
    BOOL                 smscPresent;
    CmiSmsAddressInfo    smscAddr;
}CmiNewSmsInfo;

typedef struct CmiSmsNewMsgInd_Tag
{
    UINT8                smsType;  //CmiSmsMsgType
    UINT8                smsId;
    UINT8                smsCoding; //CmiSmsMsgCoding
    BOOL                 smscPresent;
    CmiSmsAddressInfo    smscAddr;
    CmiSmsPdu            pdu;
}CmiSmsNewMsgInd;

typedef struct CmiSmsNewMsgIndexInd_Tag
{
    UINT8        smsType;  //CmiSmsMsgType
    UINT8        storage;  //CmiSmsStorage
    UINT16       index;
}CmiSmsNewMsgIndexInd;


/******************************************************************************
 * CMI_SMS_NEW_MSG_RSP
******************************************************************************/
typedef struct CmiSmsNewMsgRsp_Tag
{
    BOOL         bRPAck;
    UINT8        smsId;
    BOOL         pduPresent;
    CmiSmsPdu    pdu;
}CmiSmsNewMsgRsp;

typedef CacCmiEmptySig CmiSmsGetSmscAddrReq;

typedef struct CmiSmsGetSmscAddrCnf_Tag{
    BOOL                       smscPresent;
    UINT8                      reserved0;
    UINT16                     reserved1;
    CmiSmsAddressInfo          smscAddr;     //Service center address
} CmiSmsGetSmscAddrCnf;

typedef struct CmiSmsSetSmscAddrReq_Tag{
    CmiSmsAddressInfo          smscAddr;      //Service center address
} CmiSmsSetSmscAddrReq;

typedef CacCmiEmptySig CmiSmsSetSmscAddrCnf;

#define CI_SMS_SERVICE_MAX 3

typedef enum CmiSmsService_Tag
{
    CMI_SMS_MESSAGE_SERVICE_NORMAL = 0,     //SERVICE_NORMAL
    CMI_SMS_MESSAGE_SERVICE_WITH_ACK = 1,   //SERVICE_WITH_ACK
    CMI_SMS_MESSAGE_SERVICE_MANUFACTURE_SPECIFIC = 128

}CmiSmsService;

typedef struct CmiSmsMsgTypeInfo_Tag{
    BOOL                    mtSupported;
    BOOL                    moSupported;
    BOOL                    bmSupported;
}CmiSmsMsgTypeInfo;

typedef CacCmiEmptySig CmiSmsGetSupportedSmsServiceReq;

typedef struct CmiSmsGetSupportedSmsServiceCnf_Tag{
    CmiSmsRcCode                rc;
    UINT8                       length;
    CmiSmsService               serviceList[CI_SMS_SERVICE_MAX];
}CmiSmsGetSupportedSmsServiceCnf;

typedef struct CmiSmsSelectSmsServiceReq_Tag{
    CmiSmsService           smsService;
} CmiSmsSelectSmsServiceReq;

typedef struct CmiSmsSelectSmsServiceCnf_Tag{
    CmiSmsRcCode                rc;
    CmiSmsMsgTypeInfo           msgType;
}CmiSmsSelectSmsServiceCnf;

typedef CacCmiEmptySig CmiSmsGetCurrentSmsServiceReq;

typedef struct CmiSmsGetCurrentSmsServiceCnf_Tag{
    CmiSmsRcCode                rc;
    CmiSmsService               smsService;
    CmiSmsMsgTypeInfo           msgType;
}CmiSmsGetCurrentSmsServiceCnf;

typedef struct LwM2MSmsNewMsgInd_Tag
{
	BOOL                 smscPresent;
    CmiSmsAddressInfo    smscAddr; 
	CmiSmsPdu            pdu;
}LwM2MSmsNewMsgInd;

#endif



