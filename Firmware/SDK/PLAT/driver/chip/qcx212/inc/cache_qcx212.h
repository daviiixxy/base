/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    cache_qcx212.h
 * Description:  QCX212 cache controller driver header file
 * History:      Rev1.0   2018-07-12
 *
 ****************************************************************************/

#ifndef _CACHE_QCX212_H
#define _CACHE_QCX212_H
#include "Driver_Common.h"

 /**
   \addtogroup icache_interface_gr
   \{
  */

#ifdef __cplusplus
 extern "C" {
#endif

/**
  \fn    void EnableICache(void)
  \brief Enables Instrution cache
  \param  void
  \return void
 */
void EnableICache(void);
/**
  \fn    void DisableICache(void)
  \brief Disables Instrution cache
  \param  void
  \return void
 */
void DisableICache(void);
/**
  \fn    bool IsICacheEnabled(void)
  \brief Check whether cache is enabled
  \param  void
  \return enabled or not
 */
bool IsICacheEnabled(void);

    /** \}*/

#ifdef __cplusplus
}
#endif

#endif /* _CACHE_QCX212_H */

