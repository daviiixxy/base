/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ps_event_callback.h
 * Description:  API interface implementation header file for event callback service
 * History:      Rev1.0   2018-10-12
 *
 ****************************************************************************/
#ifndef __PS_EVENT_CALLBACK_H__
#define __PS_EVENT_CALLBACK_H__
#include "cmicomm.h"
#include "cms_util.h"
#include "ostask.h"
#include "cmisms.h"
/**
  \addtogroup psEventCallback_typedef Typedef
  \{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief List of the event IDs for URC */
typedef enum {
    NB_URC_ID_START = 0,      /**< URC event ID for command +CREG*/
    NB_URC_GROUP_MM = (CAC_MM << 12),
    NB_URC_ID_MM_SIGQ,
    NB_URC_ID_MM_TAU_EXPIRED,
    NB_URC_ID_MM_BLOCK_STATE_CHANGED,
    NB_URC_ID_MM_CERES_CHANGED,
    NB_URC_ID_MM_NITZ_REPORT,
    NB_URC_GROUP_PS = (CAC_PS << 12),
    NB_URC_ID_PS_BEARER_ACTED,
    NB_URC_ID_PS_BEARER_DEACTED,
    NB_URC_ID_PS_BEARER_MODIFY,
    NB_URC_ID_PS_NON_IP_DATA_IND,
    NB_URC_ID_PS_CEREG_CHANGED,
    NB_URC_ID_PS_NETINFO,
    NB_URC_GROUP_SIM = (CAC_SIM << 12),
    NB_URC_ID_SIM_READY,      /**< SIM card is ready*/
    NB_URC_ID_SIM_REMOVED,    /**< SIM card is removed*/
    NB_URC_GROUP_DEV = (CAC_DEV << 12),
    NB_URC_GROUP_SMS = (CAC_SMS << 12),
    NB_URC_ID_SMS_MSG_IND,

    NB_URC_ID_END,            /**< End of the URC event ID enumeration*/
} urcID_t;

typedef enum {
    NB_GROUP_BASE_MASK = (0X01 << CAC_BASE),
    NB_GROUP_DEV_MASK  = (0X01 << CAC_DEV),
    NB_GROUP_MM_MASK   = (0X01 << CAC_MM),
    NB_GROUP_PS_MASK   = (0X01 << CAC_PS),
    NB_GROUP_SIM_MASK  = (0X01 << CAC_SIM),
    NB_GROUP_SMS_MASK  = (0X01 << CAC_SMS),
    NB_GROUP_ALL_MASK  = 0X7FFFFFFF
} groupMask_t;

typedef struct {
    UINT32 messageId;
    void *param;
} eventCallbackMessage_t;


/**
  \fn    INT32 (*psEventCallback_t)(urcID_t eventId, void *param, UINT32 paramLen)
  \brief A function pointer prototype for the URC event callback.
  \param[in] eventId    Event ID
  \param[in] param      Pointer to the data structure with URC parameters.
  \param[in] paramLen   Indicates the length of the URC parameters.
 */
typedef INT32 (*psEventCallback_t)(urcID_t eventId, void *param, UINT32 paramLen);

/**
  \fn    void PSInitEventCallbackTable()
  \brief Function to Init URC event callback table.
 */
void PSInitEventCallbackTable(void);

/**
  \fn    NBStatus_t registerPSEventCallback(UINT32 groupMask, psEventCallback_t callback)
  \brief Function to register certain PS event callback.
  \param[in] groupMask  Group mask.
  \param[in] callback   Callback function to be registered.
 */
NBStatus_t registerPSEventCallback(groupMask_t groupMask, psEventCallback_t callback);

/**
  \fn    NBStatus_t deregisterPSEventCallback(psEventCallback_t callback)
  \brief Function to deregister certain PS event callback.
 */
NBStatus_t deregisterPSEventCallback(psEventCallback_t callback);

/**
  \fn    void PSTriggerEvent(urcID_t eventID, void *param, UINT32 paramLen)
  \brief Function to trigger certain PS event.
  \param[in] eventID  Event ID.
  \param[in] param    Parameter to be transfered.
  \param[in] paramLen Parameter length to be transfered.
 */
void PSTriggerEvent(urcID_t eventID, void *param, UINT32 paramLen);

/**
  \fn    void psCmiIndToAppEventTrigger(const SignalBuf *indSignalPtr)
  \brief Function to transfer indication to event trigger.
 */
void psCmiIndToAppEventTrigger(const SignalBuf *indSignalPtr);


/*
 \fn    void applIndToAppEventTrigger(CmsApplInd *pAppInd)
*/
void applIndToAppEventTrigger(CmsApplInd *pAppInd);
void cmsConvertAndSendSmsToLwM2M(CmiSmsNewMsgInd *pCmiMsgInd, LwM2MSmsNewMsgInd *pLwM2MMsgInd);


#endif

