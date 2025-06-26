/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "commonTypedef.h"

#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/certs.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

#define MAXPATH_SIZE 260
#define HTTP_CLIENT_DEFAULT_TIMEOUT 15000

///HTTP client results
typedef enum {
    HTTP_OK = 0,        ///<Success
    HTTP_PROCESSING,    //1/<Processing
    HTTP_PARSE,         //2/<url Parse error
    HTTP_DNS,           //3/<Could not resolve name
    HTTP_PRTCL,         //4/<Protocol error
    HTTP_NOTFOUND,      //5/<HTTP 404 Error
    HTTP_REFUSED,       //6/<HTTP 403 Error
    HTTP_ERROR,         //7/<HTTP xxx error
    HTTP_TIMEOUT,       //8/<Connection timeout
    HTTP_CONN,          //9/<Connection error
    HTTP_FATAL_ERROR, //10fatal error when conenct
    HTTP_CLOSED,        //11/<Connection was closed by remote host
    HTTP_MOREDATA,      //12/<Need get more data
    HTTP_OVERFLOW,      //13/<Buffer overflow
    HTTP_MBEDTLS_ERR,  
    HTTP_CONN_ERR,      //15/<Connection error

}HTTPResult;


typedef enum  {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE,
    HTTP_HEAD
}HTTP_METH;

typedef struct HttpClientSslTag
{
    mbedtls_ssl_context       sslContext;
    mbedtls_net_context       netContext;
    mbedtls_ssl_config        sslConfig;
    mbedtls_entropy_context   entropyContext;
    mbedtls_ctr_drbg_context  ctrDrbgContext;
    mbedtls_x509_crt_profile  crtProfile;
    mbedtls_x509_crt          caCert;
    mbedtls_x509_crt          clientCert;
    mbedtls_pk_context        pkContext;
}HttpClientSsl;

typedef struct HttpClientContextTag
{
    int socket;
    int timeout_s;
    int timeout_r;
    BOOL isHttps;
    int method;
    UINT16 port;
    char* basicAuthUser;
    char* basicAuthPassword;
    char** customHeaders;
    int headerNum;
    char* custHeader;
    int httpResponseCode;
    int maxredirections;
    char * location;
    HttpClientSsl * ssl;
    const char *caCert;
    const char *clientCert;
    const char *clientPk;
    int caCertLen;
    int clientCertLen;
    int clientPkLen;
}HttpClientContext;

typedef struct HttpClientDataTag
{
    char * postBuf;         //user data to be post
    int postBufLen;
    char * postContentType; //content type of the post data
    int recvContentLength;  //response content length
    int needObtainLen;      //content length hasn't get
    int blockContentLen;    //content length of one block
    BOOL isChunked;
    BOOL isMoreContent;
    char * respBuf;         //buffer to store the response body data
    char * headerBuf;       //buffer to store the response head data
    int respBufLen;
    int  headerBufLen;
    BOOL isRange;         //if get file by Range, each block (rangeTail-rangeHead+1) bytes 
    int rangeHead;
    int rangeTail;
    int contentRange;
}HttpClientData;


#define HTTPDBG(x, ...)      
#define HTTPWARN(x, ...)     
#define HTTPERR(x, ...)      
#define HTTPINFO(x, ...)     

/// Get the text form of the error number
/// 
/// Gets a pointer to a text message that described the result code.
///
/// @param[in] res is the HTTPResult code to translate to text.
/// @returns a pointer to a text message.
///
const char * GetErrorMessage(HTTPResult res);

/**
Provides a basic authentification feature (Base64 encoded username and password)
Pass two NULL pointers to switch back to no authentication
@param[in] user username to use for authentication, must remain valid durlng the whole HTTP session
@param[in] user password to use for authentication, must remain valid durlng the whole HTTP session
*/
void basicAuth(HttpClientContext* context, const char* user, const char* password); //Basic Authentification

/**
Set custom headers for request.

Pass NULL, 0 to turn off custom headers.

@code
 const char * hdrs[] = 
        {
        "Connection", "keep-alive",
        "Accept", "text/html",
        "User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64)",
        "Accept-Encoding", "gzip,deflate,sdch",
        "Accept-Language", "en-US,en;q=0.8",
        };

    http.basicAuth("username", "password");
    http.customHeaders(hdrs, 5);
@endcode

@param[in] headers an array (size multiple of two) key-value pairs, must remain valid during the whole HTTP session
@param[in] pairs number of key-value pairs
*/
void customHeaders(HttpClientContext* context, char** headers, int pairs);

HTTPResult httpSendRequest(HttpClientContext* context, const char* url, HTTP_METH method,  HttpClientData * data); 
HTTPResult httpRecvResponse(HttpClientContext* context, HttpClientData * data); 

//High Level setup functions
/** Execute a GET request on the URL
Blocks until completion
@param[in] url : url on which to execute the request
@param[in,out] pDataIn : pointer to an IHTTPDataIn instance that will collect the data returned by the request, can be NULL
@param[in] timeout waiting timeout in ms (osWaitForever for blocking function, not recommended)
@return 0 on success, HTTP error (<0) on failure
*/
HTTPResult httpGet(HttpClientContext* context, const char* url,  HttpClientData * data,  int timeout);

HTTPResult httpPost(HttpClientContext* context, const char* url,  HttpClientData * data,  int timeout);

HTTPResult httpConnect(HttpClientContext* context, const char* url); //Execute request

HTTPResult httpClose(HttpClientContext* context);

HTTPResult httpRecv(HttpClientContext* context, char* buf, INT32 minLen, INT32 maxLen, INT32* pReadLen);

//HTTPResult httpConnectSocket(INT32 socket,struct sockaddr *addr, INT32 addrlen);

#endif
