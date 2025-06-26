#ifndef __PS_SIG_ID_H__
#define __PS_SIG_ID_H__

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017, All rights reserved by Qualcomm Ltd.
 File name:      - pssigid.h
 Description:    - PS signal id enum definition
 History:        - 08/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/
#include "psl1sigid.h"

typedef enum PSSIGIDTAG
{
    /*
     * Move to osasys.h
     * 0x0100 - 0x0110
    SIG_TIMER_EXPIRY = 0x0100,
    SIG_HIB_TIMER_EXPIRY,
    */

    /*
     * 0x0900 - 0x090F, used between URAT <-> CMS(AT CMD SRV) (cms_api.h)
    */

    /*
     * 0x0910 - 0x091F, used between APP (LWM2M/COAP/MQTT, etc) <-> CMS(AT CMD SRV) (cms_api.h)
    */

    /*
     * 0x0920 - 0x0927, used for netmanager (netmgr.h)
    */

    /*
     * 0x0928 - 0x092F, used between SIMBIP <-> STK PS Proxy (psstkbip.h)
    */

    /*
     * 0x0940 - 0x094F, used for others CMS signal (cms_api.h)
    */

    /*
     * 0x0980 - 0x09FF, reserved for customer, (cms_api.h)
    */

    PS_SIGNAL_BASE = 0x1000,

    SIG_WIN_SIMULATE_INTERNAL_MSG = 0x1001, /* WinSimulateInternalMsg, simulate a internal msg for integration testing */

    SIG_CCM_BASE = 0x1100,

    /*
     * 0x11F0 - 0x11FF, used for CACCMI SIG (cmicommon.h)
     */

    /*********************************************************************
     *********************************************************************
     * signal to CCM CAC module
     *********************************************************************
     ********************************************************************/
    SIG_CCM_CAC_BASE = 0x1200,
    //SIG_CAC_CMI_REQ,
    //SIG_CAC_CMI_CNF, /*in fact need to put into ATCMD task signal definition queue*/
    //SIG_CAC_CMI_IND, /*in fact need to put into ATCMD task signal definition queue*/
    //SIG_CAC_CMI_RSP,
    SIG_CEMM_CAC_SET_PARM_CNF,  //CemmCacSetParmCnf
    SIG_CEMM_CAC_GET_PARM_CNF,  //CemmCacGetParmCnf

    SIG_CAC_SIGNAL_QUALITY_IND, //CacSignalQualityInd
    SIG_CAC_LOCAL_TIME_INFO_IND, //CacLocalTimeInfoInd

    SIG_CCM_CAC_END = 0x125f,

    SIG_CCM_COMM_BASE = 0x1260,
    SIG_CEMM_CCM_SET_PARM_CNF,  //CemmCcmSetParmCnf
    SIG_CEMM_CCM_GET_PARM_CNF,  //CemmCcmGetParmCnf

    /* CERRC - CCM */
    SIG_CERRC_CCM_SET_PARAM_CNF,    //CerrcCcmSetParamCnf
    SIG_CERRC_CCM_GET_PARAM_CNF,    //CerrcCcmGetParamCnf
    
    SIG_CEMM_CCM_GET_EMM_STATE_CNF,
	SIG_CEMM_CCM_SET_LAPI_CNF,   
	SIG_CEMM_CCM_GET_LAPI_CNF,

	SIG_CEMM_CCM_SET_ROAMING_DATA_CNF,
	SIG_CEMM_CCM_GET_ROAMING_DATA_CNF,

    SIG_CCM_COMM_END  = 0x127f,

    /*
     * signal to CCM SIM module
     */
    SIG_CCM_SIM_BASE = 0x1280,
    /* CCM - USIM */
    SIG_CCM_SIM_APP_STARTED_IND,
    SIG_CCM_SIM_APP_INIT_CNF,
    SIG_CCM_SIM_CARD_REMOVED_IND,
    SIG_CCM_SIM_GEN_ACCESS_CNF,
    SIG_CCM_SIM_TERMINATE_SESSION_CNF,
    SIG_CCM_SIM_READ_DATA_CNF,
    SIG_CCM_SIM_UPDATE_DATA_CNF,
    SIG_CCM_SIM_PIN_OPERATE_CNF,
    SIG_CCM_SIM_OPEN_LOGICAL_CHANNEL_CNF,
    SIG_CCM_SIM_CLOSE_LOGICAL_CHANNEL_CNF = 0x128A,
    SIG_CCM_SIM_RESTORE_DATA_CNF,
    SIG_CCM_SIM_EPS_CONNECTION_MODE_IND,
    SIG_CCM_SIM_SET_SIM_WRITE_COUNTER_CNF,
#ifdef FEAT_RPM
    SIG_CCM_SIM_RPM_PARAM_IND = 0x128E,     //Signal added by QCOM, rsvd here
#endif
    SIG_CCM_SIM_GEN_LOGICAL_CHANNEL_ACCESS_CNF,
    SIG_CCM_SIM_SET_SIM_PRESENCE_DETECT_CNF,
    SIG_CCM_SIM_GET_SUBSCRIBER_NUMBER_CNF,
    /* CCM - USAT */
    SIG_CCM_SIM_USAT_PROACTIVE_COMMAND_IND = 0x12A0,
    SIG_CCM_SIM_USAT_TERMINAL_PROFILE_CNF,
    SIG_CCM_SIM_USAT_REFRESH_IND,
    SIG_CCM_SIM_USAT_SET_UP_EVENT_LIST_IND,
    SIG_CCM_SIM_USAT_PROVIDE_LOCAL_INFO_IND,
    SIG_CCM_SIM_USAT_OPEN_CHANNEL_IND,
    SIG_CCM_SIM_USAT_CLOSE_CHANNEL_IND,
    SIG_CCM_SIM_USAT_SEND_DATA_IND,
    SIG_CCM_SIM_USAT_RECEIVE_DATA_IND,
    SIG_CCM_SIM_USAT_GET_CHANNEL_STATUS_IND,
    SIG_CCM_SIM_USAT_PROACTIVE_SESSION_END_IND = 0x12AA,
    SIG_CCM_SIM_USAT_EVENT_DOWNLOAD_CNF,
    SIG_CCM_SIM_USAT_MENU_SELECTION_CNF,
    SIG_CCM_SIM_USAT_SMS_PP_DOWNLOAD_CNF,
    SIG_CCM_SIM_USAT_MOSM_CONTROL_CNF,
    SIG_CCM_SIM_USAT_NETWORK_MEAS_CNF = 0x12B0,
    SIG_CCM_SIM_USAT_SEND_SM_IND,
    SIG_CCM_SIM_USAT_SEND_SM_RSP,

    SIG_CCM_SIM_END = 0x12ff,

    /*
     * signal to CCM REG module
     */
    SIG_CCM_REG_BASE = 0x1300,
    /* CEMM -> CCM REG*/
    SIG_CEMMR_REG_CNF,                  //CemmrRegCnf
    SIG_CEMMR_DEREG_CNF,                //CemmrDeregCnf
    SIG_CEMM_MANUAL_PLMN_SEARCH_CNF,    //CemmManualPlmnSearchCnf
    SIG_CEMM_ABORT_PLMN_SEARCH_CNF,     //CemmAbortPlmnSearchCnf
    SIG_CEMMR_REG_IND,                  //CemmrRegInd, when CEMM registered a PLMN
    SIG_CEMMR_DEREG_IND,                //CemmrDeRegInd, when PLMN rejected/detached by NW
    SIG_CEMMR_NW_SERVICE_STATUS_IND,    //CemmrNwServiceStatusInd
    SIG_CEMMR_NW_INFO_IND,              //CemmrNwInfoInd
    SIG_CEMM_PLMN_SET_BAND_FREQ_CNF,    //CemmPlmnSetBandFreqCnf
    SIG_CEMM_PLMN_GET_BAND_FREQ_CNF = 0x130A,   //CemmPlmnGetBandFreqCnf
    SIG_CEMMR_POWER_SAVE_CNF,           //CemmrPowerSaveCnf
    SIG_CEMMR_POWER_RECOVER_CNF,        //CemmrPowerRecoverCnf, wake up from hibernate state
    SIG_CEMM_OOS_PLMN_SELECT_CNF,       //CemmPlmnSelectStateCnf
    SIG_CEMMR_EMM_TIMER_STATE_IND,      //CemmrEmmTimerStateInd
    SIG_CEMMR_PSM_CHANGE_IND,           //CemmrPsmChangeInd
	SIG_CEMM_GTP_PLMN_SEARCH_CNF,    //CemmGtpPlmnSearchCnf
    SIG_CEMM_ABORT_GTP_PLMN_SEARCH_CNF,    //CemmAbortGtpPlmnSearchCnf
    SIG_CEMMR_PLMN_STATE_CHANGE_IND,    //CemmrPlmnSelectStateInd
    SIG_CEMMR_CONN_STATE_CHANGE_IND,    //CemmrConnStateChangeInd
    SIG_CEMM_PLMN_SET_MCC_BAND_CNF,
    SIG_CEMM_PLMN_GET_MCC_BAND_CNF,

    // ...
    SIG_CCM_REG_END = 0x137f,

    /*
     * signal to CCM PS module
     */
    SIG_CCM_PS_BASE = 0x1380,
    SIG_CCM_CESM_SET_EPS_BEARER_CTX_CNF,
    SIG_CCM_CESM_GET_EPS_BEARER_CTX_CNF,    /*CcmCesmGetEpsBearerCtxCnf*/
    SIG_CCM_CESM_ACT_EPS_BEARER_CTX_CNF,
    SIG_CCM_CESM_DEL_EPS_BEARER_CTX_CNF,
    SIG_CCM_CESM_ACT_EPS_BEARER_CTX_REJ,
    SIG_CCM_CESM_DEACT_EPS_BEARER_CTX_CNF,
    SIG_CCM_CESM_DEACT_EPS_BEARER_CTX_REJ,
    SIG_CCM_CESM_MOD_EPS_BEARER_CTX_CNF,
    SIG_CCM_CESM_ACT_DEF_EPS_BEARER_CTX_IND,
    SIG_CCM_CESM_ACT_DED_EPS_BEARER_CTX_IND,
    SIG_CCM_CESM_MOD_EPS_BEARER_CTX_IND = 0x138B,
    SIG_CCM_CESM_DEACT_EPS_BEARER_CTX_IND,
    SIG_CCM_CESM_GET_ALL_BEARERS_BASIC_INFO_CNF, /*CcmCesmGetAllBearersBasicInfoCnf*/
    //SIG_CCM_CESM_READ_BEARER_CTX_DYN_PARAM_CNF,
    //SIG_CCM_CESM_GET_DEFINED_CID_IPADDR_PARAM_CNF,
    //SIG_CCM_CESM_GET_APN_RATE_CTRL_CNF,
    SIG_CCM_CESM_SET_DEFINE_TFT_PARAM_CNF,
    //SIG_CCM_CESM_GET_DEFINE_TFT_PARAM_CNF = 0x1391,
    SIG_CCM_CESM_DEL_TFT_PARAM_CNF,
    SIG_CCM_CESM_SET_DEFINE_EPS_QOS_CNF,
    //SIG_CCM_CESM_GET_DEFINED_EPS_QOS_CNF,
    SIG_CCM_CESM_DEL_EPS_QOS_CNF,
    //SIG_CCM_CESM_SEND_DATA_VER_CP_CNF,
    SIG_CCM_CESM_ATTACHED_BEARER_CTX_PRESET_CNF,
    SIG_CCM_CESM_GET_ATTACHED_BEARER_CTX_CNF,
    SIG_CCM_CESM_SET_MT_CP_DATA_REPORT_CFG_CNF,
    SIG_CCM_CESM_GET_MT_CP_DATA_REPORT_CFG_CNF,
    SIG_CCM_CESM_MT_CP_DATA_IND = 0x139A,
    SIG_CCM_CESM_SET_DED_EPS_BEARER_CTX_CNF,
    SIG_CCM_CESM_DEL_DED_EPS_BEARER_CTX_CNF,
    SIG_CEDR_PS_DATA_PLANE_TRANS_CNF,   //CedrPsDataPlaneTransCnf, CEDR-> CCMPS
    SIG_CCM_DL_NON_IP_DATA_IND,         //CcmDlNonIpDataInd, CEDR -> CCMPS
    SIG_CCM_CESM_SET_DEFINE_AUTH_CTX_CNF,
    SIG_CCM_CESM_SET_APN_CLASS_CFG_CNF,
	SIG_CCM_CEDR_PKT_STATS_CNF,         //CcmCedrPktStatsCnf
    SIG_CCM_CESM_GET_APN_DISABLE_STATUS_CNF,
    SIG_CCM_CESM_SET_APN_DISABLE_STATUS_CNF,
    SIG_CCM_CESM_SET_THROTT_PARAM_REQ,
    SIG_CCM_CESM_ESM_REJECT_CAUSE_IND, //Send last ESM cause
    SIG_CCM_CESM_GET_EPS_BEARERS_CTX_CNF,
    SIG_CCM_CESM_GET_ALL_BEARER_BASIC_INFO_CNF,
    SIG_CCM_PS_END = 0x13ff,

    /*
     * signal to CCM SMS module
     */
    SIG_CCM_SMS_BASE = 0x1400,
    /* CEMM SMTL-> CCM SMS*/
    SIG_CEMM_SMTL_REPORT_IND,           //CemmSmtlReportInd
    SIG_CEMM_SMTL_DELIVERED_IND,        //CemmSmtlDeliveredInd
    SIG_CEMM_SMTL_STUS_REPT_IND,        //CemmSmtlStusReptInd
    SIG_CEMM_SMTL_SMS_SERVICE_AVAIL_IND,//CemmSmtlSmsServiceAvailInd
    // ...
    SIG_CCM_SMS_END = 0x147f,

    /*
     * signal to CCM DEV module
     */
    SIG_CCM_DEV_BASE = 0x1480,
    SIG_CCM_CESS_LPP_UNIT_DATA_CNF,
    SIG_CCM_CESS_LPP_UNIT_DATA_IND,
    SIG_CCM_CESS_RESET_POSITION_INFO_IND,
    SIG_CCM_CESS_LCS_UNIT_DATA_CNF,
    SIG_CCM_CESS_LCS_UNIT_DATA_IND,
    SIG_CCM_CESS_GET_CMTLRA_CNF,
    SIG_CCM_ERRC_LOC_MEAS_CNF,
    SIG_CCM_ERRC_EARLY_LOC_MEAS_CNF,
    SIG_CCM_ERRC_LOC_MEAS_IND,
    SIG_CCM_ERRC_STOP_LOC_MEAS_CNF = 0x148A,

    SIG_CCM_GET_ERRC_PHY_STATUS_CNF,    //CcmGetErrcPhyStatusCnf
    SIG_CCM_GET_L2_STATUS_CNF,          //CcmGetL2StatusCnf
    SIG_CCM_GET_NAS_STATUS_CNF,         //CcmGetNasStatusCnf
    SIG_CCM_L2_STATIS_INFO_IND,         //CcmL2StatisInfoInd

    SIG_CERRC_CCM_BASIC_CELL_LIST_INFO_CNF,     //CerrcCcmBasicCellListInfoCnf
    SIG_CERRC_CCM_ABORT_BASIC_CELL_LIST_INFO_CNF = 0x1490,   //CerrcCcmAbortBasicCellListInfoCnf
    SIG_CCM_ERRC_PHY_STATIS_INFO_IND,   //CcmErrcPhyStatisInfoInd

    SIG_CCM_GET_EMM_EVENT_STATIS_CNF,   //CemmEventStatisCnf
    SIG_CCM_GET_CERRC_EVENT_STATIS_CNF,   //CerrcEventStatisCnf
    
	SIG_CERRC_CCM_CE_INFO_IND,
	SIG_CERRC_CCM_GET_DRX_INFO_CNF,
	SIG_CCM_ERRC_PHY_DETECT_EVENT_IND,    //CcmErrcPhyDetectEventInd

    // ...
    SIG_CCM_DEV_END = 0x14ff,

    /*********************************************************************
     *********************************************************************
     * signal to CEMM module
     *********************************************************************
     *********************************************************************/
    SIG_CEMM_BASE = 0x1500,

    /* CCM/CAC -> CEMM */
    SIG_CEMMR_REG_REQ,                  //CemmrRegReq, CCM REG module send this signal to CEMM to trigger to AUTO REG, or MANUAL REG;
    SIG_CEMMR_DEREG_REQ,                //CemmrDeregReq,
    SIG_CEMM_MANUAL_PLMN_SEARCH_REQ,    //CemmManualPlmnSearchReq, only used for manual searching
    SIG_CEMM_ABORT_PLMN_SEARCH_REQ,     //CemmAbortPlmnSearchReq
    SIG_CEMM_PLMN_SET_BAND_FREQ_REQ,    //CemmPlmnSetBandFreqReq
    SIG_CEMM_PLMN_GET_BAND_FREQ_REQ,    //CemmPlmnGetBandFreqReq
    SIG_CEMM_CAC_SET_PARM_REQ,          //CemmCacSetParmReq, AT CMD set some CEMM paramerers
    SIG_CEMM_CAC_GET_PARM_REQ,          //CemmCacGetParmReq
    SIG_CEMMR_POWER_SAVE_REQ,           //CemmrPowerSaveReq, try to enter hibernate state
    SIG_CEMMR_POWER_RECOVER_REQ = 0x150A,    //CemmrPowerRecoverReq, wake up from hibernate state
    SIG_CEMM_CCM_SET_PARM_REQ,          //CemmCcmSetParmReq
    SIG_CEMM_CCM_GET_PARM_REQ,          //CemmCcmGetParmReq
    SIG_CEMM_CCM_DEV_LOC_MEAS_STATE_IND,
    SIG_CCM_GET_NAS_STATUS_REQ,         //CcmGetNasStatusReq
    SIG_CEMM_OOS_PLMN_SELECT_REQ,       //CemmOosPlmnSelectReq, only used for oos plmn select
    SIG_CCM_EMM_EVENT_STATIS_REQ, //CcmEmmEventStatisOperReq
    SIG_CEMM_CCM_SET_OPERATOR_CONFIG,   // CCM sends this signal to set operator config to EMM
    SIG_CEMM_GTP_PLMN_SEARCH_REQ,    //CemmGtpPlmnSearchReq, only used for gtp searching
    SIG_CEMM_ABORT_GTP_PLMN_SEARCH_REQ,     //CemmAbortGtpPlmnSearchReq
	SIG_CEMM_CCM_GET_EMM_STATE_REQ,
    SIG_CEMM_CCM_SET_LAPI_REQ,   
    SIG_CEMM_CCM_GET_LAPI_REQ,
    SIG_CEMM_PLMN_SET_MCC_BAND_REQ,    //CemmPlmnSetMccBandReq
    SIG_CEMM_PLMN_GET_MCC_BAND_REQ,    //CemmPlmnGetMccBandReq
    
	SIG_CEMM_CCM_SET_ROAMING_DATA_REQ,
	SIG_CEMM_CCM_GET_ROAMING_DATA_REQ,

    /* CERRC -> CEMM */
    SIG_CERRC_CONN_CNF = 0x1530,
    SIG_CERRC_RESUME_CNF,
    SIG_CERRC_RELEASE_CNF,
    SIG_CERRC_RELEASE_IND,
    SIG_CERRC_NAS_SECURITY_KEY_REQ,
    SIG_CERRC_NAS_MSG_IND,
    SIG_CERRC_PAGE_INFO_IND,
    SIG_CERRC_DEACT_CNF,
    SIG_CERRC_CELL_LOCK_CNF,
    SIG_CERRC_PLMN_SEARCH_CNF,          //CerrcPlmnSearchCnf
    SIG_CERRC_PLMN_SEARCH_IND = 0x153A, //CerrcPlmnSearchInd
    SIG_CERRC_ABORT_PLMN_SEARCH_CNF,    //CerrcAbortPlmnSearchCnf
    SIG_CERRC_DRB_INFO_IND,
    SIG_CERRC_ACT_CNF,
    SIG_CERRC_ACT_IND,
    SIG_CERRC_AS_CAPABILITY_IND,
    SIG_CERRC_POWER_RECOVER_CNF = 0x1540,
    SIG_CERRC_NAS_MSG_TRANS_FAILURE_IND,
    SIG_CERRC_NAS_MSG_TRANS_SUCC_IND,
    SIG_CERRC_CONN_NAS_UL_MSG_SUSPEND_IND,     //CerrcNasUlMsgSuspendInd
    SIG_CERRC_CONN_NAS_UL_MSG_RESUME_IND,      //CerrcNasUlMsgResumeInd
    SIG_CERRC_BARRING_ALLEVIATION_IND,   //CerrcBarringAlleviationInd
    SIG_CERRC_SMSCB_ETWS_PRIMARY_DATA_IND,     //CerrcSmscbEtwsPrimaryDataInd
    SIG_CERRC_SMSCB_ETWS_SECOND_DATA_IND,      //CerrcSmscbEtwsSecondDataInd
    SIG_CERRC_SMSCB_CMAS_DATA_IND,             //CerrcSmscbCmasDataInd
    SIG_CERRC_ACESS_BAR_DISABLE_IND,           //CerrcAccessBarDisableInd
    SIG_CERRC_GTP_PLMN_SEARCH_CNF,


    /* USIM -> CEMM */
    SIG_CEMM_SIM_APP_READY_IND = 0x1560,//CemmSimAppReadyInd
    SIG_CEMM_SIM_READ_DATA_CNF,         //CemmSimReadDataCnf
    SIG_CEMM_SIM_WRITE_DATA_CNF,        //CemmSimWriteDataCnf
    SIG_CEMM_SIM_AUTHENTICATE_CNF,
    SIG_CEMM_SIM_REMOVE_IND,
    SIG_CEMM_SIM_USAT_REFRESH_IND,
    SIG_CEMM_SIM_USAT_IMEI_SV_REQ,
    SIG_CEMM_SIM_USAT_REFRESH_FCN_IND,

    /* DR/UP/Other -> CEMM */
    SIG_CEMM_DR_REESTABLISH_REQ = 0x1580,    //CemmDrReestablishReq

    SIG_CEMM_END = 0x15FF,

    /*********************************************************************
     *********************************************************************
     * signal to CESM module
     *********************************************************************
     *********************************************************************/
    SIG_CESM_BASE = 0x1600,
    SIG_CCM_CESM_SET_EPS_BEARER_CTX_REQ,
    SIG_CCM_CESM_GET_EPS_BEARER_CTX_REQ,    /*CcmCesmGetEpsBearerCtxReq */
    SIG_CCM_CESM_DEL_EPS_BEARER_CTX_REQ,
    SIG_CCM_CESM_ACT_EPS_BEARER_CTX_REQ,
    SIG_CCM_CESM_DEACT_EPS_BEARER_CTX_REQ,
    SIG_CCM_CESM_MOD_EPS_BEARER_CTX_REQ,
    SIG_CCM_CESM_GET_ALL_BEARERS_BASIC_INFO_REQ,    /* CcmCesmGetAllBearersBasicInfoReq */
    SIG_CCM_CESM_SET_DED_EPS_BEARER_CTX_REQ,
    SIG_CCM_CESM_DEL_DED_EPS_BEARER_CTX_REQ,
    //SIG_CCM_CESM_READ_BEARER_CTX_DYN_PARAM_REQ,
    //SIG_CCM_CESM_GET_DEFINED_CID_IPADDR_PARAM_REQ,
    //SIG_CCM_CESM_GET_APN_RATE_CTRL_REQ,
    SIG_CCM_CESM_SET_DEFINE_TFT_PARAM_REQ,
    SIG_CCM_CESM_DELETE_TFT_PARAM_REQ,
    //SIG_CCM_CESM_GET_DEFINE_TFT_PARAM_REQ,
    SIG_CCM_CESM_SET_DEFINE_EPS_QOS_REQ,
    //SIG_CCM_CESM_GET_DEFINED_EPS_QOS_REQ,
    SIG_CCM_CESM_DELETE_EPS_QOS_REQ,
    //SIG_CCM_CESM_SEND_DATA_VER_CP_REQ,
    SIG_CCM_CESM_ATTACHED_BEARER_CTX_PRESET_REQ,
    SIG_CCM_CESM_GET_ATTACH_BEARER_CTX_REQ,
    SIG_CCM_CESM_SET_MT_CP_DATA_REPORT_CFG_REQ,
    SIG_CCM_CESM_GET_MT_CP_DATA_REPORT_CFG_REQ,
    SIG_CCM_CESM_SET_DEFINE_AUTH_CTX_REQ,
    SIG_CCM_CESM_SET_APN_CLASS_CFG_REQ,
    SIG_CCM_CESM_GET_APN_DISABLE_STATUS_REQ,
    SIG_CCM_CESM_SET_APN_DISABLE_STATUS_REQ,
    SIG_CCM_CESM_GET_EPS_BEARERS_CTX_REQ,
    SIG_CCM_CESM_GET_ALL_BEARER_BASIC_INFO_REQ,

    /* DR -> ESM*/
    SIG_CESM_UL_DATA_TRANS_REQ = 0x16A0,     //CesmUlDataTransReq

    SIG_CESM_END = 0x16FF,

    /*********************************************************************
     *********************************************************************
     * signal to SMS module
     *********************************************************************
     *********************************************************************/
    SIG_CESMS_BASE = 0x1700,
    SIG_CEMM_SMS_SEND_MESSAGE_REQ,      //CemmSmsSendMessageReq
    SIG_CEMM_SMS_SEND_COMMAND_REQ, //CemmSmsCommandReq
    SIG_CEMM_SMS_CONFIG_REQ,            //CemmSmsConfigReq
    SIG_CEMM_SMS_DELIVER_REPORT_REQ,    //CemmSmsDeliverReportReq
    SIG_CEMM_SMS_SEND_RP_REPORT_REQ,    //CemmSmsSendRpReportReq
    /* CEDR->CESMS */
    SIG_CEDR_SMS_TEST_LOOP_UL_DATA_TRANS_REQ, //CeDrSmsTestLoopUlDataTransReq
    SIG_CESMS_END = 0x1750,

    /*********************************************************************
     *********************************************************************
     * signal to CESS module
     *********************************************************************
     *********************************************************************/
    SIG_CESS_BASE = 0x1751,
    SIG_CCM_CESS_LPP_UNIT_DATA_REQ,
    SIG_CCM_CESS_LCS_UNIT_DATA_REQ,
    SIG_CCM_CESS_GET_CMTLRA_REQ,

    SIG_CESS_END = 0x17FF,

    /*********************************************************************
     *********************************************************************
     * signal to CERRC module
     *********************************************************************
     *********************************************************************/
    SIG_CERRC_BASE = 0x1800,

    /* CEMM->CERRC */
    SIG_CERRC_UE_CONFIG_REQ,
    SIG_CERRC_POWER_RECOVER_REQ,
    SIG_CERRC_DEACT_REQ,
    SIG_CERRC_CELL_LOCK_REQ,
    SIG_CERRC_PLMN_SEARCH_REQ,          //CerrcPlmnSearchReq, 0x1805
    SIG_CERRC_NEXT_PLMN_SEARCH_REQ,     //CerrcNextPlmnSearchReq
    SIG_CERRC_ABORT_PLMN_SEARCH_REQ,    //CerrcAbortPlmnSearchReq
    SIG_CERRC_ACT_REQ,
    SIG_CERRC_CONN_REQ,
    SIG_CERRC_NAS_MSG_REQ = 0x180A,  //0x180A
    SIG_CERRC_RESUME_REQ,
    SIG_CERRC_RELEASE_REQ,
    SIG_CERRC_NAS_SECURITY_KEY_CNF,
    SIG_CERRC_NAS_INFO_UPDATE_REQ,
    SIG_CERRC_AUTH_FAIL_IND,
    SIG_CERRC_SELECTED_PLMN_IND = 0x1810,    //CerrcUpdateSelectedPlmnInd

    /* CCM(LPP) -> CERRC */
    SIG_CERRC_LOC_MEAS_REQ = 0x1880,
    SIG_CERRC_STOP_LOC_MEAS_REQ,
    SIG_CERRC_EARLY_LOC_MEAS_REQ,
    /* CCM -> CERRC */
    SIG_CERRC_CCM_SET_PARAM_REQ,        //CerrcCcmSetParamReq
    SIG_CERRC_CCM_GET_PARAM_REQ,        //CerrcCcmGetParamReq
    SIG_CCM_GET_ERRC_PHY_STATUS_REQ,    //CcmGetErrcPhyStatusReq

    SIG_CERRC_CCM_BASIC_CELL_LIST_INFO_REQ,     //CerrcCcmBasicCellListInfoReq
    SIG_CERRC_CCM_ABORT_BASIC_CELL_LIST_INFO_REQ,   //CerrcCcmAbortBasicCellListInfoReq
    SIG_CCM_ERRC_PHY_STATIS_OPER_REQ,   //CcmErrcPhyStatisOperReq
    
	SIG_CCM_ERRC_EVENT_STATIS_REQ, //CcmErrcEventStatisOperReq
    
	SIG_CERRC_CCM_SET_CE_INFO_REQ,
    SIG_CERRC_CCM_GET_CE_INFO_REQ,
    SIG_CERRC_CCM_SET_OPERATOR_CONFIG,
    SIG_CERRC_CCM_GET_DRX_INFO_REQ,
	SIG_CERRC_GTP_PLMN_SEARCH_REQ,

    /* L1->CERRC */
    // move to psl1sigid.h

    /* UP->CERRC */
    SIG_CECP_DATA_IND = 0x18A0,  //0x18A0
    SIG_CECP_DATA_CNF,  //CecpDataCnf, whether UL ERRC PDU has been sent
    SIG_CEPDCP_INTEGRITY_CALC_CNF,
    SIG_CEPDCP_INTEGRITY_CHECK_FAIL_IND,
    SIG_CERLC_RETRANS_MAX_FAIL_IND,
    SIG_CERLC_CONNECT_RELEASE_ACK_CNF,  //0x1815
    //SIG_CERLC_DEDICATED_RECONFIG_ACK_CNF,
    SIG_CEMAC_RESET_CNF,
    SIG_CEMAC_RA_IND,
    SIG_CEMAC_CCCH_DATA_IND,
    SIG_CEMAC_TA_TIMER_EXPIRY_IND,
    SIG_CPDCP_COUNTERCHECK_CNF,
    SIG_CEUP_ABORT_IND,        //CeupAbortInd, ERRC will go idle

    /*********************************************************************
     *********************************************************************
     * signal to CE user plane (L2) module
     *********************************************************************
     *********************************************************************/
    SIG_CEUP_BASE = 0x1900,
    SIG_CEDR_BASE = 0x1900, /*signal to DR module, DR and L2 just in same task*/

    /* CERRC->UP */
    SIG_CEMAC_CCCH_DATA_REQ,            //CemacCcchDataReq
    SIG_CEMAC_RESET_REQ,                //CemacResetReq
    SIG_CEMAC_SCHEDULE_REQ_RELEASE_IND, //CemacScheduleReqReleaseInd
    SIG_CECP_DATA_REQ,                  //CecpDataReq
    SIG_CEUP_CONFIG_REQ,                //CeupConfigReq
    SIG_CEUP_REESTABLISH_REQ,           //CeupReestablishReq
    SIG_CEUP_RESUME_REQ,                //CeupResumeReq
    SIG_CEUP_SUSPEND_REQ,               //CeupSuspendReq
    SIG_CEPDCP_CIPHER_INTEGRITY_CONFIG_REQ,     //CepdcpCipherIntegrityConfigReq
    SIG_CERLC_CONNECT_RELEASE_ACK_REQ = 0x190A, //CerlcConnectReleaseAckReq
    SIG_CEMAC_MAIN_CONFIG_REQ,          //CemacMainConfigReq
    //SIG_CERLC_DEDICATED_RECONFIG_ACK_REQ,   //CerlcDedicatedReconfigAckReq

    /* -> CEPDCP */
    SIG_CEUP_DATA_REQ,                  //CeupDataReq
    /*counter check*/
    SIG_CEPDCP_COUNTERCHECK_REQ,

    /* CCM -> UP */
    SIG_CCM_GET_L2_STATUS_REQ,          //CcmGetL2StatusReq
    SIG_CCM_L2_STATIS_OPER_REQ,         //CcmL2StatisOperReq
    SIG_CCM_L2_NO_MORE_PS_DATA_REQ,     //CcmL2NoMorePsDataReq


    /* CERRC -> DR*/
    SIG_CEDR_POWER_RECOVER_DRB_INFO_IND = 0x1940,    //CedrPowerRecoverDrbInfoInd

    /* CEMM/CESM/CESMS -> DR */
    SIG_CEDR_FEATURE_SUPPORT_IND,       //CedrFeatureSupportInd
    SIG_CEDR_BEARER_ACTIVATE_IND,       //CedrBearerActivateInd
    SIG_CEDR_BEARER_MODIFY_IND,         //CedrBearerModifyInd
    SIG_CEDR_BEARER_DEACTIVATE_IND,     //CedrBearerDeactivateInd
    SIG_CEDR_BEARER_SUSPEND_IND,        //CedrBearerSuspendInd
    SIG_CEDR_BEARER_RESUME_IND,         //CedrBearerResumeInd
    SIG_CEMM_DR_REESTABLISH_RSP,        //CemmDrReestablishRsp
    SIG_CEMM_DR_SERVICE_AVAILABLE_IND,  //CemmDrServiceAvailableInd

    /* CEMMTC -> DR */
    SIG_CEDR_ACT_TEST_MODE_IND,         //CedrActTestModeInd
    SIG_CEDR_DEACT_TEST_MODE_IND,       //CedrDeactTestModeInd
    SIG_CEDR_OPEN_TEST_MODE_IND,        //CedrOpenTestModeInd
    SIG_CEDR_CLOSE_TEST_MODE_IND,       //CedrCloseTestModeInd

    SIG_CEDR_NAS_TEST_LOOP_DATA_REQ,    //CedrNasTestLoopDataReq
    SIG_CEDR_BEARER_DEFINED_IND,        //CeDrBearerDefinedInd

    /* -> DR*/
    SIG_CEDR_UL_DATA_REQ,               //CedrUlDataReq

    SIG_CEDR_PDCP_TEST_LOOP_DATA_REQ_ISR,   //CedrPdcpTestLoopDataReq
    SIG_CEDR_SMS_TEST_LOOP_DATA_REQ,    //CeDrSmsTestLoopDataReq

    /* CCM -> DR*/
    SIG_CEDR_PS_DATA_PLANE_TRANS_REQ,   //CedrPsDataPlaneTransReq
    SIG_CCM_CEDR_PKT_STATS_REQ,             //CcmCedrPktStatsReq  

    /* PDCP -> DR*/
    SIG_CEDR_PDCP_DL_NON_IP_DATA_IND_ISR,   //CedrPdcpDlNonIpDataIndIsr

    SIG_CEDR_SET_NETIF_INFO_REQ,            //NetifFastChkInfo


    /*********************************************************************
     *********************************************************************
     * signal to CUICC controllor
     *********************************************************************
     *********************************************************************/
    SIG_CUICC_CTRL_BASE = 0x1A00,
    /*signal from CCM to CUICC controller */
    SIG_CCM_SIM_INITIALISE,
    SIG_CCM_SIM_APP_INIT_REQ,
    SIG_CCM_SIM_GEN_ACCESS_REQ,
    SIG_CCM_SIM_TERMINATE_SESSION_REQ,
    SIG_CCM_SIM_READ_DATA_REQ,
    SIG_CCM_SIM_UPDATE_DATA_REQ,
    SIG_CCM_SIM_PIN_OPERATE_REQ,
    SIG_CCM_SIM_OPEN_LOGICAL_CHANNEL_REQ,
    SIG_CCM_SIM_CLOSE_LOGICAL_CHANNEL_REQ,
    SIG_CCM_SIM_RESTORE_DATA_REQ = 0x1A0A,
    SIG_CCM_SIM_SET_SIM_SLEEP_REQ,
    SIG_CCM_SIM_SET_SIM_WRITE_COUNTER_REQ,
#ifdef FEAT_RPM
	SIG_CCM_SIM_RPM_UPDATE_OM_PARAM_REQ = 0x1A0D,   //Signal added by QCOM, rsvd here
    SIG_CCM_SIM_READ_RPM_PARAM_REQ = 0x1A0E,        //Signal added by QCOM, rsvd here
#endif
    SIG_CCM_SIM_GEN_LOGICAL_CHANNEL_ACCESS_REQ,
    SIG_CCM_SIM_SET_SIM_PRESENCE_DETECT_REQ,
    SIG_CCM_SIM_GET_SUBSCRIBER_NUMBER_REQ,
    /*USAT*/
    SIG_CCM_SIM_USAT_TERMINAL_PROFILE_REQ = 0x1A20,
    SIG_CCM_SIM_USAT_PROACTIVE_COMMAND_RSP,
    SIG_CCM_SIM_USAT_REFRESH_RSP,
    SIG_CCM_SIM_USAT_PROVIDE_LOCAL_INFO_RSP,
    SIG_CCM_SIM_USAT_SET_UP_EVENT_LIST_RSP,
    SIG_CCM_SIM_USAT_OPEN_CHANNEL_RSP,
    SIG_CCM_SIM_USAT_CLOSE_CHANNEL_RSP,
    SIG_CCM_SIM_USAT_SEND_DATA_RSP,
    SIG_CCM_SIM_USAT_RECEIVE_DATA_RSP,
    SIG_CCM_SIM_USAT_GET_CHANNEL_STATUS_RSP,
    SIG_CCM_SIM_USAT_EVENT_DOWNLOAD_REQ = 0x1A2A,
  //SIG_CCM_SIM_USAT_TIMER_EXPIRATION_REQ,
  //SIG_CCM_SIM_USAT_MENU_SELECTION_REQ,
    SIG_CCM_SIM_USAT_SMS_PP_DOWNLOAD_REQ,
    SIG_CCM_SIM_USAT_MOSM_CONTROL_REQ,
   //SIG_CCM_SIM_USAT_NETWORK_MEAS_REQ,

    /*signal from CEMM to CUICC controller */
    SIG_CEMM_SIM_READ_DATA_REQ = 0x1A40,    //CemmSimReadDataReq
    SIG_CEMM_SIM_WRITE_DATA_REQ,            //CemmSimWriteDataReq
    SIG_CEMM_SIM_LOCAL_INFO_RSP,
    SIG_CEMM_SIM_AUTHENTICATE_REQ,
    SIG_CEMM_SIM_POWER_REDUCE_IND,
    SIG_CEMM_SIM_ECM_STATE_IND,
    SIG_CEMM_SIM_USAT_REFRESH_RSP,
    SIG_CEMM_SIM_USAT_IMEI_SV_CNF,
    /* added new signal for CEMM-SIM here */

    /*signal from CUICC driver to CUICC controller */
    SIG_UICC_CTRL_DRV_CARD_INSERTED_IND = 0x1A50,
    SIG_UICC_CTRL_DRV_CMD_RSP,
    SIG_UICC_CTRL_DRV_CARD_REMOVED_IND,
    SIG_UICC_CTRL_DRV_ERROR_IND,

    /* internal signal*/
    SIG_USAT_PROACTIVE_CMD_TO_FETCH_REQ,
    SIG_UICC_QUEUE_END_IND,
    SIG_UICC_CTRL_DRV_LARGE_APDU_RSP,


    /*********************************************************************
     *********************************************************************
     * signal to CUICC driver
     *********************************************************************
     *********************************************************************/
    SIG_CUICC_DRV_BASE = 0x1B00,
    SIG_UICC_CTRL_DRV_INIT_CARD,
    SIG_UICC_CTRL_DRV_RESET_REQ,
    SIG_UICC_CTRL_DRV_CMD_REQ,
    SIG_UICC_CTRL_DRV_TERMINATE_REQ,
    SIG_UICC_CTRL_DRV_CLOCK_STOP_REQ,
    SIG_UICC_PMU_DEEP_SLEEP_DEACTIVATE_IND,
    SIG_UICC_CTRL_DRV_LARGE_APDU_REQ,


    /* CERRC->CEHPY */
    // move to psl1sigid.h

    /*PS totoal 8*1024 signals*/
    SIG_PS_END = 0x3000-1

    /*
     * 0x3000 - 0x30FF, used for signal between: PS <-> PHY
    */

}PSSIGID;



#endif

