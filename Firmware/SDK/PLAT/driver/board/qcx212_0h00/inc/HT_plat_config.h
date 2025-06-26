#ifndef  __HT_PLAT_CONFIG_H__
#define  __HT_PLAT_CONFIG_H__

#include "Driver_Common.h"
#include "debug_trace.h"
#include "plat_config.h"

/*******************************************************************************
 * API
 ******************************************************************************/

/**
  \fn        plat_config_fs_t* HT_BSP_GetFsPlatConfig(void)
  \brief     Get FS platform configuration variable pointer
  \return    pointer to internal platform configuration loaded from FS
 */
plat_config_fs_t * HT_BSP_GetFsPlatConfig(void);

/**
  \fn        plat_config_raw_flash_t* HT_BSP_GetRawFlashPlatConfig(void)
  \brief     Get raw flash platform configuration variable pointer
  \return    pointer to internal platform configuration loaded from raw flash
 */
plat_config_raw_flash_t * HT_BSP_GetRawFlashPlatConfig(void);

/**
  \fn        uint32_t HT_BSP_GetPlatConfigItemValue(plat_config_id_t id)
  \brief     Get value of specific platform configuration item
  \param[in] id    id of platform configuration item, \ref plat_config_id_t
  \return    value of current configuration item
 */
uint32_t HT_BSP_GetPlatConfigItemValue(plat_config_id_t id);

/**
  \fn        uint32_t HT_BSP_GetFSAssertCount(void)
  \brief     Fetch current 'fsAssertCount' value from PLAT_INFO region
  \return    current fsAssertCount value
 */
uint32_t HT_BSP_GetFSAssertCount(void);

void HT_BSP_LoadPlatConfigFromRawFlash(void);

#endif /* __HT_PLAT_CONFIG_H__ */
