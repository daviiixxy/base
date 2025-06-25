#ifndef _CEMM_SS_SIG_H_
#define _CEMM_SS_SIG_H_
/******************************************************************************
Copyright:      - 2018, All rights reserved by Qualcomm
File name:      - cemmssmsg.h
Description:    - Define the interface between EMM and SS.
Function List:  - 
History:        - 12/06/2017, Originated by flxing
*******************************************************************************/

/*******************************************************************************
 * Includes
*******************************************************************************/

#include "pssys.h"
#include "nascommon.h"

/*******************************************************************************
 * ENUM
*******************************************************************************/
typedef enum SsMessageContainerTypeTag
{
    LPP_MESSAGE = 1, /* Table 9.9.3.42.1: Generic message container type information element */
    LCS_MESSAGE = 2
}
SsMessageContainerType;

/*******************************************************************************
 * SS->CEMM
*******************************************************************************/

typedef GosEmptySignal CemmSsEstReq;

typedef struct CemmSsUnitDataReqTag
{
    UINT8       msgContainerType;        /* SsMessageContainerType */
    UINT16      genericMsgLength;
    UINT8       *pGenericMsg;
    UINT8       addInfoPresent; /* Additional Information present */
    UINT8       addInfoLength;  /* Additional Information content length */
    UINT8       addInfoData[MAX_ADDITIONAL_INFORMATION_IE_SIZE];      /* Additional Information content */
}
CemmSsUnitDataReq;

/*******************************************************************************
 * CEMM->SS
*******************************************************************************/

typedef struct CemmSsEstCnfTag
{
    BOOL            success;
    UINT8           reserved0;
    UINT16          reserved1;
}
CemmSsEstCnf;

typedef struct CemmSsUnitDataIndTag
{
    UINT8       msgContainerType;        /* SsMessageContainerType */
    UINT16      genericMsgLength;
    UINT8       *pGenericMsg;
    UINT8       addInfoPresent; /* Additional Information present */
    UINT16      addInfoLength;  /* Additional Information content length */
    UINT8       addInfoData[MAX_ADDITIONAL_INFORMATION_IE_SIZE];      /* Additional Information content */
}
CemmSsUnitDataInd;

typedef GosEmptySignal CemmSsSuspendInd;
typedef GosEmptySignal CemmSsResumeInd;

/******************************************************************************
 * INTERNAL MSG API
******************************************************************************/

/*
 * CEMM API
 * When SS request sending data,call this internal Msg to establish RRC connection
 * then CEMM module will trigger service request/control service request
 * srcId = CE_NAS_SS
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CemmSsEstRequest(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CEMM API
 * When SS request sending data,call this internal Msg
 * then CEMM module will forward the SS message to NW
 * srcId = CE_NAS_SS
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = CemmSsUnitDataReq
*/
void CemmSsUnitDataRequest(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);


/*
 * CESS API
 * CEMM send establish confirm to CESS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = BOOL
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CessEstConfirm(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESS API
 * CEMM send SS data to CESS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = CemmSsUnitDataInd
*/
void CessUnitDataInd(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESS API
 * CEMM send suspend indication to CESS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CessSuspendInd(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);

/*
 * CESS API
 * CEMM send resume indication to CESS submodule.
 * srcId = CE_NAS_CEMM
 * argvUint8 = 0
 * argvUint16 = 0
 * argvUint32 = 0
 * argvPtr = PNULL
*/
void CessResumeInd(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);


#endif



