/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    asn1util.h
 * Description:  Header file for abstract syntax notation one (ASN1) utility API
 *
 ****************************************************************************/
#ifndef __ASN1_UTIL_H__
#define __ASN1_UTIL_H__

#include "asn1type.h"

/******************************************************************************
 ******************************************************************************
 * MARCO/STRUCT/ENUM definition
 ******************************************************************************
******************************************************************************/


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/
void AsnEnBitsValue(AsnEnContext *pEnCtx, UINT32 value, UINT8 bitLen);
UINT32 AsnDeBitsValue(AsnDeContext *pDeCtx, UINT8 bitLen);



/******************************************************************************
 *  Write/Encode Functions
******************************************************************************/
void AsnEnEnumerated(AsnEnContext *pEnCtx, BOOL bWithExt, UINT8 eVal, UINT8 maxVal);
void AsnEnChoiceTag(AsnEnContext *pEnCtx, BOOL bWithExt, UINT8 eVal, UINT8 maxVal);
void AsnEnInteger(AsnEnContext *pEnCtx, INT32 wrVal, INT32 minVal, INT32 maxVal);
void AsnEnUnsignedInteger(AsnEnContext *pEnCtx, UINT32 wrVal, UINT32 minVal, UINT32 maxVal);
void AsnEnConstLenBitStr(AsnEnContext *pEnCtx, UINT8 *pBitStr, UINT32 bitLen);
void AsnEnLimitedLenBitStr(AsnEnContext *pEnCtx, UINT8 *pBitStr, UINT32 bitLen, UINT32 minLen, UINT32 maxLen);
void AsnEnUnLimitedLenBitStr(AsnEnContext *pEnCtx, UINT8 *pBitStr, UINT32 bitLen);
void AsnEnConstLenOctStr(AsnEnContext *pEnCtx, UINT8 *pOctStr, UINT32 byteLen);
void AsnEnLimitedLenOctStr(AsnEnContext *pEnCtx, UINT8 *pOctStr, UINT32 byteLen, UINT32 minLen, UINT32 maxLen);
void AsnEnUnLimitedLenOctStr(AsnEnContext *pEnCtx, UINT8 *pOctStr, UINT32 byteLen);
void AsnEnUnLimitedLenOctStrDedicatedInfoNAS(AsnEnContext *pEnCtx, UINT8 *pOctStr, UINT32 byteLen);
void AsnEnLenWithLimitedRange(AsnEnContext *pEnCtx, UINT32 len, UINT32 minLen, UINT32 maxLen);
void AsnEnLenWithUnLimitedRange(AsnEnContext *pEnCtx, UINT32 len);
void AsnEnOptFieldBitmap(AsnEnContext *pEnCtx, UINT32 optFieldBitmap, UINT8 numOfOptIE);
void AsnEnExtensionNum(AsnEnContext *pEnCtx, UINT8 extNum);
void AsnEnExtensionBitmap(AsnEnContext *pEnCtx, UINT32 extBitmap, UINT8 numOfExt);
void AsnEnRsvdLenBufForExtension(AsnEnContext *pEnCtx);
void AsnEnFillLenBufForExtension(AsnEnContext *pEnCtx);
void AsnEnFillPaddingForExtension(AsnEnContext *pEnCtx);


/******************************************************************************
 *  Read/Decode Functions
******************************************************************************/
UINT8 AsnDeEnumerated(AsnDeContext *pDeCtx, BOOL bWithExt, UINT8 maxEnum);
UINT8 AsnDeChoiceTag(AsnDeContext *pDeCtx, BOOL bWithExt, UINT8 maxTag);
INT32 AsnDeInteger(AsnDeContext *pDeCtx, INT32 minVal, INT32 maxVal);
UINT32 AsnDeUnsignedInteger(AsnDeContext *pDeCtx, UINT32 minVal, UINT32 maxVal);
void AsnDeConstLenBitStr(AsnDeContext *pDeCtx, UINT8 *pRetBitStr, UINT32 bitLen);
void AsnDeLimitedLenBitStr(AsnDeContext *pDeCtx, UINT8 *pRetBitStr, UINT16 *pRetBitLen, UINT32 minLen, UINT32 maxLen);
void AsnDeUnLimitedLenBitStr(AsnDeContext *pDeCtx, UINT8 **ppRetBitStr, UINT16 *pRetBitLen);
void AsnDeConstLenOctStr(AsnDeContext *pDeCtx, UINT8 *pRetOctStr, UINT32 byteLen);
void AsnDeLimitedLenOctStr(AsnDeContext *pDeCtx, UINT8 *pRetOctStr, UINT16 *pRetLen, UINT32 minByteLen, UINT32 maxByteLen);
void AsnDeUnLimitedLenOctStr(AsnDeContext *pDeCtx, UINT8 **ppRetOctStr, UINT16 *pRetLen);
void AsnDeUnLimitedLenOctStrDedicatedInfoNAS(AsnDeContext *pDeCtx, UINT8 **ppRetOctStr, UINT16 *pStartOffset, UINT16 *pRetLen);
UINT16 AsnDeLenWithLimitedRange(AsnDeContext *pDeCtx, UINT16 minLen, UINT16 maxLen);
UINT16 AsnDeLenWithUnLimitedRange(AsnDeContext *pDeCtx);
UINT32 AsnDeOptFieldBitmap(AsnDeContext *pDeCtx, UINT8 numOfOptIE);
UINT8 AsnDeExtensionNum(AsnDeContext *pDeCtx);
UINT32 AsnDeExtensionBitmap(AsnDeContext *pDeCtx, UINT8 numOfExt);
void AsnDeBackupExtensionEndPost(AsnDeContext *pDeCtx);
void AsnDeGotoExtensionEndPost(AsnDeContext *pDeCtx);
void AsnDeSkipUnsupportedExtension(AsnDeContext *pDeCtx);

/******************************************************************************
 *  Asn Utility Functions
******************************************************************************/
void* AsnDeAllocIEMemory(AsnDeContext *pDeCtx, UINT16 wantByte);
AsnRet AsnGetDecodeResult(AsnDeContext *pDeCtx);
void AsnGetEncodedData(AsnEnContext *pEnCtx, UINT16 *pAsnByteLen, UINT8 **ppAsnData);

/******************************************************************************
 *  Initialisation Functions
******************************************************************************/
void AsnInitEncodeContext(AsnEnContext *pEnCtx, UINT16 estAsn1Size);
void AsnInitDecodeContext(AsnDeContext *pDeCtx, UINT8 *pAsn1Data, UINT16 asn1Len, OsaIeMemInfo *pIeMemInfo);



#endif

