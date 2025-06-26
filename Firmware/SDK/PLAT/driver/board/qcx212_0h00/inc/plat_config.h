/****************************************************************************
 *
 * Copy right:   2019-, Copyrigths of Qualcomm Ltd.
 * File name:    plat_config.h
 * Description:  platform configuration header file
 * History:      Rev1.0   2019-01-18
 *               Rev1.1   2019-11-27   Reimplement file operations with OSA APIs(LFS wrapper), not directly using LFS APIs in case of file system replacement
 *               Rev1.2   2020-01-01   Separate plat config into two parts, FS and raw flash
 *               Rev1.3   2020-06-29   Add backwards compatibility mechanism
 *
 ****************************************************************************/

#ifndef  _PLAT_CONFIG_H
#define  _PLAT_CONFIG_H

#include "Driver_Common.h"
#include "debug_trace.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

 /** \brief config file header typedef */
__PACKED_STRUCT _config_file_header
{
    uint16_t fileBodySize;     /**< size of file body, in unit of byte */
    uint8_t  version;          /**< file version, this field shall be updated when file structure is changed */
    uint8_t  checkSum;         /**< check sum value of file body */
};
typedef struct _config_file_header config_file_header_t;

/** \brief typedef of platform configuration stored in fs */
__PACKED_STRUCT _plat_config_fs_v0
{
    /** PM on/off flag
     *  valid value:
     *        0x504D5544 -- PM is disabled, "PMUD"
     *        0x504D5545 -- PM is enabled, "PMUE"
     */
    uint32_t enablePM;

    /** sleep mode
     *  valid value:
     *        0 -- dummy
     *        1 -- dummy
     */
    uint8_t sleepMode;

    /** wait n ms before sleep, when wakeup from pad
     *  valid value:
     *        0 -- do not wait
     *        x -- wait x ms
     */
    uint32_t slpWaitTime;

    /** AT baudrate*/
    uint32_t atPortBaudRate;
};

__PACKED_UNION _atPortFrameFormat
{
    uint32_t wholeValue;
    __PACKED_STRUCT _config
    {
        uint32_t dataBits    : 3;
        uint32_t parity      : 2;
        uint32_t stopBits    : 2;
        uint32_t flowControl : 3;
    } config;
};

typedef union _atPortFrameFormat atPortFrameFormat_t;

/** \brief typedef of platform configuration stored in fs */
__PACKED_STRUCT _plat_config_fs
{
    /** PM on/off flag
     *  valid value:
     *        0x504D5544 -- PM is disabled, "PMUD"
     *        0x504D5545 -- PM is enabled, "PMUE"
     */
    uint32_t enablePM;

    /** sleep mode
     *  valid value:
     *        0 -- dummy
     *        1 -- dummy
     */
    uint8_t sleepMode;

    /** wait n ms before sleep, when wakeup from pad
     *  valid value:
     *        0 -- do not wait
     *        x -- wait x ms
     */
    uint32_t slpWaitTime;

    /** AT baudrate*/
    uint32_t atPortBaudRate;

    /** AT port frame format*/
    atPortFrameFormat_t atPortFrameFormat;
};

typedef struct _plat_config_fs plat_config_fs_t;
typedef struct _plat_config_fs_v0 plat_config_fs_v0_t;

/** \brief typedef of platform configuration stored in raw flash */
__PACKED_STRUCT _plat_config_raw_flash
{
    /** action to perform when assert or hard fault occurs
     *  valid value:
     *        0 -- dump full exception info to flash and EPAT tool then trapped in endless loop(while(1))
     *        1 -- print necessary exception info then reset
     *        2 -- dump full exception info to flash then reset
     *        3 -- dump full exception info to flash and EPAT tool then reset
     *        4 -- reset directly
     */
    uint8_t faultAction;

    /** flag to control whether dump exception info to AT port
     *  valid value:
     *        0 -- off
     *        1 -- on
     */
    uint8_t dumpToATPort;

    /** WDT start/stop control
     *  valid value:
     *        0 -- stop WDT
     *        1 -- start WDT
     */
    uint8_t startWDT;

    /** unilog on/off flag
     *  valid value:
     *        0 -- unilog is disabled
     *        1 -- only sw log is enabled
     *        2 -- All log is enabled
     */
    uint8_t logControl;

    /** uart baudrate for unilog output */
    uint32_t uartBaudRate;

    /** debug trace log level setting */
    debugTraceLevelType logLevel;

};
typedef struct _plat_config_raw_flash plat_config_raw_flash_t;
typedef struct _plat_config_raw_flash plat_config_raw_flash_v0_t;

/** \brief typedef of platform info layout stored in raw flash */
__PACKED_STRUCT _plat_info_layout
{
    config_file_header_t header;           /**< raw flash plat config header */
    plat_config_raw_flash_t config;        /**< raw flash plat config body */
    uint32_t fsAssertCount;                /**< count for monitoring FS assert, when it reaches specific number, FS region will be re-formated */
};
typedef struct _plat_info_layout plat_info_layout_t;

/** @brief List of platform configuration items used to set/get sepecific setting */
typedef enum _plat_config_id
{
    PLAT_CONFIG_ITEM_FAULT_ACTION = 0,       /**< faultAction item */
    PLAT_CONFIG_ITEM_AT_PORT_DUMP,           /**< dumpToATPort item */
    PLAT_CONFIG_ITEM_START_WDT,              /**< startWDT item */
    PLAT_CONFIG_ITEM_LOG_CONTROL,            /**< logControl item */
    PLAT_CONFIG_ITEM_LOG_BAUDRATE,           /**< uart baudrate for log output */
    PLAT_CONFIG_ITEM_LOG_LEVEL,              /**< logLevel item */
    PLAT_CONFIG_ITEM_ENABLE_PM,              /**< enablePM item */
    PLAT_CONFIG_ITEM_SLEEP_MODE,             /**< sleepMode item */
    PLAT_CONFIG_ITEM_WAIT_SLEEP,             /**< wait ms before sleep */
    PLAT_CONFIG_ITEM_AT_PORT_BAUDRATE,       /**< AT port baudrate */
    PLAT_CONFIG_ITEM_AT_PORT_FRAME_FORMAT,   /**< AT port frame format */
    PLAT_CONFIG_ITEM_TOTAL_NUMBER            /**< total number of items */
} plat_config_id_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
    extern "C" {
#endif

/**
  \fn        void BSP_SavePlatConfigToFs(void)
  \brief     Save platform configuration into FS
  \return    void
 */
void BSP_SavePlatConfigToFs(void);

/**
  \fn        void BSP_LoadPlatConfigFromFs(void)
  \brief     Load platform configuration from FS
  \return    void
 */
void BSP_LoadPlatConfigFromFs(void);

/**
  \fn        plat_config_fs_t* BSP_GetFsPlatConfig(void)
  \brief     Get FS platform configuration variable pointer
  \return    pointer to internal platform configuration loaded from FS
 */
plat_config_fs_t* BSP_GetFsPlatConfig(void);

/**
  \fn        void BSP_SavePlatConfigToRawFlash(void)
  \brief     Save platform configuration into raw flash
  \return    void
 */
void BSP_SavePlatConfigToRawFlash(void);

/**
  \fn        void BSP_LoadPlatConfigFromRawFlash(void)
  \brief     Load platform configuration from raw flash
  \return    void
 */
void BSP_LoadPlatConfigFromRawFlash(void);

/**
  \fn        plat_config_raw_flash_t* BSP_GetRawFlashPlatConfig(void)
  \brief     Get raw flash platform configuration variable pointer
  \return    pointer to internal platform configuration loaded from raw flash
 */
plat_config_raw_flash_t* BSP_GetRawFlashPlatConfig(void);

/**
  \fn        uint32_t BSP_GetPlatConfigItemValue(plat_config_id_t id)
  \brief     Get value of specific platform configuration item
  \param[in] id    id of platform configuration item, \ref plat_config_id_t
  \return    value of current configuration item
 */
uint32_t BSP_GetPlatConfigItemValue(plat_config_id_t id);

/**
  \fn        void BSP_SetPlatConfigItemValue(plat_config_id_t id, uint32_t value)
  \brief     Set value of specific platform configuration item
  \param[in] id    id of platform configuration item, \ref plat_config_id_t
  \param[in] value value of configuration item to set
  \return    void
 */
void BSP_SetPlatConfigItemValue(plat_config_id_t id, uint32_t value);

/**
  \fn        uint32_t BSP_GetFSAssertCount(void)
  \brief     Fetch current 'fsAssertCount' value from PLAT_INFO region
  \return    current fsAssertCount value
 */
uint32_t BSP_GetFSAssertCount(void);

/**
  \fn        void BSP_SetFSAssertCount(uint32_t value);
  \brief     Update 'fsAssertCount' value
  \param[in] value  new value assigned to 'fsAssertCount'
  \return    void
  \note      Internal use only on FS assert occurs
 */
void BSP_SetFSAssertCount(uint32_t value);

#ifdef __cplusplus
}
#endif

#endif /* _PLAT_CONFIG_H */
