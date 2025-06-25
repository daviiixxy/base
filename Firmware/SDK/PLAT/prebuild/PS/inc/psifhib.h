#ifndef PSIF_HDR_HIB_H
#define PSIF_HDR_HIB_H

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2019- Copyrights of Qualcomm Ltd.
 File name:      - psifhib.h
 Description:    - tcpip layer hib/sleep2 mode related API
 History:        - 04/24/2019, Originated by xwang
 ******************************************************************************
******************************************************************************/
#ifdef WIN32
#include "winsys.h"
#else
#include "commontypedef.h"
#include "lwip/ip_addr.h"
#endif




/****************************************************************************** 
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/

#define PSIF_TCPIP_TINY_CONTEXT_HEADER_SIZE ((sizeof(PsifHibTcpipContextHeader)+3)&0xFFFFFFFC)
#define PSIF_IP6_TINY_CONTEXT_SIZE ((sizeof(PsifHibIp6Info)+3)&0xFFFFFFFC)
#define PSIF_TCP_TINY_CONTEXT_SIZE ((sizeof(PsifHibTcpContext)+3)&0xFFFFFFFC)
#define PSIF_DNSCACHE_TINY_CONTEXT_SIZE ((sizeof(PsifHibDnsCache)+3)&0xFFFFFFFC)
#define PSIF_UDP_TINY_CONTEXT_SIZE ((sizeof(PsifHibUdpContext)+3)&0xFFFFFFFC)



#define PSIF_TCPIP_TINY_CONTEXT_HEADER_MAGIC 0x1122
#define PSIF_IP6_TINY_CONTEXT_MAGIC 0x3344
#define PSIF_TCP_TINY_CONTEXT_MAGIC 0x5566
#define PSIF_DNSCACHE_TINY_CONTEXT_MAGIC 0x7788
#define PSIF_UDP_TINY_CONTEXT_MAGIC 0x8899


#define PSIF_DNSCACHE_MAX_URL_LEN 20

#define MAX_ACTIVE_PDN_SUPPORT 2



/****************************************************************************** 
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/************************************************************************************************************************************************************
*
* +------------------------------------+--------------------------+----------------------------+----------------------------+-----------------------------+
* | PsifHibTcpipContextHeader(4 bytes) |PsifHibIp6Info (16 bytes) |PsifHibTcpContext (116 bytes)|PsifHibDnsCache (64 bytes) |PsifHibUdpContext (48 bytes)|
* +------------------------------------+--------------------------+----------------------------+----------------------------+-----------------------------+
*
*************************************************************************************************************************************************************/

typedef enum PsifHibTcpipContextFlag_tag{
    PSIFHIBTCPIPCONTEXT_INVALD = 0,
    PSIFHIBTCPIPCONTEXT_IP6INFO_VALID = 1,
    PSIFHIBTCPIPCONTEXT_TCPCONTEXT_VALID = 2,
    PSIFHIBTCPIPCONTEXT_DNSCACHE_VALID = 3,
    PSIFHIBTCPIPCONTEXT_UDPCONTEXT_VALID = 4,
//  PSIFHIBTCPIPCONTEXT_MAX_VALID = 5,
}PsifHibTcpipContextFlag;

typedef struct PsifHibDnsCache_Tag {
    UINT16 magic; //PSIF_DNSCACHE_TINY_CONTEXT_MAGIC
    UINT16 reserved;
    UINT32 activeTime;
    UINT32 ttl;
    ip_addr_t dAddr;
    CHAR name[PSIF_DNSCACHE_MAX_URL_LEN];
}PsifHibDnsCache;    

typedef struct PsifHibIp6PrefixInfo_Tag {
    UINT8 cid;
    UINT8 reserved;
    UINT16 magic; //PSIF_IP6_TINY_CONTEXT_MAGIC
    UINT32 lifeTime;
    UINT32 activeTime; //second ticks
    UINT32 prefix[2];
}PsifHibIp6PrefixInfo_Tag;

typedef struct PsifHibIp6Info_Tag {
	struct PsifHibIp6PrefixInfo_Tag PsifHibIp6PrefixInfo[MAX_ACTIVE_PDN_SUPPORT];
}PsifHibIp6Info ;

typedef struct PsifHibTcpContext_Tag {
    UINT8 type;
    UINT8 option;
    UINT8 tos;
    UINT8 ttl;

    UINT8 SndScale;
    UINT8 RcvScale;
    UINT16 magic; //PSIF_TCP_TINY_CONTEXT_MAGIC   

    UINT8 flags;
    UINT8 reserved;
    UINT16 sockid;

    UINT16 remotePort;
    UINT16 localPort;    
    ip_addr_t remoteAddr;
    ip_addr_t localAddr;
    
    UINT32 rcvNext;
    UINT32 rcvWnd;
    UINT32 rcvAnnWnd;
    UINT32 rcvAnnRitEdge;

    UINT16 mss;
    UINT16 rto;
    INT16 sa;
    INT16 sv;

    UINT32 lastAck;

    UINT32 cWnd;
    UINT32 ssthresh;

    UINT32 sndNxt;
    UINT32 sndWl1;
    UINT32 sndWl2;

    UINT32 SndLbb;
    UINT32 SndWnd;
    UINT32 SndWndMax;
}PsifHibTcpContext;

typedef struct PsifHibUdpContext_Tag {
    UINT16 sockid;
    UINT16 magic; //PSIF_IP6_TINY_CONTEXT_MAGIC

    UINT16 remotePort;
    UINT16 localPort;    
    ip_addr_t remoteAddr;
    ip_addr_t localAddr;
}PsifHibUdpContext;

typedef struct PsifHibTcpipContextHeader_Tag {
    UINT8 flag; //PsifHibTcpipContextFlag
    UINT8 reserved;
    UINT16 magic; //PSIF_TCPIP_TINY_CONTEXT_HEADER_MAGIC
}PsifHibTcpipContextHeader;

enum pcb_hib_state {
  PCB_HIB_DISABLE_DEACTIVE     = 0,
  PCB_HIB_ENABLE_DEACTIVE      = 1,
  PCB_HIB_ENABLE_ACTIVE        = 2,
};


/******************************************************************************
 *****************************************************************************
 * global 
 *****************************************************************************
******************************************************************************/

/***********************************************************************************************
 *
 * +------------------------------------+--------------------------+----------------------------+
 * | PsifHibTcpipContextHeader(4 bytes) |PsifHibIp6Info (16 bytes) |PsifHibTcpContext (64 bytes)|
 * +------------------------------------+--------------------------+----------------------------+
 *
************************************************************************************************/
extern PsifHibTcpipContextHeader *pLwipTinyCtx;



/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

BOOL PsifIsTcpipAllowEnterHIB(void);

void PsifRequestRecoverContextFromHib(void);

BOOL PsifGetPreTcpipHibContextInfo(UINT8 type);

BOOL PsifGetCurrTcpipHibContextInfo(UINT8 type);

void PsifSetCurrTcpipHibContext(BOOL exist, UINT8 type);

void PsifSetTcpipHibContextChanged(BOOL change, UINT8 type);

BOOL PsifGetTcpipHibContextChanged(UINT8 type);

void PisfCheckTcpipHibContextNeedChang(void);

void PsifTcpipAllowEnterHib(void);

void PsifTcpipNotAllowEnterHib(void);

void PsifTcpipHibModeInit(void);

UINT32 PsifGetCurrHibTicks(void);

BOOL PsifCheckWetherRecoverFromHib(void);


#endif

