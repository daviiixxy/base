/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ps_nm_if.h
 * Description:  API interface implementation header file for PHY service
 * History:      Rev1.0   2018-10-12
 *
 ****************************************************************************/
#ifndef __PS_NM_IF_H__
#define __PS_NM_IF_H__
#include "cms_util.h"
#include "netmgr.h"



//#define ATEC_PING_IND_STR_LEN   160
//#define ATEC_ECGADDR_STR_LEN    160




CmsRetId psGetDNS(UINT32 atHandle, UINT8* url);
CmsRetId psStopPing(UINT32 atHandle );
CmsRetId psStartPing(UINT32 atHandle, UINT8* addr, INT16 addr_len, INT32 count, INT32 size, INT32 timeout, BOOL raiFlag);
CmsRetId psIperfReq(UINT32 atHandle, NmIperfReq *pIperfReq);
CmsRetId psSntpReq(UINT32 atHandle, char *sntpServer, UINT16 port, BOOL autoSync);



#endif

