/******************************************************************************
 ******************************************************************************
 Copyright:      - 2021- Copyrights of Qualcomm Inc.
 File name:      - gtp_lite.h
 Description:    - GTP transport Layer sub-module
 History:        - 19/08/2021
 ******************************************************************************
******************************************************************************/
#ifndef __GTP_LITE_H__
#define __GTP_LITE_H__

#include <gtp_client.h>
#include "gtplite_extended_c.h"
#include "GTPLiteV4.h"
#include "gtp_conn.h"
#include "Cmimm.h"

#define GTP_LITE_PERSISTENCE_FILE "gtplite.bin"
#define GTP_LITE_CONFIG_FILE	"gtplitecfg.bin"

#define GTP_HOSTNAME_LEN 40

typedef enum GtpLiteClientPrimerId_Tag
{
    GTP_LITE_CLIENT_INIT_REQ = 0xF0,
	GTP_LITE_CLIENT_POS_REQ,
    GTP_LITE_CLIENT_ABORT_REQ,
    GTP_LITE_CLIENT_DEINIT_REQ,
    GTP_LITE_SERVER_CONFIG_REQ, /* Set the Hostname and Port */
    GTP_LITE_TEST_CLEAR_AD,     /* clear the AD */
    GTP_LITE_SET_CFG,
}GtpLiteClientPrimerId;


typedef enum GtpState_enum
{
    GTP_STATE_NULL = 0,
	GTP_STATE_WAIT_LINK_UP,
	GTP_STATE_WAIT_PS_SCAN_RSP,
	GTP_STATE_WAIT_SERVER_RSP,
	GTP_STATE_WAIT_LINK_DOWN,
    GTP_STATE_MAX = 0xFF
}GtpState;

typedef enum GtpEvent_enum
{
 	GTP_EVENT_POS_REQ = 0,
 	GTP_EVENT_ABORT_REQ,
 	GTP_EVENT_SERV_LINK_UP,
 	GTP_EVENT_PS_SCAN_RSP,
 	GTP_EVENT_SERV_RSP,
 	GTP_EVENT_SERV_LINK_DOWN,
 	GTP_EVENT_OOS,
 	GTP_EVENT_AIRPLANE_MODE,
    GTP_EVENT_MAX = 9 
}GtpEvent;

typedef enum ChannelState_enum
{
	CHANNEL_DETECTED = 1,
	CHANNEL_MISSED,
	CHANNEL_NOT_ATTEMPTED
}ChannelState;

typedef enum BandInfo_enum
{
	LOW_BAND = 1,
	MID_BAND = 2
}BandInfo;

typedef struct PsChannel_Tag
{
	UINT32 earfcn;
	BandInfo bandInfo;
	ChannelState state;
	BOOL sib1Req;
	BOOL isServingCellBand;
}PsChannel;

typedef struct LaasTag_Tag
{
	BOOL isTagValid;
    uint8_t laasTag[LAAS_TAG_LEN];	
}LaasTag;

typedef struct GtpLiteNonVolatileData_Tag
{
	UINT64 pseudoClientId;                         /* 64bit randomly generated ID, to be generated only once during first bootup */
    uint8_t configId;                              /* config ID received from GTP sever */

    /*  List of Restricted Regions */
    uint8_t restrictedRegionVersion_valid;  /**< Must be set to true if restrictedRegionVersion is being passed */
    uint8_t restrictedRegionVersion;
    uint8_t restrictedRegions_valid;               /**< Must be set to true if restrictedRegions is being passed */
    uint32_t restrictedRegions_len;                /**< Must be set to # of elements in restrictedRegions */
    HomeCarrierIdStructT restrictedRegions[LOC_RESTRICTED_REGIONS_LIST_MAX_SIZE];

    /*  Minimum Seconds Between Requests */
    uint8_t minSecsBtwRequests_valid;  /**< Must be set to true if minSecsBtwRequests is being passed */
    uint16_t minSecsBtwRequests;       /* minimum time between two GTP server POS requests */
	UINT32 utcSeconds; /* UTC time when last request sent, update after a successful pos session, if UTC time not available store system time */
	BOOL isUtcTime;    /* Indicate if UTC time is stored in utcSeconds or system time is used */

	 /*  Maximum number of GTP cell requests with server access per day */
    uint8_t maxGtpCellRequestsPerDay_valid;
    uint16_t maxGtpCellRequestsPerDay; /* maximum number of requests allowed in a day,  */
	UINT16 numOfRequestsToday;  /* number of GTP requests sent today, update it after a POS session */
	UINT32 utcDays;          /* Time in seconds when first request made today, if UTC time not available store system time */
	BOOL isUtcDays;          /* indicate if utcDays is stored in utcSeconds or system time is used */

	/* If server blacklisted the GTPLite */
	uint8_t blackListedTime_valid;
	uint64_t blackListedTime;
	uint64_t UtcBlacklistTime;
	BOOL	isUtcBlackListedTime;

	/* gtp server host name, to be used to get IP address */
	uint8_t gtpHostName[GTP_HOSTNAME_LEN];
	uint16_t portnumber;

	WWanScanAssistanceData wwanScanAssistanceData; /* Scan assistance data received from GTP server, to be used to trigger scan towards PS */
	uint8_t wwanScanAssistanceData_valid;
	ScanPosConfig scanPosConfig;                   /* Scan Pos config */
	uint8_t scanPosConfig_valid;

	/* following parameters will be used for triggering PS scan request and shall be re-ordered based on scan results */
	UINT32 earfcnList[SUPPORT_MAX_FREQ_NUM];
	UINT8 sib1Req[SUPPORT_MAX_FREQ_NUM];
}GtpLiteNonVolatileData;

typedef struct GtpLiteContext_Tag
{
	GtpState currState;                 /* Current state of GTP lite */
	GtpEvent currEvent;                 /* event processed by GTPLite currently TODO: Check if can be removed */
	GtpLocationErrorId sessionRet;      /* error ID to be returned at the end of the session */
	GtpLocationCallback clientCallback; /* Client callback registered via init */
	LaasTag laastag;                    /* LAAS tag received from IoT client */
	GtpConnLinkState serverLinkState;   /* server Link state */
	BOOL isFirstRequestToServer;        /* Check if current request is first request in the session */
	BOOL isAdRequestedInCurrSession;    /* Stores if AD is alredy requested in the current session */
	BOOL scanWithFreshAd;               /* Scan with fresh AD */
	BOOL cellPositionValid;             /* Indicates if cell position is valid */
	FdclCellPosStructT cellPosition;    /* Current Cell location received from GTP sever */
	WwanScanList *wwanScanList;         /* encoded wwan Scan list information, free this before session exit */
	clientinformation *clientInfo;      /* encoded client info, free this before session exit */
	uint8_t slphdle;                    /* handle by platform to enable deep sleep */
	slpManSlpState_t slpState;          /* current sleep state */
	GenericTimeStamp *aitScanStartTime; /* storing scan start time */
	GtpLiteNonVolatileData *gtpNvm;     /* store the GTP NVM data locally */
	UINT32	reqStartTime;
	BOOL	sysOrUtc;
}GtpLiteContext;


typedef struct GtpInitReq_Tag
{
	GtpLocationCallback callback; /* Client callback registered via init */
}GtpInitReq;

typedef struct GtpPosReq_Tag
{
	BOOL isLaasTagValid;                      /* Is LAAS tag valid */
	uint8_t laasTag[LAAS_TAG_LEN];            /* LAAS tag received from IoT client */
}GtpPosReq;

typedef struct GtpPsScanCnf_Tag
{
	CmiMmGtpPlmnSearchCnf gtpPlmnSearchCnf;
}GtpPsScanCnf;

typedef struct GtpSetHostNameReq_Tag
{
	UINT8 ipAddr[GTP_HOSTNAME_LEN];
	UINT8 ipLen;
	UINT16 port;
}GtpSetHostNameReq;


typedef UINT32 GtpPsOosSig;

typedef UINT32 GtpTestClearAdSig;


typedef void (*GtpLiteCallbackFunctionP)(void *context);

typedef struct GtpLiteStateMachine_Tag
{
    const GtpLiteCallbackFunctionP gtpProcFunc;
}GtpLiteStateMachine;

void GtpLiteReadGtpNvm(GtpLiteNonVolatileData *gtpNvm);

void GtpLiteUpdateNvm(GtpLiteNonVolatileData *gtpNvm);

void GtpLiteHandlePosReq(void *gtpContext);

void GtpLiteHandleAbortReq(void *gtpContext);

void GtpLiteProcessPsScanCnf(void *context);

void GtpLiteHandleOrphanLinkUp(void *context);

void GtpLiteHandleServerLinkUp(void *context);

void GtpLiteHandleServerResponse(void *context);

void GtpLiteHandleServerLinkDown(void *context);

void GtpLiteHandleServerLinkDownRsp(void *context);

void GtpLiteHandleOos(void *context);

BOOL GtpCheckIfCurrentLocationRequestAllowed(GtpLocationErrorId *cause);
BOOL GtpCheckIfCurrentCellBelongsToRestrictedRegion(CmiNumericPlmn  plmn);

GtpState GtpLiteGetCurrentState(void);

int32_t GtpLiteTaskInit(void);
void GtpLiteHandlePsScanCnf(const SignalBuf *cnfSignalPtr);
GtpLocationErrorId GtpLiteTestClearAd(void);
GtpLocationErrorId GtpLiteSetMonthsToMins(void);
#ifdef TEST_HACKS
GtpLocationErrorId GtpLiteSetTestCfg(UINT32 id, UINT32 value);
#endif


//INT32 GtpLitePsUrcCallback(urcID_t eventID, void *param, UINT32 paramLen);


#endif
