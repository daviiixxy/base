#ifndef __UICC_CTRL_USAT_H__
#define __UICC_CTRL_USAT_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - uiccctrlusat.h
Description:    - 
Function List:  - 
History:        - 05/21/2018, Originated by xlhu
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
#define USAT_PROACTIVE_CMD_TAG_OFFSET   0
#define USAT_PROACTIVE_CMD_TAG          0xD0
#define USAT_MENU_SELECTION_TAG         0xD3
#define USAT_SMS_PP_DOWNLOAD_TAG        0xD1
#define USAT_MO_SM_CONTROL_TAG          0xD5
#define USAT_EVENT_DOWNLOAD_TAG         0xD6
#define USAT_TIMER_EXPIRATION_TAG       0xD7



/*********************************************************************************
* Type Definition
*********************************************************************************/    


/*********************************************************************************
* Enums
*********************************************************************************/

//ts102.223 6.10
typedef enum UsatCommandResultTag
{
    USAT_CR_OK,                      /* command result OK */
    USAT_CR_DATA_NOT_UNDERSTOOD,     /* unknown tag value */
    USAT_CR_TYPE_NOT_UNDERSTOOD,     /* unknown Command Type */
    USAT_CR_ERR_REQ_VALUES_MISSING,  /* the minimum set of elements is not complete */
    USAT_CR_UNEXPECTED_TAG,          /* Unexpected tag value */
    USAT_CR_REFRESH_APP_INACTIVE,    /**< Aid do not match current active AID*/
    USAT_CR_REFRESH_NON_USIM_APPS,
    USAT_CR_NOT_SUPPORT_BY_UE,          
    USAT_CR_NOT_CAP               
}
UsatCommandResult;

typedef enum UsatTypeOfCommandTag
{
    USAT_COMMAND_REFRESH                = 0x01,
    USAT_COMMAND_MORE_TIME              = 0x02,
    USAT_COMMAND_POLL_INTERVAL          = 0x03,
    USAT_COMMAND_POLLING_OFF            = 0x04,
    USAT_COMMAND_SET_UP_EVENT_LIST      = 0x05,
    USAT_COMMAND_SET_UP_CALL            = 0x10,
    USAT_COMMAND_SEND_SS                = 0x11,
    USAT_COMMAND_SEND_USSD              = 0x12,
    USAT_COMMAND_SEND_SM                = 0x13,
    USAT_COMMAND_SEND_DTMF              = 0x14,
    USAT_COMMAND_LAUNCH_BROWSER         = 0x15,
    USAT_COMMAND_PLAY_TONE              = 0x20,
    USAT_COMMAND_DISPLAY_TEXT           = 0x21,
    USAT_COMMAND_GET_INKEY              = 0x22,
    USAT_COMMAND_GET_INPUT              = 0x23,
    USAT_COMMAND_SELECT_ITEM            = 0x24,
    USAT_COMMAND_SET_UP_MENU            = 0x25,
    USAT_COMMAND_PROV_LOCAL_INFO        = 0x26,
    USAT_COMMAND_TIMER_MANAGEMENT       = 0x27,
    USAT_COMMAND_SET_UP_ID_MODE_TXT     = 0x28,
    USAT_COMMAND_RUN_AT_COMMAND         = 0x34,
    USAT_COMMAND_LANG_NOTIFICATION      = 0x35,
    USAT_COMMAND_OPEN_CHANNEL           = 0x40,
    USAT_COMMAND_CLOSE_CHANNEL          = 0x41,
    USAT_COMMAND_RECEIVE_DATA           = 0x42,
    USAT_COMMAND_SEND_DATA              = 0x43,
    USAT_COMMAND_GET_CHAN_STATUS        = 0x44

}
UsatTypeOfCommand;

typedef enum UsatComprehensionTlvTag_Tag
{
    USAT_COMMAND_DETAILS_TAG             = 0x01,
    USAT_DEVICE_ID_TAG                   = 0x02,
    USAT_RESULT_TAG                      = 0x03,
    USAT_DURATION_TAG                    = 0x04,
    USAT_ALPHA_ID_TAG                    = 0x05,
    USAT_ADDRESS_TAG                     = 0x06,
    USAT_CCP_TAG                         = 0x07,
    USAT_CPS_TAG                         = 0x08,
    USAT_SS_STRING_TAG                   = 0x09,
    USAT_USSD_STRING_TAG                 = 0x0a,
    USAT_SMS_TPDU_TAG                    = 0x0b,
    USAT_CB_PAGE_TAG                     = 0x0c,
    USAT_TEXT_STRING_TAG                 = 0x0d,
    USAT_TONE_TAG                        = 0x0e,
    USAT_ITEM_TAG                        = 0x0f,
    USAT_ITEM_ID_TAG                     = 0x10,
    USAT_RESP_LENGTH_TAG                 = 0x11,
    USAT_FILE_LIST_TAG                   = 0x12,
    USAT_LOCATION_INFO_TAG               = 0x13,
    USAT_IMEI_TAG                        = 0x14,
    USAT_IMEISV_TAG                      = 0x62,
    USAT_HELP_REQUEST_TAG                = 0x15,
    USAT_NET_MEAS_RESULT_TAG             = 0x16,
    USAT_DEFAULT_TEXT_TAG                = 0x17,
    USAT_NEXT_ACTION_INDICATOR_TAG       = 0x18,
    USAT_EVENT_LIST_TAG                  = 0x19,
    USAT_CAUSE_TAG                       = 0x1a,
    USAT_LOCATION_STATUS_TAG             = 0x1b,
    USAT_TRANSACTION_ID_TAG              = 0x1c,
    USAT_BCCH_CHAN_LIST_TAG              = 0x1d,
    USAT_ICON_ID_TAG                     = 0x1e,
    USAT_ITEM_ICON_ID_LIST_TAG           = 0x1f,
    USAT_TIMER_ID_TAG                    = 0x24,
    USAT_TIMER_VALUE_TAG                 = 0x25,
    USAT_DATETIME_TIMEZONE_TAG           = 0x26,
    USAT_CC_REQ_ACTION_TAG               = 0x27,
    USAT_AT_COMMAND_TAG                  = 0x28,
    USAT_AT_RESPONSE_TAG                 = 0x29,
    USAT_BC_REPEAT_IND_TAG               = 0x2a,
    USAT_IMMEDIATE_RESPONSE_TAG          = 0x2b,
    USAT_DTMF_STRING_TAG                 = 0x2c,
    USAT_LANGUAGE_TAG                    = 0x2d,
    USAT_TIMING_ADVANCE_TAG              = 0x2e,
    USAT_AID_TAG                         = 0x2f,
    USAT_BROWSER_ID_TAG                  = 0x30,
    USAT_URL_TAG                         = 0x31,
    USAT_BEARER_TAG                      = 0x32,
    USAT_PROV_REF_FILE_TAG               = 0x33,
    USAT_BROWSER_TERM_CAUSE_TAG          = 0x34,
    USAT_BEARER_DESCRIPTION_TAG          = 0x35,
    USAT_CHANNEL_DATA_TAG                = 0x36,
    USAT_CHANNEL_DATA_LENGTH_TAG         = 0x37,
    USAT_CHANNEL_STATUS_TAG              = 0x38,
    USAT_BUFFER_SIZE_TAG                 = 0x39,
    USAT_REFRESH_ENFORCEMENT_POLICY_TAG  = 0x3a,
    USAT_USER_PSWD_TEXT_STRING_TAG       = 0x3b,
    USAT_TRANSPORT_LEVEL_TAG             = 0x3c,
    USAT_DEST_URL_TAG                    = 0x3d,
    USAT_DEST_OTHER_ADDRESS_TAG          = 0x3e,
    USAT_NETWORK_ACCESS_NAME_TAG         = 0x47,
    USAT_ACCESS_TECHNOLOGY_TAG           = 0x3f,
    USAT_DISPLAY_PARAMS_TAG              = 0x40,
    USAT_TEXT_ATTRIBUTE_TAG              = 0x50,
    USAT_TEXT_ATTRIBUTE_LIST_TAG         = 0x51,
    USAT_FRAME_IDENTIFIER_TAG            = 0x68,    
    USAT_UTRAN_EUTRAN_MEASUREMENT_QUALIFIER_TAG   = 0x69,
    USAT_PLMNWACT_LIST_TAG               = 0x72,
    USAT_ROUTING_AREA_INFORMATION_TAG    = 0x73,
    USAT_UPDATE_ATTACH_TYPE_TAG          = 0x74,
    USAT_REJECTION_CAUSE_CODE_TAG        = 0x75,
    USAT_TRACKING_AREA_IDENTIFICATION_TAG  = 0x7d,
    USAT_UNKNOWN_TAG
}
UsatComprehensionTlvTag;






typedef enum UsatDeviceIdTag
{
    USAT_KEYPAD_DEVICE_ID               = 0x01,
    USAT_DISPLAY_DEVICE_ID              = 0x02,
    USAT_EARPIECE_DEVICE_ID             = 0x03,
    USAT_CHANNEL_0_DEVICE_ID            = 0x20,
    USAT_CHANNEL_1_DEVICE_ID            = 0x21,   
    USAT_CHANNEL_2_DEVICE_ID            = 0x22,
    USAT_CHANNEL_3_DEVICE_ID            = 0x23,
    USAT_CHANNEL_4_DEVICE_ID            = 0x24,
    USAT_CHANNEL_5_DEVICE_ID            = 0x25,
    USAT_CHANNEL_6_DEVICE_ID            = 0x26,
    USAT_CHANNEL_7_DEVICE_ID            = 0x27,  
    USAT_SIM_DEVICE_ID                  = 0x81,
    USAT_ME_DEVICE_ID                   = 0x82,
    USAT_NETWORK_DEVICE_ID              = 0x83
}
UsatDeviceId;

typedef enum UsatTimeUnitTag
{
    USAT_TIME_UNIT_MINUTES            = 0x00,
    USAT_TIME_UNIT_SECONDS            = 0x01,
    USAT_TIME_UNIT_TENTHS_OF_SECONDS  = 0x02
}
UsatTimeUnit;


typedef enum UsatAccessTechnologyTag
{
    USAT_AT_GSM         = 0x00,
    USAT_AT_UTRAN       = 0x03,
    USAT_AT_EUTRAN      = 0x08,
    USAT_AT_RESERVED    = 0xFF
}
UsatAccessTechnology;

typedef enum UsatTimerIdTag
{
    USAT_TIMER_1        = 0x01,
    USAT_TIMER_2        = 0x02,
    USAT_TIMER_3        = 0x03,
    USAT_TIMER_4        = 0x04,
    USAT_TIMER_5        = 0x05,
    USAT_TIMER_6        = 0x06,
    USAT_TIMER_7        = 0x07,
    USAT_TIMER_8        = 0x08,
    USAT_TIMER_RESERVED        = 0xFF,
}
UsatTimerId;

typedef enum UsatTimerManQualifierTag
{
    USAT_TIMER_START                = 0x00,
    USAT_TIMER_DEACTIVE             = 0x01,
    USAT_TIMER_GET_CURRENT_VALUE    = 0x02
}
UsatTimerManQualifier;


/*********************************************************************************
* STRUCTS
*********************************************************************************/

typedef struct UsatCommandDetailsTag
{
    UINT8                        commandNum;
    UsatTypeOfCommand            typeOfCommand;
    UINT8                        cmdQualifier;
    BOOL                         crFlag;   /* comprehension required flag */
}
UsatCommandDetails;

typedef struct UsatDeviceIdFiledTag
{
    UsatDeviceId                sourceDevId;
    UsatDeviceId                destinationDevId;
}
UsatDeviceIdFiled;

typedef struct UsatRefreshDataTag
{
    UINT32                            cmdDetailsRef;
    UsatFileList                      fileList;//if the fileNum is not zero, the file list is present
    UiccAid                           aid;//if the length is not zero, the aid is present
    UINT8                             refreshEnforcePolicy; //UsatRefreshEnforcePolicyEnum
    UsatAlphaId                       alphaId;
    UsatIconId                        iconId;
    UsatTextAttribute                 usatTextAttribute;
    BOOL                              frameIdPresent;
    UINT8                             frameId;
    BOOL                              plmnListPresent;
    UiccPlmnList                      plmnList; 
}
UsatRefreshData;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
void UsatProcTimerExpiration(UiccCtrlData *uiccCtrlData);

void UiccCtrlHandleTerminalProfileReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatFetchReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatEventDownloadReq(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleCcmUsatRefreshRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleCemmUsatRefreshRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatSetUpEventListRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatProvideLocalInfoRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatImeiSvCnf(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatOpenChannelRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatCloseChannelRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatReceiveDataRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatSendDataRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleUsatGetChannelStatusRsp(UiccCtrlData *uiccCtrlData);
void UiccCtrlHandleSmsPpDownloadReq (UiccCtrlData  *uiccCtrlData);
void UiccCtrlHandleMoSmsCtrlReq (UiccCtrlData  *uiccCtrlData);
void UsatProcSendSmRsp (UiccCtrlData  *uiccCtrlData);
void UiccCtrlHandleUsatRefreshTerminalRsp(UiccCtrlData *uiccCtrlData,
                                            UINT32 cmdDetailsRef,
                                            UINT8 generalResult,
                                            BOOL addiProblemPresent,
                                            UINT8 addiInfoMeProblem);


#endif

