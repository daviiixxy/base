// /*******************************************************************************
//  * Copyright (c) 2014, 2017 IBM Corp.
//  *
//  * All rights reserved. This program and the accompanying materials
//  * are made available under the terms of the Eclipse Public License v1.0
//  * and Eclipse Distribution License v1.0 which accompany this distribution.
//  *
//  * The Eclipse Public License is available at
//  *    http://www.eclipse.org/legal/epl-v10.html
//  * and the Eclipse Distribution License is available at
//  *   http://www.eclipse.org/org/documents/edl-v10.php.
//  *
//  * Contributors:
//  *   Allan Stockdill-Mander/Ian Craggs - initial API and implementation and/or initial documentation
//  *   Ian Craggs - fix for #96 - check rem_len in readPacket
//  *   Ian Craggs - add ability to set message handler separately #6
//  *******************************************************************************/
#include "MQTTClient.h"
#include "HT_MQTT_Api.h"

// #include "ht_mqtt_api.h"
// #include "ht_gpio_api.h"
// #include "ht_uart_api.h"
// // #include "uart_qcx212.h"
// #ifdef FEATURE_MBEDTLS_ENABLE
// #include "sha1.h"
// #include "sha256.h"
// #include "md5.h"
// #endif

// char *mqttSendbuf = NULL;
// char *mqttReadbuf = NULL;

// unsigned char mqttJsonbuff[128];
char mqtt_payload[128];
// int ec_sensor_temp = 20;
// char ec_data_type = 3;
// int ec_data_len = 0;
// QueueHandle_t mqttRecvMsgHandle = NULL;
QueueHandle_t mqttSendMsgHandle = NULL;
QueueHandle_t appMqttMsgHandle = NULL;

osThreadId_t mqttRecvTaskHandle = NULL;
// osThreadId_t mqttSendTaskHandle = NULL;
// osThreadId_t appMqttTaskHandle = NULL;

Mutex mqttMutex1;
// Mutex mqttMutex2;
// MQTTClient mqttClient;
// Network mqttNetwork;
// int mqtt_send_task_status_flag = 0;
int mqtt_keepalive_retry_count = 0;
// #ifdef FEATURE_MBEDTLS_ENABLE
// char mqttHb2Hex(unsigned char hb)
// {
//     hb = hb&0xF;
//     return (char)(hb<10 ? '0'+hb : hb-10+'a');
// }

// /*
//  * output = SHA-1( input buffer )
//  */
// void mqttAliHmacSha1(const unsigned char *input, int ilen, unsigned char *output,const unsigned char *key, int keylen)
// {
//     int i;
//     mbedtls_sha1_context ctx;
//     unsigned char k_ipad[ALI_SHA1_KEY_IOPAD_SIZE] = {0};
//     unsigned char k_opad[ALI_SHA1_KEY_IOPAD_SIZE] = {0};
//     unsigned char tempbuf[ALI_SHA1_DIGEST_SIZE];

//     memset(k_ipad, 0x36, ALI_SHA1_KEY_IOPAD_SIZE);
//     memset(k_opad, 0x5C, ALI_SHA1_KEY_IOPAD_SIZE);

//     for(i=0; i<keylen; i++)
//     {
//         if(i>=ALI_SHA1_KEY_IOPAD_SIZE)
//         {
//             break;
//         }
//         k_ipad[i] ^=key[i];
//         k_opad[i] ^=key[i];
//     }
//     mbedtls_sha1_init(&ctx);

//     mbedtls_sha1_starts(&ctx);
//     mbedtls_sha1_update(&ctx, k_ipad, ALI_SHA1_KEY_IOPAD_SIZE);
//     mbedtls_sha1_update(&ctx, input, ilen);
//     mbedtls_sha1_finish(&ctx, tempbuf);

//     mbedtls_sha1_starts(&ctx);
//     mbedtls_sha1_update(&ctx, k_opad, ALI_SHA1_KEY_IOPAD_SIZE);
//     mbedtls_sha1_update(&ctx, tempbuf, ALI_SHA1_DIGEST_SIZE);
//     mbedtls_sha1_finish(&ctx, tempbuf);

//     for(i=0; i<ALI_SHA1_DIGEST_SIZE; ++i)
//     {
//         output[i*2] = mqttHb2Hex(tempbuf[i]>>4);
//         output[i*2+1] = mqttHb2Hex(tempbuf[i]);
//     }
//     mbedtls_sha1_free(&ctx);
// }
// /*
//  * output = SHA-256( input buffer )
//  */
// void mqttAliHmacSha256(const unsigned char *input, int ilen, unsigned char *output,const unsigned char *key, int keylen)
// {
//     int i;
//     mbedtls_sha256_context ctx;
//     unsigned char k_ipad[ALI_SHA256_KEY_IOPAD_SIZE] = {0};
//     unsigned char k_opad[ALI_SHA256_KEY_IOPAD_SIZE] = {0};

//     memset(k_ipad, 0x36, 64);
//     memset(k_opad, 0x5C, 64);

//     if ((NULL == input) || (NULL == key) || (NULL == output)) {
//         return;
//     }

//     if (keylen > ALI_SHA256_KEY_IOPAD_SIZE) {
//         return;
//     }

//     for(i=0; i<keylen; i++)
//     {
//         if(i>=ALI_SHA256_KEY_IOPAD_SIZE)
//         {
//             break;
//         }
//         k_ipad[i] ^=key[i];
//         k_opad[i] ^=key[i];
//     }
//     mbedtls_sha256_init(&ctx);

//     mbedtls_sha256_starts(&ctx, 0);
//     mbedtls_sha256_update(&ctx, k_ipad, ALI_SHA256_KEY_IOPAD_SIZE);
//     mbedtls_sha256_update(&ctx, input, ilen);
//     mbedtls_sha256_finish(&ctx, output);

//     mbedtls_sha256_starts(&ctx, 0);
//     mbedtls_sha256_update(&ctx, k_opad, ALI_SHA256_KEY_IOPAD_SIZE);
//     mbedtls_sha256_update(&ctx, output, ALI_SHA256_DIGEST_SIZE);
//     mbedtls_sha256_finish(&ctx, output);

//     mbedtls_sha256_free(&ctx);
// }
// /*
//  * output = MD-5( input buffer )
//  */
// void mqttAliHmacMd5(const unsigned char *input, int ilen, unsigned char *output,const unsigned char *key, int keylen)
// {
//     int i;
//     mbedtls_md5_context ctx;
//     unsigned char k_ipad[ALI_MD5_KEY_IOPAD_SIZE] = {0};
//     unsigned char k_opad[ALI_MD5_KEY_IOPAD_SIZE] = {0};
//     unsigned char tempbuf[ALI_MD5_DIGEST_SIZE];

//     memset(k_ipad, 0x36, ALI_MD5_KEY_IOPAD_SIZE);
//     memset(k_opad, 0x5C, ALI_MD5_KEY_IOPAD_SIZE);

//     for(i=0; i<keylen; i++)
//     {
//         if(i>=ALI_MD5_KEY_IOPAD_SIZE)
//         {
//             break;
//         }
//         k_ipad[i] ^=key[i];
//         k_opad[i] ^=key[i];
//     }
//     mbedtls_md5_init(&ctx);

//     mbedtls_md5_starts(&ctx);
//     mbedtls_md5_update(&ctx, k_ipad, ALI_MD5_KEY_IOPAD_SIZE);
//     mbedtls_md5_update(&ctx, input, ilen);
//     mbedtls_md5_finish(&ctx, tempbuf);

//     mbedtls_md5_starts(&ctx);
//     mbedtls_md5_update(&ctx, k_opad, ALI_MD5_KEY_IOPAD_SIZE);
//     mbedtls_md5_update(&ctx, tempbuf, ALI_MD5_DIGEST_SIZE);
//     mbedtls_md5_finish(&ctx, tempbuf);

//     for(i=0; i<ALI_MD5_DIGEST_SIZE; ++i)
//     {
//         output[i*2] = mqttHb2Hex(tempbuf[i]>>4);
//         output[i*2+1] = mqttHb2Hex(tempbuf[i]);
//     }
//     mbedtls_md5_free(&ctx);
// }
// #endif

void mqttDefMessageArrived(MessageData* data)
{
    char *bufTemp = NULL;
    bufTemp = malloc(data->message->payloadlen+1);
    memset(bufTemp, 0, data->message->payloadlen+1);
    memcpy(bufTemp, data->message->payload, data->message->payloadlen);
    free(bufTemp);
}

static void NewMessageData(MessageData* md, MQTTString* aTopicName, MQTTMessage* aMessage) {
    md->topicName = aTopicName;
    md->message = aMessage;
}


static int getNextPacketId(MQTTClient *c) {
    return c->next_packetid = (c->next_packetid == MAX_PACKET_ID) ? 1 : c->next_packetid + 1;
}

static int sendPacket(MQTTClient* c, int length, Timer* timer)
{
    int rc = FAILURE,
        sent = 0;

    while (sent < length && !TimerIsExpired(timer))
    {
        #ifdef MQTT_RAI_OPTIMIZE
        rc = c->ipstack->mqttwrite(c->ipstack, &c->buf[sent], length, TimerLeftMS(timer), 0, false);
        #else
        rc = c->ipstack->mqttwrite(c->ipstack, &c->buf[sent], length, TimerLeftMS(timer));
        #endif
        if (rc < 0)  // there was an error writing the data
            break;
        sent += rc;
    }
    if (sent == length)
    {
        TimerCountdown(&c->last_sent, c->keepAliveInterval); // record the fact that we have successfully sent the packet
        rc = SUCCESS;
    }
    else
        rc = FAILURE;
    return rc;
}

void MQTTClientInit(MQTTClient* c, Network* network, unsigned int command_timeout_ms,
        unsigned char* sendbuf, size_t sendbuf_size, unsigned char* readbuf, size_t readbuf_size)
{
    int i;
    c->ipstack = network;

    for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
        c->messageHandlers[i].topicFilter = 0;
    c->command_timeout_ms = command_timeout_ms;
    c->buf = sendbuf;
    c->buf_size = sendbuf_size;
    c->readbuf = readbuf;
    c->readbuf_size = readbuf_size;
    c->isconnected = 0;
    c->cleansession = 0;
    c->ping_outstanding = 0;
    c->defaultMessageHandler = mqttDefMessageArrived;
      c->next_packetid = 1;
    TimerInit(&c->last_sent);
    TimerInit(&c->last_received);
#if defined(MQTT_TASK)
      MutexInit(&c->mutex);
#endif
}

static int decodePacket(MQTTClient* c, int* value, int timeout)
{
    unsigned char i;
    int multiplier = 1;
    int len = 0;
    const int MAX_NO_OF_REMAINING_LENGTH_BYTES = 4;

    *value = 0;
    do
    {
        int rc = MQTTPACKET_READ_ERROR;

        if (++len > MAX_NO_OF_REMAINING_LENGTH_BYTES)
        {
            rc = MQTTPACKET_READ_ERROR; /* bad data */
            goto exit;
        }
        rc = c->ipstack->mqttread(c->ipstack, &i, 1, timeout);
        if (rc != 1)
            goto exit;
        *value += (i & 127) * multiplier;
        multiplier *= 128;
    } while ((i & 128) != 0);
exit:
    return len;
}

static int readPacket(MQTTClient* c, Timer* timer)
{
    MQTTHeader header = {0};
    int len = 0;
    int rem_len = 0;

    /* 1. read the header byte.  This has the packet type in it */
    int rc = c->ipstack->mqttread(c->ipstack, c->readbuf, 1, TimerLeftMS(timer));
    if (rc != 1)
        goto exit;

    len = 1;
    /* 2. read the remaining length.  This is variable in itself */
    decodePacket(c, &rem_len, TimerLeftMS(timer));
    len += MQTTPacket_encode(c->readbuf + 1, rem_len); /* put the original remaining length back into the buffer */

    if (rem_len > (c->readbuf_size - len))
    {
        rc = BUFFER_OVERFLOW;
        goto exit;
    }

    /* 3. read the rest of the buffer using a callback to supply the rest of the data */
    if (rem_len > 0 && (c->ipstack->mqttread(c->ipstack, c->readbuf + len, rem_len, TimerLeftMS(timer)) != rem_len)) {
        rc = 0;
        goto exit;
    }

    header.byte = c->readbuf[0];
    rc = header.bits.type;
    if (c->keepAliveInterval > 0)
        TimerCountdown(&c->last_received, c->keepAliveInterval); // record the fact that we have successfully received a packet
exit:
    return rc;
}

// assume topic filter and name is in correct format
// # can only be at end
// + and # can only be next to separator
static char isTopicMatched(char* topicFilter, MQTTString* topicName)
{
    char* curf = topicFilter;
    char* curn = topicName->lenstring.data;
    char* curn_end = curn + topicName->lenstring.len;

    while (*curf && curn < curn_end)
    {
        if (*curn == '/' && *curf != '/')
            break;
        if (*curf != '+' && *curf != '#' && *curf != *curn)
            break;
        if (*curf == '+')
        {   // skip until we meet the next separator, or end of string
            char* nextpos = curn + 1;
            while (nextpos < curn_end && *nextpos != '/')
                nextpos = ++curn + 1;
        }
        else if (*curf == '#')
            curn = curn_end - 1;    // skip until end of string
        curf++;
        curn++;
    };

    return (curn == curn_end) && (*curf == '\0');
}

int deliverMessage(MQTTClient* c, MQTTString* topicName, MQTTMessage* message)
{
    int i;
    int rc = FAILURE;

    // we have to find the right message handler - indexed by topic
    for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
    {
        if (c->messageHandlers[i].topicFilter != 0 && (MQTTPacket_equals(topicName, (char*)c->messageHandlers[i].topicFilter) ||
                isTopicMatched((char*)c->messageHandlers[i].topicFilter, topicName)))
        {
            if (c->messageHandlers[i].fp != NULL)
            {
                MessageData md;
                NewMessageData(&md, topicName, message);
                c->messageHandlers[i].fp(&md);
                rc = SUCCESS;
            }
        }
    }

    if (rc == FAILURE && c->defaultMessageHandler != NULL)
    {
        MessageData md;
        NewMessageData(&md, topicName, message);
        c->defaultMessageHandler(&md);
        rc = SUCCESS;
    }

    return rc;
}

// int keepalive(MQTTClient* c)
// {
//     int rc = SUCCESS;
//     if (c->keepAliveInterval == 0)
//         goto exit;
//     if (TimerIsExpired(&c->last_sent) || TimerIsExpired(&c->last_received))
//     {
//         if (c->ping_outstanding)
//             rc = FAILURE; /* PINGRESP not received in keepalive interval */
//         else
//         {
//             Timer timer;
//             TimerInit(&timer);
//             TimerCountdownMS(&timer, 1000);
//             int len = MQTTSerialize_pingreq(c->buf, c->buf_size);
//             if (len > 0 && (rc = sendPacket(c, len, &timer)) == SUCCESS) // send the ping packet
//             {
//                 TimerCountdownMS(&c->last_received, 3000);      // ADDED NEW
//                 c->ping_outstanding = 1;
//             }
//         }
//     }
// exit:
//     return rc;
// }

int keepalive(MQTTClient* c)
{
    int rc = SUCCESS;

    if (c->keepAliveInterval == 0)
    {
        goto exit;
    }

    if (TimerIsExpired(&c->last_sent) || TimerIsExpired(&c->last_received))
    {
        if (c->ping_outstanding)
        {
            //mqtt_keepalive_retry_count++;
            rc = FAILURE; /* PINGRESP not received in keepalive interval */
        }
        else
        {
            Timer timer;
            TimerInit(&timer);
            TimerCountdownMS(&timer, 1000);
#if MQTT_TLS_ENABLE == 1
            memset(c->buf, 0, c->buf_size);
            memset(c->readbuf, 0, c->readbuf_size);
#endif	    
            int len = MQTTSerialize_pingreq(c->buf, c->buf_size);

            if (len > 0 && (rc = sendPacket(c, len, &timer)) == SUCCESS) // send the ping packet
                c->ping_outstanding = 1;
        }
    }

exit:
    return rc;
}

int keepaliveRetry(MQTTClient* c)
{
    int rc = SUCCESS;

    if (c->keepAliveInterval == 0)
    {
        goto exit;
    }

    if (TimerIsExpired(&c->last_sent) || TimerIsExpired(&c->last_received))
    {
        {
            Timer timer;
            TimerInit(&timer);
            TimerCountdownMS(&timer, 1000);

#if MQTT_TLS_ENABLE == 1
            memset(c->buf, 0, c->buf_size);
            memset(c->readbuf, 0, c->readbuf_size);
#endif
            int len = MQTTSerialize_pingreq(c->buf, c->buf_size);

            if (len > 0 && (rc = sendPacket(c, len, &timer)) == SUCCESS) // send the ping packet
                c->ping_outstanding = 1;
        }
    }

exit:
    return rc;
}

void MQTTCleanSession(MQTTClient* c)
{
    int i = 0;

    for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
        c->messageHandlers[i].topicFilter = NULL;
}

void MQTTCloseSession(MQTTClient* c)
{
    c->ping_outstanding = 0;
    c->isconnected = 0;
    if (c->cleansession)
        MQTTCleanSession(c);
}

int cycle(MQTTClient* c, Timer* timer)
{
    int len = 0,
    rc = SUCCESS;

    int packet_type = readPacket(c, timer);     /* read the socket, see what work is due */

    switch (packet_type)
    {
        default:
            /* no more data to read, unrecoverable. Or read packet fails due to unexpected network error */
            rc = packet_type;
            goto exit;
#if MQTT_TLS_ENABLE == 1
	case 100: //to handle Mbedtls EOF
	    /* no more data to read, unrecoverable. Or read packet fails due to unexpected network error */
	    rc = -1;
	    goto exit;
#endif

        case 0: /* timed out reading packet */
            break;
        case CONNACK:
            break;
        case PUBACK:
			break;
        case SUBACK:
			break;
        case UNSUBACK:
            break;
        case PUBLISH:
        {
            MQTTString topicName;
            MQTTMessage msg;
            int intQoS;
            msg.payloadlen = 0; /* this is a size_t, but deserialize publish sets this as int */
            if (MQTTDeserialize_publish(&msg.dup, &intQoS, &msg.retained, &msg.id, &topicName,
               (unsigned char**)&msg.payload, (int*)&msg.payloadlen, c->readbuf, c->readbuf_size) != 1)
                goto exit;
            msg.qos = (enum QoS)intQoS;
            deliverMessage(c, &topicName, &msg);
            if (msg.qos != QOS0)
            {
                if (msg.qos == QOS1) {
                    len = MQTTSerialize_ack(c->buf, c->buf_size, PUBACK, 0, msg.id);
                }
                else if (msg.qos == QOS2) {
                    len = MQTTSerialize_ack(c->buf, c->buf_size, PUBREC, 0, msg.id);
                }

                if (len <= 0)
                    rc = FAILURE;
                else
                    rc = sendPacket(c, len, timer);
                if (rc == FAILURE)
                    goto exit; // there was a problem
            }
            break;
        }
        case PUBREC:
        case PUBREL:
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->readbuf, c->readbuf_size) != 1)
                rc = FAILURE;
            else if ((len = MQTTSerialize_ack(c->buf, c->buf_size,
                (packet_type == PUBREC) ? PUBREL : PUBCOMP, 0, mypacketid)) <= 0)
                rc = FAILURE;
            else if ((rc = sendPacket(c, len, timer)) != SUCCESS) // send the PUBREL packet
                rc = FAILURE; // there was a problem
            if (rc == FAILURE)
                goto exit; // there was a problem
            break;
        }

        case PUBCOMP:
            break;
        case PINGRESP:
            c->ping_outstanding = 0;
            break;
    }

    if (keepalive(c) != SUCCESS) {
        int socket_stat = 0;
        mqttSendMsg mqttMsg;
        //check only keepalive FAILURE status so that previous FAILURE status can be considered as FAULT
        rc = FAILURE;
        socket_stat = sock_get_errno(c->ipstack->my_socket);
        if((socket_stat == MQTT_ERR_ABRT)||(socket_stat == MQTT_ERR_RST)||(socket_stat == MQTT_ERR_CLSD)||(socket_stat == MQTT_ERR_BADE))
        {
            /* send  reconnect msg to send task */
            memset(&mqttMsg, 0, sizeof(mqttMsg));
            mqttMsg.cmdType = MQTT_DEMO_MSG_RECONNECT;

            xQueueSend(mqttSendMsgHandle, &mqttMsg, MQTT_MSG_TIMEOUT);
        }
        else
        {
            if(mqtt_keepalive_retry_count>3)
            {
                mqtt_keepalive_retry_count = 0;
                /* send  reconnect msg to send task */
                memset(&mqttMsg, 0, sizeof(mqttMsg));
                mqttMsg.cmdType = MQTT_DEMO_MSG_RECONNECT;

                xQueueSend(mqttSendMsgHandle, &mqttMsg, MQTT_MSG_TIMEOUT);
            }
            else
            {
                keepaliveRetry(c);
            }
        }
    }

exit:
    if (rc == SUCCESS)
        rc = packet_type;
#if MQTT_TLS_ENABLE == 1
    else if (c->isconnected)
        ;//MQTTCloseSession(c);
#else
    else if (c->isconnected){
        MQTTCloseSession(c);
    	}
#endif
    return rc;
}

int MQTTYield(MQTTClient* c, int timeout_ms)
{
    int rc = SUCCESS;
    Timer timer;

    TimerInit(&timer);
    TimerCountdownMS(&timer, timeout_ms);

      do
    {
        if (cycle(c, &timer) < 0)
        {
            rc = FAILURE;
            break;
        }
    } while (!TimerIsExpired(&timer));

    return rc;
}

// int MQTTIsConnected(MQTTClient* client)
// {
//   return client->isconnected;
// }

void MQTTRun(void* parm)
{
    Timer timer;
#if MQTT_TLS_ENABLE == 1
    MQTTClient* c = (MQTTClient*)parm;
#else
    MQTTClient* c = (MQTTClient*)parm;
#endif
    if(mqttSendMsgHandle == NULL)
    {
        mqttSendMsgHandle = xQueueCreate(16, sizeof(mqttSendMsg));
    }

    if(appMqttMsgHandle == NULL)
    {
        appMqttMsgHandle = xQueueCreate(16, sizeof(mqttDataMsg));
    }

    if(mqttMutex1.sem == NULL)
    {
        MutexInit(&mqttMutex1);
    }

    TimerInit(&timer);

    while (1)
    {
#if defined(MQTT_TASK)
        MutexLock(&c->mutex);
#endif
        MutexLock(&mqttMutex1);

        TimerCountdownMS(&timer, 1500); /* Don't wait too long if no traffic is incoming */
        cycle(c, &timer);
        MutexUnlock(&mqttMutex1);

#if defined(MQTT_TASK)
        MutexUnlock(&c->mutex);
#endif
        osDelay(200);
    }
}

#if defined(MQTT_TASK)
int MQTTStartTask(MQTTClient* client)
{
    return ThreadStart(&client->thread, &MQTTRun, client);
}
#endif

int MQTTStartRECVTask(MQTTClient* c)
{
    osThreadAttr_t task_attr;

    memset(&task_attr, 0, sizeof(task_attr));
    task_attr.name = "mqttRecv";
    task_attr.stack_size = MQTT_DEMO_TASK_STACK_SIZE;
    task_attr.priority = osPriorityBelowNormal7;

    mqttRecvTaskHandle = osThreadNew(MQTTRun, (void *)c, &task_attr);
    if(mqttRecvTaskHandle == NULL)
    {
        return FAILURE;
    }

    return SUCCESS;
}

int waitfor(MQTTClient* c, int packet_type, Timer* timer)
{
    int rc = FAILURE;

    do
    {
        if (TimerIsExpired(timer))
            break; // we timed out
        rc = cycle(c, timer);
    }
    while (rc != packet_type && rc >= 0);

    return rc;
}

int MQTTConnectWithResults(MQTTClient* c, MQTTPacket_connectData* options, MQTTConnackData* data)
{
    Timer connect_timer;
    int rc = FAILURE;
    MQTTPacket_connectData default_options = MQTTPacket_connectData_initializer;
    int len = 0;

#if defined(MQTT_TASK)
      MutexLock(&c->mutex);
#endif
      if (c->isconnected) /* don't send connect packet again if we are already connected */
          goto exit;

    TimerInit(&connect_timer);
    TimerCountdownMS(&connect_timer, c->command_timeout_ms);

    if (options == 0)
        options = &default_options; /* set default options if none were supplied */

    c->keepAliveInterval = options->keepAliveInterval;
    c->cleansession = options->cleansession;
    TimerCountdown(&c->last_received, c->keepAliveInterval);
    if ((len = MQTTSerialize_connect(c->buf, c->buf_size, options)) <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &connect_timer)) != SUCCESS)  // send the connect packet
        goto exit; // there was a problem

    // this will be a blocking call, wait for the connack
    if (waitfor(c, CONNACK, &connect_timer) == CONNACK)
    {
        data->rc = 0;
        data->sessionPresent = 0;
        if (MQTTDeserialize_connack(&data->sessionPresent, &data->rc, c->readbuf, c->readbuf_size) == 1)
            rc = data->rc;
        else
            rc = FAILURE;
    }
    else
        rc = FAILURE;

exit:
    if (rc == SUCCESS)
    {
        c->isconnected = 1;
        c->ping_outstanding = 0;
    }

#if defined(MQTT_TASK)
      MutexUnlock(&c->mutex);
#endif

    return rc;
}

int MQTTReConnect(MQTTClient* client, MQTTPacket_connectData* connectData)
{
    int ret = FAILURE;

    client->ipstack->disconnect(client->ipstack);

    if ((NetworkSetConnTimeout(client->ipstack, MQTT_SEND_TIMEOUT, MQTT_RECV_TIMEOUT)) != 0)
    {
        return ret;
    }
    else
    {
        client->isconnected = 0;
        if((NetworkConnect(client->ipstack, MQTT_SERVER_URI, MQTT_SERVER_PORT)) < 0)
        {
            return ret;
        }
        else
        {

            if ((MQTTConnect(client, connectData)) != 0)
            {
                return ret;
            }
            else
            {
                ret = SUCCESS;
            }
        }
    }
    return ret;
}

int MQTTConnect(MQTTClient* c, MQTTPacket_connectData* options)
{
    MQTTConnackData data;
    return MQTTConnectWithResults(c, options, &data);
}

int MQTTSetMessageHandler(MQTTClient* c, const char* topicFilter, messageHandler messageHandler)
{
    int rc = FAILURE;
    int i = -1;

    /* first check for an existing matching slot */
    for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
    {
        if (c->messageHandlers[i].topicFilter != NULL && strcmp(c->messageHandlers[i].topicFilter, topicFilter) == 0)
        {
            if (messageHandler == NULL) /* remove existing */
            {
                c->messageHandlers[i].topicFilter = NULL;
                c->messageHandlers[i].fp = NULL;
            }
            rc = SUCCESS; /* return i when adding new subscription */
            break;
        }
    }
    /* if no existing, look for empty slot (unless we are removing) */
    if (messageHandler != NULL) {
        if (rc == FAILURE)
        {
            for (i = 0; i < MAX_MESSAGE_HANDLERS; ++i)
            {
                if (c->messageHandlers[i].topicFilter == NULL)
                {
                    rc = SUCCESS;
                    break;
                }
            }
        }
        if (i < MAX_MESSAGE_HANDLERS)
        {
            c->messageHandlers[i].topicFilter = topicFilter;
            c->messageHandlers[i].fp = messageHandler;
        }
    }
    return rc;
}

int MQTTSubscribeWithResults(MQTTClient* c, const char* topicFilter, enum QoS qos,
       messageHandler messageHandler, MQTTSubackData* data)
{
    int rc = FAILURE;
    Timer timer;
    int len = 0;
    int mqttQos = (int)qos;
    MQTTString topic = MQTTString_initializer;
    topic.cstring = (char *)topicFilter;

#if defined(MQTT_TASK)
      MutexLock(&c->mutex);
#endif
      if (!c->isconnected)
            goto exit;

    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);

    len = MQTTSerialize_subscribe(c->buf, c->buf_size, 0, getNextPacketId(c), 1, &topic, (int*)&mqttQos);
    if (len <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &timer)) != SUCCESS) // send the subscribe packet
        goto exit;             // there was a problem

    if (waitfor(c, SUBACK, &timer) == SUBACK)      // wait for suback
    {
        int count = 0;
        unsigned short mypacketid;
        data->grantedQoS = QOS0;
        mqttQos = (int)data->grantedQoS;
        if (MQTTDeserialize_suback(&mypacketid, 1, &count, (int*)&mqttQos, c->readbuf, c->readbuf_size) == 1)
        {
            if (data->grantedQoS != 0x80)
                rc = MQTTSetMessageHandler(c, topicFilter, messageHandler);
        }
    }
    else
        rc = FAILURE;

exit:
    if (rc == FAILURE)
#if MQTT_TLS_ENABLE == 1
        ;//MQTTCloseSession(c);
#else
    	{
    	//HT_TRACE(UNILOG_MQTT, MQTTSubscribeWithResults_7, P_INFO, 0, "Call MQTTClose");
        MQTTCloseSession(c);
    	}
#endif
#if defined(MQTT_TASK)
      MutexUnlock(&c->mutex);
#endif
    return rc;
}

int MQTTSubscribe(MQTTClient* c, const char* topicFilter, enum QoS qos, messageHandler messageHandler)
{
    MQTTSubackData data;
    return MQTTSubscribeWithResults(c, topicFilter, qos, messageHandler, &data);
}

int MQTTUnsubscribe(MQTTClient* c, const char* topicFilter)
{
    int rc = FAILURE;
    Timer timer;
    MQTTString topic = MQTTString_initializer;
    topic.cstring = (char *)topicFilter;
    int len = 0;

#if defined(MQTT_TASK)
      MutexLock(&c->mutex);
#endif
      if (!c->isconnected)
          goto exit;

    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);

    if ((len = MQTTSerialize_unsubscribe(c->buf, c->buf_size, 0, getNextPacketId(c), 1, &topic)) <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &timer)) != SUCCESS) // send the subscribe packet
        goto exit; // there was a problem

    if (waitfor(c, UNSUBACK, &timer) == UNSUBACK)
    {
        unsigned short mypacketid;  // should be the same as the packetid above
        if (MQTTDeserialize_unsuback(&mypacketid, c->readbuf, c->readbuf_size) == 1)
        {
            /* remove the subscription message handler associated with this topic, if there is one */
            MQTTSetMessageHandler(c, topicFilter, NULL);
        }
    }
    else
        rc = FAILURE;

exit:
    if (rc == FAILURE)
#if MQTT_TLS_ENABLE == 1
        ;//MQTTCloseSession(c);
#else
        MQTTCloseSession(c);
#endif
#if defined(MQTT_TASK)
      MutexUnlock(&c->mutex);
#endif
    return rc;
}

int MQTTPublish(MQTTClient* c, const char* topicName, MQTTMessage* message)
{
    int rc = FAILURE;
    Timer timer;
    MQTTString topic = MQTTString_initializer;
    topic.cstring = (char *)topicName;
    int len = 0;

#if defined(MQTT_TASK)
      MutexLock(&c->mutex);
#endif
      if (!c->isconnected)
            goto exit;

    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);

    if (message->qos == QOS1 || message->qos == QOS2)
        message->id = getNextPacketId(c);

    len = MQTTSerialize_publish(c->buf, c->buf_size, 0, message->qos, message->retained, message->id,
              topic, (unsigned char*)message->payload, message->payloadlen);
    if (len <= 0)
        goto exit;
    if ((rc = sendPacket(c, len, &timer)) != SUCCESS) // send the subscribe packet
        goto exit; // there was a problem

    if (message->qos == QOS1)
    {
        if (waitfor(c, PUBACK, &timer) == PUBACK)
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->readbuf, c->readbuf_size) != 1)
                rc = FAILURE;
        }
        else
            rc = FAILURE;
    }
    else if (message->qos == QOS2)
    {
        if (waitfor(c, PUBCOMP, &timer) == PUBCOMP)
        {
            unsigned short mypacketid;
            unsigned char dup, type;
            if (MQTTDeserialize_ack(&type, &dup, &mypacketid, c->readbuf, c->readbuf_size) != 1)
                rc = FAILURE;
        }
        else
            rc = FAILURE;
    }

exit:
    if (rc == FAILURE)
#if MQTT_TLS_ENABLE == 1
        ;//MQTTCloseSession(c);
#else
    {
   		HT_TRACE(UNILOG_MQTT, MQTTPublish_14, P_INFO, 0, "Call MQTTClose");
        MQTTCloseSession(c);
    }
#endif
#if defined(MQTT_TASK)
      MutexUnlock(&c->mutex);
#endif
    return rc;
}

int MQTTDisconnect(MQTTClient* c)
{
    int rc = FAILURE;
    Timer timer;     // we might wait for incomplete incoming publishes to complete
    int len = 0;

#if defined(MQTT_TASK)
    MutexLock(&c->mutex);
#endif
    TimerInit(&timer);
    TimerCountdownMS(&timer, c->command_timeout_ms);

      len = MQTTSerialize_disconnect(c->buf, c->buf_size);
    if (len > 0)
        rc = sendPacket(c, len, &timer);            // send the disconnect packet
    MQTTCloseSession(c);

#if defined(MQTT_TASK)
      MutexUnlock(&c->mutex);
#endif
    return rc;
}

int MQTTInit(MQTTClient* c, Network* n, unsigned char* sendBuf, unsigned char* readBuf)
{
    NetworkInit(n);
    MQTTClientInit(c, n, 40000, (unsigned char *)sendBuf, 1000, (unsigned char *)readBuf, 1000);

    return 0;
}

int MQTTCreate(MQTTClient* c, Network* n, char* clientID, char* username, char* password, char *serverAddr, int port, MQTTPacket_connectData* connData)
{
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    int clientLen = 0;
    int usernameLen = 0;
    int passwordLen = 0;

    if(connData != NULL)
    {
        memcpy(&connectData, connData, sizeof(MQTTPacket_connectData));
    }
    else
    {
        connectData.MQTTVersion = 4;
        connectData.keepAliveInterval = 120;
    }

    if(clientID != NULL)
    {
        clientLen = strlen(clientID);
        connectData.clientID.cstring = malloc(clientLen+1);
        memset(connectData.clientID.cstring, 0, (clientLen+1));
        memcpy(connectData.clientID.cstring, clientID, clientLen);
    }

    if(username != NULL)
    {
        usernameLen = strlen(username);
        connectData.username.cstring = malloc(usernameLen+1);;
        memset(connectData.username.cstring, 0, (usernameLen+1));
        memcpy(connectData.username.cstring, username, usernameLen);
    }

    if(password != NULL)
    {
        passwordLen = strlen(password);
        connectData.password.cstring = malloc(passwordLen+1);
        memset(connectData.password.cstring, 0, (passwordLen+1));
        memcpy(connectData.password.cstring, password, passwordLen);
    }

    if((NetworkSetConnTimeout(n, 5000, 5000)) != 0)
    {
        c->keepAliveInterval = connectData.keepAliveInterval;
        c->ping_outstanding = 1;
        return 1;
    }
    else
    {
        if ((NetworkConnect(n, serverAddr, port)) != 0)
        {
            c->keepAliveInterval = connectData.keepAliveInterval;
            c->ping_outstanding = 1;
            return 1;
        }
        else
        {
            if ((MQTTConnect(c, &connectData)) != 0)
            {
                c->ping_outstanding = 1;
                return 1;
            }
            else
            {
                #if defined(MQTT_TASK)
                    if ((MQTTStartTask(c)) != pdPASS)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                #endif
            }
        }
    }
    return 1;
}
