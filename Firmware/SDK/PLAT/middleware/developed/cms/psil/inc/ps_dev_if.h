/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ps_dev_if.h
 * Description:  API interface implementation header file for dev service
 * History:      Rev1.0   2018-10-12
 *
 ****************************************************************************/
#ifndef __PS_DEV_IF_H__
#define __PS_DEV_IF_H__
#include "cms_util.h"
#include "cmidev.h"

CmsRetId devGetFunc(UINT32 atHandle);
CmsRetId devSetFunc(UINT32 atHandle, INT32 funcVal, INT32 resetVal);
CmsRetId devGetDevStatus(UINT32 atHandle);
CmsRetId devGetSupportedCiotBandModeReq(UINT32 atHandle);
CmsRetId devGetCiotBandModeReq(UINT32 atHandle);
//CmsRetId devSetCiotBandModeReq(UINT32 atHandle, INT32 networkMode, UINT32 bandNum,  INT32* orderBand);
CmsRetId devSetCiotBandModeReq(UINT32 atHandle, CmiDevSetCiotBandReq *pCmiSetBandReq);
CmsRetId devGetCiotFreqReq(UINT32 atHandle);
CmsRetId devSetCiotFreqReq(UINT32 atHandle, UINT8 mode, const INT32 *pFreqList, UINT8 freqNum, INT32 phyCellId);
CmsRetId devSetPowerState(UINT32 atHandle, UINT8 powerState);
CmsRetId devGetExtCfg(UINT32 atHandle);
CmsRetId devSetExtCfg(UINT32 atHandle, CmiDevSetExtCfgReq *pSetExtCfgReq);
CmsRetId devSetExtCfgSync(void *msg);
CmsRetId devRmFPLMN(UINT32 atHandle, INT32 type);
CmsRetId devGetCMOLRCapa(UINT32 atHandle);
CmsRetId devGetCMOLR(UINT32 atHandle);
CmsRetId devSetCMOLR(UINT32 atHandle, UINT32 enable, UINT32 method, UINT32 horAccSet, UINT32 horAcc, UINT32 verReq, UINT32 verAccSet,
                            UINT32 verAcc, UINT32 velReq, UINT32 reqMode, UINT32 timeOut, UINT32 interval, UINT32 shapeReq, UINT32 plane,
                            UINT8* NMEAReq, UINT8* thirdPartyAddr, UINT32 paramNmb);
CmsRetId devGetCMTLRCapa(UINT32 atHandle);
CmsRetId devGetCMTLR(UINT32 atHandle);
CmsRetId devSetCMTLR(UINT32 atHandle,INT32 subscribe);
CmsRetId devGetCMTLRACapa(UINT32 atHandle);
CmsRetId devGetCMTLRA(UINT32 atHandle);
CmsRetId devSetCMTLRA(UINT32 atHandle,INT32 allow, INT32 handleId);
CmsRetId devGetESTATUS(UINT32 atHandle, UINT8 statusType);
CmsRetId devSetESTATIS(UINT32 atHandle, UINT16 periodS);
CmsRetId devGetECBCINFO(UINT32 atHandle, CmiDevGetBasicCellListInfoReq *pGetBcInfoReq);

void devGetExtCfgSync(void *msg);
void devSetFuncSync(void *msg);
void devSetCiotBandModeReqSync(void *msg);
BOOL OperStrToNumericPlmn(const UINT8 *pPlmnStr, CmiNumericPlmn *pOutPlmn);
//void devGetECBCINFOSync(void *msg);

CmsRetId devGetECPSTEST(UINT32 atHandle);
CmsRetId devSetECPSTEST(UINT32 atHandle,UINT8 subscribe);
CmsRetId devGetSupportedBandPowerClassReq(UINT32 atHandle);
CmsRetId devGetECPOWERCLASS(UINT32 atHandle);
CmsRetId devSetECPOWERCLASS(UINT32 atHandle, CmiDevSetPowerClassReq *pPowerClass);
CmsRetId devCeInfoGetFunc(UINT32 atHandle);
CmsRetId devCeInfoSetFunc(UINT32 atHandle, INT32 Val);
CmsRetId devVzwthrottleGetFunc(UINT32 atHandle);
CmsRetId devVzwthrottleSetFunc(UINT32 atHandle, INT32 Time, INT32 Counter);
CmsRetId devGetRPMPARAM(UINT32 atHandle);
CmsRetId devGetRPMVERSION(UINT32 atHandle);
CmsRetId devGetECNBR14(UINT32 atHandle);

CmsRetId devGetEVENTSTATIS(UINT32 atHandle);
CmsRetId devSetEVENTSTATIS(UINT32 atHandle, CmiDevSetEventStatisReq  *pMode);
CmsRetId devSetPSSLPCfg(UINT32 atHandle, CmiDevSetPsSleepCfgReq *pSetCfgReq);
CmsRetId devGetPSSLPCfg(UINT32 atHandle);
CmsRetId devGetQCState(UINT32 atHandle);
CmsRetId devGetDrx(UINT32 atHandle);
CmsRetId devSetQCLAPI(UINT32 atHandle,INT32 Lapi);
CmsRetId devGetQCLAPI(UINT32 atHandle);
CmsRetId devSetQCROAMINGDATA(UINT32 atHandle,INT32 RoamData);
CmsRetId devGetQCROAMINGDATA(UINT32 atHandle);

CmsRetId devGetPLmnlocklist(UINT32 atHandle);
CmsRetId devSetPLmnlocklist(UINT32 atHandle,CmiDevSetPlmnLockListReq *plocklist, UINT8 *networkOperator);





#endif

