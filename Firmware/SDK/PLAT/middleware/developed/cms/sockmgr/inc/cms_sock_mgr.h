/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: cms_sock_mgr.h
 *
 *  Description: cms socket manager API header file
 *
 *  History:create by xwang
 *
 *  Notes:
 *
******************************************************************************/

#ifndef __CMS_SOCK_MGR_H__
#define __CMS_SOCK_MGR_H__

#include "commontypedef.h"
#include "cmicomm.h"
#include "ip_addr.h"
#include "pssys.h"
#include "lwip/opt.h"
#include "ecpm_qcx212_external.h"

/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/
#define CMS_SOCK_MGR_CONTEXT_NUM_MAX 7
#define CMS_SOCK_MGR_CLIENT_PORT 60002
#define CMS_SOCK_MGR_SERVER_PORT 60003
#define CMS_SOCK_MGR_ASYNC_REQUEST_MAGIC 0x1234
#define CMS_SOCK_MGR_SYNC_REQUEST_MAGIC 0x4321
#define CMS_SOCK_MGR_RESPONSE_LEN_MAX 256   //bytes

#define CMS_SOCK_MGR_CONNECT_TIMEOUT 31            //seconds

#define CMS_SOCK_MGR_UL_STATE_INDICATION_REQ_ID 64
#define CMS_SOCK_MGR_UL_STATE_INDICATION_REQ_MAGIC 0x1234
#define CMS_SOCK_MGR_UL_STATE_INDICATION_REQ_SOURCE_ID 0XFFFFFFFF

#define CMS_SOCK_MGR_UL_DATA_SEQUENCE_MAX 255
#define CMS_SOCK_MGR_UL_DATA_SEQUENCE_MIN 1

#define CMS_SOCK_MGR_CONTEXT_MAGIC 0xABCD
#define CMS_SOCK_MGR_TCP_CONTEXT_MAGIC 0xBCDA
#define CMS_SOCK_MGR_UDP_CONTEXT_MAGIC 0xCDAB

#define CMS_SOCK_MGR_HIB_PRIVATE_CONTEXT_MAX_LENGTH 32

#define CMS_SOCK_MGR_DATA_HEADER_LENGTH_MAX 64

#define CMS_SOCK_MGR_DL_LENGTH_MAX 1358

#define CMS_SOCK_MGR_WAKEUP_SELECT_TIMEOUT 2  //seconds


#define CMSSOCKMGR_CHECK_SOURCE(source) (((source) > (SOCK_SOURCE_MINI)) && ((source) < (SOCK_SOURCE_MAX)))
#define CMSSOCKMGR_CHECK_TYPE(type) (((type) == (SOCK_CONN_TYPE_UDP)) || ((type) == (SOCK_CONN_TYPE_TCP)))

#define CMSSOCKMGR_EXPECT_CLIENT_SOCKET_ID (MEMP_NUM_NETCONN + LWIP_SOCKET_OFFSET - 2)
#define CMSSOCKMGR_EXPEXT_SERVER_SOCKET_ID (MEMP_NUM_NETCONN + LWIP_SOCKET_OFFSET - 1)

/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/
typedef enum{
    SOCK_CONN_TYPE_UDP = 1,
    SOCK_CONN_TYPE_TCP = 2,
}CmsSockMgrConnType;

typedef enum{
    SOCK_MGR_DATA_TYPE_RAW = 1,
    SOCK_MGR_DATA_TYPE_HEX_STRING = 2,
}CmsSockMgrDataType;


typedef enum{
    SOCK_SOURCE_MINI   = 0,
    SOCK_SOURCE_ATSKT     ,
    SOCK_SOURCE_ECSOC     ,
    SOCK_SOURCE_SDKAPI    ,
    SOCK_SOURCE_ECSRVSOC  ,
    SOCK_SOURCE_MAX       ,
}CmsSockMgrSource;

typedef enum{
    SOCK_EVENT_CONN_STATUS    = 0,
    SOCK_EVENT_CONN_DL        = 1,
    SOCK_EVENT_CONN_UL_STATUS = 2,
    SOCK_EVENT_CONN_ERROR     = 3,
    SOCK_EVENT_CONN_TCP_ACCEPT_CLIENT = 4, //for tcp server mode, accept client connection event
}CmsSockMgrEventType;

typedef enum{
    SOCK_CONN_STATUS_CLOSED     = 0,
    SOCK_CONN_STATUS_CREATED    = 1,
    SOCK_CONN_STATUS_CONNECTING = 2,
    SOCK_CONN_STATUS_CONNECTED  = 3,
}CmsSockMgrConnStatus;

typedef enum{
    SOCK_CONN_UL_STATUS_SUCCESS = 0,
    SOCK_CONN_UL_STATUS_FAIL    = 1,
}CmsSockMgrConnUlStatus;

typedef enum{
    SOCK_MGR_ACTION_OK      = 1,
    SOCK_MGR_ACTION_TIMEOUT = 2,
    SOCK_MGR_ACTION_FAIL    = 3,
}CmsSockMgrActionResult;

typedef enum {
    SOCK_MGR_UL_SEQUENCE_STATE_DISCARD = 0,
    SOCK_MGR_UL_SEQUENCE_STATE_SENT = 1,
}CmsSockMgrUlStatusResult;

typedef enum {
    /*
     * 401 - 500 are reserved for socket error
    */
    CME_SOCK_MGR_ERROR_BASE = 401,
    CME_SOCK_MGR_ERROR_PARAM_ERROR,                             //parameter error
    CME_SOCK_MGR_ERROR_TOO_MUCH_INST,                           //too much socket instance
    CME_SOCK_MGR_ERROR_CREATE_SOCK_ERROR,                       //create socket error
    CME_SOCK_MGR_ERROR_OPERATION_NOT_SUPPORT,                   //operation not support
    CME_SOCK_MGR_ERROR_NO_FIND_CLIENT,                          //operation not support
    CME_SOCK_MGR_ERROR_CONNECT_FAIL,                            //connect failed
    CME_SOCK_MGR_ERROR_BIND_FAIL,                               //bind failed
    CME_SOCK_MGR_ERROR_SEND_FAIL,                               //send failed
    CME_SOCK_MGR_ERROR_NO_CONNECTED,                            //connect failed
    CME_SOCK_MGR_ERROR_IS_CONNECTED,                           //already connected
    CME_SOCK_MGR_ERROR_INVALID_STATUS,
    CME_SOCK_MGR_ERROR_CONNECT_TIMEOUT,
    CME_SOCK_MGR_ERROR_DELETE_FAIL,
    CME_SOCK_MGR_ERROR_SOCK_ERROR,                                //socket error
    CME_SOCK_MGR_ERROR_NO_MEMORY,
    CME_SOCK_MGR_ERROR_NO_MORE_DL_BUFFER_RESOURCE,
    CME_SOCK_MGR_ERROR_CONNECT_IS_ONGOING,
    CME_SOCK_MGR_ERROR_UL_SEQUENCE_INVALID,
    CME_SOCK_MGR_ERROR_SEND_REQUEST_FAIL,
    CME_SOCK_MGR_ERROR_SERVER_HASE_CREATED,
    CME_SOCK_MGR_ERROR_SET_DNS_SERVER_FAIL,
    CME_SOCK_MGR_ERROR_DNS_RESOLVE_FAIL,
    CME_SOCK_MGR_ERROR_UNKNOWN,

    CME_SOCK_MGR_ERROR_MAX = 500
}CmsSockMgrErrorCode;



/******************************************************************************
 *****************************************************************************
 * structure
 *****************************************************************************
******************************************************************************/

typedef struct CmsSockMgrContext_Tag{
    INT32 sockId;  //the socket connection id
    UINT8 source; //CmsSockMgrSource
    UINT8 type; //CmsSockMgrConnType
    BOOL  hibEnable; //whether the socketid enable HIB/SLEEP2 option
    UINT8 status; //the socket connection status
    BOOL bServer; // the flag indicate whether the connection is or not server connection
    UINT8 domain;
    UINT16 localPort;
    ip_addr_t localAddr;
    UINT32 connectStartTicks;
    void *eventCallback; //error/dl/ul status event callback
    struct CmsSockMgrContext_Tag *next;
    UINT8 priContext[]; //the sock mgr private context
}CmsSockMgrContext;

typedef struct CmsSockMgrDataContext_Tag{
    UINT16 type;
    UINT16 Length;
    UINT8 header[CMS_SOCK_MGR_DATA_HEADER_LENGTH_MAX];
    UINT8 data[];
}CmsSockMgrDataContext;

typedef struct CmsSockMgrRequest_Tag{
    UINT16 magic;
    UINT8 source;
    UINT8 reqId;
    UINT32 reqTicks;
    UINT16 timeout;
    UINT16 rsvd;
    void *reqBody;
}CmsSockMgrRequest;

typedef struct CmsSockMgrResponse_Tag{
    UINT8 source;
    UINT8 reqId;
    UINT16 bodyLen; // < CMSSOCKMGRRESPONSELEN_MAX
    UINT8 body[];
}CmsSockMgrResponse;

typedef struct CmsSockMgrConnStatusArg_Tag{
    UINT8 oldStatus; //CmsSockMgrConnStatus
    UINT8 newStatus;
    UINT16 cause;
}CmsSockMgrConnStatusArg;

typedef struct CmsSockMgrConnDlArg_Tag{
    UINT16 fromPort;
    UINT16 rsvd;
    ip_addr_t fromAddr;
    CmsSockMgrDataContext *dataContext;
}CmsSockMgrConnDlArg;

typedef struct CmsSockMgrConnUlStatusArg_Tag{
    UINT8 sequence;
    UINT8 status; //CmsSockMgrConnUlStatus
    UINT16 rsvd;
}CmsSockMgrConnUlStatusArg;

typedef struct CmsSockMgrConnErrArg_Tag{
    INT32 errCode;
}CmsSockMgrConnErrArg;

typedef struct CmsSockMgrConnAcceptClientArg_Tag{
    INT32 serverSocketId;
    INT32 clientSocketId;
    UINT16 clientPort;
    UINT16 rsvd;
    ip_addr_t clientAddr;
}CmsSockMgrConnAcceptClientArg;


typedef struct CmsSockMgrUlStatusInd_Tag{
    INT32 sockId;
    INT32 ulStatus;//0->success, 1->fail/discard
    UINT32 sequence_state_bitmap[8];
}CmsSockMgrUlStatusInd;

typedef struct CmsSockMgrUlStatusRequest_Tag{
    UINT16 magic; //CMS_SOCK_MGR_UL_STATE_INDICATION_REQ_MAGIC
    UINT16 requestId; //CMS_SOCK_MGR_UL_STATE_INDICATION_REQ_ID
    UINT32 requestSource; // CMS_SOCK_MGR_UL_STATE_INDICATION_REQ_SOURCE_ID
    CmsSockMgrUlStatusInd requestBody;
}CmsSockMgrUlStatusRequest;

typedef struct CmsSockMgrConnHibContext_Tag{
    UINT16 magic;
    UINT8 source;
    UINT8 type;
    INT32 sockId;
    UINT8 status;
    UINT8 domain;
    UINT16 localPort;
    ip_addr_t localAddr;
    void *eventCallback;
    UINT8 priContext[CMS_SOCK_MGR_HIB_PRIVATE_CONTEXT_MAX_LENGTH];
}CmsSockMgrConnHibContext;  //64 bytes


typedef struct CmsSockMgrHibContext_Tag{
    UINT16 magic; //CMS_SOCK_MGR_CONTEXT_MAGIC
    UINT16 flag;
    CmsSockMgrConnHibContext tcpContext;    //64 bytes
    CmsSockMgrConnHibContext udpContext;    //64 bytes
}CmsSockMgrHibContext;  // 92 bytes

typedef void (*CmsSockMgrReqProcess)(CmsSockMgrRequest *Req, ip_addr_t *sourceAddr, UINT16 sourcePort, INT32 rcvRequestFd);

typedef void (*CmsSockMgrEventCallback)(CmsSockMgrContext *mgrContext, CmsSockMgrEventType eventType, void *eventArg);

typedef BOOL (*CmsSockMgrCheckHibMode)(CmsSockMgrContext *mgrContext);

typedef void (*CmsSockMgrStoreConnContext)(CmsSockMgrContext *sockMgrContext, CmsSockMgrConnHibContext *hibContext);
typedef void (*CmsSockMgrRecoverConnContext)(CmsSockMgrConnHibContext *hibContext);

typedef BOOL (*CmsSockMgrTcpServerProcessAcceptClient)(CmsSockMgrContext* gMgrContext, INT32 clientSocketId, ip_addr_t *clientAddr, UINT16 clientPort);

typedef struct cmsSockMgrHandleDefine_Tag{
    UINT32 source;
    CmsSockMgrReqProcess reqProcess;
    CmsSockMgrCheckHibMode hibCheck;
    CmsSockMgrStoreConnContext storeHibContext;
    CmsSockMgrRecoverConnContext recoverHibContext;
    CmsSockMgrTcpServerProcessAcceptClient tcpServerProcessAcceptClient;
}CmsSockMgrHandleDefine;

typedef struct CmsSockMgrDynamicHandleList_Tag{
    CmsSockMgrHandleDefine handle;
    struct CmsSockMgrDynamicHandleList_Tag *next;
}CmsSockMgrDynamicHandleList;

/******************************************************************************
 *****************************************************************************
 * function
 *****************************************************************************
******************************************************************************/
//get ticks
UINT32 cmsSockMgrGetCurrHibTicks(void);
UINT32 cmsSockMgrGetCurrentSysTicks(void);

//cms sock mgr context related
CmsSockMgrContext* cmsSockMgrGetContextList(void);
CmsSockMgrContext* cmsSockMgrGetFreeMgrContext(UINT16 priLen);
CmsSockMgrContext* cmsSockMgrFindMgrContextById(INT32 id);
void cmsSockMgrRemoveContextById(INT32 id);
void cmsSockMgrRemoveContext(CmsSockMgrContext *context);


//cms sock related
INT32 cmsSockMgrCreateSocket(INT32 domain, INT32 type, INT32 protocol, INT32 expect_fd);
INT32 cmsSockMgrBindSocket(INT32 fd, UINT8 domain, UINT16 localPort, ip_addr_t *localAddr);
INT32 cmsSockMgrConnectSocket(INT32 fd, UINT8 domain, UINT16 remotePort, ip_addr_t *remoteAddr, BOOL withTimeout);
INT32 cmsSockMgrCloseSocket(INT32 fd);
INT32 cmsSockMgrCreateTcpSrvSocket(INT32 domain, UINT16 listenPort, ip_addr_t *bindAddr, UINT8 listenNum, INT32 expect_fd);

CmsSockMgrConnStatus cmsSockMgrRebuildSocket(INT32 fd, ip_addr_t *localAddr, ip_addr_t *remoteAddr, UINT16 *localPort, UINT16 *remotePort, INT32 type);

CmsSockMgrConnStatus cmsSockMgrReCreateSocket(INT32 fd, INT32 domain, INT32 type);

//cms sock ul sequence status related
BOOL cmsSockMgrGetUlPendingSequenceState(UINT32 bitmap[8], UINT8 sequence);
void cmsSockMgrUpdateUlPendingSequenceBitMapState(UINT32 bitmap[8], UINT8 sequence, BOOL bActive);

//cms sock send request related
CmsSockMgrActionResult cmsSockMgrSendAsyncRequest(UINT16 reqId, void *reqBody, CmsSockMgrSource source);
CmsSockMgrActionResult cmsSockMgrSendsyncRequest(UINT16 reqId, void *reqBody, CmsSockMgrSource source, CmsSockMgrResponse *response, UINT16 timeout);

//event callback related
void csmsSockMgrCallErrorEventCallback(CmsSockMgrContext* gMgrContext, INT32 errorCode);
void cmsSockMgrCallStatusEventCallback(CmsSockMgrContext* gMgrContext, UINT8 oldStatus, UINT8 newStatus, UINT16 cause);
void cmsSockMgrCallDlEventCallback(CmsSockMgrContext* gMgrContext, CmsSockMgrDataContext *dataContext, ip_addr_t *remoteAddr, UINT16 remotePort);
void cmsSockMgrCallUlStatusEventCallback(CmsSockMgrContext* gMgrContext, UINT8 sequence, UINT8 status);


//cms sock hibernate related
BOOL cmsSockMgrEnableHibMode(CmsSockMgrContext *context);
CmsSockMgrContext* cmsSockMgrGetHibContext(CmsSockMgrConnType type);
void cmsSockMgrRecoverHibCallback(CmsSockMgrHibContext *hibContext);
void cmsSockMgrEnterHibCallback(void *data, LpState state);

//cms sock mgr init related
BOOL cmsSockMgrHandleInit(BOOL bWakeup);

//cms sock mgr handle register/unregister
BOOL cmsSockMgrRegisterHandleDefine(CmsSockMgrHandleDefine *handleDefine);
void cmsSockMgrUnregisterHandleDefine(UINT8 source);




#endif


