/****************************************************************************
 *
 * Copy right:   2018-, Copyrigths of Qualcomm Ltd.
 * File name:    pmu_qcx212.h
 * Description:  Sequencer HW header file
 * History:      03/16/2018    Originated by jinxin huang
 *
 ****************************************************************************/
#ifndef _PMU_QCX212_H
#define _PMU_QCX212_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdbool.h>
#include "qcx212_internal.h"
#include "qcx212.h"
#include "slpman_qcx212.h"

#ifndef RAM_BOOT_RET16K
#define RAM_BOOT_RET16K
#define RAM_BOOT_RET16K_CODE      __attribute__((__section__(".ramBootCode")))
#define RAM_BOOT_RET16K_RWDATA      __attribute__((__section__(".ramBootRWData")))
#define RAM_BOOT_RET16K_ZIDATA      __attribute__((__section__(".ramBootZIData")))
#define UNINIT_RET16K_ZIDATA      __attribute__((__section__(".UnInitData16K")))
#endif


#if defined(__CC_ARM)
//#pragma anon_unions
#endif

//////////////////////////////////////////////////////////////////////
// Macros
//////////////////////////////////////////////////////////////////////

// for each latch wait ceil(204.8*1000/32.768) = 6278 cycles
#define PMU_SC_RD_DELAY                 6278

//////////////////////////////////////////////////////////////////////
// HW typedef
//////////////////////////////////////////////////////////////////////


// pmu always on registers
typedef struct {
	// add note later
    __IO uint32_t rtc_bg_cfg;

    __IO uint32_t ldo_rtc_cfg;

    __IO uint32_t ldo_ret_cfg;

    __IO uint32_t Osc32k_bias_ctrl;

    //0x10
    __IO uint32_t ldo_sim_config;

    __IO uint32_t ldo_sim_en;

    __IO uint32_t ldo_fem_en;

    __IO uint32_t dcdc_lv_vout_pd;

    //0x20
    __IO uint32_t ldo_aux_adc_ena;

    __IO uint32_t ldo_aio_ena;

    __IO uint32_t iq_test_inv_ena;

    __IO uint32_t dcdc_vpa_ena;

    //0x30
    __IO uint32_t ldo_io_33_18_sel_H;

    __IO uint32_t pup_pmu_ctrl;

    __IO uint32_t pup_pmu_delay_cycle_cfg;

    //0x3c
    __IO uint32_t remap;

    //0x40
    __IO uint32_t pmu_en;

    __IO uint32_t pmu_sleep_mode;

    __IO uint32_t wic_cfg;

    __IO uint32_t sc_clk_div;

    //0x50
    __IO uint32_t sc_clk_ena;

    __IO uint32_t sc;

    __IO uint32_t wakeup_req_time;

    __IO uint32_t bc_ld;

    //0x60
    __IO uint32_t bc_ld_val;

    __IO uint32_t wakeup_pin_val_ind;

    __IO uint32_t ldo_aonio_ena;

    __IO uint32_t ldo_aonio_cfg;

    //0x70
    __IO uint32_t ate_ldo_ret_cfg;

    __IO uint32_t ate_ext_26M_in_dis;

    __IO uint32_t areg0;

    __IO uint32_t areg1;

    __IO uint32_t areg2;

    __IO uint32_t areg3;

    __IO uint32_t areg4;

    __IO uint32_t areg5;

    __IO uint32_t areg6;

    __IO uint32_t areg7;

} T_PMU_AON_REGS;



// pmu mode definition
typedef enum {
    SLEEP1 = 0, // 0,sleep1
    SLEEP2 = 1, // 1,sleep2
    HIBERNATE1 = 2, // 2,hibernate1
    HIBERNATE2 = 3, // 3,hibernate2
}PmuMode;


//////////////////////////////////////////////////////////////////////
// HW entity
//////////////////////////////////////////////////////////////////////

// HW entity CPU access base address
#define PMU_AON_REGS_BASE_ADDR            (PMU_BASE_ADDR+0x000)

// HW entitiy
#define HW_PmuAon                         ((T_PMU_AON_REGS *)   PMU_AON_REGS_BASE_ADDR)


//////////////////////////////////////////////////////////////////////
// Enums
//////////////////////////////////////////////////////////////////////
typedef enum
{
	PMU_CLK_SRC_16M=0,
	PMU_CLK_SRC_102M,
	PMU_CLK_SRC_MAX
} PmuClkCalSel;

typedef enum
{
    CAL_OFF=0,
    CAL_ON
} PmuCalCfg;


typedef enum
{
    PMU_OFF=0,
    PMU_ON
} PmuEnCtrl;

typedef enum
{
    USIM_1_8V=0,
    USIM_3_0V
} PmuUsimLdo;



static __FORCEINLINE void PMU_ENA(void)
{
    // enable pmu/ enable wakeup pin posedge/ enable wakeup pin negedge
    HW_PmuAon->pmu_en = 0x7;
}

static __FORCEINLINE uint8_t GET_USIM_POWER_STATE(void)
{
	return (uint8_t)(HW_PmuAon->ldo_sim_en & 0x01);
}


static __FORCEINLINE void PMU_USIM_POWER_UP(void)
{
    HW_PmuAon->ldo_sim_en = 0x1;
}

static __FORCEINLINE void PMU_USIM_POWER_DOWN(void)
{
    HW_PmuAon->ldo_sim_en = 0x0;
}

static __FORCEINLINE void PMU_FEM_POWER_UP(void)
{
    HW_PmuAon->ldo_fem_en = 0x1;
}

static __FORCEINLINE void PMU_FEM_POWER_DOWN(void)
{
    HW_PmuAon->ldo_fem_en = 0x0;
}

static __FORCEINLINE void PMU_WAKEUP_TIME_DISABLE(void)
{
    HW_PmuAon->wakeup_req_time = 0;
}


//////////////////////////////////////////////////////////////////////
// Structure
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Parameters
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Function declaration
//////////////////////////////////////////////////////////////////////
void PmuModeSel(PmuMode modeCfg);
UINT32 PmuSlowCntRead(void);
void PmuWakeUpTimeCfg(UINT32 wakeupReqTime);
uint8_t PmuGetCurrentRatio(void);
UINT32 PmuWakeUpTimeRead(void);
void PmuWakeUpTimeBcLdDisable(void);
void PmuBcRecvCfg(UINT32 bcValL, UINT32 bcValH, UINT32 bcLdTime);
void PmuScDivConfig(UINT32 scDivRatio);
void PmuBcRecvCfgRead(UINT32 *bcValSpn, UINT32 *bcValHfnSfnSbn, UINT32 *scOfBcLdTime);
void PmuEnable(bool PmuEn);
void PmuSetUsimLdo(PmuUsimLdo level, uint8_t trimValue);
BootFlag_e PmuGetBootFlagFromAon(void);
void PmuSetBootFlagInAon(BootFlag_e flag);
void PmuSetImageType(uint8_t type);
uint8_t PmuGetImageType(void);
UINT8 PmuGetPsCounterFromAon(void);
void PmuSetPsCounterIntoAon(UINT8 psCnt);
void PmuSetXtalVoltage(void);
void PmuSetConCounterIntoAon(UINT32 continous_counter);
UINT32 PmuGetConCounterFromAon(void);
UINT8 PmuSwCntRemainGet(void);
void PmuSwCntRemainSet(UINT8 remain_value);
void PmuSetScIntoAon(UINT32 sc_value);
UINT32 PmuGetScFromAon(void);
void PmuSetWhichTimerIntoAon(uint8_t b_timer_wakeup);
uint8_t PmuGetWhichTimerFromAon(void);
void PmuFlashPllConfig(UINT8 pllByPassFlag, UINT8 flashDisable);
bool PmuIsFlashPowerOff(void);
void PmuSetRemapIntoAon(uint8_t value);
void PmuScLatch(void);
void PmuCalConfig(PmuCalCfg calFlag);
void PmuCaliStart(PmuClkCalSel clkScr);
void PmuCaliStop(void);
void PmuFcScValueRead(UINT32 *fsValue, UINT32 *scValue);
void PmuSetWakeupPadReg(uint8_t group_num, bool posedge_en, bool negedge_en);
void PmuAonIOSettings(bool iolatch_en, bool ldo_en);
void PmuAonIOCfgGet(bool *p_iolatch_en, bool *p_ldo_en);
bool PmuAonIsLatched(void);
UINT32 PmuSlowCntReadMcuMode(void);
uint8_t PmuWakeupPinValue(void);
void PmuIOLevelSel(uint8_t sel);
void PmuIOVoltTrim(uint8_t cfg);
void PmuSet2048HzIntoAon(uint64_t cnt);
uint64_t PmuGet2048HzFromAon(void);
void PmuSet2048HzResIntoAon(uint16_t res_store);
uint16_t PmuGet2048HzResFromAon(void);
bool PmuGetAONDeepSlpTimer(uint32_t *p_target_cnt);
void PmuSetAONDeepSlpTimer(bool enable, uint32_t target_cnt);
void PmuAPPSetHibFlag1(bool flag);
bool PmuAPPGetHibFlag1(void);
void PmuGetPmuRawFlashRegionFlag(uint8_t *platPsRG, uint8_t *phyRG);
void PmuSetPmuRawFlashRegionFlag(uint8_t platPsRG, uint8_t phyRG);



#ifdef __cplusplus
}
#endif

#endif

