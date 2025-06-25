/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ecpm_qcx212_external.h
 * Description:  QCX212 platform power management header file
 * History:      05/28/2018    Originated by bchang
 *
 ****************************************************************************/

#ifndef _EC_PM_EXT_H
#define _EC_PM_EXT_H

#ifdef __cplusplus
 extern "C" {
#endif
#include <stdbool.h>
//#include "timetrans_qcx212.h"
#include "mem_map.h"

#define PMU_AON_MEMORY_SIZE             (1024*7)    //7KB

extern UINT8    flashMem[PMU_AON_MEMORY_SIZE];

#define PS_PMUTIME_TEST             (1)

#define PMU_ENABLE_MAGIC 0x504D5545		//"PMUE"
#define PMU_DISABLE_MAGIC 0x504D5544	//"PMUD"

#define PMU_AON_MID_WARE_MEM_SIZE       (256)
#define PMU_AON_HIB_TIMER_MEM_SIZE      (256)

#define PLAT_AON_HIB_TIMER_MEM_ADDR     (flashMem)
#define PLAT_AON_MID_WARE_MEM_ADDR      (flashMem+PMU_AON_HIB_TIMER_MEM_SIZE)

/*
 * list which module should vote before system enter hib state
 */
typedef enum PmuVoteDeepSlpModule_enum
{
    PMU_DEEPSLP_PHY_MOD,
    PMU_DEEPSLP_PS_CCM_MOD,
    PMU_DEEPSLP_PS_CEMM_MOD,
    PMU_DEEPSLP_PS_CERRC_MOD,
    PMU_DEEPSLP_PS_CEUP_MOD,
    PMU_DEEPSLP_PS_UICC_MOD,
    PMU_DEEPSLP_PS_LWIP_MOD,
    PMU_DEEPSLP_CMS_MOD,
    PMU_DEEPSLP_PLAT_MOD,       // indicate plat need update flash
    //...
    PMU_DEEPSLP_NUM_OF_MOD
}PmuVoteDeepSlpModule;

typedef enum
{
    LP_STATE_ACTIVE=0,
    LP_STATE_IDLE,
    LP_STATE_SLEEP1,
    LP_STATE_SLEEP2,

    LP_STATE_HIBERNATE,
    NUM_LP_MODE
} LpState;


//list which module should vote before system enter sleep state
typedef enum PmuVoteSleepModule_enum
{
    PMU_SLEEP_PHY_MOD,
    PMU_SLEEP_UICC_MOD,
    PMU_SLEEP_L2C_MOD,
    PMU_SLEEP_AT_UART_MOD,
    PMU_SLEEP_NUM_OF_MOD
}PmuVoteSleepModule;


typedef enum _pmuen_config_id
{
    PLAT_DISABLE_CONFIG_ACTION = 0,     /**< pmu disable item */
    PLAT_ENABLE_CONFIG_ACTION,  /**< pmu enable item */
    PLAT_ENABLE_ITEM_TOTAL_NUMBER       /**< total number of items */
} PmuEnCfgId;


//internal pmu vote for platform use
typedef enum PmuVotePlatInternal_enum
{
    PMU_SLEEP_ATCMD_MOD,        // vote to sleep when receive some at command
    PMU_SLEEP_NUM_OF_Other_MOD
}PmuVotePlatInternal;




typedef void(* pmuPreDeepSlpCb_t)(void *pdata, LpState state);
typedef void(* pmuPostDeepSlpCb_t)(void *pdata, LpState state);



void pmuVoteToSleep1State(PmuVoteSleepModule pmuMod, BOOL bAllow);
void pmuVoteToSleep2State(PmuVoteDeepSlpModule pmuMod, BOOL bAllow);
void  pmuVoteToHIBState(PmuVoteDeepSlpModule pmuMod, BOOL bAllow);
BOOL pmuBVoteToSleep1State(PmuVoteSleepModule pmuMod);
BOOL pmuBVoteToSleep2State(PmuVoteDeepSlpModule pmuMod);
BOOL pmuBVoteToHibState(PmuVoteDeepSlpModule pmuMod);
void pmuSetDeepestSleepMode(LpState state);
BOOL pmuBWakeupFromHib(void);
BOOL pmuBWakeupFromSleep1(void);
BOOL pmuBWakeupFromSleep2(void);
BOOL pmuBPsVoteToDeepSlpState(void);
uint32_t pmuBuildWaitSlpCfg(uint32_t value);
uint32_t pmuGetWaitSlpCfg(uint32_t value);
void pmuPlatIntVoteToSleep1State(PmuVotePlatInternal pmuMod, BOOL bAllow);
void pmuAonCtxChanged(PmuVoteDeepSlpModule pmuMod);
void pmuPreDeepSlpCbRegister(PmuVoteDeepSlpModule module, pmuPreDeepSlpCb_t cb, void *pdata);
void pmuPostDeepSlpCbRegister(PmuVoteDeepSlpModule module, pmuPostDeepSlpCb_t cb, void *pdata);
void PmuRawFlashEraseCntCheck(uint32_t *flash_platps_rg0, uint32_t *flash_platps_rg1, uint32_t *flash_platps_rg2, uint32_t *flash_platps_rg3,
    uint32_t *flash_phy_rg0, uint32_t *flash_phy_rg1, uint32_t *flash_phy_rg2, uint32_t *flash_phy_rg3);




#ifdef __cplusplus
}
#endif

#endif

