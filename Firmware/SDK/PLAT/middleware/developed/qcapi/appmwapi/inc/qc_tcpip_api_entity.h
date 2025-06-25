/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: tcpip_lib_event.h
 *
 *  Description: tcpip related SDK API
 *
 *  History: create by xwang
 *
 *  Notes:
 *
******************************************************************************/
#ifndef __TCPIP_LIB_TASK_H__
#define __TCPIP_LIB_TASK_H__

#include "commontypedef.h"
#include "cms_sock_mgr.h"



/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/

typedef enum{
    TCPIP_API_REQ_CREATE_CONNECTION = 19,
    TCPIP_API_REQ_SEND_DATA         = 20,
    TCPIP_API_REQ_CLOSE_CONNECTION  = 21,    
}TcpipApiRequestId;

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/
typedef struct TcpipApiCreateConnectionReq_Tag{
    UINT32 type;
    UINT16 localPort;
    UINT16 remotePort;
    ip_addr_t localAddr;
    ip_addr_t remoteAddr;
    void *eventCallback;
    void *tcpipApiConnEventCallback;
}TcpipApiCreateConnectionReq;

typedef struct TcpipApiSendDataReq_Tag{
    UINT32 connectionId;
    UINT8 raiInfo;
    UINT8 expectFlag;
    UINT16 dataLen;
    UINT8 sequence;
    UINT8 rsvd1;
    UINT8 rsvd2;
    UINT8 data[];
}TcpipApiSendDataReq;

typedef struct TcpipApiCloseConnectionReq_Tag{
    UINT32 connectionId;
}TcpipApiCloseConnectionReq;

typedef struct TcpipApiPriMgrContext_Tag{
    UINT16 createSourcePort;
    UINT16 creatTimeout;
    UINT32 startCreateTicks;
    UINT32 rcvRequestFd;
    void *tcpipApiConnEventCallback;
    ip_addr_t createSourceAddr;
    UINT32 bitmap[8];
}TcpipApiPriMgrContext;

typedef struct TcpipCreateConnResult_Tag{
    INT32 connectionId;
    INT32 cause;
}TcpipCreateConnResult;

typedef struct TcpipSendDataResult_Tag{
    INT32 sendLen;
    INT32 cause;
}TcpipSendDataResult;

typedef struct TcpipCloseResult_Tag{
    INT32 result;
    INT32 cause;
}TcpipCloseResult;

typedef struct TcpipApiConnHibPriContext_Tag{
    void *tcpipApiConnEventCallback;
}TcpipApiConnHibPriContext;


/******************************************************************************
 *****************************************************************************
 * FUNCTION/API
 *****************************************************************************
******************************************************************************/

void tcpipApiProessReq(CmsSockMgrRequest *atecSktReq, ip_addr_t *sourceAddr, UINT16 sourcePort, INT32 rcvRequestFd);
void tcpipApiEventCallback(CmsSockMgrContext *mgrContext, CmsSockMgrEventType eventType, void *eventArg);
BOOL tcpipCheckHibMode(CmsSockMgrContext *mgrContext);
void tcpipApiStoreConnHibContext(CmsSockMgrContext *sockMgrContext, CmsSockMgrConnHibContext *hibContext);
void tcpipApiRecoverConnContext(CmsSockMgrConnHibContext *hibContext);








#endif

