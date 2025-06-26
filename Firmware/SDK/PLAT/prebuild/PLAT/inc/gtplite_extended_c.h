/* Copyright (c) 2013-2016, 2018 The Linux Foundation. All rights reserved.
 *
 * Not a Contribution.
 *
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GPS_EXTENDED_C_H
#define GPS_EXTENDED_C_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>





#define SCAN_OBS_DATA_MAX 5
#define WWAN_ASSIST_DATA_MAX_AIT 2
#define ASSIST_CHANNEL_LIST_MAX 8 //reduced from 32 to 8 for QCX212
#define ASSIST_PLID_LIST_MAX 8
#define WWAN_SCAN_AITINFO_MAX 1 // reduced from 2 to 1 for QCX212
#define CHANNEL_INFO_MAX 8 // reduced from 32 to 8 for QCX212
#define CELL_INFO_MAX 3 //reduced from 8 to 3 for QCX212



/** Milliseconds since January 1, 1970 */
typedef int64_t GpsUtcTime;

/** Represents a location. */
typedef struct {
    /** set to sizeof(GpsLocation) */
    size_t          size;
    /** Contains GpsLocationFlags bits. */
    uint16_t        flags;
    /** Represents latitude in degrees. */
    double          latitude;
    /** Represents longitude in degrees. */
    double          longitude;
    /**
    * Represents altitude in meters above the WGS 84 reference ellipsoid.
    */
    double          altitude;
    /** Represents speed in meters per second. */
    float           speed;
    /** Represents heading in degrees. */
    float           bearing;
    /** Represents expected accuracy in meters. */
    float           accuracy;
    /** Timestamp for the location fix. */
    GpsUtcTime      timestamp;
} GpsLocation;

typedef struct {

    uint8_t homeMncValid;
    /**<   Boolean indicating if homeMnc is valid */

    uint32_t homeMcc;
    /**<   MCC of home carrier. */

    uint32_t homeMnc;
    /**<   MNC of home carrier. */
} HomeCarrierIdStructT;  /* Type */

typedef uint64_t BsObservedDataValidMask; // AD this needs investigation
#define BS_OBSERVED_DATA_MASK_VALID_GPSWEEK_V02 ((BsObservedDataValidMask)0x00000001ull) /**<  GPS week field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_GPSMSEC_V02 ((BsObservedDataValidMask)0x00000002ull) /**<  GPS Milliseconds field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_LATITUDE_V02 ((BsObservedDataValidMask)0x00000004ull) /**<  Latitude field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_LONGITUDE_V02 ((BsObservedDataValidMask)0x00000008ull) /**<  Longitude field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_HOR_UNC_V02 ((BsObservedDataValidMask)0x00000010ull) /**<  Horizontal Uncertainty field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_ALTITUDE_V02 ((BsObservedDataValidMask)0x00000020ull) /**<  Altitude field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_ALT_UNC_V02 ((BsObservedDataValidMask)0x00000040ull) /**<  Altitude Uncertainty field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_SPEED_V02 ((BsObservedDataValidMask)0x00000080ull) /**<  Speed field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_SPEED_UNC_V02 ((BsObservedDataValidMask)0x00000100ull) /**<  Speed uncertainty field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_HEADING_V02 ((BsObservedDataValidMask)0x00000200ull) /**<  Heading field is valid in BS observed data */
#define BS_OBSERVED_DATA_MASK_VALID_HEADING_UNC_V02 ((BsObservedDataValidMask)0x00000400ull) /**<  Heading Uncertainty field is valid in BS observed data */

typedef enum {
    AIRINTERFACETYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
    AIR_INTERFACE_TYPE_CDMA_V02 = 0, /**<  FDCL CDMA cell  */
    AIR_INTERFACE_TYPE_GSM_V02 = 1, /**<  FDCL GSM cell  */
    AIR_INTERFACE_TYPE_WCDMA_V02 = 2, /**<  FDCL WCDMA cell  */
    AIR_INTERFACE_TYPE_LTE_V02 = 3, /**<  FDCL LTE cell  */
    AIR_INTERFACE_TYPE_LTE_M1_V02 = 4, /**<  FDCL LTE-M1 cell  */
    AIR_INTERFACE_TYPE_LTE_NB1_V02 = 5, /**<  FDCL LTE-NB1 cell  */
    AIR_INTERFACE_TYPE_LTE_M1_MODE_A_V02 = 6, /**<  FDCL LTE-M1ModeA cell  */
    AIR_INTERFACE_TYPE_LTE_M1_MODE_B_V02 = 7, /**<  FDCL LTE-M1ModeB cell  */
    AIR_INTERFACE_TYPE_LTE_UNKNOWN_V02 = 8, /**<  FDCL LTE-Unknown cell  */
    AIRINTERFACETYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}AirInterfaceTypeEnum;

  typedef enum {
    CELLRECORDTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
    CELL_RECORD_TYPE_INVALID_V02 = 0, /**<  Invalid value  */
    CELL_RECORD_TYPE_L1_REGION_WITH_POSITION_V02 = 1, /**<  L1 region with position  */
    CELL_RECORD_TYPE_L2_REGION_WITH_POSITION_V02 = 2, /**<  L2 region with position  */
    CELL_RECORD_TYPE_L3_REGION_WITH_POSITION_V02 = 3, /**<  L3 region with position  */
    CELL_RECORD_TYPE_L4_CELL_RECORD_WITH_POSITION_V02 = 4, /**<  L4 cell record with position  */
    CELL_RECORD_TYPE_L4_CELL_RECORD_NOT_RESOLVED_V02 = 5, /**<  L4 cell record not resolved  */
    CELL_RECORD_TYPE_L4_CELL_RECORD_NO_INFO_V02 = 6, /**<  L4 cell record no information	*/
    CELLRECORDTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}CellRecordTypeEnum;

typedef enum {
    RELIABILITYENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.	Do not change or use*/
    LOC_RELIABILITY_NOT_SET_V02 = 0, /**<  Location reliability is not set  */
    LOC_RELIABILITY_VERY_LOW_V02 = 1, /**<  Location reliability is very low; use it at your own risk  */
    LOC_RELIABILITY_LOW_V02 = 2, /**<  Location reliability is low; little or no cross-checking is possible  */
    LOC_RELIABILITY_MEDIUM_V02 = 3, /**<	Location reliability is medium; limited cross-check passed	 */
    LOC_RELIABILITY_HIGH_V02 = 4, /**<  Location reliability is high; strong cross-check passed  */
    RELIABILITYENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
} LocReliabilityEnum;

typedef enum {
    GTPSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
    GTPWWAN_DOWNLOAD_SUCCESS_V02 = 0, /**<  Download success  */
    GTPWWAN_QMI_INTIALIZATION_FAIL_V02 = 1, /**<  Failure in intialization  */
    GTPWWAN_QMI_FDCL_LIST_FAIL_V02 = 2, /**<  Failure in getting fdcl list from QMI  */
    GTPWWAN_ENCODE_FAIL_V02 = 3, /**< Failure during binary encoding */
    GTPWWAN_DATA_SERVICE_FAIL_V02 = 4, /**<  Data Service not available  */
    GTPWWAN_SSL_FAIL_V02 = 5, /**<  Failure in SSL  */
    GTPWWAN_CONNECTION_FAIL_V02 = 6, /**<  Failure in http connection  */
    GTPWWAN_HTTP_REQUEST_FAIL_V02 = 7, /**<  Failure in sending request to server */
    GTPWWAN_HTTP_DOWNLOAD_ERROR_V02 = 8, /**<  Failure in HTTP download */
    GTPWWAN_SERVER_REJECT_V02 = 9, /**<  Request rejected by server */
    GTPWWAN_DECODE_FAIL_V02 = 10, /**<  Failure during decode */
    GTPWWAN_UNSPECIFIED_FAILURE_V02 = 11, /**< Unspecified failure */
    GTPSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}GtpStatusEnum;

typedef enum {
	GTP_RESPONSE_UNSPECIFIED_FAILURE,
	GTP_RESPONSE_UNSUPPORTED_PROTOCOL,
	GTP_RESPONSE_MISSING_MAND_PARAM,
	GTP_RESPONSE_BLACK_LISTED,
	GTP_RESPONSE_SUCCESS,
	GTP_RESPONSE_MAX_VAL
} GtpResponseEnum;

  typedef uint32_t FdclCellPosValidMask;
#define FDCL_CELL_POS_MASK_VALID_ALTITUDE_V02 ((FdclCellPosValidMask)0x00000001) /**<  Altitude field is valid in cell position  */
#define FDCL_CELL_POS_MASK_VALID_ALT_UNC_V02 ((FdclCellPosValidMask)0x00000002) /**<  Altitude uncertainty field is valid in cell position  */
#define FDCL_CELL_POS_MASK_VALID_ALT_CONFIDENCE_V02 ((FdclCellPosValidMask)0x00000004) /**<  Altitude confidence is valid in cell position  */
#define FDCL_CELL_POS_MASK_VALID_ALT_RELIABILITY_V02 ((FdclCellPosValidMask)0x00000008) /**<  Altitude reliability field is valid in cell position  */
#define FDCL_CELL_POS_MASK_VALID_VELOCITY_V02 ((FdclCellPosValidMask)0x00000010) /**<  velocity field is valid in cell position  */

enum optionalGenericTimeStampFieldMask
{

    GPS_TIME_PRESENT  = (1 << 0),
    TIME_TICK_SEC_PRESENT  = (1 << 1),
    UTC_TIME_PRESENT  = (1 << 2),
};


typedef uint8_t OptionalBandMask;
#define RF_BANDS_LTE (1 << 0)
#define	RF_BANDS_GSM (1 << 1)

typedef uint8_t CapabilitiesMask;
#define GTP20_SUPPORTED  (1 << 0)
#define WIFI_SUPPORTED   (1 << 1)
#define GNSS_SUPPORTED   (1 << 2)
#define GTP_20_CACHE_FIX (1 << 3)





typedef enum
{
    CONFIGURATIONFILE_OR_NV  = (1 << 0),
    QWES_CONFIGURATION  = (1 << 1)
} OemModelSourceMask;


enum RFBandLTEBandMaskIndex
{
	LTE_BANDS_INDEX_1_16 = 0,
	LTE_BANDS_INDEX_17_32,
	LTE_BANDS_INDEX_33_48,
	LTE_BANDS_INDEX_49_64,
	LTE_BANDS_INDEX_65_80,
	LTE_BANDS_INDEX_81_96,
	LTE_BANDS_INDEX_97_112,
	LTE_BANDS_INDEX_113_128,
	LTE_BANDS_INDEX_129_144,
	LTE_BANDS_INDEX_145_160,
	LTE_BANDS_INDEX_161_176,
	LTE_BANDS_INDEX_177_192,
	LTE_BANDS_INDEX_193_208,
	LTE_BANDS_INDEX_209_224,
	LTE_BANDS_INDEX_225_240,
	LTE_BANDS_INDEX_241_256
};


enum RFBandLTESubBandMask
{
	LTE_BANDS_1_16    = (1 << LTE_BANDS_INDEX_1_16),
	LTE_BANDS_17_32   = (1 << LTE_BANDS_INDEX_17_32),
	LTE_BANDS_33_48   = (1 << LTE_BANDS_INDEX_33_48),
	LTE_BANDS_49_64   = (1 << LTE_BANDS_INDEX_49_64),
	LTE_BANDS_65_80   = (1 << LTE_BANDS_INDEX_65_80),
	LTE_BANDS_81_96   = (1 << LTE_BANDS_INDEX_81_96),
	LTE_BANDS_97_112  = (1 << LTE_BANDS_INDEX_97_112),
	LTE_BANDS_113_128 = (1 << LTE_BANDS_INDEX_113_128),
	LTE_BANDS_129_144 = (1 << LTE_BANDS_INDEX_129_144),
	LTE_BANDS_145_160 = (1 << LTE_BANDS_INDEX_145_160),
	LTE_BANDS_161_176 = (1 << LTE_BANDS_INDEX_161_176),
	LTE_BANDS_177_192 = (1 << LTE_BANDS_INDEX_177_192),
	LTE_BANDS_193_208 = (1 << LTE_BANDS_INDEX_193_208),
	LTE_BANDS_209_224 = (1 << LTE_BANDS_INDEX_209_224),
	LTE_BANDS_225_240 = (1 << LTE_BANDS_INDEX_225_240),
	LTE_BANDS_241_256 = (1 << LTE_BANDS_INDEX_241_256)
};




enum CellOptFieldMask 
{
	CHANNEL_NUM_PRESENT = (1 << 0),
	PLID_PRESENT = (1 << 1),
	NB_CARRIER_FREQ_OFFSET_PRESENT = (1 << 2),
	NB_CHANNEL_RASTER_OFFSET_PRESENT = (1 << 3)
};

enum RequestedDataTypesMask
{
	L4_CELLS_REQUESTED = (1 << 0),
	L3_CELLS_REQUESTED = (1 << 1),
	L2_CELLS_REQUESTED = (1 << 2),
	RESTRICTED_REGION_REQUESTED = (1 << 3),
	WWAN_SCAN_ASSIST_DATA_REQUESTED = (1 << 4),
	TIME_ASSIST_DATA_REQUESTED = (1 << 5),
	WWAN_SCAN_POSITION_REQUESTED = (1 << 6)
};

typedef struct __attribute__ ((packed)) {
    AirInterfaceTypeEnum airInterfaceType;
    uint32_t id1;
    uint32_t id2;
    uint32_t id3;
    uint32_t id4;
	uint8_t cellOptFields;
	uint32_t channelNum;
	uint16_t plId;
}LocCellId;

#ifdef FEATURE_LOCATION_MCS
typedef struct __attribute__ ((packed)) {
	
	uint8_t timeStampMask; /* optionalGenericTimeStampFieldMask */
	uint16_t gpsWeek;
	uint32_t gpsSeconds;
	uint32_t timeTicSeconds;
	uint32_t UtcTimestamp;
	uint32_t gpsMilliseconds; //millsec of GPS week
	uint8_t timeUncertainty;
}GenericTimeStamp;
#endif

#define RF_LTE_BANDS_MASK 16
#define MODEL_SW_VERSION_MAX 256
#define OEM_ID_MAX 256
#define MODEL_ID_MAX 256
#define CDMA_REALM_MAX 256


typedef struct {

	uint64_t pcid; /*pseudo client ID*/
    /* Optional */
    /*  GTP client software version */
    uint8_t gtpClientSwVer_valid;
    uint8_t gtpClientSwMajorVersion;
    uint8_t gtpClientSwMinorVersion;

    uint8_t modemSwVersion_valid;
    char modemSwVersion[MODEL_SW_VERSION_MAX];

    uint8_t requestedDataTypes_valid;
    uint8_t requestedDataTypes;

    uint8_t restrictedRegionVersion_valid;
    uint8_t restrictedRegionVersion;

	char OemId[OEM_ID_MAX];
	char modelId[MODEL_ID_MAX];
	OemModelSourceMask oemModelSourceMask;
	CapabilitiesMask capabilityMask;
	OptionalBandMask bandMask;
	uint8_t timeUncertainty;
	//RFBandLTESubBandMask rfBandLTESubBandMask;
	uint16_t rfBandLTESubBandMask;
	uint16_t rfBandsLTEMask[RF_LTE_BANDS_MASK];
	uint16_t rfBandsGSM;
	uint8_t configId_valid;
	uint8_t configId;
	uint8_t scanAssistId_valid; /** scan assist id will the the current cell id */
	uint64_t scanAssistId;
} clientinformation;  /* Message */

#define LOC_RESTRICTED_REGIONS_LIST_MAX_SIZE 20

#ifdef FEATURE_LOCATION_MCS
enum ScanOptionalFieldMask{
    SCAN_CS_CONFIGURATION  = (1 << 0),
    SCAN_CS_ACTIVE_CONFIG   = (1 << 1),
    SCAN_POS_CONFIGURATION  = (1 << 2)
};

enum WwanScanCellOptFieldMask 
{
	ID1_PRESENT = (1 << 0),
	ID2_PRESENT = (1 << 1),
	ID3_PRESENT = (1 << 2),
	ID4_PRESENT = (1 << 3),
	CELLFLAGS_PRESENT = (1 << 4),
	POWER_MEAS_PRESENT = (1 << 5),
};

typedef struct __attribute__ ((packed)) {
	uint16_t plid;
	uint16_t cellOptFields; /* WwanScanCellOptFieldMask */
	uint16_t id1;
	uint16_t id2;
	uint16_t id3;
	uint32_t id4;
	uint8_t cellFlags;
	uint8_t powerMeasurments;
}CellInfo;

typedef struct __attribute__ ((packed)) {
	uint32_t channelNum : 24;
	uint8_t channelflags;
	uint16_t channelScanTime;
	uint8_t numOfCells;
	CellInfo cellInfo[CELL_INFO_MAX];
}ChannelInfo;

typedef struct __attribute__ ((packed)) {
	uint8_t AirInterfaceType;
	GenericTimeStamp AITScanStartTime;
	uint8_t numOfChannels;
	ChannelInfo channelInfo[CHANNEL_INFO_MAX];
}AirInterfaceInfo;

typedef struct __attribute__ ((packed)) {
    uint8_t AirInterfaceType;
    GenericTimeStamp AITScanStartTime;
    uint8_t numOfChannels;
    ChannelInfo channelInfo;
}ServingAirInterfaceInfo;


typedef struct __attribute__ ((packed))
{
	uint16_t length;
	uint8_t numOfAITs;
	AirInterfaceInfo AITInfo[WWAN_SCAN_AITINFO_MAX];
	ServingAirInterfaceInfo ServingAITInfo;
	//uint32_t crc32;
}WwanScanList;
#endif


typedef struct {

    FdclCellPosValidMask validMask;
    /**<   Bitmask indicating which of the fields in this TLV are valid.

      Valid bitmasks: \n
      - QMI_LOC_FDCL_CELL_POS_MASK_VALID_ALTITUDE (0x00000001) --  Altitude field is valid in cell position
      - QMI_LOC_FDCL_CELL_POS_MASK_VALID_ALT_UNC (0x00000002) --  Altitude uncertainty field is valid in cell position
      - QMI_LOC_FDCL_CELL_POS_MASK_VALID_ALT_CONFIDENCE (0x00000004) --  Altitude confidence is valid in cell position
      - QMI_LOC_FDCL_CELL_POS_MASK_VALID_ALT_RELIABILITY (0x00000008) --  Altitude reliability field is valid in cell position
      */
      
    /**<   \vspace{4pt} \n The cell ID for this record. */

    double latitude;
    /**<   Latitude (specified in WGS84 datum).
      \begin{itemize1}
      \item    Type: Floating point
      \item    Units: Degrees
      \item    Range: -90.0 to 90.0       \begin{itemize1}
      \item    Positive values indicate northern latitude
      \item    Negative values indicate southern latitude
      \vspace{-0.18in} \end{itemize1} \end{itemize1}
      */

    double longitude;
    /**<   Longitude (specified in WGS84 datum).
      \begin{itemize1}
      \item    Type: Floating point
      \item    Units: Degrees
      \item    Range: -180.0 to 180.0     \begin{itemize1}
      \item    Positive values indicate eastern longitude
      \item    Negative values indicate western longitude
      \vspace{-0.18in} \end{itemize1} \end{itemize1}
      */

    float horCoverageRadius;
    /**<   Horizontal coverage radius (circular).\n
      - Units: Meters */

    uint8_t horConfidence;
    /**<   Horizontal confidence, as defined by ETSI TS 101 109 (3GPP \hyperref[TS 03.32]{TS 03.32).
      \begin{itemize1}
      \item    Units: Percent (1 to 99)
      \item    0, 101 to 255 -- invalid value
      \item    If 100 is received, reinterpret to 99
      \end{itemize1}
      */

    LocReliabilityEnum horReliability;
    /**<   Specifies the reliability of the horizontal position.

      Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
      */

    float altitude;
    /**<   Altitude with respect to mean sea level.\n
      - Units: Meters */

    float altUnc;
    /**<   Vertical uncertainty. This is mandatory if either altitudeWrtEllipsoid
      or altitudeWrtMeanSeaLevel is specified.\n
      - Units: Meters */

    uint8_t altConfidence;
    /**<   Vertical confidence, as defined by  ETSI TS 101 109 (3GPP \hyperref[TS 03.32]{TS 03.32}).
      \begin{itemize1}
      \item    Units: Percent (0-99)
      \item    0 -- invalid value
      \item    100 to 256 -- not used
      \item    If 100 is received, reinterpret to 99
      \end{itemize1}
      */

    LocReliabilityEnum altReliability;
    /**<   Specifies the reliability of the vertical position.

      Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
      */

	uint32_t utcTime;
} FdclCellPosStructT;  /* Type */


typedef struct {
	uint8_t cellPos_valid;
	FdclCellPosStructT cellPos;
	uint8_t cellFlags_valid;
	uint8_t cellFlags;
} FdclCellIdStructT;

enum LocationMask
{
	ALTITUDE_PRESENT = (1 << 0),
	ALTITUDE_UNC_PRESENT = ( 1<< 1),
	LOCATION_TIMESTAMP_PRESENT = ( 1<< 2),
	LOCATION_SOURCE_PRESENT = (1 << 3),
	VELOCITY_INFORMATION_PRESENT = (1 << 4)
};

#ifdef FEATURE_LOCATION_MCS
enum ChannelOptionalFieldMask
{
    CHANNEL_PLIDS_PRESENT  = (1 << 0)
};

typedef struct __attribute__ ((packed)) {
	uint32_t channelNum : 24;
	uint8_t channelFlags : 4;
	uint8_t channelOptFields; /* enum ChannelOptionalFieldMask */
}AssistChannelList;


typedef struct __attribute__ ((packed)) {
	uint8_t AITInterfaceType;
	uint8_t NumOfChannels;
	AssistChannelList assistChannelList[ASSIST_CHANNEL_LIST_MAX];
}AssistAITList;

typedef struct __attribute__ ((packed)) {
	uint64_t ScanAssistId;
	uint8_t NumAITs;
	AssistAITList assistAITList[WWAN_ASSIST_DATA_MAX_AIT];
}WWanScanAssistanceData;

typedef struct __attribute__ ((packed)) {
	uint8_t scanPosDurationNB1 : 4;
	uint8_t maxSIB1DecodePos : 4;
	uint8_t maxCellsPerChannel : 4;
}ScanPosConfig;

typedef struct __attribute__ ((packed)) {
	//uint16_t length;
	uint8_t optFieldMask_2;
	
	/* SCAN_POS_CONFIGURATION */
	uint8_t scanPosConfig_valid;
	ScanPosConfig scanPosConfig;

	uint8_t scanAssistanceData_valid;
	WWanScanAssistanceData wwanScanAssistanceData;

    uint8_t configId_valid;
    uint8_t configId;
}GtpMCSResponse;
#endif //FEATURE_LOCATION_MCS


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GPS_EXTENDED_C_H */
