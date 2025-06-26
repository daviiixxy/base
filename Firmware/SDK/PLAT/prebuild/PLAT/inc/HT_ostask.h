#ifndef __HT_OSTASK_H__
#define __HT_OSTASK_H__

#include "commontypedef.h"
#include "ostask.h"

void HT_OsInitStart(osThreadFunc_t func, void *arg);
void HT_PsInitialiseTasks(void);
void HT_PsOsGetLwipTaskMemory(void **tcbBuf, int *tcbSize, void **stackBuf, int *stackSize);

#endif /* __HT_OSTASK_H__ */

