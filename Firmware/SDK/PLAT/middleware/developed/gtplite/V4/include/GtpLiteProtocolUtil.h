#ifndef GTP_XTA_UTIL_H
#define GTP_XTA_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif
/*===========================================================================

                  GTP XTA Utility Header File

DESCRIPTION
  This header file contains definitions of data structure and interfaces
  for GTP XTA protocol utilities.

  Copyright (c) 2018 - 2019 QUALCOMM Incorporated.
  Qualcomm Confidential and Proprietary. All Rights Reserved.
  Copyright (c) 2018 - 2019 Qualcomm Atheros, Inc.
  Qualcomm Atheros Confidential and Proprietary. All Rights Reserved. 

Export of this technology or software is regulated by the U.S. Government.
Diversion contrary to U.S. law prohibited.

===========================================================================*/

#include <stddef.h>    /* Definition for basic types and macros */
#include <stdint.h>
#include <stdbool.h>

#ifndef _UINT64_DEFINED
/** Unsigned 64-bit value.
*/
typedef  unsigned long long int  uint64; 
#define _UINT64_DEFINED
#endif


#ifndef _UINT32_DEFINED
/** Unsigned 32-bit value.
*/
typedef  unsigned long int  uint32;      
#define _UINT32_DEFINED
#endif

#ifndef _UINT16_DEFINED
/** Unsigned 16-bit value.
*/
typedef  unsigned short     uint16;      
#define _UINT16_DEFINED
#endif

#ifndef _UINT8_DEFINED
/** Unsigned 8-bit value. 
*/
typedef  unsigned char      uint8;       
#define _UINT8_DEFINED
#endif

#ifndef _INT32_DEFINED
/** Signed 32-bit value.
*/
typedef  signed long int    int32;
#define _INT32_DEFINED
#endif

#ifndef _INT16_DEFINED
/** Signed 16-bit value.
*/
typedef  signed short       int16;
#define _INT16_DEFINED
#endif

#ifndef _BOOLEAN_DEFINED

/** @addtogroup utils_services
@{ */
/** Boolean value type. 
*/
typedef  unsigned char      boolean;  
#define _BOOLEAN_DEFINED
#endif

#ifndef TRUE
#define TRUE ((boolean)1)
#endif

#ifndef FALSE
#define FALSE ((boolean)0)
#endif

typedef int64_t  int64;
typedef int8_t int8;

#define C_GDT_BIG_ENDIAN        0  /* big endian architecture */
#define C_GDT_LITTLE_ENDIAN     1  /* little endian architecture */


/* Constants */
#define GTP_XTA_UTIL_BITS_PER_BYTE     8  /* number of bits in a byte */
#define GTP_XTA_UTIL_BITS_PER_UINT64  64  /* number of bits in a U64 */
#define GTP_XTA_UTIL_BYTES_PER_UINT64  8  /* number of bytes in a U64 */

/* used for inserting arbitrary no. of bits into a byte buffer */
typedef struct
{
    uint8     *p_zBuf;         /* pointer to buffer */
    uint32    ulBufLen;        /* length of buffer */
    uint32    ulCurrentByte;   /* index to current byte in buffer */
    uint8     ucCurrentBit;    /* index to current bit in buffer (msb = 0 and lsb = 7) */
} gtp_xta_bit_inserter;

/* used for extracting arbitrary no. of bits from a byte buffer */
typedef struct
{
    const uint8 *cp_zBuf;         /* pointer to buffer */
    uint32       ulBufLen;        /* length of buffer */
    uint32       ulCurrentByte;   /* index to current byte in buffer */
    uint8        ucCurrentBit;    /* index to current bit in buffer 
                                     (msb = 0 and lsb = 7) */
} gtp_xta_bit_extractor;

/*===========================================================================
FUNCTION gtp_xta_init_bit_operations

DESCRIPTION
  This function initializes a bit inserter struct.

PARAMETERS
  None.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE - Initialization succeed.
  FALSE - Initialization failed.

SIDE EFFECTS
  None.

===========================================================================*/
void gtp_xta_init_bit_operations( void );


/*===========================================================================
FUNCTION gtp_xta_init_bit_inserter

DESCRIPTION
  This function initializes a bit inserter struct.

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit inserter structure.
  p_ucData        - (IN) Buffer to used for inserted bits.
  ulLength        - (IN) Max size of buffer in bytes.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE - Initialization succeed.
  FALSE - Initialization failed.

SIDE EFFECTS
  None.

===========================================================================*/
boolean gtp_xta_init_bit_inserter( gtp_xta_bit_inserter *p_zBitInserter,
                                   uint8 *p_ucData,
                                   uint32 ulLength );


/*===========================================================================
FUNCTION gtp_xta_set_bits_u64

DESCRIPTION
  This function inserts specified number of bits into a bit inserter struct
  (up to 57 to 64 bits depending on current bit position in inserter).

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit inserter structure.
  ulNumBits       - (IN) Number of bits to insert.
  ullDataU64      - (IN) Data (bits) to be inserted. Only the 'ulNumBits'
                         least significant bits from the UINT64 are inserted.
  bUpdatePos      - (IN) TRUE  - Move the current bit inserter position to
                                 after the last inserted bit.
                         FALSE - Don't move current bit inserter position.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE - Set succeed.
  FALSE - Set failed.

SIDE EFFECTS
  None.

===========================================================================*/
boolean gtp_xta_set_bits_u64( gtp_xta_bit_inserter *p_zBitInserter,
                              uint32 ulNumBits,
                              uint64 ullDataU64,
                              boolean bUpdatePos);


/*===========================================================================
FUNCTION gtp_xta_insert_bits_u64

DESCRIPTION
  This function inserts specified number of bits into a bit inserter struct
  and moves the current bit inserter position to after the last inserted bit.

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit inserter structure.
  ulNumBits       - (IN) Number of bits to insert.
  ullDataU64      - (IN) Data (bits) to be inserted. Only the 'ulNumBits'
                         least significant bits from the UINT64 are inserted.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE - Insert succeed.
  FALSE - Insert failed.

SIDE EFFECTS
  None.

===========================================================================*/
boolean gtp_xta_insert_bits_u64( gtp_xta_bit_inserter *p_zBitInserter,
                                 uint32 ulNumBits,
                                 uint64 ullDataU64 );


/*===========================================================================
FUNCTION gtp_xta_insert_byte_align

DESCRIPTION
  This function inserts 0 to 7 bits to align to a byte boundary.

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit inserter structure.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void gtp_xta_insert_byte_align( gtp_xta_bit_inserter *p_zBitInserter);


/*===========================================================================
FUNCTION gtp_xta_get_inserter_data

DESCRIPTION
  This function gets the pointer to the inserter data and the length of the
  data.

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit inserter structure.
  p_ucData        - (OUT) Pointer to UINT8 pointer variable to be updated
                          with pointer to the bit inserter buffer.
  p_ulLength      - (OUT) Pointer to UINT32 variable to be updated with
                          the length of the bit inserter buffer.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void gtp_xta_get_inserter_data( const gtp_xta_bit_inserter *p_zBitInserter,
                                uint8 **p_ucData,
                                uint32 *p_ulLength);


/*===========================================================================
FUNCTION gtp_xta_get_inserter_ptr

DESCRIPTION
  This function gets the pointer to the current byte in inserter buffer.

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit inserter structure.

DEPENDENCIES
  None.

RETURN VALUE
  Pointer to the current byte in inserter buffer

SIDE EFFECTS
  None.

===========================================================================*/
uint8* gtp_xta_get_inserter_ptr( const gtp_xta_bit_inserter *p_zBitInserter );


/*===========================================================================
FUNCTION gtp_xta_init_bit_extractor

DESCRIPTION
  This function initializes a bit extractor struct.

PARAMETERS
  p_zBitExtractor - (IN) Pointer to bit extractor structure.
  cp_ucData       - (IN) Buffer to used for extracting bits.
  ulLength        - (IN) Max size of buffer in bytes.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE - Initialization succeed.
  FALSE - Initialization failed.

SIDE EFFECTS
  None.

===========================================================================*/
boolean gtp_xta_init_bit_extractor( gtp_xta_bit_extractor *p_zBitExtractor,
                                    const uint8 *cp_ucData,
                                    uint32 ulLength );


/*===========================================================================
FUNCTION gtp_xta_extract_bits_u64

DESCRIPTION
  This function extracts specified number of bits from a bit extractor
  struct.

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit extractor structure.
  ulNumBits       - (IN) Number of bits to extract.
  p_ullDataU64    - (OUT) Pointer to UINT64 variable where bits will be
                          extracted to. The least significant bits in
                          the UINT64 are used.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE - Extract succeed.
  FALSE - Extract failed.

SIDE EFFECTS
  None.

===========================================================================*/
boolean gtp_xta_extract_bits_u64( gtp_xta_bit_extractor *p_zBitExtractor,
                                  uint32 ulNumBits,
                                  uint64 *p_ullDataU64 );


/*===========================================================================
FUNCTION gtp_xta_extract_byte_align

DESCRIPTION
  This function skips 0 to 7 bits to align to a byte boundary.

PARAMETERS
  p_zBitInserter  - (IN) Pointer to bit extractor structure.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void gtp_xta_extract_byte_align( gtp_xta_bit_extractor *p_zBitExtractor);


#ifdef __cplusplus
}
#endif
#endif /* GTP_XTA_UTIL_H */

