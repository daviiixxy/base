#include <stdbool.h>

#define IN 
#define INOUT
#define OUT

typedef struct {
	void 		*buf;
	uint32_t 	len;
} gtpBuffer;

typedef struct {
	/* derive from GtpWwanClient class for clientinfo and clientinfo IE values*/
	clientinformation 	*mClientInfo;

	/* L4 cell */
	uint8_t 			bL4CellValid;
	LocCellId			L4Cell;

	/* Scan Results */
	uint8_t wwanScanList_valid;
	WwanScanList wwanScanList;

	uint64_t mRequestTag;
} gtplite_request;

typedef struct {
	/* device from GtpWwanClient::mInjectData for response / reject IEs*/
    GtpResponseEnum status;

    /* Optional */
	/* blacklist info */
	uint8_t blackListedTime_valid;
	uint64_t blackListedTime;
	
    /* Optional */
    /*  Client Controls */
    uint8_t clientControls_valid;  /**< Must be set to true if clientControls is being passed */
    uint16_t clientControls;
    /**<   Client Controls */

    /* Optional */
    /*  Minimum Seconds Between Requests */
    uint8_t minSecsBtwRequests_valid;  /**< Must be set to true if minSecsBtwRequests is being passed */
    uint16_t minSecsBtwRequests;
    /**<   Minimum seconds between requests */

    /* Optional */
    /*  Restricted Region Version */
    uint8_t restrictedRegionVersion_valid;  /**< Must be set to true if restrictedRegionVersion is being passed */
    uint8_t restrictedRegionVersion;
    /**<   Restricted Region Version */

    /* Optional */
    /*  Maximum number of GTP cell requests with server access per day */
    uint8_t maxGtpCellRequestsPerDay_valid;  /**< Must be set to true if maxGtpCellRequestsPerDay is being passed */
    uint16_t maxGtpCellRequestsPerDay;
    /**<   Maximum number of GTP cell requests with server access per day. */

    /* Optional */
    /*  List of Restricted Regions */
    uint8_t restrictedRegions_valid;  /**< Must be set to true if restrictedRegions is being passed */
    uint32_t restrictedRegions_len;  /**< Must be set to # of elements in restrictedRegions */
    HomeCarrierIdStructT restrictedRegions[LOC_RESTRICTED_REGIONS_LIST_MAX_SIZE];
    /**<   List of restricted regions */
	uint8_t positionResponse_valid;
	FdclCellIdStructT positionResponse;
	
#ifdef FEATURE_LOCATION_MCS
	uint8_t gtpMCSresponse_valid;
	GtpMCSResponse gtpMCSResponse;
#endif
} gtplite_response;


#ifdef ENCDEC_MANAGED_BUFFERS
/** @brief: This function initializes enc/dec buffers 
	>>> This would be same as existing init implementation but 
	buffer class members will be static global structures <<<*/
void gtplite_prot_init(void);

/** @brief: This function encodes the V4 message 
	>>>This would be same as existing encode implementation but 
	GtpWwanClient handle class members will be passed as parameter <<<*/
booleean gtplite_prot_encode(IN gtplite_request *req, OUT gtpBuffer *encBuf);

/** @brief: This function clean up enc buffers 
	>>> This would be same as existing shutdown implementation but 
	buffer class members will be static global structures <<<*/
void gtplite_prot_shutdown_encode(void);

/** @brief: This function clean up dec buffers 
	>>> This would be same as existing shutdown implementation but 
	buffer class members will be static global structures.
	This can be handled internally as well but keeping it for uniformity<<<*/
void gtplite_prot_shutdown_decode(void);

#else

/** @ brief: This function encodes the V4 message 
	>>>This would be same as existing encode implementation but 
	  1. GtpWwanClient handle class members will be passed as parameter
	  2. init and shutdown of buffer are called internal
	  3. passed buffer is used instead of allocating internally<<<*/
bool gtplite_prot_encode(IN gtplite_request *req, INOUT gtpBuffer *encBuf);


#endif

/** @brief: This function decode the V4 message 
	>>>This would be same as existing encode implementation but 
	  1. injectdata handle in GtpWwanClient handle class members will 
	  		be passed as parameter (gtplite_response)
	  2. init and shutdown of buffer are called internal<<<*/
bool gtplite_prot_decode(IN gtpBuffer *decBuf,INOUT gtplite_response *rsp);

