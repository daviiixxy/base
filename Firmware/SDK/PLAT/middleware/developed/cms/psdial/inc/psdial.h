#ifndef __PS_DIAL_H__
#define __PS_DIAL_H__
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - psdial.h
 Description:    - DIAL functions
 History:        - 04/12/2018
 ******************************************************************************
******************************************************************************/
#include "cms_util.h"
#include "osasys.h"
#include "cmicomm.h"
#include "lwip/ip_addr.h"

/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/

/*
 * whether auto dial after power on
*/
#ifndef AT_POWER_ON_AUTO_DIAL
#define AT_POWER_ON_AUTO_DIAL 1
#endif

/*
 * DNS config parameter
*/
#define PS_DAIL_DEFAULT_DNS_NUM     2
#define PS_DAIL_IPV4_ADDR_LEN       4
#define PS_DAIL_IPV6_ADDR_LEN       16


/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/*
 * PS DAIL context
*/
typedef struct PsDialContext_Tag
{
    //UINT32  bUnderPowerOn : 1;  //whether durning power on
    UINT32  bNetifActed : 1;    //netif/PDP state, in fact this flag should set in LWIP net-manager side
    UINT32  bActIfDuringWakeup : 1;  //whether active bearer/netif during sleep2/hib wake up
    UINT32  cfunState : 5;      //CFUN state, CmiFuncValueEnum
    UINT32  bSilentReset : 1;

    UINT32  psConnStatus : 1;
    UINT32  rsvd0 :23;

    CmiSimImsiStr   ueImsi;     //20 bytes
}PsDialContext;     //24 bytes

/*
 * PS DAIL DNS CONFIG
 * DNS order:
 * 1> NW configed DNS;
 * 2> DNS configed in NVM by AT CMD: AT$QCDNSCFG
 * 3> default configed DNS indexed by UE IMSI
*/
typedef struct PsDialDnsCfg_Tag
{
    UINT8 ipv4DnsNum ; //ipv4 valid dns num
    UINT8 ipv6DnsNum ; //ipv6 valid dns num
    UINT16 rsvd;
    ip4_addr_t ipv4Dns[PS_DAIL_DEFAULT_DNS_NUM];
    ip6_addr_t ipv6Dns[PS_DAIL_DEFAULT_DNS_NUM];

}PsDialDnsCfg;     //44 bytes

typedef enum {
    PS_DIAL_NET_TYPE_IPV4     = 0,
    PS_DIAL_NET_TYPE_IPV6     = 1,
    PS_DIAL_NET_TYPE_IPV4V6   = 2,
    PS_DIAL_NET_TYPE_INVALID  = 3,
}PsDialNetType;


/******************************************************************************
 ******************************************************************************
 * External global variable
 ******************************************************************************
******************************************************************************/



/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

CmsRetId psDialProcCmiInd(const SignalBuf *indSignalPtr);
CmsRetId psDialProcCmiCnf(const SignalBuf *cnfSignalPtr);
void psDailGetCfgDnsByUeImsi(PsDialDnsCfg *pDnsCfg);


/*
 * check whether netif is acted
*/
BOOL psDialLwipNetIfIsAct(void);
BOOL psDailBeCfun1State(void);
BOOL psDailBeActNetifDoneDuringWakeup(void);

/******************************************************************************
 * psDailSetAdptDnsServerInfo
 * Description: Set DNS server address
 * input:   UINT8 cid, PsDialDnsCfg *pPcoDns, PsDialDnsCfg *pAdptDns
 * output:  BOOL
 * Comment:
******************************************************************************/
BOOL psDailSetAdptDnsServerInfo(UINT8 cid, UINT8 type, PsDialDnsCfg *pPcoDns, PsDialDnsCfg *pAdptDns, BOOL bWakeUp);

UINT8 psDialGetCfunState(void);

BOOL psDialGetPsConnStatus(void);
void psDialSendPsIpV6FailReq(UINT8 cid);

#endif

