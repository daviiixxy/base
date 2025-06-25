#ifndef __HT_PS_EVENT_CALLBACK_H__
#define __HT_PS_EVENT_CALLBACK_H__

#include "ps_event_callback.h"

/**
  \fn    NBStatus_t HT_registerPSEventCallback(UINT32 groupMask, psEventCallback_t callback)
  \brief Function to register certain PS event callback.
  \param[in] groupMask  Group mask.
  \param[in] callback   Callback function to be registered.
 */
NBStatus_t HT_registerPSEventCallback(groupMask_t groupMask, psEventCallback_t callback);

#endif

