/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: sntp.c
 *
 *  Description: sntp
 *
 *  History:creat by xwang
 *
 *  Notes:
 *
******************************************************************************/

#include "commontypedef.h"


#define SNTP_RCV_TIMEOUT 15  //seconds
#define SNTP_RETRY_TIMES 3
#define SNTP_RESEND_REQUEST_DELAY 5000 //ms

#define SNTP_DEFAULT_PORT  123



BOOL SntpInit(CHAR* serverAddr, UINT16 serverPort, UINT16 reqHandler, BOOL autoSync);

void SntpTerminat(void);

