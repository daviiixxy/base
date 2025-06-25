#ifndef NM_HDR_H
#define NM_HDR_H
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2018- Copyrights of Qualcomm Ltd.
 File name:      - netmgr.h
 Description:    - ps network data path linkup/linkdown function header
 History:        - 01/02/2018, Originated by xwang
 ******************************************************************************
******************************************************************************/

#include "commontypedef.h"
#include "lwip/ip_addr.h"
#if (RTE_PPP_EN==1)
#include "netif/ethernet.h"
#include "lwip/opt.h"
#endif
#include "cmips.h"

/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/
#define NM_PDN_TYPE_MAX_DNS_NUM     2
#define NM_MAX_DNS_NUM              4
#define NM_CID_BIND_TO_NONE         255
#define NM_ADDR_MAX_LENGTH          16
#define NM_PS_DEFAULT_CID           0
#define NM_PS_CID_MIN               0       //1, attached EPS bearer CID is changed to 0.
#define NM_PS_CID_MAX               10
#define NM_PS_INVALID_CID           255

/*
 * set bit B to 1 in D
 * example:
 *  NmBit1Set(0x00, 0) = 0x01
 *  NmBit1Set(0x01, 4) = 0x11
*/
#define NmBit1Set(D, B)   ((D) |= (1<<(B)))

/*
 * set bit B to 0 in D
 * example:
 *  NmBit0Set(0xFF, 0) = 0xFE
 *  NmBit0Set(0xFE, 4) = 0xEE
*/
#define NmBit0Set(D, B)   ((D) &= (~(1<<(B))))


/*
 * default setting for ping
*/
#define NM_PING_DEFAULT_COUNT       15
#define NM_PING_KEEP_COUNT          255
#define NM_PING_DEFAULT_PAYLOAD_SIZE    32
#define NM_PING_DEFAULT_TIMEOUT     20  //20s



#define NM_MAGIC_WORD               0xA5B7

/******************************************************************************
 *****************************************************************************
 * STRUCT/ENUM
 *****************************************************************************
******************************************************************************/

#if 0
/*
 * 0x0920 - 0x0930, SIGID used for netmanager
*/
typedef enum
{
    SIG_NM_BASE = 0x0920,

    SIG_NM_ATI_CNF, //NmAtiCnf
    SIG_NM_ATI_IND, //NmAtiInd

    SIG_NM_END  = 0x0927
}NetMgrSigId;
#endif

/*
 * the action result
*/
typedef enum
{
    NM_SUCCESS = 0,
    NM_FAIL = 1,
}NmResult;

#if 0
/*
 * ReqId & CnfId in "SIG_NM_ATI_CNF"
*/
typedef enum NM_ATI_ACTION_ID_TAG
{
    NM_ATI_ACTION_BASE = 0x1000,

/****************************************************/
    NM_ATI_ASYNC_BASE = 0X1001,

    NM_ATI_ASYNC_GET_DNS_REQ, //ASYNC reqeust
    NM_ATI_ASYNC_GET_DNS_CNF, //ASYNC cnf

    NM_ATI_ASYNC_END = 0X10FF,

/*****************************************************/

    NM_ATI_SYNC_BASE = 0X1100,

    NM_ATI_SYNC_GET_NET_INFO_REQ,

    NM_ATI_SYNC_IS_ANY_ACTIVE_SOCKET_REQ,

    NM_ATI_SYNC_END = 0X11FF,

/*****************************************************/

    NM_ATI_ACTION_END = 0xffff,
}NM_ATI_ACTION_ID;

/*
 * IndId in "SIG_NM_ATI_IND"
*/
typedef enum NM_ATI_INDICATION_ID_TAG
{
    NM_ATI_IND_BASE = 0x2000,

    NM_ATI_PING_RET_IND,    //NmAtiPingResultInd
    NM_ATI_IPERF_RET_IND,   //NmAtiIperfResultInd

    NM_ATI_NET_INFO_IND,    //NmAtiNetInfoInd


    NM_ATI_IND_END = 0xffff,
}NM_ATI_INDICATION_ID;
#endif

typedef enum NmCmsPrimId_enum
{
    NM_ATI_PRIM_BASE    = 0x00,

    /*
     * ASYN PRIM ID, REQ/CNF
    */
    NM_ATI_ASYNC_BASE   = 0x00,

    NM_ATI_ASYNC_GET_DNS_REQ, //ASYNC reqeust
    NM_ATI_ASYNC_GET_DNS_CNF, //NmAtiGetDnsCnf

    NM_ATI_ASYNC_END    = 0X1F,

    /*
     * SYN PRIM ID
    */
    NM_ATI_SYNC_BASE    = 0x20,
    NM_ATI_SYNC_GET_NET_INFO_REQ,
    NM_ATI_SYNC_IS_ANY_ACTIVE_SOCKET_REQ,
    NM_ATI_SYNC_END     = 0x3F,

    /*
     * NM IND PRIM ID
    */
    NM_ATI_PING_RET_IND = 0x40,    //NmAtiPingResultInd
    NM_ATI_IPERF_RET_IND,   //NmAtiIperfResultInd
    NM_ATI_NET_INFO_IND,    //NmAtiNetInfoInd
    NM_ATI_SNTP_RET_IND,
#if (RTE_PPP_EN==1)
    NM_ATI_LAN_INFO_IND,
#endif
    NM_ATI_PRIM_END = 0XFF,
}NmCmsPrimId;


/*
 * NM NET type
*/
typedef enum
{
    NM_NET_TYPE_INVALID = 0,    //net not available
    NM_NET_TYPE_IPV4 = 1,       //ipv4 available
    NM_NET_TYPE_IPV6 = 2,       //ipv6 available
    NM_NET_TYPE_IPV4V6 = 3,     //ipv4&ipv6 available
    NM_NET_TYPE_IPV6preparing = 4, //ipv6 preparing
    NM_NET_TYPE_IPV4_IPV6preparing = 5, //ipv4 available &ipv6 preparing
}NmNetIpType;

/*
 * the ip address type
*/
typedef enum
{
    NM_ADDR_INVALID_ADDR = 0,
    NM_ADDR_IPV4_ADDR,          // 4 bytes length
#if (RTE_PPP_EN==1)
    NM_ADDR_IPV6_ID,             //8 bytes length
    NM_ADDR_FULL_IPV6_ADDR      //16 bytes length
#else
    NM_ADDR_FULL_IPV6_ADDR,     //16 bytes length
    NM_ADDR_IPV6_ID             //8 bytes length
#endif
}NmAddrType;

/*
 *NM LAN type
*/
typedef enum
{
    NM_LAN_TYPE_INVALID = 0,
    NM_LAN_TYPE_RNDIS,
    NM_LAN_TYPE_ECM,
    NM_LAN_TYPE_PPP,
}NmLanType;

/*
 *NM LAN NET type
*/
typedef enum
{
    NM_LAN_NET_TYPE_INVALID = 0,
    NM_LAN_NET_TYPE_ETH,
    NM_LAN_NET_TYPE_PPP,
}NmLanNetType;



/*
 *NM LAN link layer status type
*/

typedef enum
{
    NM_LAN_LINK_STATUS_DISCONNECTED,
    NM_LAN_LINK_STATUS_CONNECTED,
}NmLanLinkStatus;

/*
*NM LAN data path status
*/
typedef enum
{
    NM_LAN_NET_DEACTIVED,   //lan data path is deactive
    NM_LAN_NET_ACTIVED,     //lan data path is active
    NM_LAN_NET_ACTIVED_AND_CHANGED, //lan data path is active and changed, such as ipv4 ready change to ipv4ipv6 ready
}NmLanNetStatus;


/*
 * NM ethernet LAN (RNDIS/ECM) data path ip4 mode (ip6 is always pass through mode)
*/
typedef enum
{
    NM_ETH_LAN_IP4_PATH_MODE_PASSTHROUGH = 0,   //pass through mode
    NM_ETH_LAN_IP4_PATH_MODE_NAT,               //nat mode
}NmEthLanIp4PathMode;


/*
*NM LAN ctrl api
*/
typedef enum
{
    NM_LAN_CTRL_ACTION_BIND = 0,   //pass through mode
    NM_LAN_CTRL_ACTION_UNBIND,     //nat mode
}NmLanCtrlAction;

#ifdef PPP_SUPPORT
typedef struct NetMgrWanIpv6Info_Tag
{
    ip6_addr_t  ipv6GlobalAddr;
    ip6_addr_t  ipv6LinklocalAddr;

    UINT8       dnsNum;
    UINT8       rsvd0;
    UINT16      rsvd1;
    ip6_addr_t  dns[NM_PDN_TYPE_MAX_DNS_NUM];
}NetMgrWanIpv6Info;   //52 bytes


typedef struct NetMgrWanIpv4Info_Tag
{
    ip4_addr_t  ipv4Addr;

    UINT8       dnsNum;
    UINT8       rsvd0;
    UINT16      rsvd1;
    ip4_addr_t  dns[NM_PDN_TYPE_MAX_DNS_NUM];
}NetMgrWanIpv4Info;   //16 bytes


typedef struct NetMgrWanInfo_Tag
{
    UINT8 ipType;
    UINT8 ipv4Cid;
    UINT8 ipv6Cid;
    BOOL bEnableRohc;

    NetMgrWanIpv4Info wanIpv4Info;
    NetMgrWanIpv6Info wanIpv6Info;
}NetMgrWanInfo;

typedef struct NetMgrLanIPv6Info_Tag
{
    ip6_addr_t  ipv6GlobalAddr;
    ip6_addr_t  ipv6LinklocalAddr;
}NetMgrLanIPv6Info;

typedef struct NetMgrLanIPv4Info_Tag
{
    ip4_addr_t  ipv4Addr;
}NetMgrLanIPv4Info;

#if 0
typedef struct NetMgrRndisLanInfo_Tag
{
    UINT8  ipType;
    UINT8  rsvd0;
    UINT16 rsvd1;

    NetMgrLanIPv4Info lanIpv4Info;
    NetMgrLanIPv6Info lanIpv6Info;

    UINT8 etherAddr[ETH_HWADDR_LEN];
}NetMgrRndisLanInfo;
#endif

typedef struct NetMgrPppLanInfo_Tag
{
    UINT8  ipType;
    UINT8  rsvd0;
    UINT16 rsvd1;

    NetMgrLanIPv4Info lanIpv4Info;
    NetMgrLanIPv6Info lanIpv6Info;
}NetMgrPppLanInfo;

typedef struct NetMgrLanInfo_Tag
{
    UINT8 type;
    union
    {
        //NetMgrRndisLanInfo rndisLanInfo;
        NetMgrPppLanInfo   pppLanInfo;
    }lanInfo;
}NetMgrLanInfo;



typedef struct NetMgrEthLanCfg_Tag
{
    UINT8       ethLanIp4PathMode;  //NmEthLanIp4PathMode, nat/passthrough mode
    UINT8       rsvd0;
    UINT16      rsvd1;

    ip4_addr_t  ethLocalAddr;       //Ethernet LAN netif (ECM/RNDIS) address, example: 192.168.10.1
    ip4_addr_t  ethHostAddr;        //host lan netif(ECM/RNDIS) address, if NAT mode, example: 192.168.10.5
    ip4_addr_t  ethHostNetMask;     //host lan netif(ECM/RNDIS) netmask.if NAT mode, example:255.255.255.0; if the setting is 0.0.0.0, ue will use the deault value
}NetMgrEthLanCfg;   // 12 bytes

#if 1
typedef struct NetMgrPppLanCfg_Tag
{
    ip4_addr_t  pppLocalAddr;       //PPP LAN netif address, should not same as: "ethLocalAddr", example: 192.168.20.1
}NetMgrPppLanCfg;


typedef struct NetMgrLanCfg_Tag
{
    NetMgrEthLanCfg     ethLanCfg;
    //NetMgrPppLanCfg     pppLanCfg;
}NetMgrLanCfg;      // 12 bytes


/*
*/
typedef struct NetMgrLanDataPathCap_Tag
{
    UINT8           lanType;        /* NmNetLanType */
    BOOL            bConnected;     /* Whether LAN is connected/disconnected
                                     * 1> if connected, CCIO need to try linkup LAN, if ethernet(RNDID/ECM)/PPP enabled
                                     * 2> if disconnected, CCIO need to linkdown LAN
                                    */
    UINT16          rsvd0;

    /*
     * Some basic lan info
    */
    UINT8           lanIpType;      /* NmNetIpType */
    UINT8           lanBindIp4Cid;  /* If not bind, set to : 0xFF */
    UINT8           lanBindIp6Cid;  /* If not bind, set to : 0xFF */
    UINT8           rsvd1;
}NetMgrLanDataPathCap;

/*
 * When LAN (PPP/RNDIS/ECM) state changes (connect/disconnect) need to notify CCIO
*/
//void radioDevNotifyTcpipDataPathCapability(NetMgrLanDataPathCap *pLanDataPathCap);

/*
 * query the lan tcpip data path capability, called by CCIO, to descide whether can do lan link up
*/
//NmResult NetMgrQueryLanTcpipDataPathCapability(NmLanType lanType, NetMgrLanDataPathCap *pLanDataPathCap);


/*
 *NM LAN channel TCPIP data path status
*/
typedef struct NetMgrLanChannelTcpipDataPathStatus_Tag
{
    NmLanNetStatus status; //event status with (NM_LAN_NET_DEACTIVED/NM_LAN_NET_ACTIVED/NM_LAN_NET_ACTIVED_AND_CHANGED); query return (NM_LAN_NET_DEACTIVED/NM_LAN_NET_ACTIVED)
    UINT8           lanIpType;      /* NmNetIpType */
    UINT8           lanBindIp4Cid;  /* If not bind, set to : 0xFF */
    UINT8           lanBindIp6Cid;  /* If not bind, set to : 0xFF */
    UINT8           rsvd1;
}NetMgrLanChannelTcpipDataPathStatus;

/*
/NM LAN channel TCPIP data path info(assign to host)
*/
typedef struct NetMgrLanTcpipDataPathHostInfo_Tag
{
    /*
     * Some basic lan info
    */
    UINT8           lanIpType;       /* NmNetIpType */
    UINT8           lanBindIp4Cid;   /* If not bind, set to : 0xFF */
    UINT8           lanBindIp6Cid;   /* If not bind, set to : 0xFF */
    UINT8           rsvd1;

    ip4_addr_t      hostIp4Addr;      /*the ip4 address which will assigned to host*/
    UINT32          hostIp6Prefix[2]; /*the ip6 prefix which will assigned to host*/
    UINT32          hostIp6Id[2];     /*the ip6 ID which will assigned to host*/

    ip4_addr_t      hostIp4Dns[NM_PDN_TYPE_MAX_DNS_NUM]; /*the ip4 dns which will assigned to host*/
    ip6_addr_t      hostIp6Dns[NM_PDN_TYPE_MAX_DNS_NUM]; /*the ip6 dns which will assigned to host*/

}NetMgrLanTcpipDataPathHostInfo;

/*
*/
typedef struct NmAtiLanInfo_Tag
{
    UINT8       lanType;        /*NmLanNetType, ETH/PPP LAN*/
    BOOL        bound;          /*whether current LAN , bind a WAN/netif */

    UINT8       lanBindIp4Cid;  /* If not bind, set to : 0xFF */
    UINT8       lanBindIp6Cid;  /* If not bind, set to : 0xFF */
}NmAtiLanInfo;

#endif
/*
 * Signal: NM_ATI_SIGNAL_CNF
 * signal to AT CMD SRV task,
 *  just the confirmation for "NM_ATI_ACTION_ID" request
*/
typedef struct NmAtiCnf_Tag
{
    struct {
        UINT16  cnfId;        //NM_ATI_ACTION_ID
        UINT16  srcHandler;   //Handler
        UINT16  rc;           //NmResult, return code
        UINT16  reserved;
    }header;

    UINT8   body[];
}NmAtiCnf;

/*
 * Signal: SIG_NM_ATI_IND
 * signal to AT CMD SRV task,
 *  just the result indication for some TCP/IP app (ping/iperf, etc)
*/
typedef struct NmAtiIndTag
{
    struct {
        UINT16  indId;      //NM_ATI_INDICATION_ID
        UINT16  reserved;
    }header;

    UINT8   body[];
}NmAtiInd;
#endif

/******************************************************************************
 * Net manager entity
******************************************************************************/

/*
 * PS NET status, status from CEREG
*/
typedef enum NmPsNetStatus_Tag
{
    /*
     * PS is not registered, and UE is not under dialing
    */
    NM_PS_NET_NOT_DIAL,

    /*
     * 1> PS is not registered, but under registration
     * 2> and no ACT NETIF (bearer)
    */
    NM_PS_NET_NOT_REG,

    /*
     * 1> PS is OOS (out of service)
     * 2> and must have ACT NETIF (bearer);
     * 3> If no ACT NETIF (bearer), status need to change to "NM_PS_NET_NOT_REG"
    */
    NM_PS_NET_OOS,

    /*
     * PS is registered, and NETIF maybe comes later
    */
    NM_PS_NET_REG
}NmPsNetStatus;

typedef struct NmEntity_Tag
{
    UINT8   psNetStatus;    //NmPsNetStatus
    UINT8   rsvd0;

    /*
     * CID valid value: 1 - 15;
     * If one CID (bearer) activated, related bit set to 1
    */
    UINT16  actCidsBitmap;
}NmEntity;


/******************************************************************************
 * A blocked callback designation, which called in LWIP task
******************************************************************************/
typedef enum NmBlockCallbackMsgId_Tag
{
    NM_BLOCK_CB_INVALID_ID,
    NM_NET_LINK_UP,
    NM_NET_LINK_DOWN,
#if (RTE_PPP_EN==1)
    NM_NET_LAN_LINK_UP,
    NM_NET_LAN_LINK_DOWN,
    NM_NET_LAN_LINK_LAYER_STATUS_CHANGE,
#endif
    NM_GET_NET_INFO,
#if (RTE_PPP_EN==1)
    NM_CLEAR_DNS_CACHE,
    NM_GET_DNS_SERVER,
    NM_SET_DNS_SERVER,
#endif
    NM_START_SNTP,
    NM_STOP_SNTP,
}NmBlockCallbackMsgId;

typedef struct NmBlockCallbackHdr_Tag
{
    UINT8   blcokMsgId;
    UINT8   rsvd0;
    UINT16  inputParaLen;
    UINT16  outputParaLen;
    UINT16  magicWord;      //2 bytes magic
}NmBlockCallbackHdr;    //8 bytes


/*
 * The ip address structure
 * NM_ADDR_IPV4_ADDR: 12~15:0 0~3:address
 * NM_ADDR_FULL_IPV6_ADDR: 0~15 prefix:id
 * NM_ADDR_IPV6_ID: 8~15:0 0~7:id
*/
typedef struct NmIpAddr_Tag
{
    UINT8   addrType;   //NmAddrType
    UINT8   reserved0;
    UINT16  reserved1;
    UINT8   addr[NM_ADDR_MAX_LENGTH];
}NmIpAddr;  //20 bytes


/******************************************************************************
 * ECIPERF related
******************************************************************************/
/*
 * iperf mode type
*/
typedef enum NmIperfAction_Enum
{
    NM_IPERF_STOP_ALL = 0,
    NM_IPERF_START_CLIENT = 1,
    NM_IPERF_STOP_CLIENT = 2,
    NM_IPERF_START_SERVER = 3,
    NM_IPERF_START_UDP_NAT_SERVER = 4,   //special mode
    NM_IPERF_STOP_SERVER = 5
}NmIperfAction;

/*
 * iperf network domain type
*/
typedef enum NmIperfProtocol_Enum
{
    NM_IPERF_PROTOCOL_UDP = 0,
    NM_IPERF_PROTOCOL_TCP = 1,
}NmIperfProtocol;

typedef struct NmIperfReq_Tag
{
    UINT8       reqAct;     //NmIperfAction
    UINT8       protocol;   //NmIperfProtocol
    UINT16      port;       //client/server UDP/TCP port

    BOOL        destAddrPresent;
    BOOL        tptPresent;
    BOOL        payloadSizePresent;
    BOOL        pkgNumPresent;

    ip_addr_t   destAddr;   //client, or UDP NAT server DEST address, 20 bytes
    UINT32      tpt;        //client through put setting, in bps, such as: 20000, just means 20000 bps

    UINT16      payloadSize;//client parameter
    UINT16      pkgNum;     //client parameter

    BOOL        durationPresent;
    BOOL        rptIntervalPresent;
    UINT16      rsvd0;

    UINT16      durationS;      //client/server parameter, in seconds
    UINT8       rptIntervalS;   //report internal in seconds
    UINT8       rsvd1;

    UINT16      reqHandle;
    UINT16      rsvd2;
}NmIperfReq;    //46 bytes



/******************************************************************************
 * PS netif configuration info
 * Use to link up one netif
******************************************************************************/
typedef struct NmIfConfiguration_Tag
{
#if (RTE_PPP_EN==0)
    UINT8       dnsNum;
    UINT8       mtuPresent; //if mtu is invalid ,this value will be zero
#else
    UINT16      dnsNum : 3;
    UINT16      mtuPresent : 1; //if mtu is invalid ,this value will be zero
    UINT16      cgevReason: 4;  //CmiPsPdnTypeReason
    UINT16      rsvd0 : 8;
    UINT8       clatTranslatedPDN; /* Hack, need to remove after PS CL */
#endif
    UINT16      mtu;
    NmIpAddr    ipv4Addr;
    NmIpAddr    ipv6Addr;
    NmIpAddr    dns[NM_MAX_DNS_NUM];
}NmIfConfiguration; //124 bytes


/******************************************************************************
 * NM_ATI_PRIM_GT_DNS_REQ
 * DNS query to get URL IP ADDR
******************************************************************************/
#define NM_MAX_URL_STR_LEN  256

typedef struct NmAtiGetDnsReqTag
{
    CHAR        url[NM_MAX_URL_STR_LEN];
}NmAtiGetDnsReq;

/*
 * NM_ATI_PRIM_GT_DNS_CNF
 * Suggest carry the UINT8 IP ADDR, - TBD
*/
typedef struct NmAtiGetDnsCnfTag
{
    CHAR response[64]; //need support ipv6 dns resolve
}NmAtiGetDnsCnf;


/******************************************************************************
 * NM_ATI_PRIM_PING_RESULT_IND
******************************************************************************/
typedef enum NmPingResultEnum_Tag
{
    NM_PING_RET_DONE,       //ping succ, and ping done
    NM_PING_RET_ONE_SUCC,   //One ping is succ, and maybe ping is still ongoing
    NM_PING_RET_ONE_FAIL,   //One ping is fail, and maybe ping is still ongoing
    NM_PING_RET_ONE_SEND_FAIL,  //One ping send fail
    NM_PING_PARAM_ERROR,    //input parameters error
    NM_PING_DNS_ERROR,      //DNS failed
    NM_PING_SOCKET_ERROR,   //socket error
    NM_PING_ALL_FAIL,
    NM_PING_ERROR
}NmPingResultEnum;

#define NM_ATI_PING_DEST_IP_STR_LEN    40

typedef struct NmAtiPingResultIndTag
{
    UINT8   result;         //NmPingResultEnum
    UINT8   reserved;
    UINT16  packetLossRate; //valid when "NM_PING_RET_DONE", RATE*100, example: 23 just means: 23%

    UINT16  requestNum;     //if "NM_PING_RET_ONE_SUCC/NM_PING_RET_ONE_FAIL", set to 1
    UINT16  responseNum;    //if "NM_PING_RET_ONE_SUCC" set 1, if "NM_PING_RET_ONE_FAIL", set to 0

    /*
     * ms,
     * if "NM_PING_RET_ONE_SUCC", set RTT at this time,
     * if "NM_PING_RET_ONE_FAIL", set max wait time
    */
    UINT32  minRtt;
    UINT32  maxRtt;         //ms
    UINT32  avgRtt;         //ms

    /*
     * Dest IP address, in string format;
     * For Ipv4, example: "10.10.10.10"
     * For Ipv6, example: "1234:1234:1234:1234:1234:1234:1234:1234"
    */
    CHAR    pingDst[NM_ATI_PING_DEST_IP_STR_LEN];
}NmAtiPingResultInd;  //60 bytes


typedef enum NmSntpResultEnum_Tag{
    SNTP_RESULT_OK = 0,
    SNTP_RESULT_CREATE_CLIENT_SOCK_FAIL,
    SNTP_RESULT_PARAMTER_INVALID,
    SNTP_RESULT_URL_RESOLVE_FAIL,
    SNTP_RESULT_NETWORK_NOT_READY,
    SNTP_RESULT_RETRY_REACH_MAX_TIMES,
    SNTP_RESULT_FAIL,
}NmSntpResultEnum;



typedef struct NmAtiSntpResultInd_Tag{
    UINT16 result;
    UINT16 autoSync;
    UINT32 time;
    UINT32 us;
}NmAtiSntpResultInt;

typedef struct NmNetIfDnsCfg_Tag{
    UINT8 dnsNum;
    UINT8 rsvd0;
    UINT16 rsvd1;
    ip_addr_t  dns[NM_MAX_DNS_NUM];
}NmNetIfDnsCfg; //84 bytes

/******************************************************************************
 * NM_ATI_IPERF_RET_IND
******************************************************************************/
typedef enum NmIperfModeEnum_Tag
{
    NM_IPERF_MODE_CLIENT,       //ECIPERF tmp report for every rtpInterval, iperf task is on goging
    NM_IPERF_MODE_SERVER,   //ECIPERF the last report, iperf task end
}NmIperfModeEnum;

typedef enum NmIperfResultEnum_Tag
{
    NM_IPERF_END_REPORT_SUCCESS,   //ECIPERF the last report, iperf task end
    NM_IPERF_ONE_REPORT_SUCCESS,   //ECIPERF tmp report for every rtpInterval, iperf task is on goging
    NM_IPERF_PARAM_ERROR,   //iperf parameter error, iperf task end
    NM_IPERF_SOCKET_ERROR,  //iperf socket error, iperf task end
    NM_IPERF_MALLOC_ERROR,  //iperf task malloc fail, iperf task end
}NmIperfResultEnum;

typedef struct NmAtiIperfResultIndTag
{
    UINT8   result;   //NmIperfResultEnum
    UINT8   mode;     //NmIperfModeEnum
    UINT16  reserved;

    /*
     * "dataNum"/"bandwidth" only valid when
     * 1> "result" == NM_IPERF_END_REPORT_SUCCESS, total pkg bytes and average bandwith (send/recv) during the whole duration;
     * 2> "result" == NM_IPERF_ONE_REPORT_SUCCESS, total pkg bytes and bandwith (send/recv) during report interval
    */
    UINT32  dataNum;    //client mode, total send packet bytes; for server mode, total receive packet bytes
    UINT32  bandwidth;  //bps
}NmAtiIperfResultInd;

/******************************************************************************
 * NM_ATI_SYNC_GET_NET_INFO_REQ
******************************************************************************/
typedef struct NmAtiGetNetInfoReq_Tag
{
    /*
     * 1> If user want to get the default netif info, CID could set to "NM_PS_DEFAULT_CID";
     * 2> Valid value: [NM_PS_CID_MIN - NM_PS_CID_MAX]/[1-15]
    */
    UINT8       cid;
    UINT8       rsvd0;
    UINT16      rsvd1;
}NmAtiGetNetInfoReq;


/*
 * the netif related ip info
*/
typedef struct NmNetIpv6Info_Tag{
    ip6_addr_t  ipv6Addr;

    UINT8       dnsNum;
    UINT8       rsvd0;
    UINT16      ipv6GetPrefixDelay;
    ip6_addr_t  dns[NM_PDN_TYPE_MAX_DNS_NUM];
}NmNetIpv6Info;   //52 bytes


typedef struct NmNetIpv4Info_Tag{
    ip4_addr_t  ipv4Addr;

    UINT8       dnsNum;
    UINT8       rsvd0;
    UINT16      rsvd1;
    ip4_addr_t  dns[NM_PDN_TYPE_MAX_DNS_NUM];
}NmNetIpv4Info;   //16 bytes


/*
 * netif type
*/
typedef enum NmNetifType_Tag
{
    NM_INVALID_NETIF,
    NW_DEFAULT_NETIF,   //default netif, all socket data default to send via this netif
#if (RTE_PPP_EN==1)
    NM_OTHER_NETIF
#endif
    //NW_IMS_NETIF      //FFS
}NmNetifType;


/*
 * netif status
*/
typedef enum NmNetifStatus_Tag
{
    /*
     * no netif created, and UE is not under dialing
    */
    NM_NO_NETIF_NOT_DIAL,

    /*
     * No netif created
     * 1> maybe UE is not registered, but already under dialing, and NETIF maybe be OK later
     * 2> or APP request one specific NETIF (by CID), which not created,
     * 3> when a NETIF deactivated
    */
    NM_NO_NETIF_OR_DEACTIVATED,

    /*
     * netif is created, but NETIF is OOS
    */
    NM_NETIF_OOS,

    /*
     * NETIF is suspend
     * When NETIF is OOS, must be also suspend, in such case, state should be set to OOS
    */
    //NM_NETIF_SUSPEND,

    /*
     * NETIF is activated
    */
    NM_NETIF_ACTIVATED,

    /*
     * NETIF ACTED, but some info changed, such as:
     * 1> ipv4v6 type, ipv6 RS success later, need to report NETIF changed;
     * 2> ipv4v6 two bearers, if one bearer deactivated, but another one is still exist, also need to report NETIF changed;
     * 3> This status only used for event indication report;
    */
    NM_NETIF_ACTIVATED_INFO_CHNAGED
}NmNetifStatus;


typedef enum NmNetifStatusChangeCause_Tag
{
#if (RTE_PPP_EN==1)
    NM_STATUS_CHANGE_INVALID,
#endif
    NM_STATUS_CHANGE_LINK_UP,           /* IPV6 and IPV4 bearer/netif set up, maybe one IPV4V6 bearer, or two bearers (one Ipv4, one Ipv6) */
#if (RTE_PPP_EN==0)
    NM_STATUS_CHANGE_LINK_DOWN,
#else
    NM_STATUS_CHANGE_LINK_UP_IPV4,      /* Only IPV4 bearer/netif set up */
    NM_STATUS_CHANGE_LINK_UP_IPV6,      /* Only IPV6 bearer/netif set up */
#endif
    NM_STATUS_CHANGE_RA_SUCCESS,        /* IPV6 RS succ, IPV6 full address gotten */
    NM_STATUS_CHANGE_RA_TIMEOUT,        /* IPV6 RS timeout */
    NM_STATUS_CHANGE_ENTER_OOS,
    NM_STATUS_CHANGE_EXIT_OOS,
#if (RTE_PPP_EN==1)
    NM_STATUS_CHANGE_LINK_DOWN,         /* bearer/netif down, which bearer? CID indicated in: NmAtiNetifInfo->ipv4Cid/ipv6Cid */
    NM_STATUS_CHANGE_LINK_DOWN_IPV4,    /* 1> If two bearers used for this netif, this just means IPV4 bearer deactivated,
                                         *    and only IPV6 bearer now.
                                         * 2> which IPV4 bearer deactivated? indicated in: NmAtiNetifInfo->ipv4Cid.
                                        */
    NM_STATUS_CHANGE_LINK_DOWN_IPV6,    /* 1> If two bearers used for this netif, this just means IPV6 bearer deactivated,
                                         *    and only IPV4 bearer now.
                                         * 2> which IPV4 bearer deactivated? indicated in: NmAtiNetifInfo->ipv6Cid.
                                        */
#endif
#if (RTE_PPP_EN==0)
    NM_STATUS_CHANGE_LINK_UP_PDN_IPV4_ONLY,     /* Ipv4v6 bearer request, but only ipv4 supported/activated */
    NM_STATUS_CHANGE_LINK_UP_PDN_IPV6_ONLY,     /* Ipv4v6 bearer request, but only ipv6 supported/activated */
    NM_STATUS_CHANGE_LINK_UP_PDN_SINGLE_ADDRESS_ONLY,   /* Ipv4v6 bearer request, but only ipv4 or v6 supported/activated */
    NM_STATUS_CHANGE_LINK_UP_PDN_SINGLE_ADDR_ONLY_ALLOWED_AND_SECOND_BEARER_FAILED, /* Ipv4v6 bearer request, and the second bearer act failed */
#endif
    NM_STATUS_CHANGE_OTHERS,
}NmNetifStatusChangeCause;

#if (RTE_PPP_EN==0)
typedef struct NmAtiNetifInfo_Tag
{
    UINT8               netStatus;  //NmNetifStatus
    UINT8               netifType;  //NmNetifType
    UINT8               ipType;     //NmNetIpType
    UINT8               cause;   //NmNetifStatusChangeCause

    /*
     * 1> if NETIF is ipv4v6 type:
     *    a> if two bearers created, "ipv4Cid" is for IPV4 bearer, and "ipv6Cid" is for IPV6 bearer
     *    b> if one bearer (ipv4v6) created, "ipv4Cid" = "ipv6Cid"
     * 2> if NETIF is ipv4 type
     *    a> "ipv6Cid" should set to 0
     * 3> if NETIF is ipv6 type
     *    a> "ipv4Cid" should set to 0
    */
    UINT8               ipv4Cid;
    UINT8               ipv6Cid;
    UINT16              rsvd1;

    NmNetIpv4Info       ipv4Info;   //first need to check "ipType", if "ipType" indicate ipv4 or ipv4v6, then this info must be valid
    NmNetIpv6Info       ipv6Info;   //first need to check "ipType", if "ipType" indicate ipv6 or ipv4v6, then this info must be valid
}NmAtiNetifInfo;    // 76 bytes

#else
/*
 * One WAN NETIF basic info, note, these info will return to user, should be clear
*/
typedef struct NmAtiNetifInfo_Tag
{
    UINT8               netStatus;  //NmNetifStatus
    UINT8               netifType;  //NmNetifType
    UINT8               ipType;     //NmNetIpType
    UINT8               rsvd0;
    UINT8               cause;   //NmNetifStatusChangeCause

    /*
     * 1> if NETIF is ipv4v6 type:
     *    a> if two bearers created, "ipv4Cid" is for IPV4 bearer, and "ipv6Cid" is for IPV6 bearer
     *    b> if one bearer (ipv4v6) created, "ipv4Cid" = "ipv6Cid"
     * 2> if NETIF is ipv4 type
     *    a> "ipv6Cid" should set to LWIP_PS_INVALID_CID
     * 3> if NETIF is ipv6 type
     *    a> "ipv4Cid" should set to LWIP_PS_INVALID_CID
     * ==================================================
     * Note, in case of "NmAtiNetInfoInd" indication.
     * These "ipv4Cid" and "ipv6Cid" maybe set to valid value, to indicate which bearer/netif is deactivated
    */
    UINT8               ipv4Cid;
    UINT8               ipv6Cid;
    UINT16              mtu;  //mtu size

    NmNetIpv4Info       ipv4Info;   //first need to check "ipType", if "ipType" indicate ipv4 or ipv4v6, then this info must be valid
    NmNetIpv6Info       ipv6Info;   //first need to check "ipType", if "ipType" indicate ipv6 or ipv4v6, then this info must be valid
}NmAtiNetifInfo;    // 76 bytes
#endif

/*
 * Result for: NM_ATI_SYNC_GET_NET_INFO_REQ, just return NET info info
*/
typedef struct NmAtiGetNetInfoRet_Tag
{
    NmAtiNetifInfo      netifInfo;
}NmAtiGetNetInfoRet;    //76 bytes


/*
 * NM_ATI_SYNC_IS_ANY_ACTIVE_SOCKET_REQ,
 *  return whether any activted socket
*/
typedef struct NmAtiIsAnyActiveSockRet_Tag
{
    BOOL                bAnyActSock;
    UINT8               rsvd0;
    UINT16              rsvd1;
}NmAtiIsAnyActiveSockRet;


/*
 * NM ATI SYNC result
*/
typedef struct NmAtiSyncRet_Tag
{
    union {
        NmAtiGetNetInfoRet      netInfoRet;
#if (RTE_PPP_EN==1)
        NmNetIfDnsCfg           getDnsServer;   //84 bytes
#endif
        NmAtiIsAnyActiveSockRet anyActSockRet;
    }body;
}NmAtiSyncRet;


/******************************************************************************
 * NM_ATI_NET_INFO_IND
 * NmAtiNetInfoInd
******************************************************************************/
typedef struct NmAtiNetInfoInd_Tag
{
#if (RTE_PPP_EN==1)
    UINT8           indCause;      //NmNetifStatusChangeCause
    UINT8           rsvd0;
    UINT16          rsvd1;
#endif
    NmAtiNetifInfo  netifInfo;
}NmAtiNetInfoInd;   // 76 bytes

#if (RTE_PPP_EN==1)
/*
 * lan net status change cause
*/
typedef enum NmLanNetifStatusChangeCause_Tag
{
    NM_LAN_STATUS_CHANGE_INVALID,
    NM_LAN_STATUS_CHANGE_LINK_UP, // the bind wan has active,then the lan link up success, mabybe one IPV4IPV6 wan
    NM_LAN_STATUS_CHANGE_LINK_DOWN, // the lan link down
    NM_LAN_STATUS_CHANGE_LAN_BIND, // for nat mode, the lan link up has already,the the lan bind with one active wan
    NM_LAN_STATUS_CHANGE_LAN_UNBIND,// for nat mode, the lan link up has already,the the lan unbind with one active wan
    NM_LAN_STATUS_CHANGE_WAN_LINK_UP,// for nat mode, the lan link up has already and bind a deactive wan, than the wan active
    NM_LAN_STATUS_CHANGE_WAN_LINK_DOWN,// for nat mode, the lan link up has already and bind a active wan, than the wan deactive
    NM_LAN_STATUS_CHANGE_OTHERS,
}NmLanNetifStatusChangeCause;

typedef struct NmAtiGetDnsServerReq_Tag
{
    UINT8       cid;
    UINT8       rsvd0;
    UINT16      rsvd1;
}NmAtiGetDnsServerReq;

typedef struct NmAtiSetDnsServerReq_Tag
{
    UINT8       cid;
    NmNetIfDnsCfg dnsCfg;
}NmAtiSetDnsServerReq;

typedef struct NmAtiClearDnsCacheReq_Tag
{

    BOOL        bAll;
    UINT8       rsvd0;
    UINT16      rsvd1;
    CHAR        name[DNS_MAX_NAME_LENGTH];
}NmAtiClearDnsCacheReq;

typedef struct NmAtiSetDnsCacheReq_Tag
{

    BOOL        bEanble;
    UINT8       rsvd0;
    UINT16      rsvd1;
}NmAtiSetDnsCacheReq;

typedef struct NmAtiGetLanDataPathCapReq_Tag
{
    UINT8       lanType; //NmLanNetType
    UINT8       rsvd0;
    UINT16      rsvd1;
}NmAtiGetLanDataPathCapReq;

typedef struct NmAtiGetLanDataPathStatusReq_Tag
{
    UINT8       lanType; //NmLanNetType
    UINT8       rsvd0;
    UINT16      rsvd1;
}NmAtiGetLanDataPathStatusReq;

typedef struct NmAtiGetLanDataPathHostInfoReq_Tag
{
    UINT8       lanType; //NmLanNetType
    UINT8       rsvd0;
    UINT16      rsvd1;
}NmAtiGetLanDataPathHostInfoReq;

#endif

/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/******************************************************************************
 * NetMgrLinkUp
 * Description: net manager pdn linkup function
 * input: UINT8 cid     //which CID (CAC layer ID)
 *        NmIfConfiguration *ifConf //default bearer configuration
 *        UINT8 bindToCid   //if NW assign two bearer (one for IPV4, and another for IPV6)
 *                          // when second bearer setup, need to bind to orig "netif"
 *                          // if set to "255", just means not such case
 *        BOOL bWakeup; //whether this NETIF/bearer is linked up during sleep2/hib wake up procedure
 * output: NmResult;
 * Comment:
******************************************************************************/
NmResult NetMgrLinkUp(UINT8 cid, NmIfConfiguration *pIfCfg, UINT8 bindToCid, BOOL bWakeUp, BOOL bInternetPdn);
#if (RTE_PPP_EN==1)
/*
 * Netmgr dedicated bearer linkup
*/
NmResult NetMgrDedLinkUp(UINT8 cid, UINT8 pcid, BOOL bWakeUp);
#endif
/******************************************************************************
 * NetMgrLinkDown
 * Description: netmngr pdn linkdown function
 * input: UINT8 cid
 * output: NmResult
 * Comment:
******************************************************************************/
NmResult NetMgrLinkDown(UINT8 cid);
#if (RTE_PPP_EN==1)
/*
 * Netmgr default/dedicated bearer TFT config
*/
//NmResult NetMgrTftConfig(UINT8 cid, UINT8 pfNum, CmiPsPacketFilter *pPFList);


/******************************************************************************
 * NetMgrLanLinkLayerStatusChange
 * Description: notify the tcpip stack the LAN device link layer status change
 * input: (NmLanType type, NmLanLinkStatus newStatus)
 * output:
 * return: NmResult
 * Comment: called by rndis/ppp service or psdial
 * the default link layer status of LAN is disconnected, and if the status has been change, it must be notify to tcpip stack by this API
******************************************************************************/
NmResult NetMgrLanLinkLayerStatusChange(NmLanType type, NmLanLinkStatus newStatus);


/******************************************************************************
 * NetMgrGetNetInfo
 * Description: get UE wan net info
 * input: UINT8 cid, NmAtiGetNetInfoRet *wanInfo
 * output: NmResult
 * Comment: called by app
 * if cid is LWIP_PS_INVALID_CID, will return default netif status
******************************************************************************/
NmResult NetMgrGetNetInfo(UINT8 cid, NmAtiNetifInfo *pWanInfo);

/******************************************************************************
 * NetMgrGetNetInfoWithoutPsStatusCheck
 * Description: get UE wan net info
 * input:   UINT8 cid, NmAtiNetifInfo *pNetifInfo
 * output:  NmResult
 * Comment: In this API not check whether PS is started, this API is only called
 *          by ESM, as ESM maybe call it to get IPV6 address during wakeup procedure
******************************************************************************/
NmResult NetMgrGetNetInfoWithoutPsStatusCheck(UINT8 cid, NmAtiNetifInfo *pNetifInfo);


/******************************************************************************
 * NetMgrGetDnsServerInfo
 * Description: get UE dns server config
 * input: UINT8 cid, NmNetIfDnsCfg *pGetDnsServer
 * output: NmResult
 * Comment: called by app
******************************************************************************/
NmResult NetMgrGetDnsServerInfo(UINT8 cid, NmNetIfDnsCfg *pGetDnsServer);

/******************************************************************************
 * NetMgrSetDnsServerInfo
 * Description: set UE dns cache
 * input: UINT8 cid, UINT8 number, ip_addr_t dns[NM_MAX_DNS_NUM]
 * output: NmResult
 * Comment: called by app
******************************************************************************/
NmResult NetMgrSetDnsServerInfo(UINT8 cid, UINT8 number, ip_addr_t dns[NM_MAX_DNS_NUM]);

/******************************************************************************
 * NetMgrClearDnsServerInfo
 * Description: clear UE dns cache
 * input: UINT8 cid, NmAtiGetNetInfoRet *wanInfo
 * output: NmResult
 * Comment: called by app
******************************************************************************/
NmResult NetMgrClearDnsCacheInfo(BOOL bClearAll, CHAR        name[DNS_MAX_NAME_LENGTH]);

/******************************************************************************
 * NetMgrSetDnsCache
 * Description: enable/sidable dns cache
 * input: BOOL bEnable
 * output: NmResult
 * Comment: called by app
******************************************************************************/
NmResult NetMgrSetDnsCache(BOOL bEnable);


/*
 * Send NET (NETIF) info (status)
*/
void NetMgrSendNetInfoInd(NmAtiNetInfoInd *pNetInfoInd);

/*
 * Proc "CMI_PS_GET_CEREG_CNF"
*/
void NetMgrProcCeregCnf(CmiPsGetCeregCnf *pCregCnf);

/*
 * Proc "CMI_PS_CEREG_IND"
*/
void NetMgrProcCeregInd(CmiPsCeregInd *pCregInd);


/*
 * net mgr lan configuration for tcpip data path
*/
NmResult NetMgrLanConfig(NetMgrLanCfg *lanCfg);

/*
 * net mgr lan ctrl api(control the lan data path wether bind with pdp context)
 * if the same lan type has bind, it will be replace with the new pdp context
 * if the related lan tcpip data path has been actived,then you can not bind with the new pdp context, and it will return error
*/
NmResult NetMgrLanCtrl(NmLanCtrlAction action, NmLanNetType type, UINT8 ip4Cid, UINT8 ip6Cid);


/*
 * query the lan tcpip data path capability, called by CCIO, to descide whether can do lan link up
*/
NmResult NetMgrQueryLanTcpipDataPathCapability(NmLanNetType lanType, NetMgrLanDataPathCap *pLanDataPathCap);


/******************************************************************************
 * NetMgrLanLinkUp
 * Description: netmngr establish LAN TCPIP data path function
 * input:
 * output:
 * return: NmResult
 * Comment: called by rndis/ppp service
******************************************************************************/
NmResult NetMgrLanLinkUp(NmLanType lanType, BOOL bWakeUp, UINT16 mtu);

/******************************************************************************
 * NetMgrLanDataPathDown
 * Description: netmngr LAN data path  disconnect function
 * input: UINT8 lanChannelId(channel[NM_LAN_RNDIS_CHANNEL_ID]->rndis/ecm, channel[NM_LAN_PPP_CHANNEL_ID]->ppp)
 * output:
 * return:NmResult
 * Comment:called by psdial or ps event(NM_ATI_NET_INFO_IND) callback or rndis/ppp service
******************************************************************************/
NmResult NetMgrLanLinkDown(NmLanType lanType);


/*
 * net mgr query lan tcpip data path status api
*/
NmResult NetMgrGetLanTcpipDataPathStatus(NmLanNetType lanType, NetMgrLanChannelTcpipDataPathStatus *status);

/*
 * notify the CMS/psdial the LAN info
*/
void NetMgrNotifyAtiLanInfoInd(NmAtiLanInfo *pAtiLanInfo);

/*
 * net mgr query lan tcpip data path host info api
*/
NmResult NetMgrGetLanTcpipDataPathHostInfo(NmLanNetType lanType, NetMgrLanTcpipDataPathHostInfo *info);
#endif
/******************************************************************************
 * NetMgrPingRequest
 * Description: netmngr ip ping request function
 * input: NmIpAddr *pDest   //ping DEST IP address info
 *        UINT8 tFlag       //ping count, if set "255", just means keep ping, default value 15
 *        UINT16 payloadLen     //ping payload byte len, default: 32; ping pkg size: 28(ping ICMP header)+32 = 60
 *        UINT32 timeout    //set wait time for one ping pkg
 *        BOOL   raiFlag    //whether enable rai info flag
 * output: NmResult
 * Comment:
******************************************************************************/
NmResult NetMgrPingRequest(ip_addr_t *pDest, UINT8 count, UINT16 payloadLen, UINT32 timeout, BOOL raiFlag, UINT16 reqHandle);

/******************************************************************************
 * NetMgrPingUrlRequest
 * Description: netmngr url ping request function
 * input: const CHAR* pingTarget,
 *        UINT8 count,
 *        UINT16 payloadLen,
 *        UINT32 timeout
 *        BOOL   raiFlag    //whether enable rai info flag
 * output:
 * Comment:
******************************************************************************/
NmResult NetMgrPingUrlRequest(const CHAR* pingTarget, UINT8 count, UINT16 payloadLen, UINT32 timeout, BOOL raiFlag, UINT16 reqHandle);

/******************************************************************************
 * NetMgrPingTerminate
 * Description: netmngr ping request terminate function
 * input:
 * output:
 * Comment:
******************************************************************************/
void NetMgrPingTerminate(void);

/*
*the reference AT command format: AT^ECIPERF:<action>,[protocol],["ipaddr"],[port],[tpt],[pkg_payload_size],[pkg_num],[duration],[rpt_interval]
*1 action:NmIperfAction
*1.1 client mode: must param <action>,<"ipaddr">,<tpt>
*1.2 server mode: must param <action>
*1.3 nat server mode: must param <action>,<"ipaddr">
*2 protocol: default udp
*3 "ipaddr": ipv4 or ipv6
*3.1 dst addr for client mode [must]
*3.2 remote client address for nat server mode [must]
*4 port: default 5001
*4.1 server rcv port for server mode
*4.2 dst port for client mode
*5 tpt: throughput
*6 pkg_payload_size: max -> MTU-28
*7 pkg_num
*8 duration
*9 rtp_interval: default 10 seconds
*/

/******************************************************************************
 * NetMgrIperfRequest
 * Description: netmngr iperf request function
 * input: NmIperfReq *pIperfReq
 * output: NmResult
 * Comment:
******************************************************************************/
NmResult NetMgrIperfRequest(NmIperfReq *pIperfReq);

/******************************************************************************
 * NetMgrSntpStart
 * Description: netmngr sntp start function
 * input: sntp server address and server port
 * output: NmResult
 * Comment:
******************************************************************************/
NmResult NetMgrSntpStart(CHAR *server, UINT16 port, UINT16 reqHandler, BOOL autoSync);

/******************************************************************************
 * NetMgrSntpStop
 * Description: netmngr stop sntp function
 * input:
 * output:
 * Comment:
******************************************************************************/
void NetMgrSntpStop(void);

/******************************************************************************
 * NetMgrAtiAsyncReq
 * Description: netmngr at srv async request function
 * input:   UINT16 srcHdr,
 *          UINT16 nmReqId,
 *          void *reqBody
 * output: NmResult
 * Comment:
 *  Async request API, return:
 *  1> NM_SUCCESS, just means a signal "SIG_NM_ATI_CNF" will be sent to ATCMDSRV late
 *  2> others, just means this request it failed, and no "SIG_NM_ATI_CNF" late
******************************************************************************/
NmResult NetMgrAtiAsyncReq(UINT16 srcHdr, UINT16 nmReqId, void *reqBody);

/******************************************************************************
 * NetmgrAtiSyncReq
 * Description: netmngr sync request API.
 * input:   UINT16 reqId, void *reqBody, void *result
 * output:
 * Comment:
******************************************************************************/
NmResult NetmgrAtiSyncReq(UINT16 reqId, void *reqBody, NmAtiSyncRet *pRet);

/*
 * Send URL DNS result
*/
void NetMgrSendGetDnsCnf(INT32 result, ip_addr_t *pIpInfo, UINT16 srcHdr);


/*
 * Send PING result
*/
void NetMgrSendPingResultInd(NmAtiPingResultInd *pPingRet, UINT16 reqHandle);

/*
 * Send ECIPERF result
*/
void NetMgrSendIperfResultInd(NmAtiIperfResultInd *pIperfRet, UINT16 reqHandle);

/*
 * Send SNTP result
*/
void NetMgrSendSntpResultInd(NmAtiSntpResultInt *pSntpRet, UINT16 reqHandle);

/*
 * Send NET (NETIF) info (status)
*/
void NetMgrSendNetInfoInd(NmAtiNetInfoInd *pNetInfoInd);

/*
 * Proc "CMI_PS_GET_CEREG_CNF"
*/
void NetMgrProcCeregCnf(CmiPsGetCeregCnf *pCregCnf);

/*
 * Proc "CMI_PS_CEREG_IND"
*/
void NetMgrProcCeregInd(CmiPsCeregInd *pCregInd);


#endif

