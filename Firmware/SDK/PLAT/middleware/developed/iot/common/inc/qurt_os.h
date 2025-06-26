#ifndef _QURT_OS_H
#define _QURT_OS_H

#include <stdbool.h>
#include "cmsis_os2.h"
#include "osasys.h"
#include "ps_lib_api.h"
#include "debug_trace.h"
// Macros for return codes 
#define QURT_EOK                            osOK  /**< Operation successfully performed. */
#define QURT_EINVALID                       osErrorParameter  /**< Invalid argument value, invalid key. */ 
#define QURT_EFAILED                        osError  /**< Operation failed. */
#define QURT_EFAILED_TIMEOUT                osErrorTimeout  /**< time out. */
#define QURT_EMEM                           osErrorNoMemory  /**< Not enough memory to perform operation.*/

#define TE_SUCCESS		QURT_EOK
#define TE_FAIL			QURT_EFAILED


// Macro for event signals 
#define QURT_SIGNAL_ATTR_WAIT_ANY    osFlagsWaitAny
#define QURT_SIGNAL_ATTR_WAIT_ALL    osFlagsWaitAll
#define QURT_SIGNAL_ATTR_CLEAR_MASK  0x00000004

#define QURT_TIME_NO_WAIT          0x00000000
#define QURT_TIME_WAIT_FOREVER     osWaitForever

#define TIMER_UNDEF	NULL

#define boolean bool

// Enums and constants
typedef enum {
  QURT_TIME_TICK,                  /**< -- Return time in Ticks */
  QURT_TIME_USEC,                  /**< -- Return time in Microseconds */
  QURT_TIME_MSEC,                  /**< -- Return time in Milliseconds */
  QURT_TIME_SEC,                   /**< -- Return time in Seconds */
  QURT_TIME_NONE=QURT_TIME_TICK    /**< -- Identifier to use if no particular return type is needed */ 
}qurt_time_unit_t;

typedef enum {
  T_TICK,     /**< -- Return time in Ticks */
  T_USEC,     /**< -- Return time in Microseconds */
  T_MSEC,     /**< -- Return time in Milliseconds */
  T_SEC,      /**< -- Return time in Seconds */
  T_MIN,      /**< -- Return time in Minutes */
  T_HOUR,     /**< -- Return time in Hours */

  T_NONE=T_TICK  /**< -- Identifier to use if no paticular return type is needed */ 

}
timer_unit_type;

// structure definitions 
typedef osMutexId_t qurt_mutex_t;

typedef osThreadAttr_t qurt_thread_attr_t;

typedef osThreadId_t qurt_thread_t;

typedef osEventFlagsId_t qurt_signal_t;

typedef uint32_t	qurt_time_t;

typedef osTimerId_t timer_type;
typedef timer_type * timer_ptr_type;
typedef void * timer_group_type;
typedef timer_group_type * timer_group_ptr;
typedef time_t timetick_type;
typedef enum
{
  TIMER_NO_NOTIFY_TYPE = 0x0,           /* Use this if, no notification is required */
  TIMER_NATIVE_OS_SIGNAL_TYPE = 0x1,    /* In Qurt, required for qurt_anysignal_t object */
  TIMER_FUNC1_CB_TYPE = 0x2,            /* timer_t1_cb_type type of function pointer is expected */
  TIMER_INVALID_NOTIFY_TYPE
}
timer_notify_type;
typedef void *                           time_osal_notify_obj_ptr;
typedef unsigned long int                time_osal_notify_data;
typedef timetick_type time_timetick_type;
typedef int timer_error_type;
typedef unsigned long             timer_cb_data_type;


/***********************************************************************************************************************************************
******************************** 					THREAD FUNCTIONS					********************************************************
***********************************************************************************************************************************************/

/**
 * @fn qurt_thread_attr_init()
 * @brief This function is used initialize thread attribute structure
 * @param attr pointer to thread attribute structure
 * @return  void
 */ 
static inline void qurt_thread_attr_init(qurt_thread_attr_t *attr)
{
	if (attr != NULL) memset(attr, 0, sizeof(qurt_thread_attr_t));
}

/**
 * @fn qurt_thread_attr_set_name()
 * @brief This function is used set thread name to thread attribute structure
 * @param attr pointer to thread attribute structure
 * @param name Thread name to be set
 * @return  void
 */ 
static inline void qurt_thread_attr_set_name(qurt_thread_attr_t *attr, const char *name)
{
	if (attr != NULL) attr->name = name;
}

/**
 * @fn qurt_thread_attr_set_priority()
 * @brief This function is used set thread priority to thread attribute structure
 * @param attr pointer to thread attribute structure
 * @param priority Thread priority to be set
 * @return  void
 */
static inline void qurt_thread_attr_set_priority(qurt_thread_attr_t *attr, uint16_t priority)
{
	if (attr == NULL) return;
	attr->priority = (osPriority_t)((priority <= osPriorityRealtime7 && priority >= osPriorityLow) ? priority : osPriorityBelowNormal);
}

/**
 * @fn qurt_thread_attr_set_stack_size() 
 * @brief This function is used set stack size to thread attribute structure
 * @param attr pointer to thread attribute structure
 * @param stackSize stack size to be set
 * @return  void
 */
 static inline void qurt_thread_attr_set_stack_size(qurt_thread_attr_t *attr, uint32_t stackSize)
{
	if (attr != NULL) attr->stack_size = stackSize;
}

/**
 * @fn qurt_thread_create()
 * @brief This function is used to create a thread/task with given attributes
 * @param thread_id pointer to fill in thread id
 * @param attr pointer to thread attribute structure with set attributes value
 * @param entrypoint Tfunction pointer to thread entry function
 * @param arg arguments to be passed to the thread entry function
 * @return  On success, QURT_EOK and on failure QURT_EFAILED
 */
static inline int qurt_thread_create (qurt_thread_t *thread_id, qurt_thread_attr_t *attr, void (*entrypoint) (void *), void *arg)
{
	if (thread_id == NULL || attr == NULL || entrypoint == NULL) return QURT_EINVALID;
	*thread_id = osThreadNew((osThreadFunc_t)entrypoint, (void * )arg, (const osThreadAttr_t *)attr);
	return (*thread_id == NULL) ? QURT_EFAILED : QURT_EOK;
}

/**
 * @fn qurt_thread_suspend()
 * @brief This function is used to suspend thread
 * @param thread_id id of thread to be suspended
 * @return  QURT_EOK on success, error code on failre
 */
static inline int qurt_thread_suspend (qurt_thread_t thread_id)
{
	return osThreadSuspend(thread_id);
}

/**
 * @fn qurt_thread_resume()
 * @brief This function is used to resume supended thread
 * @param thread_id id of thread to be resumed
 * @return  QURT_EOK on success, error code on failre
 */
static inline int qurt_thread_resume (qurt_thread_t thread_id)
{
	return osThreadResume(thread_id);
}


/**
 * @fn qurt_thread_get_id()
 * @brief This function is used get thread id of current/calling thread
 * @param void
 * @return  thread id of the calling thread
 */
static inline qurt_thread_t qurt_thread_get_id (void)
{
	return osThreadGetId();
}

/**
 * @fn qurt_thread_stop()
 * @brief This function is used to exit current/calling thread
 * @param void
 * @return  void
 */
static inline void qurt_thread_stop (void)
{
	osThreadExit();
}

/***********************************************************************************************************************************************
******************************** 					UTIL FUNCTIONS					************************************************************
***********************************************************************************************************************************************/
static inline qurt_time_t qurt_timer_convert_time_to_ticks(qurt_time_t time, qurt_time_unit_t time_unit )
{
	switch (time_unit)
	{
		case QURT_TIME_SEC:
			return pdMS_TO_TICKS((time * 1000));
		case QURT_TIME_MSEC:
			return pdMS_TO_TICKS((time));
		case QURT_TIME_TICK:
		default:
			return time;
	}
}

/***********************************************************************************************************************************************
******************************** 					MUTEX FUNCTIONS					************************************************************
***********************************************************************************************************************************************/

/**
 * @fn qurt_mutex_init()
 * @brief This function is used to create recursive mutex
 * @param lock pointer the mutex 
 * @return  void
 */
static inline void qurt_mutex_init(qurt_mutex_t *lock)
{
	osMutexAttr_t attr = {0};

	if (lock == NULL) return;
	attr.attr_bits |= osMutexRecursive;
	*lock = osMutexNew(&attr);
}

/**
 * @fn qurt_mutex_destroy()
 * @brief This function is used delete the mutex
 * @param lock pointer the mutex 
 * @return  void
 */
static inline void qurt_mutex_destroy(qurt_mutex_t *lock)
{
	if (NULL == lock || NULL == *lock) return;
	osMutexDelete((osMutexId_t) *lock);
	*lock = NULL;
}

/**
 * @fn qurt_mutex_lock()
 * @brief This function is used to acquire mutex
 * @param lock pointer the mutex 
 * @return  void
 */
static inline void qurt_mutex_lock(qurt_mutex_t *lock)
{
	if (NULL == lock || NULL == *lock) return;
	osMutexAcquire((osMutexId_t) *lock, osWaitForever);
}

/**
 * @fn qurt_mutex_unlock()
 * @brief This function is used to release acquired mutex
 * @param lock pointer the mutex 
 * @return  void
 */
static inline void qurt_mutex_unlock(qurt_mutex_t *lock)
{
	if (NULL == lock || NULL == *lock) return;
	osMutexRelease((osMutexId_t) *lock);
}

/***********************************************************************************************************************************************
******************************** 					SIGNAL FUNCTIONS					********************************************************
***********************************************************************************************************************************************/

/**
 * @fn qurt_signal_init()
 * @brief This function is used to create event signal handler
 * @param lock pointer the event signal handler
 * @return  void
 */
static inline void qurt_signal_init(qurt_signal_t *signal)
{
	if (signal == NULL) return;
	*signal = osEventFlagsNew(NULL);
}

/**
 * @fn qurt_signal_destroy()
 * @brief This function is used to delete/destroy event signal handler
 * @param lock pointer the event signal handler
 * @return  void
 */
static inline void qurt_signal_destroy(qurt_signal_t *signal)
{
	if (signal == NULL) return;
	osEventFlagsDelete((osEventFlagsId_t) *signal);
	*signal = NULL;
}

/**
 * @fn qurt_signal_wait()
 * @brief This function is used to indefinitely wait for one or more events 
 * @param signal pointer the event signal handler
 * @param mask bitmask of events to wait on
 * @param attribute flags defining nature of wait and post wait action
 * @return  bitmask containing events that occured 
 */
static uint32_t qurt_signal_wait(qurt_signal_t *signal, uint32_t mask, uint32_t attribute)
{
	unsigned int ret = 0;
	if (signal == NULL) return 0;
	attribute = ((attribute & QURT_SIGNAL_ATTR_CLEAR_MASK) == 0) ? (attribute | osFlagsNoClear) : (attribute & ~osFlagsNoClear);	
	ret = osEventFlagsWait((osEventFlagsId_t) *signal, mask, attribute, osWaitForever);
	HT_TRACE(UNILOG_LWM2M, qurt_signal_wait_1,P_INFO,3,"return value:%d %u %x", ret, ret, ret);
	if ((ret & 0x80000000) != 0)
	{
		HT_TRACE(UNILOG_LWM2M, qurt_signal_wait_2,P_INFO,1,"return value:%d", (ret & 0x80000000));
		return 0;
	}
	HT_TRACE(UNILOG_LWM2M, qurt_signal_wait_3,P_INFO,3,"return value:%d %u %x", ret, ret, ret);
	return ret;
}	

/**
 * @fn qurt_signal_wait_timed_ext()
 * @brief This function is used to wait for one or more events for give time period
 * @param signal pointer the event signal handler
 * @param mask bitmask of events to wait on
 * @param attribute flags defining nature of wait and post wait action
 * @param curr_signals pointer to bitmask to set the events occured
 * @param timeout time to wait (use qurt_timer_convert_time_to_ticks to convert time/QURT_TIME_NO_WAIT/QURT_TIME_WAIT_FOREVER)
 * @return  QURT_OK on success, error code on failure
 */
static inline int qurt_signal_wait_timed_ext(qurt_signal_t *signal, uint32_t mask, 
                 uint32_t attribute, uint32_t *curr_signals, qurt_time_t timeout)
{
	uint32_t ret = 0;
	if (signal == NULL || curr_signals == NULL) return QURT_EINVALID;
	attribute = ((attribute & QURT_SIGNAL_ATTR_CLEAR_MASK) == 0) ? (attribute | osFlagsNoClear) : (attribute & ~osFlagsNoClear);	
	ret = osEventFlagsWait((osEventFlagsId_t) *signal, mask, attribute, timeout);
	if ((ret & 0x80000000) != 0)
		return ret;
	*curr_signals = ret;
	return QURT_EOK;
}

/**
 * @fn qurt_signal_set()
 * @brief This function is used to set an event to event signal handler
 * @param signal pointer the event signal handler
 * @param mask bitmask of events to be set
 * @return  void
 */
static void qurt_signal_set(qurt_signal_t *signal, uint32_t mask)
{
	if (signal != NULL) osEventFlagsSet((osEventFlagsId_t) *signal, mask);
}

static uint32_t qurt_signal_get(qurt_signal_t *signal)
{
	if (signal == NULL) return 0;
	return osEventFlagsGet((osEventFlagsId_t) *signal);
}

/**
 * @fn qurt_signal_clear()
 * @brief This function is used to clear an event set in event signal handler
 * @param signal pointer the event signal handler
 * @param mask bitmask of events to be cleared
 * @return  void
 */
static inline void qurt_signal_clear(qurt_signal_t *signal, uint32_t mask)
{
	if (signal != NULL) osEventFlagsClear((osEventFlagsId_t) *signal, mask);
}

/***********************************************************************************************************************************************
******************************** 					TIMER FUNCTIONS					************************************************************
***********************************************************************************************************************************************/

timer_error_type timer_def_osal
(
  timer_ptr_type                  timer,
  timer_group_ptr                 group,
  timer_notify_type				  cb_type,
  time_osal_notify_obj_ptr		  sigs_func_addr,
  time_osal_notify_data			  sigs_mask_data
);

void timer_set
(
  timer_ptr_type                  timer,
  timetick_type                   time,
  timetick_type                   reload,
  timer_unit_type                 unit
);

boolean timer_is_active
(
  timer_ptr_type  timer
);

timetick_type timer_clr
(
  timer_ptr_type                  timer,
  timer_unit_type                 unit
);

timer_error_type timer_stop
(
  timer_ptr_type                 timer,
  timer_unit_type            unit,
  time_timetick_type             *rem_time
);


timer_error_type timer_undef
(
  /* Timer to stop */
  timer_ptr_type                  timer
);

void timer_sleep(time_timetick_type timeout, timer_unit_type unit, boolean non_deferrable);


static inline uint32_t time_get_secs()
{
	
	return (uint32_t)OsaSystemTimeReadSecs();
}

#if 0
static inline uint32_t time_get_ms_native()
{
	OsaUtcTimeTValue time;
	appGetSystemTimeUtcSync(&time);
	return (uint32_t)time.UTCms;
}
#endif
static inline uint32_t time_get_ms_native()
{
    //OsaUtcTimeTValue *utcTimePtr = NULL;
    //utcTimePtr = OsaSystemTimeReadUtc();
	//HT_TRACE(UNILOG_LWM2M, time_ms, P_VALUE, 1, "%u", utcTimePtr->UTCms);
    //return utcTimePtr->UTCms;
    return (uint32_t)(1000 * OsaSystemTimeReadSecs());
}

/***********************************************************	END		***********************************************************************/

#endif //_QURT_OS_H
