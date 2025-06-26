/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    pertypes.h
 * Description:  Header file for PER decoding and encoding types
 *
 ****************************************************************************/

#ifndef PER_TYPES_H
#define PER_TYPES_H


/******************************************************************/
/*       Includes                                                 */
/******************************************************************/
#include "commontypedef.h"


/******************************************************************/
/*       Macros                                                   */
/******************************************************************/
#define BITS_PER_UINT8                     8
#define BITS_PER_UINT16                    16
#define BITS_PER_UINT32                    32

#define ENCODED_DATA_LENGTH_OCTETS         1000
#define ENCODED_DATA_LENGTH_BITS           (ENCODED_DATA_LENGTH_OCTETS * BITS_PER_UINT8)

#define PER_DEFAULT_BUFFER_SIZE            480
#define PER_MIN_ALLOCATE_SIZE              1
#define PER_MAX_EXTENSTION_NUM             8    //need to extend for Cat1bis


/******************************************************************/
/*       Enums                                                    */
/******************************************************************/
typedef enum PerErrorTag
{
    PER_NO_ERROR = 0,

    PER_ERROR_LENGTH_OUT_OF_RANGE = 1,
    PER_ERROR_VALUE_OUT_OF_RANGE = 2,
    PER_ERROR_DECODE_OVERRUN = 3,

    PER_ERROR_INVALID_ENUM = 4,
    PER_ERROR_INVALID_CHOICE_TAG = 5,
    PER_ERROR_UNSUPPORTED_EXTENSION = 6,

    PER_ERROR_RELEASE = 7,
    PER_ERROR_GRAMMAR = 8,
    PER_ERROR_EXT_GROUP = 9,
    PER_ERROR_UTCTIME = 10,

    PER_ERROR_LPP_MSG_HEADER = 11,
    PER_ERROR_LPP_MSG_BODY = 12,
}PerError;

/******************************************************************/
/*       Structs                                                  */
/******************************************************************/
typedef struct PerDynamicMemTag
{
    //The total allocated memory size of this block
    UINT16                      allocSize;
    //The memory size already used for encode/decode, unit in bytes
    UINT16                      usedLength;
    //The pointer to the next dynamic memory block
    struct PerDynamicMemTag     *pNext;
    //The dynamic memory used for encode/decode
    UINT8                       data[PER_MIN_ALLOCATE_SIZE];
}PerDynamicMem;

typedef struct PerBufferTag
{
    //Pointer to the start address of PER encoded raw data
    UINT8                       *pEncodedData;
    //The bit offset of pEncodedData, indicate the current encode/decode bit length
    UINT32                      encodedDataBitOffset;
    //The bit offset of pEncodedData, recode the previous encode/decode bit length
    UINT32                      previousBitOffset;
    //The max bit length of the encoded raw data
    UINT32                      maxEncodedBitLength;

    //Pointer to the first dynamic memory block
    PerDynamicMem               *pHead;
    //Pointer to the last dynamic memory block
    PerDynamicMem               *pTail;

    //TRUE, only calculate the raw data length after PER encoding
    //FALSE, perform the actual PER encoding and generate the encoded raw data
    //only apply for encode
    BOOL                        bOnlyCalcLen;
    UINT16                      reserved;

    //the number of extension group, only apply for decode
    UINT8                       numOfExtGroup;
    //recode the end bit offset of the extension group, only apply for decode
    UINT32                      extGroupEndOffset[PER_MAX_EXTENSTION_NUM];
}PerBuffer;


#endif

