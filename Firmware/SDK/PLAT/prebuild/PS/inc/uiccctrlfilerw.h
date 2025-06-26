#ifndef __UICCCTRL_FILERW_H__
#define __UICCCTRL_FILERW_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm Ltd.
File name:      - uiccctrlfilerw.h
Description:    -
Function List:  -
History:        - 08/30/2017, Originated by xlhu
******************************************************************************/
/*********************************************************************************
* Includes
*********************************************************************************/
#include "uiccctrldata.h"
#include "ccmsimsig.h"
#include "uiccctrlsig.h"
#include "cemmsig.h"
/*********************************************************************************
* Macros
*********************************************************************************/

#define  USIM_NUM_SERVICES_PER_BYTE      8

#define USIM_EPSLOCI_LENGTH             0x12
#define USIM_EPSLOCI_GUTI_LENGTH        0x0B
#define USIM_EPSLOCI_LAST_TAI_LENGTH    0x05
#define USIM_EPSLOCI_STATUS_LENGTH      0x01
#define USIM_EPSLOCI_GUTI_FLAG          0xF6
#define RAW_LAI_IE_SIZE                 5

#define  USIM_APN_LIST_SIZE               10

#define SIM_MAX_NUM_DCK_DIGITS          8

#define PLMN_ELEMENT_SIZE              3
#define ACCESS_TECHNOLOGY_ELEMENT_SIZE 2

/*********************************************************************************
* Type Definition
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/

/*********************************************************************************
* STRUCTS
*********************************************************************************/

typedef struct UiccDckDataTag
{
  BOOL               networkDckValid;
  BOOL               networkSubsetDckValid;
  BOOL               serviceProviderDckValid;
  BOOL               corporateDckValid;
  UINT8              netDckDigit[SIM_MAX_NUM_DCK_DIGITS];
  UINT8              netSubDckDigit[SIM_MAX_NUM_DCK_DIGITS];
  UINT8              spDckDigit[SIM_MAX_NUM_DCK_DIGITS];
  UINT8              corporateDckDigit[SIM_MAX_NUM_DCK_DIGITS];
}
UiccDckData;






/*
typedef struct WritePlmnDataResTag
{
    UINT8      numEntriesStored;
}
WritePlmnDataRes;
*/

/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
#define USIM_SERVICE_ENABLED(s)         (BOOL)(uiccCtrlData->uiccAppData.serviceTable.s)
#define USIM_SERVICE_DEACTIVATE(n)      (uiccCtrlData->uiccAppData.serviceTable.n = FALSE)

void Encode3DigitMcc(UINT16 mcc, UINT16 mnc, UINT8 *data);
void Encode3DigitMnc(UINT16 mnc, UINT8 *data );
void EncodeMcc(UINT16 mcc, UINT8 *data);
void EncodeMnc(UINT16 mnc, UINT8 *data);
void ParsePlmnData(ApduDataBlock *dataBlock,
                           UINT16         startField,
                           UINT16         expectEntriesNum,
                           UINT16         *totalEntries,
                           UiccPlmnList       *plmnList,
                           BOOL           accessTechnologyPresent);


void ReadPreferLanguage(UiccCtrlData       *uiccCtrlData);
void ReadUsimServiceTable(UiccCtrlData *uiccCtrlData);
void ReadEnabledServiceTable(UiccCtrlData *uiccCtrlData);
void ReadAdminData (UiccCtrlData *uiccCtrlData);
void ReadIccid (UiccCtrlData *uiccCtrlData);
void ReadUiccMaxPowerConsumption(UiccCtrlData *uiccCtrlData);
void UpdateAttTerminalSupportTable(UiccCtrlData *uiccCtrlData);

void ReadFplmn (UiccCtrlData *uiccCtrlData, UiccPlmnList *plmnList, UINT16 *totalEntries);
void ReadEpsLoci (UiccCtrlData *uiccCtrlData,
                    EPSFilePresentType *epsEfPreset,
                    EpsLocationInfo *epsLociInfo,
                    BOOL *epsLociInfoValid);
void ReadPsLoci(UiccCtrlData *uiccCtrlData);
BOOL ReadAccessCtrlInfo (UiccCtrlData *uiccCtrlData, AccessClass *accessClass);
void ReadLrPlmnsi (UiccCtrlData *uiccCtrlData, BOOL *attemptHplmn);
void ReadHpplmnSearchPeriod (UiccCtrlData *uiccCtrlData, UINT16 *hpPlmnSearchPeriod);
void ReadImsi(UiccCtrlData *uiccCtrlData, BOOL *imsiEfValid);
void ReadPrefHplmnwAct(UiccCtrlData *uiccCtrlData, AccessTechnologyId* prefHplmnAct);
void ReadPlmnData (UiccCtrlData *uiccCtrlData,
                    UINT16 plmnFileId,
                    UINT16 startField,
                    UiccPlmnList *plmnList,
                    UINT16 *totalEntries);
void ReadDck (UiccCtrlData *uiccCtrlData, UiccDckData *dckData);
void ReadMsisdnReq(UiccCtrlData  *uiccCtrlData, SimDialNumberList     *pDialNumList);
void GetFdnEnabled(UiccCtrlData *uiccCtrlData);
void GetAclEnabled(UiccCtrlData *uiccCtrlData);
void ReadKeysPs(UiccCtrlData *uiccCtrlData);
void ReadEpsNscInfo(EpsNscInfo          *epsNscInfo,
                        BOOL            *epsNscInfoValid,
                        EPSFilePresentType *epsEfPreset,
                        UiccCtrlData    *uiccCtrlData);
void UpdatePlmnwActReq(UiccCtrlData  *uiccCtrlData,
                            UINT16 plmnFileId,
                            UiccPlmnList *plmnList,
                            UINT8 *numEntriesStored);
void UpdateEpsLociReq(UiccCtrlData *uiccCtrlData, EpsLocationInfo *epsLociInfo);
void UpdateEpsNscReq(UiccCtrlData *uiccCtrlData, EpsNscInfo *epsNscInfo);
void AddFplmnReq(UiccCtrlData *uiccCtrlData, UiccPlmnList *plmnList);
void DeleteFplmnReq(UiccCtrlData *uiccCtrlData, SimPlmnDelReqData *delFplmnData);
void ReadSmspReq(UiccCtrlData  *uiccCtrlData, UINT8 recordNum,
                    SimSmsParams *smsp, BOOL *smspValid);
void ReadSmssReq(UiccCtrlData  *uiccCtrlData, UINT8 *pMsgRef, BOOL *pMemExceed);

void ReadNasConfigParams(UiccCtrlData *uiccCtrlData, NasConfig *nasConfigParams);
void UpdateSmspReq(UiccCtrlData *uiccCtrlData, UINT8 recordNum, SimSmsParams *pSmsp);
void UpdateSmssReq(UiccCtrlData *uiccCtrlData, UiccSmssUpdateReqParam *pUpdateSmssReqParam);
void ReadEfActingHplmn(UiccCtrlData *uiccCtrlData, UiccPlmn *actingHplmn);
#ifdef FEAT_RPM
void ReadRpmParameters(UiccCtrlData *uiccCtrlData, RpmParameters *rpmParams);
void ReadRpmEnabled(UiccCtrlData *uiccCtrlData, UINT8 *rpmEnabled);
void ReadRpmOMParameters(UiccCtrlData *uiccCtrlData, RpmOMParmeters *rpmOMParams, BOOL *rpmOmParamsValid);
void ReadRpmOMParametersLeakRate(UiccCtrlData *uiccCtrlData, RpmOMParmetersLeakRate *rpmOMParamsLR);
void UpdateRpmVersion(UiccCtrlData *uiccCtrlData, UINT8 rpmVersion);
void UpdateRpmOMCounters(UiccCtrlData *uiccCtrlData, RpmOMParmeters *rpmOMParams);
#endif




#endif

