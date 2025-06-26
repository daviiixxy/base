#ifndef __CEUP_SIG_H__
#define __CEUP_SIG_H__

/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ceupsig.h
 * Description:  define signals received by UP module
 *
 ****************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
#include "pssys.h"
//#include "pscommutil.h"
#include "nascommon.h"
/*********************************************************************************
* Macros
*********************************************************************************/
#define NB_KEY_LENGTH                   16

#define NB_SRB_NUM                      2//SRB 1, SRB 1bis
#define CAT_SRB_NUM                     2//SRB 1, SRB 2

#define NB_DRB_NUM                      2
#define CAT_DRB_NUM                     11

#if ! defined (CERRC_CAT_MODE)
#define MAX_SRB                         NB_SRB_NUM
#define MAX_DRB                         NB_DRB_NUM
#else
#define MAX_SRB                         CAT_SRB_NUM
#define MAX_DRB                         CAT_DRB_NUM
#endif



/*********************************************************************************
* Enums
*********************************************************************************/
/********************************************************************************
* RRC->UP
*********************************************************************************/
typedef enum UpConfigTypeTag
{
    UP_CONFIG_INVALID           = 0,
    UP_CONFIG_RELEASE           = 1,
    UP_CONFIG_RELEASE_SUSPEND   = 2,    //almost the same as RELEASE, the next action can be setup or setup_resume
    UP_CONFIG_NOT_CHANGE        = 3,
    UP_CONFIG_SETUP             = 4,
    UP_CONFIG_SETUP_RESUME      = 5,    //almost the same as SETUP, can only be set if the previous action is release_suspend
    UP_CONFIG_MODIFY            = 6,
}UpConfigType;

typedef enum LogicalChannelIdTag
{
    LOGICAL_CH_ID_SRB1          = 1,
    LOGICAL_CH_ID_SRB2          = 2,  //not apply for NB-IoT
    LOGICAL_CH_ID_SRB1bis       = 3,
}LogicalChannelId;

typedef enum MacResetReasonTag
{
    MAC_REEST = 0,        //indciates that the reset is for reestablishment
    MAC_REEST_RETRY = 1,  //indicates that the reset is for re-initiating a new RA procedure if the last RA failed
    MAC_EST_RETRY = 2,    //indicates that the reset is used to trigger RA again during establishment.
    RETURN_IDLE = 3,      //indicates that the reset is used to return to idle.
    RETURN_IDLE_WITH_SUSPEND = 4,   //indicate that the reset is used to return to idle for RRCConnectionRelease with releaseCause is rrc-Suspend procedure
}MacResetReason;

typedef enum PDCPConfigDiscardTimer_NBTag
{
    PDCPConfigDiscardTimer_NB_ms5120,
    PDCPConfigDiscardTimer_NB_ms10240,
    PDCPConfigDiscardTimer_NB_ms20480,
    PDCPConfigDiscardTimer_NB_ms40960,
    PDCPConfigDiscardTimer_NB_ms81920,
    PDCPConfigDiscardTimer_NB_infinity,
    PDCPConfigDiscardTimer_NB_spare2,
    PDCPConfigDiscardTimer_NB_spare1
}PDCPConfigDiscardTimer_NB;

typedef enum PDCPConfigDiscardTimerTag
{
    PDCPConfigDiscardTimer_ms50,
    PDCPConfigDiscardTimer_ms100,
    PDCPConfigDiscardTimer_ms150,
    PDCPConfigDiscardTimer_ms300,
    PDCPConfigDiscardTimer_ms500,
    PDCPConfigDiscardTimer_ms750,
    PDCPConfigDiscardTimer_ms1500,
    PDCPConfigDiscardTimer_infinity
}PDCPConfigDiscardTimer;


typedef enum PollRetransmit_NBTag
{
    PollRetransmit_NB__ms250,
    PollRetransmit_NB_ms500,
    PollRetransmit_NB_ms1000,
    PollRetransmit_NB_ms2000,
    PollRetransmit_NB_ms3000,
    PollRetransmit_NB_ms4000,
    PollRetransmit_NB_ms6000,
    PollRetransmit_NB_ms10000,
    PollRetransmit_NB_ms15000,
    PollRetransmit_NB_ms25000,
    PollRetransmit_NB_ms40000,
    PollRetransmit_NB_ms60000,
    PollRetransmit_NB_ms90000,
    PollRetransmit_NB_ms120000,
    PollRetransmit_NB_ms180000,
    PollRetransmit_NB_spare1
}PollRetransmit_NB;


typedef enum PollRetransmitTag
{
    PollRetransmit_ms5,
    PollRetransmit_ms10,
    PollRetransmit_ms15,
    PollRetransmit_ms20,
    PollRetransmit_ms25,
    PollRetransmit_ms30,
    PollRetransmit_ms35,
    PollRetransmit_ms40,
    PollRetransmit_ms45,
    PollRetransmit_ms50,
    PollRetransmit_ms55,
    PollRetransmit_ms60,
    PollRetransmit_ms65,
    PollRetransmit_ms70,
    PollRetransmit_ms75,
    PollRetransmit_ms80,
    PollRetransmit_ms85,
    PollRetransmit_ms90,
    PollRetransmit_ms95,
    PollRetransmit_ms100,
    PollRetransmit_ms105,
    PollRetransmit_ms110,
    PollRetransmit_ms115,
    PollRetransmit_ms120,
    PollRetransmit_ms125,
    PollRetransmit_ms130,
    PollRetransmit_ms135,
    PollRetransmit_ms140,
    PollRetransmit_ms145,
    PollRetransmit_ms150,
    PollRetransmit_ms155,
    PollRetransmit_ms160,
    PollRetransmit_ms165,
    PollRetransmit_ms170,
    PollRetransmit_ms175,
    PollRetransmit_ms180,
    PollRetransmit_ms185,
    PollRetransmit_ms190,
    PollRetransmit_ms195,
    PollRetransmit_ms200,
    PollRetransmit_ms205,
    PollRetransmit_ms210,
    PollRetransmit_ms215,
    PollRetransmit_ms220,
    PollRetransmit_ms225,
    PollRetransmit_ms230,
    PollRetransmit_ms235,
    PollRetransmit_ms240,
    PollRetransmit_ms245,
    PollRetransmit_ms250,
    PollRetransmit_ms300,
    PollRetransmit_ms350,
    PollRetransmit_ms400,
    PollRetransmit_ms450,
    PollRetransmit_ms500,
    PollRetransmit_ms800_v1310,
    PollRetransmit_ms1000_v1310,
    PollRetransmit_ms2000_v1310,
    PollRetransmit_ms4000_v1310,
    PollRetransmit_spare5,
    PollRetransmit_spare4,
    PollRetransmit_spare3,
    PollRetransmit_spare2,
    PollRetransmit_spare1
}PollRetransmit;


typedef enum UlAmRlcMaxRetxThresholdTag
{
    UlAmRlcMaxRetxThreshold_t1,
    UlAmRlcMaxRetxThreshold_t2,
    UlAmRlcMaxRetxThreshold_t3,
    UlAmRlcMaxRetxThreshold_t4,
    UlAmRlcMaxRetxThreshold_t6,
    UlAmRlcMaxRetxThreshold_t8,
    UlAmRlcMaxRetxThreshold_t16,
    UlAmRlcMaxRetxThreshold_t32
}UlAmRlcMaxRetxThreshold;


typedef enum ReorderingTag
{
    Reordering_ms0,
    Reordering_ms5,
    Reordering_ms10,
    Reordering_ms15,
    Reordering_ms20,
    Reordering_ms25,
    Reordering_ms30,
    Reordering_ms35,
    Reordering_ms40,
    Reordering_ms45,
    Reordering_ms50,
    Reordering_ms55,
    Reordering_ms60,
    Reordering_ms65,
    Reordering_ms70,
    Reordering_ms75,
    Reordering_ms80,
    Reordering_ms85,
    Reordering_ms90,
    Reordering_ms95,
    Reordering_ms100,
    Reordering_ms110,
    Reordering_ms120,
    Reordering_ms130,
    Reordering_ms140,
    Reordering_ms150,
    Reordering_ms160,
    Reordering_ms170,
    Reordering_ms180,
    Reordering_ms190,
    Reordering_ms200,
    Reordering_ms1600_v1310
}Reordering;

typedef enum StatusProhibitTag
{
    StatusProhibit_ms0,
    StatusProhibit_ms5,
    StatusProhibit_ms10,
    StatusProhibit_ms15,
    StatusProhibit_ms20,
    StatusProhibit_ms25,
    StatusProhibit_ms30,
    StatusProhibit_ms35,
    StatusProhibit_ms40,
    StatusProhibit_ms45,
    StatusProhibit_ms50,
    StatusProhibit_ms55,
    StatusProhibit_ms60,
    StatusProhibit_ms65,
    StatusProhibit_ms70,
    StatusProhibit_ms75,
    StatusProhibit_ms80,
    StatusProhibit_ms85,
    StatusProhibit_ms90,
    StatusProhibit_ms95,
    StatusProhibit_ms100,
    StatusProhibit_ms105,
    StatusProhibit_ms110,
    StatusProhibit_ms115,
    StatusProhibit_ms120,
    StatusProhibit_ms125,
    StatusProhibit_ms130,
    StatusProhibit_ms135,
    StatusProhibit_ms140,
    StatusProhibit_ms145,
    StatusProhibit_ms150,
    StatusProhibit_ms155,
    StatusProhibit_ms160,
    StatusProhibit_ms165,
    StatusProhibit_ms170,
    StatusProhibit_ms175,
    StatusProhibit_ms180,
    StatusProhibit_ms185,
    StatusProhibit_ms190,
    StatusProhibit_ms195,
    StatusProhibit_ms200,
    StatusProhibit_ms205,
    StatusProhibit_ms210,
    StatusProhibit_ms215,
    StatusProhibit_ms220,
    StatusProhibit_ms225,
    StatusProhibit_ms230,
    StatusProhibit_ms235,
    StatusProhibit_ms240,
    StatusProhibit_ms245,
    StatusProhibit_ms250,
    StatusProhibit_ms300,
    StatusProhibit_ms350,
    StatusProhibit_ms400,
    StatusProhibit_ms450,
    StatusProhibit_ms500,
    StatusProhibit_ms800_v1310,
    StatusProhibit_ms1200_v1310,
    StatusProhibit_ms1600_v1310,
    StatusProhibit_ms2000_v1310,
    StatusProhibit_ms2400_v1310,
    StatusProhibit_spare2,
    StatusProhibit_spare1
}StatusProhibit;


typedef enum PollPduAmTag
{
    PollPdU_AM_p4,
    PollPdU_AM_p8,
    PollPdU_AM_p16,
    PollPdU_AM_p32,
    PollPdU_AM_p64,
    PollPdU_AM_p128,
    PollPdU_AM_p256,
    PollPdU_AM_pInfinity,
    PollPdU_AM_v1310_p512,
    PollPdU_AM_v1310_p1024,
    PollPdU_AM_v1310_p2048,
    PollPdU_AM_v1310_p4096,
    PollPdU_AM_v1310_p6144,
    PollPdU_AM_v1310_p8192,
    PollPdU_AM_v1310_p12288,
    PollPdU_AM_v1310_p16384
}PollPduAm;


typedef enum PollByteAmTag
{
    PollByte_AM_kB25,
    PollByte_AM_kB50,
    PollByte_AM_kB75,
    PollByte_AM_kB100,
    PollByte_AM_kB125,
    PollByte_AM_kB250,
    PollByte_AM_kB375,
    PollByte_AM_kB500,
    PollByte_AM_kB750,
    PollByte_AM_kB1000,
    PollByte_AM_kB1250,
    PollByte_AM_kB1500,
    PollByte_AM_kB2000,
    PollByte_AM_kB3000,
    PollByte_AM_kBinfinity,
    PollByte_AM_spare1,
    PollByte_AM_r14_kB1,

    PollByte_AM_r14_kB2,
    PollByte_AM_r14_kB5,
    PollByte_AM_r14_kB8,
    PollByte_AM_r14_kB10,
    PollByte_AM_r14_kB15,
    PollByte_AM_r14_kB3500,
    PollByte_AM_r14_kB4000,
    PollByte_AM_r14_kB4500,
    PollByte_AM_r14_kB5000,
    PollByte_AM_r14_kB5500,
    PollByte_AM_r14_kB6000,
    PollByte_AM_r14_kB6500,
    PollByte_AM_r14_kB7000,
    PollByte_AM_r14_kB7500,
    PollByte_AM_r14_kB8000,
    PollByte_AM_r14_kB9000,
    PollByte_AM_r14_kB10000,
    PollByte_AM_r14_kB11000,
    PollByte_AM_r14_kB12000,
    PollByte_AM_r14_kB13000,
    PollByte_AM_r14_kB14000,
    PollByte_AM_r14_kB15000,
    PollByte_AM_r14_kB16000,
    PollByte_AM_r14_kB17000,
    PollByte_AM_r14_kB18000,
    PollByte_AM_r14_kB19000,
    PollByte_AM_r14_kB20000,
    PollByte_AM_r14_kB25000,
    PollByte_AM_r14_kB30000,
    PollByte_AM_r14_kB35000,
    PollByte_AM_r14_kB40000
}PollByteAm;

typedef enum RlcPdcpSnSize_Tag
{
    PDCP_SN_7BIT,
    PDCP_SN_12BIT,
    PDCP_SN_15BIT,//PDCP_Config_pdcp_SN_Size_v1130_len15bits
    PDCP_SN_18BIT,//PDCP_Config_pdcp_SN_Size_v1310_len18bits

}RlcPdcpSnSize;

typedef enum Msg3CqiReportTypeTag
{
    NO_MEASUREMENTS          = 0,   //no CQI measurements is needed
    CQI_NPDCCH               = 1,   //insert 4 bits CQI report in MSG3
    CQI_NPDCCH_SHORT         = 2,   //insert 2 bits CQI report in MSG3
}Msg3CqiReportType;

typedef enum UseEdtTypeTag
{
    USE_CP_EDT               = 1,
    USE_UP_EDT               = 2,
}UseEdtType;

/*********************************************************************************
 * Structs
*********************************************************************************/
/********************************************************************************
 * RRC->UP
*********************************************************************************/
typedef struct RohcTag
{
    UINT16  maxCID;
    UINT8   profiles;  //bit indicate whether enable of PDCP_Config_NB_r13_profiles_r13
    UINT8   reserved0;
}Rohc;

typedef enum SNFieldLengthTag
{
    SNFieldLength_size5,
    SNFieldLength_size10
}SNFieldLength;

typedef enum PrioritisedBitRateTag
{
    PrioritisedBitRate_kBps0,
    PrioritisedBitRate_kBps8,
    PrioritisedBitRate_kBps16,
    PrioritisedBitRate_kBps32,
    PrioritisedBitRate_kBps64,
    PrioritisedBitRate_kBps128,
    PrioritisedBitRate_kBps256,
    PrioritisedBitRate_infinity,
    PrioritisedBitRate_kBps512_v1020,
    PrioritisedBitRate_kBps1024_v1020,
    PrioritisedBitRate_kBps2048_v1020,
    PrioritisedBitRate_spare5,
    PrioritisedBitRate_spare4,
    PrioritisedBitRate_spare3,
    PrioritisedBitRate_spare2,
    PrioritisedBitRate_spare1
}PrioritisedBitRate;

typedef enum BucketSizeDurationTag
{
    BucketSizeDuration_ms50,
    BucketSizeDuration_ms100,
    BucketSizeDuration_ms150,
    BucketSizeDuration_ms300,
    BucketSizeDuration_ms500,
    BucketSizeDuration_ms1000,
    BucketSizeDuration_spare2,
    BucketSizeDuration_spare1
}BucketSizeDuration;

typedef enum BitRateQueryProhibitTimerTag
{
    BitRateQueryProhibitTimer_r14_s0,
    BitRateQueryProhibitTimer_r14_s0dot4,
    BitRateQueryProhibitTimer_r14_s0dot8,
    BitRateQueryProhibitTimer_r14_s1dot6,
    BitRateQueryProhibitTimer_r14_s3,
    BitRateQueryProhibitTimer_r14_s6,
    BitRateQueryProhibitTimer_r14_s12,
    BitRateQueryProhibitTimer_r14_s30
}BitRateQueryProhibitTimer;


typedef struct PdcpConfigTag
{
    /*
     * For NB
     *  PDCPConfigDiscardTimer_NB, indicate index PDCPConfigDiscardTimer(PDCP_Config_NB_r13_discardTimer_r13)
     * For CAT
     *  PDCPConfigDiscardTimer(PDCP_Config_discardTimer)
    */
    UINT8   discardTimer;

    BOOL    headerCompressionUsed;
    BOOL    continueROHC;       //indicated if the drb-ContinueROHC is included in RrcConnectionResume
    UINT8   rsvd0;


    Rohc    rohc;
}PdcpConfig;    //12 bytes


typedef struct RlcAmConfig_Tag
{
    /****************************** UL-AM-RLC *********************************/

    /*
     * For NB:
     *  ignore "pollPDU" & "pollByte" & "pollPDUv1310" & "pollByter14", ERRC all set to 0
     * For Cat:
     *  PollPDU: used to backup the value of: "UL-AM-RLC->pollPDU", in case of when "RLC-Config-v1310->pollPDU-v1310" is released
     *  pollPDUv1310: "RLC-Config-v1310->pollPDU-v1310", if not configed, set to the backup value: "UL-AM-RLC->pollPDU",
     *                So RLC layer only need to use this value.
     *  PollByte & PollByte-r14
     *   Same note as "pollPDU", RLC layer only need to use the "pollByter14" value
     *
    */
    UINT8           pollPDU;        //PollPduAm
    UINT8           pollByte;       //PollByteAm

    UINT8           pollPDUv1310;   //PollPduAm
    UINT8           pollByter14;     //PollByteAm

    /*
     * For NB:
     *  PollRetransmit, indicate value of PollRetransmit_NB(T_PollRetransmit_NB_r13)
     * For Cat:
     *  UL-AM-RLC -> T-PollRetransmit, only used for AM mode, indicate value of PollRetransmit
     *
    */
    UINT16          tPollRetransmit : 6;


    /*
     * For NB:
     *  UlAmRlcMaxRetxThreshold, indicate value of UlAmRlcMaxRetxThreshold(UL_AM_RLC_NB_r13_maxRetxThreshold_r13)
     * For CAT:
     *  UL-AM-RLC -> maxRetxThreshold, ENUMERATED {t1, t2, t3, t4, t6, t8, t16, t32}
     *  UlAmRlcMaxRetxThreshold
    */
    UINT16          maxRetxThreshold : 4;
    /*
     * RLC-Config-v1250 -> ul-extended-RLC-LI-Field-r12
     * RLC-Config-v1250 -> dl-extended-RLC-LI-Field-r12
     *  Indicates the RLC LI field size. Value TRUE means that 15 bit LI length shall be used,
     *   otherwise 11 bit LI length shall be used.
    */
    UINT16          ulExtLI : 1;
    UINT16          dlExtLI : 1;

    /*
     * RLC-Config-v1310 -> ul-extended-RLC-AM-SN-r13
     * RLC-Config-v1310 -> dl-extended-RLC-AM-SN-r13
     *  Indicates whether or not the UE shall use the exteneded SN and SO length for AM bearer. Value TRUE means that 16
     *   bit SN length and 16 bit SO length shall be used, otherwise 10 bit SN length and 15 bit SO length shall be used
    */
    UINT16          ulExtSn : 1;
    UINT16          dlExtSn : 1;

    /*
     * DL_AM_RLC_NB_r13 -> enableStatusReportSN_Gap_r13
     * Only valid for NB
    */
    UINT16          enableStatusReportSNGap : 1;

    UINT16          rsvd : 1;

    /****************************** DL-AM-RLC *********************************/
    /*
     * For NB:
     *  index of T_Reordering, if not configed set to 0
     * For Cat:
     *  index of T_Reordering
    */
    UINT8           tReordering;        //Reordering

    /*
     * For NB:
     *  useless, set to 0
     * For CAT
     *  index of xxxxx, - an enum here - TBD
    */
    UINT8           tStatusProhibit;        //StatusProhibit
}RlcAmConfig;   // 8 bytes

typedef struct RlcUmBiDirConfig_Tag
{
    /*****************************UL-UM-RLC**********************************/
    /*
     * For NB (R15)
     *  set to 0
     * For CAT
     *  index of "SN-FieldLength ::= ENUMERATED {size5, size10}", - SNFieldLength
    */
    UINT8           ulSnFieldLen;

    /*****************************DL-UM-RLC**********************************/
    /*
     * For NB (R15)
     *  set to 0
     * For CAT
     *  index of "SN-FieldLength ::= ENUMERATED {size5, size10}", - SNFieldLength
    */
    UINT8           dlSnFieldLen;

    /*
     * For NB (R15):
     *  index of T_Reordering, if not configed set to 0
     * For Cat:
     *  index of T_Reordering
    */
    UINT8           tReordering;   //Reordering

    UINT8           rsvd;
}RlcUmBiDirConfig;

typedef struct RlcUmUniDirUlConfig_Tag
{
    /*****************************UL-UM-RLC**********************************/
    /*
     * For NB (R15)
     *  set to 0
     * For CAT
     *  index of "SN-FieldLength ::= ENUMERATED {size5, size10}", - SNFieldLength
    */
    UINT8           ulSnFieldLen;

    UINT8           rsvd0;
    UINT16          rsvd1;
}RlcUmUniDirUlConfig;

typedef struct RlcUmUniDirDlConfig_Tag
{
    /*****************************DL-UM-RLC**********************************/
    /*
     * For NB (R15)
     *  set to 0
     * For CAT
     *  index of "SN-FieldLength ::= ENUMERATED {size5, size10}", - SNFieldLength
    */
    UINT8           dlSnFieldLen;

    /*
     * For NB (R15):
     *  index of T_Reordering, if not configed set to 0
     * For Cat:
     *  index of T_Reordering
    */
    UINT8           tReordering;  //Reordering

    UINT16          rsvd;
}RlcUmUniDirDlConfig;

typedef enum RlcConfigModeType_Enum
{
    RLC_CONFIG_AM_MODE = 0,
    RLC_CONFIG_UM_BI_DIR_MODE,
    RLC_CONFIG_UM_UNI_DIR_UL_MODE,
    RLC_CONFIG_UM_UNI_DIR_DL_MODE
}RlcConfigModeType;

typedef union RlcConfig_Tag
{
    RlcAmConfig     amCfg;
    RlcUmBiDirConfig    umCfg;
    RlcUmUniDirUlConfig umUlCfg;
    RlcUmUniDirDlConfig umDlCfg;
}RlcConfig;

typedef struct LogicalCHConfigTag
{
    BOOL    priorityPresent;
    UINT8   priority;           /*1..16*/
    BOOL    logicalChannelSRProhibit;
    UINT8   reserved0;

}LogicalCHConfig;   //12 bytes

typedef struct DrbInfoTag
{
    UINT8       type;           //UpConfigType, 0~6 indicate: not change, setup, setup_resume, modify, releasse, release_suspend, invalid
    UINT8       epsBearerIdentity;
    UINT8       drbIdentity;    // 1..32
    UINT8       logicIdentity : 4;  // 3..10, in fact 3 should not be used for DRB
    UINT8       rlcCfgMode : 4;     //RlcConfigModeType

    PdcpConfig  pdcpConfig;     //12 bytes
    RlcConfig   rlcConfig;      //8 bytes
    LogicalCHConfig    logicConfig; //12 bytes
}DrbInfo;   //36 bytes

typedef struct SrbInfoTag
{
    UINT8       type;           //UpConfigType, 0~6 indicate: not change, setup, setup_resume, modify, releasse, release_suspend, invalid
    UINT8       logicIdentity;  //SRB1: 1, SRB2: 2, SRB1bis: 3
    //UINT16      rsvd;
    UINT8       rlcCfgMode;     //RlcConfigModeType
    UINT8       rsvd;

    RlcConfig       rlcConfig;  // 8 bytes
    LogicalCHConfig    logicConfig; //12 bytes
}SrbInfo;   //24 bytes

typedef struct LogicalChannelSrProhibitTimerTag
{
    UINT8       type; //UpConfigType, 0~6 indicate: not change, setup, setup_resume, modify, releasse, release_suspend, invalid
    UINT8       value;  // index of MAC_MainConfig_NB_r13_logicalChannelSR_ProhibitTimer_r13
    //UINT16      reserved0;
}LogicalChannelSrProhibitTimer;

/*
 * SIGID: SIG_CEUP_CONFIG_REQ
*/
typedef struct CeupConfigReqTag
{
    //for NB-IOT, index 0 - for SRB1bis, index 1 for SRB1
    //for Cat, index 0 - for SRB1, index 1 for SRB2
    SrbInfo     srbInfo[MAX_SRB];       //don't contain SRB0 info, 24*2 = 48 bytes
    DrbInfo     drbInfo[MAX_DRB];       //36*11 = 396 bytes
    //LogicalChannelSrProhibitTimer   logicChProTimer;  // from MAC_MainConfig_NB_r13
}CeupConfigReq; //444 bytes

/*
 * SIGID: SIG_CEMAC_MAIN_CONFIG_REQ
*/
typedef struct CemacMainConfigReqTag
{
    /*
     * logicalChannelSR-Config-r13
     *  from MAC_MainConfig_NB_r13, Need ON
    */
    UINT8       lcSrProTmrCfgType;  //UpConfigType, 0~6 indicate: not change, setup, setup_resume, modify, releasse, release_suspend, invalid

    /*
     * For NB mode:
     *  index of MAC_MainConfig_NB_r13_logicalChannelSR_ProhibitTimer_r13
     * For Cat mode:
     *  index of MAC-MainConfig -> sr-ProhibitTimer-r9 INTEGER (0..7),
     *    Value in number of SR period(s) of shortest SR period of any serving cell with PUCCH
    */
    UINT8       lcSrProTmrValue;    // index of MAC_MainConfig_NB_r13_logicalChannelSR_ProhibitTimer_r13

    /*
     * rai-Activation-r14
     *  Activation of release assistance indication (RAI), Need OR
    */
    BOOL        raiActivation;

    UINT8       reserved0;

}CemacMainConfigReq;

/*
 * SIGID: SIG_CEUP_REESTABLISH_REQ
*/
typedef struct CeupReestablishReqTag
{
    UINT8       lcNum;   //logic channel number which need to re-est
    UINT8       reserved0;
    UINT16      reserved1;
    UINT8       logicIdentity[MAX_SRB+MAX_DRB]; // only need to pass LCID to indicate which RB is reestablish
}CeupReestablishReq;

/*
 * SIGID: SIG_CEPDCP_CIPHER_INTEGRITY_CONFIG_REQ
*/
typedef struct CepdcpCipherAndIntegrityConfigReqTag
{
    UINT8       cipAlgo; //CipheringAlgorithm
    UINT8       intAlgo; //IntegrityAlgorithm
    //set TRUE --for SecurityModeCommand Procedure; set FALSE for such cases: RRC con re-establishment/RrcConnectionResume
    BOOL        bIgnoreNextSrbCipher;
    UINT8       reserved0;

    UINT8       rrcEncKey[NB_KEY_LENGTH];
    UINT8       upEncKey[NB_KEY_LENGTH];
    UINT8       rrcIntKey[NB_KEY_LENGTH];

}CepdcpCipherIntegrityConfigReq;

typedef struct IntCheckParmTag
{
    UINT8       rbId;
    UINT8       dir;
    UINT16      reserved0;
    UINT32      counter;
}IntCheckParm;

typedef struct CepdcpIntegrityCalcReqTag
{
    UINT8           intAlgo; //IntegrityAlgorithm
    UINT8           reserved0;
    UINT16          length;

    IntCheckParm    intParm;
    UINT8           rrcIntKey[NB_KEY_LENGTH];
    UINT8           *data_p;
}CepdcpIntegrityCalcReq;

/*
 * SIGID: SIG_CEUP_SUSPEND_REQ
*/
typedef struct CeupSuspendReqTag
{
    UINT8           lcNum;   //logic channel number which need to suspend
    UINT8           reserved0;
    UINT16          reserved1;

    UINT8           logicIdentity[MAX_SRB+MAX_DRB];
}CeupSuspendReq;

/*
 * SIGID: SIG_CEUP_RESUME_REQ
*/
typedef struct CeupResumeReqTag
{
    UINT8           lcNum;   //logic channel number which need to resume
    UINT8           reserved0;
    UINT16          reserved1;

    UINT8           logicIdentity[MAX_SRB+MAX_DRB];
}CeupResumeReq;


/******************************************************************************
 * CecpDataReq
 * SIGID: SIG_CECP_DATA_REQ
 * UL RRC PDU to PDCP
******************************************************************************/

typedef struct SrbRrcUlPduTag
{
    UINT16          totalByteLength;    /*indicate total byte length of RRC UL PDU (including RRC+NAS PDU)
                                          totalByteLength = (rrcPduBitLength+nasPduBitLength+7)/8 */
/************************************************
 * |<------- rrcPduBitLength----------->|
 * +------------------------------------+
 * |      RRC  PDU       |              |
 * +------------------------------------+
 *                       ^(insert NAS PDU at here)
 * |<-nasPduBitPosition->|
 *                       +-----------------------+
 *                       |        NAS  PDU       |
 *                       +-----------------------+
 *                       |<---nasPduBitLength--->|
 * example:
 *
 *   0   1   2   3   4   5   6   7
 * +---+---+---+---+---+---+---+---+
 * | 0   0   0   0   0   0   0   0 |    rrcPduBitLength = 8
 * +---+---+---+---+---+---+---+---+
 *          ^
 *          |nasPduBitPosition = 2
 *   0   1   2   3   4   5   6   7
 * +---+---+---+---+---+---+---+---+
 * | 1   1   1   1   1   1   1   1 |    nasPduBitLength = 8
 * +---+---+---+---+---+---+---+---+
 *
 *  in fact whole PDU : =>
 *   0   1   2   3   4   5   6   7   ....                        15
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * | 0   0   1   1   1   1   1   1   0   0   0   0   0   0   0   0 |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *
************************************************/
    UINT16          rrcPduBitLength;     /*indicate bit length of RRC PDU, aligned with 8*/
    UINT8           *rrcPdu_p;           /*pointer of RRC raw data after PER encode, which not including dedicatedInfoNAS
                                           dynmaic memory allocated by CERRC, free by UP after transmitted successfully */

    UINT16          nasPduBitLength;     /*indicate bit length of NAS PDU,
                                           0 means no NAS data need to transmit, otherwise should always be integral multiple of 8*/
    UINT16          nasPduBitPosition;   /*indicate the insert bit position, where UP inserts the NAS PDU into RRC PDU;
                                           nasPduBitPosition <= rrcPduBitLength, probable range (0..96), actually UINT8 should be enough;
                                           0 means there is no NAS PDU need to be inserted into RRC PDU */
    UINT8           *nasPdu_p;           /*pointer of NAS data,
                                           dynmaic memory allocated by NAS, free by UP after transmitted successfully;
                                           NAS PDU shoule be piggybacked in RRC PDU, if present, i.e. UP will combine RRC and NAS PDU together*/
}SrbRrcUlPdu;   //16 bytes


#define INVALID_RRC_PDU_ID  0x00
typedef struct CecpDataReqTag
{
    /*
     * This value is mandatory if confirmationRequired is TRUE;
     * This value is same as "Nas->nasMessageIndex", which range is: 1 ~ 5, 17~255;
    */
    UINT8           rrcPduId;
    UINT8           lcId;      //LogicalChannelId, SRB1: 1, SRB1bis: 3
    BOOL            cnfReqed;
    UINT8           dataRaiInfo;    /*DataRelAssistIndEnum, set to 0 if no NAS PDU is piggyback*/

    UINT8           tickType;       /* UlPduTickType, indicate the "sysTick" type */
    UINT8           reserved0;
    UINT16          reserved1;

    UINT32          sysTick;

    SrbRrcUlPdu     rrcPdu; //16 bytes
}CecpDataReq;   //28 bytes

/*
 * SIGID: SIG_CERLC_CONNECT_RELEASE_ACK_REQ
*/
typedef GosEmptySignal CerlcConnectReleaseAckReq;

/*
 * SIGID: SIG_CERLC_DEDICATED_RECONFIG_ACK_REQ
*/
//typedef GosEmptySignal CerlcDedicatedReconfigAckReq;
/*
 * SIGID: SIG_CEMAC_RESET_REQ
*/
typedef struct CemacResetReqTag
{
    UINT8       reason; //MacResetReason
    UINT8       reserved0;
    UINT8       reserved1;
    UINT8       reserved2;
}CemacResetReq;

/******************************************************************************
 * CemacCcchDataReq
 * UL CCCH data (SRB0), trigger MAC to do RA
 * SIGID: SIG_CEMAC_CCCH_DATA_REQ
******************************************************************************/
typedef struct CemacCcchDataReqTag
{
    // indicate the length of encoded rrcSetupComplete. RRC should include it if ccch message is rrcConnectionRequest
    BOOL        msg5LenPresent;
    UINT8       ccchLen;        //Byte length of CCCH data, should be a fixed value: 9 bytes
    UINT16      msg5Len;

    UINT8       cqiReportType;  //Msg3CqiReportType
    UINT8       cqiReportBitOffset; //The bit offset indicates where to insert the CQI result in MSG3, Range(47..68)
    UINT8       reserved0;
    UINT8       reserved1;

    UINT8       *data; //dynmaic memory,if using cp-edt, encoding data is in rrcPdu, including NAS
}CemacCcchDataReq;

/*
 * SIGID: SIG_CEMAC_SCHEDULE_REQ_RELEASE_IND
*/
typedef GosEmptySignal  CemacScheduleReqReleaseInd;

/*
 * SIG_CCM_GET_L2_STATUS_REQ
*/
typedef GosEmptySignal  CcmGetL2StatusReq;

/*
 * SIG_CCM_L2_STATIS_OPER_REQ
*/
typedef struct CcmL2StatisOperReq_Tag
{
    UINT8       statisReqType;  //CcmStatisReqType
    UINT8       rsvd0;
    UINT16      rsvd1;
}CcmL2StatisOperReq;


/*
 * SIG_CCM_L2_NO_MORE_PS_DATA_REQ
*/
typedef GosEmptySignal  CcmL2NoMorePsDataReq;

typedef GosEmptySignal CePdcpDlPkgContinueReq;

/******************************************************************************
 ******************************************************************************
 * CERRC/CEMM/CESM/CESMS -> DR
 ******************************************************************************
******************************************************************************/

/*
 * As DR and L2 just in the same task, we don't need these new signals to notify DRB info to DR mode
*/
#if 0
/*
 * CERRC -> DR, notify which DRB is setuped
 * SIGID: SIG_CEDR_DRB_SETUP_IND
*/
typedef struct CedrDrbSetupInd_Tag
{
    struct {
        BOOL    bSetup;
        UINT8   drbId;  //DRB-Identity, INTEGER (1..32)
        UINT8   epsId;  //eps-BearerIdentity INTEGER (0..15)
        UINT8   lcid;   //logical channel ID
    } drbCfg[NB_DRB_NUM];
}CedrDrbSetupInd;

/*
 * CERRC -> DR, notify which DRB is released
 * SIGID: SIG_CEDR_DRB_RELEASE_IND
*/
typedef struct CedrDrbReleaseInd_Tag
{
    UINT8   drbId[NB_DRB_NUM];  // 0 is invalid value
    //UINT16  reserved0;
    BOOL    bSuspend;   //whether the RRC is suspended (RRCRelase with suspended indication)
    UINT8   reserved;
}CedrDrbReleaseInd;

/*
 * CERRC -> DR, notify DRB is suspended,
 * This signal used for ERRC RE-EST procedure, and for CERRC suspend/resume procedure, suggest to release the DRB
 * SIGID: SIG_CEDR_DRB_SUSPEND_IND
*/
typedef struct CedrDrbSuspendInd_Tag
{
    UINT8   drbId[NB_DRB_NUM];  // 0 is invalid value
    UINT16  reserved0;
}CedrDrbSuspendInd;


/*
 * CERRC -> DR, notify DRB is resumed,
 * This signal used for ERRC RE-EST procedure
 * SIGID: SIG_CEDR_DRB_RESUME_IND
*/
typedef struct CedrDrbResumeInd_Tag
{
    UINT8   drbId[NB_DRB_NUM];  // 0 is invalid value
    UINT16  reserved0;
}CedrDrbResumeInd;
#endif

/*
 * CERRC -> DR, notify the DR the DRB info when wake up from hibernate state,
 * For UP-OPT case, NW suspend the RRC connection, this signal used to notify the DR the DRB info which suspended in RRC side
 * SIGID: SIG_CEDR_POWER_RECOVER_DRB_INFO_IND
*/
typedef struct CedrPowerRecoverDrbInfoInd_Tag
{
    BOOL    bSuspend;   //whether the RRC is suspended (RRCRelase with suspended indication)
    UINT8   reserved0;
    UINT16  reserved1;

    UINT8   suspendDrbId[NB_DRB_NUM];
    UINT8   suspendEpsId[NB_DRB_NUM];
}CedrPowerRecoverDrbInfoInd;


/*
 * CESM(CEMM) -> DR, notify DR CP OPT or UP OPT
 * SIGID: SIG_CEDR_FEATURE_SUPPORT_IND
*/
typedef struct CedrFeatureSupportInd_Tag
{
    UINT8   ueSuptOptType;//UE supported CIOT OPT type, CemmCiotOptTypeEnum: 1 & 3
    UINT8   uePreferOpt;  // CemmCiotOptTypeEnum: 0, 1, 2
    UINT8   nwSupCiotOpt;   //CemmCiotOptTypeEnum
    UINT8   reserved;
}CedrFeatureSupportInd;

typedef struct CeDrBearerDefinedInd_Tag
{
    UINT32   cid;
    BOOL     defined;
} CeDrBearerDefinedInd;
/*
 * 23.401, 4.7.7.3
 * The APN Uplink Rate Control applies to data PDUs sent on that APN by
 *  either Data Radio Bearers (S1-U) or Signalling Radio Bearers (NAS Data PDUs).
 * Note: if not configured, "CeDrApnRateCtrlInfo->present" = FALSE
*/
typedef enum CeDrApnRateCtrlUlTimeUnit_enum
{
    CE_DR_APN_RATE_UNRESTRICTED = 0,
    CE_DR_APN_RATE_MINUTE = 1,
    CE_DR_APN_RATE_HOUR   = 2,
    CE_DR_APN_RATE_DAY    = 3,
    CE_DR_APN_RATE_WEEK   = 4
}CeDrApnRateCtrlUlTimeUnit;

/*
 * 0 Additional exception reports at maximum rate reached are not allowed
 * 1 Additional exception reports at maximum rate reached are allowed
*/
#define CE_DR_APN_RATE_CTRL_EXCEPTION_DATA_NOT_ALLOWED  0
#define CE_DR_APN_RATE_CTRL_EXCEPTION_DATA_ALLOWED      1

typedef struct CeDrApnRateCtrlInfo_Tag
{
    UINT32  present     : 1; //whether APN RATE CTRL configured
    UINT32  reserved    : 3;
    UINT32  aer         : 1; //Additional exception reports
    UINT32  timeUnit    : 3;   //CeDrApnRateCtrlUlTimeUnit
    UINT32  maxUlRate   : 24;
}CeDrApnRateCtrlInfo;

typedef struct CeDrApnExceptCtrlInfo_Tag
{
    UINT32  present     : 1; //whether APN RATE CTRL configured
    UINT32  reserved0   : 4;
    UINT32  timeUnit    : 3;   //CeDrApnRateCtrlUlTimeUnit
    UINT32  reserved1   : 8;
    UINT32  maxUlRate   : 16;
}CeDrApnExceptCtrlInfo;

typedef struct CeDrRohcInfo_Tag
{
    BOOL     present;    //whether rohc configured
    UINT8    profiles;
    UINT16   maxCid;
}CeDrRohcInfo;

/*
 * CESM -> DR, notify DR EPS bearer activated indication
 * SIGID: SIG_CEDR_BEARER_ACTIVATE_IND
*/
typedef struct CedrBearerActivateInd_Tag
{
    UINT8   epsId;
    BOOL    bDedicated;
    UINT8   linkedEpsId;    // valid when "bDedicated" == TRUE
    BOOL    cpOnlyInd;

    UINT8   cid;
    UINT8   ipType;     //PdnType
    BOOL    mtuSizePresent;
    UINT8   reserved0;

    /*
     * 24.301, 9.9.4.28
     * 1: The purpose of the Serving PLMN rate control information element is to indicate the maximum number of uplink ESM
     *     DATA TRANSPORT messages including User data container IEs the UE is allowed to send via a PDN connection per
     *     6 minute interval
     * 2: The Serving PLMN rate control value is an integer equal to or higher than 10;
     * 3: FFFFH indicates that the maximum number send per 6 minute interval is not restricted;
    */
    UINT16  plmnRateCtrl;

    UINT16  mtuSize;

    /*
     * 24.008; 10.5.6.3.2 APN rate control parameters
    */
    CeDrApnRateCtrlInfo apnRateCtrl;

    /*
     * 24.008; 10.5.6.3.3 Additional APN rate control parameters for exception data
    */
    CeDrApnExceptCtrlInfo apnExceptRateCtrl;

    /*
     * ROHC info
     * if not configured/not modified, set the "rohcInfo".present to FALSE, then CEDR just use the old value
    */
    CeDrRohcInfo    rohcInfo;
    /*
     * For dedicated bearer, maybe configed the TFT
    */
    PacketFilterList *pfList;
}CedrBearerActivateInd;



/*
 * CESM -> DR, notify DR EPS bearer activated indication
 * SIGID: SIG_CEDR_BEARER_MODIFY_IND
*/
typedef struct CedrBearerModifyInd_Tag
{
    UINT8   epsId;
    BOOL    mtuSizePresent;
    UINT16  mtuSize;

    /*
     * ROHC info
     * if not configured/not modified, set the "rohcInfo".present to FALSE, then CEDR just use the old value
    */

    CeDrRohcInfo    rohcInfo;

    /*
     * Use dynamic memory
     * ESM just config the CUR TFT paramters to DR, if no TFT/TFT all removed, set PNULL
    */
    PacketFilterList *pfList;

    /*
     * APN control rate
     * if not configured/not modified, set the "apnRateCtrl".present to FALSE, then CEDR just use the old value
    */
    CeDrApnRateCtrlInfo apnRateCtrl;

    /*
     * 24.008; 10.5.6.3.3 Additional APN rate control parameters for exception data
     * if not configured/not modified, set the "apnExceptRateCtrl".present to FALSE, then CEDR just use the old value
    */
    CeDrApnExceptCtrlInfo apnExceptRateCtrl;

}CedrBearerModifyInd;


/*
 * CESM -> DR
 * SIGID: SIG_CEDR_BEARER_DEACTIVATE_IND
*/
typedef struct CedrBearerDeactivateInd_Tag
{
    UINT8   epsId;
    UINT8   reserved0;
    UINT16  reserved1;
}CedrBearerDeactivateInd;

/*
 * CESM -> DR
 * SIGID: SIG_CEDR_BEARER_SUSPEND_IND
*/
typedef struct  CedrBearerSuspendInd_Tag
{
    BOOL   expDataSuspendStatus;
    BOOL   upDataSuspendStatus;
    UINT16  reserved1;

}CedrBearerSuspendInd;

/*
 * CESM -> DR
 * SIGID: SIG_CEDR_BEARER_RESUME_IND
*/
typedef GosEmptySignal  CedrBearerResumeInd;

/*
 * CEMM -> DR
 * SIGID: SIG_CEMM_DR_REESTABLISH_RSP
*/
typedef struct CemmDrReestablishRsp_Tag
{
    BOOL    bSucc;
    UINT8   reserved0;
    UINT16  reserved1;
}CemmDrReestablishRsp;

/*
 * CEMM -> DR
 * CEMM notify DR that CEMM status is right to send "service request" via "CemmDrReestablishReq"
 * SIGID: SIG_CEMM_DR_SERVICE_AVAILABLE_IND
*/
typedef GosEmptySignal CemmDrServiceAvailableInd;

/*
 * CESMS -> DR
 * SIGID: SIG_CEDR_SMS_TEST_LOOP_DATA_REQ
*/
typedef struct CeDrSmsTestLoopDataReq_Tag
{
    UINT8       rpduLen;
    UINT8       reserved0;
    UINT16      reserved1;
    UINT8      *rpduInfo;
}CeDrSmsTestLoopDataReq;


/*
 * LWIP/ATCMD/Platform -> DR
 * SIGID: SIG_CEDR_UL_DATA_REQ
 * If UL PDU need to pending, just forword it to CEDR, CEDR will pending it in bearer context
*/
typedef struct CedrUlDataReq_Tag
{
    UINT8   cid;   // PDP context ID (from AT CMD)
    UINT8   reserved0;
    UINT16  totalLen;
#ifdef RTE_PPP_EN
    UINT16  shortTotalLen;
    UINT16  reserved1;
	UlPduInfo *pShortHdr;
    UlPduInfo *pShortTailer;
#endif
    UlPduInfo *pHdr;
    UlPduInfo *pTailer;
}CedrUlDataReq;

/*
 * LWIP/ATCMD/Platform -> CEPDCP
 * SIGID: CeupDataReq
 * Note: if CEDR API decide the UL PDU need to via user plane, just forword it to CEPDCP directly
*/
typedef struct CeupDataReq_Tag
{
    UINT8   lcid;   // logical channel ID (MAC layer)
    UINT8   cid;    //VS : To maintain PKT stats on per bearer level
    UINT16      totalLen;       /* total pkg size in: "pHdr" and "pTailer" list */
#ifdef RTE_PPP_EN 
    UINT16      shortTotalLen;  /* total pkg size in: "pShortHdr" and "pShortTailer" list */
    UINT16      reserved0;
	UlPduInfo *pShortHdr;
    UlPduInfo *pShortTailer;
#endif	
    UlPduInfo *pHdr;
    UlPduInfo *pTailer;
}CeupDataReq;


/*
 * UE test loop mode type enum
*/
typedef enum CeUeTestLoopMode_enum
{
    CE_UE_TEST_LOOP_MODE_A = 0,
    CE_UE_TEST_LOOP_MODE_B = 1,
    // ... C, D, E, F not support
    CE_UE_TEST_LOOP_MODE_G = 6,
    CE_UE_TEST_LOOP_MODE_H = 7, // LOOP SMS RP-DATA
    CE_UE_TEST_LOOP_MODE_I = 8  // LOOP DATA filted by TFT
}CeUeTestLoopMode;

/*
 * CEMMTC -> CEDR
 * SIGID: SIG_CEDR_ACT_TEST_MODE_IND
 *  Activate UE test mode
*/
typedef struct CedrActTestModeInd_Tag
{
    UINT8   loopMode;   //CeUeTestLoopMode
    UINT8   reserved0;
    UINT16  reserved1;
}CedrActTestModeInd;

/*
 * CEMMTC -> CEDR
 * SIGID: SIG_CEDR_DEACT_TEST_MODE_IND
 *  DEACTIVATE TEST MODE
*/
typedef GosEmptySignal CedrDeactTestModeInd;

/*
 * CEMMTC -> CEDR
 * SIGID: SIG_CEDR_OPEN_TEST_MODE_IND
 *  OPEN UE TEST LOOP
*/
typedef GosEmptySignal CedrOpenTestModeInd;


/*
 * CEMMTC -> CEDR
 * SIGID: SIG_CEDR_CLOSE_TEST_MODE_IND
 *  CLOSE UE TEST LOOP
*/
typedef struct CedrTLModeASetupDrbInfo_Tag
{
    UINT16  ulPdcpSduBitSize;
    UINT8   drbId;
    UINT8   reserved0;
}CedrTLModeASetupDrbInfo;

#define TEST_LOOP_MODE_LOOPBACK_TO_EMM_MODE   0
#define TEST_LOOP_MODE_LOOPBACK_TO_UP_MODE    1

typedef struct CedrCloseTestModeInd_Tag
{
    UINT8   loopMode;   //CeUeTestLoopMode
    UINT8   lbDrbNum;   // number of LB DRB in "modeARbSetupList"
    UINT8   tDelay;     //value of T_delay_modeB timer 0..255 seconds, & value of T_delay_modeGH timer 0..255 seconds
                        // if not include, set to 0
    UINT8   modeGHLBMode : 1;   //mode GH, Uplink loopback operation mode
    UINT8   modeGHRepNum : 7;   //Number of repetitions of received content of received user data in downlink in uplink. Range 0..127

    CedrTLModeASetupDrbInfo modeARbSetupList[NB_DRB_NUM];  //LB setup list
}CedrCloseTestModeInd;  //12 bytes

/*
 * -> CEDR
 * UL data need to loop back, how to loop back just processed in DR when process this signal
*/
typedef struct CedrNasTestLoopDataReq_Tag
{
    UINT8   epsId;
    UINT8   reserved0;
    UINT16  reserved1;

    UlPduInfo *pHdr;
    UlPduInfo *pTailer;
}CedrNasTestLoopDataReq;


/*
 * -> CEDR
 * UL data need to loop back, how to loop back just processed in DR when process this signal
 * Loopback data received from PDCP (DRB), and loopback to UL PDCP
 * This signal is created in ISR: SIG_CEDR_PDCP_TEST_LOOP_DATA_REQ_ISR
*/
typedef struct CedrPdcpTestLoopDataReq_Tag
{
    UINT8   epsId;
    UINT8   reserved0;
    UINT16  reserved1;

    // which data need to loopback
    DlPduBlock *pLBBlockHdr;
}CedrPdcpTestLoopDataReq;   // 8 bytes


/*
 * SIG_CEDR_PDCP_DL_NON_IP_DATA_IND_ISR
*/
typedef struct CedrPdcpDlNonIpDataIndIsr_Tag
{
    UINT8   epsId;
    UINT8   reserved0;
    UINT16  reserved1;

    // which data need to loopback
    DlPduBlock *pNonIpBlockHdr;   //using dynamic memory
}CedrPdcpDlNonIpDataIndIsr;

/*
 * SIG_CEDR_PS_DATA_PLANE_TRANS_REQ
 *  change Data plane
*/
typedef struct CedrPsDataPlaneTransReq_Tag
{
    BOOL    bViaUp; //if not via UP, just means via CP

    UINT8   reserved0;
    UINT16  reserved1;
}CedrPsDataPlaneTransReq;

/*
 * SIG_CCM_CEDR_PKT_STATS_REQ 
 * Pkt Stats REq for Each bearer
 */
typedef struct CcmCedrPktStatsReq_Tag
{
   UINT8 cid;
}CcmCedrPktStatsReq;

/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/*
 * CEDR API, called by CESM
 * One DL pkg memory.
 * Maybe call LWIP API: PsifAllocDlIpPkgBlockMem()
 * The memory allocated in LWIP side:
 * +-----------------+--------------------------+--------------------------+
 * | pbuf (16 bytes) |   DlPduBlock (12 bytes)  |      ip pkg (len)        |
 * +-----------------+--------------------------+--------------------------+
 *                   ^                          ^
 *                   | used in DR               | used in CESM
*/
UINT8* CedrAllocDlCpDataMem(UINT8 epsId, UINT16 length);

/*
 * CEDR API, called by CESM,
 * DL Control Plane data
*/
void CedrDlCtrlPlaneDataInd(UINT8 epsId, UINT16 length, UINT8 *ptr);

/*
 * CEDR API, called by other module (AT CMD SRC/LWIP/etc...)
 * UL one ip/non-ip Pkg
*/
BOOL CedrOneUlPkgDataReq(UINT8 cid, UINT16 length, UINT8 *ptr, UINT8 memType, BOOL bExceptData, UINT8 esmRai, BOOL mustViaCp);


/*
 * CEDR API,
 * UL ip/non-ip PDU list
*/
void CedrUlPkgListDataReq(UINT8 cid, UINT16 totalLen, UlPduInfo *pHdr, UlPduInfo *pTailer);


/*
 * CEDR API
 * Whether UL PDU is high water
*/
BOOL CedrUlIsPduHighWater(void);


/*
 * CE PDCP API, software to calc the EIAX MACI
*/
void CalcMacIWithEiaX(IntegrityAlgorithm eiaAlg, UINT8 *pKey, UINT32 count, UINT8 bearer,
                      UINT8 dir, UINT16 bitLen, UINT8 *pData, UINT8 *pOutMacI);

/*
 * CE PDCP API, software to decipher/integrity checking DL SRB PDCP PDU
*/
BOOL CePdcpDlPduSoftEeaThenEia(CipheringAlgorithm eeaAlg,
                               IntegrityAlgorithm eiaAlg,
                               UINT32   count,
                               UINT8    bearer,
                               UINT8    dir,
                               UINT16   bitLen,
                               UINT8    *pInData,
                               UINT8    *pOutData);

/*
 * CE DR API, any UL data pkg pending to send
*/
BOOL CedrAnySuspendULPendingData(void);


//VS NIDD: CEDR API for informing Socket Status of NIDD-LwM2M cid(s)
void CedrNIDDCidSockStatusProc(UINT8 cid, UINT8 sockStatus);

#endif

