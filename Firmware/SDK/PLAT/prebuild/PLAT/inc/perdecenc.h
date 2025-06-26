 /****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    perdecenc.h
 * Description:  Header file for PER decoding and encoding functions
 *
 ****************************************************************************/
#ifndef PER_DEC_ENC_H
#define PER_DEC_ENC_H

/***************************************************************************
** Nested Include Files
***************************************************************************/
//#include "pssys.h"
#include "pertypes.h"
#include "osasys.h"


/***************************************************************************
 *   Manifest Constants
 ***************************************************************************/

/***************************************************************************
 *   Macro Functions
 ***************************************************************************/
#define PER_DEV_CHECK(A,B,C,D)       OsaCheck ((A),(B),(C),(D));
#define BITS_TO_UINT8S(bits)         (((bits) + BITS_PER_UINT8 - 1)/BITS_PER_UINT8)

/***************************************************************************
 *   Types
 ***************************************************************************/

/***************************************************************************
 *   Typed Constants
 ***************************************************************************/

/***************************************************************************
 *  Function Prototypes
 ***************************************************************************/

/***************************************************************************
 *  Encode Functions
 ***************************************************************************/
void PerEncBOOL (PerBuffer *pPerBuffer,
                    BOOL   *pValue);

void PerEncBOOLValue (PerBuffer *pPerBuffer,
                         BOOL   value);

void PerEncEnum (PerBuffer *pPerBuffer,
                 UINT8      *pValue,
                 UINT8      max);

void PerEncEnumWithExtension (PerBuffer *pPerBuffer,
                              UINT8      *pValue,
                              UINT8      maxValueInRoot);

void PerEncUINT8 (PerBuffer *pPerBuffer,
                 UINT8      *pValue,
                 UINT8      min,
                 UINT8      max);

void PerEncUINT16 (PerBuffer *pPerBuffer,
                  UINT16     *pValue,
                  UINT16     min,
                  UINT16     max);

void PerEncUINT32 (PerBuffer *pPerBuffer,
                  UINT32     *pValue,
                  UINT32     min,
                  UINT32     max);

void PerEncINT8 (PerBuffer  *pPerBuffer,
                       INT8 *pValue,
                       INT8 min,
                       INT8 max);

void PerEncINT16 (PerBuffer   *pPerBuffer,
                        INT16 *pValue,
                        INT16 min,
                        INT16 max);

void PerEncINT32 (PerBuffer   *pPerBuffer,
                        INT32 *pValue,
                        INT32 min,
                        INT32 max);

void PerEncUnChangeableBitString (PerBuffer *pPerBuffer,
                           UINT8      *pValue,
                           UINT16     number);

void PerEncUnChangeableOctetString (PerBuffer *pPerBuffer,
                             UINT8      *pValue,
                             UINT16     length);

void PerEncChangeableBitString (PerBuffer *pPerBuffer,
                              UINT8      *pValue,
                              UINT16     length,
                              UINT16     min,
                              UINT16     max);

void PerEncChangeableOctetString (PerBuffer *pPerBuffer,
                                UINT8      *pValue,
                                UINT16     length,
                                UINT16     min,
                                UINT16     max);

void PerEncUnRestrictedBitString (PerBuffer *pPerBuffer,
                                   UINT8      *pValue,
                                   UINT16     length);

void PerEncUnRestrictedOctetString (PerBuffer *pPerBuffer,
                                     UINT8      *pValue,
                                     UINT16     length);

void PerEncUnRestrictedOctetStringDedicatedInfoNAS (PerBuffer *pPerBuffer,
                                     UINT8      *pValue,
                                     UINT16     length);

void PerEncRestrictedLength (PerBuffer *pPerBuffer,
                              UINT16     value,
                              UINT16     min,
                              UINT16     max);

void PerEncUnRestrictedLength (PerBuffer *pPerBuffer,
                                    UINT16     value);

void PerEncLengthOfExtensionNum (PerBuffer *pPerBuffer,
                                        UINT8     *pValue);

void PerEncExtensionGroupBegin (PerBuffer *pPerBuffer);

void PerEncExtensionGroupEnd (PerBuffer *pPerBuffer);


/***************************************************************************
 *  Decode Functions
 ***************************************************************************/
PerError PerDecBOOL (PerBuffer *pPerBuffer,
                        BOOL   *pValue);

PerError PerDecEnum (PerBuffer *pPerBuffer,
                     UINT8      *pValue,
                     UINT8      max);

PerError PerDecEnumWithExtension (PerBuffer *pPerBuffer,
                                  UINT8      *pValue,
                                  UINT8      maxValueInRoot);

PerError PerDecUINT8 (PerBuffer *pPerBuffer,
                     UINT8      *pValue,
                     UINT8      min,
                     UINT8      max);

PerError PerDecUINT16 (PerBuffer *pPerBuffer,
                      UINT16     *pValue,
                      UINT16     min,
                      UINT16     max);

PerError PerDecUINT32 (PerBuffer *pPerBuffer,
                      UINT32     *pValue,
                      UINT32     min,
                      UINT32     max);

PerError PerDecINT8 (PerBuffer  *pPerBuffer,
                           INT8 *pValue,
                           INT8 min,
                           INT8 max);

PerError PerDecINT16 (PerBuffer   *pPerBuffer,
                            INT16 *pValue,
                            INT16 min,
                            INT16 max);

PerError PerDecINT32 (PerBuffer   *pPerBuffer,
                            INT32 *pValue,
                            INT32 min,
                            INT32 max);

PerError PerDecUnChangeableBitString (PerBuffer *pPerBuffer,
                               UINT8      *pValue,
                               UINT16     length);

PerError PerDecUnChangeableOctetString (PerBuffer *pPerBuffer,
                                 UINT8      *pValue,
                                 UINT16     length);

PerError PerDecChangeableBitString (PerBuffer *pPerBuffer,
                                  UINT8      *pValue,
                                  UINT16     *pLength,
                                  UINT16     min,
                                  UINT16     max);

PerError PerDecChangeableOctetString (PerBuffer *pPerBuffer,
                                    UINT8      *pValue,
                                    UINT16     *pLength,
                                    UINT16     min,
                                    UINT16     max);

PerError PerDecUnRestrictedBitString (PerBuffer *pPerBuffer,
                                       UINT8      **ppValue,
                                       UINT16     *pLength);

PerError PerDecUnRestrictedOctetString (PerBuffer *pPerBuffer,
                                         UINT8      **ppValue,
                                         UINT16     *pLength);

PerError PerDecUnRestrictedOctetStringDedicatedInfoNAS (PerBuffer *pPerBuffer,
                                         UINT8      **ppValue,
                                         UINT16     *pEncodedDataBitOffset,
                                         UINT16     *pLength);

PerError PerDecRestrictedLength (PerBuffer *pPerBuffer,
                                    UINT16     *pValue,
                                    UINT16     min,
                                    UINT16     max);

PerError PerDecUnRestrictedLength (PerBuffer *pPerBuffer,
                                       UINT16     *pValue);

PerError PerDecLengthOfExtensionNum (PerBuffer *pPerBuffer,
                                         UINT8     *pValue);

void PerDecExtensionGroupBegin (PerBuffer *pPerBuffer);

void PerDecExtensionGroupEnd (PerBuffer *pPerBuffer);


PerError PerDecPaddingBits (PerBuffer    *pPerBuffer,
                              UINT8      **ppValue,
                              UINT16     *pLength);


/***************************************************************************
 *  Memory Allocation Functions
 ***************************************************************************/
void PerAllocMemory (PerBuffer    *pPerBuffer,
                        UINT16    numberOfBytes,
                        void      **ppBuffer);

void PerFreeMemory (PerBuffer *pPerBuffer);

void PerInitSpaceForEncode (PerBuffer *pPerBuffer);

/***************************************************************************
 *  Initialisation Functions
 ***************************************************************************/
void PerInitEncode (PerBuffer    *pPerBuffer,
                      UINT8      *pEncodedData,
                      UINT32     maxEncodedBitLength);

void PerInitDecode (PerBuffer    *pPerBuffer,
                      UINT8      *pEncodedData,
                      UINT32     maxEncodedBitLength,
                      UINT16     initialDecodeSize,
                      void       **ppDecodedData);

/***************************************************************************
 *  Other Functions
 ***************************************************************************/
UINT8 PerDec8BitsExt (UINT8  *pSource,
                         UINT32 * const pSourceBitOffset,
                         const UINT8 numOfBits);

UINT16 PerDec16BitsExt (UINT8  * const pSource,
                            UINT32 * const pSourceBitOffset,
                            const UINT8 numOfBits);

#endif
