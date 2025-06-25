/******************************************************************************
 ******************************************************************************
 Copyright:      - 2021- Copyrights of Qualcomm Ltd.
 File name:      - netfastpath.c
 Description:    - netif fastpath check
 History:        - 04/02/2021, Originated by xwang
 ******************************************************************************
******************************************************************************/

#ifndef NET_FAST_PATH_H
#define NET_FAST_PATH_H

#include "lwip/ip4.h"
#include "lwip/ip6.h"
#include "lwip/ip_addr.h"
#include "netif/ethernet.h"


#ifdef WIN32
#ifndef  LWIP_LAN_NET_CHANNEL_NUM
#define LWIP_LAN_NET_CHANNEL_NUM 2
#endif
#endif


#define NETIF_NDP_CACHE_NUM 3   //two global, one link local,  0->global, 1->global, 2->link local

#define NetifFastPathGetCheckFailTypeFromResult(result, type) (result &(1 << type))

#define NETIF_FAST_PATH_PKG_SHORT_LEVEL_LENGTH 100

#define NET_FAST_PATH_IP4_ADDR_SIZE           4
#define NET_FAST_PATH_IP6_ADDR_SIZE           16

/*
 * If more than 30s no UL&DL pkg, the TCP connection will be removed from TCP connection list
*/
#define NET_FAST_TCP_CONN_ACTIVE_PERIOD_TICKS   30000


/*
* fast path check result offset
*/

typedef enum NetPkgFastPathChkResult_Tag
{
    NETIF_PKG_FAST_PATH_CHECK_SUCCESS                   = 0, //success. can fwd directly(maybe need insert ether hdr)

    // wan/lan channel
    NETIF_PKG_FAST_PATH_NEED_INPUT_WITHOUT_LAN          = 1, //fail,can not forwatd to LAN ,need call UE input
    NETIF_PKG_FAST_PATH_NEED_INPUT_WITHOUT_WAN          = 2, //fail,can not forwatd to WAN,need call UE input
    NETIF_PKG_FAST_PATH_NEED_ROHC                       = 3, //fail,need first rohc decompress or feedback process, need call UE input function

    //ether layer
    NETIF_PKG_FAST_PATH_NEED_ETHER_RESOLVE              = 4, //fail, need dest ether layer address resolve,need call UE input function
    NETIF_PKG_FAST_PATH_NEED_ETHER_MULTICAST_INPUT      = 5, //fail, dest address is multicast,need call UE input function
    NETIF_PKG_FAST_PATH_NEED_ETHER_ARP_INPUT            = 6, //fail, arp protocol,need call UE input function
    NETIF_PKG_FAST_PATH_NEED_ETHER_PROTOCOL_INPUT       = 7, //fail, other protocol,need call UE input function

    //IP layer
    NETIF_PKG_FAST_PATH_NEED_IP_UNICAST_INPUT           = 8, //fail, dest ip address is UE local,need call UE input function
    NETIF_PKG_FAST_PATH_NEED_IP_MULTICAST_INPUT         = 9, //fail, dest ip address is multicast,need call UE input function
    NETIF_PKG_FAST_PATH_NEED_IP_REASSEMBLE              = 10, //fail, fragement pkg need reassemble
    NETIF_PKG_FAST_PATH_NEED_IP_BIG_PKG                 = 11, //fail, pkg is too larger, need fragemnt

    //transport layer
    NETIF_PKG_FAST_PATH_NEED_TRANSPORT_PROTOCOL_INPUT   = 12, //fail. not udp or tcp, need input
    NETIF_PKG_FAST_PATH_NEED_TRANSPORT_PORT_LOCAL_INPUT = 13, //fail. need input
    NETIF_PKG_FAST_PATH_NEED_TRANSPORT_PORT_MAPPING     = 14, //fail. need port mapping, need input
    NETIF_PKG_FAST_PATH_NEED_TRANSPORT_TCP_MSS_CHECK    = 15,//fail. tcp MSS check

    //specail
    NETIF_PKG_FAST_PATH_NEED_DISCARD                    = 0x0FFFFFFF, //fail, discard directly

}NetPkgFastPathChkResult;



/*
* fast path check configuration : wan ipv6 info
*/
typedef struct NetifWanIpv6Info_Tag
{
    ip6_addr_t  ipv6GlobalAddr;
    ip6_addr_t  ipv6LinklocalAddr;
}NetifWanIpv6Info;   //32 bytes

/*
* fast path check configuration : wan ipv4 info
*/
typedef struct NetifWanIpv4Info_Tag
{
    ip4_addr_t  ipv4Addr;
}NetifWanIpv4Info;   //4 bytes

/*
* fast path check configuration : wan info
*/
typedef struct NetifWanInfo_Tag
{
    UINT8   ipv4Cid;
    UINT8   ipv6Cid;
    BOOL    bEnableRohc;
    UINT8   rsvd0;
    UINT8   bCfgTft;    /* Whether TFT configed for this WAN */
    /*
     * WAN MTU size, set to MIN(ipv4MTU, ipv6MTU)
     * 1> ipv4MTU: assigned during bearer ACT, if not assigned, set to default value
     * 2> ipv6MTU: nego/set with ICMP PMTU procedure
     * In fact, ipv4MTU and ipv6MTU need to mantain separately. - TBD
    */
    UINT16  mtu;
    UINT16  rsvd;

    /*
     * WAN/UE NW assigned IPV4 address, assigned when bearer ACT.
    */
    NetifWanIpv4Info wanIpv4Info;   // 4 bytes
    /*
     * WAN/UE ipv6 address
     * 1> ipv6 global address, perfix(64 bits) UE RA nego with NW + ID(64 bits) assigned by NW during bearer ACT.
     * 2> ipv6 local address, perfix: 0xFE80://64 + ID(64 bits) assigned by NW
    */
    NetifWanIpv6Info wanIpv6Info;   // 32 bytes
}NetifWanInfo;  //48 bytes

/*
* fast path check configuration : lan ipv6 info
*/
typedef struct NetifLanIPv6Info_Tag
{
    ip6_addr_t  ipv6GlobalAddr;
    ip6_addr_t  ipv6LinklocalAddr;
}NetifLanIPv6Info;

/*
* fast path check configuration : lan ipv4 info
*/
typedef struct NetifLanIPv4Info_Tag
{
    ip4_addr_t  hostIpv4Addr;   //host ipv4 address
    ip4_addr_t  ipv4Addr;       //UE local lan netif address, used for DHCP sever address
}NetifLanIPv4Info;


/*
* fast path check configuration : arp cache for rndis lan
*/
typedef struct NetifArpCache_Tag
{
    ip4_addr_t  addr;       // 4 bytes
    struct eth_addr cache;  // 6 bytes
}NetifArpCache; // 12 bytes


/*
* fast path check configuration : ndp cache for rndis lan
*/

typedef struct NetifNdpCache_Tag
{
    ip6_addr_t  addr;       //16 bytes
    struct eth_addr cache;  /* network order */ // 6 bytes
}NetifNdpCache;     // 24 bytes


/*
* fast path check configuration :rndis lan info
*/
typedef struct NetifRndisLanInfo_Tag
{
    /*
     * UE LAN IPv4 address:
     * 1> host ipv4 address:
     *    a) public ipv4 solution: host ipv4 == NW assigned ipv4
     *    b) private local ipv4 solution: host ipv4 == user configed: 192.168.x.y
     * 2> local lan ipv4 address:
     *    now fix to: 192.168.10.1, only used as a DHCP server address now.
    */
    NetifLanIPv4Info lanIpv4Info;   // 8 bytes

    /*
     * UE local (UE APP used) LAN ipv6 global and local address
     * 1> LAN ipv6 global address, same as UE global address: perfix(64 bits) UE RA nego with NW + ID(64 bits) assigned by NW during bearer ACT.
     * 2> LAN ipv6 local address: perfix: 0xFE80://64 + ID(64 bits) assigned by NW + 1
    */
    NetifLanIPv6Info lanIpv6Info;   // 32 bytes

    /*
     * Cached RNDIS host IPv4 address, and host MAC address
     * 1> a) public ipv4 solution: host ipv4 == NW assigned ipv4
          b) private local ipv4 solution: host ipv4 == user configed: 192.168.x.y
     * 2> host MAC address, not local MAC address
     * 3> updated/set after host trigger ARP procedure
     * Note:
     * why need two: "NetifLanIPv4Info.hostIpv4Addr" and "NetifArpCache.addr" here?
     * a> In fact: these two IP address are the same, but "NetifArpCache.addr" maybe not valid before ARP procedure done
     * b> For UL PKG, FAST PATH checking the "SRC IP" with "NetifLanIPv4Info.hostIpv4Addr", not with "NetifArpCache.addr"
     * c> For DL PKG, FAST PATH checking the "DEST IP" with WAN IPV4, and then need to check whether "NetifArpCache.addr" is valid
     *    Note: "NetifArpCache.addr" is valid, just means ARP procedure done, and host MAC address is valid now
    */
    NetifArpCache arpCache;         // 12 bytes

    /*
     * Cached RNDIS host Ipv6 global address and local address
     * 1> RNDIS host IPv6 global address:
     *    Prefix(64 bits)(NW assigned prefix) + ID(64 bits)(Host generated locally, offen by EU64(MAC_ADDR))
     * 2> RNDIS host IPv6 local address:
     *    Prefix(10 bits) fixed: 0xFE80://10 + ID(118 bits)(Host generated locally, offen by EU64(MAC_ADDR))
     * 3> host MAC address, this MAC address must:
     *    arpCache->eth_addr == ndpCache[global]->eth_addr == ndpCache[local]->eth_addr
     * 4> updated/set after host tigger NDP procedure, or reflush after cache timeout, and etc
    */
    NetifNdpCache ndpCache[NETIF_NDP_CACHE_NUM];    // 48 bytes

    /*
     * UE local MAC address.
     * 1> RNDIS host -> UE, desc MAC address, and
     * 2> UE -> RNDIS host, src MAC address
    */
    struct eth_addr etherAddr;      /* network order */ // 6 bytes
}NetifRndisLanInfo;     // 108 bytes

/*
* fast path check configuration : ppp lan info
*/
typedef struct NetifPppLanInfo_Tag
{
    /*
     * UE local LAN ipv4 address.
     * 1> Now fix to: 192.168.10.1.
     * 2> Now useles.
    */
    NetifLanIPv4Info lanIpv4Info;   // 4 bytes

    /*
     * UE local (UE APP used) LAN, global & local IPv6 address
     * 1> PPP local LAN global ipv6 addr, same as UE global address:
     *     perfix(64 bits) UE RA nego with NW + ID(64 bits) assigned by NW during bearer ACT.
     * 2> PPP local LAN ipv6 local address:
     *     perfix: 0xFE80://64 + ID(64 bits) assigned by NW + 1
    */
    NetifLanIPv6Info lanIpv6Info;   // 32 bytes
}NetifPppLanInfo;   // 36 bytes


typedef struct NetifPortRange_Tag
{
    UINT16      min;
    UINT16      max;
}NetifPortRange;

typedef struct NetifPppChkLanInfo_Tag
{
    UINT16   type   :8;     //lwip_netif_type_t
    UINT16   bMajor :1;     /* If one CID used to bind both PPP and RNDIS/ECM, the first bound LAN is set to "Major" */
    UINT16   rsvd   :7;

    /*
     * PPP LAN MTU size:
     * 2> PPP, - how?
    */
    UINT16  mtu;
    #if 0   /* -TBD */

    NetifPortRange      v4FastPortRange[4];     /* 1> if port in range: [min, max] just means fast path, also need pass to LWIP to do PAT mapping
                                                 * 2> MAX 4 port range, if invalid set to 0
                                                */
    #endif

    NetifPppLanInfo   pppLanInfo;       // 36 bytes
}NetifPppChkLanInfo;  // 40 bytes


typedef struct NetifPppFastChannelInfo_Tag
{
    /*
     * Note:
     * 1> if lanInfo.type != LWIP_NETIF_TYPE_LAN_PPP, just means, PPP LAN is not setup.
     * 2> if wanInfo.ipv4Cid/ipv6Cid set to 0xFF, just means, WAN not bind
    */
    NetifPppChkLanInfo          lanInfo;   // 40 bytes
    NetifWanInfo                wanInfo;   // 48 bytes
}NetifPppFastChkInfo;   //88 bytes

typedef struct NetifFastChkInfo_Tag
{
    NetifPppFastChkInfo     pppInfo;    //88 bytes
}NetifFastChkInfo;      //248 bytes


/* the tcp connection infomation which enable tcp windows scaling*/
typedef struct NetFastPathTcpConnInfo_Tag
{
    UINT8   connIpType;     //valid(4 or 6)
    UINT8   dlScaleValue;   //tcp dl scale value, scale value in DL TCP SYN/SYN ACK pkg
    UINT8   ulScaleValue;   //tcp ul scale value, scale value in UL TCP SYN/SYN ACK pkg
    UINT8   rsvd1;
    UINT32  lastTicks;      //the time ticks recving the last tcp pkg for this connection
    UINT16  hostPort;       //host port, for ul pkg, it is source port
    UINT16  rmtPort;        //remote port, for ul pkg, it is dest port
    UINT8   hostAddr[16];   //host address, for ul pkg, it is source addrinfo
    UINT8   rmtAddr[16];    //remote address, for ul pkg, it is dest addrinfo
}NetFastPathTcpConnInfo;    //44 bytes


/******************************************************************************
 * NetifDlPkgFastPathIsr
 * Description: DL pkg fast path process
 * input: UINT8 cid, DlPduBlock *pDlPdu, NetifFastChannelInfo *pChannelChkInfo
 * output:
 * Comment:
******************************************************************************/
void NetifDlPkgFastPathIsr(UINT8 cid, UINT32 pkgNum, DlPduBlock *pDlHdr, DlPduBlock *pDlTail, NetifFastChkInfo *pChannelChkInfo);


/******************************************************************************
 * NetifUlPkgFastPathCheck
 * Description: UL pkg fast path process
 * input: UINT8 lanType(lwip_netif_type_t), UlPduBlock *pUlPdu, void *chkInfo
 * output:
 * Comment:
******************************************************************************/
//void NetifUlPkgFastPathCheck(UINT8 lanType, UlPduBlock *pUlPdu, void *chkInfo);
void NetifUlPkgFastPath(UINT8 lanType, UlPduBlock *pUlHdr, void *pUlChkInfo);


/******************************************************************************
 * NetifDlListFastPathGet
 * Description: Get all DL PDU list from "gNetifDlFastPendingList"
 * input:   DlPduBlock **ppHead     //in & out
 *          DlPduBlock **ppTail     //in & out
 * output:  if not pending, 
"*ppHead" & "*ppTail" return NULL
 * Comment: this called in Tx task only
******************************************************************************/
void NetifDlListFastPathGet(DlPduBlock **ppHead, DlPduBlock **ppTail);

UINT8 *NetifGetFastRndisDeviceMacAddr(void *pFastChkInfo);

UINT8 *NetifGetFastRndisHostMacAddr(void *pFastChkInfo);

UINT32 NetifGetFastRndisHostIpAddr(void *pFastChkInfo);

UINT32 NetifGetFastRndisWanIpAddr(void *pFastChkInfo);

UINT8 *NetifGetFastRndisIPv6MacAddr(void *pFastChkInfo, UINT8 index);

INT8 NetFastGetUlTcpConnScaleValue(UINT8 connIpType, UINT8 *hostAddr, UINT8 *rmtAddr, UINT16 hostPort, UINT16 rmtPort);

INT8 NetFastGetDlTcpConnScaleValue(UINT8 connIpType, UINT8 *hostAddr, UINT8 *rmtAddr, UINT16 hostPort, UINT16 rmtPort);

const void* NetFastUlNewTcpConnInfo(UINT8 connIpType, UINT8 *hostAddr, UINT8 *rmtAddr, UINT16 hostPort, UINT16 rmtPort, UINT8 ulScale);

const void* NetFastDlNewTcpConnInfo(UINT8 connIpType, UINT8 *hostAddr, UINT8 *rmtAddr, UINT16 hostPort, UINT16 rmtPort, UINT8 dlScale);

void NetFastDelTcpConnInfo(UINT8 connIpType, UINT8 *hostAddr, UINT8 *rmtAddr, UINT16 hostPort, UINT16 rmtPort);

#endif

