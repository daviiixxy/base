/******************************************************************************

  @file    bootstrap_info.h
  @brief   Interface File Containing Factory Bootstrapping Interfaces and DS
           This file declares the interfaces and data structures if any, used for 
           factory bootstrapping

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _BOOTSTRAP_INFO_H
#define _BOOTSTRAP_INFO_H

#define BOOTSTRAP_CFG_FILE  "bootstrap.ini"//"/data/lwm2m/bootstrap.ini"

//This is used to set the access control owner of all object instances (there should be a server by id 100 in config)
#define DEFAULT_SERVER      100 // This is the short server ID of DM Server

/**
 * @fn  bool get_bootsrap_info(lwm2m_object_t *secObjP, lwm2m_object_t *serObjP, lwm2m_object_t *acObjP)
 * @brief   This function is used to perform factory bootstapping
 *
 * This function reads the factory bootstrap configuration and populates the Security, Server and 
 * Access Control Object Instances.
 *
 * @param   secObjP     handle to security object
 * @param   serObjP     handle to server object
 * @param   acObjP      handle to Access Control object
 *
 * @return  true if succesfully read and filled the BS info, else false.
 */
bool get_bootstrap_info(lwm2m_object_t *secObjP, lwm2m_object_t *serObjP, lwm2m_object_t *acObjP, lwm2m_object_t *apnObjP);

#endif //_BOOTSTRAP_INFO_H

