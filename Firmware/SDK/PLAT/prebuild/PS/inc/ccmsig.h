#ifndef __CCM_SIG_H__
#define __CCM_SIG_H__

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - ccmsig.h
 Description:    - Signal definition to CCM (CIoT Connection Management)
 History:        - 19/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/

/******************************************************************************
 * Includes
******************************************************************************/
#include "pssys.h"
#include "pscommtype.h"
#include "nascommon.h"
#include "cmips.h"
#include "cmidev.h"

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

#define CCM_SIG_H_COMMON_LOC


/******************************************************************************
 *****************************************************************************
 * signal structure to CCM REG start from here
 *****************************************************************************
******************************************************************************/
#define CCM_SIG_H_CCM_REG_SIG_LOC

typedef enum CcmCemmRcCodeEnum_Tag
{
    CCM_CEMM_SUCC = 0,

    CCM_CEMM_CONFLICT = 1,
    CCM_CEMM_NOT_SUPPORT = 2,
    CCM_NAS_BUSY = 3,

    CCM_CEMM_RC_MAX = 0xFF
}CcmCemmRcCodeEnum;


typedef enum CemmRegStatusEnum_Tag
{
    CEMM_NOT_REG = 0,       //not registered, UE is not searching an operater to register to

    /*REG STATUS*/
    CEMM_REG_HOME = 1,      //registered, home network
    CEMM_REG_ROAMING = 2,   //registered, roaming

    /*DEREG STATUS*/
    CEMM_MO_DETACH,         //mo detach, user triggered
    CEMM_MT_DETACH,         //mt detach, network triggered
    //CEMM_LOCAL_DETACH,

    CEMM_ATTACH_REJECT,     //attach rejected by network
    CEMM_TAU_REJECT,        //tau rejected by network
    CEMM_AUTH_FAIL,         //ue authentication network failed
    CEMM_AUTH_NW_REJECT,    //network authentication ue failed
    CEMM_SR_REJECT,         //service rejected by network

    //CEMM_TIME_OUT,

    CEMM_REG_DENIED,        //attach abnormal,attempt counter is equal to 5, start t3402

    CEMM_REG_TRYING,        //tau abnormal,attempt counter is less than 5, try to register, report cereg:2

    CEMM_REG_MAX = 0xFF
}CemmRegStatusEnum;


typedef enum CemmEmmCauseEnum_Tag
{
    EMM_NO_CAUSE = 0,
    EMM_NW_CAUSE_BASE = 1,
    EMM_IMSI_UNKNOWN_IN_HSS = 0x02,
    EMM_ILLEGAL_UE = 0x03,
    // ...
    /*
     *  0 0 0 0 0 0 1 0 IMSI unknown in HSS
        0 0 0 0 0 0 1 1 Illegal UE
        0 0 0 0 0 1 0 1 IMEI not accepted
        0 0 0 0 0 1 1 0 Illegal ME
        0 0 0 0 0 1 1 1 EPS services not allowed
        0 0 0 0 1 0 0 0 EPS services and non-EPS services not allowed
        0 0 0 0 1 0 0 1 UE identity cannot be derived by the network
        0 0 0 0 1 0 1 0 Implicitly detached
        0 0 0 0 1 0 1 1 PLMN not allowed
        0 0 0 0 1 1 0 0 Tracking Area not allowed
        0 0 0 0 1 1 0 1 Roaming not allowed in this tracking area
        0 0 0 0 1 1 1 0 EPS services not allowed in this PLMN
        0 0 0 0 1 1 1 1 No Suitable Cells In tracking area
        0 0 0 1 0 0 0 0 MSC temporarily not reachable
        0 0 0 1 0 0 0 1 Network failure
        0 0 0 1 0 0 1 0 CS domain not available
        0 0 0 1 0 0 1 1 ESM failure
        0 0 0 1 0 1 0 0 MAC failure
        0 0 0 1 0 1 0 1 Synch failure
        0 0 0 1 0 1 1 0 Congestion
        0 0 0 1 0 1 1 1 UE security capabilities mismatch
        0 0 0 1 1 0 0 0 Security mode rejected, unspecified
        0 0 0 1 1 0 0 1 Not authorized for this CSG
        0 0 0 1 1 0 1 0 Non-EPS authentication unacceptable
        0 0 1 0 0 0 1 1 Requested service option not authorized in this
        PLMN
        0 0 1 0 0 1 1 1 CS service temporarily not available
        0 0 1 0 1 0 0 0 No EPS bearer context activated
        0 0 1 0 1 0 1 0 Severe network failure
        0 1 0 1 1 1 1 1 Semantically incorrect message
        0 1 1 0 0 0 0 0 Invalid mandatory information
        0 1 1 0 0 0 0 1 Message type non-existent or not implemented
        0 1 1 0 0 0 1 0 Message type not compatible with the protocol
        state
        0 1 1 0 0 0 1 1 Information element non-existent or not
        implemented
        0 1 1 0 0 1 0 0 Conditional IE error
        0 1 1 0 0 1 0 1 Message not compatible with the protocol state
        0 1 1 0 1 1 1 1 Protocol error, unspecified
    */
    EMM_PROTOCOL_ERROR_UNSPECIFIED = 0x6F,

    EMM_INTERNAL_CAUSE_BASE = 0x100,
    EMM_INTERNAL_CUASE_AUTHENTICATION_REJECT,
    //...

    EMM_MAX_CAUSE = 0xFFFF
}CemmEmmCauseEnum;

typedef enum CemmPlmnSelectState_Tag
{
    CEMM_PLMN_SELECT_STATE_DEACTIVATED         = 0,
    CEMM_PLMN_SELECT_STATE_FG_PLMN_SEARCHING   = 1,
    CEMM_PLMN_SELECT_STATE_PLMN_SELECTED       = 2,
    CEMM_PLMN_SELECT_STATE_PLMN_OOS_SLEEP      = 3
}CemmPlmnSelectState;

/******************************************************************************
 * CemmrRegCnf
 * SIG_CEMMR_REG_CNF
******************************************************************************/
typedef struct CemmrRegCnf_Tag
{
    UINT8   rcCode;       // CcmCemmRcCodeEnum, 0 - allow to do CemmrRegReq
    UINT8   nwMode;       // NwMode, try to do registration, by now NB only
    UINT8   serviceType;  // UeService, EPS only
    UINT8   plmnSelectType;   // CemmPlmnSelectTypeEnum, PLMN search type: auto / maunal
}CemmrRegCnf;

/******************************************************************************
 * CemmrDeregCnf
 * SIG_CEMMR_DEREG_CNF
******************************************************************************/
typedef struct CemmrDeregCnf_Tag
{
    UINT8   detachType;
    UINT8   reserved[3];
}CemmrDeregCnf;

/******************************************************************************
 * CemmManualPlmnSearchCnf
 * SIG_CEMM_MANUAL_PLMN_SEARCH_CNF
 * Only used for manual PLMN search procedure, confirm the PLMN found
 * CEMM PLMN sub-module should report the PLMN in suitable order:
 * The list of operators shall be in order:
 * 1> home network, RPLMN
 * Networks referenced in SIM or active application in the UICC (GSM or USIM) in the following order:
 * 2> HPLMN selector,
 * 3> User controlled PLMN selector,
 * 4> Operator controlled PLMN selector and PLMN selector (in the SIM or GSM application),
 * 5> and other networks
******************************************************************************/
#define CCM_CEMM_MAX_PLMN_NUM 10
typedef struct CemmManualPlmnSearchCnf_Tag
{
    UINT8   rcCode;         //CcmCemmRcCodeEnum, 0, just means manual PLMN search finished normally
    UINT8   plmnNum;        //if "manualMode" == CEMM_BCINFO_MANUAL_PLMN_SEARCH, "plmnNum" = serving cell info (1) + neighber cell number, if set to 0, no serving cell found
    UINT8   manualMode;     //CemmManualSearchMode
    UINT8   reserved0;

    union
    {
        /* CEMM_COPS_MANUAL_PLMN_SEARCH */
        struct
        {
            BOOL    current;
            BOOL    available;
            BOOL    forbidden;
            UINT8   nwMode;     //NwMode
            Plmn    plmn;
        }plmnList[CCM_CEMM_MAX_PLMN_NUM];   //80 bytes

        /* CEMM_BCINFO_MANUAL_PLMN_SEARCH */
        struct
        {
            CmiDevSCellBasicInfo    sCellInfo;  //24 bytes
            CmiDevNCellBasicInfo    nCellList[CMI_DEV_NCELL_INFO_CELL_NUM]; //96 bytes
        }cellInfo;  //120 bytes
    }plmnInfo;
}CemmManualPlmnSearchCnf;

/******************************************************************************
 * CemmAbortPlmnSearchCnf
 * SIG_CEMM_ABORT_PLMN_SEARCH_CNF
******************************************************************************/
typedef CemmManualPlmnSearchCnf CemmAbortPlmnSearchCnf;

/******************************************************************************
 * CemmGtpPlmnSearchCnf
 * SIG_CEMM_GTP_PLMN_SEARCH_CNF
******************************************************************************/



typedef struct CemmSib1InfoGtpTag
{
   //Physical Cell ID, range 0 - 503
   UINT16						   phyCellId;

   //Store the found Plmn-Identity
   Plmn 						   plmn;
   //the 28 bits Cell-Identity in SIB1, range 0 - 268435455
   UINT32						   cellId;
   //Tracking Area Code, bit string of size 16
   UINT16						   tac;
}CemmSib1InfoGtp;

typedef struct CemmBasicCellInfoGtpTag
{
    //DL earfcn (anchor earfcn), range 0 - 262143
    UINT32                          earfcn;
    //Physical Cell ID, range 0 - 503
    UINT16                          phyCellId[3];

    //value in units of dBm, value range: -156 ~ -44
    INT16                           rsrp[3];
    //value in units of dB, value range: -34 ~ 25
    INT16                           rsrq[3];

	CemmSib1InfoGtp                sib1data;

    UINT8                           cell_sib1_field[3];

	UINT8                           bServingCell;
	  
}CemmBasicCellInfoGtp;

typedef struct CemmBasicCellElementInfoGtpTag
{
    CemmBasicCellInfoGtp                    data;
    struct CemmBasicCellElementInfoGtpTag *pNext;
}CemmBasicCellInfoGtpElement;


typedef struct CemmGtpPlmnSearchCnfTag
{ 	
    UINT8   rcCode; //CcmCemmRcCodeEnum, 0
    ChannelScanStatus				ChannelStatus[8];
    PlmnListStatus                         status; 	
	//send new structure for GTP in plmn search cnf
   	CemmBasicCellInfoGtpElement    *pGtpInfoFirstElement;
}CemmGtpPlmnSearchCnf;

/******************************************************************************
 * CemmAbortGtpPlmnSearchCnf
 * SIG_CEMM_ABORT_GTP_PLMN_SEARCH_CNF
******************************************************************************/
typedef CemmGtpPlmnSearchCnf CemmAbortGtpPlmnSearchCnf;

#if 0
typedef struct CemmAbortPlmnSearchCnf_Tag
{
    UINT8   rcCode; //CcmCemmRcCodeEnum, 0
    UINT8   plmnNum;
    UINT16  reserved0;

    struct {
        BOOL    current;
        BOOL    available;
        BOOL    forbidden;
        UINT8   nwMode;     //NwMode
        Plmn    plmn;
    }plmnList[CCM_CEMM_MAX_PLMN_NUM];
}CemmAbortPlmnSearchCnf;
#endif

/******************************************************************************
 * CemmrRegInd
 * SIG_CEMMR_REG_IND
 * When CEMM registered a PLMN
******************************************************************************/
/*typedef enum CcmCemmAddUpdateInfoEnum_Tag
{
    NO_ADDITIONAL_INFO = 0,
    CSFB_NOT_PREFER,
    SMS_ONLY,
    ADDITIONAL_RESERVED
}CcmCemmAddUpdateInfoEnum;*/


typedef struct CemmNwPsmInfo_Tag
{
    BOOL    psmTimerPresent;    /* T3324 present */
    UINT8   t3324;
    BOOL    extT3412Present;    /* Extended T3412 present */
    UINT8   extT3412;
    UINT32  t3412s;             /* T3412 value in seconds */
}CemmNwPsmInfo;

typedef struct CemmEdrxInfo_Tag
{
    UINT8   reqEdrxPresent; /* eDRX parameters */
    UINT8   reqEdrxValue;   /* half a byte in a 4 bit format. The eDRX value refers to bit 4 to 1 of
                                                   octet 3 of the Extended DRX parameters information element */
    UINT8   reqPtwPresent;  /*  paging time window parameters */
    UINT8   reqPtwValue;    /* half a byte in a 4 bit format. The eDRX value refers to bit 8 to 5 of
                                                    octet 3 of the Extended DRX parameters information element*/
    UINT8   nwEdrxPresent;  /* whether NW cfg/enable eDRX, if TRUE, nwEdrxValue & nwPtw should be valid */
    UINT8   nwEdrxValue;
    UINT8   nwPtw;          /*
                             * <Paging_time_window>: string type; half a byte in a 4 bit format. The paging time window referes
                             *  to bit 8 to 5 of octet 3 of the Extended DRX parameters information element
                            */
    UINT8   reserved0;
}CemmEdrxInfo;

typedef struct CemmrRegInd_Tag
{
    UINT8   regStatus;      // CemmRegStatusEnum: CCM_CEMM_REG_HOME/CCM_CEMM_REG_ROAMING
    UINT8   nwMode;         // NwMode, try to do registration, by now NB only
    UINT8   serviceType;    // UeService, EPS only
    UINT8   plmnSelectType; // CemmPlmnSelectTypeEnum

    UINT16  tac;
    UINT16  phyCellId;
    UINT32  cellId;

    UINT8   band;
    UINT8   addUpdateInfo;  //AdditionalUpdateResult
    UINT8   nwSptCiotOpt;   //CemmCiotOptTypeEnum
    UINT8   reserved0;

    CemmNwPsmInfo   nwPsmInfo;
    CemmEdrxInfo    edrxInfo;
    Plmn            plmn;
	UINT32   t3402_duration;
}CemmrRegInd;


/******************************************************************************
 * CemmrNwStatusInd
 * SIG_CEMMR_NW_STATUS_IND
 * 1> When NW status changes, such as: OOS <-> IS, CELL ID/TAC changes, or some other PARMs changes
 * 2> No TAU needed,
 * 3> TAU needed, not no REG parameters changes;
 * 4> If some REG parameters changes, need to report : CemmrRegInd
******************************************************************************/
typedef enum CcmCemmUeSrvStatusEnum_Tag
{
    CCM_CEMM_NO_SERVICE = 0,
    CCM_CEMM_IN_SERVICE = 1,
    CCM_CEMM_PLMN_SEARCHING = 2,

    CCM_CEMM_MAX_UE_STATUS = 0xFF
}CcmCemmUeSrvStatusEnum;

typedef enum CcmCemmConnStatusEnum_Tag
{
    CCM_CEMM_CONN_IDLE_MODE = 0,
    CCM_CEMM_CONNECTED_MODE
}CcmCemmConnStatusEnum;

typedef struct CemmrNwServiceStatusInd_Tag
{
    UINT8   ueServiceStatus;    //CcmCemmUeSrvStatusEnum
    UINT8   band;               //if NO SRV, cell/band info are all invalid
    UINT8   connStatus;         //CcmCemmConnStatusEnum if connStatus change, others info is not accurate
    UINT8   reserved;

    Plmn    plmn;
    UINT16  tac;
    UINT16  phyCellId;
    UINT32  cellId;

    UINT8   plmnSelectType;   // CemmPlmnSelectTypeEnum, PLMN search type: auto / maunal
    UINT8   rsvd[2];

    BOOL    bPlmnSelectStateChange;
    UINT8   plmnSelectState;    //CemmPlmnSelectState
    BOOL    oosTimerPresent;
    UINT16  oosTimerS;          //OOS timer value in second
}CemmrNwServiceStatusInd;

/******************************************************************************
 * CemmrDeRegInd
 * SIG_CEMMR_DEREG_IND
 * when PLMN rejected/detached by NW
******************************************************************************/
typedef struct CemmrDeRegInd_Tag
{
    UINT8   deRegType;  //CemmRegStatusEnum
    UINT8   reserved;
    UINT16  emmCause;   //CemmEmmCauseEnum

    BOOL    cellInfoValid;  //if TRUE, just means tac/phyCellId/CellId is present
    BOOL    plmnValid;      //if TRUE, just means Plmn is present
    UINT8   band;
    //BOOL    regOngoing;     //if not registered, whether UE is trying to register to a PLMN later, maybe after OOS timer expiried
    UINT8   reserved1;

    UINT16  tac;
    UINT16  phyCellId;
    UINT32  cellId;

    Plmn    plmn;
}CemmrDeRegInd;

/******************************************************************************
 * CemmrEmmTimerStateInd
 * SIG_CEMMR_EMM_TIMER_STATE_IND
 * EMM timer state indication
******************************************************************************/
typedef enum CemmTimerEnum_Tag
{
    CEMM_T3346 = 0,   //connection blocked timer
    CEMM_T3448,       //CP data blocked timer
    CEMM_TAU_TIMER,    //T3412, or extT3412
    CEMM_T3324
}CemmTimerEnum;

typedef enum CemmTimerStateEnum_Tag
{
    CEMM_TIMER_START,
    CEMM_TIMER_STOP,
    CEMM_TIMER_EXPIRY
}CemmTimerStateEnum;

typedef struct CemmrEmmTimerStateInd_Tag
{
    UINT8   emmTimer;       //CemmTimerEnum
    UINT8   timerState;     //CemmTimerStateEnum
    UINT8   tValuePst;      //whether "timerValueS" value valid
    UINT8   param0;         //reserved

    UINT32  timerValueS;
}CemmrEmmTimerStateInd;

typedef enum CemmPsmModeEnum_Tag
{
    NORMAL_MODE,
    POWER_SAVING_MODE
}CemmPsmModeEnum;

/******************************************************************************
 * SIG_CCM_GET_PSM_MODE_CNF
 * Get current PSM mode
******************************************************************************/
typedef struct CemmrGetPsmModeCnf_Tag
{
    UINT8   psmMode;       //CemmPsmModeEnum
    UINT16  reserved1;     //reserved
    UINT8   reserved2;     //reserved
}CemmrGetPsmModeCnf;

/******************************************************************************
 * SIG_CEMMR_PSM_CHANGE_IND
 * Report current PSM mode
******************************************************************************/
typedef struct CemmrPsmChangeInd_Tag
{
    UINT8   psmMode;       //CemmPsmModeEnum
    UINT16  reserved1;     //reserved
    UINT8   reserved2;     //reserved
}CemmrPsmChangeInd;

/******************************************************************************
 * SIG_CEMMR_PLMN_STATE_CHANGE_IND
 * Report current PLMN select state
******************************************************************************/
typedef struct CemmrPlmnSelectStateInd_Tag
{
    UINT8   plmnSelectState;        //CemmPlmnSelectState
    BOOL    oosTimerPresent;
    UINT16  oosTimerS;              //OOS timer value in second
}CemmrPlmnSelectStateInd;

/******************************************************************************
 * SIG_CEMMR_CONN_STATE_CHANGE_IND
 * Report connection state change ind
******************************************************************************/
typedef struct CemmrConnStateChangeInd_Tag
{
    UINT8   connStatus;         //CcmCemmConnStatusEnum if connStatus change, others info is not accurate
    UINT8   rsvd0;
    UINT16  rsvd1;
}CemmrConnStateChangeInd;

/******************************************************************************
 * CemmrNwInfoInd
 * SIG_CEMMR_NW_INFO_IND
 * EMM information from NW
******************************************************************************/
typedef struct CemmTimeZoneAndTime_Tag
{
    UINT8   year;
    UINT8   month;
    UINT8   day;
    UINT8   hour;
    UINT8   minute;
    UINT8   second;
    UINT8   timeZone;
    UINT8   reserved0;
}CemmTimeZoneAndTime;

/*10.5.3.12 Daylight Saving Time*/
typedef enum CemmDaylightSavingTimeEnum_Tag
{
    DAYLIGHT_SAVING_TIME_NO_ADJ = 0,
    DAYLIGHT_SAVING_TIME_ONE_HOUR,
    DAYLIGHT_SAVING_TIME_TWO_HOUR,
    DAYLIGHT_SAVING_TIME_RESERVED
}CemmDaylightSavingTimeEnum;

#define CEMM_FULL_NW_NAME_LEN 32
#define CEMM_SHORT_NW_NAME_LEN 16
typedef struct CemmrNwInfoInd_Tag
{
    UINT8   fullNwNameLen;
    UINT8   shortNwNameLen;

    BOOL    localTZPresent;
    UINT8   localTimeZone;

    UINT8   fullNwName[CEMM_FULL_NW_NAME_LEN]; // CEMM need to decoded it to string type;
    UINT8   shortNwName[CEMM_SHORT_NW_NAME_LEN];

    BOOL    tzTimePresent;
    BOOL    daySaveTimePresent;
    UINT8   daySaveTime;    //CemmDaylightSavingTimeEnum
    UINT8   reserved0;

    CemmTimeZoneAndTime tzTime;
}CemmrNwInfoInd;

/******************************************************************************
 * CemmPlmnSetBandFreqCnf
 * SIG_CEMM_PLMN_SET_BAND_FREQ_CNF,
 * AT+ECBAND/AT+ECFREQ set the BAND/FREQ confirmation
******************************************************************************/
typedef struct CemmPlmnSetMccBandCnf_Tag
{
    UINT16   emmRc;      //CcmCemmRcCodeEnum
    UINT8 bandChanged;
    UINT8   reserved0;
}CemmPlmnSetMccBandCnf;

/******************************************************************************
 * CemmPlmnSetBandFreqCnf
 * SIG_CEMM_PLMN_SET_BAND_FREQ_CNF,
 * AT+ECBAND/AT+ECFREQ set the BAND/FREQ confirmation
******************************************************************************/
typedef struct CemmPlmnSetBandFreqCnf_Tag
{
    UINT8   emmRc;      //CcmCemmRcCodeEnum
    UINT8   setType;    //CemmSetBandFreqType
    BOOL    bBandOrNwChanged;
    UINT8   reserved0;
}CemmPlmnSetBandFreqCnf;

/******************************************************************************
 * CemmPlmnGetBandFreqCnf
 * SIG_CEMM_PLMN_GET_BAND_FREQ_CNF,
 * AT+ECBAND/AT+ECFREQ to get the BAND/FREQ confirmation
******************************************************************************/
typedef struct CemmCurBandSettingInfo_Tag
{
    UINT8   nwMode; // NwMode
    UINT8   bandNum;
	#if MCC_FEATURE_ENABLED
    UINT16  mcc[10];
	UINT8   mccNum;
	UINT8   mccBand[SUPPORT_MAX_BAND_NUM][SUPPORT_MAX_BAND_NUM];
	UINT8   mccBandNum[SUPPORT_MAX_BAND_NUM];
	#endif
    UINT8   orderedBand[SUPPORT_MAX_BAND_NUM];
}CemmCurBandSettingInfo; //20 bytes

typedef struct CemmBandCapaInfo_Tag
{
    UINT8   nwMode; // NwMode
    UINT8   bandNum;
    UINT16  reserved;
    UINT8   supportband[SUPPORT_MAX_BAND_NUM];
}CemmBandCapaInfo;  //20 bytes

typedef enum CemmFreqSettingTypeEnum_Tag
{
    NO_FREQ_SETTING = 0,
    PREFER_FREQ_SETTING,
    LOCK_FREQ_SETTING,
    PREFER_FREQ_AND_LOCK_FREQ_SETTING
}CemmFreqSettingTypeEnum;

typedef struct CemmFreqSettingInfo_Tag
{
    UINT8   freqType;   //CemmFreqSettingTypeEnum

    UINT8   cellPresent;// indicate whether phyCellId present, for cell lock case
    UINT16  phyCellId;  // phyCell ID, 0 - 503

    UINT8   arfcnNum;
    UINT8   reserved0;
    UINT16  reserved1;
    UINT32  lockedArfcn;
    UINT32  arfcnList[SUPPORT_MAX_FREQ_NUM];
}CemmFreqSettingInfo;  //40 bytes


typedef struct CemmPlmnGetBandFreqCnf_Tag
{
    UINT8   emmRc;              //CcmCemmRcCodeEnum
    UINT8   getBandFreqType;    //CemmGetBandInfoTypeEnum
    UINT16  reserved0;

    union {
        CemmCurBandSettingInfo  curBandInfo;
        CemmBandCapaInfo        bandCapaInfo;
        CemmFreqSettingInfo     freqInfo;
    } getBandFreqInfo;
}CemmPlmnGetBandFreqCnf;

typedef struct CemmPlmnGetMccBandCnf_Tag
{
    UINT8   emmRc;              //CcmCemmRcCodeEnum
    UINT16  reserved0;
    UINT16  mcc[10];
    union {
        CemmCurBandSettingInfo  curBandInfo;
    } getBandFreqInfo;
}CemmPlmnGetMccBandCnf;



/******************************************************************************
 * CemmPlmnOosPlmnSelectCnf
 * SIG_CEMM_OOS_PLMN_SELECT_CNF,
 * $QCPLMNSI confirm
******************************************************************************/
typedef struct CemmPlmnOosPlmnSelectCnf_Tag
{
    UINT8   rcCode; //CcmCemmRcCodeEnum, 0, just means oos PLMN select finished normally
    UINT8   reserved[3];
}CemmPlmnOosPlmnSelectCnf;

/******************************************************************************
 * CemmrPowerSaveCnf
 * SIG_CEMMR_POWER_SAVE_CNF,
 * Try to enter hibernate state
******************************************************************************/
typedef GosEmptySignal CemmrPowerSaveCnf;

/******************************************************************************
 * CemmrPowerRecoverCnf
 * SIG_CEMMR_POWER_RECOVER_CNF,
 * Wake up from hibernate state, pass some CEMM info to CCM
******************************************************************************/
typedef struct CemmrPowerRecoverCnf_Tag
{
    UINT8   regStatus;      // CemmRegStatusEnum
    UINT8   nwMode;         // NwMode
    UINT8   serviceType;    // UeService, EPS only
    UINT8   plmnSelectType;  // CemmPlmnSelectTypeEnum, auto plmn/maunal plmn setting, no matter the REG status

    UINT8   plmnSelectState;    //CemmPlmnSelectState
    BOOL    oosTimerPresent;
    UINT16  oosTimerS;          //OOS timer value in second

    UINT8   ueServiceStatus;    // CcmCemmUeSrvStatusEnum
    BOOL    cellInfoValid;      // whether tac/phyCellId/band info valid
    BOOL    plmnValid;          // whether the PLMN info valid
    UINT8   reserved1;

    UINT16  tac;
    UINT16  phyCellId;
    UINT32  cellId;

    UINT8   band;
    UINT8   addUpdateInfo;  //AdditionalUpdateResult
    UINT8   nwSupCiotOpt;   //CemmCiotOptTypeEnum
    UINT8   reserved2;

    CemmNwPsmInfo   nwPsmInfo;
    CemmEdrxInfo    edrxInfo;
    Plmn            plmn;
}CemmrPowerRecoverCnf;

/******************************************************************************
 * CemmCacSetParmCnf
 * SIG_CEMM_CAC_SET_PARM_CNF,
 * confirm from CEMM to CAC for "SIG_CEMM_CAC_SET_PARM_REQ"
******************************************************************************/
typedef struct CemmCacSetParmCnf_Tag
{
    UINT8   emmRc;      //CcmCemmRcCodeEnum
    UINT8   parmType;   //CemmParmType
    UINT16  reserved0;
}CemmCacSetParmCnf;


/******************************************************************************
 * CemmCacGetParmCnf
 * SIG_CEMM_CAC_GET_PARM_CNF,
 * confirm from CEMM to CAC for "SIG_CEMM_CAC_GET_PARM_REQ"
******************************************************************************/
/*
 * PSM PARM
*/
typedef struct CemmGetRequestPsmParmInfo_Tag
{
    UINT8 psmReqMode;       //CemmPsmReqModeEnum

    UINT8 reqBitmap;        /*bit 0 - T3412, bit 1 -  T3324*/

    UINT8 reqPeriodicTau;   /*T3412*/
    UINT8 reqActiveTime;    /*T3324*/
}CemmGetRequestPsmParmInfo;

/*
 * EDRX PARM
*/
typedef struct CemmGetEdrxParmInfo_Tag
{
    UINT8   edrxReqMode;    //CemmEdrxReqModeEnum
    BOOL    reqEdrxPresent;
    UINT8   reqEdrxValue;
    UINT8   reqPtwValue;

    BOOL    nwEdrxPresent;
    UINT8   nwEdrxValue;
    UINT8   nwPtw;

    UINT8   reserved0;
}CemmGetEdrxParmInfo;

/*
 * CIOT OPT CFG PARM
*/
typedef struct CemmGetCiotOptCfgParmInfo_Tag
{
    UINT8   ueSuptOptType;//UE supported CIOT OPT type, CemmCiotOptTypeEnum: 1 & 3
    UINT8   uePreferOpt;  // CemmCiotOptTypeEnum: 0, 1, 2
    UINT16  reserved;
}CemmGetCiotOptCfgParmInfo;

typedef struct CemmGetCipcaParmInfo_Tag
{
    BOOL    attachWithoutPdn;  //EPS Attach with/without PDN connection
    UINT8   reserved0;
    UINT16  reserved;
}CemmGetCipcaParmInfo;

typedef struct CemmGetPlmnSelectStateParmInfo_Tag
{
    UINT8   plmnSelectState;    //CemmPlmnSelectState
    BOOL    oosTimerPresent;
    UINT16  oosTimerS;          //remain OOS timer in seconds
}CemmGetPlmnSelectStateParmInfo;


typedef struct CemmCacGetParmCnf_Tag
{
    UINT8   emmRc;      //CcmCemmRcCodeEnum
    UINT8   parmType;   //CemmParmType
    UINT8   bodyLen;
    UINT8   reserved0;

    /*
     * PSM: CemmGetRequestPsmParmInfo
     * EDRX: CemmGetEdrxParmInfo
     * CIOT OPT CFG: CemmGetCiotOptCfgParmInfo
    */
    UINT8   body[];
}CemmCacGetParmCnf;


/******************************************************************************
 * SIG_CEMM_CCM_SET_PARM_CNF
 *  confirm from CEMM to CAC for "SIG_CEMM_CAC_SET_PARM_REQ"
******************************************************************************/
typedef struct CemmCcmSetParmCnf_Tag
{
    UINT8   emmRc;       //CcmCemmRcCodeEnum
    UINT8   ccmParmType; //CcmParmType
    UINT16  reserved0;
}CemmCcmSetParmCnf;


/******************************************************************************
 * CemmCcmGetParmCnf
 * SIG_CEMM_CCM_GET_PARM_CNF,
 * confirm from CEMM to CCM for "SIG_CEMM_CCM_GET_PARM_REQ"
******************************************************************************/
typedef struct CcmGetEmmCapaParm_Tag
{
    BOOL    supportSms;
    UINT8   plmnSearchPowerLevel;
    BOOL    enableEpco;                 //whether enable EPCO
    BOOL    tauForSms;
    UINT8   dnsIpv4AddrReadCfg;
    UINT8   dnsIpv6AddrReadCfg;
    UINT16  rsvd;
    UINT32  t3324MaxValue;
    BOOL    overrideLrplmnsi;
	UINT8   bEnableHPPlmnSearch;
}CcmGetEmmCapaParm;


typedef struct CcmGetPlmnRegTypeParm_Tag
{
    UINT8   plmnSelectType; // CemmPlmnSelectTypeEnum
    UINT8   reserved0;
    UINT16  reserved1;

    Plmn    manualPlmn; //if "CEMM_MANUAL_PLMN_REG"/"CEMM_MANUAL_THEN_AUTO_PLMN_REG"
}CcmGetPlmnRegTypeParm;

typedef struct CcmGetPsTestParm_Tag
{
    BOOL    psTestEnable;
    UINT8   reserved0;
    UINT16  reserved1;
}CcmGetPsTestParm;

typedef struct CcmGetPsSleepCfgParm_Tag
{
    UINT16  minT3324;
    UINT16  minEdrxPeriod;
    UINT32  minT3412;
}CcmGetPsSleepCfgParm;

typedef struct CemmCcmGetParmCnf_Tag
{
    UINT8   emmRc;       //CcmCemmRcCodeEnum
    UINT8   ccmParmType; //CcmParmType
    UINT8   bodyLen;
    UINT8   reserved0;

    /*
     * CCM_EMM_CAPA_PRAM: CcmGetEmmCapaParm
     * CCM_PLMN_REG_TYPE_PRAM: CcmGetPlmnRegTypeParm
     * CCM_PS_TEST_PRAM: CcmGetPsTestParm
    */
    UINT8   body[];
}CemmCcmGetParmCnf;

typedef struct CemmCcmGetEmmStatusCnf_Tag
{
	CmiDevNasEmmSubState    eMEmmsubstate;
}CemmCcmGetEmmStatusCnf;

typedef GosEmptySignal CemmCcmSetLapicnf;

typedef struct CemmCcmGetLapicnf_Tag
{
	CmiDevGetLapiCnf    lapiInfo;
}CemmCcmGetLapicnf;

typedef GosEmptySignal CemmCcmSetRoamingDataCnf;


typedef struct CemmCcmGetRoamingDataCnf_Tag
{
	CmiDevGetRoamingDataCnf    RoamDataInfo;
}CemmCcmGetRoamingDataCnf;


/******************************************************************************
 ******************************************************************************
 * CESM -> CCM PS
 ******************************************************************************
******************************************************************************/
#define CCM_SIG_H_CCM_PS_SIG_LOC

/******************************************************************************
 * MACRO
******************************************************************************/

/******************************************************************************
 * ENUM
******************************************************************************/
typedef enum CcmCesmRcCodeEnum_Tag
{
    CCM_CESM_SUCC   = 0,
    CCM_CESM_NO_VALID_INFO,
    CCM_CESM_FAILURE,

    CCM_CESM_RC_MAX = 0xFF
}CcmCesmRcCodeEnum;

/******************************************************************************
 * STRUCTS
******************************************************************************/
typedef struct CcmCesmActDefEpsBearerCtxIndTag
{
    UINT8           cid;
    BOOL            esmCausePresent;
    UINT16          esmCause; //EsmCause
    //UINT8           reserved;
}CcmCesmActDefEpsBearerCtxInd;

typedef struct CcmCesmSetEpsBearerCtxCnfTag
{
    UINT8               rc;//CcmCesmRcCodeEnum
    UINT8               cid;
    UINT16              reserved;
}CcmCesmSetEpsBearerCtxCnf;


/*
 * SIG_CCM_CESM_GET_EPS_BEARER_CTX_CNF
 *  return all EPS bearer context, 276 bytes
*/
typedef struct CcmCesmGetEpsBearerCtxCnf_Tag
{
    /*
     * 4 bytes
    */
    UINT32      esmRc : 8;      //CcmCesmRcCodeEnum
    UINT32      cid : 8;        /* context Id, same as ebi for MT PDN, allocate from 1 for MO PDN, 0 is reserved */
    UINT32      pcid : 8;       /* primary CID, used to decide whether this bearer is a default/dedicated bearer, if default bearer set to 0*/
    UINT32      epsId : 4;      /* EpsBearerId, eps bearer ID, if not actived, set to 0*/
    UINT32      pdnType : 4;    /* PdnType, IP type */


    /*
     * 4 bytes
    */
    UINT32      cmiBrState : 4; /* CmiPsBearerState */
    UINT32      bReqAll : 1;    /* whether request all bearer info*/
    UINT32      bContinue : 1;  /* whether another eps bearer context followed, in case of request for all bearers context */
    UINT32      reqTypePresent : 1; /* whether config by CGDCONT */
    UINT32      NSLPIPresent : 1;   /* whether config by CGDCONT */

    UINT32      ipv4AlloTypePresent : 1;
    UINT32      ipv4MtuDisTypePresent : 1;
    UINT32      nonIpMtuDisTypePresent : 1;
    UINT32      pcscfDisTypePresent : 1;    /* not support, now set to FALSE */
    UINT32      imCnSigFlagPresent : 1;     /* not support, now set to FALSE */
    UINT32      epsQosPresent : 1;
    UINT32      ipv4MtuPresent : 1;
    UINT32      nonIpMtuPresent : 1;

    UINT32      apnAmbrPresent:  1;
    UINT32      reqType : 3;        /* CmiPsBearerReqType, 3 bit, valid when "reqTypePresent" is set to TRUE */
    UINT32      imCnSigFlag : 1;    /* CmiPsImCnSigFlag, 1 bit, not support */
    UINT32      NSLPI : 1;          /* CmiPsNSLPICfg, NAS signalling priority, 1 bit, valid when "NSLPIPresent" set to TRUE */
    UINT32      pcscfDisType : 2;   /* CmiPsPcscfDiscoveryType, 2 bits, not support */

    UINT32      ipv4AlloType : 1;   /* CmiPsIpv4AllocType, 1 bit, valid when "ipv4AlloTypePresent" set to TRUE */
    UINT32      ipv4MtuDisByNas : 1;    /* IPv4 MTU size discovery through NAS signalling, valid when "ipv4MtuDisTypePresent" set to TRUE */
    UINT32      dnsNum : 3;
	UINT32      reserved1 :3;
    
    UINT32      reqTftNum : 5;      /*how many TFT request by AT+CGTFT */
    UINT32      reqCmiId: 16;           /* which PS CMI REQ, EPS bearer info */
    UINT32      nonIpMtuDisByNas : 1;   /* Non-IP MTU size discovery through NAS signalling, valid when "nonIpMtuDisTypePresent" set to TRUE*/
    UINT32      reserved3 :10;

    UINT16      ipv4MtuSize;
    UINT16      nonIpMtuSize;
	UINT16      splmnRateCtrl;     /*Serving PLMN rate control 2 octets*/
    UINT16      reserved4;


    CmiIpAddr           gwipv4Addr;   //20 bytes
    CmiIpAddr           ipv4Addr;   //20 bytes
    CmiIpAddr           ipv6Addr;   //20 bytes
    CmiIpAddr           dnsAddr[PDN_MAX_NW_ADDR_NUM];   //20*4 = 80 bytes

    AccessPointName     apn;    /* 104 bytes encoded APN */
    APNRateControl      apnRateCtrl;    //4 bytes
    AdditionalAPNRateControl    addApnRateCtrl; //4 bytes

    EpsQualityOfService epsQos;    /* NW assigned EPS QOS, valid when "epsQosPresent" is set to TRUE, 20 bytes */

    APNAMaxBitRate      apnAmbr;  /* NW assigned ,for Dyn  QOS query*/

    ULPcoPAPAuth        papAuth;  /*pap auth,set by AT+CGAUTH*/

    EpsQualityOfService *pReqEpsQos;    /* UE request EPS QOS parameter, set by AT+CGEQOS, dynamic memory, if no, return NULL */

    /*
     * bearer PacketFilter info, if bearer assigned/activated TFT, using dynamic memory
    */
    PacketFilterList    *pTftHdr;

    /*
     * set by CGTFT, and need to modification/activate, using dynamic memory
     *  and the number is set by "reqTftNum", just if "reqTftNum" = 2, this memory size is: 2*sizeof(CmiPsTftFilter)
    */
    CmiPsTftFilter      *pReqTftList;
}CcmCesmGetEpsBearerCtxCnf; //276 bytes


typedef struct CcmCesmGetDefinedEpsBearerCtxCnfTag
{
    CmiPsDefinedBearerCtx          bearerCtxInfo;
}
CcmCesmGetDefinedEpsBearerCtxCnf;

typedef struct CcmCesmDelDefinedEpsBearerCtxCnfTag
{
    UINT8               rc;//CcmCesmRcCodeEnum
    UINT8               cid;
    UINT16              reserved;
}
CcmCesmDelDefinedEpsBearerCtxCnf;

/*
 * CESM -> CCM PS
 * SIG_CCM_CESM_GET_ALL_BEARERS_BASIC_INFO_CNF
*/
typedef struct CcmCesmGetAllBearersBasicInfoCnf_Tag
{
    UINT8   reqCmdId;   /* which AT CMD (request) need UE all bearers info*/
    UINT8   validNum;
    UINT16  reserved0;
    CmiPsBearerCidBasicInfo bearerBasicInfoList[CMI_PS_CID_NUM];
}CcmCesmGetAllBearersBasicInfoCnf;

#if 0
typedef struct CcmCesmReadBearerCtxDynParamCnfTag
{
    CmiPsBearerCtxDynParam        bearerCtxDynParam;
}
CcmCesmReadBearerCtxDynParamCnf;

typedef struct CcmCesmGetDefinedCidIpAddrParamCnfTag
{
    CmiPsDefinedBearerAddr        definedBearerAddr;
}
CcmCesmGetDefinedCidIpAddrParamCnf;
#endif

typedef struct CcmCesmActEpsBearerCtxCnfTag
{
    UINT8               cid;
    BOOL                esmCausePresent;
    UINT16              esmCause; //EsmCause #50/#51#52 --TBD
}
CcmCesmActEpsBearerCtxCnf;

typedef struct CcmCesmActEpsBearerCtxRejTag
{
    UINT8               cid;
    UINT16              esmCause; //EsmCause
    UINT8               reserved;
}
CcmCesmActEpsBearerCtxRej;

typedef struct CcmCesmDeactEpsBearerCtxCnfTag
{
    UINT8               cid;
    UINT16              esmCause; //EsmCause
    UINT8               reserved;
}
CcmCesmDeactEpsBearerCtxCnf;

typedef struct CcmCesmDeactEpsBearerCtxRejTag
{
    UINT8               cid;
    UINT16              esmCause; //EsmCause
    UINT8               reserved;
}
CcmCesmDeactEpsBearerCtxRej;

typedef struct CcmCesmDeactEpsBearerCtxIndTag
{
    UINT8               cid;
    UINT16              esmCause; //EsmCause
    UINT8               reserved;
}
CcmCesmDeactEpsBearerCtxInd;


typedef struct CcmCesmActDeDEpsBearerCtxIndTag
{
    UINT8           pCid;
    UINT8           cid;
    BOOL            esmCausePresent;
    UINT16          esmCause; //EsmCause
    UINT8           reserved1;
    UINT16          reserved2;
}CcmCesmActDedEpsBearerCtxInd;

typedef struct CcmCesmSetDedEpsBearerCtxCnfTag
{
    UINT8               rc;//CcmCesmRcCodeEnum
    UINT8               cid;
    UINT16               reserved;
}
CcmCesmSetDedEpsBearerCtxCnf;

typedef struct CcmCesmDelDedEpsBearerCtxCnfTag
{
    UINT8               rc;//CcmCesmRcCodeEnum
    UINT8               cid;
    UINT16              reserved;
}
CcmCesmDelDedEpsBearerCtxCnf;


typedef struct CcmCesmGetDedEpsBearerCtxCnfTag
{
    UINT8               cid;
    UINT8               pCid;
    UINT8               imCnFlag;
    UINT8               reserved;
}
CcmCesmGetDedEpsBearerCtxCnf;

#if 0
typedef struct CcmCesmGetAPNrateCtrlCnfTag
{
    UINT8               cid;
    UINT8               AER;
    UINT8               UplinkTimeUnit;
    UINT8               reserved;
    UINT32              MaximumUplinkRate;
}
CcmCesmGetAPNrateCtrlCnf;
#endif

typedef struct CcmCesmModifyEpsBearerCtxCnfTag
{
    UINT8               cid;
    UINT16              esmCause; //EsmCause
    UINT8               reason;
}
CcmCesmModifyEpsBearerCtxCnf;


typedef struct CcmCesmModifyEpsBearerCtxIndTag
{
    UINT8               cid;
    UINT8               reason;
    UINT16              reserved2;
}
CcmCesmModifyEpsBearerCtxInd;


typedef struct CcmCesmSetDefineTFTParamCnfTag
{
    UINT8               cid;
    UINT8               rc; //CcmCesmRcCodeEnum
    UINT16              reserved;
}CcmCesmSetDefineTFTParamCnf;

typedef struct CcmCesmDelTFTParamCnfTag
{
    UINT8               cid;
    UINT8               rc; //CcmCesmRcCodeEnum
    UINT16              reserved;
}CcmCesmDelTFTParamCnf;

#if 0
typedef struct TftPacketTag
{
    CmiPsTftFilter          TftFilter[CMI_PS_MAX_TFT_FILTERS];
    UINT8                   numFilters;
    UINT8                   reserved;
    UINT16                  reserved2;
}TftPacket;

typedef struct CcmCesmGetDefineTFTParamCnfTag
{
    TftPacket               tftPacket;
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmGetDefineTFTParamCnf;
#endif

typedef struct CcmCesmSetDefineEpsQosCnfTag
{
    UINT8               cid;
    UINT8               rc; //CcmCesmRcCodeEnum
    UINT16              reserved;
}CcmCesmSetDefineEpsQosCnf;

typedef struct CcmCesmGetDefineEpsQosCnfTag
{
    CmiPsEpsQosParams       qosParam[CMI_PS_MAX_BEARER_NUM];
    UINT8                   numOfQos;
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT16                  reserved;
}CcmCesmGetDefineEpsQosCnf;

typedef struct CcmCesmDelEpsQosCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmDelEpsQosCnf;

/*
typedef struct CcmCesmSendDataVerCPCnfTag
{
    UINT8         rc; //CcmCesmRcCodeEnum
}CcmCesmSendDataVerCPCnf;
*/

typedef struct CcmCesmAttBearCtxPresetCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmAttBearCtxPresetCnf;

typedef struct CcmCesmGetAttBearCtxCnfTag
{
    AttachedBearCtxParam    attBearCtxParam;
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmGetAttBearCtxCnf;

typedef struct CcmCesmSetMtCpDataReportCfgCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmSetMtCpDataReportCfgCnf;

typedef struct CcmCesmGetMtCpDataReportCfgCnfTag
{
    UINT8                   reporting;
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT16                  reserved2;
}CcmCesmGetMtCpDataReportCfgCnf;

typedef struct CcmCesmMtCpDataIndTag
{
    UINT8         cid;
    UINT16        length; //CcmCesmRcCodeEnum
    UINT8*        pData;
}CcmCesmMtCpDataInd;

typedef struct CcmCesmEsmRejectCauseIndTag
{
    UINT16              esmCause; //EsmCause
    UINT16               reserved;
}CcmCesmEsmRejectCauseInd;

typedef struct CcmCesmSetDefineAuthCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmSetDefineAuthCnf;

typedef struct CcmCesmSetQcApnClassCnfTag
{
	UINT8 					rc; //CcmCesmRcCodeEnum
	UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmSetQcApnClassCnf;

typedef struct CcmCesmSetThrottParamReqTag
{
    UINT16  	maxPdnConnPerBlock;
	UINT16 		maxPdnConnTimer;
	UINT16 		pdnReqWaitTimer;
	UINT16      reserved1;
}CcmCesmSetThrottParamReq;


/******************************************************************************
 ******************************************************************************
 * OTHER -> CCM
 ******************************************************************************
******************************************************************************/
#define CCM_SIG_H_CCM_OTHER_SIG_LOC

/******************************************************************************
 * MACRO
******************************************************************************/

/*
 * SIG_CAC_SIGNAL_QUALITY_IND
*/
typedef struct CacSignalQualityInd_Tag
{
    /* TS 36.133-v14.5.0, Table 9.1.4-1
     * -17 rsrp < -156 dBm
     * -16 -156 dBm <= rsrp < -155 dBm
     *  ...
     * -3 -143 dBm <= rsrp < -142 dBm
     * -2 -142 dBm <= rsrp < -141 dBm
     * -1 -141 dBm <= rsrp < -140 dBm
     * 0 rsrp < -140 dBm
     * 1 -140 dBm <= rsrp < -139 dBm
     * 2 -139 dBm <= rsrp < -138 dBm
     *  ...
     * 95 -46 dBm <= rsrp < -45 dBm
     * 96 -45 dBm <= rsrp < -44 dBm
     * 97 -44 dBm <= rsrp
    */
    BOOL    rsrpPresent; //FALSE: RSRP not known or not detectable
    INT8    rsrp;        /*-17 ~ 97*/

    /* TS 36.133-v14.5.0, Table 9.1.7-1/Table 9.1.24-1
     * -30 rsrq < -34 dB
     * -29 -34 dB <= rsrq < -33.5 dB
     *   ...
     * -2 -20.5 dB <= rsrq < -20 dB
     * -1 -20 dB <= rsrq < -19.5 dB
     * 0 rsrq < -19.5 dB
     * 1 -19.5 dB <= rsrq < -19 dB
     * 2 -19 dB <= rsrq < -18.5 dB
     *   ...
     * 32 -4 dB <= rsrq < -3.5 dB
     * 33 -3.5 dB <= rsrq < -3 dB
     * 34 -3 dB <= rsrq
     * 35 -3 dB <= rsrq < -2.5 dB
     * 36 -2.5 dB <= rsrq < -2
     *   ...
     * 45 2 dB <= rsrq < 2.5 dB
     * 46 2.5 dB <= rsrq
    */
    BOOL    rsrqPresent; //FALSE: RSRQ not known or not detectable
    INT8    rsrq; /*-30 ~ 46*/

    // DL block error, real block error * 10000, so 21, just means 0.0021 = 0.21%
    UINT16  dlBer;

    // 0-CE Level 0; 1-CE Level 1; 2-CE Level 2
    UINT8   ceLevel;

    //SNR Signal-to-Noise Ratio
    // value in dB, value range: -30 ~ 30
    INT8    snr;
}CacSignalQualityInd;


/*
 * SIG_CEDR_PS_DATA_PLANE_TRANS_CNF
 */
typedef struct CedrPsDataPlaneTransCnf_Tag
{
    BOOL    bSucc;
    UINT8   reserved0;
    UINT16  reserved1;
}CedrPsDataPlaneTransCnf;


/*
 * SIG_CCM_DL_NON_IP_DATA_IND
 *  Just pass the DL non-ip data to CAC/AT
*/
typedef struct CcmDlNonIpDataInd_Tag
{
    UINT8   cid;
    UINT16  length;
    UINT8   *pData;    // using dynamic memory
}CcmDlNonIpDataInd;

/* 
 * SIG_CCM_CEDR_PKT_STATS_CNF
 */
typedef struct CcmCedrPktStatsCnf_Tag
{
   UINT8  cid;
   BearerPktStats pktStatsPerBearer;
}CcmCedrPktStatsCnf;

/******************************************************************************
 * CERRC->CCM DEV lpp
******************************************************************************/
/*
 * SIG_CCM_ERRC_LOC_MEAS_CNF
 *  Just pass loc meaurement result to LPP submodule
*/
typedef struct CcmErrcLocMeasCnf_Tag
{
    UINT8                           otdoaMeasResult;    //CmiOtdoaMeasResult
    BOOL                            otdoaMeasuredInfoPresent;
    BOOL                            ecidMeasuredInfoPresent;
    UINT8                           reserved1;
    CmiEcidMeasResult               ecidMeasResult;
    CmiOtdoaMeasuredInfoNB          otdoaMeasuredInfo;
    CmiEcidMeasuredInfo             ecidMeasuredInfo;
}CcmErrcLocMeasCnf;

/*
 * SIG_CCM_ERRC_LOC_MEAS_IND
 *  errc report the loc measurement in cell change triggered meas case
*/
typedef struct CcmErrcLocMeasInd_Tag
{
    CmiEcidMeasResult               ecidMeasResult;
    CmiEcidMeasuredInfo             ecidMeasuredInfo;
}CcmErrcLocMeasInd;

/*
 * SIG_CCM_ERRC_EARLY_LOC_MEAS_CNF
 *  errc confirm the early loc measurement
*/
typedef struct CcmErrcEarlyLocMeasCnf_Tag
{
    UINT8                           otdoaMeasResult;    //CmiOtdoaMeasResult
    BOOL                            otdoaMeasuredInfoPresent;
    BOOL                            ecidMeasuredInfoPresent;
    UINT8                           reserved1;
    CmiEcidMeasResult               ecidMeasResult;
    CmiOtdoaMeasuredInfoNB          otdoaMeasuredInfo;
    CmiEcidMeasuredInfo             ecidMeasuredInfo;
}CcmErrcEarlyLocMeasCnf;

/*
 * SIG_CCM_ERRC_STOP_LOC_MEAS_CNF
 *  errc confirm stop loc measurement
*/
typedef struct CcmErrcStopLocMeasCnf_Tag
{
    UINT8                           otdoaMeasResult;    //CmiOtdoaMeasResult
    BOOL                            otdoaMeasuredInfoPresent;
    BOOL                            ecidMeasuredInfoPresent;
    UINT8                           reserved1;
    CmiEcidMeasResult               ecidMeasResult;
    CmiOtdoaMeasuredInfoNB          otdoaMeasuredInfo;
    CmiEcidMeasuredInfo             ecidMeasuredInfo;
}CcmErrcStopLocMeasCnf;


/******************************************************************************
 * CESS->CCM DEV lpp
******************************************************************************/
typedef enum CcmCessRcCodeEnum_Tag
{
    CCM_CESS_FAILURE = 0,
    CCM_CESS_SUCC = 1
}CcmCessRcCodeEnum;

/*
 * SIG_CCM_CESS_LPP_UNIT_DATA_CNF
 *  Just pass uplink LPP data transfer result to LPP submodule
*/
typedef struct CcmCessLppUnitDataCnf_Tag
{
    UINT8        result;    //CcmCessRcCodeEnum
    UINT8        reserved0;
    UINT16       reserved1;
}CcmCessLppUnitDataCnf;

/*
 * SIG_CCM_CESS_LPP_UNIT_DATA_IND
 *  Pass downlink LPP data to LPP submodule
*/
typedef struct CcmCessLppUnitDataInd_Tag
{
    UINT16       length;
    BOOL         nasRoutingIdPresent;
    UINT8        reserved;
    UINT32       nasRoutingId;  /*IE type octet string(size(4))*/
    UINT8        *pdata;    // using dynamic memory
}CcmCessLppUnitDataInd;

/*
 * SIG_CCM_CESS_RESET_POSITION_INFO_IND
 *  Pass 'reset ue positioning stored information' to LPP
*/
typedef struct CcmCessResetPositionInfoInd_Tag
{
    UePositioningTechnology     resetPositionInfo;
}CcmCessResetPositionInfoInd;

/*
 * SIG_CCM_CESS_LCS_UNIT_DATA_CNF
 *  Just pass uplink LCS data transfer result to LPP submodule
*/
typedef struct CcmCessLcsUnitDataCnf_Tag
{
    UINT8        result;    //CcmCessRcCodeEnum
    UINT8        reserved0;
    UINT16       reserved1;
}CcmCessLcsUnitDataCnf;

/*
 * SIG_CCM_CESS_LCS_UNIT_DATA_IND
 *  Pass downlink LCS data to CCM
*/
typedef struct CcmCessLcsUnitDataInd_Tag
{
    UINT8   lcsMessage; //LcsMessage
    UINT16  bodyLen;
    UINT8   handleId;

    /*
     * molr result - MolrResult
     * lcs location notification - LcsLocNotifyInfo
    */
    UINT8   body[];
}CcmCessLcsUnitDataInd;

/******************************************************************************
 * CESS->CCM DEV
******************************************************************************/

/******************************************************************************
 * CcmCessGetCmtlraCnf
 * SIG_CCM_CESS_GET_CMTLRA_CNF
******************************************************************************/
typedef struct CcmCessGetCmtlraCnf_Tag
{
    UINT8   allowance; //CmiDevLocationDisclosureAllowance
    UINT8   handleId;
    UINT16  reserved;
}CcmCessGetCmtlraCnf;


/******************************************************************************
 * SIG_CERRC_CCM_SET_PARAM_CNF
 * set parameters should be all succ, by now all setting parameters could be checked in CCM layer
******************************************************************************/
typedef struct CerrcCcmSetParamCnfTag
{
    UINT8   setParamType;   /* CerrcCcmParamType */
    BOOL    result;         /* set para result */
    UINT16  reserved;
}CerrcCcmSetParamCnf;

/******************************************************************************
 * SIG_CERRC_CCM_GET_PARAM_CNF
 * Get ERRC configed parameters/capability
******************************************************************************/

#define UE_POWER_CLASS_3_BIT_OFFSET                  (1 << 0)
#define UE_POWER_CLASS_5_BIT_OFFSET                  (1 << 1)
#define UE_POWER_CLASS_6_BIT_OFFSET                  (1 << 2)

/*
 * getParamType = CERRC_CCM_PARAM_EXTENDED_CONFIG
*/
typedef struct CerrcCcmExtCfgParam_Tag
{
    UINT8   relVersion;     /*release version, 13 - 14*/
    BOOL    supportUpRai;   /*indicate capability: rai-Support-r14*/
    BOOL    supportMultiCarrier; /*indicate capability: multiCarrier_r13*/
    BOOL    supportMultiTone; /*indicate capability: multiTone_r13*/

    UINT8   ueCfgDataInactTimerS; /*DataInactivityTimer-r14, UE local configed value, not the NW assigned value */
    UINT8   ueCfgRelaxMonitorDeltaP; /*range [0..15], value in dB, UE local configed value, not the NW assigned value */
    BOOL    enableCellResel;
    BOOL    enableConnReEst;

    UINT8   nbCategory;     /* Configure the NB-IoT category. Only support 1 and 2 now */
    BOOL    disableNCellMeas;   /* Configure disable Ncell Meas */
    BOOL    supportTwoHarq;
	UINT16  ueCfgCellSearchTimer; //cellSearchGuardTimer
	BOOL    dataInactMon_r14;

	BOOL    interferenceRandomisation_r14;

	BOOL    supportMultiCarrierNPRACH;
	BOOL    supportMultiCarrierPaging;

	BOOL    cpReestablishment;
    UINT8   rsvd;
}CerrcCcmExtCfgParam;   //12 bytes

/*
 * getParamType = CERRC_CCM_PARAM_POWER_CLASS
*/
typedef struct CerrcCcmPowerClassCfg_Tag
{
    //AT+POWERCLASS ?
    //return the band & power class of current customer configured power class
    UINT8   numOfBand;
    UINT8   rsvd1;
    UINT16  rsvd2;

    UINT8   band[RRC_PHY_SUPPORT_BAND_NUM];
    UINT8   powerClass[RRC_PHY_SUPPORT_BAND_NUM];   //powerClassBitmap or real power class?
}CerrcCcmPowerClassCfg; //68 bytes

/*
 * getParamType = CERRC_CCM_PARAM_POWER_CLASS_CAPABILITY
*/
typedef struct CerrcCcmPowerClassCapa_Tag
{
    //AT+POWERCLASS = ?
    //return the band & max power class support by RF
    UINT8   numOfRfBand;
    UINT8   rsvd1;
    UINT16  rsvd2;

    UINT8   rfBand[RRC_PHY_SUPPORT_BAND_NUM];
    UINT8   rfPowerClass[RRC_PHY_SUPPORT_BAND_NUM]; //the bitmap of all supported power class
}CerrcCcmPowerClassCapa; //68 bytes

/*
 * getParamType = CERRC_CCM_PARAM_REL_FEATURE
*/
typedef CmiDevGetNBRelFeatureCnf    CerrcCcmNbRelFeatureParam;

/*
 * Signal: SIG_CERRC_CCM_GET_PARAM_CNF
*/
typedef struct CerrcCcmGetParamCnf_Tag
{
    UINT8   getParamType;   /* CerrcCcmParamType */
    BOOL    bSucc;          //now always succ
    UINT16  rsvd;

    union {
        CerrcCcmExtCfgParam     extCfgParam;
        CerrcCcmPowerClassCfg   powerClassCfg;
        CerrcCcmPowerClassCapa  powerClassCapa;
        CerrcCcmNbRelFeatureParam   nbRelFeature;
    } param;
}CerrcCcmGetParamCnf;


/******************************************************************************
 * SIG_CERRC_CCM_LOCAL_TIME_INFO_IND
 * Get UTC time in SIB16
******************************************************************************/
typedef struct ReferenceTimeTag
{
    UINT32  /* 0 to 72999 */               refDays;
    UINT32  /* 0 to 86399 */               refSeconds;
    UINT16  /* 0 to 999 */                 refMilliSeconds;
    UINT16  /* 0 to 3999 */                refQuarterMicroSeconds;
}ReferenceTime;

typedef struct TimeReferenceInfo_Tag
{
    /*If bLocalClock is FALSE, the origin of the time field is 00:00:00 on Gregorian calendar date 6 January, 1980 (start of GPS time).
      If bLocalClock is TRUE, the interpretation of the origin of the time is unspecified and left up to upper layers.*/
    BOOL                                   bLocalClock;
    ReferenceTime                          time;

    /*This field indicates the number of LSBs which may be inaccurate in the refQuarterMicroSeconds field.
      If uncertainty is absent, the uncertainty of refQuarterMicroSeconds is not specified.*/
    BOOL                                   uncertaintyPresent;
    UINT8  /* 0 to 12 */                   uncertainty;

    /*This field indicates the reference SFN for time reference information.
      The time field indicates the time at the ending boundary of the SFN indicated by referenceSFN.
      The UE considers the frame indicated by the referenceSFN nearest to the frame where the field is received.*/
    BOOL                                   referenceSfnPresent;
    UINT16  /* 0 to 1023 */                referenceSfn;

    /*Assuming that NAS might need to be informed abort current SFN, TBD*/
    UINT16  /* 0 to 1023 */                currentSfn;
}TimeReferenceInfo;

typedef struct CacLocalTimeInfoInd_Tag
{
    /*The field counts the number of UTC seconds in 10ms units since 00:00:00 on Gregorian calendar date 1 January, 1900
      (midnight between Sunday, December 31, 1899 and Monday, January 1, 1900).
      NOTE:
      The UE may use this field together with the leapSeconds field to obtain GPS time as follows:
      GPS Time (in seconds) = timeInfoUTC (in seconds) - 2,524,953,600 (seconds) + leapSeconds,
      where 2,524,953,600 is the number of seconds between 00:00:00 on Gregorian calendar date 1 January, 1900
      and 00:00:00 on Gregorian calendar date 6 January, 1980 (start of GPS time).*/
    UINT8  /*0 to 549755813887*/           timeInfoUTC [5];

    /*It indicates if and how daylight saving time (DST) is applied to obtain the local time.
     The semantics is the same as the semantics of the Daylight Saving Time IE in TS 24.301 and TS 24.008.
     The second right bit (0x02) of the bit string contains the b2 of octet 3, i.e. the value part of the Daylight Saving Time IE,
     and the last/rightmost bit (0x01) of the bit string contains b1 of octet 3.*/
    BOOL                                   dayLightSavingTimePresent;
    UINT8  /* 0 to 3 */                    dayLightSavingTime;

    /*Number of leap seconds offset between GPS Time and UTC.
      UTC and GPS time are related i.e. GPS time -leapSeconds = UTC time.*/
    BOOL                                   leapSecondsPresent;
    INT16  /* -127 to 128 */               leapSeconds;

    /*Offset between UTC and local time in units of 15 minutes. Actual value = field value * 15 minutes.
      Local time of the day is calculated as UTC time + localTimeOffset.*/
    BOOL                                   localTimeOffsetPresent;
    INT8  /* -63 to 64 */                  localTimeOffset;

    /*Only apply for R15 and later*/
    BOOL                                   timeReferenceInfoPresent;
    TimeReferenceInfo                      timeReferenceInfo;
}CacLocalTimeInfoInd;


/******************************************************************************
 ******************************************************************************
  CCM DEV Engineering Mode
 ******************************************************************************
******************************************************************************/

/*
 * SIG_CCM_GET_ERRC_PHY_STATUS_CNF
*/
typedef struct CcmGetErrcPhyStatusCnf_Tag
{
    CmiDevPhyStatusInfo     phyStatus;
    CmiDevRrcStatusInfo     rrcStatus;
}CcmGetErrcPhyStatusCnf;

/*
 * SIG_CCM_GET_L2_STATUS_CNF
*/
typedef struct CcmGetL2StatusCnf_Tag
{
    CmiDevL2StatusInfo      l2Status;   //4 bytes
}CcmGetL2StatusCnf;

/*
 * SIG_CCM_GET_NAS_STATUS_CNF
*/
typedef struct CcmGetNasStatusCnf_Tag
{
    CmiDevNasStatusInfo     nasStatus;  //100 bytes
}CcmGetNasStatusCnf;

/******************************************************************************
 * UE period statistic info report, Engineering Mode
******************************************************************************/
typedef enum CcmStatisReqType_Enum
{
    CCM_DEV_START_STATIS,   //each layer start statistic count
    CCM_DEV_GET_STATIS,     //get each layer statis info
    CCM_DEV_STOP_STATIS
}CcmStatisReqType;

/*
 * SIG_CCM_L2_STATIS_INFO_IND
*/
typedef struct CcmL2StatisInfoInd_Tag
{
    CmiDevL2StatisInfo      l2Statis;
}CcmL2StatisInfoInd;

/*
 * SIG_CCM_ERRC_PHY_STATIS_INFO_IND
*/
typedef struct CcmErrcPhyStatisInfoInd_Tag
{
    CmiDevPhyStatisInfo     phyStatis;
}CcmErrcPhyStatisInfoInd;

/******************************************************************************
 * CemmEventStatisCnf
 * SIG_CCM_GET_EMM_EVENT_STATIS_CNF
******************************************************************************/
typedef struct CcmEmmEventStatisCnf_Tag
{
    UINT16  numAttachSucc;      /* count of Attach Success */
    UINT16  numAttachFail;
    UINT16  numTauSucc;         /* count of TAU Success */
    UINT16  numTauFail;
    UINT16  numSrSucc;          /* count of Service request Success */
    UINT16  numSrFail;
    UINT16  numAuthFail;        /* count of Authentication Success */
    UINT16  numDetach;          /* count of Detach */
    UINT16  numOOS;             /* count of PLMN, OOS */
    UINT16  rsvd;
}CcmEmmEventStatisCnf;



/******************************************************************************
 * CerrcEventStatisCnf
 * SIG_CCM_GET_CERRC_EVENT_STATIS_CNF
******************************************************************************/
typedef struct CerrcEventStatisCnf_Tag
{
    UINT16  numRrcConnEstSucc;      /* count of RRC Conn Est Success */
    UINT16  numRrcConnEstFail;      /* count of RRC Conn Est fail */
}CerrcEventStatisCnf;

/*
 * SIG_CERRC_CCM_BASIC_CELL_LIST_INFO_CNF
*/
typedef CmiDevGetBasicCellListInfoCnf CerrcCcmBasicCellListInfoCnf;

/*
 * SIG_CERRC_CCM_ABORT_BASIC_CELL_LIST_INFO_CNF
*/
typedef CmiDevGetBasicCellListInfoCnf CerrcCcmAbortBasicCellListInfoCnf;

/******************************************************************************
*   SIG_CERRC_CCM_CE_INFO_IND
******************************************************************************/
typedef struct CcmErrcCeInfoInd_Tag
{
    BOOL                                    ceInfoReportingEnabled;  //Store CE reporting enable/disable info
    BOOL                                    ceEnabled;
    CmiDevErrcUEState                       ueState;    //Store the UE state  //
    UINT8                                   downlinkRepetition; //Store downlinkRepetition factor
    UINT8                                   uplinkRepetition; //Store uplinkRepetition factor
    //value in units of dBm, value range: -156 ~ -44
    INT16                                   rsrp;
    // value in dB, value range: -30 ~ 30
    INT8            cinr;
    // 0: report for SIG_CERRC_CCM_SET_CE_INFO_REQ, 1:SIG_CERRC_CCM_GET_CE_INFO_REQ ; 2: report for Unsolicited response.
    CmiDevErrcReportReason reportReason;
}CcmErrcCeInfoInd;

typedef struct CcmCesmModifyApnProfileCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmModifyApnProfileCnf;

typedef struct CcmCesmCreateApnProfileCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmCreateApnProfileCnf;

typedef struct CcmCesmGetApnProfileCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8 					searchResult;
	BOOL					oldPdpTypeValid;
	UINT8					oldPdpType;
}CcmCesmGetApnProfileCnf;

typedef struct CcmCesmGetApnDisableStatusCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8					disableStatus;
    UINT8                   reserved;
    UINT16                  reserved2;
}CcmCesmGetApnDisableStatusCnf;

typedef struct CcmCesmSetApnDisableStatusCnfTag
{
    UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8					reserved;
    UINT8                   reserved1;
    UINT16                  reserved2;
}CcmCesmSetApnDisableStatusCnf;

typedef struct CerrcCcmGetDrxParamCnf_Tag
{

    UINT32       drxcycle;

	UINT8        mode; // 0-RRC IDLE, 1- RRC CONNECTED

	UINT8		 onDurationTimer; //DrxOnDurationTimerNB

//Timer for DRX in TS 36.321 [6]. Value in number of PDCCH periods.
//Value range:{0,1,2,3,4,8,16,32}
    UINT8		drxInactivityTimer; //DrxInactivityTimerNB
//Timer for DRX in TS 36.321 [6]. Value in number of PDCCH periods.
    UINT8		drxRetransmissionTimer; //DrxRetransmissionTimerNB
//longDRX-Cycle in TS 36.321 [6]. The value of longDRX-Cycle is in number of sub-frames.
    UINT8		longdrxCycle;	//DrxCycle
//drxStartOffset in TS 36.321 [6]. Value is in number of sub-frames by step of (drx-cycle / 256).
//Value range:{0~255}
    UINT8		drxStartOffset;
//Timer for DRX in TS 36.321 [6]. Value in number of PDCCH periods.
    UINT8    	drxULRetransmissionTimer;	//DrxULRetransmissionTimerNB
}CerrcCcmGetDrxParamCnf;

/*
 * SIG_CCM_ERRC_PHY_DETECT_EVENT_IND
*/
typedef CmiDevDetectEventInd CcmErrcPhyDetectEventInd;

#endif

