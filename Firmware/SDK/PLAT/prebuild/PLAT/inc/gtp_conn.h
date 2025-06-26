/******************************************************************************
 ******************************************************************************
 Copyright:      - 2021- Copyrights of Qualcomm Inc.
 File name:      - gtp_conn.c
 Description:    - GTP transport Layer sub-module
 History:        - 19/08/2021
 ******************************************************************************
******************************************************************************/

#ifndef __GTP_CONN_H__
#define __GTP_CONN_H__

#include "gtp_lite_conn.h"
#include "cms_api.h"


#define MAX_IP_ADDRESS_LEN        	   4
#define GTP_CONN_ATTACH_BEARER_CID     0
#define GTP_CONN_CTXT_MAX			   1

typedef enum GtpConnTransProtocol_Tag
{
    GTP_CONN_TRANS_PROTO_TCP = 0,
    GTP_CONN_TRANS_PROTO_UDP = 1,
    GTP_CONN_TRANS_PROTO_NIDD =2,
}GtpConnTransProtocol;

typedef enum GtpConnLinkState_Tag
{
    GTP_CONN_LINK_NULL,		    //socket is closed
    GTP_CONN_LINK_CONN_ERROR,	//socket (or)bind (or)connect is failed 
    GTP_CONN_LINK_READY,	    //socket is up
    GTP_CONN_LINK_SEND_ERROR, 	//send failed to send the data (or) socket is not availble
    GTP_CONN_LINK_QSP_ERROR,
    GTP_CONN_LINK_RECV_TIMEOUT_ERROR, //there is a timeout error while receiving the data from GTPSERVER
    GTP_CONN_LINK_DROPPED,		//if socket is not up (or) any socket fatal error 
}GtpConnLinkState;

typedef struct GtpConnLinkUpInd_Tag
{
    UINT8	cid;
    UINT8 	protocolFamily;               /* client family AF_INET, AF_INET6, AF_NONIP */
	UINT8 	qspCfg;    
    UINT8 	transProtocol;                /* TCP, UDP, NIDD*/
    UINT16  portNum;
    union {
    	UINT8   ipv4DestAddr[MAX_IP_ADDRESS_LEN];          /* destination address */
    	UINT32 	ipv6DestAddr[MAX_IP_ADDRESS_LEN];
    }un;
	UINT8 *serverKeyFile;
} GtpConnLinkUpReq;


typedef struct GtpConnLinkDownInd_Tag
{
    uint8_t     cause;
}GtpConnLinkDownInd;

typedef struct GtpConnRecvDataReq_Tag
{
	uint8_t				   numReTxMax;
    uint32_t	           recvTimeOut;// fill the recvtimeout in secs
}GtpConnRecvDataReq;

typedef struct GtpConnDataPdu_Tag
{
    uint16_t                        length;
    uint8_t                         *ptr;
}GtpConnDataPdu;

typedef struct GtpConnRecvDataRsp_Tag
{
    GtpConnDataPdu       dataPdu;	// In case of timeout, length would be 0,  prt will be NULL
} GtpConnRecvDataRsp;

typedef struct GtpConnSendDataReq_Tag
{
    GtpConnDataPdu       dataPdu;
}GtpConnSendDataReq;

typedef struct GtpConnCtxt_tag
{
    GtpConnLinkState        linkState;
    int                     mySocket;
	UINT8					endTimeoutFlag;//this flag indicates that recv end timeout is calculated if it is set to 1
	UINT32					recvEndTimeout;
	UINT8					transport;
	GtpConnDataPdu			txPdu; //Used only in case of UDP for retx
	uint8_t					txCount; //Used only in case of UDP for retx
}GtpConnCtxt;

typedef struct GtpConnDynData_Tag
{
    GtpConnCtxt        ctxt[GTP_CONN_CTXT_MAX];
}GtpConnDynData;


int32_t GtpConnInit(void);
int32_t GtpConnDeInit(void);

#endif



