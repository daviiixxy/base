/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: ec_coap_api.h
 *
 *  Description: COAP interface layer header file
 *
 *  History:
 *
 *  Notes:
 *
******************************************************************************/
#ifndef __EC_COAP_API_H__
#define __EC_COAP_API_H__

//#include "at_coap_task.h"

/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/


/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/
/*
 * APPL SGID: APPL_COAP, related PRIM ID
*/
typedef enum applCoapPrimId_Enum
{
    APPL_COAP_PRIM_ID_BASE = 0,

    APPL_COAP_CREATE_REQ,
    APPL_COAP_CREATE_CNF,
    APPL_COAP_CREATE_IND,

    APPL_COAP_DELETE_REQ,
    APPL_COAP_DELETE_CNF,
    APPL_COAP_DELETE_IND,

    APPL_COAP_ADDRES_REQ,
    APPL_COAP_ADDRES_CNF,
    APPL_COAP_ADDRES_IND,

    APPL_COAP_HEAD_REQ,
    APPL_COAP_HEAD_CNF,
    APPL_COAP_HEAD_IND,

    APPL_COAP_OPTION_REQ,
    APPL_COAP_OPTION_CNF,
    APPL_COAP_OPTION_IND,

    APPL_COAP_SEND_REQ,
    APPL_COAP_SEND_CNF,
    APPL_COAP_SEND_IND,

    APPL_COAP_CNF_REQ,
    APPL_COAP_CNF_CNF,
    APPL_COAP_CNF_IND,

    APPL_COAP_RECV_REQ,
    APPL_COAP_RECV_CNF,
    APPL_COAP_RECV_IND,

    APPL_COAP_PRIM_ID_END = 0xFF
}applCoapPrimId;

/*
 * COAP error code
*/
typedef enum AT_COAP_ERROR
{
    COAP_PARAM_ERROR = 1,                             /**/
    COAP_CREATE_CLIENT_ERROR = 2,                     /**/
    COAP_CREATE_SOCK_ERROR = 3,                       /**/
    COAP_CONNECT_UDP_FAIL = 4,                        /**/
    COAP_CONNECT_COAP_FAIL = 5,                       /**/
    COAP_SUB_FAIL = 6,                                /**/
    COAP_UNSUB_FAIL = 7,                              /**/
    COAP_SEND_FAIL = 8,                               /**/
    COAP_DELETE_FAIL = 9,                             /**/
    COAP_FIND_CLIENT_FAIL = 10,                       /**/
    COAP_NOT_SUPPORT = 11,                            /**/
    COAP_NOT_CONNECTED = 12,                          /**/
    COAP_INFO_FAIL = 13,                              /**/
    COAP_NETWORK_FAIL = 14,                           /**/
    COAP_URI_FAIL = 15,                             /**/
    COAP_TASK_FAIL = 16,                            /**/
    COAP_RECREATE_CLIENT_ERROR = 17,                /**/
    COAP_SEND_NOT_END_FAIL = 18,
    COAP_RECV_FAIL = 19,

}atCoapError;



/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/



#endif


