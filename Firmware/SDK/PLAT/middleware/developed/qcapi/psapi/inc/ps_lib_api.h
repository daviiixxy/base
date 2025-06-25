/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ps_lib_api.h
 * Description:  QCX212 opencpu pslibapi header file
 * History:      Rev1.0   2018-12-10
 *
 ****************************************************************************/

#ifndef __PS_LIB_API_H__
#define __PS_LIB_API_H__
#include "task.h"
#include "cmsis_os2.h"
#include "cms_util.h"
#include "netmgr.h"
#include "cmimm.h"
#include "cmidev.h"
#include "cmips.h"


/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/
#define NV9_DATA_LEN               96       /*not suitable to put here, -TBD*/
#define NV9_DATA_IMEI_LEN          32
#define NV9_DATA_SN_LEN            32
#define NV9_DATA_IMEI_LOCK_LEN     16
#define NV9_DATA_SN_LOCK_LEN       16

#define NV9_DATA_IMEI_OFFSET        0
#define NV9_DATA_SN_OFFSET          32
#define NV9_DATA_IMEI_LOCK_OFFSET   64
#define NV9_DATA_SN_LOCK_OFFSET     80


#define PS_APN_MAX_SIZE             (CMI_PS_MAX_APN_LEN+1)
#define PS_INVALID_CID_VAL  0xFF
#define PS_DEFAULT_BEARER_CID_VAL  0


/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/



/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/*
 * APP request PS service
*/
typedef struct AppPsCmiReqData_Tag
{
    /* request input */
    UINT8   sgId;       //PS service group ID: CacSgIdEnum
    UINT8   rsvd0;

    UINT16  reqPrimId;  //request prim ID.
    UINT16  cnfPrimId;

    UINT16  reqParamLen;
    void    *pReqParam;

    /* confirm output */
    UINT16  cnfRc;      //confirm return code: MtErrorResultCode/SmsErrorResultCode
    UINT16  cnfBufLen;
    void    *pCnfBuf;   //filled in callback API
}AppPsCmiReqData;   //20 bytes



struct imsiApiMsg {
  CHAR *imsi;
  UINT8 len;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct iccidApiMsg {
  CHAR *iccid;
  UINT8 len;
  osSemaphoreId_t *sem;
  UINT16 result;
};

typedef struct PsApnRateCtrlParam_Tag
{
    UINT8       aer;        //Additional exception reports
    UINT8       ulTimeUnit; //CmiPsApnRateCtrlUlTimeUnit
    UINT16      reserved0;
    UINT32      maxUlRate;
}PsApnRateCtrlParam;

struct pnrcApiMsg{	
   INT32 cid;
   BOOL bGetAll;
   PsApnRateCtrlParam *var;
   UINT8 len;
   osSemaphoreId_t *sem;
   UINT16 result;
};

struct cgcontrdpApiMsg {
  UINT8 *cid;
  UINT8 *len;
  UINT8 index;
  UINT8 *APN;
  osSemaphoreId_t *sem;
  UINT16 result;
};

typedef enum PsPdnTypeTag
{
    //PDN_TYPE_PPP = 0,  /* PPP */
    PS_PDN_TYPE_IP_V4 = 1,  /* IPv4 */
    PS_PDN_TYPE_IP_V6,      /* IPv6 */
    PS_PDN_TYPE_IP_V4V6,    /* IPv4v6 */
    //PS_PDN_TYPE_X25,      /* X.25 */
    //PS_PDN_TYPE_OSPIH,    /* OSPIH */
    PS_PDN_TYPE_NON_IP =5,     /* NON IP*/
    PS_PDN_TYPE_NUM
}PsPdnType;


typedef struct PsAPNSettingTag
{
    UINT8   cid;
    UINT8   pdnType;        //CmiPsPdnType
    UINT8   reserved0;
    UINT8   apnLength;      /* 0 - apn is not present */
    UINT8   apnStr[CMI_PS_MAX_APN_LEN];//apn string

    /* "PDP_addr" is ignored with the set command */
    /* "d_comp" & "h_comp" is for 2/3G, don't need */

    BOOL    ipv4AlloTypePresent;
    UINT8   ipv4AlloType;   /* CmiPsIpv4AllocType. IPv4 address allocation through NAS signalling, or by DHCP */

    BOOL    reqTypePresent;
    UINT8   reqType;        /*CmiPsBearerReqType */

    BOOL    NSLPIPresent;
    UINT8   NSLPI;          /*CmiPsNSLPICfg, NAS signalling priority*/
    
    BOOL    ipv4MtuDisTypePresent;
    BOOL    ipv4MtuDisByNas;    /* IPv4 MTU size discovery through NAS signalling */

    BOOL    nonIpMtuDisTypePresent;
    BOOL    nonIpMtuDisByNas;   /* Non-IP MTU size discovery through NAS signalling*/

    BOOL    RDSPresent;
    UINT8   RDS;            /*0-Reliable Data Service is not being used for the PDN connection;1-Reliable Data Service is being used for the PDN connection*/

    
    //UINT16  reserved1;
    
    /*
     * <securePCO>, not support now (PAP/CHAP)
    */

    /*
     * <Local_Addr_Ind>, not support now
     * "local IP address in TFT"
    */
    
    /*
     * IMS/pcscf not support now
    */
    BOOL    pcscfDisTypePresent;
    UINT8   pcscfDisType;   //CmiPsPcscfDiscoveryType

    BOOL    imCnSigFlagPresent;
    UINT8   imCnSigFlag;    //CmiPsImCnSigFlag
}PsAPNSetting;

typedef struct PsIpAddrTag
{
    UINT8   addrType;    //CmiIpAddrType
    UINT8   subnetLength;
    UINT16  reserved0;
    UINT8   addrData[CMI_MAX_IP_ADDR_LEN];
}PsIpAddr;    //20 bytes

typedef struct PsBearerCtxDynParamTag
{
    UINT8               cid; // context Id
    UINT8               bid; // bearer Id
    UINT8               reserved0;
    UINT8               apnLength;          /* 0 - apn is not present */
    UINT8               apnStr[CMI_PS_MAX_APN_LEN];//apn string
    PsIpAddr           ipv4Addr;   // if bearer is non-ip type, ipv4Addr/ipv6Addr both invalid
    PsIpAddr           ipv6Addr;
    PsIpAddr           gwIpv4Addr;
  
    UINT8               dnsAddrNum;
    UINT8               pCscfAddrNum;
    UINT8               imCnSigFlag;  //0, 1
    UINT8               lipaInd;      //0, 1;

    PsIpAddr           dnsAddr[CMI_PDN_MAX_NW_ADDR_NUM];
    PsIpAddr           pCscfAddr[CMI_PDN_MAX_NW_ADDR_NUM];

    BOOL                ipv4MtuPresent;
    UINT16              ipv4Mtu;
    BOOL                nonIpMtuPresent;
    UINT16              nonIpMtu;
    //UINT16              servingPlmnRateCtrl;
    BOOL                needRetryAnotherIPType;//retry another IP type bearer needed;
}PsBearerCtxDynParam;    //312 bytes

struct getIPApiMsg {
  PsBearerCtxDynParam *var;
  UINT8 *cid;
  UINT8 *len;
  UINT8 index;
  UINT8 flag;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct celevelApiMsg {
  UINT8 act;
  UINT8 celevel;
  UINT8 cc;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct signalApiMsg {
  INT8 *snr;
  INT8 *rsrp;
  UINT8 *csq;
  osSemaphoreId_t *sem;
  UINT16 result;
};



struct psmApiMsg {
  UINT8 *psmMode;
  UINT32 *tauTimeS;
  UINT32 *activeTimeS;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct edrxApiMsg {
  UINT8 *actType;
  UINT32 *edrxValueMs;
  union {
    UINT32 *nwPtwMs;
    UINT8 *modeVal;
  } share;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct ceregApiMsg {
  UINT8 *state;
  UINT16 *tac;
  UINT32 *cellId;
  UINT32 *tauTimeS;
  UINT32 *activeTimeS;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct extCfgApiMsg {
  UINT8 powerlevel;
  UINT8 powerCfun;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct cfunApiMsg {
  UINT8 fun;
  UINT8 rst;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct addr{
  UINT8	*addressStr;
  UINT16  addrStrLen;
  osSemaphoreId_t *sem;
  UINT32  type;
  UINT16 result;
};

struct callStartStopMsg{
   INT32	cid;
   INT32	state;
   UINT8 *addRc;
   osSemaphoreId_t *sem;
   UINT16 result;
};

struct msidnApiMsg{
   CHAR *msisd;
   UINT8 len;
   osSemaphoreId_t *sem;
   UINT16 result;
};

struct DeleteApiMsg{
	UINT32 var;
	osSemaphoreId_t *sem;
	UINT16 result;
};

struct CgauthApiMsg{
	INT32 cid;
	INT32 authPort;
	UINT8* userId;
	UINT8 userIdLength;
	UINT8* password;
	UINT8 passwordLength;
	osSemaphoreId_t *sem;
	UINT16 result;
};

struct attachApiMsg{
	BOOL  fattached; 
	osSemaphoreId_t *sem;
	UINT16 result;
};

typedef struct PsProfileRes_struct
{
	UINT8 pdpType;
	BOOL apnNameValid;
  	char apnName[DEVICE_INFO_APN_NAME_MAX + 1];
}PsProfileRes;

typedef struct PsMandatoryResChanged_struct
{
	BOOL pdpTypeValid;
	UINT8 pdpType;
  	BOOL apnNameValid;
    char apnName[DEVICE_INFO_APN_NAME_MAX + 1];
}PsMandatoryResChanged;

struct CdgcontApiMsg{
	PsAPNSetting *var;
	UINT8 *cid;
	osSemaphoreId_t *sem;
	UINT16 result;
};

struct CreateApnprofileApiMsg{
  UINT8 src_type;
  PsProfileRes *profile;
  osSemaphoreId_t *sem;
  UINT16 result;
};

/* PS_GET_APN_PROFILE_SYNC_CNF */
typedef struct PsGetAPNProfileSyncCnfTag
{
	UINT8                   rc; //CcmCesmRcCodeEnum
    UINT8 					searchResult;
	BOOL					oldPdpTypeValid;
	UINT8					oldPdpType;
}APNProfileSyncCnf;

struct ModifyApnprofileApiMsg{
  UINT8 src_type;
  PsProfileRes *profile;
  PsMandatoryResChanged *res;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct DisableApnprofileApiMsg{
  UINT8 *status; 
  UINT8  pdp_type;
  char *apn;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct SetDisableApnprofileApiMsg{
  UINT8  status; 
  UINT8  pdp_type;
  char *apn;
  osSemaphoreId_t *sem;
  UINT16 result;
};


struct GetApnprofileApiMsg{ 
  PsProfileRes *profile;
  APNProfileSyncCnf *res;
  osSemaphoreId_t *sem;
  UINT16 result;
};

typedef struct BearerPktStats
{
   UINT32 pkts_tx;
   UINT32 pkts_rx;
   INT64  bytes_tx;  
   INT64  bytes_rx;
   UINT32 pkts_dropped_tx;
   UINT32 pkts_dropped_rx;
}PktStat;

struct pktStateApiMsg{
  PktStat *stat;	
  UINT8 cid;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct splmnrateApiMsg{
  UINT32 index;	
  UINT32 *splmnRate;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct mmGetEdrxApiMsg{
  UINT8 *var;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct mmsetEdrxApiMsg{
  UINT8 modeVal;
  UINT8 actType;
  UINT8 ptw;
  UINT8 edrx;
  osSemaphoreId_t *sem;
  UINT16 result;
};

typedef enum PsBearerStateTag
{
    PS_BEARER_INVALID       = 0,
    PS_BEARER_DEFINED       = 1,
    PS_BEARER_ACTIVATING    = 2,
    PS_BEARER_ACTIVATED     = 3,
    PS_BEARER_MODIFING      = 4,
    PS_BEARER_DEACTIVATING  = 5,
    PS_BEARER_MAX_STATE
}PsBearerState;

typedef struct apnProfile_Tag{
	PsPdnType pdn_type;
	PsBearerState bearerState;
	UINT8 cid;
}apnProfile;

struct getApnProfileMsg{
  UINT8 *apn;
  apnProfile* profile_list;
  UINT8 *profileCount;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct getAuthParamMsg{
  UINT8 cid;
  UINT8 *userName;
  UINT8 *userNameLen;
  UINT8 *pwd;
  UINT8 *pwdLen;
  UINT8* auth_prot;
  osSemaphoreId_t *sem;
  UINT16 result;
};


struct powerStateApiMsg {
  UINT8 powerState;
  UINT16 result;
};

struct cchoApiMsg {
  UINT8 *dfName;
  UINT8 *sessionID;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct cchcApiMsg {
  UINT8 sessionID;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct cglaApiMsg {
  UINT8 sessionID;
  UINT8 *command;
  UINT16 cmdLen;
  UINT8 *response;
  UINT16 *respLen;
  osSemaphoreId_t *sem;
  UINT16 result;
};

#define SIM_FILE_PATH_MAX_LEN 8
#define SIM_APDU_DATA_MAX_LEN 256
typedef struct CrsmCmdParam_Tag
{
    UINT8       command;
    UINT16      fileId;
    UINT8       p1;
    UINT8       p2;
    UINT8       p3;
    UINT16      dataLen;
    UINT8       data[SIM_APDU_DATA_MAX_LEN];
    UINT8       pathLen;
    UINT8       filePath[SIM_FILE_PATH_MAX_LEN];
}
CrsmCmdParam;

typedef struct CrsmRspParam_Tag
{
    UINT8    sw1;
    UINT8    sw2;
    UINT8    respLen;
    UINT8    responseData[SIM_APDU_DATA_MAX_LEN];

}
CrsmRspParam;

struct crsmApiMsg {
  CrsmCmdParam  *cmdParam;
  CrsmRspParam  *responseParam;
  osSemaphoreId_t *sem;
  UINT16 result;
};

struct ecbandApiMsg {
    UINT8 networkMode;
    UINT8 bandNum;
    UINT16 result;
    UINT8 *orderBand;
    osSemaphoreId_t *sem;
};

struct senduserdataApiMsg {
    INT32  cid;
	INT32 dataLen;
	UINT8 *pData;
	INT32  rai;
	INT32  typeofUserData;
	UINT16 result;
	osSemaphoreId_t *sem;
};


struct sendCSODCPdataApiMsg {
    INT32  cid;
	INT32 cdataLen;
	UINT8 *cpData;
	INT32  rai;
	INT32  typeofUserData;
	UINT16 result;
	osSemaphoreId_t *sem;
};

/******************************************************************************
 * Neighber cell info/measurment
 * Note: this API will trigger neighber cell search/measurement, which maybe
 *        cost some power
******************************************************************************/
typedef enum NeighCellReqType_enum
{
    GET_NEIGHBER_CELL_MEAS      = CMI_DEV_GET_BASIC_CELL_MEAS,  /* Only measure neighber cell, no cellID/TAC returned */
    GET_NEIGHBER_CELL_ID_INFO   = CMI_DEV_GET_BASIC_CELL_ID     /* Search neighber cell, neighber cellID & TAC also returned, this cost more time */
}NeighCellReqType;

#define PS_LIB_BASIC_CELL_REQ_MAX_CELL_NUM  5       //MAX cell measured: 1 serving cell + 4 neighber cell

typedef CmiDevGetBasicCellListInfoCnf BasicCellListInfo;


/******************************************************************************
 * CELL lock/unlock,
 * perfer FREQ setting/clear
******************************************************************************/
#define SUPPORT_MAX_FREQ_NUM    8 //== CMI_DEV_SUPPORT_MAX_FREQ_NUM
typedef struct CiotSetFreqParams_Tag
{
    UINT8   mode;       // CmiDevSetFreqModeEnum
    UINT8   cellPresent;// indicate whether phyCellId present
    UINT16  phyCellId; // phyCell ID, 0 - 503

    UINT8   arfcnNum; // 0 is not allowed for mode is CMI_DEV_SET_PREFER_FREQ (1);
                      // max number is CMI_DEV_SUPPORT_MAX_FREQ_NUM
    UINT8   reserved0;
    UINT16  reserved1;
    UINT32  lockedArfcn;//locked EARFCN
    UINT32  arfcnList[SUPPORT_MAX_FREQ_NUM];
}CiotSetFreqParams; // total 44 bytes

typedef struct CiotGetFreqParams_Tag
{
    UINT8   mode;       // CmiDevGetFreqModeEnum  3:means UE has set preferred EARFCN list and has locked EARFCN
    UINT8   cellPresent;// indicate whether phyCellId present
    UINT16  phyCellId; // phyCell ID, 0 - 503

    UINT8   arfcnNum; // 0 is not allowed for mode is CMI_DEV_SET_PREFER_FREQ (1);
                      // max number is CMI_DEV_SUPPORT_MAX_FREQ_NUM
    UINT8   reserved0;
    UINT16  reserved1;
    UINT32  lockedArfcn;//locked EARFCN
    UINT32  arfcnList[SUPPORT_MAX_FREQ_NUM];
}CiotGetFreqParams; // total 44 bytes


/******************************************************************************
 * Get PS extended status info
******************************************************************************/
typedef enum UeExtStatusType_TAG
{
    UE_EXT_STATUS_ALL   = CMI_DEV_GET_ECSTATUS,
    UE_EXT_STATUS_PHY   = CMI_DEV_GET_ECSTATUS_PHY,
    UE_EXT_STATUS_L2    = CMI_DEV_GET_ECSTATUS_L2,
    UE_EXT_STATUS_ERRC  = CMI_DEV_GET_ECSTATUS_RRC,
    UE_EXT_STATUS_EMM   = CMI_DEV_GET_ECSTATUS_EMM,
    UE_EXT_STATUS_PLMN  = CMI_DEV_GET_ECSTATUS_PLMN,
    UE_EXT_STATUS_ESM   = CMI_DEV_GET_ECSTATUS_ESM,
    UE_EXT_STATUS_CCM   = CMI_DEV_GET_ECSTATUS_CCM
}UeExtStatusType;

typedef CmiDevGetExtStatusCnf   UeExtStatusInfo;

/******************************************************************************
 * Set attach bearer parameter
******************************************************************************/
typedef CmiPsSetAttachedBearerCtxReq    SetAttachBearerParams;

/******************************************************************************
 * Get attach bearer setting parameter
******************************************************************************/
typedef CmiPsGetAttachedBearerCtxCnf    GetAttachBearerSetting;

/******************************************************************************
 * Set UE extended configuration
******************************************************************************/
typedef CmiDevSetExtCfgReq   SetExtCfgParams;

/******************************************************************************
 * Get UE extended configuration
******************************************************************************/
typedef CmiDevGetExtCfgCnf   GetExtCfgSetting;

/******************************************************************************
 * Set PS sleep configuration
******************************************************************************/
typedef CmiDevSetPsSleepCfgReq   SetPsSlpCfgParams;

/******************************************************************************
 * Get PS sleep configuration
******************************************************************************/
typedef CmiDevGetPsSleepCfgCnf   GetPsSlpCfgParams;


/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/

//void appCheckTcpipReady(void);
void psSyncProcCmiCnf(const SignalBuf *cnfSignalPtr);

CmsRetId appGetsmscaddress(UINT8 *sms_addr);
CmsRetId appGetMsisdnNumsync(CHAR *msisdn);
CmsRetId  appGetCGAPNRCsync(INT32 cid, PsApnRateCtrlParam *info);
CmsRetId appGetIPSettingSync(UINT8 cid,PsBearerCtxDynParam *info);
CmsRetId appGetAPNProfileSync(PsProfileRes *profile, APNProfileSyncCnf *res);
CmsRetId appGetAPNDisableSync(UINT8 pdp_type, char *apn,UINT8 *status);
CmsRetId appGetSplmnRateSync(UINT32 cid, UINT32 *rc);
CmsRetId appGetPktStatsSync(UINT8 cid, PktStat *stat);
CmsRetId appGetEDRXPtwSettingSync(UINT8 *ptwEdrx);
CmsRetId appGetApnProfilesSync(UINT8 *apn, apnProfile* profileList, UINT8 *profileCount);
CmsRetId appGetAuthParamsSync(UINT8 cid,UINT8* prot, UINT8* userName, UINT8* userLen, UINT8* pwd, UINT8* pwdLen);



CmsRetId initPsCmiReqMapList(void);
CmsRetId appGetNetInfoSync(UINT32 cid, NmAtiSyncRet *pNmNetInfo);
CmsRetId appGetImsiNumSync(CHAR *imsi);
CmsRetId appGetIccidNumSync(CHAR *iccid);
CmsRetId appGetImeiNumSync(CHAR *imei);
CmsRetId appGetPSMSettingSync(UINT8 *psmmode, UINT32 *tauTime, UINT32 *activeTime);
CmsRetId appSetPSMSettingSync(UINT8 psmMode, UINT32 tauTime, UINT32 activeTime);
CmsRetId appGetCeregStateSync(UINT8 *state);
CmsRetId appGetEDRXSettingSync(UINT8 *actType, UINT32 *nwEdrxValueMs, UINT32 *nwPtwMs);
CmsRetId appSetEDRXSettingSync(UINT8 modeVal, UINT8 actType, UINT32 reqEdrxValueMs);
CmsRetId appGetLocationInfoSync(UINT16 *tac, UINT32 *cellId);
CmsRetId appGetTAUInfoSync(UINT32 *tauTimeS, UINT32 *activeTimeS);
CmsRetId appGetAPNSettingSync(UINT8 cid, UINT8 *apn);
CmsRetId appCheckSystemTimeSync(void);
CmsRetId appGetSystemTimeSecsSync(time_t *time);
CmsRetId appGetSystemTimeUtcSync(OsaUtcTimeTValue *time);
CmsRetId appGetActedCidSync(UINT8 *cid, UINT8 *num);

/**
  \fn          appSetSimLogicalChannelOpenSync
  \brief       Send cmi request to open SIM logical channel
  \param[out]  *sessionID: Pointer to a new logical channel number returned by SIM
  \param[in]   *dfName: Pointer to DFname selected on the new logical channel
  \returns     CMS_RET_SUCC: success
  \            CMS_SIM_NOT_INSERT: SIM not inserted
  \            CMS_OPER_NOT_SUPPROT: operation not supported
*/
CmsRetId appSetSimLogicalChannelOpenSync(UINT8 *sessionID, UINT8 *dfName);

/**
  \fn          appSetSimLogicalChannelCloseSync
  \brief       Send cmi request to close SIM logical channel
  \param[in]   sessionID: the logical channel number to be closed
  \returns     CMS_RET_SUCC---success
  \            CMS_SIM_NOT_INSERT: SIM not inserted
  \            CMS_INVALID_PARAM: input invalid parameters
*/
CmsRetId appSetSimLogicalChannelCloseSync(UINT8 sessionID);

/**
  \fn          appSetSimGenLogicalChannelAccessSync
  \brief       Send cmi request to get generic SIM logical channel access
  \param[in]   sessionID: the logical channel number
  \param[in]   *command: Pointer to command apdu, HEX string
  \param[in]   cmdLen: the length of command apdu, max value is CMI_SIM_MAX_CMD_APDU_LEN * 2 (522)
  \param[out]  *response: Pointer to response apdu, HEX string
  \param[out]  respLen: the length of command apdu, max value is 4KB
  \returns     CmsRetId
*/
CmsRetId appSetSimGenLogicalChannelAccessSync(UINT8 sessionID, UINT8 *command, UINT16 cmdLen,
                                                UINT8 *response, UINT16 *respLen);

/**
  \fn          appSetRestrictedSimAccessSync
  \brief       Send cmi request to get generic SIM access
  \param[in]   *pCmdParam: Pointer to command parameters
  \param[out]  *pRspParam: Pointer to response parameters
  \returns     CMS_RET_SUCC---success
  \            CMS_SIM_NOT_INSERT: SIM not inserted
  \            CMS_INVALID_PARAM: input invalid parameters
*/
CmsRetId appSetRestrictedSimAccessSync(CrsmCmdParam *pCmdParam, CrsmRspParam *pRspParam);

/**
  \fn          CmsRetId appGetCFUN(UINT8 *pOutCfun)
  \brief       Get current CFUN state
  \param[out]  *pOutCfun      //refer "CmiFuncValueEnum" CMI_DEV_MIN_FUNC(0)/CMI_DEV_FULL_FUNC(1)/CMI_DEV_TURN_OFF_RF_FUNC(4)
  \returns     CmsRetId
*/
CmsRetId appGetCFUN(UINT8 *pOutCfun);

UINT8 appGetBootCFUNMode(void);
UINT8 appGetSearchPowerLevelSync(void);
UINT8 appGetCELevelSync(void);
CmsRetId appGetSignalInfoSync(UINT8 *csq, INT8 *snr, INT8 *rsrp);
UINT8* appGetNBVersionInfo(void);
BOOL appGetSNNumSync(CHAR* sn);

BOOL appGetImeiLockSync(CHAR* imeiLock);
BOOL appGetSNLockSync(CHAR* snLock);

/**
  \fn          CmsRetId appSetBandModeSync(UINT8 networkMode, UINT8 bandNum,  UINT8 *orderBand)
  \brief
  \param[out] networkMode: network mode
  \param[out] bandNum: valid num of orderBand
  \param[out] orderBand is an array of size 16 bytes

  \returns     CmsRetId
*/
CmsRetId appSetBandModeSync(UINT8 networkMode, UINT8 bandNum,  UINT8 *orderBand);
/**
  \fn          CmsRetId appGetBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand)
  \brief
  \param[out] networkMode: network mode
  \param[out] bandNum: valid num of orderBand
  \param[out] orderBand is an array of size 16 bytes
  \returns     CmsRetId
*/
CmsRetId appGetBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand);

/**
  \fn          CmsRetId appGetSupportedBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand)
  \brief
  \param[out] networkMode: network mode
  \param[out] bandNum: valid num of orderBand
  \param[out] orderBand is an array of size 16 bytes
  \returns     CmsRetId
*/
CmsRetId appGetSupportedBandModeSync(INT8 *networkMode, UINT8 *bandNum,  UINT8 *orderBand);


/**
  \fn           CmsRetId appGetECBCInfoSync(NeighCellReqType reqType,
  \                                         UINT8 reqMaxCellNum,
  \                                         UINT16 maxMeasTimeSec,
  \                                         BasicCellListInfo *pBcListInfo)
  \brief        Request PS to measure/search neighber cell
  \param[in]    reqType         Measurement/Search.
  \param[in]    reqMaxCellNum   How many cell info need to returned, including serving cell, range: (1-5)
  \param[in]    maxMeasTimeSec  Measure/search guard timer, range: (4-300)
  \param[out]   pBcListInfo     Pointer to store the result basic cell info
  \returns      CmsRetId
*/
CmsRetId appGetECBCInfoSync(NeighCellReqType reqType, UINT8 reqMaxCellNum, UINT16 maxMeasTimeSec, BasicCellListInfo *pBcListInfo);

/**
  \fn          CmsRetId appSetCiotFreqSync
  \brief       Send cmi request to set prefer EARFCN list, lock or unlock cell
  \param[in]   CiotSetFreqParams *pCiotFreqParams, the pointer to the CiotSetFreqParams
  \returns     CmsRetId
  \NTOE:       Set EARFCN must be restricted to execute in power off or air plane state.
*/
CmsRetId appSetCiotFreqSync(CiotSetFreqParams *pCiotFreqParams);

/**
  \fn          CmsRetId appGetCiotFreqSync
  \brief       Send cmi request to get the current EARFCN setting.
  \param[out]  CiotGetFreqParams *pCiotFreqParams, the pointer to the CiotGetFreqParams
  \returns     CmsRetId
*/
CmsRetId appGetCiotFreqSync(CiotGetFreqParams *pCiotFreqParams);

/**
  \fn          CmsRetId appGetPSMModeSync(uint8_t *pMode)
  \brief       Send cmi request to get current psm mode
  \param[out]  *pMode     Pointer to store the result of psm mode
  \returns     CmsRetId
*/
CmsRetId appGetPSMModeSync(UINT8 *pMode);


/**
  \fn          CmsRetId appSetsenddata(INT32 cid, INT32 dataStrLen, UINT8 *pStrdata, INT32 rai, INT32 typeOfUserData)
  \brief       send data via control plane or user plane.
  \returns     CmsRetId
*/
CmsRetId appSetsenddata(INT32 cid, INT32 dataStrLen, UINT8 *pStrdata, INT32 rai, INT32 typeOfUserData);

/**
  \fn          CmsRetId appSetCSODCP(INT32 cid, INT32 cdataStrLen, UINT8 *cpStrdata, INT32 rai, INT32 typeOfUserData)
  \brief       Transmit data over control plane to network via MT.
  \returns     CmsRetId
*/
CmsRetId appSetCSODCP(INT32 cid, INT32 cdataStrLen, UINT8 *cpStrdata, INT32 rai, INT32 typeOfUserData);

/**
  \fn          appGetUeExtStatusInfoSync
  \brief       Send cmi request to get the extended status infomation of UE.
  \param[in]   UeExtStatusType statusType, the request type of status information
  \param[out]  UeExtStatusInfo *pStatusInfo, the pointer to the status information returned.
  \returns     CmsRetId
*/
CmsRetId appGetUeExtStatusInfoSync(UeExtStatusType statusType, UeExtStatusInfo *pStatusInfo);

/**
  \fn          appSetEDRXPtwSync
  \brief       Send cmi request to set paging time window
  \param[in]   reqPtwValue      PTW value encoded in 24.008
  \returns     CmsRetId
  \NOTE:
*/
CmsRetId appSetEDRXPtwSync(UINT8 reqPtwValue);

/**
  \fn          CmsRetId appGetPtwSettingSync(uint8_t *pMode)
  \brief       Send cmi request to get current PTW setting
  \param[out]  *pPtw     Pointer to store the result of paging time window
  \returns     CmsRetId
*/
CmsRetId appGetPtwSettingSync(UINT8 *pPtw);


/**
  \fn          appSetAttachBearerSync
  \brief       Send cmi request to set attach bearer info, such as ip type and APN
  \param[in]   pAttachBearerParams      INPUT, request attach bearer parameter
  \returns     CmsRetId
  \NOTE:       This attach bearer setting take effect in next attach procedure, refer AT: AT+ECATTBEARER
*/
CmsRetId appSetAttachBearerSync(SetAttachBearerParams *pAttachBearerParams);

/**
  \fn          appGetAttachBearerSettingSync
  \brief       Send cmi request to get attach bearer setting
  \param[out]  pAttachBearerSettingParams   OUTPUT, return current attach bearer setting info
  \returns     CmsRetId
  \NOTE:       Return attach bearer setting, refer AT: AT+ECATTBEARER?
*/
CmsRetId appGetAttachBearerSettingSync(GetAttachBearerSetting *pAttachBearerSettingParams);


/**
  \fn          appSetEccfgSync
  \brief       Send cmi request to set the UE extended configuration
  \param[in]   pSetExtCfgParams     the pointer to set the extended status infomation of UE
  \returns     CmsRetId
  \NOTE:       refer: AT+ECCFG
*/
CmsRetId appSetEccfgSync(SetExtCfgParams *pSetExtCfgParams);

/**
  \fn          appGetEccfgSettingSync
  \brief       Send cmi request to get the extended status infomation of UE.
  \param[out]  pExtCfgSetting   the pointer to the extended status infomation of UE returned.
  \returns     CmsRetId
  \NOTE:       refer: AT+ECCFG
*/
CmsRetId appGetEccfgSettingSync(GetExtCfgSetting *pExtCfgSetting);



/**
  \fn          appSetEcPsSlpCfgSync
  \brief       Send cmi request to set the protocol stack sleep2/hibernate configuration
  \param[in]   SetPsSlpCfgParams     the pointer to set the set parameters
  \returns     CmsRetId
  \NOTE:       refer: AT+ECPSSLPCFG =
*/
CmsRetId appSetEcPsSlpCfgSync(SetPsSlpCfgParams *pSetPsSlpCfgParams);
/**
  \fn           appGetEcPsSlpCfgSync
  \brief        Send cmi request to get the protocol stack sleep2/hibernate config.
  \param[out]   pExtCfgSetting   the pointer to the parameters returned.
  \returns      CmsRetId
  \NOTE:        refer: AT+ECPSSLPCFG?
*/
CmsRetId appGetEcPsSlpCfgSync(GetPsSlpCfgParams *pPsSlpCfgSetting);

/**
  \fn          appSetEcSIMSleepSync
  \brief       set UE to allow SIM card sleep (power off SIM) or not (power on SIM) for appSetCSIMSync(AT+CSIM) and appSetRestrictedSimAccessSync(AT+CRSM)
  \param[in]   BOOL bAllowSleep, indicated whether allow SIM sleep or not
  \returns     CmsRetId
  \NOTE:       refer: AT+ECSIMSLEEP,
  \            shall set SIM sleep not allowed (power on SIM) before useappSetCSIMSync(AT+CSIM) or appSetRestrictedSimAccessSync(AT+CRSM),
  \            then set SIM sleep allowed (power off SIM) to save power after finish if required.
*/
CmsRetId appSetEcSIMSleepSync(BOOL bAllowSleep);

/**
  \fn          appSetCSIMSync
  \brief       Send cmi request to transmit APDU command to the SIM and get APDU response from the SIM
  \param[in]   UINT16 cmdApduStrLen, the length of command APDU string
  \param[in]   UINT8 *cmdApduStr, the pointor to the command APDU, hex string
  \param[in]   UINT16 rspApduBufSize, the buffer size for response APDU, shall evaluate the max length of response APDU hex string
  \param[out]  UINT16 *rspApduStrLen, the pointor to the length of response APDU string, shall less than rspApduBufSize
  \param[out]  UINT8 *rspApduStr, the pointor to the response APDU, hex string
  \returns     CmsRetId
  \NOTE:       refer: AT+CSIM
*/
CmsRetId appSetCSIMSync(UINT16 cmdApduStrLen,
                                UINT8 *cmdApduStr,
                                UINT16 rspApduBufSize,
                                UINT16 *rspApduStrLen,
                                UINT8 *rspApduStr);


CmsRetId appSetAPNSettingSync(PsAPNSetting *info, UINT8 *cid);

/**
  \fn          CmsRetId appSetCFUN(UINT8 fun)
  \brief       Send cfun request to NB
  \param[in]   fun: 0 minimum function and 1 full function
  \returns     CmsRetId
*/
CmsRetId appSetCFUN(UINT8 fun);

#endif

