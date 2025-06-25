/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    PhyExtApi.h
 * Description:  PHY function called by PS/PLAT
 * History:      02/29/2020    Originated by Zhiliang Fu
 *
 ****************************************************************************/
#include "CommonTypedef.h"

#ifndef PHY_DEBUG_ON
#define PHY_DEBUG_ON
#endif

// Called by pmuTrySleep1/qc_main/
extern void PhyPowerOnInit(UINT8 wakeupType);

// Called by ec_main
extern void PHY_PMU_WAKEUP_TYPE_SET(UINT8 wakeupType);

// Called by pmuTrySleep1
extern UINT8 PHY_PMU_WAKEUP_TYPE_GET(void);

// Called by ec_main
extern void PhyEndWorkOnPadInt(void);

// Called by PsInitialiseTasks
extern void PhySendTaskIdleSchd(void);

// Called by pmuEnterTickless
extern void DCXOFTBufStore2Flash(void);

// Called by pmuSwitchInIdle
extern BOOL PhyEarfcnCollideCheck(void);

// Called by XIC_IntHandler
extern BOOL PHY_GET_UNILOG_ONOFF(void);
extern UINT8 PhyLogLevelGet(void);
extern BOOL PhyLogAllowCheck(UINT8 uniLogLevel);
extern void PhyDebugPrint(UINT8 moduleID, UINT8 subID, UINT32 *pSwLogData, UINT32 swLogLen, UINT8 uniLogLevel, UINT8 ramLogSwitch);


// Called by PmuSlowCntRead
extern UINT32 SQ_ScLtch_Read(void);

// Called by PmuBcRecvCfg
extern void SQ_BcLdSrc_Set(UINT32 bcLdSrc);

// Called by PLAT to get version of PHYLIB
extern UINT8* PHY_LIBVER_GET(void);

