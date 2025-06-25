/******************************************************************************

  @file    uint_test.h
  @brief   Server unit test Interface File 
           This file declares the interfaces and data structures if any, of 
           unit test server implementation
  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _LWM2MSERVER_H
#define _LWM2MSERVER_H

/* Function for qcli command to start unit test lwm2m server */
QCLI_Command_Status_t lwm2m_server_start(uint32_t Parameter_Count, 
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to list clients	*/
QCLI_Command_Status_t list_clients(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to read client*/
QCLI_Command_Status_t read_client(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command todisc client */
QCLI_Command_Status_t disc_client(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to write client */
QCLI_Command_Status_t write_client(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/*Function for qcli command to write time */
QCLI_Command_Status_t write_time(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to write attr */
QCLI_Command_Status_t write_attr(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);	

/* Function for qcli command to clear client */
QCLI_Command_Status_t clear_client(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to exec client */
QCLI_Command_Status_t exec_client(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to del client */
QCLI_Command_Status_t del_client(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to create object instance */
QCLI_Command_Status_t create_object(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to observe client */
QCLI_Command_Status_t observe_client(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to cancel client observation */
QCLI_Command_Status_t cancel_observe(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

/* Function for qcli command to send roaming and out_of_roaming signals */
QCLI_Command_Status_t roaming_signal(uint32_t Parameter_Count,
    QCLI_Parameter_t* Parameter_List);

extern m2m_ser_set_call_handle(void * callHdl);
#endif
