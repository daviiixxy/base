/******************************************************************************
 ******************************************************************************
 Copyright:      - 2021- Copyrights of Qualcomm Inc.
 File name:      - gtp_client.h
 Description:    - GTP transport Layer sub-module
 History:        - 19/08/2021
 ******************************************************************************
******************************************************************************/
#ifndef __GTP_CLIENT_H__
#define __GTP_CLIENT_H__

#define LAAS_TAG_LEN 5

/* GTP Config Item IDs */
#define GTP_CFG_TRANSPORT	1
#define GTP_CFG_QSP			2
#define GTP_CFG_MAXRETX		3
#define GTP_CFG_RTIMEOUT	4


typedef enum {
    GTP_LOCATION_SUCCESS = 0,                    /**< Success, location sent back to client or sent as LAAS */
	GTP_LOCATION_ERROR_BUSY,                     /**< Already in process of request */
    GTP_LOCATION_ERROR_GENERAL_FAILURE,          /**< General failure */
	GTP_LOCATION_ERROR_TEMP_NOT_REACHABLE,       /**< Network not reachable, UE out of service or server has blocked the device temproraily */
    GTP_LOCATION_ERROR_CALLBACK_MISSING,         /**< Callback is missing. */
	GTP_LOCATION_ERROR_CLIENT_ABORT,             /**< Aborted by client */
    GTP_LOCATION_ERROR_INVALID_PARAMETER,        /**< Invalid parameter. */
    GTP_LOCATION_ERROR_NOT_INITIALIZED,          /**< Not initialized, when location client is not initialized */
    GTP_LOCATION_ERROR_NOT_SUPPORTED,            /**< Not supported. */
    GTP_LOCATION_ERROR_LOAD_FAILURE,             /**< GTP server could not get loaded, connection with location server couldn't be established */
    GTP_LOCATION_ERROR_LOCATION_DISABLED,        /**< Location module license is disabled due to restricted area or server disabled due to other reason, caller shouldn't retry after this cause */
} GtpLocationErrorId;

/**
 *
 * Flags to indicate which values are valid in a location.
 */
typedef enum {
    GTP_LOCATION_HAS_LAT_LONG_BIT =          (1 << 0),   /**< Location has a valid latitude and longitude. */
    GTP_LOCATION_HAS_ALTITUDE_BIT =          (1 << 1),   /**< Location has a valid altitude. */
    GTP_LOCATION_HAS_HORIZONTAL_UNCERTAINTY_BIT = (1 << 2),   /**< Location has valid horizontal uncertainty . */
    GTP_LOCATION_HAS_VERTICAL_UNCERTAINTY_BIT = (1 << 3),   /**< Location has valid vertical uncertainty. */
} GtpLocationFlags;

/** Structure for location information. */
typedef struct {
    GtpLocationFlags flags;   			/**< Bitwise OR of gtpLocationFlags. */
    UINT32 timestamp;                   /**< UTC timestamp for a location fix; milliseconds since Jan. 1, 1970. */
    double latitude;                    /**< Latitude in degrees. */
    double longitude;                   /**< Longitude in degrees. */
    float altitude;                     /**< Altitude in meters above the WGS 84 reference ellipsoid. */
    float horizontalUncertainty;        /**< Horizontal Uncertainty in meters. */
    float verticalUncertainty;          /**< Vertical Uncertainty in meters. */
} GtpLocationInfo;

/**  
 * Callback used for the appGtpLiteInit() API.
 * This is an mandatory function and callback can't be NULL.
 * Callback is called for delivering the location fix after calling the appGtpLiteGetCurrentLocation()
 * 
 * @param[in] location  Structure containing information related to the tracked location.
 * @param[in] err # gtpLocationErrorId associated with the request.
 * This could be GTP_LOCATION_SUCCESS (location is valid) or GTP_LOCATION_ERROR_GENERAL_FAILURE (location is not valid).
 * @return None.
*/
typedef void(*GtpLocationCallback)(
    GtpLocationInfo location,
    GtpLocationErrorId err
);


/**
  \fn           appGtpLiteInit
  \brief        Initializes GTP lite client, which is used to get the current device location 
  \             by contacting GTP server. App has to call appGtpLiteInit() function before triggering the location request.
				Note: Can be called only once, subsequent calls will be failed.
  \param[in]    gtpLocationCallback, registers the callback function to return location to client after appGtpLiteGetCurrentLocation() is called by client
  \param[out]   .
  \returns      gtpLocationErrorId
  \NOTE:        refer: 
*/
GtpLocationErrorId appGtpLiteInit(GtpLocationCallback  responseCb);

/**
  \fn           appGtpLiteDeInit
  \brief        Shutdown the GTP lite client, to only be called after appGtpLiteInit, removes the callbacks
  \param[out]   
  \returns      gtpLocationErrorId
  \NOTE:        refer: 
*/
GtpLocationErrorId appGtpLiteDeInit(void);

/**
  \fn           GtpLiteSetIpAddrAndPort
  \brief        Configures GTP lite connection info (IP address, Port)
  \param[out]   
  \returns      void
  \NOTE:        refer: 
*/
void GtpLiteSetIpAddrAndPort(UINT8 *pAddr, INT16 addr_len, INT32 port, UINT8 qspEnable);

/**
  \fn           GtpLiteSetCfg
  \brief        Configures GTP lite connection info (transport, QSP, retx params)
  \param[in]	cfgid: refer GTP_CFG_* above
  \param[in]	value: config value of config item <cfgid>
  \					for GTP_CFG_TRANSPORT, 	value 0 - TCP, 1 - UDP
  \					for GTP_CFG_QSP, 		value 0 - disabled, 1 - Enabled(RSA-3072), 2 - Enabled(RSA-2048)
  \					for GTP_CFG_MAXRETX,	value - number of retransmission attempt only for UDP
  \					for GTP_CFG_RTIMEOUT,	value - response timeout for TCP, retx timeout for UDP
  \param[out]   
  \returns      gtpLocationErrorId
  \NOTE:        refer: 
*/
GtpLocationErrorId GtpLiteSetCfg(UINT32 cfgid, UINT32 value);

/**
  \fn           GtpLiteGetCfg
  \brief        Gets Configuration of GTP lite connection info (transport, QSP, retx params)
  \param[in]	cfgid refer GTP_CFG_* above
  \param[out]   
  \returns      config value for requested config item or 0xFFFFFFFF on failure
  \NOTE:        refer: 
*/
UINT32 GtpLiteGetCfg(UINT32 cfgid);


/**
  \fn           appGtpLiteGetCurrentLocation
  \brief        Get current location. Location client shall start the location procedure,
  \             function will return immediately. Location data will be sent asynchronously via the callback
  \             registered via appGtpLiteInit()
  \param[in]    BOOL isLaasTagValid, to be set, when location is provided to server with LAAS tag 
  \param[in]	UINT8 LaaS Tag[5] 40bits(8 bit Customer ID : 32 bits device token)
  \param[out]   
  \returns      gtpLocationErrorId
  \NOTE:        Only to be called after appGtpLiteInit()
*/
GtpLocationErrorId appGtpLiteGetCurrentLocation(BOOL isLaasTagValid, uint8_t laasTag[LAAS_TAG_LEN]);

/**
  \fn           appGtpLiteAbortLocationRequest
  \brief        Abort the ongoing location request which was done via appGtpLiteGetCurrentLocation.
  				It can be called before appGtpLiteDeInit, if location indication is not received by application before this call. 
				callback shall be called which is registered via appGtpLiteInit. 
  \param[out]   
  \returns      gtpLocationErrorId
  \NOTE:        refer: 
*/
GtpLocationErrorId appGtpLiteAbortLocationRequest(void);

#endif
