/******************************************************************************
 ******************************************************************************
 Copyright:      - 2021- Copyrights of Qualcomm Inc.
 File name:      - gtp_at.h
 Description:    - GTP transport Layer sub-module
 History:        - 19/08/2021
 ******************************************************************************
******************************************************************************/
#ifndef __GTP_AT_H__
#define __GTP_AT_H__

#include "at_util.h"

CmsRetId qcGtpIpAddr(const AtCmdInputContext *pAtCmdReq);
CmsRetId qcGtpTest(const AtCmdInputContext *pAtCmdReq);
CmsRetId qcGtpCfg(const AtCmdInputContext *pAtCmdReq);
CmsRetId qcGtpTestCfg(const AtCmdInputContext *pAtCmdReq);

#endif

