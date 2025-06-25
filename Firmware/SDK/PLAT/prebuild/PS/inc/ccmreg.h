#ifndef __CCMREG_H__
#define __CCMREG_H__

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - ccmreg.h
 Description:    - CCM (CIoT Connection Management) REG (registration) sub-module
 History:        - 05/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/
#include "ccmcomm.h"
#include "cemmsig.h"
#include "ccmsig.h"
#include "cmimm.h"
#include "cmidev.h"

#define CCM_REG_MANUAL_PLMN_SEARCH_TIME_IN_SEC 300 //5*60s
#define PS_SILENT_RESET_MAX_COUNT   0
#define CCM_REG_GTP_PLMN_SEARCH_TIME_IN_SEC 2000


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/
typedef enum CcmRegLowLayerRegStateEnum_Tag
{
    REG_CEMM_UNDER_DEACT = 0,   /* deactivated/power off state, cfun0/4 state */
    REG_CEMM_UNDER_DEREG = 1,   /* detached state, COPS=2, and for NB: CGATT=0 */
    REG_CEMM_UNDER_EPS_REG = 2,
    //REG_CEMM_UNDER_NON_EPS_REG = 2,     // invalid for NB
    //REG_CEMM_UNDER_COMBINED_REG = 3,    // invalid for NB
    //REG_CEMM_UNDER_DEREG_BY_USER = 4,
}CcmRegLowLayerRegStateEnum;


/******************************************************************************
 * CcmRegDynCtx
 * CCM REG dynamic context, which allocated in dynamic memory
 * 1> REG procedure
 * 2> DEREG procedure
 * 3> Power wake up procedure
 * 4> Manual PLMN search
 * 5> Band change procedure
 * 6> autoApn, autoBand procedure, after power on, and SIM ready
 * etc
******************************************************************************/
typedef enum CcmRegProcEnum_tag
{
    CCM_NONE_REG_PROC = 0,
    CCM_REG_PROC,
    CCM_DEREG_PROC,

    CCM_REG_POWER_WAKE_UP_PROC,  //wake up from hibernate/sleep2 state
    CCM_REG_POWER_AUTO_CFG_PROC,
    CCM_REG_CHANGE_BAND_PROC
}CcmRegProcEnum;

typedef struct CcmRegRegProcParm_Tag
{
    NwMode                  nwMode;         // NwMode,  by now NB only
    UeService               serviceType;    // EPS only
    CemmPlmnSelectTypeEnum  plmnSelectType; // CemmPlmnSelectTypeEnum
    Plmn                    manualPlmn;
}CcmRegRegProcParm; //8 bytes

typedef struct CcmRegDeregProcParm_Tag
{
    CemmDetachType  detachType;
    UeService       detachSrvType;
	BOOL            is_ipv6_rs_failed;
}CcmRegDeregProcParm;   //4 bytes

typedef struct CcmRegRegProc_Tag
{
    CcmRegProcEnum      proc;
    CcmSubModuleIdEnum  srcModule; /*which sub-mod trigger it*/
    union {
        CcmRegRegProcParm   regParm;
        CcmRegDeregProcParm deregParm;
    }procParm;
}CcmRegRegProc; //12 bytes

typedef struct  CcmRegChangeBandProc_Tag
{
    CcmRegProcEnum  proc;   //set to "CCM_REG_CHANGE_BAND_PROC", just means "change band" procedure is ongoing;
    BOOL            needReReg;  //whether need to re-register. (re-attach)
}CcmRegChangeBandProc;

typedef struct CcmRegDynCtx_Tag
{
    CcmRegRegProc   ongoingReg;     // ongoing REG procedure
    CcmRegRegProc   pendingReg;

    CcmRegProcEnum  onPowerProc;    //power save/power wake up procedure
    CcmRegChangeBandProc    changeBand; //REG/DEREG, SRCID = CCM_REG

    GosTimerId      manualPlmnProtectTimerId;
	GosTimerId      gtpPlmnProtectTimerId;
}CcmRegDynCtx;

/******************************************************************************
 * CcmRegStaticCtx
 * CCM REG STATIC context, which allocated in static memory, just as a global variable
******************************************************************************/
typedef struct CcmRegStaticCtx_Tag
{
    CemmRegStatusEnum           regStatus;
    CcmCemmUeSrvStatusEnum      ueSrvStatus;

    NwMode                      nwMode;         // NwMode
    UeService                   serviceType;    // EPS only
    CemmPlmnSelectTypeEnum      plmnSelectType; // auto or manual

    UINT8                       plmnSelectState;//CemmPlmnSelectState
    BOOL                        cellInfoValid;  // whether tac/phyCellId/band info valid
    BOOL                        plmnValid;      // whether the PLMN info valid
    CemmEmmCauseEnum            emmCause;       //CemmEmmCauseEnum

    UINT16                      tac;
    UINT16                      phyCellId;
    UINT32                      cellId;

    UINT8                       band;
    //BOOL                        regOngoing;     //if not registered, whether UE is trying to register to a PLMN later, maybe after OOS timer expiried
    AdditionalUpdateResult      addUpdateInfo;  //AdditionalUpdateResult
    CemmCiotOptTypeEnum         nwSptCiotOpt;   //CemmCiotOptTypeEnum

    CemmNwPsmInfo               nwPsmInfo;
    CemmEdrxInfo                edrxInfo;
    Plmn                        plmn;
    CcmCemmConnStatusEnum       connStatus;
	BOOL                        dereg_rs_failure;
}CcmRegStaticCtx;



/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
/*
 * internal MSG
*/
void CcmRegProcPoweroffReqMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmRegProcPoweronReqMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmRegProcSimReadyIndMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmRegProcSimNokIndMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmRegProcPsAttachReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmRegProcPsDetachReqMsg(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
void CcmRegRsFailRegReq(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);


void CcmRegSetCiotBandReq(CmiDevSetCiotBandReq *pCmiBandReq);
void CcmRegSetCiotFreqReq(CmiDevSetCiotFreqReq *pCmiFreqReq);
void CcmRegGetCurCiotBandFreqReq(UINT8 getBandFreqType);
void CcmRegGetCmiMmCregCnfInfo(CmiMmCregModeEnum reportMode, CmiMmGetCregCnf *pGetCregCnf);
void CcmRegGetCmiMmCregIndInfo(CmiCregChangedTypeEnum changedType, CmiMmCregInd *pCregInd);
void CcmRegGetCmiPsCeregCnfInfo(CmiPsCeregModeEnum reportMode, CmiPsGetCeregCnf *pGetCeregCnf);
void CcmRegGetCmiPsCeregIndInfo(CmiCeregChangedTypeEnum ceregChangedType, CmiPsCeregInd *pCeregInd);
void CcmRegAutoPlmnSelectReq(void);
void CcmRegManualPlmnSelectReq(CmiMmManualPlmnSelectReq *pManualSelectReq);
void CcmRegDeregReq(CcmSubModuleIdEnum subMod);
void CcmRegRsFailDeregReq(CcmSubModuleIdEnum subMod);
CcmCommRcEnum CcmRegSetCmiMmCurOperInfoCnfInfo(CmiPlmnFormatEnum plmnFormat, CmiMmGetCurOperInfoCnf *pCurOperInfoCnf);
CcmCommRcEnum CcmRegManualPlmnSearchReq(CemmManualSearchMode mode, UINT32 guardTimerS, UINT8 reqMaxNum);

void CcmRegInit(BOOL bWakeUp);
void CcmRegProcessSignal(SignalBuf *sig);
void CcmRegProcTimerExpiry(GosTimerExpiry *pTimerExpiry);

void CcmRegGetCmiPsCSCONCnfInfo(CmiPsGetConnStatusCnf *pCmiGetConnStatusCnf);
void CcmRegGetCmiPsCSCONIndInfo(CmiPsConnStatusInd *pCsconInd);

void CcmRegOosPlmnSelectReq(void);
CcmCommRcEnum CcmRegGtpPlmnSearchReq(CmiMmGtpPlmnSearchReq *pGtpPlmnSearchReq);
void CcmRegAbortGtpPlmnSearchReq(CmiMmAbortGtpPlmnSearchReq *pAbortGtpPlmnSearchReq);



//void CcmRegSendPsAttachCnfMsg(void);
//void CcmRegSendPsDetachCnfMsg(void);


/******************************************************************************
 * CCMREG functions, which called by CCM/Other sub-modules
******************************************************************************/
/*
 * CCMREG API
 * CCMREG API for CCMPS when AT+CGATT? read the current Packet Domain service state
*/
BOOL CcmRegCurEpsBeAttached(void);

/*
 * CCMREG API
 *  whether current CEMM/NAS under registration, if return TRUE, don't need to trigger EMM to do attach procedure
*/
BOOL CcmRegCemmBeUnderReg(void);

/*
 * CCM REG API
 *  Get current location info
*/
void CcmRegGetLocationInfo(Plmn* pPlmn, UINT16 *pTac, UINT32 *pCellId);

void CcmRegGetCellInfo(Plmn* pPlmn, UINT32 *pCellId, UINT16 *pPhyCellId);

/*
 * CCM REG API
 *  Get current Conn Status
*/
CcmCemmConnStatusEnum CcmRegGetConnStatus(void);

/*
*/
void CcmRegCemmSetPlmnRegParmCnf(CcmCemmRcCodeEnum rcCode);

void CcmRegGetCmiPsCeerCnfInfo(CmiPsGetCeerCnf *pCeerCnf);

#endif

