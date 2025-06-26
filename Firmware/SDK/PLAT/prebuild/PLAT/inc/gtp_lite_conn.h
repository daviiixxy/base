/******************************************************************************
 ******************************************************************************
 Copyright:      - 2021- Copyrights of Qualcomm Inc.
 File name:      - gtp_conn.c
 Description:    - GTP transport Layer sub-module
 History:        - 19/08/2021
 ******************************************************************************
******************************************************************************/
#ifndef __GTP_LITE_CONN_H__
#define __GTP_LITE_CONN_H__

typedef enum GtpLiteConnPrimerId_Tag
{
    GTP_LITE_CONN_LINK_UP_REQ = 0x01,
    GTP_LITE_CONN_LINK_UP_IND,
    GTP_LITE_CONN_LINK_DOWN_REQ,
    GTP_LITE_CONN_LINK_DOWN_IND,
    GTP_LITE_CONN_SEND_DATA_REQ,
    GTP_LITE_CONN_SEND_DATA_RSP,
    GTP_LITE_CONN_RECV_DATA_REQ,
    GTP_LITE_CONN_RECV_DATA_RSP,
}GtpLiteConnPrimerId;
	
#endif

