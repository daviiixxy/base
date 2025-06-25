/****************************************************************************
*
* Copy right:   2017-, Copyrigths of Qualcomm Ltd.
* File name:      debug_trace.h
* Description:  Caterpiller software debug trace function header file
* History:      Rev1.0   2018-07-12
*
****************************************************************************/

#ifndef _DEBUG_TRACE_H
#define _DEBUG_TRACE_H

#include <stdbool.h>
#include <stdint.h>

#if defined CHIP_QCX212
#include "unilog_qcx212.h"
#elif defined CHIP_QCX212S
#include "unilog_qcx212s.h"
#endif
#include "cmsis_compiler.h"

#ifdef __cplusplus
      extern "C" {
#endif

#define USE_UNILOG

#undef  USE_MINILOG
#define USE_MINILOG     0

#ifdef USE_UNILOG

/** \brief Module ID
           PHY------0~256;  PS------257~768;  PLA------769~1024
           Every Module Owns 524288  Items Log Capacity
*/
typedef enum
{
    UNILOG_ID_BEGIN,
    UNILOG_PHY_DUMP = 1,   /**< used for PHY HEX dump */
    UNILOG_PHY_ICS,
    UNILOG_PHY_ULPATH,
    UNILOG_PHY_RXDFE,
    UNILOG_PHY_CE,   //5
    UNILOG_PHY_DE,
    UNILOG_PHY_AXC,
    UNILOG_PHY_RF,
    UNILOG_PHY_SCHEDULE,
    UNILOG_PHY_MACSF,
    UNILOG_PHY_MEAS,//10
    UNILOG_PHY_PMU,
    UNILOG_PHY_GRAPH,
    UNILOG_PHY_END=256,

    UNILOG_PS_DUMP = 257,   /**< used for PS HEX dump */
    UNILOG_PS_STRING = 258,
    UNILOG_PS = 259,
    UNILOG_UP = 260,
    UNILOG_MAC,
    UNILOG_RLC,
    UNILOG_PDCP,
    UNILOG_BM,
    UNILOG_DR,
    UNILOG_CERRC = 280,
    UNILOG_NAS = 300,
    UNILOG_CEMM,
    UNILOG_CESM,
    UNILOG_SMS,
    UNILOG_SS,
    UNILOG_NAS_PLMN,
    UNILOG_UICC = 320,
    UNILOG_UICC_DRV = 330,
    UNILOG_CCM = 340,
    UNILOG_CCM_REG,
    UNILOG_CCM_DEV,
    UNILOG_CCM_PS,
    UNILOG_CCM_SMS,
    UNILOG_CCM_SIM,
    UNILOG_CAC = 350,
    UNILOG_CAC_DEV,
    UNILOG_CAC_MM,
    UNILOG_CAC_PS,
    UNILOG_CAC_SIM,
    UNILOG_CAC_SMS,

    UNILOG_NB_RRC_BCCH_BCH_DUMP = 600,
    UNILOG_NB_RRC_BCCH_DL_SCH_DUMP,
    UNILOG_NB_RRC_DL_CCCH_DUMP,
    UNILOG_NB_RRC_DL_DCCH_DUMP,
    UNILOG_NB_RRC_DL_PCCH_DUMP,
    UNILOG_NB_RRC_UL_CCCH_DUMP,
    UNILOG_NB_RRC_UL_DCCH_DUMP,

    UNILOG_LTE_RRC_BCCH_BCH_DUMP,
    UNILOG_LTE_RRC_BCCH_DL_SCH_DUMP,
    UNILOG_LTE_RRC_BCCH_DL_SCH_BR_DUMP,
    UNILOG_LTE_RRC_DL_CCCH_DUMP,
    UNILOG_LTE_RRC_DL_DCCH_DUMP,
    UNILOG_LTE_RRC_DL_PCCH_DUMP,
    UNILOG_LTE_RRC_SC_MCCH_DUMP,
    UNILOG_LTE_RRC_UL_CCCH_DUMP,
    UNILOG_LTE_RRC_UL_DCCH_DUMP,

    UNILOG_EPS_SECURITY_DUMP,
    UNILOG_EPS_PLAIN_DUMP,

    UNILOG_IP_PKG_DUMP,

    UNILOG_TCPIP_LWIP = 735,
    UNILOG_TCPIP_NETMGR,
    UNILOG_TCPIP_TLS,
    UNILOG_TCPIP_PING,
    UNILOG_TCPIP_IPERF,
    UNILOG_TCPIP_DNS,
    UNILOG_TCPIP_SDK_API,
    UNILOG_TCPIP_SNTP,
    UNILOG_PSIF,
    UNILOG_ROHC,
    UNILOG_PS_SIG_DUMP = 750,
    UNILOG_PS_INTER_MSG,
    UNILOG_PS_DEBUG_ASSERT,
    UNILOG_PS_END = 768,

    UNILOG_PLA_DUMP = 769,   /**< used for PLA HEX dump */
    UNILOG_PLA_STRING = 770,
    UNILOG_PLA_INTERNAL_CMD = 771,
    UNILOG_PLA_DRIVER,
    UNILOG_EXCEP_PRINT,
    UNILOG_ATCMD,
    UNILOG_ATCMD_PARSER,
    UNILOG_ATCMD_EXEC,
    UNILOG_ATCMD_HTTP,
    UNILOG_ATCMD_LWM2M,
    UNILOG_ATCMD_SOCK,
    UNILOG_LFS,
    UNILOG_MQTT,
    UNILOG_COAP,
    UNILOG_ONENET,
    UNILOG_CTLWM2M,
    UNILOG_LWM2M,
    
    UNILOG_HTTP_CLIENT,
    UNILOG_TINY_DTLS,
    UNILOG_PS_DAIL,
    UNILOG_PS_STK_BIP,
    UNILOG_CMS,
    UNILOG_SIM_BIP,
    UNILOG_PS_LPP,
    UNILOG_CMS_PS_IL,       //CMS interface layer, CMS/psil
    UNILOG_CMS_SOCK_MGR,
    UNILOG_EC_API,          //ECAPI
    UNILOG_PLA_MIDWARE,  //MidWare
    UNILOG_PLA_APP,
    UNILOG_PLA_RAMDUMP,
    UNILOG_PLA_END,
    UNILOG_DM,
    UNILOG_OSA,
    UNILOG_PLA_CUSTOMER = 900,
    UNILOG_ABUP_FOTA = 901,
    UNILOG_ABUP_APP = 902,
    UNILOG_FWUPD,
    UNILOG_SSL,
    UNILOG_MBEDTLS,
	UNILOG_TSENS,
	UNILOG_HTTP_CLIENT_1,
	UNILOG_PLA_APP1,
    UNILOG_AT,
    UNILOG_GTP_CONN,
    UNILOG_GTP_LITE,

    /*
     * new add here for customer
    */

    UNILOG_AZURE,
    UNILOG_QCFILEOP,
    UNILOG_ID_END = 1023
} UniLogModuleIdType;

/** \brief trace level */
typedef enum {
    P_DEBUG,           /**< debug, lowest priority */
    P_INFO,            /**< info */
    P_VALUE,           /**< value */
    P_SIG,             /**< signalling/significant */
    P_WARNING,         /**< warning */
    P_ERROR            /**< error, highest priority */
} debugTraceLevelType;

// Move unilog interface to here
extern void uniLogDebugLevelSet(debugTraceLevelType debugLevel);
extern void uniLogInitStart(unilogPeripheralType periphType);

#define HT_TRACE(moduleID, subID, debugLevel, argLen, format,  ...) \
        if(uniLogTraceAllowCheck(moduleID, debugLevel)) \
        { \
            swLogMsgPrint(moduleID##_##subID, debugLevel, argLen, ##__VA_ARGS__); \
        }

#define QCOMM_DUMP(moduleID, subID, debugLevel, format, dumpLen, dump) \
        if(uniLogTraceAllowCheck(moduleID, debugLevel)) \
        { \
            swLogEcDump(moduleID##_##subID, debugLevel, dumpLen, dump); \
        }

#define QCOMM_DUMP_POLLING(moduleID, subID, debugLevel, format, dumpLen, dump) \
        if(uniLogTraceAllowCheck(moduleID, debugLevel)) \
        { \
            swLogEcDumpPolling(moduleID##_##subID, debugLevel, dumpLen, dump); \
        }

#define HT_STRING(moduleID, subID, debugLevel, format, string) \
        if(uniLogTraceAllowCheck(moduleID, debugLevel)) \
        { \
            swLogEcStr(moduleID##_##subID, debugLevel, string); \
        }

#endif

/** \brief gobal trace on/off control for a module */
typedef enum {
    DEBUG_TRACE_DISEN=0,         /**< trace on */
    DEBUG_TRACE_EN               /**< trace off */
} module_trace_enable_t;


/** \brief trace header struct */
typedef struct {
    const char *module_name;             /**< module name */
    debugTraceLevelType debug_trace_level;     /**< trace level */
    const char *func_name;               /**< function name */
    int line_number;                     /**< line number */
    unsigned long  time_stamp;           /**< time stamp */
} debug_trace_message_t;


/** \brief debug trace control block, per module */
typedef struct {
    const char *module_name;                          /**< module name */
    module_trace_enable_t    module_trace_en;         /**< tarce on/off control */
    debugTraceLevelType   trace_level;                      /**< trace level */
} trace_control_block_t;


/** called by specific module to set the default control block */
#define trace_add_module(_module_name, _trace_level) \
trace_control_block_t trace_control_block_##_module_name = \
{ \
    #_module_name, \
    (DEBUG_TRACE_DISEN), \
    (debugTraceLevelType)(_trace_level) \
}


#define DEBUG_TRACE_OUTPUT_MEMORY   0    /**< just put the log in log ring buffer */
#define DEBUG_TRACE_OUTPUT_NONE     1    /**< just discrad the log */
#define DEBUG_TRACE_OUTPUT_UART     2    /**< put the log to the uart */
#define DEBUG_TRACE_OUTPUT_UNILOG   3    /**< put the log to the unilog */
#define DEBUG_TRACE_OUTPUT_RTT      4    /**< put the log to the RTT */

#if USE_MINILOG
/** \brief macro used to output printf style trace */
#define DEBUG_TRACE(_module, _level,_trace, ...) \
do { \
    extern trace_control_block_t trace_control_block_##_module; \
    print_module_trace(&trace_control_block_##_module, \
                                             __FILE__+(strlen(__FILE__)>16 ? (strlen(__FILE__)-16) : 0), \
                                             __LINE__, \
                                             _level, \
                                             (_trace), \
                                             ##__VA_ARGS__); \
} while (0)

/** \brief macro used to dump hex data */
#define HEXDUMP_TRACE(_module, _level,_dump_name, _data, _len) \
 do { \
     extern trace_control_block_t trace_control_block_##_module; \
     dump_module_hexdata(&trace_control_block_##_module, \
                                             __FILE__+(strlen(__FILE__)>16 ? (strlen(__FILE__)-16) : 0), \
                                             __LINE__, \
                                             _level, \
                                             (_data), \
                                             (_len), \
                                             (_dump_name)); \
 } while (0)

#else
// minilog disabled
#define DEBUG_TRACE(_module, _level,_trace, ...)
#define HEXDUMP_TRACE(_module, _level,_dump_name, _data, _len)
#endif

/** \brief control on or off the debug trace for each module */
#define log_config_print_switch(_module, _log_switch) \
do { \
    extern log_control_block_t log_control_block_##_module; \
    log_control_block_##_module.log_switch = (_log_switch); \
} while (0)


/** \brief control the level of debug trace for each module */
#define log_config_print_level(_module, _level) \
do { \
    extern log_control_block_t log_control_block_##_module; \
    log_control_block_##_module.print_level = (_level); \
} while (0)

/**
  \fn            void dump_module_hexdata(void *handle,
                        const char *func,
                        int line,
                        debugTraceLevelType level,
                        const void *data,
                        int length,
                        const char *dump_name)
  \brief         dump hex data of a given ptr and length,
                 used to dump struct/array raw data
  \param[in]     handle    module trace control block ptr
  \param[in]     func      func name
  \param[in]     line      line number
  \param[in]     level     trace level
  \param[in]     data      output data pointer
  \param[in]     length    output data length
  \param[in]     dump_name dump name
  \returns       void
*/
void dump_module_hexdata(void *handle,
                        const char *func,
                        int line,
                        debugTraceLevelType level,
                        const void *data,
                        int length,
                        const char *dump_name);

/**
  \fn            void print_module_trace(void *handle,
                      const char *func,
                      int line,
                      debugTraceLevelType level,
                      const char *message, ...)
  \brief         output normal printf style trace,called by DEBUG_TRACE MACRO
  \param[in]     handle    module trace control block ptr
  \param[in]     func      func name
  \param[in]     line      line number
  \param[in]     level     trace level
  \param[in]     message   format message, it can optionally contain embedded format specifiers
                           that are replaced by the values specified in subsequent additonal arguments
  \param[in]     ...       additional arguments
  \returns       void
 */
void print_module_trace(void *handle,
                      const char *func,
                      int line,
                      debugTraceLevelType level,
                      const char *message, ...);
/**
  \fn           void debug_trace_init()
  \brief        set default trace output port, create debug trace task
                load debug trace setting after NVDM is done
  \param        void
  \returns      void
*/
void debug_trace_init(void);

#ifdef __cplusplus
}
#endif

#endif// _DEBUG_TRACE_H

