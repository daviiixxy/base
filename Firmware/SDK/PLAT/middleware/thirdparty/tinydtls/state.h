/*******************************************************************************
 *
 * Copyright (c) 2011, 2012, 2013, 2014, 2015 Olaf Bergmann (TZI) and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v. 1.0 which accompanies this distribution.
 *
 * The Eclipse Public License is available at http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 * http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Olaf Bergmann  - initial API and implementation
 *    Hauke Mehrtens - memory optimization, ECC integration
 *
 *******************************************************************************/

/**
 * @file state.h
 * @brief state information for DTLS FSM
 */

#ifndef _DTLS_STATE_H_
#define _DTLS_STATE_H_

//#include <sys/types.h>
#include <stdint.h>

#include "global.h"
#include "hmac.h"

typedef enum { 
  DTLS_STATE_INIT = 0,
  DTLS_STATE_WAIT_CLIENTHELLO,        //1
  DTLS_STATE_WAIT_CLIENTCERTIFICATE,  //2
  DTLS_STATE_WAIT_CLIENTKEYEXCHANGE,  //3
  DTLS_STATE_WAIT_CERTIFICATEVERIFY,  //4
  DTLS_STATE_WAIT_CHANGECIPHERSPEC,   //5
  DTLS_STATE_WAIT_FINISHED,           //6
  DTLS_STATE_FINISHED,                //7
  /* client states */
  DTLS_STATE_CLIENTHELLO,             //8
  DTLS_STATE_WAIT_SERVERCERTIFICATE,  //9
  DTLS_STATE_WAIT_SERVERKEYEXCHANGE,  //10
  DTLS_STATE_WAIT_SERVERHELLODONE,    //11

  DTLS_STATE_CONNECTED,               //12
  DTLS_STATE_CLOSING,                 //13
  DTLS_STATE_CLOSED                   //14
} dtls_state_t;

typedef struct {
  uint16_t mseq_s;	     /**< send handshake message sequence number counter */
  uint16_t mseq_r;	     /**< received handshake message sequence number counter */

  /** pending config that is updated during handshake */
  /* FIXME: dtls_security_parameters_t pending_config; */

  /* temporary storage for the final handshake hash */
  dtls_hash_ctx hs_hash;
} dtls_hs_state_t;
#endif /* _DTLS_STATE_H_ */
