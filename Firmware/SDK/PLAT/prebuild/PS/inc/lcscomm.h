#ifndef _LCS_COMMON_H_
#define _LCS_COMMON_H_
/*******************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    lcscomm.h
 * Description:  Location Service messages defenition
 * History:      12/17/2018, Originated by flxing
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/

#include "pssys.h"

/******************************************************************************
 * Macros
 ******************************************************************************/

#define     MAX_SIZE_EXTERNAL_ADDRESS           20
#define     MAX_SIZE_MLC_NUMBER                 9
#define     MAX_SIZE_H_GMLC_ADDRESS             17
#define     MAX_SIZE_LOCATION_ESTIMATE          20
#define     MAX_SIZE_VELOCITY_ESTIMATE          7
#define     MAX_SIZE_GANSS_ASSISTANCE_DATA      40
#define     MAX_NUM_OF_LPP_MESSAGE              3
#define     MAX_SIZE_ASSISTANCE_DATA            38
#define     MAX_SIZE_EXTENSION_TYPE             16
#define     MAX_SIZE_EXTENSION_ID               16
#define     MAX_NUM_OF_PRIVATE_EXTENSIONS       10

#define     MAX_SIZE_DECIPHERING_KEYS           15
#define     MAX_SIZE_ADD_LOCATION_ESTIMATE      91
#define     MAX_SIZE_PLMN_LIST                  20
#define     MAX_SIZE_PLMN_ID                    3

#define     MAX_LCS_NAME_STRING_LENGTH          63
#define     MAX_SIZE_LCS_CODEWORD               20

/*******************************************************************************
* Type Definition
*******************************************************************************/  

typedef enum NotificationType_Tag
{
    NOTIFY_LOCATION_ALLOWED                               = 0,
    NOTIFY_AND_VERIFY_LOCATION_ALLOWED_IF_NO_RESPONSE     = 1,
    NOTIFY_AND_VERIFY_LOCATION_NOT_ALLOWED_IF_NO_RESPONSE = 2,
    LOCATION_NOT_ALLOWED                                  = 3
}
NotificationType;

typedef enum LocationEstimateType_Tag
{
    CURRENT_LOCATION               = 0,
    CURRENT_OR_LAST_KNOWN_LOCATION = 1,
    INITIAL_LOCATION               = 2,
    ACTIVATE_DEFERRED_LOCATION     = 3,
    CANCEL_DEFERRED_LOCATION       = 4,
    NOTIFICATION_VERIFICATION_ONLY = 5
}
LocationEstimateType;

typedef struct DeferredLocationEventType_Tag
{
    BOOL                    deferredLocationEventTypePresent;
    INT16                   deferredLocationEventType;
}
DeferredLocationEventType;

typedef struct LocationType_Tag
{
    BOOL                        present;
    LocationEstimateType        locEstimateType;
    DeferredLocationEventType   deferredLocEventType;
}
LocationType;

typedef struct HGmlcAddress_Tag
{
    BOOL        present;
    INT8        hGmlcAddressLength;
    INT8        hGmlcAddress[MAX_SIZE_MLC_NUMBER];
}
HGmlcAddress;

typedef struct ExternalAddress_Tag
{
    BOOL        present;
    INT8        addressLength;
    INT8        externalAddress[MAX_SIZE_EXTERNAL_ADDRESS];
}
ExternalAddress;

typedef struct SsLcsExtensionType_Tag
{
    INT8         n;
    INT8         data[MAX_SIZE_EXTENSION_TYPE];
}
SsLcsExtensionType;

typedef struct SsLcsExtensionId_Tag
{
    INT8         n;
    INT8         data[MAX_SIZE_EXTENSION_ID];
}
SsLcsExtensionId;

typedef struct SsLcsPrivateExtListData_Tag
{
    BOOL                    extTypePresent;
    SsLcsExtensionType      extType;
    SsLcsExtensionId        extId;
}
SsLcsPrivateExtListData;

typedef struct SsLcsPrivateExtensionList_Tag
{
    INT8                       n; /* 1 to maxNumOfPrivateExtensions */
    SsLcsPrivateExtListData    data[MAX_NUM_OF_PRIVATE_EXTENSIONS];
}
SsLcsPrivateExtensionList;

typedef struct SsLcsPcsExtensions_Tag
{
    INT8    dummy;
}
SsLcsPcsExtensions;

typedef struct SsLcsExtensionContainer_Tag
{
    BOOL                        privateExtensionListPresent;
    SsLcsPrivateExtensionList   privateExtensionList;
    BOOL                        pcs_ExtensionsPresent;
    SsLcsPcsExtensions          pcs_Extensions;
}
SsLcsExtensionContainer;

typedef struct ExtensionContainer_Tag
{
    BOOL                        present;
    SsLcsExtensionContainer     data;
}
ExtensionContainer;

typedef struct ClientExternalId_Tag
{
    BOOL                present;
    ExternalAddress     externalAddress;
    ExtensionContainer  extensionContainer;
}
ClientExternalId;

typedef struct DataCodingScheme_Tag
{
    INT8        scheme;
}
DataCodingScheme;

typedef struct NameString_Tag
{
    INT8        length;
    INT8        name[MAX_LCS_NAME_STRING_LENGTH];
}
NameString;

typedef enum LcsFormatIndicator_Tag
{
    LOGICAL_NAME  = 0,
    EMAIL_ADDRESS = 1,
    MSISDN        = 2,
    URL           = 3,
    SIP_URL       = 4
}
LcsFormatIndicator;

typedef struct LcsFormatIndicatorItem_Tag
{
    BOOL                present;
    LcsFormatIndicator  formatIndicator;
}
LcsFormatIndicatorItem;

typedef struct ClientName_Tag
{
    BOOL                    present;
    DataCodingScheme        dataCodingScheme;
    NameString              nameString;
    LcsFormatIndicatorItem  optFormatIndicator;
}
ClientName;

typedef struct LcsRequestorId_Tag
{
    BOOL                        present;
    DataCodingScheme            dataCodingScheme;
    NameString                  requestorIdString;
    LcsFormatIndicatorItem      optFormatIndicator;
}
LcsRequestorId;

typedef struct LcsCodeword_Tag
{
    BOOL                present;
    DataCodingScheme    dataCodingScheme;
    INT8                length;
    INT8                codewordString[MAX_SIZE_LCS_CODEWORD];
}
LcsCodeword;

typedef struct LcsServiceTypeId_Tag
{
    BOOL    present;
    INT8    serviceTypeId;
}
LcsServiceTypeId;

typedef struct DeferredLocationExt_Tag
{
    BOOL    present;
    INT8    deferredLocationExt;
}
DeferredLocationExt;

/******************************************************************************
LocationNotificationArg ::= SEQUENCE {
 notificationType [0] NotificationToMSUser,
 locationType     [1] LocationType,
 lcsClientExternalID [2] LCSClientExternalID OPTIONAL,
 lcsClientName     [3] LCSClientName  OPTIONAL,
 ... ,
 lcsRequestorID     [4] LCSRequestorID  OPTIONAL,
 lcsCodeword      [5] LCSCodeword      OPTIONAL,
 lcsServiceTypeID [6] LCSServiceTypeID OPTIONAL,
 deferredLocationExt [7] DeferredLocationExt OPTIONAL }
******************************************************************************/
typedef struct LcsLocNotifyInfo_Tag
{
    NotificationType        notifyType;
    LocationType            locationType;
    ClientExternalId        lcsClientExternalId;
    ClientName              lcsClientName;
    LcsRequestorId          lcsRequestorId;
    LcsCodeword             lcsCodeword;
    LcsServiceTypeId        serviceTypeId;
    DeferredLocationExt     deferedLocationExt;
}
LcsLocNotifyInfo;

typedef enum VerificationResponse_Tag
{
    PERMISSION_DENIED  = 0,
    PERMISSION_GRANTED = 1
}
VerificationResponse;

/******************************************************************************
LocationNotificationRes ::= SEQUENCE {
 verificationResponse [0] VerificationResponse OPTIONAL,
 ...}
******************************************************************************/
typedef struct LcsLocationNotificationResponse_Tag
{
    BOOL                    present;
    VerificationResponse    verificationResponse;
}
LcsLocationNotificationResponse;

typedef struct LcsLocationNotificationResult_Tag
{
    LcsLocationNotificationResponse     response;
    UINT8                               handleId;
}
LcsLocationNotificationResult;

/* For E-UTRAN access, only locationEstimate, assistanceData, periodicEvent,
   deferredMt-lrOrmo-lrCancellation, enteringAreaEvent, leavingAreaEvent, 
   beingInsideAreaEvent, motionEvent or maximumIntervalExpirationEvent shall be included */
typedef enum MolrType_Tag
{
    LOCATION_ESTIMATE                             = 0,
    ASSISTANCE_DATA                               = 1,
    DECIPHERING_KEYS                              = 2,
    DEFERRED_MOLR_TTTP_INITIATION                 = 3,
    DEFERRED_MOLR_SELF_LOCATIONINITIATION         = 4,
    DEFERRED_MTLR_OR_MO_LR_TTTP_LOCATION_ESTIMATE = 5,
    DEFEERED_MT_LRORMO_LR_CANCELLATION            = 6,
    PERIODIC_EVENT                                = 7,
    ENTERING_AREA_EVENT                           = 8,
    LEAVING_AREA_EVENT                            = 9,
    BEING_IN_SIDE_AREA_EVENT                      = 10,
    MOTION_EVENT                                  = 11,
    MAXIMUM_INTERVAL_EXPIRATION_EVENT             = 12
}
MolrType;

/* The parameter locationMethod shall be included if and only if the molr-Type 
   is set to value deCipheringKeys or assistanceData. */

/* locationMethod shall not be included for E-UTRAN access. */
typedef enum LocationMethod_Tag
{
    MS_BASED_EOTD          = 0,
    MS_ASSISTED_EOTD       = 1,
    ASSISTED_GPS           = 2,
    MS_BASED_OTDOA         = 3,
    ASSISTED_GANSS         = 4,
    ASSISTED_GPS_AND_GANSS = 5
}
LocationMethod;

typedef struct LocationMethodItem_Tag
{
    BOOL                present;
    LocationMethod      method;
}
LocationMethodItem;

typedef struct HorizontalAccuracy_Tag
{
    BOOL    present;
    INT8    accuracy;
}
HorizontalAccuracy;

typedef struct VerticalAccuracy_Tag
{
    BOOL    present;
    INT8    accuracy;
}
VerticalAccuracy;

typedef enum ResponseTimeCatagory_Tag
{
    LOW_DELAY      = 0,
    DELAY_TOLERANT = 1
}
ResponseTimeCatagory;

typedef struct ResponseTime_Tag
{
    BOOL                    present;
    ResponseTimeCatagory    responseTimeCatagory;
}
ResponseTime;

typedef struct LcsQos_Tag
{
    HorizontalAccuracy      horizontalAccuracy;
    BOOL                    verticalCoordReq;
    VerticalAccuracy        verticalAccuracy;
    ResponseTime            responseTime;
    ExtensionContainer      extensionContainer;
    BOOL                    velocityRequest;
}
LcsQos;

typedef struct  LcsQosItem_Tag
{
    BOOL        present;
    LcsQos      lcsQosData;
}
LcsQosItem;

typedef struct MlcNumber_Tag
{
    BOOL    present;
    INT8    mlcNumberLength;
    INT8    mlcNumber[MAX_SIZE_MLC_NUMBER];
}
MlcNumber;

typedef struct GpsAssistanceData_Tag
{
    BOOL    present;
    INT8    assistanceDataLength;
    INT8    assistanceData[MAX_SIZE_ASSISTANCE_DATA];
}
GpsAssistanceData;

typedef enum GadShapesBitMask_Tag
{
    ELLIPSOID_POINT                                         = 0x01,
    ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE                 = 0x02,
    ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE                = 0x04,
    POLYGON                                                 = 0x08,
    ELLIPSOID_POINT_WITH_ALTITUDE                           = 0x10,
    ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID = 0x20,
    ELLIPSOID_ARC                                           = 0x40
}
GadShapesBitMask;

typedef struct SupportedGadShapes_Tag
{
    BOOL    present;
    INT16   supportedGADShapesBitMask;
}
SupportedGadShapes;

typedef struct AgeOfLocationInfo_Tag
{
    BOOL    present;
    INT16   ageOfLocationInformation; /* 0..32767 */
}
AgeOfLocationInfo;

typedef struct LocationEstimate_Tag
{
    BOOL    present;
    INT8    length;
    INT8    data[MAX_SIZE_LOCATION_ESTIMATE]; /* IMPLICIT OCTET STRING */
}
LocationEstimate;

typedef struct VelocityEstimate_Tag
{
    BOOL    present;
    INT8    length;
    INT8    data[MAX_SIZE_VELOCITY_ESTIMATE]; /* IMPLICIT OCTET STRING */
}
VelocityEstimate;

typedef struct ReferenceNumber_Tag
{
    BOOL    present;
    INT8    data; /* IMPLICIT OCTET STRING */
}
ReferenceNumber;

typedef struct PeriodicLdrInfo_Tag
{
    BOOL    present;
    INT32   reportingAount;       /* 1 .. 8639999 */
    INT32   reportingInterval;    /* 1 .. 8639999 */
}
PeriodicLdrInfo;

typedef struct SequenceNumber_Tag
{
    BOOL    present;
    INT32   sequenceNumber;       /* 1 .. 8639999 */
}
SequenceNumber;

typedef enum TerminationCause_Tag
{
    SUBSCRIBER_TERMINATION = 0,
    UE_TERMINATION         = 1
}
TerminationCause;

typedef struct TerminationCauseItem_Tag
{
    BOOL                present;
    TerminationCause    terminationCause;
}
TerminationCauseItem;

typedef struct GanssAssistanceData_Tag
{
    BOOL    present;
    INT8    length;
    INT8    data[MAX_SIZE_GANSS_ASSISTANCE_DATA]; /* IMPLICIT OCTET STRING */
}
GanssAssistanceData;

typedef struct MultiplePositioningProtocolPdusData_Tag
{
    INT8    length;
    INT8    data[255/* TBD:LPP message max size */];
}
MultiplePositioningProtocolPdusData;

typedef struct MultiplePositioningProtocolPdus_Tag
{
    INT8                                    numOfLppMsg;
    MultiplePositioningProtocolPdusData     lppMsg[MAX_NUM_OF_LPP_MESSAGE];
}
MultiplePositioningProtocolPdus;

typedef struct MultiplePositioningProtocolPdusItem_Tag
{
    BOOL                                present;
    MultiplePositioningProtocolPdus     data;
}
MultiplePositioningProtocolPdusItem;


/******************************************************************************
LCS-MOLRArg ::= SEQUENCE {
    molr-Type                  [0]  MOLR-Type,
 locationMethod                 [1]  LocationMethod                  OPTIONAL,
 lcs-QoS                      [2]  LCS-QoS                   OPTIONAL,
 lcsClientExternalID             [3]  LCSClientExternalID             OPTIONAL,
 mlc-Number                  [4]  ISDN-AddressString                 OPTIONAL,
 gpsAssistanceData             [5]  GPSAssistanceData                 OPTIONAL,
 ...,
 supportedGADShapes             [6]  SupportedGADShapes                 OPTIONAL,
 lcsServiceTypeID             [7]  LCSServiceTypeID                 OPTIONAL,
 ageOfLocationInfo             [8]  AgeOfLocationInformation         OPTIONAL,
 locationType                 [9]  LocationType                  OPTIONAL,
 pseudonymIndicator             [10] NULL                       OPTIONAL,
 h-gmlc-address                 [11] GSN-Address                  OPTIONAL,
 locationEstimate             [12] Ext-GeographicalInformation     OPTIONAL,
 velocityEstimate             [13] VelocityEstimate                 OPTIONAL,
 referenceNumber                 [14] LCS-ReferenceNumber             OPTIONAL,
 periodicLDRInfo                 [15] PeriodicLDRInfo                 OPTIONAL,
 locationUpdateRequest         [16] NULL                          OPTIONAL,
 sequenceNumber                 [17] SequenceNumber                  OPTIONAL,
 terminationCause             [18] TerminationCause                 OPTIONAL,
 mo-lrShortCircuit             [19] NULL                          OPTIONAL,
 ganssAssistanceData             [20] GANSSAssistanceData             OPTIONAL,
 multiplePositioningProtocolPDUs [21] MultiplePositioningProtocolPDUs OPTIONAL,
 locationInfo                 [22] LocationInfo                  OPTIONAL }
******************************************************************************/

/*
NOTE: Only the following IEs defined in MO-LR Invoke in 3GPP TS 24.080 [5] are used for E-UTRAN LCS:
- molr-Type
- lcs-QoS
- lcsServiceTypeID
- ageOfLocationInformation
- locationType
- mlc-Number
- lcsClientExternalID
- pseudonymIndicator
- supportedGADShapes
- multiplePositioningProtocolPDUs
*/
typedef struct SsLcsMolrData_Tag
{
    MolrType                                molrType;
    LocationMethodItem                      locationMethod;
    LcsQosItem                              lcsQos;
    ClientExternalId                        clientExternalId;
    MlcNumber                               mlcNumber;
    GpsAssistanceData                       gpsAssistanceData;
    SupportedGadShapes                      supportedGadShapes;
    LcsServiceTypeId                        lcsServiceTypeId;
    AgeOfLocationInfo                       ageOfLocationInfo;
    LocationType                            locationType;
    BOOL                                    pseudonymIndicator;
    HGmlcAddress                            hGmlcAddress;
    LocationEstimate                        locationEstimate;
    VelocityEstimate                        velocityEstimate;
    ReferenceNumber                         referenceNumber;
    PeriodicLdrInfo                         periodicLdrInfo;
    BOOL                                    locationUpdateRequest;  /* IMPLICIT NULL OPTIONAL */
    SequenceNumber                          sequenceNumber;
    TerminationCauseItem                    teminationCause;
    BOOL                                    moLrShortCircuit;       /* IMPLICIT NULL OPTIONAL */
    GanssAssistanceData                     ganssAssistanceData;
    MultiplePositioningProtocolPdusItem     multiplePositioningProtocolPdus;
    //locationInfo:can't find the definition   TBD
}
SsLcsMolrData;

typedef struct MolrRequest_Tag
{
    SsLcsMolrData       lcsMolrData;
    UINT16              timeout;        /* Timer T(LCSL)= 10s to 300s */
}
MolrRequest;

typedef struct DecipheringKeys_Tag
{
    BOOL    present;
    INT8    length;
    INT8    data[MAX_SIZE_DECIPHERING_KEYS]; /* Fixed size of 15 bytes  IMPLICIT OCTET STRING */
}
DecipheringKeys;

typedef struct AddLocationEstimate_Tag
{
    BOOL    present;
    INT8    length;
    INT8    data[MAX_SIZE_ADD_LOCATION_ESTIMATE]; /* IMPLICIT OCTET STRING */
}
AddLocationEstimate;

typedef struct PlmnId_Tag
{
    INT8    length;
    INT8    plmnId[MAX_SIZE_PLMN_ID];
}
PlmnId;

typedef enum RanTechnology_Tag
{
    RAN_TECHNOLOGY_GSM  = 0,
    RAN_TECHNOLOGY_UMTS = 1,
}
RanTechnology;

typedef struct SsLcsOptRanTechnology_Tag
{
    BOOL            present;
    RanTechnology   ranTechnology;
}
SsLcsOptRanTechnology;

typedef struct PlmnListData_Tag
{
    PlmnId                  plmnId;
    SsLcsOptRanTechnology   ranTechnology;
    BOOL                    ranPeriodicLocationSupport;       /* IMPLICIT NULL OPTIONAL */
}
PlmnListData;

typedef struct PlmnList_Tag
{
    BOOL            present;
    INT8            length;
    PlmnListData    plmnlist[MAX_SIZE_PLMN_LIST];
}
PlmnList;

typedef struct ReportingPlmnListData_Tag
{
    BOOL        plmnListPrioritized;       /* IMPLICIT NULL OPTIONAL */
    PlmnList    plmnlist;
}
ReportingPlmnListData;

typedef struct ReportingPlmnList_Tag
{
    BOOL                    present;
    ReportingPlmnListData   data;       /* IMPLICIT NULL OPTIONAL */
}
ReportingPlmnList;


/******************************************************************************
LCS-MOLRRes::= SEQUENCE {
 locationEstimate     [0] Ext-GeographicalInformation     OPTIONAL,
 decipheringKeys      [1] DecipheringKeys           OPTIONAL,
 ...,
 add-LocationEstimate    [2] Add-GeographicalInformation     OPTIONAL,
 velocityEstimate     [3] VelocityEstimate             OPTIONAL,
 referenceNumber         [4] LCS-ReferenceNumber             OPTIONAL,
 h-gmlc-address      [5] GSN-Address                  OPTIONAL,
 mo-lrShortCircuit     [6] NULL                   OPTIONAL,
 reportingPLMNList     [7] ReportingPLMNList             OPTIONAL
 }
******************************************************************************/

/*
-- decipheringKeys shall not be included for E-UTRAN access.
-- referenceNumber shall not be included for E-UTRAN access.
-- h-gmlc-address shall not be included for E-UTRAN access.
-- mo-lrShortCircuit shall not be included for E-UTRAN access.
-- reportingPLMNList shall not be included for E-UTRAN access.
*/
typedef struct MolrResult_Tag
{
    LocationEstimate        locationEstimate;
    DecipheringKeys         decipheringKeys;
    AddLocationEstimate     addLocationEstimate;
    VelocityEstimate        velocityEstimate;
    ReferenceNumber         referenceNumber;
    HGmlcAddress            hGmlcAddress;
    BOOL                    moLrShortCircuit;
    ReportingPlmnList       reportingPlmnList;
}
MolrResult;

#endif


