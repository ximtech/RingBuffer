#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


typedef struct RingBuffer *RingBuffer;
typedef int RingBufferDataType;                                 // set container data type 

RingBuffer getRingBufferInstance(uint32_t bufferSize);   // get initialized byteBuffer, provide buffer capacity

void ringBufferDelete(RingBuffer ringBuffer);                      // destroying the container
void ringBufferReset(RingBuffer ringBuffer);                       // set pointers to zero, and the data count, causing the buffer to be "empty"
bool isRingBufferFull(RingBuffer ringBuffer);                      // check that buffer is full
bool isRingBufferNotFull(RingBuffer ringBuffer);
bool isRingBufferEmpty(RingBuffer ringBuffer);                     // buffer empty if no data received
bool isRingBufferNotEmpty(RingBuffer ringBuffer);
uint32_t getRingBufferSize(RingBuffer ringBuffer);                 // return elements count in buffer

void ringBufferAdd(RingBuffer ringBuffer, RingBufferDataType value);       // add item to buffer
RingBufferDataType ringBufferGet(RingBuffer ringBuffer);      // get data from buffer, return item if buffer have value and NULL otherwise
