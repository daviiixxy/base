#ifndef PSIF_HDR_DL_MM_H
#define PSIF_HDR_DL_MM_H

/******************************************************************************
 ******************************************************************************
 Copyright:      - 2018- Copyrights of Qualcomm Ltd.
 File name:      - psifmem.h
 Description:    - ps downlink memory manager header file
 History:        - 04/04/2018, Originated by xwang
 ******************************************************************************
******************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/

/*
*ps memory pool init function
*/
void PsMmPoolInit(void);

/*
 * The memory allocated:
 * +------------------------------------------+--------------------------+
 * | ps_mm_block_tag header(ps_mm_block_size) | data                     |
 * +------------------------------------------+--------------------------+
 *                  					      ^
 *                                            | return address
 * 
*/
void *PsMmMalloc( size_t size );

/*
*ps memory free function 
*/
void PsMmFree(void* memory);

/*
*check whether there is any free memory 
*/
UINT8 IsAnyPsDlFreeMm(void);

/*
*get the remain free mm size
*/
int PsMmGetRemainFreeSize(void);

#ifdef __cplusplus
}
#endif


#endif

