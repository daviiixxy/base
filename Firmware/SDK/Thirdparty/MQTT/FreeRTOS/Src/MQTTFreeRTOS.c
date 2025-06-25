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
 *    Ian Craggs - convert to FreeRTOS
 *******************************************************************************/

#include "MQTTFreeRTOS.h"
#include "debug_log.h"

int ThreadStart(Thread* thread, void (*fn)(void*), void* arg)
{
    int rc = 0;
    uint16_t usTaskStackSize = (configMINIMAL_STACK_SIZE * 5);
    UBaseType_t uxTaskPriority = uxTaskPriorityGet(NULL); /* set the priority as the same as the calling task*/

    rc = xTaskCreate(fn,    /* The function that implements the task. */
        "MQTTTask",         /* Just a text name for the task to aid debugging. */
        usTaskStackSize,    /* The stack size is defined in FreeRTOSIPConfig.h. */
        arg,                /* The task parameter, not used in this case. */
        uxTaskPriority,     /* The priority assigned to the task is defined in FreeRTOSConfig.h. */
        &thread->task);     /* The task handle is not used. */

    return rc;
}


void MutexInit(Mutex* mutex)
{
    mutex->sem = xSemaphoreCreateMutex();
}

int MutexLock(Mutex* mutex)
{
    return xSemaphoreTake(mutex->sem, portMAX_DELAY);
}

int MutexUnlock(Mutex* mutex)
{
    return xSemaphoreGive(mutex->sem);
}


void TimerCountdownMS(Timer* timer, unsigned int timeout_ms)
{
    timer->xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
    vTaskSetTimeOutState(&timer->xTimeOut); /* Record the time at which this function was entered. */
}


void TimerCountdown(Timer* timer, unsigned int timeout) 
{
    TimerCountdownMS(timer, timeout * 1000);
}


int TimerLeftMS(Timer* timer) 
{
    xTaskCheckForTimeOut(&timer->xTimeOut, &timer->xTicksToWait); /* updates xTicksToWait to the number left */
    return (int)(((int)timer->xTicksToWait < 0) ? 0 : (timer->xTicksToWait * portTICK_PERIOD_MS));
}


char TimerIsExpired(Timer* timer)
{
    return xTaskCheckForTimeOut(&timer->xTimeOut, &timer->xTicksToWait) == pdTRUE;
}


void TimerInit(Timer* timer)
{
    timer->xTicksToWait = 0;
    memset(&timer->xTimeOut, '\0', sizeof(timer->xTimeOut));
}


int FreeRTOS_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    TickType_t xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
    TimeOut_t xTimeOut;
    int recvLen = 0;

    vTaskSetTimeOutState(&xTimeOut); /* Record the time at which this function was entered. */
    do
    {
        int rc = 0;

        FreeRTOS_setsockopt(n->my_socket, 0, FREERTOS_SO_RCVTIMEO, &xTicksToWait, sizeof(xTicksToWait));
        rc = FreeRTOS_recv(n->my_socket, buffer + recvLen, len - recvLen, 0);
        if (rc > 0)
            recvLen += rc;
        else if (rc < 0)
        {
            recvLen = rc;
            break;
        }
    } while (recvLen < len && xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) == pdFALSE);

    return recvLen;
}


int FreeRTOS_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    TickType_t xTicksToWait = timeout_ms / portTICK_PERIOD_MS; /* convert milliseconds to ticks */
    TimeOut_t xTimeOut;
    int sentLen = 0;

    vTaskSetTimeOutState(&xTimeOut); /* Record the time at which this function was entered. */
    do
    {
        int rc = 0;

        FreeRTOS_setsockopt(n->my_socket, 0, FREERTOS_SO_RCVTIMEO, &xTicksToWait, sizeof(xTicksToWait));
        rc = FreeRTOS_send(n->my_socket, buffer + sentLen, len - sentLen, 0);
        if (rc > 0)
            sentLen += rc;
        else if (rc < 0)
        {
            sentLen = rc;
            break;
        }
    } while (sentLen < len && xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) == pdFALSE);

    return sentLen;
}


int FreeRTOS_disconnect(Network* n)
{
    int ret;
    ret = FreeRTOS_closesocket(n->my_socket);
    return ret;
}

int FreeRTOSConnectTimeout(INT32 connectFd, UINT32 timeout)
{
    fd_set writeSet;
    fd_set errorSet;
    FD_ZERO(&writeSet);
    FD_ZERO(&errorSet);
    FD_SET(connectFd,&writeSet);
    FD_SET(connectFd,&errorSet);
    struct timeval tv;
    tv.tv_sec  = timeout;
    tv.tv_usec = 0;
    
    if(select(connectFd+1, NULL, &writeSet, &errorSet, &tv)<=0)
    {
        int mErr = sock_get_errno(connectFd);
        //HT_TRACE(UNILOG_MQTT, mqttConnectTimeout_1, P_WARNING, 1, "connect select<0 get errno=%d", mErr);
        if(mErr)
        {
            return MQTT_CONN;
        }
        else
        {
            return MQTT_TIMEOUT;
        }
    }
    else
    {
        if(FD_ISSET(connectFd, &errorSet))
        {
            int mErr = sock_get_errno(connectFd);
            //HT_TRACE(UNILOG_MQTT, mqttConnectTimeout_2, P_WARNING, 1, "select error fd set get errno=%d", mErr);
            if(mErr)
            {
                return MQTT_CONN;
            }
        }
        else if(FD_ISSET(connectFd, &writeSet))
        {
            //HT_TRACE(UNILOG_MQTT, mqttConnectTimeout_3, P_WARNING, 0, "errno=115(EINPROGRESS) connect success in time(10s)");
        }
    }

    return MQTT_CONN_OK;

}
void NetworkInit(Network* n) {
    n->my_socket = -1;
    n->mqttread = FreeRTOS_read;
    n->mqttwrite = FreeRTOS_write;
    n->disconnect = FreeRTOS_disconnect;
}

int TLSNetworkConnect(Network* n, char* addr, int port, int timeout_ms)
{
    struct sockaddr_in sAddr;
    int retVal = -1;
    ip_addr_t ipAddress;
    INT32 errCode;
    INT32 flags = 0;

    if ((FreeRTOS_gethostbyname(addr, &ipAddress)) != 0)
        goto exit;
    sAddr.sin_family = AF_INET;
    sAddr.sin_port = FreeRTOS_htons((uint16_t)port);
    sAddr.sin_addr.s_addr = ipAddress.u_addr.ip4.addr;
    memset(sAddr.sin_zero, 0, 8);
    flags = fcntl(n->my_socket, F_GETFL, 0);

    if ((retVal = FreeRTOS_connect(n->my_socket, (struct sockaddr *)&sAddr, sizeof(sAddr))) < 0)
    {
        errCode = sock_get_errno(n->my_socket);
        if(errCode == EINPROGRESS)
        {
            ////HT_TRACE(UNILOG_MQTT, TLSNetworkConnect_0, P_ERROR, 0, "TLSConnectSocket connect is ongoing");

            retVal = FreeRTOSConnectTimeout(n->my_socket, (UINT32 )timeout_ms); //for bearer suspend timeout is 25s
            if(retVal == 0)
            {
              //  //HT_TRACE(UNILOG_MQTT, TLSNetworkConnect_1, P_INFO, 0, "TLSConnectSocket connect success");
            }
            else
            {
                //HT_TRACE(UNILOG_MQTT, TLSNetworkConnect_2, P_ERROR, 1, "TLSConnectSocket connect fail,error code %d", errCode);
                if(socket_error_is_fatal(errCode))
                {
                    retVal = 1;
                }
            }
        }
        else
        {
            //HT_TRACE(UNILOG_MQTT, TLSNetworkConnect_3, P_ERROR, 1, "TLSConnectSocket connect fail %d",errCode);
            retVal = 1;
        }
    }
    else
    {
        //HT_TRACE(UNILOG_MQTT, TLSNetworkConnect_4, P_ERROR, 0, "TLSConnectSocket connect success");
    }

    /* Initialize mbedtls. */
    /* Initialize TLS contexts and set credentials. */
    /* Perform TLS handshake. */
    
    fcntl(n->my_socket, F_SETFL, flags&~O_NONBLOCK); 

exit:
    return retVal;
}

int NetworkConnect(Network* n, char* addr, int port)
{
    struct sockaddr_in sAddr;
    int retVal = -1;
    ip_addr_t ipAddress;
    INT32 errCode;
    INT32 flags = 0;

    if ((FreeRTOS_gethostbyname(addr, &ipAddress)) != 0) {
        goto exit;
    }
        
    sAddr.sin_family = AF_INET;
    sAddr.sin_port = FreeRTOS_htons((uint16_t)port);
    sAddr.sin_addr.s_addr = ipAddress.u_addr.ip4.addr;
    memset(sAddr.sin_zero, 0, 8);
    flags = fcntl(n->my_socket, F_GETFL, 0);

    if ((retVal = FreeRTOS_connect(n->my_socket, (struct sockaddr *)&sAddr, sizeof(sAddr))) < 0)
    {
        errCode = sock_get_errno(n->my_socket);
        if(errCode == EINPROGRESS)
        {
            //HT_TRACE(UNILOG_MQTT, mqttConnectSocket_2, P_ERROR, 0, "mqttConnectSocket connect is ongoing");

            retVal = FreeRTOSConnectTimeout(n->my_socket, 30); //for bearer suspend timeout is 25s
            if(retVal == 0)
            {
                //HT_TRACE(UNILOG_MQTT, mqttConnectSocket_3, P_INFO, 0, "mqttConnectSocket connect success");
            }
            else
            {
                //HT_TRACE(UNILOG_MQTT, mqttConnectSocket_4, P_ERROR, 1, "mqttConnectSocket connect fail,error code %d", errCode);
                if(socket_error_is_fatal(errCode))
                {
                    retVal = 1;
                }
            }
        }
        else
        {
            //HT_TRACE(UNILOG_MQTT, mqttConnectSocket_5, P_ERROR, 1, "mqttConnectSocket connect fail %d",errCode);
            retVal = 1;
        }
    }
    else
    {
        //HT_TRACE(UNILOG_MQTT, mqttConnectSocket_1, P_ERROR, 0, "mqttConnectSocket connect success");
    }

    fcntl(n->my_socket, F_SETFL, flags&~O_NONBLOCK); 

exit:
    return retVal;
}
int NetworkSetConnTimeout(Network* n, int send_timeout, int recv_timeout)
{
    int ret = 0;
#if LWIP_SO_SNDRCVTIMEO_NONSTANDARD
    int tx_timeout = send_timeout;
    int rx_timeout = recv_timeout;
#else
  struct timeval tx_timeout;
  tx_timeout.tv_sec = send_timeout/1000;
  tx_timeout.tv_usec = (send_timeout%1000)*1000;
  struct timeval rx_timeout;
  rx_timeout.tv_sec = recv_timeout/1000;
  rx_timeout.tv_usec = (recv_timeout%1000)*1000;
#endif   

    if ((n->my_socket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP)) < 0)
        return 1;

    ret = FreeRTOS_setsockopt(n->my_socket, SOL_SOCKET, SO_SNDTIMEO, &tx_timeout, sizeof(tx_timeout));
    if(ret != 0)
    {
    
        //HT_TRACE(UNILOG_MBEDTLS, NetworkSetConnTimeout_0, P_INFO, 1, "..11. TLS socket set timeout fail..socket=%d.",n->my_socket);
        //return 1;
    }
    ret = FreeRTOS_setsockopt(n->my_socket, SOL_SOCKET, SO_RCVTIMEO, &rx_timeout, sizeof(rx_timeout));
    if(ret != 0)
    {
        //HT_TRACE(UNILOG_MBEDTLS, NetworkSetConnTimeout_1, P_INFO, 0 , "..22. TLS socket set timeout fail...");
        //return 1;
    }
    INT32 flags = fcntl(n->my_socket, F_GETFL, 0);
    if(flags < 0)
    {
        //HT_TRACE(UNILOG_MBEDTLS,NetworkSetConnTimeout_2, P_INFO, 0, "mqtt get file cntrl flags fail");
        return 1;
    }
    
    fcntl(n->my_socket, F_SETFL, flags|O_NONBLOCK); //set socket as nonblock for connect timeout
    
    return 0;
}
