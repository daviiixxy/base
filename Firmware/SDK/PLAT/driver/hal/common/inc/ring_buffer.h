/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ring_buffer.h
 * Description:  ring buffer header file
 * History:      Rev1.0   2018-08-06
 *
 ****************************************************************************/

#ifndef __RingBufferUtils_h__
#define __RingBufferUtils_h__

#include <stdint.h>
#include <string.h>

// Struct defination for Ring Buffer
typedef struct
{
  uint8_t*  buffer;
  uint32_t  size;
  volatile uint32_t  head; /* Read from */
  volatile uint32_t  tail; /* Write to */
} ring_buffer_t;

#ifndef MIN
#define MIN(x,y)  ((x) < (y) ? (x) : (y))
#endif


int initRingBuffer( ring_buffer_t* ring_buffer, uint8_t* buffer, uint32_t size );
int deinitRingBuffer( ring_buffer_t* ring_buffer );
uint32_t getFreeRingBuffer( ring_buffer_t* ring_buffer );
uint32_t getRingBufferUsedSpace( ring_buffer_t* ring_buffer );
int getRingBufferData( ring_buffer_t* ring_buffer, uint8_t** data, uint32_t* contiguous_bytes );
uint32_t pushRingBuffer( ring_buffer_t* ring_buffer, const uint8_t* data, uint32_t data_length );
int popRingBuffer( ring_buffer_t* ring_buffer, uint8_t* data, uint32_t data_length, uint32_t* number_of_bytes_read );
uint32_t getRingBufferTotalSize(ring_buffer_t *ring_buffer);

#endif // __RingBufferUtils_h__



