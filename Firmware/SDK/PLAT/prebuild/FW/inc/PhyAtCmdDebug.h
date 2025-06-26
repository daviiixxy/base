/****************************************************************************
*
* Copy right:   2017-, Copyrigths of Qualcomm Ltd.
* File name:    PhyAtCmdDebug.h
* Description:  Definition of L1 AT command info
* History:      04/18/2019    Originated by Pan Wang
*
****************************************************************************/
#ifndef _PHY_ATCMD_DEBUG_H
#define _PHY_ATCMD_DEBUG_H
#if defined(__CC_ARM)
#pragma anon_unions
#endif

/*
// All possible configuration list as bellow:
AT+ECPHYCFG?  (check the status of all modules)
return "power", powerTestFlag, targetPower, "Oos", oosTestFlag, "Escape", onOffFlag,  "Dump", onOffFlag, dumpTask, "TxDpd", onOffFlag, "graph", onOffFlag, "algoParam", 0, param_0

AT+ECPHYCFG="power",0             (turn off tx power debug)
AT+ECPHYCFG="power",1, 15         (turn on tx power debug with targetPower(15))
AT+ECPHYCFG="power",2,-10, 20     (turn on tx power debug with minPower(-10) and maxPower(10), and maxPower >= minPower)

AT+ECPHYCFG="oos",0               (turn off oos debug)
AT+ECPHYCFG="oos",1               (disable oos)
AT+ECPHYCFG="oos",2               (report OOS)

AT+ECPHYCFG="escape",0            (turn off escape debug)
AT+ECPHYCFG="escape",1            (turn on escape debug)

AT+ECPHYCFG="txDpd",0             (turn off txDpd debug)
AT+ECPHYCFG="txDpd",1             (turn on txDpd)

AT+ECPHYCFG="graph",0             (turn off PHY GRAPH of hwTask)
AT+ECPHYCFG="graph",1             (turn on PHY GRAPH of hwTask)

AT+ECPHYCFG="dcxoinit",1          (Initialize DCXO calibration file, once when triggered)
AT+ECPHYCFG="dcxoinit",2          (Initialize DCXO gpDCXOFTBuf, once when triggered)


AT+ECPHYCFG="algoParam", 0        (PHY ALGO. parameters debug)
AT+ECPHYCFG="algoParam", type, [param0], [param1], ...., [param6]
ICS CELL LOCK:

DCXO TX GAP AFC:

// 0 <= minCombLen <= maxCombLen <= 20
// speed Level: 0-0km/h; 1-15km/h; 2-30km/h; 3-60km/h; 4-90km/h; 5-120km/h; 0xFF-not Set
// atcIntCombLen: 0,1,2,3,0xFF(not Set)
CE COMB LEN & SPEED LEVEL: AT+ECPHYCFG="algoParam",3,minCombLen,maxCombLen,speed Level,atcIntCombLen

// channel Type: 0-PCH NPDxCH; 1-SIB1; 2-SIBx; 3-RAR/MSG4/CRNTI NPDxCH
// ceAxc INT distance: number of data subframe
CEAXC INT DIST: AT+ECPHYCFG="algoParam",4,channel Type,ceAxc INT distance

// eDRX enable: 0-enable; 1-disable
// eDRX cycle: 1~10, only valid when eDRX is enabled
eDRX configuration: AT+ECPHYCFG="algoParam",8,eDRX enable,eDRX cycle

non-anchor paging: AT+ECPHYCFG="algoParam",14,
                                non-anchor carrier euArfcn(part0),
                                non-anchor carrier euArfcn(part1),
                                non-anchor carrier euArfcn(part2),
                                non-anchor carrier euArfcn(part3)
for example, 3738: part0-3;part1-7;part2-3;part3-8
             300:  part0-0;part1-3;part2-0;part3-0

// statisReqType:0-START; 1-GET; 2-STOP
cephyStatisOperReq: AT+ECPHYCFG="algoParam",17, statisReqType

// dlFreqOffset: 0-skip this value;9-(-7.5)kHz; 10-(-2.5)kHz; 11-0kHz; 12-2.5kHz; 13-7.5kHz
dlFreqOffset in SIB5: AT+ECPHYCFG="algoParam",18, dlFreqOffset

// enable all Rx subframes for sensitivity test or performance test in fading channel
AT+ECPHYCFG="algoParam",19

// DL bitmap debug in SIB1_CFG
AT+ECPHYCFG="algoParam",25,(downlinkBitmapConfigType << 4) | dlBitmapChoice,subframePatternBitStringHigh(bit15~8),
            subframePatternBitStringHigh(bit7~0),subframePatternBitStringLow(31~24),subframePatternBitStringLow(23~16),
            subframePatternBitStringLow(15~8),subframePatternBitStringLow(7~0)


AT+ECPHYCFG="Assert",1          (Trigger Assert immediately)
AT+ECPHYCFG="Assert",2          (Trigger psReset)


AT+ECPHYCFG="Clean",1           (clear all ECPHYCFG)

*/

#define PHY_ATCMD_ALGOPARAM_LEN        7
#define PHY_ATC_DEFAULT_VALUE          0x7F


//define AT command for phy debug
typedef enum
{
    PHY_DEBUG_SET_POWER         = 0x00,
    PHY_DEBUG_SET_OOS           = 0x01,
    PHY_DEBUG_SET_ESCAPE        = 0x02,
    PHY_DEBUG_SET_DUMP          = 0x03,
    PHY_DEBUG_SET_TXDPD         = 0x04,
    PHY_DEBUG_SET_GRAPH         = 0x05,
    PHY_DEBUG_SET_ALGOPARAM     = 0x06,
    PHY_DEBUG_SET_DCXO_CALI_INIT = 0x07,    // used to INIT DCXO Calibration file, should send AT+CFUN=0 followed
    PHY_DEBUG_SET_LOG_LEVEL     = 0x08,
    PHY_DEBUG_SET_EDRX_SIMU     = 0x09,
    PHY_DEBUG_SET_ASSERT        = 0x0F,
    PHY_DEBUG_CLEAR_ALL         = 0xFF,
}phyDbgModule;
typedef UINT8 phyDbgModule_t;



// Tx Power Mode
typedef enum
{
    PHY_TXPOWER_DEBUG_OFF           = 0x00,
    PHY_TXPOWER_FIXED_POWER         = 0x01,
    PHY_TXPOWER_LIMIT_MAX_POWER     = 0x02,
    PHY_TXPOWER_MAX_POWER           = 0x03,         // set max power of UE, more than 23dBm
}phyDbgOnOffflag;



// subtype for PHY_DEBUG_SET_ALGOPARAM
typedef enum
{
    PHY_ALGO_TYPE_ICS_CELLLOCK      = 0x01,
    PHY_ALGO_TYPE_DCXO_TX_GAP_AFC   = 0x02,
    PHY_ALGO_TYPE_CE_COMBLEN_SPDLVL = 0x03,
    PHY_ALGO_TYPE_CEAXC_INT_DIST    = 0x04,
    PHY_ALGO_TYPE_TX_TAOFFSET       = 0x05,     // only one param range 0~31
    PHY_ALGO_TYPE_SET_CELEVEL       = 0x06,     // only one param range 0~31
    PHY_ALGO_TYPE_SET_FILTTYPE      = 0x07,     // only one param range 0~31
    PHY_ALGO_TYPE_EDRX_CONFIG       = 0x08,
    PHY_ALGO_TYPE_PRESYNC_MODE      = 0x09,
    PHY_ALGO_TYPE_CELEVEL_TXPOW     = 0x0A,
    PHY_ALGO_TYPE_CONNECT_MODE      = 0x0B,
    PHY_ALGO_TYPE_INIT_TA           = 0x0C,
    PHY_ALGO_TYPE_DCXO_HIGH_TEMP    = 0x0D,     //high temperature device test
    PHY_ALGO_TYPE_NONANCHOR_PAGING  = 0x0E,
    PHY_ALGO_TYPE_PRESYNC_SEGMENT   = 0x0F,
    PHY_ALGO_TYPE_CEINFO_REQ        = 0x10,
    PHY_ALGO_TYPE_STATIS_OPER_REQ   = 0x11,
    PHY_ALGO_TYPE_INTER_FREQ_MEAS   = 0x12,
    PHY_ALGO_TYPE_ENABLE_ALL_RX     = 0x13,
    // Set meas earfcn&freqOfst,  earfcn = (pAtCmdAlgoParam->param[0]*100 + pAtCmdAlgoParam->param[1]), dlFreqOfst = pAtCmdAlgoParam->param[2]
    PHY_ALGO_TYPE_MEAS_CFG          = 0x14,
    PHY_ALGO_TYPE_FALSE_DCI_SIM     = 0x15,
    PHY_ALGO_TYPE_RFIP2_DBG         = 0x16,
    PHY_ALGO_TYPE_NPRS_DUMP         = 0x17,
    PHY_ALGO_TYPE_BI_DISABLE        = 0x18,
    PHY_ALGO_TYPE_DLBMP_DBG         = 0x19,
    PHY_ALGO_TYPE_IDLE_SPDEST       = 0x1A,
}phyDbgAlgoType;
typedef UINT8 phyDbgAlgoType_t;


typedef struct PhyDebugAtCmdSetParam_Tag
{
    phyDbgModule_t  module;
    INT8            data[9];

}PhyDebugAtCmdSetParam;


//return for tx power module status
typedef struct AtCmdPowerInfo_Tag
{
    //powerTestFlag == 0, mean APC;
    //powerTestFlag == 1, mean set targetPower by AT command
    //powerTestFlag == 2, mean set minPower and maxPower by AT command
    UINT8  powerTestFlag;
    INT8   minPower;
    INT8   maxPower;
    INT8   targetPower;     // FWL = 2
}AtCmdPowerInfo;

//return for oos status
//AT+PHYDBGSET="OOS",oosTestFlag //if oosTestFlag =1 disable OOS function, 2 report OOS
//AT+PHYDBGGET="OOS" return oosTestFlag
typedef struct AtCmdOOSInfo_Tag
{
    UINT8 oosTestFlag;
}AtCmdOOSInfo;


// Used for Rx/Tx Dump
// Note: should Config dump Task and then trigger assert by set dumpTask = 0xFF
//       should disable PMU when dump used
// Dump Sequence:
// Step 1: UE Power ON
// Step 2: AT+CFUN=0
// Step 3: AT+ECPHYCFG="dump",1,dumpTask   -> Set DumpTask
// [Step 4: AT+ECPHYCFG?             -> check dumpTask]
// Step 5: AT+CFUN=1
// Step 6: Wait after run over dumpTask, then
// Step 7: Save dump data from 0x38000 in KEIL by:   SAVE D:\zlfu\xxx.txt 0x38000,0x3FFFF
typedef struct AtCmdDumpInfo_Tag
{
    UINT8 onOffFlag;   // Set By AT CMD, and store in FLASH, restore from FLASH after power on/wake up
    UINT8 dumpTask;    // 0xFF to trigger assert without dump
    UINT8 dumpFlag;    // only set by AT CMD, not restore from FLASH, after dump configured, clear this flag
    UINT8 gpValue;
}AtCmdDumpInfo;


//return for escape status
typedef struct AtCmdEscapeInfo_Tag
{
    //1 debug function on; 0 use default parameter
    //if wanting to close escape funtion, use onOffFlag with value 1 and set rsrpTh a larger value, for example 0dB
    UINT8  onOffFlag;
    INT8   rsrpTh;
    INT8   escpSnrUrgentTh;
    INT8   escpSnrCriticalTh;
    UINT8  raFailTh;
    INT8   rsrqTh;
    UINT8  escapeEvaNoTh;
}AtCmdEscapeInfo;

// Used for Enable/Disable TX DPD
// Note: for Current Code, default config is enable DPD
// Step 1: UE Power ON
// Step 2: AT+CFUN=0
// Step 3: AT+ECPHYCFG="txDpd",1
// [Step 4: AT+ECPHYCFG?             -> check txDpd]
// Step 5: AT+CFUN=1
typedef struct AtCmdTxDpdInfo_Tag
{
    UINT8  disableFlag;   // Set By AT CMD, and store in FLASH, restore from FLASH after power on/wake up
}AtCmdTxDpdInfo;


// Used for Enable/Disable PHY Graph of HwTask
// Note: for Current Code, default config is disable
// Step 1: UE Power ON
// Step 2: AT+CFUN=0
// Step 3: AT+ECPHYCFG="graph",1
// [Step 4: AT+ECPHYCFG?             -> check onOffFlag
// Step 5: AT+CFUN=1
typedef struct AtCmdGraphInfo_Tag
{
    UINT8  onOffFlag;   // Set By AT CMD, and store in FLASH, restore from FLASH after power on/wake up
}AtCmdGraphInfo;


// Used for Set algo parameters
// Step 1: UE Power ON
// Step 2: AT+CFUN=0
// Step 3: AT+ECPHYCFG="algoParam", type, [param0], [param1], [param2], [param3], [param4], [param5], [param6]
// [Step 4: AT+ECPHYCFG?             -> check txDpd]
// Step 5: AT+CFUN=1
typedef struct AtCmdAlgoParam_Tag
{
    phyDbgAlgoType_t    algoType;     // 0: OFF, 1~255 different algo Type defined by PHY
    UINT8               param[PHY_ATCMD_ALGOPARAM_LEN];
}AtCmdAlgoParam;


// Used for Set PHY log level
// Step 3: AT+ECPHYCFG="logLevel",1
typedef struct AtCmdPhyLogInfo_Tag
{
    UINT8  logLevel;   // 0: reduced Log level
                       // 1: all PHY logs
                       // > 1: no PHY LOGS
}AtCmdPhyLogInfo;


typedef struct AtCmdPhyEdrxPara_Tag
{
    BOOL enableFlag;   // 0:disable; 1:enable
    UINT8 eDRXPrdIdx;  // eDRX period. 0:81.92s, 1:655.36s, 2:1310.72s
    UINT8 eDRXPtwIdx;  // eDRX PTW. 0:20.48s, 1:40.96s
    UINT8 rsvd;
}AtCmdPhyEdrxPara;


typedef struct PhyDebugAtCmdInfo_old_v2_Tag
{
    AtCmdPowerInfo      atCmdPowerInfo;  //restore at command for tx power
    AtCmdOOSInfo        atCmdOOSInfo;    //restore at command for oos
    AtCmdEscapeInfo     atCmdEscapeInfo; //restore at command for escape
    AtCmdDumpInfo       atCmdDumpInfo;   //for dump or trigger assert
    AtCmdTxDpdInfo      atCmdTxDpdInfo;
    AtCmdGraphInfo      atCmdGraphInfo;
    AtCmdAlgoParam      atCmdAlgoParam;  // free defined algo parameters
    AtCmdPhyLogInfo     atCmdPhyLogCtrl;
}PhyDebugAtCmdInfo_old_v2;


typedef struct PhyDebugAtCmdInfo_Tag
{
    AtCmdPowerInfo      atCmdPowerInfo;  //restore at command for tx power
    AtCmdOOSInfo        atCmdOOSInfo;    //restore at command for oos
    AtCmdEscapeInfo     atCmdEscapeInfo; //restore at command for escape
    AtCmdDumpInfo       atCmdDumpInfo;   //for dump or trigger assert
    AtCmdTxDpdInfo      atCmdTxDpdInfo;
    AtCmdGraphInfo      atCmdGraphInfo;
    AtCmdAlgoParam      atCmdAlgoParam;  // free defined algo parameters
    AtCmdPhyLogInfo     atCmdPhyLogCtrl;
    AtCmdPhyEdrxPara    atCmdPhyEdrxPara;
    UINT32              rsvd0;
    UINT32              rsvd1;
}PhyDebugAtCmdInfo;

//AT+ECPHYCFG?
//get all module status
typedef struct PhyDebugAtCmdAllInfo_Tag
{
    UINT8 flag[16];
}PhyDebugAtCmdAllInfo;

typedef struct CePhyReqTag
{
    struct {
        UINT32 reqId;
        UINT32 srcHandler;
    }header;

    UINT8 body[];
}CePhyReq;

typedef struct CePhyCnfTag
{
    struct {
        UINT32      cnfId;      //4 MSB bits SG ID | 16 bits PRIM ID
        UINT32      srcHandler; //Handler from CePhyReq
        UINT32      rc;
        UINT32      reserved;
    }header;

    UINT8 body[];
}CePhyCnf;

typedef struct CePhyIndTag
{
    struct {
        UINT32      indId;      //4 MSB bits SG ID | 16 bits PRIM ID
        UINT32      reserved;
    }header;

    UINT8 body[];
}CePhyInd;

#define CEPHY_GET_SG_ID(reqId) (((reqId)>>16)&0xffff)
#define CEPHY_GET_PRIM_ID(reqId) ((reqId)&0xffff)
#define CEPHY_SET_REQ_CNF_ID(sgId, primId) ((UINT32)(((sgId)<<16)|((primId)&0xffff)))
//#define AT_CMD_SET          1
//#define AT_CMD_SET_TX_POWER 1
typedef enum CePhyRetEnum_Tag   /* ret*/
{
    /* CEPHY <-> PLAT */
    CEPHY_RET_OK,
    CEPHY_RET_ERR,
}CePhyRetEnum;

// Phy with PLAT used Signal ID definition, start from 0x5000
typedef enum CePhySigIdEnum_Tag   /* SIG Id*/
{
    /* CEPHY <-> PLAT */
    SIG_CEPHY_DEBUG_BASE,
    SIG_CEPHY_DEBUG_REQ,
    SIG_CEPHY_DEBUG_CNF,
    SIG_CEPHY_DEBUG_IND,
    SIG_CEPHY_DEBUG_RSP,
}CePhySigIdEnum;

typedef enum CePhySgIdEnum_Tag   /* SG Id*/
{
    SG_CEPHY_BASE = 1,//basic/common
    SG_CEPHY_DEBUG = 2,

    SG_CEPHY_MAX
}CePhySgIdEnum;

// Phy with PLAT used Signal ID definition, start from 0x5000
typedef enum CePhyPrimIdEnum_Tag   /* Prim Id*/
{
    /* CEPHY <-> PLAT */
    SIG_CEPHY_PLAT_BASE = 0x3f00,
    SIG_CEPHY_DEBUG_AT_CMD_SET_REQ, //PhyDebugAtSetCfgReq
    SIG_CEPHY_DEBUG_AT_CMD_SET_CNF,

    SIG_CEPHY_DEBUG_AT_CMD_GET_REQ, //PhyDebugAtGetCfgReq
    SIG_CEPHY_DEBUG_AT_CMD_GET_ALL_CNF, //PhyDebugAtCmdAllInfo
}CePhyPrimIdEnum;

extern PhyDebugAtCmdInfo *gpPhyDebugAtCmd;


BOOL PhyDebugAtSetCfgReq(CePhyReq *psig);
BOOL PhyDebugAtGetCfgReq(CePhyReq *psig);
void CePhyRequest(UINT16 srcHdr, UINT8 sigId, UINT8 sgId, UINT16 primId, UINT16 primSize, void *primBody);
void CePhyConfirm(UINT16 atHandle, UINT32 retCode, UINT16 sigId, UINT16 sgId, UINT16 primId, UINT16 primSize, void *primBody);
INT32 PhyDebugSetTxPower(INT32 txPower);
void PhyEscapeModuleThSet(INT16* rsrpTh, INT16* escpSnrUrgentTh, INT16* escpSnrCriticalTh, INT16* raFailTh, INT16* rsrqTh, INT16* escapeEvaNoTh);
void PhyOOSModuleFunction(INT16 *curSnr, INT16 qOutTh);
BOOL PhyTxDpdOnOffGet(void);
BOOL PhyGraphOnOffGet(void);
BOOL PhyDbgMeasCfgCheck(void);
UINT32 PhyDbgMeasCfgEarfcnGet(void);
BOOL PhyIcsLockCellCheck(void);
BOOL PhyCeCombLenSpdLvlCheck(void);
BOOL PhyCeAxcIntDistCheck(void);
UINT8 PhyDbgAlgoParamGet(UINT8 index);
BOOL PhyDcxoTxGapAfcCheck(void);
BOOL PhyTxTaOffSetCheck(void);
BOOL PhyCeLevelCheck(void);
BOOL PhyFiltTypeCheck(void);
BOOL PhyEdrxCfgCheck(void);
BOOL PhyConnectCfgCheck(void);
BOOL PhyPresyncCfgCheck(void);
BOOL PhyCeLevelTxPowCheck(void);
BOOL PhyDebugTxPowerMaxCheck(void);
BOOL PhyInitTaSetCheck(void);
BOOL PhyPresyncHeatCfgCheck(void);
BOOL PhyNonAnchorPagingCheck(void);
BOOL PhyIsDummyNonAnchorPaging(void);
BOOL PhyStatisOperReqCheck(void);
BOOL PhyDummyInterDlFreqOfstCheck(void);
BOOL PhyEnableAllRxCheck(void);
BOOL PhyPresyncOsSegPara(void);
BOOL PhyFalseDciSimCheck(void);
BOOL PhyFakeEdrxCheck(void);
BOOL PhyRfIp2DebugCheck(void);
BOOL PhyDlBmpDbgCheck(void);
BOOL PhyIdleSpeedEstDbgCheck(void);


#endif

