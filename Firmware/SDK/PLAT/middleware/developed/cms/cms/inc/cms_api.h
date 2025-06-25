/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: cms_api.h
 *
 *  Description: CMS (Communication Modem Service layer/task) external API & signal definition
 *
 *  History:
 *
 *  Notes:
 *
******************************************************************************/
#ifndef __CMS_API_H__
#define __CMS_API_H__

#include <stdint.h>
#include "string.h"
#include "CommonTypedef.h"
#include "osasys.h"

/******************************************************************************
 *****************************************************************************
 * CMS EXTERNAL COMMON MARCO
 *****************************************************************************
******************************************************************************/


#define CMS_MAX_DELAY_MS            0xEFFFFFFF  //without time out

/******************************************************************************
 *****************************************************************************
 * CMS EXTERNAL COMMON ENUM
 *****************************************************************************
******************************************************************************/


/*
 * Signal ID between CMS task and other tasks
*/
typedef enum cmsSigId_Enum
{
    /*
     * 0x0900 - 0x09FF, reserved for CMS task signals
    */

    SIG_CMS_BASE = 0x0900,

    /*
     * 0x0900 - 0x090F, used between URAT <-> CMS (AT CMD SRV)
    */
    AT_CMD_SIGNAL_BASE = 0x0900,
    SIG_AT_CMD_STR_REQ,     //AtCmdStrReq
    SIG_AT_CMD_CONTINUE_REQ,    //AtCmdContinueReq
    //SIG_AT_SMS_CTRL_REQ,
    //SIG_AT_SMS_ESC_REQ,

    //SIG_AT_CHAN_REG_REQ,


    AT_CMD_SIGNAL_END  = 0x090F,

    /*
     * 0x0910 - 0x091F, used between APP (LWM2M/COAP/MQTT, etc) <-> CMS(AT CMD SRV) (cms_comm.h)
    */
    APP_SIGNAL_BASE = 0x0910,
    SIG_APP_MSG_CALLBACK,
    //SIG_APP_APPL_REQ,
    //SIG_APP_APPL_CNF,       //ApplRetCnf
    //SIG_APP_APPL_IND,
    SIG_CMS_APPL_REQ,       //CmsApplReq
    SIG_CMS_APPL_CNF,       //CmsApplCnf
    SIG_CMS_APPL_IND,       //CmsApplInd

    APP_SIGNAL_END  = 0x091F,


    /*
     * 0x0920 - 0x0927, used for netmanager (netmgr.h)
    */

    /*
     * 0x0928 - 0x092F, used between SIMBIP <-> STK PS Proxy (psstk_bip.h)
    */

    /*
     * 0x0940 - 0x094F, used for others CMS signal
    */
    SIG_CMS_OTHER_BASE = 0x0940,
    SIG_CMS_PHY_WAKEUP_READY_IND,   //OsaEmptySignal, after PHY wake up ready, send this signal to CMS to schedule PS tasks
    SIG_CMS_SYN_API_REQ,            //CmsSynApiReq
    SIG_CMS_HIGH_PRI_SYN_API_REQ,   //CmsSynApiReq, this called with high priority without any block in CMS task
    SIG_CMS_BLOCK_API_REQ,          //CmsBlockApiReq
    SIG_CMS_NON_BLOCK_API_REQ,      //CmsNonBlockApiReq

    SIG_CMS_OTHER_END = 0x094F,

    /*
     * 0x0980 - 0x09FF, reserved for customer, an example
    */
    CUSTOMER_SIGNAL_BASE = 0x0980,
    SIG_CUSTOMER_MSG_CALLBACK,
    SIG_CUSTOMER_REQ,
    SIG_CUSTOMER_CNF,
    SIG_CUSTOMER_IND,

    CUSTOMER_SIGNAL_END = 0x09FF

}cmsSigId;

/*
 * CMS ERROR CODE, at_api/cms_api common return error code
*/
typedef enum CmsRetId_enum
{
    CMS_RET_SUCC = 0,
    NBStatusSuccess     = CMS_RET_SUCC,

    CMS_FAIL            = -1,
    NBStatusFail        = CMS_FAIL,
    CMS_INVALID_PARAM   = -2,
    NBStatusInvalidParam= CMS_INVALID_PARAM,
    CMS_BUSY            = -3,
    NBStatusBusy        = CMS_BUSY,
    CMS_LIST_FULL       = -4,
    NBStatusListFull    = CMS_LIST_FULL,
    CMS_LIST_NOT_FOUND  = -5,
    NBStatusListNotFound = CMS_LIST_NOT_FOUND,
    CMS_SEMP_ERROR      = -6,   //Semaphore not created/error
    NBStatusSemphoreNULL= CMS_SEMP_ERROR,
    CMS_TIME_OUT        = -7,
    NBStatusTimeout     = CMS_TIME_OUT,
    CMS_SIM_NOT_INSERT  = -8,   //SIM not inserted
    NBStatusSimNotInserted  = CMS_SIM_NOT_INSERT,
    CMS_OPER_NOT_SUPPROT    = -9,   //operation not supported
    NBStatusOperNotSupported    = CMS_OPER_NOT_SUPPROT,
    CMS_SIM_WRONG       = -10,  //SIM wrong, excute command while returned invalid data
    NBStatusSimWrong    = CMS_SIM_WRONG,
    CMS_NOT_POWER_ON    = -11,  //Not power on, maybe cfun0 state
    NBStatusSimNotPowerOn   = CMS_NOT_POWER_ON,
    CMS_SIM_BUSY        = -12,  //SIM busy, cannot process any instruction
    NBStatusSimBusy     = CMS_SIM_BUSY,
    CMS_NO_MEM          = -13,
    CMS_NO_RESOURCE     = -14,
    CMS_PDN_NOT_VALID   = -15,
    NBStatusPdnNotValid = CMS_PDN_NOT_VALID,
}_CmsRetId;

typedef INT32 CmsRetId;

typedef CmsRetId    NBStatus_t;

#if 0
/*
 * PS lib API, function return codes
*/
typedef enum
{
    NBStatusSimBusy          = -12,//SIM busy, cannot process any instruction
    NBStatusSimNotPowerOn    = -11,//SIM is not power on, maybe cfun0 state
    NBStatusSimWrong         = -10,//SIM wrong, excute command while returned invalid data
    NBStatusOperNotSupported = -9, //operation not supported
    NBStatusSimNotInserted   = -8, //SIM not inserted
    NBStatusTimeout          = -7,
    NBStatusSemphoreNULL     = -6,
    NBStatusListNotFound     = -5,
    NBStatusListFull         = -4,
    NBStatusBusy             = -3,
    NBStatusInvalidParam     = -2, //input invalid parameters
    NBStatusFail             = -1,
    NBStatusSuccess          = 0
}NBStatus_t;
#endif

/*
 * APP layer ID, value: 0 - 255
 *  CmsApplCnf->header.appId
*/
typedef enum CmsAppLayerId_Enum
{
    APPL_BASE   = 1,
    APPL_NM     = 2,
    APPL_SOCKET = 3,
    APPL_MQTT   = 4,
    APPL_COAP   = 5,
    APPL_LWM2M  = 6,
    APPL_HTTP   = 7,
    APPL_HTTPS  = 8,
    APPL_DTLS   = 9,
    APPL_ECSOC  = 10,
    APPL_ONENET = 11,
    APPL_CTLWM2M = 12,
    APPL_ADC     = 13,
    APPL_EXAMPLE = 14,
	APPL_TSENS   = 15,
    /*
     * new APPL add here
    */
    APPL_FWUPD = 16,

    APPL_END    = 0xFF
}CmsAppId;


/*
 * ApplRetCode
 * value of "ApplRetCnf->header.rc"
 * Note:
 * 1> If some APP has their own error code, need to defined in their own header file, such as: at_sock_task.h
 * 2> But the "0" is reserved for SUCC
*/
typedef enum applRetCode_Enum
{
    APPL_RET_SUCC = 0,
    APPL_RET_FAIL = 1,
    APPL_RET_NETWORK_FAIL = 2,
    APPL_RET_END,
}ApplRetCode;

/*
 * onenet error code
*/
typedef enum ATCI_CIS_ERROR
{
    CIS_UNKNOWN_ERROR = 100,                                //unknown error
    CIS_PARAM_ERROR = 601,                                  //parameter error
    CIS_STATU_ERROR = 602,                                  //status error
}_AtciCisError;

/*
 * http error code
*/
typedef enum AT_HTTP_ERROR
{
    HTTP_PARAM_ERROR = 1,                                  //parameter error
    HTTP_CLIENTS_EXHAOUST = 2,                             //clients number reach max number
    HTTP_URL_FORMAT_ERROR = 3,                             //url format error
    HTTP_URL_PARSE_ERROR = 4,                              //url parse error
    HTTP_OPERATION_NOT_SUPPORT = 5,                        //operation not support
    HTTP_NO_FIND_CLIENT_ID = 6,                            //not find client id
    HTTP_ALREADY_CONNECTED = 7,                            //already connected
    HTTP_CONNECT_FAILED = 8,                               //connect failed
    HTTP_SEND_FAILED = 9,                                  //send failed
    HTTP_CMD_CONTIUE = 10,                                 //contiune enter cmd
    HTTP_NO_NETWORK = 11,                                  //network not ready
    HTTP_CLIENT_NOT_OPEN = 12,                              //client has closed
    HTTP_DESTORY_FAILED = 13,
    HTTP_NOT_SUPPORT_HTTPS = 14,
    HTTP_CREATE_FAILED = 15                               //create failed
}_AtHttpError;

/*
 * LWM2M error code
*/

typedef enum AT_LWM2M_ERROR
{
    LWM2M_PARAM_ERROR = 1,                             //parameter error
    LWM2M_SEMPH_ERROR = 2,                             //cannot create semph
    LWM2M_CONFIG_ERROR = 3,                            //config error
    LWM2M_NO_FREE_CLIENT = 4,                          //no free client
    LWM2M_NO_FIND_CLIENT = 5,                          //no find client
    LWM2M_OPERATION_NOT_SUPPORT = 6,                   //operation not support
    LWM2M_ADDOBJ_FAILED = 7,                           //add object failed
    LWM2M_NO_FIND_OBJ = 8,                             //no find object
    LWM2M_DELOBJ_FAILED = 9,                           //delete object failed
    LWM2M_NO_NETWORK = 10,                             //network not ready
    LWM2M_INTER_ERROR = 11,                            //internal error
    LWM2M_REG_BAD_REQUEST = 12,                        //register fail bad request
    LWM2M_REG_FORBIDEN = 13,                           //register fail forbden
    LWM2M_REG_PRECONDITION = 14,                       //register fail parameter error
    LWM2M_REG_TIMEOUT = 15,                            //register fail timeout
    LWM2M_SESSION_INVALID = 16,                        //create session fail
    LWM2M_ALREADY_ADD = 17,                             //already has object
    LWM2M_ATTR_ERROR = 18,
    LWM2M_GETLIFETIME_ERROR = 19,
    LWM2M_WAKEUP_ERROR =20,
    LWM2M_SETLIFETIME_ERROR,
    LWM2M_FILE_OPERATION_NOT_SUPPORT                   //operation not support
}_AtLwm2mError;



typedef enum AT_CTLWM2M_ERROR
{
    CTLWM2M_OTHER_ERROR = 1,
    CTLWM2M_PARAM_NUM_ERROR = 2,
    CTLWM2M_PARAM_VALUE_ERROR = 3,
    CTLWM2M_TERMINAL_NOT_READY = 4,
    CTLWM2M_NOT_SUPPORT_SECURITY_MODE = 5,
    CTLWM2M_OPERATION_NOT_SUPPORT = 6,
    CTLWM2M_ADDOBJ_FAILED = 7,
    CTLWM2M_PARAM_NOT_INT = 8,
    CTLWM2M_DELOBJ_FAILED = 9,
    CTLWM2M_SEMPH_ERROR = 10,
    CTLWM2M_PARAM_LEN_OVERFLOW = 14,
    CTLWM2M_PLATFORM_NOT_READY = 15,
    CTLWM2M_DATALEN_NOT_EVEN = 17,
    CTLWM2M_NOT_ALLOWED_CONNECT  = 32,
    CTLWM2M_NOT_SEND_COMMAND  = 33,
    CTLWM2M_CREATE_SESSION_FAILED  = 34
}_AtCtLwm2mError;


#if 0
typedef enum AT_MQTT_ERROR
{
    MQTT_PARAM_ERROR = 1,                             /**/
    MQTT_CREATE_CLIENT_ERROR = 2,                     /**/
    MQTT_CREATE_SOCK_ERROR = 3,                       /**/
    MQTT_CONNECT_TCP_FAIL = 4,                        /**/
    MQTT_CONNECT_MQTT_FAIL = 5,                       /**/
    MQTT_SUB_FAIL = 6,                                /**/
    MQTT_UNSUB_FAIL = 7,                              /**/
    MQTT_SEND_FAIL = 8,                               /**/
    MQTT_DELETE_FAIL = 9,                             /**/
    MQTT_FIND_CLIENT_FAIL = 10,                       /**/
    MQTT_NOT_SUPPORT = 11,                            /**/
    MQTT_NOT_CONNECTED = 12,                          /**/
    MQTT_INFO_FAIL = 13,                              /**/
    MQTT_NETWORK_FAIL = 14,                           /**/
    MQTT_PARAM_FAIL = 15,                             /**/
    MQTT_TASK_FAIL = 16,                              /**/
    MQTT_RECV_FAIL = 17,
    MQTT_ALI_ENCRYP_FAIL = 18,

}_AtMqttError;
#endif
#if 0
typedef enum AT_COAP_ERROR
{
    COAP_PARAM_ERROR = 1,                             /**/
    COAP_CREATE_CLIENT_ERROR = 2,                     /**/
    COAP_CREATE_SOCK_ERROR = 3,                       /**/
    COAP_CONNECT_UDP_FAIL = 4,                        /**/
    COAP_CONNECT_COAP_FAIL = 5,                       /**/
    COAP_SEND_FAIL = 6,                               /**/
    COAP_DELETE_FAIL = 7,                             /**/
    COAP_FIND_CLIENT_FAIL = 8,                       /**/
    COAP_NOT_SUPPORT = 9,                            /**/
    COAP_NOT_CONNECTED = 10,                          /**/
    COAP_INFO_FAIL = 11,                              /**/
    COAP_NETWORK_FAIL = 12,                           /**/
    COAP_URI_FAIL = 13,                           /**/
    COAP_TASK_FAIL = 14,                          /**/
    COAP_RECREATE_CLIENT_ERROR = 15,                      /**/
    COAP_SEND_NOT_END_FAIL = 16,
    COAP_RECV_FAIL = 17,

}_AtCoapError;
#endif


typedef enum AT_CUSTOM_ERROR
{
    CUSTOM_ERROR = 0,                             /**/
    CUSTOM_PARAM_ERROR = 1,                             /**/
    CUSTOM_OPERATION_NOT_SUPPORT = 2,                     /**/
}_AtCustomError;






/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/


#if 0
/*
 * SigId: SIG_APP_APPL_CNF
*/
typedef struct ApplRetCnfTag
{
    struct {
        UINT16      cnfId;      //8 MSB bits APPL SG ID | 8 bits APPL PRIM ID
        UINT16      srcHandler; //Handler from CacCmiReq
        UINT16      rc;
        UINT16      reserved;
    }header;

    UINT8 body[];
}ApplRetCnf;
#endif

/*
 * SigId: SIG_CMS_APPL_REQ
 *  Signal send to other APP task
*/
typedef struct CmsApplReq_Tag
{
    struct {
        UINT8       appId;      //CmsAppId
        UINT8       primId;     //prim ID in each APP group
        UINT16      srcHandler;
    }header;

    UINT8 body[];
}CmsApplReq;

/*
 * SigId: SIG_CMS_APPL_CNF
 * Signal sent from APP tasks
*/
typedef struct CmsApplCnf_Tag
{
    struct {
        UINT8       appId;      //CmsAppId
        UINT8       primId;     //prim ID in each APP group
        UINT16      srcHandler; //Handler
        UINT16      rc;
        UINT16      rsvd;
    }header;

    UINT8 body[];
}CmsApplCnf;

/*
 * SigId: SIG_CMS_APPL_IND
 * Signal sent from APP tasks
*/
typedef struct CmsApplInd_Tag
{
    struct {
        UINT8       appId;      //CmsAppId
        UINT8       primId;     //prim ID in each APP group

        /*
         * As some indication is triggered by some AT request, in such as need to fill this "reqHandler",
         *  otherwise set to "BROADCAST_IND_HANDLER".
        */
        UINT16      reqHandler;
    }header;

    UINT8 body[];
}CmsApplInd;



/*
 * SigId: SIG_CUSTOMER_CNF, used as an example
*/
typedef struct custRetCnfTag
{
    struct {
        UINT16      cnfId;
        UINT16      srcHandler; //Handler from CacCmiReq
        UINT16      rc;
        UINT16      reserved;
    }header;

    UINT8 body[];
}custRetCnf;

/*
 * SigIg: SIG_CUSTOMER_IND, used as an example
*/
typedef struct custRetIndTag
{
    struct {
        UINT16      indId;
        UINT16      srcHandler;
        UINT16      rc;
        UINT16      reserved;
    }header;

    UINT8 body[];
}custRetInd;





/******************************************************************************
 *****************************************************************************
 * CMS EXTERNAL API
 *****************************************************************************
******************************************************************************/


/*
 * APP send the "SIG_CMS_APPL_CNF" to CMS task
*/
CmsRetId applSendCmsCnf(UINT16 reqHandler, UINT16 rcCode, UINT8 appId, UINT8 primId, UINT16 primSize, void *pPrimBody);

/*
 * APP send the "SIG_CMS_APPL_IND" to CMS task
*/
CmsRetId applSendCmsInd(UINT16 reqHandler, UINT8 appId, UINT8 primId, UINT16 primSize, void *pPrimBody);


#endif

