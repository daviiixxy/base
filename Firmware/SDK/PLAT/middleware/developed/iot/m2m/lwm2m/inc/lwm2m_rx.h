#ifndef LWM2M_RX_H
#define LWM2M_RX_H
/*===========================================================================
                         LWM2M_RX.H

DESCRIPTION
   This header file contains definitions used internally by the LWM2M Module. 
  
   Copyright (c) 2017-2020 by Qualcomm Technologies INCORPORATED.
   All Rights Reserved.
   Qualcomm Confidential and Proprietary.

Export of this technology or software is regulated by the U.S. Government.
Diversion contrary to U.S. law prohibited.

===========================================================================*/
//#include "lwm2mclient.h" 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//#include "qurt_signal.h"
//#include "qurt_thread.h"
//#include "qurt_error.h"
#include "err.h"
//#include "qurt.h"
//#include "rcinit.h"
//#include "qurt_mutex.h"
//#include "dsm.h"
#include "internals.h"


#define LWM2M_MAX_DL_PKTS      50

/*------------------------------------------------------------------------------
  Typedef Declaration
------------------------------------------------------------------------------*/
typedef qurt_signal_t lwm2m_signal_t;

/*------------------------------------------------------------------------------
  This is the command queue that will be used to enqueue commands from
  external entities
------------------------------------------------------------------------------*/
typedef q_type lwm2m_task_pkt_q;


typedef enum
{
  LWM2M_MIN_CMD_EVT,
  LWM2M_REQ_PKT,
  LWM2M_RESP_PKT,
  LWM2M_PROFILE_PROCESSING,
  LWM2M_REGISTRATION_CB,
  LWM2M_DEREGISTRATION_CB,
  LWM2M_REGISTRATION_UPDATE_CB,
  LWM2M_BOOTSTRAP_CB,
  LWM2M_EXT_APPLICATION_CB,
#ifdef PSM_LWM2M
  LWM2M_PSM_CB,      // LwM2M PSM callback recieved event
#endif
  LWM2M_EVENT_CB,
  LWM2M_MAX_CMD_EVT
} lwm2m_pkt_id_e;


/*------------------------------------------------------------------------------
  Structure Declaration
------------------------------------------------------------------------------*/

typedef struct
{
  lwm2m_signal_t              lwm2m_signal;
  qurt_mutex_t                lwm2m_mutex;
  q_type*                     cmd_q_ptr;
}lwm2m_pktq_t;


typedef struct{
  q_link_type                   link;
  lwm2m_pkt_id_e                cmd_id;
} lwm2m_pkt_hdr_t;


typedef struct{
  void * cHandle;
  void * message;
  void * clientData;
} lwm2m_pkt_data_t;


typedef struct{
  lwm2m_pkt_hdr_t               cmd_hdr;
  lwm2m_pkt_data_t              cmd_data;
} lwm2m_pkt_t;


/*------------------------------------------------------------------------------
  Signal Related Macros
------------------------------------------------------------------------------*/
#define LWM2M_SIGNAL_MASK       0x00000001

#define LWM2M_TASK_IS_SIG_SET(signal, signal_mask)  ((signal & signal_mask) != 0)

#define LWM2M_TASK_CLEAR_SIG(signal, signal_mask) \
                                    qurt_signal_clear(&signal,signal_mask)

#define LWM2M_TASK_SET_SIG(signal, signal_mask) \
                                    qurt_signal_set(&signal, signal_mask)

/*------------------------------------------------------------------------------
  Command Queue Related Macros
------------------------------------------------------------------------------*/

#define LWM2M_CMD_ID_RANGE_CHECK(cmd_id) \
                                       ( (cmd_id > LWM2M_MIN_CMD_EVT) && \
                                         (cmd_id < LWM2M_MAX_CMD_EVT) )

/*==============================================================================
FUNCTION LWM2M_PROCESS_COMMANDS()

DESCRIPTION
  This function dequeues all outstanding commands from and dispatches the
  processor functions.

PARAMETERS
  NONE

RETURN VALUE
  None

DEPENDENCIES 
  None 

SIDE EFFECTS
  None
==============================================================================*/
void lwm2m_process_pkt(void);


/*===========================================================================

FUNCTION LWM2M_CMDQ_INIT()

DESCRIPTION
  Initialize the command queues and set the command queue pointers in the
  lwm2m_info struct to the appropriate values.

DEPENDENCIES
  None.

RETURN VALUE

SIDE EFFECTS
  None

=========================================================================*/
void lwm2m_pkt_init (lwm2m_pktq_t * lwm2m_state);


/*===========================================================================

FUNCTION LWM2M_GET_CMD_BUFFER

DESCRIPTION
  This function is used to allocate a command buffer that the client can
  then enqueue into the command queue.

DEPENDENCIES
  None.

RETURN VALUE
  Pointer to the command

SIDE EFFECTS
  None

=========================================================================*/
lwm2m_pkt_t* lwm2m_get_pkt_buffer(void);


/*===========================================================================

FUNCTION  LWM2M_ENQUEUE_CMD

DESCRIPTION
  This function is used to enqueue the command into the LWM2M queue

DEPENDENCIES
  None.

PARAMETERS
  Pointer to the command to enqueue

RETURN VALUE
  Void

SIDE EFFECTS
  None

=========================================================================*/
void lwm2m_enqueue_pkt(lwm2m_pkt_t* cmd_ptr);


/*===========================================================================

FUNCTION LWM2M_DEQUEUE_CMD

DESCRIPTION
  This function de-queues and returns a command from the LWM2M task
  command queues.

DEPENDENCIES
  None

RETURN VALUE
  Pointer to the command if present in the queue. NULL otherwise

SIDE EFFECTS
  None

==============================================================================*/
static lwm2m_pkt_t* lwm2m_dequeue_pkt( void );

/*===========================================================================

FUNCTION LWM2M_CNT_CMD

DESCRIPTION
  This function returns the number of items currently queued on LWM2M task
  command queues.

DEPENDENCIES
  None
    
RETURN VALUE
  The number of items currently queued on the LWM2M task
  command queue.

SIDE EFFECTS
  None.

==============================================================================*/
int lwm2m_cnt_pkt( void );


/*=============================================================================

FUNCTION LWM2M_SET_SIGNAL

DESCRIPTION
  Set the lwm2m signal using lock protection

DEPENDENCIES
  None.

RETURN VALUE
  none

SIDE EFFECTS
  None

==============================================================================*/
void lwm2m_set_signal(void);

/*=============================================================================

FUNCTION LWM2M_MUTEX_INIT

DESCRIPTION
  lwm2m mutex Initialization

DEPENDENCIES
  None.

RETURN VALUE
  none

SIDE EFFECTS
  None

==============================================================================*/
static void lwm2m_mutex_init(void);

/*=============================================================================

FUNCTION LWM2M_SIGNAL_INIT

DESCRIPTION
  LWM2M Signal Initialization
  
DEPENDENCIES
  None.

RETURN VALUE
  none

SIDE EFFECTS
  None

==============================================================================*/
static void lwm2m_signal_init(void);

/*=============================================================================

FUNCTION LWM2M_SIGNAL_WAIT

DESCRIPTION
  This API will wait on the LWM2M signal.
  The LWM2M signal will be set during various operations.

DEPENDENCIES
  None.

RETURN VALUE
  none

SIDE EFFECTS
  None

==============================================================================*/
static void lwm2m_signal_wait(void);


#endif /* LWM2M_RX_H */


