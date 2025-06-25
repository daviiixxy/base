#ifndef __CCMDEV_H__
#define __CCMDEV_H__

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - ccmdev.h
 Description:    - CCM (CIoT Connection Management) DEV (device) sub-module
 History:        - 05/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/
#include "ccmcomm.h"
#include "cmidev.h"
#include "ccmsig.h"


/*
 * CCM_DEV_ECBCINFO_GUARD_TIMER timer value
*/
#define CCM_DEV_ECBCINFO_GUARD_TIMER_VALUE_SEC   8

extern BOOL gEventStatisMode;

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

typedef enum CcmDevPowerStateEnum_Tag
{
    CCM_DEV_POWER_OFF_STATE = 0,
    CCM_DEV_AIR_PLANE_STATE = 1,
    CCM_DEV_POWER_ON_STATE = 2
}CcmDevPowerStateEnum;

typedef enum CcmDevProcedureEnum_Tag
{
    CCM_DEV_NONE_PROC = 0,
    CCM_DEV_CFUN0_PROC,
    CCM_DEV_CFUN4_PROC,
    CCM_DEV_CFUN1_PROC,

    //CCM_DEV_SET_BAND_PROC,
    //CCM_DEV_POWER_SAVE_HIB_PROC,
    //CCM_DEV_POWER_SAVE_SLEEP2_PROC,
    CCM_DEV_POWER_WAKE_UP_PROC,

    CCM_DEV_MAX_PROC = 32
}CcmDevProcedureEnum;

typedef enum CcmDevLppCnfStatus_Tag
{
    CONFIRM_LPP_STATUS_OK,
    CONFIRM_LPP_STATUS_ERROR,
    CONFIRM_LPP_STATUS_FATAL
}CcmDevLppCnfStatus;


typedef struct CcmDevGetExtCfgParamProc_Tag
{
    BOOL    emmCnf;     /*whether parameters from EMM confirmed*/
    BOOL    errcCnf;    /*whether parameters from ERRC confirmed*/
    UINT16  rsvd;

    CmiDevGetExtCfgCnf paramCfgCnf;
}CcmDevGetExtCfgParamProc;

/*
 * AT$QCSTATUS?
*/
typedef enum CcmDevUeLayerEnum_Tag
{
    CCM_DEV_CCM_LAYER,
    CCM_DEV_NAS_LAYER,
    CCM_DEV_CERRC_LAYER,
    CCM_DEV_CERRC_LAYER_CELL_INFO,
    CCM_DEV_L2_LAYER,
    CCM_DEV_L2_LAYER_STATIS_INFO,
    CCM_DEV_PHY_LAYER
}CcmDevUeLayerEnum;

typedef struct CcmDevGetExtStatusInfoProc_Tag
{
    BOOL    emmCnf;     /*whether parameters from EMM confirmed*/
    BOOL    errcCnf;    /*whether parameters from ERRC confirmed*/
    BOOL    l2Cnf;      /*whether parameters from L2 confirmed*/
    BOOL    errcCellInfoCnf; /*whether parameters from ERRC CELL INFO confirmed*/
    BOOL    l2StatisCnf;     /*whether parameters from L2 Statis confirmed*/

    CmiDevGetExtStatusCnf   extStatusCnf;
}CcmDevGetExtStatusInfoProc;


typedef struct CcmDevStatisInfoProc_Tag
{
    UINT16      periodTimeS;
    UINT16      reqHandler;//saved CMI REQ handler for CMI_DEV_EXT_STATIS_IND
    GosTimerId  statisReportTimer;

    BOOL        errcCnf;    /*whether parameters from ERRC confirmed*/
    BOOL        l2Cnf;      /*whether parameters from L2 confirmed*/
    UINT16      rsvd0;

    CmiDevExtStatisInd  statisInd;
}CcmDevStatisInfoProc;

/*
 * AT+ECBCINFO procedure
*/
typedef struct CcmDevBcInfoProc_Tag
{
    UINT8           mode;       //CmiDevGetBasicCellInfoMode
    BOOL            needSave;
    UINT16          reqHandler;

    UINT8           rptMode;    //CmiDevGetBasicCellInfoRptMode
    UINT8           rsvd0;
    UINT16          rsvd1;

    GosTimerId      getBCInfoGuardTimer;    /* Get basic cell info (from ERRC) guard timer */
}CcmDevBcInfoProc;


typedef struct CcmDevDynCtx_Tag
{
    /*CFUN proc context*/
    CcmDevProcedureEnum     onFuncProc;         /* CcmDevProcedureEnum, current CFUN ongoing procedure */
    CcmSubModuleIdEnum      funcSrc;            /* type: CcmSubModuleIdEnum, which sub-module trigger the CFUN procedure */
    CcmDevProcedureEnum     pendingFuncProc;    /* CcmDevProcedureEnum, pending CFUN procedure  */
    CcmSubModuleIdEnum      pendingFuncSrc;     /* type: CcmSubModuleIdEnum, which sub-module trigger the pending CFUN procedure */

    //UINT8
    CcmDevProcedureEnum     onPowerProc;            /* CCM_DEV_POWER_WAKE_UP_PROC */

    //GosTimerId              getBCInfoGuardTimer;    /* Get basic cell info (from ERRC) guard timer */
    OsaHibTimerId           powerOnDelayGuardTimer; /* Power on delay guard timer */

    CcmDevGetExtCfgParamProc    *pGetExtCfgProc;    /* AT$QCCFG?, to get extended configed parameters */
    CcmDevGetExtStatusInfoProc  *pGetExtStatusProc; /* AT$QCSTATUS? */
    CcmDevStatisInfoProc        *pStatisInfoProc;

    CcmDevBcInfoProc            *pBcInfoProc;
    CmiDevEmmRrcEventStatisCnf  *pGetEventStatisProc;   /* AT+ECEVENTSTATIS? */
}CcmDevDynCtx;

typedef struct CcmDevLppLocMeasCtx_Tag
{
    /******************************************************************************
    * bWaitingMeasCnf
    * After CCM lpp send SIG_CERRC_LPP_LOC_MEAS_REQ, set the config and clear it
    * when ccm lpp receive SIG_CCM_ERRC_LOC_MEAS_CNF or SIG_CCM_ERRC_STOP_LOC_MEAS_CNF
    *****************************************************************************/
    BOOL            bWaitingMeasCnf;
    /******************************************************************************
    * bWaitingEarlyMeasCnf
    * After CCM lpp send SIG_CERRC_LPP_EARLY_LOC_MEAS_REQ, set the config and clear it
    * when ccm lpp receive SIG_CCM_ERRC_EARLY_LOC_MEAS_CNF or SIG_CCM_ERRC_STOP_LOC_MEAS_CNF
    *****************************************************************************/
    BOOL            bWaitingEarlyMeasCnf;
    /******************************************************************************
    * bOtdoaOngoing
    * After CCM lpp send SIG_CERRC_LPP_LOC_MEAS_REQ, if otdoa is included, set the config and clear it
    * when ccm lpp receive SIG_CCM_ERRC_LOC_MEAS_CNF or SIG_CCM_ERRC_STOP_LOC_MEAS_CNF
    *****************************************************************************/
    BOOL            bOtdoaOngoing;
    /******************************************************************************
    * bEcidOngoing
    * After CCM lpp send SIG_CERRC_LPP_LOC_MEAS_REQ, if ecid is included, set the config and clear it
    * when ccm lpp receive SIG_CCM_ERRC_LOC_MEAS_CNF or SIG_CCM_ERRC_STOP_LOC_MEAS_CNF
    *****************************************************************************/
    BOOL            bEcidOngoing;
}CcmDevLppLocMeasCtx;

typedef enum CcmDevCurrOperatorEnum_Tag
{
    CCM_DEV_OPERATOR_NO_OPERATOR = 0x00,
    CCM_DEV_OPERATOR_ATT = 0x01,
    CCM_DEV_OPERATOR_VZW = 0x02,
    CCM_DEV_OPERATOR_TMOBILE = 0x03,
    CCM_DEV_OPERATOR_TELSTRA = 0x05,
	CCM_DEV_OPERATOR_KT = 0x06,
    CCM_DEV_OPERATOR_LGU = 0x07,
    CCM_DEV_OPERATOR_DT = 0x08,
    CCM_DEV_OPERATOR_TELEFONICA = 0x09,
    CCM_DEV_OPERATOR_TEST = 0x10

}CcmDevCurrOperatorEnum;

/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
void CcmDevProcSimPoweronCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmDevSetCfunReq(CmiFuncValueEnum func, UINT8 subMod);
void CcmDevPowerSaveReq(CmiPowerStateEnum powerSaveState);
void CcmDevPowerWakeUpReq(void);
CmiFuncValueEnum CcmDevGetCfunReq(void);
void CcmDevProcSimPoweroffCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmDevProcRegPoweroffCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmDevProcRegPoweronCnfMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);

void CcmDevInit(BOOL bWakeUp);

CcmDevPowerStateEnum CcmDevGetCurPowerState(void);

void CcmDevCmiLppUlDataReqFunc(UINT16 dataLen, UINT8 *data, BOOL nasRoutingIdPresent, UINT16 nasRoutingId);
void CcmDevCmiLppLocMeasReqFunc(BOOL otdoaMeasPresent, BOOL ecidMeasPresent,
                                          CmiOtdoaMeasReqData          *otdoaReqData,
                                          CmiEcidMeasReqData           *ecidReqData);
void CcmDevCmiLppEarlyLocMeasReqFunc(void);
void CcmDevCmiLppStopLocMeasReqFunc(BOOL withTempResult);
void CacDevCmiDevLppUlDataCnf(UINT16 CmiRcCode);
void CacDevCmiDevLppGetLocInfoInd(CmiDevLppGetLocInfoInd *pGetLocInd);
void CcmDevSetCmolrReq(CmiDevSetCmolrReq *pCmiCmolrReq);
void CcmDevSetCmtlraReq(CmiDevSetCmtlraReq *pCmiCmtlraReq);

BOOL CcmDevSetExtCfgReq(CmiDevSetExtCfgReq *pSetEcfgReq);
BOOL CcmDevGetExtCfgReq(void);
void CcmDevGetEmmCapaParamCnf(CcmCemmRcCodeEnum emmRc, CcmGetEmmCapaParm *pEmmCapaParm);
void CcmDevGetCerrcExtendedConfigParamCnf(CerrcCcmExtCfgParam *pCerrcGetParamCnf);
void CcmDevGetCerrcPowerClassParamCnf(CerrcCcmPowerClassCfg *pCerrcGetParamCnf);
void CcmDevGetCcmStatusInfo(CmiDevCcmStatusInfo *pCcmStatus);
BOOL CcmDevGetExtStatusReq(UINT16 reqHandler, UINT8  getStatusType);
BOOL CcmDevSetExtStatisModeReq(UINT16 reqHandler, UINT16 periodRptS);
CcmCommRcEnum CcmDevGetBasicCellListInfoReq(UINT16 reqHandler, CmiDevGetBasicCellListInfoReq *pCmiBcInfoReq);
void CcmDevSetPsTestReq(BOOL enablePsTest);
void CcmDevGetPsTestReq(void);
void CcmDevGetPsTestCnf(CcmCemmRcCodeEnum emmRc, CcmGetPsTestParm *pPsTest);
void CcmDevSetPowerClassReq(CmiDevSetPowerClassReq  *powerClassReq);
void CcmDevGetPowerClassReq(CerrcCcmParamType    getParaType);

void CcmDevSetCeInfoReq(CmiDevSetCeInfoReq *pSetCeInfoReq);
void CcmDevGetCeInfoReq(void);

#ifdef VZW_ACC_TEST
void CcmDevSetVzwThrottleReq(CmiDevSetVzwThrottleReq *pSetVzwThrottleReq);
void CcmDevGetVzwThrottleReq(void);
#endif

void CcmDevProcPowerOnGuardTimerExpiry(void);
void CcmPsBackoffTimerExpiry(void);

#ifdef FEAT_JIO_PLMN_LOCK
void CcmDevgetPlmnLockList(CacCmiReq *pCmiReq);
void CcmDevPrintPlmnList(void *plmnlist);
void CcmDevsetPlmnLockListReq(CmiDevSetPlmnLockListReq *pSetPlmnLockReq);
void CacDevSetPlmnLockListCnf(CcmCommRcEnum rc);
void CcmDevHandleInvalidSim(BOOL sim_invalid);
#endif


void CcmDevProcTimerExpiry(GosTimerExpiry *pTimerExpiry);
void CcmDevProcessSignal(SignalBuf *sig);
void CcmDevBcInfoManualPlmnSearchCnf(CemmManualPlmnSearchCnf *pManualBcInfoCnf);
void CcmDevGetBcInfoFromTinyContext(CmiDevGetBasicCellListInfoCnf *pBcInfo);
void CcmDevGetNBRelFeatureReq(void);
void CcmDevGetNBRelFeatureCnf(CerrcCcmNbRelFeatureParam *pNbRelFeature);

void CcmDevSetEventStatisModeReq(CmiDevSetEventStatisReq *pEventStatisReq);
void CcmDevEventStatisAllocMemoryReq(void);
void CcmDevSendRRCStatisOperReqSig(CcmEventStatisReqType reqType);
void CcmDevSendEMMStatisOperReqSig(CcmEventStatisReqType reqType);
void CacDevSetEventStatisCnf(CcmCommRcEnum rc);
void CacDevSendEventStatisCnf(CcmCommRcEnum rc, CmiDevEmmRrcEventStatisCnf *pEventStatisCnf);
void CcmDevSetPsSleepCfgReq(CmiDevSetPsSleepCfgReq *pSetPsSlpCfgReq);
void CcmDevGetPsSleepCfgReq(void);
void CcmDevGetPsSleepCfgCnf(CcmCemmRcCodeEnum emmRc, CcmGetPsSleepCfgParm *pPsSlpCfgCnf);
void CcmDevGetDrxReq(void);
void CcmDevGetLapiInfoReq(void);
void CcmDevgetPlmnList(CacCmiReq *pCmiReq);
void CcmDevPrintPlmnList(void *plmnlist);
void CcmDevsetPlmnListReq(CmiDevSetPlmnListReq *pSetPlmnLockReq);
void CcmDevHandleInvalidSim(BOOL sim_invalid);
void CcmDevSetLapiInfoReq(CmiDevSetLapiReq *setLapiInfo);
void CcmDevSetRoamingDataInfoReq(CmiDevSetRoamingDataReq *setRoamingDataReq);
void CcmDevGetRoamingDataInfoReq(void);
void CcmCemmDevGetEmmStatusCnf(CemmCcmGetEmmStatusCnf *pGetEmmStatusCnf);
void CcmCemmDevGetLapiInfoCnf(CemmCcmGetLapicnf *pGetEmmGetLapiCnf);
void CcmCemmDevGetRoamingDataInfoCnf(CemmCcmGetRoamingDataCnf *pGetRoamingDataCnf);
void CcmDevGetEmmStatusCnf();

#endif

