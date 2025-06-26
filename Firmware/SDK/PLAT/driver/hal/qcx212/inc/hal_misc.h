/****************************************************************************
 *
 * Copy right:   2019-, Copyrigths of Qualcomm Ltd.
 * File name:    hal_misc.h
 * Description:  QCX212 hal for misc header file
 * History:      Rev1.0   2019-12-12
 *
 ****************************************************************************/

#ifndef _HAL_MISC_H
#define _HAL_MISC_H


/**
  \brief  HAL_Get_ChipID enum
 */
typedef enum _chip_id_sel
{
   CHIP_ID_ONLYID = 0,  /**< only read chip ID */
   CHIP_ID_REVID,       /**< only read revison ID */
   CHIP_ID_FULLID         /**< read both  chip ID & revison ID */
} chip_id_sel;


/**
  \brief Get chip id
  \param[in] sel       HAL_Get_ChipID enum
  \return              chip id value
 */
uint32_t HAL_Get_ChipID(chip_id_sel sel);


#ifdef __cplusplus
}
#endif

#endif /* _HAL_MISC_H */
