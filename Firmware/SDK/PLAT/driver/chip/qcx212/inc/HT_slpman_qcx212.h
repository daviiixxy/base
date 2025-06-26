#ifndef __HT_SPMAN_QCX212_H__
#define __HT_SPMAN_QCX212_H__

#include "slpman_qcx212.h"

/**
  \fn          void HT_slpManRegisterUsrSlpDepthCb(pmuUserdefSleepCb_Func callback);
  \brief       register a user callback function to control sleep depth
  \param[in]   callback    input a callback function
  \return      none.
*/
void HT_slpManRegisterUsrSlpDepthCb(slpUserdefSleepCb_Func callback);
void HT_slpManGetPMUSettings(void);
slpManRet_t HT_slpManApplyPlatVoteHandle(const char* name, uint8_t *handle);

/**
  \fn          slpManRet_t HT_slpManPlatVoteDisableSleep(uint8_t handle, slpManSlpState_t status);
  \brief       vote for keep wakeup
  \param[in]   handle        the platform vote handle.
  \param[in]   status        input the sleep status. A handle can only vote to a specific status.
  \return      error code.
*/
slpManRet_t HT_slpManPlatVoteDisableSleep(uint8_t handle, slpManSlpState_t status);

#endif /* __HT_SPMAN_QCX212_H__ */
