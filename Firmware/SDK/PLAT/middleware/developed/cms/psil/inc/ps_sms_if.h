/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: ps_sms_if.h
 *
 *  Description: API interface for SMS service
 *
 *  History:
 *
 *  Notes:
 *
******************************************************************************/
#ifndef __PS_SMS_IF_H__
#define __PS_SMS_IF_H__

#include "cms_util.h"
#include "cmisms.h"

/******************************************************************************
 * SMS/CB Parameter Definitions: (27.005)
 * ============================================================================
 * A) Message storage param
 * 1. <index>: integer type
 *          value in the range of location numbers supported by the associated memory
 * 2. <mem1>: string type
 *          memory from which messages are READ and DELETED; +CMGL/+CMGR/+CMGD
 *   "BM"   - broadcast message storage (-NOT support)
 *   "ME"   - ME message storage        (-NOT support)
 *   "MT"   - any of the storages associated with ME    (-NOT support)
 *   "SM"   - (U)SIM message storage    (-NOT support)  - plan to - TBD
 *   "TA"   - TA message storage        (-NOT support)
 *   "SR"   - status report storage     (-NOT support)
 * 3. <mem2>: memory to which writing and sending operations
 *    <mem3>: memory to which received SMs are preferred to be stored
 *            unless forwarded directly to TE: +CNMI
 * 4. <stat>: integer type in PDU mode; string type in text mode
 *            the status of message in memory
 *    0 "REC UNREAD"    received unread message (i.e. new message)
 *    1 "REC READ"      received read message
 *    2 "STO UNSENT"    stored unsent message (only applicable to SMs)
 *    3 "STO SENT"      stored sent message (only applicable to SMs)
 *    4 "ALL"           all messages (only applicable to +CMGL command)
 *
 * ============================================================================
 * B) Message data param
 * 1. <ackpdu>: string type
            RP-ACK PDU
 * 2. <alpha>:  string type
 *          alphanumeric representation of <da> or <oa> corresponding to the entry found in MT phonebook
 * 3. <cdata>:  string type
 *          TP-Command-Data in text mode responses,
 *          example: int: 42 (0x2A) => "2A"
 * 4. <ct>:     integer type
 *          TP-Command-Type (default: 0)
 * 5. <da>:     string format
 *          TP-Destination-Address, type of address given by <toda>
 * 6. <data>
 *          TP-User-Data in text mode response
 * 7. <dcs>     integer format
 *           SMS Data Coding Scheme (default 0)
 * 8. <dt>      time-string format
 *          TP-Discharge-Time: "yy/MM/dd,hh:mm:ss¡Àzz"
 * 9. <fo>      integer format
 *          first octet of SMS-DELIVER, SMSSUBMIT (default 17), SMS-STATUS-REPORT, or SMS-COMMAND (default 2)
 * 10.<length>  integer format
 *          the length of the message body <data> in characters, in the text mode (+CMGF=1)
 *          the length of the actual TP data unit in octets (INT8), in the PDU mode (+CMGF=0)
 * 11.<mid>     integer format
 *          CBM Message Identifier
 * 12.<mn>      integer format
 *          TP-Message-Number
 * 13.<mr>      integer format
 *          TP-Message-Reference
 * 14.<oa>      string format
 *          TP-Originating-Address, type of address given by <tooa>
 * 15.<page>    integer format
 *          23.041 CBM Page Parameter bits 4-7
 * 16.<pages>   integer format
 *          23.041 CBM Page Parameter bits 0-3
 * 17.<pdu>     hexadecimal format
 *          SMS TPDU in hexadecimal format: ME/TA converts each octet of TP data unit into two IRA character
 *          example: int: 42 (0x2A) => "2A"
 * 18.<pid>     integer format
 *          23.040 TP-Protocol-Identifier in integer format (default 0)
 * 19.<ra>      string format
 *          23.040 TP-Recipient-Address, type of address given by <tora>
 * 20.<sca>     string format
 *          24.011 RP SC (SMS service centre) address Address, type of address given by <tosca>
 * 21.<scts>    time-string format
 *          23.040 TP-Service-Centre-Time-Stamp
 * 22.<sn>      integer format
 *          23.041 CBM Serial Number
 * 23.<st>      integer format
 *          23.040 TP-Status
 * 24.<toda>    integer format
 *          24.011 TP-Destination-Address Type-of-Address
 *          when first character of <da> is + (IRA 43) default is 145, otherwise default is 129
 * 25.<tooa>/<tora>/<tosca>
 *          Type-of-Address octet in integer format
 * 26.<vp>      integer format/time-string format
 *          depending on SMS-SUBMIT <fo> setting: 3GPP TS 23.040 [3] TP-Validity-Period
 *          either in integer format (default 167) or in time-string format (refer <dt>)
 *
*******************************************************************************
 * Memory:
 * 1> AT+CSMP, +CSCA and +CSCB settings are stored directly to non-volatile memory of ME
 *   a) AT+CSMP, param saved in mwconfig.nvm;
 *   b) +CSCA=<sca>[,<tosca>], param saved in UICC
 *
******************************************************************************/



/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/


#define PSIL_SMS_ADDR_INTERNATIONAL_PREFIX   ((UINT8)'+')
#define PSIL_SMS_MAX_PDU_SIZE           CMI_SMS_MAX_PDU_SIZE    //180
#define PSIL_SMS_MAX_TXT_SIZE           160

/*
 * Service Centre address, ref: 24.011 8.2.5.1
 * +----------------+
 * |    length      |   Length of SC Address contents
 * +----------------+
 * |      TOA       |   Type-of-Address
 * +----------------+
 * | dig 2 | dig 1  |   Address value, 0 - 10 bytes
 * +----------------+
 * | dig 4 | dig 3  |
 * +----------------+
 * length: byte length, include: TOA and address.
 * TOA:
 *   7                           0
 * +---+---+---+---+---+---+---+---+
 * | 1 |  type-num |    num-plan   |
 * +---+---+---+---+---+---+---+---+
 *  type-num:   CmiSmsNumTypeEnum
 *  num-plan:   CmiSmsNumPlanEnum
*/
#define PSIL_SMS_ADDR_ENCODE_MAX_SIZE   12


/*
 * From 27.005:
 * 1> <pdu>: In the case of SMS: 3GPP TS 24.011 [6] SC address followed by 3GPP TS 23.040 [3] TPDU in
 *        hexadecimal format.
 * 2> AT input is "HEX" (hexadecimal) string type, example: "2A" just means: 0x2A.
 * 3> So the input max string size should be: 2*(180+12)
*/
#define PSIL_SMS_HEX_PDU_STR_MAX_SIZE   (2*(PSIL_SMS_MAX_PDU_SIZE+PSIL_SMS_ADDR_ENCODE_MAX_SIZE))


#define PSIL_SMS_BCD_POS                2

/*
 * FO:
 * SMS-SUBMIT first octet, ref: 23.040 9.2.2.2
 *   7                           0
 * +---+---+---+---+---+---+---+---+
 * |RP |UDHISRR|  VPF  | RD|  MTI  |
 * +---+---+---+---+---+---+---+---+
 * RP:  Reply Path, 0 - not set
 * UDHI:User-Data-Header-Indicator, 0 - The TP-UD field contains only the short message
 * SRR: Status-Report-Request , 1 - A status report is requested
 * VPF: Validity-Period-Format, 00 - TP-VP field not present
 * RD:  Reject-Duplicates, 0 - SC not reject the duplicate SMS
 * MTI: Message-Type-Indicator, 01 - SMS-SUBMIT
 *
 * Default FO: 0x21; SMS-SUBMIT PDU, status report required
*/
#define PSIL_MSG_FO_DEFAULT             ((UINT8)0x21)
#define PSIL_MSG_VP_DEFAULT             ((UINT8)167)        /* 24 hours - see 3GPP TS 23.040-9.2.3.12 */
#define PSIL_MSG_PID_DEFAULT            ((UINT8)0)          /* see 3GPP TS 23.040-9.2.3.9 */
#define PSIL_MSG_REF_DEFAULT            ((UINT8)0)          /* Reference=0  */
#define PSIL_MSG_UDH_NOT_PRESENT        ((UINT8)0)

/*
 * SMS-SUBMIT T-PDU format/basic element, ref: 23.040 9.2.2.2
 * +----------------+
 * |      FO        |
 * +----------------+
 * |      MR        |   Message-Reference
 * +----------------+
 * \      DA        \   Destination-Address, length: 2 - 12 bytes
 * +----------------+
 * |      PID       |   Protocol-Identifier
 * +----------------+
 * |      DCS       |   Data-Coding-Scheme
 * +----------------+
 * :      VP        :   Validity-Period, 0/1/7 bytes
 * +----------------+
 * |      UDL       |   User-Data-Length
 * +----------------+
 * \      UD        \   User-Data, 0 - 140 bytes
 * +----------------+
*/

/*
 * SM-TL, address field (Destination-Address), ref: 23.040 9.1.2.5
 * +----------------+
 * |      AL        |   Address length
 * +----------------+
 * |      TOA       |   Type-of-Address
 * +----------------+
 * \      AV        \   Address value, 0 - 10 bytes
 * +----------------+
 * AL:  Number of useful semi-octets within the Address-Value field. !! (1 byte -> 2 length) !!
 * TOA:
 *   7                           0
 * +---+---+---+---+---+---+---+---+
 * | 1 |  type-num |    num-plan   |
 * +---+---+---+---+---+---+---+---+
 *  type-num:   CmiSmsNumTypeEnum
 *  num-plan:   CmiSmsNumPlanEnum
*/






/*
 * MSG/SMS ADDRESS LEN, encoded MAX 10 bytes, so MAX 20 length here
*/
#define PSIL_MSG_MAX_ADDR_LEN   20


/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/


typedef enum PsilSmsDCSType_enum
{
    PSIL_SMS_DCS_GENERAL_TYPE = 0,
    PSIL_SMS_DCS_WAIT_TYPE,
    PSIL_SMS_DCS_CLASS_TYPE
}PsilSmsDCSType;

typedef enum PsilSmsDCSClass_enum
{
    PSIL_SMS_DCS_CLASS_0 = 0,
    PSIL_SMS_DCS_CLASS_1,       /* Default meaning: ME-specific */
    PSIL_SMS_DCS_CLASS_2,       /* (U)SIM specific message */
    PSIL_SMS_DCS_CLASS_3        /* Default meaning: TE specific */
}PsilSmsDCSClass;

typedef enum PsilSmsDCSIndType_Tag
{
    PSIL_SMS_DCS_VOICEMAIL_IND = 0, /* Voicemail Message Waiting */
    PSIL_SMS_DCS_FAX_IND,           /* Fax Message Waiting */
    PSIL_SMS_DCS_EMAIL_IND,         /* Electronic Mail Message Waiting */
    PSIL_SMS_DCS_OTHER_IND          /* Other Message Waiting */
}PsilSmsDCSIndType;

/*
 * enum to record current MSG/SMS operation
 */
typedef enum
{
    PSIL_SMS_OPER_LIST_MSG = 1,
    PSIL_SMS_OPER_READ_MSG,
    PSIL_SMS_OPER_SEND_MSG,
    PSIL_SMS_OPER_STORE_MSG,
    PSIL_SMS_OPER_STORE_MSG_WITH_INDEX,
    PSIL_SMS_OPER_SEND_STORED_MSG,
    PSIL_SMS_OPER_DEL_MSG,
    PSIL_SMS_OPER_DEL_ALL_MSG,
    PSIL_SMS_OPER_GET_STORAGE_INFO,
    PSIL_SMS_OPER_QUERY_DEL_MSG,
    PSIL_SMS_OPER_NULL
}PsilSmsOperation;


/*
 * enum used in encoding/decoding SMS text
*/
typedef enum
{
    PSIL_MSG_CODING_DEFAULT       = 0x00, /* DCS_DEFAULT, should be 246 (0xF6), does not support 8-bit alphabet */
    PSIL_MSG_CODING_8BIT          = 0x01,
    PSIL_MSG_CODING_UCS2          = 0x02,
    PSIL_MSG_CODING_RESERVED      = 0x03,

    PSIL_MSG_CODING_NUM_OF
}PsilMsgCodingType;

/*
 * current SMS input/output format
*/
typedef enum PsilSmsFormatMode_enum
{
    PSIL_SMS_FORMAT_PDU_MODE = 0,
    PSIL_SMS_FORMAT_TXT_MODE = 1,
    PSIL_SMS_FORMAT_NUM_MODE
}PsilSmsFormatMode;

/*
 * <toda>, type of dest address
 *   3GPP TS 24.011 [6] TP-Destination-Address Type-of-Address octet in integer format (when first
 *     character of <da> is + (IRA 43) default is 145, otherwise default is 129)
 *   3GPP TS 23.040, 9.1.2.5
*/
typedef enum PsilSmsTypeOfAddrOct_enum
{
    PSIL_SMS_TOA_OCT_NUMBER_UNKNOWN       = 0x81,   /* 129, Unknown type, IDSN format number */
    PSIL_SMS_TOA_OCT_NUMBER_RESTRICTED    = 0x80,   /* 128, Unknown type, unknown number format */
    PSIL_SMS_TOA_OCT_NUMBER_NATIONAL      = 0xA1,   /* 161, National number type, IDSN format */
    PSIL_SMS_TOA_OCT_NUMBER_INTERNATIONAL = 0x91,   /* 145, International number type, ISDN format */
    PSIL_SMS_TOA_OCT_NUMBER_NET_SPECIFIC  = 0xB1,   /* 177, Network specific number, ISDN format */
    PSIL_SMS_TOA_OCT_NUMBER_DEDICATED     = 0xC1,   /* 193, Subscriber number, ISDN format */
    PSIL_SMS_TOA_OCT_NUMBER_EXTENSION     = 0xF1,   /* 241, extension, ISDN format*/
    PSIL_SMS_TOA_OCT_NUMBER_INVALID
}PsilSmsTypeOfAddrOct;



/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/*
 * SMS send message/command info, used for AT:
 * 1> AT+CMGS
 *   a) text mode
 *      AT+CMGS=<da>[,<toda>]<CR>
 *       text is entered<ctrl-Z/ESC>
 *   b) PDU mode
 *      +CMGS=<length><CR>
 *       PDU is given<ctrl-Z/ESC>
 * 2> AT+CMGC
 *   a) text mode
 *      AT+CMGC=<fo>,<ct>[,<pid>[,<mn>[,<da>[,<toda>]]]]<CR>
 *       text is entered<ctrl-Z/ESC>
 *   b) PDU mode
 *      +CMGC=<length><CR>
 *       PDU is given<ctrl-Z/ESC>
 * =====================================
 * Note:
 According to 27.005
 *
 *
*/
typedef struct PsilSmsSendInfo_Tag
{
    UINT16      reqHander;  /*if set to zero, just means no sending request */

    /*
     * Used for PDU mode, input of: +CMGS=<length><CR>
     * <length> must indicate the number of octets coded in the TP layer data unit to be given
     *    (i.e. SMSC address octets are excluded)
     * If set to 0, just means not set.
    */
    UINT16      reqPduLen;

    /*
     * For Text mode,
     * +CMGS=<da>[,<toda>]<CR>...
     *
     * example:
     * DA: "+8613813801380"
     * daInfo.len = 13
     * daInfo.digits = "8613813801380\0" => string format
     */
    CmiSmsAddressInfo   daInfo;

    UINT16      inputOffset;
    BOOL        bCommand;
    UINT8       rsvd0;
    UINT8       input[PSIL_SMS_HEX_PDU_STR_MAX_SIZE];    //not support long SMS
}PsilSmsSendInfo;

typedef struct PsilSmsTimeStampInfo_tag
{
    UINT8   year;
    UINT8   month;
    UINT8   day;
    UINT8   hour;
    UINT8   minute;
    UINT8   second;
    UINT8   tz;     //time zone
    UINT8   tzSign; //'+'/'-'
}PsilSmsTimeStampInfo;

typedef struct PsilSmsDcsInfo_Tag
{
    UINT32 type;
    UINT32 msgClass;
    UINT32 alphabet;
    UINT32 indication;
}PsilSmsDcsInfo;


/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/
void smsSetSrvCenterAddrsync(void *msg);
void smsGetSrvCenterAddrsync(void *msg);
CmsRetId smsQuerySmsService(UINT32 atHandle);
CmsRetId smsGetSmsService(UINT32 atHandle);
CmsRetId smsSetSmsService(UINT32 atHandle, const UINT32 service);
CmsRetId smsGetSrvCenterAddr(UINT32 atHandle);
CmsRetId smsSetSrvCenterAddr(UINT32 atHandle, const UINT8 *addressStr, UINT16 addrStrLen, UINT32 toaOctType);
void smsPduDecodeAddress(UINT8 *pPdu, UINT8 *pIdx, UINT8 *pAddrOutput, UINT8 outBufSize);
void smsPduDecodeProtocolId(UINT8 *pPdu, UINT8 *pIdx, UINT8 *pidOutput);
void smsPduDecodeDcs( UINT8 *pPdu, UINT8 *pIdx, PsilSmsDcsInfo *dDCS);
void smsPduDecodeTimeStamp( UINT8 *pPdu, UINT8 *pIdx, PsilSmsTimeStampInfo *tm);
void smsPduDecodeUserData(UINT8     *pUserData,
                          UINT8     pduDataLen,
                          PsilMsgCodingType codingType,
                          BOOL      hdrPst,
                          UINT8     *pDst,
                          UINT8     *pOutLen,
                          UINT8     dstBufSize);

CmsRetId smsSendSms(UINT8 smsFormat, PsilSmsSendInfo *pSendInfo);

UINT16 errorCauseofSendSms(UINT16 rc, UINT8 rpCause, UINT8 tpCause);
void smsPutPackedSMSC(CmiSmsAddressInfo *pScaInfo, CHAR *pSmsc, UINT16 *pSmscLen);
void smsSMSCToHexStrPdu(CmiSmsAddressInfo *pScaInfo, CHAR *pSmsc, UINT16 *pSmscLen);


#endif

