#ifndef __PS_SYS_H__
#define __PS_SYS_H__

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017, All rights reserved by Qualcomm
 File name:      - pssys.h
 Description:    - PS system common include header files, and common MARCO
 History:        - 08/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/

/******************************************************************************
 *TBD
 * include OS header files
******************************************************************************/
#ifdef WIN32
#include "winsys.h"
#else
#include "osasys.h"
#include "ostask.h"
#include "cmsis_os2.h"
#include "debug_trace.h"
#include "debug_log.h"
//#include "ecpm_qcx212.h"
#endif
#include "psdebug.h"

/*
 * offset of body in a structure
*/
#ifndef OFFSETOF
#define OFFSETOF(type, body) ((UINT32)&(((type *)0)->body))
#endif

#ifndef GOS_GET_SIGNAL_FROM_BODY
#define     GOS_GET_SIGNAL_FROM_BODY    OSA_GET_SIGNAL_FROM_BODY
#endif

/*
 * 4 bytes align 
*/
#ifndef ALIGNED_4BYTE
#ifdef WIN32
#define ALIGNED_4BYTE
#else
#define ALIGNED_4BYTE __ALIGNED(4)
#endif
#endif

/*
 * Code in RAM
*/
#ifndef PS_CODE_IN_RAM
#ifdef WIN32
#define PS_CODE_IN_RAM
#else
#define PS_CODE_IN_RAM  __attribute__((__section__(".ramCode2")))
#endif
#endif

/*
 * 4 bytes aligned size
*/
#define FOUR_BYTE_ALIGN_SIZE(size)  (((size)+3)&(0xFFFFFFFC))


#ifdef WIN32
#define PS_HW_REG_WRITE_32(_pHW, val)
#define PS_HW_REG_READ_32(_pHW, val)
#else

#if   defined ( __CC_ARM )

#define PS_HW_REG_WRITE_32(_pHW, val)   \
do {                                    \
    __asm                               \
    {                                   \
        STR val, [_pHW]                 \
    }                                   \
}while(FALSE)

#define PS_HW_REG_READ_32(_pHW, val)    \
do {                                    \
    __asm                               \
    {                                   \
        LDR val, [_pHW]                 \
    }                                   \
}while(FALSE)

#elif defined ( __GNUC__ )

#define PS_HW_REG_WRITE_32(_pHW, val)  __STREXW(val, _pHW)

#define PS_HW_REG_READ_32(_pHW, val) val = __LDREXW(_pHW)

#endif

#endif


/******************************************************************************
 * InternalMsg
 *  internal message in a task, used to communicate between sub-modules in a task
 *  16 bytes
 *****************************************************************************/
typedef void (*MsgHandler)(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);
typedef struct InternalMsg_Tag
{
    MsgHandler msgHandler;
    
    UINT8   srcId; // msg from which sub-module
    UINT8   argvUint8;
    UINT16  argvUint16;
    UINT32  argvUint32;
    void    *argvPtr;
}InternalMsg;

/******************************************************************************
 * MsgQueue
 * Message buffer queue, use to buffer internal message
 *****************************************************************************/
typedef UnitQueue MsgQueue;

/******************************************************************************
 * EMPTY SIGNAL
******************************************************************************/
typedef UINT32 GosEmptySignal;

/******************************************************************************
 * SIG_WIN_SIMULATE_INTERNAL_MSG
******************************************************************************/
typedef struct WinSimulateInternalMsg_Tag
{
    MsgHandler msgHandler;
    
    UINT8   srcId; // msg from which sub-module
    UINT8   argvUint8;
    UINT16  argvUint16;
    UINT32  argvUint32;
    void    *argvPtr;
}WinSimulateInternalMsg;


/******************************************************************************
 ******************************************************************************
 * external some SYS/OS API
 ******************************************************************************
 *****************************************************************************/
void GosLogSig(UINT16 dTaskId, SignalBuf *pSig);
void GosDumpSig(UINT16 dTaskId, SignalBuf *pSig);

//void GosCreateSignal(UINT16 sigId, UINT16 sigBodySize, SignalBuf **signal);
#define     GosCreateSignal     OsaCreateSignal
//void GosCreateZeroSignal(UINT16 sigId, UINT16 sigBodySize, SignalBuf **signal);
#define     GosCreateZeroSignal OsaCreateZeroSignal
//void GosCreateIsrSignal(UINT16 sigId, UINT16 sigBodySize, SignalBuf **signal);
#define     GosCreateIsrSignal  OsaCreateFastSignal
//void GosSendSignal(UINT16 taskId, SignalBuf **signal);
#define     GosSendSignal   OsaSendSignal
#define     GosSendNoLogSignal  OsaSendNoLogSignal
// dump the signal to RAM
#define     GosSendDumpSignal   OsaSendDumpSignal
#define     GosSendNoDumpSignal OsaSendNoDumpSignal
//void OsaSendSignalToFront(UINT16 taskId, SignalBuf **signal)
#define     GosSendSignalToFront    OsaSendSignalToFront



//void GosDestroySignal(SignalBuf **signal);
#define     GosDestroySignal    OsaDestroySignal
//void OsaDestroyFastSignal(SignalBuf **signal);
#define     GosDestroyIsrSignal    OsaDestroyFastSignal
//void GosReceiveSignal(UINT16 taskId, SignalBuf **signal); // if no signal received, just blocked
#define     GosReceiveSignal    OsaReceiveSignal

//void* GosAllocMemory(UINT16 size); // if no memory left, NULL will return
#define     GosAllocMemory      OsaAllocMemory
//void* GosAllocZeroMemory(UINT16 size);
#define     GosAllocZeroMemory  OsaAllocZeroMemory
//void GosFreeMemory(void **ptr); //after free it, *ptr is set to PNULL
#define     GosFreeMemory       OsaFreeMemory

/*
 * NVM file APIs
*/
#ifdef WIN32
typedef FILE*   GOSFILE;
//GOSFILE GosFopen(UINT8 nvId, UINT8 *fileName, UINT8 *mode);
#define GosFopen(nvId, fileName, mode)    WinFopen((fileName), (mode))
#define GosFclose   WinFclose
#define GosFread    WinFread
#define GosFwrite   WinFwrite
#define GosFremove  WinFremove
#elif defined NVRAM_FILE_SYSTEM  //old file system
//typedef NVFILE_HANDLER GOSFILE;
typedef void*   GOSFILE;
//GOSFILE GosFopen(UINT8 nvId, UINT8 *fileName, UINT8 *mode);
#define GosFopen(nvId, fileName, mode)  (GOSFILE)NVFopen((nvId), (mode))
//UINT32  GosFclose(GOSFILE fp);
#define GosFclose(fp)   NVFclose((NVFILE_HANDLER)(fp))
//UINT32  GosFread(void *buf, UINT32 size, UINT32 count, GOSFILE fp);
#define GosFread(buf, size, count, fp)  NVFread((buf), (size), (count), (NVFILE_HANDLER)(fp))
//UINT32  GosFwrite(void *buf, UINT32 size, UINT32 count, GOSFILE fp);
#define GosFwrite(buf, size, count, fp) NVFwrite((buf), (size), (count), (NVFILE_HANDLER)(fp))
//UINT32  GosFremove(UINT8 *fileName);
#define GosFremove(fileName) NVFremove(0)
#else
typedef OSAFILE   GOSFILE;
//GOSFILE GosFopen(UINT8 nvId, UINT8 *fileName, UINT8 *mode);
#define GosFopen(nvId, fileName, mode)  (GOSFILE)OsaFopen((const char *)(fileName), (const char *)(mode))
#define GosFclose   OsaFclose
#define GosFread    OsaFread
#define GosFwrite   OsaFwrite
#define GosFremove  OsaFremove

#endif


/*
 * GosGetSysTickCout
*/
#ifdef WIN32
#define GosGetSysTickCount() GetTickCount()
#else
#define GosGetSysTickCount() osKernelGetTickCount()
#endif


/******************************************************************************
 ******************************************************************************
  externl functions
 ******************************************************************************
******************************************************************************/
typedef enum PsPrintModId_Tag
{
    PS_MOD_START_ID = 0x10,
    PS = PS_MOD_START_ID,
    PS_UP = 0x11,
    PS_CERRC,
    PS_NAS,
    PS_UICC,
    PS_UICC_DRV,
    PS_CCM,
    PS_CAC,

    PS_MOD_MAX_ID = 0x30
}PsPrintModId;


/******************************************************************************
 * GosPrintf/GosPsPrintf
******************************************************************************/
#ifdef WIN32
#define GosTraceAddModule(_module_name, _trace_level) 
#else
#define GosTraceAddModule(_module_name, _trace_level)   trace_add_module(_module_name, (debugTraceLevelType)_trace_level)
#endif

#ifdef WIN32
#define GosPrintf   OsaPrintf
#else
#define GosPrintf(level, fmt, ...)  \
    DEBUG_TRACE(PS, (debugTraceLevelType)(level), fmt, ##__VA_ARGS__)
#endif

#ifdef WIN32
#define GosPsPrintf OsaPsPrintf
#else
#define GosPsPrintf(mod, submod, level, fmt, ...)   \
    DEBUG_TRACE(mod, (debugTraceLevelType)(level), "[%s] "fmt, #submod, ##__VA_ARGS__)
#endif

#ifdef WIN32
#define GosHexDump(_module, _level, _dump_name, _data, _len)    \
    OsaHexDump((_dump_name), _data, _len)
#else
//void GosHexDump(_module, _level,_dump_name, _data, _len)
#define GosHexDump(_module, _level, _dump_name, _data, _len)     \
    HEXDUMP_TRACE(_module, (debugTraceLevelType)(_level), _dump_name, _data, _len)
#endif


/******************************************************************************
 * GosCheck/GosDebugBegin/GosDebugEnd
******************************************************************************/
#define     GosCheck    OsaCheck
#define     GosDebugBegin   OsaDebugBegin
#define     GosDebugEnd     OsaDebugEnd


/******************************************************************************
 * Internal message queue function
******************************************************************************/
void GosLogInternalMsg(InternalMsg *msg, const CHAR *pHdr, UINT16 varSize);

//void GosMsgQueueInit(MsgQueue *msgQ);
#define GosMsgQueueInit(Q) UnitQueueInit((Q), sizeof(InternalMsg))
/*
 * void GosMsgEnQueue(MsgQueue *msgQ, InternalMsg *msg, MsgHandler hdr, UINT16 varSize);
 * MsgQueue *msgQ;  // internal Msg queue
 * InternalMsg *msg; // internal Msg;
 * MsgHandler hdr;  //which callback func;
 * UINT16 varSize;  //size of "argvPtr"
*/
//#define GosMsgEnQueue(Q, M, H, S) UnitEnQueue((Q), (M))
#define GosMsgEnQueue(Q, M, H, S)   \
do {                                \
    GosLogInternalMsg((M), #H, (S));    \
    UnitEnQueue((Q), (M));              \
}while(FALSE)


//void GosMsgDeQueue(MsgQueue *msgQ, InternalMsg *msg);
#define GosMsgDeQueue(Q, M) UnitDeQueue((Q), (M))
//void GosMsgOnQueue(MsgQueue *msgQ);
#define GosMsgOnQueue(Q)    UnitOnQueue((Q))
//void GosMsgFlushQueue(MsgQueue *msgQ);
#define GosMsgFlushQueue(Q) UnitFlushQueue((Q))

/******************************************************************************
 * Gos Signal QUEUE function
******************************************************************************/
#define     GosSigQueueInit     OsaSigQueueInit
//void GosSigEnQueue(SignalQueue *que, SignalBuf **signal);
#define     GosSigEnQueue       OsaSigEnQueue
//void GosSigDeQueue(SignalQueue *que, SignalBuf **signal);
#define     GosSigDeQueue       OsaSigDeQueue
//BOOL GosSigOnQueue(SignalQueue *que);
#define     GosSigOnQueue       OsaSigOnQueue
//void GosSigFlushQueue(SignalQueue *que);
#define     GosSigFlushQueue    OsaSigFlushQueue

/******************************************************************************
 * Gos Task Flags function
******************************************************************************/
//UINT32 GosTaskFlagsSet(UINT16 taskId, UINT32 flags);
#define     GosTaskFlagsSet     OsaTaskFlagsSet  
//UINT32 GosTaskFlagsWait(UINT32 waitFlags);
#define     GosTaskFlagsWait    OsaTaskFlagsWait
//UINT32 OsaTaskFlagsClear(UINT32 clearFlags)
#define     GosTaskFlagsClear   OsaTaskFlagsClear

/******************************************************************************
 * Gos signal timer function
 * When timer expiry, timer task will create a signal (TIMER_EXPIRY) to SRC task
******************************************************************************/
typedef OsaTimerId GosTimerId;

#define GOS_TIMER_NOT_CREATE OSA_TIMER_NOT_CREATE

typedef OsaTimerExpiry  GosTimerExpiry;

void GosPsHibTimerExpiryFunc(OsaHibTimerId hibTimerId);

//GosTimerId GosTimerNew(UINT16 taskId, UINT16 timerEnum, osTimerType_t type);
//osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr)
#ifdef WIN32
void OsaTimerExpiryFunc(void *argument);
#define GosTimerNew(taskId, timerEnum, type)    \
    osTimerNew(OsaTimerExpiryFunc, type, taskId, timerEnum)
#else
#define GosTimerNew     OsaTimerNew
#endif
#define GosTimerStart   OsaTimerStart
#define GosTimerStop    OsaTimerStop
#define GosTimerIsRunning   OsaTimerIsRunning
//osStatus_t GosTimerDelete(GosTimerId *timer_id);
#define GosTimerDelete      OsaTimerDelete
#define GosTimerGetRemainTicks  OsaTimerGetRemainTicks


/******************************************************************************
 ******************************************************************************
 *  TIMER/SYS time ticks info, which need to still runing in HIBERNATE STATE
 ******************************************************************************
******************************************************************************/
typedef OsaHibMs  GosHibMs; 

typedef struct GosHibTimerExpiry_Tag
{
    UINT8   hibTimerId;
    UINT8   reserved0;
    UINT16  reserved1;
}GosHibTimerExpiry;


/******************************************************************************
 * GosGetHibTickCount()
 * Description: Get current HIB tick count
 * input: void
 * output: OsaHibTick
 * Comment: 
 *  Suggest 1 tick = 1ms
******************************************************************************/
//OsaHibTick  OsaGetHibTickCount(void);
#ifdef WIN32
#define GosGetHibSecondCount()    GetTickCount()
#else
extern uint32_t pmuGetHibSecondCount(void);
#define GosGetHibSecondCount()    pmuGetHibSecondCount()
#endif

/*
 * MARCO:
 * SECONDS_TO_HIB_TICKS(sec)
 * MINUTES_TO_HIB_TICKS(min)
 * MILLISECONDS_TO_HIB_TICKS(MS)
*/

/******************************************************************************
 * GosHibTimerStart
 * Description: Start HIB timer
 *        OsaHibTimerId timerId;    //which HIB timer
 *        UINT32 periodMs;         //timer period in millisecond
 * output: void
 * Comment: 
 *  if "timerId" already start before, just print a warning, and restart it
******************************************************************************/
//void OsaHibTimerStart(OsaHibTimerId timerId, OsaHibMs nMs);
#define GosHibTimerStart(hibTid, periodMs)     OsaHibTimerStart(hibTid, periodMs)

/******************************************************************************
 * GosHibTimerIsRunning
 * Description: whether the HIB timer is running
 * input: OsaHibTimerId timerId
 * output: BOOL
 * Comment: 
******************************************************************************/
//BOOL    OsaHibTimerIsRunning(OsaHibTimerId timerId);
#define GosHibTimerIsRunning(hibTid)        OsaHibTimerIsRunning(hibTid)

/******************************************************************************
 * GosHibTimerStopAndDel
 * Description: stop HIB and delete HIB timer
 * input: OsaHibTimerId timerId
 * output: void
 * Comment: 
******************************************************************************/
//void    OsaHibTimerStopAndDel(OsaHibTimerId timerId);
//#define GosHibTimerStop(hibTid)
#define GosHibTimerStopAndDel(hibTid)       OsaHibTimerStopAndDel(hibTid)


/******************************************************************************
 * GosHibTimerGetRemainMs
 * Description: Get HIB timer remaining time value in milli-seconds
 * input: OsaHibTimerId hibTId
 * output: UINT32
 * Comment:
******************************************************************************/
//UINT32 OsaHibTimerGetRemainMs(OsaHibTimerId hibTId)
#define GosHibTimerGetRemainMs(hibTid)      OsaHibTimerGetRemainMs(hibTid)



/******************************************************************************
 * GosFwdWinSimulateInternalMsgSig
 * This API only use for integration testing in WIN PC
******************************************************************************/
void GosFwdWinSimulateInternalMsgSig(UINT8 srcId, UINT8 argvUint8, UINT16 argvUint16, UINT32 argvUint32, void* argvPtr);


#if 0
/*
 * RAM LOG
*/
//void PsRamLogVar(UINT8 *file, UINT16 line, UINT32 var1, UINT32 var2, UINT32 var3);
#define GosPsRamLogVar(var1, var2, var3)    \
    PsRamLogVar(__FILE__, __LINE__, (var1), (var2), (var3))

//void PsRamLogHexDump(UINT8 *file, UINT16 line, UINT16 hexLen, UINT8 *hex);
#define GosPsRamLogHexDump(hexLen, hex)     \
    PsRamLogHexDump(__FILE__, __LINE__, hexLen, hex)
#endif

#endif

