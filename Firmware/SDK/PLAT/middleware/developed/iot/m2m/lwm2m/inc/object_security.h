/******************************************************************************

  @file    object_security.h
  @brief   Security Object Interface File
           This file declares the interfaces and data structures if any, of  
           security object implementation
  ---------------------------------------------------------------------------
  Copyright (c) 2016-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _OBJECT_SECURITY_H
#define _OBJECT_SECURITY_H

//<PORT_TODO>#include "qapi_ssl.h"

#if defined (LWM2M_BOOTSTRAP)
#define LWM2M_SECURITY_RESOURCE_INST_IS_HOLD_OFF_TIMER       0
#define LWM2M_SECURITY_RESOURCE_INST_IS_BOOTSTRAPPED         1
#endif
#define MAX_CUST_30000_RES_INSTANCES 10

#define MAX_CERT_NAME_LEN 64//<PORT_TODO>QAPI_NET_SSL_MAX_CERT_NAME_LEN 
#define HOLD_OFF_TIMER_DEFAULT 10
#define MAX_SMS_NUMBER 32

typedef enum
{
  CERT_SOURCE_UNKNOWN  = 0,
  CERT_SOURCE_PRELOAD,
  CERT_SOURCE_NETWORK,
} cert_source_enum;

typedef struct _security_instance_
{
  struct _security_instance_ * next;        // matches lwm2m_list_t::next
  uint16_t                     instanceId;  // matches lwm2m_list_t::id
  char *                       uri;
  bool                         isBootstrap;
  uint8_t                      securityMode;
  char                         clientCertFName[MAX_CERT_NAME_LEN]; /* holding secure client certificate/psk file name */
  char *                       publicIdentity;
  uint16_t                     publicIdLen;
  char                         serverCertFName[MAX_CERT_NAME_LEN]; /* holding secure server certificate/psk file name */
  char *                       serverPublicKey;
  uint16_t                     serverPublicKeyLen;
  char *                       secretKey;
  uint16_t                     secretKeyLen;
  uint8_t                      smsSecurityMode;
  char *                       smsParams; // SMS binding key parameters
  uint16_t                     smsParamsLen;
  char *                       smsSecret; // SMS binding secret key
  uint16_t                     smsSecretLen;
  uint16_t                     shortID;
  uint32_t                     clientHoldOffTime;
  char *                       sms_number;
#if defined (LWM2M_BOOTSTRAP)
  resource_instance_int_list_t*    custom30000List;
#endif  
  cert_source_enum		       cert_source;

} security_instance_t;

#ifdef FACTORY_BOOTSTRAPPING
/**
 * @fn  lwm2m_object_t * get_security_object();
 * @brief   This function creates a empty security object(No Instantiation)
 *
 * @return  if successful, a pointer to created object, else null
 */
lwm2m_object_t * get_security_object(void);
#else
/**
 * @fn  lwm2m_object_t * get_security_object()
 * @brief   This function creates security object and instantiates it with
 *          the given values
 *
 * @param   serverId    Short server ID of the lwm2m server
 * @param   serverUri   URI of the lwm2m server
 * @param   bsPskId     Public identity used to connect securely with the server
 * @param   psk         Pre-Shared key used in secure connection with the server
 * @param   pskLen      Length of psk
 * @param   isBootstrap Indicates if the server is a bootstrap server or m2m server
 *
 * @return  if successful, a pointer to created object, else null
 */
lwm2m_object_t * get_security_object(int serverId, const char* serverUri,
                 char * bsPskId, char * psk, uint16_t pskLen, bool isBootstrap);
#endif

/**
 * @fn  void clean_security_object(lwm2m_object_t * objectP);
 * @brief   Deletes all instances of the security object
 *
 * @param   objectP pointer to security object
 *
 * @return  void
 */
void clean_security_object(lwm2m_object_t * objectP);

/**
 * @fn  char * get_server_uri(lwm2m_object_t * objectP, uint16_t secObjInstID);
 * @brief   This function is used to get the URI of the server
 *
 * @param   objectP         pointer to security object
 * @param   secObjInstID    instance id of the object instance
 *
 * @return  URI string 
 */
char * get_server_uri(lwm2m_object_t * objectP, uint16_t secObjInstID);

int load_security_persistent_info(lwm2m_object_t *secObjInstP);
int store_security_persistent_info(security_instance_t *secInstanceP, boolean store);
int lwm2m_ssl_security_store(security_instance_t *instance, uint16_t shortID);
void lwm2m_update_security_credentials(lwm2m_context_t * contextP);

#if defined (LWM2M_BOOTSTRAP) 
bool get_serverobj_isbootstrapped(lwm2m_object_t * objectP, uint16_t secObjInstID);
void update_isbootstrap_field_for_security_instance(lwm2m_object_t * sec_objectP, uint16_t secObjInstID);
void update_security_isbootstrap_flag(lwm2m_object_t * sec_objectP);
#endif

#endif //_OBJECT_SECURITY_H
