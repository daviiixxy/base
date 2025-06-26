/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    asn1type.h
 * Description:  Header file for abstract syntax notation one (ASN1) entity
 *
 ****************************************************************************/
#ifndef __ASN1_TYPE_H__
#define __ASN1_TYPE_H__
#ifdef WIN32
#include "winsys.h"
#else
#include "osasys.h"
#endif
#include "osautil.h"


/******************************************************************************
 ******************************************************************************
 * MARCO/STRUCT/ENUM definition
 ******************************************************************************
******************************************************************************/

#define AsnCheck            OsaCheck
#define AsnDebugBegin       OsaDebugBegin
#define AsnDebugEnd         OsaDebugEnd

#define AsnFreeMemory       OsaFreeMemory

#define AsnIsBit1           OsaIsBit1
#define AsnBit1Set          OsaBit1Set

/*
 * backup ASN1 max extension number
*/
#define ASN1_BACKUP_MAX_EXT_NUM                 8

/*
 * estimated ASN1 encoded container size
*/
#define ASN1_EST_CONTAINER_SIZE_IN_BYTE         200

/*
 * ASN1 supported extension number
*/
#define ASN1_MAX_SUPPORT_EXTENSION              32

/*
 * ASN1 option number is sequece
*/
#define ASN1_MAX_OPT_FIELD_IN_SEQUENCE          32

/*
 * ASN1 write/encode buffer enlarge by 128 bytes one time
*/
#define ASN_EN_BUF_STEP_SIZE    128

/*
 * ASN1 PDU max size in bytes
*/
#define ASN_EN_BUF_MAX_SIZE     4096



/**
 * name ASN1 Error codes
 * These error codes are OR'ed to X509 error codes for higher error granularity.
 * ASN1 is a standard to specify data structures.
*/
typedef enum AsnRetEnum_Tag
{
    ASN_RET_SUCC = 0,

    ASN_ERR_OUT_OF_DATA     = 1,        /**< Out of data when parsing an ASN1 data structure. */
    ASN_ERR_UNEXPECTED_TAG  = 2,        /**< ASN1 tag was of an unexpected value. */
    ASN_ERR_INVALID_LENGTH  = 3,        /**< Error when trying to determine the length or invalid length. */
    ASN_ERR_LENGTH_MISMATCH = 4,        /**< Actual length differs from expected length. */
    ASN_ERR_INVALID_DATA    = 5,        /**< Data is invalid/not support */
    ASN_ERR_UNEXPECTED_ENUM = 6,        /**< ASN1 enum was of an unexpected value. */
    ASN_ERR_ALLOC_FAILED    = 7,        /**< Memory allocation failed */
    ASN_ERR_BUF_TOO_SMALL   = 8         /**< Buffer too small when writing ASN.1 data structure. */
}AsnRetEnum;

typedef UINT8   AsnRet;



/*
 * ASN1 read/decode context info
*/
typedef struct AsnDeContext_Tag
{
    /*
     * decodeResult, ref to AsnRetEnum, init to ASN_RET_SUCC
    */
    AsnRet          decRet;

    /*
     * backup extension number
    */
    UINT8           bkExtNum;
    UINT16          rsvd0;

    /*
     * pData, store the source ASN1 data
    */
    UINT8           *pData;
    /*
     * memLen, memory length of "pData"
    */
    UINT32          memBitLen;

    /*
     * curRdBitPost, current position of "pData"
    */
    UINT32          curRdBitPost;

    /*
     * pDeMemHdr, Pointer to the first dynamic memory block
    */
    OsaIeMemInfo    ieMemInfo;

    /*
     * backup end position of extension element
    */
    UINT32          bkExtEndPost[ASN1_BACKUP_MAX_EXT_NUM];      //32 bytes
}AsnDeContext;  //52 bytes

/*
 * ASN1 write/encode context info
*/
typedef struct AsnEnContext_Tag
{
    /*
     * pBuf, store the source ASN1 data, allocated in heap
    */
    UINT8       *pBuf;
    /*
     * memLen, memory length of "pBuf"
    */
    UINT32      memBitLen;

    /*
     * curWrBitPost, current write position of "pBuf"
    */
    UINT32      curWrBitPost;

    /*
     * recored extension length position number
    */
    UINT8       extLenNum;
    UINT8       rsvd0;
    UINT16      rsvd1;

    /*
     * extLenBitPost, bit position if extension length, need to reserved 8 bit length postion firstly before encode the extension
    */
    UINT32      extLenBitPost[ASN1_BACKUP_MAX_EXT_NUM]; //32 bytes
}AsnEnContext;  // 48 bytes




#endif

