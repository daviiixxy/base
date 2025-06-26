/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    cerrcsig.h
 * Description:  define all signals received by RRC module
 * History:      09/08/2017    Originated by Yunfei Li
 *
 ****************************************************************************/
#ifndef CERRC_SIG_H
#define CERRC_SIG_H
/*********************************************************************************
* Includes
*********************************************************************************/
#include "psutil.h"
#include "cmidev.h"

/*********************************************************************************
* Macros
*********************************************************************************/


/*********************************************************************************
* Type Definition
*********************************************************************************/


/*********************************************************************************
* Enums
*********************************************************************************/
/********************************************************************************
* MM->RRC
*********************************************************************************/
typedef enum CerrcDeactReasonEnum
{
    CERRC_DEACT_REASON_POWER_OFF = 0,
    CERRC_DEACT_REASON_ACTIVATE_PSM = 1,        //EMM activate PSM mode, need to deact AS layer
    //CERRC_DEACT_REASON_HIB_POWER_SAVE = 2,      //HIB DEEP SLEEP
    //CERRC_DEACT_REASON_SLEEP2_POWER_SAVE = 3    //SLEEP2 state
}CerrcDeactReason;

typedef enum CEstablishmentCauseTag
{
    CEstablishmentCause_MT_Access = 0,
    CEstablishmentCause_MO_Signalling = 1,
    CEstablishmentCause_MO_Data = 2,
    CEstablishmentCause_MO_ExceptionData = 3,    //only apply for NB-IoT
    CEstablishmentCause_Delay_Tolerant = 4,
    CEstablishmentCause_Emergency = 5,           //only apply for eMTC/Cat1
    CEstablishmentCause_HighPriorityAccess = 6,  //only apply for eMTC/Cat1
    CEstablishmentCause_spare1 = 7
}
CEstablishmentCause;        /* 36.331, 6.2.2/6.7.3.6 */

typedef enum CallTypeTag
{
    CALL_TYPE_ORIGINATING_SIGNALLING = 0,
    CALL_TYPE_ORIGINATING_CALLS = 1,
    CALL_TYPE_ORIGINATING_SMS = 2,
    CALL_TYPE_TERMINATING_CALLS = 3,
    CALL_TYPE_EMERGENCY_CALLS = 4,              //only apply for eMTC/Cat1
    CALL_TYPE_ORIGINATING_MMTEL_VOICE = 5,      //only apply for eMTC/Cat1
    CALL_TYPE_ORIGINATING_MMTEL_VEDIO = 6,      //only apply for eMTC/Cat1
    CALL_TYPE_ORIGINATING_SMSoIP = 7,           //only apply for eMTC/Cat1
    CALL_TYPE_ORIGINATING_CSFB = 8,             //only apply for eMTC/Cat1
}
CallType;

typedef enum CConnRelReasonTag
{
    CCONN_REL_NORMAL = 0,
    CCONN_REL_OTHER = 1
}
CConnRelReason;

typedef enum OperatorEnum
{
	OPERATOR_NONE = 0,
	OPERATOR_ATT = 1,
	OPERATOR_VZW = 2,
	OPERATOR_TMOBILE =3,	
	OPERATOR_TELSTRA =5 //aligned with CCM
}
Operator;

/********************************************************************************
* UP->RRC
*********************************************************************************/


/*********************************************************************************
* Structs
*********************************************************************************/
/********************************************************************************
* MM->RRC
*********************************************************************************/
typedef struct CerrcUeConfigReqTag
{
    //support or not-support
    BOOL                            sharedNetworkSupport;
    //FddTddMode: 0-FDD; 1-TDD; Only apply for Cat1/eMTC
    UINT8                           fddTddMode;
    UINT8                           reserved1;
    UINT8                           reserved2;
}CerrcUeConfigReq;


typedef enum CerrcPlmnSearchType_enum
{
    //normal plmn search, specified PLMN, and CERRC beed to start immediately in FOREGROUND
    CERRC_PLMN_SEARCH_NORMAL = 0,
    //period high plmn search, specified PLMN, cerrc should search for this high priority PLMN either in FOREGROUND or BACKGROUND
    CERRC_PLMN_SEARCH_PERIOD_HIGH_PLMN = 1,
    //manual plmn search, NO specified PLMN, trigger by AT+COPS=?, user try to find out all PLMN info, either in FOREGROUND(PSM) or BACKGROUND
    CERRC_PLMN_SEARCH_MANUAL = 2,
    //manual plmn search, trigger by AT: AT+ECBCINFO=1, try to find 5 cell info, including serving cell, just 1 serving cell + 4 neighber cells
    //if "requestedPlmn" is present, cells returned should be with the same PLMN or EPLMN, and serving cell should be in header of the list
    //if "requestedPlmn" is not present, cells (MAX 5) should be returned in order of decreasing signal quality.
    CERRC_PLMN_SEARCH_BCINFO = 3,

	CERRC_PLMN_SEARCH_GTP = 4
}CerrcPlmnSearchType;

typedef struct CerrcPlmnSearchReqTag
{
    //CerrcPlmnSearchType: Normal(0), PeriodHigh(1), Manual(2)
    UINT8                           searchType;
    //Number of frequency UE should scan during PLMN
    UINT8                           numOfFreq;
    //Number of band UE should scan during PLMN
    UINT8                           numOfBand;
    //requestedPlmnValid is FALSE when executing manual PLMN search
    //otherwise, requestedPlmnValid should always be TRUE
    BOOL                            requestedPlmnValid;
    //only sent one PLMN to RRC, other EPLMN stored by NAS
    //RRC will get EPLMN list by calling API
    Plmn                            requestedPlmn;

    /*
     * Cell lock feature, if cell lock:
     *  1> "bCellLock" should be TRUE;
     *  2> "numOfFreq" should be 1, and "numOfBand" should be 0;
    */
    BOOL                            bCellLock;      //Be lock cell,
    /* plmnSearchSeqNum is just used for FG plmn Search and bCellLock is False,
       otherwise plmnSearchSeqNum should be 0
     */
    UINT8                           plmnSearchSeqNum;
    //UINT16                          lockPhyCellId;  //range(0..503), 0xFFFF means invalid, only valid when cell lock
    /*
     * Lock/Preferred PHY Cell ID, used in two cases:
     * 1> Cell lock, if phyCellId specified to lock;
     * 2> PhyCellId which need PHY prefer to find, last serving cell phyCellId, only valid between CerrcPlmnSearchReq/CerrcPlmnSearchCnf
    */
    UINT16                          phyCellId;   //range(0..503), 0xFFFF means invalid

    /*
     * MAX cell number request to Measurement/search/return,
     * 1> only valid when "searchType" == CERRC_PLMN_SEARCH_BCINFO, and "reqMaxBCCellNum" should <= 5;
     * 2> for other "searchType", set to zero
    */
    UINT8                           reqMaxBCCellNum;
    UINT8                           mccFeatureEnabled;
    UINT16                          rsvd1;

    //the left most bit is 31, euArfcn is bit[23:0]
    //[31:24] represents CarrierFreqOffset
    UINT32                          freqList[SUPPORT_MAX_FREQ_NUM+1];
    //See TS36.101 section 5.5, value range: 1~256
    //now support to 255
    UINT8                           bandList[RRC_PHY_SUPPORT_BAND_NUM];

    //As per GTP SCAN REQUEST
	UINT8                           Sib1count;

    UINT8                           Sib1flag[SUPPORT_MAX_FREQ_NUM];
	
}CerrcPlmnSearchReq;

typedef GosEmptySignal  CerrcNextPlmnSearchReq;

typedef GosEmptySignal  CerrcAbortPlmnSearchReq;

typedef GosEmptySignal  CerrcAuthFailInd;


typedef struct CerrcActReqTag
{
    //Number of frequency UE should scan during PLMN
    UINT8                           numOfFreq;
    //Number of band UE should scan during PLMN
    UINT8                           numOfBand;
    //for NB-IoT, this flag is always TRUE???
    BOOL                            requestedPlmnValid;

    /*
     * Cell lock feature, if cell lock:
     *  1> "bCellLock" should be TRUE;
     *  2> "numOfFreq" should be 1, and "numOfBand" should be 0;
    */
    BOOL                            bCellLock;      //Be lock cell,

    /* actReqSeqNum is just used for numOfBand > 0 and bCellLock is False,
       otherwise actReqSeqNum should be 0
    */
    UINT8                           actReqSeqNum;
    UINT8                           reserved;
    //UINT16                          lockPhyCellId;  //range(0..503), 0xFFFF means invalid, only valid when cell lock,
    /*
     * Locked/Preferred PHY Cell ID, used in two cases:
     * 1> Cell lock, if phyCellId specified to lock;
     * 2> PhyCellId which need PHY prefer to find, last serving cell phyCellId, only valid between CerrcActReq/CerrcActCnf
    */
    UINT16                          phyCellId;   //range(0..503), 0xFFFF means invalid

    //only sent one PLMN to RRC, other EPLMN stored by NAS
    //RRC will get EPLMN list by calling API
    Plmn                            requestedPlmn;
    //the left most bit is 31, euArfcn is bit[23:0]
    //[31:24] represents CarrierFreqOffset
    UINT32                          freqList[SUPPORT_MAX_FREQ_NUM+1];
    //See TS36.101 section 5.5, value range: 1~256
    //now support to 255
    UINT8                           bandList[RRC_PHY_SUPPORT_BAND_NUM];
}CerrcActReq;

typedef struct CerrcDeactReqTag
{
    UINT8                           deactReason;  //CerrcDeactReason
    UINT8                           reserved0;
    UINT8                           reserved1;
    UINT8                           reserved2;
}CerrcDeactReq;

typedef struct CerrcNasMsgReqTag
{
    UINT16                          nasMessageLength;
    BOOL                            needTransResultInd;
    UINT8                           nasMessageIndex; //RRC PDU ID, range(1..5, 17..255)
    UINT8                           *nasMessage;    //ALWAYS be freed by AS, either ERRC or UP

    UINT8                           dataRaiInfo;    /*DataRelAssistIndEnum*/
    UINT8                           tickType;       /* UlPduTickType, indicate the "sysTick" type */
    UINT16                          reserved;

    UINT32                          sysTick;
}CerrcNasMsgReq;

typedef struct CAreaIdentityTag
{
    Tai                             tai;
}CAreaIdentity;

typedef struct CerrcConnReqTag
{
    UINT16                          nasMessageLength;
    UINT8                           establishmentCause; //CEstablishmentCause
    UINT8                           nasMessageIndex; //RRC PDU ID, range(1..5, 17..255)

    UINT8                           *nasMessage;    //this memory is always freed by AS(RRC or UP)

    UINT8                           callType;   //CallType
    BOOL                            attachWithoutPDNConnectivity;
    //Indicate if the UE supports the User plane CIoT EPS Optimisation, see TS 24.301
    BOOL                            upCIoTOptimisation;
    //TRUE means DCN-ID will be included in the RrcConnectionSetupComplete message
    BOOL                            dcnIdPresent;

    //DCN identity identifies a specific decicated core network, range(0..65535)
    UINT16                          dcnId;
    //0 indicate HPLMN or EHPLMN, 1 indicate OPLMN, 2 indicate non-HPLMN/EHPLMN/OPLMN
    UINT8                           plmnType;
    UINT8                           dataRaiInfo;    /*DataRelAssistIndEnum*/

    CAreaIdentity                   areaIdentity;

    //3 the followed parameters are only apply for Cat1/eMTC
    //Indicate if the UE supports the Control plane CIoT EPS Optimisation, see TS 24.301
    BOOL                            cpCIoTOptimisation;
    //Indicate if the UE subject to EAB, TBD
    BOOL                            subjectToEab;
    //Indicate if the UE subject to ACDC, TBD
    BOOL                            subjectToAcdc;
    //Indicates the ACDC category as defined in TS 24.105, range (1..16)
    UINT8                           acdcCategory;
}CerrcConnReq;

/* RRC will resume the signalling first, then send CerrcResumeCnf to MM,
 * MM then send CerrcNasMsgReq, for example ESM data request, to RRC */
typedef struct CerrcResumeReqTag
{
    UINT8                           establishmentCause;  //CEstablishmentCause
    UINT8                           callType;   //CallType
    BOOL                            attachWithoutPDNConnectivity;
    //Indicate if the UE supports the User plane CIoT EPS Optimisation, see TS 24.301
    BOOL                            upCIoTOptimisation;

    //0 indicate HPLMN or EHPLMN, 1 indicate OPLMN, 2 indicate non-HPLMN/EHPLMN/OPLMN
    UINT8                           plmnType;
    UINT16                          nasMessageLength;  //estimate by CEMM, CEMM->CERRC used to calculate msg5 len in advance
    UINT8                           reserved0;

    CAreaIdentity                   areaIdentity;

    //3 the followed parameters are only apply for Cat1/eMTC
    //Indicate if the UE supports the Control plane CIoT EPS Optimisation, see TS 24.301
    BOOL                            cpCIoTOptimisation;
    //Indicate if the UE subject to EAB, TBD
    BOOL                            subjectToEab;
    //Indicate if the UE subject to ACDC, TBD
    BOOL                            subjectToAcdc;
    //Indicates the ACDC category as defined in TS 24.105, range (1..16)
    UINT8                           acdcCategory;
}
CerrcResumeReq;

typedef struct CerrcConnRelReqTag
{
    UINT8                           reason; //CConnRelReason
    UINT8                           reserved0;
    UINT8                           reserved1;
    UINT8                           reserved2;
}
CerrcConnRelReq;

typedef struct CerrcNasSecurityKeyCnfTag
{
    AsmeKey                         kasme;
    NasCount                        uplinkNasCount;
}
CerrcNasSecurityKeyCnf;

typedef struct StmsiTag
{
    UINT8                           mmeCode;
    UINT8                           reserved0;
    UINT16                          reserved1;
    UINT32                          mTmsi;
}
Stmsi;

typedef enum GutiElemTypeTag
{
    GUTI_STMSI,
    GUTI_GUMMEI,
    GUTI_INVALID
}
GutiElemType;

typedef struct MmeIdentityTag
{
    UINT16                          mmeGroupId;
    UINT8                           mmeCode;
    UINT8                           reserved0;
}
MmeIdentity;

typedef struct GuMmeiTag
{
    Plmn                            plmn;
    MmeIdentity                     mmeId;
    //BOOL         threeDigitMnc;  don't need this BOOL
}
GuMmei;

typedef struct GutiElementTag
{
    UINT8                           gutiElemType;  //GutiElemType
    UINT8                           reserved0;
    UINT16                          reserved1;
    Stmsi                           sTmsi;
    GuMmei                          guMmei;
}
GutiElement;

typedef struct CerrcNasExtendDrxConfigTag
{
    //eDRX cycle, see TS24.008 section 10.5.5.32, value range: 5.12~10485.76 seconds
    //EdrxValueForS1Mode
    UINT8                           eDrxCycle;
    //Length of PTW, see TS24.008 section 10.5.5.32, value range:256*(1~16)*10ms
    //PagingTimeWindowForNBMode
    UINT8                           ptwLength;

    //UE specific DRX cycle is configured by upper layer, see TS24.008 section 10.5.5.6
    BOOL                            specificDrxCyclePresent;
    //DrxCycleLengthAndValueForS1
    UINT8                           specificDrxCycle;
}CerrcNasExtendDrxConfig;

//based on TS23.003-2.3
#define MAX_IMSI_DIGIT_NUM          15
typedef struct CerrcSimInfoUpdateReqTag
{
    //digit number of IMSI, when sim is removed, set this length as zero
    UINT8                           imsiLength;
    //if the IMSI is "123456", imsi[0]=1, imis[1]=2...
    /* The IMSI is not more than 15 digits,it is composed as:MCC(3 digits)+MNC(2 or 3 digits)+MSIN */
    UINT8                           imsi[MAX_IMSI_DIGIT_NUM];
    /* according to 31.102, the access info is mapping as the rules: Byte 1: bit8~bit1 -->ACC15~08; Byte 2: bit8~bit1 -->ACC07~00 */
    /* accessClass = Byte1 + Byte2 */
    UINT16                          accessClass;
    UINT16                          reserved0;
}CerrcSimInfoUpdateReq;

typedef enum UpdateEdrxFlagTag
{
    SETUP_EDRX,
    RELEASE_EDRX,
    NOT_CHANGE_EDRX
}
UpdateEdrxFlag;

typedef enum UpdateRestrictEcFlagTag
{
    RESTRICTION_ON_USE_OF_EC_NOT_SUPPORTED = 0,
    RESTRICTION_ON_USE_OF_EC_SUPPORTED = 1
}
UpdateRestrictEcFlag;

typedef struct CerrcNasInfoUpdateReqTag
{
    //TRUE means update Restriction on use of enhanced coverage
    BOOL                            restrictEcPresent;
    //TRUE means update simInfo, FALSE means not update simInfo
    UINT8                           simInfoPresent;
    //TRUE means update GUTI, FALSE means not update GUTI
    UINT8                           gutiPresent;
    //UpdateEdrxFlag
    UINT8                           eDrxConfigType;
    //TRUE means update requestedPlmn(ATTACH/TAU success), FALSE means not update requestedPlmn
    BOOL                            requestedPlmnPresent;

    //UpdateRestrictEcFlag
    UINT8                           restrictEc;
    UINT16                          reserved0;
    CerrcSimInfoUpdateReq           simInfo;
    GutiElement                     guti;
    CerrcNasExtendDrxConfig         eDrxConfig;
    Plmn                            requestedPlmn;
}CerrcNasInfoUpdateReq;

typedef struct CerrcCellLockReqTag
{
    BOOL                            cellLockEnable;
    //0: CELL_LOCK_NONE, 1: CELL_LOCK_FREQ_ONLY, 2: CELL_LOCK_FREQ_CELL
    UINT8                           mode;
    UINT16                          phyCellId;//0~503
    //the left most bit is 31, euArfcn is bit[23:0]
    //[31:24] represents CarrierFreqOffset
    UINT32                          carrierFreq;
}CerrcCellLockReq;

//exit from deep-sleep with eDrx or PSM
//typedef CerrcNasInfoUpdateReq   CerrcPowerRecoverReq;
typedef struct CerrcPowerRecoverReqTag
{
    CerrcNasInfoUpdateReq           nasInfo;

    //indicate if currently under PSM state
    //TRUE means under PSM state, only valid when ERRC in DEACT state
    BOOL                            bPsmState;
    UINT8                           rsvd[3];
}CerrcPowerRecoverReq;

/*
* EMM -> ERRC, to indicate the NAS selected PLMN
* Apply for shared network, i.e. there is at least 2 PLMN in one cell.
* ALWAYS send after CerrcActCnf/CerrcActInd
* when CerrcActCnf/CerrcActInd includes 2 or more PLMNs,
* and NAS selected a different PLMN other than the PLMN indicated by selectedPlmnIndex
*/
typedef struct CerrcUpdateSelectedPlmnIndTag
{
    Plmn                            selectedPlmn;
}CerrcUpdateSelectedPlmnInd;


/********************************************************************************
* UP->RRC
*********************************************************************************/
/*
typedef struct CecpDataIndTag
{
    UINT8              numberOfSdus;
    UINT8              srbId[NB_SRB_NUM];
    SrbPdcpSdu         pdcpSdu[NB_SRB_NUM]; //Macro for 4 // seems not right, need to change, -TBD, - jcweng
}
CecpDataInd;
*/

/******************************************************************************
 * DL RRC PDU   //SIG_CECP_DATA_IND
 * CecpDataInd
******************************************************************************/
#define MAX_DL_RRC_PDU_NUM 2

typedef struct CeDlRrcPduTag
{
    UINT16                          length; //byte length

    /*
     * LCID for each RRC PDU, for NB in fact only one SRB: SRB1bis: 3, SRB1: 1
     * // UINT8 srbId, as for NB, no "srbId" configed;
    */
    UINT8                           lcid;
    BOOL                            bDeciphered;  // whether this PDU had deciphered by PDCP

    /*
     * as some CERRC message need to do integrity check in CERRC side,
     *  so need "count" as a input parameters for integrity checking
    */
    UINT32                          dlCount;    // pdcp count, this value is uesd when calc XmacI of SecurityModeCommand msg

    /*
     * dynamic memory
     * 1> SRB1/SRB2:
     *    Include (the first byte is) PDCP header, as some CERRC message need to do integrity check in CERRC side
     *     and "PDCP header" need to take into integrity checking
     * 2> SRB1bis
     *    As no PDCP entity for SRB1bis, here no PDCP header, and "pData" just point to RRC PDU
    */
    UINT8                           *pData;
}CeDlRrcPdu; // 12 bytes

/*
 * !!! Note: !!!
 * As this signal just send from ISR, and signal size should not extend PS_OSA_ISR_SIG_BODY_MAX_SIZE(28) bytes
*/
typedef struct CecpDataIndTag
{
    UINT8                           rrcPduNum;
    UINT8                           reserved0;
    UINT16                          reserved1;
    CeDlRrcPdu                      pdu[MAX_DL_RRC_PDU_NUM]; // if more than 3 RRC PDU in PDCP side, PDCP need to send 2(or more) signal
}CecpDataInd;   //28 bytes


/******************************************************************************
 * CecpDataCnf
 * PDCP -> CERRC, confirm which RRC PDU has been sent successfully
******************************************************************************/
#if 0
#define MAX_CONFIRM_RRC_PDU_NUM 3
typedef struct CecpDataCnfTag
{
    UINT8   numberOfRrcPduId : 2; //The number of UL information transfer message Id confirmed by PDCP
    UINT8   pdu1Sent : 1;
    UINT8   pdu2Sent : 1;
    UINT8   pdu3Sent : 1;
    UINT8   reserved : 3;

    UINT8   rrcPduId[MAX_CONFIRM_RRC_PDU_NUM];
}CecpDataCnf;
#endif
typedef struct CecpDataCnfTag
{
    UINT8   failPduNum;
    UINT8   succPduNum;
    UINT16  rsvd;

    /*
     * if PDUID = 0 sent failed, then failPduIdBitmap[0].bit0 = 1;
     * if PDUID = 31 sent failed, then failPduIdBitmap[0].bit31 = 1;
     * if PDUID = 32 sent failed, then failPduIdBitmap[1].bit0 = 1;
     * ...
     * if PDUID = 255 sent failed, then failPduIdBitmap[7].bit0 = 1;
     */
    UINT32  failPduIdBitmap[MAX_NAS_MSG_BITMAP_NUM];
    /*
     * if PDUID = 0 sent succ, then succPduIdBitmap[0].bit0 = 1;
     * if PDUID = 31 sent succ, then succPduIdBitmap[0].bit31 = 1;
     * if PDUID = 32 sent succ, then succPduIdBitmap[1].bit0 = 1;
     * ...
     * if PDUID = 255 sent failed, then failPduIdBitmap[7].bit0 = 1;
     */
    UINT32  succPduIdBitmap[MAX_NAS_MSG_BITMAP_NUM];
}CecpDataCnf;   //68 bytes

typedef struct CepdcpIntegrityCalcCnfTag
{
    UINT32                          macI;
}CepdcpIntegrityCalcCnf;

/*
typedef struct CepdcpIntegrityCheckFailIndTag
{
    UINT8         reserved;     //RRC don't need info from pdcp so far, just keep this struct here
}
CepdcpIntegrityCheckFailInd;
*/
typedef GosEmptySignal CepdcpIntegrityCheckFailInd;

typedef struct CerlcRetransMaxFailIndTag
{
    UINT8                           lcid;
    UINT8                           reserved0;
    UINT16                          reserved1;
}CerlcRetransMaxFailInd;

/*
typedef struct CerlcConnectReleaseAckCnfTag
{
    BOOL     delayTimeout;
    UINT8    reserved0;
    UINT16   reserved1;
}
CerlcConnectReleaseAckCnf;
*/
typedef GosEmptySignal CerlcConnectReleaseAckCnf;

//typedef GosEmptySignal CerlcDedicatedReconfigAckCnf;

typedef struct  CemacResetCnfTag
{
    UINT8                           reason; //MacResetReason
    UINT8                           reserved0;
    UINT16                          reserved1;
}CemacResetCnf;

typedef enum AccessResultTag
{
    ACCESS_SUCCESS,
    ACCESS_ERROR,
}AccessResult;

typedef struct CemacRAIndTag
{
    UINT8                           result;  // AccessResult
    UINT8                           reserved0;
    UINT16                          crnti;   // RRCConnectionReestablishmentRequest need C-RNTI, only valid when RA success
}CemacRAInd;

typedef struct CemacCcchDataIndTag
{
    UINT16                          length;
    UINT16                          reserved0;
    UINT8                           *data;  // dynmaic memory
}CemacCcchDataInd;

//typedef UINT8  CemacTATimerExpiryInd;   //NULL message
typedef GosEmptySignal  CemacTATimerExpiryInd;

/*
 * SIGID: SIG_CEUP_ABORT_IND
*/
typedef GosEmptySignal  CeupAbortInd;

/******************************************************************************
 * CCM(LPP)->RRC
******************************************************************************/
/******************************************************************************
 *  CerrcLocMeasReq  SIG_CERRC_LOC_MEAS_REQ
 * CCM LPP -> CERRC, to get loc measurement result
******************************************************************************/
typedef struct CerrcLocMeasReqTag
{
    BOOL                      otdoaMeasPresent;
    BOOL                      ecidMeasPresent;
    UINT16                    reserved;
    CmiOtdoaMeasReqData       otdoaReqData; //272 bytes
    CmiEcidMeasReqData        ecidReqData;  //4 bytes
}CerrcLocMeasReq;        // 280 bytes

/******************************************************************************
 *  CerrcStopLocMeasReq  SIG_CERRC_STOP_LOC_MEAS_REQ
 * CCM LPP -> CERRC, to stop loc measurement
******************************************************************************/
typedef struct CerrcStopLocMeasReqTag
{
    BOOL                           withTempResult;
    UINT8                          reserved0;
    UINT16                         reserved1;
}CerrcStopLocMeasReq;

/******************************************************************************
 *  CerrcEarlyLocMeasReq  SIG_CERRC_EARLY_LOC_MEAS_REQ
 * CCM LPP -> CERRC, to ask ERRC to report current otdoa/ecid measurement result
******************************************************************************/
typedef GosEmptySignal CerrcEarlyLocMeasReq;

/******************************************************************************
 * SIG_CERRC_CCM_SET_PARAM_REQ
 *  used to set some RRC configed parameters (capability)
******************************************************************************/
typedef struct CerrcCcmSetParamReqTag
{
    BOOL    upRaiPresent;
    BOOL    supportUpRai;   /*indicate capability: rai-Support-r14*/

    BOOL    dataInactTimerPresent;
    UINT8   dataInactTimerS;    /*DataInactivityTimer-r14, used in CERRC; should > 40s, and max: 180s; 0 - just means not use DataInactivityTimer feature */

    BOOL    relaxMonitorPresent;
    UINT8   relaxMonitorDeltaP; /*range [0..15], value in dB, 0 means relaxed monitoring(36.304, 5.2.4.12) in is not used, used in CERRC*/

    BOOL    relVersionPresent;
    UINT8   relVersion;         /*release version, only 13 - 14*/

    BOOL    multiCarrierPresent;
    BOOL    supportMultiCarrier;   /*indicate capability: multiCarrier_r13*/

    BOOL    multiTonePresent;
    BOOL    supportMultiTone;   /*indicate capability: multiTone_r13*/

    BOOL    enableCellReselPresent;
    BOOL    enableCellResel;

    BOOL    enableConnReEstPresent;
    BOOL    enableConnReEst;

    BOOL    nbCategoryPresent;
    UINT8   nbCategory;         /* Configure the NB-IoT category. Only support 1 and 2 now */

    BOOL    disableNCellMeasPresent;
    BOOL    disableNCellMeas;

    /*Band & powerClass should always set together, and band should belong to supported band list*/
    BOOL    bandPresent;
    UINT8   band;               /*Band 0 means set all band, otherwise, set specific band's power class*/
    BOOL    powerClassPresent;
    UINT8   powerClass;         /*the UE power class, valid value 3/5/6, TS36.101, Table 6.2.2F-1*/

    UINT8   setParamType;   /* CerrcCcmParamType */
	
	//Guard timer for cell search in seconds
	BOOL     cellSearchGuardTimerPresent;
	UINT16    cellSearchGuardTimerS; //cellSearchGuardTimer

	UINT8    dataInactMon_r14Present;
    BOOL	 dataInactMon_r14;

	UINT8    interferenceRandomisation_r14Present;
	BOOL     interferenceRandomisation_r14;

	BOOL    SupportTwoHarqPresent;
	BOOL    SupportTwoHarq;

	BOOL    SupportMultiCarrierNPRACHPresent;
	BOOL    SupportMultiCarrierNPRACH;

	BOOL    SupportMultiCarrierPagingPresent;
	BOOL    SupportMultiCarrierPaging;

	BOOL    CpReestablishmentPresent;
	BOOL    CpReestablishment;
	
    UINT8   rsv0;
    UINT16  rsv1;
}CerrcCcmSetParamReq;

/******************************************************************************
 * SIG_CERRC_CCM_SET_OPERATOR_CONFIG
 *  used to set operator flag
******************************************************************************/
typedef struct CerrcCcmSetOperatorConfigTag
{
    /*Operator ::   0x00 : No operator info
 					0x01 : AT&T
					0x02 : VZW
					0x03 : T-Mobile*/
    UINT8                           operator;
}CerrcCcmSetOperatorConfig;

/******************************************************************************
 * SIG_CERRC_CCM_GET_PARAM_REQ
 *  used to get some RRC configed parameters (capability)
******************************************************************************/
typedef enum CerrcCcmParamType_Tag
{
    CERRC_CCM_PARAM_EXTENDED_CONFIG,
    CERRC_CCM_PARAM_POWER_CLASS,
    CERRC_CCM_PARAM_POWER_CLASS_CAPABILITY,
    CERRC_CCM_PARAM_REL_FEATURE,
}CerrcCcmParamType;

typedef struct CerrcCcmGetParamReqTag
{
    UINT8   getParamType;   /* CerrcCcmParamType */
    UINT8   reserved0;
    UINT16  reserved1;
}CerrcCcmGetParamReq;

/******************************************************************************
 * SIG_CERRC_CCM_SET_CE_INFO_REQ
 * used to set CE INFO reporting
******************************************************************************/
typedef struct CcmSetErrcCEInfoReqTag
{
    BOOL                                    ceInfoReporting;  
} CcmSetErrcCEInfoReq;


/******************************************************************************
 * SIG_CERRC_CCM_GET_CE_INFO_REQ
 * used to get CE INFO parameters
******************************************************************************/
typedef GosEmptySignal      CcmGetErrcCEInfoReq;


/******************************************************************************
 * SIG_CCM_GET_ERRC_PHY_STATUS_REQ
 *  used to get ERRC & PHY status parameters
 *  ERRC need to FWD a signal to PHY, to get its status parameters
******************************************************************************/
typedef GosEmptySignal      CcmGetErrcPhyStatusReq;


/******************************************************************************
 * SIG_CERRC_CCM_BASIC_CELL_LIST_INFO_REQ
 *  Get basic cell info, including SCell & NCell
******************************************************************************/
//typedef GosEmptySignal      CerrcCcmBasicCellListInfoReq;
typedef struct CerrcCcmBasicCellListInfoReq_Tag
{
    UINT8   reqMaxCellNum;      //MAX cell measurement/return, inclduing serving cell, MAX value: 5, 1 serving cell + 4 neighber cell
    UINT8   rsvd0;
    UINT16  rsvd1;
}CerrcCcmBasicCellListInfoReq;


/******************************************************************************
 * SIG_CERRC_CCM_ABORT_BASIC_CELL_LIST_INFO_REQ
******************************************************************************/
typedef GosEmptySignal      CerrcCcmAbortBasicCellListInfoReq;


/******************************************************************************
 * SIG_CCM_ERRC_PHY_STATIS_OPER_REQ
 *  CCM let ERRC & PHY to start/stop/get statistic info
******************************************************************************/
typedef struct CcmErrcPhyStatisOperReq_Tag
{
    UINT8       statisReqType;  //CcmStatisReqType
    UINT8       rsvd0;
    UINT16      rsvd1;
}CcmErrcPhyStatisOperReq;


/******************************************************************************
 * SIG_CCM_ERRC_EVENT_STATIS_REQ
 *  CCM let ERRC to start/stop/get statistic info
******************************************************************************/
typedef struct CcmErrcEventStatisOperReq_Tag
{
    UINT8       statisReqType;  //CcmEventStatisReqType
    UINT8       rsvd0;
    UINT16      rsvd1;
}CcmErrcEventStatisOperReq;

typedef GosEmptySignal CcmGetErrcDrxParamReq;

#endif

