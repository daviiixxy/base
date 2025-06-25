#ifndef PSIF_HDR_ROHC_ADPT_H
#define PSIF_HDR_ROHC_ADPT_H

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2018- Copyrights of Qualcomm Ltd.
 File name:      - psif_rohc_adpt.h
 Description:    - psif rohc adapt layer header file
 History:        - 08/17/2018, Originated by xwang
 ******************************************************************************
******************************************************************************/
#ifdef WIN32
#include "winsys.h"
#else
#include "commontypedef.h"
#endif

#include "lwip/priv/tcpip_priv.h"
#include "lwip/err.h"


/****************************************************************************** 
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/

#define ROHC_COMPRESS_MAX_LEN 128
#define PSIF_ROHC_COMPRESS_HEADER_LEN_MAX 80
#define PSIF_ROHC_DECOMPRESS_HEADER_LEN_MAX 80
#define PSIF_ROHC_FEEDBACK_LEN_MAX 40
#define PSIF_ROHC_O_MODE 2

/****************************************************************************** 
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

typedef struct PsifRohcMngrCreate_Tag{
    struct tcpip_api_call_data call;
    UINT8 cid;
    UINT8 onlyUplink;
    UINT16 maxCid;
    UINT32 rohcProfiles;
    UINT32 mrru; 
}PsifRohcMngrCreate;

typedef struct PsifRohcMngrDestroy_Tag{
    struct tcpip_api_call_data call;
    UINT8 cid;
    UINT8 reserved0;
    UINT16 reserved1; 
}PsifRohcMngrDestroy;

typedef struct PsifRohcMngrReset_Tag{
    struct tcpip_api_call_data call;
    UINT8 channelId;
    UINT8 reserved0;
    UINT16 reserved1; 
}PsifRohcMngrReset;

typedef struct PsifRohcMngrCompress_Tag{
    struct tcpip_api_call_data call;
    void    *pPdu;
    UINT8 channelId;
    UINT8 reserved0;
    UINT16 reserved1; 
}PsifRohcMngrCompress;

#if 0
/*
*rohc profile bitmap define
*/

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
#endif

typedef struct RohcDataBuffer_Tag{
  UINT8* data;
  UINT16 dataLen; //data length
  UINT16 maxLen;
  UINT16 payloadOffset;
  UINT16 payloadSize;  
}RohcDataBuffer;


typedef struct RohcHeaderBuffer_Tag{
  UINT8* data;
  UINT16 len; //data length
  UINT16 maxLen;
}RohcHeaderBuffer;

typedef struct RohcBuff_Tag
{
    UINT16 dataLen;
    UINT16 buffLen;
    UINT8 *pData;
}RohcBuff;


typedef struct RohcFeedbackBuffer_Tag{
  UINT8* data;
  UINT16 len; //data length
  UINT16 maxLen;
}RohcFeedbackBuffer;

enum {
    ROHC_ADPT_ACTION_STATUS_SUCCESS = 0,
    ROHC_ADPT_ACTION_STATUS_FAIL = 1,    
    ROHC_ADPT_ACTION_STATUS_MAX = 64,    
};

typedef struct NetifRohcChannel_Tag {
    void *channelComp; // rohc compress channel context
    void *channelDecomp; // rohc decompress channel context  
    UINT8 cid; // which context id the rohc channel is assigned
    UINT8 compOnly; // the flag indication whether compress only
    UINT8 state; //
    UINT8 reserved2;
}NetifRohcChannel;

typedef struct PsifRohcChannelList_Tag {
    struct NetifRohcChannel_Tag netifRohcChannel;
    struct PsifRohcChannelList_Tag *next;
}PsifRohcChannelList;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/*get the psif rohc channel mng list by cid*/
PsifRohcChannelList *PsifGetRohcChannel(UINT8 cid);

void* RohcCreateCompChannel(UINT32 rohcProfiles, UINT16 maxCid, UINT32 mrru);

void* RohcCreateDecompChannel(UINT32 rohcProfiles, UINT16 maxCid, UINT32 mrru, UINT8 decompressMode, void *rohcomp);

void RohcDestroyCompChannel(void *compChannel);

void RohcDestroyDecompChannel(void *decompChannel);

void RohcResetCompChannel(void *compChannel);

void RohcResetDecompChannel(void *decompChannel);

UINT8 RohcCompressPacket(void *compChannel, struct RohcDataBuffer_Tag *inputPacket, struct RohcHeaderBuffer_Tag *compressHeader);

UINT8 RohcDecompressPacket(void *decompChannel, struct RohcDataBuffer_Tag *compressPacket, struct RohcHeaderBuffer_Tag *decompressHeader, struct RohcFeedbackBuffer_Tag *sendFeedback);

UINT8 RohcReceiveFeedbackPacket(void *compChannel, struct RohcFeedbackBuffer_Tag * feedPacket);

/*
*psif create rohc channel callback funcion which will run in the tcpip thread
*/
void PsifCreateRohcCallback(void *arg);

/*
*psif destroy rohc channel callback funcion which will run in the tcpip thread
*/
void PsifDestroyRohcCallback(void *arg);

/*
*psif reset rohc channel callback funcion which will run in the tcpip thread
*/
void PsifResetRohcCallback(void *arg);

/*
*psif rohc channel compress packet callback funcion which will run in the tcpip thread
*/
err_t PsifCompressRohcCallback(struct tcpip_api_call_data *arg);

UINT32 PsifGetRohcCapability(void);



#endif
