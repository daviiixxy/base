/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    unilog_qcx212.h
 * Description:  QCX212 unilog controller header file
 * History:      Rev1.0   2018-07-12
 *
 ****************************************************************************/


#ifndef _UNILOG_API_H
#define _UNILOG_API_H
#ifdef __cplusplus
 extern "C" {
#endif
#include <stdbool.h>
#include <stdint.h>


#define UNILOG_QUEUE_MAX_LEN                  (100)
#define UNILOG_USING_MALLOC_TH                (10)
#define UNILOG_TRACE_MAX_MODULE_VALUE         (1024)
#define UNILOG_DMA_REQ_TH                     (4)

//#define UNILOG_STATISTIC

typedef enum
{
    SW_HEADER,
    SW_BODY,
    SW_ENDING
} swLogDataType;

typedef enum
{
    NO_MALLOC,
    USING_MALLOC
} msgMemType;

typedef enum
{
    UART_0_FOR_UNILOG = 2,
    UART_1_FOR_UNILOG = 3,
    INVALID_FOR_UNILOG
} unilogPeripheralType;

// Owner ID
typedef enum
{
    UNILOG_PHY_LOG,
    UNILOG_PS_LOG,
    UNILOG_PLA_LOG,
}UniLogOwnerIdType;

//UniLog SW log ID constructed by:  OwnerID(3bits) <<29| ModuleID(10bits)<<19 | subID(19bits)
#define UNILOG_ID_CONSTRUCT(ownerId, moduleId, subId)    ((ownerId << 29) | (moduleId << 19) | subId)

#define UNILOG_GET_OWNERID(swLogId)    ((swLogId) >> 29)


#define BEGIN_TRACE_IDS(MODULE) \
        enum MODULE##_ENUM{ \
             MODULE##_BEGIN = MODULE << 19,

#define END_TRACE_IDS(MODULE) \
            MODULE##__END};

#define TRACE_DEF(TRACE_ID, STRING) \
        TRACE_ID,


#pragma pack(1)
typedef struct unilogQueueMsg
{
    uint8_t msgFlag; //Indicate using malloc or not, 1: yes 0: no
    uint32_t msgLen;
    union
    {
        uint32_t msgData[11]; //Can contain 10 items arg
        uint32_t *pMsgData;
    } msg;
} unilogQueueMsgType;
#pragma pack()

extern void uniLogModuleAllowTraces(uint16_t moduleID);
extern void uniLogModuleDisableTraces(uint16_t moduleID);
extern void uniLogModuleAllowAllTraces(void);
extern void uniLogModuleDisableAllTraces(void);
extern bool uniLogTraceAllowCheck(uint16_t moduleID, uint8_t debugLevel);

void uniLogFlushOut(uint32_t flush_data);
extern void uniLogStop(void);
extern void uniLogStopHwLog(void);
extern bool uniLogIsInitialized(void);
void uniLogGetSettingFromFlash(void);
extern void swLogMsgPrint(uint32_t swLogID, uint8_t debugLevel, uint8_t argLen, ...);
extern void swLogMsgDump(uint32_t swLogID, uint32_t *pSwLogData, uint32_t swLogLen);
extern void swLogEcDump(uint32_t swLogID, uint8_t debugLevel, uint32_t dumpLen, const uint8_t *pDump);
extern void swLogEcDumpPolling(uint32_t swLogID, uint8_t debugLevel, uint32_t dumpLen, const uint8_t *pDump);
extern void swLogEcStr(uint32_t swLogID, uint8_t debugLevel, const uint8_t *pStr);

#if defined(UNILOG_STATISTIC) && defined(PM_FEATURE_ENABLE)
void uniLogGetSwLogTrafficStatus(void);
#endif


#ifdef __cplusplus
}
#endif

#endif//_UNILOG_API_H

