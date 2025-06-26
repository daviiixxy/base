/******************************************************************************

  @file    iottask.h

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------

 *****************************************************************************/

#ifndef _IOTTASK_H_
#define _IOTTASK_H_

#define LWM2M_TASK_STACK_SIZE			(6656)	 /*6.5k*/
#define LWM2M_RX_TASK_STACK_SIZE		(6*1024) /*6k*/ 	
#define COAP_TASK_STACK_SIZE			(6*1024) /*6k*/ 	
#define AT_TASK_STACK_SIZE				(6656)	 /*6.5k*/
#define AT_TASK_QUEUE_SIZE				10

#define LWM2M_TASK_PRIORITY				osPriorityBelowNormal4
#define LWM2M_RX_TASK_PRIORITY			osPriorityBelowNormal6
#define COAP_TASK_PRIORITY				osPriorityBelowNormal7
#define AT_TASK_PRIORITY				osPriorityLow7


#endif //_IOTTASK_H_

