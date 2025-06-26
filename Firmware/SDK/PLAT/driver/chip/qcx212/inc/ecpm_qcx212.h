/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ecpm_qcx212.h
 * Description:  QCX212 platform power management header file
 * History:      05/28/2018    Originated by bchang
 *
 ****************************************************************************/

#ifndef _EC_PM_H
#define _EC_PM_H

#ifdef __cplusplus
 extern "C" {
#endif
#include <stdbool.h>
#include "pmu_qcx212.h"
#include "timetrans_qcx212.h"
#include "mem_map.h"
#include "ecpm_qcx212_external.h"


///////////temp code for cerrcboot.c/////////////////
#define HIB_SECONDS_TO_TICKS(S) (UINT32)(S)
#define HIB_MINUTES_TO_TICKS(M) (HIB_SECONDS_TO_TICKS(M)*60)


/////////////////////////////////////////////////////



#define SMALLIMG_DBG_FLAG   0x44424746  //"DBGF"
#define SMALLIMG_REL_FLAG   0x52454C46  //"RELF"

#define PMU_WAIT2SLP_FLAG   0xff330000
/******************************************************************************
 ******************************************************************************
 * AON RAM memory, always on memory
 ******************************************************************************
******************************************************************************/

// RAM location and size for PS/L1 to store backup data, before enter HIB, platform will
// update the data to flash if necessary

#define PMU_AON_PLAT_MEM_SIZE           (PMU_AON_HIB_TIMER_MEM_SIZE+PMU_AON_MID_WARE_MEM_SIZE)   //0.5KB

#define PMU_AON_PS_DRX_BOOT_MEM_SIZE    64          //PS AON MEM. which should be also need to read in DRX BOOT IMAGE
#define PMU_AON_PS_MEM_SIZE             (2560-PMU_AON_PS_DRX_BOOT_MEM_SIZE)    //2.5KB - 64

#define PMU_AON_PLATPS_MEM_SIZE         (1024*3) //4KB
#define PMU_AON_PHY_CELLINFO_MEM_SIZE   (1024*3)    // include 3K AON MEM + 1K DCXO mem


/*
 * AON MEM
 * +----------------+--------------------------+----------------------+------------------------+-------------------------+--------------------------+
 * |Plat(0.5K)      | PS AON (2.5K-64)         | PS DRX BOOT MEM (64) | PHY AON CELL INFO(3KB) |    EMPTY(1KB-4byte)     | PHY Flash ERASE CNT(4byte) 
 * +----------------+--------------------------+----------------------+------------------------+-------------------------+--------------------------+
 * |<---0.5K------->|<-----------------2.5K ------------------------->|<------------------- 4K ---------------------------------------------------->|
 * |                 \                         ^
 * |                   \                       | DRX BOOT IMAGE should read AON start from here
 * |                     \                                            ^
 * |                       v                                          |
 * +-----------+-----------+                                          |
 * | HIB Timer |  MID WARE |                                          |
 * +-----------+-----------+                                        PLAT PS Flash Erase CNT in flash only @ 0x1000-4
 * |<- 256 B ->|<- 256 B ->|
*/
#define PLAT_AON_MEM_ADDR   (flashMem)


#define PS_AON_MEM_ADDR     (flashMem + PMU_AON_PLAT_MEM_SIZE)
#define PS_DRX_BOOT_AON_MEM_ADDR (flashMem+PMU_AON_PS_MEM_SIZE+PMU_AON_PLAT_MEM_SIZE)
#define PHY_AON_MEM_ADDR    (flashMem+PMU_AON_PS_MEM_SIZE+PMU_AON_PLAT_MEM_SIZE+PMU_AON_PS_DRX_BOOT_MEM_SIZE)       // Start addr for PHY AON CELL INFO
#define PHY_DCXO_MEM_ADDR   (flashMem+PMU_AON_PS_MEM_SIZE+PMU_AON_PLAT_MEM_SIZE+PMU_AON_PS_DRX_BOOT_MEM_SIZE+PMU_AON_PHY_CELLINFO_MEM_SIZE)  // Start addr for PHY AON DCXO


extern uint32_t GET_PMU_RAWFLASH_OFFSET(void);

#define FLASHMEM_BACKUP_XIP_ADDR      			(GET_PMU_RAWFLASH_OFFSET())
#define FLASHMEM_PSDRX_BACKUP_XIP_ADDR  (GET_PMU_RAWFLASH_OFFSET()+PMU_AON_PS_MEM_SIZE+PMU_AON_PLAT_MEM_SIZE)
#define FLASHMEM_PSAON_BACKUP_XIP_ADDR  (GET_PMU_RAWFLASH_OFFSET()+PMU_AON_PLAT_MEM_SIZE)
#define FLASHMEM_PHY_BACKUP_XIP_ADDR    (GET_PMU_RAWFLASH_OFFSET()+0x1000)
#define FLASHMEM_PHY_DCXO_BACKUP_XIP_ADDR    (GET_PMU_RAWFLASH_OFFSET()+0x1000+PMU_AON_PHY_CELLINFO_MEM_SIZE)   // FLASH start addr for DCXO data
#define FLASHMEM_BACKUP_NONXIP_PLATPS_ADDR   (FLASHMEM_BACKUP_XIP_ADDR-FLASH_XIP_ADDR)
#define FLASHMEM_BACKUP_NONXIP_PHY_ADDR   (FLASHMEM_BACKUP_XIP_ADDR-FLASH_XIP_ADDR+0x1000)


#define FLASHMEM_WRITE_CNT_PLATPS_XIP_RG0 (GET_PMU_RAWFLASH_OFFSET()+0x1000-4)
#define FLASHMEM_WRITE_CNT_PHY_XIP_RG0 (GET_PMU_RAWFLASH_OFFSET()+0x2000-4)
#define FLASHMEM_WRITE_CNT_PLATPS_NONXIP_RG0 (FLASHMEM_WRITE_CNT_PLATPS_XIP_RG0-FLASH_XIP_ADDR)
#define FLASHMEM_WRITE_CNT_PHY_NONXIP_RG0 (FLASHMEM_WRITE_CNT_PHY_XIP_RG0-FLASH_XIP_ADDR)



/******************************************************************************
 ******************************************************************************
 * SLEEP2 memory, also on during SLEEP2
 ******************************************************************************
******************************************************************************/

/*
 * SLEEP2 MEM
 *  6KB memory which could remain during SLEEP2 PMU state
 *  Total
 *+-----------------------------+-----------------------------+
 *|   PS SLEEP2 MEM (3KB)       |    PHY SLEEP2 MEM (3KB)     |
 *+-----------------------------+-----------------------------+
 *|<----------- 3K ------------>|<----------- 3K ------------>|
 *
*/
#define PMU_SLEEP2_MEMORY_SIZE  (6144)  //6KB
#define PMU_SLEEP2_PS_MEM_SIZE  (3072)  //3KB
#define PMU_SLEEP2_PHY_MEM_SIZE (3072)  //3KB

extern uint8_t sleep2BackUpMem[PMU_SLEEP2_MEMORY_SIZE];


/*
 * PS/PHY sleep2 memory address
*/
#define PS_SLEEP2_MEM_ADDR      (sleep2BackUpMem)
#define PHY_SLEEP2_MEM_ADDR     (sleep2BackUpMem + PMU_SLEEP2_PS_MEM_SIZE)


#define PMU_SLEEP_MUDOLE_MASK   (0x7)


#define PMU_DEEPSLP_MODULE_MASK     (0xFF)
#define PMU_DEEPSLP_MODULE_MASK_SMALLIMG     (0x1)		//only check phy vote flag



/*	HW  BootRom  Bootloader	  preSync	paging	 fullimage and os start
  |----|-------|------------|---------|--------|------------------------|
							^
							|
  						 BcLoad
*/
#define PMU_HW_STARTUP_TIMER		(4)
#define PMU_HW_DCXO_EXTRA_TIMER		(4)			// when using dcxo we need PMU_HW_STARTUP_TIMER+PMU_HW_DCXO_EXTRA_TIMER=8ms for hw bootup

#define PMU_BOOTROM_TIMER			(1)			// run to bootloader(system init) need 8.7ms
#define PMU_BOOTLOADER_L1_TIMER		PMU_DEFAULT_BL_TIME	// tested wakeup to phyinit complete need 17.5ms

#define PMU_PS_PREDEEPSLEEP_TIME    (5)        // maybe less than 20
#define PMU_PS_POSTDEEPSLEEP_TIME   (14)        // maybe less than 13

#define PMU_PSHANDSHAKE_TIME		(PMU_PS_PREDEEPSLEEP_TIME+PMU_PS_POSTDEEPSLEEP_TIME)    // code run time after sleep should also consider



#define RUNTIME_CHECKER_SIZE        (3)

#define PMU_PREHIB_REALTIME_THD     (2)
#define PMU_PRESLP_REALTIME_THD     (2)
#define PMU_PRESLP2_REALTIME_THD     (2)


#define PMU_TIMER_PROC_AHEAD_TIME                       (240)
#define PMU_SMALLIMG_HIB_EXPECTED_CODE_RUNNING_TIME     (2)
#define PMU_SMALLIMG_WORTH_SLEEP_TIME   (50+PMU_SMALLIMG_HIB_EXPECTED_CODE_RUNNING_TIME)


#define PMU_FULL_IMAGE_START_TIME   (50)        // time for bootloader -> fullimage -> freertos on

#define PMU_CHECK_CODE_RUNNING_TIME    (1)

#define PMU_PSM_HIB_CHECKER         (0)

#define PMU_SWTIMER_SLEEP_THD       (500)       // to fix timing bug in qcx212






#ifdef PMU_CHECK_CODE_RUNNING_TIME
typedef enum PmuRunTimeCheckPoint_enum
{
    PMU_RUNTIME_PS_PRESLEEP,
    PMU_RUNTIME_PS_POSTSLEEP,
    PMU_RUNTIME_PS_WAKEUPFLOW,
    PMU_RUNTIME_HIB_PRESLEEP,
    PMU_RUNTIME_HIB_POSTSLEEP,
    PMU_RUNTIME_SLP1_PRESLEEP,
    PMU_RUNTIME_SLP1_POSTSLEEP,
    PMU_RUNTIME_SLP2_PRESLEEP,
    PMU_RUNTIME_SLP2_POSTSLEEP,

    PMU_RUNTIME_SLP1_POSTCALLBACKS,
    PMU_RUNTIME_SLP2_POSTCALLBACKS,
    PMU_RUNTIME_HIB_POSTCALLBACKS,

    PMU_RUNTIMR_SLP2_PREUSRCB,
    PMU_RUNTIMR_HIB_PREUSRCB,
    PMU_RUNTIME_FLASH_UPDATE,

    PMU_RUNTIME_FINISHTIMER,            //just finish a timer do not print log
    PMU_RUNTIME_CHECKPOINT_MAX,
}PmuRunTimeCheckPoint;


typedef struct
{
    uint32_t RunTime1[RUNTIME_CHECKER_SIZE];
    uint32_t RunTime2[RUNTIME_CHECKER_SIZE];
}PmuRunTimeChecker;

typedef struct
{
    PmuRunTimeCheckPoint check_id;
    uint16_t expected_runtime;
}PmuRunTimeArray;


#endif


typedef enum PmuTimeCompensate_enum
{
    PMU_TIME_COMPENSATE_SAMPLE1,
    PMU_TIME_COMPENSATE_SAMPLE2,
    PMU_TIME_COMPENSATE_SAMPLE3,
}PmuTimeCompensateSM;

typedef struct PmuTimeSample_t
{
    uint32_t sample1;
    uint32_t sample2;
    uint32_t sample3;
    uint8_t sc_ratio;
    uint8_t valid_map;
}PmuTimeSample;










typedef enum PmuSlpResult_enum
{
    PMU_SLPFAIL_INVALID,
    PMU_SLPFAIL_INT,
    PMU_SLPFAIL_TIME,
    PMU_SLPFAIL_FLASH,
    PMU_SLPFAIL_VOTE,
    PMU_SLPFAIL_UART,
    PMU_SLP_SUCCESS,
    PMU_SLPFAIL_HIBTIMER,		
    PMU_SLP_RESULT_MAX,
}PmuSlpResult;


typedef struct
{
    IOLatchEn AonIOSimLatch;
    IOLatchEn AonIOUsrLatch;
	bool AonIOSimPowerOn;
	bool AonIOUsrPowerOn;
}IOLatchInfo_t;


/*** struct to maintain core context, only used before enter sleep mode.
since core will power off and lost all its context. need to restore the core
context after wake up from sleep*/

//NVIC context
typedef struct
{
  __IOM uint32_t ISER[1U];               /*size=32  Interrupt Set Enable Register */
  __IOM uint32_t ICER[1U];               /*size=32  Interrupt Clear Enable Register */
  __IOM uint32_t ISPR[1U];               /*size=32  Interrupt Set Pending Register */
  __IOM uint32_t ICPR[1U];               /*size=32  Interrupt Clear Pending Register */
  __IOM uint8_t  IP[9U];               /*size=9 Interrupt Priority Register (8Bit wide) */
}  NVIC_Store;


//SCB context,currently only necessary register is stored,may be need add later
typedef struct
{
  __IOM uint32_t ICSR;                   /*size=4 Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*size=4 Vector Table Offset Register */
  __IOM uint8_t SHP1;                    /*size=1 pend sv priority Register */
  __IOM uint8_t SHP2;                    /*size=1 systick priority Register */
  __IOM uint32_t AIRCR;                  /* size=4 for priority group */
  __IOM uint32_t CCR;
} SCB_Store;



// This typedef describes the structure at which the core register is stored.
typedef struct
{
//    uint32_t valid_magic;       // indicate this area is not overwritten
	uint32_t sr1_r12[12];    /**size=0x30**/// place to store relevant user\system registers (r1-r12)
	uint32_t spsp;           /**size=0x4 **/// place to store the PSP
	uint32_t sLR;            /**size=0x4 **/// place to store the LR
	uint32_t smsp;          /**size=0x4 **/// place to store the MSP
	uint32_t sxPSR;         /**size=0x4**/// place to store XPSR
	uint32_t sPRIMASK;     /**size=0x4 **/// place to store PRIMASK
	uint32_t sFAULTMASK;  /**size=0x4 **/// place to store FAULTMASK
	uint32_t sBASEPRI;  /**size=0x4 **/// place to store BASEPRI
	uint32_t sCONTROL;  /**size=0x4 **/// place to store CONTROL
    NVIC_Store sNVIC;
	SCB_Store sSCB;//no need to store all SCB registers
	MPU_Type sMPU;//mpu context
	uint32_t xic_mask0;
	uint32_t xic_mask1;
    uint32_t xic_clrovf0;
    // for msg transfer between small image and full image
    uint32_t wakeupSlowCnt;
    uint32_t sleepTime;
    uint8_t wakeup_type;
    uint8_t padIntLatch;
}sleepStateBackupRegs;




/**
  \brief a stucture for array to store backup function and it's parameters.
 */
typedef struct
{
	pmuPreDeepSlpCb_t func;
	void *pdata;
}pmuPreDeepSlpCbFunc_t;

/**
  \brief a stucture for array to store restore function and it's parameters.
 */
typedef struct
{
	pmuPostDeepSlpCb_t func;
	void *pdata;
}pmuPostDeepSlpCbFunc_t;

typedef LpState (* pmuUserdefSleepCb_Func)(void);

void pmuRegisterUsrSlpModeCb(pmuUserdefSleepCb_Func callback);

//////////////////////api for ps/phy /////////////////


void pmuAONIOPowerOn(uint8_t id);
void pmuAONIOPowerOff(uint8_t id);
uint32_t pmuGetHibSecondCount(void);
uint32_t pmuBoot2BcTime(void);
bool pmuAonCtxPhyCheck(void);

////////////////////////api for plat///////////////////////
void pmuHibTimerChangedSet(bool IsChanged);
void pmuUsrAddSlpDelay(uint32_t value);
void pmuSetTimingCfg(pmuTimeCfg_t *cfg);
void pmuGetTimingCfg(pmuTimeCfg_t *cfg);
void pmuGetDefaultTimingCfg(void);
void pmuFlushUsrNVMem(bool immediately, LpState lowPowerState);
void pmuHibTimerRecoverEnv(void);
void ecpmLatchPadInt(uint8_t bitmap);
void ecpmSetLatchedPending(void);
void pmuRecoverSystemRegisters(void);
BootFlag_e pmuGetBootFlag(void);
void PmuSetImageType(uint8_t type);
void InitWakeFullImage(void);
void SetWakeFullImage(uint32_t WakeFullImage);
uint32_t CheckWakeFullImage(void);
uint8_t PmuGetImageType(void);
void pmuSetSleepedFlag(bool sleeped);
bool pmuGetSleepedFlag(void);
void pmuGetSleepFailReason(slpManSlpState_t *DeepestSlpMode, slpManSlpState_t *psphyVoteState, slpManSlpState_t *appVoteState,  slpManSlpState_t *usrdefSlpMode,  uint32_t *drvVoteMap, uint32_t *drvVoteMask);
void pmuGetSDKVoteDetail(uint32_t *sleepVoteFlag, uint32_t *sleep2VoteFlag, uint32_t *hibVoteFlag);

// call in rtc interrupt handler
void pmuSwTimerIntEnter(void);
void pmuRestoreHibTimer(void);
void pmuRestoreBootFlag(void);
uint8_t pmuGetWakeupSrc(void);
uint8_t pmuCheckWakeupSrc(void);
uint32_t pmuGetWakeupSlowCnt(void);
void pmuSetWakeupSlowCnt(uint32_t value);
uint32_t pmuGetSleepTime(void);
void pmuSetSleepTime(uint32_t value);
void pmuSetWakeupPad(padWakeupSettings_t cfg);
void pmuRegisterUsrSlpModeCb(pmuUserdefSleepCb_Func callback);
#if PS_PMUTIME_TEST
bool pmuCheckPSWakeup(void);
#endif
void pmuEnterTickless(void);
void pmuGetPMUSettings(void);
void pmuEnterHibernate(LpState last_sleep_state);
void pmuInit(void);
void pmuInitSmallImg(void);
void pmuDeinit(void);
void pmuUpdateUserNVMem(void);
uint8_t * pmuGetUserNVMem(void);
void pmuRestoreUserNVMem(void);
bool pmuExtIntPreProcess(uint8_t bitmap);
void pmuProductionTest(PmuMode mode);
void pmuSetDrvVoteMask(uint32_t mask);
//////////////MCU Mode/////////////////
void pmuAONIOSet(uint8_t id, IOLatchEn latch_en);
IOLatchEn pmuAONIOGet(uint8_t id);
void pmuAONIOLatchRelease(void);
bool pmuAONIOIsLatchRel(void);
uint32_t pmuGetEstimateSlpTime(void);
uint8_t pmuGetSCRatio(void);
uint32_t pmuScReadMcuMode(void);
void pmuMcuModeThdSet(uint32_t mcuModeEnterThd, uint32_t firstMcuModeSlpTime);
void pmuSetMcuMode(bool mcu_en);
uint8_t ecpmGetLatchPad(void);
void ecpmClrLatchPad(void);
void pmuRawFlashInitCheck(void);



#ifdef __cplusplus
}
#endif

#endif

