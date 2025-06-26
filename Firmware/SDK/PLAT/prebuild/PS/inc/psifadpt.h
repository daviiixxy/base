#ifndef PSIF_HDR_ADAPT_H
#define PSIF_HDR_ADAPT_H

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2018- Copyrights of Qualcomm Ltd.
 File name:      - psifadpt.h
 Description:    - ps netif adapt later
 History:        - 01/02/2018, Originated by xwang
 ******************************************************************************
******************************************************************************/

#include "pspdu.h"
#include "lwip/netif.h"
#include "lwip/priv/tcpip_priv.h"
#include "psifapi.h"
#if (RTE_PPP_EN==1)
#include "netfastpath.h"
#include "cmips.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************** 
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/
    
#define PS_NETIF_PREFIX_NAME 'p'
#define INVALID_CID 255
#define PS_MAX_DNS_NUM 2
#define PS_IF_UL_MAGIC_WORD 0x3456
#define LWIP_UL_PDU_MEM_TYPE  1


/****************************************************************************** 
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

#if (RTE_PPP_EN==1)
typedef struct PsifDlPkgPendingList_Tag
{
    UINT16          pkgNum; // the total pkg num of the pending list
    UINT16          rsvd;

    DlPduBlock      *pHead;
    DlPduBlock      *pTail;
}PsifDlPkgPendingList;
#endif

/*
 * PS IF control header allocated before UL IP PKG send to PS
 *
 * +---------------------------+----------------------------------------------------+
 * | PsifUlDataHeader(4 bytes) |                  UL IP PKG                         |
 * +---------------------------+----------------------------------------------------+
*/
typedef struct PsifUlDataHeader_Tag
{
    UINT16 magic; //PS_UL_MAGIC
    UINT16 ulLen; // UL packet length
}PsifUlDataHeader;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/



/******************************************************************************
 *                   UL, UE -> LWIP, LWIP -> PS                               *
******************************************************************************/

/*
 * PS/CEDR API
 *  UL ip/non-ip PDU list
 * 1> "DataPduInfo" use the dynamic memory (HEAP), and free later in the target TASK
*/
extern void CedrUlPkgListDataReqFromLwip(UINT8 cid, UINT16 totalLen, UlPduInfo *pHdr, UlPduInfo *pTailer);


/*
 * PS/CEDR API
 * Whether PS UL high water, if set to TRUE, can't send the UL data;
*/
extern UINT8 CedrUlIsPduHighWater(void);

/*
 * PS/CEDR API
 * Whether PS under test loop back mode
*/
extern BOOL CedrBeTestLoop(void);

//NIDD: CEDR API for informing Socket Status of NIDD-LwM2M cid(s)
void CedrLwm2mNIDDCidSockStatus(UINT8 cid, BOOL sockStatus);


#if 0
/*
* add ps total ul data size
*/
void PsAddTotalUlDataSize(UINT16 size);
#endif

/*
 * DL PKG input
*/
PsIfRet PsifDlInput(UINT8 cid, DlPduBlock *pPduHdr);
#if (RTE_PPP_EN==1)
UINT8 PsifPendingDlInput(UINT8 cid);

err_t PsifUlRohcOutput(UlPduInfo *pUlPdu, UINT8 cid);

void PsifDlPkgListInput(UINT8 cid, UINT16 pkgNum, DlPduBlock *pHead, DlPduBlock *pTail);
#endif
void PsNetifSyncRohcChannel(struct netif *netif, UINT8 cid);

err_t PsNetifInit(struct netif *netif);

void PsifDumpUlPacket(UlPduInfo *psData);

void PsifDumpDlPacket(struct pbuf *pbufData);

UINT16 PsifGetCurrentPacketDelay(void);

/*
 * PS IF UL PKG memory functions
*/
UINT8 *PsifAllocUlPkgMem(UINT16 len);
void PsifFreeUlPkgMem(UINT8 *pUlPkg);

BOOL PsifCheckAnyPendingData(void);
void PsifSuspendInd(BOOL suspend);
void PsNetifCidDr(UINT8 cid, BOOL flag);
err_t PsNonIpOutput(struct pbuf *p, UINT8 cid);


#if (RTE_PPP_EN==1)
void PsifSetFastPathChkInfo(NetifFastChkInfo *pChkInfo);
#endif



#ifdef __cplusplus
}
#endif

#endif

