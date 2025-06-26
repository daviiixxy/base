/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *******************************************************************************/

#if !defined(MQTTFreeRTOS_H)
#define MQTTFreeRTOS_H

#include "FreeRTOS.h"
#include "FreeRTOS_Sockets.h"
// #include "FreeRTOS_IP.h"
#include "semphr.h"
#include "task.h"

///MQTT client results
typedef enum {
    MQTT_CONN_OK = 0,        ///<Success
    MQTT_PROCESSING,    ///<Processing
    MQTT_PARSE,         ///<url Parse error
    MQTT_DNS,           ///<Could not resolve name
    MQTT_PRTCL,         ///<Protocol error
    MQTT_NOTFOUND,      ///<HTTP 404 Error
    MQTT_REFUSED,       ///<HTTP 403 Error
    MQTT_ERROR,         ///<HTTP xxx error
    MQTT_TIMEOUT,       ///<Connection timeout
    MQTT_CONN,          ///<Connection error
    MQTT_FATAL_ERROR, //fatal error when conenct
    MQTT_CLOSED,        ///<Connection was closed by remote host
    MQTT_MOREDATA,      ///<Need get more data
    MQTT_OVERFLOW,      ///<Buffer overflow
    MQTT_MBEDTLS_ERR,  

}MQTTResult;
typedef struct Timer 
{
	TickType_t xTicksToWait;
	TimeOut_t xTimeOut;
} Timer;

typedef struct Network Network;

struct Network
{
	xSocket_t my_socket;
	int (*mqttread) (Network*, unsigned char*, int, int);
	int (*mqttwrite) (Network*, unsigned char*, int, int);
	int (*disconnect) (Network*);
};

void TimerInit(Timer*);
char TimerIsExpired(Timer*);
void TimerCountdownMS(Timer*, unsigned int);
void TimerCountdown(Timer*, unsigned int);
int TimerLeftMS(Timer*);

typedef struct Mutex
{
	SemaphoreHandle_t sem;
} Mutex;

void MutexInit(Mutex*);
int MutexLock(Mutex*);
int MutexUnlock(Mutex*);

typedef struct Thread
{
	TaskHandle_t task;
} Thread;

int ThreadStart(Thread*, void (*fn)(void*), void* arg);

int FreeRTOS_read(Network*, unsigned char*, int, int);
int FreeRTOS_write(Network*, unsigned char*, int, int);
int FreeRTOS_disconnect(Network*);

void NetworkInit(Network*);
int NetworkConnect(Network*, char*, int);
int NetworkSetConnTimeout(Network* n, int send_timeout, int recv_timeout);

int TLSNetworkConnect(Network* n, char* addr, int port, int timeout_ms);

#endif
