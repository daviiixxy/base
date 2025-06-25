/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ec_ctlwm2m_api.h
 * Description:  API interface implementation header file for ChinaNet lwm2m
 * History:      Rev1.0   2018-11-27
 *
 ****************************************************************************/
#ifndef __EC_CTLWM2M_API_H__
#define __EC_CTLWM2M_API_H__
#include "cms_util.h"
#include "port/platform.h"
#include "ps_event_callback.h"
#include "ctiot_lwm2m_sdk.h"

/*
 * APPL SGID: APPL_CTLWM2M, related PRIM ID
*/
typedef enum applCtPrimId_Enum
{
    APPL_CT_PRIM_ID_BASE = 0,
    APPL_CT_DEREG_CNF,
    APPL_CT_SEND_CNF,
    APPL_CT_UPDATE_CNF,
	APPL_CT_IND,
    APPL_CT_PRIM_ID_END = 0xFF
}applCtPrimId;

typedef INT32 (*ps_event_callback_t) (urcID_t eventID, void *param, UINT32 paramLen);

uint16_t ctiot_funcv1_set_dfota_mode(ctiot_funcv1_context_t* pTContext, uint8_t mode);

uint16_t ctiot_funcv1_set_mod(ctiot_funcv1_context_t* pTContext,uint8_t securityMode,uint8_t idAuthMode,uint8_t autoTAUUpdate,uint8_t onUQMode,uint8_t onCELevel2Policy,uint8_t autoHeartBeat,uint8_t wakeupNotify, uint8_t protocolMode);
uint16_t ctiot_funcv1_get_mod(ctiot_funcv1_context_t* pContext,uint8_t* idAuthMode,uint8_t* autoTAUUpdate,uint8_t* onUQMode,uint8_t* onCELevel2Policy,uint8_t* autoHeartBeat,uint8_t* wakeupNotify, uint8_t* protocolMode);
uint16_t ctiot_funcv1_set_pm(ctiot_funcv1_context_t* pTContext,char* serverIP,uint16_t port,uint32_t lifeTime,char* objectInstanceList);
uint16_t ctiot_funcv1_get_pm(ctiot_funcv1_context_t* pContext,char* serverIP,uint16_t* port,uint32_t* lifeTime,char* objectInstanceList);
uint16_t ctiot_funcv1_session_init(ctiot_funcv1_context_t* pContext);
uint16_t ctiot_funcv1_reg(ctiot_funcv1_context_t* pTContext);
uint16_t ctiot_funcv1_dereg(ctiot_funcv1_context_t* pContext, ps_event_callback_t eventcallback);
ctiot_funcv1_login_status_e ctiot_funcv1_get_reg_status(ctiot_funcv1_context_t* pContext);
uint16_t ctiot_funcv1_update_bindmode(ctiot_funcv1_context_t* pContext,uint8_t bindMode,uint16_t* msgId,uint8_t* newObjList, lwm2m_transaction_callback_t updateCallback);
uint16_t ctiot_funcv1_update_reg(ctiot_funcv1_context_t* pTContext,uint16_t*msgId,bool withObjects, lwm2m_transaction_callback_t updateCallback);
uint16_t ctiot_funcv1_cmdrsp(ctiot_funcv1_context_t* pTContext,uint16_t msgId,char* token,uint16_t responseCode,char* uriStr,uint8_t observe,uint8_t dataFormat,char* dataS);
uint16_t ctiot_funcv1_notify(ctiot_funcv1_context_t* pTContext,char* token,char* uriStr,uint8_t dataFormat,char* dataS,uint8_t sendMode);
uint16_t ctiot_funcv1_get_status(ctiot_funcv1_context_t* pTContext,uint8_t queryType,uint16_t msgId);
uint16_t ctiot_funcv1_send(ctiot_funcv1_context_t* pTContext,char* data,ctiot_funcv1_send_mode_e sendMode, ctiot_callback_notify notifyCallback, UINT8 seqNum);
void ctiot_funcv1_clean_params(void);
void ctiot_funcv1_clean_context(void);
uint16_t ctiot_funcv1_set_psk(ctiot_funcv1_context_t* pContext,uint8_t securityMode,uint8_t* pskId,uint8_t* psk);
uint16_t ctiot_funcv1_get_psk(ctiot_funcv1_context_t* pContext,uint8_t* securityMode);
uint16_t ctiot_funcv1_set_idauth_pm(ctiot_funcv1_context_t* pTContext,char* idAuthStr);

void ctiot_funcv1_init_sleep_handler(void);
void ctiot_funcv1_disable_sleepmode(void);
void ctiot_funcv1_enable_sleepmode(void);
void ctiot_funcv1_sleep_vote(system_status_e status);
uint16_t ctiot_funcv1_get_localIP(char* localIP);
uint16_t ctiot_funcv1_wait_cstate(ctiot_funcv1_chip_info* pChipInfo);
uint16_t ctiot_funcv1_set_regswt_mode(ctiot_funcv1_context_t* pTContext, uint8_t type);
uint16_t ctiot_funcv1_set_nsmi_mode(ctiot_funcv1_context_t* pTContext, uint8_t type);
uint16_t ctiot_funcv1_set_nnmi_mode(ctiot_funcv1_context_t* pTContext, uint8_t type);
BOOL ctiot_funcv1_get_data_status(ctiot_funcv1_context_t* pTContext,uint8_t* status,uint8_t* seqNum);
uint16_t ctiot_funcv1_get_recvData(ctiot_funcv1_context_t* pTContext, uint8_t* datalen, uint8_t** dataStr);
uint16_t ctiot_funcv1_free_recvData(ctiot_funcv1_context_t* pTContext);


#endif

