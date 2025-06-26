/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: ps_ps_if.h
 *
 *  Description: API interface for PS service
 *
 *  History:
 *
 *  Notes:
 *
******************************************************************************/
#ifndef __PS_PS_IF_H__
#define __PS_PS_IF_H__
#include "netmgr.h"
#include "cmicomm.h"
#include "cmips.h"
#include "cms_util.h"


/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/

#define PSIL_PS_PDP_IP_V6_SIZE      128
#define PSIL_PS_PDP_IPV4_SIZE       16
#define PSIL_IPV4_SUBNETMUX_MAX_LEN     32

#ifndef MIN
#define MIN(a, b) ((a) < (b)? (a) : (b))
#endif /* MIN */


#define PP_PS_PDP_IP_ADDR_STR_SIZE          128

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
typedef struct PsilPsAddrTempInfo_tag
{
   UINT8   len;
   UINT8   valData[PSIL_PS_PDP_IP_V6_SIZE];
}PsilPsAddrTempInfo; /* PDP address */


/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/
CmsRetId psSetGPRSRegStatus(UINT32 atHandle, UINT32 state);
CmsRetId psGetGPRSRegStatus(UINT32 atHandle);
CmsRetId psDeleteCGDCONTContext(UINT32 atHandle, UINT32 dwContextID);
CmsRetId psSetGPRSAttached(UINT32 atHandle, BOOL fAttached);
CmsRetId psGetGPRSAttached(UINT32 atHandle);
CmsRetId psGetGPRSContextActivatedList(UINT32 atHandle);
CmsRetId psSetGPRSContextActivated(UINT32 atHandle, INT32 cid, INT32 state);
CmsRetId psEnterDataState(UINT32 atHandle, UINT8 cid);
CmsRetId psSetCdgcont(UINT32 atHandle, DefineBearerCtxInfo* ctxInfo);
CmsRetId psGetCGCONTRDPCaps(UINT32 atHandle);
CmsRetId psGetCGCONTRDPParam(UINT32 atHandle, UINT32 cid);
CmsRetId psGetAllCGCONTRDPParam(UINT32 atHandle);
CmsRetId psQueryERegOption(UINT32 atHandle);
CmsRetId psGetERegStatus(UINT32 atHandle);
//CmsRetId psSetERegOption(UINT32 atHandle, UINT8 regOption);
CmsRetId psGetCGTFT(UINT32 atHandle);
CmsRetId psDeleteTft(UINT32 atHandle, INT32 cid);
CmsRetId psSetTftFilter(UINT32 atHandle, const CmiPsTftFilter *tftFilter);
CmsRetId psSendUserData(UINT32 atHandle, INT32 cid, INT32 dataStrLen, UINT8 *pStrdata, INT32 rai, INT32 typeOfUserData, BOOL isCSODCP);
CmsRetId psSetQcPdpCfge(UINT32 atHandle, INT32 apnClass, INT32 enabled, INT32 maxPdnConnPerBlock, INT32 maxPdnConnTimer, INT32 pdnReqWaitTimer);
CmsRetId psSetAttBear(UINT32 atHandle, AttachedBearCtxPreSetParam * param);
CmsRetId psGetATTBEAR(UINT32 atHandle);
CmsRetId psGetGPRSActiveCidList (UINT32 atHandle);
CmsRetId psModGPRSContext (UINT32 atHandle, UINT32 cid);
CmsRetId psGetCGDCONTCid (UINT32 atHandle);
CmsRetId psSetCGEQOSQualityService (UINT32 atHandle, const CmiPsEpsQosParams* params);
CmsRetId psDeleteCGEQOSQualityService (UINT32 atHandle, UINT32 cid);
CmsRetId psGetCGEQOSQualityService (UINT32 atHandle);
CmsRetId psGetCGEQOSRDPCapsQos(UINT32 atHandle);
CmsRetId psSetCGEQOSRDPQualityService(UINT32 atHandle, UINT32 cid, BOOL bGetAll);
CmsRetId psSetRTDCP(UINT32 atHandle, INT32 reporting);
CmsRetId psGetCurRTDCP(UINT32 atHandle);
CmsRetId psSetCGAUTH(UINT32 atHandle,INT32 cid,INT32 authPort,UINT8* userId,UINT8 userIdLength, UINT8* password,UINT8 passwordLength);
CmsRetId psGetCGAUTH(UINT32 atHandle);
CmsRetId psSetCIPCA(UINT32 atHandle,INT32 n,INT32 attach);
CmsRetId psGetCIPCA(UINT32 atHandle);
CmsRetId psGetCGAPNRCCid(UINT32 atHandle);
CmsRetId psGetCGAPNRC(UINT32 atHandle, INT32 cid, BOOL bGetAll);
//CmsRetId psSetAllCGAPNRC(UINT32 atHandle);
CmsRetId psSetECCIOTPLANE(UINT32 atHandle,INT32 plane);
CmsRetId psGetPDPAddrCid(UINT32 atHandle);
CmsRetId psGetPDPAddr(UINT32 atHandle, INT32 cid, BOOL bGetAll);
CmsRetId psGetCSCON(UINT32 atHandle);
CmsRetId psSendNoMorePsDataReq(UINT32 atHandle);
CmsRetId psGetBearerPktStats (UINT32 atHandle, UINT8 cid);

CmsRetId psGetCEER(UINT32 atHandle);

void psSetNetMaskStr(UINT8 addrType, int maskLen, char *maskStr);
void psUint8IpAddrToStr(UINT8 addrType, UINT8 *valData, CHAR *ippStr);
void psUint8Ipv4AddrToStr(UINT8 *addrData, CHAR *ippStr);
void psUint8Ipv6AddrToStr(UINT8 addrType, UINT8 *ipUint8Addr, CHAR *ippStr);

void psPdpTypeToStr(UINT8 pdpType, char  *typeStr);
BOOL psIpStrAddrToHexAddr(PsilPsAddrTempInfo *input);
int psNetMaskStrToLen(char* mask);

BOOL psBeAllZero(const UINT8 *ArrayName, UINT8 Length);
void psSetGPRSAttachedsync(void *msg);
void psGetCGAPNRCsync(void *msg);
void psSetCGAUTHsync(void *msg);
void psSetCdgcontsync(void *msg);
void psModifyAPNProfilesync(void *msg);
void psCreateAPNProfilesync(void *msg);
void psGetAPNProfilesync(void *msg);
void psGetAPNDisablesync(void *msg);
void psSetGPRSContextActivatedsync(void *msg);
void psGetPDPAddrsync(void *msg);
void psDeleteCGDCONTContextsync(void *msg);
void psGetSplmnRateParamSync(void *msg);
void psGetBearerPktStatsync(void *msg);
void psGetCGDCONTCidsync(void *msg);
void psGetCGAUTHSync(void *msg);
void  psGetCGCONTRDPCapsSync(void *msg);
void  psGetERegStatusSync(void *msg);
void psGetCGCONTRDPParamSync(void *msg);
void psSetAPNDisablesync(void *msg);
void psSenduserdataSync(void *msg);
void psCSODCPSync(void *msg);
CmsRetId psGetESMCause(UINT32 atHandle);

#endif

