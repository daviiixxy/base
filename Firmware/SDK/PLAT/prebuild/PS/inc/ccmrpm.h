#ifdef FEAT_RPM

#ifndef __CCMRPM_H__
#define __CCMRPM_H__

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2020- Copyrights of Qualcomm Inc.
 File name:      - ccmrpm.h
 Description:    - CCM (CIoT Connection Management) RPM (Radio Policy Manager) sub-module
 History:        - 11/06/2020, Originated by souv
 ******************************************************************************
******************************************************************************/
#include "ccmcomm.h"
#include "cmidev.h"
#include "ccmsig.h"
#include "ccmdev.h"

#define RPM_VERSION 0x02

#define NO_OF_RPM_FX_COUNTERS         5

#define NO_OF_CPDP_COUNTERS           4

#define INVALID_TIMER 0xffffffffL

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

typedef struct CcmRpmParamTag
{
    /* RPM functionality enabled or disabled at power up */
    BOOL                 rpmFlag;
    /* Max no of SW resets per Hour allowed by RPM following “permanent” EMM reject */
    UINT8                N1;
    /* Average time before RPM resets modem following permanent EMM reject */
    UINT8                T1;
    /* Average time before RPM resets modem following permanent EMM reject if T1 = 0xFF */
    UINT8                T1_ext;
    
    /* Fx[0]: Max number of PDN Connectivity Requests per Hour allowed by RPM following a PDP Activation Ignore Scenario */     
    /* Fx[1]: Max number of PDN Connectivity Requests per Hour allowed by RPM following a “Permanent” PDP Activation Reject */
    /* Fx[2]: Max number of PDN Connectivity Requests per Hour allowed by RPM following a “Temporary” PDP Activation Reject */
    /* Fx[3]: Max number of PDN Connectivity Activation/ Deactivation Requests per Hour allowed by RPM */
    UINT8                Fx[NO_OF_RPM_FX_COUNTERS]; 
}
CcmRpmParam;

typedef struct CcmRpmOmCounterTag
{
    BOOL                 isValid;                        // If RPM params are present on SIM card, If not all RPM OM functionality shall be disabled.
    UINT8                Cbr1;                           //Counter related to N1
    UINT8                Cr1;                            //Counter related to T1
    UINT8                Cpdpx[NO_OF_RPM_FX_COUNTERS];   //Counter related to Fx
}
CcmRpmOmCounter;


typedef struct CcmRpmOmCountersLeakRateTag
{
    UINT8                LR1;      //Leak rate(in Hours) for C-BR-1 - Not used currently
    UINT8                LR2;      //Leak rate(in Hours) for C-R-1
    UINT8                LR3;      //Leak rate(in Hours) for CPDP-1 to C-PDP-4
    UINT8                reserved;          //reserved for future use
}
CcmRpmOmCountersLeakRate;

typedef struct CcmRpmTimer_Tag
{
    UINT32              rpmStartTime;
}
CcmRpmTimer;

typedef enum CcmRpmCounterEnum_Tag
{
    RPM_COUNTER_F1 = 0,
    RPM_COUNTER_F2 = 1,  
    RPM_COUNTER_F3 = 2,
    RPM_COUNTER_F4 = 3,
    RPM_COUNTER_F4_att = 4
}CcmRpmCounterEnum;

typedef struct CcmRpmHibTimer_Tag
{
    UINT32              timerPeriod;
    OsaHibTimerId       hibTimerId;
}
CcmRpmHibTimer;

typedef struct CcmRpmTimerInformationTag
{
    CcmRpmHibTimer      t1;          //if T1 equal 0xFF, T1_ext will be used as timer period
    CcmRpmHibTimer      LR2Timer;
    CcmRpmHibTimer      LR3Timer;
}
CcmRpmTimerInformation;

typedef struct CcmRpmContext_Tag
{
    UINT8                     rpmVersion;
    BOOL                     isDtSimCard;
    BOOL                     rpmParamsPresentOnSimCard;
    BOOL                     rpmTriggeredAirplaneToggle;
    CcmRpmParam               rpmParam;
    CcmRpmOmCounter           omCounter;
    CcmRpmOmCountersLeakRate  omCountersLeakRate;
    CcmRpmTimer               rpmTimer[NO_OF_RPM_FX_COUNTERS];
    CcmRpmTimer               rpmN1Timer;
    CcmRpmTimer               rpmTimerFxTimeElapsed[NO_OF_RPM_FX_COUNTERS];
    CcmRpmTimer               n1TimerTimeElapased;
    CcmRpmTimerInformation    rpmTimerInformation;
}CcmRpmContext;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

void CcmRpmInit(BOOL   bWakeup);
BOOL CcmRpmIsRpmEnabled(void);
void CcmRpmHibTimerExpiry(UINT16 hibTimerId);
void CcmRpmCheckEsmRejCause(UINT16 esmCause);
void CcmRpmCheckEmmRejCause(UINT16 emmCause);
void CcmRpmIncrementF4(CcmRpmCounterEnum rpmCnt, BOOL updateNvm);
BOOL CcmRpmAllowActEpsBearerReq(BOOL updateCounter);
void CcmRpmResetRpmCounters(void);
void CcmRpmResetRpmCountersExceptF4(BOOL updateNvm);
void CcmRpmDeepSlpEnterCallBack(void);

void CcmRpmProcSimRpmParamInd(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmRpmSimNokIndMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmRpmSimChangeIndMsg(BOOL isSimChanged);

void CcmRegProcSimRefreshIndMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);
void CcmRpmOperatorConfigMsg(UINT8 srcId, UINT8 argv1, UINT16 argv2, UINT32 argv3, void* argv);

void CcmRpmGetRpmParamInfoReq(void);

void CcmRpmGetRpmVersionReq(void);
void CcmRpmSetRpmParamInfoReq(CmiDevSetRpmParamReq *pSetRpmParamReq);

BOOL CcmRpmGetRpmEnabled(void);

BOOL CcmRpmIsDtSimCard(void);

BOOL CcmRpmCheckN1Validation(BOOL powerup, UINT8 cfun);

BOOL CcmRpmIsRpmTriggeredAirplaneToggle(void);

void CcmRpmTurnRpmAirplaneToggleOff(void );

BOOL CcmRpmCheckFxValidation(UINT8 counterId, BOOL powerUp);

void CcmRpmResetN1(BOOL updateNvm);


#endif

#endif

