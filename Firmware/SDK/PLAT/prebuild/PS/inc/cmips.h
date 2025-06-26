#ifndef __CMI_PS_H__
#define __CMI_PS_H__
/******************************************************************************
Copyright:      - 2017- Copyrights of Qualcomm Ltd.
File name:      - cmips.h
Description:    - CMI (CIoT modem interface) PS handling interface defination
History:        - 08/09/2017, Originated by jcweng
******************************************************************************/
#include "cmicomm.h"

/******************************************************************************
 *****************************************************************************
 * Macro
 *****************************************************************************
******************************************************************************/
#define CMI_PS_CID_NUM              11
#define CMI_PS_INVALID_CID          0xFF
#define CMI_PS_MAX_VALID_CID        10  //CID MAX VALUE
#define CMI_PS_MIN_VALID_CID        0
#define CMI_PS_MAX_TFT_FILTERS      16
#define CMI_PS_MAX_APN_LEN          100
#define CMI_PS_MAX_AUTH_STR_LEN     81
#define CMI_PDN_MAX_NW_ADDR_NUM     4
#define CMI_PS_MAX_BEARER_NUM       11
#define DEVICE_INFO_APN_NAME_MAX 	100 /**< Maximum APN name length . */

/******************************************************************************
 *****************************************************************************
 * Enums
 *****************************************************************************
******************************************************************************/
typedef enum CMI_PS_PRIM_ID_TAG
{
    CMI_PS_PRIM_BASE = 0,

    CMI_PS_DEFINE_BEARER_CTX_REQ,   //AT+CGDCONT=<cid>,<PDP_type>, CmiPsDefineBearerCtxReq
    CMI_PS_DEFINE_BEARER_CTX_CNF,   //CmiPsDefineBearerCtxCnf
    CMI_PS_DEL_BEARER_CTX_REQ,      //AT+CGDCONT=<cid>, CmiPsDelBearerCtxReq
    CMI_PS_DEL_BEARER_CTX_CNF,      //CmiPsDelBearerCtxCnf

    CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ,   /*CmiPsGetAllBearersCidsInfoReq*/
    CMI_PS_GET_ALL_BEARERS_CIDS_INFO_CNF,   /*CmiPsGetAllBearersCidsInfoCnf*/

    /*
     * useless, please use: CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ
     * CMI_PS_GET_DEFINED_CID_LIST_REQ,
     * CMI_PS_GET_DEFINED_CID_LIST_CNF,
    */

    /*
     * AT+CGDCONT? is to query all the defined PDP info, in order to reduce the struct size,
     * Each time return one bearer info;
    */
    CMI_PS_GET_DEFINED_BEARER_CTX_REQ,  //CmiPsGetDefinedBearerCtxReq
    CMI_PS_GET_DEFINED_BEARER_CTX_CNF,  //CmiPsGetDefinedBearerCtxCnf


    /*
     * AT+CGDCONT=?, return directly in AtCmdSrv side, don't need to involved a new CMI
     * CMI_PS_GET_BEARER_CTX_CAPA_REQ, //AT+CGDCONT=?
     * CMI_PS_GET_BEARER_CTX_CAPA_CNF = 10,
    */

    /*
     * useless, please use: CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ
     * CMI_PS_GET_VACANCY_CIDS_REQ, //AT+CGVCID?, get vacant (not used) CID list
     * CMI_PS_GET_VACANCY_CIDS_CNF = 10,
     */

    /***********************************************************************
     * Define the NB attached bearer context, by:
     *  AT+CGDCONT=0,<pdp_type>, or
     *  AT$QCATTBEARER=<PDP_type>, ....
     **********************************************************************/
    CMI_PS_SET_ATTACHED_BEARER_CTX_REQ,         //CmiPsSetAttachedBearerCtxReq
    CMI_PS_SET_ATTACHED_BEARER_CTX_CNF = 10,    //CmiPsSetAttachedBearerCtxCnf
    CMI_PS_GET_ATTACHED_BEARER_CTX_REQ,     //CmiPsGetAttachedBearerCtxReq
    CMI_PS_GET_ATTACHED_BEARER_CTX_CNF,     //CmiPsGetAttachedBearerCtxCnf

    CMI_PS_SET_ATTACHED_AUTH_CTX_REQ,   //AT$QCATTAUTH=xxx,xxx, - TBD
    CMI_PS_SET_ATTACHED_AUTH_CTX_CNF,
    CMI_PS_GET_ATTACHED_AUTH_CTX_REQ,   //AT$QCATTAUTH?, -TBD
    CMI_PS_GET_ATTACHED_AUTH_CTX_CNF = 0x10,

    CMI_PS_DEFINE_DEDICATED_BEARER_CTX_REQ, //AT+CGDSCONT=<cid>,<p_cid>, ...,
    CMI_PS_DEFINE_DEDICATED_BEARER_CTX_CNF,
    CMI_PS_DEL_DEDICATED_BEARER_CTX_REQ,    //AT+CGDSCONT=<cid>,
    CMI_PS_DEL_DEDICATED_BEARER_CTX_CNF = 20,
    CMI_PS_GET_DEFINED_DEDICATED_BEARER_CTX_REQ, //AT+CGDSCONT?,
    CMI_PS_GET_DEFINED_DEDICATED_BEARER_CTX_CNF,

    /*
     * AT+CGDSCONT=?, return directly in AtCmdSrv side, don't need to involved a new CMI
     * CMI_PS_GET_DEDICATED_BEARER_CTX_CAPA_REQ, //AT+CGDSCONT=?
     * CMI_PS_GET_DEDICATED_BEARER_CTX_CAPA_CNF,
    */

    CMI_PS_SET_ATTACH_STATE_REQ,    //AT+CGATT, CmiPsSetAttachStateReq
    CMI_PS_SET_ATTACH_STATE_CNF,    //CmiPsSetAttachStateCnf
    CMI_PS_GET_ATTACH_STATE_REQ,    //AT+CGATT?, CmiPsGetAttachStateReq
    CMI_PS_GET_ATTACH_STATE_CNF,    //CmiPsGetAttachStateCnf
    CMI_PS_GET_ATTACH_STATE_CAPA_REQ,   //AT+CGATT=?, -TBD
    CMI_PS_GET_ATTACH_STATE_CAPA_CNF,

    CMI_PS_SET_BEARER_ACT_STATE_REQ,    //AT+CGACT, CmiPsSetBearerActStateReq
    CMI_PS_SET_BEARER_ACT_STATE_CNF = 30,   //CmiPsSetBearerActStateCnf

    /*
     * useless, please use: CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ
     * CMI_PS_GET_BEARER_ACT_STATE_REQ, //AT+CGACT?
     * CMI_PS_GET_BEARER_ACT_STATE_CNF,
     */

    CMI_PS_GET_BEARER_ACT_CAPA_REQ,     //AT+CGACT=?, -TBD
    CMI_PS_GET_BEARER_ACT_CAPA_CNF = 0x20,

    CMI_PS_MODIFY_BEARER_CTX_REQ,   //AT+CGCMOD, CmiPsModifyBearerCtxReq
    CMI_PS_MODIFY_BEARER_CTX_CNF,   //CmiPsModifyBearerCtxCnf

    /************************************************************************
     * Get CIDs associated with actived default & dedicated bearer
     * AT+CGCMOD=?
     * AT+CGTFTRDP=?
     * AT+CGEQOSRDP=?
     ************************************************************************/
    /*
     * Useless, please try: CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ
     * CMI_PS_GET_ACTED_BEARER_CIDS_REQ,
     * CMI_PS_GET_ACTED_BEARER_CIDS_CNF = 40,
    */
    CMI_PS_ENTER_DATA_STATE_REQ,    //AT+CGDATA, CmiPsEnterDataStateReq
    CMI_PS_ENTER_DATA_STATE_CNF,    //CmiPsEnterDataStateCnf

    CMI_PS_SET_PS_EVENT_REPORT_CFG_REQ,     //AT+CGEREP=[<mode>[,bfr]], -TBD
    CMI_PS_SET_PS_EVENT_REPORT_CFG_CNF,     //
    CMI_PS_GET_PS_EVENT_REPORT_CFG_REQ,     //AT+CGEREP? -TBD
    CMI_PS_GET_PS_EVENT_REPORT_CFG_CNF = 40,
    CMI_PS_GET_PS_EVENT_REPORT_CFG_CAPA_REQ, //AT+CGEREP=? -TBD
    CMI_PS_GET_PS_EVENT_REPORT_CFG_CAPA_CNF ,

    CMI_PS_DETACH_STATE_IND,    //+CGEV: xx DETACH, -TBD

    //+CGEV: ME PDN ACT <cid>
    //+CGEV: NW/ME ACT <p_cid>, <cid>, <event_type>
    CMI_PS_BEARER_ACTED_IND,    //+CGEV: ME PDN ACT <cid>, CmiPsBearerActedInd
    //CMI_PS_DEDICATED_BEARER_ACTED_IND, //+CGEV: NW/ME ACT <p_cid>, <cid>, <event_type>

    //+CGEV: NW/MS PDN DEACT <cid>
    //+CGEV: NW/ME DEACT <p_cid>,<cid>
    CMI_PS_BEARER_DEACT_IND,    //+CGEV: NW/MS PDN DEACT <cid>, CmiPsBearerDeActInd

    CMI_PS_BEARER_MODIFY_IND,   //+CGEV: NW/ME MODIFY <cid>, CmiPsBearerModifyInd

    //CMI_PS_SET_CEREG_MODE_REQ,  //AT+CEREG=<n>, CmiPsSetCeregModeReq
    //CMI_PS_SET_CEREG_MODE_CNF = 0x30,   //CmiPsSetCeregModeCnf
    CMI_PS_GET_CEREG_REQ,       //AT+CEREG? CmiPsGetCeregReq
    CMI_PS_GET_CEREG_CNF = 50,  //CmiPsGetCeregCnf
    CMI_PS_GET_CEREG_CAP_REQ,   //AT+CEREG=?, CmiPsGetCeregCapReq
    CMI_PS_GET_CEREG_CAP_CNF,   //CmiPsGetCeregCapCnf
    CMI_PS_CEREG_IND,   //+CEREG xxx, CmiPsCeregInd

    CMI_PS_READ_BEARER_DYN_CTX_REQ, //AT+CGCONTRDP=<cid>; CmiPsReadBearerDynCtxParamReq
    CMI_PS_READ_BEARER_DYN_CTX_CNF, //CmiPsReadBearerDynCtxParamCnf

    /*
     * Useless, please try: CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ
     * CMI_PS_GET_ACTED_DEFAULT_BEARER_CIDS_REQ, //AT+CGCONTRDP=?
     * CMI_PS_GET_ACTED_DEFAULT_BEARER_CIDS_CNF,
     */

    CMI_PS_READ_DEDICATED_BEARER_DYN_CTX_REQ, //AT+CGSCONTRDP, -TBD
    CMI_PS_READ_DEDICATED_BEARER_DYN_CTX_CNF,

    /*
     * Useless, please try: CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ
     * CMI_PS_GET_ACTED_DEDICATED_BEARER_CIDS_REQ, //AT+CGSCONTRDP=?
     * CMI_PS_GET_ACTED_DEDICATED_BEARER_CIDS_CNF,
     */

    CMI_PS_DEFINE_TFT_PARM_REQ, //AT+CGTFT=[<cid>, ...], CmiPsSetDefineTFTParamReq
    CMI_PS_DEFINE_TFT_PARM_CNF, //CmiPsSetDefineTFTParamCnf
    CMI_PS_GET_DEFINED_TFT_PARM_REQ = 60, //AT+CGTFT?, CmiPsGetDefineTFTParamReq
    CMI_PS_GET_DEFINED_TFT_PARM_CNF,    //CmiPsGetDefineTFTParamCnf
    CMI_PS_DELETE_TFT_PARM_REQ, //CmiPsDelTFTParamReq
    CMI_PS_DELETE_TFT_PARM_CNF, //CmiPsDelTFTParamCnf

    /*
     * AT+CGTFT=?, AtCmdSrv return directly
     * CMI_PS_GET_TFT_SETTING_PARA_CAPA_REQ, // FFU, not support now
     * CMI_PS_GET_TFT_SETTING_PARA_CAPA_CNF,
    */

    CMI_PS_READ_DYN_TFT_CTX_REQ = 0x40, //AT+CGTFTRDP[=<cid>], -TBD
    CMI_PS_READ_DYN_TFT_CTX_CNF,

    CMI_PS_DEFINE_EPS_QOS_REQ,      //AT+CGEQOS=<cid>,<QCI>,..., CmiPsDefineEpsQoSReq
    CMI_PS_DEFINE_EPS_QOS_CNF,      //CmiPsDefineEpsQoSCnf
    CMI_PS_DEL_DEFINE_EPS_QOS_REQ,  //CmiPsDelEpsQosReq
    CMI_PS_DEL_DEFINE_EPS_QOS_CNF,  //CmiPsDelEpsQosCnf
    CMI_PS_GET_DEFINED_EPS_QOS_REQ = 70, //AT+CEQOS?, CmiPsGetDefinedEpsQoSReq, get current settings of each defined QOS, note here, not activated EPS QOS
    CMI_PS_GET_DEFINED_EPS_QOS_CNF, //CmiPsGetDefinedEpsQoSCnf
    CMI_PS_GET_EPS_QOS_SETTING_CAPA_REQ, //AT+CEQOS=? -TBD
    CMI_PS_GET_EPS_QOS_SETTING_CAPA_CNF,

    CMI_PS_READ_DYN_BEARER_EPS_QOS_REQ, //AT+CGEQOSRDP[=<cid>], CmiPsReadDynEpsQoSReq
    CMI_PS_READ_DYN_BEARER_EPS_QOS_CNF, //CmiPsReadDynEpsQoSCnf

    CMI_PS_DEL_NON_ACT_BEARER_CTX_REQ, //AT+CGDEL[=<cid>] //seems just the same as CGDCONT=<cid>, CGDSCONT=<cid>, -TBD
    CMI_PS_DEL_NON_ACT_BEARER_CTX_CNF,

    CMI_PS_DEFINE_AUTH_CTX_REQ,     //AT+CGAUTH=<cid>,<auth_proto>,[<userid>,<password>]
    CMI_PS_DEFINE_AUTH_CTX_CNF,
    CMI_PS_GET_DEFINED_AUTH_CTX_REQ = 80, //AT+CGAUTH?
    CMI_PS_GET_DEFINED_AUTH_CTX_CNF = 0x51,
    CMI_PS_GET_AUTH_CTX_CAPA_REQ,   //AT+CGAUTH=?
    CMI_PS_GET_AUTH_CTX_CAPA_CNF,


    CMI_PS_SET_ATTACH_WITH_OR_WITHOUT_PDN_REQ,  //AT+CIPCA, CmiPsSetAttachWithOrWithoutPdnReq
    CMI_PS_SET_ATTACH_WITH_OR_WITHOUT_PDN_CNF,  //CmiPsSetAttachWithOrWithoutPdnCnf
    CMI_PS_GET_ATTACH_WITH_OR_WITHOUT_PDN_REQ,  //AT+CIPCA? CmiPsGetAttachWithOrWithoutPdnReq
    CMI_PS_GET_ATTACH_WITH_OR_WITHOUT_PDN_CNF,  //CmiPsSetAttachWithOrWithoutPdnCnf

    CMI_PS_NO_MORE_PS_DATA_REQ,     //CmiPsNoMorePsDataReq
    CMI_PS_NO_MORE_PS_DATA_CNF,     //CmiPsNoMorePsDataCnf

    CMI_PS_SEND_CP_DATA_REQ = 90,   //AT+CSODCP, CmiPsSendOriDataViaCpReq
    CMI_PS_SEND_CP_DATA_CNF,        //CmiPsSendOriDataViaCpCnf

    CMI_PS_SET_MT_CP_DATA_REPORT_CFG_REQ, //AT+CRTDCP=<reporting>
    CMI_PS_SET_MT_CP_DATA_REPORT_CFG_CNF,
    CMI_PS_GET_MT_CP_DATA_REPORT_CFG_REQ, //AT+CRTDCP?
    CMI_PS_GET_MT_CP_DATA_REPORT_CFG_CNF,
    CMI_PS_GET_MT_CP_DATA_REPORT_CAPA_REQ = 0x60, //AT+CRTDCP=?
    CMI_PS_GET_MT_CP_DATA_REPORT_CAPA_CNF,

    CMI_PS_MT_CP_DATA_IND, //+CRTDCP:<cid>,<cpdata_length>,<cpdata>

    CMI_PS_GET_APN_RATE_CTRL_PARM_REQ, //AT+CGAPNRC, CmiPsGetAPNRateCtrlReq
    CMI_PS_GET_APN_RATE_CTRL_PARM_CNF = 100,    //CmiPsGetAPNRateCtrlCnf

    CMI_PS_GET_BEARER_IPADDR_REQ,   //AT+CGPADDR = <cid1>[,<cid2>], CmiPsGetBearerIpAddrReq
    CMI_PS_GET_BEARER_IPADDR_CNF,   //CmiPsGetBearerIpAddrCnf

    /*
     * AT$QCSENDDATA=<cid>,<data_length>,<data>[,<RAI>[,<type_of_user_data>]]
     * Note:
     * 1> User could send non-ip/ip data via this AT CMD;
     * 2> Not the same as: +CSODCP,
     *    AT$QCSENDDATA: could send data via CP or UP
     *    AT+CSODCP:   only send the data via CP
    */
    CMI_PS_SEND_UL_DATA_REQ,    //AT$QCSENDDATA=<cid>,<data_length>,<data>[,<RAI>[,<type_of_user_data>]], CmiPsSendUlDataReq
    CMI_PS_SEND_UL_DATA_CNF,    //CmiPsSendUlDataCnf

    /*
     * for NON-IP data, just foward to AT CMD SRV UART
    */
    CMI_PS_RECV_DL_NON_IP_DATA_IND, //+RECVNONIP: <cid>,<data_length>,<data> , CmiPsRecvDlNonIpDataInd

    CMI_PS_TRANS_CIOT_PLANE_REQ,    //AT$QCCIOTPLANE=plane, to select CP or UP, CmiPsTransCiotPlaneReq
    CMI_PS_TRANS_CIOT_PLANE_CNF,    //CmiPsTransCiotPlaneCnf

    CMI_PS_GET_CONN_STATUS_REQ,     //CmiPsGetConnStatusReq, AT+CSCON?
    CMI_PS_GET_CONN_STATUS_CNF,     //CmiPsGetConnStatusCnf

    CMI_PS_CONN_STATUS_IND = 110,   //CmiPsConnStatusInd, +CSCON: <mode>

	CMI_PS_SET_QC_APN_CLASS_CFG_REQ, //AT$QCPDPCFGE
	CMI_PS_SET_QC_APN_CLASS_CFG_CNF,

    CMI_PS_GET_BEARER_PKT_STATS_REQ, // CmiPsGetBearerPktStatsReq
    CMI_PS_GET_BEARER_PKT_STATS_CNF,  // CmiPsGetBearerPktStatsCnf
    //AT+CABTSR / AT+CABTRDP, -TBD

	CMI_PS_GET_PLMN_RATE_CTRL_PARM_REQ,
    CMI_PS_GET_PLMN_RATE_CTRL_PARM_CNF,
	
	CMI_PS_GET_APN_DISABLE_SYNC_STATUS_REQ = 120,
	CMI_PS_GET_APN_DISABLE_SYNC_STATUS_CNF,
    CMI_PS_GET_CEER_REQ,             //CmiPsGetCeerReq, AT+CEER
    CMI_PS_GET_CEER_CNF,             //CmiPsGetCeerCnf

	CMI_PS_SET_APN_DISABLE_SYNC_STATUS_REQ,
	CMI_PS_SET_APN_DISABLE_SYNC_STATUS_CNF,

	CMI_PS_GET_ESM_CAUSE_REQ, //AT$QCESMCAUSE
	CMI_PS_GET_ESM_CAUSE_CNF,

	CMI_PS_READ_BEARER_DYNS_CTX_REQ, //AT$QCGCONTRDP=<cid>
    CMI_PS_READ_BEARER_DYNS_CTX_CNF, 

	//AT$QCGCONTRDP
	CMI_PS_GET_ALL_BEARERS_CID_INFO_REQ,  
    CMI_PS_GET_ALL_BEARERS_CID_INFO_CNF,   

    CMI_PS_PRIM_END = 0x0fff
}CMI_PS_PRIM_ID;


typedef enum CmiPsBearerTypeTag
{
    CMI_PS_BEARER_NULL,
    CMI_PS_BEARER_DEFAULT,
    CMI_PS_BEARER_DEDICATED,
    CMI_PS_BEARER_MAX_TYPE
}CmiPsBearerType;

/*
 * CGEV reason
 * <reason>: integer type; indicates the reason why the context activation request for PDP type IPv4v6 was not
 *   granted. This parameter is only included if the requested PDP type associated with <cid> is IPv4v6, and the
 *   PDP type assigned by the network for <cid> is either IPv4 or IPv6.
 * 0 IPv4 only allowed
 * 1 IPv6 only allowed
 * 2 single address bearers only allowed.
 * 3 single address bearers only allowed and MT initiated context activation for a second address type bearer was
 *   not successful.
*/
typedef enum CmiPsPdnTypeReasonTag
{
    CMI_PS_IPV4_ONLY_ALLOWED,
    CMI_PS_IPV6_ONLY_ALLOWED,
    CMI_PS_SINGLE_ADDR_BEARER_ONLY_ALLOWED,
    CMI_PS_SINGLE_ADDR_ONLY_ALLOWED_BUT_ACTIVE_SECOND_BEARER_FAILED,    // - NOT support now
    CMI_PS_PDN_TYPE_REASON_NULL  //indicate no reason
}CmiPsPdnTypeReason;

/*
 * TS27007 10.1.1, only IPv4, IPv6 and IPv4v6 values are supported for EPS service.
*/
typedef enum CmiPsPdnTypeTag
{
    //CMI_PS_PDN_TYPE_PPP = 0,  /* PPP */
    CMI_PS_PDN_TYPE_IP_V4 = 1,  /* IPv4 */
    CMI_PS_PDN_TYPE_IP_V6,      /* IPv6 */
    CMI_PS_PDN_TYPE_IP_V4V6,    /* IPv4v6 */
    //CMI_PS_PDN_TYPE_X25,      /* X.25 */
    //CMI_PS_PDN_TYPE_OSPIH,    /* OSPIH */
    CMI_PS_PDN_TYPE_NON_IP =5,     /* NON IP*/
    CMI_PS_PDN_TYPE_NUM
}CmiPsPdnType;

/*
 *  Authentication protocol used for this PDP context
*/
typedef enum CmiSecurityProtocolTag
{
    CMI_SECURITY_PROTOCOL_NULL = 0,  /*null*/
    CMI_SECURITY_PROTOCOL_PAP = 1,   /*PAP*/
	CMI_SECURITY_PROTOCOL_PPP_LCP_PAP   = 13,   /* AUTH info extract from PPP LCP AUTH info, which type is PAP,
                                                 * difference with: CMI_SECURITY_PROTOCOL_PAP:
                                                 * a) "PPP_LCP_PAP" not need to save NVM, and when PDP activated/deactivated could remove.
                                                 * b) "PPP_LCP_PAP" not need to return in "CmiPsGetDefineAuthCtxCnf", when read the AUTH info
                                                */
    CMI_SECURITY_PROTOCOL_PPP_LCP_CHAP  = 14,   /* AUTH info extract from PPP LCP AUTH info, which type is CHAP,
                                                 * difference with: CMI_SECURITY_PROTOCOL_CHAP:
                                                 * a) "PPP_LCP_CHAP" not need to save NVM, and when PDP activated/deactivated could remove.
                                                 * b) "PPP_LCP_CHAP" not need to return in "CmiPsGetDefineAuthCtxCnf", when read the AUTH info.
                                                 * c) auth info is not username/paaword, but encoded CHAP challenge and CHAP response info.                                                */
    CMI_SECURITY_PROTOCOL_NUM   = 0xF   /* 4 bits */
}CmiSecurityProtocol;


typedef enum CmiPsBearerStateTag
{
    CMI_PS_BEARER_INVALID       = 0,
    CMI_PS_BEARER_DEFINED       = 1,
    CMI_PS_BEARER_ACTIVATING    = 2,
    CMI_PS_BEARER_ACTIVATED     = 3,
    CMI_PS_BEARER_MODIFING      = 4,
    CMI_PS_BEARER_DEACTIVATING  = 5,
    CMI_PS_BEARER_MAX_STATE
}CmiPsBearerState;

typedef enum CmiPsIpv4AllocTypeTag
{
    CMI_IPV4_ADDR_ALLOC_THROUGH_NAS_SIGNALNG,
    CMI_IPV4_ADDR_ALLOC_THROUGH_DHCP
}CmiPsIpv4AllocType;

typedef enum CmiPsPcscfDiscoveryTypeTag
{
    CMI_PS_PCSCF_ADDR_DISCOVERY_NOT_INFLUENCED_BY_CGDCONT,
    CMI_PS_PCSCF_ADDR_DISCOVERY_THROUGH_NAS_SIGNALNG,
    CMI_PS_PCSCF_ADDR_DISCOVERY_THROUGH_DHCP
}CmiPsPcscfDiscoveryType;

typedef enum CmiPsIpv4MtuDiscoveryTypeTag
{
    CMI_IPV4_ADDR_MTU_SIZE_DISCOVERY_NOT_INFLUENCED_BY_CGDCONT,
    CMI_IPV4_ADDR_MTU_SIZE_DISCOVERY_THROUGH_NAS_SIGNALNG
}CmiPsIpv4MtuDiscoveryType;


typedef enum CmiPsNonIpMtuDiscoveryTypeTag
{
    CMI_PS_NONIP_MTU_SIZE_DISCOVERY_NOT_INFLUENCED_BY_CGDCONT,
    CMI_PS_NONIP_MTU_SIZE_DISCOVERY_THROUGH_NAS_SIGNALNG
}CmiPsNonIpMtuDiscoveryType;

/*
 * request_type, 27.007
 * 0 PDP context is for new PDP context establishment or for handover from a non-3GPP access network (how
 *   the MT decides whether the PDP context is for new PDP context establishment or for handover is
 *   implementation specific)
 * 1 PDP context is for emergency bearer services
 * 2 PDP context is for new PDP context establishment
 * 3 PDP context is for handover from a non-3GPP access network
 * 4 PDP context is for handover of emergency bearer services from a non-3GPP access networ
*/
typedef enum CmiPsBearerReqTypeTag
{
    CMI_PS_NEW_BEARER_NO_KNOWN_REQ = 0,
    CMI_PS_EMERGENCY_BEARER_REQ = 1,    //not support
    CMI_PS_NEW_BEARER_REQ = 2,
    CMI_PS_HO_BEARER_REQ  = 3,          //not support
    CMI_PS_HO_EMERGENCY_BEARER_REQ = 4  //not support
}CmiPsBearerReqType;

/*
 * IM_CN_Signalling_Flag, 27.007
 * 0 UE indicates that the PDP context is not for IM CN subsystem-related signalling only
 * 1 UE indicates that the PDP context is for IM CN subsystem-related signalling only
*/
typedef enum CmiPsImCnSigFlagTag
{
    CMI_PS_BEARER_NOT_FOR_IM_CN_SIG_ONLY = 0,
    CMI_PS_BEARER_FOR_IM_CN_SIG_ONLY
}CmiPsImCnSigFlag;

/*
 * NSLPI, 27.007
 * <NSLPI>: integer type; indicates the NAS signalling priority requested for this PDP context:
 * 0 indicates that this PDP context is to be activated with the value for the low priority indicator configured in the MT.
 * 1 indicates that this PDP context is is to be activated with the value for the low priority indicator set to "MS is not configured for NAS signalling low priority".
*/
typedef enum CmiPsNSLPICfgTag
{
    CMI_PS_CFG_FOR_NSLPI = 0,
    CMI_PS_NOT_CFG_FOR_NSLPI
}CmiPsNSLPICfg;


#define CMI_PS_IS_BEARER_ACTIVTED(cmiPsBrState)   (((cmiPsBrState) == CMI_PS_BEARER_ACTIVATED) || ((cmiPsBrState) == CMI_PS_BEARER_MODIFING))
#define CMI_PS_IS_BEARER_INVALID(cmiPsBrState)    (((cmiPsBrState) == CMI_PS_BEARER_INVALID) || ((cmiPsBrState) >= CMI_PS_BEARER_MAX_STATE))


/******************************************************************************
 *****************************************************************************
 * CMI STRUCT
 *****************************************************************************
******************************************************************************/

typedef struct CmiNumericRange_struct
{
    UINT16    min;
    UINT16    max;
}CmiNumericRange;


typedef struct DefineBearerCtxInfoTag
{
    UINT8   cid;
    UINT8   pdnType;        //CmiPsPdnType
    UINT8   reserved0;
    UINT8   apnLength;      /* 0 - apn is not present */
    UINT8   apnStr[CMI_PS_MAX_APN_LEN];//apn string

    /* "PDP_addr" is ignored with the set command */
    /* "d_comp" & "h_comp" is for 2/3G, don't need */

    BOOL    ipv4AlloTypePresent;
    UINT8   ipv4AlloType;   /* CmiPsIpv4AllocType. IPv4 address allocation through NAS signalling, or by DHCP */

    BOOL    reqTypePresent;
    UINT8   reqType;        /*CmiPsBearerReqType */

    BOOL    NSLPIPresent;
    UINT8   NSLPI;          /*CmiPsNSLPICfg, NAS signalling priority*/

    BOOL    ipv4MtuDisTypePresent;
    BOOL    ipv4MtuDisByNas;    /* IPv4 MTU size discovery through NAS signalling */

    BOOL    nonIpMtuDisTypePresent;
    BOOL    nonIpMtuDisByNas;   /* Non-IP MTU size discovery through NAS signalling*/

    BOOL    RDSPresent;
    UINT8   RDS;            /*0-Reliable Data Service is not being used for the PDN connection;1-Reliable Data Service is being used for the PDN connection*/


    //UINT16  reserved1;

    /*
     * <securePCO>, not support now (PAP/CHAP)
    */

    /*
     * <Local_Addr_Ind>, not support now
     * "local IP address in TFT"
    */

    /*
     * IMS/pcscf not support now
    */
    BOOL    pcscfDisTypePresent;
    UINT8   pcscfDisType;   //CmiPsPcscfDiscoveryType

    BOOL    imCnSigFlagPresent;
    UINT8   imCnSigFlag;    //CmiPsImCnSigFlag
    BOOL    device_wakeup;
}DefineBearerCtxInfo;


typedef struct CmiPsBearerCtxDynParamTag
{
    UINT8               cid; // context Id
    UINT8               bid; // bearer Id
    UINT8               reserved0;
    UINT8               apnLength;          /* 0 - apn is not present */
    UINT8               apnStr[CMI_PS_MAX_APN_LEN];//apn string
    CmiIpAddr           ipv4Addr;   // if bearer is non-ip type, ipv4Addr/ipv6Addr both invalid
    CmiIpAddr           ipv6Addr;
    CmiIpAddr           gwIpv4Addr;

    UINT8               dnsAddrNum;
    UINT8               pCscfAddrNum;
    UINT8               imCnSigFlag;  //0, 1
    UINT8               lipaInd;      //0, 1;

    CmiIpAddr           dnsAddr[CMI_PDN_MAX_NW_ADDR_NUM];
    CmiIpAddr           pCscfAddr[CMI_PDN_MAX_NW_ADDR_NUM];

    BOOL                ipv4MtuPresent;
    UINT16              ipv4Mtu;
    BOOL                nonIpMtuPresent;
    UINT16              nonIpMtu;
    //UINT16              servingPlmnRateCtrl;
    BOOL                needRetryAnotherIPType;//retry another IP type bearer needed;

}CmiPsBearerCtxDynParam;    //312 bytes

typedef struct CmiPsDedBearerCtxDynParamTag
{
    UINT8               cid; // context Id
    UINT8               pCid;//
    UINT8               bid; // bearer Id
    UINT8               imCnSigFlag;  //0, 1
}CmiPsDedBearerCtxDynParam;


/*
 * CMI_PS_DEFINE_BEARER_CTX_REQ
 *  AT+CGDCONT=[<cid>[,<PDP_type>[,<APN>[,<PDP_addr>[,<d_comp>
 *             [,<h_comp>[,<IPv4AddrAlloc>[,<request_type>[,<PCSCF_discovery>
 *             [,<IM_CN_Signalling_Flag_Ind>[,<NSLPI>[,<securePCO>[,<IPv4_MTU_discovery>]
 *             [,<Local_Addr_Ind>][,<NonIP_MTU_discovery>]]]]]]]]]]]]]
*/
typedef struct CmiPsDefineBearerCtxReqTag
{
    DefineBearerCtxInfo          bearerCtxInfo;
}CmiPsDefineBearerCtxReq;


/*
 * CMI_PS_DEFINE_BEARER_CTX_CNF 
*/

typedef struct CmiPsDefineBearerCtxCnfTag
{
    UINT8 cid;
	UINT8 reserved0;
	UINT16 reserved1;
}CmiPsDefineBearerCtxCnf;

/*
 * CMI_PS_GET_DEFINED_BEARER_CTX_REQ
*/
typedef struct CmiPsGetDefinedBearerCtxReqTag
{
    BOOL    bAllCid;    //whether get all defined bearer context info
    UINT8   cid;        //if "bAllCid" == FALSE, specified one CID
    UINT16  reserved1;
}CmiPsGetDefinedBearerCtxReq;

/*
 * CMI_PS_GET_DEFINED_BEARER_CTX_CNF
 * +CGDCONT: <cid>,<PDP_type>,<APN>,<PDP_addr>,<d_comp>,<h_comp>
 *           [,<IPv4AddrAlloc>[,<request_type>[,<PCSCF_discovery>
 *           [,<IM_CN_Signalling_Flag_Ind>[,<NSLPI>[,<securePCO>
 *           [,<IPv4_MTU_discovery>[,<Local_Addr_Ind>[,<NonIP_MTU_discovery>]]]]]]]]]
*/
typedef struct CmiPsDefineBearerCtxTag
{
    UINT8   cid;
    UINT8   bearerState;    //CmiPsBearerState
    UINT8   pdnType;        //CmiPsPdnType
    UINT8   apnLength;      /* 0 - apn is not present */
    UINT8   apnStr[CMI_PS_MAX_APN_LEN];//apn string

    /* <PDP_addr> */
    CmiIpAddr   ipv4Addr; // if bearer is non-ip type, ipv4Addr/ipv6Addr both invalid
    CmiIpAddr   ipv6Addr;

    /*
     * <d_comp>,<h_comp> is used for 2/3G;
     * default value is 0 - off in AT CMD SRV
    */
    BOOL    ipv4AddrAllocPresent;
    UINT8   ipv4AlloType;   /* CmiPsIpv4AllocType. IPv4 address allocation through NAS signalling, or by DHCP */
    BOOL    reqTypePresent;
    UINT8   reqType;        /*CmiPsBearerReqType */

    /*
     * IMS/pcscf not support now, set to 0
    */
    BOOL    pCscfDiscoveryPresent;
    UINT8   pcscfDisType;   //CmiPsPcscfDiscoveryType
    BOOL    imCnSigFlagPresent;
    UINT8   imCnSigFlag;    //CmiPsImCnSigFlag

    BOOL    NSLPIPresent;
    UINT8   NSLPI;          /*CmiPsNSLPICfg, NAS signalling priority*/

    /*<securePCO> is not support now, default 0 - Security protected transmission of PCO is not requested */

    /*
     * <Local_Addr_Ind>, not support now
     * "local IP address in TFT", default value 0 - MS does not support local IP address in TFTs
    */
    BOOL    ipv4MTUDiscoveryPresent;
    BOOL    ipv4MtuDisByNas;    /* IPv4 MTU size discovery through NAS signalling */

    BOOL    nonIpMtuDiscoveryPresent;
    BOOL    nonIpMtuDisByNas;   /* Non-IP MTU size discovery through NAS signalling*/

    UINT16  reserved0;
}CmiPsDefinedBearerCtx;

typedef struct CmiPsGetDefinedBearerCtxCnfTag
{
    /*
     * AT+CGDCONT? is to query all the defined PDP info, in order to reduce the struct size,
     * Each time return one bearer info;
    */
    BOOL    bContinue;
    BOOL    bCtxValid;  /*whether 'definedBrCtx' is valid*/
    UINT16  reserved1;
    CmiPsDefinedBearerCtx    definedBrCtx;
}CmiPsGetDefinedBearerCtxCnf;


/*
 * CMI_PS_DEL_BEARER_CTX_REQ
*/
typedef struct CmiPsDelBearerCtxReqTag
{
    UINT8           cid;
    UINT8           reserved;
    UINT16          reserved2;
}CmiPsDelBearerCtxReq;


/*
 * CMI_PS_DEL_BEARER_CTX_CNF
*/
typedef CacCmiEmptySig  CmiPsDelBearerCtxCnf;



/*
* CMI_PS_DEFINE_DEDICATED_BEARER_CTX_REQ
* +CGDSCONT=[<cid>,<p_cid>[,<d_comp>[,<h_comp>[,<IM_CN_Signalling_Flag_Ind>]]]]
*
*/

typedef struct CmiPsDedicateBearerCtxReqTag
{
    UINT8   cid;
    UINT8   pCid;        //primary cid,  The list of permitted values is returned by the test form of the command.
    /*
     * <d_comp>,<h_comp> is used for 2/3G;
     * default value is 0 - off in AT CMD SRV
    */

    BOOL    imCnSigFlagPresent;
    UINT8   imCnSigFlag;    //CmiPsImCnSigFlag

}CmiPsDedicateBearerCtxReq;

/*
 * CMI_PS_DEFINE_DEDICATED_BEARER_CTX_CNF
*/
typedef CacCmiEmptySig CmiPsDefineDedicateBearerCtxCnf;

/*
* CMI_PS_DEL_DEDICATED_BEARER_CTX_REQ
*/
typedef struct CmiPsDelDedBearerCtxReqTag
{
    UINT8           cid;
    UINT8           reserved;
    UINT16          reserved2;
}CmiPsDelDedBearerCtxReq;

/*
* CMI_PS_DEL_DEDICATED_BEARER_CTX_CNF
*/
typedef CacCmiEmptySig  CmiPsDelDedBearerCtxCnf;


/*
 * CMI_PS_GET_DEFINED_DEDICATED_BEARER_CTX_REQ
*/
typedef struct CmiPsGetDedicateBearerCtxReqTag
{
    BOOL    bAllCid; //whether get all defined bearer context info
    UINT8   cid;    //if "bAllCid" == FALSE, specified one CID
    UINT16  reserved1;
}CmiPsGetDedicateBearerCtxReq;

/*
 * CMI_PS_GET_DEFINED_DEDICATED_BEARER_CTX_CNF
 * [+CGDSCONT: <cid>,<p_cid>,<d_comp>,<h_comp>,<IM_CN_Signalling_Flag_Ind>]
*/

typedef struct CmiPsGetDefinedDedBearerCtxCnfTag
{
    UINT8   cid;
    UINT8   pCid;
    BOOL    imCnSigFlagPresent;
    UINT8   imCnSigFlag;    //CmiPsImCnSigFlag
}CmiPsGetDefinedDedBearerCtxCnf;


/*
 * CMI_PS_SET_BEARER_ACT_STATE_REQ
*/
typedef struct CmiPsSetBearerActStateReqTag
{
    UINT8           cid;
    UINT8           state; //indicates the state of bearer context activation. 1--activated; 0 - deactivated
    UINT16          reserved;
}CmiPsSetBearerActStateReq;

/*
 * CMI_PS_SET_BEARER_ACT_STATE_CNF
*/
typedef struct CmiPsSetBearerActStateCnfTag
{
	UINT32 result;
}CmiPsSetBearerActStateCnf;



/*
 * CMI_PS_BEARER_ACTED_IND ,
 * default pdn //pCid=0, bearerType=CMI_PS_BEARER_DEFAULT
 * +CGEV: NW PDN ACT <cid>
 * +CGEV: ME PDN ACT <cid>[,<reason>,...

 * dedicate pdn //<pCid> should exist, <bearerType> should be CMI_PS_BEARER_DEDICATED, <event_type>: only support: 0 Informational event
 * +CGEV: NW ACT <p_cid>, <cid>, <event_type>
 * +CGEV: ME ACT <p_cid>, <cid>, <event_type>
*/

typedef struct CmiPsBearerActedIndTag
{
    UINT8          cid;
    UINT8          pCid;        // the associated primary cid,if not equal to 0, bearerType should be CMI_PS_BEARER_DEDICATED;
    UINT8          bearerType;  //CmiPsBearerType
    BOOL           isMeInitial; /* indicate the bearer activation is intialed by ME(TRUE) or NW(FALSE) */
    UINT8          pdnReason;   //CmiPsPdnTypeReason
    UINT8          reserved1;
    UINT16         reserved2;
}CmiPsBearerActedInd;


/*
 * CMI_PS_BEARER_MODIFY_IND ,
 * +CGEV: NW MODIFY <cid>, <change_reason>, <event_type>[,<WLAN_Offload>]
 * +CGEV: ME MODIFY <cid>, <change_reason>, <event_type>[,<WLAN_Offload>]
 * Note:
 *  <change_reason>: TFT changed/Qos changed
 *  <event_type>: only support: 0 Informational event
*/

/* bitmap that indicates what kind of change occurred */
typedef enum CmiPsBearerModifyReason_enum
{
    /*
     * Bit 1 TFT changed
     * Bit 2 Qos changed
     * Bit 1&2, TFT and Qos changed
    */
    CMI_PS_NONE_CHANGED,
    CMI_PS_TFT_CHANGED,
    CMI_PS_QOS_CHANGED,
    CMI_PS_TFT_AND_QOS_CHANGED
}CmiPsBearerModifyReason;

typedef struct CmiPsBearerModifyIndTag
{
    UINT8           cid;
    BOOL            bUeInited;  /*whether UE init this modification procedure*/
    UINT8           changeReasonBitmap; //bit map of "CmiPsBearerModifyReason"
    UINT8           rsvd;
}CmiPsBearerModifyInd;


/*
 * CMI_PS_BEARER_DEACT_IND ,
 * default pdn //pCid=0, bearerType=CMI_PS_BEARER_DEFAULT
 * +CGEV: NW PDN DEACT <cid>  //network init
 * +CGEV: ME PDN DEACT <cid>  //UE init

 * dedicate pdn //<pCid> should exist, <bearerType> should be CMI_PS_BEARER_DEDICATED, <event_type>: only support: 0 Informational event
 * +CGEV: NW DEACT <p_cid>, <cid>, <event_type>
 * +CGEV: ME DEACT <p_cid>, <cid>, <event_type>
*/

typedef struct CmiPsBearerDeActIndTag
{
    UINT8           cid;
    UINT8           pCid;  // the associated primary cid,if not equal to 0, bearerType should be CMI_PS_BEARER_DEDICATED;
    UINT8           bearerType; //CmiPsBearerType
    BOOL            isMeInitial; /* indicate the bearer activation is intialed by ME(TRUE) or NW(FALSE) */
    UINT16          cause;
    UINT8           reserved1;
    UINT8           reserved2;
}CmiPsBearerDeActInd;


/*
 * CMI_PS_DEFINE_EPS_QOS_REQ
 * AT+CGEQOS=[<cid>[,<QCI>[,<DL_GBR>,<UL_GBR>[,<DL_MBR>,<UL_MBR]]]]
*/
typedef struct CmiPsEpsQosParamsTag
{
    UINT8               cid;
    UINT8               qci;
    BOOL                gbrMbrPresent;  /* indicate the present of GBR/MBR, need two BOOL ? */
    UINT8               reserved0;
    UINT32              ulMBR;          /* UL_MBR, kbit/s */
    UINT32              dlMBR;          /* DL_MBR, kbit/s */
    UINT32              ulGBR;          /* UL_GBR, kbit/s */
    UINT32              dlGBR;          /* DL_GBR, kbit/s */
}CmiPsEpsQosParams; //20 bytes

typedef struct CmiPsDefineEpsQoSReqTag
{
    CmiPsEpsQosParams   epsQosParam;
}CmiPsDefineEpsQoSReq;

/*
 * CMI_PS_DEFINE_EPS_QOS_CNF
*/
typedef CacCmiEmptySig CmiPsDefineEpsQoSCnf;

/*
 * CMI_PS_DEL_DEFINE_EPS_QOS_REQ
*/
typedef struct CmiPsDelEpsQosReq_Tag
{
    UINT8    cid;
}CmiPsDelEpsQosReq;


/*
 * CMI_PS_DEL_DEFINE_EPS_QOS_CNF
*/
typedef CacCmiEmptySig CmiPsDelEpsQosCnf;

/*
 * CMI_PS_GET_DEFINED_EPS_QOS_REQ
*/
typedef struct CmiPsGetDefinedEpsQoSReqTag
{
    BOOL        bAllCid;    /* return all BERRER EQOS info*/
    UINT8       cid;
    UINT16      reserved2;
}CmiPsGetDefinedEpsQoSReq;

/*
 * CMI_PS_GET_DEFINED_EPS_QOS_CNF
*/
typedef struct CmiPsGetDefinedEpsQoSCnfTag
{
    //UINT8   epsQosNum;
    //UINT8   reserved0;
    //UINT16  reserved1;
    /*
     * AT+CGEQOS? need to return all defined QoS.
     * As PS each time could only return one EQOS info, here use "bContinue" to decide any EQOS followed
    */
    BOOL        bContinue;
    BOOL        epsQosValid;
    UINT16      reserved0;
    CmiPsEpsQosParams   epsQosParam;
}CmiPsGetDefinedEpsQoSCnf;

/*
 * CMI_PS_READ_DYN_BEARER_EPS_QOS_REQ
 * AT+CGEQOSRDP[=<cid>]
*/
typedef struct CmiPsReadDynEpsQoSReqTag
{
    BOOL        bAllCid;
    UINT8       cid;    /* if "bAllCid" == FALSE */
    UINT16      reserved1;
}CmiPsReadDynEpsQoSReq;

/*
 * <cid>,<QCI>,[<DL_GBR>,<UL_GBR>],[<DL_MBR>,<UL_MBR>][,<DL_AMBR>,<UL_AMBR>]
*/
typedef struct CmiPsEpsQosDynParamsTag
{
    UINT8       cid;
    UINT8       qci;
    UINT16      gbrPresent : 1; /* indicate the present of GBR */
    UINT16      mbrPresent : 1; /* indicate the present of MBR */
    UINT16      ambrPresent: 1; /* indicate the present of AMBR */
    UINT16      reserved0 : 13;

    UINT32      ulGBR;          /* UL_GBR, kbit/s */
    UINT32      dlGBR;          /* DL_GBR, kbit/s */
    UINT32      ulMBR;          /* UL_MBR, kbit/s */
    UINT32      dlMBR;          /* DL_MBR, kbit/s */
    UINT32      ulAMBR;
    UINT32      dlAMBR;
}CmiPsEpsQosDynParams; //28 bytes

/*
 * CMI_PS_READ_DYN_BEARER_EPS_QOS_CNF
*/
typedef struct CmiPsReadDynEpsQoSCnfTag
{
    /*
     * AT+CGEQOSRDP need to return all bearer configed/activated EQOS.
     * As PS each time could only return one EQOS info, here use "bContinue" to decide any EQOS followed
    */
    BOOL        bContinue;
    BOOL        epsQosValid;
    UINT16      reserved0;
    CmiPsEpsQosDynParams    epsQosDynParams;
}CmiPsReadDynEpsQoSCnf;


/*
 * CMI_PS_READ_BEARER_DYN_CTX_REQ
 * AT+CGCONTRDP? / AT+CGCONTRDP=<cid>
*/
typedef struct CmiPsReadBearerDynCtxParamReqTag
{
    BOOL        bAllCid;    //whether request all actived default bearer info
    UINT8       cid;        //if "bAllCid" == FALSE, get specified default bearer info;
    UINT16      reserved1;
}CmiPsReadBearerDynCtxParamReq;

/*
 * CMI_PS_READ_BEARER_DYN_CTX_CNF
*/
typedef struct CmiPsReadBearerDynCtxParamCnfTag
{
    /*
     * AT+CGCONTRDP? is to query all the actived default bearer info, in order to reduce the struct size,
     * Each time return one bearer info;
    */
    BOOL                    bContBearer;
    BOOL                    bearerCtxPresent;
    UINT16                  reserved0;

    CmiPsBearerCtxDynParam  ctxDynPara;
}CmiPsReadBearerDynCtxParamCnf;

/*
 * CMI_PS_READ_DEDICATED_BEARER_DYN_CTX_REQ
 * AT+CGSCONTRDP?
*/
typedef struct CmiPsReadDedBearerDynCtxParamReqTag
{
    BOOL        bAllCid;    //whether request all actived default bearer info
    UINT8       cid;        //if "bAllCid" == FALSE, get specified default bearer info;
    UINT16      reserved1;
}CmiPsReadDedBearerDynCtxParamReq;


/*
 * CMI_PS_READ_DEDICATED_BEARER_DYN_CTX_CNF
 * AT+CGSCONTRDP?
*/
typedef struct CmiPsReadDedBearerDynCtxParamCnfTag
{
    /*
     * AT+CGCONTRDP? is to query all the actived Dedicate bearer info, in order to reduce the struct size,
     * Each time return one bearer info;
    */
    BOOL                    bContBearer;
    BOOL                    bearerCtxPresent;
    UINT16                  reserved0;

    CmiPsDedBearerCtxDynParam  ctxDynPara;
}CmiPsReadDedBearerDynCtxParamCnf;




/*
 * CMI_PS_MODIFY_BEARER_CTX_REQ,
 *  +CGCMOD[=<cid>
*/
typedef struct CmiPsModifyBearerCtxReqTag
{
    UINT8           cid;
    UINT8           reserved1;
    UINT16          reserved2;
}CmiPsModifyBearerCtxReq;

/*
 * CMI_PS_MODIFY_BEARER_CTX_CNF
*/
typedef CacCmiEmptySig CmiPsModifyBearerCtxCnf;


/*
 * CMI_PS_GET_ALL_BEARERS_CIDS_INFO_REQ
 * 1> This CMI will return all current basic bearers (cids) info;
 * 2> And several AT CMDs could be mapped to this CMI interface, in order to distinguish which AT CMD,
 *    involved a member: "getCidsCmd";
 * 3> PS will return all bearers (CIDs) basic info, no matter the request CMD ("getCidsCmd"),
 *    and AT CMD (psproxy) need to decide which info need to return (print) according to the member: "getCidsCmd"
*/
typedef enum CmiPsGetAllCidsInfoCmd_Enum
{
    CMI_PS_DEFAULT_GET_CIDS_CMD = 0,

    /*
     * AT+CGACT?
     *  returns the current activation states for all the defined PDP contexts
    */
    CMI_PS_CGACT_GET_CIDS_CMD,
    CMI_PS_GET_ACTED_BEARERS_CMD = CMI_PS_CGACT_GET_CIDS_CMD,

    /*
     * AT+CGCONTRDP=?
     *   returns a list of <cid>s associated with active non secondary contexts
    */
    CMI_PS_CGCONTRDP_GET_CIDS_CMD,
    CMI_PS_GET_ACTED_DEFAULT_BEARERS_CMD = CMI_PS_CGCONTRDP_GET_CIDS_CMD,

    /*
     * AT+CGSCONTRDP=?
     *  returns a list of <cid>s associated with active secondary PDP contexts
    */
    CMI_PS_CGSCONTRDP_GET_CIDS_CMD,
    CMI_PS_GET_ACTED_DEDICATED_BEARERS_CMD = CMI_PS_CGSCONTRDP_GET_CIDS_CMD,

    /*
     * AT+CGTFTRDP=?
     *  returns a list of <cid>s associated with active secondary and non secondary contexts
    */
    CMI_PS_CGTFTRDP_GET_CIDS_CMD,

    /*
     * AT+CGEQOSRDP=?
     *  returns a list of <cid>s associated with secondary or non secondary active PDP contexts
    */
    CMI_PS_CGEQOSRDP_GET_CIDS_CMD,

    /*
     * AT+CGCMOD=?
     *  returns a list of <cid>s associated with active contexts
    */
    CMI_PS_CGCMOD_GET_CIDS_CMD,

    /*
     * AT+CGPADDR=?
     *  returns a list of defined <cid>s
    */
    CMI_PS_CGPADDR_GET_CIDS_REQ,
    CMI_PS_GET_DEFINED_BEARERS_CMD = CMI_PS_CGPADDR_GET_CIDS_REQ,

    /*
     * AT+CGAPNRC=?
     *  returns a list of <cid>s associated with secondary and non secondary active PDP contexts
    */
    CMI_PS_CGAPNRC_GET_CIDS_CMD,          /* CGAPNRC */

    /*
     * AT+CGVCID?
     *  return vacant (not used) CID list
    */
    CMI_PS_CGVCID_GET_CIDS_CMD,

	/*
     * AT$QCGCONTRDP=?
     *   returns a list of <cid>s associated with active non secondary contexts
    */
    CMI_PS_CGCONTRDP_GET_CID_CMD,
    CMI_PS_GET_ACTED_DEFAULT_BEARER_CMD = CMI_PS_CGCONTRDP_GET_CID_CMD,

    CMI_PS_GET_CIDS_NUM_OPERS
}CmiPsGetAllCidsInfoCmd;

typedef struct CmiPsGetAllBearersCidsInfoReqTag
{
    UINT8       getCidsCmd; //CmiPsGetAllCidsInfoCmd
    UINT8       reserved;
    UINT16      reserved2;
}CmiPsGetAllBearersCidsInfoReq;

typedef struct CmiPsBearerCidBasicInfoTag
{
    UINT8       cid;        //0-10
    UINT8       epsId;      //0-10, if not activated, set to 0
    UINT8       bearerState;    //CmiPsBearerState
    UINT8       bearerType;     //CmiPsBearerType
}CmiPsBearerCidBasicInfo;

/*
 * CMI_PS_GET_ALL_BEARERS_CIDS_INFO_CNF
*/
typedef struct CmiPsGetAllBearersCidsInfoCnfTag
{
     UINT8          getCidsCmd; //CmiPsGetAllCidsInfoCmd
     UINT8          validNum;
     UINT16         reserved0;
     CmiPsBearerCidBasicInfo    basicInfoList[CMI_PS_CID_NUM];
}CmiPsGetAllBearersCidsInfoCnf;


/*
 * CMI_PS_GET_BEARER_IPADDR_REQ,//AT+CGPADDR=<cid>
 * AT+CGPADDR=[=<cid>[,<cid>[,...]]]
 *  The execution command returns a list of PDP addresses for the specified context identifiers. If no <cid> is specified,
 *  the addresses for all defined contexts are returned.
*/
typedef struct CmiPsGetBearerIpAddrReqTag
{
    /*
     * if no <cid> is specified, should return all bearers IP address
    */
    BOOL            bAllCid;
    UINT8           cid;
    UINT16          reserved0;
}CmiPsGetBearerIpAddrReq;

/*
 * CMI_PS_GET_BEARER_IPADDR_CNF,
*/
typedef struct CmiPsGetBearerIpAddrCnfTag
{
    BOOL            bContinue;  //whether another bearer IP address return followed
    UINT8           cid;
    UINT16          reserved0;
    CmiIpAddr       ipv4Addr;
    CmiIpAddr       ipv6Addr;
}CmiPsGetBearerIpAddrCnf;


/*
 * CMI_PS_GET_ATTACH_STATE_REQ,
*/
typedef CacCmiEmptySig  CmiPsGetAttachStateReq;

typedef enum CmiPsAttachStateEnum_Tag
{
    CMI_PS_DETACHED = 0,
    CMI_PS_ATTACHED
}CmiPsAttachStateEnum;

/*
 * CMI_PS_GET_ATTACH_STATE_CNF,
*/
typedef struct CmiPsGetAttachStateCnfTag
{
    UINT8           state;      //CmiPsAttachStateEnum
    UINT8           reserved1;
    UINT16          reserved2;
}CmiPsGetAttachStateCnf;

/*
 * CMI_PS_SET_ATTACH_STATE_REQ,
*/
typedef struct CmiPsSetAttachStateReqTag
{
    UINT8           state;      //CmiPsAttachStateEnum
    UINT8           reserved1;
    UINT16          reserved2;
}CmiPsSetAttachStateReq;

/*
 * CMI_PS_SET_ATTACH_STATE_CNF,
*/
typedef CacCmiEmptySig CmiPsSetAttachStateCnf;

/*
 * CMI_PS_ENTER_DATA_STATE_REQ,//AT+CGDATA
*/
typedef struct CmiPsEnterDataStateReqTag
{
    UINT8           cid;//cid to be actived;
    UINT8           reserved1;
    UINT16          reserved2;
}CmiPsEnterDataStateReq;

/*
 *CMI_PS_ENTER_DATA_STATE_CNF,
*/
typedef CacCmiEmptySig CmiPsEnterDataStateCnf;


/*
 * CMI_PS_NO_MORE_PS_DATA_REQ, //AT+CNMPSD
*/
typedef CacCmiEmptySig CmiPsNoMorePsDataReq;

/*
 * CMI_PS_NO_MORE_PS_DATA_CNF, //AT+CNMPSD
*/
typedef CacCmiEmptySig CmiPsNoMorePsDataCnf;


/* ===== struct of CEREG ===== */
typedef enum CmiMmCeregModeEnum_TAG
{
    CMI_PS_DISABLE_CEREG = 0,
    CMI_PS_ENABLE_CEREG = 1,
    CMI_PS_CEREG_LOC_INFO = 2,
    CMI_PS_CEREG_LOC_EMM_CAUSE = 3,
    CMI_PS_CEREG_LOC_PSM_INFO = 4,
    CMI_PS_CEREG_LOC_PSM_INFO_EMM_CAUSE = 5
}CmiPsCeregModeEnum;

typedef enum CmiCeregStateEnum_Tag
{
    CMI_PS_NOT_REG = 0,
    CMI_PS_REG_HOME = 1,
    CMI_PS_NOT_REG_SEARCHING = 2,
    CMI_PS_REG_DENIED = 3,
    CMI_PS_REG_UNKNOWN = 4,
    CMI_PS_REG_ROAMING = 5,
    CMI_PS_REG_SMS_ONLY_HOME = 6,        // not applicable
    CMI_PS_REG_SMS_ONLY_ROAMING = 7,     // not applicable
    CMI_PS_REG_EMERGENCY = 8,
    CMI_PS_REG_CSFB_NOT_PREFER_HOME = 9, // not applicable
    CMI_PS_REG_CSFB_NOT_PREFER_ROAMING = 10 //not applicable

}CmiCeregStateEnum;

typedef enum CmiCeregActEnum_Tag
{
    CMI_PS_GSM = 0,
    CMI_PS_GSM_COMPACT = 1,
    CMI_PS_UMTS = 2,
    CMI_PS_GSM_EGPRS = 3,
    CMI_PS_HSDPA = 4,
    CMI_PS_HSUPA = 5,
    CMI_PS_HSDPA_HSUPA = 6,
    CMI_PS_LTE = 7,
    CMI_PS_EC_GSM = 8,
    CMI_PS_NB_IOT = 9 //NB only
}CmiCeregActEnum;

#if 0
/*
 * CMI_PS_SET_CEREG_MODE_REQ, //AT+CEREG=<n>
*/
typedef struct CmiPsSetCeregModeReq_Tag
{
    UINT8 reportMode;   //CmiPsCeregModeEnum
    UINT8 reserved1;
    UINT16 reserved2;
}CmiPsSetCeregModeReq;

/*
 * CMI_PS_SET_CEREG_MODE_CNF,
*/
typedef CacCmiEmptySig CmiPsSetCeregModeCnf;
#endif

/*
 * CMI_PS_GET_CEREG_REQ, //AT+CEREG?
*/
typedef CacCmiEmptySig CmiPsGetCeregReq;

/*
 * CMI_PS_GET_CEREG_CNF,
*/
typedef struct CmiPsGetCeregCnf_Tag
{
    //UINT8   ceregMode;    //CmiPsCeregModeEnum, this "ceregMode" saved in ATCMDSRC side
    UINT8   state;          //CmiCeregStateEnum
    BOOL    bRegOngoing;    //if not registered, whether low layer is trying to search/register to a PLMN
    UINT16  rsvd0;

    BOOL    locPresent;
    UINT8   act;            //CmiCeregActEnum
    UINT16  tac;
    UINT32  celId;

    BOOL    rejCausePresent;
    UINT8   causeType;      // only support 0 by now
    UINT16  rejCause;

    BOOL    activeTimePresent;
    UINT8   activeTime;     //T3324, valid when "activeTimePresent" == TRUE

    BOOL    extTauTimePresent;
    UINT8   extPeriodicTau; //extT3412, valid when "extTauTimePresent" == TRUE

    /*
     * Active Time value in seconds, valid when "extTauTimePresent" == TRUE
    */
    UINT32  activeTimeS;
    /*
     * extended periodic TAU value in seconds, valid when "extTauTimePresent" == TRUE
    */
    UINT32  extPeriodicTauS;

    /*
     * 1> if NW not config the extT3412(extPeriodicTau), should return this T3412 (periodicTauS) value in seconds;
     * 2> else (if NW config extT3412), don't need to return this T3412 (periodicTauS)
    */
    BOOL    tauTimerPresent;
    UINT8   rsvd1;
    UINT16  rsvd2;

    UINT32  periodicTauS;
}CmiPsGetCeregCnf;

/*
 * CMI_PS_GET_CEREG_CAP_REQ, //AT+CEREG=?
*/
typedef CacCmiEmptySig CmiPsGetCeregCapReq;

/*
 * CMI_PS_GET_CEREG_CAP_CNF,
*/
typedef struct CmiPsGetCeregCapCnf_Tag
{
    UINT8     bBitMap; // bit 0 set to 1, means suppurt n = 0;
    UINT8     reserved1;
    UINT16    reserved2;
}CmiPsGetCeregCapCnf;

/*
 * CMI_PS_GET_PLMN_RATE_CTRL_PARM_REQ,
*/
typedef struct CmiPsGetPLMNRateCtrlReqTag
{
    UINT8       cid;
    UINT16      reserved1;
}CmiPsGetPLMNRateCtrlReq;


/******************************************************************************
 * Note:
 * Change level should: CMI_CEREG_STATE_CHANGED > CMI_CEREG_LOC_INFO_CHANGED > CMI_CEREG_REJECT_INFO_CHANGED > CMI_CEREG_PSM_INFO_CHANGED
 * Just means:
 * 1> If "CMI_CEREG_STATE_CHANGED" is set, just means registation state changed,
 *     can't set to low level: "CMI_CEREG_LOC_INFO_CHANGED/CMI_CEREG_REJECT_INFO_CHANGED/CMI_CEREG_PSM_INFO_CHANGED"
 * 2> If "CMI_CEREG_LOC_INFO_CHANGED" is set, just means registation state not changed, but location info changed,
 *     can't set to low level: "CMI_CEREG_REJECT_INFO_CHANGED/CMI_CEREG_PSM_INFO_CHANGED"
******************************************************************************/
typedef enum CmiCeregChangedTypeEnum_Tag
{
    CMI_CEREG_NONE_CHANGED = 0,
    CMI_CEREG_STATE_CHANGED,
    CMI_CEREG_LOC_INFO_CHANGED, //location info changes
    CMI_CEREG_REJECT_INFO_CHANGED,
    CMI_CEREG_PSM_INFO_CHANGED
}CmiCeregChangedTypeEnum;

/*
 * CMI_PS_CEREG_IND, //+CEREG xxx
*/
typedef struct CmiPsCeregInd_Tag
{
    UINT8   state;          //CmiCeregStateEnum
    UINT8   changedType;    //CmiCeregChangedTypeEnum, which type of info are changed
    BOOL    bRegOngoing;    //if not registered, whether UE is trying to register to a PLMN later, maybe after OOS timer expiried
    UINT8   rsvd0;

    BOOL    locPresent;
    UINT8   act;            //CmiCeregActEnum
    UINT16  tac;
    UINT32  celId;

    BOOL    rejCausePresent;
    UINT8   causeType;      // only support 0 by now
    UINT16  rejCause;
	CmiNumericPlmn	  plmn;

    BOOL    activeTimePresent;
    UINT8   activeTime;     //T3324, valid when "activeTimePresent" == TRUE

    BOOL    extTauTimePresent;
    UINT8   extPeriodicTau; //extT3412, valid when "extTauTimePresent" == TRUE

    /*
     * Active Time value in seconds, valid when "extTauTimePresent" == TRUE
    */
    UINT32  activeTimeS;

    /*
     * extended periodic TAU value in seconds, valid when "extTauTimePresent" == TRUE
    */
    UINT32  extPeriodicTauS;

    /*
     * 1> if NW not config the extT3412(extPeriodicTau), should return this T3412 (periodicTauS) value in seconds;
     * 2> else (if NW config extT3412), don't need to return this T3412 (periodicTauS)
    */
    BOOL    tauTimerPresent;
    UINT8   rsvd1;
    UINT32  periodicTauS;
}CmiPsCeregInd;


/*
 * CMI_PS_SET_ATTACH_WITH_OR_WITHOUT_PDN_REQ, //AT+CIPCA
*/
typedef struct CmiPsSetAttachWithOrWithoutPdnReq_Tag
{
    UINT8       nflag;
    UINT8       attachedWithoutPdn; // value 0-1;
    UINT16      reserved1;
}CmiPsSetAttachWithOrWithoutPdnReq;

/*
 * CMI_PS_SET_ATTACH_WITH_OR_WITHOUT_PDN_CNF,
*/
typedef CacCmiEmptySig CmiPsSetAttachWithOrWithoutPdnCnf;

/*
 * CMI_PS_GET_ATTACH_WITH_OR_WITHOUT_PDN_REQ, //AT+CIPCA?
*/
typedef CacCmiEmptySig CmiPsGetAttachWithOrWithoutPdnReq;

/*
 * CMI_PS_GET_ATTACH_WITH_OR_WITHOUT_PDN_CNF,
*/
typedef struct CmiPsGetAttachWithOrWithoutPdnCnf_Tag
{
    UINT8       nflag;
    UINT8       attachedWithoutPdn; // value 0-1;
    UINT16      reserved1;
}CmiPsGetAttachWithOrWithoutPdnCnf;

/*
 * CMI_PS_GET_APN_RATE_CTRL_PARM_REQ, //
 * AT+CGAPNRC=<cid>
 *  +CGAPNRC: <cid>[,<Additional_exception_reports>[,<Uplink_time_unit>[,<Maximum_uplink_rate]]
 * If the parameter <cid> is omitted, the APN rate control parameters for all active PDP contexts are returned
*/
typedef struct CmiPsGetAPNRateCtrlReq_Tag
{
    BOOL        bAllCid;    //whether request all actived default bearer info
    UINT8       cid;        //if "bAllCid" == FALSE, get specified default bearer info;
    UINT16      reserved0;
}CmiPsGetAPNRateCtrlReq;

typedef enum CmiPsApnRateCtrlUlTimeUnit_Enum
{
    CMI_PS_APN_RATE_UNRESTRICTED = 0,
    CMI_PS_APN_RATE_MINUTE = 1,
    CMI_PS_APN_RATE_HOUR   = 2,
    CMI_PS_APN_RATE_DAY    = 3,
    CMI_PS_APN_RATE_WEEK   = 4
}CmiPsApnRateCtrlUlTimeUnit;

typedef struct CmiPsApnRateCtrlParam_Tag
{
    UINT8       aer;        //Additional exception reports
    UINT8       ulTimeUnit; //CmiPsApnRateCtrlUlTimeUnit
    UINT16      reserved0;
    UINT32      maxUlRate;
}CmiPsApnRateCtrlParam;

/*
 * CMI_PS_GET_APN_RATE_CTRL_PARM_CNF,
*/
typedef struct CmiPsGetAPNRateCtrlCnf_Tag
{
    /*
     * Note:
     * if get all bearer APNRC info, and if a bearer is activated, but no APNRC info configed, then:
     *  "cid" should be set to right value, and "apnRateValid" set to FALSE
    */
    BOOL        bContinue;
    BOOL        apnRateValid;
    UINT8       cid;        /*if not valid, set to 0*/
    UINT8       reserved0;
    CmiPsApnRateCtrlParam   apnRateParam;
}CmiPsGetAPNRateCtrlCnf;

/*
 * CMI_PS_GET_PLMN_RATE_CTRL_PARM_CNF,
*/
typedef struct CmiPsGetPLMNRateCtrlCnf_Tag
{
    BOOL        bContinue;
    UINT8       cid;        /*if not valid, set to 0*/
    UINT8       reserved0;
    UINT16      splmnRateCtrl;
}CmiPsGetPLMNRateCtrlCnf;

/*
 * CMI_PS_DEFINE_TFT_PARM_REQ, //AT+CGTFT=[<cid>, ...],
 * sizeof(CmiPsTftFilter) = 52
*/
typedef struct CmiPsTftFilter_struct
{
    UINT8               cid;
    UINT8               pfId;
    UINT8               epIndex;
    BOOL                pIdNextHdrPresent;
    UINT8               pIdNextHdr;
    BOOL                tosPresent;
    UINT8               tosTc;
    UINT8               tosTcMask;

    BOOL                dstPortRangePresent;
    BOOL                srcPortRangePresent;
    BOOL                ipSecSPIPresent;
    BOOL                flowLabelPresent;

    CmiNumericRange     dstPortRange;
    CmiNumericRange     srcPortRange;
    UINT32              ipSecSPI;
    UINT32              flowLabel;

    CmiIpAddr           remoteAddrAndMask;

    UINT8               direction;
    UINT8               nwpfId;
    UINT16              reserved0;
}CmiPsTftFilter;

typedef struct CmiPsSetDefineTFTParamReq_Tag
{
    CmiPsTftFilter filter;
}CmiPsSetDefineTFTParamReq;

/*
 * CMI_PS_DEFINE_TFT_PARM_CNF,
*/
typedef CacCmiEmptySig CmiPsSetDefineTFTParamCnf;

/*
 * CMI_PS_DELETE_TFT_PARM_REQ,
*/
typedef struct CmiPsDelTFTParamReq_Tag
{
    UINT8    cid;
}CmiPsDelTFTParamReq;

/*
 * CMI_PS_DELETE_TFT_PARM_CNF,
*/
typedef CacCmiEmptySig CmiPsdelTFTParamCnf;

/*
 * CMI_PS_GET_DEFINED_TFT_PARM_REQ, //AT+CGTFT?
*/
typedef struct CmiPsGetDefineTFTParamReq_Tag
{
    BOOL    bAllCid;
    UINT8   cid;
    UINT16  reserved0;
}CmiPsGetDefineTFTParamReq;

/*
 * CMI_PS_GET_DEFINED_TFT_PARM_CNF,
*/
typedef struct  CmiPsGetDefineTFTParamCnfTag
{
    BOOL            epsTftValid;
    BOOL            bContinue;   //whether next bearer TFT info followed
    UINT8           numFilters;
    UINT8           reserved0;
    CmiPsTftFilter  filters[CMI_PS_MAX_TFT_FILTERS];    //52*16 = 832 bytes
}CmiPsGetDefineTFTParamCnf;

/*
 * CMI_PS_SET_ATTACHED_BEARER_CTX_REQ
 * AT$QCATTBEARER=<PDP_type>[,<eitf>[,<apn>[,<IPv4AddrAlloc>[,<NSLPI>[,<IPv4_MTU_discovery>[,<NonIP_MTU_discovery>
 *            [,<PCSCF_discovery>[,<IM_CN_Signalling_Flag_Ind>]]]]]]]]
 * +CGDCONT=0,<PDP_type>[,<APN>[,<PDP_addr>[,<d_comp>[,<h_comp>[,<IPv4AddrAlloc>
 *           [,<request_type>[,<PCSCF_discovery>[,<IM_CN_Signalling_Flag_Ind>[,<NSLPI>[,<securePCO>
 *           [,<IPv4_MTU_discovery>][,<Local_Addr_Ind>][,<NonIP_MTU_discovery>]]]]]]]]]]]
*/
typedef struct AttachedBearCtxPreSetParam_Tag
{
    UINT8   pdnType;        //CmiPsPdnType
    BOOL    eitfPresent;    //ESM information transfer flag
    UINT8   eitf;           //0 - 1; 0 - security protected ESM information transfer not required, 1 - security protected ESM information transfer required

    UINT8   apnLength;      /* 0 - apn is not present */
    UINT8   apnStr[CMI_PS_MAX_APN_LEN];//apn string

    BOOL    ipv4AlloTypePresent;
    UINT8   ipv4AlloType;   /* CmiPsIpv4AllocType. IPv4 address allocation through NAS signalling, or by DHCP */

    BOOL    NSLPIPresent;
    UINT8   NSLPI;          /*CmiPsNSLPICfg, NAS signalling priority*/

    BOOL    ipv4MtuDisTypePresent;
    BOOL    ipv4MtuDisByNas;    /* IPv4 MTU size discovery through NAS signalling */

    BOOL    nonIpMtuDisTypePresent;
    BOOL    nonIpMtuDisByNas;   /* Non-IP MTU size discovery through NAS signalling*/

    BOOL    authProPresent;
    UINT8   authProtocol;    /*CmiSecurityProtocol */
    UINT8   authUserNameLength;
    UINT8   authUserName[CMI_PS_MAX_AUTH_STR_LEN];//auth username string
    UINT8   authPasswordLength;
    UINT8   authPassword[CMI_PS_MAX_AUTH_STR_LEN];//auth password string

    /*
     * IMS/pcscf not support now
    */
    BOOL    pcscfDisTypePresent;
    UINT8   pcscfDisType;   //CmiPsPcscfDiscoveryType

    BOOL    imCnSigFlagPresent;
    UINT8   imCnSigFlag;    //CmiPsImCnSigFlag
    UINT8   reserved1;
    UINT16  reserved2;
}AttachedBearCtxPreSetParam;

typedef struct CmiPsSetAttachedBearerCtxReq_Tag
{
    AttachedBearCtxPreSetParam     attBearCtxPreset;
}CmiPsSetAttachedBearerCtxReq;

/*
 * CMI_PS_SET_ATTACHED_BEARER_CTX_CNF
*/
typedef CacCmiEmptySig CmiPsSetAttachedBearerCtxCnf;

/*
 * CMI_PS_GET_ATTACHED_BEARER_CTX_REQ
 * AT$QCATTBEARER?
*/
typedef CacCmiEmptySig CmiPsGetAttachedBearerCtxReq;

/*
 * CMI_PS_GET_ATTACHED_BEARER_CTX_CNF
 *  $QCATTBEARER=<PDP_type>,<eitf>,<apn>,<IPv4AddrAlloc>,<NSLPI>,<IPv4_MTU_discovery>,<NonIP_MTU_discovery>
 *               ,<PCSCF_discovery>,<IM_CN_Signalling_Flag_Ind>
*/
typedef struct AttachedBearCtxParam_Tag
{
    UINT8   pdnType;        //CmiPsPdnType
    UINT8   eitf;           //0 - 1; 0 - security protected ESM information transfer not required, 1 - security protected ESM information transfer required
    UINT8   apnLength;      /* 0 - apn is not present */
    UINT8   apnStr[CMI_PS_MAX_APN_LEN];//apn string

    UINT8   ipv4AlloType;   /* CmiPsIpv4AllocType. IPv4 address allocation through NAS signalling, or by DHCP */
    UINT8   NSLPI;          /* CmiPsNSLPICfg, NAS signalling priority*/

    BOOL    ipv4MtuDisByNas;    /* IPv4 MTU size discovery through NAS signalling */
    BOOL    nonIpMtuDisByNas;   /* Non-IP MTU size discovery through NAS signalling*/

    UINT8   authProtocol;    /*CmiSecurityProtocol */
    UINT8   authUserNameLength;
    UINT8   authUserName[CMI_PS_MAX_AUTH_STR_LEN];//auth username string
    UINT8   authPasswordLength;
    UINT8   authPassword[CMI_PS_MAX_AUTH_STR_LEN];//auth password string

    
    /*
     * IMS/pcscf not support now
    */
    UINT8   pcscfDisType;   //CmiPsPcscfDiscoveryType
    UINT8   imCnSigFlag;    //CmiPsImCnSigFlag
    UINT16  reserved1;

}AttachedBearCtxParam;

typedef struct CmiPsGetAttachedBearerCtxCnf_Tag
{
    AttachedBearCtxParam  attBearCtxParam;
}CmiPsGetAttachedBearerCtxCnf;

/*
 * RAI enum
*/
typedef enum CmiPsRelAssistIndEnum_Tag
{
    CMI_PS_RAI_NO_INFO = 0,
    CMI_PS_RAI_NO_UL_DL_FOLLOWED = 1,
    CMI_PS_RAI_ONLY_DL_FOLLOWED = 2,
    CMI_PS_RAI_RESERVED = 3
}CmiPsRelAssistIndEnum;

/*
 * type_of_user_data
*/
typedef enum CmiPsUserDataType_enum
{
    CMI_PS_REGULAR_DATA = 0,
    CMI_PS_EXCEPT_DATA = 1
}CmiPsUserDataType;

/*
 * CMI_PS_SEND_CP_DATA_REQ
 * +CSODCP=<cid>,<cpdata_length>,<cpdata>[,<RAI>[,<type_of_user_data>]
*/
#if 0
typedef struct OriDataPacketParamTag
{
    UINT8   cid;
    UINT8   reserved0;
    UINT16  dataLen; //max len is 1600;
    UINT8   *cpData;  //need allocate firstly when called by AT

    UINT8   rai;     //CmiPsRelAssistIndEnum, indicates the value of the release assistance indication, if not set, default: CMI_PS_RAI_NO_INFO
    UINT8   typeOfUserData; //CmiPsUserDataType, indicates whether the user data that is transmitted is regular or exceptional.
    UINT16  reserved1;
}OriDataPacketParam;
#endif

typedef struct CmiPsSendOriDataViaCpReqTag
{
    UINT8   cid;
    UINT8   reserved0;
    UINT16  dataLen; //max len is 1600;
    UINT8   *cpData;  //need allocate firstly when called by AT

    UINT8   rai;     //CmiPsRelAssistIndEnum, indicates the value of the release assistance indication, if not set, default: CMI_PS_RAI_NO_INFO
    UINT8   typeOfUserData; //CmiPsUserDataType, indicates whether the user data that is transmitted is regular or exceptional.
    UINT16  reserved1;
}CmiPsSendOriDataViaCpReq;


typedef struct CmiPsSetQcPdpCfgReqTag
{
    UINT8   apnClass;
    UINT8   disabled;
	UINT16  maxPdnConnPerBlock;
	UINT16 	maxPdnConnTimer;
	UINT16 	pdnReqWaitTimer;
}CmiPsSetQcPdpCfgReq;

/*
 * CMI_PS_SEND_CP_DATA_CNF
*/
typedef CacCmiEmptySig CmiPsSendOriDataViaCpCnf;

/*
 * CMI_PS_SET_MT_CP_DATA_REPORT_CFG_REQ
 * +CRTDCP=[<reporting>]
*/
typedef struct CmiPsSetCpDataReportCfgReq_Tag
{
    UINT8     reporting;
    UINT8     reserved1;
    UINT16    reserved2;
}CmiPsSetCpDataReportCfgReq;

/*
 * CMI_PS_SET_MT_CP_DATA_REPORT_CFG_CNF
*/
typedef CacCmiEmptySig CmiPsSetCpDataReportCfgCnf;

/*
 * CMI_PS_GET_MT_CP_DATA_REPORT_CFG_REQ
 * +CRTDCP?
*/
typedef CacCmiEmptySig CmiPsGetCpDataReportCfgReq;
/*
 * CMI_PS_GET_MT_CP_DATA_REPORT_CFG_CNF
*/
typedef struct CmiPsGetCpDataReportCfgCnf_Tag
{
    UINT8   reporting;
    UINT8   reserved1;
    UINT16  reserved2;
}CmiPsGetCpDataReportCfgCnf;

/*
 * CMI_PS_MT_CP_DATA_IND, //+CRTDCP:<cid>,<cpdata_length>,<cpdata>
*/
typedef struct CmiPsMtCpDataInd_Tag
{
    UINT8   cid;
    UINT8   reserved0;
    UINT16  length;
    UINT8   *cpdata;
}CmiPsMtCpDataInd;


/*
 * CMI_PS_SEND_UL_DATA_REQ
 *  AT$QCSENDDATA=<cid>,<data_length>,<data>[,<RAI>[,<type_of_user_data>]]
 * Note:
 * 1> User could send non-ip/ip data via this AT CMD;
 * 2> Not the same as: +CSODCP,
 *    AT$QCSENDDATA: could send data via CP or UP
 *    AT+CSODCP:   only send the data via CP
*/
typedef struct CmiPsSendUlDataReq_Tag
{
    UINT8   cid;
    UINT8   reserved0;
    UINT16  dataLen; //max len is 1600;
    UINT8   *pData;  //should use dynamic memory

    UINT8   rai;     //CmiPsRelAssistIndEnum, indicates the value of the release assistance indication, if not set, default: CMI_PS_RAI_NO_INFO
    UINT8   typeOfUserData; //CmiPsUserDataType, indicates whether the user data that is transmitted is regular or exceptional.
    UINT16  reserved1;
}CmiPsSendUlDataReq;

/*
 * CMI_PS_SEND_UL_DATA_CNF
 * AT$QCSENDDATA
*/
typedef CacCmiEmptySig CmiPsSendUlDataCnf;


/*
 * CMI_PS_RECV_DL_NON_IP_DATA_IND
 *  +RECVNONIP: <cid>,<data_length>,<data>
 *  For NON-IP data, just foward to AT CMD SRV UART
*/
typedef struct CmiPsRecvDlNonIpDataInd_Tag
{
    UINT8   cid;
    UINT8   reserved0;
    UINT16  length;
    UINT8   *pData;    // using dynamic memory
}CmiPsRecvDlNonIpDataInd;


/*
 * CMI_PS_TRANS_CIOT_PLANE_REQ,
 *  AT$QCCIOTPLANE=plane, to select CP or UP
*/
typedef enum CmiPsDataPlane_Enum
{
    CMI_PS_CTRL_PLANE,
    CMI_PS_USER_PLANE,
    CMI_PS_UNKNOWN_PLANE
}CmiPsDataPlane;

typedef struct CmiPsTransCiotPlaneReq_Tag
{
    UINT8   plane;      //CmiPsDataPlane
    UINT8   reserved0;
    UINT16  reserved1;
}CmiPsTransCiotPlaneReq;

/*
 * CMI_PS_TRANS_CIOT_PLANE_CNF
*/
typedef CacCmiEmptySig CmiPsTransCiotPlaneCnf;


/******************************************************************************
 * CMI_PS_GET_CONN_STATUS_REQ
 * CMI_PS_GET_CONN_STATUS_CNF
 * AT+CSCON?
 *  +CSCON: <n>,<mode>[,<state>]    //<state> not support now
******************************************************************************/
typedef CacCmiEmptySig  CmiPsGetConnStatusReq;

typedef enum CmiPsConnStatusModeEnum_Tag
{
    CMI_Ps_CONN_IDLE_MODE = 0,
    CMI_Ps_CONNECTED_MODE
}CmiPsConnStatusModeEnum;

typedef struct CmiPsGetConnStatusCnf_Tag
{
    UINT8   connMode;   //CmiPsConnStatusModeEnum
    UINT8   reserved0;
    UINT16  reserved1;
}CmiPsGetConnStatusCnf;

/*
 * CMI_PS_CONN_STATUS_IND
 *  +CSCON: <mode>[,<state>[,<access>]] // we only support: <mode>
*/
typedef struct CmiPsConnStatusInd_Tag
{
    UINT8   connMode;   //CmiPsConnStatusModeEnum
    UINT8   reserved0;
    UINT16  reserved1;
}CmiPsConnStatusInd;



/******************************************************************************
 * CMI_PS_DEFINE_AUTH_CTX_REQ
 * CMI_PS_DEFINE_AUTH_CTX_CNF
 * AT+CGAUTH=cid,auth_prot,userid,password
 *  OK

 * CMI_PS_GET_DEFINED_AUTH_CTX_REQ
 * CMI_PS_GET_DEFINED_AUTH_CTX_CNF
 * AT+CGAUTH?
 *  +CGAUTH: cid,auth_prot,<userid,password>
******************************************************************************/
typedef struct CmiPsSetDefineAuthCtxReq_Tag
{
    UINT8   cid;
    UINT8   authProtocol;    /*CmiSecurityProtocol */
    UINT8   authUserNameLength;
    UINT8   authUserName[CMI_PS_MAX_AUTH_STR_LEN];//auth username string
    UINT8   authPasswordLength;
    UINT8   authPassword[CMI_PS_MAX_AUTH_STR_LEN];//auth password string
}CmiPsSetDefineAuthCtxReq;

/*
 * CMI_PS_DEFINE_AUTH_CTX_CNF
*/
typedef CacCmiEmptySig CmiPsSetDefineAuthCtxCnf;
/*
 * CMI_PS_GET_DEFINED_AUTH_CTX_REQ
*/
typedef CacCmiEmptySig CmiPsGetDefineAuthCtxReq;

/*
 * CMI_PS_SET_QC_APN_CLASS_CFG_CNF
*/
typedef CacCmiEmptySig CmiPsQcApnClassCfgCnf;

/*
 * CMI_PS_GET_DEFINED_AUTH_CTX_CNF
*/
typedef struct CmiPsGetDefineAuthCtxCnf_Tag
{
    BOOL    bContinue;  //whether another bearer IP address return followed
    UINT8   cid;
    UINT8   authProtocol;                         /*CmiSecurityProtocol */
    UINT8   authUserName[CMI_PS_MAX_AUTH_STR_LEN +1];//auth username string
    UINT8   authPassword[CMI_PS_MAX_AUTH_STR_LEN +1];//auth password string
}CmiPsGetDefineAuthCtxCnf;

typedef struct BearerPktStats_Tag
{
   UINT32 pkts_tx;
   UINT32 pkts_rx;
   INT64  bytes_tx;  
   INT64  bytes_rx;
   UINT32 pkts_dropped_tx;
   UINT32 pkts_dropped_rx;
}BearerPktStats;
typedef CacCmiEmptySig CmiPsGetCeerReq;

typedef enum CmiEmmCauseTag
{
    CMI_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS                                  = 0x02,
    CMI_EMM_CAUSE_ILLEGAL_UE                                           = 0x03,
    CMI_EMM_CAUSE_IMEI_NOT_ACCEPTED                                    = 0x05,
    CMI_EMM_CAUSE_ILLEGAL_ME                                           = 0x06,
    CMI_EMM_CAUSE_EPS_SERVICES_NOT_ALLOWED                             = 0x07,
    CMI_EMM_CAUSE_EPS_AND_NON_EPS_SERVICES_NOT_ALLOWED                 = 0x08,
    CMI_EMM_CAUSE_UE_ID_CAN_NOT_BE_DERIVED_IN_NETWORK                  = 0x09,
    CMI_EMM_CAUSE_IMPLICITLY_DETACHED                                  = 0x0A,
    CMI_EMM_CAUSE_PLMN_NOT_ALLOWED                                     = 0X0B,
    CMI_EMM_CAUSE_TRACKING_AREA_NOT_ALLOWED                            = 0x0C,
    CMI_EMM_CAUSE_ROAMING_NOT_ALLOWED_IN_THIS_TRACKING_AREA            = 0X0D,
    CMI_EMM_CAUSE_EPS_SERVICE_NOT_ALLOWED_IN_THIS_PLMN                 = 0x0E,
    CMI_EMM_CAUSE_NO_SUITABLE_CELLS_IN_TRACKING_AREA                   = 0x0F,
    CMI_EMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE                        = 0x10,
    CMI_EMM_CAUSE_NETWORK_FAILURE                                      = 0x11,
    CMI_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE                              = 0x12,
    CMI_EMM_CAUSE_ESM_FAILURE                                          = 0x13,
    CMI_EMM_CAUSE_MAC_FAILURE                                          = 0X14,
    CMI_EMM_CAUSE_SYNCH_FAILURE                                        = 0X15,
    CMI_EMM_CAUSE_CONGESTION                                           = 0X16,
    CMI_EMM_CAUSE_UE_SECURITY_CAPAILITIES_MISMATCH                     = 0x17,
    CMI_EMM_CAUSE_SECURITY_MODE_REJECTED_UNSPECIFIED                   = 0x18,
    CMI_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                          = 0x19,
    CMI_EMM_CAUSE_NON_EPS_AUTHENTICATION_UNACCEPTABLE                  = 0x1A,
    CMI_EMM_CAUSE_REQUESTED_SERVICE_OPTION_NOT_AUTHORIZED_IN_THIS_PLMN = 0X23,
    CMI_EMM_CAUSE_CS_SERVICE_TEMPORARILY_NOT_AVAILABLE                 = 0x27,
    CMI_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED                      = 0x28,
    CMI_EMM_CAUSE_SERVERE_NETWORK_FAILURE                              = 0x2A,
    CMI_EMM_CAUSE_SYMANTICALLY_INCORRECT_MESSAGE                       = 0X5F,
    CMI_EMM_CAUSE_INVALID_MANDATORY_INFORMATION                        = 0X60,
    CMI_EMM_CAUSE_MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED         = 0X61,
    CMI_EMM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE  = 0X62,
    CMI_EMM_CAUSE_INFORMATION_ELEMENT_NON_EXISTENT_OR_NOT_IMPLEMENTED  = 0X63,
    CMI_EMM_CAUSE_CONDITIONAL_IE_ERROR                                 = 0X64,
    CMI_EMM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE       = 0X65,
    CMI_EMM_CAUSE_PROTOCOL_ERROR_UNSPECIFIED                           = 0X6F,
}CmiEmmCause;

typedef struct CmiPsGetCeerCnf_Tag
{
    BOOL       bEmmCausePresent;
    BOOL       bEsmCausePresent;
    UINT16     emmCause;
    UINT16     esmCause;
 }
CmiPsGetCeerCnf;

/*
 * CMI_PS_GET_BEARER_PKT_STATS_REQ
 */
typedef struct CmiPsGetBearerPktStatsReq_Tag
{
   UINT8 cid;
}CmiPsGetBearerPktStatsReq;

/*
 * CMI_PS_GET_BEARER_PKT_STATS_CNF
 */
typedef struct CmiPsGetBearerPktStatsCnf_Tag
{
    UINT8 cid;
    BearerPktStats pktStatsPerBearer;
}CmiPsGetBearerPktStatsCnf;

/* CMI_PS_GET_APN_DISABLE_SYNC_STATUS_CNF */
typedef struct CmiPsGetAPNDisableSyncStatusCnfTag
{
	UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8					disableStatus;
    UINT8                   reserved;
    UINT16                  reserved2;
}CmiPsGetAPNDisableSyncStatusCnf;

/* CMI_PS_SET_APN_DISABLE_SYNC_STATUS_CNF */
typedef CacCmiEmptySig CmiPsSetAPNDisableSyncStatusCnf;


typedef struct CmiPsGetAPNDisableSyncStatusReq_Tag
{
	UINT8 pdpType;
	char apnName[DEVICE_INFO_APN_NAME_MAX + 1];	
}CmiPsGetAPNDisableSyncStatusReq;

typedef struct CmiPsSetAPNDisableSyncStatusReq_Tag
{
	UINT8 pdpType;
	char apnName[DEVICE_INFO_APN_NAME_MAX + 1];
	BOOL disableStatus;
}CmiPsSetAPNDisableSyncStatusReq;

/*CMI_PS_GET_ESM_CAUSE_REQ*/
typedef CacCmiEmptySig CmiPsGetEsmCause;

typedef struct CmiPsGetEsmCauseCnf_Tag{
	BOOL	rejCausePresent;
	UINT8	causeType;		// only support 0 by now
	UINT16	rejCause;
}CmiPsGetEsmCauseCnf;


#endif

