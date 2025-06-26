/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ps_mm_if.h
 * Description:  API interface implementation header file for mm service
 * History:      Rev1.0   2018-10-12
 *
 ****************************************************************************/
#ifndef __PS_MM_IF_H__
#define __PS_MM_IF_H__
#include "cms_util.h"
#include "ps_lib_api.h"

CmsRetId mmQueryRegOption(UINT32 atHandle);
CmsRetId mmGetRegStatus(UINT32 atHandle);
//CmsRetId mmSetRegOption(UINT32 atHandle, UINT8 regOption);
CmsRetId mmQuerySuppOperator(UINT32 atHandle);
CmsRetId mmGetCurrOperator(UINT32 atHandle);
//CmsRetId mmSetCurrOperator(UINT32 atHandle, INT32 modeVal, INT32 formatVal, UINT8 *networkOperator, INT32 opeStrLen, INT32 accTchVal);
CmsRetId mmSetAutoPlmnRegister(UINT32 atHandle);
CmsRetId mmSetManualPlmnRegister(UINT32 atHandle, BOOL bFailToAuto, INT32 operFormat, UINT8 *pOperStr, INT32 accTchVal);
CmsRetId mmSetDeregister(UINT32 atHandle);
CmsRetId mmSetOperFormat(UINT32 atHandle, INT32 operFormat);
CmsRetId mmSetNwModeIndSetting(UINT32 atHandle, INT32 bNwModeInd);
CmsRetId mmGetNwModeIndSetting(UINT32 atHandle);
//CmsRetId mmGetESignalQuality(UINT32 atHandle, UINT8 *rsrq, UINT8 *rsrp);
CmsRetId mmGetCpsms(UINT32 atHandle);
CmsRetId mmSetCpsms(UINT32 atHandle, UINT8 modeVal, const UINT8 *pRauT, const UINT8 *pGprsT, const UINT8 *pTauT, const UINT8 *pActT);
CmsRetId mmGetEdrx(UINT32 atHandle);
CmsRetId mmSetEdrx(UINT32 atHandle, UINT8 modeVal, UINT8 actType, UINT8* edrxVal);
CmsRetId mmReadEdrxDyn(UINT32 atHandle);
CmsRetId mmGetCiotoptCapa(UINT32 atHandle);
CmsRetId mmSetCiotoptCfg(UINT32 atHandle, CmiMmSetCiotOptCfgReq *pSetCiotOptCfgReq);
CmsRetId mmGetCiotoptCfg(UINT32 atHandle);
CmsRetId mmGetCoverEnhancStatu(UINT32 atHandle);
CmsRetId mmGetEcplmns(UINT32 atHandle);
CmsRetId mmExecEcplmns(UINT32 atHandle);

void mmGetCpsmsSync(void *msg);
void mmSetCpsmsSync(void *msg);
void mmSetEdrxSync(void *msg);
void mmReadEdrxDynSync(void *msg);
void mmGetPtwEdrxsync(void *msg);
void mmSetPtwEdrxsync(void *msg);
void mmGetCoverEnhancStatuSync(void *msg);
void mmGetSignalInfoSync(void *msg);
CmsRetId mmGetCESQ(UINT32 atHandle);
CmsRetId mmGetECPSMR(UINT32 atHandle);

UINT8 mmGetCsqRssiFromCesq(INT8 rsrp, INT8 rsrq);

CmsRetId mmSetPtwEdrx(UINT32 atHandle, UINT8 modeVal, UINT8 actType, UINT8* ptw, UINT8* edrxVal);
CmsRetId mmGetPtwEdrx(UINT32 atHandle);
CmsRetId mmGetECEMMTIME(UINT32 atHandle);
CmsRetId mmSendIpv6RsFailReq(UINT32 atHandle, UINT8 cid);

#endif

