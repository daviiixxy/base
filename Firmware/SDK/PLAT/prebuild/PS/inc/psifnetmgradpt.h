
#ifndef PSIF_HDR_NET_MGR_ADPT_H
#define PSIF_HDR_NET_MGR_ADPT_H

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2018- Copyrights of Qualcomm Ltd.
 File name:      - psif_mng.h
 Description:    - ps netif register/unregister function header
 History:        - 01/02/2018, Originated by xwang
 ******************************************************************************
******************************************************************************/

#ifdef WIN32
#include "winsys.h"
#else
#include "commontypedef.h"
#endif
#include "lwip/priv/tcpip_priv.h"
#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "netmgr.h"

/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/

#define PS_MAX_DNS_NUM 2


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/


typedef struct PsIfRegisterCfg_Tag
{
    UINT8       cid;
    UINT8       bindTo;
    BOOL        isDefualt;  //1 -> default pdn, 0 -> not default pdn
    UINT8       type;       //NmNetIpType

    UINT16      mtu;
    BOOL        bWakeUp;    //when wake up from sleep2/HIB, netif re-created/recovered,
    //UINT8       rsvd0;
    BOOL        bOOS;       //when wake up from sleep2/HIB, netif re-created/recovered, but maybe still OOS

    NmNetIpv4Info ipv4Conf;
    NmNetIpv6Info ipv6Conf;
}PsIfRegisterCfg;   //72 bytes

#if 0
typedef struct PsIfUnregisterConf_Tag
{
    struct tcpip_api_call_data call;
    UINT8 cid;
}PsIfUnregisterConf;
#endif
typedef struct PsIfUnregisterCfg_Tag
{
    UINT8       cid;
    UINT8       rsvd0;
    UINT16      rsvd1;
}PsIfUnregisterCfg;



/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/*
 * PS netif register callback funcion which will run in the tcpip thread
*/
err_t PsifRegisterCallback(PsIfRegisterCfg *msg);

/*
 * PS netif unregister callback funcion which will run in the tcpip thread
*/
err_t PsifUnregisterCallback(PsIfUnregisterCfg *msg);

/*
 * PS netif get UE network info callback funcion which will run in the tcpip thread
*/
err_t PsifGetNetInfoCallback(UINT8 reqCid, NmAtiGetNetInfoRet *pGetNetInfoRet);

/*
 * When service state changes, need to notify netif to update, and send the indication to up layer
*/
err_t PsifServiceStateIndCallback(BOOL bInService);


#endif
