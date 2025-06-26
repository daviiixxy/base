/******************************************************************************

  @file    object_server.h
  @brief   Server Object Interface File
           This file declares the interfaces and data structures if any, of 
           server object implementation
  ---------------------------------------------------------------------------
  Copyright (c) 2016-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _OBJECT_SERVER_H
#define _OBJECT_SERVER_H

#define LWM2M_SERVER_RESOURCE_INST_IS_REGISTERED                  0
#define LWM2M_SERVER_RESOURCE_INST_IS_CLIENT_HOLD_OFF_TIMER       1
#define MAX_CUST_30000_RES_INSTANCES 10

#define MAX_BINDING_SIZE 5
#define MAX_PREFERRED_TRANSPORT_SIZE 2
#define MAX_REG_TRIGGER_PARAM_SIZE 2

/*Enum for registration retry resources set */
typedef enum reg_retry_params_e
{
  REG_PRIORITY_SET                      = 0x01,
  INITIAL_DELAY_TIMER_SET               = 0x02,
  REG_FAILURE_SET                       = 0x04,
  BS_ON_REG_FAILURE_SET                 = 0x08,
  CONN_RETRY_COUNT_SET                  = 0x10,
  CONN_RETRY_TIMER_SET                  = 0x20,
  CONN_SEQ_DELAY_TIMER_SET              = 0x40,
  CONN_SEQ_DELAY_COUNT_SET              = 0x80,
} reg_retry_params_t;

typedef struct _server_instance_
{
  struct _server_instance_ *next;   // matches lwm2m_list_t::next
  uint16_t    instanceId;           // matches lwm2m_list_t::id
  uint16_t    shortServerId;
  uint32_t    lifetime;
  uint32_t    defaultMinPeriod;
  uint32_t    defaultMaxPeriod;
  uint32_t    disableTimeout;
  bool        storing;
  char        binding[MAX_BINDING_SIZE];
  objlink_t   apnLink; 
  bool        trigger; 
  char        prefTransport[MAX_PREFERRED_TRANSPORT_SIZE];
  bool        regTrigger; 
  char        regTriggerParam[MAX_REG_TRIGGER_PARAM_SIZE];
  uint8_t     res_set;             // Flag to check which resources are set.
  uint16_t    priority;            // Server priority 
  uint32_t    initial_delay_timer; // Time to wait before attempting first registration 
  bool        reg_failure;         // Blocking or Non-Blocking server
  bool        bs_on_failure;       // To perform rebootstraping or not in case of failure
  uint8_t     retry_count;         // No of attempts in one communication sequence.
  uint32_t    retry_timer;         // Initial timeout used for backoffs.
  uint32_t    seq_delay_timer;     // Delay between two communication sequence.
  uint8_t     seq_retry_count;     // No of communication sequence to be attempted.
  resource_instance_int_list_t*    custom30000List;
} server_instance_t;

#ifdef FACTORY_BOOTSTRAPPING
/**
 * @fn  lwm2m_object_t * get_server_object()
 * @brief   This function is used to create an empty server object
 *          (No instantiation)
 *
 * @return returns pointer to server object created if successful, 
 *         else return null
 */
lwm2m_object_t * get_server_object(void);
#else
/**
 * @fn  lwm2m_object_t * get_server_object()
 * @brief   This function is used to get the inited server object
 *
 * @param   serverId    Short Server ID of the lwm2m server
 * @param   binding     Binding mode to be used to connect to the lwm2m server
 * @param   lifetime    Lifetime period of the registration with this server
 * @param   storing     Indicates if the notifies needs to be stored if 
 *                      server disabled
 *
 * @return returns pointer to server object created if successful, 
 *         else return null
 */
lwm2m_object_t * get_server_object(int serverId, const char* binding, int lifetime,
                 bool storing);
#endif

/**
 * @fn  void clean_server_object()
 * @brief   Deletes all instances of server object
 *
 * @param   object  handle to server object
 *
 * @return  void
 */
void clean_server_object(lwm2m_object_t * object);

     
int load_server_persistent_info(lwm2m_object_t *serObjP);
int store_server_persistent_info(server_instance_t *targetP,  boolean store);
void update_isRegistered_for_server (lwm2m_object_t * serv_object,uint16_t ssid, uint8_t value);
uint32_t get_serverobj_hold_off_time(lwm2m_object_t * objectP, uint16_t servObjInstID);

#endif
