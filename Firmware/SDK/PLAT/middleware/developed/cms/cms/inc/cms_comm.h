/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    cms_comm.h
 * Description:  Communication Modem Service layer/task common header file
 * History:      Rev1.0   2018-08-06
 *
 ****************************************************************************/
#ifndef __CMS_COMM_H__
#define __CMS_COMM_H__
#include "osasys.h"
#include "ostask.h"
#include "cms_util.h"

#define AT_QUEUE_MAX_LEN                    16
#define UART_EVENT_RX_FLAG                  0x01
#define UART_EVENT_OPT                      0x00
#define UART_EVENT_TIME_OUT                 0xffffffffUL
#define UART_BUF_LEN                        16
#define READ_WAIT                           1
#define READ_DATA                           2
#define CMI_SYNC_MAX_REQUESTS               10

enum appMsgType {
  APP_MSG_API,
  APP_MSG_API_CALL,
  APP_MSG_CALLBACK
};




NBStatus_t appCallbackWithNoBlock(app_callback_fn function, void *ctx);
void cmsWakeupPs(void *arg);

#endif

