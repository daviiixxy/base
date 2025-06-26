#ifndef PSIF_HDR_ROHC_API_H
#define PSIF_HDR_ROHC_API_H
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2018- Copyrights of Qualcomm Ltd.
 File name:      - psif_rohc_utility.h
 Description:    - provide rohc related API header file
 History:        - 08/20/2018, Originated by xwang
 ******************************************************************************
******************************************************************************/
#ifdef WIN32
#include "winsys.h"
#else
#include "commontypedef.h"
#endif
#include "pspdu.h"

/****************************************************************************** 
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/

#define PSIF_ROHC_SMALL_CID_MAX 15U
#define PSIF_ROHC_LARGE_CID_MAX ((1U << 14) - 1)


enum RohcProfile_Enum
{
    UE_ROHC_PROFILE_0x0000 = 0,    /*RFC 5795*/
#define  UE_ROHC_PROFILE_NO_COMP UE_ROHC_PROFILE_0x0000
    UE_ROHC_PROFILE_0x0001 = 1,    /*RFC 3095, RFC 4815*/
#define  UE_ROHC_PROFILE_RTP     UE_ROHC_PROFILE_0x0001
    UE_ROHC_PROFILE_0x0002 = 2,    /*RFC 3095, RFC 4815*/
#define  UE_ROHC_PROFILE_UDP     UE_ROHC_PROFILE_0x0002
    UE_ROHC_PROFILE_0x0003 = 3,    /*RFC 3095, RFC 4815*/
#define  UE_ROHC_PROFILE_ESP     UE_ROHC_PROFILE_0x0003
    UE_ROHC_PROFILE_0x0004 = 4,    /*RFC 3843, RFC 4815*/
#define  UE_ROHC_PROFILE_IP      UE_ROHC_PROFILE_0x0004
    UE_ROHC_PROFILE_0x0006 = 6,    /*RFC 6846*/
#define  UE_ROHC_PROFILE_TCP     UE_ROHC_PROFILE_0x0006
    UE_ROHC_PROFILE_0x0101 = 7,    /*RFC 5225*/
#define  UE_ROHC_PROFILE_RTP_V2  UE_ROHC_PROFILE_0x0101
    UE_ROHC_PROFILE_0x0102 = 8,    /*RFC 5225*/
#define  UE_ROHC_PROFILE_UDP_V2  UE_ROHC_PROFILE_0x0102
    UE_ROHC_PROFILE_0x0103 = 9,    /*RFC 5225*/
#define  UE_ROHC_PROFILE_ESP_V2  UE_ROHC_PROFILE_0x0103
    UE_ROHC_PROFILE_0x0104 = 10,   /*RFC 5225*/
#define  UE_ROHC_PROFILE_IP_V2   UE_ROHC_PROFILE_0x0104
};


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/* 
 * Get the UE ROHC capability
 * output: pRohcProfiles, see RohcProfile_Enum
 * output: pRohcMaxCid, the max context id for ROHC channel
 * return: 
 *  FALSE: not support ROHC (header compression)
 *  TRUE : support ROHC, and "profiles" & "maxCid" right return
*/
BOOL RohcGetUeRohcCapability(UINT32 *pRohcProfiles, UINT16 *pRohcMaxCid);


/*
 * Create ROHC for a special channel(bear)
 * input: cid, which channel will enable ROHC feature, AT CMD context id, must sync with the link_up cid
 * input: rohcProfiles, example ROHCv1_PROFILE_UNCOMPRESSED_T | ROHCv1_PROFILE_IP_T
 * input: maxRohcCid, the max context id for channel
 * input: onlyUplink, uplink only header compress indocation,1->enable 0->disable 
 * return: 0->success, others->fail
*/
UINT8 RohcCreateRohcChannel(UINT8 cid, UINT32 rohcProfiles, UINT16 maxRohcCid, BOOL onlyUplink);


/*
 * disable ROHC for a special channel(bear)
 * input: cid, which channel will disable ROHC feature, AT CMD context id
 * return: 0->success, others->fail
*/
UINT8 RohcDestroyRohcChannel(UINT8 cid);


/*
 * Reset ROHC setting for a special channel:
 *  1> reset the header compression protocol for uplink and start with an IR state in U-mode
 *  2> reset the header compression protocol for downlink and start with NC state in U-mode
 * input: cid, which channel will disable ROHC feature, AT CMD context id
 * return: 0->success, others->fail
*/
UINT8 RohcResetRohcChannel(UINT8 cid);


/*
 * Let ROHC module to compress the PKG;
 * 1> When UE in IDLE state, and UL pkg comes (uncompressed pkg), then this UL pkg just trigger to establish the connection;
 * 2> After RRC connection established, then maybe config ROHC;
 * 3> Here need to pass the uncompress the pkg to ROHC to compress it again;
 * 4> ROHC compress the pkg, and resend them to PS again
 * 5> This should ba a non-blocked API
 *return: 0->success, others->fail
*/
UINT8 RohcReCompDataPdu(UINT8 cid, UlPduInfo *pPdu);


/**************************************************************************************************************************************************************
*
*Todo:
*1. rohc context store & reuse
*2. rohc profile-specific information set
***************************************************************************************************************************************************************/
#if 0

/*
 * For UP-OPT case:
 *  ROHC context should be stored into tiny context (AON Flash) when RRC release the connection with suspension
*/
void RohcStoreChannel(UINT8 cid);

/*
 * For UP-OPT case:
 *  ROHC context should be re-used, when RRC connection resume back
*/
void RohcReuseChannel(UINT8 cid);


/*
 * 1> The profile specific information is carried in ESM signalling, when activate/modify a bearer context:
 * 2> And this field corresponds to the profile-specific information in the header of the ROHC IR packet type in IETF RFC 5795 [37]
 * 3> UINT8 profileId;  //RohcProfile
 *    UINT8 *pSpecInfo; //just use dynamic memory
*/
void RohcSetProfileSpecInfo(UINT8 cid, UINT8 profileId, UINT8 len, UINT8 *pSpecInfo);

#endif


#endif

