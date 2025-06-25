#ifndef __HT_PS_LIB_API_H__
#define __HT_PS_LIB_API_H__

#include "cms_api.h"
#include "ps_lib_api.h"
#include "HT_ps_lib_api.h"

void HT_psSyncProcCmiCnf(const SignalBuf *cnfSignalPtr);
CmsRetId HT_Getsmscaddress(UINT8 *sms_addr);
CmsRetId HT_GetMsisdnNumsync(CHAR *msisdn);
CmsRetId HT_GetCGAPNRCsync(INT32 cid, PsApnRateCtrlParam *info);
CmsRetId HT_GetIPSettingSync(UINT8 cid,PsBearerCtxDynParam *info);
CmsRetId HT_GetAPNProfileSync(PsProfileRes *profile, APNProfileSyncCnf *res);
CmsRetId HT_GetAPNDisableSync(UINT8 pdp_type, char *apn,UINT8 *status);
CmsRetId HT_GetSplmnRateSync(UINT32 cid, UINT32 *rc);
CmsRetId HT_GetPktStatsSync(UINT8 cid, PktStat *stat);
CmsRetId HT_GetEDRXPtwSettingSync(UINT8 *ptwEdrx);
CmsRetId HT_GetApnProfilesSync(UINT8 *apn, apnProfile* profileList, UINT8 *profileCount);
CmsRetId HT_GetAuthParamsSync(UINT8 cid,UINT8* prot, UINT8* userName, UINT8* userLen, UINT8* pwd, UINT8* pwdLen);
CmsRetId HT_initPsCmiReqMapList(void);
CmsRetId HT_GetNetInfoSync(UINT32 cid, NmAtiSyncRet *pNmNetInfo);
CmsRetId HT_GetImsiNumSync(CHAR *imsi);
CmsRetId HT_GetIccidNumSync(CHAR *iccid);
CmsRetId HT_GetImeiNumSync(CHAR *imei);
CmsRetId HT_GetPSMSettingSync(UINT8 *psmmode, UINT32 *tauTime, UINT32 *activeTime);
CmsRetId HT_GetCeregStateSync(UINT8 *state);
CmsRetId HT_GetEDRXSettingSync(UINT8 *actType, UINT32 *nwEdrxValueMs, UINT32 *nwPtwMs);
CmsRetId HT_GetLocationInfoSync(UINT16 *tac, UINT32 *cellId);
CmsRetId HT_GetTAUInfoSync(UINT32 *tauTimeS, UINT32 *activeTimeS);
CmsRetId HT_GetAPNSettingSync(UINT8 cid, UINT8 *apn);
CmsRetId HT_CheckSystemTimeSync(void);
CmsRetId HT_GetSystemTimeSecsSync(time_t *time);
CmsRetId HT_GetSystemTimeUtcSync(OsaUtcTimeTValue *time);
CmsRetId HT_GetActedCidSync(UINT8 *cid, UINT8 *num);

CmsRetId HT_GetCFUN(UINT8 *pOutCfun);
UINT8 HT_GetBootCFUNMode(void);
UINT8 HT_GetSearchPowerLevelSync(void);
UINT8 HT_GetCELevelSync(void);
CmsRetId HT_GetSignalInfoSync(UINT8 *csq, INT8 *snr, INT8 *rsrp);
UINT8* HT_GetNBVersionInfo(void);
BOOL HT_GetSNNumSync(CHAR* sn);
BOOL HT_GetImeiLockSync(CHAR* imeiLock);
BOOL HT_SetImeiLockSync(CHAR* imeiLock);
BOOL HT_GetSNLockSync(CHAR* snLock);

#endif /* __HT_PS_LIB_API_H__ */