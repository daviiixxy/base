#ifndef _CEMM_SIG_H_
#define _CEMM_SIG_H_
/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    cerrcsig.h
 * Description:  define all signals received by MM module
 * History:      09/08/2017    Originated by Yunfei Li
 *
 ****************************************************************************/

/*********************************************************************************
* Includes
*********************************************************************************/
#include "pscommtype.h"
#include "pspdu.h"
#include "cmips.h"
#include "lcscomm.h"
#ifndef WIN32
#if defined CHIP_QCX212 || defined CHIP_QCX212_Z0
#include "ecpm_qcx212.h"
#endif

#endif
/*********************************************************************************
* Macros
*********************************************************************************/
#define     CK_SIZE                     16
#define     IK_SIZE                     16

/*********************************************************************************
* Type Definition
*********************************************************************************/


/*********************************************************************************
* Enums
*********************************************************************************/
/********************************************************************************
* RRC->MM
*********************************************************************************/
typedef enum PlmnListStatusTag
{
    PLMN_LIST_SUCCESS = 0,
    PLMN_LIST_FAILED = 1,
    PLMN_LIST_FAILED_NO_VALID_PLMN = 2,         //no requested PLMN in FG plmnsearchreq
    PLMN_LIST_FAILED_NO_VALID_FREQ_BAND = 3,    //no valid freq and band in cerrcplmnsearchreq
    PLMN_LIST_FAILED_WRONG_STATE = 4,           //plmn search is triggered in incorrect RRC state
    PLMN_LIST_ABORT = 5,
    PLMN_LIST_ABORT_CELL_RESELECTION = 6,       //plmn search is aborted due to starting cell reselection procedure
    PLMN_LIST_ABORT_ACT_REQ = 7,                //plmn search is aborted due to starting to handle CerrcActReq
    PLMN_LIST_ABORT_ESCAPE_SCELL = 8,           //plmn search is aborted because serving cell is NOT suitable anymore
    PLMN_LIST_ABORT_SI_UPDATE = 9,              //plmn search is aborted due to system information modification
    PLMN_LIST_ABORT_AS_DEACT = 10,              //plmn search is aborted because AS will be deactivated
    PLMN_LIST_ABORT_ESTABLISH_OR_RESUME = 11,   //plmn search is aborted due to rrc connection is established or resumed
    PLMN_LIST_ABORT_NAS_ABORT = 12,             //plmn search is aborted by NAS with cerrcAbortPlmnSearchReq
    PLMN_LIST_ABORT_PS_RESET                    //plmn search is aborted due to PHY triggered PS reset
}PlmnListStatus;

#if 0
typedef enum LowMidFreqStatusTag
{
	LOW_FREQ = 1,
	MID_FREQ = 2,	
}LowMidFreqStatus;
#endif

typedef enum ChannelStatusTag
{
	DETECTED = 1,
	MISSED = 2,
	NOT_ATTEMPTED = 3,
}ChannelScanStatus;

typedef enum ActStatusTag
{
    ACT_NO_SERVICE = 0,
    ACT_SUCCESS = 1,
    ACT_EMERGENCY = 2,
    ACT_FORBIDDEN_TA = 3,
    ACT_FORBIDDEN_NAT_TA = 4,
}ActStatus;

typedef enum ActFailCauseTag
{
    ACT_REQ_SUCCESS = 0,
    ACT_REQ_FAILED_NO_VALID_PLMN = 1,           //no requested PLMN in CerrcActReq
    ACT_REQ_FAILED_NO_VALID_FREQ_BAND = 2,      //no valid freq and band in CerrcActReq
    ACT_REQ_FAILED_WRONG_STATE = 3,             //CerrcActReq is triggered in incorrect RRC state, e.g. need CerrcReleaseReq first
}ActFailCause;

typedef enum CeIntegrityProtectionInfoTag
{
    INTEGRITY_CHECK_NOT_PERFORMED       = 0,
    INTEGRITY_CHECK_SUCCESSFUL          = 1,
    INTEGRITY_CHECK_UNSUCCESSFUL        = 2
}
CeIntegrityProtectionInfo;

typedef enum CEstablishStatusTag
{
    CESTABLISH_SUCCESS                               = 0,
    CESTABLISH_FAIL_TAC_HAS_CHANGED                  = 1,
    CESTABLISH_FAIL_OTHERS                           = 2,
    CESTABLISH_FAIL_WRONG_STATE                      = 3,
    CESTABLISH_FAIL_T300_EXPIRY                      = 4,
    CESTABLISH_FAIL_REJECTED_ACCESS_BARRED           = 5,  //reject by NW, RrcConnectionReject
    CESTABLISH_FAIL_ACCESS_BARRED_FOR_SIGNALLING     = 6,  //barred by access barring check, originating signalling
    CESTABLISH_FAIL_ACCESS_BARRED_FOR_CALL           = 7,  //barred by access barring check, originating calls
    CESTABLISH_FAIL_REL_BY_MM                        = 8,  //waiting for RrcConnectionSetup, but CEMM send CerrcReleaseReq/CerrcDeactReq
    CESTABLISH_FAIL_RESELECTION                      = 9,  //reselection occurs while T300 is running, 36.331, 5.3.3.5
    //3 the followed parameters are only apply for Cat1/eMTC
    CESTABLISH_FAIL_ACCESS_BARRED_EAB                = 10,  //access barring is applicable due to EAB, only apply for eMTC/Cat1
    CESTABLISH_FAIL_ACCESS_BARRED_ACDC               = 11,  //access barring is applicable due to ACDC, only apply for eMTC/Cat1
}
CEstablishStatus;

typedef enum CResumeStatusTag
{
    CRESUME_SUCCESS                                 = 0,
    CRESUME_SUCCESS_RRCSETUP_SUCCESS                = 1,
    CRESUME_FAIL_TAC_HAS_CHANGED                    = 2,
    CRESUME_FAIL_OTHERS                             = 3,
    CRESUME_FAIL_WRONG_STATE                        = 4,
    CRESUME_FAIL_T300_EXPIRY                        = 5,
    CRESUME_FAIL_REJECTED_ACCESS_BARRED             = 6,   //reject by NW, RrcConnectionReject
    CRESUME_FAIL_ACCESS_BARRED_FOR_SIGNALLING       = 7,   //barred by access barring check, originating signalling
    CRESUME_FAIL_ACCESS_BARRED_FOR_CALL             = 8,   //barred by access barring check, originating calls
    CRESUME_FAIL_REL_BY_MM                          = 9,   //waiting for RrcConnectionResume/RrcConnectionSetup, but CEMM send CerrcReleaseReq/CerrcDeactReq
    CRESUME_FAIL_RESELECTION                        = 10,  //reselection occurs while T300 is running, 36.331, 5.3.3.5
    //3 the followed parameters are only apply for Cat1/eMTC
    CRESUME_FAIL_ACCESS_BARRED_EAB                  = 11,  //access barring is applicable due to EAB, only apply for eMTC/Cat1
    CRESUME_FAIL_ACCESS_BARRED_ACDC                 = 12,  //access barring is applicable due to ACDC, only apply for eMTC/Cat1
}
CResumeStatus;

typedef enum CerrcReleaseCauseTag
{
    REL_CAUSE_LOAD_BALANCING_TAU_REQUIRED = 0,
    REL_CAUSE_CONNECTION_FAILURE          = 1,
    REL_CAUSE_SUSPEND                     = 2,  //Only used in CerrcReleaseInd
    REL_CAUSE_OTHERS                      = 3
}
CerrcReleaseCause;

typedef enum DrbSetupStatusTag
{
    DRB_SETUP_SUCCESS                   = 0,
    DRB_SETUP_FAIL                      = 1
}
DrbSetupStatus;

typedef enum PageInfoTypeTag
{
    PAGED_BY_STMSI,
    PAGED_BY_IMSI
}
PageInfoType;

typedef enum CnDomainTag
{
    CN_DOMAIN_PS,
    CN_DOMAIN_CS,
    CN_DOMAIN_INVALID,
}
CnDomain;

/******************************************************************************
 * EMM,RRC statistic info report, Engineering Mode:AT+ECEVENTSTATIS=<mode>
******************************************************************************/
typedef enum CcmEventStatisReqType_Enum
{
    CCM_DEV_EVENT_START_STATIS,   //each EMM,RRC layer start statistic count
    CCM_DEV_EVENT_STOP_STATIS,    //stop each layer statis info
    CCM_DEV_EVENT_GET_STATIS,    //get each layer statis info
    CCM_DEV_EVENT_CLEAR_STATIS,
}CcmEventStatisReqType;


/*********************************************************************************
* Structs
*********************************************************************************/
/********************************************************************************
* RRC->MM
*********************************************************************************/
typedef struct CerrcAsCapabilityIndTag
{
    //bit31 is left most
    //bit0,1,2...31 of supportedBandMask[0] represents band1,2,3...32
    //bit0,1,2...31 of supportedBandMask[1] represents band33,34,35...64
    //bit0,1,2...31 of supportedBandMask[2] represents band65,66,67...96
    UINT32                          supportedBandMask[MAX_BAND_MASK_NUM];
}CerrcAsCapabilityInd;

typedef struct CerrcPlmnListInfoTag
{
    //Store the found Plmn-Identity
    Plmn                            Plmn;
    //Tracking Area Code, bit string of size 16
    UINT16                          tac;
    //range: 0~97, TS36.133-v13.8.0, Table 9.1.4-1
    //range:-17~97, TS36.133-v14.5.0, Table 9.1.4-1
    INT8                            nRsrp;
    //TRUE means attach without PDN connectivity as specified in TS 24.301 is supported for this PLMN
    //4 only apply for NB-IoT
    BOOL                            attachWithoutPDNConnectivity;
    //the left most bit is 31, euArfcn is bit[23:0]
    //[31:24] represents CarrierFreqOffset
    UINT32                          carrierFreq;//euArfcn;
    //PCI, 0~503
    UINT16                          phyCellId;
    //store this information for RRC, MM could ignore it
    BOOL                            isBarred;
    //store this information for RRC, MM could ignore it
    BOOL                            isPlmnRequested;
}CerrcPlmnListInfo;

typedef struct CerrcPlmnListElementTag
{
    CerrcPlmnListInfo               data;
    struct CerrcPlmnListElementTag *pNext;
}CerrcPlmnListElement;

typedef struct CerrcPlmnSearchIndTag
{
    //L1 report whether high level candicator is done or not
    //Used for PLMN search of weak signal
    BOOL                            isHighLevelDone;
    //All PLMNs found from SIB1, shoule not exceed SUPPORT_MAX_PLMN_NUM
    UINT8                           numOfPlmn;
    //The number of high quality PLMN, should not exceed numOfPlmn. See TS36.304 section 5.1.2.2
    //strong PLMN info. is put ahead of non-strong PLMN
    UINT8                           numOfStrongPlmn;
    UINT8                           reserved0;
    //use list
    CerrcPlmnListElement            *pFirstElement;
}CerrcPlmnSearchInd;

#define CERRC_MAX_BCINFO_CELL_NUM     5 //CMI_DEV_NCELL_INFO_CELL_NUM + 1
typedef struct CerrcBasicCellInfoTag
{
    //DL earfcn (anchor earfcn), range 0 - 262143
    UINT32                          earfcn;
    //Physical Cell ID, range 0 - 503
    UINT16                          phyCellId;

    //value in units of dBm, value range: -156 ~ -44
    INT16                           rsrp;
    //value in units of dB, value range: -34 ~ 25
    INT16                           rsrq;
    //value in dB, value range: -30 ~ 30
    BOOL                            snrPresent;
    INT8                            snr;

    //Store the found Plmn-Identity
    Plmn                            plmn;
    //the 28 bits Cell-Identity in SIB1, range 0 - 268435455
    UINT32                          cellId;
    //Tracking Area Code, bit string of size 16
    UINT16                          tac;

    //indicate if this is serving cell
    BOOL                            bServingCell;
    UINT8                           rsvd;
}CerrcBasicCellInfo;

typedef struct CerrcBasicCellElementInfoTag
{
    CerrcBasicCellInfo               data;
    struct CerrcBasicCellElementInfoTag *pNext;
}CerrcBasicCellInfoElement;

typedef struct CerrcPlmnSearchCnfTag
{
    //PLMN status when reporting PlmnSearchCnf
    UINT8                           status;  //PlmnListStatus
    //All PLMNs found from SIB1, shoule not exceed SUPPORT_MAX_PLMN_NUM
    UINT8                           numOfPlmn;
    //The number of high quality PLMN, should not exceed numOfPlmn. See TS36.304 section 5.1.2.2
    //strong PLMN info. is put ahead of non-strong PLMN
    UINT8                           numOfStrongPlmn;
    //The basic cell number in pBcInfoFirstElement
    UINT8                           numOfCell;
    //PLMN list
    //pFirstElement exists only when searchType is NOT 'CERRC_PLMN_SEARCH_BCINFO', and pBcInfoFirstElement is PNULL
    CerrcPlmnListElement            *pFirstElement;
    //Basic cell info list, MAX 5 cells, 1 serving cell + MAX 4 neighbor cells, in descending order of RSRP
    //pBcInfoFirstElement exists only when searchType is 'CERRC_PLMN_SEARCH_BCINFO', and pFirstElement is PNULL
    //NOTE: multi CerrcBasicCellInfo might be included for one cell
    CerrcBasicCellInfoElement       *pBcInfoFirstElement;
}CerrcPlmnSearchCnf;

typedef CerrcPlmnSearchCnf CerrcAbortPlmnSearchCnf;

//////////////////////////GTP//////////////////////////////////////
typedef struct CerrcSib1InfoGtpTag
{
   //Physical Cell ID, range 0 - 503
   UINT16						   phyCellId;

   //Store the found Plmn-Identity
   Plmn 						   plmn;
   //the 28 bits Cell-Identity in SIB1, range 0 - 268435455
   UINT32						   cellId;
   //Tracking Area Code, bit string of size 16
   UINT16						   tac;
}CerrcSib1InfoGtp;

typedef struct CerrcBasicCellInfoGtpTag
{
    //DL earfcn (anchor earfcn), range 0 - 262143
    UINT32                          earfcn;
    //Physical Cell ID, range 0 - 503
    UINT16                          phyCellId[3];

    //value in units of dBm, value range: -156 ~ -44
    INT16                           rsrp[3];
    //value in units of dB, value range: -34 ~ 25
    INT16                           rsrq[3];

	CerrcSib1InfoGtp                sib1data;

    UINT8                           cell_sib1_field[3];

	UINT8                           bServingCell;

	UINT8                           num_of_cells;
	  
}CerrcBasicCellInfoGtp;

typedef struct CerrcBasicCellElementInfoGtpTag
{
    CerrcBasicCellInfoGtp                    data;
    struct CerrcBasicCellElementInfoGtpTag *pNext;
}CerrcBasicCellInfoGtpElement;


typedef struct CerrcGtpSearchCnfTag
{ 	
    UINT8                           status;  //PlmnListStatus	
	//send new structure for GTP in plmn search cnf
   	CerrcBasicCellInfoGtpElement    *pGtpInfoFirstElement;
	
	ChannelScanStatus				ChannelStatus[8];
}CerrcGtpSearchCnf;


/////////////////////////////GTP///////////////////////////////

typedef struct CerrcActPlmnIdInfoTag
{
    //TRUE means attach without PDN connectivity as specified in TS 24.301 is supported for this PLMN
    BOOL                            attachWithoutPDNConnectivity;
    //This field indicates if the UE is allowed to resume the connection with User plane CIoT EPS Optimisation, see TS 24.301
    //Only apply for eMTC/Cat1
    BOOL                            bUpCIoTOpt;
    //This field indicates if the UE is allowed to establish the connection with Control plane CIoT EPS Optimisation, see TS 24.301
    //Only apply for eMTC/Cat1
    BOOL                            bCpCIoTOpt;
	//Indicate if this PLMN is 'reserved' for operator use, ref 36.331 5.3.1
    UINT8                           bRsvdPlmn;
    //MCC&MNC
    Plmn                            plmnIdentity;
}CerrcActPlmnIdInfo;

typedef struct CerrcActSystemInfoTag
{
    //Bit string of size 28
    UINT32                          cellIdentity;
    //the left most bit is 31, euArfcn is bit[23:0]
    //[31:24] represents CarrierFreqOffset
    UINT32                          carrierFreq;//euArfcn;
    //0~503
    UINT16                          phyCellId;
    //Tracking Area Code, bit string of size 16
    UINT16                          tac;
    //See TS36.101 section 5.5, value range: 1~256
    //now support to 255
    UINT8                           freqBandIndicator;
    //TS36.331, value range:1~6
    UINT8                           numOfPlmnIdInfo;
    UINT16                          reserved0;

    CerrcActPlmnIdInfo              plmnIdInfoList[MAX_PLMN_LIST_SIZE];

    //IDLE state DRX cycle in ms, ref to SIB2 defaultPagingCycle-r13 ENUMERATED {rf128, rf256, rf512, rf1024}
    UINT32                          idleDrxCycle;

    #if 0
    //3 the followed parameters are only apply for Cat1/eMTC
    //Indicates whether the cell supports IMS emergency bearer services for UEs in limited service mode.
    //If absent, IMS emergency call is not supported by the network in the cell for UEs in limited service mode.
    BOOL                            imsEmergencySupport;
    //Indicates whether the cell supports eCall over IMS services for UEs as defined in TS 23.401. If absent, eCall over IMS is not supported by the network in the cell.
    BOOL                            eCallOverIMSSupport;
    //Indicates if idle mode extended DRX is allowed in the cell. The UE shall stop using extended DRX in idle mode if eDRX-Allowed is not present.
    BOOL                            eDRXAllowed;
    UINT8                           reserved1;
    #endif
}CerrcActSystemInfo;

typedef struct CerrcActIndTag
{
    //report status to NAS
    UINT8                           actStatus;  //ActStatus
    //Array index of plmnIdentityInfoList in SystemInfo, range: 0~5
    //Used for shared network support
    UINT8                           selectedPlmnIndex;
    //the number of frequency in freqList, only apply for OOS
    UINT8                           numOfFreq;
    UINT8                           reserved0;

    //All system information reported to NAS, get from SIB1
    CerrcActSystemInfo              systemInfo;

    //the frequency list that ERRC has already performed cell search, only apply for OOS
    //the left most bit is 31, euArfcn is bit[23:0],[31:24] represents CarrierFreqOffset
    UINT32                          oosFreqList[SUPPORT_MAX_FREQ_NUM+1];
}CerrcActInd;

typedef struct CerrcActCnfTag
{
    //report status to NAS
    UINT8                           actStatus;  //ActStatus
    //Array index of plmnIdentityInfoList in SystemInfo, range: 0~5
    //Used for shared network support
    UINT8                           selectedPlmnIndex;
    //Inform EMM if the CerrcActReq is processed successfully
    UINT8                           actFailCause;  //ActFailCause
    UINT8                           reserved1;

    //All system information reported to NAS, get from SIB1
    CerrcActSystemInfo              systemInfo;
}CerrcActCnf;


typedef GosEmptySignal CerrcAccessBarDisableInd;

typedef struct CerrcPowerRecoverCnfTag
{
    //bit31 is left most
    //bit0,1,2...31 of supportedBandMask[0] represents band1,2,3...32
    //bit0,1,2...31 of supportedBandMask[1] represents band33,34,35...64
    //bit0,1,2...31 of supportedBandMask[2] represents band65,66,67...96
    UINT32                          supportedBandMask[MAX_BAND_MASK_NUM];

    //Array index of plmnIdentityInfoList in SystemInfo, range: 0~5
    //Used for shared network support
    UINT8                           selectedPlmnIndex;
    UINT8                           reserved0;
    UINT16                          reserved1;

    //All system information reported to NAS, get from SIB1
    CerrcActSystemInfo              systemInfo;
}CerrcPowerRecoverCnf;

/*
typedef struct CerrcCellInfoIndTag
{
    //Array index of plmnIdentityInfoList in SystemInfo, range: 0~5
    //Used for shared network support
    UINT8                       selectedPlmnIndex;
    UINT8                       reserved0;
    UINT8                       reserved1;
    UINT8                       reserved2;

    //All system information reported to NAS, get from SIB1
    CerrcActSystemInfo          systemInfo;
}CerrcCellInfoInd;
*/

//typedef GosEmptySignal CerrcDeactCnf;
typedef struct CerrcDeactCnfTag
{
    UINT8                           deactReason;  //CerrcDeactReason
    //the number of frequency in freqList
    UINT8                           numOfFreq;
    UINT8                           reserved0;
    UINT8                           reserved1;
    //the last serving cell's frequency and the inter-frequency list that got from NW configuration, such as SIB5 and measConfig(eMTC/Cat1)
    //the left most bit is 31, euArfcn is bit[23:0],[31:24] represents CarrierFreqOffset
    UINT32                          freqList[SUPPORT_MAX_FREQ_NUM+1];
}CerrcDeactCnf;

typedef struct CerrcNasMsgIndTag
{
    UINT16                          nasMsgByteLength;

    /*************************************
    * example:
    *   7   6   5   4   3   2   1   0
    * +---+---+---+---+---+---+---+---+
    * |   |   |   |   |   |   |   |   |
    * +---+---+---+---+---+---+---+---+
    *          ^
    *          |
    *          nasMsgFirstBitOffset = 2
    *************************************/
    UINT8                           nasMsgFirstBitOffset;
    UINT8                           reserved0;
    UINT8                           *pNasMsg;
    //start address of layer2 message, if there have more than one nas messages
    //this value except the last nas message is set as PNULL
    UINT8                           *pL2Msg;
}
CerrcNasMsgInd;

typedef struct CerrcNasMsgTransFailureIndTag
{
    Plmn                            plmnIdentity;   //the latest camped cell PLMN
    UINT16                          trackingAreaCode; //the latest camped cell TAC
    UINT16                          reserved0;
    //Transfer failure NAS message index, range (0..255)
    //bitmap[0] represents 31..0 |bitmap[1] represents 63..32 | ...  |bitmap[7] represents 255..224
    UINT32                          failMsgBitmap[MAX_NAS_MSG_BITMAP_NUM];
}
CerrcNasMsgTransFailureInd;

typedef struct CerrcNasMsgTransSuccIndTag
{
    //Transfer success NAS message index, range (0..255)
    //bitmap[0] represents 31..0 |bitmap[1] represents 63..32 | ...  |bitmap[7] represents 255..224
    UINT32                          succMsgBitmap[MAX_NAS_MSG_BITMAP_NUM];
}
CerrcNasMsgTransSuccInd;

typedef struct CerrcConnCnfTag
{
    UINT8                           establishStatus;  //CEstablishStatus
    BOOL                            extendedWaitTimerPresent;
    UINT16                          extendedWaitTimer;
}
CerrcConnCnf;

typedef struct CerrcResumeCnfTag
{
    //indicate whether UE still in suspend mode or not, if resume fail(signalling setup fail);
    //MM should not care this value if signalling setup success(including CRESUME_SUCCESS_RRCSETUP_SUCCESS)
    BOOL                            suspendInd;
    UINT8                           resumeStatus;  //CResumeStatus
    UINT16                          extendedWaitTimer;
    BOOL                            extendedWaitTimerPresent;
    UINT8                           reserved0;
    UINT8                           reserved1;
    UINT8                           reserved2;
}
CerrcResumeCnf;

//typedef GosEmptySignal CerrcReleaseCnf;

typedef struct CerrcReleaseIndTag
{
    UINT8                           cause;  //CerrcReleaseCause
    BOOL                            extendedWaitTimePresent;
    UINT16                          extendedWaitTime;      //Value in seconds, range(1..1800)
    BOOL                            extendedWaitTimeCpDataPresent; //be TRUE only if the extendedWaitTimePresent is FALSE; otherwise is FALSE.
    UINT16                          extendedWaitTimeCpData; //Value in seconds, range(1..1800)
    //TRUE: received RrcConnectionRelease; Normally, bNwRel is TRUE in CerrcReleaseInd
    //When bNwRel is TRUE in CerrcReleaseCnf, means RRC received RrcConnectionRelease first, then received CerrcReleaseReq during waiting for cerlcConnectReleaseAckCnf
    BOOL                            bNwRel;
}
CerrcReleaseInd;

typedef CerrcReleaseInd CerrcReleaseCnf;

typedef struct CerrcDrbInfoIndTag
{
    UINT8                           drbSetupStatus;   //DrbSetupStatus, always be SUCCESS
    UINT8                           epsBearerNum;
    UINT8                           epsBearerIdentity[NB_DRB_NUM];
}CerrcDrbInfoInd;

typedef GosEmptySignal CerrcNasSecurityKeyReq;

typedef struct CerrcPageInfoIndTag
{
    UINT8                           pageInfoType;  //PageInfoType
    UINT8                           cnDomain;      //CnDomain, only apply for eMTC/CAT1
    UINT8                           reserved1;
    UINT8                           reserved2;
}
CerrcPageInfoInd;

typedef struct CerrcCellLockCnfTag
{
    BOOL                            cellLockSuccess;
    UINT8                           reserved0;
    UINT8                           reserved1;
    UINT8                           reserved2;
}CerrcCellLockCnf;


typedef GosEmptySignal CerrcNasUlMsgSuspendInd;

typedef struct CerrcNasUlMsgResumeIndTag
{
    BOOL                            resumeResult;   //TRUE: resume success; FALSE: resume fail
    UINT8                           reserved[3];
}CerrcNasUlMsgResumeInd;


#define     BARRING_ALLEV_MT_ACCESS         (1)
#define     BARRING_ALLEV_MO_CALLS          (1<<1)
#define     BARRING_ALLEV_MO_SIGNALLING     (1<<2)
#define     BARRING_ALLEV_ACDC              (1<<3)

//only apply for Cat1/eMTC
typedef struct CerrcBarringAlleviationIndTag
{
    //the cause for barring alleviation: MT_ACCESS |MO_CALLS | MO_SIGNALLING | ACDC
    UINT8                           causeBitmap;
    UINT8                           reserved[3];
}CerrcBarringAlleviationInd;

typedef struct CerrcSmscbEtwsPrimaryDataIndTag
{
    UINT16                           messageIdentifier;
    UINT16                           serialNumber;
    UINT16                           warningType;
    UINT8                            rsvd[2];
}CerrcSmscbEtwsPrimaryDataInd;

typedef struct CerrcSmscbEtwsSecondDataIndTag
{
    UINT16                           messageIdentifier;
    UINT16                           serialNumber;
    UINT8                            dataCodingScheme;
    UINT8                            rsvd;
    UINT16                           warningMessageLength;
    UINT8                           *pWarningMessage;
}CerrcSmscbEtwsSecondDataInd;

typedef struct CerrcSmscbCmasDataIndTag
{
    UINT16                           messageIdentifier;
    UINT16                           serialNumber;
    UINT8                            dataCodingScheme;
    BOOL                             warningAreaCoordinatesPresent;
    UINT8                            rsvd[2];
    UINT16                           warningMessageLength;
    UINT16                           warningAreaCoordinatesLength;//only used when warningAreaCoordinatesPresent is TRUE
    UINT8                           *pWarningMessage;
    UINT8                           *pWarningAreaCoordinates;//only used when warningAreaCoordinatesPresent is TRUE
}CerrcSmscbCmasDataInd;

/******************************************************************************
 ******************************************************************************
 * CCM (uplayer) -> CEMM
 ******************************************************************************
******************************************************************************/

/******************************************************************************
 * CemmrRegReq
 * SIG_CEMMR_REG_REQ
 * 1> CCM send this signal to CEMM to trigger REG procedure: AUTO or MANUAL
 * 2> CEMM only check the paramters, and if allow to do register, just CNF (CemmrRegCnf)
 *    directly, don't need to wait for PLMN search/attach procedure
******************************************************************************/
typedef struct CemmrRegReqTag
{
    UINT8   nwMode;               // NwMode,  by now NB only
    UINT8   serviceType;          // UeService, EPS only
    UINT8   plmnSelectType;       // CemmPlmnSelectTypeEnum
    BOOL    bExceptEvent;         // if "Except event", CERRC need to establish connection even if it's barred

    Plmn    manualPlmn;
}CemmrRegReq;

/******************************************************************************
 * CemmrDeregReq
 * SIG_CEMMR_DEREG_REQ
 * 1> CCM send this signal to CEMM to trigger DEREG procedure: Power off or MO detach
 * 2> CEMM need to finish all DEREG prcedure, then confirm with: CemmrDeregCnf
******************************************************************************/
typedef enum CemmDetachTypeEnumTag
{
    NORMAL_MO_DETACH,
    NORMAL_MO_DETACH_WITH_SWITCH_OFF,
    SIM_REFRESH
}CemmDetachType;

typedef struct CemmrDeregReqTag
{
    UINT8       detachType;    // CemmDetachType
    UINT8       detachSrvType; // UeService,
    UINT16      reserved0;
}CemmrDeregReq;


/******************************************************************************
 * CemmManualPlmnSearchReq
 * SIG_CEMM_MANUAL_PLMN_SEARCH_REQ
 * Only used for manual PLMN search procedure
******************************************************************************/
#define CEMM_MANUAL_PLMN_SEARCH_REQ_ALL_NUM     0xFF

typedef enum CemmManualSearchMode_Enum
{
    CEMM_COPS_MANUAL_PLMN_SEARCH = 0,
    CEMM_BCINFO_MANUAL_PLMN_SEARCH
}CemmManualSearchMode;

typedef struct CemmManualPlmnSearchReq_Tag
{
    UINT8       manualMode;     //CemmManualSearchMode
    UINT8       reqMaxNum;      //how many PLMN/Cell need to report in MAX, if set to 0xFF, return all, only valid when "manualMode" == CEMM_BCINFO_MANUAL_PLMN_SEARCH
    UINT16      rsvd1;
}CemmManualPlmnSearchReq;

typedef struct CemmGtpPlmnSearchReq_Tag
{
     UINT32 arfcnList[SUPPORT_MAX_FREQ_NUM];
     UINT8  reqSib1bitmap[SUPPORT_MAX_FREQ_NUM];
     UINT8  sib1required;  
     UINT8  scanDuration;
	 UINT8     rsvd0;
	 UINT8     rsvd1;
	 

}CemmGtpPlmnSearchReq;

/******************************************************************************
 * CemmOosPlmnSelectReq
 * SIG_CEMM_OOS_PLMN_SELECT_REQ
 * Only used for oos select procedure
******************************************************************************/
typedef GosEmptySignal CemmOosPlmnSelectReq;


/******************************************************************************
 * CemmAbortPlmnSearchReq
 * SIG_CEMM_ABORT_PLMN_SEARCH_REQ
 * Only used to abort manual PLMN search procedure
******************************************************************************/
typedef GosEmptySignal CemmAbortPlmnSearchReq;

/******************************************************************************
 * CemmAbortPlmnSearchReq
 * SIG_CEMM_ABORT_GTP_PLMN_SEARCH_REQ
 * Only used to abort manual PLMN search procedure
******************************************************************************/
typedef GosEmptySignal CemmAbortGtpPlmnSearchReq;


/******************************************************************************
 * CemmPlmnSetBandFreqReq
 * SIG_CEMM_PLMN_SET_BAND_FREQ_REQ
 * Set NW mode/BAND info/freq info
******************************************************************************/
typedef enum CemmSetBandFreqTypeEnumTag
{
    SET_NW_BAND_INFO = 0,
    UNLOCK_CELL_FREQ_INFO,
    SET_PREFER_FREQ_INFO,
    LOCK_CELL_INFO,
    CLEAR_PREFER_FREQ_LIST
}CemmSetBandFreqType;

//#define SUPPORT_MAX_BAND_NUM 32
#define CMI_DEV_SUPPORT_MAX_BAND_NUM  32

typedef struct CemmPlmnSetMccBandReqTag
{
    UINT8   mccNum;
	UINT8   bandNum;
    UINT16  reserved1;
    UINT16  mcc[10];
    UINT8   orderedBand[CMI_DEV_SUPPORT_MAX_BAND_NUM];
}CemmPlmnSetMccBandReq;

typedef GosEmptySignal CemmPlmnGetMccBandReq;


//#define SUPPORT_MAX_BAND_NUM 32
typedef struct CemmPlmnSetBandInfoTag
{
    UINT8 nwMode; // NwMode current NB only
    UINT8 bandNum;
    UINT16 reserved;
    UINT8 orderedBand[SUPPORT_MAX_BAND_NUM];
}CemmPlmnSetBandInfo; // 20 bytes

typedef struct CemmPlmnSetFreqInfoTag
{
    UINT8  cellPresent;// indicate whether phyCellId present
    UINT8  arfcnNum;
    UINT16 phyCellId; // phyCell ID, 0 - 503

    UINT32 arfcnList[SUPPORT_MAX_FREQ_NUM];
}CemmPlmnSetFreqInfo; // 36 bytes

typedef struct CemmPlmnSetBandFreqReqTag
{
    UINT8   setType; //CemmSetBandFreqType
    UINT8   reserved0;
    UINT16  reserved1;
    union
    {
        CemmPlmnSetBandInfo bandInfo;
        CemmPlmnSetFreqInfo freqInfo;
    } setBandFreqInfo;
}CemmPlmnSetBandFreqReq;

/******************************************************************************
 * CemmPlmnGetBandFreqReq
 * SIG_CEMM_PLMN_GET_BAND_FREQ_REQ
 * Get BAND/FREQ info
******************************************************************************/
typedef enum CemmGetBandFreqTypeEnumTag
{
    GET_CUR_BAND_SETTING_INFO,
    GET_BAND_CAPA_INFO,
    GET_FREQ_SETTING_INFO
}CemmGetBandInfoTypeEnum;

typedef struct CemmPlmnGetBandFreqReqTag
{
    UINT8   getBandFreqType;  //CemmGetBandInfoTypeEnum
    UINT8   reserved0;
    UINT16  reserved1;
}CemmPlmnGetBandFreqReq;

/******************************************************************************
 * SIG_CEMM_CAC_SET_PARM_REQ,  //CemmCacSetParmReq
 * AT CMD set some CEMM related parameters
******************************************************************************/
// which parameters is to set
typedef enum CemmParmTypeEnumTag
{
    CEMM_REQUEST_PSM_PARM,
    CEMM_REQUEST_EDRX_PARM,
    CEMM_REQUEST_PTW_EDRX_PARM,
    CEMM_CIOT_OPT_CFG_PARM,
    CEMM_REQUEST_CIPCA_PARM,    //AT+CIPCA, Initial PDP context activation
    CEMM_REMOVE_FPLMN_PARM,     //remove FPLMN request
    CEMM_REQUEST_PLMN_SELECT_STATE_PARM,

    // ...
}CemmParmType;

/*
 * SET_PSM_PARM info
 */

typedef struct CemmSetPsmParmInfo_Tag
{
    UINT8 psmReqMode;       //CemmPsmReqModeEnum

    UINT8 reqBitmap;        /*bit 0 - T3412, bit 1 -  T3324*/

    UINT8 reqPeriodicTau;   /*T3412*/
    UINT8 reqActiveTime;    /*T3324*/
}CemmSetPsmParmInfo;

/*
 * SET_EDRX_PARM info
 */

typedef struct CemmSetEdrxParmInfo_Tag
{
    UINT8   edrxReqMode;    //CemmEdrxReqModeEnum

    BOOL    edrxValuePresent;
    BOOL    ptwValuePresent;
    /*
        *<Requested_eDRX_value>: string type; half a byte in a 4 bit format.
        * The eDRX value refers to bit 4 to 1 of octet 3 of the Extended DRX parameters information element
        * for NB, available value: 0x02 - 0x0F
        */
    UINT8   reqEdrxValue;
    /*
        *<Requested_Paging_time_window>: string type; half a byte in a 4 bit format.
        * The PTW value refers to bit 5 to 8 of octet 3 of the Extended DRX parameters information element
        * for NB, available value: 0x00 - 0x0F
        */
    UINT8   reqPtwValue;
    UINT8   reserved0;
    UINT16  reserved1;
}CemmSetEdrxParmInfo;

/*
 * CEMM_CIOT_OPT_CFG_PARM
*/

typedef struct CemmSetCiotOptCfgParmInfo_Tag
{
    BOOL    resetParm;  //reset the parameters for CIoT EPS optimization to the default values

    BOOL    ueSuptOptPresent;
    UINT8   ueSuptOptType;    //UE supported CIOT OPT type: CemmCiotOptTypeEnum: 1 & 3

    UINT8   uePreferOptPresent;
    UINT8   uePreferOpt;  // CemmCiotOptTypeEnum: 0, 1, 2

    UINT8   reserved0;
    UINT16  reserved1;
}CemmSetCiotOptCfgParmInfo;

/*
 * CEMM_REQUEST_CIPCA_PARM
*/
typedef struct CemmSetCipcaParmInfo_Tag
{
    BOOL    attachWithoutPdn;  //EPS Attach with/without PDN connection
    UINT8   reserved0;
    UINT16  reserved1;
}CemmSetCipcaParmInfo;

/*
 * CEMM_REMOVE_FPLMN_PARM
*/
typedef struct CemmRemoveFPlmnInfo_Tag
{
    BOOL    rmNvmFplmn;
    BOOL    rmSimFplmn;
    UINT16  reserved;
}CemmRemoveFPlmnInfo;

/******************************************************************************
 * SIG_CEMM_CAC_SET_PARM_REQ,  //CemmCacSetParmReq
 * AT CMD set some CEMM related parameters
******************************************************************************/
typedef struct CemmCacSetParmReqTag
{
    UINT8   parmType; //CemmParmType
    UINT8   bodyLen;
    UINT16  reserved0;

    /*
     * PSM - CemmSetPsmParmInfo
     * EDRX - CemmSetEdrxParmInfo
     * OPT_CFG - CemmSetCiotOptCfgParmInfo
     * CIPCA - CemmSetCipcaParmInfo
     * REMOVE_FPLMN
    */
    UINT8   body[];
}CemmCacSetParmReq;

typedef struct CemmSetOpConfigParmReqTag
{
    UINT8   operator;    
}CemmSetOpConfigParmReq;

/******************************************************************************
 * SIG_CEMM_CAC_GET_PARM_REQ,  //CemmCacGetParmReq
 * AT CMD to get the CEMM related parameters
******************************************************************************/
typedef struct CemmCacGetParmReqTag
{
    UINT8   parmType;     //CemmParmType
    UINT8   reserved0;
    UINT16  reserved1;
}CemmCacGetParmReq;

/******************************************************************************
 * SIG_CEMMR_POWER_SAVE_REQ,   //CemmrPowerSaveReq
 * Try to enter hibernate/sleep2 state
******************************************************************************/
typedef enum CemmPowerSaveLevelEnum
{
    CEMM_HIB_POWER_SAVE = 0,
    CEMM_SLEEP2_POWER_SAVE
}CemmPowerSaveLevel;

typedef struct CemmrPowerSaveReqTag
{
    //UINT8   powerSaveLevel; //CemmPowerSaveLevel
    LpState lowPowerState;
    UINT8   reserved0;
    UINT16  reserved1;
}CemmrPowerSaveReq;

/******************************************************************************
 * SIG_CEMMR_POWER_RECOVER_REQ,   //CemmrPowerRecoverReq
 * Wake up from hibernate state
******************************************************************************/
typedef GosEmptySignal CemmrPowerRecoverReq;


/******************************************************************************
 * SIG_CEMM_CCM_SET_PARM_REQ
 *  Set some MM parameters from CCM
******************************************************************************/
typedef enum CcmParmType_enum
{
    CCM_EMM_CAPA_PRAM,
    CCM_PLMN_REG_TYPE_PRAM,
    CCM_PS_TEST_PRAM,
    CCM_PS_SLEEP_CFG_PRAM

    //...
}CcmParmType;

typedef struct CcmSetEmmCapaParm_Tag
{
    BOOL    supportSmsPresent;
    BOOL    supportSms;
    BOOL    tauForSmsPresent;
    BOOL    tauForSms;                  //whether need to trigger TAU if NW not support SMS

    BOOL    plmnSearchPowerLevelPresent;
    UINT8   plmnSearchPowerLevel;       //PlmnSearchPowerLevel
    BOOL    epcoPst;                    //whether "enableEpco" present
    BOOL    enableEpco;                 //whether enable EPCO

    BOOL    dnsIpAddrReadCfgPresent;
    UINT8   dnsIpType;
    UINT8   enableDnsIpAddrRead;
    BOOL    t3324ValuePresent;

    UINT32  t3324ValueS;
    BOOL    overrideLrplmnsiPresent;
    BOOL    overrideLrplmnsi;

    BOOL    bEnableHPPlmnSearchPresent;
    UINT8   bEnableHPPlmnSearch;
}CcmSetEmmCapaParm;

typedef struct CcmSetPlmnRegTypeParm_Tag
{
    UINT8   plmnSelectType; // CemmPlmnSelectTypeEnum
    UINT8   reserved0;
    UINT16  reserved1;

    Plmn    manualPlmn; //if "CEMM_MANUAL_PLMN_REG"/"CEMM_MANUAL_THEN_AUTO_PLMN_REG"
}CcmSetPlmnRegTypeParm;

typedef struct CcmSetPsTestParm_Tag
{
    BOOL    psTestPresent;
    BOOL    psTest;
    UINT16  reserved0;
}CcmSetPsTestParm;

typedef struct CcmSetPsSleepCfgParm_Tag
{
    BOOL    t3324Present;
    BOOL    t3412Present;
    BOOL    edrxPresent;
    UINT8   rsvd;
    UINT16  minT3324ValueS;
    UINT16  minEdrxPeriodS;
    UINT32  minT3412ValueS;
}CcmSetPsSleepCfgParm;

typedef struct CemmCcmSetParmReqTag
{
    UINT8   ccmParmType; //CcmParmType
    UINT8   bodyLen;
    UINT16  reserved0;

    /*
     * CCM_EMM_CAPA_PRAM
     * CCM_PLMN_REG_TYPE_PRAM
     * CCM_PS_TEST_PRAM
     * CCM_PS_SLEEP_CFG_PRAM
    */
    UINT8   body[];
}CemmCcmSetParmReq;

/******************************************************************************
 * SIG_CEMM_CCM_GET_PARM_REQ
 *  GET some parameters from CEMM
******************************************************************************/
typedef struct CemmCcmGetParmReq_Tag
{
    UINT8   ccmParmType; //CcmParmType
    UINT8   reserved0;
    UINT16  reserved1;
}CemmCcmGetParmReq;

/******************************************************************************
 * SIG_CEMM_CCM_GET_EMM_STATUS_REQ
 *  GET EMM status from CEMM
******************************************************************************/
typedef GosEmptySignal CemmCcmGetEmmStatusReq;

/******************************************************************************
 * SIG_CEMM_CCM_GET_EMM_STATUS_REQ
 *  GET EMM status from CEMM
******************************************************************************/
typedef struct CemmCcmSetLapiReq_Tag
{
   UINT8 lapi;
}CemmCcmSetLapiReq;

/******************************************************************************
 * SIG_CEMM_CCM_GET_LAPI_REQ
 *  GET LAPI Info
******************************************************************************/
typedef GosEmptySignal CemmCcmGetLapiReq;

/******************************************************************************
 * SIG_CCM_CESS_LPP_UNIT_DATA_REQ
 *  Send LPP Data to NW by CESS
******************************************************************************/
typedef struct CcmCessLppUnitDataReq_Tag
{
    UINT16       length;
    BOOL         nasRoutingIdPresent;
    UINT8        reserved;
    UINT32       nasRoutingId;   /*IE type octet string(size(4))*/
    UINT8        *pdata;
}CcmCessLppUnitDataReq;

/******************************************************************************
 * SIG_CEMM_CCM_DEV_LOC_MEAS_STATE_IND
 *  Deliver DEV module loc meas state to CEMM, CEMM will decide to enter PSM state
 *  or not based on the setting
******************************************************************************/
typedef struct CemmCcmDevLocMeasStateInd_Tag
{
    BOOL         isMeasing;
    UINT8        reserved1;
    UINT16       reserved2;
}CemmCcmDevLocMeasStateInd;

/******************************************************************************
 * SIG_CCM_CESS_LCS_UNIT_DATA_REQ
 *  Send LCS Data to NW by CESS
******************************************************************************/
typedef enum LcsMessageTag
{
    LCS_MESSAGE_MOLR,
    LCS_MESSAGE_LOCATION_NOTIFICATION,
    LCS_MESSAGE_LOCATION_RESULT,
}LcsMessage;

typedef struct CcmCessLcsUnitDataReq_Tag
{
    UINT8   lcsMessage; //LcsMessage
    UINT16  bodyLen;
    UINT8   reserved0;

    /*
     * molr - SsLcsMolrData
     * notification result - LcsLocationNotificationResponse
    */
    UINT8   body[];
}CcmCessLcsUnitDataReq;

/******************************************************************************
 * SIG_CCM_CESS_GET_CMTLRA_REQ,   //CcmCessCmtlraReq
 * AT+CMTLRA?
******************************************************************************/
typedef GosEmptySignal CcmCessCmtlraReq;


/******************************************************************************
 ******************************************************************************
 * USIM -> CEMM
 ******************************************************************************
******************************************************************************/

typedef struct UiccPlmn_Tag
{
    BOOL                    plmnValid;
    UINT8                   reserved0;
    AccessTechnologyId      accessTechnology;       /* Access Technology, if no act, set to 0*/

    Plmn                    plmn;
}UiccPlmn;

#define UICC_PLMN_TRUNCATED_NUM    8   //Truncated
typedef struct UiccPlmnList_Tag
{
    UiccPlmn                uiccPlmn[UICC_PLMN_TRUNCATED_NUM]; /* read at most plmn entries every read request */
}UiccPlmnList;

typedef enum CemmSimRequestStatusTag
{
    CEMM_SIM_REQ_OK,                      /* Valid request */
    CEMM_SIM_REQ_FAIL,                    /* request result failed */
    CEMM_SIM_INVALID_MAC,                 /* Invalid MAC */
    CEMM_SIM_SYNC_FAILURE,                /* Synchronisation failure */
    CEMM_SIM_ACCESS_DENIED,               /* Authentication failed */
    CEMM_SIM_NOT_UPDATED,                 /* Uicc could not be updated */
    CEMM_SIM_SERVICE_UNAVAIL,             /* Service unavailable */
    CEMM_SIM_UNKNOWN_ERROR                /* Other error */
}CemmSimRequestStatus;

typedef enum CemmSimReqItemTag
{
    CEMM_REQ_RW_EPSLOCI,    /* Eps location information */
    CEMM_REQ_RW_EPSNSC,     /* Eps NAS security context */
    CEMM_REQ_R_FPLMN,       /* forbidden plmn */
    CEMM_REQ_R_UPLMN,       /* user plmn with access technology */
    CEMM_REQ_R_HPLMN,       /* EFHPLMNwAcT (HPLMN selector with Access Technology) */
    CEMM_REQ_R_OPLMN,       /* operator plmn with access technology */
    CEMM_REQ_R_EHPLMN,      /* equivalent plmn with access technology */
    CEMM_REQ_ADD_FPLMN,     /* Add FPLMN into UICC */
    CEMM_REQ_DEL_FPLMN,
    CEMM_REQ_R_HPPLMN,
    CEMM_REQ_UNKOWN = 0xFF
}CemmSimReqItem;        /* request item determined to the uicc file Id */

/******************************************************************************
 * NAS Signalling Priority
******************************************************************************/
typedef enum NasSignallingPriority_Tag
{
    NAS_SIGNALLING_RESERVED1    = 0,    /* Reserved(0) */
    NAS_SIGNALLING_LOW_PRIORITY = 1,    /* NAS signalling low priority */
    NAS_SIGNALLING_RESERVED2    = 2     /* Reserved(2-255) */
}NasSignallingPriority;

typedef struct NasConfig_Tag
{
    UINT8                   nasSignallingPriority;  /* NasSignallingPriority */
    UINT8                   minPeriodicSearchTimer; /* value in minutes */
    BOOL                    extendedAccessBarring;
    BOOL                    t3245Behaviour;
    BOOL                    overrideNasSignallingLowPriority;
    BOOL                    overrideExtendedAccessBarring;
    BOOL                    fastFirstHigherPriorityPlmnSearch;
    UINT8                   smRetryWaitTime;
    BOOL                    dcnIdPresent;
    UINT16                  defaultDcnId;
    BOOL                    exceptionDataReportingAllowed;
}NasConfig;

/******************************************************************************
 * Globally Unique Temporary Identifier
******************************************************************************/
#define MAX_GUTI_SIZE     10

/******************************************************************************
 * EPS location information
******************************************************************************/
typedef struct EpsLocationInfo_Tag
{
    //Guti                    guti;
    UINT8       gutiContents[MAX_GUTI_SIZE];
    UINT8       epsUpdateStatus; //EpsUpdateStatus
    UINT8       reserved0;

    Tai         tai;
}EpsLocationInfo;

/******************************************************************************
 * EPS NAS security context
******************************************************************************/
typedef struct EpsNscInfo_Tag
{
    UINT8           asmeKsi;        /* KSIasme, if invalid, set to NO_KEY_IS_AVAILABLE :0x07 */
    UINT8           algorithmId;
    UINT16          reserved;

    AsmeKey         asmeKey;        /* Kasme */
    NasCount        ulNasCount;
    NasCount        dlNasCount;
}EpsNscInfo;

typedef enum EPSFilePresentType_Tag
{
    EPS_FILE_NOT_PRESENT = 0,
    EPS_LOCI_PRESENT     = 1,
    EPS_NSC_PRESENT      = 2,
    EPS_LOCI_NSC_PRESENT = 3
}EPSFilePresentType;

/*
 * SIGID: SIG_CEMM_SIM_APP_READY_IND
*/
typedef struct CemmSimAppReadyIndTag
{
    Imsi                imsi;   // EF_IMSI & EF_HPLMNNWAct & EF_AD

    AccessClass         accessClass;        //UINT16
    UINT16              hpPlmnSearchPeriod; /* units of minutes (0 - 240*60), default value is 72*60 minutes */

    /*
     * EHPLMN info & FPLMN info
    */
    UINT16              totalNumEhplmn; //if no EF_EHPLMN, this number set to 0
    UINT16              totalNumFplmns;
    UiccPlmnList        ehplmn;         /* EF_EHPLMN & EF_HPLMNNWAct */
    UiccPlmnList        forbiddenPlmn;  /* list of forbidden PLMNs */

    /*
     * EPS LOC and SECURITY info
    */
    UINT8               epsFilePresent; /* EPSFilePresentType */
    BOOL                epsLociInfoValid;
    BOOL                epsNscInfoValid;
    BOOL                attemptHplmn;   /* EF_LRPLMNSI*/

    EpsLocationInfo     epsLocationInfo;
    EpsNscInfo          epsNscInfo;     /* Eps NAS security context information */
    NasConfig           nasConfig;
	UiccPlmn            actingHplmn;    /* HPLMN considered if EF HPLMN consider valid PLMN */
}CemmSimAppReadyInd;


/*
 * Read the specific PLMN info stored in UICC card
 * When "reqItem" is "CEMM_REQ_FPLMN/CEMM_REQ_UPLMN/CEMM_REQ_HPLMN/CEMM_REQ_OPLMN/CEMM_REQ_EHPLMN"
*/
typedef struct SimPlmnRspDataTag
{
    /*
     * As the limited size of signal structure, only "PLMN_LIST_SIZE(8)" PLMN info could be carried in one signal
     * here, if one specific PLMN number in UICC > "PLMN_LIST_SIZE", then should carry these PLMNs in several signals
     * example: "totalEntries" = 10;
     *  first signal: startField = 0, totalEntries = 10
     *  second signal:  startField = 8, totalEntries = 10
    */
    UINT16          startField;
    UINT16          totalEntries;   /* total entries of plmn*/
    UiccPlmnList    plmnList;
}SimPlmnRspData;

/*
 * SIGID: SIG_CEMM_SIM_READ_DATA_CNF
*/
typedef struct CemmSimReadDataCnfTag
{
    UINT8   requestStatus;  /*CemmSimRequestStatus, return status*/
    UINT8   reqItem;        /*CemmSimReqItem request item determined to the uicc file Id */
    UINT16  reserved0;
    UINT8   respData[];     /* response data read from uicc, e.g. (PlmnRspData *)respData used for PLMN data after read from UICC */
}CemmSimReadDataCnf;

/*
 * SIGID: SIG_CEMM_SIM_WRITE_DATA_CNF
*/
typedef struct CemmSimWriteDataCnfTag
{
    UINT8   requestStatus;  /*CemmSimRequestStatus */
    UINT8   reqItem;        /*CemmSimReqItem, request item determined to the uicc file Id */
    UINT16  reserved0;
}CemmSimWriteDataCnf;

/*
 * UICC AUTH INFO
*/
/******************************************************************************
 * Authentication response value
******************************************************************************/
#define RES_SIZE 16
typedef struct AuthResTag
{
    UINT8   length;
    UINT8   reserved0;
    UINT16  reserved1;
    UINT8   data[RES_SIZE];
}AuthRes;

/******************************************************************************
 * Authentication re-synchronization token AUTS
******************************************************************************/
#define AUTS_SIZE 16
typedef struct AutsTag
{
    UINT8   length;
    UINT8   reserved0;
    UINT16  reserved1;
    UINT8   data[AUTS_SIZE];
}Auts;

typedef struct CkIkContentTag
{
    UINT8           ksi;  //NasKsi
    UINT8           ikLen;
    UINT8           ckLen;
    UINT8           reserved1;
    UINT8           ik[IK_SIZE];
    UINT8           ck[CK_SIZE];
}CkIkContent;

typedef struct HpPlmnSearchPeriodTag
{
    UINT16          period;/* units of minutes (0 - 240*60), default value is 72*60 minutes */
    UINT16          reserved;
}
HpPlmnSearchPeriod;

/*
 * SIGID: SIG_CEMM_SIM_AUTHENTICATE_CNF
*/
typedef struct CemmsimAuthenticateCnfTag
{
    UINT8       requestStatus;  /* CemmSimRequestStatus */
    UINT8       reserved0;
    UINT16      reserved1;

    AuthRes     res;
    CkIkContent keys;
    Auts        auts;
}CemmSimAuthenticateCnf;

/*
 * SIGID: SIG_CEMM_SIM_USAT_REFRESH_IND
*/
typedef struct CemmSimUsatRefreshIndTag
{
    UINT32                  cmdDetailsRef;
    UINT8                   refreshType;//UsatRefreshType
    UINT16                  reserved;
    UINT8                   numOfOplmn;
    //UINT8                   numOfFileItem;
    UiccPlmnList            oplmnList;
    //UINT8                   fileItem[8];//CemmSimReqItem
}
CemmSimUsatRefreshInd;

/*
 * SIGID: SIG_CEMM_SIM_USAT_IMEI_SV_REQ
*/
typedef struct CemmSimUsatImeiSVReqTag
{
    UINT32                  cmdDetailsRef;
    UINT8                   idType;//IdType
    UINT8                   reserved1;
    UINT16                  reserved2;
}
CemmSimUsatImeiSVReq;


/*
 * SIGID: SIG_CEMM_SIM_USAT_REFRESH_FCN_IND
 * Refresh with file change notification
*/
typedef struct CemmSimUsatRefreshFcnIndTag
{
    UINT8               reqItem;    /*CemmSimReqItem, request item determined to the uicc file Id */
    UINT8               reserved1;
    UINT16              reserved2;
    UINT8               ItemData[]; /* file data read from uicc, e.g. (HpPlmnSearchPeriod *)ItemData used for HPPPLMN data after read from UICC */
}
CemmSimUsatRefreshFcnInd;


/*
 * SIG_CCM_GET_NAS_STATUS_REQ
*/
typedef GosEmptySignal      CcmGetNasStatusReq;

/******************************************************************************
 ******************************************************************************
 * CCM SMS -> CESMS
 ******************************************************************************
******************************************************************************/

#define     SMS_MAX_CMD_LEN                     157
#define     MAX_SMS_TIMESTAMP_LEN             14

typedef struct SmsMsg_Tag
{
    UINT8           len;
    UINT8           reserved0;
    UINT16          reserved1;
    UINT8          *data;
}SmsMsg;


typedef struct CemmSmsSendMessageReq_Tag
{
   UINT8                            smsId;
   UINT8                            msgRef;
   BOOL                             replyPath;
   UINT8                            msgLen;
   UINT8                           *msgData;
   MsgAddress                       smeAddr;
   MsgAddress                       scAddr;
   SmsProtocolId                    protocolId;
   SmsDataCoding                    smsDataCodingScheme;
   UINT8                            validityPeriodFormat;  //VpFormat
   UINT8                            validityPeriodAsValue;
   UINT8                            validityPeriodAsTime[MAX_SMS_TIMESTAMP_LEN];
   BOOL                             rejectDuplicates;
   BOOL                             userDataHeaderPresent;
   BOOL                             statusReportReq;
   BOOL                             concatSmsPresent;
   UINT16                           concatSmsRefNum;
   UINT8                            concatSmsSeqNum;
   UINT8                            concatSmsLen;
}CemmSmsSendMessageReq;

typedef struct CemmSmsConfigReq_Tag
{
   BOOL                            moreMsgToSend;
   BOOL                            readyState;
   UINT16                          reserved0;
}CemmSmsConfigReq;

typedef struct CemmSmsDeliverReportReq_Tag
{
    UINT8                            smsId;
    UINT8                            tpCause;  //TpCause
    UINT8                            stReport;  //SmsStatusOfReport
    BOOL                             smsProtocolIdPresent;
    BOOL                             smsDataCodingSchemePresent;
    UINT8                            usrDataLen;
    UINT16                           reserved0;
    UINT8                           *usrData;
    SmsProtocolId                    smsProtocolId;
    SmsDataCoding                    smsDataCoding;
}CemmSmsDeliverReportReq;

typedef struct CemmSmsSendRpReportReq_Tag
{
    UINT8                            smsId;
    UINT8                            tpCause;  //TpCause
    UINT8                            stReport;  //SmsStatusOfReport
}CemmSmsSendRpReportReq;

typedef enum SmsCommand_Tag
{
    SMS_CMD_ENQUIRY              =   0,
    SMS_CMD_CANCEL,
    SMS_CMD_DELETE,
    SMS_CMD_ENABLE_SRR
}SmsCommand;

typedef struct CemmSmsCommandReq_Tag
{
   UINT8                                smsId;
   UINT8                                msgRef;
   UINT8                                msgNum;
   UINT8                                cmdDataLen;
   MsgAddress                           scAddr;
   SmsProtocolId                        smsProtocolId;
   SmsCommand                           commandType;
   UINT8                                cmdData[SMS_MAX_CMD_LEN];
   BOOL                                 statusReportReq;
   UINT16                               reserved0;
   MsgAddress                           smeAddr;
}CemmSmsCommandReq;


/******************************************************************************
 ******************************************************************************
 * DR -> CESMS
 ******************************************************************************
******************************************************************************/
/*
 * DR -> CESMS
 * SIGID: SIG_CEDR_SMS_TEST_LOOP_UL_DATA_TRANS_REQ
*/
typedef struct DrSmsDataPdu_Tag
{
    UINT16      length;
    UINT16      reserved1;

    UINT8       *ptr;
    struct DrSmsDataPdu_Tag *pNext;
}DrSmsDataPdu;

typedef struct CeDrSmsTestLoopUlDataTransReq_Tag
{
    DrSmsDataPdu     *pPendingHdr;
    DrSmsDataPdu     *pPendingTailer;
}CeDrSmsTestLoopUlDataTransReq;


/******************************************************************************
 ******************************************************************************
 * DR -> CEMM
 ******************************************************************************
******************************************************************************/

/*
 * DR -> CEMM, trigger CEMM to establish the DRB
 * SIGID: SIG_CEMM_DR_REESTABLISH_REQ
*/
typedef struct CemmDrReestablishReq_Tag
{
    BOOL    bExceptData;
    UINT8   reserved0;
    UINT16  reserved1;
}CemmDrReestablishReq;


/******************************************************************************
 ******************************************************************************
 * CCM/DR -> CESM
 ******************************************************************************
******************************************************************************/
#define INVALID_CID_VALUE    0xFF

#if 0   //move to "DataRelAssistIndEnum"
//Release assistance ind
typedef enum CesmRelAssistIndEnum_Tag
{
    CESM_RAI_NO_INFO = 0,
    CESM_RAI_NO_UL_DL_FOLLOWED = 1,
    CESM_RAI_ONLY_DL_FOLLOWED = 2,
    CESM_RAI_RESERVED = 3
}CesmRelAssistIndEnum;
#endif

/*
* CCM -> CESM, set EPS bearer context
* SIGID: SIG_CCM_CESM_SET_EPS_BEARER_CTX_REQ
*/
typedef struct CcmCesmSetEpsBearerCtxReq_Tag
{
    DefineBearerCtxInfo          bearerCtxInfo;
}
CcmCesmSetEpsBearerCtxReq;

/*
 * CCM -> CESM, get EPS bearer context
 * SIGID: SIG_CCM_CESM_GET_EPS_BEARER_CTX_REQ
*/
typedef struct CcmCesmGetEpsBearerCtxReq_Tag
{
    UINT8       reqCid;
    BOOL        bReqAll;    /* whether request all bearers info */
    UINT16      reqCmiId;   /* which PS CMI ID */

    BOOL        bGetTft;    /* whether activated/configed TFT need to return*/
    BOOL        bGetReqTft; /* whether requested/defined TFT need to return, AT+CGTFT?*/
    BOOL        bGetReqEpsQos;  /* whether requested/defined EPS QOS need to return, AT+CGEQOS*/
    BOOL        bGetDynEpsQos;  /* whether activated/configed TFT need to return*/
    BOOL        bGetApnRc;    /* whether apnRc need to return*/
    BOOL        bGetPapAuth;  /*whether pap auth need to return*/
}CcmCesmGetEpsBearerCtxReq;


/*
 * CCM -> CESM, del EPS bearer context
* SIGID: SIG_CCM_CESM_DEL_EPS_BEARER_CTX_REQ
*/
typedef struct CcmCesmDelEpsBearerCtxReq_Tag
{
    UINT8               cid;
    UINT8               reserved1;
    UINT16              reservd2;
}
CcmCesmDelEpsBearerCtxReq;


/*
* CCM -> CESM, activate EPS bearer context reqeust
* SIGID: SIG_CCM_CESM_ACT_EPS_BEARER_CTX_REQ
*/
typedef struct CcmCesmActEpsBearerCtxReq_Tag
{
    UINT8               cid;
    UINT8               reserved1;
    UINT16              reservd2;
}
CcmCesmActEpsBearerCtxReq;

/*
* CCM -> CESM, deactive EPS bearer context reqeust
* SIGID: SIG_CCM_CESM_DEACT_EPS_BEARER_CTX_REQ
*/
typedef struct CcmCesmDeactEpsBearerCtxReq_Tag
{
    UINT8               cid;
    UINT16              cause;//EsmCause
    BOOL 				is_rs_fail;
    UINT16              reservd;
}
CcmCesmDeactEpsBearerCtxReq;

/*
* CCM -> CESM, activate EPS bearer context reqeust
* SIGID: SIG_CCM_CESM_MOD_EPS_BEARER_CTX_REQ
*/
typedef struct CcmCesmModifyEpsBearerCtxReq_Tag
{
    UINT8               cid;
    UINT8               reserved1;
    UINT16              reservd2;
}
CcmCesmModifyEpsBearerCtxReq;

#if 0
/*
 * CCM -> CESM, read bearer context dynamic parameter
 * SIGID: SIG_CCM_CESM_READ_BEARER_CTX_DYN_PARAM_REQ
*/
typedef struct CcmCesmReadBearerCtxDynParamReq_Tag
{
    UINT8               cid;
    UINT8               reserved1;
    UINT16              reservd2;
}
CcmCesmReadBearerCtxDynParamReq;
#endif

#if 0
/*
* CCM -> CESM, read bearer context dynamic parameter
* SIGID: SIG_CCM_CESM_GET_DEFINED_CID_IPADDR_PARAM_REQ
*/
typedef struct CcmCesmGetDefinedCidIpAddrParamReq_Tag
{
    UINT8               cid;
    UINT8               reserved1;
    UINT16              reservd2;
}
CcmCesmGetDefinedCidIpAddrParamReq;
#endif

#if 0
/*
* CCM -> CESM, get APNRC REQ
* SIGID: SIG_CCM_CESM_GET_APN_RATE_CTRL_REQ
*/
typedef struct CcmCesmGetAPNRateCtrlReq_Tag
{
    UINT8               cid;
    UINT8               reserved1;
    UINT16              reservd2;
}
CcmCesmGetAPNRateCtrlReq;
#endif

/*
* CCM -> CESM, Set dedicate bearer context req
* SIGID: SIG_CCM_CESM_SET_DEDICATE_EPS_BEARER_CTX_REQ
*/
typedef struct CcmCesmSetDedEpsBearerCtxReq_Tag
{
    UINT8               cid;
    UINT8               pCid;
    BOOL                imcnPresent;
    UINT8               imcnFlag;
}
CcmCesmSetDedEpsBearerCtxReq;

/*
* CCM -> CESM, del dedicate bearer context req
* SIGID: SIG_CCM_CESM_DEL_DED_EPS_BEARER_CTX_REQ
*/

typedef struct CcmCesmDelDedEpsBearerCtxReq_Tag
{
    UINT8               cid;
    UINT8               reserved1;
    UINT16              reservd2;
}
CcmCesmDelDedEpsBearerCtxReq;

/*
* CCM -> CESM, set Define TFT
* SIGID: SIG_CCM_CESM_SET_DEFINE_TFT_PARAM_REQ
*/

typedef struct CcmCesmSetDefineTFTParamReq_Tag
{
    CmiPsTftFilter  TFTFilter;
}
CcmCesmSetDefineTFTParamReq;

/*
* CCM -> CESM, del TFT
* SIGID: SIG_CCM_CESM_DELETE_TFT_PARAM_REQ
*/
typedef struct CcmCesmDelTFTParamReq_Tag
{
    UINT8               cid;
}
CcmCesmDelTFTParamReq;

#if 0
/*
 * CCM -> CESM, get TFT
 * SIGID: SIG_CCM_CESM_GET_DEFINE_TFT_PARAM_REQ
*/

typedef struct CcmCesmGetDefineTFTParamReq_Tag
{
    UINT8               cid;
}CcmCesmGetDefineTFTParamReq;
#endif

/*
* CCM -> CESM, set Define qos
* SIGID: SIG_CCM_CESM_SET_DEFINE_EPS_QOS_REQ
*/

typedef struct CcmCesmSetDefineEpsQosReq_Tag
{
    CmiPsEpsQosParams EpsQosParam;
}
CcmCesmSetDefineEpsQosReq;

/*
* CCM -> CESM, del Qos
* SIGID: SIG_CCM_CESM_DELETE_EPS_QOS_REQ
*/
typedef struct CcmCesmDelEpsQosReq_Tag
{
    UINT8               cid;
}
CcmCesmDelEpsQosReq;

#if 0
/*
* CCM -> CESM, get QOS
* SIGID: SIG_CCM_CESM_GET_DEFINED_EPS_QOS_REQ
*/

typedef CacCmiEmptySig CcmCesmGetDefineEpsQosReq;
#endif

#if 0
/*
* CCM -> CESM, Send Data
* SIGID: SIG_CCM_CESM_SEND_DATA_VER_CP_REQ
*/

typedef struct CcmCesmSendDataVerCPReq_Tag
{
    OriDataPacketParam  dataParam;
}CcmCesmSendDataVerCPReq;
#endif

/*
* CCM -> CESM, attached bearer preset
* SIGID: SIG_CCM_CESM_ATTACHED_BEARER_CTX_PRESET_REQ
*/
typedef struct CcmCesmAttBearCtxPresetReq_Tag
{
    AttachedBearCtxPreSetParam  presetParam;
}CcmCesmAttBearCtxPresetReq;

/*
* CCM -> CESM, get attached bearer
* SIGID: SIG_CCM_CESM_GET_ATTACH_BEARER_CTX_REQ
*/

typedef CacCmiEmptySig CcmCesmGetAttBearCtxReq;


/*
* CCM -> CESM, set cpdata report cfg
* SIGID: SIG_CCM_CESM_SET_MT_CP_DATA_REPORT_CFG_REQ
*/
typedef struct CcmCesmSetMtCpDataReportCfgReq_Tag
{
    UINT16 reporting;
}CcmCesmSetMtCpDataReportCfgReq;

/*
* CCM -> CESM, get cpdata report cfg
* SIGID: SIG_CCM_CESM_GET_MT_CP_DATA_REPORT_CFG_REQ
*/
typedef CacCmiEmptySig CcmCesmGetMtCpDataReportCfgReq;

/*
 * CCM -> CESM
 * SIG_CCM_CESM_GET_ALL_BEARERS_BASIC_INFO_REQ
*/
typedef struct CcmCesmGetAllBearersBasicInfoReq_Tag
{
    UINT8   reqCmdId;   /* which AT CMD (request) need UE all bearers info*/
    UINT8   reserved0;
    UINT16  reserved1;
}CcmCesmGetAllBearersBasicInfoReq;


/*
 * DR -> CESM, UL data via CP
 * SIGID: SIG_CESM_UL_DATA_TRANS_REQ
*/
typedef struct CesmUlDataTransReq_Tag
{
    UINT8       epsId;

    /*
     * Note: "bExceptData" & "esmRai" just move to "UlPduInfo", and set by APP, not by ESM
    */
    //BOOL    bExceptData;    /* need to pass to CEMM/CERRC, if "Except Data", CERRC need to establish connection even if it's barred */
    //UINT8   esmRai;         /* DataRelAssistIndEnum, release assistance indication */
    UINT8       reserved0;
    UINT16      reserved1;

    UlPduInfo   *pHdr;      /*this memory use dynamic memory*/
    UlPduInfo   *pTailer;
}CesmUlDataTransReq;



/*
 * CCM -> CESM, SET DEFINE AUTH IN PCO
 * SIGID: SIG_CCM_CESM_SET_DEFINE_AUTH_CTX_REQ
*/
typedef struct CcmCesmSetDefineAuthReq_Tag
{
    UINT8       cid;
    UINT8       proto;
    UINT8       userIdLength;
    UINT8       userId[CMI_PS_MAX_AUTH_STR_LEN];
    UINT8       passwordLength;
    UINT8       password[CMI_PS_MAX_AUTH_STR_LEN];
}CcmCesmSetDefineAuthReq;

/******************************************************************************
 * SIG_CCM_EMM_EVENT_STATIS_REQ
 *  CCM let EMM to start/stop/get statistic info
******************************************************************************/
typedef struct CcmEmmEventStatisOperReq_Tag
{
    UINT8       statisReqType;  //CcmEventStatisReqType
    UINT8       rsvd0;
    UINT16      rsvd1;
}CcmEmmEventStatisOperReq;

/*
 * CCM -> CESM, Enable/Disable APN class
 * SIGID: SIG_CCM_CESM_SET_APN_CLASS_CFG_REQ
*/
typedef struct CcmCesmSetApnClassCfgReq_Tag
{
    UINT8       apnClass;
    UINT8       disabled; // 0: Enabled, 1 = disabled
    UINT16  	maxPdnConnPerBlock;
	UINT16 		maxPdnConnTimer;
	UINT16 		pdnReqWaitTimer;
}CcmCesmSetApnClassCfgReq;

typedef struct CcmCesmGetApnDisableStatusReq_Tag
{
	CmiPsGetAPNDisableSyncStatusReq	ApnDisableStatus;
	UINT8 apnLength;
}CcmCesmGetApnDisableStatusReq;

typedef struct CcmCesmSetApnDisableStatusReq_Tag
{
	CmiPsSetAPNDisableSyncStatusReq	ApnDisableStatus;
	UINT8 apnLength;
}CcmCesmSetApnDisableStatusReq;

typedef struct CcmSetEmmLapiInfoReq_Tag
{
  UINT8 LAPI;
}CcmSetEmmLapiInfoReq;

typedef struct CemmCcmSetRoamingDataReq_Tag
{
   BOOL RoamData;
}CemmCcmSetRoamingDataReq;

typedef GosEmptySignal CemmCcmGetRoamingDataReq;

/*********************************************************************************
 * Enums
*********************************************************************************/
typedef enum CurrentTaiType_Tag
{
    NORMAL_TA,
    FORBIDDEN_TA_FOR_REGIONAL_PROVISION_OF_SERVICE,
    FORBIDDEN_TA_FOR_ROAMING,
    BLOCKED_TA
}CurrentTaiType;

/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/*
 * CE PLMN API
 * Decide whether these two PLMN is EPLMN
*/
BOOL CePlmnIsEplmn(Plmn srcPlmn, Plmn destPlmn);

/*
 * CE PLMN API
 * Get "plmn" type
*/
PlmnType CePlmnGetPlmnType(Plmn plmn);

/*
 * CEMM EMM API
 * Check a TAI is a forbidden TAI or a blocked TAI or a normal TAI
*/
CurrentTaiType GetTaiType(Tai  tai);

/*
 * CEMM EMM API
 * Get Kasme and NAS UPLINK COUNT
*/
void CemmNasSecurityKey(AsmeKey *kasme, NasCount *uplinkNasCount);

/*
 * CEMM EMM API
 * Get NAS-MAC and NAS UPLINK COUNT
*/
void CemmNasMacForReEst(UINT8     *pInData,      //input, the message to be protected to calculate NAS-MAC
                        UINT16     bitLen,       //input, the bit length of message
                        NasCount  *uplinkNasCount, //output, the uplink NAS COUNT that would be used for the next uplink NAS message
                        UINT32    *nasMac);      //ouput, the 32 bits NAS MAC

/*
 * CE PLMN API,
 * Get UE band capability
 * input&return parameters: UINT8 *pRetBand
 * if band is invalid, set to 0
 * example: pRetBand[SUPPORT_MAX_BAND_NUM] = {2, 4, 5, 0}; just means only 2/4/5 valid
*/
void CePlmnGetBandCapability(UINT8 *pRetBand);

/*
 * CEMM API,
 * API for ERRC to check whether EMM side is ok to support CP re-establish.
*/
BOOL CemmIsCpReestSupport(void);

/*
 * CEMM API
 * Whether UE set to support UP
*/
BOOL CemmUpSupport(void);

/*
 * CEMM API
 * API for TCP/IP to get ul send delay ticks
*/
void CemmGetUlSendDelayTicks(UINT32 *pOutDelayTicks);

#endif

