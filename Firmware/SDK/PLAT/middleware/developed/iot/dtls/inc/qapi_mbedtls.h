#ifndef QAPI_MBEDTLS_H_
#define QAPI_MBEDTLS_H_

#include "mbedtls/ssl_ciphersuites.h"
#include "debug_log.h"

//#define DTLS_DEBUG_LEVEL 1


#ifdef IOT_MEM_DEBUG
#define DTLS_MEMCPY(d,dlen,s,slen) {\
	dtls_memcpy_trace(dlen,slen);\
	if((dlen) < (slen)) {\
			EC_ASSERT(0,0,0,0);\
		}\
		else {\
		memcpy((d), (s), (slen));\
		}\
	}
#else
#define DTLS_MEMCPY(d,dl,s,sl) memcpy((d),(s),((dl)<(sl)?(dl):(sl)))
#endif

//fragment length supported
#define SSL_MAX_FRAGM_LEN_512            				1  
#define SSL_MAX_FRAGM_LEN_1024           				2 
#define SSL_MAX_FRAGM_LEN_2048           				3  
#define SSL_MAX_FRAGM_LEN_4096           				4


//ciphersuites list supported
#define SSL_TLS_PSK_WITH_AES_128_CCM_8						0xC0A8
#define SSL_TLS_PSK_WITH_AES_128_CBC_SHA256 				0xAE
#define SSL_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8				0xC0AE
#define SSL_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256			0xC023

//Maximum cipherlist support
#define SUPPORT_MAX_CIPHER_LIST							8

//maximum ca list support
#define SSL_MAX_CA_LIST									8

#define SSL_PSK_MAX_LEN 								32

//error codes
#define DTLS_OK							 0
#define DTLS_FAILURE 					-1
#define DTLS_MEMORY_ERROR 				-2
#define DTLS_INVALID_PARAM 				-3
#define DTLS_BAD_INPUT					-4
#define DTLS_INVALID_STATE -5

typedef void * SSL_Obj_Hdl_t;
typedef const void * SSL_Cert_t; 

typedef const void * qapi_Net_SSL_Cert_t;
typedef const void * qapi_Net_SSL_DICERT_t;
typedef const void * qapi_Net_SSL_CAList_t;
typedef const void * qapi_Net_SSL_PSKTable_t;





typedef int Status_t;

/** Maximum number of characters in a certificate or CA list name. */
#define SSL_MAX_CERT_NAME_LEN (64) 

/** Maximum number of cipher suites that can be configured. */
#define SSL_CIPHERSUITE_LIST_DEPTH 8

/** Invalid handle. */
#define SSL_INVALID_HANDLE (0)

typedef struct /** @cond */__SSL_Verify_Policy_s/** @endcond */ {
    uint8_t domain ;
    /**< TRUE to verify certificate commonName against the peer's domain name. */

    uint8_t time_Validity ;
    /**< TRUE to verify certificate time validity. */

    uint8_t send_Alert ;
    /**< TRUE to immediately send a fatal alert on detection of an untrusted certificate. */

    char match_Name[SSL_MAX_CERT_NAME_LEN];
    /**< Name to match against the common name or altDNSNames of the certificate. See 
         #QAPI_NET_SSL_MAX_CERT_NAME_LEN. */
}  SSL_Verify_Policy_t;

/**
 * Structure to configure an SSL connection. 
 */
typedef  struct /** @cond */__SSL_Config_s/** @endcond */ {
    uint16_t protocol ;
    /**< Protocol to use. See QAPI_NET_SSL_PROTOCOL_*. */

    uint16_t cipher[SSL_CIPHERSUITE_LIST_DEPTH] ;
    /**< Cipher to use. See SSL cipher suites QAPI_NET_TLS* and 
         #QAPI_NET_SSL_CIPHERSUITE_LIST_DEPTH. */

    SSL_Verify_Policy_t verify ;
    /**< Certificate verification policy. */

    uint16_t max_Frag_Len;
    /**< Maximum fragment length in bytes. */

    uint16_t max_Frag_Len_Neg_Disable;
    /**< Whether maximum fragment length negotiation is allowed. See RFC 6066. */

    uint16_t sni_Name_Size;
    /**< Length of the SNI server name. */

    char *sni_Name;
    /**< Server name for SNI. */

	unsigned int flag;
	/*to check it is enabled for the vzw nwteok or not*/

} SSL_Config_t;

typedef enum
{
  SSL_CERTIFICATE_E = 1,
  /**< Certificate type. */

  SSL_CA_LIST_E = 2,
  /**< CA list type. */

  SSL_PSK_TABLE_E = 3,
  /**< PSK key table type. */

  SSL_DI_CERT_E = 4,
  /**< Domain-issued certificate type. */

  SSL_RPK_CERT_E = 5
  /**< Raw Public Key certificate type. */

} SSL_Cert_Type_t;

typedef struct __SSL_CERT_s
{
    uint8_t *cert_Buf;       
    /**< Client certificate buffer. */ 
    uint32_t cert_Size;   
    /**< Client certificate buffer size. */
    uint8_t *key_Buf;        
    /**< Private key buffer. */ 
    uint32_t key_Size;    
    /**< Private key buffer size. */
    uint8_t *pass_Key;       
    /**< Password phrase. */
} ssl_CERT_t; 

typedef struct __SSL_CA_Info_s
{
    uint8_t *ca_Buf;      
    /**< Certificate authority list buffer. */
    uint32_t ca_Size;  
    /**< Certificate authority list buffer size. */
} ssl_CA_Info_t;


typedef struct __SSL_CA_List_s
{
    uint32_t ca_Cnt;                                    
    /**< Certificate authority list count. */
    ssl_CA_Info_t *ca_Info[SSL_MAX_CA_LIST];  
    /**< Certificate authority list info. */
} ssl_CA_List_t; 
	
typedef struct __SSL_PSK_Table_s
{
    uint32_t psk_Size;  
    /**< PSK table buffer size. */
    uint8_t *psk_Buf;      
    /**< PSK table buffer. */ 
} ssl_PSK_Table_t;

typedef struct __SSL_DI_Cert_s
{
    uint32_t di_Cert_Size;  
    /**< Domain-issued certificate buffer size. */
    uint8_t *di_Cert_Buf;      
    /**< Domain-issued certificate buffer. */ 
} SSL_DI_Cert_t;

typedef struct __SSL_RPK_Cert_s
{
    uint8_t *pubkey_Buf;       
    /**< Public key buffer. */ 
    uint32_t pubkey_Size;   
    /**< Public key buffer size. */
    uint8_t *privkey_Buf;        
    /**< Private key buffer. */ 
    uint32_t privkey_Size;    
    /**< Private key buffer size. */
    uint8_t *pass_Key;       
    /**< Password phrase. */
} ssl_RPK_Cert_t;


typedef struct __SSL_Cert_Info_s
{
    SSL_Cert_Type_t cert_Type;	/**< Certification type. */
    union
    {
       ssl_CERT_t cert;		  /**< Certificate. */
       ssl_CA_List_t ca_List;	  /**< CA list. */
       ssl_PSK_Table_t psk_Tbl;  /**< PSK table. */
       SSL_DI_Cert_t di_cert;    /**< Domain-issued certificate. */
       ssl_RPK_Cert_t rpk_cert;  /**< Raw Public Key certificate. */
    } info;								  /**< Certificate information. */
} /** @cond */SSL_Cert_Info_t/** @endcond */;
typedef enum
{
  SSL_ID_CN = 1,
  /**< Subject common name; refer to RFC6125, Section 1.8. */

  SSL_ID_ALT_DNS = 2,
  /**< Subject alternate name entry of type dNSName; refer to RFC6125, Section 1.8. */

  SSL_ID_SRV = 3,
  /**< Service type name. */

  SSL_ID_ALT_URI = 4,
  /**< Subject alternate name entry of type URI; refer to RFC6125, Section 1.8. */

} SSL_Identifier_Type_t;

typedef struct /** @cond */__qapi_Net_SSL_Identifier_s/** @endcond */ {
    SSL_Identifier_Type_t identifier_Type;
    /**< Type of identifier to extract from the certificate. */

    char identifier_Name[SSL_MAX_CERT_NAME_LEN];
    /**< Name (altDNSNames, altURIs, or common name of the certificate. See 
         #QAPI_NET_SSL_MAX_CERT_NAME_LEN. */
}  SSL_Identifier_t;


#ifdef IOT_MEM_DEBUG
void dtls_memcpy_trace(size_t dlen,size_t slen);
#endif
SSL_Obj_Hdl_t SSL_obj_new(void);
Status_t SSL_configure(SSL_Obj_Hdl_t ssl, SSL_Config_t *cfg);
Status_t SSL_fd_set(SSL_Obj_Hdl_t ssl, uint32_t fd);
Status_t SSL_connect(SSL_Obj_Hdl_t ssl);
Status_t SSL_read(SSL_Obj_Hdl_t ssl, void *buf, uint32_t num);
Status_t SSL_write(SSL_Obj_Hdl_t ssl, void *buf, uint32_t num);
Status_t SSL_obj_free(SSL_Obj_Hdl_t hdl);
Status_t SSL_shutdown(SSL_Obj_Hdl_t ssl);


Status_t SSL_cert_load(SSL_Obj_Hdl_t hdl, SSL_Cert_Type_t type, const char *name);
Status_t SSL_cert_delete(char *file_name, SSL_Cert_Type_t type);
Status_t SSL_Cert_File_Exists(char *file_name, SSL_Cert_Type_t type);
Status_t SSL_cert_convert_and_store(SSL_Cert_Info_t *cert_info, const	uint8_t *cert_name);
Status_t SSL_cert_store(const char *name, SSL_Cert_Type_t type, SSL_Cert_t cert, uint32_t size);
Status_t SSL_save_session(SSL_Obj_Hdl_t ssl);



int parse_and_store_psk(ssl_PSK_Table_t *psk, const uint8_t *cert_name);
int unhexify( char const *hex, unsigned char *dst, size_t size);
int parse_and_store_di_cert(SSL_DI_Cert_t *diCert, const uint8_t *out_file);
int parse_and_store_cert(ssl_CERT_t *cert, const uint8_t *out_file);
int parse_and_store_calist(ssl_CA_List_t *calist, const uint8_t *out_file);
Status_t SSL_cert_load_get_identifier(SSL_Obj_Hdl_t hdl, SSL_Identifier_t *identifier, const char *name);


#endif
