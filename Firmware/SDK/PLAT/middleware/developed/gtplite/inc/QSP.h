#ifndef QSP_H_
#define QSP_H_
/* File Inclusions */
#include "mbedtls/pk.h"

/* MAcro Definitions */
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif

#define QSP_MAX_KEY_LEN				32 /* 256 bits */

#define QSP_KEYCRYPT_RSA_OEAP_3074		1
#define QSP_KEYCRYPT_RSA_OEAP_2048		2

#define QSP_PLCRYPT_AES256_GCM		1

/* Data Structures */
typedef struct QspSession_Tag {
	mbedtls_pk_context	rsaPubKey; /* Server Public key used to encrypt session Key */
	uint8_t 			sessionAesKey[QSP_MAX_KEY_LEN]; /* Session Key */
	uint8_t			messageID; /* message ID of the session */
	uint8_t			kEncMeth;
} QspSession_t;

typedef struct QspSessionKeyInfo_Tag {
	uint8_t	payloadEncryptMethod; /* encyption method of payload encryption*/
	uint8_t	keyEncryptMethod; /* encryption used to encrypt session key */
	char *	preKey; /* key used to encrypt session key */
} QspSessInfo_t;

typedef enum QspRet_e
{
	QSP_OK = 0,
	QSP_ERROR_PARAM,
	QSP_ERROR_RESP,
	QSP_ERROR_AUTH,
	QSP_ERROR_CRYPT,
	QSP_ERROR_FORMAT,
	QSP_ERROR_INVALIDMID,
	QSP_ERROR_UNKNOWN
} QspRet;

/* Interface Prototypes */
QspRet QSP_Session_Init(OUT QspSession_t **sessP, IN QspSessInfo_t *sessInfo);

QspRet QSP_Session_Encode(IN QspSession_t *sessP, INOUT GtpConnDataPdu *buff);

QspRet	QSP_Session_Decode(IN QspSession_t *sessP, INOUT GtpConnDataPdu *buff);

void QSP_Session_Deinit(QspSession_t **sessP);

#endif //QSP_H_
