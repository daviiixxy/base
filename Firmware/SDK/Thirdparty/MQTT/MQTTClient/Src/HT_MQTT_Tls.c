
#include "HT_MQTT_Tls.h"

MqttClientSsl *ssl;

static int HT_MQTT_MyCertVerify(void * data, mbedtls_x509_crt * crt, int depth, uint32_t * flags) {
	char buf[4096];

	((void) data);
	mbedtls_x509_crt_info(buf, sizeof(buf) - 1, "", crt);
	return (0);
}

static int HT_MQTT_TLSDisconnect(Network * network) {
	int ret = 0;

	do {
		ret = mbedtls_ssl_close_notify(&(ssl->sslContext));
	} while(ret == MBEDTLS_ERR_SSL_WANT_WRITE);

	mbedtls_net_free(&(ssl->netContext));

	return 0;
}

static int HT_MQTT_TLSWrite(Network * network, unsigned char *buffer, int len, int timeout_ms) {
	int ret = 0;
	int written;
	int frags;

	for (written = 0, frags = 0; written < len; written += ret, frags++) {
		while ((ret = mbedtls_ssl_write(&(ssl->sslContext), buffer + written, len - written)) <= 0) {
			if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
				return ret;
			}
		}
	}

	return written;
}

static int HT_MQTT_TLSRead(Network * network, unsigned char *buffer, int len, int timeout_ms) {
	int rxLen = 0;
	int ret_val = -1;
	bool isErrorFlag = false;
	bool isCompleteFlag = false;

	if (timeout_ms != 0)
		mbedtls_ssl_conf_read_timeout(&(ssl->sslConfig), timeout_ms);

	do {
		ret_val = mbedtls_ssl_read(&(ssl->sslContext), buffer, len);

		if (ret_val > 0) {
			rxLen += ret_val;
		}
		else if (ret_val == MBEDTLS_ERR_SSL_TIMEOUT) {
			ret_val = 0;
			return ret_val;
		}
		else if (ret_val == MBEDTLS_ERR_SSL_WANT_READ) {
			isErrorFlag = true;
		}
		else if (ret_val == 0) {
			ret_val = 100; //To Handle Mbedtls EOF case
			return ret_val;
		}

		if (rxLen >= len) {
			isCompleteFlag = true;
		}
	
	} while( (!isErrorFlag) && (!isCompleteFlag) );

	return ret_val;
}

int32_t HT_MQTT_TLSConnect(MqttClientContext *context, Network *network) {
	int32_t ret = 0;
	const char *custom = "SSLs";
    int32_t authmode = MBEDTLS_SSL_VERIFY_NONE;

	context->ssl = malloc(sizeof(MqttClientSsl));
    ssl = context->ssl;

	/*
	 * 0. Initialize the RNG and the session data
	 */
	// Basic mbedtls stack initialization
	mbedtls_net_init(&ssl->netContext);
    mbedtls_ssl_init(&ssl->sslContext);
    mbedtls_ssl_config_init(&ssl->sslConfig);
    mbedtls_x509_crt_init(&ssl->caCert);
    mbedtls_x509_crt_init(&ssl->clientCert);
    mbedtls_pk_init(&ssl->pkContext);
    mbedtls_ctr_drbg_init(&ssl->ctrDrbgContext);
    mbedtls_entropy_init(&ssl->entropyContext);

	if ((ret =
		 mbedtls_ctr_drbg_seed(& (ssl->ctrDrbgContext), mbedtls_entropy_func, &(ssl->entropyContext), (const unsigned char *) custom, strlen(custom))) !=0) {			
		return ret;
	}

	/*
	 * Initialize server ca root 
	 */

	if (context->clientCert != NULL && context->clientPk != NULL) {
		authmode = MBEDTLS_SSL_VERIFY_REQUIRED;
		ret = mbedtls_x509_crt_parse(& (ssl->caCert), (const unsigned char *)context->caCert, context->caCertLen);

		if (ret < 0) {
			return -1;
		}
	} 

	//2. START OF CLIENT CERT INIT AND PARSING - device_ec_cert.pem
    if (context->clientCert != NULL && context->clientPk != NULL) {
        ret = mbedtls_x509_crt_parse(&(ssl->clientCert), (const unsigned char *) context->clientCert, context->clientCertLen);
        if (ret != 0) {
            return -1;
        }

        ret = mbedtls_pk_parse_key(&ssl->pkContext, (const unsigned char *) context->clientPk, context->clientPkLen, NULL, 0);
        if (ret != 0) {
            return -1;
        }
    }

	// 5. Setup the network parameters
	network->mqttread = HT_MQTT_TLSRead;
	network->mqttwrite = HT_MQTT_TLSWrite;
	network->disconnect = HT_MQTT_TLSDisconnect;

	// 4. Start the TLS connection
	ret = NetworkSetConnTimeout(network, 5000, 5000); 	// Add send_timeout , recieve_timeout in TLSConnectParams 
    if(ret != 0) {
        return -1;
    }

	// Step 4.2: Do NetworkConnect // hostname and port
	ret = TLSNetworkConnect(network, context->host, context->port, context->timeout_ms);
    if(ret != 0) {
        return -1;
    }
    ssl->netContext.fd = network->my_socket;

	// step 4.4 Moving to setup SSL structure.
	if ((ret = mbedtls_ssl_config_defaults(&(ssl->sslConfig), 
		MBEDTLS_SSL_IS_CLIENT, 
		MBEDTLS_SSL_TRANSPORT_STREAM, 
		MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
		return ret;
	}

	mbedtls_ssl_conf_max_version(&ssl->sslConfig, MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3);
    mbedtls_ssl_conf_min_version(&ssl->sslConfig, MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3);

	mbedtls_ssl_conf_verify(&ssl->sslConfig, HT_MQTT_MyCertVerify, NULL);
	mbedtls_ssl_conf_authmode(&(ssl->sslConfig), authmode);

#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH)
    if ((ret = mbedtls_ssl_conf_max_frag_len(&(ssl->sslConfig), MBEDTLS_SSL_MAX_FRAG_LEN_1024)) != 0) {
        return -1;
    }
#endif

	// Step 4.5 SSL conf check for CA chain.
#if defined(MBEDTLS_X509_CRT_PARSE_C) 
    
    mbedtls_ssl_conf_cert_profile(&ssl->sslConfig, &ssl->crtProfile);
	mbedtls_ssl_conf_ca_chain(&(ssl->sslConfig), &(ssl->caCert), NULL);

	if(context->clientCert) {
        if ((ret = mbedtls_ssl_conf_own_cert(&(ssl->sslConfig), &(ssl->clientCert), &(ssl->pkContext))) != 0) {
            return -1;
        }
    }

#endif
	
	// Step 4.7 Random number generator	
	mbedtls_ssl_conf_rng(&(ssl->sslConfig), mbedtls_ctr_drbg_random, &(ssl->ctrDrbgContext));	

	//mbedtls_ssl_conf_dbg(&(ssl->conf), sslDebug, NULL);
	if (context->timeout_r > 0) {
		uint32_t recvTimeout;

		recvTimeout = context->timeout_r > MAX_TIMEOUT ? MAX_TIMEOUT * 1000 : context->timeout_r * 1000;
        mbedtls_ssl_conf_read_timeout(&(ssl->sslConfig), recvTimeout);
	}

	if ((ret = mbedtls_ssl_setup(&(ssl->sslContext), &(ssl->sslConfig))) != 0) {
        return -1;
    }

	//	  params->pDestinationURL = hostname;
	mbedtls_ssl_set_hostname(&(ssl->sslContext), context->host);
    mbedtls_ssl_set_bio(&(ssl->sslContext), &(ssl->netContext), mbedtls_net_send, mbedtls_net_recv, mbedtls_net_recv_timeout);
	
	// Step 4.12 TLS HANDSHAKE process on
    while ((ret = mbedtls_ssl_handshake(&(ssl->sslContext))) != 0) {
        if ((ret != MBEDTLS_ERR_SSL_WANT_READ) && (ret != MBEDTLS_ERR_SSL_WANT_WRITE)) {
            return -1;
        }
    }

    /*
     * 4. Verify the server certificate
     */
    ret = mbedtls_ssl_get_verify_result(&(ssl->sslContext));
    if (ret != 0) {
        return -1;
    }

	return ret;
}
