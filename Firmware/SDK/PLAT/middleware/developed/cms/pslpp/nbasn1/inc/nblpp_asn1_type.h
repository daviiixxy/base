
#ifndef __NBLPP_ASN1_TYPE_H__
#define __NBLPP_ASN1_TYPE_H__

#ifdef WIN32
#include "winsys.h"
#else
#include "osasys.h"
#endif

#include "asn1util.h"



#define maxEARFCN                                      65535

#define maxEARFCN_Plus1                                65536

#define maxEARFCN2                                     262143

#define maxEPDU                                        16

#define maxAddPRSconfig_r14                            2

#define maxAvailNarrowBands_Minus1_r14                 15

#define maxFreqLayers                                  3

#define maxCarrier_r14                                 5

#define maxCells_r14                                   72

#define maxPaths_r14                                   2

#define maxBands                                       64

#define maxFBI                                         64

#define maxFBI_Plus1                                   65

#define maxFBI2                                        256

#define maxMBS_r14                                     64

#define maxWLAN_AP_r13                                 64

#define maxWLAN_DataSets_r14                           8

#define maxWLAN_AP_r14                                 128

#define maxVisibleAPs_r14                              32

#define maxKnownAPs_r14                                2048

#define maxBT_Beacon_r13                               32



/******** INTEGER BEGIN ********/

typedef UINT8      SequenceNumberLpp;  /* INTEGER (0..255) */


typedef UINT8      TransactionNumber;  /* INTEGER (0..255) */


typedef UINT16     ARFCN_ValueEUTRA;  /* INTEGER (0..65535) */


typedef UINT32     ARFCN_ValueEUTRA_v9a0;  /* INTEGER (65536..262143) */


typedef UINT32     ARFCN_ValueEUTRA_r14;  /* INTEGER (0..262143) */


typedef UINT16     ARFCN_ValueUTRA;  /* INTEGER (0..16383) */


typedef UINT16     EPDU_ID;  /* INTEGER (1..256) */


typedef UINT8      ReportingDuration;  /* INTEGER (0..255) */


/******** INTEGER END ********/



/******** BIT STRING BEGIN ********/

#ifndef __ASNBITSTRING_MAXSIZE8__
#define __ASNBITSTRING_MAXSIZE8__

typedef struct AsnBitString_MaxSize8Tag
{
    UINT16 n; /*SIZE(1..8)*/
    UINT8 data[1];
}
AsnBitString_MaxSize8;
#endif


#ifndef __ASNBITSTRING_MAXSIZE16__
#define __ASNBITSTRING_MAXSIZE16__

typedef struct AsnBitString_MaxSize16Tag
{
    UINT16 n; /*SIZE(1..16)*/
    UINT8 data[2];
}
AsnBitString_MaxSize16;
#endif


#ifndef __ASNBITSTRING_64__
#define __ASNBITSTRING_64__

typedef struct AsnBitString_64Tag
{
    UINT8 data[8];
}
AsnBitString_64;
#endif


#ifndef __ASNBITSTRING_128__
#define __ASNBITSTRING_128__

typedef struct AsnBitString_128Tag
{
    UINT8 data[16];
}
AsnBitString_128;
#endif


#ifndef __ASNBITSTRING_256__
#define __ASNBITSTRING_256__

typedef struct AsnBitString_256Tag
{
    UINT8 data[32];
}
AsnBitString_256;
#endif


#ifndef __ASNBITSTRING_512__
#define __ASNBITSTRING_512__

typedef struct AsnBitString_512Tag
{
    UINT8 data[64];
}
AsnBitString_512;
#endif


#ifndef __ASNBITSTRING_1024__
#define __ASNBITSTRING_1024__

typedef struct AsnBitString_1024Tag
{
    UINT8 data[128];
}
AsnBitString_1024;
#endif


#ifndef __ASNBITSTRING_40__
#define __ASNBITSTRING_40__

typedef struct AsnBitString_40Tag
{
    UINT8 data[5];
}
AsnBitString_40;
#endif


#ifndef __ASNBITSTRING_33__
#define __ASNBITSTRING_33__

typedef struct AsnBitString_33Tag
{
    UINT8 data[5];
}
AsnBitString_33;
#endif


#ifndef __ASNBITSTRING_MAXSIZE1024__
#define __ASNBITSTRING_MAXSIZE1024__

typedef struct AsnBitString_MaxSize1024Tag
{
    UINT16 n; /*SIZE(1..1024)*/
    UINT8 data[128];
}
AsnBitString_MaxSize1024;
#endif


#ifndef __ASNBITSTRING_34__
#define __ASNBITSTRING_34__

typedef struct AsnBitString_34Tag
{
    UINT8 data[5];
}
AsnBitString_34;
#endif


#ifndef __ASNBITSTRING_48__
#define __ASNBITSTRING_48__

typedef struct AsnBitString_48Tag
{
    UINT8 data[6];
}
AsnBitString_48;
#endif


#ifndef __ASNBITSTRING__
#define __ASNBITSTRING__
typedef struct AsnBitStringTag
{
    UINT16 n;
    UINT8 *data;
}
AsnBitString;
#endif

/******** BIT STRING END ********/



/******** OCTET STRING BEGIN ********/

#ifndef __ASNOCTETSTRING_6__
#define __ASNOCTETSTRING_6__

typedef struct AsnOctetString_6Tag
{
    UINT8 data[6];
}
AsnOctetString_6;
#endif


#ifndef __ASNOCTETSTRING_MAXSIZE32__
#define __ASNOCTETSTRING_MAXSIZE32__

typedef struct AsnOctetString_MaxSize32Tag
{
    UINT16 n; /*SIZE(1..32)*/
    UINT8 data[32];
}
AsnOctetString_MaxSize32;
#endif


#ifndef __ASNOCTETSTRING__
#define __ASNOCTETSTRING__
typedef struct AsnOctetStringTag
{
    UINT16 n;
    UINT8 *data;
}
AsnOctetString;
#endif

/******** OCTET STRING END ********/


typedef struct BT_TargetDeviceErrorCauses_r13Tag
{
    enum BT_TargetDeviceErrorCauses_r13_cause_r13 {
        BT_TargetDeviceErrorCauses_r13_cause_r13_undefined = 0,
        BT_TargetDeviceErrorCauses_r13_cause_r13_requestedMeasurementsNotAvailable = 1,
        BT_TargetDeviceErrorCauses_r13_cause_r13_notAllrequestedMeasurementsPossible = 2
    } cause_r13;
    UINT8                                  bt_Beacon_rssiMeasurementNotPossible_r13;    /* OPTIONAL */
    UINT8                                  bt_Beacon_rssiMeasurementNotPossible_r13Present : 1;
    UINT8                                  reserved : 7;
}BT_TargetDeviceErrorCauses_r13;


typedef struct BT_LocationServerErrorCauses_r13Tag
{
    enum BT_LocationServerErrorCauses_r13_cause_r13 {
        BT_LocationServerErrorCauses_r13_cause_r13_undefined = 0
    } cause_r13;
}BT_LocationServerErrorCauses_r13;


typedef struct BT_Error_r13Tag
{
    UINT8       tag;
        #define TAG_BT_Error_r13_locationServerErrorCauses_r13 0
        #define TAG_BT_Error_r13_targetDeviceErrorCauses_r13 1
    union {
        BT_LocationServerErrorCauses_r13       *locationServerErrorCauses_r13;
        BT_TargetDeviceErrorCauses_r13         *targetDeviceErrorCauses_r13;
    } choice;
}BT_Error_r13;


typedef struct BT_RequestCapabilities_r13Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}BT_RequestCapabilities_r13;


typedef struct PositioningModesTag
{
    AsnBitString_MaxSize8                  posModes;
}PositioningModes;


typedef struct BT_ProvideCapabilities_r13Tag
{
    AsnBitString_MaxSize8                  bt_Modes_r13;
    AsnBitString_MaxSize8                  bt_MeasSupported_r13;
    PositioningModes                       *periodicalReportingSupported_r14;    /* OPTIONAL */
    UINT8                                  idleStateForMeasurements_r14Present : 1;
    UINT8                                  periodicalReportingSupported_r14Present : 1;
    UINT8                                  reserved : 6;
}BT_ProvideCapabilities_r13;


typedef struct BT_RequestLocationInformation_r13Tag
{
    AsnBitString_MaxSize8                  requestedMeasurements_r13;
}BT_RequestLocationInformation_r13;


typedef struct BT_MeasurementElement_r13Tag
{
    AsnBitString_48                        btAddr_r13;
    INT8  /* INTEGER (-128..127) */        rssi_r13;    /* OPTIONAL */
    UINT8                                  rssi_r13Present : 1;
    UINT8                                  reserved : 7;
}BT_MeasurementElement_r13;


typedef struct BT_MeasurementList_r13Tag
{
    BT_MeasurementElement_r13                          data;
    struct BT_MeasurementList_r13Tag                   *next;
}
BT_MeasurementList_r13;


typedef struct UTCTimeTag
{
    /* In 36.355, the UTCTime takes form of 'YYMMDDhhmmssZ' 
        Each UTCTime character has its own actual value range, such as '0' ~ '9', although we have to encode them as INTEGER (0..126) 
        More information about UTCTime: X.680.47/X.690.11.8 */ 
    UINT16 n;
    UINT8  /* INTEGER(0..126) */                       *data;
}
UTCTime;


typedef struct BT_MeasurementInformation_r13Tag
{
    UTCTime                                *measurementReferenceTime_r13;    /* OPTIONAL */
    BT_MeasurementList_r13                 *bt_MeasurementList_r13;    /* OPTIONAL */
    UINT8                                  measurementReferenceTime_r13Present : 1;
    UINT8                                  bt_MeasurementList_r13Present : 1;
    UINT8                                  reserved : 6;
}BT_MeasurementInformation_r13;


typedef struct BT_ProvideLocationInformation_r13Tag
{
    BT_MeasurementInformation_r13          *bt_MeasurementInformation_r13;    /* OPTIONAL */
    BT_Error_r13                           *bt_Error_r13;    /* OPTIONAL */
    UINT8                                  bt_MeasurementInformation_r13Present : 1;
    UINT8                                  bt_Error_r13Present : 1;
    UINT8                                  reserved : 6;
}BT_ProvideLocationInformation_r13;


typedef struct WLAN_AP_Identifier_r13Tag
{
    AsnOctetString_6                       bssid_r13;
    AsnOctetString_MaxSize32               *ssid_r13;    /* OPTIONAL */
    UINT8                                  ssid_r13Present : 1;
    UINT8                                  reserved : 7;
}WLAN_AP_Identifier_r13;


typedef struct WLAN_RequestAssistanceData_r14_wlan_AP_StoredData_r14Tag
{
    WLAN_AP_Identifier_r13                             data;
    struct WLAN_RequestAssistanceData_r14_wlan_AP_StoredData_r14Tag *next;
}
WLAN_RequestAssistanceData_r14_wlan_AP_StoredData_r14;


typedef struct WLAN_RequestAssistanceData_r14_visibleAPs_r14Tag
{
    WLAN_AP_Identifier_r13                             data;
    struct WLAN_RequestAssistanceData_r14_visibleAPs_r14Tag *next;
}
WLAN_RequestAssistanceData_r14_visibleAPs_r14;


typedef struct WLAN_RequestAssistanceData_r14Tag
{
    AsnBitString_MaxSize8                  requestedAD_r14;
    WLAN_RequestAssistanceData_r14_visibleAPs_r14 *visibleAPs_r14;    /* OPTIONAL */
    WLAN_RequestAssistanceData_r14_wlan_AP_StoredData_r14 *wlan_AP_StoredData_r14;    /* OPTIONAL */
    UINT8                                  visibleAPs_r14Present : 1;
    UINT8                                  wlan_AP_StoredData_r14Present : 1;
    UINT8                                  reserved : 6;
}WLAN_RequestAssistanceData_r14;


typedef struct LocationDataLCI_r14Tag
{
    UINT8  /* BIT STRING (SIZE(6)) */      latitudeUncertainty_r14;
    AsnBitString_34                        latitude_r14;
    UINT8  /* BIT STRING (SIZE(6)) */      longitudeUncertainty_r14;
    AsnBitString_34                        longitude_r14;
    UINT8  /* BIT STRING (SIZE(6)) */      altitudeUncertainty_r14;    /* OPTIONAL */
    UINT32  /* BIT STRING (SIZE(30)) */    altitude_r14;    /* OPTIONAL */
    UINT8  /* BIT STRING (SIZE(8)) */      datum_r14;
    UINT8                                  altitudeUncertainty_r14Present : 1;
    UINT8                                  altitude_r14Present : 1;
    UINT8                                  reserved : 6;
}LocationDataLCI_r14;


typedef struct WLAN_AP_Location_r14Tag
{
    LocationDataLCI_r14                    locationDataLCI_r14;
}WLAN_AP_Location_r14;


typedef struct WLAN_AP_Data_r14Tag
{
    WLAN_AP_Identifier_r13                 wlan_AP_Identifier_r14;
    WLAN_AP_Location_r14                   *wlan_AP_Location_r14;    /* OPTIONAL */
    UINT8                                  wlan_AP_Location_r14Present : 1;
    UINT8                                  reserved : 7;
}WLAN_AP_Data_r14;


typedef struct SupportedChannels_11bg_r14Tag
{
    BOOL                                   ch1_r14;
    BOOL                                   ch2_r14;
    BOOL                                   ch3_r14;
    BOOL                                   ch4_r14;
    BOOL                                   ch5_r14;
    BOOL                                   ch6_r14;
    BOOL                                   ch7_r14;
    BOOL                                   ch8_r14;
    BOOL                                   ch9_r14;
    BOOL                                   ch10_r14;
    BOOL                                   ch11_r14;
    BOOL                                   ch12_r14;
    BOOL                                   ch13_r14;
    BOOL                                   ch14_r14;
}SupportedChannels_11bg_r14;


typedef struct SupportedChannels_11a_r14Tag
{
    BOOL                                   ch34_r14;
    BOOL                                   ch36_r14;
    BOOL                                   ch38_r14;
    BOOL                                   ch40_r14;
    BOOL                                   ch42_r14;
    BOOL                                   ch44_r14;
    BOOL                                   ch46_r14;
    BOOL                                   ch48_r14;
    BOOL                                   ch52_r14;
    BOOL                                   ch56_r14;
    BOOL                                   ch60_r14;
    BOOL                                   ch64_r14;
    BOOL                                   ch149_r14;
    BOOL                                   ch153_r14;
    BOOL                                   ch157_r14;
    BOOL                                   ch161_r14;
}SupportedChannels_11a_r14;


typedef struct WLAN_DataSet_r14_wlan_AP_List_r14Tag
{
    WLAN_AP_Data_r14                                   data;
    struct WLAN_DataSet_r14_wlan_AP_List_r14Tag        *next;
}
WLAN_DataSet_r14_wlan_AP_List_r14;


typedef struct WLAN_DataSet_r14Tag
{
    WLAN_DataSet_r14_wlan_AP_List_r14      wlan_AP_List_r14;
    SupportedChannels_11a_r14              *supportedChannels_11a_r14;    /* OPTIONAL */
    SupportedChannels_11bg_r14             *supportedChannels_11bg_r14;    /* OPTIONAL */
    UINT8                                  supportedChannels_11a_r14Present : 1;
    UINT8                                  supportedChannels_11bg_r14Present : 1;
    UINT8                                  reserved : 6;
}WLAN_DataSet_r14;


typedef struct WLAN_ProvideAssistanceData_r14_wlan_DataSet_r14Tag
{
    WLAN_DataSet_r14                                   data;
    struct WLAN_ProvideAssistanceData_r14_wlan_DataSet_r14Tag *next;
}
WLAN_ProvideAssistanceData_r14_wlan_DataSet_r14;


typedef struct WLAN_LocationServerErrorCauses_r13Tag
{
    enum WLAN_LocationServerErrorCauses_r13_cause_r13 {
        WLAN_LocationServerErrorCauses_r13_cause_r13_undefined = 0,
        WLAN_LocationServerErrorCauses_r13_cause_r13_requestedADNotAvailable_v1420 = 1,
        WLAN_LocationServerErrorCauses_r13_cause_r13_notAllrequestedADAvailable_v1420 = 2
    } cause_r13;
    UINT8                                  apLocationDataUnavailable_r14;    /* OPTIONAL */
    UINT8                                  apLocationDataUnavailable_r14Present : 1;
    UINT8                                  reserved : 7;
}WLAN_LocationServerErrorCauses_r13;


typedef struct WLAN_TargetDeviceErrorCauses_r13Tag
{
    enum WLAN_TargetDeviceErrorCauses_r13_cause_r13 {
        WLAN_TargetDeviceErrorCauses_r13_cause_r13_undefined = 0,
        WLAN_TargetDeviceErrorCauses_r13_cause_r13_requestedMeasurementsNotAvailable = 1,
        WLAN_TargetDeviceErrorCauses_r13_cause_r13_notAllrequestedMeasurementsPossible = 2
    } cause_r13;
    UINT8                                  wlan_AP_RSSI_MeasurementNotPossible_r13;    /* OPTIONAL */
    UINT8                                  wlan_AP_RTT_MeasurementNotPossible_r13;    /* OPTIONAL */
    UINT8                                  wlan_AP_RSSI_MeasurementNotPossible_r13Present : 1;
    UINT8                                  wlan_AP_RTT_MeasurementNotPossible_r13Present : 1;
    UINT8                                  reserved : 6;
}WLAN_TargetDeviceErrorCauses_r13;


typedef struct WLAN_Error_r13Tag
{
    UINT8       tag;
        #define TAG_WLAN_Error_r13_locationServerErrorCauses_r13 0
        #define TAG_WLAN_Error_r13_targetDeviceErrorCauses_r13 1
    union {
        WLAN_LocationServerErrorCauses_r13     *locationServerErrorCauses_r13;
        WLAN_TargetDeviceErrorCauses_r13       *targetDeviceErrorCauses_r13;
    } choice;
}WLAN_Error_r13;


typedef struct WLAN_ProvideAssistanceData_r14Tag
{
    WLAN_ProvideAssistanceData_r14_wlan_DataSet_r14 *wlan_DataSet_r14;    /* OPTIONAL */
    WLAN_Error_r13                         *wlan_Error_r14;    /* OPTIONAL */
    UINT8                                  wlan_DataSet_r14Present : 1;
    UINT8                                  wlan_Error_r14Present : 1;
    UINT8                                  reserved : 6;
}WLAN_ProvideAssistanceData_r14;


typedef struct WLAN_RequestCapabilities_r13Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}WLAN_RequestCapabilities_r13;


typedef struct WLAN_ProvideCapabilities_r13Tag
{
    AsnBitString_MaxSize8                  wlan_Modes_r13;
    AsnBitString_MaxSize8                  wlan_MeasSupported_r13;
    AsnBitString_MaxSize8                  *wlan_AP_AD_Supported_r14;    /* OPTIONAL */
    PositioningModes                       *periodicalReportingSupported_r14;    /* OPTIONAL */
    UINT8                                  wlan_AP_AD_Supported_r14Present : 1;
    UINT8                                  periodicalReportingSupported_r14Present : 1;
    UINT8                                  idleStateForMeasurements_r14Present : 1;
    UINT8                                  reserved : 5;
}WLAN_ProvideCapabilities_r13;


typedef struct WLAN_RequestLocationInformation_r13Tag
{
    AsnBitString_MaxSize8                  requestedMeasurements_r13;
    BOOL                                   assistanceAvailability_r14;    /* OPTIONAL */
    UINT8                                  assistanceAvailability_r14Present : 1;
    UINT8                                  reserved : 7;
}WLAN_RequestLocationInformation_r13;


typedef struct WLAN_RTT_r13Tag
{
    UINT32  /* INTEGER (0..16777215) */    rttValue_r13;
    enum WLAN_RTT_r13_rttUnits_r13 {
        WLAN_RTT_r13_rttUnits_r13_microseconds = 0,
        WLAN_RTT_r13_rttUnits_r13_hundredsofnanoseconds = 1,
        WLAN_RTT_r13_rttUnits_r13_tensofnanoseconds = 2,
        WLAN_RTT_r13_rttUnits_r13_nanoseconds = 3,
        WLAN_RTT_r13_rttUnits_r13_tenthsofnanoseconds = 4
    } rttUnits_r13;
    UINT8  /* INTEGER (0..255) */          rttAccuracy_r13;    /* OPTIONAL */
    UINT8                                  rttAccuracy_r13Present : 1;
    UINT8                                  reserved : 7;
}WLAN_RTT_r13;


typedef struct WLAN_MeasurementElement_r13Tag
{
    WLAN_AP_Identifier_r13                 wlan_AP_Identifier_r13;
    INT16  /* INTEGER (-127..128) */       rssi_r13;    /* OPTIONAL */
    WLAN_RTT_r13                           *rtt_r13;    /* OPTIONAL */
    UINT16  /* INTEGER (0..256) */         apChannelFrequency_r13;    /* OPTIONAL */
    BOOL                                   servingFlag_r13;    /* OPTIONAL */
    UINT8                                  rssi_r13Present : 1;
    UINT8                                  rtt_r13Present : 1;
    UINT8                                  apChannelFrequency_r13Present : 1;
    UINT8                                  servingFlag_r13Present : 1;
    UINT8                                  reserved : 4;
}WLAN_MeasurementElement_r13;


typedef struct WLAN_MeasurementList_r13Tag
{
    WLAN_MeasurementElement_r13                        data;
    struct WLAN_MeasurementList_r13Tag                 *next;
}
WLAN_MeasurementList_r13;


typedef struct WLAN_MeasurementInformation_r13Tag
{
    UTCTime                                *measurementReferenceTime_r13;    /* OPTIONAL */
    WLAN_MeasurementList_r13               *wlan_MeasurementList_r13;    /* OPTIONAL */
    UINT8                                  measurementReferenceTime_r13Present : 1;
    UINT8                                  wlan_MeasurementList_r13Present : 1;
    UINT8                                  reserved : 6;
}WLAN_MeasurementInformation_r13;


typedef struct WLAN_ProvideLocationInformation_r13Tag
{
    WLAN_MeasurementInformation_r13        *wlan_MeasurementInformation_r13;    /* OPTIONAL */
    WLAN_Error_r13                         *wlan_Error_r13;    /* OPTIONAL */
    UINT8                                  wlan_MeasurementInformation_r13Present : 1;
    UINT8                                  wlan_Error_r13Present : 1;
    UINT8                                  reserved : 6;
}WLAN_ProvideLocationInformation_r13;


typedef struct Sensor_RequestAssistanceData_r14Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}Sensor_RequestAssistanceData_r14;


typedef struct EllipsoidPointWithAltitudeAndUncertaintyEllipsoidTag
{
    enum EllipsoidPointWithAltitudeAndUncertaintyEllipsoid_latitudeSign {
        EllipsoidPointWithAltitudeAndUncertaintyEllipsoid_latitudeSign_north = 0,
        EllipsoidPointWithAltitudeAndUncertaintyEllipsoid_latitudeSign_south = 1
    } latitudeSign;
    UINT32  /* INTEGER (0..8388607) */     degreesLatitude;
    INT32  /* INTEGER (-8388608..8388607) */ degreesLongitude;
    enum EllipsoidPointWithAltitudeAndUncertaintyEllipsoid_altitudeDirection {
        EllipsoidPointWithAltitudeAndUncertaintyEllipsoid_altitudeDirection_height = 0,
        EllipsoidPointWithAltitudeAndUncertaintyEllipsoid_altitudeDirection_depth = 1
    } altitudeDirection;
    UINT16  /* INTEGER (0..32767) */       altitude;
    UINT8  /* INTEGER (0..127) */          uncertaintySemiMajor;
    UINT8  /* INTEGER (0..127) */          uncertaintySemiMinor;
    UINT8  /* INTEGER (0..179) */          orientationMajorAxis;
    UINT8  /* INTEGER (0..127) */          uncertaintyAltitude;
    UINT8  /* INTEGER (0..100) */          confidence;
}EllipsoidPointWithAltitudeAndUncertaintyEllipsoid;


typedef struct Sensor_AssistanceDataList_r14Tag
{
    INT16  /* INTEGER (-20000..10000) */   refPressure_r14;
    EllipsoidPointWithAltitudeAndUncertaintyEllipsoid *refPosition_r14;    /* OPTIONAL */
    INT8  /* INTEGER (-64..63) */          refTemperature_r14;    /* OPTIONAL */
    UINT8                                  refPosition_r14Present : 1;
    UINT8                                  refTemperature_r14Present : 1;
    UINT8                                  reserved : 6;
}Sensor_AssistanceDataList_r14;


typedef struct Sensor_LocationServerErrorCauses_r13Tag
{
    enum Sensor_LocationServerErrorCauses_r13_cause_r13 {
        Sensor_LocationServerErrorCauses_r13_cause_r13_undefined = 0,
        Sensor_LocationServerErrorCauses_r13_cause_r13_assistanceDataNotSupportedByServer_v1420 = 1,
        Sensor_LocationServerErrorCauses_r13_cause_r13_assistanceDataSupportedButCurrentlyNotAvailableByServer_v1420 = 2
    } cause_r13;
}Sensor_LocationServerErrorCauses_r13;


typedef struct Sensor_TargetDeviceErrorCauses_r13Tag
{
    enum Sensor_TargetDeviceErrorCauses_r13_cause_r13 {
        Sensor_TargetDeviceErrorCauses_r13_cause_r13_undefined = 0,
        Sensor_TargetDeviceErrorCauses_r13_cause_r13_assistanceDataMissing_v1420 = 1
    } cause_r13;
}Sensor_TargetDeviceErrorCauses_r13;


typedef struct Sensor_Error_r13Tag
{
    UINT8       tag;
        #define TAG_Sensor_Error_r13_locationServerErrorCauses_r13 0
        #define TAG_Sensor_Error_r13_targetDeviceErrorCauses_r13 1
    union {
        Sensor_LocationServerErrorCauses_r13   *locationServerErrorCauses_r13;
        Sensor_TargetDeviceErrorCauses_r13     *targetDeviceErrorCauses_r13;
    } choice;
}Sensor_Error_r13;


typedef struct Sensor_ProvideAssistanceData_r14Tag
{
    Sensor_AssistanceDataList_r14          *sensor_AssistanceDataList_r14;    /* OPTIONAL */
    Sensor_Error_r13                       *sensor_Error_r14;    /* OPTIONAL */
    UINT8                                  sensor_AssistanceDataList_r14Present : 1;
    UINT8                                  sensor_Error_r14Present : 1;
    UINT8                                  reserved : 6;
}Sensor_ProvideAssistanceData_r14;


typedef struct Sensor_RequestCapabilities_r13Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}Sensor_RequestCapabilities_r13;


typedef struct Sensor_AssistanceDataSupportList_r14Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}Sensor_AssistanceDataSupportList_r14;


typedef struct Sensor_ProvideCapabilities_r13Tag
{
    AsnBitString_MaxSize8                  sensor_Modes_r13;
    Sensor_AssistanceDataSupportList_r14   *sensor_AssistanceDataSupportList_r14;    /* OPTIONAL */
    PositioningModes                       *periodicalReportingSupported_r14;    /* OPTIONAL */
    UINT8                                  sensor_AssistanceDataSupportList_r14Present : 1;
    UINT8                                  periodicalReportingSupported_r14Present : 1;
    UINT8                                  idleStateForMeasurements_r14Present : 1;
    UINT8                                  reserved : 5;
}Sensor_ProvideCapabilities_r13;


typedef struct Sensor_RequestLocationInformation_r13Tag
{
    BOOL                                   uncompensatedBarometricPressureReq_r13;
    BOOL                                   assistanceAvailability_r14;    /* OPTIONAL */
    UINT8                                  assistanceAvailability_r14Present : 1;
    UINT8                                  reserved : 7;
}Sensor_RequestLocationInformation_r13;


typedef struct Sensor_MeasurementInformation_r13_uncertainty_r14Tag
{
    UINT16  /* INTEGER (0..1000) */        range_r14;
    UINT8  /* INTEGER (1..100) */          confidence_r14;
}Sensor_MeasurementInformation_r13_uncertainty_r14;


typedef struct Sensor_MeasurementInformation_r13Tag
{
    UTCTime                                *measurementReferenceTime_r13;    /* OPTIONAL */
    UINT32  /* INTEGER (30000..115000) */  uncompensatedBarometricPressure_r13;    /* OPTIONAL */
    Sensor_MeasurementInformation_r13_uncertainty_r14 *uncertainty_r14;    /* OPTIONAL */
    UINT8                                  measurementReferenceTime_r13Present : 1;
    UINT8                                  uncompensatedBarometricPressure_r13Present : 1;
    UINT8                                  uncertainty_r14Present : 1;
    UINT8                                  reserved : 5;
}Sensor_MeasurementInformation_r13;


typedef struct Sensor_ProvideLocationInformation_r13Tag
{
    Sensor_MeasurementInformation_r13      *sensor_MeasurementInformation_r13;    /* OPTIONAL */
    Sensor_Error_r13                       *sensor_Error_r13;    /* OPTIONAL */
    UINT8                                  sensor_MeasurementInformation_r13Present : 1;
    UINT8                                  sensor_Error_r13Present : 1;
    UINT8                                  reserved : 6;
}Sensor_ProvideLocationInformation_r13;


typedef struct TBS_RequestAssistanceData_r14Tag
{
    BOOL                                   mbs_AlmanacAssistanceDataReq_r14;
    BOOL                                   mbs_AcquisitionAssistanceDataReq_r14;
}TBS_RequestAssistanceData_r14;


typedef struct MBS_AcquisitionAssistance_r14Tag
{
    UINT16  /* INTEGER (0..32767) */       transmitterID_r14;    /* OPTIONAL */
    enum MBS_AcquisitionAssistance_r14_mbsConfiguration_r14 {
        MBS_AcquisitionAssistance_r14_mbsConfiguration_r14_tb1 = 0,
        MBS_AcquisitionAssistance_r14_mbsConfiguration_r14_tb2 = 1,
        MBS_AcquisitionAssistance_r14_mbsConfiguration_r14_tb3 = 2,
        MBS_AcquisitionAssistance_r14_mbsConfiguration_r14_tb4 = 3
    } mbsConfiguration_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (1..128) */          pnCodeIndex_r14;    /* OPTIONAL */
    UINT32  /* INTEGER (919750000..927250000) */ freq_r14;    /* OPTIONAL */
    UINT8                                  transmitterID_r14Present : 1;
    UINT8                                  mbsConfiguration_r14Present : 1;
    UINT8                                  pnCodeIndex_r14Present : 1;
    UINT8                                  freq_r14Present : 1;
    UINT8                                  reserved : 4;
}MBS_AcquisitionAssistance_r14;


typedef struct MBS_AlmanacAssistance_r14Tag
{
    UINT16  /* INTEGER (0..32767) */       transmitterID_r14;
    UINT32  /* BIT STRING (SIZE(26)) */    transmitterLatitude_r14;
    UINT32  /* BIT STRING (SIZE(27)) */    transmitterLongitude_r14;
    UINT16  /* BIT STRING (SIZE(15)) */    transmitterAltitude_r14;
    UINT8  /* INTEGER (0..25) */           timeCorrection_r14;    /* OPTIONAL */
    UINT8                                  timeCorrection_r14Present : 1;
    UINT8                                  reserved : 7;
}MBS_AlmanacAssistance_r14;


typedef struct MBS_AssistanceDataElement_r14Tag
{
    MBS_AlmanacAssistance_r14              *mbs_AlmanacAssistance_r14;    /* OPTIONAL */
    MBS_AcquisitionAssistance_r14          *mbs_AcquisitionAssistance_r14;    /* OPTIONAL */
    UINT8                                  mbs_AlmanacAssistance_r14Present : 1;
    UINT8                                  mbs_AcquisitionAssistance_r14Present : 1;
    UINT8                                  reserved : 6;
}MBS_AssistanceDataElement_r14;


typedef struct MBS_AssistanceDataList_r14Tag
{
    MBS_AssistanceDataElement_r14                      data;
    struct MBS_AssistanceDataList_r14Tag               *next;
}
MBS_AssistanceDataList_r14;


typedef struct TBS_AssistanceDataList_r14Tag
{
    MBS_AssistanceDataList_r14             *mbs_AssistanceDataList_r14;    /* OPTIONAL */
    UINT8                                  mbs_AssistanceDataList_r14Present : 1;
    UINT8                                  reserved : 7;
}TBS_AssistanceDataList_r14;


typedef struct TBS_LocationServerErrorCauses_r13Tag
{
    enum TBS_LocationServerErrorCauses_r13_cause_r13 {
        TBS_LocationServerErrorCauses_r13_cause_r13_undefined = 0,
        TBS_LocationServerErrorCauses_r13_cause_r13_assistanceDataNotSupportedByServer_v1420 = 1,
        TBS_LocationServerErrorCauses_r13_cause_r13_assistanceDataSupportedButCurrentlyNotAvailableByServer_v1420 = 2
    } cause_r13;
}TBS_LocationServerErrorCauses_r13;


typedef struct TBS_TargetDeviceErrorCauses_r13Tag
{
    enum TBS_TargetDeviceErrorCauses_r13_cause_r13 {
        TBS_TargetDeviceErrorCauses_r13_cause_r13_undefined = 0,
        TBS_TargetDeviceErrorCauses_r13_cause_r13_thereWereNotEnoughMBSBeaconsReceived = 1,
        TBS_TargetDeviceErrorCauses_r13_cause_r13_assistanceDataMissing_v1420 = 2
    } cause_r13;
}TBS_TargetDeviceErrorCauses_r13;


typedef struct TBS_Error_r13Tag
{
    UINT8       tag;
        #define TAG_TBS_Error_r13_locationServerErrorCauses_r13 0
        #define TAG_TBS_Error_r13_targetDeviceErrorCauses_r13 1
    union {
        TBS_LocationServerErrorCauses_r13      *locationServerErrorCauses_r13;
        TBS_TargetDeviceErrorCauses_r13        *targetDeviceErrorCauses_r13;
    } choice;
}TBS_Error_r13;


typedef struct TBS_ProvideAssistanceData_r14Tag
{
    TBS_AssistanceDataList_r14             *tbs_AssistanceDataList_r14;    /* OPTIONAL */
    TBS_Error_r13                          *tbs_Error_r14;    /* OPTIONAL */
    UINT8                                  tbs_AssistanceDataList_r14Present : 1;
    UINT8                                  tbs_Error_r14Present : 1;
    UINT8                                  reserved : 6;
}TBS_ProvideAssistanceData_r14;


typedef struct TBS_RequestCapabilities_r13Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}TBS_RequestCapabilities_r13;


typedef struct MBS_AssistanceDataSupportList_r14Tag
{
    BOOL                                   mbs_AcquisitionAssistanceDataSupport_r14;
    BOOL                                   mbs_AlmanacAssistanceDataSupport_r14;
}MBS_AssistanceDataSupportList_r14;


typedef struct TBS_ProvideCapabilities_r13Tag
{
    AsnBitString_MaxSize8                  tbs_Modes_r13;
    MBS_AssistanceDataSupportList_r14      *mbs_AssistanceDataSupportList_r14;    /* OPTIONAL */
    PositioningModes                       *periodicalReportingSupported_r14;    /* OPTIONAL */
    AsnBitString_MaxSize8                  *mbs_ConfigSupport_r14;    /* OPTIONAL */
    UINT8                                  mbs_AssistanceDataSupportList_r14Present : 1;
    UINT8                                  periodicalReportingSupported_r14Present : 1;
    UINT8                                  mbs_ConfigSupport_r14Present : 1;
    UINT8                                  mbs_IdleStateForMeasurements_r14Present : 1;
    UINT8                                  reserved : 4;
}TBS_ProvideCapabilities_r13;


typedef struct TBS_RequestLocationInformation_r13Tag
{
    BOOL                                   mbsSgnMeasListReq_r13;
    BOOL                                   mbsAssistanceAvailability_r14;    /* OPTIONAL */
    AsnBitString_MaxSize8                  *mbsRequestedMeasurements_r14;    /* OPTIONAL */
    UINT8                                  mbsAssistanceAvailability_r14Present : 1;
    UINT8                                  mbsRequestedMeasurements_r14Present : 1;
    UINT8                                  reserved : 6;
}TBS_RequestLocationInformation_r13;


typedef struct MBS_BeaconMeasElement_r13Tag
{
    UINT16  /* INTEGER (0..32767) */       transmitterID_r13;
    UINT32  /* INTEGER (0..2097151) */     codePhase_r13;
    UINT8  /* INTEGER (0..63) */           codePhaseRMSError_r13;
    INT16  /* INTEGER (-130..-30) */       rssi_r14;    /* OPTIONAL */
    UINT8                                  rssi_r14Present : 1;
    UINT8                                  reserved : 7;
}MBS_BeaconMeasElement_r13;


typedef struct MBS_BeaconMeasList_r13Tag
{
    MBS_BeaconMeasElement_r13                          data;
    struct MBS_BeaconMeasList_r13Tag                   *next;
}
MBS_BeaconMeasList_r13;


typedef struct TBS_MeasurementInformation_r13Tag
{
    UTCTime                                *measurementReferenceTime_r13;    /* OPTIONAL */
    MBS_BeaconMeasList_r13                 *mbs_SgnMeasList_r13;    /* OPTIONAL */
    UINT8                                  measurementReferenceTime_r13Present : 1;
    UINT8                                  mbs_SgnMeasList_r13Present : 1;
    UINT8                                  reserved : 6;
}TBS_MeasurementInformation_r13;


typedef struct TBS_ProvideLocationInformation_r13Tag
{
    TBS_MeasurementInformation_r13         *tbs_MeasurementInformation_r13;    /* OPTIONAL */
    TBS_Error_r13                          *tbs_Error_r13;    /* OPTIONAL */
    UINT8                                  tbs_MeasurementInformation_r13Present : 1;
    UINT8                                  tbs_Error_r13Present : 1;
    UINT8                                  reserved : 6;
}TBS_ProvideLocationInformation_r13;


typedef struct ECID_TargetDeviceErrorCausesTag
{
    enum ECID_TargetDeviceErrorCauses_cause {
        ECID_TargetDeviceErrorCauses_cause_undefined = 0,
        ECID_TargetDeviceErrorCauses_cause_requestedMeasurementNotAvailable = 1,
        ECID_TargetDeviceErrorCauses_cause_notAllrequestedMeasurementsPossible = 2
    } cause;
    UINT8                                  rsrpMeasurementNotPossible;    /* OPTIONAL */
    UINT8                                  rsrqMeasurementNotPossible;    /* OPTIONAL */
    UINT8                                  ueRxTxMeasurementNotPossible;    /* OPTIONAL */
    UINT8                                  nrsrpMeasurementNotPossible_r14;    /* OPTIONAL */
    UINT8                                  nrsrqMeasurementNotPossible_r14;    /* OPTIONAL */
    UINT8                                  rsrpMeasurementNotPossiblePresent : 1;
    UINT8                                  rsrqMeasurementNotPossiblePresent : 1;
    UINT8                                  ueRxTxMeasurementNotPossiblePresent : 1;
    UINT8                                  nrsrpMeasurementNotPossible_r14Present : 1;
    UINT8                                  nrsrqMeasurementNotPossible_r14Present : 1;
    UINT8                                  reserved : 3;
}ECID_TargetDeviceErrorCauses;


typedef struct ECID_LocationServerErrorCausesTag
{
    enum ECID_LocationServerErrorCauses_cause {
        ECID_LocationServerErrorCauses_cause_undefined = 0
    } cause;
}ECID_LocationServerErrorCauses;


typedef struct ECID_ErrorTag
{
    UINT8       tag;
        #define TAG_ECID_Error_locationServerErrorCauses 0
        #define TAG_ECID_Error_targetDeviceErrorCauses 1
    union {
        ECID_LocationServerErrorCauses         *locationServerErrorCauses;
        ECID_TargetDeviceErrorCauses           *targetDeviceErrorCauses;
    } choice;
}ECID_Error;


typedef struct ECID_RequestCapabilitiesTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}ECID_RequestCapabilities;


typedef struct ECID_ProvideCapabilitiesTag
{
    AsnBitString_MaxSize8                  ecid_MeasSupported;
    UINT8                                  ueRxTxSupTDD_r13Present : 1;
    UINT8                                  periodicalReporting_r14Present : 1;
    UINT8                                  triggeredReporting_r14Present : 1;
    UINT8                                  idleStateForMeasurements_r14Present : 1;
    UINT8                                  reserved : 4;
}ECID_ProvideCapabilities;


typedef struct ECID_RequestLocationInformationTag
{
    AsnBitString_MaxSize8                  requestedMeasurements;
}ECID_RequestLocationInformation;


typedef struct CellGlobalIdEUTRA_AndUTRA_mccTag
{
    /* SEQUENCE (SIZE (3)) OF */
    UINT8  /* INTEGER(0..9) */                         data[3];
}
CellGlobalIdEUTRA_AndUTRA_mcc;


typedef struct CellGlobalIdEUTRA_AndUTRA_mncTag
{
    UINT16 n;  /* SEQUENCE (SIZE (2..3)) OF  */
    UINT8  /* INTEGER(0..9) */                         data[3];
}
CellGlobalIdEUTRA_AndUTRA_mnc;


typedef struct CellGlobalIdEUTRA_AndUTRA_plmn_IdentityTag
{
    CellGlobalIdEUTRA_AndUTRA_mcc          mcc;
    CellGlobalIdEUTRA_AndUTRA_mnc          mnc;
}CellGlobalIdEUTRA_AndUTRA_plmn_Identity;


typedef struct CellGlobalIdEUTRA_AndUTRATag
{
    CellGlobalIdEUTRA_AndUTRA_plmn_Identity plmn_Identity;
    struct CellGlobalIdEUTRA_AndUTRA_cellIdentity {
        UINT8       tag;
            #define TAG_CellGlobalIdEUTRA_AndUTRA_cellIdentity_eutra 0
            #define TAG_CellGlobalIdEUTRA_AndUTRA_cellIdentity_utra 1
        union {
            UINT32  /* BIT STRING (SIZE(28)) */    eutra;
            UINT32  /* BIT STRING (SIZE(32)) */    utra;
        } choice;
    } cellIdentity;
}CellGlobalIdEUTRA_AndUTRA;


typedef enum CarrierFreqOffsetNB_r14Tag
{
    CarrierFreqOffsetNB_r14_v_10 = 0,
    CarrierFreqOffsetNB_r14_v_9 = 1,
    CarrierFreqOffsetNB_r14_v_8 = 2,
    CarrierFreqOffsetNB_r14_v_7 = 3,
    CarrierFreqOffsetNB_r14_v_6 = 4,
    CarrierFreqOffsetNB_r14_v_5 = 5,
    CarrierFreqOffsetNB_r14_v_4 = 6,
    CarrierFreqOffsetNB_r14_v_3 = 7,
    CarrierFreqOffsetNB_r14_v_2 = 8,
    CarrierFreqOffsetNB_r14_v_1 = 9,
    CarrierFreqOffsetNB_r14_v_0dot5 = 10,
    CarrierFreqOffsetNB_r14_v0 = 11,
    CarrierFreqOffsetNB_r14_v1 = 12,
    CarrierFreqOffsetNB_r14_v2 = 13,
    CarrierFreqOffsetNB_r14_v3 = 14,
    CarrierFreqOffsetNB_r14_v4 = 15,
    CarrierFreqOffsetNB_r14_v5 = 16,
    CarrierFreqOffsetNB_r14_v6 = 17,
    CarrierFreqOffsetNB_r14_v7 = 18,
    CarrierFreqOffsetNB_r14_v8 = 19,
    CarrierFreqOffsetNB_r14_v9 = 20
}CarrierFreqOffsetNB_r14;


typedef struct MeasuredResultsElementTag
{
    UINT16  /* INTEGER (0..503) */         physCellId;
    CellGlobalIdEUTRA_AndUTRA              *cellGlobalId;    /* OPTIONAL */
    ARFCN_ValueEUTRA                       arfcnEUTRA;
    UINT16  /* BIT STRING (SIZE(10)) */    systemFrameNumber;    /* OPTIONAL */
    UINT8  /* INTEGER (0..97) */           rsrp_Result;    /* OPTIONAL */
    UINT8  /* INTEGER (0..34) */           rsrq_Result;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        ue_RxTxTimeDiff;    /* OPTIONAL */
    ARFCN_ValueEUTRA_v9a0                  arfcnEUTRA_v9a0;    /* OPTIONAL */
    UINT8  /* INTEGER (0..113) */          nrsrp_Result_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (0..74) */           nrsrq_Result_r14;    /* OPTIONAL */
    CarrierFreqOffsetNB_r14                carrierFreqOffsetNB_r14;    /* OPTIONAL */
    UINT16  /* BIT STRING (SIZE(10)) */    hyperSFN_r14;    /* OPTIONAL */
    INT8  /* INTEGER (-17..-1) */          rsrp_Result_v1470;    /* OPTIONAL */
    INT8  /* INTEGER (-30..46) */          rsrq_Result_v1470;    /* OPTIONAL */
    UINT16                                 cellGlobalIdPresent : 1;
    UINT16                                 systemFrameNumberPresent : 1;
    UINT16                                 rsrp_ResultPresent : 1;
    UINT16                                 rsrq_ResultPresent : 1;
    UINT16                                 ue_RxTxTimeDiffPresent : 1;
    UINT16                                 arfcnEUTRA_v9a0Present : 1;
    UINT16                                 nrsrp_Result_r14Present : 1;
    UINT16                                 nrsrq_Result_r14Present : 1;
    UINT16                                 carrierFreqOffsetNB_r14Present : 1;
    UINT16                                 hyperSFN_r14Present : 1;
    UINT16                                 rsrp_Result_v1470Present : 1;
    UINT16                                 rsrq_Result_v1470Present : 1;
    UINT16                                 reserved : 4;
}MeasuredResultsElement;


typedef struct MeasuredResultsListTag
{
    MeasuredResultsElement                             data;
    struct MeasuredResultsListTag                      *next;
}
MeasuredResultsList;


typedef struct ECID_SignalMeasurementInformationTag
{
    MeasuredResultsElement                 *primaryCellMeasuredResults;    /* OPTIONAL */
    MeasuredResultsList                    measuredResultsList;
    UINT8                                  primaryCellMeasuredResultsPresent : 1;
    UINT8                                  reserved : 7;
}ECID_SignalMeasurementInformation;


typedef struct ECID_ProvideLocationInformationTag
{
    ECID_SignalMeasurementInformation      *ecid_SignalMeasurementInformation;    /* OPTIONAL */
    ECID_Error                             *ecid_Error;    /* OPTIONAL */
    UINT8                                  ecid_SignalMeasurementInformationPresent : 1;
    UINT8                                  ecid_ErrorPresent : 1;
    UINT8                                  reserved : 6;
}ECID_ProvideLocationInformation;


typedef struct SV_IDTag
{
    UINT8  /* INTEGER (0..63) */           satellite_id;
}SV_ID;


typedef struct SBAS_IDsTag
{
    AsnBitString_MaxSize8                  sbas_IDs;
}SBAS_IDs;


typedef struct SBAS_IDTag
{
    enum SBAS_ID_sbas_id {
        SBAS_ID_sbas_id_waas = 0,
        SBAS_ID_sbas_id_egnos = 1,
        SBAS_ID_sbas_id_msas = 2,
        SBAS_ID_sbas_id_gagan = 3
    } sbas_id;
}SBAS_ID;


typedef struct GNSS_SignalIDsTag
{
    UINT8  /* BIT STRING (SIZE(8)) */      gnss_SignalIDs;
}GNSS_SignalIDs;


typedef struct GNSS_SignalIDTag
{
    UINT8  /* INTEGER (0..7) */            gnss_SignalID;
}GNSS_SignalID;


typedef struct GNSS_ID_BitmapTag
{
    AsnBitString_MaxSize16                 gnss_ids;
}GNSS_ID_Bitmap;


typedef struct GNSS_IDTag
{
    enum GNSS_ID_gnss_id {
        GNSS_ID_gnss_id_gps = 0,
        GNSS_ID_gnss_id_sbas = 1,
        GNSS_ID_gnss_id_qzss = 2,
        GNSS_ID_gnss_id_galileo = 3,
        GNSS_ID_gnss_id_glonass = 4,
        GNSS_ID_gnss_id_bds = 5
    } gnss_id;
}GNSS_ID;


typedef struct GNSS_TargetDeviceErrorCausesTag
{
    enum GNSS_TargetDeviceErrorCauses_cause {
        GNSS_TargetDeviceErrorCauses_cause_undefined = 0,
        GNSS_TargetDeviceErrorCauses_cause_thereWereNotEnoughSatellitesReceived = 1,
        GNSS_TargetDeviceErrorCauses_cause_assistanceDataMissing = 2,
        GNSS_TargetDeviceErrorCauses_cause_notAllRequestedMeasurementsPossible = 3
    } cause;
    UINT8                                  fineTimeAssistanceMeasurementsNotPossible;    /* OPTIONAL */
    UINT8                                  adrMeasurementsNotPossible;    /* OPTIONAL */
    UINT8                                  multiFrequencyMeasurementsNotPossible;    /* OPTIONAL */
    UINT8                                  fineTimeAssistanceMeasurementsNotPossiblePresent : 1;
    UINT8                                  adrMeasurementsNotPossiblePresent : 1;
    UINT8                                  multiFrequencyMeasurementsNotPossiblePresent : 1;
    UINT8                                  reserved : 5;
}GNSS_TargetDeviceErrorCauses;


typedef struct GNSS_LocationServerErrorCausesTag
{
    enum GNSS_LocationServerErrorCauses_cause {
        GNSS_LocationServerErrorCauses_cause_undefined = 0,
        GNSS_LocationServerErrorCauses_cause_undeliveredAssistanceDataIsNotSupportedByServer = 1,
        GNSS_LocationServerErrorCauses_cause_undeliveredAssistanceDataIsSupportedButCurrentlyNotAvailableByServer = 2,
        GNSS_LocationServerErrorCauses_cause_undeliveredAssistanceDataIsPartlyNotSupportedAndPartlyNotAvailableByServer = 3
    } cause;
}GNSS_LocationServerErrorCauses;


typedef struct A_GNSS_ErrorTag
{
    UINT8       tag;
        #define TAG_A_GNSS_Error_locationServerErrorCauses 0
        #define TAG_A_GNSS_Error_targetDeviceErrorCauses 1
    union {
        GNSS_LocationServerErrorCauses         *locationServerErrorCauses;
        GNSS_TargetDeviceErrorCauses           *targetDeviceErrorCauses;
    } choice;
}A_GNSS_Error;


typedef struct A_GNSS_RequestCapabilitiesTag
{
    BOOL                                   gnss_SupportListReq;
    BOOL                                   assistanceDataSupportListReq;
    BOOL                                   locationVelocityTypesReq;
}A_GNSS_RequestCapabilities;


typedef struct BDS_GridModelSupport_r12Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}BDS_GridModelSupport_r12;


typedef struct BDS_DifferentialCorrectionsSupport_r12Tag
{
    GNSS_SignalIDs                         gnssSignalIDs;
}BDS_DifferentialCorrectionsSupport_r12;


typedef struct GNSS_AuxiliaryInformationSupportTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_AuxiliaryInformationSupport;


typedef struct GNSS_UTC_ModelSupportTag
{
    AsnBitString_MaxSize8                  *utc_Model;    /* OPTIONAL */
    UINT8                                  utc_ModelPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_UTC_ModelSupport;


typedef struct GNSS_AlmanacSupportTag
{
    AsnBitString_MaxSize8                  *almanacModel;    /* OPTIONAL */
    UINT8                                  almanacModelPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_AlmanacSupport;


typedef struct GNSS_AcquisitionAssistanceSupportTag
{
    UINT8                                  confidenceSupport_r10Present : 1;
    UINT8                                  dopplerUncertaintyExtSupport_r10Present : 1;
    UINT8                                  reserved : 6;
}GNSS_AcquisitionAssistanceSupport;


typedef struct GNSS_DataBitAssistanceSupportTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_DataBitAssistanceSupport;


typedef struct GNSS_RealTimeIntegritySupportTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_RealTimeIntegritySupport;


typedef struct GNSS_NavigationModelSupportTag
{
    AsnBitString_MaxSize8                  *clockModel;    /* OPTIONAL */
    AsnBitString_MaxSize8                  *orbitModel;    /* OPTIONAL */
    UINT8                                  clockModelPresent : 1;
    UINT8                                  orbitModelPresent : 1;
    UINT8                                  reserved : 6;
}GNSS_NavigationModelSupport;


typedef struct GNSS_DifferentialCorrectionsSupportTag
{
    GNSS_SignalIDs                         gnssSignalIDs;
    BOOL                                   dgnss_ValidityTimeSup;
}GNSS_DifferentialCorrectionsSupport;


typedef struct GNSS_TimeModelListSupportTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_TimeModelListSupport;


typedef struct GNSS_GenericAssistDataSupportElementTag
{
    GNSS_ID                                gnss_ID;
    SBAS_ID                                *sbas_ID;    /* OPTIONAL */
    GNSS_TimeModelListSupport              *gnss_TimeModelsSupport;    /* OPTIONAL */
    GNSS_DifferentialCorrectionsSupport    *gnss_DifferentialCorrectionsSupport;    /* OPTIONAL */
    GNSS_NavigationModelSupport            *gnss_NavigationModelSupport;    /* OPTIONAL */
    GNSS_RealTimeIntegritySupport          *gnss_RealTimeIntegritySupport;    /* OPTIONAL */
    GNSS_DataBitAssistanceSupport          *gnss_DataBitAssistanceSupport;    /* OPTIONAL */
    GNSS_AcquisitionAssistanceSupport      *gnss_AcquisitionAssistanceSupport;    /* OPTIONAL */
    GNSS_AlmanacSupport                    *gnss_AlmanacSupport;    /* OPTIONAL */
    GNSS_UTC_ModelSupport                  *gnss_UTC_ModelSupport;    /* OPTIONAL */
    GNSS_AuxiliaryInformationSupport       *gnss_AuxiliaryInformationSupport;    /* OPTIONAL */
    BDS_DifferentialCorrectionsSupport_r12 *bds_DifferentialCorrectionsSupport_r12;    /* OPTIONAL */
    BDS_GridModelSupport_r12               *bds_GridModelSupport_r12;    /* OPTIONAL */
    UINT16                                 sbas_IDPresent : 1;
    UINT16                                 gnss_TimeModelsSupportPresent : 1;
    UINT16                                 gnss_DifferentialCorrectionsSupportPresent : 1;
    UINT16                                 gnss_NavigationModelSupportPresent : 1;
    UINT16                                 gnss_RealTimeIntegritySupportPresent : 1;
    UINT16                                 gnss_DataBitAssistanceSupportPresent : 1;
    UINT16                                 gnss_AcquisitionAssistanceSupportPresent : 1;
    UINT16                                 gnss_AlmanacSupportPresent : 1;
    UINT16                                 gnss_UTC_ModelSupportPresent : 1;
    UINT16                                 gnss_AuxiliaryInformationSupportPresent : 1;
    UINT16                                 bds_DifferentialCorrectionsSupport_r12Present : 1;
    UINT16                                 bds_GridModelSupport_r12Present : 1;
    UINT16                                 reserved : 4;
}GNSS_GenericAssistDataSupportElement;


typedef struct GNSS_GenericAssistanceDataSupportTag
{
    GNSS_GenericAssistDataSupportElement               data;
    struct GNSS_GenericAssistanceDataSupportTag        *next;
}
GNSS_GenericAssistanceDataSupport;


typedef struct GNSS_EarthOrientationParametersSupportTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_EarthOrientationParametersSupport;


typedef struct GNSS_IonosphericModelSupportTag
{
    AsnBitString_MaxSize8                  ionoModel;
}GNSS_IonosphericModelSupport;


typedef struct GNSS_ReferenceLocationSupportTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_ReferenceLocationSupport;


typedef struct AccessTypesTag
{
    AsnBitString_MaxSize8                  accessTypes;
}AccessTypes;


typedef struct GNSS_ReferenceTimeSupportTag
{
    GNSS_ID_Bitmap                         gnss_SystemTime;
    AccessTypes                            *fta_Support;    /* OPTIONAL */
    UINT8                                  fta_SupportPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_ReferenceTimeSupport;


typedef struct GNSS_CommonAssistanceDataSupportTag
{
    GNSS_ReferenceTimeSupport              *gnss_ReferenceTimeSupport;    /* OPTIONAL */
    GNSS_ReferenceLocationSupport          *gnss_ReferenceLocationSupport;    /* OPTIONAL */
    GNSS_IonosphericModelSupport           *gnss_IonosphericModelSupport;    /* OPTIONAL */
    GNSS_EarthOrientationParametersSupport *gnss_EarthOrientationParametersSupport;    /* OPTIONAL */
    UINT8                                  gnss_ReferenceTimeSupportPresent : 1;
    UINT8                                  gnss_ReferenceLocationSupportPresent : 1;
    UINT8                                  gnss_IonosphericModelSupportPresent : 1;
    UINT8                                  gnss_EarthOrientationParametersSupportPresent : 1;
    UINT8                                  reserved : 4;
}GNSS_CommonAssistanceDataSupport;


typedef struct AssistanceDataSupportListTag
{
    GNSS_CommonAssistanceDataSupport       gnss_CommonAssistanceDataSupport;
    GNSS_GenericAssistanceDataSupport      gnss_GenericAssistanceDataSupport;
}AssistanceDataSupportList;


typedef struct GNSS_SupportElement_fta_MeasSupportTag
{
    AccessTypes                            cellTime;
    PositioningModes                       mode;
}GNSS_SupportElement_fta_MeasSupport;


typedef struct GNSS_SupportElementTag
{
    GNSS_ID                                gnss_ID;
    SBAS_IDs                               *sbas_IDs;    /* OPTIONAL */
    PositioningModes                       agnss_Modes;
    GNSS_SignalIDs                         gnss_Signals;
    GNSS_SupportElement_fta_MeasSupport    *fta_MeasSupport;    /* OPTIONAL */
    BOOL                                   adr_Support;
    BOOL                                   velocityMeasurementSupport;
    UINT8                                  sbas_IDsPresent : 1;
    UINT8                                  fta_MeasSupportPresent : 1;
    UINT8                                  reserved : 6;
}GNSS_SupportElement;


typedef struct GNSS_SupportListTag
{
    GNSS_SupportElement                                data;
    struct GNSS_SupportListTag                         *next;
}
GNSS_SupportList;


typedef struct LocationCoordinateTypesTag
{
    BOOL                                   ellipsoidPoint;
    BOOL                                   ellipsoidPointWithUncertaintyCircle;
    BOOL                                   ellipsoidPointWithUncertaintyEllipse;
    BOOL                                   polygon;
    BOOL                                   ellipsoidPointWithAltitude;
    BOOL                                   ellipsoidPointWithAltitudeAndUncertaintyEllipsoid;
    BOOL                                   ellipsoidArc;
}LocationCoordinateTypes;


typedef struct VelocityTypesTag
{
    BOOL                                   horizontalVelocity;
    BOOL                                   horizontalWithVerticalVelocity;
    BOOL                                   horizontalVelocityWithUncertainty;
    BOOL                                   horizontalWithVerticalVelocityAndUncertainty;
}VelocityTypes;


typedef struct A_GNSS_ProvideCapabilitiesTag
{
    GNSS_SupportList                       *gnss_SupportList;    /* OPTIONAL */
    AssistanceDataSupportList              *assistanceDataSupportList;    /* OPTIONAL */
    LocationCoordinateTypes                *locationCoordinateTypes;    /* OPTIONAL */
    VelocityTypes                          *velocityTypes;    /* OPTIONAL */
    PositioningModes                       *periodicalReportingNotSupported_r14;    /* OPTIONAL */
    UINT8                                  gnss_SupportListPresent : 1;
    UINT8                                  assistanceDataSupportListPresent : 1;
    UINT8                                  locationCoordinateTypesPresent : 1;
    UINT8                                  velocityTypesPresent : 1;
    UINT8                                  periodicalReportingNotSupported_r14Present : 1;
    UINT8                                  idleStateForMeasurements_r14Present : 1;
    UINT8                                  reserved : 2;
}A_GNSS_ProvideCapabilities;


typedef struct GNSS_PositioningInstructionsTag
{
    GNSS_ID_Bitmap                         gnss_Methods;
    BOOL                                   fineTimeAssistanceMeasReq;
    BOOL                                   adrMeasReq;
    BOOL                                   multiFreqMeasReq;
    BOOL                                   assistanceAvailability;
}GNSS_PositioningInstructions;


typedef struct A_GNSS_RequestLocationInformationTag
{
    GNSS_PositioningInstructions           gnss_PositioningInstructions;
}A_GNSS_RequestLocationInformation;


typedef struct MeasurementReferenceTime_eUTRATag
{
    UINT16  /* INTEGER (0..503) */         physCellId;
    CellGlobalIdEUTRA_AndUTRA              *cellGlobalId;    /* OPTIONAL */
    UINT16  /* BIT STRING (SIZE(10)) */    systemFrameNumber;
    UINT8                                  cellGlobalIdPresent : 1;
    UINT8                                  reserved : 7;
}MeasurementReferenceTime_eUTRA;


typedef struct MeasurementReferenceTime_fddTag
{
    UINT16  /* INTEGER (0..511) */         primary_CPICH_Info;
}MeasurementReferenceTime_fdd;


typedef struct MeasurementReferenceTime_tddTag
{
    UINT8  /* INTEGER (0..127) */          cellParameters;
}MeasurementReferenceTime_tdd;


typedef struct MeasurementReferenceTime_uTRATag
{
    struct MeasurementReferenceTime_mode {
        UINT8       tag;
            #define TAG_MeasurementReferenceTime_mode_fdd 0
            #define TAG_MeasurementReferenceTime_mode_tdd 1
        union {
            MeasurementReferenceTime_fdd           *fdd;
            MeasurementReferenceTime_tdd           *tdd;
        } choice;
    } mode;
    CellGlobalIdEUTRA_AndUTRA              *cellGlobalId;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        referenceSystemFrameNumber;
    UINT8                                  cellGlobalIdPresent : 1;
    UINT8                                  reserved : 7;
}MeasurementReferenceTime_uTRA;


typedef struct CellGlobalIdGERAN_LPP_mccTag
{
    /* SEQUENCE (SIZE (3)) OF */
    UINT8  /* INTEGER(0..9) */                         data[3];
}
CellGlobalIdGERAN_LPP_mcc;


typedef struct CellGlobalIdGERAN_LPP_mncTag
{
    UINT16 n;  /* SEQUENCE (SIZE (2..3)) OF  */
    UINT8  /* INTEGER(0..9) */                         data[3];
}
CellGlobalIdGERAN_LPP_mnc;


typedef struct CellGlobalIdGERAN_LPP_plmn_IdentityTag
{
    CellGlobalIdGERAN_LPP_mcc              mcc;
    CellGlobalIdGERAN_LPP_mnc              mnc;
}CellGlobalIdGERAN_LPP_plmn_Identity;


typedef struct CellGlobalIdGERAN_LPPTag
{
    CellGlobalIdGERAN_LPP_plmn_Identity    plmn_Identity;
    UINT16  /* BIT STRING (SIZE(16)) */    locationAreaCode;
    UINT16  /* BIT STRING (SIZE(16)) */    cellIdentity;
}CellGlobalIdGERAN_LPP;


typedef struct MeasurementReferenceTime_referenceFrameTag
{
    UINT16  /* INTEGER (0..65535) */       referenceFN;
    UINT8  /* INTEGER (0..63) */           referenceFNMSB;    /* OPTIONAL */
    UINT8                                  referenceFNMSBPresent : 1;
    UINT8                                  reserved : 7;
}MeasurementReferenceTime_referenceFrame;


typedef struct MeasurementReferenceTime_gSMTag
{
    UINT16  /* INTEGER (0..1023) */        bcchCarrier;
    UINT8  /* INTEGER (0..63) */           bsic;
    CellGlobalIdGERAN_LPP                  *cellGlobalId;    /* OPTIONAL */
    MeasurementReferenceTime_referenceFrame referenceFrame;
    UINT8  /* INTEGER (0..127) */          deltaGNSS_TOD;    /* OPTIONAL */
    UINT8                                  cellGlobalIdPresent : 1;
    UINT8                                  deltaGNSS_TODPresent : 1;
    UINT8                                  reserved : 6;
}MeasurementReferenceTime_gSM;


typedef struct ECGI_mccTag
{
    /* SEQUENCE (SIZE (3)) OF */
    UINT8  /* INTEGER(0..9) */                         data[3];
}
ECGI_mcc;


typedef struct ECGI_mncTag
{
    UINT16 n;  /* SEQUENCE (SIZE (2..3)) OF  */
    UINT8  /* INTEGER(0..9) */                         data[3];
}
ECGI_mnc;


typedef struct ECGITag
{
    ECGI_mcc                               mcc;
    ECGI_mnc                               mnc;
    UINT32  /* BIT STRING (SIZE(28)) */    cellidentity;
}ECGI;


typedef struct MeasurementReferenceTime_nbIoT_r14Tag
{
    UINT16  /* INTEGER (0..503) */         nbPhysCellId_r14;
    ECGI                                   *nbCellGlobalId_r14;    /* OPTIONAL */
    UINT16  /* BIT STRING (SIZE(10)) */    sfn_r14;
    UINT16  /* BIT STRING (SIZE(10)) */    hyperSFN_r14;    /* OPTIONAL */
    UINT8                                  nbCellGlobalId_r14Present : 1;
    UINT8                                  hyperSFN_r14Present : 1;
    UINT8                                  reserved : 6;
}MeasurementReferenceTime_nbIoT_r14;


typedef struct MeasurementReferenceTime_networkTimeTag
{
    UINT8       tag;
        #define TAG_MeasurementReferenceTime_networkTime_eUTRA 0
        #define TAG_MeasurementReferenceTime_networkTime_uTRA 1
        #define TAG_MeasurementReferenceTime_networkTime_gSM 2
        #define TAG_MeasurementReferenceTime_networkTime_nbIoT_r14 3
    union {
        MeasurementReferenceTime_eUTRA         *eUTRA;
        MeasurementReferenceTime_uTRA          *uTRA;
        MeasurementReferenceTime_gSM           *gSM;
        MeasurementReferenceTime_nbIoT_r14     *nbIoT_r14;
    } choice;
}MeasurementReferenceTime_networkTime;


typedef struct MeasurementReferenceTimeTag
{
    UINT32  /* INTEGER (0..3599999) */     gnss_TOD_msec;
    UINT16  /* INTEGER (0..3999) */        gnss_TOD_frac;    /* OPTIONAL */
    UINT8  /* INTEGER (0..127) */          gnss_TOD_unc;    /* OPTIONAL */
    GNSS_ID                                gnss_TimeID;
    MeasurementReferenceTime_networkTime   *networkTime;    /* OPTIONAL */
    UINT8                                  gnss_TOD_fracPresent : 1;
    UINT8                                  gnss_TOD_uncPresent : 1;
    UINT8                                  networkTimePresent : 1;
    UINT8                                  reserved : 5;
}MeasurementReferenceTime;


typedef struct GNSS_LocationInformationTag
{
    MeasurementReferenceTime               measurementReferenceTime;
    GNSS_ID_Bitmap                         agnss_List;
}GNSS_LocationInformation;


typedef struct GNSS_SatMeasElementTag
{
    SV_ID                                  svID;
    UINT8  /* INTEGER (0..63) */           cNo;
    enum GNSS_SatMeasElement_mpathDet {
        GNSS_SatMeasElement_mpathDet_notMeasured = 0,
        GNSS_SatMeasElement_mpathDet_low = 1,
        GNSS_SatMeasElement_mpathDet_medium = 2,
        GNSS_SatMeasElement_mpathDet_high = 3
    } mpathDet;
    UINT8  /* INTEGER (0..3) */            carrierQualityInd;    /* OPTIONAL */
    UINT32  /* INTEGER (0..2097151) */     codePhase;
    UINT8  /* INTEGER (0..127) */          integerCodePhase;    /* OPTIONAL */
    UINT8  /* INTEGER (0..63) */           codePhaseRMSError;
    INT16  /* INTEGER (-32768..32767) */   doppler;    /* OPTIONAL */
    UINT32  /* INTEGER (0..33554431) */    adr;    /* OPTIONAL */
    UINT8                                  carrierQualityIndPresent : 1;
    UINT8                                  integerCodePhasePresent : 1;
    UINT8                                  dopplerPresent : 1;
    UINT8                                  adrPresent : 1;
    UINT8                                  reserved : 4;
}GNSS_SatMeasElement;


typedef struct GNSS_SatMeasListTag
{
    GNSS_SatMeasElement                                data;
    struct GNSS_SatMeasListTag                         *next;
}
GNSS_SatMeasList;


typedef struct GNSS_SgnMeasElementTag
{
    GNSS_SignalID                          gnss_SignalID;
    UINT8  /* INTEGER (0..127) */          gnss_CodePhaseAmbiguity;    /* OPTIONAL */
    GNSS_SatMeasList                       gnss_SatMeasList;
    UINT8                                  gnss_CodePhaseAmbiguityPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_SgnMeasElement;


typedef struct GNSS_SgnMeasListTag
{
    GNSS_SgnMeasElement                                data;
    struct GNSS_SgnMeasListTag                         *next;
}
GNSS_SgnMeasList;


typedef struct GNSS_MeasurementForOneGNSSTag
{
    GNSS_ID                                gnss_ID;
    GNSS_SgnMeasList                       gnss_SgnMeasList;
}GNSS_MeasurementForOneGNSS;


typedef struct GNSS_MeasurementListTag
{
    GNSS_MeasurementForOneGNSS                         data;
    struct GNSS_MeasurementListTag                     *next;
}
GNSS_MeasurementList;


typedef struct GNSS_SignalMeasurementInformationTag
{
    MeasurementReferenceTime               measurementReferenceTime;
    GNSS_MeasurementList                   gnss_MeasurementList;
}GNSS_SignalMeasurementInformation;


typedef struct A_GNSS_ProvideLocationInformationTag
{
    GNSS_SignalMeasurementInformation      *gnss_SignalMeasurementInformation;    /* OPTIONAL */
    GNSS_LocationInformation               *gnss_LocationInformation;    /* OPTIONAL */
    A_GNSS_Error                           *gnss_Error;    /* OPTIONAL */
    UINT8                                  gnss_SignalMeasurementInformationPresent : 1;
    UINT8                                  gnss_LocationInformationPresent : 1;
    UINT8                                  gnss_ErrorPresent : 1;
    UINT8                                  reserved : 5;
}A_GNSS_ProvideLocationInformation;


typedef struct BDS_GridModelReq_r12Tag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}BDS_GridModelReq_r12;


typedef struct BDS_DifferentialCorrectionsReq_r12Tag
{
    GNSS_SignalIDs                         dgnss_SignalsReq;
}BDS_DifferentialCorrectionsReq_r12;


typedef struct GNSS_AuxiliaryInformationReqTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_AuxiliaryInformationReq;


typedef struct GNSS_UTC_ModelReqTag
{
    UINT8  /* INTEGER (1..8) */            modelID;    /* OPTIONAL */
    UINT8                                  modelIDPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_UTC_ModelReq;


typedef struct GNSS_AlmanacReqTag
{
    UINT8  /* INTEGER (1..8) */            modelID;    /* OPTIONAL */
    UINT8                                  modelIDPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_AlmanacReq;


typedef struct GNSS_AcquisitionAssistanceReqTag
{
    GNSS_SignalID                          gnss_SignalID_Req;
}GNSS_AcquisitionAssistanceReq;


typedef struct GNSS_DataBitsReqSatElementTag
{
    SV_ID                                  svID;
}GNSS_DataBitsReqSatElement;


typedef struct GNSS_DataBitsReqSatListTag
{
    GNSS_DataBitsReqSatElement                         data;
    struct GNSS_DataBitsReqSatListTag                  *next;
}
GNSS_DataBitsReqSatList;


typedef struct GNSS_DataBitAssistanceReqTag
{
    UINT16  /* INTEGER (0..3599) */        gnss_TOD_Req;
    UINT16  /* INTEGER (0..999) */         gnss_TOD_FracReq;    /* OPTIONAL */
    UINT8  /* INTEGER (0..15) */           dataBitInterval;
    GNSS_SignalIDs                         gnss_SignalType;
    GNSS_DataBitsReqSatList                *gnss_DataBitsReq;    /* OPTIONAL */
    UINT8                                  gnss_TOD_FracReqPresent : 1;
    UINT8                                  gnss_DataBitsReqPresent : 1;
    UINT8                                  reserved : 6;
}GNSS_DataBitAssistanceReq;


typedef struct GNSS_RealTimeIntegrityReqTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_RealTimeIntegrityReq;


typedef struct ReqNavListInfo_orbitModelID_PrefListTag
{
    UINT16 n;  /* SEQUENCE (SIZE (1..8)) OF  */
    UINT8  /* INTEGER(1..8) */                         data[8];
}
ReqNavListInfo_orbitModelID_PrefList;


typedef struct ReqNavListInfo_clockModelID_PrefListTag
{
    UINT16 n;  /* SEQUENCE (SIZE (1..8)) OF  */
    UINT8  /* INTEGER(1..8) */                         data[8];
}
ReqNavListInfo_clockModelID_PrefList;


typedef struct ReqNavListInfoTag
{
    AsnBitString_64                        svReqList;
    ReqNavListInfo_clockModelID_PrefList   *clockModelID_PrefList;    /* OPTIONAL */
    ReqNavListInfo_orbitModelID_PrefList   *orbitModelID_PrefList;    /* OPTIONAL */
    BOOL                                   addNavparamReq;    /* OPTIONAL */
    UINT8                                  clockModelID_PrefListPresent : 1;
    UINT8                                  orbitModelID_PrefListPresent : 1;
    UINT8                                  addNavparamReqPresent : 1;
    UINT8                                  reserved : 5;
}ReqNavListInfo;


typedef struct SatListRelatedDataElementTag
{
    SV_ID                                  svID;
    UINT16  /* BIT STRING (SIZE(11)) */    iod;
    UINT8  /* INTEGER (1..8) */            clockModelID;    /* OPTIONAL */
    UINT8  /* INTEGER (1..8) */            orbitModelID;    /* OPTIONAL */
    UINT8                                  clockModelIDPresent : 1;
    UINT8                                  orbitModelIDPresent : 1;
    UINT8                                  reserved : 6;
}SatListRelatedDataElement;


typedef struct SatListRelatedDataListTag
{
    SatListRelatedDataElement                          data;
    struct SatListRelatedDataListTag                   *next;
}
SatListRelatedDataList;


typedef struct StoredNavListInfoTag
{
    UINT16  /* INTEGER (0..4095) */        gnss_WeekOrDay;
    UINT8  /* INTEGER (0..255) */          gnss_Toe;
    UINT8  /* INTEGER (0..15) */           t_toeLimit;
    SatListRelatedDataList                 *satListRelatedDataList;    /* OPTIONAL */
    UINT8                                  satListRelatedDataListPresent : 1;
    UINT8                                  reserved : 7;
}StoredNavListInfo;


typedef struct GNSS_NavigationModelReqTag
{
    UINT8       tag;
        #define TAG_GNSS_NavigationModelReq_storedNavList 0
        #define TAG_GNSS_NavigationModelReq_reqNavList 1
    union {
        StoredNavListInfo                      *storedNavList;
        ReqNavListInfo                         *reqNavList;
    } choice;
}GNSS_NavigationModelReq;


typedef struct GNSS_DifferentialCorrectionsReqTag
{
    GNSS_SignalIDs                         dgnss_SignalsReq;
    BOOL                                   dgnss_ValidityTimeReq;
}GNSS_DifferentialCorrectionsReq;


typedef struct GNSS_TimeModelElementReqTag
{
    UINT8  /* INTEGER (1..15) */           gnss_TO_IDsReq;
    BOOL                                   deltaTreq;
}GNSS_TimeModelElementReq;


typedef struct GNSS_TimeModelListReqTag
{
    GNSS_TimeModelElementReq                           data;
    struct GNSS_TimeModelListReqTag                    *next;
}
GNSS_TimeModelListReq;


typedef struct GNSS_EarthOrientationParametersReqTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_EarthOrientationParametersReq;


typedef struct GNSS_IonosphericModelReqTag
{
    UINT8  /* BIT STRING (SIZE(2)) */      klobucharModelReq;    /* OPTIONAL */
    UINT8                                  neQuickModelReq;    /* OPTIONAL */
    UINT8                                  klobucharModelReqPresent : 1;
    UINT8                                  neQuickModelReqPresent : 1;
    UINT8                                  reserved : 6;
}GNSS_IonosphericModelReq;


typedef struct GNSS_ReferenceLocationReqTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}GNSS_ReferenceLocationReq;


typedef struct GNSS_ReferenceTimeReq_gnss_TimeReqPrefListTag
{
    GNSS_ID                                            data;
    struct GNSS_ReferenceTimeReq_gnss_TimeReqPrefListTag *next;
}
GNSS_ReferenceTimeReq_gnss_TimeReqPrefList;


typedef struct GNSS_ReferenceTimeReqTag
{
    GNSS_ReferenceTimeReq_gnss_TimeReqPrefList gnss_TimeReqPrefList;
    BOOL                                   gps_TOW_assistReq;    /* OPTIONAL */
    BOOL                                   notOfLeapSecReq;    /* OPTIONAL */
    UINT8                                  gps_TOW_assistReqPresent : 1;
    UINT8                                  notOfLeapSecReqPresent : 1;
    UINT8                                  reserved : 6;
}GNSS_ReferenceTimeReq;


typedef struct GNSS_GenericAssistDataReqElementTag
{
    GNSS_ID                                gnss_ID;
    SBAS_ID                                *sbas_ID;    /* OPTIONAL */
    GNSS_TimeModelListReq                  *gnss_TimeModelsReq;    /* OPTIONAL */
    GNSS_DifferentialCorrectionsReq        *gnss_DifferentialCorrectionsReq;    /* OPTIONAL */
    GNSS_NavigationModelReq                *gnss_NavigationModelReq;    /* OPTIONAL */
    GNSS_RealTimeIntegrityReq              *gnss_RealTimeIntegrityReq;    /* OPTIONAL */
    GNSS_DataBitAssistanceReq              *gnss_DataBitAssistanceReq;    /* OPTIONAL */
    GNSS_AcquisitionAssistanceReq          *gnss_AcquisitionAssistanceReq;    /* OPTIONAL */
    GNSS_AlmanacReq                        *gnss_AlmanacReq;    /* OPTIONAL */
    GNSS_UTC_ModelReq                      *gnss_UTCModelReq;    /* OPTIONAL */
    GNSS_AuxiliaryInformationReq           *gnss_AuxiliaryInformationReq;    /* OPTIONAL */
    BDS_DifferentialCorrectionsReq_r12     *bds_DifferentialCorrectionsReq_r12;    /* OPTIONAL */
    BDS_GridModelReq_r12                   *bds_GridModelReq_r12;    /* OPTIONAL */
    UINT16                                 sbas_IDPresent : 1;
    UINT16                                 gnss_TimeModelsReqPresent : 1;
    UINT16                                 gnss_DifferentialCorrectionsReqPresent : 1;
    UINT16                                 gnss_NavigationModelReqPresent : 1;
    UINT16                                 gnss_RealTimeIntegrityReqPresent : 1;
    UINT16                                 gnss_DataBitAssistanceReqPresent : 1;
    UINT16                                 gnss_AcquisitionAssistanceReqPresent : 1;
    UINT16                                 gnss_AlmanacReqPresent : 1;
    UINT16                                 gnss_UTCModelReqPresent : 1;
    UINT16                                 gnss_AuxiliaryInformationReqPresent : 1;
    UINT16                                 bds_DifferentialCorrectionsReq_r12Present : 1;
    UINT16                                 bds_GridModelReq_r12Present : 1;
    UINT16                                 reserved : 4;
}GNSS_GenericAssistDataReqElement;


typedef struct GNSS_GenericAssistDataReqListTag
{
    GNSS_GenericAssistDataReqElement                   data;
    struct GNSS_GenericAssistDataReqListTag            *next;
}
GNSS_GenericAssistDataReqList;


typedef struct GNSS_CommonAssistDataReqTag
{
    GNSS_ReferenceTimeReq                  *gnss_ReferenceTimeReq;    /* OPTIONAL */
    GNSS_ReferenceLocationReq              *gnss_ReferenceLocationReq;    /* OPTIONAL */
    GNSS_IonosphericModelReq               *gnss_IonosphericModelReq;    /* OPTIONAL */
    GNSS_EarthOrientationParametersReq     *gnss_EarthOrientationParametersReq;    /* OPTIONAL */
    UINT8                                  gnss_ReferenceTimeReqPresent : 1;
    UINT8                                  gnss_ReferenceLocationReqPresent : 1;
    UINT8                                  gnss_IonosphericModelReqPresent : 1;
    UINT8                                  gnss_EarthOrientationParametersReqPresent : 1;
    UINT8                                  reserved : 4;
}GNSS_CommonAssistDataReq;


typedef struct A_GNSS_RequestAssistanceDataTag
{
    GNSS_CommonAssistDataReq               *gnss_CommonAssistDataReq;    /* OPTIONAL */
    GNSS_GenericAssistDataReqList          *gnss_GenericAssistDataReq;    /* OPTIONAL */
    UINT8                                  gnss_CommonAssistDataReqPresent : 1;
    UINT8                                  gnss_GenericAssistDataReqPresent : 1;
    UINT8                                  reserved : 6;
}A_GNSS_RequestAssistanceData;


typedef struct GridIonElement_r12Tag
{
    UINT16  /* INTEGER (1..320) */         igp_ID_r12;
    UINT16  /* INTEGER (0..511) */         dt_r12;
    UINT8  /* INTEGER (0..15) */           givei_r12;
}GridIonElement_r12;


typedef struct GridIonList_r12Tag
{
    GridIonElement_r12                                 data;
    struct GridIonList_r12Tag                          *next;
}
GridIonList_r12;


typedef struct BDS_GridModelParameter_r12Tag
{
    UINT16  /* INTEGER (0..3599) */        bds_RefTime_r12;
    GridIonList_r12                        gridIonList_r12;
}BDS_GridModelParameter_r12;


typedef struct DBDS_CorrectionElement_r12Tag
{
    SV_ID                                  svID;
    UINT8  /* INTEGER (0..15) */           bds_UDREI_r12;
    UINT8  /* INTEGER (0..15) */           bds_RURAI_r12;
    INT16  /* INTEGER (-4096..4095) */     bds_ECC_DeltaT_r12;
}DBDS_CorrectionElement_r12;


typedef struct DBDS_CorrectionList_r12Tag
{
    DBDS_CorrectionElement_r12                         data;
    struct DBDS_CorrectionList_r12Tag                  *next;
}
DBDS_CorrectionList_r12;


typedef struct BDS_SgnTypeElement_r12Tag
{
    GNSS_SignalID                          *gnss_SignalID;    /* OPTIONAL */
    DBDS_CorrectionList_r12                dbds_CorrectionList_r12;
    UINT8                                  gnss_SignalIDPresent : 1;
    UINT8                                  reserved : 7;
}BDS_SgnTypeElement_r12;


typedef struct BDS_SgnTypeList_r12Tag
{
    BDS_SgnTypeElement_r12                             data;
    struct BDS_SgnTypeList_r12Tag                      *next;
}
BDS_SgnTypeList_r12;


typedef struct BDS_DifferentialCorrections_r12Tag
{
    UINT16  /* INTEGER (0..3599) */        dbds_RefTime_r12;
    BDS_SgnTypeList_r12                    bds_SgnTypeList_r12;
}BDS_DifferentialCorrections_r12;


typedef struct GNSS_ID_GLONASS_SatElementTag
{
    SV_ID                                  svID;
    GNSS_SignalIDs                         signalsAvailable;
    INT8  /* INTEGER (-7..13) */           channelNumber;    /* OPTIONAL */
    UINT8                                  channelNumberPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_ID_GLONASS_SatElement;


typedef struct GNSS_ID_GLONASSTag
{
    GNSS_ID_GLONASS_SatElement                         data;
    struct GNSS_ID_GLONASSTag                          *next;
}
GNSS_ID_GLONASS;


typedef struct GNSS_ID_GPS_SatElementTag
{
    SV_ID                                  svID;
    GNSS_SignalIDs                         signalsAvailable;
}GNSS_ID_GPS_SatElement;


typedef struct GNSS_ID_GPSTag
{
    GNSS_ID_GPS_SatElement                             data;
    struct GNSS_ID_GPSTag                              *next;
}
GNSS_ID_GPS;


typedef struct GNSS_AuxiliaryInformationTag
{
    UINT8       tag;
        #define TAG_GNSS_AuxiliaryInformation_gnss_ID_GPS 0
        #define TAG_GNSS_AuxiliaryInformation_gnss_ID_GLONASS 1
    union {
        GNSS_ID_GPS                            *gnss_ID_GPS;
        GNSS_ID_GLONASS                        *gnss_ID_GLONASS;
    } choice;
}GNSS_AuxiliaryInformation;


typedef struct UTC_ModelSet5_r12Tag
{
    INT32  /* INTEGER (-2147483648..2147483647) */ utcA0_r12;
    INT32  /* INTEGER (-8388608..8388607) */ utcA1_r12;
    INT8  /* INTEGER (-128..127) */        utcDeltaTls_r12;
    UINT8  /* INTEGER (0..255) */          utcWNlsf_r12;
    UINT8  /* INTEGER (0..255) */          utcDN_r12;
    INT8  /* INTEGER (-128..127) */        utcDeltaTlsf_r12;
}UTC_ModelSet5_r12;


typedef struct UTC_ModelSet4Tag
{
    INT32  /* INTEGER (-8388608..8388607) */ utcA1wnt;
    INT32  /* INTEGER (-2147483648..2147483647) */ utcA0wnt;
    UINT8  /* INTEGER (0..255) */          utcTot;
    UINT8  /* INTEGER (0..255) */          utcWNt;
    INT8  /* INTEGER (-128..127) */        utcDeltaTls;
    UINT8  /* INTEGER (0..255) */          utcWNlsf;
    INT8  /* INTEGER (-128..127) */        utcDN;
    INT8  /* INTEGER (-128..127) */        utcDeltaTlsf;
    UINT8  /* INTEGER (0..7) */            utcStandardID;
}UTC_ModelSet4;


typedef struct UTC_ModelSet3Tag
{
    UINT16  /* INTEGER (1..1461) */        nA;
    INT32  /* INTEGER (-2147483648..2147483647) */ tauC;
    INT16  /* INTEGER (-1024..1023) */     b1;    /* OPTIONAL */
    INT16  /* INTEGER (-512..511) */       b2;    /* OPTIONAL */
    UINT8  /* BIT STRING (SIZE(2)) */      kp;    /* OPTIONAL */
    UINT8                                  b1Present : 1;
    UINT8                                  b2Present : 1;
    UINT8                                  kpPresent : 1;
    UINT8                                  reserved : 5;
}UTC_ModelSet3;


typedef struct UTC_ModelSet2Tag
{
    INT16  /* INTEGER (-32768..32767) */   utcA0;
    INT16  /* INTEGER (-4096..4095) */     utcA1;
    INT8  /* INTEGER (-64..63) */          utcA2;
    INT8  /* INTEGER (-128..127) */        utcDeltaTls;
    UINT16  /* INTEGER (0..65535) */       utcTot;
    UINT16  /* INTEGER (0..8191) */        utcWNot;
    UINT8  /* INTEGER (0..255) */          utcWNlsf;
    UINT8  /* BIT STRING (SIZE(4)) */      utcDN;
    INT8  /* INTEGER (-128..127) */        utcDeltaTlsf;
}UTC_ModelSet2;


typedef struct UTC_ModelSet1Tag
{
    INT32  /* INTEGER (-8388608..8388607) */ gnss_Utc_A1;
    INT32  /* INTEGER (-2147483648..2147483647) */ gnss_Utc_A0;
    UINT8  /* INTEGER (0..255) */          gnss_Utc_Tot;
    UINT8  /* INTEGER (0..255) */          gnss_Utc_WNt;
    INT8  /* INTEGER (-128..127) */        gnss_Utc_DeltaTls;
    UINT8  /* INTEGER (0..255) */          gnss_Utc_WNlsf;
    INT8  /* INTEGER (-128..127) */        gnss_Utc_DN;
    INT8  /* INTEGER (-128..127) */        gnss_Utc_DeltaTlsf;
}UTC_ModelSet1;


typedef struct GNSS_UTC_ModelTag
{
    UINT8       tag;
        #define TAG_GNSS_UTC_Model_utcModel1 0
        #define TAG_GNSS_UTC_Model_utcModel2 1
        #define TAG_GNSS_UTC_Model_utcModel3 2
        #define TAG_GNSS_UTC_Model_utcModel4 3
        #define TAG_GNSS_UTC_Model_utcModel5_r12 4
    union {
        UTC_ModelSet1                          *utcModel1;
        UTC_ModelSet2                          *utcModel2;
        UTC_ModelSet3                          *utcModel3;
        UTC_ModelSet4                          *utcModel4;
        UTC_ModelSet5_r12                      *utcModel5_r12;
    } choice;
}GNSS_UTC_Model;


typedef struct AlmanacBDS_AlmanacSet_r12Tag
{
    SV_ID                                  svID;
    UINT8  /* INTEGER (0..255) */          bdsAlmToa_r12;    /* OPTIONAL */
    UINT32  /* INTEGER (0..16777215) */    bdsAlmSqrtA_r12;
    UINT32  /* INTEGER (0..131071) */      bdsAlmE_r12;
    INT32  /* INTEGER (-8388608..8388607) */ bdsAlmW_r12;
    INT32  /* INTEGER (-8388608..8388607) */ bdsAlmM0_r12;
    INT32  /* INTEGER (-8388608..8388607) */ bdsAlmOmega0_r12;
    INT32  /* INTEGER (-65536..65535) */   bdsAlmOmegaDot_r12;
    INT16  /* INTEGER (-32768..32767) */   bdsAlmDeltaI_r12;
    INT16  /* INTEGER (-1024..1023) */     bdsAlmA0_r12;
    INT16  /* INTEGER (-1024..1023) */     bdsAlmA1_r12;
    UINT16  /* BIT STRING (SIZE(9)) */     bdsSvHealth_r12;    /* OPTIONAL */
    UINT8                                  bdsAlmToa_r12Present : 1;
    UINT8                                  bdsSvHealth_r12Present : 1;
    UINT8                                  reserved : 6;
}AlmanacBDS_AlmanacSet_r12;


typedef struct AlmanacECEF_SBAS_AlmanacSetTag
{
    UINT8  /* INTEGER (0..3) */            sbasAlmDataID;
    SV_ID                                  svID;
    UINT8  /* BIT STRING (SIZE(8)) */      sbasAlmHealth;
    INT16  /* INTEGER (-16384..16383) */   sbasAlmXg;
    INT16  /* INTEGER (-16384..16383) */   sbasAlmYg;
    INT16  /* INTEGER (-256..255) */       sbasAlmZg;
    INT8  /* INTEGER (-4..3) */            sbasAlmXgdot;
    INT8  /* INTEGER (-4..3) */            sbasAlmYgDot;
    INT8  /* INTEGER (-8..7) */            sbasAlmZgDot;
    UINT16  /* INTEGER (0..2047) */        sbasAlmTo;
}AlmanacECEF_SBAS_AlmanacSet;


typedef struct AlmanacGLONASS_AlmanacSetTag
{
    UINT16  /* INTEGER (1..1461) */        gloAlm_NA;
    UINT8  /* INTEGER (1..24) */           gloAlmnA;
    UINT8  /* INTEGER (0..31) */           gloAlmHA;
    INT32  /* INTEGER (-1048576..1048575) */ gloAlmLambdaA;
    UINT32  /* INTEGER (0..2097151) */     gloAlmtlambdaA;
    INT32  /* INTEGER (-131072..131071) */ gloAlmDeltaIa;
    INT32  /* INTEGER (-2097152..2097151) */ gloAlmDeltaTA;
    INT8  /* INTEGER (-64..63) */          gloAlmDeltaTdotA;
    UINT16  /* INTEGER (0..32767) */       gloAlmEpsilonA;
    INT16  /* INTEGER (-32768..32767) */   gloAlmOmegaA;
    INT16  /* INTEGER (-512..511) */       gloAlmTauA;
    UINT8  /* INTEGER (0..1) */            gloAlmCA;
    UINT8  /* BIT STRING (SIZE(2)) */      gloAlmMA;    /* OPTIONAL */
    UINT8                                  gloAlmMAPresent : 1;
    UINT8                                  reserved : 7;
}AlmanacGLONASS_AlmanacSet;


typedef struct AlmanacMidiAlmanacSetTag
{
    SV_ID                                  svID;
    UINT16  /* INTEGER (0..2047) */        midiAlmE;
    INT16  /* INTEGER (-1024..1023) */     midiAlmDeltaI;
    INT16  /* INTEGER (-1024..1023) */     midiAlmOmegaDot;
    UINT32  /* INTEGER (0..131071) */      midiAlmSqrtA;
    INT16  /* INTEGER (-32768..32767) */   midiAlmOmega0;
    INT16  /* INTEGER (-32768..32767) */   midiAlmOmega;
    INT16  /* INTEGER (-32768..32767) */   midiAlmMo;
    INT16  /* INTEGER (-1024..1023) */     midiAlmaf0;
    INT16  /* INTEGER (-512..511) */       midiAlmaf1;
    BOOL                                   midiAlmL1Health;
    BOOL                                   midiAlmL2Health;
    BOOL                                   midiAlmL5Health;
}AlmanacMidiAlmanacSet;


typedef struct AlmanacReducedKeplerianSetTag
{
    SV_ID                                  svID;
    INT8  /* INTEGER (-128..127) */        redAlmDeltaA;
    INT8  /* INTEGER (-64..63) */          redAlmOmega0;
    INT8  /* INTEGER (-64..63) */          redAlmPhi0;
    BOOL                                   redAlmL1Health;
    BOOL                                   redAlmL2Health;
    BOOL                                   redAlmL5Health;
}AlmanacReducedKeplerianSet;


typedef struct AlmanacNAV_KeplerianSetTag
{
    SV_ID                                  svID;
    UINT16  /* INTEGER (0..65535) */       navAlmE;
    INT16  /* INTEGER (-32768..32767) */   navAlmDeltaI;
    INT16  /* INTEGER (-32768..32767) */   navAlmOMEGADOT;
    UINT8  /* INTEGER (0..255) */          navAlmSVHealth;
    UINT32  /* INTEGER (0..16777215) */    navAlmSqrtA;
    INT32  /* INTEGER (-8388608..8388607) */ navAlmOMEGAo;
    INT32  /* INTEGER (-8388608..8388607) */ navAlmOmega;
    INT32  /* INTEGER (-8388608..8388607) */ navAlmMo;
    INT16  /* INTEGER (-1024..1023) */     navAlmaf0;
    INT16  /* INTEGER (-1024..1023) */     navAlmaf1;
}AlmanacNAV_KeplerianSet;


typedef struct AlmanacKeplerianSetTag
{
    SV_ID                                  svID;
    UINT16  /* INTEGER (0..2047) */        kepAlmanacE;
    INT16  /* INTEGER (-1024..1023) */     kepAlmanacDeltaI;
    INT16  /* INTEGER (-1024..1023) */     kepAlmanacOmegaDot;
    UINT8  /* BIT STRING (SIZE(4)) */      kepSV_StatusINAV;
    UINT8  /* BIT STRING (SIZE(2)) */      kepSV_StatusFNAV;    /* OPTIONAL */
    INT16  /* INTEGER (-4096..4095) */     kepAlmanacAPowerHalf;
    INT16  /* INTEGER (-32768..32767) */   kepAlmanacOmega0;
    INT16  /* INTEGER (-32768..32767) */   kepAlmanacW;
    INT16  /* INTEGER (-32768..32767) */   kepAlmanacM0;
    INT16  /* INTEGER (-32768..32767) */   kepAlmanacAF0;
    INT16  /* INTEGER (-4096..4095) */     kepAlmanacAF1;
    UINT8                                  kepSV_StatusFNAVPresent : 1;
    UINT8                                  reserved : 7;
}AlmanacKeplerianSet;


typedef struct GNSS_AlmanacElementTag
{
    UINT8       tag;
        #define TAG_GNSS_AlmanacElement_keplerianAlmanacSet 0
        #define TAG_GNSS_AlmanacElement_keplerianNAV_Almanac 1
        #define TAG_GNSS_AlmanacElement_keplerianReducedAlmanac 2
        #define TAG_GNSS_AlmanacElement_keplerianMidiAlmanac 3
        #define TAG_GNSS_AlmanacElement_keplerianGLONASS 4
        #define TAG_GNSS_AlmanacElement_ecef_SBAS_Almanac 5
        #define TAG_GNSS_AlmanacElement_keplerianBDS_Almanac_r12 6
    union {
        AlmanacKeplerianSet                    *keplerianAlmanacSet;
        AlmanacNAV_KeplerianSet                *keplerianNAV_Almanac;
        AlmanacReducedKeplerianSet             *keplerianReducedAlmanac;
        AlmanacMidiAlmanacSet                  *keplerianMidiAlmanac;
        AlmanacGLONASS_AlmanacSet              *keplerianGLONASS;
        AlmanacECEF_SBAS_AlmanacSet            *ecef_SBAS_Almanac;
        AlmanacBDS_AlmanacSet_r12              *keplerianBDS_Almanac_r12;
    } choice;
}GNSS_AlmanacElement;


typedef struct GNSS_AlmanacListTag
{
    GNSS_AlmanacElement                                data;
    struct GNSS_AlmanacListTag                         *next;
}
GNSS_AlmanacList;


typedef struct GNSS_AlmanacTag
{
    UINT8  /* INTEGER (0..255) */          weekNumber;    /* OPTIONAL */
    UINT8  /* INTEGER (0..255) */          toa;    /* OPTIONAL */
    UINT8  /* INTEGER (0..3) */            ioda;    /* OPTIONAL */
    BOOL                                   completeAlmanacProvided;
    GNSS_AlmanacList                       gnss_AlmanacList;
    UINT16  /* INTEGER (256..1023) */      toa_ext_v1240;    /* OPTIONAL */
    UINT8  /* INTEGER (4..15) */           ioda_ext_v1240;    /* OPTIONAL */
    UINT8                                  weekNumberPresent : 1;
    UINT8                                  toaPresent : 1;
    UINT8                                  iodaPresent : 1;
    UINT8                                  toa_ext_v1240Present : 1;
    UINT8                                  ioda_ext_v1240Present : 1;
    UINT8                                  reserved : 3;
}GNSS_Almanac;


typedef struct GNSS_AcquisitionAssistElementTag
{
    SV_ID                                  svID;
    INT16  /* INTEGER (-2048..2047) */     doppler0;
    UINT8  /* INTEGER (0..63) */           doppler1;
    UINT8  /* INTEGER (0..4) */            dopplerUncertainty;
    UINT16  /* INTEGER (0..1022) */        codePhase;
    UINT8  /* INTEGER (0..127) */          intCodePhase;
    UINT8  /* INTEGER (0..31) */           codePhaseSearchWindow;
    UINT16  /* INTEGER (0..511) */         azimuth;
    UINT8  /* INTEGER (0..127) */          elevation;
    BOOL                                   codePhase1023;    /* OPTIONAL */
    enum GNSS_AcquisitionAssistElement_dopplerUncertaintyExt_r10 {
        GNSS_AcquisitionAssistElement_dopplerUncertaintyExt_r10_d60 = 0,
        GNSS_AcquisitionAssistElement_dopplerUncertaintyExt_r10_d80 = 1,
        GNSS_AcquisitionAssistElement_dopplerUncertaintyExt_r10_d100 = 2,
        GNSS_AcquisitionAssistElement_dopplerUncertaintyExt_r10_d120 = 3,
        GNSS_AcquisitionAssistElement_dopplerUncertaintyExt_r10_noInformation = 4
    } dopplerUncertaintyExt_r10;    /* OPTIONAL */
    UINT8                                  codePhase1023Present : 1;
    UINT8                                  dopplerUncertaintyExt_r10Present : 1;
    UINT8                                  reserved : 6;
}GNSS_AcquisitionAssistElement;


typedef struct GNSS_AcquisitionAssistListTag
{
    GNSS_AcquisitionAssistElement                      data;
    struct GNSS_AcquisitionAssistListTag               *next;
}
GNSS_AcquisitionAssistList;


typedef struct GNSS_AcquisitionAssistanceTag
{
    GNSS_SignalID                          gnss_SignalID;
    GNSS_AcquisitionAssistList             gnss_AcquisitionAssistList;
    UINT8  /* INTEGER (0..100) */          confidence_r10;    /* OPTIONAL */
    UINT8                                  confidence_r10Present : 1;
    UINT8                                  reserved : 7;
}GNSS_AcquisitionAssistance;


typedef struct GNSS_DataBitsSgnElementTag
{
    GNSS_SignalID                          gnss_SignalType;
    AsnBitString_MaxSize1024               gnss_DataBits;
}GNSS_DataBitsSgnElement;


typedef struct GNSS_DataBitsSgnListTag
{
    GNSS_DataBitsSgnElement                            data;
    struct GNSS_DataBitsSgnListTag                     *next;
}
GNSS_DataBitsSgnList;


typedef struct GNSS_DataBitsSatElementTag
{
    SV_ID                                  svID;
    GNSS_DataBitsSgnList                   gnss_DataBitsSgnList;
}GNSS_DataBitsSatElement;


typedef struct GNSS_DataBitsSatListTag
{
    GNSS_DataBitsSatElement                            data;
    struct GNSS_DataBitsSatListTag                     *next;
}
GNSS_DataBitsSatList;


typedef struct GNSS_DataBitAssistanceTag
{
    UINT16  /* INTEGER (0..3599) */        gnss_TOD;
    UINT16  /* INTEGER (0..999) */         gnss_TODfrac;    /* OPTIONAL */
    GNSS_DataBitsSatList                   gnss_DataBitsSatList;
    UINT8                                  gnss_TODfracPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_DataBitAssistance;


typedef struct BadSignalElementTag
{
    SV_ID                                  badSVID;
    GNSS_SignalIDs                         *badSignalID;    /* OPTIONAL */
    UINT8                                  badSignalIDPresent : 1;
    UINT8                                  reserved : 7;
}BadSignalElement;


typedef struct GNSS_BadSignalListTag
{
    BadSignalElement                                   data;
    struct GNSS_BadSignalListTag                       *next;
}
GNSS_BadSignalList;


typedef struct GNSS_RealTimeIntegrityTag
{
    GNSS_BadSignalList                     gnss_BadSignalList;
}GNSS_RealTimeIntegrity;


typedef struct NavModel_BDS_KeplerianSet_r12Tag
{
    UINT8  /* INTEGER (0..31) */           bdsAODE_r12;
    UINT8  /* INTEGER (0..15) */           bdsURAI_r12;
    UINT32  /* INTEGER (0..131071) */      bdsToe_r12;
    UINT32  /* INTEGER (0..2147483647) */  bdsAPowerHalf_r12;
    UINT32  /* INTEGER (0..2147483647) */  bdsE_r12;
    INT32  /* INTEGER (-2147483648..2147483647) */ bdsW_r12;
    INT16  /* INTEGER (-32768..32767) */   bdsDeltaN_r12;
    INT32  /* INTEGER (-2147483648..2147483647) */ bdsM0_r12;
    INT32  /* INTEGER (-2147483648..2147483647) */ bdsOmega0_r12;
    INT32  /* INTEGER (-8388608..8388607) */ bdsOmegaDot_r12;
    INT32  /* INTEGER (-2147483648..2147483647) */ bdsI0_r12;
    INT16  /* INTEGER (-8192..8191) */     bdsIDot_r12;
    INT32  /* INTEGER (-131072..131071) */ bdsCuc_r12;
    INT32  /* INTEGER (-131072..131071) */ bdsCus_r12;
    INT32  /* INTEGER (-131072..131071) */ bdsCrc_r12;
    INT32  /* INTEGER (-131072..131071) */ bdsCrs_r12;
    INT32  /* INTEGER (-131072..131071) */ bdsCic_r12;
    INT32  /* INTEGER (-131072..131071) */ bdsCis_r12;
}NavModel_BDS_KeplerianSet_r12;


typedef struct NavModel_SBAS_ECEFTag
{
    UINT16  /* INTEGER (0..5399) */        sbasTo;    /* OPTIONAL */
    UINT8  /* BIT STRING (SIZE(4)) */      sbasAccuracy;
    INT32  /* INTEGER (-536870912..536870911) */ sbasXg;
    INT32  /* INTEGER (-536870912..536870911) */ sbasYg;
    INT32  /* INTEGER (-16777216..16777215) */ sbasZg;
    INT32  /* INTEGER (-65536..65535) */   sbasXgDot;
    INT32  /* INTEGER (-65536..65535) */   sbasYgDot;
    INT32  /* INTEGER (-131072..131071) */ sbasZgDot;
    INT16  /* INTEGER (-512..511) */       sbasXgDotDot;
    INT16  /* INTEGER (-512..511) */       sbagYgDotDot;
    INT16  /* INTEGER (-512..511) */       sbasZgDotDot;
    UINT8                                  sbasToPresent : 1;
    UINT8                                  reserved : 7;
}NavModel_SBAS_ECEF;


typedef struct NavModel_GLONASS_ECEFTag
{
    UINT8  /* INTEGER (0..31) */           gloEn;
    UINT8  /* BIT STRING (SIZE(2)) */      gloP1;
    BOOL                                   gloP2;
    UINT8  /* INTEGER (0..3) */            gloM;
    INT32  /* INTEGER (-67108864..67108863) */ gloX;
    INT32  /* INTEGER (-8388608..8388607) */ gloXdot;
    INT8  /* INTEGER (-16..15) */          gloXdotdot;
    INT32  /* INTEGER (-67108864..67108863) */ gloY;
    INT32  /* INTEGER (-8388608..8388607) */ gloYdot;
    INT8  /* INTEGER (-16..15) */          gloYdotdot;
    INT32  /* INTEGER (-67108864..67108863) */ gloZ;
    INT32  /* INTEGER (-8388608..8388607) */ gloZdot;
    INT8  /* INTEGER (-16..15) */          gloZdotdot;
}NavModel_GLONASS_ECEF;


typedef struct NavModelCNAV_KeplerianSetTag
{
    UINT16  /* INTEGER (0..2015) */        cnavTop;
    INT8  /* INTEGER (-16..15) */          cnavURAindex;
    INT32  /* INTEGER (-33554432..33554431) */ cnavDeltaA;
    INT32  /* INTEGER (-16777216..16777215) */ cnavAdot;
    INT32  /* INTEGER (-65536..65535) */   cnavDeltaNo;
    INT32  /* INTEGER (-4194304..4194303) */ cnavDeltaNoDot;
    AsnBitString_33                        cnavMo;
    AsnBitString_33                        cnavE;
    AsnBitString_33                        cnavOmega;
    AsnBitString_33                        cnavOMEGA0;
    INT32  /* INTEGER (-65536..65535) */   cnavDeltaOmegaDot;
    AsnBitString_33                        cnavIo;
    INT16  /* INTEGER (-16384..16383) */   cnavIoDot;
    INT16  /* INTEGER (-32768..32767) */   cnavCis;
    INT16  /* INTEGER (-32768..32767) */   cnavCic;
    INT32  /* INTEGER (-8388608..8388607) */ cnavCrs;
    INT32  /* INTEGER (-8388608..8388607) */ cnavCrc;
    INT32  /* INTEGER (-1048576..1048575) */ cnavCus;
    INT32  /* INTEGER (-1048576..1048575) */ cnavCuc;
}NavModelCNAV_KeplerianSet;


typedef struct NavModelNAV_KeplerianSet_ephemSF1RsvdTag
{
    UINT32  /* INTEGER (0..8388607) */     reserved1;
    UINT32  /* INTEGER (0..16777215) */    reserved2;
    UINT32  /* INTEGER (0..16777215) */    reserved3;
    UINT16  /* INTEGER (0..65535) */       reserved4;
}NavModelNAV_KeplerianSet_ephemSF1Rsvd;


typedef struct NavModelNAV_KeplerianSet_addNAVparamTag
{
    UINT8  /* INTEGER (0..3) */            ephemCodeOnL2;
    UINT8  /* INTEGER (0..1) */            ephemL2Pflag;
    NavModelNAV_KeplerianSet_ephemSF1Rsvd  ephemSF1Rsvd;
    UINT8  /* INTEGER (0..31) */           ephemAODA;
}NavModelNAV_KeplerianSet_addNAVparam;


typedef struct NavModelNAV_KeplerianSetTag
{
    UINT8  /* INTEGER (0..15) */           navURA;
    UINT8  /* INTEGER (0..1) */            navFitFlag;
    UINT16  /* INTEGER (0..37799) */       navToe;
    INT32  /* INTEGER (-2147483648..2147483647) */ navOmega;
    INT16  /* INTEGER (-32768..32767) */   navDeltaN;
    INT32  /* INTEGER (-2147483648..2147483647) */ navM0;
    INT32  /* INTEGER (-8388608..8388607) */ navOmegaADot;
    UINT32  /* INTEGER (0..2147483647) */  navE;
    INT16  /* INTEGER (-8192..8191) */     navIDot;
    UINT32  /* INTEGER (0..2147483647) */  navAPowerHalf;
    INT32  /* INTEGER (-2147483648..2147483647) */ navI0;
    INT32  /* INTEGER (-2147483648..2147483647) */ navOmegaA0;
    INT16  /* INTEGER (-32768..32767) */   navCrs;
    INT16  /* INTEGER (-32768..32767) */   navCis;
    INT16  /* INTEGER (-32768..32767) */   navCus;
    INT16  /* INTEGER (-32768..32767) */   navCrc;
    INT16  /* INTEGER (-32768..32767) */   navCic;
    INT16  /* INTEGER (-32768..32767) */   navCuc;
    NavModelNAV_KeplerianSet_addNAVparam   *addNAVparam;    /* OPTIONAL */
    UINT8                                  addNAVparamPresent : 1;
    UINT8                                  reserved : 7;
}NavModelNAV_KeplerianSet;


typedef struct NavModelKeplerianSetTag
{
    UINT16  /* INTEGER (0..16383) */       keplerToe;
    INT32  /* INTEGER (-2147483648..2147483647) */ keplerW;
    INT16  /* INTEGER (-32768..32767) */   keplerDeltaN;
    INT32  /* INTEGER (-2147483648..2147483647) */ keplerM0;
    INT32  /* INTEGER (-8388608..8388607) */ keplerOmegaDot;
    UINT32  /* INTEGER (0..2147483647) */  keplerE;
    INT16  /* INTEGER (-8192..8191) */     keplerIDot;
    UINT32  /* INTEGER (0..2147483647) */  keplerAPowerHalf;
    INT32  /* INTEGER (-2147483648..2147483647) */ keplerI0;
    INT32  /* INTEGER (-2147483648..2147483647) */ keplerOmega0;
    INT16  /* INTEGER (-32768..32767) */   keplerCrs;
    INT16  /* INTEGER (-32768..32767) */   keplerCis;
    INT16  /* INTEGER (-32768..32767) */   keplerCus;
    INT16  /* INTEGER (-32768..32767) */   keplerCrc;
    INT16  /* INTEGER (-32768..32767) */   keplerCic;
    INT16  /* INTEGER (-32768..32767) */   keplerCuc;
}NavModelKeplerianSet;


typedef struct BDS_ClockModel_r12Tag
{
    UINT8  /* INTEGER (0..31) */           bdsAODC_r12;
    UINT32  /* INTEGER (0..131071) */      bdsToc_r12;
    INT32  /* INTEGER (-8388608..8388607) */ bdsA0_r12;
    INT32  /* INTEGER (-2097152..2097151) */ bdsA1_r12;
    INT16  /* INTEGER (-1024..1023) */     bdsA2_r12;
    INT16  /* INTEGER (-512..511) */       bdsTgd1_r12;
}BDS_ClockModel_r12;


typedef struct SBAS_ClockModelTag
{
    UINT16  /* INTEGER (0..5399) */        sbasTo;
    INT16  /* INTEGER (-2048..2047) */     sbasAgfo;
    INT8  /* INTEGER (-128..127) */        sbasAgf1;
}SBAS_ClockModel;


typedef struct GLONASS_ClockModelTag
{
    INT32  /* INTEGER (-2097152..2097151) */ gloTau;
    INT16  /* INTEGER (-1024..1023) */     gloGamma;
    INT8  /* INTEGER (-16..15) */          gloDeltaTau;    /* OPTIONAL */
    UINT8                                  gloDeltaTauPresent : 1;
    UINT8                                  reserved : 7;
}GLONASS_ClockModel;


typedef struct CNAV_ClockModelTag
{
    UINT16  /* INTEGER (0..2015) */        cnavToc;
    UINT16  /* INTEGER (0..2015) */        cnavTop;
    INT8  /* INTEGER (-16..15) */          cnavURA0;
    UINT8  /* INTEGER (0..7) */            cnavURA1;
    UINT8  /* INTEGER (0..7) */            cnavURA2;
    INT16  /* INTEGER (-512..511) */       cnavAf2;
    INT32  /* INTEGER (-524288..524287) */ cnavAf1;
    INT32  /* INTEGER (-33554432..33554431) */ cnavAf0;
    INT16  /* INTEGER (-4096..4095) */     cnavTgd;
    INT16  /* INTEGER (-4096..4095) */     cnavISCl1cp;    /* OPTIONAL */
    INT16  /* INTEGER (-4096..4095) */     cnavISCl1cd;    /* OPTIONAL */
    INT16  /* INTEGER (-4096..4095) */     cnavISCl1ca;    /* OPTIONAL */
    INT16  /* INTEGER (-4096..4095) */     cnavISCl2c;    /* OPTIONAL */
    INT16  /* INTEGER (-4096..4095) */     cnavISCl5i5;    /* OPTIONAL */
    INT16  /* INTEGER (-4096..4095) */     cnavISCl5q5;    /* OPTIONAL */
    UINT8                                  cnavISCl1cpPresent : 1;
    UINT8                                  cnavISCl1cdPresent : 1;
    UINT8                                  cnavISCl1caPresent : 1;
    UINT8                                  cnavISCl2cPresent : 1;
    UINT8                                  cnavISCl5i5Present : 1;
    UINT8                                  cnavISCl5q5Present : 1;
    UINT8                                  reserved : 2;
}CNAV_ClockModel;


typedef struct NAV_ClockModelTag
{
    UINT16  /* INTEGER (0..37799) */       navToc;
    INT8  /* INTEGER (-128..127) */        navaf2;
    INT16  /* INTEGER (-32768..32767) */   navaf1;
    INT32  /* INTEGER (-2097152..2097151) */ navaf0;
    INT8  /* INTEGER (-128..127) */        navTgd;
}NAV_ClockModel;


typedef struct StandardClockModelElementTag
{
    UINT16  /* INTEGER (0..16383) */       stanClockToc;
    INT8  /* INTEGER (-32..31) */          stanClockAF2;
    INT32  /* INTEGER (-1048576..1048575) */ stanClockAF1;
    INT32  /* INTEGER (-1073741824..1073741823) */ stanClockAF0;
    INT16  /* INTEGER (-512..511) */       stanClockTgd;    /* OPTIONAL */
    UINT8  /* INTEGER (0..255) */          sisa;
    UINT8  /* INTEGER (0..1) */            stanModelID;    /* OPTIONAL */
    UINT8                                  stanClockTgdPresent : 1;
    UINT8                                  stanModelIDPresent : 1;
    UINT8                                  reserved : 6;
}StandardClockModelElement;


typedef struct StandardClockModelListTag
{
    StandardClockModelElement                          data;
    struct StandardClockModelListTag                   *next;
}
StandardClockModelList;


typedef struct GNSS_OrbitModelTag
{
    UINT8       tag;
        #define TAG_GNSS_OrbitModel_keplerianSet 0
        #define TAG_GNSS_OrbitModel_nav_KeplerianSet 1
        #define TAG_GNSS_OrbitModel_cnav_KeplerianSet 2
        #define TAG_GNSS_OrbitModel_glonass_ECEF 3
        #define TAG_GNSS_OrbitModel_sbas_ECEF 4
        #define TAG_GNSS_OrbitModel_bds_KeplerianSet_r12 5
    union {
        NavModelKeplerianSet                   *keplerianSet;
        NavModelNAV_KeplerianSet               *nav_KeplerianSet;
        NavModelCNAV_KeplerianSet              *cnav_KeplerianSet;
        NavModel_GLONASS_ECEF                  *glonass_ECEF;
        NavModel_SBAS_ECEF                     *sbas_ECEF;
        NavModel_BDS_KeplerianSet_r12          *bds_KeplerianSet_r12;
    } choice;
}GNSS_OrbitModel;


typedef struct GNSS_ClockModelTag
{
    UINT8       tag;
        #define TAG_GNSS_ClockModel_standardClockModelList 0
        #define TAG_GNSS_ClockModel_nav_ClockModel 1
        #define TAG_GNSS_ClockModel_cnav_ClockModel 2
        #define TAG_GNSS_ClockModel_glonass_ClockModel 3
        #define TAG_GNSS_ClockModel_sbas_ClockModel 4
        #define TAG_GNSS_ClockModel_bds_ClockModel_r12 5
    union {
        StandardClockModelList                 *standardClockModelList;
        NAV_ClockModel                         *nav_ClockModel;
        CNAV_ClockModel                        *cnav_ClockModel;
        GLONASS_ClockModel                     *glonass_ClockModel;
        SBAS_ClockModel                        *sbas_ClockModel;
        BDS_ClockModel_r12                     *bds_ClockModel_r12;
    } choice;
}GNSS_ClockModel;


typedef struct GNSS_NavModelSatelliteElementTag
{
    SV_ID                                  svID;
    UINT8  /* BIT STRING (SIZE(8)) */      svHealth;
    UINT16  /* BIT STRING (SIZE(11)) */    iod;
    GNSS_ClockModel                        gnss_ClockModel;
    GNSS_OrbitModel                        gnss_OrbitModel;
    UINT8  /* BIT STRING (SIZE(4)) */      svHealthExt_v1240;    /* OPTIONAL */
    UINT8                                  svHealthExt_v1240Present : 1;
    UINT8                                  reserved : 7;
}GNSS_NavModelSatelliteElement;


typedef struct GNSS_NavModelSatelliteListTag
{
    GNSS_NavModelSatelliteElement                      data;
    struct GNSS_NavModelSatelliteListTag               *next;
}
GNSS_NavModelSatelliteList;


typedef struct GNSS_NavigationModelTag
{
    UINT8  /* INTEGER (0..1) */            nonBroadcastIndFlag;
    GNSS_NavModelSatelliteList             gnss_SatelliteList;
}GNSS_NavigationModel;


typedef struct DGNSS_CorrectionsElementTag
{
    SV_ID                                  svID;
    UINT16  /* BIT STRING (SIZE(11)) */    iod;
    UINT8  /* INTEGER (0..3) */            udre;
    INT16  /* INTEGER (-2047..2047) */     pseudoRangeCor;
    INT8  /* INTEGER (-127..127) */        rangeRateCor;
    UINT8  /* INTEGER (0..7) */            udreGrowthRate;    /* OPTIONAL */
    UINT8  /* INTEGER (0..7) */            udreValidityTime;    /* OPTIONAL */
    UINT8                                  udreGrowthRatePresent : 1;
    UINT8                                  udreValidityTimePresent : 1;
    UINT8                                  reserved : 6;
}DGNSS_CorrectionsElement;


typedef struct DGNSS_SatListTag
{
    DGNSS_CorrectionsElement                           data;
    struct DGNSS_SatListTag                            *next;
}
DGNSS_SatList;


typedef struct DGNSS_SgnTypeElementTag
{
    GNSS_SignalID                          gnss_SignalID;
    UINT8  /* INTEGER (0..7) */            gnss_StatusHealth;
    DGNSS_SatList                          dgnss_SatList;
}DGNSS_SgnTypeElement;


typedef struct DGNSS_SgnTypeListTag
{
    DGNSS_SgnTypeElement                               data;
    struct DGNSS_SgnTypeListTag                        *next;
}
DGNSS_SgnTypeList;


typedef struct GNSS_DifferentialCorrectionsTag
{
    UINT16  /* INTEGER (0..3599) */        dgnss_RefTime;
    DGNSS_SgnTypeList                      dgnss_SgnTypeList;
}GNSS_DifferentialCorrections;


typedef struct GNSS_TimeModelElementTag
{
    UINT16  /* INTEGER (0..65535) */       gnss_TimeModelRefTime;
    INT32  /* INTEGER (-67108864..67108863) */ tA0;
    INT16  /* INTEGER (-4096..4095) */     tA1;    /* OPTIONAL */
    INT8  /* INTEGER (-64..63) */          tA2;    /* OPTIONAL */
    UINT8  /* INTEGER (1..15) */           gnss_TO_ID;
    UINT16  /* INTEGER (0..8191) */        weekNumber;    /* OPTIONAL */
    INT8  /* INTEGER (-128..127) */        deltaT;    /* OPTIONAL */
    UINT8                                  tA1Present : 1;
    UINT8                                  tA2Present : 1;
    UINT8                                  weekNumberPresent : 1;
    UINT8                                  deltaTPresent : 1;
    UINT8                                  reserved : 4;
}GNSS_TimeModelElement;


typedef struct GNSS_TimeModelListTag
{
    GNSS_TimeModelElement                              data;
    struct GNSS_TimeModelListTag                       *next;
}
GNSS_TimeModelList;


typedef struct GNSS_EarthOrientationParametersTag
{
    UINT16  /* INTEGER (0..65535) */       teop;
    INT32  /* INTEGER (-1048576..1048575) */ pmX;
    INT16  /* INTEGER (-16384..16383) */   pmXdot;
    INT32  /* INTEGER (-1048576..1048575) */ pmY;
    INT16  /* INTEGER (-16384..16383) */   pmYdot;
    INT32  /* INTEGER (-1073741824..1073741823) */ deltaUT1;
    INT32  /* INTEGER (-262144..262143) */ deltaUT1dot;
}GNSS_EarthOrientationParameters;


typedef struct NeQuickModelParameterTag
{
    UINT16  /* INTEGER (0..2047) */        ai0;
    INT16  /* INTEGER (-1024..1023) */     ai1;
    INT16  /* INTEGER (-8192..8191) */     ai2;
    UINT8  /* INTEGER (0..1) */            ionoStormFlag1;    /* OPTIONAL */
    UINT8  /* INTEGER (0..1) */            ionoStormFlag2;    /* OPTIONAL */
    UINT8  /* INTEGER (0..1) */            ionoStormFlag3;    /* OPTIONAL */
    UINT8  /* INTEGER (0..1) */            ionoStormFlag4;    /* OPTIONAL */
    UINT8  /* INTEGER (0..1) */            ionoStormFlag5;    /* OPTIONAL */
    UINT8                                  ionoStormFlag1Present : 1;
    UINT8                                  ionoStormFlag2Present : 1;
    UINT8                                  ionoStormFlag3Present : 1;
    UINT8                                  ionoStormFlag4Present : 1;
    UINT8                                  ionoStormFlag5Present : 1;
    UINT8                                  reserved : 3;
}NeQuickModelParameter;


typedef struct KlobucharModelParameterTag
{
    UINT8  /* BIT STRING (SIZE(2)) */      dataID;
    INT8  /* INTEGER (-128..127) */        alfa0;
    INT8  /* INTEGER (-128..127) */        alfa1;
    INT8  /* INTEGER (-128..127) */        alfa2;
    INT8  /* INTEGER (-128..127) */        alfa3;
    INT8  /* INTEGER (-128..127) */        beta0;
    INT8  /* INTEGER (-128..127) */        beta1;
    INT8  /* INTEGER (-128..127) */        beta2;
    INT8  /* INTEGER (-128..127) */        beta3;
}KlobucharModelParameter;


typedef struct GNSS_IonosphericModelTag
{
    KlobucharModelParameter                *klobucharModel;    /* OPTIONAL */
    NeQuickModelParameter                  *neQuickModel;    /* OPTIONAL */
    UINT8                                  klobucharModelPresent : 1;
    UINT8                                  neQuickModelPresent : 1;
    UINT8                                  reserved : 6;
}GNSS_IonosphericModel;


typedef struct GNSS_ReferenceLocationTag
{
    EllipsoidPointWithAltitudeAndUncertaintyEllipsoid threeDlocation;
}GNSS_ReferenceLocation;


typedef struct CarrierFreq_NB_r14Tag
{
    ARFCN_ValueEUTRA_r14                   carrierFreq_r14;
    CarrierFreqOffsetNB_r14                carrierFreqOffset_r14;    /* OPTIONAL */
    UINT8                                  carrierFreqOffset_r14Present : 1;
    UINT8                                  reserved : 7;
}CarrierFreq_NB_r14;


typedef struct NetworkTime_nBIoT_r14Tag
{
    UINT16  /* INTEGER (0..503) */         nbPhysCellId_r14;
    ECGI                                   *nbCellGlobalId_r14;    /* OPTIONAL */
    CarrierFreq_NB_r14                     nbCarrierFreq_r14;
    UINT8                                  nbCellGlobalId_r14Present : 1;
    UINT8                                  reserved : 7;
}NetworkTime_nBIoT_r14;


typedef struct NetworkTime_gSMTag
{
    UINT16  /* INTEGER (0..1023) */        bcchCarrier;
    UINT8  /* INTEGER (0..63) */           bsic;
    CellGlobalIdGERAN_LPP                  *cellGlobalIdGERAN;    /* OPTIONAL */
    UINT8                                  cellGlobalIdGERANPresent : 1;
    UINT8                                  reserved : 7;
}NetworkTime_gSM;


typedef struct NetworkTime_tddTag
{
    UINT8  /* INTEGER (0..127) */          cellParameters;
}NetworkTime_tdd;


typedef struct NetworkTime_fddTag
{
    UINT16  /* INTEGER (0..511) */         primary_CPICH_Info;
}NetworkTime_fdd;


typedef struct NetworkTime_uTRATag
{
    struct NetworkTime_mode {
        UINT8       tag;
            #define TAG_NetworkTime_mode_fdd 0
            #define TAG_NetworkTime_mode_tdd 1
        union {
            NetworkTime_fdd                        *fdd;
            NetworkTime_tdd                        *tdd;
        } choice;
    } mode;
    CellGlobalIdEUTRA_AndUTRA              *cellGlobalIdUTRA;    /* OPTIONAL */
    ARFCN_ValueUTRA                        uarfcn;
    UINT8                                  cellGlobalIdUTRAPresent : 1;
    UINT8                                  reserved : 7;
}NetworkTime_uTRA;


typedef struct NetworkTime_eUTRATag
{
    UINT16  /* INTEGER (0..503) */         physCellId;
    CellGlobalIdEUTRA_AndUTRA              *cellGlobalIdEUTRA;    /* OPTIONAL */
    ARFCN_ValueEUTRA                       earfcn;
    ARFCN_ValueEUTRA_v9a0                  earfcn_v9a0;    /* OPTIONAL */
    UINT8                                  cellGlobalIdEUTRAPresent : 1;
    UINT8                                  earfcn_v9a0Present : 1;
    UINT8                                  reserved : 6;
}NetworkTime_eUTRA;


typedef struct NetworkTimeTag
{
    UINT16  /* INTEGER (0..12533) */       secondsFromFrameStructureStart;
    UINT32  /* INTEGER (0..3999999) */     fractionalSecondsFromFrameStructureStart;
    INT8  /* INTEGER (-64..63) */          frameDrift;    /* OPTIONAL */
    struct NetworkTime_cellID {
        UINT8       tag;
            #define TAG_NetworkTime_cellID_eUTRA 0
            #define TAG_NetworkTime_cellID_uTRA 1
            #define TAG_NetworkTime_cellID_gSM 2
            #define TAG_NetworkTime_cellID_nBIoT_r14 3
        union {
            NetworkTime_eUTRA                      *eUTRA;
            NetworkTime_uTRA                       *uTRA;
            NetworkTime_gSM                        *gSM;
            NetworkTime_nBIoT_r14                  *nBIoT_r14;
        } choice;
    } cellID;
    UINT8                                  frameDriftPresent : 1;
    UINT8                                  reserved : 7;
}NetworkTime;


typedef struct GPS_TOW_AssistElementTag
{
    UINT8  /* INTEGER (1..64) */           satelliteID;
    UINT16  /* INTEGER (0..16383) */       tlmWord;
    UINT8  /* INTEGER (0..1) */            antiSpoof;
    UINT8  /* INTEGER (0..1) */            alert;
    UINT8  /* INTEGER (0..3) */            tlmRsvdBits;
}GPS_TOW_AssistElement;


typedef struct GPS_TOW_AssistListTag
{
    GPS_TOW_AssistElement                              data;
    struct GPS_TOW_AssistListTag                       *next;
}
GPS_TOW_AssistList;


typedef struct GNSS_SystemTimeTag
{
    GNSS_ID                                gnss_TimeID;
    UINT16  /* INTEGER (0..32767) */       gnss_DayNumber;
    UINT32  /* INTEGER (0..86399) */       gnss_TimeOfDay;
    UINT16  /* INTEGER (0..999) */         gnss_TimeOfDayFrac_msec;    /* OPTIONAL */
    UINT8  /* BIT STRING (SIZE(2)) */      notificationOfLeapSecond;    /* OPTIONAL */
    GPS_TOW_AssistList                     *gps_TOW_Assist;    /* OPTIONAL */
    UINT8                                  gnss_TimeOfDayFrac_msecPresent : 1;
    UINT8                                  notificationOfLeapSecondPresent : 1;
    UINT8                                  gps_TOW_AssistPresent : 1;
    UINT8                                  reserved : 5;
}GNSS_SystemTime;


typedef struct GNSS_ReferenceTimeForOneCellTag
{
    NetworkTime                            networkTime;
    UINT8  /* INTEGER (0..127) */          referenceTimeUnc;
    UINT8                                  bsAlignPresent : 1;
    UINT8                                  reserved : 7;
}GNSS_ReferenceTimeForOneCell;


typedef struct GNSS_ReferenceTime_gnss_ReferenceTimeForCellsTag
{
    GNSS_ReferenceTimeForOneCell                       data;
    struct GNSS_ReferenceTime_gnss_ReferenceTimeForCellsTag *next;
}
GNSS_ReferenceTime_gnss_ReferenceTimeForCells;


typedef struct GNSS_ReferenceTimeTag
{
    GNSS_SystemTime                        gnss_SystemTime;
    UINT8  /* INTEGER (0..127) */          referenceTimeUnc;    /* OPTIONAL */
    GNSS_ReferenceTime_gnss_ReferenceTimeForCells *gnss_ReferenceTimeForCells;    /* OPTIONAL */
    UINT8                                  referenceTimeUncPresent : 1;
    UINT8                                  gnss_ReferenceTimeForCellsPresent : 1;
    UINT8                                  reserved : 6;
}GNSS_ReferenceTime;


typedef struct GNSS_GenericAssistDataElementTag
{
    GNSS_ID                                gnss_ID;
    SBAS_ID                                *sbas_ID;    /* OPTIONAL */
    GNSS_TimeModelList                     *gnss_TimeModels;    /* OPTIONAL */
    GNSS_DifferentialCorrections           *gnss_DifferentialCorrections;    /* OPTIONAL */
    GNSS_NavigationModel                   *gnss_NavigationModel;    /* OPTIONAL */
    GNSS_RealTimeIntegrity                 *gnss_RealTimeIntegrity;    /* OPTIONAL */
    GNSS_DataBitAssistance                 *gnss_DataBitAssistance;    /* OPTIONAL */
    GNSS_AcquisitionAssistance             *gnss_AcquisitionAssistance;    /* OPTIONAL */
    GNSS_Almanac                           *gnss_Almanac;    /* OPTIONAL */
    GNSS_UTC_Model                         *gnss_UTC_Model;    /* OPTIONAL */
    GNSS_AuxiliaryInformation              *gnss_AuxiliaryInformation;    /* OPTIONAL */
    BDS_DifferentialCorrections_r12        *bds_DifferentialCorrections_r12;    /* OPTIONAL */
    BDS_GridModelParameter_r12             *bds_GridModel_r12;    /* OPTIONAL */
    UINT16                                 sbas_IDPresent : 1;
    UINT16                                 gnss_TimeModelsPresent : 1;
    UINT16                                 gnss_DifferentialCorrectionsPresent : 1;
    UINT16                                 gnss_NavigationModelPresent : 1;
    UINT16                                 gnss_RealTimeIntegrityPresent : 1;
    UINT16                                 gnss_DataBitAssistancePresent : 1;
    UINT16                                 gnss_AcquisitionAssistancePresent : 1;
    UINT16                                 gnss_AlmanacPresent : 1;
    UINT16                                 gnss_UTC_ModelPresent : 1;
    UINT16                                 gnss_AuxiliaryInformationPresent : 1;
    UINT16                                 bds_DifferentialCorrections_r12Present : 1;
    UINT16                                 bds_GridModel_r12Present : 1;
    UINT16                                 reserved : 4;
}GNSS_GenericAssistDataElement;


typedef struct GNSS_GenericAssistDataListTag
{
    GNSS_GenericAssistDataElement                      data;
    struct GNSS_GenericAssistDataListTag               *next;
}
GNSS_GenericAssistDataList;


typedef struct GNSS_CommonAssistDataTag
{
    GNSS_ReferenceTime                     *gnss_ReferenceTime;    /* OPTIONAL */
    GNSS_ReferenceLocation                 *gnss_ReferenceLocation;    /* OPTIONAL */
    GNSS_IonosphericModel                  *gnss_IonosphericModel;    /* OPTIONAL */
    GNSS_EarthOrientationParameters        *gnss_EarthOrientationParameters;    /* OPTIONAL */
    UINT8                                  gnss_ReferenceTimePresent : 1;
    UINT8                                  gnss_ReferenceLocationPresent : 1;
    UINT8                                  gnss_IonosphericModelPresent : 1;
    UINT8                                  gnss_EarthOrientationParametersPresent : 1;
    UINT8                                  reserved : 4;
}GNSS_CommonAssistData;


typedef struct A_GNSS_ProvideAssistanceDataTag
{
    GNSS_CommonAssistData                  *gnss_CommonAssistData;    /* OPTIONAL */
    GNSS_GenericAssistDataList             *gnss_GenericAssistData;    /* OPTIONAL */
    A_GNSS_Error                           *gnss_Error;    /* OPTIONAL */
    UINT8                                  gnss_CommonAssistDataPresent : 1;
    UINT8                                  gnss_GenericAssistDataPresent : 1;
    UINT8                                  gnss_ErrorPresent : 1;
    UINT8                                  reserved : 5;
}A_GNSS_ProvideAssistanceData;


typedef struct OTDOA_TargetDeviceErrorCausesTag
{
    enum OTDOA_TargetDeviceErrorCauses_cause {
        OTDOA_TargetDeviceErrorCauses_cause_undefined = 0,
        OTDOA_TargetDeviceErrorCauses_cause_assistance_data_missing = 1,
        OTDOA_TargetDeviceErrorCauses_cause_unableToMeasureReferenceCell = 2,
        OTDOA_TargetDeviceErrorCauses_cause_unableToMeasureAnyNeighbourCell = 3,
        OTDOA_TargetDeviceErrorCauses_cause_attemptedButUnableToMeasureSomeNeighbourCells = 4
    } cause;
}OTDOA_TargetDeviceErrorCauses;


typedef struct OTDOA_LocationServerErrorCausesTag
{
    enum OTDOA_LocationServerErrorCauses_cause {
        OTDOA_LocationServerErrorCauses_cause_undefined = 0,
        OTDOA_LocationServerErrorCauses_cause_assistanceDataNotSupportedByServer = 1,
        OTDOA_LocationServerErrorCauses_cause_assistanceDataSupportedButCurrentlyNotAvailableByServer = 2
    } cause;
}OTDOA_LocationServerErrorCauses;


typedef struct OTDOA_ErrorTag
{
    UINT8       tag;
        #define TAG_OTDOA_Error_locationServerErrorCauses 0
        #define TAG_OTDOA_Error_targetDeviceErrorCauses 1
    union {
        OTDOA_LocationServerErrorCauses        *locationServerErrorCauses;
        OTDOA_TargetDeviceErrorCauses          *targetDeviceErrorCauses;
    } choice;
}OTDOA_Error;


typedef struct OTDOA_RequestCapabilitiesTag
{
    UINT8                                  padding; /*this IE will not effect encode/decode, just to make sure not defining a empty struct*/
}OTDOA_RequestCapabilities;


typedef struct SupportedBandEUTRA_v9a0Tag
{
    UINT16  /* INTEGER (65..256) */        bandEUTRA_v9a0;    /* OPTIONAL */
    UINT8                                  bandEUTRA_v9a0Present : 1;
    UINT8                                  reserved : 7;
}SupportedBandEUTRA_v9a0;


typedef struct SupportedBandEUTRA_LPPTag
{
    UINT8  /* INTEGER (1..64) */           bandEUTRA;
}SupportedBandEUTRA_LPP;


typedef struct OTDOA_ProvideCapabilities_supportedBandListEUTRA_v9a0Tag
{
    SupportedBandEUTRA_v9a0                            data;
    struct OTDOA_ProvideCapabilities_supportedBandListEUTRA_v9a0Tag *next;
}
OTDOA_ProvideCapabilities_supportedBandListEUTRA_v9a0;


typedef struct OTDOA_ProvideCapabilities_supportedBandListEUTRATag
{
    SupportedBandEUTRA_LPP                             data;
    struct OTDOA_ProvideCapabilities_supportedBandListEUTRATag *next;
}
OTDOA_ProvideCapabilities_supportedBandListEUTRA;


typedef struct OTDOA_ProvideCapabilitiesTag
{
    AsnBitString_MaxSize8                  otdoa_Mode;
    OTDOA_ProvideCapabilities_supportedBandListEUTRA *supportedBandListEUTRA;    /* OPTIONAL */
    OTDOA_ProvideCapabilities_supportedBandListEUTRA_v9a0 *supportedBandListEUTRA_v9a0;    /* OPTIONAL */
    enum OTDOA_ProvideCapabilities_maxSupportedPrsBandwidth_r14 {
        OTDOA_ProvideCapabilities_maxSupportedPrsBandwidth_r14_n6 = 0,
        OTDOA_ProvideCapabilities_maxSupportedPrsBandwidth_r14_n15 = 1,
        OTDOA_ProvideCapabilities_maxSupportedPrsBandwidth_r14_n25 = 2,
        OTDOA_ProvideCapabilities_maxSupportedPrsBandwidth_r14_n50 = 3,
        OTDOA_ProvideCapabilities_maxSupportedPrsBandwidth_r14_n75 = 4,
        OTDOA_ProvideCapabilities_maxSupportedPrsBandwidth_r14_n100 = 5
    } maxSupportedPrsBandwidth_r14;    /* OPTIONAL */
    enum OTDOA_ProvideCapabilities_maxSupportedPrsConfigs_r14 {
        OTDOA_ProvideCapabilities_maxSupportedPrsConfigs_r14_c2 = 0,
        OTDOA_ProvideCapabilities_maxSupportedPrsConfigs_r14_c3 = 1
    } maxSupportedPrsConfigs_r14;    /* OPTIONAL */
    enum OTDOA_ProvideCapabilities_numberOfRXantennas_r14 {
        OTDOA_ProvideCapabilities_numberOfRXantennas_r14_rx1 = 0
    } numberOfRXantennas_r14;    /* OPTIONAL */
    UINT32                                 supportedBandListEUTRAPresent : 1;
    UINT32                                 supportedBandListEUTRA_v9a0Present : 1;
    UINT32                                 interFreqRSTDmeasurement_r10Present : 1;
    UINT32                                 additionalNeighbourCellInfoList_r10Present : 1;
    UINT32                                 prs_id_r14Present : 1;
    UINT32                                 tp_separation_via_muting_r14Present : 1;
    UINT32                                 additional_prs_config_r14Present : 1;
    UINT32                                 prs_based_tbs_r14Present : 1;
    UINT32                                 additionalPathsReport_r14Present : 1;
    UINT32                                 densePrsConfig_r14Present : 1;
    UINT32                                 maxSupportedPrsBandwidth_r14Present : 1;
    UINT32                                 prsOccGroup_r14Present : 1;
    UINT32                                 prsFrequencyHopping_r14Present : 1;
    UINT32                                 maxSupportedPrsConfigs_r14Present : 1;
    UINT32                                 periodicalReporting_r14Present : 1;
    UINT32                                 multiPrbNprs_r14Present : 1;
    UINT32                                 idleStateForMeasurements_r14Present : 1;
    UINT32                                 numberOfRXantennas_r14Present : 1;
    UINT32                                 reserved : 14;
}OTDOA_ProvideCapabilities;


typedef struct OTDOA_RequestLocationInformationTag
{
    BOOL                                   assistanceAvailability;
    UINT8  /* INTEGER (1..32) */           maxNoOfRSTDmeas_r14;    /* OPTIONAL */
    UINT8                                  multipathRSTD_r14Present : 1;
    UINT8                                  maxNoOfRSTDmeas_r14Present : 1;
    UINT8                                  reserved : 6;
}OTDOA_RequestLocationInformation;


typedef struct OTDOA_MeasQualityTag
{
    UINT8  /* BIT STRING (SIZE(2)) */      error_Resolution;
    UINT8  /* BIT STRING (SIZE(5)) */      error_Value;
    UINT8  /* BIT STRING (SIZE(3)) */      error_NumSamples;    /* OPTIONAL */
    UINT8                                  error_NumSamplesPresent : 1;
    UINT8                                  reserved : 7;
}OTDOA_MeasQuality;


typedef struct AdditionalPath_r14Tag
{
    INT16  /* INTEGER (-256..255) */       relativeTimeDifference_r14;
    OTDOA_MeasQuality                      *path_Quality_r14;    /* OPTIONAL */
    UINT8                                  path_Quality_r14Present : 1;
    UINT8                                  reserved : 7;
}AdditionalPath_r14;


typedef struct AdditionalPathList_r14Tag
{
    AdditionalPath_r14                                 data;
    struct AdditionalPathList_r14Tag                   *next;
}
AdditionalPathList_r14;


typedef struct NeighbourMeasurementElement_NB_r14Tag
{
    UINT16  /* INTEGER (0..503) */         physCellIdNeighbour_r14;
    ECGI                                   *cellGlobalIdNeighbour_r14;    /* OPTIONAL */
    ARFCN_ValueEUTRA_r14                   earfcnNeighbour_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..12711) */       rstd_r14;
    OTDOA_MeasQuality                      rstd_Quality_r14;
    UINT16  /* INTEGER (0..4095) */        tpIdNeighbour_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        prsIdNeighbour_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (0..5) */            delta_rstd_r14;    /* OPTIONAL */
    AdditionalPathList_r14                 *additionalPathsNeighbour_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        nprsIdNeighbour_r14;    /* OPTIONAL */
    CarrierFreqOffsetNB_r14                carrierFreqOffsetNB_Neighbour_r14;    /* OPTIONAL */
    UINT8                                  cellGlobalIdNeighbour_r14Present : 1;
    UINT8                                  earfcnNeighbour_r14Present : 1;
    UINT8                                  tpIdNeighbour_r14Present : 1;
    UINT8                                  prsIdNeighbour_r14Present : 1;
    UINT8                                  delta_rstd_r14Present : 1;
    UINT8                                  additionalPathsNeighbour_r14Present : 1;
    UINT8                                  nprsIdNeighbour_r14Present : 1;
    UINT8                                  carrierFreqOffsetNB_Neighbour_r14Present : 1;
}NeighbourMeasurementElement_NB_r14;


typedef struct NeighbourMeasurementList_NB_r14Tag
{
    NeighbourMeasurementElement_NB_r14                 data;
    struct NeighbourMeasurementList_NB_r14Tag          *next;
}
NeighbourMeasurementList_NB_r14;


typedef struct OTDOA_SignalMeasurementInformation_NB_r14Tag
{
    UINT16  /* BIT STRING (SIZE(10)) */    systemFrameNumber_r14;
    UINT16  /* INTEGER (0..503) */         physCellIdRef_r14;
    ECGI                                   *cellGlobalIdRef_r14;    /* OPTIONAL */
    ARFCN_ValueEUTRA_r14                   earfcnRef_r14;    /* OPTIONAL */
    OTDOA_MeasQuality                      *referenceQuality_r14;    /* OPTIONAL */
    NeighbourMeasurementList_NB_r14        neighbourMeasurementList_r14;
    UINT16  /* INTEGER (0..4095) */        tpIdRef_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        prsIdRef_r14;    /* OPTIONAL */
    AdditionalPathList_r14                 *additionalPathsRef_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        nprsIdRef_r14;    /* OPTIONAL */
    CarrierFreqOffsetNB_r14                carrierFreqOffsetNB_Ref_r14;    /* OPTIONAL */
    UINT16  /* BIT STRING (SIZE(10)) */    hyperSFN_r14;    /* OPTIONAL */
    UINT16                                 cellGlobalIdRef_r14Present : 1;
    UINT16                                 earfcnRef_r14Present : 1;
    UINT16                                 referenceQuality_r14Present : 1;
    UINT16                                 tpIdRef_r14Present : 1;
    UINT16                                 prsIdRef_r14Present : 1;
    UINT16                                 additionalPathsRef_r14Present : 1;
    UINT16                                 nprsIdRef_r14Present : 1;
    UINT16                                 carrierFreqOffsetNB_Ref_r14Present : 1;
    UINT16                                 hyperSFN_r14Present : 1;
    UINT16                                 reserved : 7;
}OTDOA_SignalMeasurementInformation_NB_r14;


typedef struct NeighbourMeasurementElementTag
{
    UINT16  /* INTEGER (0..503) */         physCellIdNeighbour;
    ECGI                                   *cellGlobalIdNeighbour;    /* OPTIONAL */
    ARFCN_ValueEUTRA                       earfcnNeighbour;    /* OPTIONAL */
    UINT16  /* INTEGER (0..12711) */       rstd;
    OTDOA_MeasQuality                      rstd_Quality;
    ARFCN_ValueEUTRA_v9a0                  earfcnNeighbour_v9a0;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        tpIdNeighbour_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        prsIdNeighbour_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (0..5) */            delta_rstd_r14;    /* OPTIONAL */
    AdditionalPathList_r14                 *additionalPathsNeighbour_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        nprsIdNeighbour_r14;    /* OPTIONAL */
    CarrierFreqOffsetNB_r14                carrierFreqOffsetNB_Neighbour_r14;    /* OPTIONAL */
    UINT16                                 cellGlobalIdNeighbourPresent : 1;
    UINT16                                 earfcnNeighbourPresent : 1;
    UINT16                                 earfcnNeighbour_v9a0Present : 1;
    UINT16                                 tpIdNeighbour_r14Present : 1;
    UINT16                                 prsIdNeighbour_r14Present : 1;
    UINT16                                 delta_rstd_r14Present : 1;
    UINT16                                 additionalPathsNeighbour_r14Present : 1;
    UINT16                                 nprsIdNeighbour_r14Present : 1;
    UINT16                                 carrierFreqOffsetNB_Neighbour_r14Present : 1;
    UINT16                                 reserved : 7;
}NeighbourMeasurementElement;


typedef struct NeighbourMeasurementListTag
{
    NeighbourMeasurementElement                        data;
    struct NeighbourMeasurementListTag                 *next;
}
NeighbourMeasurementList;


typedef struct OTDOA_SignalMeasurementInformationTag
{
    UINT16  /* BIT STRING (SIZE(10)) */    systemFrameNumber;
    UINT16  /* INTEGER (0..503) */         physCellIdRef;
    ECGI                                   *cellGlobalIdRef;    /* OPTIONAL */
    ARFCN_ValueEUTRA                       earfcnRef;    /* OPTIONAL */
    OTDOA_MeasQuality                      *referenceQuality;    /* OPTIONAL */
    NeighbourMeasurementList               neighbourMeasurementList;
    ARFCN_ValueEUTRA_v9a0                  earfcnRef_v9a0;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        tpIdRef_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        prsIdRef_r14;    /* OPTIONAL */
    AdditionalPathList_r14                 *additionalPathsRef_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        nprsIdRef_r14;    /* OPTIONAL */
    CarrierFreqOffsetNB_r14                carrierFreqOffsetNB_Ref_r14;    /* OPTIONAL */
    UINT16  /* BIT STRING (SIZE(10)) */    hyperSFN_r14;    /* OPTIONAL */
    UINT16                                 cellGlobalIdRefPresent : 1;
    UINT16                                 earfcnRefPresent : 1;
    UINT16                                 referenceQualityPresent : 1;
    UINT16                                 earfcnRef_v9a0Present : 1;
    UINT16                                 tpIdRef_r14Present : 1;
    UINT16                                 prsIdRef_r14Present : 1;
    UINT16                                 additionalPathsRef_r14Present : 1;
    UINT16                                 nprsIdRef_r14Present : 1;
    UINT16                                 carrierFreqOffsetNB_Ref_r14Present : 1;
    UINT16                                 hyperSFN_r14Present : 1;
    UINT16                                 reserved : 6;
}OTDOA_SignalMeasurementInformation;


typedef struct OTDOA_ProvideLocationInformationTag
{
    OTDOA_SignalMeasurementInformation     *otdoaSignalMeasurementInformation;    /* OPTIONAL */
    OTDOA_Error                            *otdoa_Error;    /* OPTIONAL */
    OTDOA_SignalMeasurementInformation_NB_r14 *otdoaSignalMeasurementInformation_NB_r14;    /* OPTIONAL */
    UINT8                                  otdoaSignalMeasurementInformationPresent : 1;
    UINT8                                  otdoa_ErrorPresent : 1;
    UINT8                                  otdoaSignalMeasurementInformation_NB_r14Present : 1;
    UINT8                                  reserved : 5;
}OTDOA_ProvideLocationInformation;


typedef struct OTDOA_RequestAssistanceDataTag
{
    UINT16  /* INTEGER (0..503) */         physCellId;
    AsnBitString_MaxSize8                  *adType_r14;    /* OPTIONAL */
    UINT8                                  adType_r14Present : 1;
    UINT8                                  reserved : 7;
}OTDOA_RequestAssistanceData;


typedef struct NPRS_Info_r14_nprs_MutingInfoA_r14Tag
{
    UINT8       tag;
        #define TAG_NPRS_Info_r14_nprs_MutingInfoA_r14_po2_r14 0
        #define TAG_NPRS_Info_r14_nprs_MutingInfoA_r14_po4_r14 1
        #define TAG_NPRS_Info_r14_nprs_MutingInfoA_r14_po8_r14 2
        #define TAG_NPRS_Info_r14_nprs_MutingInfoA_r14_po16_r14 3
    union {
        UINT8  /* BIT STRING (SIZE(2)) */      po2_r14;
        UINT8  /* BIT STRING (SIZE(4)) */      po4_r14;
        UINT8  /* BIT STRING (SIZE(8)) */      po8_r14;
        UINT16  /* BIT STRING (SIZE(16)) */    po16_r14;
    } choice;
}NPRS_Info_r14_nprs_MutingInfoA_r14;


typedef struct NPRS_Info_r14_partA_r14Tag
{
    struct NPRS_Info_r14_nprsBitmap_r14 {
        UINT8       tag;
            #define TAG_NPRS_Info_r14_nprsBitmap_r14_subframePattern10_r14 0
            #define TAG_NPRS_Info_r14_nprsBitmap_r14_subframePattern40_r14 1
        union {
            UINT16  /* BIT STRING (SIZE(10)) */    subframePattern10_r14;
            AsnBitString_40                        *subframePattern40_r14;
        } choice;
    } nprsBitmap_r14;
    NPRS_Info_r14_nprs_MutingInfoA_r14     *nprs_MutingInfoA_r14;    /* OPTIONAL */
    UINT8                                  nprs_MutingInfoA_r14Present : 1;
    UINT8                                  reserved : 7;
}NPRS_Info_r14_partA_r14;


typedef struct NPRS_Info_r14_nprs_MutingInfoB_r14Tag
{
    UINT8       tag;
        #define TAG_NPRS_Info_r14_nprs_MutingInfoB_r14_po2_r14 0
        #define TAG_NPRS_Info_r14_nprs_MutingInfoB_r14_po4_r14 1
        #define TAG_NPRS_Info_r14_nprs_MutingInfoB_r14_po8_r14 2
        #define TAG_NPRS_Info_r14_nprs_MutingInfoB_r14_po16_r14 3
    union {
        UINT8  /* BIT STRING (SIZE(2)) */      po2_r14;
        UINT8  /* BIT STRING (SIZE(4)) */      po4_r14;
        UINT8  /* BIT STRING (SIZE(8)) */      po8_r14;
        UINT16  /* BIT STRING (SIZE(16)) */    po16_r14;
    } choice;
}NPRS_Info_r14_nprs_MutingInfoB_r14;


typedef struct NPRS_Info_r14_partB_r14Tag
{
    enum NPRS_Info_r14_nprs_Period_r14 {
        NPRS_Info_r14_nprs_Period_r14_ms160 = 0,
        NPRS_Info_r14_nprs_Period_r14_ms320 = 1,
        NPRS_Info_r14_nprs_Period_r14_ms640 = 2,
        NPRS_Info_r14_nprs_Period_r14_ms1280 = 3
    } nprs_Period_r14;
    enum NPRS_Info_r14_nprs_startSF_r14 {
        NPRS_Info_r14_nprs_startSF_r14_zero = 0,
        NPRS_Info_r14_nprs_startSF_r14_one_eighth = 1,
        NPRS_Info_r14_nprs_startSF_r14_two_eighths = 2,
        NPRS_Info_r14_nprs_startSF_r14_three_eighths = 3,
        NPRS_Info_r14_nprs_startSF_r14_four_eighths = 4,
        NPRS_Info_r14_nprs_startSF_r14_five_eighths = 5,
        NPRS_Info_r14_nprs_startSF_r14_six_eighths = 6,
        NPRS_Info_r14_nprs_startSF_r14_seven_eighths = 7
    } nprs_startSF_r14;
    enum NPRS_Info_r14_nprs_NumSF_r14 {
        NPRS_Info_r14_nprs_NumSF_r14_sf10 = 0,
        NPRS_Info_r14_nprs_NumSF_r14_sf20 = 1,
        NPRS_Info_r14_nprs_NumSF_r14_sf40 = 2,
        NPRS_Info_r14_nprs_NumSF_r14_sf80 = 3,
        NPRS_Info_r14_nprs_NumSF_r14_sf160 = 4,
        NPRS_Info_r14_nprs_NumSF_r14_sf320 = 5,
        NPRS_Info_r14_nprs_NumSF_r14_sf640 = 6,
        NPRS_Info_r14_nprs_NumSF_r14_sf1280 = 7
    } nprs_NumSF_r14;
    NPRS_Info_r14_nprs_MutingInfoB_r14     *nprs_MutingInfoB_r14;    /* OPTIONAL */
    UINT8                                  nprs_MutingInfoB_r14Present : 1;
    UINT8                                  reserved : 7;
}NPRS_Info_r14_partB_r14;


typedef struct NPRS_Info_r14Tag
{
    enum NPRS_Info_r14_operationModeInfoNPRS_r14 {
        NPRS_Info_r14_operationModeInfoNPRS_r14_inband = 0,
        NPRS_Info_r14_operationModeInfoNPRS_r14_standalone = 1
    } operationModeInfoNPRS_r14;
    CarrierFreq_NB_r14                     *nprs_carrier_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (0..174) */          nprsSequenceInfo_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        nprsID_r14;    /* OPTIONAL */
    NPRS_Info_r14_partA_r14                *partA_r14;    /* OPTIONAL */
    NPRS_Info_r14_partB_r14                *partB_r14;    /* OPTIONAL */
    UINT8                                  nprs_carrier_r14Present : 1;
    UINT8                                  nprsSequenceInfo_r14Present : 1;
    UINT8                                  nprsID_r14Present : 1;
    UINT8                                  partA_r14Present : 1;
    UINT8                                  partB_r14Present : 1;
    UINT8                                  reserved : 3;
}NPRS_Info_r14;


typedef struct PRS_Info_NB_r14Tag
{
    NPRS_Info_r14                                      data;
    struct PRS_Info_NB_r14Tag                          *next;
}
PRS_Info_NB_r14;


typedef struct OTDOA_NeighbourCellInfoNB_r14Tag
{
    UINT16  /* INTEGER (0..503) */         physCellIdNB_r14;    /* OPTIONAL */
    ECGI                                   *cellGlobalIdNB_r14;    /* OPTIONAL */
    CarrierFreq_NB_r14                     *carrierFreq_r14;    /* OPTIONAL */
    ARFCN_ValueEUTRA_r14                   earfcn_r14;    /* OPTIONAL */
    enum OTDOA_NeighbourCellInfoNB_r14_eutra_NumCRS_Ports_r14 {
        OTDOA_NeighbourCellInfoNB_r14_eutra_NumCRS_Ports_r14_ports_1_or_2 = 0,
        OTDOA_NeighbourCellInfoNB_r14_eutra_NumCRS_Ports_r14_ports_4 = 1
    } eutra_NumCRS_Ports_r14;    /* OPTIONAL */
    enum OTDOA_NeighbourCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14 {
        OTDOA_NeighbourCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14_r4 = 0,
        OTDOA_NeighbourCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14_r8 = 1,
        OTDOA_NeighbourCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14_r16 = 2
    } otdoa_SIB1_NB_repetitions_r14;    /* OPTIONAL */
    PRS_Info_NB_r14                        *nprsInfo_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (0..19) */           nprs_slotNumberOffset_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (0..63) */           nprs_SFN_Offset_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..1279) */        nprs_SubframeOffset_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..16383) */       expectedRSTD_r14;    /* OPTIONAL */
    UINT16  /* INTEGER (0..1023) */        expectedRSTD_Uncertainty_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (1..72) */           prsNeighbourCellIndex_r14;    /* OPTIONAL */
    PRS_Info_NB_r14                        *nprsInfo_Type2_v1470;    /* OPTIONAL */
    UINT16                                 physCellIdNB_r14Present : 1;
    UINT16                                 cellGlobalIdNB_r14Present : 1;
    UINT16                                 carrierFreq_r14Present : 1;
    UINT16                                 earfcn_r14Present : 1;
    UINT16                                 eutra_NumCRS_Ports_r14Present : 1;
    UINT16                                 otdoa_SIB1_NB_repetitions_r14Present : 1;
    UINT16                                 nprsInfo_r14Present : 1;
    UINT16                                 nprs_slotNumberOffset_r14Present : 1;
    UINT16                                 nprs_SFN_Offset_r14Present : 1;
    UINT16                                 nprs_SubframeOffset_r14Present : 1;
    UINT16                                 expectedRSTD_r14Present : 1;
    UINT16                                 expectedRSTD_Uncertainty_r14Present : 1;
    UINT16                                 prsNeighbourCellIndex_r14Present : 1;
    UINT16                                 nprsInfo_Type2_v1470Present : 1;
    UINT16                                 reserved : 2;
}OTDOA_NeighbourCellInfoNB_r14;


typedef struct OTDOA_NeighbourCellInfoListNB_r14Tag
{
    OTDOA_NeighbourCellInfoNB_r14                      data;
    struct OTDOA_NeighbourCellInfoListNB_r14Tag        *next;
}
OTDOA_NeighbourCellInfoListNB_r14;


typedef struct OTDOA_ReferenceCellInfoNB_r14Tag
{
    UINT16  /* INTEGER (0..503) */         physCellIdNB_r14;    /* OPTIONAL */
    ECGI                                   *cellGlobalIdNB_r14;    /* OPTIONAL */
    CarrierFreq_NB_r14                     *carrierFreqRef_r14;    /* OPTIONAL */
    ARFCN_ValueEUTRA_r14                   earfcn_r14;    /* OPTIONAL */
    enum OTDOA_ReferenceCellInfoNB_r14_eutra_NumCRS_Ports_r14 {
        OTDOA_ReferenceCellInfoNB_r14_eutra_NumCRS_Ports_r14_ports1_or_2 = 0,
        OTDOA_ReferenceCellInfoNB_r14_eutra_NumCRS_Ports_r14_ports4 = 1
    } eutra_NumCRS_Ports_r14;    /* OPTIONAL */
    enum OTDOA_ReferenceCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14 {
        OTDOA_ReferenceCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14_r4 = 0,
        OTDOA_ReferenceCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14_r8 = 1,
        OTDOA_ReferenceCellInfoNB_r14_otdoa_SIB1_NB_repetitions_r14_r16 = 2
    } otdoa_SIB1_NB_repetitions_r14;    /* OPTIONAL */
    PRS_Info_NB_r14                        *nprsInfo_r14;    /* OPTIONAL */
    PRS_Info_NB_r14                        *nprsInfo_Type2_v1470;    /* OPTIONAL */
    UINT8                                  physCellIdNB_r14Present : 1;
    UINT8                                  cellGlobalIdNB_r14Present : 1;
    UINT8                                  carrierFreqRef_r14Present : 1;
    UINT8                                  earfcn_r14Present : 1;
    UINT8                                  eutra_NumCRS_Ports_r14Present : 1;
    UINT8                                  otdoa_SIB1_NB_repetitions_r14Present : 1;
    UINT8                                  nprsInfo_r14Present : 1;
    UINT8                                  nprsInfo_Type2_v1470Present : 1;
}OTDOA_ReferenceCellInfoNB_r14;


typedef struct PRS_Info_prs_MutingInfo_r9Tag
{
    UINT8       tag;
        #define TAG_PRS_Info_prs_MutingInfo_r9_po2_r9 0
        #define TAG_PRS_Info_prs_MutingInfo_r9_po4_r9 1
        #define TAG_PRS_Info_prs_MutingInfo_r9_po8_r9 2
        #define TAG_PRS_Info_prs_MutingInfo_r9_po16_r9 3
        #define TAG_PRS_Info_prs_MutingInfo_r9_po32_v1420 4
        #define TAG_PRS_Info_prs_MutingInfo_r9_po64_v1420 5
        #define TAG_PRS_Info_prs_MutingInfo_r9_po128_v1420 6
        #define TAG_PRS_Info_prs_MutingInfo_r9_po256_v1420 7
        #define TAG_PRS_Info_prs_MutingInfo_r9_po512_v1420 8
        #define TAG_PRS_Info_prs_MutingInfo_r9_po1024_v1420 9
    union {
        UINT8  /* BIT STRING (SIZE(2)) */      po2_r9;
        UINT8  /* BIT STRING (SIZE(4)) */      po4_r9;
        UINT8  /* BIT STRING (SIZE(8)) */      po8_r9;
        UINT16  /* BIT STRING (SIZE(16)) */    po16_r9;
        UINT32  /* BIT STRING (SIZE(32)) */    po32_v1420;
        AsnBitString_64                        *po64_v1420;
        AsnBitString_128                       *po128_v1420;
        AsnBitString_256                       *po256_v1420;
        AsnBitString_512                       *po512_v1420;
        AsnBitString_1024                      *po1024_v1420;
    } choice;
}PRS_Info_prs_MutingInfo_r9;


typedef struct PRS_Info_nb4_r14Tag
{
    /* SEQUENCE (SIZE (3)) OF */
    UINT8  /* INTEGER(0..maxAvailNarrowBands_Minus1_r14) */ data[3];
}
PRS_Info_nb4_r14;


typedef struct PRS_Info_prsHoppingInfo_r14Tag
{
    UINT8       tag;
        #define TAG_PRS_Info_prsHoppingInfo_r14_nb2_r14 0
        #define TAG_PRS_Info_prsHoppingInfo_r14_nb4_r14 1
    union {
        UINT8  /* INTEGER (0..15) */           nb2_r14;
        PRS_Info_nb4_r14                       *nb4_r14;
    } choice;
}PRS_Info_prsHoppingInfo_r14;


typedef struct PRS_InfoTag
{
    enum PRS_Info_prs_Bandwidth {
        PRS_Info_prs_Bandwidth_n6 = 0,
        PRS_Info_prs_Bandwidth_n15 = 1,
        PRS_Info_prs_Bandwidth_n25 = 2,
        PRS_Info_prs_Bandwidth_n50 = 3,
        PRS_Info_prs_Bandwidth_n75 = 4,
        PRS_Info_prs_Bandwidth_n100 = 5
    } prs_Bandwidth;
    UINT16  /* INTEGER (0..4095) */        prs_ConfigurationIndex;
    enum PRS_Info_numDL_Frames {
        PRS_Info_numDL_Frames_sf_1 = 0,
        PRS_Info_numDL_Frames_sf_2 = 1,
        PRS_Info_numDL_Frames_sf_4 = 2,
        PRS_Info_numDL_Frames_sf_6 = 3,
        PRS_Info_numDL_Frames_sf_add_v1420 = 4
    } numDL_Frames;
    PRS_Info_prs_MutingInfo_r9             *prs_MutingInfo_r9;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        prsID_r14;    /* OPTIONAL */
    UINT8  /* INTEGER (1..160) */          add_numDL_Frames_r14;    /* OPTIONAL */
    enum PRS_Info_prsOccGroupLen_r14 {
        PRS_Info_prsOccGroupLen_r14_g2 = 0,
        PRS_Info_prsOccGroupLen_r14_g4 = 1,
        PRS_Info_prsOccGroupLen_r14_g8 = 2,
        PRS_Info_prsOccGroupLen_r14_g16 = 3,
        PRS_Info_prsOccGroupLen_r14_g32 = 4,
        PRS_Info_prsOccGroupLen_r14_g64 = 5,
        PRS_Info_prsOccGroupLen_r14_g128 = 6
    } prsOccGroupLen_r14;    /* OPTIONAL */
    PRS_Info_prsHoppingInfo_r14            *prsHoppingInfo_r14;    /* OPTIONAL */
    UINT8                                  prs_MutingInfo_r9Present : 1;
    UINT8                                  prsID_r14Present : 1;
    UINT8                                  add_numDL_Frames_r14Present : 1;
    UINT8                                  prsOccGroupLen_r14Present : 1;
    UINT8                                  prsHoppingInfo_r14Present : 1;
    UINT8                                  reserved : 3;
}PRS_Info;


typedef struct Add_PRSconfigNeighbourElement_r14Tag
{
    PRS_Info                               *add_prsInfo_r14;    /* OPTIONAL */
    UINT8                                  add_prsInfo_r14Present : 1;
    UINT8                                  reserved : 7;
}Add_PRSconfigNeighbourElement_r14;


typedef struct OTDOA_NeighbourCellInfoElement_addPRSconfigNeighbour_r14Tag
{
    Add_PRSconfigNeighbourElement_r14                  data;
    struct OTDOA_NeighbourCellInfoElement_addPRSconfigNeighbour_r14Tag *next;
}
OTDOA_NeighbourCellInfoElement_addPRSconfigNeighbour_r14;


typedef struct OTDOA_NeighbourCellInfoElementTag
{
    UINT16  /* INTEGER (0..503) */         physCellId;
    ECGI                                   *cellGlobalId;    /* OPTIONAL */
    ARFCN_ValueEUTRA                       earfcn;    /* OPTIONAL */
    enum OTDOA_NeighbourCellInfoElement_cpLength {
        OTDOA_NeighbourCellInfoElement_cpLength_normal = 0,
        OTDOA_NeighbourCellInfoElement_cpLength_extended = 1
    } cpLength;    /* OPTIONAL */
    PRS_Info                               *prsInfo;    /* OPTIONAL */
    enum OTDOA_NeighbourCellInfoElement_antennaPortConfig {
        OTDOA_NeighbourCellInfoElement_antennaPortConfig_ports_1_or_2 = 0,
        OTDOA_NeighbourCellInfoElement_antennaPortConfig_ports_4 = 1
    } antennaPortConfig;    /* OPTIONAL */
    UINT8  /* INTEGER (0..19) */           slotNumberOffset;    /* OPTIONAL */
    UINT16  /* INTEGER (0..1279) */        prs_SubframeOffset;    /* OPTIONAL */
    UINT16  /* INTEGER (0..16383) */       expectedRSTD;
    UINT16  /* INTEGER (0..1023) */        expectedRSTD_Uncertainty;
    ARFCN_ValueEUTRA_v9a0                  earfcn_v9a0;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        tpId_r14;    /* OPTIONAL */
    enum OTDOA_NeighbourCellInfoElement_cpLengthCRS_r14 {
        OTDOA_NeighbourCellInfoElement_cpLengthCRS_r14_normal = 0,
        OTDOA_NeighbourCellInfoElement_cpLengthCRS_r14_extended = 1
    } cpLengthCRS_r14;    /* OPTIONAL */
    BOOL                                   sameMBSFNconfigNeighbour_r14;    /* OPTIONAL */
    enum OTDOA_NeighbourCellInfoElement_dlBandwidth_r14 {
        OTDOA_NeighbourCellInfoElement_dlBandwidth_r14_n6 = 0,
        OTDOA_NeighbourCellInfoElement_dlBandwidth_r14_n15 = 1,
        OTDOA_NeighbourCellInfoElement_dlBandwidth_r14_n25 = 2,
        OTDOA_NeighbourCellInfoElement_dlBandwidth_r14_n50 = 3,
        OTDOA_NeighbourCellInfoElement_dlBandwidth_r14_n75 = 4,
        OTDOA_NeighbourCellInfoElement_dlBandwidth_r14_n100 = 5
    } dlBandwidth_r14;    /* OPTIONAL */
    OTDOA_NeighbourCellInfoElement_addPRSconfigNeighbour_r14 *addPRSconfigNeighbour_r14;    /* OPTIONAL */
    UINT16                                 cellGlobalIdPresent : 1;
    UINT16                                 earfcnPresent : 1;
    UINT16                                 cpLengthPresent : 1;
    UINT16                                 prsInfoPresent : 1;
    UINT16                                 antennaPortConfigPresent : 1;
    UINT16                                 slotNumberOffsetPresent : 1;
    UINT16                                 prs_SubframeOffsetPresent : 1;
    UINT16                                 earfcn_v9a0Present : 1;
    UINT16                                 tpId_r14Present : 1;
    UINT16                                 prs_only_tp_r14Present : 1;
    UINT16                                 cpLengthCRS_r14Present : 1;
    UINT16                                 sameMBSFNconfigNeighbour_r14Present : 1;
    UINT16                                 dlBandwidth_r14Present : 1;
    UINT16                                 addPRSconfigNeighbour_r14Present : 1;
    UINT16                                 reserved : 2;
}OTDOA_NeighbourCellInfoElement;


typedef struct OTDOA_NeighbourFreqInfoTag
{
    OTDOA_NeighbourCellInfoElement                     data;
    struct OTDOA_NeighbourFreqInfoTag                  *next;
}
OTDOA_NeighbourFreqInfo;


typedef struct OTDOA_NeighbourCellInfoListTag
{
    OTDOA_NeighbourFreqInfo                            data;
    struct OTDOA_NeighbourCellInfoListTag              *next;
}
OTDOA_NeighbourCellInfoList;


typedef struct OTDOA_ReferenceCellInfo_addPRSconfigRef_r14Tag
{
    PRS_Info                                           data;
    struct OTDOA_ReferenceCellInfo_addPRSconfigRef_r14Tag *next;
}
OTDOA_ReferenceCellInfo_addPRSconfigRef_r14;


typedef struct OTDOA_ReferenceCellInfoTag
{
    UINT16  /* INTEGER (0..503) */         physCellId;
    ECGI                                   *cellGlobalId;    /* OPTIONAL */
    ARFCN_ValueEUTRA                       earfcnRef;    /* OPTIONAL */
    enum OTDOA_ReferenceCellInfo_antennaPortConfig {
        OTDOA_ReferenceCellInfo_antennaPortConfig_ports1_or_2 = 0,
        OTDOA_ReferenceCellInfo_antennaPortConfig_ports4 = 1
    } antennaPortConfig;    /* OPTIONAL */
    enum OTDOA_ReferenceCellInfo_cpLength {
        OTDOA_ReferenceCellInfo_cpLength_normal = 0,
        OTDOA_ReferenceCellInfo_cpLength_extended = 1
    } cpLength;
    PRS_Info                               *prsInfo;    /* OPTIONAL */
    ARFCN_ValueEUTRA_v9a0                  earfcnRef_v9a0;    /* OPTIONAL */
    UINT16  /* INTEGER (0..4095) */        tpId_r14;    /* OPTIONAL */
    enum OTDOA_ReferenceCellInfo_cpLengthCRS_r14 {
        OTDOA_ReferenceCellInfo_cpLengthCRS_r14_normal = 0,
        OTDOA_ReferenceCellInfo_cpLengthCRS_r14_extended = 1
    } cpLengthCRS_r14;    /* OPTIONAL */
    BOOL                                   sameMBSFNconfigRef_r14;    /* OPTIONAL */
    enum OTDOA_ReferenceCellInfo_dlBandwidth_r14 {
        OTDOA_ReferenceCellInfo_dlBandwidth_r14_n6 = 0,
        OTDOA_ReferenceCellInfo_dlBandwidth_r14_n15 = 1,
        OTDOA_ReferenceCellInfo_dlBandwidth_r14_n25 = 2,
        OTDOA_ReferenceCellInfo_dlBandwidth_r14_n50 = 3,
        OTDOA_ReferenceCellInfo_dlBandwidth_r14_n75 = 4,
        OTDOA_ReferenceCellInfo_dlBandwidth_r14_n100 = 5
    } dlBandwidth_r14;    /* OPTIONAL */
    OTDOA_ReferenceCellInfo_addPRSconfigRef_r14 *addPRSconfigRef_r14;    /* OPTIONAL */
    UINT16                                 cellGlobalIdPresent : 1;
    UINT16                                 earfcnRefPresent : 1;
    UINT16                                 antennaPortConfigPresent : 1;
    UINT16                                 prsInfoPresent : 1;
    UINT16                                 earfcnRef_v9a0Present : 1;
    UINT16                                 tpId_r14Present : 1;
    UINT16                                 cpLengthCRS_r14Present : 1;
    UINT16                                 sameMBSFNconfigRef_r14Present : 1;
    UINT16                                 dlBandwidth_r14Present : 1;
    UINT16                                 addPRSconfigRef_r14Present : 1;
    UINT16                                 reserved : 6;
}OTDOA_ReferenceCellInfo;


typedef struct OTDOA_ProvideAssistanceDataTag
{
    OTDOA_ReferenceCellInfo                *otdoa_ReferenceCellInfo;    /* OPTIONAL */
    OTDOA_NeighbourCellInfoList            *otdoa_NeighbourCellInfo;    /* OPTIONAL */
    OTDOA_Error                            *otdoa_Error;    /* OPTIONAL */
    OTDOA_ReferenceCellInfoNB_r14          *otdoa_ReferenceCellInfoNB_r14;    /* OPTIONAL */
    OTDOA_NeighbourCellInfoListNB_r14      *otdoa_NeighbourCellInfoNB_r14;    /* OPTIONAL */
    UINT8                                  otdoa_ReferenceCellInfoPresent : 1;
    UINT8                                  otdoa_NeighbourCellInfoPresent : 1;
    UINT8                                  otdoa_ErrorPresent : 1;
    UINT8                                  otdoa_ReferenceCellInfoNB_r14Present : 1;
    UINT8                                  otdoa_NeighbourCellInfoNB_r14Present : 1;
    UINT8                                  reserved : 3;
}OTDOA_ProvideAssistanceData;


typedef struct CommonIEsErrorTag
{
    enum CommonIEsError_errorCause {
        CommonIEsError_errorCause_undefined = 0,
        CommonIEsError_errorCause_lppMessageHeaderError = 1,
        CommonIEsError_errorCause_lppMessageBodyError = 2,
        CommonIEsError_errorCause_epduError = 3,
        CommonIEsError_errorCause_incorrectDataValue = 4,
        CommonIEsError_errorCause_lppSegmentationError_v1450 = 5
    } errorCause;
}CommonIEsError;


typedef struct CommonIEsAbortTag
{
    enum CommonIEsAbort_abortCause {
        CommonIEsAbort_abortCause_undefined = 0,
        CommonIEsAbort_abortCause_stopPeriodicReporting = 1,
        CommonIEsAbort_abortCause_targetDeviceAbort = 2,
        CommonIEsAbort_abortCause_networkAbort = 3
    } abortCause;
}CommonIEsAbort;


typedef AsnBitString_MaxSize16                             LocationSource_r13;


typedef enum EarlyFixReport_r12Tag
{
    EarlyFixReport_r12_noMoreMessages = 0,
    EarlyFixReport_r12_moreMessagesOnTheWay = 1
}EarlyFixReport_r12;


typedef enum LocationFailureCauseTag
{
    LocationFailureCause_undefined = 0,
    LocationFailureCause_requestedMethodNotSupported = 1,
    LocationFailureCause_positionMethodFailure = 2,
    LocationFailureCause_periodicLocationMeasurementsNotAvailable = 3
}LocationFailureCause;


typedef struct LocationErrorTag
{
    LocationFailureCause                   locationfailurecause;
}LocationError;


typedef struct HorizontalVelocityTag
{
    UINT16  /* INTEGER (0..359) */         bearing;
    UINT16  /* INTEGER (0..2047) */        horizontalSpeed;
}HorizontalVelocity;


typedef struct HorizontalWithVerticalVelocityTag
{
    UINT16  /* INTEGER (0..359) */         bearing;
    UINT16  /* INTEGER (0..2047) */        horizontalSpeed;
    enum HorizontalWithVerticalVelocity_verticalDirection {
        HorizontalWithVerticalVelocity_verticalDirection_upward = 0,
        HorizontalWithVerticalVelocity_verticalDirection_downward = 1
    } verticalDirection;
    UINT8  /* INTEGER (0..255) */          verticalSpeed;
}HorizontalWithVerticalVelocity;


typedef struct HorizontalVelocityWithUncertaintyTag
{
    UINT16  /* INTEGER (0..359) */         bearing;
    UINT16  /* INTEGER (0..2047) */        horizontalSpeed;
    UINT8  /* INTEGER (0..255) */          uncertaintySpeed;
}HorizontalVelocityWithUncertainty;


typedef struct HorizontalWithVerticalVelocityAndUncertaintyTag
{
    UINT16  /* INTEGER (0..359) */         bearing;
    UINT16  /* INTEGER (0..2047) */        horizontalSpeed;
    enum HorizontalWithVerticalVelocityAndUncertainty_verticalDirection {
        HorizontalWithVerticalVelocityAndUncertainty_verticalDirection_upward = 0,
        HorizontalWithVerticalVelocityAndUncertainty_verticalDirection_downward = 1
    } verticalDirection;
    UINT8  /* INTEGER (0..255) */          verticalSpeed;
    UINT8  /* INTEGER (0..255) */          horizontalUncertaintySpeed;
    UINT8  /* INTEGER (0..255) */          verticalUncertaintySpeed;
}HorizontalWithVerticalVelocityAndUncertainty;


typedef struct VelocityTag
{
    UINT8       tag;
        #define TAG_Velocity_horizontalVelocity 0
        #define TAG_Velocity_horizontalWithVerticalVelocity 1
        #define TAG_Velocity_horizontalVelocityWithUncertainty 2
        #define TAG_Velocity_horizontalWithVerticalVelocityAndUncertainty 3
    union {
        HorizontalVelocity                     *horizontalVelocity;
        HorizontalWithVerticalVelocity         *horizontalWithVerticalVelocity;
        HorizontalVelocityWithUncertainty      *horizontalVelocityWithUncertainty;
        HorizontalWithVerticalVelocityAndUncertainty *horizontalWithVerticalVelocityAndUncertainty;
    } choice;
}Velocity;


typedef struct Ellipsoid_PointTag
{
    enum Ellipsoid_Point_latitudeSign {
        Ellipsoid_Point_latitudeSign_north = 0,
        Ellipsoid_Point_latitudeSign_south = 1
    } latitudeSign;
    UINT32  /* INTEGER (0..8388607) */     degreesLatitude;
    INT32  /* INTEGER (-8388608..8388607) */ degreesLongitude;
}Ellipsoid_Point;


typedef struct Ellipsoid_PointWithUncertaintyCircleTag
{
    enum Ellipsoid_PointWithUncertaintyCircle_latitudeSign {
        Ellipsoid_PointWithUncertaintyCircle_latitudeSign_north = 0,
        Ellipsoid_PointWithUncertaintyCircle_latitudeSign_south = 1
    } latitudeSign;
    UINT32  /* INTEGER (0..8388607) */     degreesLatitude;
    INT32  /* INTEGER (-8388608..8388607) */ degreesLongitude;
    UINT8  /* INTEGER (0..127) */          uncertainty;
}Ellipsoid_PointWithUncertaintyCircle;


typedef struct EllipsoidPointWithUncertaintyEllipseTag
{
    enum EllipsoidPointWithUncertaintyEllipse_latitudeSign {
        EllipsoidPointWithUncertaintyEllipse_latitudeSign_north = 0,
        EllipsoidPointWithUncertaintyEllipse_latitudeSign_south = 1
    } latitudeSign;
    UINT32  /* INTEGER (0..8388607) */     degreesLatitude;
    INT32  /* INTEGER (-8388608..8388607) */ degreesLongitude;
    UINT8  /* INTEGER (0..127) */          uncertaintySemiMajor;
    UINT8  /* INTEGER (0..127) */          uncertaintySemiMinor;
    UINT8  /* INTEGER (0..179) */          orientationMajorAxis;
    UINT8  /* INTEGER (0..100) */          confidence;
}EllipsoidPointWithUncertaintyEllipse;


typedef struct PolygonPointsTag
{
    enum PolygonPoints_latitudeSign {
        PolygonPoints_latitudeSign_north = 0,
        PolygonPoints_latitudeSign_south = 1
    } latitudeSign;
    UINT32  /* INTEGER (0..8388607) */     degreesLatitude;
    INT32  /* INTEGER (-8388608..8388607) */ degreesLongitude;
}PolygonPoints;


typedef struct PolygonListTag
{
    PolygonPoints                                      data;
    struct PolygonListTag                              *next;
}
PolygonList;


typedef struct EllipsoidPointWithAltitudeTag
{
    enum EllipsoidPointWithAltitude_latitudeSign {
        EllipsoidPointWithAltitude_latitudeSign_north = 0,
        EllipsoidPointWithAltitude_latitudeSign_south = 1
    } latitudeSign;
    UINT32  /* INTEGER (0..8388607) */     degreesLatitude;
    INT32  /* INTEGER (-8388608..8388607) */ degreesLongitude;
    enum EllipsoidPointWithAltitude_altitudeDirection {
        EllipsoidPointWithAltitude_altitudeDirection_height = 0,
        EllipsoidPointWithAltitude_altitudeDirection_depth = 1
    } altitudeDirection;
    UINT16  /* INTEGER (0..32767) */       altitude;
}EllipsoidPointWithAltitude;


typedef struct EllipsoidArcTag
{
    enum EllipsoidArc_latitudeSign {
        EllipsoidArc_latitudeSign_north = 0,
        EllipsoidArc_latitudeSign_south = 1
    } latitudeSign;
    UINT32  /* INTEGER (0..8388607) */     degreesLatitude;
    INT32  /* INTEGER (-8388608..8388607) */ degreesLongitude;
    UINT16  /* INTEGER (0..65535) */       innerRadius;
    UINT8  /* INTEGER (0..127) */          uncertaintyRadius;
    UINT8  /* INTEGER (0..179) */          offsetAngle;
    UINT8  /* INTEGER (0..179) */          includedAngle;
    UINT8  /* INTEGER (0..100) */          confidence;
}EllipsoidArc;


typedef struct LocationCoordinatesTag
{
    UINT8       tag;
        #define TAG_LocationCoordinates_ellipsoidPoint 0
        #define TAG_LocationCoordinates_ellipsoidPointWithUncertaintyCircle 1
        #define TAG_LocationCoordinates_ellipsoidPointWithUncertaintyEllipse 2
        #define TAG_LocationCoordinates_polygon 3
        #define TAG_LocationCoordinates_ellipsoidPointWithAltitude 4
        #define TAG_LocationCoordinates_ellipsoidPointWithAltitudeAndUncertaintyEllipsoid 5
        #define TAG_LocationCoordinates_ellipsoidArc 6
    union {
        Ellipsoid_Point                        *ellipsoidPoint;
        Ellipsoid_PointWithUncertaintyCircle   *ellipsoidPointWithUncertaintyCircle;
        EllipsoidPointWithUncertaintyEllipse   *ellipsoidPointWithUncertaintyEllipse;
        PolygonList                            *polygon;
        EllipsoidPointWithAltitude             *ellipsoidPointWithAltitude;
        EllipsoidPointWithAltitudeAndUncertaintyEllipsoid *ellipsoidPointWithAltitudeAndUncertaintyEllipsoid;
        EllipsoidArc                           *ellipsoidArc;
    } choice;
}LocationCoordinates;


typedef enum SegmentationInfo_r14Tag
{
    SegmentationInfo_r14_noMoreMessages = 0,
    SegmentationInfo_r14_moreMessagesOnTheWay = 1
}SegmentationInfo_r14;


typedef struct CommonIEsProvideLocationInformationTag
{
    LocationCoordinates                    *locationEstimate;    /* OPTIONAL */
    Velocity                               *velocityEstimate;    /* OPTIONAL */
    LocationError                          *locationError;    /* OPTIONAL */
    EarlyFixReport_r12                     earlyFixReport_r12;    /* OPTIONAL */
    LocationSource_r13                     *locationSource_r13;    /* OPTIONAL */
    UTCTime                                *locationTimestamp_r13;    /* OPTIONAL */
    SegmentationInfo_r14                   segmentationInfo_r14;    /* OPTIONAL */
    UINT8                                  locationEstimatePresent : 1;
    UINT8                                  velocityEstimatePresent : 1;
    UINT8                                  locationErrorPresent : 1;
    UINT8                                  earlyFixReport_r12Present : 1;
    UINT8                                  locationSource_r13Present : 1;
    UINT8                                  locationTimestamp_r13Present : 1;
    UINT8                                  segmentationInfo_r14Present : 1;
    UINT8                                  reserved : 1;
}CommonIEsProvideLocationInformation;


typedef struct MessageSizeLimitNB_r14Tag
{
    UINT16  /* INTEGER (1..512) */         measurementLimit_r14;    /* OPTIONAL */
    UINT8                                  measurementLimit_r14Present : 1;
    UINT8                                  reserved : 7;
}MessageSizeLimitNB_r14;


typedef enum EnvironmentTag
{
    Environment_badArea = 0,
    Environment_notBadArea = 1,
    Environment_mixedArea = 2
}Environment;


typedef struct ResponseTimeNB_r14Tag
{
    UINT16  /* INTEGER (1..512) */         timeNB_r14;
    UINT16  /* INTEGER (1..512) */         responseTimeEarlyFixNB_r14;    /* OPTIONAL */
    UINT8                                  responseTimeEarlyFixNB_r14Present : 1;
    UINT8                                  reserved : 7;
}ResponseTimeNB_r14;


typedef struct ResponseTimeLppTag
{
    UINT8  /* INTEGER (1..128) */          time;
    UINT8  /* INTEGER (1..128) */          responseTimeEarlyFix_r12;    /* OPTIONAL */
    UINT8                                  responseTimeEarlyFix_r12Present : 1;
    UINT8                                  reserved : 7;
}ResponseTimeLpp;


typedef struct VerticalAccuracyLppTag
{
    UINT8  /* INTEGER (0..127) */          accuracy;
    UINT8  /* INTEGER (0..100) */          confidence;
}VerticalAccuracyLpp;


typedef struct HorizontalAccuracyLppTag
{
    UINT8  /* INTEGER (0..127) */          accuracy;
    UINT8  /* INTEGER (0..100) */          confidence;
}HorizontalAccuracyLpp;


typedef struct QoSTag
{
    HorizontalAccuracyLpp                  *horizontalAccuracy;    /* OPTIONAL */
    BOOL                                   verticalCoordinateRequest;
    VerticalAccuracyLpp                    *verticalAccuracy;    /* OPTIONAL */
    ResponseTimeLpp                        *responseTime;    /* OPTIONAL */
    BOOL                                   velocityRequest;
    ResponseTimeNB_r14                     *responseTimeNB_r14;    /* OPTIONAL */
    UINT8                                  horizontalAccuracyPresent : 1;
    UINT8                                  verticalAccuracyPresent : 1;
    UINT8                                  responseTimePresent : 1;
    UINT8                                  responseTimeNB_r14Present : 1;
    UINT8                                  reserved : 4;
}QoS;


typedef enum AdditionalInformationLppTag
{
    AdditionalInformationLpp_onlyReturnInformationRequested = 0,
    AdditionalInformationLpp_mayReturnAditionalInformation = 1
}AdditionalInformationLpp;


typedef struct TriggeredReportingCriteriaTag
{
    BOOL                                   cellChange;
    ReportingDuration                      reportingDuration;
}TriggeredReportingCriteria;


typedef struct PeriodicalReportingCriteriaTag
{
    enum PeriodicalReportingCriteria_reportingAmount {
        PeriodicalReportingCriteria_reportingAmount_ra1 = 0,
        PeriodicalReportingCriteria_reportingAmount_ra2 = 1,
        PeriodicalReportingCriteria_reportingAmount_ra4 = 2,
        PeriodicalReportingCriteria_reportingAmount_ra8 = 3,
        PeriodicalReportingCriteria_reportingAmount_ra16 = 4,
        PeriodicalReportingCriteria_reportingAmount_ra32 = 5,
        PeriodicalReportingCriteria_reportingAmount_ra64 = 6,
        PeriodicalReportingCriteria_reportingAmount_ra_Infinity = 7
    } reportingAmount;    /* DEFAULT ra_Infinity */
    enum PeriodicalReportingCriteria_reportingInterval {
        PeriodicalReportingCriteria_reportingInterval_noPeriodicalReporting = 0,
        PeriodicalReportingCriteria_reportingInterval_ri0_25 = 1,
        PeriodicalReportingCriteria_reportingInterval_ri0_5 = 2,
        PeriodicalReportingCriteria_reportingInterval_ri1 = 3,
        PeriodicalReportingCriteria_reportingInterval_ri2 = 4,
        PeriodicalReportingCriteria_reportingInterval_ri4 = 5,
        PeriodicalReportingCriteria_reportingInterval_ri8 = 6,
        PeriodicalReportingCriteria_reportingInterval_ri16 = 7,
        PeriodicalReportingCriteria_reportingInterval_ri32 = 8,
        PeriodicalReportingCriteria_reportingInterval_ri64 = 9
    } reportingInterval;
    UINT8                                  reportingAmountPresent : 1;
    UINT8                                  reserved : 7;
}PeriodicalReportingCriteria;


typedef enum LocationInformationTypeTag
{
    LocationInformationType_locationEstimateRequired = 0,
    LocationInformationType_locationMeasurementsRequired = 1,
    LocationInformationType_locationEstimatePreferred = 2,
    LocationInformationType_locationMeasurementsPreferred = 3
}LocationInformationType;


typedef struct CommonIEsRequestLocationInformationTag
{
    LocationInformationType                locationInformationType;
    TriggeredReportingCriteria             *triggeredReporting;    /* OPTIONAL */
    PeriodicalReportingCriteria            *periodicalReporting;    /* OPTIONAL */
    AdditionalInformationLpp               additionalInformation;    /* OPTIONAL */
    QoS                                    *qos;    /* OPTIONAL */
    Environment                            environment;    /* OPTIONAL */
    LocationCoordinateTypes                *locationCoordinateTypes;    /* OPTIONAL */
    VelocityTypes                          *velocityTypes;    /* OPTIONAL */
    MessageSizeLimitNB_r14                 *messageSizeLimitNB_r14;    /* OPTIONAL */
    SegmentationInfo_r14                   segmentationInfo_r14;    /* OPTIONAL */
    UINT16                                 triggeredReportingPresent : 1;
    UINT16                                 periodicalReportingPresent : 1;
    UINT16                                 additionalInformationPresent : 1;
    UINT16                                 qosPresent : 1;
    UINT16                                 environmentPresent : 1;
    UINT16                                 locationCoordinateTypesPresent : 1;
    UINT16                                 velocityTypesPresent : 1;
    UINT16                                 messageSizeLimitNB_r14Present : 1;
    UINT16                                 segmentationInfo_r14Present : 1;
    UINT16                                 reserved : 7;
}CommonIEsRequestLocationInformation;


typedef struct CommonIEsProvideAssistanceDataTag
{
    SegmentationInfo_r14                   segmentationInfo_r14;    /* OPTIONAL */
    UINT8                                  segmentationInfo_r14Present : 1;
    UINT8                                  reserved : 7;
}CommonIEsProvideAssistanceData;


typedef struct CommonIEsRequestAssistanceDataTag
{
    ECGI                                   *primaryCellID;    /* OPTIONAL */
    SegmentationInfo_r14                   segmentationInfo_r14;    /* OPTIONAL */
    UINT8                                  primaryCellIDPresent : 1;
    UINT8                                  segmentationInfo_r14Present : 1;
    UINT8                                  reserved : 6;
}CommonIEsRequestAssistanceData;


typedef struct CommonIEsProvideCapabilitiesTag
{
    SegmentationInfo_r14                   segmentationInfo_r14;    /* OPTIONAL */
    AsnBitString                           *lpp_message_segmentation_r14;    /* OPTIONAL */
    UINT8                                  segmentationInfo_r14Present : 1;
    UINT8                                  lpp_message_segmentation_r14Present : 1;
    UINT8                                  reserved : 6;
}CommonIEsProvideCapabilities;


typedef struct CommonIEsRequestCapabilitiesTag
{
    AsnBitString                           *lpp_message_segmentation_req_r14;    /* OPTIONAL */
    UINT8                                  lpp_message_segmentation_req_r14Present : 1;
    UINT8                                  reserved : 7;
}CommonIEsRequestCapabilities;


typedef AsnOctetString                                     EPDU_Body;


typedef struct EPDU_NameTag
{
    /* The EPDU-Name is defined as VisibleString (SIZE (1..32)) in 36.355 
        Each character's actual value range is (32..126), although we have to encode them as INTEGER (0..126) 
        More information about VisibleString: X.680.43.7/X691.30.5.3/X.691.A.1.4.2 */ 
    UINT16 n;  /* SEQUENCE (SIZE (1..32)) OF  */
    UINT8  /* INTEGER(0..126) */                       data[32];
}
EPDU_Name;


typedef struct EPDU_IdentifierTag
{
    EPDU_ID                                ePDU_ID;
    EPDU_Name                              *ePDU_Name;    /* OPTIONAL */
    UINT8                                  ePDU_NamePresent : 1;
    UINT8                                  reserved : 7;
}EPDU_Identifier;


typedef struct EPDUTag
{
    EPDU_Identifier                        ePDU_Identifier;
    EPDU_Body                              ePDU_Body;
}EPDU;


typedef struct EPDU_SequenceTag
{
    EPDU                                               data;
    struct EPDU_SequenceTag                            *next;
}
EPDU_Sequence;


typedef struct Error_r9_IEsTag
{
    CommonIEsError                         *commonIEsError;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_Error;    /* OPTIONAL */
    UINT8                                  commonIEsErrorPresent : 1;
    UINT8                                  epdu_ErrorPresent : 1;
    UINT8                                  reserved : 6;
}Error_r9_IEs;


typedef struct ErrorLppTag
{
    UINT8       tag;
        #define TAG_ErrorLpp_error_r9 0
        #define TAG_ErrorLpp_criticalExtensionsFuture 1
    union {
        Error_r9_IEs                           *error_r9;
        UINT8                                  criticalExtensionsFuture;
    } choice;
}ErrorLpp;


typedef struct Abort_r9_IEsTag
{
    CommonIEsAbort                         *commonIEsAbort;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_Abort;    /* OPTIONAL */
    UINT8                                  commonIEsAbortPresent : 1;
    UINT8                                  epdu_AbortPresent : 1;
    UINT8                                  reserved : 6;
}Abort_r9_IEs;


typedef struct Abort_c1Tag
{
    UINT8       tag;
        #define TAG_Abort_c1_abort_r9 0
        #define TAG_Abort_c1_spare3 1
        #define TAG_Abort_c1_spare2 2
        #define TAG_Abort_c1_spare1 3
    union {
        Abort_r9_IEs                           *abort_r9;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
    } choice;
}Abort_c1;


typedef struct AbortTag
{
    struct Abort_criticalExtensions {
        UINT8       tag;
            #define TAG_Abort_criticalExtensions_c1 0
            #define TAG_Abort_criticalExtensions_criticalExtensionsFuture 1
        union {
            Abort_c1                               *c1;
            UINT8                                  criticalExtensionsFuture;
        } choice;
    } criticalExtensions;
}Abort;


typedef struct ProvideLocationInformation_r9_IEsTag
{
    CommonIEsProvideLocationInformation    *commonIEsProvideLocationInformation;    /* OPTIONAL */
    A_GNSS_ProvideLocationInformation      *a_gnss_ProvideLocationInformation;    /* OPTIONAL */
    OTDOA_ProvideLocationInformation       *otdoa_ProvideLocationInformation;    /* OPTIONAL */
    ECID_ProvideLocationInformation        *ecid_ProvideLocationInformation;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_ProvideLocationInformation;    /* OPTIONAL */
    Sensor_ProvideLocationInformation_r13  *sensor_ProvideLocationInformation_r13;    /* OPTIONAL */
    TBS_ProvideLocationInformation_r13     *tbs_ProvideLocationInformation_r13;    /* OPTIONAL */
    WLAN_ProvideLocationInformation_r13    *wlan_ProvideLocationInformation_r13;    /* OPTIONAL */
    BT_ProvideLocationInformation_r13      *bt_ProvideLocationInformation_r13;    /* OPTIONAL */
    UINT16                                 commonIEsProvideLocationInformationPresent : 1;
    UINT16                                 a_gnss_ProvideLocationInformationPresent : 1;
    UINT16                                 otdoa_ProvideLocationInformationPresent : 1;
    UINT16                                 ecid_ProvideLocationInformationPresent : 1;
    UINT16                                 epdu_ProvideLocationInformationPresent : 1;
    UINT16                                 sensor_ProvideLocationInformation_r13Present : 1;
    UINT16                                 tbs_ProvideLocationInformation_r13Present : 1;
    UINT16                                 wlan_ProvideLocationInformation_r13Present : 1;
    UINT16                                 bt_ProvideLocationInformation_r13Present : 1;
    UINT16                                 reserved : 7;
}ProvideLocationInformation_r9_IEs;


typedef struct ProvideLocationInformation_c1Tag
{
    UINT8       tag;
        #define TAG_ProvideLocationInformation_c1_provideLocationInformation_r9 0
        #define TAG_ProvideLocationInformation_c1_spare3 1
        #define TAG_ProvideLocationInformation_c1_spare2 2
        #define TAG_ProvideLocationInformation_c1_spare1 3
    union {
        ProvideLocationInformation_r9_IEs      *provideLocationInformation_r9;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
    } choice;
}ProvideLocationInformation_c1;


typedef struct ProvideLocationInformationTag
{
    struct ProvideLocationInformation_criticalExtensions {
        UINT8       tag;
            #define TAG_ProvideLocationInformation_criticalExtensions_c1 0
            #define TAG_ProvideLocationInformation_criticalExtensions_criticalExtensionsFuture 1
        union {
            ProvideLocationInformation_c1          *c1;
            UINT8                                  criticalExtensionsFuture;
        } choice;
    } criticalExtensions;
}ProvideLocationInformation;


typedef struct RequestLocationInformation_r9_IEsTag
{
    CommonIEsRequestLocationInformation    *commonIEsRequestLocationInformation;    /* OPTIONAL */
    A_GNSS_RequestLocationInformation      *a_gnss_RequestLocationInformation;    /* OPTIONAL */
    OTDOA_RequestLocationInformation       *otdoa_RequestLocationInformation;    /* OPTIONAL */
    ECID_RequestLocationInformation        *ecid_RequestLocationInformation;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_RequestLocationInformation;    /* OPTIONAL */
    Sensor_RequestLocationInformation_r13  *sensor_RequestLocationInformation_r13;    /* OPTIONAL */
    TBS_RequestLocationInformation_r13     *tbs_RequestLocationInformation_r13;    /* OPTIONAL */
    WLAN_RequestLocationInformation_r13    *wlan_RequestLocationInformation_r13;    /* OPTIONAL */
    BT_RequestLocationInformation_r13      *bt_RequestLocationInformation_r13;    /* OPTIONAL */
    UINT16                                 commonIEsRequestLocationInformationPresent : 1;
    UINT16                                 a_gnss_RequestLocationInformationPresent : 1;
    UINT16                                 otdoa_RequestLocationInformationPresent : 1;
    UINT16                                 ecid_RequestLocationInformationPresent : 1;
    UINT16                                 epdu_RequestLocationInformationPresent : 1;
    UINT16                                 sensor_RequestLocationInformation_r13Present : 1;
    UINT16                                 tbs_RequestLocationInformation_r13Present : 1;
    UINT16                                 wlan_RequestLocationInformation_r13Present : 1;
    UINT16                                 bt_RequestLocationInformation_r13Present : 1;
    UINT16                                 reserved : 7;
}RequestLocationInformation_r9_IEs;


typedef struct RequestLocationInformation_c1Tag
{
    UINT8       tag;
        #define TAG_RequestLocationInformation_c1_requestLocationInformation_r9 0
        #define TAG_RequestLocationInformation_c1_spare3 1
        #define TAG_RequestLocationInformation_c1_spare2 2
        #define TAG_RequestLocationInformation_c1_spare1 3
    union {
        RequestLocationInformation_r9_IEs      *requestLocationInformation_r9;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
    } choice;
}RequestLocationInformation_c1;


typedef struct RequestLocationInformationTag
{
    struct RequestLocationInformation_criticalExtensions {
        UINT8       tag;
            #define TAG_RequestLocationInformation_criticalExtensions_c1 0
            #define TAG_RequestLocationInformation_criticalExtensions_criticalExtensionsFuture 1
        union {
            RequestLocationInformation_c1          *c1;
            UINT8                                  criticalExtensionsFuture;
        } choice;
    } criticalExtensions;
}RequestLocationInformation;


typedef struct ProvideAssistanceData_r9_IEsTag
{
    CommonIEsProvideAssistanceData         *commonIEsProvideAssistanceData;    /* OPTIONAL */
    A_GNSS_ProvideAssistanceData           *a_gnss_ProvideAssistanceData;    /* OPTIONAL */
    OTDOA_ProvideAssistanceData            *otdoa_ProvideAssistanceData;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_Provide_Assistance_Data;    /* OPTIONAL */
    Sensor_ProvideAssistanceData_r14       *sensor_ProvideAssistanceData_r14;    /* OPTIONAL */
    TBS_ProvideAssistanceData_r14          *tbs_ProvideAssistanceData_r14;    /* OPTIONAL */
    WLAN_ProvideAssistanceData_r14         *wlan_ProvideAssistanceData_r14;    /* OPTIONAL */
    UINT8                                  commonIEsProvideAssistanceDataPresent : 1;
    UINT8                                  a_gnss_ProvideAssistanceDataPresent : 1;
    UINT8                                  otdoa_ProvideAssistanceDataPresent : 1;
    UINT8                                  epdu_Provide_Assistance_DataPresent : 1;
    UINT8                                  sensor_ProvideAssistanceData_r14Present : 1;
    UINT8                                  tbs_ProvideAssistanceData_r14Present : 1;
    UINT8                                  wlan_ProvideAssistanceData_r14Present : 1;
    UINT8                                  reserved : 1;
}ProvideAssistanceData_r9_IEs;


typedef struct ProvideAssistanceData_c1Tag
{
    UINT8       tag;
        #define TAG_ProvideAssistanceData_c1_provideAssistanceData_r9 0
        #define TAG_ProvideAssistanceData_c1_spare3 1
        #define TAG_ProvideAssistanceData_c1_spare2 2
        #define TAG_ProvideAssistanceData_c1_spare1 3
    union {
        ProvideAssistanceData_r9_IEs           *provideAssistanceData_r9;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
    } choice;
}ProvideAssistanceData_c1;


typedef struct ProvideAssistanceDataTag
{
    struct ProvideAssistanceData_criticalExtensions {
        UINT8       tag;
            #define TAG_ProvideAssistanceData_criticalExtensions_c1 0
            #define TAG_ProvideAssistanceData_criticalExtensions_criticalExtensionsFuture 1
        union {
            ProvideAssistanceData_c1               *c1;
            UINT8                                  criticalExtensionsFuture;
        } choice;
    } criticalExtensions;
}ProvideAssistanceData;


typedef struct RequestAssistanceData_r9_IEsTag
{
    CommonIEsRequestAssistanceData         *commonIEsRequestAssistanceData;    /* OPTIONAL */
    A_GNSS_RequestAssistanceData           *a_gnss_RequestAssistanceData;    /* OPTIONAL */
    OTDOA_RequestAssistanceData            *otdoa_RequestAssistanceData;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_RequestAssistanceData;    /* OPTIONAL */
    Sensor_RequestAssistanceData_r14       *sensor_RequestAssistanceData_r14;    /* OPTIONAL */
    TBS_RequestAssistanceData_r14          *tbs_RequestAssistanceData_r14;    /* OPTIONAL */
    WLAN_RequestAssistanceData_r14         *wlan_RequestAssistanceData_r14;    /* OPTIONAL */
    UINT8                                  commonIEsRequestAssistanceDataPresent : 1;
    UINT8                                  a_gnss_RequestAssistanceDataPresent : 1;
    UINT8                                  otdoa_RequestAssistanceDataPresent : 1;
    UINT8                                  epdu_RequestAssistanceDataPresent : 1;
    UINT8                                  sensor_RequestAssistanceData_r14Present : 1;
    UINT8                                  tbs_RequestAssistanceData_r14Present : 1;
    UINT8                                  wlan_RequestAssistanceData_r14Present : 1;
    UINT8                                  reserved : 1;
}RequestAssistanceData_r9_IEs;


typedef struct RequestAssistanceData_c1Tag
{
    UINT8       tag;
        #define TAG_RequestAssistanceData_c1_requestAssistanceData_r9 0
        #define TAG_RequestAssistanceData_c1_spare3 1
        #define TAG_RequestAssistanceData_c1_spare2 2
        #define TAG_RequestAssistanceData_c1_spare1 3
    union {
        RequestAssistanceData_r9_IEs           *requestAssistanceData_r9;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
    } choice;
}RequestAssistanceData_c1;


typedef struct RequestAssistanceDataTag
{
    struct RequestAssistanceData_criticalExtensions {
        UINT8       tag;
            #define TAG_RequestAssistanceData_criticalExtensions_c1 0
            #define TAG_RequestAssistanceData_criticalExtensions_criticalExtensionsFuture 1
        union {
            RequestAssistanceData_c1               *c1;
            UINT8                                  criticalExtensionsFuture;
        } choice;
    } criticalExtensions;
}RequestAssistanceData;


typedef struct ProvideCapabilities_r9_IEsTag
{
    CommonIEsProvideCapabilities           *commonIEsProvideCapabilities;    /* OPTIONAL */
    A_GNSS_ProvideCapabilities             *a_gnss_ProvideCapabilities;    /* OPTIONAL */
    OTDOA_ProvideCapabilities              *otdoa_ProvideCapabilities;    /* OPTIONAL */
    ECID_ProvideCapabilities               *ecid_ProvideCapabilities;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_ProvideCapabilities;    /* OPTIONAL */
    Sensor_ProvideCapabilities_r13         *sensor_ProvideCapabilities_r13;    /* OPTIONAL */
    TBS_ProvideCapabilities_r13            *tbs_ProvideCapabilities_r13;    /* OPTIONAL */
    WLAN_ProvideCapabilities_r13           *wlan_ProvideCapabilities_r13;    /* OPTIONAL */
    BT_ProvideCapabilities_r13             *bt_ProvideCapabilities_r13;    /* OPTIONAL */
    UINT16                                 commonIEsProvideCapabilitiesPresent : 1;
    UINT16                                 a_gnss_ProvideCapabilitiesPresent : 1;
    UINT16                                 otdoa_ProvideCapabilitiesPresent : 1;
    UINT16                                 ecid_ProvideCapabilitiesPresent : 1;
    UINT16                                 epdu_ProvideCapabilitiesPresent : 1;
    UINT16                                 sensor_ProvideCapabilities_r13Present : 1;
    UINT16                                 tbs_ProvideCapabilities_r13Present : 1;
    UINT16                                 wlan_ProvideCapabilities_r13Present : 1;
    UINT16                                 bt_ProvideCapabilities_r13Present : 1;
    UINT16                                 reserved : 7;
}ProvideCapabilities_r9_IEs;


typedef struct ProvideCapabilities_c1Tag
{
    UINT8       tag;
        #define TAG_ProvideCapabilities_c1_provideCapabilities_r9 0
        #define TAG_ProvideCapabilities_c1_spare3 1
        #define TAG_ProvideCapabilities_c1_spare2 2
        #define TAG_ProvideCapabilities_c1_spare1 3
    union {
        ProvideCapabilities_r9_IEs             *provideCapabilities_r9;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
    } choice;
}ProvideCapabilities_c1;


typedef struct ProvideCapabilitiesTag
{
    struct ProvideCapabilities_criticalExtensions {
        UINT8       tag;
            #define TAG_ProvideCapabilities_criticalExtensions_c1 0
            #define TAG_ProvideCapabilities_criticalExtensions_criticalExtensionsFuture 1
        union {
            ProvideCapabilities_c1                 *c1;
            UINT8                                  criticalExtensionsFuture;
        } choice;
    } criticalExtensions;
}ProvideCapabilities;


typedef struct RequestCapabilities_r9_IEsTag
{
    CommonIEsRequestCapabilities           *commonIEsRequestCapabilities;    /* OPTIONAL */
    A_GNSS_RequestCapabilities             *a_gnss_RequestCapabilities;    /* OPTIONAL */
    OTDOA_RequestCapabilities              *otdoa_RequestCapabilities;    /* OPTIONAL */
    ECID_RequestCapabilities               *ecid_RequestCapabilities;    /* OPTIONAL */
    EPDU_Sequence                          *epdu_RequestCapabilities;    /* OPTIONAL */
    Sensor_RequestCapabilities_r13         *sensor_RequestCapabilities_r13;    /* OPTIONAL */
    TBS_RequestCapabilities_r13            *tbs_RequestCapabilities_r13;    /* OPTIONAL */
    WLAN_RequestCapabilities_r13           *wlan_RequestCapabilities_r13;    /* OPTIONAL */
    BT_RequestCapabilities_r13             *bt_RequestCapabilities_r13;    /* OPTIONAL */
    UINT16                                 commonIEsRequestCapabilitiesPresent : 1;
    UINT16                                 a_gnss_RequestCapabilitiesPresent : 1;
    UINT16                                 otdoa_RequestCapabilitiesPresent : 1;
    UINT16                                 ecid_RequestCapabilitiesPresent : 1;
    UINT16                                 epdu_RequestCapabilitiesPresent : 1;
    UINT16                                 sensor_RequestCapabilities_r13Present : 1;
    UINT16                                 tbs_RequestCapabilities_r13Present : 1;
    UINT16                                 wlan_RequestCapabilities_r13Present : 1;
    UINT16                                 bt_RequestCapabilities_r13Present : 1;
    UINT16                                 reserved : 7;
}RequestCapabilities_r9_IEs;


typedef struct RequestCapabilities_c1Tag
{
    UINT8       tag;
        #define TAG_RequestCapabilities_c1_requestCapabilities_r9 0
        #define TAG_RequestCapabilities_c1_spare3 1
        #define TAG_RequestCapabilities_c1_spare2 2
        #define TAG_RequestCapabilities_c1_spare1 3
    union {
        RequestCapabilities_r9_IEs             *requestCapabilities_r9;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
    } choice;
}RequestCapabilities_c1;


typedef struct RequestCapabilitiesTag
{
    struct RequestCapabilities_criticalExtensions {
        UINT8       tag;
            #define TAG_RequestCapabilities_criticalExtensions_c1 0
            #define TAG_RequestCapabilities_criticalExtensions_criticalExtensionsFuture 1
        union {
            RequestCapabilities_c1                 *c1;
            UINT8                                  criticalExtensionsFuture;
        } choice;
    } criticalExtensions;
}RequestCapabilities;


typedef enum InitiatorTag
{
    Initiator_locationServer = 0,
    Initiator_targetDevice = 1
}Initiator;


typedef struct LPP_TransactionIDTag
{
    Initiator                              initiator;
    TransactionNumber                      transactionNumber;
}LPP_TransactionID;


typedef struct LPP_MessageType_c1Tag
{
    UINT8       tag;
        #define TAG_LPP_MessageType_c1_requestCapabilities 0
        #define TAG_LPP_MessageType_c1_provideCapabilities 1
        #define TAG_LPP_MessageType_c1_requestAssistanceData 2
        #define TAG_LPP_MessageType_c1_provideAssistanceData 3
        #define TAG_LPP_MessageType_c1_requestLocationInformation 4
        #define TAG_LPP_MessageType_c1_provideLocationInformation 5
        #define TAG_LPP_MessageType_c1_abort 6
        #define TAG_LPP_MessageType_c1_error 7
        #define TAG_LPP_MessageType_c1_spare7 8
        #define TAG_LPP_MessageType_c1_spare6 9
        #define TAG_LPP_MessageType_c1_spare5 10
        #define TAG_LPP_MessageType_c1_spare4 11
        #define TAG_LPP_MessageType_c1_spare3 12
        #define TAG_LPP_MessageType_c1_spare2 13
        #define TAG_LPP_MessageType_c1_spare1 14
        #define TAG_LPP_MessageType_c1_spare0 15
    union {
        RequestCapabilities                    *requestCapabilities;
        ProvideCapabilities                    *provideCapabilities;
        RequestAssistanceData                  *requestAssistanceData;
        ProvideAssistanceData                  *provideAssistanceData;
        RequestLocationInformation             *requestLocationInformation;
        ProvideLocationInformation             *provideLocationInformation;
        Abort                                  *abort;
        ErrorLpp                               *error;
        UINT8                                  spare7;
        UINT8                                  spare6;
        UINT8                                  spare5;
        UINT8                                  spare4;
        UINT8                                  spare3;
        UINT8                                  spare2;
        UINT8                                  spare1;
        UINT8                                  spare0;
    } choice;
}LPP_MessageType_c1;


typedef struct LPP_MessageTypeTag
{
    UINT8       tag;
        #define TAG_LPP_MessageType_c1 0
        #define TAG_LPP_MessageType_messageClassExtension 1
    union {
        LPP_MessageType_c1                     *c1;
        UINT8                                  messageClassExtension;
    } choice;
}LPP_MessageType;


typedef struct AcknowledgementTag
{
    BOOL                                   ackRequested;
    SequenceNumberLpp                      ackIndicator;    /* OPTIONAL */
    UINT8                                  ackIndicatorPresent : 1;
    UINT8                                  reserved : 7;
}Acknowledgement;


typedef struct LPP_MessageTag
{
    LPP_TransactionID                      *transactionID;    /* OPTIONAL */
    BOOL                                   endTransaction;
    SequenceNumberLpp                      sequenceNumber;    /* OPTIONAL */
    Acknowledgement                        *acknowledgement;    /* OPTIONAL */
    LPP_MessageType                        *lpp_MessageType;    /* OPTIONAL */
    UINT8                                  transactionIDPresent : 1;
    UINT8                                  sequenceNumberPresent : 1;
    UINT8                                  acknowledgementPresent : 1;
    UINT8                                  lpp_MessageTypePresent : 1;
    UINT8                                  reserved : 4;
}LPP_Message;


#endif
