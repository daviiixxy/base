#ifndef __MW_CONFIG_H__
#define __MW_CONFIG_H__
/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    mw_config.h
 * Description:  middleware configuration header file
 * History:      Rev1.0   2019-04-10
 *
 ****************************************************************************/
#include "osasys.h"

#include "PhyAtCmdDebug.h"

#include "cms_def.h"
//#include "ps_sms_if.h"


/******************************************************************************
 *****************************************************************************
 * MARCO/MARCO
 *****************************************************************************
******************************************************************************/

/*
 * CMS/AT channel 0 is reserved for internal
*/
#define MID_WARE_USED_AT_CHAN_NUM   (CMS_CHAN_NUM-1)


#define MID_WARE_NVM_FILE_LATEST_VERSION    3
#define MID_WARE_NVM_FILE_NAME      "midwareconfig.nvm"

#define MID_WARE_DM_APPKEY_LEN      11
#define MID_WARE_DM_SECRET_LEN      33

#define MID_WARE_DM_PORT_LEN        12

#define MID_WARE_DM_TML_IMEI_LEN    18

#define MID_WARE_DM_PLMN_LEN        8

#define MID_WARE_DM_DEVICE_INFO_LEN     20
#define MID_WARE_DM_APP_INFO_LEN        20
#define MID_WARE_DM_MAC_LEN             19
#define MID_WARE_DM_ROM_LEN             19
#define MID_WARE_DM_RAM_LEN             19
#define MID_WARE_DM_CPU_LEN             19
#define MID_WARE_DM_OSSYSVER_LEN        32
#define MID_WARE_DM_SWVER_LEN           32
#define MID_WARE_DM_SWNAME_LEN          32
#define MID_WARE_DM_VOLTE_LEN           7
#define MID_WARE_DM_NET_TYPE_LEN        19
#define MID_WARE_DM_ACCOUNT_LEN         45
#define MID_WARE_DM_PHONE_NUM_LEN       19
#define MID_WARE_DM_LOCATION_LEN        20



#define MID_WARE_SIM_CCID_LEN       20
#define MID_WARE_DEFAULT_DNS_NUM    2
#define MID_WARE_IPV4_ADDR_LEN      4
#define MID_WARE_IPV6_ADDR_LEN      16

#define MID_WARE_MODEL_LEN          24   /*for autoreg model*/
#define MID_WARE_SWVER_LEN          24   /*for autoreg swver*/
#define MID_WARE_REGACK_LEN         16   /*for autoreg ack print*/

typedef enum MidWareATChanCfgEnum_Tag
{
    MID_WARE_AT_CHAN_ECHO_CFG,      //ATE0/ATE1
    MID_WARE_AT_CHAN_SUPPRESS_CFG,  //ATQ0/ATQ1
    MID_WARE_AT_CHAN_CREG_RPT_CFG,  //CmiMmCregModeEnum
    MID_WARE_AT_CHAN_CEREG_RPT_CFG, //CmiPsCeregModeEnum
    MID_WARE_AT_CHAN_EDRX_RPT_CFG,  //TRUE/FALSE
    MID_WARE_AT_CHAN_CIOT_OPT_RPT_CFG,  //CmiMmCiotReportModeEnum
    MID_WARE_AT_CHAN_CSCON_RPT_CFG,
    MID_WARE_AT_CHAN_SMS_MODE_CFG,  //PDU mode/TEXT mode
    MID_WARE_AT_CHAN_TIME_ZONE_REP_CFG, //CTZR
    MID_WARE_AT_CHAN_TIME_ZONE_UPD_CFG, //CTZU
    MID_WARE_AT_CHAN_CMEE_CFG,      //CMEE
    MID_WARE_AT_CHAN_ECCESQ_RPT_CFG,    //QCCESQ
    MID_WARE_AT_CHAN_CGEREP_MODE_CFG,   //CGEREP
    MID_WARE_AT_CHAN_PSM_RPT_CFG,     //QCPSMR
    MID_WARE_AT_CHAN_EMM_TIME_RPT_CFG,     //QCEMMTIME
    MID_WARE_AT_CHAN_PTW_EDRX_RPT_CFG,  //QCPTWEDRXP
    MID_WARE_AT_CHAN_ECPIN_STATE_RPT_CFG,  //QCPIN
    MID_WARE_AT_CHAN_ECPADDR_RPT_CFG,   //QCPADDR
    MID_WARE_AT_CHAN_ECPCFUN_RPT_CFG,   //QCPCFUN
    MID_WARE_AT_CHAN_ECLED_MODE_CFG,    //QCLEDMODE
    MID_WARE_AT_CHAN_ECPURC_HIB_RPT_CFG, //QCPURC HIB report
    MID_WARE_AT_CHAN_IPINFO_RPT_MODE_CFG,  //IPINFO
    MID_WARE_AT_CHAN_NITZ_TIME_ZONE_CFG,  //NITZ

    MID_WARE_AT_CHAN_CFG_MAX
}MidWareATChanCfgEnum;

typedef enum MidWareDMCfgEnum_Tag
{
    MID_WARE_AT_DM_MODE_CFG, //DM mode  0:no dm  1: has dm
    MID_WARE_AT_DM_LIFETIME_CFG, //DM lifetime unit:minute
    MID_WARE_AT_DM_APPKEY_CFG, //DM appkey string like "M100000364"
    MID_WARE_AT_DM_SECRET_CFG, //DM secret string like "j5MOg7I6456971aQN7z6Bl36Xk5wYA5Q"
    MID_WARE_AT_DM_TEST_CFG, //DM test mode 0:commercial platform  1:test platform


    MID_WARE_AT_DM_CFG_MAX
}MidWareDMCfgEnum;


//atChanConfig


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

typedef struct MidWareNvmHeader_Tag
{
    UINT16 fileBodySize; //file body size, not include size of header;
    UINT8  version;
    UINT8  checkSum;
}MidWareNvmHeader;


typedef struct MidWareDefaultDnsCfg_Tag
{
    UINT8   ipv4Dns[MID_WARE_DEFAULT_DNS_NUM][MID_WARE_IPV4_ADDR_LEN];
    UINT8   ipv6Dns[MID_WARE_DEFAULT_DNS_NUM][MID_WARE_IPV6_ADDR_LEN];
}MidWareDefaultDnsCfg;     //40 bytes

typedef struct MidWareDmConfig_old_v1_Tag
{
    UINT8   mode;        //DM mode  0:no dm  1: has dm
    UINT8   test;        //DM test mode 0:commercial platform  1:test platform
    UINT16  lifeTime;    //DM lifetime unit:minute
    CHAR    appKey[MID_WARE_DM_APPKEY_LEN];    //DM appkey string like "M100000364"
    CHAR    secret[MID_WARE_DM_SECRET_LEN];    //DM secret string like "j5MOg7I6456971aQN7z6Bl36Xk5wYA5Q"
}MidWareDmConfig_old_v1;   //48 bytes

typedef struct MidWareDmConfig_Tag
{
    UINT8   mode;        //DM mode  0:no dm  1: has dm
    UINT8   test;        //DM test mode 0:commercial platform  1:test platform

    CHAR    serverIP[MID_WARE_IPV6_ADDR_LEN];    //
    CHAR    serverPort[MID_WARE_DM_PORT_LEN];
    UINT32  lifeTime;    //DM lifetime unit:second

    CHAR    appKey[MID_WARE_DM_APPKEY_LEN];    //DM appkey string like "M100000364"
    CHAR    secret[MID_WARE_DM_SECRET_LEN];    //DM secret string like "j5MOg7I6456971aQN7z6Bl36Xk5wYA5Q"
    UINT8   ifType;        //
    CHAR    tmlIMEI[MID_WARE_DM_TML_IMEI_LEN];    //

    CHAR    PLMN1[MID_WARE_DM_PLMN_LEN];    //
    CHAR    PLMN2[MID_WARE_DM_PLMN_LEN];    //
    CHAR    PLMN3[MID_WARE_DM_PLMN_LEN];    //

    UINT8   queryOpt;        //
    UINT8   eraseOpt;        //
    UINT8   DMstate;        //

    //CHAR    deviceInfo[MID_WARE_DM_DEVICE_INFO_LEN];  //
    //CHAR    appInfo[MID_WARE_DM_APP_INFO_LEN];  //
    //CHAR    MAC[MID_WARE_DM_MAC_LEN];   //
    //CHAR    ROM[MID_WARE_DM_ROM_LEN];   //
    //CHAR    RAM[MID_WARE_DM_RAM_LEN];   //
    //CHAR    CPU[MID_WARE_DM_CPU_LEN];   //
    //CHAR    osSysVer[MID_WARE_DM_OSSYSVER_LEN]; //
    //CHAR    swVer[MID_WARE_DM_SWVER_LEN];   //
    //CHAR    swName[MID_WARE_DM_SWNAME_LEN]; //
    //CHAR    VoLTE[MID_WARE_DM_VOLTE_LEN];   //
    //CHAR    netType[MID_WARE_DM_NET_TYPE_LEN];  //
    CHAR    account[MID_WARE_DM_ACCOUNT_LEN];   //
    CHAR    phoneNum[MID_WARE_DM_PHONE_NUM_LEN];    //
    //CHAR    location[MID_WARE_DM_LOCATION_LEN]; //
}MidWareDmConfig;   //48 bytes

/*
 * SMS Text Mode Parameters, set by: AT+CSMP=[<fo>[,<vp>[,<pid>[,<dcs>]]]]
*/
typedef struct MidWareCSMPParam_Tag
{
    UINT8   fo;               // First octet +CSMP=
    UINT8   vp;               // Validity Period, this maybe a string type, - TBD
    UINT8   pid;              // Protocol Identifier
    UINT8   dcs;              // Data coding scheme
}MidWareCSMPParam;

typedef struct MidWareSetCSMPParam_Tag
{
    BOOL    foPresent;
    BOOL    vpPresent;
    BOOL    pidPresent;
    BOOL    dcsPresent;

    MidWareCSMPParam    csmpParam;
}MidWareSetCSMPParam;


/*
 * used for AT CMD channel
*/
typedef struct MidWareAtChanConfig_Tag
{
    UINT32  chanId           : 4;       //PSDecoderChann, currently, only one channel used for ATCMD: PS_CHANNEL_MODEM
    UINT32  echoValue        : 1;       //ATE0/ATE1, set whether need to echo each AT CMD REQ
    UINT32  suppressionValue : 1;       //ATQ0/ATQ1, whether suppress result code
    UINT32  cregRptMode      : 2;       //CmiMmCregModeEnum

    UINT32  ceregRptMode     : 3;       //CmiPsCeregModeEnum
    UINT32  needEdrxRpt      : 1;       //AT+CEDRXS, whether need to report EDRX value, when EDRX value changes
    UINT32  needCiotOptRpt   : 3;       //CmiMmCiotReportModeEnum
    UINT32  smsSendMode      : 1;       //+CMGF=[<n>] Pdu/Text mode, PsilSmsFormatMode

    UINT32  csconRptMode     : 2;       //+CSCON=[<n>], AtcCSCONRptLevel
    UINT32  cmeeMode         : 2;       //+CMEE, AtcCMEERetType
    UINT32  timeZoneRptMode  : 2;       //+CTZR, AtcCTZRRptValue
    UINT32  timeZoneUpdMode  : 1;       //+CTZU, AtcCTZUUpdateValue
    UINT32  cgerepMode       : 1;       //+CGEREP, AtcCGEREPMode

    UINT32  eccesqRptMode    : 2;       //$QCCESQ, AtcECCESQRptValue
    UINT32  ecpsmRptMode     : 1;       //$QCPSMR, AtcECPSMRValue
    UINT32  ecemmtimeRptMode : 3;       //$QCEMMTIME
    UINT32  ecPtwEdrxRpt     : 1;       //AT$QCPTWEDRXS, whether need to report PTW/EDRX value, when PTW/EDRX value changes
    UINT32  ecpinRptMode     : 1;       //$QCPIN,

    UINT32  ecpaddrRptMode   : 1;       //$QCPADDR
    UINT32  ecpcfunRptMode   : 1;       //$QCPCFUN
    UINT32  ecledMode        : 1;       //$QCLEDMODE
    UINT32  ecHibRptMode     : 1;       //$QCPURC=Hibnate,enable
    UINT32  ecipinfoRptMode    : 1;       //+IPINFO
    UINT32  ecTimeZoneUpdMode  : 1;       //+NITZ
    UINT32  rsvd               : 26;
//    UINT32  rsvd0            : 28;

    MidWareCSMPParam    textSmsParam;
}MidWareAtChanConfig;

typedef struct MidWareAtSocketConfig_Tag
{
    UINT16  publicDlBufferToalSize;
    UINT8   publicDlPkgNumMax;
    UINT8   mode;
}MidWareAtSocketConfig;

typedef struct MidWareRsvdConfig_Tag
{
    UINT32  reserved0;
    UINT32  reserved1;
    UINT32  reserved2;
    UINT32  reserved3;
    UINT32  reserved4;
    UINT32  reserved5;
    UINT32  reserved6;
    UINT32  reserved7;   
}MidWareRsvdConfig;


/*
 * Middle ware NVM file structure
*/
typedef struct MidWareNvmConfig_Tag
{
    /*
     * used for AT CMD
    */

    /*
     * AT channel NVM config
    */
    MidWareAtChanConfig     atChanConfig[MID_WARE_USED_AT_CHAN_NUM];

    /*
     * used for autoReg
    */
    struct {
        UINT32  autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   ccid[MID_WARE_SIM_CCID_LEN];  /* ccid */
        UINT8   model[MID_WARE_MODEL_LEN];  /* autoReg model */
        UINT8   swver[MID_WARE_SWVER_LEN];  /* autoReg swver */
        UINT8   autoRegAck[MID_WARE_REGACK_LEN];  /* autoReg ack */
    } autoRegConfig;    //36 bytes

    struct {
        UINT32  autoRegLastRegSuccTime;       /*autoRegLastRegSuccTime:  last register succ time*/
        UINT32  autoRegPastTime;       /*autoRegPastTime: time form last register succ time*/
        UINT32  autoRegRang;       /*autoRegRang*/
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCuccConfig;    //36 bytes

    struct {
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCtccConfig;    //36 bytes

    /*
     * used for CMS other sub-mode
    */
    MidWareDefaultDnsCfg    defaultDnsCfg;     //40 bytes

    /*
     * used for DM
    */
    MidWareDmConfig         dmConfig; //48 bytes

    /*
     * used for phy
     */
    PhyDebugAtCmdInfo       phyAtCmdContent;  //28 bytes

    /*
     * used for middleware sleep retention power on clear flag
    */
    #if 0
    struct {
        UINT32   timeSyncTriggered;//set when time sync trigger after power on(by NITZ or SNTP)
    } mwSleepRetenFlag;
    #endif
    UINT32      timeSyncTriggered  : 1;    //0-1, set 1 when time sync trigger after power on(by NITZ or SNTP), and clear (0) when power on
    UINT32      abupFotaEnableFlag : 1;     //0-1, 1---enable, 0---disable, default is 0
    UINT32      rsvd : 30;

    /*
     * used for EC socket public setting
    */
    MidWareAtSocketConfig   ecSocPubCfg;

    /*
     * OSA/UTC TIME info
    */
    OsaTimeTValue           timeSecs;
    MidWareRsvdConfig       mwReserved;
}MidWareNvmConfig;


/******************************************************************************
 *****************************************************************************
 * OLD backup version
 *****************************************************************************
******************************************************************************/

/*
 * used for AT CMD channel
*/
typedef struct MidWareAtChanConfig_v00_Tag
{
    UINT32  chanId           : 4;       //PSDecoderChann, currently, only one channel used for ATCMD: PS_CHANNEL_MODEM
    UINT32  echoValue        : 1;       //ATE0/ATE1, set whether need to echo each AT CMD REQ
    UINT32  suppressionValue : 1;       //ATQ0/ATQ1, whether suppress result code
    UINT32  cregRptMode      : 2;       //CmiMmCregModeEnum

    UINT32  ceregRptMode     : 3;       //CmiPsCeregModeEnum
    UINT32  needEdrxRpt      : 1;       //AT+CEDRXS, whether need to report EDRX value, when EDRX value changes
    UINT32  needCiotOptRpt   : 3;       //CmiMmCiotReportModeEnum
    UINT32  smsSendMode      : 1;       //+CMGF=[<n>] Pdu/Text mode, PsilSmsFormatMode

    UINT32  csconRptMode     : 2;       //+CSCON=[<n>], AtcCSCONRptLevel
    UINT32  cmeeMode         : 2;       //+CMEE, AtcCMEERetType
    UINT32  timeZoneRptMode  : 2;       //+CTZR, AtcCTZRRptValue
    UINT32  timeZoneUpdMode  : 1;       //+CTZU, AtcCTZUUpdateValue
    UINT32  cgerepMode       : 1;       //+CGEREP, AtcCGEREPMode

    UINT32  eccesqRptMode    : 2;       //$QCCESQ, AtcECCESQRptValue
    UINT32  ecpsmRptMode     : 1;       //$QCPSMR, AtcECPSMRValue
    UINT32  ecemmtimeRptMode : 3;       //$QCEMMTIME
    UINT32  ecPtwEdrxRpt     : 1;       //AT$QCPTWEDRXS, whether need to report PTW/EDRX value, when PTW/EDRX value changes
    UINT32  ecpinRptMode     : 1;       //$QCPIN,

    UINT32  ecpaddrRptMode   : 1;       //$QCPADDR
    UINT32  ecpcfunRptMode   : 1;       //$QCPCFUN
    UINT32  ecledMode        : 1;       //$QCLEDMODE
    UINT32  rsvd0            : 29;

    MidWareCSMPParam    textSmsParam;
}MidWareAtChanConfig_old_v0;

/*
 * Middle ware NVM file structure
*/
typedef struct MidWareNvmConfig_old_v00_Tag
{
    /*
     * used for AT CMD
    */

    /*
     * AT channel NVM config
    */
    MidWareAtChanConfig_old_v0     atChanConfig[MID_WARE_USED_AT_CHAN_NUM];

    /*
     * used for autoReg
    */
    struct {
        UINT32  autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   ccid[MID_WARE_SIM_CCID_LEN];  /* ccid */
        UINT8   model[MID_WARE_MODEL_LEN];  /* autoReg model */
        UINT8   swver[MID_WARE_SWVER_LEN];  /* autoReg swver */
        UINT8   autoRegAck[MID_WARE_REGACK_LEN];  /* autoReg ack */
    } autoRegConfig;    //36 bytes

    struct {
        UINT32  autoRegLastRegSuccTime;       /*autoRegLastRegSuccTime:  last register succ time*/
        UINT32  autoRegPastTime;       /*autoRegPastTime: time form last register succ time*/
        UINT32  autoRegRang;       /*autoRegRang*/
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCuccConfig;    //36 bytes

    struct {
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCtccConfig;    //36 bytes

    /*
     * used for CMS other sub-mode
    */
    MidWareDefaultDnsCfg    defaultDnsCfg;     //40 bytes

    /*
     * used for DM
    */
    MidWareDmConfig         dmConfig; //48 bytes

    /*
     * used for phy
     */
    PhyDebugAtCmdInfo       phyAtCmdContent;  //28 bytes

    /*
     * used for middleware sleep retention power on clear flag
    */
    struct {
        UINT32   timeSyncTriggered;//set when time sync trigger after power on(by NITZ or SNTP)
    } mwSleepRetenFlag;

    /*
    * used for EC socket public setting
    */
    MidWareAtSocketConfig ecSocPubCfg;

}MidWareNvmConfig_old_v00;

/*
 * Middle ware NVM file structure
*/
typedef struct MidWareNvmConfig_old_v01_Tag
{
    /*
     * used for AT CMD
    */

    /*
     * AT channel NVM config
    */
    MidWareAtChanConfig     atChanConfig[MID_WARE_USED_AT_CHAN_NUM];

    /*
     * used for autoReg
    */
    struct {
        UINT32  autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   ccid[MID_WARE_SIM_CCID_LEN];  /* ccid */
        UINT8   model[MID_WARE_MODEL_LEN];  /* autoReg model */
        UINT8   swver[MID_WARE_SWVER_LEN];  /* autoReg swver */
        UINT8   autoRegAck[MID_WARE_REGACK_LEN];  /* autoReg ack */
    } autoRegConfig;    //36 bytes

    struct {
        UINT32  autoRegLastRegSuccTime;       /*autoRegLastRegSuccTime:  last register succ time*/
        UINT32  autoRegPastTime;       /*autoRegPastTime: time form last register succ time*/
        UINT32  autoRegRang;       /*autoRegRang*/
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCuccConfig;    //36 bytes

    struct {
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCtccConfig;    //36 bytes

    /*
     * used for CMS other sub-mode
    */
    MidWareDefaultDnsCfg    defaultDnsCfg;     //40 bytes

    /*
     * used for DM
    */
    MidWareDmConfig_old_v1         dmConfig; //48 bytes

    /*
     * used for phy
     */
    PhyDebugAtCmdInfo       phyAtCmdContent;  //28 bytes

    /*
     * used for middleware sleep retention power on clear flag
    */
#if 0
    struct {
        UINT32   timeSyncTriggered;//set when time sync trigger after power on(by NITZ or SNTP)
    } mwSleepRetenFlag;
#endif
    UINT32      timeSyncTriggered : 1;    //0-1, set 1 when time sync trigger after power on(by NITZ or SNTP), and clear (0) when power on
    UINT32      rsvd : 31;

    /*
    * used for EC socket public setting
    */
    MidWareAtSocketConfig   ecSocPubCfg;

    /*
     * OSA/UTC TIME info
    */
    OsaTimeTValue           timeSecs;
}MidWareNvmConfig_old_v01;

typedef struct MidWareNvmConfig_old_v02_Tag
{
    /*
     * used for AT CMD
    */

    /*
     * AT channel NVM config
    */
    MidWareAtChanConfig     atChanConfig[MID_WARE_USED_AT_CHAN_NUM];

    /*
     * used for autoReg
    */
    struct {
        UINT32  autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   ccid[MID_WARE_SIM_CCID_LEN];  /* ccid */
        UINT8   model[MID_WARE_MODEL_LEN];  /* autoReg model */
        UINT8   swver[MID_WARE_SWVER_LEN];  /* autoReg swver */
        UINT8   autoRegAck[MID_WARE_REGACK_LEN];  /* autoReg ack */
    } autoRegConfig;    //36 bytes

    struct {
        UINT32  autoRegLastRegSuccTime;       /*autoRegLastRegSuccTime:  last register succ time*/
        UINT32  autoRegPastTime;       /*autoRegPastTime: time form last register succ time*/
        UINT32  autoRegRang;       /*autoRegRang*/
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCuccConfig;    //36 bytes

    struct {
        UINT8   autoRegEnableFlag;       /*autoRegEnableFlag  1:disable register 2: enable register*/
        UINT8   autoRegFlag;             /*autoRegFlag        1:no register  2: has register*/
    } autoRegCtccConfig;    //36 bytes

    /*
     * used for CMS other sub-mode
    */
    MidWareDefaultDnsCfg    defaultDnsCfg;     //40 bytes

    /*
     * used for DM
    */
    MidWareDmConfig         dmConfig; //48 bytes

    /*
     * used for phy
     */
    PhyDebugAtCmdInfo_old_v2       phyAtCmdContent;  //28 bytes

    /*
     * used for middleware sleep retention power on clear flag
    */
    #if 0
    struct {
        UINT32   timeSyncTriggered;//set when time sync trigger after power on(by NITZ or SNTP)
    } mwSleepRetenFlag;
    #endif
    UINT32      timeSyncTriggered  : 1;    //0-1, set 1 when time sync trigger after power on(by NITZ or SNTP), and clear (0) when power on
    UINT32      abupFotaEnableFlag : 1;     //0-1, 1---enable, 0---disable, default is 0
    UINT32      rsvd : 30;

    /*
     * used for EC socket public setting
    */
    MidWareAtSocketConfig   ecSocPubCfg;

    /*
     * OSA/UTC TIME info
    */
    OsaTimeTValue           timeSecs;
}MidWareNvmConfig_old_v02;


/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/

/*
 * load/read "midwareconfig.nvm" NVM file
*/
void mwLoadNvmConfig(void);

/*
 * save "midwareconfig.nvm" NVM file, or AON field
*/
void mwSaveAtChanConfig(void);

/*
 * get one AT channel config item value
*/
UINT32 mwGetAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum);

/*
 * set and save one AT channel config item value
*/
void mwSetAndSaveAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum, UINT32 value);

/*
 * set one AT channel config item value, but not write to flash, need call API: mwSaveNvmConfig()
 * used in case: if need to write several config values, in order to reduce times of write flash
*/
void mwSetAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum, UINT32 value, BOOL *bChanged);

/*
 * Get all csmp config value
*/
BOOL mwGetCsmpConfig(UINT8 chanId, MidWareCSMPParam *config);

/*
 *Restore gAtSmsMessage's value
*/
//void mwRestoreSmsInfo(void);

/*
 * Set and save all CSMP config value
*/
void mwSetAndSaveCsmpConfig(UINT8 chanId, MidWareSetCSMPParam *pSetCsmp);

/*
 * get all DM config item value
*/
void mwGetAllDMConfig(MidWareDmConfig* config);
/*
 * get DM config item value
*/
UINT8* mwGetDMConfigItemValue(MidWareDMCfgEnum cfgEnum);

/*
 * set and save DM config item value
*/
void mwSetAndSaveDMConfigItemValue(MidWareDMCfgEnum cfgEnum, UINT8* value);

UINT8 mwGetCmccAutoRegEnableFlag(void);

/*
 * set DM config item value, but not write to flash, need call API: mwSaveNvmConfig()
 * used in case: if need to write several config values, in order to reduce times of write flash
*/
void mwSetDMConfigItemValue(MidWareDMCfgEnum cfgEnum, UINT8* value, BOOL *bChanged);

UINT8 mwGetEcAutoRegEnableFlag(void);
void mwSetEcAutoRegEnableFlag(UINT8 autoReg);
UINT8 *mwGetEcAutoRegModel(void);
UINT8 mwSetEcAutoRegModel(UINT8 *model);
UINT8 *mwGetEcAutoRegSwver(void);
UINT8 mwSetEcAutoRegSwver(UINT8 *swver);
UINT8 *mwGetEcAutoRegAckPrint(void);
UINT8 mwSetEcAutoRegAckPrint(UINT8 *ack);
UINT8 mwGetCtccAutoRegEnableFlag(void);
void mwSetCtccAutoRegEnableFlag(UINT8 autoReg);
UINT8 mwGetCtccAutoRegFlag(void);
void mwSetCtccAutoRegFlag(UINT8 autoReg);

UINT8 mwGetCuccAutoRegEnableFlag(void);
void mwSetCuccAutoRegEnableFlag(UINT8 autoReg);
UINT8 mwGetCuccAutoRegFlag(void);
void mwSetCuccAutoRegFlag(UINT8 autoReg);
UINT32 mwGetCuccAutoRegLastRegTime(void);
void mwSetCuccAutoRegLastRegTime(UINT32 autoRegTime);
UINT32 mwGetCuccAutoRegPastTime(void);
void mwSetCuccAutoRegPastTime(UINT32 autoRegTime);
UINT32 mwGetCuccAutoRegRang(void);
void mwSetCuccAutoRegRang(UINT32 autoRegRangTime);
UINT32 mwGetTimeSyncFlag(void);
void mwSetTimeSyncFlag(UINT32 timeSyncTriggered);

void mwGetEcSocPublicConfig(UINT8 *mode, UINT8 *publicDlPkgNumMax, UINT16 *publicDlBufferToalSize);
UINT8 mwSetEcSocPublicConfig(UINT8 mode, UINT8 publicDlPkgNumMax, UINT16 publicDlBufferToalSize);

OsaTimeTValue mwGetTimeSecs(void);
void mwSetTimeSecs(OsaTimeTValue time);

/*
 * Set the default DNS config, and save to NVM
*/
void mwSetAndSaveDefaultDnsConfig(MidWareDefaultDnsCfg *pDnsCfg);

/*
 * Get the default DNS config from NVM
*/
void mwGetDefaultDnsConfig(MidWareDefaultDnsCfg *pDnsCfg);
void mwSetAndSaveAllDMConfig(MidWareDmConfig* config);

UINT32 mwGetAbupFotaEnableFlag(void);
void mwSetAbupFotaEnableFlag(UINT32 abupFotaEnableFlag);
UINT32 mwGetSimEdrxValue(AtCmdPhyEdrxPara *atCmdPhyEdrxPara);
UINT32 mwSetSimEdrxValue(AtCmdPhyEdrxPara *atCmdPhyEdrxPara);

#endif

