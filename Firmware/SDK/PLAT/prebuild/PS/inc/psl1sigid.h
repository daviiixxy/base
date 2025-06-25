#ifndef _PS_L1_SIGID_H
#define _PS_L1_SIGID_H

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - psl1sigid.h
 Description:    - Signal ID defination between PHY and PS
 History:        - 10/10/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/

typedef enum PSL1SIGIDTAG
{

    PS_L1_SIGNAL_BASE = 0x3000,

    /*
     * CERRC -> CEHPY
     */
    SIG_CERRC_TO_CEPHY_BASE = 0x3000,
    SIG_CEPHY_INIT_CONFIG_REQ,
    SIG_CEPHY_CELL_SEARCH_REQ,   //CephyCellSearchReq
    SIG_CEPHY_NEXT_CELL_SEARCH_REQ,
    SIG_CEPHY_DRX_CELL_SEARCH_REQ,
    SIG_CEPHY_DRX_NEXT_CELL_SEARCH_REQ, //0x3005
    SIG_CEPHY_SYS_INFO_REQ,
    SIG_CEPHY_SYS_INFO_STOP_REQ, //0x3007
    SIG_CEPHY_NCELL_SYS_INFO_REQ,
    SIG_CEPHY_NCELL_SYS_INFO_STOP_REQ,
    SIG_CEPHY_SIB1_CONFIG_REQ = 0x300A,  //0x300A
    SIG_CEPHY_COMMON_CONFIG_REQ,
    SIG_CEPHY_PAGING_CONFIG_REQ,
    SIG_CEPHY_INTRA_FREQ_CONFIG_REQ,
    SIG_CEPHY_INTER_FREQ_CONFIG_REQ,
    SIG_CEPHY_CELL_MEAS_REQ,    //0x300F
    SIG_CEPHY_CELL_MEAS_STOP_REQ = 0x3010,
    SIG_CEPHY_CELL_RESELECT_REQ,
    SIG_CEPHY_DEACT_REQ,
    SIG_CEPHY_DEDICATED_CONFIG_REQ,
    SIG_CEPHY_LOC_MEAS_REQ = 0x3014,
    SIG_CEPHY_STOP_LOC_MEAS_REQ = 0x3015,
    SIG_CEPHY_EARLY_LOC_MEAS_REQ = 0x3016,
    SIG_CEPHY_GET_STATUS_REQ = 0x3017,
    SIG_CEPHY_BASIC_CELL_INFO_REQ = 0x3018, //CephyBasicCellInfoReq
    SIG_CEPHY_NEXT_BASIC_CELL_INFO_REQ = 0x3019,
    SIG_CEPHY_BASIC_CELL_INFO_STOP_REQ = 0x301A,
    SIG_CEPHY_IN_SYNC_CTRL_REQ = 0x301B, //CephyInSyncCtrlReq
    SIG_CEPHY_POWER_RECOVER_REQ = 0x301C, //CephyPowerRecoverReq
    SIG_CEPHY_NONANCHOR_NPRACH_FMT2_CONFIG_REQ = 0x301D, //CephyNonAnchorNprachFmt2ConfigReq
    SIG_CEPHY_CE_INFO_REQ = 0x301E, //CephyCEInfoReq
    SIG_CEPHY_STATIS_OPER_REQ = 0x301F, //CephyStatisOperReq
    SIG_CEPHY_NPRS_SAMPLE_DUMP_REQ = 0x3020, //CephyNPRSSampleDumpReq
    SIG_CEPHY_SPEED_EST_REQ = 0x3021, //CephySpeedEstReq
    SIG_CEPHY_SET_MAX_TXPOWER_REQ = 0x3022, //CephySetMaxTxPowerReq

    //SIG_CEPHY_RESUME_CONFIG_REQ,  //replace with SIG_CEPHY_DEDICATED_CONFIG_REQ

    /* CERRC ->CEPHY signal add here */
    SIG_CEPHY_CONN_MEAS_GAP_CONFIG_REQ = 0x3030, //used for emtc in rrc connected state
    SIG_CEPHY_CONN_MEAS_CONFIG_REQ = 0x3031, //used for emtc in rrc connected state
    SIG_CEPHY_HANDOVER_REQ = 0x3032, //eMTC/Cat1 only
    SIG_CEPHY_HANDOVER_COMMOM_CONFIG_REQ = 0x3033,  //eMTC/Cat1 only

    SIG_CERRC_TO_CEPHY_END = 0x303F,

    /*
     * CEUP -> CEPHY
     */
    SIG_CEUP_TO_CEPHY_BASE = 0x3040,
    SIG_CEPHY_RANDOM_ACCESS_REQ,    //CephyRandomAccessReq
    SIG_CEPHY_TA_CMD_REQ,           //CephyTaCmdReq
    SIG_CEPHY_MSG3_DATA_REQ,        //CephyMsg3DataReq
    SIG_CEPHY_CRNTI_CONFIG_REQ,     //CephyCrntiConfigReq
    SIG_CEPHY_MAC_RESET_REQ,        //CephyMacResetReq, 0x3025
    SIG_CEPHY_DRX_CMD_REQ,          //CephyDrxCmdReq
    SIG_CEPHY_UL_DATA_REQ,          //CephyUlDataReq
    SIG_CEPHY_START_TIMER_REQ,      //CephyStartTimerReq
    SIG_CEPHY_STOP_TIMER_REQ,       //CephyStopTimerReq
    SIG_CEPHY_CONN_REL_HARQ_ACK_RSLT_REQ,    //CephyConnRelHarqAckRsltReq

    /* CERRC ->CEPHY signal add here */

    SIG_CEUP_TO_CEPHY_END = 0x305F,


    /*
     * CEPHY -> CERRC
     */
    SIG_CEPHY_TO_CERRC_BASE = 0x3060,
    SIG_CEPHY_INIT_CONFIG_CNF,      //CephyInitConfigCnf
    SIG_CEPHY_CELL_SEARCH_CNF,      //CephyCellSearchCnf
    SIG_CEPHY_DRX_CELL_SEARCH_CNF,//CephyDrxCellSearchCnf
    SIG_CEPHY_SYS_INFO_IND,         //CephySysInfoInd
    SIG_CEPHY_NCELL_SYS_INFO_IND,   //CephyNcellSysInfoInd, 0x3045
    SIG_CEPHY_CELL_MEAS_IND,        //CephyCellMeasInd
    SIG_CEPHY_DEACT_CNF,            //
    SIG_CEPHY_PAGING_IND,           //CephyPagingInd
    SIG_CEPHY_SYNC_STATUS_IND,      //CephySyncStatusInd
    SIG_CEPHY_CONN_STATIS_INFO_IND = 0x306A,//CephyConnStatisInfoInd
    SIG_CEPHY_DATA_INACTIVITY_TIMER_EXPIRY, //CephyDataInactivityTimerExpiry
    SIG_CEPHY_RESET_IND,            //CephyResetInd
    SIG_CEPHY_START_RESELECTION_IND,   //CephyStartRelectionInd
    SIG_CEPHY_LOC_MEAS_CNF,
    SIG_CEPHY_STOP_LOC_MEAS_CNF,
    SIG_CEPHY_EARLY_LOC_MEAS_CNF = 0x3070,
    SIG_CEPHY_GET_STATUS_CNF,
    SIG_CEPHY_BASIC_CELL_INFO_CNF = 0x3072, //CephyBasicCellInfoCnf
    SIG_CEPHY_POWER_RECOVER_CNF, //CephyPowerRecoverCnf
    SIG_CEPHY_CE_INFO_IND = 0x3074, //CephyCEInfoInd
    SIG_CEPHY_STATIS_INFO_IND = 0x3075, //CephyStatisInfoInd
    SIG_CEPHY_NPRS_SAMPLE_DUMP_IND = 0x3076, //CephyNPRSSampleDumpInd
    SIG_CEPHY_SPEED_EST_CNF = 0x3077, //CephySpeedEstCnf
    SIG_CEPHY_RSSISCAN_IND = 0x3078,    // CephyRssiScanInd
    /* CEPHY ->CERRC signal add here */
    SIG_CEPHY_HANDOVER_CNF = 0x3090, //eMTC/Cat1 only

    SIG_CEPHY_TO_CERRC_END = 0x309F,


    /* CEPHY -> CEUP */
    SIG_CEPHY_TO_CEUP_BASE = 0x30A0,
    SIG_CEPHY_NPDCCH_ORDER_IND,     //CephyNpdcchOrderInd
    SIG_CEPHY_PREAMBLE_TRANS_MAX_IND,   //CephyPreambleTransMaxInd
    SIG_CEPHY_RECV_RAR_IND,         //CephyRecvRARInd
    SIG_CEPHY_CRNTI_CR_SUCC_IND,    //CephyCrntiCRSuccInd
    SIG_CEPHY_MAC_RESET_CNF,        //CephyMacResetCnf 0x3065
    SIG_CEPHY_DL_DATA_IND,          //CephyDlDataInd
    SIG_CEPHY_UL_GRANT_IND,         //CephyUlGrantInd
    SIG_CEPHY_TIMER_EXPIRY_IND,     //CephyTimerExpiryInd
    SIG_CEPHY_RACH_CANCEL_IND,      //CephyRachCancelInd
    SIG_CEPHY_CONN_REL_HARQ_ACK_RSLT_CNF,    //CephyConnRelHarqAckRsltCnf

    /* CEPHY ->CEUP signal add here */

    SIG_CEPHY_TO_CEUP_END = 0x30BF,


    /*PS <-> L1 totoal 255 signals*/
    PS_L1_SIGNAL_END = 0x30FF

}PSL1SIGID;


#endif

