#ifndef __UICC_CTRL_CMD_H__
#define __UICC_CTRL_CMD_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm Ltd.
File name:      - uiccctrlcmd.h
Description:    - UiccCtrl command apdu data defination
Function List:  - 
History:        - 08/30/2017, Originated by xlhu
******************************************************************************/
/*********************************************************************************
* Includes
*********************************************************************************/
#include "pssys.h"
#include "cemmsig.h"
#include "uiccctrldata.h"
#include "uiccctrlsig.h"
/*********************************************************************************
* Macros
*********************************************************************************/
#define UICC_MAX_PATT_LENGTH 255

#define UICC_USIM_SESSION_ACTIVATION     0x00
#define UICC_USIM_SESSION_TERMINATION    0x40
#define UICC_USIM_SESSION_NONE           0x60
    
#define UICC_SELECT_FIRST_OCCURENCE 0x00
#define UICC_SELECT_LAST_OCCURENCE  0x01
#define UICC_SELECT_NEXT_OCCURENCE  0x02
#define UICC_SELECT_PREV_OCCURENCE  0x03
    
#define UICC_RETURN_NO_DATA         0x0C
#define UICC_RETURN_FCP_DATA        0x04
#define UICC_RETURN_FMD_DATA        0x08
#define UICC_RETURN_FCI_DATA        0x00
#define UICC_RETURN_FCI_W_INTERFACE 0x10
    
#define DATA_LEN_SELECT    2
    
#define SW_LENGTH      2
    
#define SW1_NORMAL_ENDING           0x90
#define SW1_NORMAL_ENDING_WITH_EXTRA_INFO_PROCMD    0x91
#define SW1_NORMAL_ENDING_WITH_EXTRA_INFO_RETRIES   0x92
#define SW1_SIMAT_IS_BUSY           0x93
#define SW1_WARNING1                0x62
#define SW1_WARNING2                0x63
#define SW1_EXEC_ERROR_NO_INFO_MEM_UNCHANGE    0x64
#define SW1_EXEC_ERROR_NO_INFO_MEM_CHANGE      0x65
#define SW1_FUNC_IN_CLA_NOT_SUP     0x68
#define SW1_COM_NOT_ALLOWED         0x69
#define SW1_WRONG_PARAM             0x6a
    
    
#define SW1_LENGTH                  0x9f
#define SW1_REFERENCE_ERROR         0x94
#define SW1_SECURITY_ERROR          0x98
#define SW1_WRONG_LENGTH_P3         0x67
#define SW1_WRONG_PARAMS_P1_P2      0x6b
#define SW1_INS_NOT_SUPPORT_OR_INVALID     0x6d
#define SW1_CLASS_NOT_SUPPORT              0x6e
#define SW1_TECHNICAL_PROBLEM         0x6f
    
#define SW1_DDL_ERROR_LENGTH        0x9e
#define SW1_EXPECTED_LENGTH         0x6C
    
    
#define SW1_APP_ERROR               0x98
    
#define SW2_NORMAL                  0x00
#define SW2_MEM_ERROR               0x40
#define SW2_NO_EF                   0x00
#define SW2_OUT_OF_RANGE            0x02
#define SW2_FILE_ID_NOT_FOUND       0x04
#define SW2_PATTERN_NOT_FOUND       0x04
#define SW2_INCONSISTENCY           0x08
#define SW2_NO_CHV_INITIALISED      0x02
#define SW2_AUTHENTICATION_ERROR    0x04
#define SW2_ERROR_WITH_CHV          0x08
#define SW2_ERROR_WITH_INV_STATUS   0x10
#define SW2_NO_ATTEMPTS_LEFT        0x40
#define SW2_CANT_INCREMENT          0x80
#define SW2_NO_INFO_GIVEN                   0x00
#define SW2_INCREASE_CANNOT_BE_PERF         0x50
#define SW2_AUTH_ERROR                      0x62
#define SW2_INCORRECT_DATA_FIELD            0x80
#define SW2_DATA_CORRUPTED                  0x81
#define SW2_MEM_PROBLEM                     0x81
#define SW2_LOGICAL_CHAN_NOT_SUP            0x81
#define SW2_COM_INC_WITH_FILE_STRUCT        0x81
#define SW2_FUNC_NOT_SUPPORTED              0x81
#define SW2_EOF_REACHED_BEFORE_READING_LE   0x82
#define SW2_SEC_MSG_NOT_SUP                 0x82
#define SW2_SEC_STATUS_NOT_SATISFIED        0x82
#define SW2_FILE_NOT_FOUND                  0x82
#define SW2_SELECTED_FILE_INVALID           0x83
#define SW2_AUTH_PIN_BLOCKED                0x83
#define SW2_REC_NOT_FOUND                   0x83
#define SW2_REF_DATA_INVALIDATED            0x84
#define SW2_NOT_ENOUGH_MEMORY               0x84
#define SW2_SELECTED_FILE_TERMINATE         0x85
#define SW2_COND_OF_USED_NOT_SATISFIED      0x85
#define SW2_NO_EF_SELECTED                  0x86
#define SW2_INCORRECT_P1_P2                 0x86
#define SW2_INCONSISTENT_LC                 0x87
#define SW2_REF_DATA_NOT_FOUND              0x88
#define SW2_PIN_METHOD_BLOCKED              0xc0
#define SW2_MORE_DATA_AVAILABLE             0xF1
#define SW2_MORE_DATA_EXPECTED              0xF1
#define SW2_MORE_DATA_AVAIL_PROCMD_PENDING  0xF2
#define SW2_MORE_DATA_EXP_PROCMD_PENDING    0xF2
#define SW2_RESPONSE_DATA_AVAILBLE          0xF3

/*Tags used for the FCI decode, current not support */
#define UICC_FCI_TAG                    0x6F
    
/*Tags used for the FCP decode */
#define UICC_FCP_TAG                    0x62
#define UICC_FILE_DESCRIPTOR_TAG        0x82
#define UICC_FILE_ID_TAG                0x83
#define UICC_DF_NAME_TAG                0x84
#define UICC_PROPRIETARY_INFO_TAG       0xa5
#define UICC_CHARACTERISTICS_TAG        0x80
#define UICC_APP_POWER_CONSUMPTION_TAG  0x81
#define UICC_MIN_APP_CLOCK_FREQ_TAG     0x82
#define UICC_MEM_AVAIL_TAG              0x83
#define UICC_LIFE_CYCLE_STATUS_TAG      0x8a
    
#define UICC_COMPACT_TAG                0x8c
#define UICC_EXPANDED_TAG               0xab
#define UICC_REF_TO_EXPANDED_TAG        0x8b
#define UICC_PIN_STATUS_TEMPLATE_DO     0xc6
    
#define UICC_AM_DO_TAG                  0x80
#define UICC_OR_TAG                     0xa0
#define UICC_AND_TAG                    0xaf
#define UICC_SC_DO_TAG                  0xa4
#define UICC_SC_DO_ALWAYS_TAG           0x90
    
#define UICC_AM_DO_TAG_INS_START        0x81
#define UICC_AM_DO_TAG_INS_END          0x8F
#define UICC_AM_DO_TAG_PROPRITARY       0x9C
    
    
#define UICC_FILE_SIZE_TAG              0x80
#define UICC_TOTAL_FILE_SIZE_TAG        0x81
#define UICC_SHORT_FILE_ID_TAG                    0x88
    
#define UICC_PS_DO_TAG                  0x90
#define UICC_USAGE_QUAL_TAG             0x95
#define UICC_KEY_REFERENCE_TAG          0x83
    
#define UICC_APPLICATION_TEMPLATE_TAG   0x61
#define UICC_APPLICATION_IDENTIFIER_TAG 0x4f
#define UICC_APPLICATION_LABEL_TAG      0x50

#define TLV_TAG_OFFSET  0
#define TLV_LENGTH_OFFSET  1
#define TLV_VALUE_OFFSET_BEGIN 2
#define TLV_TAG_LENGTH_SIZE 2
#define CLASS_A_MASK               0x01
#define CLASS_B_MASK               0x02
#define CLASS_C_MASK               0x04
#define ACTIVATION_MASK            0xfd
#define DELETE_FILE_MASK        0x40
#define TERMINATE_MASK          0x20
#define ACTIVATE_MASK           0x10
#define DEACTIVATE_MASK         0x08
#define WRITE_MASK              0x04
#define UPDATE_MASK             0x02
#define READ_AND_SEARCH_MASK    0x01
#define DELETE_FILE             0x40
#define TERMINATE               0x20
#define ACTIVATE                0x10
#define DEACTIVATE              0x08
#define WRITE                   0x04
#define UPDATE                  0x02
#define READ_AND_SEARCH         0x01

/*length of the TLV objects */
#define UICC_APP_POWER_CONSUMPTION_TLV_LENGTH   3
#define UICC_EF_TOTAL_FILE_SIZE_LENGTH         2
#define UICC_SHORT_FILE_ID_TLV_LENGTH                     1
#define UICC_FILE_SIZE_TLV_LENGTH               2
#define UICC_FILE_ID_TLV_LENGTH                 2
#define UICC_MIN_APP_CLOCK_FREQ_TLV_LENGTH      1
#define UICC_CHARACTERISTICS_TLV_LENGTH         1
#define UICC_LIFE_CYCLE_STATUS_TLV_LENGTH       1
#define UICC_KEY_REFERENCE_TLV_LENGTH           1
#define UICC_USAGE_QUAL_TLV_LENGTH              1
#define UICC_REF_TO_EXPANDED_TLV_LENGTH         3
#define UICC_AM_DO_TLV_LENGTH                   1
#define UICC_CAMPING_FREQ_TLV_LENGTH            2
#define UICC_NEIGHBOUR_FREQ_TLV_LENGTH          2
#define UICC_CLOCK_STOP_MODE_MASK   0x0d

/*   file structures   */
#define EF_STRUCT_TRANS              1
#define EF_STRUCT_LF             2
#define EF_STRUCT_CYC              6

#define SHORT_FILE_ID_REF_USED_FLAG    0x80
#define MAX_BINARY_READ_BYTES    0xff
#define MAX_NUM_PIN_APP                 8

//#define     CIPHERING_KEY_SIZE          8

#define LEVEL_2_KEY_REF   0x80
#define LEVEL_1_KEY_REF   0x00

#define  NO_PREFERRED_LEVEL         0x01
#define  HIGH_LEVEL_ONLY            0x04
#define  HIGH_LEVEL_PREFERRED       0x05
#define  LOW_LEVEL_ONLY             0x08
#define  LOW_LEVEL_PREFERRED        0x09
#define  NEVER_ALLOWED              0x00


#define SHORT_FILE_ID_PL        0x05
#define SHORT_FILE_ID_ARR       0x06
#define SHORT_FILE_ID_DIR       0x1e
#define SHORT_FILE_ID_LI        0x02
#define SHORT_FILE_ID_AD        0x03
#define SHORT_FILE_ID_UST       0x04
#define SHORT_FILE_ID_EST       0x05
#define SHORT_FILE_ID_ACC       0x06
#define SHORT_FILE_ID_IMSI      0x07
#define SHORT_FILE_ID_KEYS      0x08
#define SHORT_FILE_ID_KEYS_PS   0x09
#define SHORT_FILE_ID_LOCI      0x0b
#define SHORT_FILE_ID_PS_LOCI   0x0c
#define SHORT_FILE_ID_FPLMN     0x0d
#define SHORT_FILE_ID_CBMID     0x0e
#define SHORT_FILE_ID_START_HFN 0x0f
#define SHORT_FILE_ID_THRESHOLD 0x10
#define SHORT_FILE_ID_HPLMN     0x12
#define SHORT_FILE_ID_ICI       0x14
#define SHORT_FILE_ID_OCI       0x15
#define SHORT_FILE_ID_PNN       0x19
#define SHORT_FILE_ID_OPL       0x1a
#define SHORT_FILE_ID_OPLMN_ACT 0x11
#define SHORT_FILE_ID_HPLMN_ACT 0x13
#define SHORT_FILE_ID_USIM_ARR  0x17
#define SHORT_FILE_ID_EPS_NSC   0x18
#define SHORT_FILE_ID_EPS_LOCI  0x1E

    

/*********************************************************************************
* Type Definition
*********************************************************************************/  

/******************************************************************************
 *****************************************************************************
 * Enums
 *****************************************************************************
******************************************************************************/

typedef enum UiccSelectMethodTag
{
    SELECT_BY_FILE_ID                  = 0x00,
    SELECT_CHILD_DF_OF_CURRENT_DF      = 0x01,
    SELECT_PARENT_DF_OF_CURRENT_DF     = 0x03,
    SELECT_BY_DF_NAME                  = 0x04,
    SELECT_BY_PATH_FROM_MF             = 0x08,
    SELECT_BY_PATH_FROM_DF             = 0x09
}
UiccSelectMethod;

typedef enum UiccClassByteTag
{
    UICC_USIM_CLASS    = 0x00,
    UICC_80_CLASS      = 0x80,
    UICC_90_CLASS      = 0x90,
    UICC_40_CLASS      = 0x40,
    UICC_GSM_CLASS     = 0xa0
}
UiccClassByte;

typedef enum UiccLogicalChannelTag
{
    BASIC_CHANNEL            = 0,
    LOGICAL_CHANNEL_1        = 1,
    LOGICAL_CHANNEL_2        = 2,
    LOGICAL_CHANNEL_3        = 3,
    MAX_LOGICAL_CHANNELS_NUM = 4
}
UiccLogicalChannel;

typedef enum UiccAdfSelectModeTag
{
    UICC_FIRST_OR_ONLY_OCCURRENCE       = 0x00,
    UICC_LAST_OCCURRENCE                = 0x01,
    UICC_NEXT_OCCURRENCE                = 0x02,
    UICC_PREVIOUS_OCCURRENCE            = 0x03
}
UiccAdfSelectMode;

typedef enum StatusPara1Tag
{
    STATUS_NO_INDCATION = 0,
    STATUS_APP_INITIALIZED = 1,
    STATUS_APP_TO_TERMIANTE = 2
}
StatusPara1;

typedef enum ApduCmdTag
{
    APDU_CMD_SELECT             = 0xa4,
    APDU_CMD_STATUS             = 0xf2,
    APDU_CMD_SLEEP              = 0xfa,
    APDU_CMD_READ_BINARY        = 0xb0,
    APDU_CMD_UPDATE_BINARY      = 0xd6,
    APDU_CMD_READ_RECORD        = 0xb2,
    APDU_CMD_UPDATE_RECORD      = 0xdc,
    APDU_CMD_SEARCH_RECORD      = 0xa2,
    APDU_CMD_INCREASE           = 0x32,
    APDU_CMD_VERIFY_PIN         = 0x20,
    APDU_CMD_CHANGE_PIN         = 0x24,
    APDU_CMD_DISABLE_PIN        = 0x26,
    APDU_CMD_ENABLE_PIN         = 0x28,
    APDU_CMD_UNBLOCK_PIN        = 0x2c,
    APDU_CMD_INVALIDATE         = 0x04,
    APDU_CMD_REHABILITATE       = 0x44,
    APDU_CMD_AUTHENTICATE       = 0x88,

    APDU_CMD_MANAGE_CHANNEL     = 0x70,
    APDU_CMD_SUSPEND_UICC       = 0x76,
    APDU_CMD_GET_CHALLENGE      = 0x84,

    APDU_CMD_GET_RESPONSE       = 0xc0,
    APDU_CMD_TERMINAL_PROFILE   = 0x10,
    APDU_CMD_ENVELOPE           = 0xC2,
    APDU_CMD_FETCH              = 0x12,
    APDU_CMD_TERMINAL_RESPONSE  = 0x14
}
ApduCmd;

typedef enum UiccParseStatusTag
{
    UICC_PARSE_OK,
    UICC_PARSE_TYPE_NOT_UNDERSTOOD,  /* for usat, unknown data Type in Cmd Details data */
    UICC_PARSE_REQ_VALUES_MISSING,   /* No valid value */
    UICC_PARSE_UNEXPECTED_TAG,       /* Unexpected/Unknown tag */
    UICC_PARSE_WRONG_LENGTH,          
    UICC_PARSE_SEC_ATTRIBUTES_MISSING,
    UICC_PARSE_PHONEBOOK_ERROR,           
    UICC_PARSE_PIN_TEMPLATE_ERROR         
}
UiccParseStatus;


typedef enum UiccFileRecordTag
{
    UICC_REC_UNDEFINED,
    UICC_REC_UNKNOWN,
    UICC_REC_KNOWN
}
UiccFileRecord;


typedef enum UiccRecordRwModeTag
{
    UICC_REC_RWMODE_CURRENT_ABSOLUTE =   0x04,
    UICC_REC_RWMODE_NEXT             =   0x02,
    UICC_REC_RWMODE_PREVIOUS         =   0x03
}
UiccRecordRwMode;

/******************************************************************************
 *****************************************************************************
 * STRUCTS
 *****************************************************************************
******************************************************************************/
/*
* the parameters for select command
*/
typedef struct SelectCommandParaTag
{
    //UiccClassByte                  classByte;
    //UiccLogicalChannel             logicalChannel;
    UiccSelectMethod               selectMethod;
    BOOL                           expectedRspData;
    UiccFileType                   fileType;
    AppSessionCtrl                 sessionCtrl;
    UiccAdfSelectMode              adfSelectMode;
    UINT16                         fileId;
    UiccFilePath                   filePath;
    UiccAid                        aid;
}
SelectCommandPara;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
BOOL ResetUiccCmdStatus(CommandStatus  cmdStatus);
StatusWords ParseUiccStatusWords(UiccCtrlData *uiccCtrlData, 
                                 UiccCtrlDrvCmdRsp *rspApduData);
void ExecuteUiccSelectCommand(SelectCommandPara *selectCommandPara, 
                              UiccCtrlData *uiccCtrlData);
void ExecuteUiccStatusCommand(UiccCtrlData *uiccCtrlData, 
                              StatusPara1 statusP1);
void ExecuteUiccReadBinaryCommand(UINT16  efId, 
                                  UINT16 numberOfBytes, 
                                  UINT16 offset, 
                                  UiccCtrlData *uiccCtrlData, 
                                  ApduDataBlock *dataBlock);
void ExecuteUiccUpdateBinaryCommand(UINT16  efId, 
                                    UINT16 offset, 
                                    ApduDataBlock *dataBlock, 
                                    UiccCtrlData *uiccCtrlData);
void ExecuteUiccReadRecordCommand(UINT16 efId, 
                                  UiccRecordRwMode mode, 
                                  UINT8 recordNumber, 
                                  UiccCtrlData *uiccCtrlData, 
                                  ApduDataBlock *dataBlock);

void ExecuteUiccUpdateAttTstCommand( ApduDataBlock  *dataBlock,
                                                  UiccCtrlData   *uiccCtrlData);
void ExecuteUiccReadEfActingHplmnCommand(UINT16          numberOfBytes,
                                            UINT16          offset,
                                            UiccCtrlData    *uiccCtrlData,
                                            ApduDataBlock   *dataBlock);


#ifdef FEAT_RPM
void ExecuteUiccReadRpmBinaryCommand(UINT16                    efId,
                                            UINT16          numberOfBytes,
                                            UINT16          offset,
                                            UiccCtrlData    *uiccCtrlData,
                                            ApduDataBlock   *dataBlock);

void ExecuteUiccUpdateRpmBinaryCommand(UINT16         efId,
                                    UINT16         offset,
                                    ApduDataBlock  *dataBlock,
                                    UiccCtrlData   *uiccCtrlData);
#endif

void ExecuteUiccUpdateRecordCommand(UINT16                  efId,
                                    UiccRecordRwMode        mode,
                                    ApduDataBlock          *dataBlock,
                                    UINT8                   recordNumber,
                                    UiccCtrlData           *uiccCtrlData);

void ExecuteUiccVerifyPinCommand(UINT8              *pinValue,
                                 UiccKeyRefValue    keyRef,
                                 BOOL               retryCountOnly,
                                 UiccCtrlData       *uiccCtrlData);

void ExecuteUiccChangePinCommand(UiccPinValue       oldPinValue,
                                 UiccPinValue       newPinValue,
                                 UiccCtrlData       *uiccCtrlData,
                                 UiccKeyRefValue    keyRef);
                                     
void ExecuteUiccDisablePinCommand(UiccPinValue       pinValue,
                                  UiccCtrlData       *uiccCtrlData,
                                  UiccKeyRefValue    rpKeyReference,
                                  UiccKeyRefValue    keyRef);


void ExecuteUiccEnablePinCommand(UiccPinValue       pinValue,
                                 UiccCtrlData       *uiccCtrlData,
                                 UiccKeyRefValue    keyRef);

void ExecuteUiccUnblockPinCommand(UiccPinValue       unblockPinValue,
                                  UiccPinValue       newPinValue,
                                  BOOL               retryCountOnly,
                                  UiccCtrlData       *uiccCtrlData,
                                  UiccKeyRefValue    keyRef);

void ExecuteUiccAuthenticateCommand(UINT8           *rand,
                                    UINT8           *autn,
                                    UiccCtrlData    *uiccCtrlData,
                                    Auts            *auts,
                                    CkIkContent     *key,
                                    AuthRes         *authRes);

void ExecuteSuspendUiccCommand(UiccSuspendType      cmdType,
                               UiccSuspendDuration  minDuration,
                               UiccSuspendDuration  maxDuration,
                               UINT8                *pSecData,
                               UiccCtrlData         *uiccCtrlData);
void ExecuteUiccManageChannelCommand(BOOL isOpen, UINT8 *logicChNum, UiccCtrlData *uiccCtrlData);

void ExecuteUiccGenAccessCommand(UINT8                  *commandData,
                                            UINT16       commandLength,
                                            UINT8        **rspApdu,
                                            UINT16       *rspApduLen,
                                            UiccCtrlData *uiccCtrlData);
void ExecuteUiccGenLogicalChAccessCommand(UINT8                  *commandData,
                                                    UINT16       commandLength,
                                                    UINT8        **rspApdu,
                                                    UINT16       *rspApduLen,
                                                    UiccCtrlData *uiccCtrlData);

void ExecuteUiccTerminalProfileCommand(UiccCtrlData *uiccCtrlData, UINT8 tpLen, UINT8 *pTpValue);

void ExecuteUiccFetchCommand(UiccCtrlData   *uiccCtrlData, 
                             ApduDataBlock  *dataBlock);
void ExecuteUiccTerminalResponseCommand(UiccCtrlData    *uiccCtrlData, 
                                        ApduDataBlock   *dataBlock);
                                     
UiccParseStatus ParseUiccApplicationTemplate(ApduDataBlock  *dataBlock, 
                                             UiccAid        *aid, 
                                             UiccAidLabel   *label);
UiccParseStatus ParseUiccArrRecord(UINT8                    recordLength,
                                   UINT8                    *ptr,
                                   UiccEfExpandedFormat     *expandedFormat);
BOOL ExecuteUiccEnvelopeCommand(UiccCtrlData *uiccCtrlData, ApduDataBlock *dataBlock);

#endif

