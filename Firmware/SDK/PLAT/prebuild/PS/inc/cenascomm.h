#ifndef __CE_NAS_COMM_H__
#define __CE_NAS_COMM_H__
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - cenascomm.h
 Description:    - CE NAS layer common include header file
 History:        - 05/12/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/
#include "pssigid.h"
#include "pssys.h"
#include "nascommon.h"
/******************************************************************************
 * ceNasMsgQue
 * CE NAS internal MSG queue, pass messages between sub-modules
******************************************************************************/
extern MsgQueue ceNasMsgQue;
#define pCeNasMsgQue (&ceNasMsgQue)

/******************************************************************************
 *****************************************************************************
 * ENUM/MARCO
 *****************************************************************************
******************************************************************************/

typedef enum CeNasSubModuleIdEnum_tag
{
    CE_NAS_COMM = 0,
    CE_NAS_CEMM = 1,
    CE_NAS_CESM = 2,
    CE_NAS_SMS  = 3,
    CE_NAS_PLMN = 4,
    CE_NAS_SS   = 5,

    CE_NAS_MAX_SUB_MOD
}CeNasSubModuleIdEnum;


typedef enum CeNasTimerIdEnum_Tag
{
    CE_NAS_INVALID_TIMER = 0,

    /*
     * CEMM timer ID
    */
    CE_EMM_BASE_TIMER = 0,
    /* 64 timers reserved */
    CE_EMM_T3410_ID,
    CE_EMM_T3416_ID,
    CE_EMM_T3417_ID,
    CE_EMM_T3418_ID,
    CE_EMM_T3420_ID = 5,
    CE_EMM_T3421_ID,
    CE_EMM_T3423_ID,
    CE_EMM_T3430_ID,
    CE_EMM_T3440_ID,
    CE_EMM_T3449_ID = 10,
    CE_EMM_POWER_OFF_TIMER_ID,
    CE_EMM_SIG_RETRANSMIT_TIMER_ID,

    CE_EMM_END_TIMER = 0x3F,

    /*
     * CESM timer ID
    */
    CE_ESM_BASE_TIMER = 0x40,
    //64 timers
    CE_ESM_T3396_ID,
    CE_ESM_T3480_ID,
    CE_ESM_T3481_ID,
    CE_ESM_T3482_ID,
    CE_ESM_T3492_ID,
    CE_ESM_ESR_TIMER_ID,
    CE_ESM_NO_HIBERNATE_TIMER_ID,
    CE_ESM_CPSR_ABORT_DELAY_TIMER_ID,
    CE_ESM_THROTTLING_TIMER_ID,
    CE_ESM_END_TIMER = 0x7F,

    /*
     * CE PLMN timer ID
    */
    CE_PLMN_BASE_TIMER = 0x80,
    //32 timers
    CE_PLMN_END_TIMER = 0xAF,


    /*
     * CE SMS timer ID
    */
    CE_SMS_ENTITY_BASE_TIMER = 0x100,
    // 128 timers
    CE_SMS_TC1M_ETY0_ID = 0x110,
    CE_SMS_TC1M_ETY1_ID,
    CE_SMS_TC1M_ETY2_ID,
    CE_SMS_TC1M_ETY3_ID,
    CE_SMS_TC1M_ETY4_ID,
    CE_SMS_TC1M_ETY5_ID,
    CE_SMS_TC1M_ETY6_ID,
    CE_SMS_TC1M_ETY7_ID,
    CE_SMS_TC1M_ETY8_ID,
    CE_SMS_TC1M_ETY9_ID,
    CE_SMS_TC1M_ETY10_ID,
    CE_SMS_TC1M_ETY11_ID,
    CE_SMS_TC1M_ETY12_ID,
    CE_SMS_TC1M_ETY13_ID,

    CE_SMS_TR1M_ETY0_ID = 0x120,
    CE_SMS_TR1M_ETY1_ID,
    CE_SMS_TR1M_ETY2_ID,
    CE_SMS_TR1M_ETY3_ID,
    CE_SMS_TR1M_ETY4_ID,
    CE_SMS_TR1M_ETY5_ID,
    CE_SMS_TR1M_ETY6_ID,
    CE_SMS_TR1M_ETY7_ID,
    CE_SMS_TR1M_ETY8_ID,
    CE_SMS_TR1M_ETY9_ID,
    CE_SMS_TR1M_ETY10_ID,
    CE_SMS_TR1M_ETY11_ID,
    CE_SMS_TR1M_ETY12_ID,
    CE_SMS_TR1M_ETY13_ID,

    CE_SMS_TR2M_ETY0_ID = 0x130,
    CE_SMS_TR2M_ETY1_ID,
    CE_SMS_TR2M_ETY2_ID,
    CE_SMS_TR2M_ETY3_ID,
    CE_SMS_TR2M_ETY4_ID,
    CE_SMS_TR2M_ETY5_ID,
    CE_SMS_TR2M_ETY6_ID,
    CE_SMS_TR2M_ETY7_ID,
    CE_SMS_TR2M_ETY8_ID,
    CE_SMS_TR2M_ETY9_ID,
    CE_SMS_TR2M_ETY10_ID,
    CE_SMS_TR2M_ETY11_ID,
    CE_SMS_TR2M_ETY12_ID,
    CE_SMS_TR2M_ETY13_ID,

    CE_SMS_TRAM_ETY0_ID = 0x140,
    CE_SMS_TRAM_ETY1_ID,
    CE_SMS_TRAM_ETY2_ID,
    CE_SMS_TRAM_ETY3_ID,
    CE_SMS_TRAM_ETY4_ID,
    CE_SMS_TRAM_ETY5_ID,
    CE_SMS_TRAM_ETY6_ID,
    CE_SMS_TRAM_ETY7_ID,
    CE_SMS_TRAM_ETY8_ID,
    CE_SMS_TRAM_ETY9_ID,
    CE_SMS_TRAM_ETY10_ID,
    CE_SMS_TRAM_ETY11_ID,
    CE_SMS_TRAM_ETY12_ID,
    CE_SMS_TRAM_ETY13_ID,

    CE_SMS_RETRAM_ETY0_ID = 0x150,
    CE_SMS_RETRAM_ETY1_ID,
    CE_SMS_RETRAM_ETY2_ID,
    CE_SMS_RETRAM_ETY3_ID,
    CE_SMS_RETRAM_ETY4_ID,
    CE_SMS_RETRAM_ETY5_ID,
    CE_SMS_RETRAM_ETY6_ID,
    CE_SMS_RETRAM_ETY7_ID,
    CE_SMS_RETRAM_ETY8_ID,
    CE_SMS_RETRAM_ETY9_ID,
    CE_SMS_RETRAM_ETY10_ID,
    CE_SMS_RETRAM_ETY11_ID,
    CE_SMS_RETRAM_ETY12_ID,
    CE_SMS_RETRAM_ETY13_ID,

    CE_SMS_DELAY_RELEASE_BASE_ID = 0x160,
    CE_SMS_DELAY_RELEASE_ETY7_ID = 0x167,
    CE_SMS_DELAY_RELEASE_ETY8_ID,
    CE_SMS_DELAY_RELEASE_ETY9_ID,
    CE_SMS_DELAY_RELEASE_ETY10_ID,
    CE_SMS_DELAY_RELEASE_ETY11_ID,
    CE_SMS_DELAY_RELEASE_ETY12_ID,
    CE_SMS_DELAY_RELEASE_ETY13_ID,

    CE_SMS_ENTITY_END_TIMER =  0x180,

    /*
     * CESS timer ID
    */
    CE_SS_BASE_TIMER = 0x200,
    /* 16 timers reserved */
    CE_SS_LCSL_TIMER_ID,
    CE_SS_ESTABLISH_TIMER_ID,
    CE_SS_END_TIMER = 0x210,


    CE_NAS_MAX_TIMER = 0x0800
}CeNasTimerIdEnum;

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/
typedef struct CenasHibTimer_Tag
{
    UINT32              timerPeriod;
    OsaHibTimerId       hibTimerId;
}
CenasHibTimer;

typedef struct CenasTimer_Tag
{
    CeNasTimerIdEnum    timerIdOfTask;
    UINT32              timerPeriod;
    osTimerId_t         timerId;
}
CenasTimer;

typedef struct PsApnEntityTag
{
    BOOL             t3396Running;
    BOOL             ApnBarred;
    UINT16           reserved;
    CenasTimer       t3396;
    AccessPointName  apn;
}PsApnEntity;



/******************************************************************************
 ************************** Tiny RAM ******************************************
 * CeNasTinyContext
 * Note:
 *  Most important NAS context, which stored in the AON (always on line) memory
 *  (maybe a limited a flash) need to control the size;
 ******************************************************************************
******************************************************************************/
#define CE_NAS_TINY_CTX_PLMN_NUM            8
#define CE_NAS_TINY_CTX_TAI_NUM             4
#define CE_NAS_TINY_CTX_GPRS_FPLMN_NUM      3

typedef struct CeNasTinyContext_Tag
{
    /*
     * CE EMM
     */
    UINT32                  withoutPdnSupported : 1;
    UINT32                  cpCiotSupported : 1;
    UINT32                  upCiotSupported : 1;
    UINT32                  ePcoSupported : 1;
    UINT32                  hcCpCiotSupported : 1;
    UINT32                  currentService : 2;         /* UeService */
    UINT32                  epsAttached : 1;            /* EPS attached or not */
    UINT32                  nwEdrxValid : 1;            /* Network has assigned eDRX parameter */
    UINT32                  eKsi : 3;                   /* NasKsi */
    UINT32                  integrityAlgorithm : 2;     /* IntegrityAlgorithm */
    UINT32                  encryptionAlgorithm : 2;    /* CipheringAlgorithm */
    UINT32                  nwT3412ExtValid : 1;        /* Network has assigned extended T3412 value */
    UINT32                  nwT3324Valid : 1;           /* Networkhas assigned T3324 value */
    UINT32                  overrideLowPriority : 1;    /* Override NAS signalling low priority */
    UINT32                  suspendSignalling : 1;      /* NAS signalling is suspend */
    UINT32                  periodicTauNeed : 1;        /* Need periodic tau */
    UINT32                  tauForSmsOnly : 1;          /* Need tau for Sms */
    UINT32                  simPresent : 1;             /* Sim is present or not */
    UINT32                  tauRequired : 1;            /* tau required */
    UINT32                  pendingTau : 1;             /* Pending TAU */
    UINT32                  simInvalidForEps : 1;       /* Sim invalid for eps service */
    UINT32                  disableHibInPctMode :1;     /* Not allow UE enter Hibernate under Protocol Conformance Test mode */
    UINT32                  suspendedEsm : 1;           /* Has already suspended ESM */
    UINT32                  suspendedSms : 1;           /* Has already suspended SMS */
    UINT32                  suspendedSs : 1;            /* Has already suspended SS */
    UINT32                  lastSignallingPriority : 1; /* Last signalling priority in Attach/Tau/Control Ser Req */
    UINT32                  simInvalidForSms : 1;       /* Sim invalid for Sms service */

    UINT32                  nwSuppAttWithoutPdn : 1;    /* Sysinfo indicates support ATTACH without PDN or not */
    UINT32                  bT3346ForException : 1;     /* T3346 was started when connection was established with cause set to  "MO exception data" */
    UINT32                  attachRejReceived : 1;      /* Whether received ATTACH REJECT with T3402 on new PLMN */
    UINT32                  regFailedOnNewPlmn : 1;     /* ATTACH or TAU failed on a new PLMN */
    UINT32                  reserved : 28;

    UINT8                   keyAsme[KASME_SIZE];        /* Kasme */
    UINT8                   oldGuti[MAX_GUTI_SIZE];     /* GUTI */
    UINT8                   ulCountOverflow[2];         /* 16-bit UL NAS count overflow */
    UINT8                   dlCountOverflow[2];         /* 16-bit DL NAS count overflow */
    UINT8                   taiListNum;                 /* The number of TAI lists saved in tiny context */
    UINT8                   taiNum;                     /* The number of TAIs saved in tiny context */
    TaiWithType             taiList[CE_NAS_TINY_CTX_TAI_NUM];
    UINT16                  accessClass;                /* SIM Access class */
    UINT8                   nasSignallingPriority;      /* NasSignallingPriority */
    UINT8                   regStatus;                  /* CemmRegStatusEnum */
    UINT8                   rrActStatus;                /* ActStatus */
    UINT8                   epsUpdateStatus;            /* EpsUpdateStatus */
    UINT8                   emmState;                   /* EmmSubState */
    UINT8                   deactiveReason;             /* Deactive Reason */
    UINT8                   attachCounter;              /* Attach attempt counter */
    UINT8                   tauCouonter;                /* Tau attempt counter */
    UINT8                   tauForSmsCount;             /* tau for sms count */
    Tai                     lastVisitedRegisteredTai;   /* Registered TAI */
    Tai                     sysInfoTai;                 /* Sys Info TAI */
    UINT32                  cellIdentity;               /* cellIdentity */
    UINT32                  carrierFreq;                /* Carrier Freq */
    GprsTimer2              nwT3324Value;               /* Network configured T3324 value */
    GprsTimer3              nwT3412ExtValue;            /* Network configured Extended T3412 value */
    UINT32                  t3412ExtendedRemainValueS;  /* T3412 Extended Remain Value in Seconds */
    UINT32                  t3412PeriodS;               /* T3412 timeout period */
    UINT32                  t3402Period;
    ExtendedDrxParameters   nwEdrxInfo;                 /* Network configured eDRX information */
    TinyForbiddenTaiInfo    forbiddenTaiInfo;           /* fobidden Tai Info */
    AdditionalUpdateResult  additionalUpdateResult;     /* Additional update result */
	Plmn                    t3346BlockPlmn;
	UINT8                   N_HF_counter;
	UINT8                   CurrentOperator;        /* Current Operator  */
	UINT32                  idleDrxCycle;               /* IDLE DRX cycle in milliseconds */

    /*
     * CE PLMN, as CE SMS only one BOOL value, just insert here for memory save
     */
    UINT16                  hpPlmnSearchPeriod;         /*current high priority PLMN search period, in minutes */
    //UINT8                   minPeriodicSearchTimer;
    UINT16                  initHpPlmnSearchPeriod;     /*inited when SIM ready, in minutes */

    UINT32                  cePlmnHbTimerId : 1;
    UINT32                  cePlmnHbTimerState : 1;
    UINT32                  cePlmnHbOosTimerTimes : 2;
    UINT32                  cePlmnHbHplmnTimerTimes : 2;
    UINT32                  rplmnType : 3;              /* PlmnType, indicated which "PlmnType" of RPLMN*/
	#if MCC_FEATURE_ENABLED
	BOOL                    mccPresentSodaqDb;
	#endif
    /*CE SMS*/
    UINT32                  ceSmsReadyToReceive : 1;

    UINT32                  gprsFPlmnNum : 2;           /* Number of GPRS FPLMN stored in "plmnList"*/
    UINT32                  blockPlmnPresent : 1;       /* whether BLOCK PLMN stored in "plmnList"*/
    UINT32                  blockPlmnReason : 2;        /* CemmPlmnBlockReason, indicated the blocked PLMN reason, valid when "blockPlmnPresent" == TRUE */
    UINT32                  fastFirstHigherPriorityPlmnSearch : 1;
    //UINT32                  reserved : 1;
    UINT32                  bPlmnSimReady : 1;          /* whether SIM insert/ready, used in CEPLMN sub-module */
    UINT32                  blockTac : 16;              /* valid when "blockPlmnPresent" == TRUE */

    UINT32                  plmnSelectState : 2;
    UINT32                  oosTimerPresent : 1;
    UINT32                  oosTimerS : 16;                  //OOS timer value in second
    UINT32                  plmnSearchSeqNum : 3;            //Plmn Search Seq Num
    UINT32                  epsFilePresentType : 2;
    UINT32                  bFirstPoweron : 1;
    UINT32                  reservedPlmn2 : 6;
    UINT32                  hplmnTimerExpiredSC;        /* Home Plmn Timer expired second count */

    Plmn                    selectedPlmn;           /* CePlmn Module selected Plmn */

    /*
     * 23.122 - 3.1
     * This list is deleted when the MS is switched off or when the SIM is removed;
     * The maximum number of possible entries in this list is implementation dependant, but must be at least one entry.
     * The HPLMN (if the EHPLMN list is not present or is empty) or an EHPLMN (if the EHPLMN list is present) shall not be
     *  stored on the list of "forbidden PLMNs for GPRS service"
    */
    /*
     * plmn list info stored in tiny context:
     * 1> EHPLMN read from SIM card, just store here from index 0;
     * 2> if only "gprsFPlmnPresent", then index for "gprsFPlmn" = CE_NAS_TINY_CTX_PLMN_NUM - 1
     * 3> if only "blockPlmnPresent", then index for "blockedPlmn" = CE_NAS_TINY_CTX_PLMN_NUM - 1
     * 4> if both "gprsFPlmnPresent" and "blockPlmnPresent", then
     *      index for "gprsFPlmn" = CE_NAS_TINY_CTX_PLMN_NUM - 2;
     *      index for "blockedPlmn" = CE_NAS_TINY_CTX_PLMN_NUM - 1;
    */
    Plmn                    plmnList[CE_NAS_TINY_CTX_PLMN_NUM];
    Plmn                    gprsFplmnList[CE_NAS_TINY_CTX_GPRS_FPLMN_NUM];
	Plmn                    reqPlmn;


    /*
     * CE ESM
     */
    UINT8                   attBearerPresetIsReady :1;// whether ATTBEARER is set, used for AUTOAPN feature. in fact, this flag should set to 0 when CFUN0 - TBD
    UINT8                   reservedEsm :7;
    EsmBearerTinyCtx        esmBearerTinyCtx;
	EsmBearerTinyCtx        esmBearerCtx;
	UINT32                  CurrentPlmnType;
	UINT8                   t3402CounterForLgu;
	UINT8                   t3402CounterForCause17Lgu;
}CeNasTinyContext;


extern CeNasTinyContext *pCeNasTinyCtx;

/******************************************************************************
 * tiny RAM memory used by PLMN
 * Two timer maybe still exist during Hibernate state:
 * 1> Period High PLMN search timer (T)
 * 2> OOS wake up to PLMN search timer
 * 3> These two timer can't co-exist
******************************************************************************/
#define CE_PLMN_HB_OOS_PLMN_SEARCH_TIMER    0
#define CE_PLMN_HB_PERIOD_HIGH_PLMN_SEARCH_TIMER    1
#define CE_PLMN_HB_TIMER_NOT_RUNNING        0
#define CE_PLMN_HB_TIMER_RUNNING            1
#define CE_PLMN_HB_TIMER_TIMERS_MAX         3
//#define cemmPlmnHbTimerId       pCeNasTinyCtx->cePlmnHbTimerId
//#define cemmPlmnHbTimerState    pCeNasTinyCtx->cePlmnHbTimerState
//#define cemmPlmnHbTimerTimes    pCeNasTinyCtx->cePlmnHbTimerTimes

/******************************************************************************
 ************************** Hibernate state ***********************************
 * Whether NAS task allow the PMU enter the hibernate state (only AON memory)
 * Each sub-module has a bit to indicate whether allow it:
 *  0 - allow, 1 - not allow
 ******************************************************************************
******************************************************************************/
extern UINT32 ceNasHibernateCtrlBitmap;

#define CENAS_SUB_MOD_ALLOW_HIBERNATE(subMod)     \
do {                                            \
    if ((subMod)<32 && (subMod)>=0)             \
        (ceNasHibernateCtrlBitmap &= (~(1<<(subMod))));   \
    else                                                \
        GosCheck(FALSE, subMod, ceNasHibernateCtrlBitmap, 0); \
}while(FALSE)


#define CENAS_SUB_MOD_NOT_ALLOW_HIBERNATE(subMod) \
	do {                                            \
		if ((subMod)<32 && (subMod)>=0) 	\
		{				\
			if(ceNasHibernateCtrlBitmap==0) \
			{				\
				pmuVoteToHIBState(PMU_DEEPSLP_PS_CEMM_MOD, FALSE);\
			}				\
			(ceNasHibernateCtrlBitmap |= (1<<(subMod)));	\
		}				\
		else                                                \
		GosCheck(FALSE, subMod, ceNasHibernateCtrlBitmap, 0); \
	}while(FALSE)


/******************************************************************************
 ************************* Tiny Context changed *******************************
 * ceNasTinyCtxChangedBitmap
 * This variable used to decide whether the tiny context need to save to flash
 *  before enter hibernate state
 * if "ceNasTinyCtxChangedBitmap" is set to zero, just means all tiny contexts
 * are not changed, don't need to copy to flash
 ******************************************************************************
******************************************************************************/
extern UINT32  ceNasTinyCtxChangedBitmap;

#define CENAS_SUB_MOD_TINY_CONTEXT_CHANGED(subMod)     \
do {                                            \
    if ((subMod)<32 && (subMod)>=0)             \
        (ceNasTinyCtxChangedBitmap |= (1<<(subMod)));  \
    else                                                \
        GosCheck(FALSE, subMod, ceNasTinyCtxChangedBitmap, 0); \
}while(FALSE)



/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

#define CeNasPrintf(subMod, level, fmt, ...) \
        GosPsPrintf(PS_NAS, subMod, level, fmt, ##__VA_ARGS__)

extern void CeNasStartTimer(CenasTimer    *timerEntity);
extern BOOL CeNasTimerIsRunning(osTimerId_t    timer_id);
extern void CeNasStopTimer(CenasTimer    *timerEntity);
extern void CeNasTimerExpiry(UINT16  timerEnum);
extern BOOL CeNasHibTimerIsRunning(OsaHibTimerId    hibTimerId);
extern void CeNasStopHibTimer(CenasHibTimer    *hibTimerEntity);
extern void CeNasHibTimerExpiry(UINT16  hibTimerId);
extern void CeNasSaveNvmFiles(void);

#endif

