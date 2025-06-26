/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ps_sim_if.h
 * Description:  The header file for API interface for PS SIM module
 * History:      Rev1.0   2018-10-12
 *
 ****************************************************************************/
#ifndef __PS_SIM_IF_H__
#define __PS_SIM_IF_H__

#include "cms_util.h"

CmsRetId simGetImsi(UINT32 atHandle);
CmsRetId simGetPinState(UINT32 atHandle);
CmsRetId simEnterPin(UINT32 atHandle, UINT8* oldPasswd, UINT8* newPasswd);
CmsRetId simSetCRSM(UINT32 atHandle, INT32 cmd, INT32 fileId, INT32 p1, INT32 p2, INT32 p3, CHAR *data, CHAR *pathId);
CmsRetId simSetCSIM(UINT32 atHandle, UINT16 cmdStrLen, UINT8 *cmdStr);
CmsRetId simGetIccid(UINT32 atHandle);
CmsRetId simSetCPWD(UINT32 atHandle, UINT8 no, UINT8 oper, UINT8* oldPasswd, UINT8* newPasswd);
CmsRetId simSetClck(UINT32 atHandle, UINT8 mode, UINT8 fac, UINT8* pinCode);
CmsRetId simSetCcho(UINT32 atHandle, UINT8 *dfName);
CmsRetId simSetCchc(UINT32 atHandle, UINT8 sessionId);
CmsRetId simSetCgla(UINT32 atHandle, UINT8 sessionId, UINT16 len, UINT8* command);
CmsRetId simSetSimSleep(UINT32 atHandle, UINT8 mode);
CmsRetId simGetSimSleepState(UINT32 atHandle);
CmsRetId simSetCpinr(UINT32 atHandle, UINT8 pinCode);
CmsRetId simSetECSWC(UINT32 atHandle, UINT8 mode);
CmsRetId simGetSWCSetting(UINT32 atHandle);
CmsRetId simSetECSIMPD(UINT32 atHandle, UINT8 mode);
CmsRetId simGetECSIMPDSetting(UINT32 atHandle);
CmsRetId simGetSubscriberNumber(UINT32 atHandle);
CmsRetId simSetTerminalProfile(UINT32 atHandle, UINT8 mode, UINT16 strLen, UINT8 *profileStr);
CmsRetId simGetTerminalProfile(UINT32 atHandle);
void simGetSubscriberNumbersync(void *msg);

void simGetImsiSync(void *msg);
void simGetIccidSync(void *msg);
void simSetCchoSync(void *msg);
void simSetCchcSync(void *msg);
void simSetCglaSync(void *msg);
void simSetCrsmSync(void *msg);

#endif

