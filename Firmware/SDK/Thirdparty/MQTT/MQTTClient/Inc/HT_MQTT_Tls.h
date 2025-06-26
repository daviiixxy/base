/*

  _    _ _______   __  __ _____ _____ _____   ____  _   _
 | |  | |__   __| |  \/  |_   _/ ____|  __ \ / __ \| \ | |
 | |__| |  | |    | \  / | | || |    | |__) | |  | |  \| |
 |  __  |  | |    | |\/| | | || |    |  _  /| |  | | . ` |
 | |  | |  | |    | |  | |_| || |____| | \ \| |__| | |\  |
 |_|  |_|  |_|    |_|  |_|_____\_____|_|  \_\\____/|_| \_|
 =================== Advanced R&D ========================

 Copyright (c) 2023 HT Micron Semicondutores S.A.
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

*/

/*!
 * \file HT_MQTT_Tls.h
 * \brief TLS implementation for MQTT. 
  * \author HT Micron Advanced R&D,
 *         Hêndrick Bataglin Gonçalves, Christian Roberto Lehmen,  Matheus da Silva Zorzeto, Felipe Kalinski Ferreira,
 *         Leandro Borges, Mauricio Carlotto Ribeiro, Henrique Kuhn, Cleber Haack, Eduardo Mendel
 * 
 * \link https://github.com/htmicron
 * \version 0.1
 * \date December 4, 2023
 */

#ifndef __HT_MQTT_H__
#define __HT_MQTT_H__

#include "MQTTClient.h"
#include "MQTTConnect.h"
#include "MQTTFreeRTOS.h"
#include "MQTTPacket.h"
#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/certs.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

#define MAX_TIMEOUT (2*60)  //2 min

#define HT_MQTT_TX_BUF_LEN 1024
#define HT_MQTT_RX_BUF_LEN 1024

typedef struct MqttClientSslTag {
    mbedtls_ssl_context sslContext;
    mbedtls_net_context netContext;
    mbedtls_ssl_config sslConfig;
    mbedtls_entropy_context entropyContext;
    mbedtls_ctr_drbg_context ctrDrbgContext;
    mbedtls_x509_crt_profile crtProfile;
    mbedtls_x509_crt caCert;
    mbedtls_x509_crt clientCert;
    mbedtls_pk_context pkContext;
} MqttClientSsl;

typedef struct MqttClientContextTag {
    int32_t socket;
    int32_t timeout_s;
    int32_t timeout_r;
    bool isMqtt;
    int32_t method;
    uint16_t port;
    char *basicAuthUser;
    char *basicAuthPassword;
    char **customHeaders;
    int32_t headerNum;
    char *custHeader;
    int32_t MqttResponseCode;
    int32_t maxredirections;
    char *location;
    MqttClientSsl *ssl;
    const char *caCert;
    const char *clientCert;
    const char *clientPk;
    int32_t caCertLen;
    int32_t clientCertLen;
    int32_t clientPkLen;
    char *host;
    uint32_t timeout_ms;
} MqttClientContext;

int32_t HT_MQTT_TLSConnect(MqttClientContext *context, Network *network);

#endif /*__HT_MQTT_H__*/

/************************ HT Micron Semicondutores S.A *****END OF FILE****/
