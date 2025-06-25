
#ifndef _CEMM_PLMN_MSG_H_
#define _CEMM_PLMN_MSG_H_
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - cemmplmnmsg.h
Description:    - Define the interface between EMM and PLMN.
Function List:  -
History:        -
*******************************************************************************/

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "cemmsig.h"
#include "cerrcsig.h"
#include "ccmsig.h"

/******************************************************************************
 *****************************************************************************
 * ENUM & MARCO
 *****************************************************************************
******************************************************************************/
typedef enum CemmAsStateEnum_Tag
{
    CEMM_AS_IDLE = 0,
    CEMM_AS_GO_IDLE,
    CEMM_AS_CONNECTING,
    CEMM_AS_CONNECTED,
}CemmAsStateEnum;


typedef enum CemmPlmnIdleReqCause_Tag
{
    MANUAL_SEARCH_NEED_GO_IDLE,
	GTP_SEARCH_NEED_GO_IDLE,
    CHANGE_PLMN_NEED_GO_IDLE
}CemmPlmnIdleReqCause;

/*
 * Deact cause send in "CePlmnProcDeactReqMsg" by CEMM
*/
typedef enum CemmPlmnDeactCause_Tag
{
    CEMM_PLMN_DEACT_DETACH,
    CEMM_PLMN_DEACT_POWER_OFF,
    CEMM_PLMN_DEACT_ACT_PSM,
    CEMM_PLMN_DEACT_CRITICAL_REJECT,
    CEMM_PLMN_DEACT_BUTT
}CemmPlmnDeactCause;

typedef enum CemmPlmnBlockReason_Tag
{
    CEMM_PLMN_BLOCK_REASON_NONE,
    CEMM_PLMN_BLOCK_REASON_T3402,
    CEMM_PLMN_BLOCK_REASON_REJ_BY_CAUSE_42,
    CEMM_PLMN_BLOCK_REASON_SMS_UNAVAILABLE_IN_THIS_PLMN
}CemmPlmnBlockReason;


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/


/*******************************************************************************
 * CEMM->PLMN
*******************************************************************************/
typedef struct CemmPlmnSelectReq_Tag
{
    UINT8   nwMode;             /* NwMode */
    UINT8   plmnSelectType;     /* CemmPlmnSelectTypeEnum */
    UINT16  reserved0;

    Plmn    manualPlmn;         /* if "plmnSelectType" is "CEMM_MANUAL_PLMN_REG/CEMM_MANUAL_THEN_AUTO_PLMN_REG" */

    BOOL    blockedPlmnPresent; /* whether any blocked PLMN & TAC valid */
    BOOL    fplmnPresent;
    BOOL    gprsFPlmnPresent;

    /* Two cases:
     * 1: A PLMN on which ATTACH/TAU attempt counter reached 5 and T3402 has been started
     * 2: Rejected by cause 42
     */
    UINT8   blockedPlmnReason;
    Plmn    blockedPlmn;
    Plmn    fPlmn;          /* forbidden PLMN  */
    Plmn    gprsFPlmn;
    UINT16  blockedTac;
    UINT8   abortPlmn;
    UINT8   reserved2;
}CemmPlmnSelectReq;

/*******************************************************************************
 * PLMN->CEMM
*******************************************************************************/
typedef struct CemmPlmnSelectCnf_Tag
{
    //UINT8   numOfReq;
    //UINT8   numOfBand;
    BOOL    selectPlmnValid;
    UINT8   reserved0;
    UINT16  reserved1;

    Plmn    selectedPlmn;

    /*
     * FREQ & BAND info, PLMN just provide a API to fill it
    */
    //UINT32  freqList[SUPPORTED_MAX_FREQ_NUM + 1];
    //UINT16  bandList[RRC_PHY_SUPPORT_BAND_NUM];
}CemmPlmnSelectCnf;

typedef CemmPlmnSelectCnf CemmPlmnSelectInd;

typedef struct CemmPlmnPowerRecoveryInfo_Tag
{
    BOOL    bRegistered;    /* whether UE already registered */
    UINT8   reserved0;
    UINT16  reserved1;
}CemmPlmnPowerRecoveryInfo;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/******************************************************************************
 * CEMM PLMN functions, which called by CEMM/Other sub-modules
******************************************************************************/
/*
 * PLMN API
 * When CEMM/NAS task receive "SIG_CEMM_SIM_APP_READY_IND"
*/
void CePlmnSimReadyInd(CemmSimAppReadyInd *pSimAppReadyInd);

/*
 * CEMM API
 * Just get current AS connection state
*/
CemmAsStateEnum CemmGetCurAsState(void);

void CePlmnSendGtpPlmnSearchReqSig(CemmGtpPlmnSearchReq *pGtpSearchReq);

/*
 * PLMN API
*/
void CePlmnFillActReqInfo(CerrcActReq *pActReq, BOOL isPsmAct);

/*
 * PLMN API
 * When CEMM registered a PLMN, notify the PLMN sub-module the registered PLMN info
*/
void CePlmnRegisteredInd(Plmn plmn, BOOL bUpdateEplmn, UINT8 eplmnNum, Plmn *pEplmnList);

/*
 * PLMN API
*/
void CePlmnDeregisteredInd(BOOL bDelEplmn);

/*
 * PLMN API
 * cases:
 * 1> T3402 expiry
 * 2> Reject cause #42, blocked this PLMN for 2*T period, after this time expiry, call it
*/
void CePlmnRemoveBlockedPlmn(Plmn plmn);


/*
 * PLMN API
 * T3245 expiry or receive AT$QCRMFPLMN
 * Upon expiry of the timer T3245 or receive AT$QCRMFPLMN, the UE shall erase the "forbidden PLMN list", 
 * the "forbidden PLMNs for GPRS service" list, and the "forbidden PLMNs for attach in S101 mode" list 
 * and set the USIM to valid for non-EPS and EPS services
*/
void CePlmnRemoveAllFplmn(BOOL rmNvmFplmn, BOOL rmSimFplmn);

/*
 * PLMN API
*/
CemmPlmnSelectTypeEnum CePlmnGetPlmnSelectType(void);

/*
 * PLMN API
*/
void CePlmnAddPreferFreq(UINT32 euArfcn, UINT16 phyCellId);

/*
 * PLMN API
*/
void CePlmnDelPreferFreq(UINT32 *pFreqList, UINT8 num);

/*
 * PLMN API
*/
void CePlmnDelPhyCellId(void);

/*
 * PLMN API
*/
void CePlmnDelLastPreferFreq(void);

/*
 * PLMN API
*/
BOOL CePlmnIsEHplmn(Plmn plmn);

/*
 * PLMN API
 * return "minutes" time
*/
UINT16 CePlmnGetPlmnTMinVaule(void);

/*
 * PLMN API
 * Called by CEMM, when received "CemmSimReadDataCnf" from SIM
 *  which "reqItem" is "CEMM_REQ_R_FPLMN/CEMM_REQ_R_UPLMN/CEMM_REQ_R_HPLMN/CEMM_REQ_R_OPLMN/CEMM_REQ_R_EHPLMN"
*/
void CePlmnSimReadDataCnf(CemmSimReadDataCnf *pSimReadCnf);

/*
 * PLMN API
 * Called by CEMM, when received "CemmSimWriteDataCnf" from SIM
 *  which "reqItem" is "CEMM_REQ_ADD_FPLMN/CEMM_REQ_DEL_FPLMN"
*/
void CePlmnSimWriteDataCnf(CemmSimWriteDataCnf *pSimWriteCnf);

/*
 * PLMN API
 * Called by CEMM, when received "CemmSimUsatRefreshFcnInd" from SIM
 *  which "reqItem" is "CEMM_REQ_R_HPPLMN"
*/
void CePlmnSimRefreshFcnInd(CemmSimUsatRefreshFcnInd    *pSimRefreshFcnInd);

/*
 * PLMN API
 * Called by CEMM, when received "CerrcPowerRecoverCnf" from ERRC
*/
void CePlmnSetRfBandCapability(UINT32 *pBand);

/*
 * PLMN API
 * Called by CEMM, when received "SIG_CEMM_CCM_SET_PARM_REQ" from Ccm
*/
void CePlmnSetPlmnRegTypeParm(CcmSetPlmnRegTypeParm *pSetPlmnRegTypeParm);

/*
 * PLMN API
 * Called by CEMM, when received "SIG_CEMM_CCM_GET_PARM_REQ" from Ccm
*/
void CePlmnGetPlmnRegTypeParm(CcmGetPlmnRegTypeParm *pGetPlmnRegTypeParm);

/*
 * PLMN API
 * Called by CEMM, when received "SIG_CEMM_CCM_SET_PARM_REQ" from Ccm
 */
void CePlmnSetPlmnSearchPowerLevel(PlmnSearchPowerLevel plmnSearchPowerLevel);

/*
 * PLMN API
 * Called by CEMM, when received "SIG_CEMM_CCM_GET_PARM_REQ" from Ccm
 */
PlmnSearchPowerLevel CePlmnGetPlmnSearchPowerLevel(void);

/*
 * PLMN API
 * Called by CEMM, when recovery from HIB/Sleep2 state
*/
void CePlmnSetPowerRecoveryInfo(CemmPlmnPowerRecoveryInfo *pPlmnPowerRecoveryInfo);

/*
 * PLMN API
 * Called by CEMM, when enter HIB/Sleep2 state
*/
void CePlmnSaveDeepSleepInfo(void);

/*
 * PLMN API
 * Called by CEMM, to return blocked PLMN info
*/
void CePlmnGetBlockedPlmnInfo(Plmn *pBlockPlmn, CemmPlmnBlockReason *pBlockReason, UINT16   *blockTac);

/*
 * PLMN API
 * Called by CEMM, to return PLMN Search State info
*/
void CePlmnGetPlmnSelectStateParm(CemmGetPlmnSelectStateParmInfo *pGetPlmnSelectStateParm);

/*
 * PLMN API
 * Called by CEMM, to return PLMN EM status Para info
*/
void CePlmnGetEMPlmnStatusParm(CcmGetNasStatusCnf *pGetNasStatusCnf);

/*
 * CEMM API
 * Just get IMSI from PLMN module when wake up
*/
void CemmGetImsi(Imsi *imsi);

/*
 * PLMN API
 * Called by CEMM, set the prefer FREQ list
*/
void CePlmnSetPreferFreqList(UINT32 *pFreqList, UINT8 freqNum);

/*
 * PLMN API
 * Called by CEMM, Clear Plmn Search Seq Num
*/
void CePlmnClearPlmnSearchSeqNum(void);


/*
 * CEMM PLMN API
 * Decide whether the plmn is in the eplmn list
*/
BOOL CePlmnIsEqualRplmn(Plmn plmn);

/*
 * CE PLMN API
 * Called by EMM, when remove rplmn in sim
*/
void CePlmnRemoveRplmn(void);


/******************************************************************************
 * INTERNAL MSG API
******************************************************************************/
/*
 * PLMN API
 * When CEMM desicde to find a suitable PLMN to camp on, call this internal Msg;
 * then CE PLMN module will trigger PLMN search procedure
 * srcId = CE_NAS_CEMM
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = CemmPlmnSelectReq
*/
void CePlmnProcSelectReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * PLMN module select a suitable PLMN, and let CEMM to do camp/resigter
 * srcId = CE_NAS_PLMN
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = CemmPlmnSelectCnf
*/
void CemmProcPlmnSelectCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * PLMN API
 * When CEMM trigger to do "DEACT" procedure
 * srcId = CE_NAS_CEMM
 * argvUint8 = the cause of "DEACT", CemmPlmnDeactCause
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL;
*/
void CePlmnProcDeactReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * srcId = CE_NAS_PLMN
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmProcPlmnDeactCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * PLMN sub-module need to do something (such as maunal PLMN search) when CERRC in connected state, this internal
 * msg trigger CEMM to release CERRC connection
 * srcId = CE_NAS_PLMN
 * argvUint8 = CemmPlmnIdleReqCause
 * argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmProcIdleStateReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * PLMN API
 * After AS go idle, which trigger by "CemmIdleStateReq";
 * srcId = CE_NAS_CEMM
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CePlmnProcIdleStateCnfMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * PLMN just cannel the "CemmIdleStateReq" (such as: if manaul PLMN search finished), then CEMM could resume other module,
 *  and let CERRC to establish the connection if needed
 * srcId = CE_NAS_PLMN
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmProcCancelIdleStateReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * PLMN API
 * When AS layer release the connection, notify PLMN module, maybe PLMN has some pending PLMN search procedure
 * srcId = CE_NAS_CEMM
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CePlmnProcIdleStateIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);


/*
 * CEMM API
 * After PLMN select a high priority PLMN
 * srcId = CE_NAS_PLMN
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = CemmPlmnSelectInd
*/
void CemmProcPlmnSelectInd(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * After PLMN searching done
 * srcId = CE_NAS_PLMN
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmProcNoPlmnSelectIndMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * PLMN State Change Ind Rpt and notify CEMM
 * srcId = CE_NAS_PLMN
 * argvUint8/argvUint16/argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmProcPlmnSelectStateChangeInd(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);


/*
 * PLMN API
*/
void CePlmnGetPlmnSelectState(UINT8 *pPlmnSelectState, BOOL *pOosTimerPresent, UINT16  *pOosTimerS);

/*
 * PLMN API
 * Called by CEMM, to GET PLMN OOS count
*/
void CePlmnGetPlmnOosCount(UINT16 *numOos);

/*
 * PLMN API
 * Called by CEMM, to Clear PLMN OOS count
*/
void CePlmnClearPlmnOosCount(void);

#endif

