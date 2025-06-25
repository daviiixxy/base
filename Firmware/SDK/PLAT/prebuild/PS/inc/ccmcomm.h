#ifndef __CCM_COMM_H__
#define __CCM_COMM_H__
/******************************************************************************
Copyright:      - 2017- Copyrights of Qualcomm Ltd.
File name:      - ccmcomm.h
Description:    - CCM (CIoT Connection Management) module common header file
History:        - 05/09/2017, Originated by jcweng
******************************************************************************/
#include "pssys.h"
#include "ccmcomm.h"
#include "cmidev.h"
#include "cemmsig.h"
#include "cerrcsig.h"

/******************************************************************************
 ******************************************************************************
 * STRUCT definition
 ******************************************************************************
******************************************************************************/

typedef enum CcmSubModuleIdEnum_Tag
{
    CCM_INVALID_SUB_MOD = 0,

    CCM_CAC_BASE = 1,
    CCM_CAC_DEV = 2,
    CCM_CAC_MM = 3,
    CCM_CAC_PS = 4,
    CCM_CAC_SIM = 5,
    CCM_CAC_SMS = 6,

    CCM_BASE = 16,
    CCM_REG = 17,
    CCM_DEV = 18,
    CCM_PS  = 19,
    CCM_SMS = 20,
    CCM_SIM = 21,
#ifdef FEAT_RPM
    CCM_RPM = 22,
#endif

    CCM_SUB_MODULE_MAX = 31
}CcmSubModuleIdEnum;


typedef enum CcmCommRcEnum_Tag
{
    CCM_RC_SUCC = 0,

    CCM_RC_BUSY = 1,
    CCM_RC_SIM_NOK = 2,
    CCM_RC_SIM_NOT_INSERT,
    CCM_RC_NOT_POWER_ON,
    CCM_RC_FAIL,
    CCM_RC_NOT_SUPPORT,
    CCM_RC_NO_MEMORY,
    CCM_INVALID_PLMN,
    CCM_PLMN_DUPLICATE_USED,
    CCM_PLMN_NOT_FOUND,
    CCM_PLMN_TABLE_EMPTY,
    CCM_PLMN_TABLE_FULL,


    CCM_RC_MAX = 0xFF
}CcmCommRcEnum;

typedef enum CcmTimerIdEnum_Tag
{
    CCM_INVALID_TIMER = 0,

    CCM_CAC_BASE_TIMER = 0,
    // 14 timers reserved
    CCM_CAC_END_TIMER = 0x0F,

    CCM_CAC_DEV_BASE_TIMER = 0x11,
    //14 timers
    CCM_CAC_DEV_END_TIMER = 0x1F,

    CCM_CAC_MM_BASE_TIMER = 0x21,
    //14 timers
    CCM_CAC_MM_END_TIMER = 0x2F,

    CCM_CAC_PS_BASE_TIMER = 0x31,
    //14 timers
    CCM_CAC_PS_END_TIMER = 0x3F,

    CCM_CAC_SIM_BASE_TIMER = 0x41,
    //14 timers
    CCM_CAC_SIM_END_TIMER = 0x4F,

    CCM_CAC_SMS_BASE_TIMER = 0x51,
    //14 timers
    CCM_CAC_SMS_END_TIMER = 0x5F,

    CCM_BASE_TIMER = 0x81,
    //14 timers
    CCM_END_TIMER = 0x8F,

    CCM_REG_BASE_TIMER = 0x91,
    CCM_REG_MANUAL_PLMN_SEARCH_PROTECT_TIMER,
    CCM_REG_GTP_PLMN_SEARCH_PROTECT_TIMER,

    CCM_REG_END_TIMER = 0x9F,

    CCM_DEV_BASE_TIMER = 0xA1,
    CCM_DEV_STATIS_REPORT_PERIOD_TIMER,
    CCM_DEV_ECBCINFO_GUARD_TIMER,

    CCM_DEV_END_TIMER = 0xAF,

    CCM_PS_BASE_TIMER = 0xB1,
    CCM_PS_CGATT_GUARD_TIMER,

    CCM_PS_END_TIMER = 0xBF,

    CCM_SMS_BASE_TIMER = 0xC1,
    //
    CCM_SMS_END_TIMER = 0xCF,

    CCM_SIM_BASE_TIMER = 0xD1,
    //
    CCM_SIM_END_TIMER = 0xDF,

    CCM_MAX_TIMER = 0xFF
}CcmTimerIdEnum;

/*
 * CCM POWR STATE Request,
 * CFUN0/CFUN1/CFUN4;
 * POWER SAVE (hibernate state)/POWER WAKE UP
*/
typedef enum CcmPowerStateReq_Enum
{
    CCM_CFUN0_POWER_OFF_REQ,
    CCM_CFUN4_POWER_OFF_REQ,
    //CCM_HIBERNATE_POWER_SAVE_REQ,
    //CCM_SLEEP2_POWER_SAVE_REQ,

    CCM_CFUN1_POWER_ON_REQ,
    CCM_CFUN4_POWER_ON_SIM_REQ,
    CCM_POWER_WAKE_UP_REQ   //wake up from hibernate state
}CcmPowerStateReq;

/******************************************************************************
 ************************** Tiny RAM ******************************************
 * CcmTinyContext
 * Note:
 *  Most important CCM context, which stored in the AON (always on line) memory
 *  need to control the size, in draft: each sub-module 4 bytes, and totally
 *  don't exceed 64 bytes
 ******************************************************************************
******************************************************************************/
typedef struct CcmTinyContext_Tag
{
    /******************************************************************************
     * UINT8   devTinyCtx
     * 4 bits reserved | 3 bits dev state | 1 bits rpmEnabled
     *****************************************************************************/
    UINT32      devState : 3;
    UINT32      rpmEnabled : 1;
    UINT32      devRsvd : 4;

    /******************************************************************************
     * UINT8   regTinyCtx
     * From LSB:
     * 3 bits REG STATE // CcmRegLowLayerRegStateEnum
     * 1 bit  // whether COPS DEREG REQ
     * 3 bits  // ccm ps state Enum
     *****************************************************************************/
    UINT32      lowLayerRegState:3;     /* CcmRegLowLayerRegStateEnum */
    UINT32      bCopsDereg: 1;
    UINT32      inPsmMode : 1;          /* TRUE means UE is under PSM mode,FALSE means UE is not under PSM mode */
    UINT32      silentResetCounter : 3;
    UINT32      lastEmmRejCause : 16;
    UINT8       cregStatus;             /* <stat> in AT+CREG */
    UINT8       ceregStatus;            /* <stat> in AT+CEREG */
    /* 6 bytes above */

    /******************************************************************************
     * UINT8   psTinyCtx
     * From LSB:
     * 3 bits   //one bearer state
     * 8 bit    //cid
     * 1 bit    //whether PS CGATT0 (detached) state
     *****************************************************************************/
    UINT32      brState: 3;
    UINT32      cid : 8;
    UINT32      brState_1: 3;
    UINT32      psRsvd0_1: 5;
    UINT32      cid_1 : 8;
	UINT8      currOpeartor: 5;
    UINT32      psRsvd : 16;
    /* 4 bytes above */

    /******************************************************************************
     *  simTinyCtx
     *****************************************************************************/
    UINT8                   uiccState:3;  //CcmSimStateEnum
    UINT8                   smspService:1;
    UINT8                   smsPPService:1;
    UINT8                   moSmsCtrlService:1;
    UINT8                   universalPinSupportedByCard:1;
    UINT8                   verifyUniversalPin:1;

    UINT8                   pin1KeyReference; //UiccKeyRefValue
    UINT8                   pin2KeyReference; //UiccKeyRefValue
    UINT8                   simReserved;
    /* 4 bytes above */
    UiccPinStatus           pin1Status;
    UiccPinStatus           pin2Status;
    UiccPinStatus           universalPinStatus;
    UiccPinStatus           unblockPin1Status;
    UiccPinStatus           unblockPin2Status;
    UiccPinStatus           unblockUniversalPinStatus;
    /* 24 bytes above */

    /******************************************************************************
     *  smsTinyCtx
     *****************************************************************************/
    UINT32                  msgReference : 8;
    UINT32                  ccmsmsState : 3;  //CcmsmState
    UINT32                  smssAvailable : 1;
    UINT32                  smsRsvd : 20;
	UINT32                  t3402_duration;
	UINT16      			lastEsmRejCause;
    /* 4 bytes above */

    /*
     * ECBCINFO need to save into tiny context in some case, cost too many...
    */
    CmiDevSCellBasicInfo    sCellInfo;  //24 bytes
    CmiDevNCellBasicInfo    nCellList[CMI_DEV_NCELL_INFO_CELL_NUM]; //96 bytes
    /* 120 bytes above */

}CcmTinyContext;

extern CcmTinyContext *pCcmTinyCtx;

/******************************************************************************
 * UINT8   devTinyCtx
 * 5 bits reserved | 3 bits dev state
 *****************************************************************************/
#define CCM_GET_DEV_STATE()         (pCcmTinyCtx->devState)
#define CCM_SET_DEV_STATE(newState) ((pCcmTinyCtx->devState) = ((newState)&0x07))


/******************************************************************************
 * UINT8   regTinyCtx
 * From LSB:
 * 3 bits REG STATE // CcmRegLowLayerRegStateEnum
 * 1 bit  // whether COPS DEREG REQ
 *****************************************************************************/
#define REG_GET_CEMM_UNDER_REG_STATE()          (pCcmTinyCtx->lowLayerRegState)
#define REG_SET_CEMM_UNDER_REG_STATE(newState)  ((pCcmTinyCtx->lowLayerRegState) = ((newState)&0x07))
#define REG_IS_COPS_DEREG()     (pCcmTinyCtx->bCopsDereg)
#define REG_SET_COPS_DEREG()    (pCcmTinyCtx->bCopsDereg = 1)
#define REG_CLEAR_COPS_DEREG()  (pCcmTinyCtx->bCopsDereg = 0)

/******************************************************************************
 * UINT8   psTinyCtx
 * From LSB:
 * 3 bits   //one bearer state
 * 4 bit    //cid
 * 1 bit    //whether PS CGATT0 (detached) state
 *****************************************************************************/
#define CCM_PS_TINY_GET_CID()               (pCcmTinyCtx->cid)
#define CCM_PS_TINY_SET_CID(newCid)         ((pCcmTinyCtx->cid) = ((newCid)&0xff))
#define CCM_PS_TINY_GET_BEARER_STATE()      (pCcmTinyCtx->brState)
#define CCM_PS_TINY_SET_BEARER_STATE(newState)  ((pCcmTinyCtx->brState) = ((newState)&0x07))

#define CCM_PS_TINY_GET_CID_1()               (pCcmTinyCtx->cid_1)
#define CCM_PS_TINY_SET_CID_1(newCid)         ((pCcmTinyCtx->cid_1) = ((newCid)&0xff))
#define CCM_PS_TINY_GET_BEARER_STATE_1()      (pCcmTinyCtx->brState_1)
#define CCM_PS_TINY_SET_BEARER_STATE_1(newState)  ((pCcmTinyCtx->brState_1) = ((newState)&0x07))


#if 0
#define CCM_PS_TINY_IS_CGATT0()             (pCcmTinyCtx->bCgatt0)
#define CCM_PS_TINY_SET_CGATT0()            (pCcmTinyCtx->bCgatt0 = 1)
#define CCM_PS_TINY_CLEAR_CGATT0()          (pCcmTinyCtx->bCgatt0 = 0)
#endif

/******************************************************************************
 ************************** Hibernate state ***********************************
 * Whether CCM task allow the PMU enter the hibernate state (only AON RAM)
 * Each sub-module has a bit to indicate whether allow it:
 *  0 - allow, 1 - not allow
 ******************************************************************************
******************************************************************************/
extern UINT32 ccmHibernateCtrlBitmap;
#define CCM_SUB_MOD_ALLOW_HIBERNATE(subMod)     \
do {                                            \
    if ((subMod)<32 && (subMod)>=0)             \
        (ccmHibernateCtrlBitmap &= (~(1<<(subMod))));   \
    else                                                \
        GosCheck(FALSE, subMod, ccmHibernateCtrlBitmap, 0); \
}while(FALSE)


#define CCM_SUB_MOD_NOT_ALLOW_HIBERNATE(subMod) \
do {                                            \
    if ((subMod)<32 && (subMod)>=0)             \
        (ccmHibernateCtrlBitmap |= (1<<(subMod)));      \
    else                                                \
        GosCheck(FALSE, subMod, ccmHibernateCtrlBitmap, 0); \
}while(FALSE)


/******************************************************************************
 ************************* Tiny Context changed *******************************
 * ccmTinyCtxChangedBitmap
 * This variable used to decide whether the tiny context need to save to flash
 *  before enter hibernate state
 * if "ccmTinyCtxChangedBitmap" is set to zero, just means all tiny contexts
 * are not changed, don't need to copy to flash
 ******************************************************************************
******************************************************************************/
extern UINT32  ccmTinyCtxChangedBitmap;

#define CCM_SUB_MOD_TINY_CONTEXT_CHANGED(subMod)     \
do {                                            \
    if ((subMod)<32 && (subMod)>=0)             \
        (ccmTinyCtxChangedBitmap |= (1<<(subMod)));  \
    else                                                \
        GosCheck(FALSE, subMod, ccmTinyCtxChangedBitmap, 0); \
}while(FALSE)



/******************************************************************************
 * ccmMsgQue
 * CCM internal MSG queue, pass messages between sub-modules
******************************************************************************/
extern MsgQueue ccmMsgQue;
#define pCcmMsgQue (&ccmMsgQue)


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
#define CcmPrintf(subMod, level, fmt, ...) \
        GosPsPrintf(PS_CCM, subMod, level, fmt, ##__VA_ARGS__)


/*
 * set extended config
*/
void CcmSetCcmExtCfgParam(CmiDevSetExtCfgReq *pSetEcfgReq);

/*
 * get extened config, AT^ECCFG?
*/
void CcmGetCcmExtCfgParam(CmiDevGetExtCfgCnf *pExtCfgCnf);

/*
 * send "SIG_CEMM_CCM_SET_PARM_REQ" signal to CEMM task
*/
void CcmSendCemmCcmSetParmReqSig(CcmParmType parmType, UINT8 len, void *pParm);

/*
 * send "SIG_CEMM_CCM_GET_PARM_REQ" signal to CEMM task
*/
void CcmSendCemmCcmGetParmReqSig(CcmParmType parmType);

/*
 * send "SIG_CERRC_CCM_SET_PARAM_REQ" signal to CERRC task
*/
void CcmSendCerrcCcmSetParamReqSig(CerrcCcmSetParamReq *pCerrcSetParamReq);

/*
 * send "SIG_CERRC_CCM_GET_PARAM_REQ" signal to CERRC task, to get CFG parameters
*/
void CcmSendCerrcCcmGetParamReqSig(CerrcCcmParamType    getParaType);

/*
 * returns UINT8 currOperator
*/
UINT8 CcmDevGetCurrentOperator(void);

/*
 * returns UINT8 currOperator
*/
UINT8 CcmDevGetOperator(BOOL bWakeUp);


/*
*/
void CcmMainSetCurrOperator(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);


void CcmSaveNvmFiles(void);

/*
 * CcmCemmRcCodeEnum -> CcmCommRcEnum
*/
CcmCommRcEnum CeNasRcToCcmRc(UINT32 ccmRc);

void CcmSendCemmCcmGetEmmStatusReqSig(void);

void CcmSendGetLapiInfoReq(void);

void CcmSendCemmCcmSetLapiInfoReqSig(CmiDevSetLapiReq *setLapiInfo);

void CcmSendCemmCcmSetRoamingDataInfoReqSig(CmiDevSetRoamingDataReq *setRoamingDataReq);

void CcmSendGetRoamingDataInfoReq(void);







#endif

