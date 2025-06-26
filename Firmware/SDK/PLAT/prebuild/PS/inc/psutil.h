#ifndef __PS_UTIL_H__
#define __PS_UTIL_H__
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - psutil.h
 Description:    - Protocol Stack COMMON utility, just defined some common
                   functions/structures which is common for all PS tasks
 History:        - 14/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/

#include "pssys.h"
#include "pscommtype.h"
#include "pspdu.h"
#include "nascommon.h"

#define CHECK_EBI_VALID(ebi)    (((ebi) >= EBI_5) && ((ebi) <= EBI_15))
#define CHECK_CID_VALID(cid)    ((cid) <= 10)

/*
 * invalid PDP/bearer CID
*/
#define PS_INVALID_PDP_CID      255

/*
 * UL PKG default (LT) life time
*/
#define PS_UL_PKG_DEFAULT_LIFE_TIME_SEC     20

/*
 * MAX UL PKG pending PKG size
*/
#define PS_NB_UL_MAX_PENDING_PKG_SIZE       4500    //3*1500

/*
 * MAX UL PKG pending PKG number
*/
#define PS_NB_UL_MAX_PENDING_PKG_NUM        10

/*
 * Invalid band indicator, band range (1..70) ref to 36.101, Table 5.7.3-1
*/
#define PS_INVALID_BAND                     0


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

UINT8 Uint8Bit1Search(UINT8 data);
UINT8 Uint16Bit1Search(UINT16 data);
UINT8 Uint32Bit1Search(UINT32 data);
UINT8 UintBit1Search(UINT32 data);

UINT8 Uint4Bit0Search(UINT8 data);
UINT8 Uint8Bit0Search(UINT8 data);
UINT8 Uint16Bit0Search(UINT16 data);
UINT8 Uint32Bit0Search(UINT32 data);
UINT8 UintBit0Search(UINT32 data);
extern void OsaFreeOneDlPduBlock(DlPduBlock **pDlPduBlk);
extern void OsaFreeUlPduBlockList(UlPduBlock **pUlPduBlk);
/*
 * set bit B to 1 in D
 * example:
 *  Bit1Set(0x00, 0) = 0x01
 *  Bit1Set(0x01, 4) = 0x11
*/
#define Bit1Set(D, B)   ((D) |= ((UINT32)1<<(B)))

/*
 * set bit B to 0 in D
 * example:
 *  Bit0Set(0xFF, 0) = 0xFE
 *  Bit0Set(0xFE, 4) = 0xEE
*/
#define Bit0Set(D, B)   ((D) &= (~((UINT32)1<<(B))))

/*
 * whether bit B in D is 1
 * example:
 *  IsBit1(1010 1010, 0) = FALSE
 *  IsBit1(1010 1010, 1) = TRUE
*/
#define IsBit1(D, B)    ((((D)>>(B))&0x01) == 0x01)

/*
 * whether bit B in D is 0
 * example:
 *  IsBit0(1010 1010, 0) = TRUE
 *  IsBit0(1010 1010, 1) = FALSE
*/
#define IsBit0(D, B)    ((((D)>>(B))&0x01) == 0x00)

/*
 * Get bit N value
 * example:
 *  GetBitN(1010 1010, 0) = 0
 *  GetBitN(1010 1010, 1) = 1
*/
#define GetBitN(D, B)   (((D)>>(B))&0x01)

/*
 * Get N bits value, start from S,
 * example:
 *  GetBitsN(0x18, 0, 4) = 0x08
 *  GetBitsN(0x18, 3, 2) = 0x03
*/
#define GetBitsN(D, S, N)   (((D)>>(S))&(~(0xFFFFFFFF << (N))))

/*
 * Set N bits of D (UINT8) start from S to V,
 *  (D) &= ~((~(0xFFFFFFFF<<(N)))<<(S)); // set N bits to 0
 *  (D) |= (((V)&(~(0xFFFFFFFF<<(N))))<<(S)); // set N bits to V
 * example:
 *  SetUint8BitsN(1111 1111, 2, 4, 1010) => 1110 1011
 *  SetUint8BitsN(0000 0000, 4, 3, 101)  => 0101 0000
*/
#define SetUint8BitsN(D, S, N, V)   ((D) &= ~((~(0xFFFFFFFF<<(N)))<<(S)), (D) |= (((V)&(~(0xFFFFFFFF<<(N))))<<(S)))

/*
 * GET bytes number from bits number
 * example: GetBitsByteLen(3) = 1
 *          GetBitsByteLen(8) = 1
 *          GetBitsByteLen(10) = 2
*/
//#define GetBitsByteLen(bits)    (((bits)&0x07) == 0 ? ((bits)>>3) : (((bits)>>3)+1))
#define GetBitsByteLen(bits)    (((bits)+7)>>3)



/*
 * set bits value (1-32 bits) ina UINT8 pBuf
*/
void SetBufBitsValue(UINT8 *pBuf, UINT16 *startBitOffset, UINT8 bitsLen, UINT32 value);

/*
 * Get "bitLen" (MAX 32 bits) bits value from "pBuf" start from "bitOffset"
*/
UINT32 GetBufBitsValue(const UINT8 *pBuf, UINT32 *startBitOffset, UINT8 bitsLen);
#define Get4ByteAlignLen(byteLen)   (((byteLen)+3)&0xFFFFFFFC)

/*
 * BITS COPY
*/
void PsBitsCopy(UINT8 *pDestBuf, UINT16 *pDestBO, UINT8 *pSrcBuf, UINT16 ibo, UINT16 bitLen);

/*
 * get PLMN info from IMSI
*/
Plmn PsGetPlmnFromImsi(Imsi *pImsi);

/*
 * SHA-256 functions
*/
/* The right shift operation */
#define SHR(x, n)   ((x) >> (n))
/* The rotate right (circular right shift) operation */
#define ROTR(x, n)  (((x) >> (n)) | ((x) << (32 - (n))))
#define Ch(x, y, z)     (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x, y, z)    (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIGMA0(x)       (ROTR((x), 2)  ^ ROTR((x), 13) ^ ROTR((x), 22))
#define SIGMA1(x)       (ROTR((x), 6)  ^ ROTR((x), 11) ^ ROTR((x), 25))
#define sigma0(x)       (ROTR((x), 7)  ^ ROTR((x), 18) ^ (SHR((x), 3)))
#define sigma1(x)       (ROTR((x), 17) ^ ROTR((x), 19) ^ (SHR((x), 10)))


#ifdef WIN32
void PsFreeOneDlPduBlock(DlPduBlock **pDlPduBlk);      //specification
#else
#define PsFreeOneDlPduBlock(ppDlPduBlk)     OsaFreeOneDlPduBlock((ppDlPduBlk))
#endif

#ifdef WIN32
void PsFreeDlPduBlockList(DlPduBlock **pDlPduBlk);      //specification
#else
#define PsFreeDlPduBlockList(ppDlPduBlk)    OsaFreeDlPduBlockList((ppDlPduBlk))
#endif


#ifdef WIN32
void PsFreeOneUlPduBlock(UlPduBlock **pUlPduBlk);      //specification
#else
#define PsFreeOneUlPduBlock(ppUlPduBlk)    OsaFreeOneUlPduBlock((ppUlPduBlk))
#endif

#ifdef WIN32
void PsFreeUlPduBlockList(UlPduBlock **pUlPduBlk);      //specification
#else
#define PsFreeUlPduBlockList(ppUlPduBlk)    OsaFreeUlPduBlockList((ppUlPduBlk))
#endif

#define SET_UINT32_DATA_LEFT_SHIFT(n,b,i)             \
{                                                     \
    (n) = ( (UINT32) (b)[(i)    ]       )             \
        | ( (UINT32) (b)[(i) + 1] <<  8 )             \
        | ( (UINT32) (b)[(i) + 2] << 16 )             \
        | ( (UINT32) (b)[(i) + 3] << 24 );            \
}

#define SET_UINT32_DATA_RIGHT_SHIFT(n,b,i)            \
{                                                     \
    (b)[(i)    ] = (UINT8) (((n)       ) & 0xFF );    \
    (b)[(i) + 1] = (UINT8) (((n) >>  8 ) & 0xFF );   \
    (b)[(i) + 2] = (UINT8) (((n) >> 16 ) & 0xFF );   \
    (b)[(i) + 3] = (UINT8) (((n) >> 24 ) & 0xFF );   \
}



typedef enum PS_CHAP_AUTH_CODE_TYPE_Tag
{
    CHAP_MSG_CODE_TYPE_CHALLENGE = 1,
    CHAP_MSG_CODE_TYPE_RESPONSE  = 2,
    CHAP_MSG_CODE_TYPE_SUCCESS   = 3,
    CHAP_MSG_CODE_TYPE_FAILURE   = 4,
}PS_CHAP_AUTH_CODE_TYPE;



/******************************************************************************
 *****************************************************************************
 * Functions specification
 *****************************************************************************
******************************************************************************/

UINT8 Uint8Bit1Search(UINT8 data);
UINT8 Uint16Bit1Search(UINT16 data);
UINT8 Uint32Bit1Search(UINT32 data);
UINT8 UintBit1Search(UINT32 data);

UINT8 Uint4Bit0Search(UINT8 data);
UINT8 Uint8Bit0Search(UINT8 data);
UINT8 Uint16Bit0Search(UINT16 data);
UINT8 Uint32Bit0Search(UINT32 data);
UINT8 UintBit0Search(UINT32 data);


/*
 * BITS COPY
*/
void PsBitsCopy(UINT8 *pDestBuf, UINT16 *pDestBO, UINT8 *pSrcBuf, UINT16 ibo, UINT16 bitLen);

/*
 * get PLMN info from IMSI
*/
Plmn PsGetPlmnFromImsi(Imsi *pImsi);
void HmacSha256(UINT16 inputKeyLength, UINT8 *pInputKey, UINT32 messageLength, UINT8 *pMessageContent, UINT8 *outPut);

/*
 * Free the Data memory, which type is : DataPduMemType
*/
void PsFreeDataPduMem(UINT8 memType, UINT8 **ptr);

void PsFreeDataPdu(UINT8 memType, UINT8 *ptr);


/*
 * Free the "UlPduInfo" list
*/
void PsFreeDataPduList(UlPduInfo **pPdu);

/*
 * Free the "PacketFilterList" list
*/
void PsFreePacketFilterlist(PacketFilterList** pflist);

/*
 * Copy the "PacketFilterList" list
*/
void PsCopyTftList(const PacketFilterList *pSrcTftHdr, PacketFilterList **ppDestTftHdr);

/*
 * get next UL Pkg header in the list
*/
UlPduInfo* PsGetNextUlPkgHdr(UlPduInfo *pPdu);

/*
 * check whether the UL PKG(DATA) is out of date
*/
BOOL PsUlDataBeOutDate(UINT8 tickType, UINT32 sysTick, BOOL *bMustDiscard);

/*
 * Get the PDU pkg number, and valid total length in UL PDU list
*/
void PsGetUlPduNumAndLenInList(const UlPduInfo *pHdr, const UlPduInfo *pTailer, UINT32 *pPduNum, UINT32 *pPduLen);

/*
 * Clear the UL pending PKG list
 *  check whether out of date, or pending pkg number/size overflow
*/
UINT32 PsClearUlPendingPduList(UlPduInfo **pHdr, UlPduInfo **pTailer);

/*
 * APN format convert
*/
void ConvertDisPlayApnToNetworkFormat(UINT8 *srcApn, UINT8 srcApnLen, UINT8 *desApn, UINT8 *desApnLen);
void ConvertNetworkApnToDisPlayFormat(UINT8 *srcApn, UINT8 srcApnLen, UINT8 *desApn, UINT8 *desApnLen);

/*
 * Convert DL EARFCN to BAND
*/
UINT8 PsGetBandFromDlEarfcn(UINT32 dlEarfcn);

/*
 * Convert DL EARFCN to Frequency
*/
UINT32 PsConvertDlEarfcnToFrequency(UINT32 dlEarfcn);

/*
 * Check overseas operator
*/
BOOL PsIsOverseasOperator(Plmn plmn);

/* Get current operator from PS */
UINT8 PsGetCurrentOperator(void);

#endif

