#ifndef __UICC_CTRL_USIM_H__
#define __UICC_CTRL_USIM_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - uiccctrlusim.h
Description:    -
Function List:  -
History:        - 09/05/2017, Originated by xlhu
******************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
//#include "pscommutil.h"
#include "uiccctrldata.h"
#include "pssys.h"
#include "ccmsimsig.h"
/*********************************************************************************
* Macros
*********************************************************************************/

#define     CK_OFFSET            1
#define     IK_OFFSET              17
#define     EF_KEYS_FILE_SIZE      33

/*********************************************************************************
* Type Definition
*********************************************************************************/


/*********************************************************************************
* Enums
*********************************************************************************/

/*********************************************************************************
* STRUCTS
*********************************************************************************/


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
void ConvertCcmRequestStatus(CommandStatus cmdStatus,
                                 StatusWords  statusWords, UINT8 *cnfStatus);
void UiccCtrlHandleTeminateSessionReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandlePinOperateReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleCcmReadDataReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleCcmUpdateDataReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleGenAccessReq(UiccCtrlData *uiccCtrlData);
void NotifyCcmCardRemoved(UiccRemovedCause uiccRmCause);
void NotifyMmCardRemoved(void);
void UiccCtrlHandleMmReadDataReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleMmWriteDataReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleMmAuthReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleRestoreDataReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandlePowerReduceInd(UiccCtrlData *uiccCtrlData);
void UiccctrlHandleOpenLogicalChannelReq(UiccCtrlData *uiccCtrlData);
void UiccctrlHandleCloseLogicalChannelReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleSimWriteCntReq(UiccCtrlData *uiccCtrlData);
#ifdef FEAT_RPM
void UiccCtrlHandleRpmUpdateOmParamReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleReadRpmParamReq(UiccCtrlData *uiccCtrlData);
#endif
void UiccCtrlHandleGenLogicalChAccessReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleSimPresenceDetectReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleGetSubscriberNumReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleSimSleepReq(UiccCtrlData *uiccCtrlData);


#endif
